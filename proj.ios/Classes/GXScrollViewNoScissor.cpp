//
//  GXScrollViewNoScissor.cpp
//  ww4
//
//  Created by xiao tang on 13-7-25.
//
//

#include "GXScrollViewNoScissor.h"
#include "MathLib.h"

#define offsetX pTouch->getLocationInView().x - pTouch->getPreviousLocationInView().x
#define offsetY pTouch->getPreviousLocationInView().y - pTouch->getLocationInView().y
#define positionX this->getPosition().x
#define positionY this->getPosition().y

GXScrollViewNoScissor* GXScrollViewNoScissor::create(int _priority) {
    GXScrollViewNoScissor* pRet = new GXScrollViewNoScissor();
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


void GXScrollViewNoScissor::visit(void) {
    CCLayer::visit();
}

void GXScrollViewNoScissor::setPosition(const CCPoint& newPosition) {
    CCNode::setPosition(newPosition);
    if(unionNode != NULL) {
        unionNode->setPosition(newPosition);
    }
}

//bool GXScrollViewNoScissor::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent) {
//    
//    if (!isVisible())
//    {
//		return false;
//    }
//    CCPoint touchLocation = pTouch->getLocation();
//    CCPoint local = this->convertToNodeSpace(touchLocation);
//    
//    if(Mathlib::inBound(local.x,
//                        viewSize.width,
//                        0)
//       &&Mathlib::inBound(local.y,
//                          viewSize.height,
//                          0)) {
//           //           dispatchToChild(pTouch, pEvent);
//           CC_UNUSED_PARAM(pEvent);
//           speedVector.x = 0;
//           speedVector.y = 0;
//           this->unschedule(schedule_selector(GXScrollView::decelerate));
//           if(isEnabled) {
//               if(mode == toggleMode) {
//                   
//                   m_pSelectedItem =this->itemForTouch(pTouch);
//                   isMove = false;
//               } else {
//                   m_pSelectedItem = this->itemForTouch(pTouch);
//                   if (m_pSelectedItem)
//                   {
//                       
//                       m_pSelectedItem->selected();
//                       
//                   }
//               }
//           }
//           
//           return true;
//       }
//    return false;
//    
//
//}
//
//void GXScrollViewNoScissor::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent) {
//    GXScrollView::ccTouchMoved(pTouch,pEvent);
//}
//
//void GXScrollViewNoScissor::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent) {
//    GXScrollView::ccTouchEnded(pTouch,pEvent);
//}