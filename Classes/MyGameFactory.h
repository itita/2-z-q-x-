//
//  MyGameFactory.h
//  ww2
//
//  Created by DingYu Fu on 12-9-15.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#ifndef ww2_MyGameFactory_h
#define ww2_MyGameFactory_h


//#define bubingBaseHealth 20
//#define bubingBaseCost 20
//#define bubingBaseSpeed 1
//#define bubingBaseDamage 8
//#define bubingBaseRange 4
//#define bubingUpdateDamageRate 1
//#define bubingUpdateSpeedRate 0.2
//#define bubingUpdateCostRate 1.5
//#define bubingUpdateHealthRate 0
//
//#define tankBaseHealth 50
//#define tankBaseCost 70
//#define tankBaseSpeed 2
//#define tankBaseDamage 10
//#define tankBaseRange 5
//#define tankUpdateHealthRate 2.5
//#define tankUpdateDamageRate 1
//#define tankUpdateCostRate 2
//#define tankUpdateSpeedRate 0

#include "MyBuilding.h"
#include "MyBattleBuilding.h"
#include "MyBuildingCard.h"
#include "MyJsonUtil.h"
#include "MyState.h"
#include "cocos2d.h"
#include "MyUnitCard.h"
#include "MyBaseMessage.h"

using namespace cocos2d;


class staticInit {
    
public:
    static staticInit* create();
    
};

class MyGameFactory {
    
public:
    static CCDictionary* creatorMap;
    static staticInit* init;
//    static MyBuilding* createBingYing(CCObject* target,int level);
//    static MyBattleBuilding* createBattleBingYing(CCObject* target,int level);
//    static MyBuilding* createWall(CCObject* target,int level);
//    static MyBattleBuilding* createBattleWall(CCObject* target,int level);
//    static MyBuilding* createYouTian(CCObject* target,int level);
//    static MyBattleBuilding* createCreateInBattle(int tag,CCObject* target,int level);
    
//    static MyBuilding* createDestoryBuilding(int tag,CCObject* target,int level);
//    static MyBattleBuilding* createBattleDestory(int tag,CCObject* target,int level);
    
//    static MyBattleBuilding* createBattleDiaoBao(CCObject* target,int level);
//    static MyBuilding* createDefenderInCreate(int tag,CCObject* target,int level);
//    static MyBattleBuilding* createBattleDaPao(CCObject* target,int level);
//    static MyBuilding* createKuangchang(CCObject* target,int level);
//    static MyBuilding* createZhihuisuo(CCObject* target,int level);
//    static MyBuilding* createLianluozhongxin(CCObject* target,int level);

//    static MyBuilding* createzhihuisuo(CCObject* target);
//    static MyBuilding* createBattleZhihuisuo(CCObject* target);
//    static MyBuilding* createOrnaments(int tag,CCObject* target);
//    static MyBattleBuilding* createBattleOrnaments(int tag,CCObject* target);
    
//    static MyBuilding* createCombineWall(int tag,CCObject* target,int level);
//    static MyBattleBuilding* createBattleCombineWall(int tag,CCObject* target,int level);
    
    
//    static MyBuilding* createByTag(int tag,CCObject* target,int level);
//    static MyBuilding* createBattleByTag(int tag,CCObject* target);
    static MyBuilding* createBuildingByBean(BuildingBean* bean,CCObject* target);
    static MyBattleBuilding* createBattleBuildingByBean(BuildingBean* bean,CCObject* target, bool isDisplaySummary = true);
    static MyBuilding* createReadyToBuildByTag(int tag,CCObject* target);
//    static MyBuildingCard* createCard(int tag,CCObject* target);
    static CCArray* createAllCard(CCObject* target,int filter = 0);
    static void addState(MyBuilding* building,int stateTag,CCObject* target);
    static GXCreator* createCreatorbyJsonScriptFile(const std::string& relativePath,int classTag);
//    static void setStateUpdateInfo(MyState* state, CCLayer* updateLayer);
//    static void setLevel(int level ,int tag,GXFSM* fsm);
    
//    static CCLayer* getUnitCardDescriptTag(CreatorInfoBean* bean,bool isAll = true);
//    static CCLayer* getUpdateBar(float per1,float per2,const char* upName);
    static MyBaseMessage* getMessageByCommander(char* cmd);
//    static CCLayer* getUnitClassDescript(UnitCreator* bean);
    static CCLayer* getBuildingClassDescript(BuildingCreator* bean);
    static CCNode* getShopResourceIcon(int resourceIcon,int level);
    static CCSprite* getBuildingSpriteByTag(int tag);
    static CCLabelTTF* getBuildingNameByTag(int tag, int size);
    
private:
    
    
};


#endif
