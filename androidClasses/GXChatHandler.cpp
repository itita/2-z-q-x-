//
//  GXChatHandler.cpp
//  ww4
//
//  Created by xiao tang on 13-4-10.
//
//

#include "GXChatHandler.h"
#include "GXUtil.h"
#include "GXString.h"
#include "MyJsonUtil.h"
#include "MyUtil.h"
#include "PulsarNative.h"

#include <netdb.h>
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include <sys/select.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#endif

#define bufSize 1000
#define waitSendTag 0
#define readySendTag 1
#define sendingTag 2
#define closeSendTag 3
#define startSendThreadTag 4


#define PC_PKG_TYPE_MASK 0xff
#define PC_PKG_TYPE_BYTES 1
#define PC_PKG_BODY_LEN_BYTES 3
#define PC_PKG_HEAD_BYTES (PC_PKG_TYPE_BYTES + PC_PKG_BODY_LEN_BYTES)
#define PC_PKG_MAX_BODY_BYTES (1 << 24)
#define pc__pkg_type(head) (head[0] & 0xff)
#define PC_HANDSHAKE_OK 200
#define PC_HEARTBEAT_TIMEOUT_FACTOR 2


#define PC_MSG_FLAG_BYTES 1
#define PC_MSG_ROUTE_LEN_BYTES 1
#define PC_MSG_ROUTE_CODE_BYTES 2
#define PC_MSG_HAS_ID(TYPE) ((TYPE) == PC_MSG_REQUEST ||                      \
(TYPE) == PC_MSG_RESPONSE)
#define PC_MSG_HAS_ROUTE(TYPE) ((TYPE) != PC_MSG_RESPONSE)
#define PC_MSG_VALIDATE(TYPE) ((TYPE) == PC_MSG_REQUEST ||                    \
(TYPE) == PC_MSG_NOTIFY ||                     \
(TYPE) == PC_MSG_RESPONSE ||                   \
(TYPE) == PC_MSG_PUSH)
//#define PC__MSG_CHECK_LEN(INDEX, LENGTH) do {                                 \
//if((INDEX) > (LENGTH)) {                                                    \
//goto error;                                                               \
//}                                                                           \
//}while(0);
#define PC_PB_EVAL_FACTOR 2



#define PC_MSG_FLAG_BYTES 1

#define PC_MSG_ROUTE_LEN_BYTES 1

#define PC_MSG_ROUTE_CODE_BYTES 2

#define PC_MSG_HAS_ID(TYPE) ((TYPE) == PC_MSG_REQUEST ||                      \
(TYPE) == PC_MSG_RESPONSE)

#define PC_MSG_HAS_ROUTE(TYPE) ((TYPE) != PC_MSG_RESPONSE)

#define PC_MSG_VALIDATE(TYPE) ((TYPE) == PC_MSG_REQUEST ||                    \
(TYPE) == PC_MSG_NOTIFY ||                     \
(TYPE) == PC_MSG_RESPONSE ||                   \
(TYPE) == PC_MSG_PUSH)

#define PC__MSG_CHECK_LEN(INDEX, LENGTH) do {                                 \
if((INDEX) > (LENGTH)) {                                                    \
if(msg) free(msg);if(route_str) free((void *)route_str);if(body) free(body);return NULL;                                                              \
}                                                                           \
}while(0);


bool GXChatHandler::isConn = false;
bool chatAcceptFlag = false;
int GXChatHandler::sendFlag = waitSendTag;
CCArray* GXChatHandler::sendArray = NULL;
static GXChatHandler* gchInstance;
//pthread_mutex_t GXChatHandler::mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t GXChatHandler::pomeloMutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t GXChatHandler::sendMutex = PTHREAD_MUTEX_INITIALIZER;
pthread_t chat_accept_id;
std::vector<char> GXChatHandler::sendBuffer;

int id = 0;

typedef struct pc_buf_t {
    unsigned long len;
    char* base;
} pc_buf_t;

typedef enum pc_pkg_type_e {
    PC_PKG_HANDSHAKE = 1,
    PC_PKG_HANDSHAKE_ACK,
    PC_PKG_HEARBEAT,
    PC_PKG_DATA,
    PC_PKG_KICK,
    PC_PKG_DISCONNCET
} pc_pkg_type;

//typedef enum {
//    PC_MSG_REQUEST = 0,
//    PC_MSG_NOTIFY,
//    PC_MSG_RESPONSE,
//    PC_MSG_PUSH
//} pc_msg_type;

pc_buf_t pc_pkg_encode(pc_pkg_type type, const char *data, size_t len) {
    pc_buf_t buf;
    
    
    size_t size = PC_PKG_HEAD_BYTES + len;
    buf.base = (char *)malloc(size);
    if(buf.base == NULL) {
//        fprintf(stderr, "Fail to malloc for Pomelo package, size: %lu.\n", size);
        buf.len = -1;
        return buf;
    }
    
    memset(buf.base, 0, size);
    
    buf.base[0] = type & PC_PKG_TYPE_MASK;
    char *base = buf.base + (PC_PKG_HEAD_BYTES - 1);
    
    if(len) {
        size_t body_size = len;
        int i;
        
        for(i=0; i<PC_PKG_BODY_LEN_BYTES; i++, base--) {
            *base = body_size % 0x100;
            body_size = body_size >> 8;
        }
        
        memcpy(buf.base + PC_PKG_HEAD_BYTES, data, len);
    } else {
        // body is empty
    }
    
    buf.len = size;
    
    return buf;
}

static uint8_t pc__msg_id_length(uint32_t id) {
    uint8_t len = 0;
    do {
        len += 1;
        id >>= 7;
    } while(id > 0);
    return len;
}

static inline size_t pc__msg_encode_flag(pc_msg_type type, int compressRoute,
                                         char *base, size_t offset) {
    base[offset++] = (type << 1) | (compressRoute ? 1 : 0);
    return offset;
}

static inline size_t pc__msg_encode_id(uint32_t id, char *base, size_t offset) {
    do{
        uint32_t tmp = id % 128;
        uint32_t next = id / 128;
        
        if(next != 0){
            tmp = tmp + 128;
        }
        base[offset++] = tmp;
        id = next;
    } while(id != 0);
    return offset;
    //    base = base+4;
    //    for(int i=0; i<4; i++, base--) {
    //        *base = id % 0x100;
    //        id >>= 8;
    //    }
    //    return 5;
}

static inline size_t pc__msg_encode_route(const char *route, uint16_t route_len,
                                          char *base, size_t offset) {
    base[offset++] = route_len & 0xff;
    
    memcpy(base + offset, route, route_len);
    
    return offset + route_len;
}

pc_buf_t pc_msg_encode_route(uint32_t id, pc_msg_type type,
                             const char *route, pc_buf_t msg) {
    pc_buf_t buf;
    
    memset(&buf, 0, sizeof(pc_buf_t));
    
    uint8_t id_len = PC_MSG_HAS_ID(type) ? pc__msg_id_length(id) : 0;
    uint16_t route_len = PC_MSG_HAS_ROUTE(type) ? strlen(route) : 0;
    
    //    size_t msg_len = PC_MSG_FLAG_BYTES + 4 + PC_MSG_ROUTE_LEN_BYTES +
    //    route_len + msg.len;
    size_t msg_len = PC_MSG_FLAG_BYTES + id_len + PC_MSG_ROUTE_LEN_BYTES +
    route_len + msg.len;
    
    char *base = buf.base = (char *)malloc(msg_len);
    
    if(buf.base == NULL) {
        buf.len = -1;
        if(buf.len != -1) free(buf.base);
        buf.len = -1;
        return buf;
    }
    
    size_t offset = 0;
    
    // flag
    offset = pc__msg_encode_flag(type, 0, base, offset);
    
    // message id
    if(PC_MSG_HAS_ID(type)) {
        offset = pc__msg_encode_id(id, base, offset);
    }
    
    // route
    if(PC_MSG_HAS_ROUTE(type)) {
        offset = pc__msg_encode_route(route, route_len, base, offset);
    }
    
    // body
    memcpy(base + offset, msg.base, msg.len);
    
    buf.len = msg_len;
    
    return buf;
    
}

GXChatInfoBean* pc_msg_decode(GXChatInfoBean* msg,const char *data, size_t len) {
    //    GXChatInfoBean *msg = NULL;
    char *route_str = NULL;
    char *body = NULL;
    
    //    msg = GXChatInfoBean::create();
    if(msg == NULL) {
        fprintf(stderr, "Fail to malloc for pc_raw_msg_t.\n");
        return NULL;
    }
    
    size_t offset = 0;
    
    PC__MSG_CHECK_LEN(offset + PC_MSG_FLAG_BYTES, len);
    // flag
    uint8_t flag = data[offset++];
    
    // type
    uint8_t type = (flag >> 1) & 0xff;
    
    if(!PC_MSG_VALIDATE(type)) {
        fprintf(stderr, "Unknown Pomleo message type: %d.\n", type);
        if(msg) free(msg);
        if(route_str) free((void *)route_str);
        if(body) free(body);
        return NULL;
    }
    
    msg->msgType = type;
    
    // compress flag
    uint8_t compressRoute = flag & 0x01;
    msg->compressRoute = compressRoute;
    
    // message id
    uint32_t id = 0;
    
    if(PC_MSG_HAS_ID(type)) {
        PC__MSG_CHECK_LEN(offset + 1, len);
        int i = 0;
        uint8_t m;
        do{
            m = data[offset++];
            id = id + ((m & 0x7f) * (1 << (7*i)));
            i++;
        }while(m >= 128);
    }
    msg->pid = id;
    
    // route
    if(PC_MSG_HAS_ROUTE(type)) {
        if(compressRoute) {
            PC__MSG_CHECK_LEN(offset + PC_MSG_ROUTE_CODE_BYTES, len);
            msg->route_code |= (data[offset++] & 0xff) << 8;
            msg->route_code |= data[offset++] & 0xff;
        } else {
            PC__MSG_CHECK_LEN(offset + PC_MSG_ROUTE_LEN_BYTES, len);
            size_t route_len = data[offset++];
            
            if(route_len) {
                route_str = (char *)malloc(route_len + 1);
                if(route_str == NULL) {
                    fprintf(stderr, "Fail to malloc for message route string.\n");
                    if(msg) free(msg);
                    if(route_str) free((void *)route_str);
                    if(body) free(body);
                    return NULL;
                }
                
                PC__MSG_CHECK_LEN(offset + route_len, len);
                memset(route_str, 0, route_len + 1);
                memcpy(route_str, data + offset, route_len);
                msg->route_str = route_str;
            }
            
            offset += route_len;
        }
    }
    
    // body
    size_t body_len = len - offset;
    if(body_len) {
        body = (char *)malloc(body_len+1);
        memcpy(body, data + offset, body_len);
        body[body_len] = 0;
    }
    msg->base = body;
    msg->len = body_len;
    
    return msg;
    
    //error:
    //    if(msg) free(msg);
    //    if(route_str) free((void *)route_str);
    //    if(body) free(body);
    //    return NULL;
}


GXChatHandler* GXChatHandler::getInstance(){
    if (gchInstance == NULL) {
        gchInstance = new GXChatHandler();
        //    conn->curl = curl_easy_init();
        gchInstance->unionMsgArray = CCArray::create();
        gchInstance->unionMsgArray->retain();
        gchInstance->worldMsgArray = CCArray::create();
        gchInstance->worldMsgArray->retain();
        gchInstance->pomeloArray = CCArray::create();
        gchInstance->pomeloArray->retain();
        gchInstance->sendArray = CCArray::create();
        gchInstance->sendArray->retain();
        //        gchInstance->toAddPomeloArray = CCArray::create();
        //        gchInstance->toAddPomeloArray->retain();
        
        gchInstance->m_pScheduler = CCDirector::sharedDirector()->getScheduler();
        gchInstance->m_pScheduler->retain();
        
        
        
//        free(buf.base);
    }
    return gchInstance;
}

void GXChatHandler::startPomelo(const char* host) {
//    const char* ip = ((CCString*)strs->objectAtIndex(0))->getCString();
    CCArray* strs = GXUtil::Split(host,":");
    const char* ip = ((CCString*)strs->objectAtIndex(0))->getCString();
    const char* portStr = ((CCString*)strs->objectAtIndex(1))->getCString();
    unsigned short port = (unsigned short)atoi(portStr);
    if(initConnectPomelo(ip,port)) {
        setCacheChatServerUrl(CCString::create(host));
        sendHandShake();
    }
}

void GXChatHandler::sendHandShake() {
    pc_buf_t buf = pc_pkg_encode(PC_PKG_HANDSHAKE,"{\"sys\":{\"version\":\"0.0.1\",\"type\":\"c\"}}",strlen("{\"sys\":{\"version\":\"0.0.1\",\"type\":\"c\"}}"));
    sendCmd(GXpc_buf_t::create(buf.base,buf.len));
}

void GXChatHandler::sendHandShakeAck() {
    pc_buf_t buf3 = pc_pkg_encode(PC_PKG_HANDSHAKE_ACK, NULL, 0);
    gchInstance->sendCmd(GXpc_buf_t::create(buf3.base,buf3.len));
}

void GXChatHandler::sendGetRoute(const char* routeStr) {
    pc_buf_t body;
    char str[100] = {0};
    sprintf(str,"{\"uid\":\"%d\",\"rid\":\"%d\",\"nickname\":\"%s\"}",PulsarNative::userId,PulsarNative::serverId,MyGameInfo::getInstance()->getNickName());
    body.base = str;
    body.len = strlen(str);
//    const char* routeStr = "gate.gateHandler.queryEntry";
    pc_buf_t buf = pc_msg_encode_route(1,PC_MSG_REQUEST,routeStr,body);
    
    pc_buf_t buf2 = pc_pkg_encode(PC_PKG_DATA,buf.base,buf.len);
    gchInstance->sendCmd(GXpc_buf_t::create(buf2.base,buf2.len));
 
    free(buf.base);
}

void GXChatHandler::excuteMsg() {
    pthread_mutex_lock(&GXChatHandler::pomeloMutex);
    CCObject* obj;
    CCARRAY_FOREACH(pomeloArray,obj) {
        GXChatInfoBean* bean = (GXChatInfoBean*)obj;
        if (bean->pkgType == PC_PKG_HANDSHAKE) {
//            pc_buf_t buf3 = pc_pkg_encode(PC_PKG_HANDSHAKE_ACK, NULL, 0);
//            gchInstance->sendCmd(GXpc_buf_t::create(buf3.base,buf3.len));
            sendHandShakeAck();
//            //            free(buf3.base);
//            pc_buf_t body;
//            char str[100] = {0};
//            sprintf(str,"{\"uid\":\"%d\",\"rid\":\"%d\"}",PulsarNative::userId,PulsarNative::serverId);
//            body.base = str;
//            body.len = strlen(str);
            const char* routeStr = "gate.gateHandler.queryEntry";
            if (routeType == 2) {
                routeStr = "connector.entryHandler.enter";
            }
            sendGetRoute(routeStr);
//            pc_buf_t buf = pc_msg_encode_route(1,PC_MSG_REQUEST,routeStr,body);
//            
//            pc_buf_t buf2 = pc_pkg_encode(PC_PKG_DATA,buf.base,buf.len);
//            gchInstance->sendCmd(GXpc_buf_t::create(buf2.base,buf2.len));
//            //            for (int i= 0; i < buf2.len ; i++) {
//            //                CCLog("%c,%d",buf2.base[i],buf2.base[i]);
//            //            }
//            free(buf.base);
            //        free(buf2.base);
        }else if (bean->pkgType == PC_PKG_DATA){
            if (bean->route_str && strcmp("onChat",bean->route_str) == 0) {
                StartScene* scene = dynamic_cast<StartScene*>(CCDirector::sharedDirector()->getRunningScene());
                GXMsg* msg = MyJsonUtil::parseChat(bean->base);
                if (scene != NULL && scene->isEnter == true) {
                    scene->addCharMsg(msg);
                } else {
                    worldMsgArray->addObject(msg);
                }
                msg->release();
            } else if(bean->route_str && strcmp("addUnion",bean->route_str) == 0) {
                if (MyGameInfo::getInstance()->getUnionBean()->getName()->compare("") != 0) {
                    sendAddUnion(MyGameInfo::getInstance()->getUnionBean()->getName()->getCString());
                }
            }
        } else if(bean->msgType == PC_MSG_Route) {
            routeType = 1;
//            initConnectPomelo(bean->host,bean->port);
//
//            sendHandShake();
            setCacheInfoBean(bean);
            sendCutOffGatter();
            
        }
        else if (bean->pkgType == PC_PKG_DISCONNCET) {
//            disconnectPomelo();
            if(routeType == 1 ){
                initConnectPomelo(getCacheInfoBean()->host,getCacheInfoBean()->port);
                setCacheInfoBean(NULL);
                sendHandShake();
                routeType = 2;
            } else {
                routeType = 0;
                worldMsgArray->removeAllObjects();
                unionMsgArray->removeAllObjects();
                CCLog("断过来了");
            }
        }
    }
    if(pomeloArray->count()>0) {
        pomeloArray->removeAllObjects();
    }
    
    
    pthread_mutex_unlock(&GXChatHandler::pomeloMutex);
}

void GXChatHandler::sendWorldChat(CCString* str2) {
    char str[1000] = {0};
    sprintf(str,"{\"from\":\"[世界] %s[%s]\",\"unionId\":\"-1\",\"content\":\"%s\"}",MyGameInfo::getInstance()->getNickName(),MyUtil::getInstance()->getRankString(MyGameInfo::getInstance()->getPower()),str2->getCString());
    pc_buf_t body;
    body.base = str;
    body.len = strlen(str);
    pc_buf_t buf1 = pc_msg_encode_route(1,PC_MSG_REQUEST,"chat.chatHandler.send",body);
    pc_buf_t buf2 = pc_pkg_encode(PC_PKG_DATA,buf1.base,buf1.len);
    sendCmd(GXpc_buf_t::create(buf2.base,buf2.len));
    free(buf1.base);
//    free(buf2.base);
}

void GXChatHandler::sendUnionChat(CCString* str2) {
    char str[1000] = {0};
    sprintf(str,"{\"from\":\"[联盟] %s[%s]\",\"unionId\":\"%s\",\"content\":\"%s\"}",MyGameInfo::getInstance()->getNickName(),MyUtil::getInstance()->getRankString(MyGameInfo::getInstance()->getPower()),MyGameInfo::getInstance()->getUnionBean()->getName()->getCString(),str2->getCString());
    pc_buf_t body;
    body.base = str;
    body.len = strlen(str);
    pc_buf_t buf1 = pc_msg_encode_route(1,PC_MSG_REQUEST,"chat.chatHandler.send",body);
    pc_buf_t buf2 = pc_pkg_encode(PC_PKG_DATA,buf1.base,buf1.len);
    sendCmd(GXpc_buf_t::create(buf2.base,buf2.len));
    free(buf1.base);
    //    free(buf2.base);
}

void GXChatHandler::sendAddUnion(const char* unionId) {
    if (!initSucc) {
        return;
    }
    char str[1000] = {0};
    sprintf(str,"{\"unionId\":\"%s\",\"msg\":\"联盟成员[%s]上线了\"}",unionId,MyGameInfo::getInstance()->getNickName());
    pc_buf_t body;
    body.base = str;
    body.len = strlen(str);
    pc_buf_t buf1 = pc_msg_encode_route(1,PC_MSG_REQUEST,"area.unionHandler.initUnion",body);
    pc_buf_t buf2 = pc_pkg_encode(PC_PKG_DATA,buf1.base,buf1.len);
    sendCmd(GXpc_buf_t::create(buf2.base,buf2.len));
    free(buf1.base);
}

void GXChatHandler::sendExitUnion(const char* unionId) {
    if (!initSucc) {
        return;
    }
    char str[1000] = {0};
    sprintf(str,"{\"unionId\":\"%s\"}",unionId);
    pc_buf_t body;
    body.base = str;
    body.len = strlen(str);
    pc_buf_t buf1 = pc_msg_encode_route(1,PC_MSG_REQUEST,"area.unionHandler.exitUnion",body);
    pc_buf_t buf2 = pc_pkg_encode(PC_PKG_DATA,buf1.base,buf1.len);
    sendCmd(GXpc_buf_t::create(buf2.base,buf2.len));
    free(buf1.base);
}

void GXChatHandler::sendDisconnect() {
    if(isConn) {
        pc_buf_t body;
        body.base = "{}";
        body.len = strlen("{}");
        pc_buf_t buf1 = pc_msg_encode_route(1,PC_MSG_REQUEST,"connector.entryHandler.exit",body);
        pc_buf_t buf2 = pc_pkg_encode(PC_PKG_DATA,buf1.base,buf1.len);
        sendCmd(GXpc_buf_t::create(buf2.base,buf2.len));
        free(buf1.base);
    } else {
        CCLog("聊天已经断开");
    }
}

void GXChatHandler::sendCutOffGatter() {
    if(isConn) {
        pc_buf_t body;
        char str[100] = {0};
        sprintf(str,"{\"uid\":\"%d\",\"rid\":\"%d\",\"nickname\":\"%s\"}",PulsarNative::userId,PulsarNative::serverId,MyGameInfo::getInstance()->getNickName());
        body.base = str;
        body.len = strlen(str);
        pc_buf_t buf1 = pc_msg_encode_route(1,PC_MSG_REQUEST,"gate.gateHandler.cutoffGater",body);
        pc_buf_t buf2 = pc_pkg_encode(PC_PKG_DATA,buf1.base,buf1.len);
        sendCmd(GXpc_buf_t::create(buf2.base,buf2.len));
        free(buf1.base);
    } else {
        CCLog("聊天已经断开");
    }
}

void GXChatHandler::setHeartbeat(int tick) {
    m_pScheduler->scheduleSelector(schedule_selector(GXChatHandler::sendHeartbeat), this, tick, kCCRepeatForever, 0, false);
}

bool GXChatHandler::initConnectPomelo(const char* hostName,int port) {
    if (!isConn) {
        int i =0;
        while (i<1) {
            isConn = this->socketConnect(hostName,port);
            if(isConn) {
                chatAcceptFlag = true;
                pthread_create(&chat_accept_id, NULL, GXChatHandler::acceptResponse, NULL);
                pthread_detach(chat_accept_id);
                m_pScheduler->scheduleSelector(schedule_selector(GXChatHandler::excuteMsg), this, 1, kCCRepeatForever, 0, false);
                
                return true;
            };
            i++;
        }
    } else {
        CCLog("这很危险");
        return true;
    }
    return false;
}

bool GXChatHandler::socketConnect(const char* hostName,int port) {
    struct sockaddr_in sa;
    struct hostent* hp;
    
    hp = gethostbyname(hostName);
    if(!hp){
        return false;
    }
    memset(&sa, 0, sizeof(sa));
    memcpy((char*)&sa.sin_addr, hp->h_addr, hp->h_length);
    sa.sin_family = hp->h_addrtype;
    sa.sin_port = htons(port);
    
    socketHandle = socket(sa.sin_family, SOCK_STREAM, 0);
    
    if(socketHandle < 0){
        printf( "failed to create socket\n" );
        return false;
    }
    if(::connect(socketHandle, (sockaddr*)&sa, sizeof(sa)) < 0){
        printf( "failed to connect socket\n" );
        ::close(socketHandle);
        return false;
    }
    //    CCLog("Client connect OK ！ IP: %s:%d ",ip,port);
    return true;
}



void* GXChatHandler::acceptResponse(void *arg) {
    while (chatAcceptFlag) {
        GXChatInfoBean* bean =  GXChatHandler::getInstance()->socketRead();
        if (bean->route_str == NULL){
            MyJsonUtil::parseChatInfoBean(bean);
            if(bean->msgType == PC_MSG_Route) {
                bean->pkgType = -1;
//                GXChatHandler::getInstance()->disconnectPomelo();
            }
        }
        pthread_mutex_lock(&GXChatHandler::pomeloMutex);
        GXChatHandler::getInstance()->pomeloArray->addObject(bean);
        bean->release();
        pthread_mutex_unlock(&GXChatHandler::pomeloMutex);
        
    }
    pthread_exit(NULL);
    return 0;
}

GXChatInfoBean* GXChatHandler::socketRead() {
    recvBuffer.clear();
    char ptr[1000] = {0};
    int length = 4;
    while(length){
        int iRet = recv(socketHandle, ptr, length, 0);
        if(iRet <= 0) {
            GXChatInfoBean* bean = GXChatInfoBean::create();
            bean->pkgType = PC_PKG_DISCONNCET;
            disconnectPomelo();
            chatAcceptFlag = false;
            return bean;
        }
        recvBuffer.insert(recvBuffer.end(), ptr, ptr+iRet);
        length -= iRet;
    }
    char* cmdLengthStr = GXUtil::transCharVectorToCCString(&recvBuffer);
    size_t pkg_len = 0;
    GXChatInfoBean* bean = GXChatInfoBean::create();
    bean->pkgType = cmdLengthStr[0];
    for(int i=1; i<PC_PKG_HEAD_BYTES; i++) {
        if(i > 1) {
            pkg_len <<= 8;
        }
        pkg_len += cmdLengthStr[i] & 0xff;
    }
    free(cmdLengthStr);
//    CCLog("接收的长度是：%d",pkg_len);
    
    if (pkg_len == 0) {
//        CCLog("空串过来了");
        bean->pkgType = PC_PKG_HEARBEAT;
        return bean;
    }
    recvBuffer.clear();
    int ptrLength = -1;
    int pag_lenback = pkg_len;
    while(pkg_len){
        if (pkg_len < bufSize) {
            ptrLength = pkg_len;
        } else {
            ptrLength = bufSize;
        }
        int iRet = recv(socketHandle, ptr, ptrLength, 0);
        if(iRet <= 0) {
            bean->pkgType = PC_PKG_DISCONNCET;
            disconnectPomelo();
            chatAcceptFlag = false;
            return bean;
        }
        recvBuffer.insert(recvBuffer.end(), ptr, ptr+iRet);
        //        CCLog("本次缓冲长度%d,缓冲大小%s",iRet,ptr);
        pkg_len -= iRet;
    }
    if (bean->pkgType == PC_PKG_DATA) {
        char* str21 =GXUtil::transCharVectorToCCString(&recvBuffer);
        pc_msg_decode(bean,str21,pag_lenback);
        free(str21);
//        CCLog("接受的内容为:%s,长度1:%d,长度2:%d",bean->base,strlen(bean->base),bean->len);
    } else {
        bean->base = GXUtil::transCharVectorToCCString(&recvBuffer);
//        CCLog("接受的内容为:%s,长度1:%d,长度2:%d",bean->base,strlen(bean->base),bean->len);
    }
    return bean;
}

void GXChatHandler::sendCmd(GXpc_buf_t* str) {
    if (isConn) {
        //连接了在加，免得会加入很多不必要的因素
        pthread_mutex_lock(&GXChatHandler::sendMutex);
        sendArray->addObject(str);
        str->release();
//        if (sendFlag == waitSendTag) {
//            sendFlag = readySendTag;
//        }
        if (GXChatHandler::sendFlag == waitSendTag) {
            GXChatHandler::sendFlag = startSendThreadTag;
            pthread_t send_id;
            pthread_create(&send_id, NULL, GXChatHandler::toSend, NULL);
            pthread_detach(send_id);
        }
        pthread_mutex_unlock(&GXChatHandler::sendMutex);
//        CCLog("发送：%s",str->base);
    }
}


void* GXChatHandler::toSend(void *arg) {
    if (!isConn) {
        pthread_exit(NULL);
        return 0;
    }
    while (sendFlag == startSendThreadTag) {
        sendAll();
    }
    pthread_exit(NULL);
    return 0;
}

void GXChatHandler::sendAll() {
    if (sendArray->count() <= 0) {
        CCLog("发送为空还发个JB");
        pthread_mutex_unlock(&GXChatHandler::sendMutex);
        GXChatHandler::sendFlag = waitSendTag;
        pthread_mutex_unlock(&GXChatHandler::sendMutex);
        return;
    }
//    sendBuffer.clear();
    
    GXpc_buf_t* tempStr;
    sendBuffer.clear();
    pthread_mutex_lock(&GXChatHandler::sendMutex);
//    int len = 0;
    for (int i = 0; i<sendArray->count(); i++) {
        tempStr = (GXpc_buf_t*)sendArray->objectAtIndex(i);
        sendBuffer.insert(sendBuffer.end(), tempStr->base, tempStr->base+tempStr->len);
//        len+=tempStr->len;
    }
    sendArray->removeAllObjects();
//    CCLog("len:%d，buf:%d",len,sendBuffer.size());
    GXChatHandler::sendFlag = sendingTag;
    pthread_mutex_unlock(&GXChatHandler::sendMutex);
    char* sendStr = GXUtil::transCharVectorToCCString(&sendBuffer);
    GXChatHandler::getInstance()->socketWrite(sendStr,sendBuffer.size());
    pthread_mutex_lock(&GXChatHandler::sendMutex);
    if (sendArray->count() >0) {
        sendFlag = startSendThreadTag;
    } else {
        sendFlag = waitSendTag;
    }
    pthread_mutex_unlock(&GXChatHandler::sendMutex);
//    for (int i = 0; i<sendArray->count(); i++) {
//        pthread_mutex_lock(&GXChatHandler::sendMutex);
//        tempStr = (GXpc_buf_t*)sendArray->objectAtIndex(i);
//        GXChatHandler::sendFlag = sendingTag;
//        pthread_mutex_unlock(&GXChatHandler::sendMutex);
//        GXChatHandler::getInstance()->socketWrite(tempStr->base,tempStr->len);
////        CCLog("发送内容是:%s",tempStr->base);
//    }
//    
//    pthread_mutex_lock(&GXChatHandler::sendMutex);
//    sendArray->removeAllObjects();
//    sendFlag = waitSendTag;
//    pthread_mutex_unlock(&GXChatHandler::sendMutex);
    return;
}

bool GXChatHandler::socketWrite(char* str,unsigned long length) {
    //    int length = strlen(str);
    char *p = str;
    while(length){
        int iRet = send(socketHandle,p,length,0);
        if(iRet <= 0) {
            CCLog("发送失败,代码:%d",iRet);
            return false;
        }
        p += iRet;
        length -= iRet;
    }
    return true;
}

void GXChatHandler::disconnectPomelo() {
    if(socketHandle!=-1) {
        ::shutdown(socketHandle,2);
        ::close(socketHandle);
        socketHandle = -1;
    }
    initSucc = false;
    chatAcceptFlag = false;
    isConn = false;
}

void GXChatHandler::sendHeartbeat() {
    pc_buf_t buf = pc_pkg_encode(PC_PKG_HEARBEAT, NULL, 0);
    sendCmd(GXpc_buf_t::create(buf.base,buf.len));
}


//void GXChatHandler::handleUnionMessage(GXMsg* msg) {
//    //    printf("上所前");
//    int ret = pthread_mutex_lock(&GXChatHandler::mutex);
//    CCAssert(ret == 0, "lock error ,error code ");
//    //    CCLog("有没有锁，有没有锁啊？");、
//    //    printf( "上锁后%s说：%s\n", msg.from().resource().c_str(), msg.body().c_str());
//    unionMsgArray->addObject(msg);
//    msg->release();
//    GXChatHandler::isUnionNew = true;
//    pthread_mutex_unlock(&GXChatHandler::mutex);
//}

//void GXChatHandler::handleWorldMessage(GXMsg* msg) {
//    //    printf("上所前");
//    int ret = pthread_mutex_lock(&GXChatHandler::mutex);
//    CCAssert(ret == 0, "lock error ,error code ");
//    //    CCLog("有没有锁，有没有锁啊？");、
//    //    printf( "上锁后%s说：%s\n", msg.from().resource().c_str(), msg.body().c_str());
//    worldMsgArray->addObject(msg);
//    msg->release();
//    GXChatHandler::isWorldNew = true;
//    pthread_mutex_unlock(&GXChatHandler::mutex);
//}

CCScheduler* GXChatHandler::getScheduler()
{
    return m_pScheduler;
}

void GXChatHandler::setScheduler(CCScheduler* scheduler)
{
    if( scheduler != m_pScheduler ) {
        //        this->unscheduleAllSelectors();
        CC_SAFE_RETAIN(scheduler);
        CC_SAFE_RELEASE(m_pScheduler);
        m_pScheduler = scheduler;
    }
}

GXChatInfoBean* GXChatInfoBean::create() {
    GXChatInfoBean* bean = new GXChatInfoBean();
    return bean;
}

GXpc_buf_t* GXpc_buf_t::create() {
    GXpc_buf_t* BUF = new GXpc_buf_t();
    return BUF;
}

GXpc_buf_t* GXpc_buf_t::create(char* base,unsigned long len) {
    GXpc_buf_t* BUF = new GXpc_buf_t();
    BUF->base = base;
    BUF->len = len;
    return BUF;
}
