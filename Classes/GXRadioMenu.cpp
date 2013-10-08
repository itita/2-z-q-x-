//
//  GXRadioMenu.cpp
//  ww2
//
//  Created by DingYu Fu on 12-9-6.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "GXRadioMenu.h"

GXRadioMenu* GXRadioMenu::create(int _priority,cocos2d::CCMenuItem *item, ...){
    va_list args;
    va_start(args,item);
    GXRadioMenu *pRet = new GXRadioMenu();
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
        pRet->selectTemp = NULL;
        pRet->priority = _priority;
        va_end(args);
        
        return pRet;
    }
    va_end(args);
    CC_SAFE_RELEASE_NULL(pRet);
    return NULL;
}

void GXRadioMenu::onEnter() {
    CCMenu::onEnter();
    setSelect(0);
}

GXRadioMenu* GXRadioMenu::create(int _priority) {
    GXRadioMenu *pRet = new GXRadioMenu();
    if (pRet && pRet->init())
    {
        pRet->autorelease();
        pRet->selectTemp = NULL;
//        pRet->setSelect(0);
        pRet->priority = _priority;
        return pRet;
    }
    CC_SAFE_DELETE(pRet);
    return NULL;
}

bool GXRadioMenu::ccTouchBegan(cocos2d::CCTouch *touch, cocos2d::CCEvent *event) {
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
    CCObject* obj;
    CCMenuItem* item;
    if (m_pSelectedItem)
    {
        CCARRAY_FOREACH(this->getChildren(), obj) {
            item = dynamic_cast<CCMenuItem*>(obj);
            item->unselected();
        }
        
        m_eState = kCCMenuStateTrackingTouch;
        m_pSelectedItem->selected();
        return true;
    }
    return false;
}

void GXRadioMenu::ccTouchMoved(cocos2d::CCTouch *touch, cocos2d::CCEvent *event){
    CC_UNUSED_PARAM(event);
    CCAssert(m_eState == kCCMenuStateTrackingTouch, "[Menu ccTouchMoved] -- invalid state");
    CCMenuItem *currentItem = this->itemForTouch(touch);
    if (currentItem != m_pSelectedItem) 
    {
        if (m_pSelectedItem)
        {
            m_pSelectedItem->unselected();
        }
        m_pSelectedItem = currentItem;
        if (m_pSelectedItem)
        {
            m_pSelectedItem->selected();
        }
    }
}

void GXRadioMenu::ccTouchEnded(cocos2d::CCTouch *touch, cocos2d::CCEvent *event) {
    CC_UNUSED_PARAM(touch);
    CC_UNUSED_PARAM(event);
    CCAssert(m_eState == kCCMenuStateTrackingTouch, "[Menu ccTouchEnded] -- invalid state");
    if (m_pSelectedItem)
    {
//        m_pSelectedItem->unselected();
        selectTemp = m_pSelectedItem;
        m_pSelectedItem->selected();
        m_pSelectedItem->activate();
    } else {
        selectTemp -> selected();
    }
    m_eState = kCCMenuStateWaiting;
}

void GXRadioMenu::setSelect(int index) {
    CCObject* obj;
    if (getChildren() && index < getChildren()->count()) {
        CCMenuItem* item;
        CCARRAY_FOREACH(this->getChildren(), obj) {
            item = dynamic_cast<CCMenuItem*>(obj);
            item->unselected();
        }
        selectTemp = item;
        item = (CCMenuItem*)getChildren()->objectAtIndex(index);
        item->selected();
        item->activate();
    }
}


void GXRadioMenu::registerWithTouchDispatcher()
{
    CCDirector* pDirector = CCDirector::sharedDirector();
    pDirector->getTouchDispatcher()->addTargetedDelegate(this, priority, true);
}
