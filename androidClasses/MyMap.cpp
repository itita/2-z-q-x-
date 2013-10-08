//
//  MyMap.cpp
//  WW2
//
//  Created by DingYu Fu on 12-8-26.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "MyMap.h"
#include "ReadyToBuild.h"
#include "GXScrollTMXTileMap.h"
#include "cocos2d.h"
#include "Mathlib.h"
#include "MyTiledMenuItemSprite.h"
#include "MyBuilding.h"
#include "StartScene.h"
#include "DefineSet.h"
#include "SimpleAudioEngine.h"
#include "MyTiledMenuItem.h"
#include "MyHttpConnection.h"

MyMap::~MyMap() {
//    items->release();
//    moveTemp->release();
//    CC_SAFE_RELEASE_NULL(moveTemp);
    CC_SAFE_RELEASE_NULL(items);
//    CCLog("MyMap released");
    //没有二次restain
    //所以在 child释放之后 就OVER了
//    green->release();
//    red->release();
//    arrowd->release();
//    arrowr->release();
//    arrowu->release();
//    arrowl->release();
//    items->release();
}


void MyMap::addChild(cocos2d::CCNode* child) {
   
//    MyMenu* menu = dynamic_cast<MyMenu*>(child);
//    if (menu != NULL) {
//        menu->setMap(this);
//        if(menu->positionByTiled.x<9999999) {
//            menu->setPositionByTiled(menu->positionByTiled);
//        }
//        if (!this->checkScreenBound(menu->getPosition().x, menu->getPosition().y)) {
//            CCLog("child out of bound");
////            CCAssert(1 == 2, "child out of bound");
//            return;
//        }
//        items->addObject(menu);
//        GXScrollTMXTileMap::addChild(child,999999-menu->getPositionY());
//        return;
//    }
//    GXScrollTMXTileMap::addChild(child);
    
    MyTiledMenuItem* item = dynamic_cast<MyTiledMenuItem*>(child);
    if (item != NULL) {
        item->setMap(this);
        if(item->positionByTiled.x<9999999) {
            item->setPositionByTiled(item->positionByTiled);
        }
        if (item->getTag()!=ghostTag && !this->checkRectTiledBound(this->transMapToTiled(item->getPosition()),item->contentSizeByTiled) ) {
            CCLog("child out of bound");
//            this->checkRectTiledBound(this->transMapToTiled(item->getPosition()),item->contentSizeByTiled);
            CCAssert(1 == 2, "child out of bound");
            return;
        }
        items->addObject(item);
        if(dynamic_cast<MyBuilding*>(item)) {
            ((MyBuilding*)item)->fsm->getCurrentState()->doStart();
        }
        if (((MyBuilding*)item)->getRoad() !=NULL) {
            roadSheet->addChild(((MyBuilding*)item)->getRoad());
        }
        GXScrollTMXTileMap::addChild(child,999999-item->getPositionY());
        return;
    }
    GXScrollTMXTileMap::addChild(child);
}

void MyMap::addChild(cocos2d::CCNode* child,int zorder){
    
//    MyMenu* menu = dynamic_cast<MyMenu*>(child);
//    if (menu != NULL) {
//        
//        menu->setMap(this);
//        if(menu->positionByTiled.x<9999999) {
//            menu->setPositionByTiled(menu->positionByTiled);
//        }
//        if (!this->checkScreenBound(menu->getPosition().x, menu->getPosition().y)) {
//            CCLog("child out of bound");
//            return;
//        }
//        items->addObject(menu);
//    }
//    GXScrollTMXTileMap::addChild(child,zorder);
    MyTiledMenuItem* item = dynamic_cast<MyTiledMenuItem*>(child);
    if (item != NULL) {
        item->setMap(this);
        if(item->positionByTiled.x<9999999) {
            item->setPositionByTiled(item->positionByTiled);
        }
        if (!this-> checkRectTiledBound(transMapToTiled(item->getPosition()),item->contentSizeByTiled)) {
            
            CCLog("child out of bound");
            if (!this->isBuild()) {
                CCAssert(1 != 2, "child out of bound");
                return;
            }
//            return;
        }
        items->addObject(item);
        if(dynamic_cast<MyBuilding*>(item)) {
            ((MyBuilding*)item)->fsm->getCurrentState()->doStart();
        }
    }
    GXScrollTMXTileMap::addChild(child,zorder);
}

void MyMap::removeChild(cocos2d::CCNode *child, bool cleanup) {
//    CCTMXTiledMap::removeChild(child, cleanup);
//    if (dynamic_cast<MyMenu*>(child) != NULL) {
//        items->removeObject(child);
//    }
    CCTMXTiledMap::removeChild(child, cleanup);
    if (dynamic_cast<MyTiledMenuItem*>(child) != NULL) {
        items->removeObject(child);
    }
}

MyMap* MyMap::create(const char *tmxFile) {
    MyMap *pRet = new MyMap();
    if (pRet->initWithTMXFile(tmxFile))
    {
        pRet->autorelease();
        pRet->setViewSize(winSize);
        
        pRet->items = CCArray::create();
        pRet->items->retain();
        pRet->loadTip();
//        pRet->oriPosition = ccp(0,0);
        pRet->contentMapSize = pRet->getContentSize();

//        CCSprite* tip = tipTiled
//        pRet->roadSheet = CCSpriteBatchNode::create("buildstruct.pvr.ccz");
//        pRet->addChild(pRet->roadSheet,1);
        return pRet;
    }
    CC_SAFE_DELETE(pRet);
    return NULL;

}

void MyMap::loadTip() {
//    char str[64] = {0};  
//    sprintf(str, "greenTip.png");
//    green = CCSprite::createWithSpriteFrameName("greenTip.png");
    green = CCLayer::create();
//    sprintf(str, "redTip.png");
    red = CCLayer::create();
    arrowu = CCSprite::createWithSpriteFrameName("tiparrowu.png");
    arrowd = CCSprite::createWithSpriteFrameName("tiparrowd.png");
    arrowl = CCSprite::createWithSpriteFrameName("tiparrowl.png");
    arrowr = CCSprite::createWithSpriteFrameName("tiparrowr.png");
    this->addChild(green,999999);
    this->addChild(red,999999);
    this->addChild(arrowu,999999);
    this->addChild(arrowd,999999);
    this->addChild(arrowl,999999);
    this->addChild(arrowr,999999);
    
    green->setVisible(false);
    red->setVisible(false);
    arrowu->setOpacity(0);
    arrowd->setOpacity(0);
    arrowl->setOpacity(0);
    arrowr->setOpacity(0);
}

bool MyMap::collisionDetection() {
    return collisionDetection(moveTemp);
}


bool MyMap::collisionDetection(CCMenuItem* checkItem) {
//    CCLog("comming");
    if (checkItem == NULL) {
        isCollision = true;
        return true;
    }
    
    cocos2d::CCObject* object;
    MyTiledMenuItem* temp = (MyTiledMenuItem*)checkItem;
//    CCPoint pos = temp->getPosition();
    if(!this->checkRectTiledBound(temp->getPositionByTiled(),temp->contentSizeByTiled)) {
//    if (pos.x<330 || pos.x>1480 || pos.y<210 ||pos.y>750) {
    
        //不能移动到地图外部。
        isCollision = true;
        return true;
    }
    CCARRAY_FOREACH(items, object) {
        MyTiledMenuItem* testItem = dynamic_cast<MyTiledMenuItem*>(object);
        if (testItem != temp) {
            CCPoint tiled1 = temp->getPositionByTiled();
            CCPoint tiled2 = testItem->getPositionByTiled();
            float dx = absf(tiled2.x - tiled1.x);
            float dy = absf(tiled2.y - tiled1.y);
            if(dx< (testItem->contentSizeByTiled.width + temp->contentSizeByTiled.width)/2 && dy<(testItem->contentSizeByTiled.height+ temp->contentSizeByTiled.height)/2
               ) {
                isCollision = true;
                return true;
            } else {
                isCollision = false;
            }
        } else {
//            CCLog("same");
        }
    }
    return false;
}

CCLayer* MyMap::getTip() {
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



void MyMap::initTip(CCPoint pos,CCSize &contentSize) {
    green->removeAllChildrenWithCleanup(true);
    red->removeAllChildrenWithCleanup(true);
    if (contentSize.width ==contentSize.height) {
        green->setPosition(pos);
        red->setPosition(pos);
        CCSprite* greenTip =  CCSprite::createWithSpriteFrameName("greenTip.png");
        CCSprite* redTip =  CCSprite::createWithSpriteFrameName("redTip.png");
        greenTip->setScale(contentSize.width);
        redTip->setScale(contentSize.width);
        green->addChild(greenTip);
        red->addChild(redTip);
    } else {
        int gcd = Mathlib::getGcd(contentSize.width,contentSize.height);
        float offsetX = 0;
        float offsetY = 0;
        if(((int)contentSize.width/gcd)%2 ==0) {
            offsetX+=0.5;
        }
        if(((int)contentSize.height/gcd)%2 ==0) {
            offsetY+=0.5;
        }
        CCPoint tiledPos = transMapToTiled(pos);
        int beiX = contentSize.width/gcd;
        int beiY = contentSize.height/gcd;
        green->setPosition(pos);
        red->setPosition(pos);
        CCPoint tempPos;
        for (int i=0;i<beiX;i++) {
            for (int j=0;j<beiY;j++) {
                CCSprite* greenTip =  CCSprite::createWithSpriteFrameName("greenTip.png");
                tempPos = transTiledToMap(ccp(tiledPos.x+(i-beiX/2+offsetX)*gcd,tiledPos.y+(j-beiY/2+offsetY)*gcd));
                greenTip->setPosition(ccp(tempPos.x-pos.x,tempPos.y-pos.y));
                greenTip->setScale(gcd);
                green->addChild(greenTip);
            }
        }
        for (int i=0;i<beiX;i++) {
            for (int j=0;j<beiY;j++) {
                CCSprite* redTip =  CCSprite::createWithSpriteFrameName("redTip.png");
                tempPos = transTiledToMap(ccp(tiledPos.x+(i-beiX/2+offsetX)*gcd,tiledPos.y+(j-beiY/2+offsetY)*gcd));
                redTip->setPosition(ccp(tempPos.x-pos.x,tempPos.y-pos.y));
                redTip->setScale(gcd);
                red->addChild(redTip);
            }
        }
    }
    

}

void MyMap::dispearTip() {
    if(isBuild()) {
        return;
    }
    green->setVisible(false);
    red->setVisible(false);
    green->removeAllChildrenWithCleanup(true);
    red->removeAllChildrenWithCleanup(true);
}

bool MyMap::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent){
    
    
    if (!m_enabled) {
        return false;
    }
    CCPoint test = transMapToTiled(ccp(pTouch->getLocationInView().x,pTouch->getLocationInView().y));
    CCPoint tiled = transMapToTiled(test);
    if(Mathlib::inBound(pTouch->getLocationInView().x,
                        0+viewSize.width,
                        0)
       &&Mathlib::inBound((CCDirector::sharedDirector()->getWinSize().height
                           -pTouch->getLocationInView().y),
                          0+viewSize.height,
                          0)) {
           speedVector.x = 0;
           speedVector.y = 0;
           this->unschedule(schedule_selector(MyMap::decelerate));
           if (this->isBuild()) {
               //TODO 在建造模式总是要返回些什么
               m_pSelectedItem = this->itemForTouch(pTouch);
               MyTiledMenuItem* tileItem = dynamic_cast<MyTiledMenuItem*>(m_pSelectedItem);
               if (tileItem)
               {
                   if (tileItem->getActive()) {
                       moveEnabled = true;
                       cacheTouch  = this->transMapToTiled(this->convertToNodeSpace(pTouch->getLocation()));
                       buildisMove = false;
                       this->moveTemp = m_pSelectedItem;
                       tileItem->reorderZandTouchPriority(1000000);
                       m_pSelectedItem->selected();
                       return true;
                   } else {
                       m_pSelectedItem = NULL;
                       return true;
                   }
               }
             
               if (m_pSelectedItem) {
                   if (m_pSelectedItem->getTag() != sureTransition && m_pSelectedItem->getTag() != CancelTransition ) {
                       m_pSelectedItem = NULL;
                   } else {
                       m_pSelectedItem->selected();
                   }
               }
               return true;
           }
           m_pSelectedItem = this->itemForTouch(pTouch);
           if (m_pSelectedItem)
           {
               //未建造模式下选择
               MyTiledMenuItem* tileItem = dynamic_cast<MyTiledMenuItem*>(m_pSelectedItem);
               if (tileItem != NULL) {
                   //选择主建筑
                   if (tileItem->getActive()) {
                       //TODO
                       moveEnabled = true;
                       cacheTouch  = this->transMapToTiled(this->convertToNodeSpace(pTouch->getLocation()));
                       buildisMove = false;
                       this->moveTemp = m_pSelectedItem;
                       tileItem->reorderZandTouchPriority(1000000);
                   }
                   
               } else {
                  // 选择按钮
//                   this->moveTemp = m_pSelectedItem;
                   buildisMove = false;
               }
               m_pSelectedItem->selected();
           } else {
               ((StartScene*)getParent())->cancelAllDialog();
           }
           return true;
       }
    return false;
    
}

bool MyMap::cancelAllBuilding() {
    CCObject* obj;
    MyBuilding* building;
    float flag = false;
    CCARRAY_FOREACH(items, obj) {
        //这段是测试用的
//        {
//            MyTiledMenuItem* tiledItem =  dynamic_cast<MyTiledMenuItem*>(obj);
//            if (tiledItem->getActive()) {
//                if(collisionDetection(tiledItem)) {
//                    tiledItem->toReLoc();
//                }
//                tiledItem->setActive(false);
//                flag = true;
//            }
//
//        }
        
        building = dynamic_cast<MyBuilding*>(obj);
        if(building != NULL) {
            if(building->getActive()) {
                //TODO
                if(collisionDetection(building)) {
                    building->toReLoc();
                }
                building->dismissAllTransition();
                building->dismissSummary();
                building->setActive(false);
                flag = true;
            } else {
//                flag = building->dismissSummary();
            }
        }
    }
    if(moveTemp!=NULL&&collisionDetection(moveTemp)) {
        ((MyTiledMenuItem*)moveTemp)->toReLoc();
        flag = true;
    }
    dispearArrowTip();
    dispearTip();
    return flag;
}

void MyMap::registerWithTouchDispatcher() {
    GXScrollTMXTileMap::registerWithTouchDispatcher();
    CCDirector::sharedDirector()->getKeypadDispatcher()->addDelegate(this);
}

void MyMap::unRegisterWithTouchDispatcher() {
    GXScrollTMXTileMap::unRegisterWithTouchDispatcher();
    CCDirector::sharedDirector()->getKeypadDispatcher()->removeDelegate(this);
}

void MyMap::keyBackClicked() {
    CCLog("keyBackClicked");
//    CCDirector::sharedDirector()->end();
    ((StartScene*)getParent())->toExit();
}

void MyMap::keyMenuClicked() {
    CCLog("keyMenuClicked");
}

void MyMap::dispearArrowTip(){
    arrowu->runAction(CCFadeTo::create(0.15,0));
//    arrowu->runAction(CCFadeOut::create(0.15));
    arrowr->runAction(CCFadeTo::create(0.15,0));
//    arrowr->runAction(CCFadeOut::create(0.15));
    arrowd->runAction(CCFadeTo::create(0.15,0));
//    arrowd->runAction(CCFadeOut::create(0.15));
    arrowl->runAction(CCFadeTo::create(0.15,0));
//    arrowl->runAction(CCFadeOut::create(0.15));
}

void MyMap::moveArrowTip(const cocos2d::CCPoint &pos, CCSize &size) {

    arrowu->setPosition(transTiledToMap(ccp(pos.x,pos.y- size.height/2 -1)));
    
    arrowl->setPosition(transTiledToMap(ccp(pos.x- size.width/2 -1,pos.y)));
    
    arrowr->setPosition(transTiledToMap(ccp(pos.x + size.width/2+1,pos.y)));
    
    arrowd->setPosition(transTiledToMap(ccp(pos.x,pos.y+ size.height/2 +1)));
    
}

void MyMap::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent) {
//    GXScrollTMXTileMap::ccTouchMoved(pTouch, pEvent);
    MyTiledMenuItem* item = dynamic_cast<MyTiledMenuItem*>(m_pSelectedItem);
    if(moveEnabled && item && item->moveEnabled) {
        //        CCPoint gloabal = Mathlib::getGlobalPosition(this);
        CCPoint touchLocation = pTouch->getLocationInView();
        touchLocation = CCDirector::sharedDirector()->convertToGL(touchLocation);
        CCPoint tiled = this->transMapToTiled(this->convertToNodeSpace(touchLocation));
        if(item->contentSizeByTiled.width == 1 || item->contentSizeByTiled.height == 1) {
            CCPoint posi = this->transTiledToMap(Mathlib::roundPoint(tiled));
            if(posi.x != item->getPosition().x || posi.y != item->getPosition().y) {
                //TODO
                buildisMove = true;
                CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sfx_movebuilding.wav");
                item->setPositionByTiled(this->transMapToTiled(posi));
                this->collisionDetection();
                this->getTip()->setPosition(posi);
                this->moveArrowTip(Mathlib::roundPoint(tiled), item->contentSizeByTiled);
            }
            return;
        }
        int dx  = Mathlib::intToZero(tiled.x - cacheTouch.x);
        int dy = Mathlib::intToZero(tiled.y - cacheTouch.y);
        cacheTouch.x+=dx;
        cacheTouch.y+=dy;
        if(dx!=0 || dy!= 0) {
            //TODO
            buildisMove = true;
            CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sfx_movebuilding.wav");
            CCPoint mapTiled = item->getPositionByTiled();
            
            item->setPositionByTiled(ccp(mapTiled.x + dx,mapTiled.y+dy));
            this->collisionDetection();
            this->getTip()->setPosition(item->getPosition());
            this->moveArrowTip(item->getPositionByTiled(),item->contentSizeByTiled);
        }
    } else {
        if (!isMoved && Mathlib::getDistance(pTouch->getLocationInView(), pTouch->getPreviousLocationInView())>14) {
            isMoved = true;
            if (m_pSelectedItem) {
                m_pSelectedItem->unselected();
            }
        }
        
//        map->ccTouchMoved(pTouch, pEvent);
        GXScrollTMXTileMap::ccTouchMoved(pTouch, pEvent);
    }
    
//    if (!isMoved && Mathlib::getDistance(pTouch->getLocationInView(), pTouch->getPreviousLocationInView()) > transWindowToGLInRetina(7)) {
//        isMoved = true;
//    }
}

void MyMap::ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent) {
    if (!m_pSelectedItem) {
        if(!isMoved && !isBuild()) {
            cancelAllBuilding();
        } else if(isBuild()&& !isMoved){
            CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sfx_error.wav");
            if (moveTemp && !checkRectTiledBound(this->transMapToTiled(moveTemp->getPosition()),((MyBuilding*)moveTemp)->contentSizeByTiled)) {
                
                //出界了,取消建筑模式
                ((ReadyToBuild*)((MyBuilding*)moveTemp)->fsm->getState(ReadyToBuildStateTag))->cancelCallBack(NULL);
                
            }
        }
        isMoved = false;
        GXScrollTMXTileMap::ccTouchEnded(pTouch, pEvent);
    } else {
        MyTiledMenuItem* tiledItem = dynamic_cast<MyTiledMenuItem*>(m_pSelectedItem);
        if (tiledItem != NULL) {
            
            //点击主建筑时
            if (!tiledItem->getActive() && isMoved) {
                
                //未激活建筑 同时移动地图时，不激活建筑
                
                CC_UNUSED_PARAM(pTouch);
                CC_UNUSED_PARAM(pEvent);
                m_pSelectedItem->unselected();
                GXScrollTMXTileMap::ccTouchEnded(pTouch, pEvent);
            } else if(!tiledItem->getActive() && !isMoved) {
                
                //未激活建筑时点击建筑时（不移动地图），激活建筑，取消其他建筑
                
                this->cancelAllBuilding();
                m_pSelectedItem->unselected();
                m_pSelectedItem->activate();
            } else if(tiledItem->getActive() && buildisMove) {
                
                //激活建筑并拖动建筑
                
                if (this->collisionDetection()) {
                    
                    //落点有碰撞，播错误提示并取消
                    
                    CC_UNUSED_PARAM(pTouch);
                    CC_UNUSED_PARAM(pEvent);
                    CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sfx_error.wav");
                    m_pSelectedItem->unselected();
                } else {
                    //落点无碰撞，放置建筑
                    tiledItem->cacheLoc = tiledItem->getPosition();
//                    CCPoint loc = tiledItem->getPositionByTiled();
                    tiledItem->reorderZandTouchPriority(999999-tiledItem->getPosition().y);
                    if(!isBuild()) {
                        //非建筑模式中，服务器更新建筑位置
                        MyHttpConnection::getInstance()->sendMovingBuilding(tiledItem->pid,tiledItem->getPositionByTiled());
                    }
//                    MyMenu::reorderZandTouchPriority(999999-this->getPosition().y, kCCMenuHandlerPriority-loc.x-loc.y);
                    this->dispearTip();
                    CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sfx_place.wav");
                    m_pSelectedItem->unselected();
                    m_pSelectedItem->activate();
                }
            } else if(tiledItem->getActive() && !buildisMove) {
                
                //建筑激活并且没有移动
                if(!this->isBuild()) {
                    
                    //不在建筑模式下，取消选择
                    
                    if (!this->collisionDetection()) {
                        
                        //没有在碰撞区，成功取消，并设置Y的位置
                        
                        this->cancelAllBuilding();
                        
                        CCPoint loc = tiledItem->getPositionByTiled();
                        tiledItem->reorderZandTouchPriority(999999-tiledItem->getPosition().y);
//                        MyMenu::reorderZandTouchPriority(999999-this->getPosition().y, kCCMenuHandlerPriority-loc.x-loc.y);
                        
                    } else {
                        
                        //在碰撞区，播错误声音，不取消
                        
                        CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sfx_error.wav");
                        
                    }
                    CC_UNUSED_PARAM(pTouch);
                    CC_UNUSED_PARAM(pEvent);
    
                    m_pSelectedItem->unselected();
                } else {
                    //在建筑模式下，
                    if (!this->collisionDetection()) {
                        
                        //没有在碰撞区
                        
                        CCPoint loc = tiledItem->getPositionByTiled();
                        tiledItem->reorderZandTouchPriority(999999-tiledItem->getPosition().y);
//                        MyMenu::reorderZandTouchPriority(999999-this->getPosition().y, kCCMenuHandlerPriority-loc.x-loc.y);
                        CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sfx_place.wav");
                        m_pSelectedItem->unselected();
                        m_pSelectedItem->activate();
                    } else {
                        
                        //在碰撞区，播错误声音，不取消
                        
                        CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sfx_error.wav");
                       
                        m_pSelectedItem->unselected();
                        
                    }
                }
                
            }
            
        }  else {
            // 点击按键或者其他
            if(!isMoved) {
                m_pSelectedItem->unselected();
//                CCLog("befor active");
                m_pSelectedItem->activate();
//                CCLog("end active");
            }
        }
        isMoved = false;
        moveEnabled = false;
        buildisMove = false;
    }
}

void MyMap::displayAllSummary() {
    CCObject* obj;
    MyBuilding* building;
    CCARRAY_FOREACH(items, obj) {
        building = dynamic_cast<MyBuilding*>(obj);
        if(building != NULL) {
            if (building->contentSizeByTiled.width >1) {
                building->displaySummary();
            }
        }
    }
}

bool MyMap::isBuild() {
    return _isBuild;
}

void MyMap::setBuild(bool __isbuild,CCMenuItem* moveTemp) {
    if (_isBuild != __isbuild) {
//        this->scheduleOnce(schedule_selector(MyMap::setMapPriority),0);
        if (__isbuild) {
            CCDirector::sharedDirector()->getTouchDispatcher()->setPriority(-503,this);
        } else {
            CCDirector::sharedDirector()->getTouchDispatcher()->setPriority(-127,this);
        }
    }
    
    _isBuild = __isbuild;
    this->moveTemp = moveTemp;
}
//
//void MyMap::setMapPriority() {
//    if (isBuild()) {
//        CCDirector::sharedDirector()->getTouchDispatcher()->setPriority(-503,this);
//    } else {
//        CCDirector::sharedDirector()->getTouchDispatcher()->setPriority(-127,this);
//    }
//}

CCMenuItem* MyMap::itemForTouch(cocos2d::CCTouch *touch) {
    CCPoint touchLocation = touch->getLocationInView();
    touchLocation = CCDirector::sharedDirector()->convertToGL(touchLocation);
    if (m_pChildren && m_pChildren->count() > 0)
    {
        CCObject* pObject = NULL;
        CCARRAY_FOREACH_REVERSE(m_pChildren, pObject)
        {
            CCMenuItem* pChild = dynamic_cast<CCMenuItem*>(pObject);
            if (pChild && pChild->isVisible() && pChild->isEnabled())
            {
                MyTiledMenuItem* tileItem = dynamic_cast<MyTiledMenuItem*>(pChild);
                if (tileItem != NULL) {
                    CCPoint posiT = this->transMapToTiled(pChild->getPosition());
                    
                    CCPoint tiled = this->transMapToTiled(this->convertToNodeSpace(touchLocation));
                    if (tileItem->getActive()) {
                        CCPoint local = this->convertToNodeSpace(touchLocation);
                        CCRect r = tileItem->rect();

                        if (r.containsPoint(local))
                        {
                            return (CCMenuItem*)pChild;
                        }
                    }else if(tileItem->contentSizeByTiled.width == 1&& tileItem->contentSizeByTiled.height == 1) {
                        CCPoint local = this->convertToNodeSpace(touchLocation);
                        CCRect r = tileItem->rect();
                        if (r.containsPoint(local))
                        {
                            
                            tileItem->cacheLoc = tileItem->getPosition();
                            return (CCMenuItem*)pChild;
                        }
                    } else {
                        if(Mathlib::inBound(tiled.x, posiT.x+tileItem->contentSizeByTiled.width/2, posiT.x-tileItem->contentSizeByTiled.width/2) &&
                           Mathlib::inBound(tiled.y, posiT.y+tileItem->contentSizeByTiled.height/2, posiT.y-tileItem->contentSizeByTiled.height/2)) {
                            tileItem->cacheLoc = tileItem->getPosition();
                            return tileItem;
                        }
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

bool MyMap::collisionDetectionSpecial(const CCPoint& testposi,const CCSize& size) {
    CCObject* object;
    CCARRAY_FOREACH(items, object) {
        MyTiledMenuItem* testItem = dynamic_cast<MyTiledMenuItem*>(object);
  
        CCPoint tiled2 = testItem->getPositionByTiled();
        if (testItem->getTag() >= ornamentsDefineTag) {
            continue;
        }
        float dx = absf(tiled2.x - testposi.x);
        float dy = absf(tiled2.y - testposi.y);
        if(dx< (testItem->contentSizeByTiled.width + size.width)/2 && dy<(testItem->contentSizeByTiled.height+ size.height)/2) {
            return true;
        }
    }
    return false;
}

