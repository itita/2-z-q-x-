//
//  MyTiledMenuItemSprite.cpp
//  ww2
//
//  Created by DingYu Fu on 12-8-29.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "MyTiledMenuItemSprite.h"
#include "MyBuilding.h"
#include "cocos2d.h"


MyTiledMenuItemSprite::~MyTiledMenuItemSprite() {
    CCLog("MyTiledMenuItemSprite released");
}

MyTiledMenuItemSprite* MyTiledMenuItemSprite::create( cocos2d::CCNode *normalSprite, cocos2d::CCNode *selectedSprite, cocos2d::CCObject *target, SEL_MenuHandler selector) {
    MyTiledMenuItemSprite *pRet = new MyTiledMenuItemSprite();
    pRet->initWithNormalSprite(normalSprite, selectedSprite, NULL, target, selector); 
    pRet->autorelease();
//    pRet->contentSizeByTiled = _contentSize;
    return pRet;
}

MyTiledMenuItemSprite* MyTiledMenuItemSprite::create(cocos2d::CCNode *normalSprite, cocos2d::CCNode *selectedSprite) {
    MyTiledMenuItemSprite *pRet = new MyTiledMenuItemSprite();
    pRet->initWithNormalSprite(normalSprite, selectedSprite, NULL, NULL,NULL); 
    pRet->autorelease();
    //    pRet->contentSizeByTiled = _contentSize;
    return pRet;
}


void MyTiledMenuItemSprite::runTouchAction() {
//    CCScaleBy* action = CCScaleBy::create(0.5, 1.3);
//    float zoom = 10/getContentSize().width;
    this->runAction(CCSequence::create(CCScaleTo::create(0.1, 1.15), CCScaleTo::create(0.1, 1.0),NULL));
//    MyBuilding* mybuilding = dynamic_cast<MyBuilding*>(this->getParent());
//    this->scheduleOnce(schedule_selector(MyTiledMenuItemSprite::updateTouchPriority), 0);
}

//void MyTiledMenuItemSprite::updateTouchPriority() {
//    MyBuilding* mybuilding = dynamic_cast<MyBuilding*>(this->getParent());
//    CCPoint loc = mybuilding->map->transMapToTiled(mybuilding->getPosition());
//    CCDirector::sharedDirector()->getTouchDispatcher()->setPriority((int)(kCCMenuHandlerPriority-loc.x-loc.y),mybuilding);
//}

