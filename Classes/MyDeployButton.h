//
//  MyDeployButton.h
//  ww2
//
//  Created by DingYu Fu on 12-9-6.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#ifndef ww2_MyDeployButton_h
#define ww2_MyDeployButton_h
#include "cocos2d.h"
#include "MyUnit.h"
#include "MyGameInfo.h"
#include "GXAntiCrack.h"

using namespace cocos2d;

class MyDeployButton : public CCMenuItemSprite {
public:
    ~MyDeployButton();
    MyDeployButton():
    bean(NULL),
    count(0),
    cooldown(100),
    currentCool(100),
    blackBack(NULL){
        summaryCount = GXintValue::create(0);
        summaryCount->retain();
    }
    
    CreatorInfoBean* bean;
    int count;
    int cooldown;
    
    static MyDeployButton* create(CreatorInfoBean* bean, CCObject* target, SEL_MenuHandler selector);
    void initDescription();
    virtual void selected();
    MyUnit* deployUnit();
    
    void recovereyCoolDown();
    
    
    
private:
    float currentCool;
    CCSprite* blackBack;
    GXintValue* summaryCount;
};



#endif
