//
//  MyContinueTiledMenuItemSprite.cpp
//  ww2
//
//  Created by DingYu Fu on 12-9-15.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "MyContinueTiledMenuItemSprite.h"
#include "MyMap.h"
#include "MyBuilding.h"
#include "Mathlib.h"
#include "MyBattleMap.h"

MyContinueTiledMenuItemSprite::~MyContinueTiledMenuItemSprite() {
    CC_SAFE_RELEASE_NULL(spriteFileName);
}

MyContinueTiledMenuItemSprite* MyContinueTiledMenuItemSprite::create(CCString* spriteFileName,CCObject* target, SEL_MenuHandler selector) {
    
    MyContinueTiledMenuItemSprite *pRet = new MyContinueTiledMenuItemSprite();
    char str[64];
    sprintf(str, "%sc",spriteFileName->getCString());
    CCSprite* r = CCSprite::createWithSpriteFrameName(str);
    CCSprite* r1 = CCSprite::createWithSpriteFrameName(str);
//    sprintf(str, "%sl",spriteFileName->getCString());
//    CCSprite* l = CCSprite::createWithSpriteFrameName(str);
//    sprintf(str, "%su",spriteFileName->getCString());
//    CCSprite* u = CCSprite::createWithSpriteFrameName(str);
//    sprintf(str, "%sd",spriteFileName->getCString());
//    CCSprite* d = CCSprite::createWithSpriteFrameName(str);
    pRet->initWithNormalSprite(r, r1, NULL, target, selector); 
    pRet->autorelease();
    pRet->spriteFileName = spriteFileName;
    pRet->ld = 0;
    pRet->lu = 0;
    pRet->rd = 0;
    pRet->ru = 0;
    pRet->isSelected = false;
    spriteFileName->retain();
    //    pRet->contentSizeByTiled = _contentSize;
    return pRet;
} 

void MyContinueTiledMenuItemSprite::runTouchAction() {
    MyTiledMenuItemSprite::runTouchAction();
    isSelected = false;
    updateLoc(1);
}


void MyContinueTiledMenuItemSprite::selected() {
    CCMenuItem::selected();
    //TODO 废弃了
//    MyMenu* menu = (MyMenu*)this->getParent();
//    if (!isSelected && menu->getActive()) {
//        MyMap* map = dynamic_cast<MyMap*>(this->getParent()->getParent());
//        updateLoc(0);
//        lu = 0;
//        ld = 0;
//        ru = 0;
//        rd = 0;
//        isSelected = true;
//    }
}

void MyContinueTiledMenuItemSprite::updateLoc(int value) {
    //这个地方有点日甩
//    MyMap* map = dynamic_cast<MyMap*>(this->getParent()->getParent());
//    if (map!= NULL) {
//        CCArray* items = map->getItems();
//        CCObject* obj;
//        CCARRAY_FOREACH(items, obj) {
//            MyBuilding* builiding = (MyBuilding*)obj;
//            MyContinueTiledMenuItemSprite* item = dynamic_cast<MyContinueTiledMenuItemSprite*>(builiding->getChildByTag(myTiledMenuItemTag));
//            if(item != NULL && spriteFileName->compare(item->spriteFileName->getCString())==0) {
//                CCPoint itemPos = Mathlib::roundPoint(map->transMapToTiled(item->getParent()->getPosition()));
//                CCPoint thisPos = Mathlib::roundPoint(map->transMapToTiled(this->getParent()->getPosition())); 
//                if (itemPos.x - thisPos.x == 1 && itemPos.y == thisPos.y) {
//                    item->lu = value;
//                    this->rd = value;
//                    item->updateSprite();
//                } else if (itemPos.x - thisPos.x == -1 && itemPos.y == thisPos.y) {
//                    this->lu = value;
//                    item->rd = value;
//                    item->updateSprite();
//                } else if (itemPos.y - thisPos.y == 1 && itemPos.x == thisPos.x)  {
//                    this->ld = value;
//                    item->ru = value;
//                    item->updateSprite();
//                } else if (itemPos.y - thisPos.y == -1 && itemPos.x == thisPos.x) {
//                    this->ru = value;
//                    item->ld = value;
//                    item->updateSprite();
//                }
////                CCLog("x:%f,y:%f",itemPos.x,itemPos.y);
//                //            item->
//            }
//        }
//        updateSprite();
//    }
}

void MyContinueTiledMenuItemSprite::updateSprite() {
    char str[64];
    if ((ld && ru) && !lu && ! rd) {
        sprintf(str, "%sud.png",spriteFileName->getCString());
        CCSprite* r = CCSprite::createWithSpriteFrameName(str);
        this->setNormalImage(r);
    } else if((lu && rd) && !ld && !ru){
        sprintf(str, "%slr.png",spriteFileName->getCString());
        CCSprite* r = CCSprite::createWithSpriteFrameName(str);
        this->setNormalImage(r);
    } 
//    else if((lu && ru) && !ld && !rd) {
//        sprintf(str, "%slu.png",spriteFileName->getCString());
//        CCSprite* r = CCSprite::createWithSpriteFrameName(str);
//        this->setNormalImage(r);
//    } else if((lu && ld) && !ru && !rd) {
//        sprintf(str, "%srd.png",spriteFileName->getCString());
//        CCSprite* r = CCSprite::createWithSpriteFrameName(str);
//        this->setNormalImage(r);
//    } else if((ld && rd) && !ru && !lu) {
//        sprintf(str, "%slr.png",spriteFileName->getCString());
//        CCSprite* r = CCSprite::createWithSpriteFrameName(str);
//        this->setNormalImage(r);
//    } else if((ru && rd) && !lu && !ld) {
//        sprintf(str, "%sld.png",spriteFileName->getCString());
//        CCSprite* r = CCSprite::createWithSpriteFrameName(str);
//        this->setNormalImage(r);
//    } 
    else {
        sprintf(str, "%sc.png",spriteFileName->getCString());
        CCSprite* r = CCSprite::createWithSpriteFrameName(str);
        this->setNormalImage(r);
    }
}

MyContinueTiledMenuItemSprite* MyContinueTiledMenuItemSprite::create(cocos2d::CCString *spriteFileName) {
    MyContinueTiledMenuItemSprite *pRet = new MyContinueTiledMenuItemSprite();
    char str[64];
    sprintf(str, "%sc.png",spriteFileName->getCString());
    CCSprite* r = CCSprite::createWithSpriteFrameName(str);
    CCSprite* r1 = CCSprite::createWithSpriteFrameName(str);
    //    sprintf(str, "%sl",spriteFileName->getCString());
    //    CCSprite* l = CCSprite::createWithSpriteFrameName(str);
    //    sprintf(str, "%su",spriteFileName->getCString());
    //    CCSprite* u = CCSprite::createWithSpriteFrameName(str);
    //    sprintf(str, "%sd",spriteFileName->getCString());
    //    CCSprite* d = CCSprite::createWithSpriteFrameName(str);
    pRet->initWithNormalSprite(r, r1, NULL, NULL, NULL); 
    pRet->autorelease();
    pRet->spriteFileName = spriteFileName;
    pRet->ld = 0;
    pRet->lu = 0;
    pRet->rd = 0;
    pRet->ru = 0;
    pRet->isSelected = false;
    spriteFileName->retain();
    //    pRet->contentSizeByTiled = _contentSize;
    return pRet;
}


