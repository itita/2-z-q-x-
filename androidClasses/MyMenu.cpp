//
//  MyMenu.cpp
//  ww2
//
//  Created by DingYu Fu on 12-8-25.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#define offsetX (pTouch->locationInView().x - pTouch->previousLocationInView().x)
#define offsetY (pTouch->previousLocationInView().y - pTouch->locationInView().y)
#define positionX (this->getPosition().x)
#define positionY (this->getPosition().y)
#define shiftX (pTouch->locationInView().x - this->convertToWorldSpace(this->getPosition()).x)
#define shiftY (pTouch->locationInView().y - this->convertToWorldSpace(this->getPosition()).y)
#define locationY ( CCDirector::sharedDirector()->getWinSize().height - pTouch->locationInView().y)
//#define pChildTiledSize ((MyTiledMenuItemSprite*)pChild)->contentSizeByTiled



#include <iostream>
#include "cocos2d.h"
#include "MyMenu.h"
#include "Mathlib.h"
#include "MyTiledMenuItemSprite.h"
#include "CoordinateTrans.h"
#include "DefineSet.h"
#include "SimpleAudioEngine.h"
#include "MyBattleMap.h"
#include "ReadyToBuild.h"

using namespace cocos2d;


MyMenu* MyMenu::create(const CCSize& contentSize,CCMenuItem* item, ...){
    va_list args;
    va_start(args,item);
    MyMenu *pRet = new MyMenu();
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
        va_end(args);
        pRet->contentSizeByTiled = contentSize;
        MyTiledMenuItemSprite* myItem= dynamic_cast<MyTiledMenuItemSprite*>(item);
        if(myItem != NULL) {
            //TODO
//            myItem -> setTag(myTiledMenuItemTag);
        }
        return pRet;
    }
    va_end(args);
    CC_SAFE_DELETE(pRet);
    return NULL;
}

void MyMenu::ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent){
    CCMenu::ccTouchMoved(pTouch, pEvent);
    if(moveEnabled) {
//        CCPoint gloabal = Mathlib::getGlobalPosition(this);
        CCPoint touchLocation = pTouch->getLocationInView();
        touchLocation = CCDirector::sharedDirector()->convertToGL(touchLocation);
        CCPoint tiled = map->transMapToTiled(map->convertToNodeSpace(touchLocation));
        if(contentSizeByTiled.width == 1 || contentSizeByTiled.height == 1) {
            CCPoint posi = map->transTiledToMap(Mathlib::roundPoint(tiled));
            if(posi.x != this->getPosition().x || posi.y != this->getPosition().y) {
            
                isMoved = true;
                CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sfx_movebuilding.wav");
                this->setPosition(posi);
                ((MyMap*)map)->collisionDetection();
                ((MyMap*)map)->getTip()->setPosition(posi);
                ((MyMap*)map)->moveArrowTip(Mathlib::roundPoint(tiled), this->contentSizeByTiled);
            }
            return;
        }
        int dx  = Mathlib::intToZero(tiled.x - cacheTouch.x);
        int dy = Mathlib::intToZero(tiled.y - cacheTouch.y);
        cacheTouch.x+=dx;
        cacheTouch.y+=dy;
        if(dx!=0 || dy!= 0) {
            isMoved = true;
            CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sfx_movebuilding.wav");
            CCPoint mapTiled = getPositionByTiled();
            
            this->setPositionByTiled(ccp(mapTiled.x + dx,mapTiled.y+dy));
            ((MyMap*)map)->collisionDetection();
            ((MyMap*)map)->getTip()->setPosition(this->getPosition());
            ((MyMap*)map)->moveArrowTip(this->getPositionByTiled(),contentSizeByTiled);
        }
    } else if(!isActive){
        if (!isMoved && Mathlib::getDistance(pTouch->getLocationInView(), pTouch->getPreviousLocationInView())>10) {
            isMoved = true;
        }
        map->ccTouchMoved(pTouch, pEvent);
    }
}



void MyMenu::setPosition(const cocos2d::CCPoint &pos) {
    if(map != NULL) {
        if(pos.x<300 ||pos.x>1350|| pos.y<250||pos.y>900) {
            CCLog("%f,%f",pos.x,pos.y);
        }
        
//        CCAssert(pos.x>transWindowToGLInRetina(300),"out of bound");
//        CCAssert(pos.y>transWindowToGLInRetina(250),"out of bound");
//        CCAssert(pos.x<transWindowToGLInRetina(1350),"out of bound");
//        CCAssert(pos.y<transWindowToGLInRetina(900),"out of bound");
    }
//    if (pos.x < 1 && pos.y<1) {
//        CCAssert(1 == 2,"out of bound");
//    }
    CCMenu::setPosition(pos);
    this->positionByTiled.x = 9999999;
}


void MyMenu::setMap(GXScrollTMXTileMap *_map) {
    map = _map;
//    tiledSize = transTiledSizeInRetina(map->layerNamed("tiled")->getMapTileSize());
//    setContentSizeByTiled(this->getContentSize());
}


void MyMenu::setPositionByTiled(const cocos2d::CCPoint &pos) {
    if(map != NULL) {
        this->setPosition(map->transTiledToMap(pos));
        this->positionByTiled = pos;
    } else {
        this->positionByTiled = pos;
    }
}

bool MyMenu::ccTouchBegan(cocos2d::CCTouch *touch, cocos2d::CCEvent *event) {
    if (isActive) {
        cacheTouch  = map->transMapToTiled(map->convertToNodeSpace(touch->getLocation()));
        if (CCMenu::ccTouchBegan(touch, event)) {
//            if (m_pSelectedItem->getTag() == myTiledMenuItemTag) {
//                moveEnabled = true;
//                isMoved = false;
//                //TODO
////                ((MyMap*)map)->moveTemp = this;
//                MyMenu::reorderZandTouchPriority(1000000, -499);
//            } else {
////                ((MyMap*)map)->moveTemp = this;
//                moveEnabled = false;
//                isMoved = false;
//            }
            return true;
        }
        return false;
    }
    if (((MyMap*)map)->isBuild()) {
        return false;
    }
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



void MyMenu::ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent) {
    
    //先检测路径在~调用回调
    
    if (m_pSelectedItem) {
        //TODO
//        if (m_pSelectedItem->getTag() == myTiledMenuItemTag)
        {
            
            //点击主建筑时
            
            MyMap* myMap = (MyMap*)map;
            if (!isActive && isMoved) {
                
                //未激活建筑 同时移动地图时，不激活建筑
                
                CC_UNUSED_PARAM(pTouch);
                CC_UNUSED_PARAM(pEvent);
                CCAssert(m_eState == kCCMenuStateTrackingTouch, "[Menu ccTouchEnded] -- invalid state");
                m_pSelectedItem->unselected();
                m_eState = kCCMenuStateWaiting;
            } else if(!isActive && !isMoved) {
                
                //未激活建筑时点击建筑时（不移动地图），激活建筑，取消其他建筑
                
                ((MyMap*)map)->cancelAllBuilding();
                CCMenu::ccTouchEnded(pTouch, pEvent);
            } else if(isActive && isMoved) {
                
                //激活建筑并拖动建筑
                
                if (myMap->collisionDetection()) {
                    
                    //落点有碰撞，播错误提示并取消
                    
                    CC_UNUSED_PARAM(pTouch);
                    CC_UNUSED_PARAM(pEvent);
                    CCAssert(m_eState == kCCMenuStateTrackingTouch, "[Menu ccTouchEnded] -- invalid state");
                    CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sfx_error.wav");
                    m_pSelectedItem->unselected();
                    m_eState = kCCMenuStateWaiting;
                } else {
                    //落点无碰撞，放置建筑
                    cacheLoc = this->getPosition();
                    CCPoint loc = getPositionByTiled();
                    MyMenu::reorderZandTouchPriority(999999-this->getPosition().y, kCCMenuHandlerPriority-loc.x-loc.y);
                    ((MyMap*)map)->dispearTip();
                    CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sfx_place.wav");
                    CCMenu::ccTouchEnded(pTouch, pEvent);
                }
            } else if(isActive && !isMoved) {
                
                //建筑激活并且没有移动
                if(!myMap->isBuild()) {
                    
                    //不在建筑模式下，取消选择
                    
                    if (!((MyMap*)map)->collisionDetection()) {
                        
                        //没有在碰撞区，成功取消，并设置Y的位置
                        
                        ((MyMap*)map)->cancelAllBuilding();
                        
                        CCPoint loc = getPositionByTiled();
                        MyMenu::reorderZandTouchPriority(999999-this->getPosition().y, kCCMenuHandlerPriority-loc.x-loc.y);
                        
                    } else {
                        
                        //在碰撞区，播错误声音，不取消
                        
                        CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sfx_error.wav");
                        
                    }
                    CC_UNUSED_PARAM(pTouch);
                    CC_UNUSED_PARAM(pEvent);
                    CCAssert(m_eState == kCCMenuStateTrackingTouch, "[Menu ccTouchEnded] -- invalid state");
                    m_pSelectedItem->unselected();
                    m_eState = kCCMenuStateWaiting;
                } else {
                    //在建筑模式下，
                    if (!((MyMap*)map)->collisionDetection()) {
                        
                        //没有在碰撞区
                        
                        CCPoint loc = getPositionByTiled();
                        MyMenu::reorderZandTouchPriority(999999-this->getPosition().y, kCCMenuHandlerPriority-loc.x-loc.y);
                        CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sfx_place.wav");
                        CCMenu::ccTouchEnded(pTouch, pEvent);
                    } else {
                        
                        //在碰撞区，播错误声音，不取消
                        
                        CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sfx_error.wav");
                        CC_UNUSED_PARAM(pTouch);
                        CC_UNUSED_PARAM(pEvent);
                        CCAssert(m_eState == kCCMenuStateTrackingTouch, "[Menu ccTouchEnded] -- invalid state");
                        m_pSelectedItem->unselected();
                        m_eState = kCCMenuStateWaiting;
                        
                    }
                }
                
            }
            
        }
        //todo
//        else
        {
            // 点击按键或者其他
            CCMenu::ccTouchEnded(pTouch, pEvent);
        }
    } else {
        CCMenu::ccTouchEnded(pTouch, pEvent);
    }
    isMoved = false;
    moveEnabled = false;
    
//    ((MyMap*)map)->dispearTip();
    
//    if(m_pSelectedItem && m_pSelectedItem->getTag() != myTiledMenuItemTag && !isMoved) {
//        CCMenu::ccTouchEnded(pTouch, pEvent);
//        isMoved = false;
//        return;
//    }
//    if (!isActive && isMoved) {
//        CC_UNUSED_PARAM(pTouch);
//        CC_UNUSED_PARAM(pEvent);
//        CCAssert(m_eState == kCCMenuStateTrackingTouch, "[Menu ccTouchEnded] -- invalid state");
//        if (m_pSelectedItem)
//        {
//            m_pSelectedItem->unselected();
//        }
//        m_eState = kCCMenuStateWaiting;
//        moveEnabled = false;
//        isMoved = false;
//        return;
//    }
//    if(isActive && !isMoved && !((MyMap*)map)->isBuild()) {
//        if (!((MyMap*)map)->collisionDetection()) {
//            ((MyMap*)map)->cancelAllBuilding();
//            
//            CCPoint loc = getPositionByTiled();
//            MyMenu::reorderZandTouchPriority(999999-this->getPosition().y, kCCMenuHandlerPriority-loc.x-loc.y);
//            
//        } else {
//            CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sfx_error.wav");
//            
//        }
//        CC_UNUSED_PARAM(pTouch);
//        CC_UNUSED_PARAM(pEvent);
//        CCAssert(m_eState == kCCMenuStateTrackingTouch, "[Menu ccTouchEnded] -- invalid state");
//        if (m_pSelectedItem)
//        {
//            m_pSelectedItem->unselected();
//        }
//        m_eState = kCCMenuStateWaiting;
//        moveEnabled = false;
//        isMoved = false;
//        return;
//    }
//    
//    if (!isActive && !isMoved) {
//        ((MyMap*)map)->cancelAllBuilding();
//        CCMenu::ccTouchEnded(pTouch, pEvent);
//        return;
//    }
//    
//    if(isActive && moveEnabled && !((MyMap*)map)->collisionDetection()) {
//        cacheLoc = this->getPosition();
//        CCPoint loc = getPositionByTiled();
//        MyMenu::reorderZandTouchPriority(999999-this->getPosition().y, kCCMenuHandlerPriority-loc.x-loc.y);
//        ((MyMap*)map)->dispearTip();
//        if(isMoved) {
//            CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sfx_place.wav");
//        }
//        CCMenu::ccTouchEnded(pTouch, pEvent);
//    } else {
//        CC_UNUSED_PARAM(pTouch);
//        CC_UNUSED_PARAM(pEvent);
//        CCAssert(m_eState == kCCMenuStateTrackingTouch, "[Menu ccTouchEnded] -- invalid state");
//        CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sfx_error.wav");
//        if (m_pSelectedItem)
//        {
//            m_pSelectedItem->unselected();
//        }
//        m_eState = kCCMenuStateWaiting;
//    }
//    ((MyMap*)map)->moveArrowTip(getPositionByTiled(), contentSizeByTiled.width);
//    moveEnabled = false;
//    isMoved = false;
//    CCLog("%f",999999-this->getPosition().y);
    
    
}

CCMenuItem* MyMenu::itemForTouch(CCTouch *touch) {
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
                if (dynamic_cast<MyTiledMenuItemSprite*>(pChild) != NULL){
                    CCPoint posiT = map->transMapToTiled(this->getPosition());
                    
                    CCPoint tiled = map->transMapToTiled(map->convertToNodeSpace(touchLocation));
                    if (contentSizeByTiled.width == 1 && contentSizeByTiled.height == 1) {
                        CCPoint local = pChild->convertToNodeSpace(touchLocation);
                        CCRect r = ((CCMenuItem*)pChild)->rect();
                        r.origin = CCPointZero;
                        if (r.containsPoint(local))
                        {
                            //物体碰撞系统参数，上面是地形碰撞系统
//                            ((MyMap*)map)->initTip(this->getPosition(), contentSizeByTiled.width);
//                            ((MyMap*)map)->cancelAllBuilding();
//                            ((MyMap*)map)->moveTemp  = this;
                            cacheLoc = this->getPosition();
                            return (CCMenuItem*)pChild;
                        }
                    } else {
                        if(Mathlib::inBound(tiled.x, posiT.x+contentSizeByTiled.width/2, posiT.x-contentSizeByTiled.width/2) &&
                           Mathlib::inBound(tiled.y, posiT.y+contentSizeByTiled.height/2, posiT.y-contentSizeByTiled.height/2)) {
                            cacheLoc = this->getPosition();
//                            ((MyMap*)map)->initTip(this->getPosition(), contentSizeByTiled.width);
//                            ((MyMap*)map)->cancelAllBuilding();
//                            ((MyMap*)map)->moveTemp  = this;
                            return (CCMenuItem*)pChild;
                        }
                    }
                } else {
                    CCPoint local = pChild->convertToNodeSpace(touchLocation);
                    CCRect r = ((CCMenuItem*)pChild)->rect();
                    r.origin = CCPointZero;
                    if (r.containsPoint(local))
                    {
                        //物体碰撞系统参数，上面是地形碰撞系统
                        //TODO
//                        ((MyMap*)map)->moveTemp  = this;
                        cacheLoc = this->getPosition();
                        return (CCMenuItem*)pChild;
                    }
                }
            }
        }
    }
    return NULL;
}

void MyMenu::addChild(cocos2d::CCNode *child) {
    CCMenuItem* item = dynamic_cast<CCMenuItem*>(child);
    if(item) {
        CCMenu::addChild(child);
    } else {
        CCLayer::addChild(child);
    }
}

CCPoint MyMenu::getPositionByTiled() {
    positionByTiled = map->transMapToTiled(getPosition());
    return positionByTiled;
}

void MyMenu::addChild(cocos2d::CCNode *child,int zoreder) {
    CCMenuItem* item = dynamic_cast<CCMenuItem*>(child);
    if(item) {
        CCMenu::addChild(child,zoreder);
    } else {
        CCLayer::addChild(child,zoreder);
    }
}

void MyMenu::addChild(cocos2d::CCNode *child, int zOrder, int tag) {
    CCLayer::addChild(child,zOrder,tag);
}

void MyMenu::registerWithTouchDispatcher() {
    CCPoint loc = map->transMapToTiled(this->getPosition());
    CCDirector* pDirector = CCDirector::sharedDirector();
    pDirector->getTouchDispatcher()->addTargetedDelegate(this, kCCMenuHandlerPriority-loc.x-loc.y, true);
}

void MyMenu::setActive(bool active) {
    if (isEnabled()) {
        isActive = active;
        if (isActive) {
//            ((MyMap*)map)->moveTemp = this;
            CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sfx_pickup.wav");
            ((MyMap*)map)->moveArrowTip(this->getPositionByTiled(),contentSizeByTiled);
            ((MyMap*)map)->initTip(this->getPosition(), contentSizeByTiled);
            ((MyMap*)map)->arrowu->runAction(CCFadeIn::create(0.15));
            ((MyMap*)map)->arrowd->runAction(CCFadeIn::create(0.15));
            ((MyMap*)map)->arrowl->runAction(CCFadeIn::create(0.15));
            ((MyMap*)map)->arrowr->runAction(CCFadeIn::create(0.15));
        } else {
            ((MyMap*)map)->dispearArrowTip();
            ((MyMap*)map)->moveTemp = NULL;
        }
    }
}

void MyMenu::toReLoc() {
    this->setPosition(cacheLoc);
    CCPoint loc = this->getPositionByTiled();
    ((MyMap*)map)->moveArrowTip(loc,contentSizeByTiled);
    ((MyMap*)map)->dispearTip();
    reorderZandTouchPriority(999999-this->getPosition().y, kCCMenuHandlerPriority-loc.x-loc.y);
}

void MyMenu::reorderZandTouchPriority(int zorder,int TouchPriority) {
    this->scheduleOnce(schedule_selector(MyMenu::updateTouchPriority),0);
    this->getParent()->reorderChild(this, zorder);
    varTouchPriority = TouchPriority;
}
void MyMenu::updateTouchPriority() {
    CCDirector::sharedDirector()->getTouchDispatcher()->setPriority(varTouchPriority,this);
}


