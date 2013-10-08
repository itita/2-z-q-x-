//
//  GXChatHandler.h
//  ww4
//
//  Created by xiao tang on 13-4-10.
//
//

#ifndef __ww4__GXChatHandler__
#define __ww4__GXChatHandler__

#include <iostream>
#include "cocos2d.h"
#include "GXMsg.h"
#include "GXString.h"

using namespace cocos2d;

typedef enum {
    PC_MSG_REQUEST = 0,
    PC_MSG_NOTIFY,
    PC_MSG_RESPONSE,
    PC_MSG_PUSH,
    PC_MSG_Route,
    PC_MSG_Chat
} pc_msg_type;

class GXChatInfoBean : public CCObject {
public:
    GXChatInfoBean():
    pid(-1),
    pkgType(-1),
    msgType(-1),
    base(NULL),
    compressRoute(0),
    len(-1),
    code(-1),
    host(NULL),
    port(-1),
    route_code(-1),
    route_str(NULL){
    };
    ~GXChatInfoBean() {
        if (base != NULL) {
            free(base);
        }
        if (host != NULL) {
            free(host);
        }
        if (route_str != NULL) {
            free(route_str);
        }
    }
    
    uint32_t pid;
    /*! Message type. */
    int pkgType;
    int msgType;
    /*! Compress flag of message route string. 0: not compress; 1: compres. */
    uint8_t compressRoute;
    /*! Rout information of message. Route string or code which decided by compressRoute. */
    int code;
    uint16_t route_code;
    char *route_str;
    static GXChatInfoBean* create();
    char* base;
    char* host;
    int port;
    int len;
    
};

class GXpc_buf_t : public CCObject{
    
public:
    GXpc_buf_t():len(-1),base(NULL) {}
    
    ~GXpc_buf_t() {
        if (base!=NULL) {
            free(base);
        }
    }
    
    static GXpc_buf_t* create();
    static GXpc_buf_t* create(char* base,unsigned long len);
    
    unsigned long len;
    char* base;
};

class GXChatHandler : public CCObject {
    
public:
    GXChatHandler():
    unionMsgArray(NULL),
    worldMsgArray(NULL),
    pomeloArray(NULL),
    isUnionNew(false),
    isWorldNew(false),
    routeType(0),
    cacheChatServerUrl(NULL),
    cacheInfoBean(NULL),
    initSucc(false){
    
    }
    
    bool initConnectPomelo(const char* hostName,int port);
    bool socketConnect(const char* hostName,int port);
    
    static GXChatHandler* getInstance();
//    void handleWorldMessage(GXMsg* msg);
//    void handleUnionMessage(GXMsg* msg);
    
    
    static void* acceptResponse(void *arg);
    GXChatInfoBean* socketRead();
    static CCArray* sendArray;
    bool socketWrite(char* str,unsigned long length);
    std::vector<char> recvBuffer;
    static bool isConn;
    CCArray* pomeloArray;
//    CCArray* toAddPomeloArray;
    static pthread_mutex_t pomeloMutex;
    static pthread_mutex_t sendMutex;
//    static pthread_mutex_t mutex;
    int socketHandle;
    static int sendFlag;
    void excuteMsg();
    void disconnectPomelo();
    static void* toSend(void *arg);
    void sendCmd(GXpc_buf_t* str);
    static void sendAll();
    void startPomelo(const char* host);
    
    void sendWorldChat(CCString* str);
    void sendUnionChat(CCString* str);
    void sendHandShake();
    void sendHandShakeAck();
    void sendGetRoute(const char* routeStr);
    void setHeartbeat(int tick);
    void sendAddUnion(const char* unionId);
    void sendExitUnion(const char* unionId);
    void sendDisconnect();
    void sendCutOffGatter();
    
    CCArray* unionMsgArray;
    CCArray* worldMsgArray;
    bool isUnionNew;
    bool isWorldNew;
    CC_PROPERTY(CCScheduler*, m_pScheduler, Scheduler);
    int routeType;
    CC_SYNTHESIZE_RETAIN(CCString*,cacheChatServerUrl,CacheChatServerUrl);
    CC_SYNTHESIZE_RETAIN(GXChatInfoBean*,cacheInfoBean,CacheInfoBean);
    bool initSucc;
private:
    static std::vector<char> sendBuffer;
    void sendHeartbeat();
};
#endif /* defined(__ww4__GXChatHandler__) */
