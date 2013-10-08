//
//  NewCreateMap.cpp
//  ww2
//
//  Created by DingYu Fu on 12-9-13.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "NewCreateMap.h"
#include "MyEntity.h"
#include "DefineSet.h"
#include "GXUtil.h"


NewCreateMap* NewCreateMap::create(const char *tmxfileName) {
    NewCreateMap *pRet = new NewCreateMap();
    if (pRet->initWithTMXFile(tmxfileName))
    {
        pRet->autorelease();
        pRet->registerWithTouchDispatcher();
        pRet->viewSize = winSize;
        CCDirector::sharedDirector()->setProjection(kCCDirectorProjection2D);
        pRet->init();
        pRet->isCollision = false;
        return pRet;
    }
    CC_SAFE_DELETE(pRet);
    return NULL;
}

void NewCreateMap::loadTip() {
    GXUtil::loadResourceUtilSucc("tipTiled.plist", "tipTiled.pvr.ccz");
    char str[64] = {0};  
    sprintf(str, "greenTip.png");
    green = CCSprite::createWithSpriteFrameName(str);
    sprintf(str, "redTip.png");
    red = CCSprite::createWithSpriteFrameName(str);
    this->addChild(green);
    this->addChild(red);
    green->setVisible(false);
    red->setVisible(false);
}


       

CCSprite* NewCreateMap::getTip() {
    if(isCollision) {
        green->setVisible(false);
        red->setVisible(true);
        return red;
    } else {
        green->setVisible(true);
        red->setVisible(false);
        return green;
    }
}

void NewCreateMap::initTip(CCPoint pos,float scale) {
    //    green->setVisible(true);
    //    red->setVisible(true);
    green->setPosition(pos);
    red->setPosition(pos);
    green->setScale(scale);
    red->setScale(scale);
}

void NewCreateMap::dispearTip() {
    green->setVisible(false);
    red->setVisible(false);
}

bool NewCreateMap::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent){
    this->cancelAllBuilding();
    return GXScrollTMXTileMap::ccTouchBegan(pTouch, pEvent);
}

void NewCreateMap::cancelAllBuilding() {
    CCArray* children = this->getChildren();
    CCObject* obj;
    MyEntity* building;
    CCARRAY_FOREACH(children, obj) {
        building = dynamic_cast<MyEntity*>(obj);
        if(building != NULL) {
//            building->getChildByTag("menu");
        }
    }
    
}
