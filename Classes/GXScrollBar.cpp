//
//  GXScrollBar.cpp
//  ww4
//
//  Created by xiao tang on 13-7-30.
//
//

#include "GXScrollBar.h"
#include "Mathlib.h"

GXScrollBar* GXScrollBar::create(int _priority,int length,CCObject* target,SEL_ScrollBarChangeRate selector)
{
    GXScrollBar *pRet = new GXScrollBar();
    if (pRet && pRet->CCLayer::init())
    {
        pRet->init(length);
        pRet->target = target;
        pRet->selector = selector;
        pRet->priority = _priority;
        pRet->setTouchEnabled(true);
        pRet->autorelease();
        return pRet;
    }
    CC_SAFE_DELETE(pRet);
    return NULL;
}

void GXScrollBar::init(int length) {
    CCSprite* bar = CCSprite::createWithSpriteFrameName("conversionSliderButton.png");
    this->bar = bar;
    bar->setPosition(ccp(-length/2+bar->getContentSize().width/2,0));
    
    CCSprite* scroller = CCSprite::createWithSpriteFrameName("conversionSliderScroller2.png");
    scroller->setScaleX(length/scroller->getContentSize().width);
    
    CCSprite* left = CCSprite::createWithSpriteFrameName("conversionSliderScroller.png");
    left->setPosition(ccp(-length/2,0));
//    left->setOpacity(255*0.5);
    
    
    CCSprite* right = CCSprite::createWithSpriteFrameName("conversionSliderScroller.png");
//    right->setAnchorPoint(ccp(0,0));
    right->setFlipX(true);
    right->setPosition(ccp(length/2,0));
//    right->setOpacity(255);
    
    this->addChild(scroller);
    
    this->addChild(right);
    this->addChild(left);
    this->addChild(bar);
    
    this->setContentSize(CCSizeMake(length,bar->getContentSize().height));
    this->length = length;
}

void GXScrollBar::registerWithTouchDispatcher()
{
    CCDirector* pDirector = CCDirector::sharedDirector();
    pDirector->getTouchDispatcher()->addTargetedDelegate(this, priority, true);
}


bool GXScrollBar::ccTouchBegan(cocos2d::CCTouch *touch, cocos2d::CCEvent *event) {
    CCPoint touchLocation = touch->getLocation();
    CCPoint local = this->convertToNodeSpace(touchLocation);
    if (local.x >= -1*getContentSize().width/2 && local.x <= getContentSize().width/2
        && local.y >= -1*getContentSize().height/2 && local.y <= getContentSize().height/2)
    {
        return true;
    }
    return false;
}

void GXScrollBar::ccTouchEnded(CCTouch *touch, CCEvent* event)
{
    
}



void GXScrollBar::ccTouchMoved(cocos2d::CCTouch *touch, cocos2d::CCEvent *event) {
    CCPoint touchLocation = touch->getLocation();
    CCPoint local = this->convertToNodeSpace(touchLocation);
    bar->setPositionX(Mathlib::bound(local.x,length/2-bar->getContentSize().width/2,-length/2+bar->getContentSize().width/2));
    
    percentage = (bar->getPosition().x+length/2-bar->getContentSize().width/2)/(length-bar->getContentSize().width);
    
    (target->*selector)(this);
}