//
//  NewMenuSpriteItem.cpp
//  ww2
//
//  Created by DingYu Fu on 12-9-13.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "NewMenuSpriteItem.h"

#include "cocos2d.h"

using namespace cocos2d;


NewMenuSpriteItem* NewMenuSpriteItem::create( cocos2d::CCNode *normalSprite, cocos2d::CCNode *selectedSprite, cocos2d::CCObject *target, SEL_MenuHandler selector) {
    NewMenuSpriteItem *pRet = new NewMenuSpriteItem();
    pRet->initWithNormalSprite(normalSprite, selectedSprite, NULL, target, selector); 
    pRet->autorelease();
    //    pRet->contentSizeByTiled = _contentSize;
    return pRet;
}


void NewMenuSpriteItem::runTouchAction() {
    //    CCScaleBy* action = CCScaleBy::create(0.5, 1.3);
    //    float zoom = 10/getContentSize().width;
    this->runAction(CCSequence::create(CCScaleTo::create(0.1, 1.15), CCScaleTo::create(0.1, 1.0),NULL));
}