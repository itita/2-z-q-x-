//
//  NewbieStartScene.h
//  ww3
//
//  Created by xiao tang on 12-12-9.
//
//

#ifndef ww3_NewbieStartScene_h
#define ww3_NewbieStartScene_h
#include "cocos2d.h"
#include "MyBuilding.h"
#include "GXBaseScene.h"
#include "GXMsg.h"
#include "StartScene.h"
//state



class NewbieStartScene : public StartScene {
    
private:
    void initControl();
    virtual ~NewbieStartScene();
    
public:
    virtual bool init();
    CREATE_FUNC(NewbieStartScene);
    static  NewbieStartScene* create(CCArray* buildings);
    void toBattleScene();
    virtual bool init(CCArray* buildings);
    virtual void loadResource();
    virtual void releaseResource();
    void doPause();
    void toExit();
//    virtual void sendCallBack(CCNode* sender);
//    virtual void updateChar();
    
public:
    void hiddenControlUI();
    void displayControlUI();
    
};

class NewbieStartSceneCreator :public GXCreator {
    
public:
    CCArray* buildingBeans;
    virtual ~NewbieStartSceneCreator();
    
    NewbieStartSceneCreator():
    buildingBeans(NULL)
    {};
    
    virtual CCObject* creatObj();
    virtual void doFill(CCObject* entity);
    
    static NewbieStartSceneCreator* create(CCArray* array);
};

#endif
