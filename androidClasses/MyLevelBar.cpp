//
//  MyLevelBar.cpp
//  ww3
//
//  Created by xiao tang on 12-10-17.
//
//

#include "MyLevelBar.h"
#include "DefineSet.h"
#include "Mathlib.h"


MyLevelBar* MyLevelBar::create(cocos2d::CCSprite *upSprite, cocos2d::CCSprite *backSprite,const CCSize& size) {
    MyLevelBar *progressBar = new MyLevelBar();
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
//        progressBar->maxCapacity = maxCapacity;
        progressBar->label = CCLabelAtlas::create("0", "number5.png", 16, 22, '.');
        progressBar->label->setAnchorPoint(ccp(0,0.0));
        progressBar->label->setPosition(ccp(backSprite->getContentSize().width/2,backSprite->getContentSize().height/4*3));
        progressBar->addChild(progressBar->label,3);
        progressBar->setContentSize(size);
        return progressBar;
    }
    CC_SAFE_DELETE(progressBar);
    return NULL;
}

//void MyLevelBar::setCapacity(int capacity) {
//    capacity = Mathlib::bound(capacity, maxCapacity, 0);
//    float percentage = (float)capacity/(float)maxCapacity;
//    GXProgressBar::updatePercentage(percentage);
//    upSprite->setTextureRect(CCRectMake(myoriRect.origin.x, myoriRect.origin.y, 0, myoriRect.size.height));
//}

void MyLevelBar::setContentSize(const cocos2d::CCSize &var) {
    GXProgressBar::setContentSize(var);
    if (label !=NULL) {
        label->setScale(var.height*2/label->getContentSize().height);
        label->setPosition(ccp(var.width/2,var.height));
    }
}

void MyLevelBar::setLevel(int _level) {
    this->level = _level;
    char str[40] = {0};
    sprintf(str, "%d",level);
    label->setString(str);
}

void MyLevelBar::levelUp() {
    setLevel(level+1);
}