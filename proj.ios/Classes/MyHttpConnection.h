//
//  MyHttpConnection.h
//  ww2
//
//  Created by DingYu Fu on 12-9-16.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#ifndef ww2_MyHttpConnection_h
#define ww2_MyHttpConnection_h
//#include "curl/curl.h"
#include "cocos2d.h"
#include <string>
//#include <openssl/bio.h>
//#include <netdb.h>
#include "MyBaseMessage.h"

using namespace cocos2d;

#define getUserDataUrl "http://106.187.52.13:8080/WWKENNEDY/servlet/getuser"
#define loadStartSceneUrl "http://106.187.52.13:8080/WWKENNEDY/servlet/getgamedata"
#define updateStartSceneUrl "http://106.187.52.13:8080/WWKENNEDY/servlet/updategamedata"
#define UpdateOthersGameData "http://106.187.52.13:8080/WWKENNEDY/servlet/updateothersgamedata"
#define getOtherDataUrl "http://106.187.52.13:8080/WWKENNEDY/servlet/getothersgamedata"
#define addMatchUrl "http://106.187.52.13:8080/WWKENNEDY/servlet/addmatches"
#define getAllMatchesUrl "http://106.187.52.13:8080/WWKENNEDY/servlet/getallmatches"
#define getWhoAttackMeUrl "http://106.187.52.13:8080/WWKENNEDY/servlet/getwhoattackedme"
#define getTopRankUrl "http://106.187.52.13:8080/WWKENNEDY/servlet/getpowerrank"
#define getAttackListUrl "http://106.187.52.13:8080/WWKENNEDY/servlet/getgamedatalist"
#define getConscribeListUrl "http://106.187.52.13:8080/WWKENNEDY/servlet/Conscribe"
#define getRobDeltaTimeUrl "http://106.187.52.13:8080/WWKENNEDY/servlet/getrobdeltatime"
#define updateResourceByRobUrl "http://106.187.52.13:8080/WWKENNEDY/servlet/updateresourcebyrob"

//#define sslSocketUrl "192.168.1.222:8000"
//开发服务起
//#define sslSocketUrl "106.186.23.68:8000"

//电信服务器
//#define sslSocketUrl "218.245.3.236:8000"

//#define sslSocketUrl "106.187.52.13:8000"

//#define getUserDataUrl "http://192.168.1.222:8080/WWKENNEDY/servlet/getuser"
//#define loadStartSceneUrl "http://192.168.1.222:8080/WWKENNEDY/servlet/getgamedata"
//#define updateStartSceneUrl "http://192.168.1.222:8080/WWKENNEDY/servlet/updategamedata"
//#define UpdateOthersGameData "http://192.168.1.222:8080/WWKENNEDY/servlet/updateothersgamedata"
//#define getOtherDataUrl "http://192.168.1.222:8080/WWKENNEDY/servlet/getothersgamedata"
//#define addMatchUrl "http://192.168.1.222:8080/WWKENNEDY/servlet/addmatches"
//#define getAllMatchesUrl "http://192.168.1.222:8080/WWKENNEDY/servlet/getallmatches"
//#define getWhoAttackMeUrl "http://192.168.1.222:8080/WWKENNEDY/servlet/getwhoattackedme"
//#define getTopRankUrl "http://192.168.1.222:8080/WWKENNEDY/servlet/getpowerrank"
//#define getAttackListUrl "http://192.168.1.222:8080/WWKENNEDY/servlet/getgamedatalist"
//#define getConscribeListUrl "http://192.168.1.222:8080/WWKENNEDY/servlet/Conscribe"
//#define getConscribeListUrl "http://192.168.1.222:8080/WWKENNEDY/servlet/Conscribe"
//#define getRobDeltaTimeUrl "http://192.168.1.222:8080/WWKENNEDY/servlet/getrobdeltatime"
//#define updateResourceByRobUrl "http://192.168.1.222:8080/WWKENNEDY/servlet/updateresourcebyrob"



class MyHttpConnection : public CCObject {
    
    
public:
//    BIO* bio;
    int socketHandle;
    std::vector<char> recvBuffer;
    static std::vector<char> sendBuffer;
    static CCArray* sendArray;
    static int sendFlag;
    MyHttpConnection():
//    bio(NULL),
    cecheCmd(NULL),
    cacheHostUrl(NULL),
    gameDataListArray(NULL),
    maxOrderId(0),
    socketHandle(-1){
        gameDataListArray = CCArray::create();
        gameDataListArray->retain();
    }
    static MyHttpConnection* getInstance();
    static void release();
//    virtual bool post(CCString* var,CCString* url);
//    virtual bool postByClient(CCString* var,CCString* url);
//    virtual CCString* get(CCString* url);
//    std::string temp;
    
//    virtual CCString* getStartSceneData();
//    virtual CCString* getStartSceneData(bool isCreatorStyle);
//    bool updateStartSceneData(CCString* updateJson);
//    void updateStartSceneDataAsynchronous(CCString* updateJson,CCObject* pTarget, SEL_CallFuncND pSelector);
//    virtual CCString* getOtherData();
//    virtual bool addMatch(bool isWin,float robberOil,float robberIron,CCString* unitJson,CCString* note);
//    virtual bool createAccount(CCString* updateJson);
//    virtual CCString* getMyMatches();
//    virtual CCString* getNoReadedMatches();
//    virtual CCString* getWhoAttackMeMatches();
//    virtual CCString* getOtherData(CCString* ititaId);
//    virtual bool updateResource(CCString* ititaId,bool isUpdateTime);
//    virtual bool updateBattleOtherData(CCString* updateJson);
//    CCString* getUserData();
//    virtual CCString* getTopRank(int pageNo);
//    CCString* getAttackList();
//    CCString* getConscrbeList();
//    CCString* getRobDeltaTime();
//    virtual bool updateResourceByRob();
    
    void sendCreateUnionCmd(CCString* unionName, CCString* unionDes,CCString* emblemName);
    void readUnionByItitiaId();
//    bool initSSL(const char* sslSocketUrl,int serverId);
    bool initSocket(const char* socketUrl,int serverId);
    void sendNotice(CCString* notice);
    void sendJoinUnion(int unionId);
    void sendKickUnion(CCString* ititaId);
    void sendReplyApplicant(CCDictionary* varMap);
    void sendDissolveUnion();
    void sendExitUnion();
    void sendDisconnect();
    void sendUnionChat(CCString* str);
    void sendWorldChat(CCString* str);
    void sendLogin(CCObject* userBean,bool isReconn);
    void sendGetGameData(bool isCreateor);
    void sendRegister(CCObject* userBean);
    void sendUpdateGameData();
//    void sendUpdateCreateStyle();
    void sendFastEnterGame(bool isReconn);
    void sendGetGameDataList();
    void sendGetOthers(int userId,bool isBySearch = false);
    void sendAddMatchInfo(bool isWin,float robberOil,float robberIron,CCString* unitJson,int attackType);
    void sendGetWhoAttackMeMatch(int type = -1);
    void sendGetNoReadedMatches();
    void sendUpdateBattleOtherData(CCString* updateJson,int robberOil,int robberIron);
    void sendUpdateResource(long deltaOil,long deltaIron,long deltaGlory);
    void sendGetTopRank(int pageNo);
    void sendGetBoughtList();
//    void sendBuyList(CCArray* list);
    void sendBuyResource(int tag);
//    void sendAckDiamond();
    void sendCompleteQuest(int questId);
//    void sendUpdatePower(float powerCount);
    void sendUpdateMissionProgress(char* str,int missionId);
    void sendGetDefend(int level);
    void sendGetCpuWar();
    void sendFinishCPUWar(int cpuwarlevel,bool isWin);
    void sendOpenBox(int prizeBoxId,float interceptRate);
    void sendUpdateDefendGameData(CCString* buildStyleJson);
    void sendMovingBuilding(int buildingId,const CCPoint& target);
    void sendCollectResource(int buildingId);
    void sendConstructBuilding(int buildingId,int buildingTag,float x,float y);
    void sendChangeStateById(int buildingId,int sid);
    void sendUpdateBuildingById(int buildingId);
    void sendRemoveBuildingById(int buildingId);
    void sendRepiarBuildingById(int buildingId);
    void sendContinueBuildingById(int buildingId,int dir,int combineId);
    void sendSplitBuilding(int buildingId);
    void sendUpdateArmyId(int armyId);
    void sendGetRobInfo();
    void sendCollectMubeiById(int mubeiId);
    void sendCollectAllMubei();
    void sendResendGameDataListArray(int ordId);
    void sendGetOrderId();
    void sendOneKeyCollect();
    void sendAddMatchNote(CCString* note);
    void sendChangeNickName(const char* newname);
    void sendGetDefendList();
    void sendGetRecharge();
    void sendOneKeyUpdate(int buildingTag,int level);
    void sendCreateSort(int id[]);
    void sendGetIsFreeBoost();
    void sendSureBoost();
    void sendConversionResource(int resourceTag,float rate,bool isUseDiamond);
    void sendSearchEnemyByNickname(CCString* nickname);
    void commonThirdRegisterOrLogin(int userId,bool isReconnect);
    
    void getAllMemberByPage(int pageNo,int pageSize);
    void getAllUnionByPage(int pageNo, int pageSize);
    
    //并不断开~只是清楚数据，关闭线程
//    void clearConnectInfoManual();
    static void sendbyPipline();
    static void* toSendbyPipline(void *arg);
    static bool isConn;
    static bool isSendMsg;
    void sendCecheCmd();

//    virtual void onHttpRequestCompleted(cocos2d::CCNode *sender, void *data);
    CC_SYNTHESIZE_RETAIN(CCString*,cecheCmd,CecheCmd);
    static pthread_mutex_t sendMutex;
    CC_SYNTHESIZE_RETAIN(CCString*,cacheHostUrl,CacheHostUrl);
    
    void clearGameDataListArray() {
        gameDataListArray->removeAllObjects();
        maxOrderId = 0;
    }
    
private:
    static MyHttpConnection* create();
    static void* acceptResponse(void *arg);
//    CURL *curl;
//    virtual bool sslWrite(char* str);
//    virtual char* sslRead();
    bool socketWrite(char* str);
    char* socketRead();
    inline char* getDisconnectCmd();
//    virtual bool sslSocketConnect(const char* sslSocketUrl);
    bool socketConnect(const char* sslSocketUrl, unsigned short port);
    void sendCmd(CCString* str);
    CC_PROPERTY(CCScheduler*, m_pScheduler, Scheduler);
    void scan();
    void sendHeartbeat();
    
    CCArray* gameDataListArray;
    int maxOrderId;
    
};

//size_t write_data(char *ptr, size_t size, size_t nmemb, std::string *writerData);
//
//int debug_callback (CURL * url, curl_infotype type, char * chr, size_t t, void * ptr);

//class ScanSchedule : public CCNode{
//    
//public:
//    ~ScanSchedule() {
////        CCLog("ScanSchedule released");
//    }
//    static ScanSchedule* create();
//    void scan();
//    void sendHeartbeat();
//};

#endif
