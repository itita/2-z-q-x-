//
//  DefendScene.h
//  ww4
//
//  Created by xiao tang on 13-6-10.
//
//

#ifndef __ww4__DefendScene__
#define __ww4__DefendScene__

#include "MyBattleMap.h"
#include "BattleScene.h"
#include "MyAtlasNumber.h"
#include "GXUtil.h"

//#define beforeFightTag 0
//#define fightingTag 1
//#define afterFightTag 2

#define surrenderTag 11
#define nextTag 12
#define surrenderDialogTag 13
#define bingzhongmenuTag 33

//#define bubingCreatorTag 101
//#define tankCreatorTag 102



class DefendScene : public BattleScene{
    
public:
    DefendScene():
    deployTime(0),
    attackerDirection(attackLD),
    completeRate(0),
    cpuWarLevel(0),
    baseLoc(30)
    {
        attackerCreatorInfoBeanList = CCArray::create();
        attackerCreatorInfoBeanList->retain();
        attackerCountList = CCArray::create();
        attackerCountList->retain();
        attackerTimeList = CCArray::create();
        attackerTimeList->retain();
        
//        prizeBox1TagList = CCArray::create();
//        prizeBox1TagList->retain();
//        prizeBox2TagList = CCArray::create();
//        prizeBox2TagList->retain();
//        prizeBox3TagList = CCArray::create();
//        prizeBox3TagList->retain();
//        
//        prizeBox1CountList = CCArray::create();
//        prizeBox1CountList->retain();
//        prizeBox2CountList = CCArray::create();
//        prizeBox2CountList->retain();
//        prizeBox3CountList = CCArray::create();
//        prizeBox3CountList->retain();
        
        for (int i=0; i<3; i++) {
            prizeBoxTagList[i] = CCArray::create();
            prizeBoxTagList[i]->retain();
            prizeBoxCountList[i] = CCArray::create();
            prizeBoxCountList[i]->retain();
        }
        
        for (int i=0; i<10; i++) {
            attackDeployCountList[i] = 0;
            attackerSummaryList[i] =0;
        }
        
        for (int i=0; i<3; i++) {
            prizeBoxIds[i] = 0;
        }
    };
    
    ~DefendScene() {
        releaseResource();
        CC_SAFE_RELEASE_NULL(battleMap);
        CC_SAFE_RELEASE_NULL(attackerCreatorInfoBeanList);
        CC_SAFE_RELEASE_NULL(attackerCountList);
        CC_SAFE_RELEASE_NULL(attackerTimeList);
        
//        CC_SAFE_RELEASE_NULL(prizeBox1TagList);
//        CC_SAFE_RELEASE_NULL(prizeBox2TagList);
//        CC_SAFE_RELEASE_NULL(prizeBox3TagList);
//        
//        CC_SAFE_RELEASE_NULL(prizeBox1CountList);
//        CC_SAFE_RELEASE_NULL(prizeBox2CountList);
//        CC_SAFE_RELEASE_NULL(prizeBox3CountList);
        for (int i=0; i<3; i++) {
            CC_SAFE_RELEASE_NULL(prizeBoxTagList[i]);
            CC_SAFE_RELEASE_NULL(prizeBoxCountList[i]);
        }
        //    CocosDenshion::SimpleAudioEngine::sharedEngine()->unloadEffect("sfx_deploySoldier.m4a");
        //    CocosDenshion::SimpleAudioEngine::sharedEngine()->unloadEffect("sfx_deployTank.m4a");
        //    CocosDenshion::SimpleAudioEngine::sharedEngine()->unloadEffect("sfx_diaobao1f.wav");
        //    CocosDenshion::SimpleAudioEngine::sharedEngine()->unloadEffect("sfx_paoji.m4a");
        CCLog("Defender released!");
    }
    
    virtual bool init();
    virtual bool init(CCArray* buildings);
    virtual void initUI(CCString* attackerAvatar);
    virtual void callback1(CCObject* pSender);
    static  DefendScene* create(CCArray* buildings,CCString* attackerAvatar);
    static  DefendScene* create();
    
    virtual void toVictory();
    virtual void toFight();
//    virtual void retain();
    virtual void toSurrender();
    virtual void doPause();
    virtual void doResume();
    virtual void loadResource();
    virtual void releaseResource();
    
    CCArray* attackerCreatorInfoBeanList;
    CCArray* attackerCountList;
    CCArray* attackerTimeList;
    
    CCArray* prizeBoxTagList[3];
    CCArray* prizeBoxCountList[3];

    int prizeBoxIds[3];
    
    int attackerSummaryList[10];
    int attackerDirection;
    int getFighting() {
        return isFighting;
    }
    void addAttackerCreateInfoBean(CreatorInfoBean* _bean) {
        attackerCreatorInfoBeanList->addObject(_bean);
        char str[30] = {0};
        char str1[30] = {0};
        sprintf(str, "%s.plist",_bean->creator->getSpriteFileName());
        sprintf(str1, "%s.pvr.ccz",_bean->creator->getSpriteFileName());
        GXUtil::loadResourceUtilSucc(str,str1);
        GarbageResourceCollection::getInstance()->addGarbage(str,CCString::create(str1));
    }
   
    
    MyBattleMap* battleMap;
    float completeRate;
    int cpuWarLevel;
    
protected:
    
//    int isFighting;
    bool isVictory;
    //    virtual void initSound();
    //    virtual void toReturnHomeWait();
    //    virtual void toContinueWarWait();
    virtual void toBuildSceneWait(CCMenuItem* item);
    virtual void toBuildScene();
    virtual void surrender();
    virtual void cancelSurrender();
    virtual CCLayer* getVictoryUI(bool isVictory);
    virtual void addDefendInfo(bool victory);
    virtual int getBaseLoc();
    
//    CreatorInfoBean attackerCreatorInfoBeanList[];
//    CC_SYNTHESIZE_RETAIN(CCString*,attackerAvatar,AttackerAvatar);
private:
//    int lastTime;
//    CCLabelAtlas* lastTimeLabel;
    int attackDeployCountList[10];
    void startAttack();
    void deployUnit();
    long deployTime;
    void getBoxPrize(CCMenuItem* item);
    void openBox(CCMenuItemSprite* box);
    void checkVictory();
    int baseLoc;
};

#endif /* defined(__ww4__DefendScene__) */
