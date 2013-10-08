//
//  MyState.h
//  ww2
//
//  Created by DingYu Fu on 12-9-2.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#ifndef ww2_MyState_h
#define ww2_MyState_h
#include "GXFSMstate.h"
#include "MyBuilding.h"
#include "GXCreator.h"

#define transitionMenuTag 500
#define zhuyeMenuTag 99999

class TransitionInfo : public CCObject {
    
public:
    
    TransitionInfo():
    spriteName(""),
    rec(NULL),
    tag(-1),
    selector(NULL)
    {
    }
    
    ~TransitionInfo() {
        //为避免循环持有~不保持~也不销毁
//        CC_SAFE_RELEASE_NULL(rec);
    }
    
    CCMenuItem* getButton();
    static TransitionInfo* create(int tag,const std::string& spriteName,CCObject* rec,SEL_MenuHandler selector);
    
    std::string spriteName;
    CCObject* rec;
    SEL_MenuHandler selector;
    int tag;
};

class MyState : public GXFSMstate {
public:
    MyState();
    MyBuilding* building;
    CCDictionary* itemDictionary;
    virtual void doState();
    static MyState* create(int _stateId,CCSprite* item);
    virtual void init(MyBuilding* building);
    virtual ~MyState();
    virtual void dismissAllTransition();
    virtual void showAllTransition();
    virtual void infoCallBack(cocos2d::CCObject *pSender);
    virtual void setItem(CCSprite* item);
    virtual CCSprite* getItem();
//    virtual void setUpdateInfo(CCLayer* updateLayer);
    virtual void addTransition(int inputId,int ioutputId,CCObject* menuitem);
    virtual void clickCallBack();
    virtual TransitionInfo* getTransition(int inputId);
//    void removeAllTransiton();
protected:
    CCSprite* item;
};



//class MyStateCreator : public GXCreator{
//    
//public:
//    MyStateCreator();
//    int stateId;
//    CCPoint itemAnchor;
//    const char* CCMenuItemSpriteName;
//    cocos2d::CCDictionary* transitionMap;
//    static MyStateCreator* create();
//    virtual CCObject* createObj();
//    virtual void doFill(CCObject* entity);
//    
//};

#endif
