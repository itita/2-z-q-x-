//
//  GXReverseSheild.cpp
//  ww3
//
//  Created by xiao tang on 12-12-19.
//
//

#include "GXReverseSheild.h"

GXReverseSheild* GXReverseSheild::create(int _priority)
{

    GXReverseSheild *pRet = new GXReverseSheild();
    if (pRet && pRet->CCMenu::init())
    {
        pRet->priority = _priority;
        pRet->autorelease();
        return pRet;
    }
    CC_SAFE_DELETE(pRet);
    return NULL;
}

void GXReverseSheild::registerWithTouchDispatcher()
{
    CCDirector* pDirector = CCDirector::sharedDirector();
    pDirector->getTouchDispatcher()->addTargetedDelegate(this, priority, true);
}

GXReverseSheild::~GXReverseSheild() {
//    CCLog("GXReverseSheild released");
}

bool GXReverseSheild::ccTouchBegan(cocos2d::CCTouch *touch, cocos2d::CCEvent *event) {
    CCPoint touchLocation = touch->getLocation();
    CCPoint local = this->convertToNodeSpace(touchLocation);
    CCRect r = CCRectMake( getPositionX() - getContentSize().width * getAnchorPoint().x,
                         getPositionY() - getContentSize().height * getAnchorPoint().y,
                         getContentSize().width, getContentSize().height);
    r.origin = CCPointZero;
    
    if (r.containsPoint(local))
    {
        return false;
    }
    return true;
   
}

void GXReverseSheild::ccTouchEnded(CCTouch *touch, CCEvent* event)
{
    
}

void GXReverseSheild::ccTouchMoved(cocos2d::CCTouch *touch, cocos2d::CCEvent *event) {
    
}