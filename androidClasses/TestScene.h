//
//  TestScene.h
//  ww4
//
//  Created by xiao tang on 13-1-22.
//
//

#ifndef __ww4__TestScene__
#define __ww4__TestScene__

#include <iostream>

#include "cocos2d.h"
#include "GXBaseScene.h"
#include "MyMenuItem.h"
#include "ReadyToBattleTrigger.h"
#include "MyMessageManage.h"

using namespace cocos2d;

#endif /* defined(__ww4__TestScene__) */

class BaseInfoBean : public CCObject {
    
public:
    ~BaseInfoBean() {
        CCLog("baseInfoBean has released");
        CC_SAFE_RELEASE_NULL(nickName);
        CC_SAFE_RELEASE_NULL(unionName);
        CC_SAFE_RELEASE_NULL(defenSuccRate);
    }
    BaseInfoBean():
    nickName(NULL),
    oil(0),
    iron(0),
    honor(0),
    time(0),
    nowTime(0),
    defenSuccRate(NULL),
    unionName(NULL),
    trophyRate(0.5),
    type(0),
    userId(-1){
        setUnionName(CCString::create(""));
    }
    
//    CC_SYNTHESIZE_RETAIN(CCString*,ititaId,ItitaId);
    CC_SYNTHESIZE_RETAIN(CCString*,nickName,Nickname);
    CC_SYNTHESIZE_RETAIN(CCString*,unionName,UnionName);
    CC_SYNTHESIZE_RETAIN(CCString*,defenSuccRate,DefenSuccRate);
    
    int userId;
    float oil;
    float iron;
    float honor;
    float trophyRate;
    int type;
    unsigned long long time;
    unsigned long long nowTime;
    unsigned long long experience;
    
    
    static BaseInfoBean* create();
    void toBattleScene(CCNode* pSender);
    
};

class TestScene : public GXBaseScene,public cocos2d::CCIMEDelegate,public cocos2d::CCTextFieldDelegate{
    
    
public:
    
    TestScene():
//    baseInfoBeanArray(NULL),
    myArmyList(NULL),
    isChangeArmy(false){
        trigger = ReadyToBattleTrigger::create(this);
        trigger->retain();
        MyMessageManage::getInstance()->registerTrigger(trigger);
    }
    
    ~TestScene() {
        releaseResource();
//        CC_SAFE_RELEASE(baseInfoBeanArray);
        CC_SAFE_RELEASE(myArmyList);
        if (trigger != NULL) {
            MyMessageManage::getInstance()->unRegisterTrigger(trigger);
            CC_SAFE_RELEASE(trigger);
        }
    }
    
    
    virtual bool init(CCArray* baseInfoBeanArray);
//    CREATE_FUNC(TestScene);
    static TestScene* create(CCArray* beanArray);
//    CCArray* baseInfoBeanArray;
    CCArray* myArmyList;
    virtual void loadResource();
    virtual void releaseResource();
    
    void toDeployArmy(CCNode* pSender);
    void quitDeployCallBack();
    int flag[5];
    bool isChangeArmy;

    void displaySearchResultList(CCArray* searchBaseInfoBeanArray);
private:
    CCMenuItemSprite* getBaseInfoItem(BaseInfoBean* bean);
    void toNextCallBack();
    void toHomeCallBack(CCNode* pSender);
    void selectCard(MyMenuItem* pSender);
    void cancelCard(MyMenuItem* pSender);
    void initCloud();
    void cloudCallBack(CCNode* pSender,CCSprite* cloud);
    void toSearchNickname();
    void toAttachIME(CCMenuItem* item);
    void quitSearch();
    void sureSearchEnemyByNickname(CCMenuItem* item);
    ReadyToBattleTrigger* trigger;
};
