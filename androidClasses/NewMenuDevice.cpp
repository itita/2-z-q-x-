//
//  NewMenuDevice.cpp
//  ww2
//
//  Created by DingYu Fu on 12-9-13.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "NewMenuDevice.h"
#include "NewMenuSpriteItem.h"
#include "Mathlib.h"
#include "NewCreateMap.h"

NewMenuDevice* NewMenuDevice::create(const CCSize& contentSize,CCMenuItem* item, ...){
    va_list args;
    va_start(args,item);
    NewMenuDevice *pRet = new NewMenuDevice();
    CCArray* pArray = NULL;
    if( item )
    {
        pArray = CCArray::create(item, NULL);
        CCMenuItem *i = va_arg(args, CCMenuItem*);
        while(i)
        {
            pArray->addObject(i);
            i = va_arg(args, CCMenuItem*);
        }
    }
    if (pRet && pRet->initWithArray(pArray))
    {
        pRet->autorelease();
        //        pRet->setContentSizeByTiled(_ContentTileSize);
        va_end(args);
        pRet->positionByTiled.x = 9999999;
        pRet->contentSizeByTiled = contentSize;
        pRet->isMoved = false;
        pRet->parent = NULL;
        NewMenuSpriteItem* myItem= dynamic_cast<NewMenuSpriteItem*>(item);
        if(myItem != NULL) {
            myItem -> setTag(TiledMenuItemTag);
        }
        return pRet;
    }
    va_end(args);
    CC_SAFE_DELETE(pRet);
    return NULL;
}

void NewMenuDevice::ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent){
    CCMenu::ccTouchMoved(pTouch, pEvent);
    if(isMoved) {
        //        CCPoint gloabal = Mathlib::getGlobalPosition(this);
        CCPoint touchLocation = pTouch->getLocationInView();
        touchLocation = CCDirector::sharedDirector()->convertToGL(touchLocation);
        CCPoint tiled = parent->getMap()->transMapToTiled(parent->getMap()->convertToNodeSpace(touchLocation));
        CCPoint posi = parent->getMap()->transTiledToMap(Mathlib::roundPoint(tiled));
        this->setPosition(posi);
        ((NewCreateMap*)parent->getMap())->getTip()->setPosition(posi);
//        ((NewCreateMap*)parent->getMap())->partService-;
    }
}



void NewMenuDevice::setPosition(const cocos2d::CCPoint &pos) {
    CCMenu::setPosition(pos);
    this->positionByTiled.x = 9999999;
}




void NewMenuDevice::setPositionByTiled(const cocos2d::CCPoint &pos) {
    if(parent->getMap() != NULL) {
        this->setPosition(parent->getMap()->transTiledToMap(pos));
    } else {
        this->positionByTiled = pos;
    }
}

bool NewMenuDevice::ccTouchBegan(cocos2d::CCTouch *touch, cocos2d::CCEvent *event) {
    //    CCPoint pouchT = map->transScreenToMap(ccp(pTouch->locationInView().x,pTouch->locationInView().y));
    //    CCPoint posiT = map->transMapToTiled(this->getPosition());
    //        
    //    CCPoint tiled = map->transMapToTiled(pouchT);
    //    if(Mathlib::inBound(tiled.x, posiT.x+contentSizeByTiled.width/2, posiT.x-contentSizeByTiled.width/2) &&
    //           Mathlib::inBound(tiled.y, posiT.y+contentSizeByTiled.height/2, posiT.y-contentSizeByTiled.height/2)) {
    //        isMoved = true;
    //    }
    //    return CCMenu::ccTouchBegan(pTouch, pEvent);
    
    CC_UNUSED_PARAM(event);
    if (m_eState != kCCMenuStateWaiting || ! m_bVisible || !isEnabled())
    {
        return false;
    }
    
    for (CCNode *c = this->m_pParent; c != NULL; c = c->getParent())
    {
        if (c->isVisible() == false)
        {
            return false;
        }
    }
    
    m_pSelectedItem = this->itemForTouch(touch);
    if (m_pSelectedItem)
    {
        m_eState = kCCMenuStateTrackingTouch;
        m_pSelectedItem->selected();
        return true;
    }
    return false;
    
}



void NewMenuDevice::ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent) {
    CCMenu::ccTouchEnded(pTouch, pEvent);
    isMoved = false;
    ((NewCreateMap*)parent->getMap())->dispearTip();
//    if(((NewCreateMap*)parent->getMap())->collisionDetection()) {
//        this->setPosition(cacheLoc);
//    }
}

CCMenuItem* NewMenuDevice::itemForTouch(CCTouch *touch) {
    CCPoint touchLocation = touch->getLocationInView();
    touchLocation = CCDirector::sharedDirector()->convertToGL(touchLocation);
    if (m_pChildren && m_pChildren->count() > 0)
    {
        CCObject* pObject = NULL;
        CCARRAY_FOREACH(m_pChildren, pObject)
        {
            CCMenuItem* pChild = dynamic_cast<CCMenuItem*>(pObject);
            if (pChild && pChild->isVisible() && ((CCMenuItem*)pChild)->isEnabled())
            {
                if (dynamic_cast<NewMenuSpriteItem*>(pChild) != NULL){
                    CCPoint posiT = parent->getMap()->transMapToTiled(this->getPosition());
                    
                    CCPoint tiled = parent->getMap()->transMapToTiled(parent->getMap()->convertToNodeSpace(touchLocation));
                    //                    CCLog("posiTx:%f,posiTy:%f", posiT.x,posiT.y);
                    //                    CCLog("tiledX:%f,tiledY:%f", tiled.x,tiled.y);
                    //                    CCLog("pChildTiledSizeW:%f,pChildTiledSizeH:%f",pChildTiledSize.width,pChildTiledSize.height);
                    if(Mathlib::inBound(tiled.x, posiT.x+contentSizeByTiled.width/2, posiT.x-contentSizeByTiled.width/2) &&
                       Mathlib::inBound(tiled.y, posiT.y+contentSizeByTiled.height/2, posiT.y-contentSizeByTiled.height/2)) {
                        isMoved = true;
                        cacheLoc = this->getPosition();
                        ((NewCreateMap*)parent->getMap())->initTip(this->getPosition(), contentSizeByTiled.width);
                        ((NewCreateMap*)parent->getMap())->moveTemp  = this;
                        ((NewCreateMap*)parent->getMap())->cancelAllBuilding();
                        return (CCMenuItem*)pChild;
                    }
                } else {
                    CCPoint local = pChild->convertToNodeSpace(touchLocation);
                    CCRect r = ((CCMenuItem*)pChild)->rect();
                    r.origin = CCPointZero;
                    if (r.containsPoint(local))
                    {
                        return (CCMenuItem*)pChild;
                    }
                }
            }
        }
    }
    return NULL;
}

void NewMenuDevice::addChild(cocos2d::CCNode *child) {
    CCMenuItem* item = dynamic_cast<CCMenuItem*>(child);
    if(item) {
        CCMenu::addChild(child);
    } else {
        CCLayer::addChild(child);
    }
}

void NewMenuDevice::addChild(cocos2d::CCNode *child,int zoreder) {
    CCMenuItem* item = dynamic_cast<CCMenuItem*>(child);
    if(item) {
        CCMenu::addChild(child,zoreder);
    } else {
        CCLayer::addChild(child,zoreder);
    }
}

void NewMenuDevice::addChild(cocos2d::CCNode *child, int zOrder, int tag) {
    CCLayer::addChild(child,zOrder,tag);
}

