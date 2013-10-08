    //
//  MyHttpConnection.cpp
//  ww2
//
//  Created by DingYu Fu on 12-9-16.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "MyHttpConnection.h"
#include "cocos2d.h"
//#include "curl/curl.h"
#include "PulsarNative.h"
#include "MyGameInfo.h"
#include "GXUtil.h"
#include "MyJsonUtil.h"
#include "cocos-ext.h"
//#include "openssl/bio.h"
//#include "openssl/ssl.h"
//#include "openssl/err.h"

#include <netdb.h>
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include <sys/select.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#endif

#include <pthread.h>
#include "DefineSet.h"
#include "MyGameFactory.h"
#include "GXString.h"
#include "GXMessage.h"
#include "GXInteger.h"
#include "MyUtil.h"
#include "ServerScene.h"
#include "ResendOrder.h"

using namespace cocos2d;
using namespace extension;

#define bufSize 1000
#define waitSendTag 0
#define readySendTag 1
#define sendingTag 2
#define closeSendTag 3
#define startSendThreadTag 4

static MyHttpConnection* mhcInstance;
CCArray* MyHttpConnection::sendArray = NULL;
pthread_mutex_t MyHttpConnection::sendMutex = PTHREAD_MUTEX_INITIALIZER;
std::vector<char> MyHttpConnection::sendBuffer;
int MyHttpConnection::sendFlag = waitSendTag;
bool acceptFlag = false;
bool MyHttpConnection::isConn = false;
bool MyHttpConnection::isSendMsg = true;

pthread_t accept_id;
//pthread_t send_id;

MyHttpConnection* MyHttpConnection::getInstance(){
    if (mhcInstance == NULL) {
        mhcInstance = MyHttpConnection::create();
    }
    return mhcInstance;
}

//bool MyHttpConnection::initSSL(const char* sslSocketUrl,int _serverId) {
//    if (!isSSLConn) {
//        curl_global_init(CURL_GLOBAL_ALL);
//        SSL_load_error_strings();
//        ERR_load_BIO_strings();
//        SSL_library_init();
//        OpenSSL_add_all_algorithms();
//        OpenSSL_add_all_ciphers();
//        int i =0;
//        while (i<1) {
//            isSSLConn = mhcInstance->sslSocketConnect(sslSocketUrl);
//            if(isSSLConn) {
//                setCacheHostUrl(CCString::create(sslSocketUrl));
//                PulsarNative::serverId = _serverId;
////                CCLog("服务器Id是：%d",_serverId);
////                char str[500] = {0};
////                sprintf(str,"{\"cmd\":\"user.login\",\"nickName\":\"%s\",\"ititaId\":\"%s\", \"pwd\":\"*xkkkIIkksafasdfjk((LLLLIIIIjjjsadf+_oo1544@$x\"}\n\r", MyGameInfo::getInstance()->getNickName(),PulsarNative::getItitaId());
////                mhcInstance->sslWrite(str);
//                acceptFlag = true;
//                pthread_create(&accept_id, NULL, MyHttpConnection::acceptResponse, NULL);
//                pthread_detach(accept_id);
//                m_pScheduler->scheduleSelector(schedule_selector(MyHttpConnection::scan), this, sendScanRate, false, kCCRepeatForever, 0);
//                m_pScheduler->scheduleSelector(schedule_selector(MyHttpConnection::sendHeartbeat), this, 120, false, kCCRepeatForever, 0);
////                scan->schedule(schedule_selector(ScanSchedule::scan),sendScanRate);
////                scan->schedule(schedule_selector(ScanSchedule::sendHeartbeat),120);
//                return true;
//            };
//            i++;
//        }
//    } else {
//        return true;
//    }
//    return false;
//}

bool MyHttpConnection::initSocket(const char* socketUrl,int _serverId) {
    if (!isConn) {
//        curl_global_init(CURL_GLOBAL_ALL);
        int i =0;
        CCArray* strs = GXUtil::Split(socketUrl,":");
        const char* ip = ((CCString*)strs->objectAtIndex(0))->getCString();
        const char* portStr = ((CCString*)strs->objectAtIndex(1))->getCString();
        unsigned short port = (unsigned short)atoi(portStr);
        while (i<1) {
            isConn = mhcInstance->socketConnect(ip,port);
            if(isConn) {
                setCacheHostUrl(CCString::create(socketUrl));
                PulsarNative::serverId = _serverId;
                //                CCLog("服务器Id是：%d",_serverId);
                //                char str[500] = {0};
                //                sprintf(str,"{\"cmd\":\"user.login\",\"nickName\":\"%s\",\"ititaId\":\"%s\", \"pwd\":\"*xkkkIIkksafasdfjk((LLLLIIIIjjjsadf+_oo1544@$x\"}\n\r", MyGameInfo::getInstance()->getNickName(),PulsarNative::getItitaId());
                //                mhcInstance->sslWrite(str);
                acceptFlag = true;
                pthread_create(&accept_id, NULL, MyHttpConnection::acceptResponse, NULL);
                pthread_detach(accept_id);
                m_pScheduler->scheduleSelector(schedule_selector(MyHttpConnection::scan), this, sendScanRate, kCCRepeatForever, 0, false);
                m_pScheduler->scheduleSelector(schedule_selector(MyHttpConnection::sendHeartbeat), this, 30, kCCRepeatForever, 0, false);
                //                scan->schedule(schedule_selector(ScanSchedule::scan),sendScanRate);
                //                scan->schedule(schedule_selector(ScanSchedule::sendHeartbeat),120);
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

void MyHttpConnection::release() {
//    curl_easy_cleanup(mhcInstance->curl);
    CC_SAFE_RELEASE_NULL(mhcInstance);
    mhcInstance=NULL;
}



//bool MyHttpConnection::post(CCString *var,CCString* url) {
//    
//    CURLcode res;
//    curl = curl_easy_init();
////    CCLog(url->getCString());
//    if (curl)
//    {
//        
//        curl_easy_setopt(curl, CURLOPT_VERBOSE, 1);
//        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, var->getCString());
//        curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, var->length());
//        curl_easy_setopt(curl, CURLOPT_URL, url->getCString());
//        res = curl_easy_perform(curl);
//        /* always cleanup */
//        curl_easy_cleanup(curl);
//        if (res == 0)
//        {
//            //TODO something success
//            cocos2d::CCLog("conn succ");
//            return true;
//        }
//        else
//        {
//            //TODO something failed
//            cocos2d::CCLog("conn fail");
//            return false;
//        }
//    }
//    //    CC_SAFE_DELETE_ARRAY(var);
//    return false;
//}

//bool MyHttpConnection::postByClient(cocos2d::CCString *var, cocos2d::CCString *url) {
//    
//    cocos2d::extension::CCHttpRequest* request = new cocos2d::extension::CCHttpRequest();
//    request->setUrl(url->getCString());
//    request->setRequestType(cocos2d::extension::CCHttpRequest::kHttpPost);
//    //    request->setResponseCallback(this, callfuncND_selector(MyHttpConnection::onHttpRequestCompleted));
//    
//    // write the post data
//    //    const char* postData = "visitor=cocos2d&TestSuite=Extensions Test/NetworkTest";
//    request->setRequestData(var->getCString(), var->length());
//    
//    //    request->setTag(LOAD_DATA_ROME_SEVER);
//    cocos2d::extension::CCHttpClient::getInstance()->send(request);
//    request->release();
//    return true;
//}

void* MyHttpConnection::toSendbyPipline(void *arg) {
    if (!isConn) {
        pthread_exit(NULL);
        return 0;
    }
    sendbyPipline();
    pthread_exit(NULL);
    return 0;
}

void MyHttpConnection::sendbyPipline() {
    if (sendArray->count() <= 0) {
        CCLog("发送为空还发个JB");
        pthread_mutex_unlock(&MyHttpConnection::sendMutex);
        MyHttpConnection::sendFlag = waitSendTag;
        pthread_mutex_unlock(&MyHttpConnection::sendMutex);
        return;
    }
    sendBuffer.clear();
    int ret = pthread_mutex_lock(&MyHttpConnection::sendMutex);
    CCAssert(ret == 0, "lock error ,error code ");
    CCString* tempStr;
    for (int i = 0; i<sendArray->count(); i++) {
        tempStr = (CCString*)sendArray->objectAtIndex(i);
        sendBuffer.insert(sendBuffer.end(), tempStr->getCString(), tempStr->getCString()+tempStr->length());
    }
    sendArray->removeAllObjects();
    MyHttpConnection::sendFlag = sendingTag;
    pthread_mutex_unlock(&MyHttpConnection::sendMutex);
    char* sendStr = GXUtil::transCharVectorToCCString(&sendBuffer);
    if (MyHttpConnection::getInstance()->socketWrite(sendStr)) {
        pthread_mutex_lock(&MyHttpConnection::sendMutex);
//        CCAssert(ret == 0, "lock error ,error code ");
        if (sendArray->count() >0) {
            sendFlag = readySendTag;
        } else {
            sendFlag = waitSendTag;
        }
        pthread_mutex_unlock(&MyHttpConnection::sendMutex);
    } else {
        pthread_mutex_lock(&MyHttpConnection::sendMutex);
//        CCAssert(ret == 0, "lock error ,error code ");
//        if(strlen(sendStr) > 0) {
//        	sendFlag = readySendTag;
//			GXString* lastStr = GXString::create(sendStr);
//			sendArray->addObject(lastStr);
//			lastStr->release();
			CCLog("发送失败~不重发了：%s",sendStr);
//        } else {
//        	sendFlag = waitSendTag;
//        }
        if (sendArray->count() >0) {
            sendFlag = readySendTag;
        } else {
            sendFlag = waitSendTag;
        }
        
        pthread_mutex_unlock(&MyHttpConnection::sendMutex);
    };
//    CCLog("发送内容是:%s",sendStr);
    free(sendStr);
    return;
}


void* MyHttpConnection::acceptResponse(void *arg) {
    while (acceptFlag) {
        //        MyHttpConnection::getInstance()->sslRead();
//        CCLog("%s",MyHttpConnection::getInstance()->sslRead());
        MyBaseMessage* msg =  MyGameFactory::getMessageByCommander(MyHttpConnection::getInstance()->socketRead());
        if (isSendMsg && msg) {
            msg->sendMsg();
        }
       
    }
    pthread_exit(NULL);
    return 0;
}



MyHttpConnection* MyHttpConnection::create() {
    MyHttpConnection* conn = new MyHttpConnection();
    //    conn->curl = curl_easy_init();
    conn->m_pScheduler = CCDirector::sharedDirector()->getScheduler();
    conn->m_pScheduler->retain();
    sendArray = CCArray::create();
    sendArray->retain();
    //    GXUtil::IsBigOrSmall();
    return conn;
}

//size_t write_data(void *ptr, size_t size, size_t nmemb, void *stream)
////这个函数是为了符合CURLOPT_WRITEFUNCTION, 而构造的
//{
//    CCLog("我日你家哥");
//    return NULL;
//}



//CCString* MyHttpConnection::get(CCString *url){
//    CURLcode res;
//    curl = curl_easy_init();
//    if (curl)
//    {
//        temp = "";
//        //        curl_easy_setopt(curl, CURLOPT_URL, "http://192.168.0.103:8080/DEFENDDIAOYUISLAND/servlet/updategamedata");
//        //        char str[400] = {0};
//        //        sprintf(str, "itita_id=%s",PulsarNative::getDeviceId());
//        //        curl_easy_setopt(curl, CURLOPT_VERBOSE, 1);
//        //        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, str);
//        //        curl_easy_setopt(curl, CURLoption option, ...);
////        CCLog(url->getCString());
//        curl_easy_setopt(curl, CURLOPT_URL, url->getCString());
//        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
//        curl_easy_setopt(curl,CURLOPT_WRITEDATA,&temp);
//        
//        //        CURLOPT_DEBUGFUNCTION
//        //        curl_easy_setopt(curl,CURLOPT_DEBUGFUNCTION,debug_callback);
//        res = curl_easy_perform(curl);
//        /* always cleanup */
//        curl_easy_cleanup(curl);
//        
//        if (res == 0)
//        {
//            cocos2d::CCLog("conn succ");
//            int k = 0;
//            for (k =temp.length()-1; k>=0; --k) {
//                //        char a = str2.at(k);
//                if ( temp.at(k) ==  '0' || temp.at(k) =='\r' || temp.at(k) =='\n') {
//                    continue;
//                } else {
//                    break;
//                }
//            }
//            temp = temp.substr(0,k+1);
//            std::string result(temp);
//            temp.clear();
//            return CCString::create(result);
//        }
//        else
//        {
//            //TODO something failed
//            cocos2d::CCLog("conn fail");
//            return CCString::create("failed");
//        }
//    }
//    CCAssert(curl!=NULL, "curl is NULL");
//    return CCString::create("failed");
//}
//
//size_t write_data(char *ptr, size_t size, size_t nmemb, std::string *writerData)
////这个函数是为了符合CURLOPT_WRITEFUNCTION, 而构造的
//{
//    
//    if (writerData == NULL)
//        return 0;
//    if(strcmp(ptr, "") != 0) {
//        //        CCLog(ptr);
//        //        MyHttpConnection::getInstance()->temp = ptr;
//        writerData->append(ptr,size*nmemb);
//    }
//    //    CCLog(ptr);
//    
//    //    CCLog(str);
//    //    MyHttpConnection::getInstance()->temp = new char[65535];
//    //    sprintf(MyHttpConnection::getInstance()->temp, "%s",ptr);
//    //    CC_SAFE_DELETE_ARRAY(ptr);
//    return size*nmemb;
//}
//
//int debug_callback (CURL * url, curl_infotype type, char * chr, size_t t, void * ptr) {
//    CCLog(chr);
//    return 1;
//}

//CCString* MyHttpConnection::getStartSceneData() {
//    std::string str("");
//    str.append(loadStartSceneUrl)
//    .append("?itita_id=")
//    .append(PulsarNative::getDeviceId());
//    //    sprintf(str, "%s?itita_id=%s",loadStartSceneUrl,PulsarNative::getDeviceId());
//    CCString* response = MyHttpConnection::getInstance()->get(CCString::create( str));
//    //    CCLog(response);
//    return response;
//}
//
//CCString* MyHttpConnection::getStartSceneData(bool isCreator) {
//    std::string str("");
//    str.append(loadStartSceneUrl)
//    .append("?itita_id=")
//    .append(PulsarNative::getDeviceId())
//    .append("&attachCreatorStyle=true");
//    CCString* response = MyHttpConnection::getInstance()->get(CCString::create(str));
//    //    CCLog(response);
//    return response;
//}
//
//bool MyHttpConnection::updateStartSceneData(CCString* updateJson) {
//    char str2[40] = {0};
//    std::string str("");
//    str.append("itita_id=")
//    .append(PulsarNative::getDeviceId())
//    .append("&build_style=")
//    .append(updateJson->getCString())
//    .append("&oil=");
//    sprintf(str2, "%d",(int)MyGameInfo::getInstance()->getDeltaOil());
//    str.append(str2)
//    .append("&iron=");
//    sprintf(str2, "%d",(int)MyGameInfo::getInstance()->getDeltaIron());
//    str.append(str2)
//    .append("&creator_style=")
//    .append(MyJsonUtil::packAllCreator()->getCString())
//    .append("&level=");
//    sprintf(str2, "%lld",MyGameInfo::getInstance()->getExperience());
//    str.append(str2)
//    .append("&glory=");
//    sprintf(str2,"%d",(int)MyGameInfo::getInstance()->getDeltaGlory());
//    str.append(str2);
//    
//    //    CCLog("exp:%ld",MyGameInfo::getInstance()->experience);
//    MyGameInfo::getInstance()->initDelta();
//    return MyHttpConnection::getInstance()->post(CCString::create(str),CCString::create(updateStartSceneUrl));
//}
//
//void MyHttpConnection::updateStartSceneDataAsynchronous(CCString* updateJson,CCObject* pTarget, SEL_CallFuncND pSelector) {
//    char str2[40] = {0};
//    std::string str("");
//    str.append("itita_id=")
//    .append(PulsarNative::getDeviceId())
//    .append("&build_style=")
//    .append(updateJson->getCString())
//    .append("&oil=");
//    sprintf(str2, "%d",(int)MyGameInfo::getInstance()->getDeltaOil());
//    str.append(str2)
//    .append("&iron=");
//    sprintf(str2, "%d",(int)MyGameInfo::getInstance()->getDeltaIron());
//    str.append(str2)
//    .append("&creator_style=")
//    .append(MyJsonUtil::packAllCreator()->getCString())
//    .append("&level=");
//    sprintf(str2, "%lld",MyGameInfo::getInstance()->getExperience());
//    str.append(str2)
//    .append("&glory=");
//    sprintf(str2,"%d",(int)MyGameInfo::getInstance()->getDeltaGlory());
//    str.append(str2);
//    
//    MyGameInfo::getInstance()->initDelta();
//    
//    CCHttpRequest* request = new CCHttpRequest();
//    request->setUrl(updateStartSceneUrl);
//    request->setRequestType(CCHttpRequest::kHttpPost);
//    std::vector<std::string> headers;
//    headers.push_back("Content-Type: application/json; charset=utf-8");
//    request->setHeaders(headers);
//    request->setResponseCallback(pTarget, pSelector);
//    
//    request->setRequestData(str.c_str(), str.length());
//    
//    CCHttpClient::getInstance()->send(request);
//    request->release();
//    
//}
//
//CCString* MyHttpConnection::getOtherData() {
//    char str[400] = {0};
//    sprintf(str, "%s?itita_id=%s",getOtherDataUrl, PulsarNative::getDeviceId());
//    //    sprintf(str, "%s?itita_id=865411013906550",loadStartSceneUrl);
//    return get(CCString::create(str));
//}
//
//bool MyHttpConnection::addMatch(bool isWin,float robberOil,float roberIron,CCString* unitJson,CCString* note) {
//    char var [900] = {0};
//    if (isWin) {
//        sprintf(var, "itita_id=%s&defense_id=%s&won=true&trophy_oil=%d&trophy_iron=%d&unit_json=%s&note=%s",PulsarNative::getDeviceId(),MyGameInfo::getInstance()->getEnemyItitaId()->getCString(),(int)robberOil,(int)roberIron,unitJson->getCString(),note->getCString());
//    } else {
//        sprintf(var, "itita_id=%s&defense_id=%s&won=false&trophy_oil=%d&trophy_iron=%d&unit_json=%s&note=%s",PulsarNative::getDeviceId(),MyGameInfo::getInstance()->getEnemyItitaId()->getCString(),(int)robberOil,(int)roberIron,unitJson->getCString(),note->getCString());
//    }
//    return MyHttpConnection::getInstance()->post(CCString::create(var), CCString::create(addMatchUrl));
//}

//CCString* MyHttpConnection::getMyMatches() {
//    char url[500] = {0};
//    sprintf(url, "%s?itita_id=%s",getAllMatchesUrl,PulsarNative::getDeviceId());
//    return get(CCString::create(url));
//}
//
//CCString* MyHttpConnection::getNoReadedMatches() {
//    char url[500] ={0};
//    sprintf(url, "%s?itita_id=%s&action=NOTREADED",getWhoAttackMeUrl,PulsarNative::getDeviceId());
//    //    CCLog(url);
//    return get(CCString::create(url));
//}

//CCString* MyHttpConnection::getWhoAttackMeMatches() {
//    char url[500] ={0};
//    sprintf(url, "%s?itita_id=%s",getWhoAttackMeUrl,PulsarNative::getDeviceId());
//    //    CCLog(url);
//    return get(CCString::create(url));
//}



//CCString* MyHttpConnection::getOtherData(CCString *ititaId) {
//    char url [600] = {0};
//    sprintf(url, "%s?ititaId=%s",getOtherDataUrl,ititaId->getCString());
//    //    CCLog(url);
//    return get(CCString::create(url));
//}

//bool MyHttpConnection::updateResource(CCString *ititaId,bool isUpdateTime) {
//    char str[300]= {0};
//    sprintf(str, "itita_id=%s&oil=%d&iron=%d&glory=%d&update_time=false",ititaId->getCString(),(int)MyGameInfo::getInstance()->getDeltaOil(),(int)MyGameInfo::getInstance()->getDeltaIron(),(int)MyGameInfo::getInstance()->getDeltaGlory());
//    MyGameInfo::getInstance()->initDelta();
//    return MyHttpConnection::getInstance()->post(CCString::create(str),CCString::create(updateStartSceneUrl));
//}

//bool MyHttpConnection::updateBattleOtherData(CCString *updateJson) {
//    char str2[20] = {0};
//    std::string str("");
//    str.append("ititaId=")
//    .append(MyGameInfo::getInstance()->getEnemyItitaId()->getCString())
//    .append("&buildingStyle=")
//    .append(updateJson->getCString())
//    .append("&oil=");
//    sprintf(str2, "%d",(int)MyGameInfo::getInstance()->enemyDeltaOil);
//    str.append(str2)
//    .append("&iron=");
//    sprintf(str2, "%d",(int)MyGameInfo::getInstance()->enemyDeltaIron);
//    str.append(str2);
//    
//    MyGameInfo::getInstance()->enemyDeltaOil = 0;
//    MyGameInfo::getInstance()->enemyDeltaIron = 0;
//    return MyHttpConnection::getInstance()->post(CCString::create(str),CCString::create(UpdateOthersGameData));
//}

//CCString* MyHttpConnection::getConscrbeList() {
//    return MyHttpConnection::getInstance()->get(CCString::create(getConscribeListUrl));
//}
//
//
//CCString* MyHttpConnection::getUserData() {
//    char str[500] = {0};
//    sprintf(str, "%s?itita_id=%s",getUserDataUrl,PulsarNative::getDeviceId());
//    return get(CCString::create(str));
//}

//CCString* MyHttpConnection::getTopRank(int pageNo) {
//    char str[500] = {0};
//    sprintf(str, "%s?itita_id=%s&page_no=%d&page_size=20",getTopRankUrl,PulsarNative::getDeviceId(),pageNo);
//    return get(CCString::create(str));
//}

//CCString* MyHttpConnection::getAttackList() {
//    char str[500] = {0};
//    sprintf(str, "%s?itita_id=%s",getAttackListUrl,PulsarNative::getDeviceId());
//    return get(CCString::create(str));
//}
//
//CCString* MyHttpConnection::getRobDeltaTime() {
//    char str[500] = {0};
//    sprintf(str, "%s?itita_id=%s",getRobDeltaTimeUrl,PulsarNative::getDeviceId());
//    return get(CCString::create(str));
//}



//void apps_ssl_info_callback(const SSL *s, int where, int ret)
//{
//    const char *str;
//    int w;
//    w=where& ~SSL_ST_MASK;
//    if (w & SSL_ST_CONNECT) str="SSL_connect";
//    else if (w & SSL_ST_ACCEPT) str="SSL_accept";
//    else str="undefined";
//    if (where & SSL_CB_LOOP)
//    {
//        CCLog("%s:%s\n",str,SSL_state_string_long(s));
//    }
//    else if (where & SSL_CB_ALERT)
//    {
//        str=(where & SSL_CB_READ)?"read":"write";
//        CCLog("SSL3 alert %s:%s:%s\n",
//              str,
//              SSL_alert_type_string_long(ret),
//              SSL_alert_desc_string_long(ret));
//    }
//    else if (where & SSL_CB_EXIT)
//    {
//        if (ret == 0)
//            CCLog("%s:failed in %s\n",
//                  str,SSL_state_string_long(s));
//        else if (ret < 0)
//        {
//            CCLog("%s:error in %s\n",
//                  str,SSL_state_string_long(s));
//        }
//    }
//}

//bool MyHttpConnection::sslSocketConnect(const char* sslSocketUrl) {
//    SSL_CTX * ctx = SSL_CTX_new(SSLv3_client_method());
//    
//    if(!ctx) {
//    	CCLog("%s",ERR_reason_error_string(ERR_get_error()));
//    }
//    SSL * ssl;
//#if   (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
//    if(!SSL_CTX_load_verify_locations(ctx, CCFileUtils::sharedFileUtils()->fullPathFromRelativePath("tclient.pem"), NULL))
//#endif
//#if   (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
//        if(!SSL_CTX_load_verify_locations(ctx, "/data/data/com.itita.ww2/files/tclient.pem", NULL))
//#endif
//    {
//        CCLog("%s",ERR_reason_error_string(ERR_get_error()));
////        CCAssert(1 == 2, "PEM ERROR");
//    }
//    SSL_CTX_set_verify_depth(ctx, 1);
//    bio = BIO_new_ssl_connect(ctx);
//    CCAssert(bio != NULL,"bio not null");
//    BIO_get_ssl(bio, &ssl);
//    SSL_set_mode(ssl, SSL_MODE_AUTO_RETRY);
//    /* Attempt to connect */
//    BIO_set_conn_hostname(bio, sslSocketUrl);
//    /* Verify the connection opened and perform the handshake */
//    if(BIO_do_connect(bio) <= 0)
//    {
//        /* Handle failed connection */
//        CCLog("连接失败，释放数据，返回");
//        CCLog("%s",ERR_reason_error_string(ERR_get_error()));
//        SSL_CTX_free(ctx);
//        BIO_free(bio);
//        return false;
//    }
//    int rc = SSL_get_verify_result(ssl);
//    if(rc != X509_V_OK) {
//        if (rc == X509_V_ERR_DEPTH_ZERO_SELF_SIGNED_CERT || rc == X509_V_ERR_SELF_SIGNED_CERT_IN_CHAIN) {
//            CCLog("self signed certificate\n");
//        }
//        else {
//            CCLog("Certificate verification error: %ld\n", SSL_get_verify_result(ssl));
//            
//            SSL_CTX_free(ctx);
//            BIO_free(bio);
//            return false;
//        }
//    }
//    SSL_set_info_callback(ssl,apps_ssl_info_callback);
//    SSL_CTX_set_timeout(ctx, 150);
//    MyHttpConnection::sendFlag = waitSendTag;
//    return true;
//}

bool MyHttpConnection::socketConnect(const char* socketUrl, unsigned short port) {
    struct sockaddr_in sa;
    struct hostent* hp;
    
    hp = gethostbyname(socketUrl);
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
    MyHttpConnection::sendFlag = waitSendTag;
//    CCLog("Client connect OK ！ IP: %s:%d ",ip,port);
    return true;
}


//bool MyHttpConnection::sslWrite(char* str) {
//    if(BIO_write(bio, str, strlen(str)) <= 0)
//    {
//        if(! BIO_should_retry(bio))
//        {
//            CCLog("发送失败");
//        	CCLog("%s",ERR_reason_error_string(ERR_get_error()));
//            return false;
//        }
//        CCLog("发送失败");
//        CCLog("%s",ERR_reason_error_string(ERR_get_error()));
//        return false;
//    }
//    return true;
//}

bool MyHttpConnection::socketWrite(char* str) {
    int length = strlen(str);
    char *p = str;
    while(length){
        int iRet = send(socketHandle,p,length,0);
        if(iRet <= 0) {
            CCLog("发送失败");
            return false;
        }
        p += iRet;
        length -= iRet;
    }
    return true;
}

//char* MyHttpConnection::sslRead() {
//    recvBuffer.clear();
//    char ptr[bufSize] = {0};
//    int length = bufSize;
//    bool flag = true;
//    while (flag) {
//        length = BIO_read(bio, ptr, bufSize);
//        if(length == 0)
//        {
//            CCLog("连接关闭");
//            MyHttpConnection::sendFlag = closeSendTag;
//            MyHttpConnection::isSSLConn = false;
//            CCLog("%s",ERR_reason_error_string(ERR_get_error()));
//            char* str = (char*)malloc(strlen("{\"cmd\":\"system.disconnect\"}")*sizeof(char)+1);
//            strcpy(str,"{\"cmd\":\"system.disconnect\"}");
//            acceptFlag = false;
////            BIO_free(bio);
//            return str;
//        }
//        else if(length < 0)
//        {
//            if(! BIO_should_retry(bio))
//            {
//                /* Handle failed read here */
//                CCLog("连接失败");
//                CCLog("%s",ERR_reason_error_string(ERR_get_error()));
//            }
//            /* Do something to handle the retry */
//            CCLog("连接失败");
//            CCLog("%s",ERR_reason_error_string(ERR_get_error()));
//            char* str = (char*)malloc(strlen("{\"cmd\":\"system.disconnect\"}")*sizeof(char)+1);
//            strcpy(str,"{\"cmd\":\"system.disconnect\"}");
//            MyHttpConnection::sendFlag = closeSendTag;
//            MyHttpConnection::isSSLConn = false;
//            acceptFlag = false;
////            BIO_free(bio);
//            return str;
//        }
//        if (ptr[length-1] == '\r') {
//            flag = false;
//        }
//        recvBuffer.insert(recvBuffer.end(), ptr, ptr+length);
////        CCLog(ptr);
//    }
//    return GXUtil::transCharVectorToCCString(&recvBuffer);
//}

char* MyHttpConnection::socketRead() {
    recvBuffer.clear();
    char ptr[bufSize] = {0};
    int length = 6;
    while(length){
        int iRet = recv(socketHandle, ptr, length, 0);
        if(iRet <= 0) {
            return getDisconnectCmd();
        }
        recvBuffer.insert(recvBuffer.end(), ptr, ptr+iRet);
        length -= iRet;
    }
    char* cmdLengthStr = GXUtil::transCharVectorToCCString(&recvBuffer);
    int cmdLength = atoi(cmdLengthStr);
    free(cmdLengthStr);
//    CCLog("接收的长度是：%d",cmfdLength);
    
    if (cmdLength == 0) {
//        CCLog("空串过来了");
        char* str = (char*)malloc(strlen("2")*sizeof(char)+1);
        strcpy(str,"2");
        return str;
    }
    recvBuffer.clear();
    int ptrLength = -1;
    while(cmdLength){
        if (cmdLength < bufSize) {
            ptrLength = cmdLength;
        } else {
            ptrLength = bufSize;
        }
        int iRet = recv(socketHandle, ptr, ptrLength, 0);
        if(iRet <= 0) {
            return getDisconnectCmd();
        }
        recvBuffer.insert(recvBuffer.end(), ptr, ptr+iRet);
//        CCLog("本次缓冲长度%d,缓冲大小%s",iRet,ptr);
        cmdLength -= iRet;
    }
    
    return GXUtil::transCharVectorToCCString(&recvBuffer);
}

char* MyHttpConnection::getDisconnectCmd() {
    CCLog("连接失败");
    close(socketHandle);
    char* str = (char*)malloc(strlen("{\"cmd\":\"system.disconnect\"}")*sizeof(char)+1);
    strcpy(str,"{\"cmd\":\"system.disconnect\"}");
    MyHttpConnection::sendFlag = closeSendTag;
    MyHttpConnection::isConn = false;
    acceptFlag = false;
    //            BIO_free(bio);
    return str;
}

void MyHttpConnection::sendCreateUnionCmd(CCString* unionName, CCString* unionDes,CCString* emblemName) {
    char str[500] = {0};
    sprintf(str,"{\"cmd\":\"union.create\",\"name\":\"%s\",\"description\":\"%s\" ,\"emblem\":\"%s\"}\r\n",unionName->getCString(),unionDes->getCString(),emblemName->getCString());
    sendCmd(CCString::create(str));
}

void MyHttpConnection::readUnionByItitiaId() {
//    char str[500] = {0};
//    sprintf(str,"{\"cmd\":\"union.getByItitaId\"}\r\n",PulsarNative::getItitaId());
    sendCmd(CCString::create("{\"cmd\":\"union.getByItitaId\"}\r\n"));
}

void MyHttpConnection::sendNotice(CCString* notice) {
    char str[1000] = {0};
    sprintf(str,"{\"cmd\":\"union.publishNotice\", \"notice\":\"%s\", \"unionId\":\"%d\"}\r\n",notice->getCString(),MyGameInfo::getInstance()->getUnionBean()->unionId);
//    CCLog("%s",str);
    sendCmd(CCString::create(str));
}

void MyHttpConnection::sendJoinUnion(int unionId) {
    char str[1000] = {0};
    sprintf(str,"{\"cmd\":\"union.applyJoin\",\"extrasMsg\":\"\",\"unionId\":\"%d\"}\r\n",unionId);
//    CCLog("%s",str);
    sendCmd(CCString::create(str));
}

void MyHttpConnection::sendUnionChat(CCString* str2) {
    char str[1000] = {0};
    sprintf(str,"{\"cmd\":\"chat.union\",\"content\":\"%s\",\"speaker\":\"[联盟] %s[%s]\"}\r\n",str2->getCString(),MyGameInfo::getInstance()->getNickName(),MyUtil::getInstance()->getRankString(MyGameInfo::getInstance()->getPower()));
    sendCmd(CCString::create(str));
}

void MyHttpConnection::sendWorldChat(CCString* str2) {
    char str[1000] = {0};
    sprintf(str,"{\"cmd\":\"chat.world\",\"content\":\"%s\",\"speaker\":\"[世界] %s[%s]\"}\r\n",str2->getCString(),MyGameInfo::getInstance()->getNickName(),MyUtil::getInstance()->getRankString(MyGameInfo::getInstance()->getPower()));
    sendCmd(CCString::create(str));
}

void MyHttpConnection::sendGetOthers(int userId,bool isBySearch ) {
    char str[300] = {0};
    if (isBySearch) {
        sprintf(str,"{\"cmd\":\"gameData.getOthers\",\"userId\":\"%d\",\"action\":\"searchNick\"}\r\n",userId);
    } else {
        sprintf(str,"{\"cmd\":\"gameData.getOthers\",\"userId\":\"%d\"}\r\n",userId);
    }
    CCString* cache = CCString::create(str);
    setCecheCmd(cache);
    sendCmd(cache);
}

void MyHttpConnection::sendReplyApplicant(CCDictionary* varMap) {
    char str[1000] = {0};
//    CCLog("%s",((GXString*)msg->varMap->objectForKey("applicant"))->getCString());
//    CCLog("%d",((GXInteger*)msg->varMap->objectForKey("unionId"))->getValue());
    sprintf(str,"{\"cmd\":\"union.approveApply\",\"applicant\":\"%s\",\"agree\":\"%s\"}\r\n",((CCString*)varMap->objectForKey("applicant"))->getCString(),((CCString*)varMap->objectForKey("succ"))->compare("Y")==0?"true":"false");
//    CCLog("%s",str);
    sendCmd(CCString::create(str));
}

void MyHttpConnection::getAllUnionByPage(int pageNo, int pageSize) {
    char str[100] = {0};
    sprintf(str,"{\"cmd\":\"union.pagging\",\"pageSize\":\"%d\",\"pageIndex\":\"%d\"}\r\n",pageSize,pageNo);
//    CCLog("%s",str);
    sendCmd(CCString::create(str));
}

void MyHttpConnection::getAllMemberByPage(int pageNo,int pageSize) {
    char str[300] = {0};
    sprintf(str,"{\"cmd\":\"union.members\",\"pageSize\":\"%d\",\"pageIndex\":\"%d\"}\r\n",pageSize,pageNo);
//    CCLog("%s",str);
    sendCmd(CCString::create(str));
}

void MyHttpConnection::sendKickUnion(CCString* ititaId) {
    char str[400] = {0};
    sprintf(str,"{\"cmd\":\"union.remove\",\"removedMember\":\"%s\"}\r\n",ititaId->getCString());
//    CCLog("%s",str);
    sendCmd(CCString::create(str));
}

void MyHttpConnection::sendDisconnect() {
    char str[300] = {0};
    sprintf(str,"{\"cmd\":\"user.loginout\",\"validateCode\":\"sadfasdfkjklsdjgkjsadkgjklsajdgka*eI\"}\r\n");
    sendCmd(CCString::create(str));
}

void MyHttpConnection::sendDissolveUnion() {
    char str[300] = {0};
    sprintf(str,"{\"cmd\":\"union.dissolve\"}\r\n");
    //    CCLog(str);
    sendCmd(CCString::create(str));
}

//{"cmd":"union.exit","ititaId":"xisjsiskjikidkid","unionId","8"}

void MyHttpConnection::sendExitUnion() {
    char str[300] = {0};
    sprintf(str,"{\"cmd\":\"union.exit\"}\r\n");
//    CCLog(str);
    sendCmd(CCString::create(str));
}

void MyHttpConnection::sendLogin(CCObject* userBean,bool isReconn) {
    char str[400] = {0};
    if (isReconn) {
        sprintf(str,"{\"cmd\":\"user.login\", \"ititaId\":\"%s\", \"cipher\":\"%s\", \"pwd\":\"*xkkkIIkksafasdfjk((LLLLIIIIjjjsadf+_oo15\",\"deviceId\":\"%s\",\"ititaChannel\":\"%s\",\"version\":\"0\",\"isReconnect\":\"true\"}\r\n",((UserBean*)userBean)->getItitaId()->getCString(),((UserBean*)userBean)->getPassword()->getCString(),PulsarNative::getDeviceId(),PulsarNative::getItitaChannel());
    } else {
        sprintf(str,"{\"cmd\":\"user.login\", \"ititaId\":\"%s\", \"cipher\":\"%s\", \"pwd\":\"*xkkkIIkksafasdfjk((LLLLIIIIjjjsadf+_oo15\",\"deviceId\":\"%s\",\"ititaChannel\":\"%s\",\"version\":\"0\"}\r\n",((UserBean*)userBean)->getItitaId()->getCString(),((UserBean*)userBean)->getPassword()->getCString(),PulsarNative::getDeviceId(),PulsarNative::getItitaChannel());
    }
    sendCmd(CCString::create(str));
}

void MyHttpConnection::sendFastEnterGame(bool isReconn) {
    char str[400] = {0};
    if (isReconn) {
        sprintf(str,"{\"cmd\":\"user.loginNoRegister\",\"deviceId\":\"%s\",\"pwd\":\"*xkkkIIkksafasdfjk((LLLLIIIIjjjsadf+_oo15\",\"ititaChannel\":\"%s\",\"version\":\"0\",\"isReconnect\":\"true\"}\r\n",PulsarNative::getDeviceId(),PulsarNative::getItitaChannel());
    } else {
        sprintf(str,"{\"cmd\":\"user.loginNoRegister\",\"deviceId\":\"%s\",\"pwd\":\"*xkkkIIkksafasdfjk((LLLLIIIIjjjsadf+_oo15\",\"ititaChannel\":\"%s\",\"version\":\"0\"}\r\n",PulsarNative::getDeviceId(),PulsarNative::getItitaChannel());
    }
    sendCmd(CCString::create(str));
}

void MyHttpConnection::sendGetGameData(bool isCreateor) {
    char str[300] = {0};
    if (isCreateor) {
        sprintf(str,"{\"cmd\":\"gameData.getMyself\",\"attachCreatorStyle\":\"true\"}\r\n");
    } else {
        sprintf(str,"{\"cmd\":\"gameData.getMyself\"}\r\n");
    }
    CCString* cache = CCString::create(str);
    setCecheCmd(cache);
    sendCmd(cache);
}

void MyHttpConnection::sendRegister(CCObject* bean) {
    char str[600] = {0};
    sprintf(str,"{\"cmd\":\"user.register\",\"nickname\":\"%s\",\"ititaId\":\"%s\",\"cipher\":\"%s\",\"deviceId\":\"%s\",\"qq\":\"%s\",\"signature\":\"%s\",\"avatar\":\"%s\",\"pwd\":\"*xkkkIIkksafasdfjk((LLLLIIIIjjjsadf+_oo15\",\"ititaChannel\":\"%s\",\"version\":\"0\"}\r\n",((UserBean*)bean)->getNickname()->getCString(),((UserBean*)bean)->getItitaId()->getCString(),((UserBean*)bean)->getPassword()->getCString(),
            PulsarNative::getDeviceId(),((UserBean*)bean)->getQQ()->getCString(),((UserBean*)bean)->getSignature()->getCString(),((UserBean*)bean)->getAvatar()->getCString(),PulsarNative::getItitaChannel());
//    CCLog("长度是：%d",strlen(str));
//    CCLog(str);
    sendCmd(CCString::create(str));
}

void MyHttpConnection::sendUpdateGameData() {
    char str[200] = {0};
    sprintf(str,"{\"cmd\":\"gameData.updateMyself\",\"boardOil\":\"%d\",\"boardIron\":\"%d\",\"updateLastTime\":\"true\"}\r\n",(int)MyGameInfo::getInstance()->getOil(),(int)MyGameInfo::getInstance()->getInstance()->getIron());
//    MyGameInfo::getInstance()->initDelta();
    sendCmd(CCString::create(str));
}

//void MyHttpConnection::sendUpdateCreateStyle() {
//    char str[5000] = {0};
//    sprintf(str,"{\"cmd\":\"gameData.updateMyself\",\"ititaId\":\"%s\",\"creatorStyle\":\"%s\",\"updateLastTime\":\"false\"}\r\n",PulsarNative::getItitaId(),MyJsonUtil::packAllCreator()->getCString());
//    sendCmd(CCString::create(str));
//}

void MyHttpConnection::sendGetGameDataList() {
    char str[300] = {0};
    sprintf(str,"{\"cmd\":\"gameData.getGameDataList\"}\r\n");
    CCString* cache = CCString::create(str);
    setCecheCmd(cache);
    sendCmd(cache);
}

void MyHttpConnection::sendAddMatchInfo(bool isWin,float robberOil,float robberIron,CCString* unitJson,int attackType) {
    char str[10000] = {0};
    if (isWin) {
        if (attackType == 0) {
            sprintf(str,"{\"cmd\":\"match.addMatches\",\"defender\":\"%d\",\"won\":\"true\",\"trophyOil\":\"%d\",\"trophyIron\":\"%d\",\"unitJSON\":\"%s\"}\r\n",MyGameInfo::getInstance()->getEnemyUserId(),(int)robberOil,(int)robberIron,unitJson->getCString());
        } else if(attackType == 1) {
            sprintf(str,"{\"cmd\":\"match.addMatches\",\"defender\":\"%d\",\"won\":\"true\",\"trophyOil\":\"%d\",\"trophyIron\":\"%d\",\"unitJSON\":\"%s\",\"action\":\"searchNick\"}\r\n",MyGameInfo::getInstance()->getEnemyUserId(),(int)robberOil,(int)robberIron,unitJson->getCString());
        }
    } else {
        if (attackType == 0) {
            sprintf(str,"{\"cmd\":\"match.addMatches\",\"defender\":\"%d\",\"won\":\"false\",\"trophyOil\":\"%d\",\"trophyIron\":\"%d\",\"unitJSON\":\"\%s\"}\"}\r\n",MyGameInfo::getInstance()->getEnemyUserId(),(int)robberOil,(int)robberIron,unitJson->getCString());
        } else if(attackType == 1) {
            sprintf(str,"{\"cmd\":\"match.addMatches\",\"defender\":\"%d\",\"won\":\"false\",\"trophyOil\":\"%d\",\"trophyIron\":\"%d\",\"unitJSON\":\"\%s\",\"action\":\"searchNick\"}\"}\r\n",MyGameInfo::getInstance()->getEnemyUserId(),(int)robberOil,(int)robberIron,unitJson->getCString());
        }
    }
//    CCLog(str);
    sendCmd(CCString::create(str));
}

void MyHttpConnection::sendUpdateBattleOtherData(CCString* updateJson,int robberOil,int robberIron) {
    char str[30000] = {0};
    sprintf(str,"{\"cmd\":\"gameData.updateOthers\",\"userId\":\"%d\",\"buildingStyle\":\"%s\",\"deltaOil\":\"%d\",\"deltaIron\":\"%d\",\"robberOil\":\"%d\",\"robberIron\":\"%d\"}\r\n",MyGameInfo::getInstance()->getEnemyUserId(),updateJson->getCString(),(int)MyGameInfo::getInstance()->enemyDeltaOil,(int)MyGameInfo::getInstance()->enemyDeltaIron,robberOil*-1,robberIron*-1);
//    CCLog(str);
    MyGameInfo::getInstance()->enemyDeltaOil = 0;
    MyGameInfo::getInstance()->enemyDeltaIron = 0;
    sendCmd(CCString::create(str));
}

void MyHttpConnection::sendUpdateResource(long deltaOil,long deltaIron,long deltaGlory) {
    char str[200]= {0};
    sprintf(str, "{\"cmd\":\"gameData.changeResource\",\"deltaOil\":\"%ld\",\"deltaIron\":\"%ld\",\"deltaGlory\":\"%ld\"}\r\n",deltaOil,deltaIron,deltaGlory);
    sendCmd(CCString::create(str));
}

void MyHttpConnection::sendGetWhoAttackMeMatch(int type) {
    char str[300]= {0};
    if (type == -1) {
        sprintf(str, "{\"cmd\":\"match.getWhoAttackedMe\"}\r\n");
    } else if(type == 0) {
        sprintf(str, "{\"cmd\":\"match.getWhoAttackedMe\",\"won\":\"false\"}\r\n");
    } else if(type == 1) {
        sprintf(str, "{\"cmd\":\"match.getWhoAttackedMe\",\"won\":\"true\"}\r\n");
    }
    
    sendCmd(CCString::create(str));
}

void MyHttpConnection::sendGetNoReadedMatches() {
    char str[300]= {0};
    sprintf(str, "{\"cmd\":\"match.getWhoAttackedMe\",\"action\":\"NOTREADED\"}\r\n");
    sendCmd(CCString::create(str));
}

void MyHttpConnection::sendGetTopRank(int pageNo) {
    
    char str[300]= {0};
    sprintf(str, "{\"cmd\":\"gameData.getPowerRank\",\"pageNo\":\"%d\",\"pageSize\":\"20\"}\r\n",pageNo);
    sendCmd(CCString::create(str));
}


void MyHttpConnection::sendGetBoughtList() {
    char str[200] = {0};
    sprintf(str, "{\"cmd\":\"store.bought\"}\r\n");
    sendCmd(CCString::create(str));
}

//void MyHttpConnection::sendBuyList(CCArray* list) {
//    std::vector<char> strBuffer;
//    CCString* tempStr;
//    for (int i = 0; i<list->count(); i++) {
//        tempStr = (CCString*)list->objectAtIndex(i);
//        strBuffer.insert(strBuffer.end(), tempStr->getCString(), tempStr->getCString()+tempStr->length());
//    }
//    char* sendStr = GXUtil::transCharVectorToCCString(&strBuffer);
////    CCLog(sendStr);
//    sendCmd(CCString::create(sendStr));
//    free(sendStr);
//}

void MyHttpConnection::sendBuyResource(int tag) {
    char str[200] = {0};
    sprintf(str, "{\"cmd\":\"store.buy\",\"tag\":\"%d\"}\r\n",tag);
    sendCmd(CCString::create(str));
}

void MyHttpConnection::sendGetDefend(int level) {
    char str[200] = {0};
    sprintf(str, "{\"cmd\":\"gameData.getForDefend\", \"level\":\"%d\"}\r\n",level);
    sendCmd(CCString::create(str));
}

void MyHttpConnection::sendAddMatchNote(CCString* note) {
    char str[200] = {0};
    sprintf(str, "{\"cmd\":\"match.addMatchNote\",\"note\":\"%s\"}\r\n",note->getCString());
    sendCmd(CCString::create(str));
}

void MyHttpConnection::sendChangeNickName(const char* newName) {
//    {"cmd":"user.updateNickname", "nickname":"卡死求济公"}
    char str[200] = {0};
    sprintf(str, "{\"cmd\":\"user.updateNickname\",\"nickname\":\"%s\"}\r\n",newName);
    sendCmd(CCString::create(str));
}

void MyHttpConnection::sendGetDefendList() {
    char str[200] = {0};
    sprintf(str, "{\"cmd\":\"cpuwar.getCPUWarList\"}\r\n");
    sendCmd(CCString::create(str));
}

void MyHttpConnection::sendCecheCmd() {
    if (getCecheCmd() != NULL) {
        sendCmd(getCecheCmd());
    }
}

//void MyHttpConnection::sendAckDiamond() {
//    char str[200] = {0};
//    sprintf(str, "{\"cmd\":\"store.ackdiamond\", \"userId\":\"%d\"}\r\n",PulsarNative::userId);
//    sendCmd(CCString::create(str));
//}

void MyHttpConnection::sendCompleteQuest(int questTag) {
    char str[200] = {0};
    sprintf(str, "{\"cmd\":\"mission.finished\", \"userId\":\"%d\", \"missionId\":\"%d\",\"orderId\":\"%d\"}\r\n",PulsarNative::userId,questTag,maxOrderId);
    ResendOrder* cmd = ResendOrder::create(str,maxOrderId);
    maxOrderId++;
    gameDataListArray->addObject(cmd);
    sendCmd(cmd);
}

//void MyHttpConnection::sendUpdatePower(float powerCount) {
//    char str[100] = {0};
//    sprintf(str, "{\"cmd\":\"gameData.updatePower\", \"userId\":\"%d\", \"deltaPower\":\"%f\"}\r\n",PulsarNative::userId,powerCount);
//    sendCmd(CCString::create(str));
//}

void MyHttpConnection::sendUpdateMissionProgress(char* progressStr,int missionId) {
    char str[300] = {0};
    sprintf(str, "{\"cmd\":\"mission.progress\", \"userId\":\"%d\", \"missionId\":\"%d\",\"progressStr\":\"%s\"}\r\n",PulsarNative::userId,missionId,progressStr);
    sendCmd(CCString::create(str));
//    free(progressStr);
}

void MyHttpConnection::sendGetCpuWar() {
    char str[300] = {0};
    sprintf(str, "{\"cmd\":\"cpuwar.getCPUWar\", \"userId\":\"%d\"}\r\n",PulsarNative::userId);
    sendCmd(CCString::create(str));
}

void MyHttpConnection::sendFinishCPUWar(int cpuwarlevel,bool isWin) {
    char str[300] = {0};
    if (isWin) {
        sprintf(str, "{\"cmd\":\"cpuwar.finishCPUWar\",\"userId\":\"%d\",\"level\":\"%d\",\"won\":\"%s\"}\r\n",PulsarNative::userId,cpuwarlevel,"true");
    } else {
        sprintf(str, "{\"cmd\":\"cpuwar.finishCPUWar\",\"userId\":\"%d\",\"level\":\"%d\",\"won\":\"%s\"}\r\n",PulsarNative::userId,cpuwarlevel,"false");
    }
    sendCmd(CCString::create(str));
}

void MyHttpConnection::sendOpenBox(int prizeBoxId,float interceptRate) {
    char str[300] = {0};
    
    sprintf(str, "{\"cmd\":\"cpuwar.openBox\",\"prizeBoxId\":\"%d\",\"interceptRate\":\"%f\"}\r\n",prizeBoxId,interceptRate);
    sendCmd(CCString::create(str));
}

void MyHttpConnection::sendUpdateDefendGameData(CCString* buildStyleJson) {
    char str[20000] = {0};
    sprintf(str,"{\"cmd\":\"building.refreshBuildings\", \"buildingStyle\":\"%s\"}\r\n",buildStyleJson->getCString());
    sendCmd(CCString::create(str));
}

void MyHttpConnection::sendMovingBuilding(int buildingId,const CCPoint& target) {
    char str[300] = {0};
    sprintf(str, "{\"cmd\":\"building.move\",\"id\":\"%d\",\"x\":\"%f\",\"y\":\"%f\",\"orderId\":\"%d\"}\r\n",buildingId,target.x,target.y,maxOrderId);
    ResendOrder* cmd = ResendOrder::create(str,maxOrderId);
    maxOrderId++;
    gameDataListArray->addObject(cmd);
    sendCmd(cmd);
}

void MyHttpConnection::sendCollectResource(int buildingId) {
    char str[300] = {0};
    sprintf(str,"{\"cmd\":\"building.resourceCollect\", \"id\":\"%d\",\"orderId\":\"%d\"}\r\n",buildingId,maxOrderId);
    ResendOrder* cmd = ResendOrder::create(str,maxOrderId);
    maxOrderId++;
    gameDataListArray->addObject(cmd);
    sendCmd(cmd);
}

void MyHttpConnection::sendConstructBuilding(int buildingId,int buildingTag,float x,float y) {
    char str[300] = {0};
    sprintf(str,"{\"cmd\":\"building.create\", \"id\":\"%d\", \"tag\":\"%d\", \"x\":\"%f\",\"y\":\"%f\",\"orderId\":\"%d\"}\r\n",buildingId,buildingTag,x,y,maxOrderId);
    ResendOrder* cmd = ResendOrder::create(str,maxOrderId);
    maxOrderId++;
    gameDataListArray->addObject(cmd);
    sendCmd(cmd);
}

void MyHttpConnection::sendChangeStateById(int buildingId,int sid) {
    char str[300] = {0};
    sprintf(str,"{\"cmd\":\"building.changeState\", \"id\":\"%d\",\"sid\":\"%d\",\"orderId\":\"%d\"}\r\n",buildingId,sid,maxOrderId);
    ResendOrder* cmd = ResendOrder::create(str,maxOrderId);
    maxOrderId++;
    gameDataListArray->addObject(cmd);
    sendCmd(cmd);
}

void MyHttpConnection::sendUpdateBuildingById(int buildingId) {
    char str[300] = {0};
    sprintf(str,"{\"cmd\":\"building.update\", \"id\":\"%d\",\"orderId\":\"%d\"}\r\n",buildingId,maxOrderId);
    ResendOrder* cmd = ResendOrder::create(str,maxOrderId);
    maxOrderId++;
    gameDataListArray->addObject(cmd);
    sendCmd(cmd);
}

void MyHttpConnection::sendRemoveBuildingById(int buildingId) {
    char str[200] = {0};
    sprintf(str, "{\"cmd\":\"building.remove\",\"id\":\"%d\",\"orderId\":\"%d\"}\r\n",buildingId,maxOrderId);
    ResendOrder* cmd = ResendOrder::create(str,maxOrderId);
    maxOrderId++;
    gameDataListArray->addObject(cmd);
    sendCmd(cmd);
}

void MyHttpConnection::sendRepiarBuildingById(int buildingId) {
    char str[200] = {0};
    sprintf(str, "{\"cmd\":\"building.repair\",\"id\":\"%d\",\"orderId\":\"%d\"}\r\n",buildingId,maxOrderId);
    ResendOrder* cmd = ResendOrder::create(str,maxOrderId);
    maxOrderId++;
    gameDataListArray->addObject(cmd);
    sendCmd(cmd);
}

void MyHttpConnection::sendContinueBuildingById(int buildingId,int dir,int combineId) {
    char str[200] = {0};
    sprintf(str, "{\"cmd\":\"building.wallCombine\", \"id\":\"%d\", \"direction\":\"%d\" ,\"combineId\":\"%d\",\"orderId\":\"%d\"}\r\n",buildingId,dir,combineId,maxOrderId);
    ResendOrder* cmd = ResendOrder::create(str,maxOrderId);
    maxOrderId++;
    gameDataListArray->addObject(cmd);
    sendCmd(cmd);
}

void MyHttpConnection::sendSplitBuilding(int buildingId) {
    char str[200] = {0};
    sprintf(str, "{\"cmd\":\"building.wallSplit\", \"id\":\"%d\",\"orderId\":\"%d\"}\r\n",buildingId,maxOrderId);
    ResendOrder* cmd = ResendOrder::create(str,maxOrderId);
    maxOrderId++;
    gameDataListArray->addObject(cmd);
    sendCmd(cmd);
}

void MyHttpConnection::sendUpdateArmyId(int armyId) {
    char str[200] = {0};
    sprintf(str, "{\"cmd\":\"creator.update\",\"unitCardId\":\"%d\",\"orderId\":\"%d\"}\r\n",armyId,maxOrderId);
    ResendOrder* cmd = ResendOrder::create(str,maxOrderId);
    maxOrderId++;
    gameDataListArray->addObject(cmd);
    sendCmd(cmd);
}

void MyHttpConnection::sendGetRobInfo() {
    char str[200] = {0};
    sprintf(str, "{\"cmd\":\"gameData.getRobInfo\"}\r\n");
    sendCmd(CCString::create(str));
}

void MyHttpConnection::sendCollectMubeiById(int mubeiId) {
    char str[200] = {0};
    sprintf(str,"{\"cmd\":\"building.tombCollect\",\"action\":\"single\",\"id\":\"%d\",\"orderId\":\"%d\"}\r\n",mubeiId,maxOrderId);
    ResendOrder* cmd = ResendOrder::create(str,maxOrderId);
    maxOrderId++;
    gameDataListArray->addObject(cmd);
    sendCmd(cmd);
}

void MyHttpConnection::sendCollectAllMubei() {
    char str[200] = {0};
    sprintf(str,"{\"cmd\":\"building.tombCollect\",\"action\":\"all\",\"id\":\"1\",\"orderId\":\"%d\"}\r\n", maxOrderId);
    ResendOrder* cmd = ResendOrder::create(str,maxOrderId);
    maxOrderId++;
    gameDataListArray->addObject(cmd);
    sendCmd(cmd);
}

void MyHttpConnection::sendResendGameDataListArray(int orderId){
    CCObject* obj;
    int index=0;
    CCARRAY_FOREACH(gameDataListArray,obj) {
        ResendOrder* order = (ResendOrder*)obj;
        if (order->orderId < orderId) {
            index++;
        } else {
            sendCmd(order);
        }
    }
    if (index >= gameDataListArray->count()) {
        gameDataListArray->removeAllObjects();
    }
}

void MyHttpConnection::sendGetOrderId() {
    char str[200] = {0};
    sprintf(str,"{\"cmd\":\"building.getOrderId\"}\r\n");
    CCString* cmd = CCString::create(str);
    sendCmd(cmd);
}

void MyHttpConnection::sendOneKeyCollect() {
    char str[200] = {0};
    sprintf(str,"{\"cmd\":\"building.oneKeyCollect\",\"orderId\":\"%d\"}\r\n", maxOrderId);
    ResendOrder* cmd = ResendOrder::create(str,maxOrderId);
    maxOrderId++;
    gameDataListArray->addObject(cmd);
    sendCmd(cmd);
}

void MyHttpConnection::sendGetRecharge() {
    CCString* cmd = CCString::create("{\"cmd\":\"store.hasRecharge\"}\r\n");
    sendCmd(cmd);
}

void MyHttpConnection::sendOneKeyUpdate(int buildingTag,int level) {
    char str[200] = {0};
    sprintf(str,"{\"cmd\":\"building.oneKeyUpdate\",\"tag\":\"%d\",\"level\":\"%d\",\"orderId\":\"%d\"}\r\n", buildingTag,level,maxOrderId);
    ResendOrder* cmd = ResendOrder::create(str,maxOrderId);
    maxOrderId++;
    gameDataListArray->addObject(cmd);
    sendCmd(cmd);
}

void MyHttpConnection::sendCreateSort(int id[]) {
    char str[200] = {0};
    sprintf(str,"{\"cmd\":\"creator.updateSort\",\"creatorSort\":\"%d,%d,%d,%d,%d\"}\r\n", id[4],id[3],id[2],id[1],id[0]);
    CCString* cmd = CCString::create(str);
    sendCmd(cmd);
}

void MyHttpConnection::sendGetIsFreeBoost() {
    char str[200] = {0};
    sprintf(str,"{\"cmd\":\"gameData.isBoost\"}\r\n");
    CCString* cmd = CCString::create(str);
    sendCmd(cmd);
}

void MyHttpConnection::sendSureBoost() {
    char str[200] = {0};
    sprintf(str,"{\"cmd\":\"gameData.boostProduce\",\"orderId\":\"%d\"}\r\n",maxOrderId);
    ResendOrder* cmd = ResendOrder::create(str,maxOrderId);
    maxOrderId++;
    gameDataListArray->addObject(cmd);
    sendCmd(cmd);
}

void MyHttpConnection::sendConversionResource(int resourceTag,float rate,bool isUseDiamond) {
    char str[200] = {0};
    if (isUseDiamond) {
        sprintf(str,"{\"cmd\":\"gameData.conversionResource\",\"resourceTag\":\"%d\",\"changeRate\":\"%f\",\"isUseDiamond\":\"true\",\"orderId\":\"%d\"}\r\n",resourceTag,rate,maxOrderId);
    } else {
        sprintf(str,"{\"cmd\":\"gameData.conversionResource\",\"resourceTag\":\"%d\",\"changeRate\":\"%f\",\"isUseDiamond\":\"false\",\"orderId\":\"%d\"}\r\n",resourceTag,rate,maxOrderId);
    }
    ResendOrder* cmd = ResendOrder::create(str,maxOrderId);
    maxOrderId++;
    gameDataListArray->addObject(cmd);
    sendCmd(cmd);
}

void MyHttpConnection::sendSearchEnemyByNickname(CCString* nickname) {
    char str[200] = {0};
    sprintf(str,"{\"cmd\":\"gameData.searchByNickname\",\"like\":\"%s\"}\r\n",nickname->getCString());
    CCString* cmd = CCString::create(str);
    sendCmd(cmd);
}

void MyHttpConnection::commonThirdRegisterOrLogin(int userId,bool isReconn) {
//    char str[200] = {0};
//    sprintf(str,"{\"cmd\":\"user.commonThirdRegisterOrLogin\",\"thirdId\":\"%d%d\",\"deviceId\":\"%s\"}\r\n",userId,serverId,PulsarNative::getDeviceId());
//    CCString* cmd = CCString::create(str);
//    sendCmd(cmd);
    
    char str[400] = {0};
    if (isReconn) {
        sprintf(str,"{\"cmd\":\"user.commonThirdRegisterOrLogin\", \"thirdId\":\"%d\", \"pwd\":\"*xkkkIIkksafasdfjk((LLLLIIIIjjjsadf+_oo15\",\"deviceId\":\"%s\",\"ititaChannel\":\"%s\",\"version\":\"0\",\"isReconnect\":\"true\"}\r\n",userId,PulsarNative::getDeviceId(),PulsarNative::getItitaChannel());
    } else {
        sprintf(str,"{\"cmd\":\"user.commonThirdRegisterOrLogin\", \"thirdId\":\"%d\", \"pwd\":\"*xkkkIIkksafasdfjk((LLLLIIIIjjjsadf+_oo15\",\"deviceId\":\"%s\",\"ititaChannel\":\"%s\",\"version\":\"0\"}\r\n",userId,PulsarNative::getDeviceId(),PulsarNative::getItitaChannel());
    }
    sendCmd(CCString::create(str));
}

void MyHttpConnection::sendCmd(CCString* str) {
    pthread_mutex_lock(&MyHttpConnection::sendMutex);
    if (isConn) {
        //连接了在加，免得会加入很多不必要的因素
        sendArray->addObject(str);
        if (sendFlag == waitSendTag) {
            sendFlag = readySendTag;
        }
    }
    
    pthread_mutex_unlock(&MyHttpConnection::sendMutex);
}



//void MyHttpConnection::clearConnectInfoManual() {
//    acceptFlag = false;
//    BIO_free(bio);
//}


//ScanSchedule* ScanSchedule::create() {
//    ScanSchedule* ptr = new ScanSchedule();
//    ptr->autorelease();
//    return ptr;
//}

void MyHttpConnection::scan() {
    if (MyHttpConnection::sendFlag == readySendTag) {
        pthread_mutex_lock(&MyHttpConnection::sendMutex);
        MyHttpConnection::sendFlag = startSendThreadTag;
        pthread_mutex_unlock(&MyHttpConnection::sendMutex);
        pthread_t send_id;
        pthread_create(&send_id, NULL, MyHttpConnection::toSendbyPipline, NULL);
        pthread_detach(send_id);
    }
}

void MyHttpConnection::sendHeartbeat() {
    if (MyHttpConnection::sendFlag != closeSendTag) {
         MyHttpConnection::getInstance()->sendCmd(CCString::create("1\r\n"));
    }
   
}

CCScheduler* MyHttpConnection::getScheduler()
{
    return m_pScheduler;
}

void MyHttpConnection::setScheduler(CCScheduler* scheduler)
{
    if( scheduler != m_pScheduler ) {
        //        this->unscheduleAllSelectors();
        CC_SAFE_RETAIN(scheduler);
        CC_SAFE_RELEASE(m_pScheduler);
        m_pScheduler = scheduler;
    }
}
