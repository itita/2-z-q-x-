//
//  ServerSelectScroll2.cpp
//  ww4
//
//  Created by xiao tang on 13-9-20.
//
//

#include "ServerSelectScroll2.h"
#include "MyGameInfo.h"
#include "Mathlib.h"
#include "ServerScene.h"

#define offsetX pTouch->getLocationInView().x - pTouch->getPreviousLocationInView().x
#define offsetY pTouch->getPreviousLocationInView().y - pTouch->getLocationInView().y
#define positionX this->getPosition().x
#define positionY this->getPosition().y

ServerSelectScroll2* ServerSelectScroll2::create(int _priority) {
    ServerSelectScroll2* pRet = new ServerSelectScroll2();
    if (pRet && pRet->init())
    {
        pRet->priority = _priority;
//        pRet->beilv = winSize.width/960;
        pRet->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(pRet);
    }
    return pRet;
}

//bool ServerSelectScroll2::init() {
//    
//}

void ServerSelectScroll2::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent) {
    CCLayer::ccTouchMoved(pTouch,pEvent);
    if (isEnabled) {
        
        CCPoint lastLoc = this->getPosition();
        float realY = Mathlib::bound(positionY + offsetY,
                                     oriPosition.y,
                                     viewSize.height-mapSize.height+oriPosition.y);
        float realX = this->getPositionX()-(realY-this->getPositionY())*0.33;
        this->setPosition(ccp(realX,realY));

        if (mode == clickMode && m_pSelectedItem && Mathlib::getDistance(pTouch->getLocationInView(), pTouch->getPreviousLocationInView())>10 ) {
            m_pSelectedItem->unselected();
            m_pSelectedItem = NULL;
        }
        if (mode == toggleMode) {
            if (m_pSelectedItem && Mathlib::getDistance(pTouch->getLocationInView(), pTouch->getPreviousLocationInView())>10) {
                isMove = true;
            }
        }
    }
}

bool ServerSelectScroll2::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent) {
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
           speedVector.x = 0;
           speedVector.y = 0;
           return true;
       }
    return false;
}

void ServerSelectScroll2::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent) {
    CCLayer::ccTouchEnded(pTouch,pEvent);
    CC_UNUSED_PARAM(pTouch);
    CC_UNUSED_PARAM(pEvent);
//    this->schedule(schedule_selector(ServerSelectScroll::decelerate));
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
