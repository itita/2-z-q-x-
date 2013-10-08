//
//  MyProgressBar.cpp
//  ww3
//
//  Created by xiao tang on 12-10-17.
//
//

#include "MyProgressBar.h"
#include "DefineSet.h"
#include "Mathlib.h"


MyProgressBar* MyProgressBar::create(cocos2d::CCSprite *upSprite, cocos2d::CCSprite *backSprite,int maxCapacity) {
    MyProgressBar *progressBar = new MyProgressBar();
    if (progressBar && progressBar->init())
    {
        progressBar->autorelease();
        //        pobSprite->oriSize = pobSprite->getTextureRect().size;
        //        pobSprite->oriPoint = pobSprite->getTextureRect().origin;
        progressBar->myoriRect = upSprite->getTextureRect();
        //        pobSprite->myoriRect->retain()
        
        progressBar->addChild(backSprite);
        backSprite->setTag(backTag);
        backSprite->setAnchorPoint(ccp(0,0));
        progressBar->addChild(upSprite);
        upSprite->setAnchorPoint(ccp(0,0));
        progressBar->upSprite = upSprite;
        progressBar->maxCapacity = maxCapacity;
        char str[20] = {0};
        sprintf(str, "%d/%d",maxCapacity,maxCapacity);
        progressBar->label = CCLabelAtlas::create(str, "number2.png", 16, 30, '.');
        progressBar->label->setAnchorPoint(ccp(0.5,0.5));
        progressBar->label->setPosition(ccp(backSprite->getContentSize().width/2,backSprite->getContentSize().height/2));
        progressBar->addChild(progressBar->label,3);
        return progressBar;
    }
    CC_SAFE_DELETE(progressBar);
    return NULL;
}

void MyProgressBar::setCapacity(int capacity) {
    capacity = Mathlib::bound(capacity, maxCapacity, 0);
    float percentage = (float)capacity/(float)maxCapacity;
    GXProgressBar::updatePercentage(percentage);
    char str[20] = {0};
    sprintf(str, "%d/%d",capacity,maxCapacity);
    label->setString(str);
}

void MyProgressBar::setContentSize(const cocos2d::CCSize &var) {
    GXProgressBar::setContentSize(var);
    if (label !=NULL) {
        label->setScale(var.width*0.75/label->getContentSize().width);
        label->setPosition(ccp(var.width/2,var.height/2));
    }
}