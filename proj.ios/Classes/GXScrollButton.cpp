//
//  GXScrollButton.cpp
//  ww2
//
//  Created by DingYu Fu on 12-8-25.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "GXScrollButton.h"
#include "cocos2d.h"

#include "Mathlib.h"
using namespace cocos2d;


GXScrollButton* GXScrollButton::creat(CCSprite* _downFacade,CCSprite* _upFacade) {
    GXScrollButton * pRet = new GXScrollButton();
    pRet->downFacade = _downFacade;
    pRet->upFacade = _upFacade;
	if (pRet && pRet->init())
    {
        pRet->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(pRet);
    }
    
    
	return pRet;
}

bool GXScrollButton::init() {
    isPress = false;
    this->addChild(upFacade);
    this->addChild(downFacade);
    downFacade->setVisible(false);
    return true;
}


bool GXScrollButton::onDown(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent) {
    return true;
}

bool GXScrollButton::onUp(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent) {
    return true;
}

bool GXScrollButton::onCancel(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent) {
    return true;
}

