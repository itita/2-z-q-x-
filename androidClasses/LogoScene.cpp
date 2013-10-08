//
//  LogoScene.cpp
//  ww2
//
//  Created by DingYu Fu on 12-8-17.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#define createCocosPoint(__X__,__Y__) cocos2d::CCPointMake((float)(__X__), (float)(__Y__))

#include <iostream>
#include "cocos2d.h"
#include "LogoSence.h"

using namespace cocos2d;

bool LogoScene::init() {
    CCLayer *layer = CCLayer::create();
    CCSprite *logo = CCSprite::create("itita.png");
//    logo->initWithFile("itita.png");
    layer->addChild(logo);
    this->addChild(layer);
    logo->setPosition(createCocosPoint(CCDirector::sharedDirector()->getWinSize().width/2,CCDirector::sharedDirector()->getWinSize().height/2));
    

    return true;
};

