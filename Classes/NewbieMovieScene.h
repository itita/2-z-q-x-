//
//  NewbieMovieScene.h
//  ww3
//
//  Created by xiao tang on 12-12-20.
//
//

#ifndef __ww3__NewbieMovieScene__
#define __ww3__NewbieMovieScene__

#include "BattleScene.h"
#include "GXCreator.h"

class NewbieMovieScene : public BattleScene{
    
public:
    ~NewbieMovieScene(){
        releaseResource();
        CCLog("newbieMove has released");
    }
    static  NewbieMovieScene* create(CCArray* buildings);
    virtual bool init(cocos2d::CCArray *buildings);
    virtual void initUI();
    virtual void toFight();
    virtual void toBuildScene();
    virtual void victory();
    virtual void doPause();
    virtual void toSurrender();
    virtual void loadResource();
    virtual void releaseResource();
    
    MyBattleMap* getMap() {
        return battleMap;
    }
};

class NewbieMoveSceneCreator :public GXCreator {
    
public:
    CCArray* buildingBeans;
    virtual ~NewbieMoveSceneCreator();
    NewbieMoveSceneCreator():
    buildingBeans(NULL)
    {};
    virtual CCObject* creatObj();
    virtual void doFill(CCObject* entity);
    
    static NewbieMoveSceneCreator* create(CCArray* array);
};

#endif /* defined(__ww3__NewbieMovieScene__) */
