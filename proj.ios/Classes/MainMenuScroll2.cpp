//
//  MainMenuScroll2.cpp
//  ww4
//
//  Created by xiao tang on 13-8-30.
//
//

#include "MainMenuScroll2.h"
#include "Mathlib.h"

#define offsetX pTouch->getLocationInView().x - pTouch->getPreviousLocationInView().x
#define offsetY pTouch->getPreviousLocationInView().y - pTouch->getLocationInView().y
#define positionX this->getPosition().x
#define positionY this->getPosition().y


MainMenuScroll2* MainMenuScroll2::create(int _priority) {
    MainMenuScroll2* pRet = new MainMenuScroll2();
    if (pRet && pRet->init())
    {
        pRet->screenWidth = CCEGLView::sharedOpenGLView()->getFrameSize().width;
        pRet->priority = _priority;
        pRet->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(pRet);
    }
    return pRet;
}

void MainMenuScroll2::visit(void) {
    glEnable(GL_SCISSOR_TEST);
   
    
//    float zoomX = screenWidthRate;
	float zoomY = screenHeightRate;
//	float orix = getOriPosition().x * zoomX;
	float oriy = getOriPosition().y * zoomY;
//	float viewW = viewSize.width * zoomX;
	float viewH = viewSize.height * zoomY;
	glScissor(0, oriy, screenWidth, viewH);
    
    
    CCLayer::visit();
    
    glDisable(GL_SCISSOR_TEST);

}

void MainMenuScroll2::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent) {
    CCLayer::ccTouchMoved(pTouch,pEvent);
  
    if (isEnabled) {
        float offsetYCount = offsetY;
        float xiajie = viewSize.height-mapSize.height+oriPosition.y;
        CCPoint lastLoc = this->getPosition();
        this->setPosition(ccp(Mathlib::bound(positionX + offsetX,
                                             oriPosition.x,
                                             viewSize.width-mapSize.width+oriPosition.x),positionY + offsetYCount));
        
//        Mathlib::bound(positionY + offsetY,
//                       oriPosition.y,
//                       viewSize.height-mapSize.height+oriPosition.y)
//        CCLog("offsetY : %f",offsetYCount);
        if (positionY > oriPosition.y && offsetYCount>0) {
//            CCLog("juli:%f,xiajie:%f,height:%f",(positionY-oriPosition.y),xiajie,viewSize.height);
//            float rate =  Mathlib::min(1,((positionY-positionY)/(viewSize.height/2)));
//            CCLog("rate:%f",rate);
            this->setPositionY(positionY-offsetYCount*Mathlib::min(1,((positionY-oriPosition.y)/(viewSize.height/2))));
        } else if(positionY < xiajie && offsetYCount <0) {
//            CCLog("oriY:%f",positionY);
//            CCLog("juli:%f,xiajie:%f,height:%f",(xiajie-positionY),xiajie,viewSize.height);
//            Mathlib::min(1,((xiajie-positionY)/(viewSize.height/2)));
//            float rate =  Mathlib::min(1,((xiajie-positionY)/(viewSize.height/2)));
//            CCLog("rate:%f",rate);
            this->setPositionY(positionY-offsetYCount*Mathlib::min(1,((xiajie-positionY)/(viewSize.height/2))));
//            CCLog("newY:%f",positionY);
        }
        
        
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

void MainMenuScroll2::decelerate() {
    this->setPosition(ccp(Mathlib::bound(positionX + speedVector.x,
                                         oriPosition.x,
                                         viewSize.width-mapSize.width+oriPosition.x),
                          positionY + speedVector.y));
//    Mathlib::bound(positionY + speedVector.y,
//                   oriPosition.y,
//                   viewSize.height-mapSize.height+oriPosition.y
    
//    CCLog("%f",speedVector.x);
//    CCLog("%f",speedVector.y);
    float length = Mathlib::getDistance(ccp(0,0), speedVector);
    
    float xiajie = viewSize.height-mapSize.height+oriPosition.y;
    if(length != 0) {
        speedVector.x -= decelerateSpeed * speedVector.x/length;
        speedVector.y -= 5 * speedVector.y/length;
    }
    if (positionY > oriPosition.y) {
        this->setPositionY(positionY-50*Mathlib::max(0.05,((positionY-oriPosition.y)/200)));
        if(speedVector.y < 10) {
            speedVector.y = 0;
        }
    } else if(positionY < xiajie) {
        this->setPositionY(positionY+50*Mathlib::max(0.05,((xiajie-positionY)/200)));
        if(speedVector.y > -10) {
            speedVector.y = 0;
        }
    } else {
        if( length < decelerateSpeed) {
            this->unschedule(schedule_selector(GXScrollView::decelerate));
        }
    }
}

//bool MainMenuScroll2::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent) {
////    if(GXScrollView::ccTouchBegan(pTouch,pEvent) && menuLight != NULL) {
////        menuLight->stopAllActions();
////        menuLight->runAction(CCFadeTo::create(0.5,255));
////        return true;
////    }
//    if(GXScrollView::ccTouchBegan(pTouch,pEvent) && menuUpTip != NULL) {
//        if(this->getPositionY() > 510-715) {
//            menuUpTip->setVisible(true);
//            menuUpTip->stopAllActions();
//            menuUpTip->runAction(CCFadeTo::create(0.5,255));
//        }
//        return true;
//    }
//    return false;
//}

//void MainMenuScroll2::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent) {
////    if(menuLight != NULL) {
////        menuLight->stopAllActions();
////        menuLight->runAction(CCFadeTo::create(0.5,0));
////    }
//    if(menuUpTip != NULL) {
//        menuUpTip->setVisible(false);
//    }
//    return GXScrollView::ccTouchEnded(pTouch,pEvent);
//}
