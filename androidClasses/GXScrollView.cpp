//
//  GXScrollView.cpp
//  ww2
//
//  Created by DingYu Fu on 12-8-23.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#define offsetX pTouch->getLocationInView().x - pTouch->getPreviousLocationInView().x
#define offsetY pTouch->getPreviousLocationInView().y - pTouch->getLocationInView().y
#define positionX this->getPosition().x
#define positionY this->getPosition().y



#include <iostream>
#include "GXScrollView.h"
#include "cocos2d.h"
#include "Mathlib.h"

using namespace cocos2d;

float GXScrollView::screenWidthRate = 1;
float GXScrollView::screenHeightRate = 1;

GXScrollView::~GXScrollView() {
//    CCLog("GXScrollView Release");
}


bool GXScrollView::init() {
    CCLayer::init();
    this->setTouchEnabled(true);
    return true;
}


GXScrollView* GXScrollView::create(int _priority)
{
    GXScrollView* pRet = new GXScrollView();
    if (pRet && pRet->init())
    {
        pRet->priority = _priority;
        pRet->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(pRet);
    }
    return pRet;
}
bool GXScrollView::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent) {
//    CCLOG("COME BEGIN");
//    return CCLayer::ccTouchBegan(pTouch,pEvent);
//    CCLOG("thisX:%f", pTouch->locationInView().x);
//    CCLOG("thisY:%f", pTouch->locationInView().y);
    if (!isVisible())
    {
		return false;
    }
    
    if(Mathlib::inBound(pTouch->getLocationInView().x,
                        this->getOriPosition().x+viewSize.width,
                        this->getOriPosition().x)
       &&Mathlib::inBound((CCDirector::sharedDirector()->getWinSize().height
                           -pTouch->getLocationInView().y),
                          this->getOriPosition().y+viewSize.height,
                          this->getOriPosition().y)) {
//           dispatchToChild(pTouch, pEvent);
           CC_UNUSED_PARAM(pEvent);
           speedVector.x = 0;
           speedVector.y = 0;
           this->unschedule(schedule_selector(GXScrollView::decelerate));
           if(isEnabled) {
               if(mode == toggleMode) {
                   
                   m_pSelectedItem =this->itemForTouch(pTouch);
                   isMove = false;
               } else {
                   m_pSelectedItem = this->itemForTouch(pTouch);
                   if (m_pSelectedItem)
                   {
                       
                       m_pSelectedItem->selected();
                       
                   }
               }
           }
           
           return true;
    }
    return false;
}

void GXScrollView::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent) {
    CCLayer::ccTouchMoved(pTouch,pEvent);
//    CCLOG("thisX:%f", pTouch->locationInView().x);
//    CCLOG("thisY:%f", pTouch->locationInView().y);
//    CCLOG("preX:%f", pTouch->previousLocationInView().x);
//    CCLOG("preY:%f", pTouch->previousLocationInView().y);
//    mapSize
//    float positionX = this->getPosition().x;
//    float positionY = this->getPosition().y;
//    float offsetX  = pTouch->locationInView().x - pTouch->previousLocationInView().x;
//    float offsetY = pTouch->previousLocationInView().y - pTouch->locationInView().y;
//    float newX =Mathlib::bound(positionX + offsetX,
//                  oriPosition.x,
//                  viewSize.width-mapSize.width+oriPosition.x);
//    
//    float newY =Mathlib::bound(positionY + offsetY,
//                  oriPosition.y,
//                  viewSize.height-mapSize.height+oriPosition.y);
    if (isEnabled) {
        
        CCPoint lastLoc = this->getPosition();
        this->setPosition(ccp(Mathlib::bound(positionX + offsetX,
                                             oriPosition.x,
                                             viewSize.width-mapSize.width+oriPosition.x),
                              Mathlib::bound(positionY + offsetY,
                                             oriPosition.y,
                                             viewSize.height-mapSize.height+oriPosition.y)));
        //    this->setPosition(ccp(newX,newY));
        
        if (mode == clickMode && m_pSelectedItem && Mathlib::getDistance(pTouch->getLocationInView(), pTouch->getPreviousLocationInView())>10 ) {
            m_pSelectedItem->unselected();
            m_pSelectedItem = NULL;
        }
        if (mode == toggleMode) {
            if (m_pSelectedItem && Mathlib::getDistance(pTouch->getLocationInView(), pTouch->getPreviousLocationInView())>10) {
                isMove = true;
            }
        }
        
        
        speedVector.x = (getPosition().x - lastLoc.x+speedVector.x)/2;
        speedVector.y = (getPosition().y - lastLoc.y+speedVector.y)/2;
    }
}

void GXScrollView::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent) {
    CCLayer::ccTouchEnded(pTouch,pEvent);
    CC_UNUSED_PARAM(pTouch);
    CC_UNUSED_PARAM(pEvent);
    if (speedVector.x != 0 || speedVector.y != 0 ) {
        this->schedule(schedule_selector(GXScrollView::decelerate));
    }
    if (mode == clickMode) {
        if (m_pSelectedItem && isEnabled)
        {
            m_pSelectedItem->unselected();
            m_pSelectedItem->activate();
        }
    } else {
        if (!isMove&&m_pSelectedItem!=NULL) {
            CCObject* obj;
            CCMenuItem* item;
            CCARRAY_FOREACH(this->getChildren(), obj) {
                item = dynamic_cast<CCMenuItem*>(obj);
                item->unselected();
            }
            m_pSelectedItem->selected();
            m_pSelectedItem->activate();
        }
    }
    
}

void GXScrollView::registerWithTouchDispatcher(void) {
    //    CCLayer::registerWithTouchDispatcher();
    //    CCDirector* pDirector = CCDirector::sharedDirector();
//    CCLOG("registed");
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, priority, true);
    
    //    CCDirector::sharedDirector()->getTouchDispatcher()->addStandardDelegate(this,0);
    
}

void GXScrollView::setContentSize(const CCSize& size) {
    CCLayer::setContentSize(size);
    this->setViewSize(size);
    
}

void GXScrollView::setViewSize(const CCSize& size) {
    this->viewSize = size;
    mapSize = size;
}

void GXScrollView::setOriPosition(const CCPoint& point) {
    CCLayer::setPosition(point);
    this->oriPosition = point;
}

void GXScrollView::visit() {
    glEnable(GL_SCISSOR_TEST);
     //x, y, w, h
//    CCLog("OX:%f,OY:%f",oriPosition.x,oriPosition.y);
//    CCLog("Vw:%f,Vh:%f",viewSize.width, viewSize.height);
    
// 480 320 作为IOS设计大小存在。
    
//#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
//    glScissor(oriPosition.x, oriPosition.y, viewSize.width , viewSize.height);
//#endif
    
// 960 640 作为android设计大小存在
    
//#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    
//    float zoomX = screenWidthRate;
//	float zoomY = screenHeightRate;
	float orix = getOriPosition().x * screenWidthRate;
	float oriy = getOriPosition().y * screenHeightRate;
	float viewW = viewSize.width * screenWidthRate;
	float viewH = viewSize.height * screenHeightRate;
	glScissor(orix, oriy, viewW, viewH);
    
//    float heibian = screenSize.width
//    - (screenSize.height / 640 * 960);
//	float zoomX = screenSize.width / 960;
//	float zoomY = screenSize.height / 640;
//	float orix = getOriPosition().x * zoomX + heibian / 2;
//	float oriy = getOriPosition().y * zoomY;
//	float viewW = viewSize.width * zoomX - heibian;
//	float viewH = viewSize.height * zoomY;
//	glScissor(orix, oriy, viewW, viewH);
//#endif
    
    
    
    
    
    
//    glScissor(glScissorAdapter(oriPosition.x), glScissorAdapter(oriPosition.y), glScissorAdapter(viewSize.width), glScissorAdapter(viewSize.height));
   
    CCLayer::visit();

    glDisable(GL_SCISSOR_TEST);
}

void GXScrollView::setMapSize(CCSize size) {
    mapSize = CCSizeMake(MAX(size.width, viewSize.width), MAX(size.height, viewSize.height));
}

//void GXScrollView::dispatchToChild(CCTouch *pTouch, CCEvent *pEvent ) {
//    GXScrollButton* button = NULL;
//    CCObject* object = NULL;
//    CCARRAY_FOREACH(this->getChildren(), object) {
//        button = dynamic_cast<GXScrollButton*>(object);
//        if(button != NULL) {
//            CCLog("button down");
//        }
//    }
//}

CCMenuItem* GXScrollView::itemForTouch(CCTouch *touch)
{
    CCPoint touchLocation = touch->getLocation();
    
    if (m_pChildren && m_pChildren->count() > 0)
    {
        CCObject* pObject = NULL;
        CCARRAY_FOREACH_REVERSE(m_pChildren, pObject)
        {
            CCMenuItem* pChild = dynamic_cast<CCMenuItem*>(pObject);
            if (pChild && pChild->isVisible() && pChild->isEnabled())
            {
                CCPoint local = pChild->convertToNodeSpace(touchLocation);
                CCRect r = pChild->rect();
                r.origin = CCPointZero;
                
                if (r.containsPoint(local))
                {
                    return (CCMenuItem*)pChild;
                }
            }
        }
    }
    
    return NULL;
}

void GXScrollView::decelerate() {
    this->setPosition(ccp(Mathlib::bound(positionX + speedVector.x,
                                         oriPosition.x,
                                         viewSize.width-mapSize.width+oriPosition.x),
                          Mathlib::bound(positionY + speedVector.y,
                                         oriPosition.y,
                                         viewSize.height-mapSize.height+oriPosition.y)));
    float length = Mathlib::getDistance(ccp(0,0), speedVector);
    if(length < decelerateSpeed) {
        this->unschedule(schedule_selector(GXScrollView::decelerate));
    }
    speedVector.x -= decelerateSpeed * speedVector.x/length;
    speedVector.y -= decelerateSpeed * speedVector.y/length;
}

void GXScrollView::setMode(int modeCode) {
    if (modeCode==clickMode) {
        CCObject* obj;
        CCMenuItem* item;
        CCARRAY_FOREACH(this->getChildren(), obj) {
            item = dynamic_cast<CCMenuItem*>(obj);
            item->unselected();
        }
    } else {
        CCObject* obj;
        CCMenuItem* item;
        CCARRAY_FOREACH(this->getChildren(), obj) {
            item = dynamic_cast<CCMenuItem*>(obj);
            item->selected();
            item->activate();
            break;
        }
    }
    this->mode = modeCode;
}

void GXScrollView::runChildAction(cocos2d::CCAction *action) {
    CCObject* obj;
    CCARRAY_FOREACH(m_pChildren, obj) {
        ((CCNode*)obj)->runAction((CCAction*)action->copyWithZone(NULL));
    }
}

