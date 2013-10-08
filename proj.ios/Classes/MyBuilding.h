//
//  MyBuiding.h
//  ww2
//
//  Created by DingYu Fu on 12-9-1.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#ifndef ww2_MyBuiding_h
#define ww2_MyBuiding_h
#include "MyTiledMenuItem.h"
#include "GXFSMstate.h"
#include "GXFSMclass.h"
#include "AliveInterface.h"
#include "IbeAttack.h"
#include "GXCreator.h"
#include "GXAntiCrack.h"

//不冲突状态，可以作为约定在各个模式中切换
//#define BeAttackStateTag 17
//#define WorkStateTag 17
//#define DefendStateTag 17
//#define battleNormalStateTag 17
//
//#define RuinsStateTag 21
//
//#define toRuinsTransition 22
//#define UnfinishedStateTag 15
//#define BuildTransition 16
//
//#define CancelTransition 18
//#define DestroyStateTag 19
//#define CollectTransition 20
//#define InfoTransition 21
//#define UpdateTransition 22
//#define ConscriptionTransition 23
//#define RepairTransition 24

#define  updateSummaryRate 2

//#include "MyState.h"
typedef void (*SEL_SetLevel)(int,GXFSM*);
typedef void (*SEL_SetUpdateInfo)(GXFSMstate*,cocos2d::CCLayer*);

class MyBuilding : public MyTiledMenuItem{
    
public:
    GXFSM* fsm;
    MyBuilding():
    doStateInterval(-1),
    fsm(NULL),
    setLevel_selector(NULL),
    setUpdateInfo_selector(NULL),
    resourceTag(0),
    y(0),
    road(NULL){
        level = GXintValue::create(1);
        level->retain();
        maxLevel = GXintValue::create(1);
        maxLevel->retain();
        summaryCount = GXintValue::create(0);
        summaryCount->retain();
        buildingName = CCString::create("");
        buildingName->retain();
    }
    static MyBuilding* create(int tag,const CCSize& _contentSizebyTiled,GXFSMstate* state,int _maxLevel);
    
    //    static MyBuilding* create(int tag,const CCSize& _contentSizebyTiled,GXFSMstate *state,int level,CCMenuItem* item, ...);
    
    virtual ~MyBuilding();
    virtual void doCurrentState();
//    virtual void release();
//    virtual void retain();
    //    virtual void showAllTransition();
    virtual void dismissAllTransition();
    virtual void showCurrentTransition();
    virtual void addState(GXFSMstate* state);
    virtual void changeState(int inputId);
    virtual void changeStateById(int id);
    //    virtual void dispose();
    //    virtual bool isAlive();
    //    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    //    virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
    
    virtual void runTouchAction();
    virtual void displaySummary();
    virtual bool dismissSummary();
    virtual void updateLevel(CCMenuItem* item);
    virtual void updateCallBack(CCMenuItem* pSender);
    virtual float updateBuilding();
    virtual void sellCallBack(CCNode* pSender);
    virtual void setLevel(int level);
    virtual void setSummaryCount(int count);
    virtual int getSummaryCount();
    virtual void setPositionByTiled(const CCPoint& pos);
    
    
    
    //这个属性可以交给状态~哎 也不好~毕竟最后什么模式都会显示
    CCSize costRange;
    virtual int getLevel();
    virtual void setMaxLevel(int _maxLevel);
    virtual int getMaxLevel();
    int resourceTag;
    void setRoad(CCSprite* _road);
    CCSprite* getRoad() {
        return road;
    }
    
    void setBuildingName(CCString* _buildingName,float _y) {
        CC_SAFE_RELEASE_NULL(buildingName);
        buildingName = _buildingName;
        buildingName->retain();
        y = _y;
    }
    
    const char* getBuildingName() {
        return buildingName->getCString();
    }
    
    void setDoStateInterval(float _doStateInterval);
    
    float doStateInterval;
    float y;
    SEL_SetLevel setLevel_selector;
    SEL_SetUpdateInfo setUpdateInfo_selector;
    float getUpdateSummary(float base,int level);
private:
    static MyBuilding* create();
    GXintValue* maxLevel;
    GXintValue* level;
    GXintValue* summaryCount;
    CCSprite* road;
    CCString* buildingName;
    
};

class BuildingCreator : public GXCreator {
    
public:
    
    BuildingCreator():
    spriteFileName(NULL),
    buildingName(NULL),
    cardId(-1),
    rarity(0){
        descInfos = CCArray::create();
        descInfos->retain();
    }
    
    int cardId;
    int rarity;
    CCArray* descInfos;
    
    ~BuildingCreator() {
        CC_SAFE_RELEASE_NULL(spriteFileName);
        CC_SAFE_RELEASE_NULL(buildingName);
        CC_SAFE_RELEASE_NULL(buildingName);
    }
    
    static  BuildingCreator* create();
    virtual CCObject* creatObj();
    virtual void doFill(CCObject* entity);
    
    const char* getSpriteFileName() {
        return spriteFileName->getCString();
    }
    
    const char* getBuildingName() {
        return buildingName->getCString();
    }
    
    void setSpriteFileName(CCString* _spriteFileName) {
        CC_SAFE_RELEASE_NULL(spriteFileName);
        spriteFileName = _spriteFileName;
        CC_SAFE_RETAIN(spriteFileName);
    }
    
    void setBuildingName(CCString* _buildingName) {
        CC_SAFE_RELEASE_NULL(buildingName);
        buildingName = _buildingName;
        CC_SAFE_RETAIN(buildingName);
    }
    
private:
    CCString* spriteFileName;
    CCString* buildingName;
    
};

class DescInfo : public CCObject {
    
public:
    
    static DescInfo* create();
    
    std::string icon;
    std::string label;

};

#endif
