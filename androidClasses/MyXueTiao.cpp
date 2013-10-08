//
//  MyXueTiao.cpp
//  ww2
//
//  Created by DingYu Fu on 12-9-9.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "MyXueTiao.h"
#include "cocos2d.h"
#include "Mathlib.h"

MyXueTiao* MyXueTiao::create(const char *filename) {
    MyXueTiao *pobSprite = new MyXueTiao();
    if (pobSprite && pobSprite->initWithFile(filename))
    {
        pobSprite->autorelease();
        pobSprite->setAnchorPoint(ccp(0,0.5));
//        pobSprite->oriSize = pobSprite->getTextureRect().size;
//        pobSprite->oriPoint = pobSprite->getTextureRect().origin;
        pobSprite->myoriRect = pobSprite->getTextureRect();
//        pobSprite->myoriRect->retain()
        pobSprite->percentage = 100;
        return pobSprite;
    }
    CC_SAFE_DELETE(pobSprite);
    return NULL;
}

void MyXueTiao::updatePercentage(float percentage) {
//    getTextureRect().= oriSize.height/2; 
    this->percentage = percentage;
    float zoom = Mathlib::bound(percentage, 1, 0);
    setTextureRect(CCRectMake(myoriRect.origin.x, myoriRect.origin.y, myoriRect.size.width *zoom, myoriRect.size.height));
}