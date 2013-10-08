////
////  MainMenuScroll.cpp
////  ww4
////
////  Created by xiao tang on 13-8-15.
////
////
//
//#include "MainMenuScroll.h"
//#include "Mathlib.h"
//
//#define offsetX pTouch->getLocationInView().x - pTouch->getPreviousLocationInView().x
//#define offsetY pTouch->getPreviousLocationInView().y - pTouch->getLocationInView().y
//#define positionX this->getPosition().x
//#define positionY this->getPosition().y
//
//MainMenuScroll* MainMenuScroll::create(int _priority,int _space,const CCPoint& _oriPoint) {
//    MainMenuScroll* pRet = new MainMenuScroll();
//    if (pRet && pRet->init())
//    {
//        pRet->priority = _priority;
//        pRet->space = _space;
//        pRet->oriPoint = _oriPoint;
//        pRet->autorelease();
//    }
//    else
//    {
//        CC_SAFE_DELETE(pRet);
//    }
//    return pRet;
//}
//
//void MainMenuScroll::addChild(cocos2d::CCNode* child) {
//    child->setPosition(oriPoint.x,oriPoint.y+this->getChildrenCount()*space);
//    GXScrollView::addChild(child);
//}
//
//
//bool MainMenuScroll::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent) {
//    if(GXScrollView::ccTouchBegan(pTouch,pEvent) && menuLight != NULL) {
//        menuLight->stopAllActions();
//        menuLight->runAction(CCFadeTo::create(0.5,255));
//        return true;
//    }
//    return false;
//}
//void MainMenuScroll::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent) {
//    if(menuLight != NULL) {
//        menuLight->stopAllActions();
//        menuLight->runAction(CCFadeTo::create(0.5,0));
//    }
//    return GXScrollView::ccTouchEnded(pTouch,pEvent);
//}
//
//void MainMenuScroll::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent) {
//    CCLayer::ccTouchMoved(pTouch,pEvent);
//    
//    if (isEnabled) {
//        
//        CCPoint lastLoc = this->getPosition();
//        this->setPosition(ccp(Mathlib::bound(positionX + offsetX,
//                                             oriPosition.x,
//                                             viewSize.width-mapSize.width+oriPosition.x),positionY + offsetY));
//        //    this->setPosition(ccp(newX,newY));
//        
//        if (mode == clickMode && m_pSelectedItem && Mathlib::getDistance(pTouch->getLocationInView(), pTouch->getPreviousLocationInView())>10) {
//            m_pSelectedItem->unselected();
//            m_pSelectedItem = NULL;
//        }
//        if (mode == toggleMode) {
//            if (m_pSelectedItem && Mathlib::getDistance(pTouch->getLocationInView(), pTouch->getPreviousLocationInView())>10) {
//                isMove = true;
//            }
//        }
//        speedVector.x = (getPosition().x - lastLoc.x+speedVector.x)/2;
//        speedVector.y = (getPosition().y - lastLoc.y+speedVector.y)/2;
//        int newCoordinate = preCoordinate;
//        if (this->getPositionY() > 0) {
//            newCoordinate = (int)(this->getPositionY()/space)+1;
//        } else {
//            newCoordinate = (int)(this->getPositionY()/space);
//        }
//        if(newCoordinate != preCoordinate) {
//            int count = this->getChildrenCount();
//            int cha = newCoordinate - preCoordinate;
//            for (int k = 1; k<=cha; k++) {
//                int index = 999;
//                float y  = 99999;
//                if (preCoordinate+k > 0) {
//                    index  = count-1- Mathlib::abs((preCoordinate+k-1)%count);
//                    y = oriPoint.y+(-preCoordinate-k)*space;
//                } else if(preCoordinate+k == 0) {
//                    index = 0;
//                    y = oriPoint.y+(-preCoordinate-k)*space;
//                } else {
//                    index =  Mathlib::abs((preCoordinate+1+k)%count);
//                    y = oriPoint.y+(-preCoordinate-k-1)*space;
//                } 
////                int index = count-1- Mathlib::abs((preCoordinate+k)%count);
////                int index = Mathlib::abs((count-preCoordinate-1-k)%count);
//                CCNode* node = (CCNode*)this->getChildren()->objectAtIndex(index);
//                node->setPosition(ccp(oriPoint.x,y));
//            }
//            for (int k = -1; k>=cha; k--) {
//                int index = 999;
//                if (preCoordinate+k > 0) {
//                    index  = count-1- Mathlib::abs((preCoordinate+k+count-6)%count);
//                } else if(preCoordinate+k == 0) {
//                    index = 5;
//                } else {
//                    index = Mathlib::abs((-preCoordinate-k+5)%count);
//                }
////                int index = Mathlib::abs((count-preCoordinate-k)%count);
////                int index = Mathlib::abs((preCoordinate+k)%count);
//                CCNode* node = (CCNode*)this->getChildren()->objectAtIndex(index);
//                float y = oriPoint.y+(5-preCoordinate-k)*space;
//                node->setPosition(ccp(oriPoint.x,y));
//            }
//            preCoordinate = newCoordinate;
//        }
////        if (this) {
//
//    }
//}
//
////void MainMenuScroll::visit(void) {
////    CCLayer::visit();
////}
//
//void MainMenuScroll::decelerate() {
//    this->setPosition(ccp(Mathlib::bound(positionX + speedVector.x,
//                                         oriPosition.x,
//                                         viewSize.width-mapSize.width+oriPosition.x),positionY + speedVector.y));
//    float length = Mathlib::getDistance(ccp(0,0), speedVector);
//    if(length < decelerateSpeed) {
//        this->unschedule(schedule_selector(GXScrollView::decelerate));
//    }
//    speedVector.x -= decelerateSpeed * speedVector.x/length;
//    speedVector.y -= decelerateSpeed * speedVector.y/length;
//    int newCoordinate = preCoordinate;
//    if (this->getPositionY() > 0) {
//        newCoordinate = (int)(this->getPositionY()/space)+1;
//    } else {
//        newCoordinate = (int)(this->getPositionY()/space);
//    }
//    if(newCoordinate != preCoordinate) {
//        int count = this->getChildrenCount();
//        int cha = newCoordinate - preCoordinate;
//        for (int k = 1; k<=cha; k++) {
//            //new > ord 向上增加
//            int index = 999;
//            float y  = 99999;
//            if (preCoordinate+k > 0) {
//                index  = count-1- Mathlib::abs((preCoordinate+k-1)%count);
//                y = oriPoint.y+(-preCoordinate-k)*space;
//            } else if(preCoordinate+k == 0) {
//                index = 0;
//                y = oriPoint.y+(-preCoordinate-k)*space;
//            } else {
//                index =  Mathlib::abs((preCoordinate+1+k)%count);
//                y = oriPoint.y+(-preCoordinate-k-1)*space;
//            }
//            
////            int index = Mathlib::abs((count-preCoordinate-1-k)%count);
//            CCNode* node = (CCNode*)this->getChildren()->objectAtIndex(index);
////            float y = oriPoint.y+(-preCoordinate-k)*space;
//            node->setPosition(ccp(oriPoint.x,y));
//        }
//        for (int k = -1; k>=cha; k--) {
////            int index = Mathlib::abs((count-preCoordinate-k)%count);
////            int index = Mathlib::abs((preCoordinate+k)%count);
//            int index = 999;
//            if (preCoordinate+k > 0) {
//                index = count-1- Mathlib::abs((preCoordinate+k+count-6)%count);
//            } else if(preCoordinate+k == 0) {
//                index = 5;
//            } else {
//                index = Mathlib::abs((-preCoordinate-k+5)%count);
//            }
//            CCNode* node = (CCNode*)this->getChildren()->objectAtIndex(index);
////            float y = oriPoint.y+(count-preCoordinate-k)*space;
//            node->setPosition(ccp(oriPoint.x,oriPoint.y+(5-preCoordinate-k)*space));
//        }
//        preCoordinate = newCoordinate;
//    }
//}