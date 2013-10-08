//
//  NewbieBattleScene.h
//  ww3
//
//  Created by xiao tang on 12-12-17.
//
//

#ifndef __ww3__NewbieBattleScene__
#define __ww3__NewbieBattleScene__

#include "BattleScene.h"
#include "GXCreator.h"

#define enemyOilIconTag 10001
#define enemyIronIconTag 10002
#define enemyHonorIconTag 10003

using namespace cocos2d;

class NewbieBattleScene : public BattleScene {
    
public:
    ~NewbieBattleScene() {
        releaseResource();
    }
    static  NewbieBattleScene* create(CCArray* buildings);
    virtual bool init(cocos2d::CCArray *buildings);
    virtual void initUI();
    virtual void toFight();
    virtual CCLayer* getVictoryUI(bool isVictory);
    virtual void toBuildScene();
    virtual void callback1(CCObject* pSender);
    virtual void doPause();
    virtual void toSurrender();
    virtual void loadResource();
    virtual void releaseResource();
    MyBattleMap* getMap() {
        return battleMap;
    }
};

class NewbieBattleSceneCreator :public GXCreator {
    
public:
    CCArray* buildingBeans;
    virtual ~NewbieBattleSceneCreator();
    NewbieBattleSceneCreator():
    buildingBeans(NULL)
    {};
    
    virtual CCObject* creatObj();
    virtual void doFill(CCObject* entity);
    
    static NewbieBattleSceneCreator* create(CCArray* array);
};

#endif /* defined(__ww3__NewbieBattleScene__) */
