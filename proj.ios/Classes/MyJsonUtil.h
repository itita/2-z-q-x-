//
//  MyJsonUtil.h
//  ww2
//
//  Created by DingYu Fu on 12-9-16.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#ifndef ww2_MyJsonUtil_h
#define ww2_MyJsonUtil_h
#include "cocos2d.h"
#include "libjson.h"
#include "StartScene.h"
#include "BattleScene.h"
#include "DefendScene.h"
#include "GXCommander.h"
#include "GXMessage.h"
#include "GXArray.h"
#include "GXMsg.h"
#include "MyBaseQuest.h"
#include "AttackerInfoBean.h"
#include "GXChatHandler.h"
#include "GXMsg.h"

//#include "TestScene.h"
using namespace cocos2d;

class BuildingBean : public CCObject{
public:
    BuildingBean():
    pid(-1),
    tag(0),
    currentStateId(0),
    posX(0),
    posY(0),
    arg0(0),
    lifePercentage(100),
    level(1){}
    static BuildingBean* create();
    int pid;
    int tag;
    int currentStateId;
    int level;
    float posX;
    float posY;
    float arg0;
    float lifePercentage;
};

class topRankBean : public CCObject{
public:
    
    ~topRankBean() {
        CC_SAFE_RELEASE_NULL(emblem);
        CC_SAFE_RELEASE_NULL(unionName);
        CC_SAFE_RELEASE_NULL(ititaId);
        CC_SAFE_RELEASE_NULL(nickName);
    }
    
    topRankBean():
    rankNo(999),
    ititaId(NULL),
    nickName(NULL),
    power(10),
    emblem(NULL)
    {
        unionName = CCString::create("");
        unionName->retain();
    }
    static topRankBean* create();
    int rankNo;
    CC_SYNTHESIZE_RETAIN(CCString*,ititaId,ItitaId);
    CC_SYNTHESIZE_RETAIN(CCString*,nickName,Nickname);
    float power;
    
    void setEmblem(CCString* _emblem) {
        CC_SAFE_RELEASE_NULL(emblem);
        emblem = _emblem;
        emblem->retain();
    }
    CCString* getEmblem() {
        return emblem;
    }
    
    void setUnionName(CCString* _unionName) {
        CC_SAFE_RELEASE_NULL(unionName);
        unionName = _unionName;
        unionName->retain();
    }
    
    CCString* getUnionName() {
        return unionName;
    }
    
    
private:
    CCString* emblem;
    CCString* unionName;
};

class ConscribeInfoBean : public CCObject  {
    
public:
    ~ConscribeInfoBean() {
        CC_SAFE_RELEASE_NULL(jsonName);
//        CCLog("ConscribeInfoBean has been released");
    }
    
    ConscribeInfoBean():
    jsonName(NULL),
    level(1){
        for (int i =0; i<9; i++) {
            randomSeed[i] = 0;
        }
    }
    
    static ConscribeInfoBean* create();
    void setJsonName(CCString* jsonName);
    CCString* getJsonName() {
        return jsonName;
    }
    int level;
    int randomSeed[9];
private:
    CCString* jsonName;
    
};

class MyJsonUtil {
    
public:
    static CCString* packAllBuilding(CCArray* array);
    static CCString* packAllBattleBuilding(CCArray* array);
    static CCArray* parseBuildingFromJson(json_char* str);
    static CCArray* parseBuildingFromJson(CCString* str);
    static CCArray* parseBuildingFromJsonNoCompress(CCString* str);
    static void parseCreatorStyle(json_char* str);
    
    static StartScene* parseNativeInfo(CCString* str);
    static BattleScene* parseBattleNativeInfo(CCString* str);
    static DefendScene* parseDefendNativeInfo(CCString* str);
    
    static CCScene* parseReadyNativeInfo(CCString* str);
    static CCArray* parseBaseInfoBean(CCString* str);
//    static UnitCreator* parseUnitCreator(CCString* str);
    static BuildingCreator* parseBuildingCreator(CCString* str);
    static CCArray* parseMatches(CCString* str);
    static CCString* packBattleUnit(CCArray* creatorArray);
    static CCString* packAllCreator();
    static CCString* parseUserData(CCString* str);
    static CCArray* parseTopRank(CCString* str);
    static CCArray* parseConscribeList(CCString* str);
    static GXCommander* parseGXCommanderByString(char* str);
    static UnionBean* parseUserUnion(CCString* str);
    static CCArray* parseUnionList(CCString* str);
    static CCArray* parsePushUnionApplyJoin(CCString* str);
    static CCArray* parseUnionMember(CCString* str);
    static void parseBoughtInfo(CCString* str);
    static GXMsg* parseGXMsg(GXString* str);
    static void parseLoginInfo(CCString* str);
    static bool parseChargeInfo(CCString* str);
    static CCArray* parseServerInfo();
    static const char* parseGameInfo(const char* str);
    static CCArray* parseQuest(CCString* str);
    static AttackerInfoBean* parseAttackInfoBean(CCString* str);
    static CCArray* parsePushMatch(CCString* str);
    static CCScene* parseChiefSceneInfo(CCString* str);
    static void parseResourceChange(CCString* str);
    static CCArray* parseDefendList(CCString* str);
    static BuildingBean* parseBuildBean(CCString* str);
    static void parseChatInfoBean(GXChatInfoBean* bean);
    static GXMsg* parseChat(const char* str);
    
private:
    static BuildingBean* parseNode(JSONNODE* node);
};





#endif
