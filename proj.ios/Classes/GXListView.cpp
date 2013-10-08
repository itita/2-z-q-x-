//
//  GXListView.cpp
//  ww3
//
//  Created by xiao tang on 12-11-22.
//
//

#include "GXListView.h"
#include "DefineSet.h"

#define moveAction 11

GXListView* GXListView::create(int _priority) {
    GXListView* pRet = new GXListView();
    if (pRet && pRet->init())
    {
        pRet->priority = _priority;
        pRet->childSize = CCSizeMake(0, 0);
        pRet->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(pRet);
    }
    return pRet;
}

void GXListView::addChild(cocos2d::CCNode *child) {
    GXScrollView::addChild(child);
    float cha = 0;
    if (childSize.height+child->getContentSize().height>mapSize.height) {
        cha = childSize.height+child->getContentSize().height - mapSize.height;
        mapSize = CCSizeMake(mapSize.width, childSize.height+child->getContentSize().height);
    }else {
//        mapSize = CCSizeMake(mapSize.width, mapSize.height+child->getContentSize().height);
        childSize = CCSizeMake(0, mapSize.height - child->getContentSize().height);
        cha = child->getContentSize().height;
    }
    
    child->setAnchorPoint(ccp(0,0));
    child->setPosition(ccp(40,childSize.height));
    childSize = CCSizeMake(0, childSize.height+child->getContentSize().height+10);
//    this->stopAllActions();
    
    if (this->getActionByTag(moveAction) != NULL) {
        this->stopActionByTag(moveAction);
    }
    
    CCAction* action = CCMoveTo::create(0.25, ccp(getPosition().x,viewSize.height-mapSize.height+oriPosition.y));
    action->setTag(moveAction);
    this->runAction(action);
    if (this->getChildrenCount() > 30) {
        ((CCNode*)this->getChildren()->objectAtIndex(0))->removeFromParentAndCleanup(true);
    }

    

}

void GXListView::addChildNoAction(cocos2d::CCNode *child) {
    GXScrollView::addChild(child);
    float cha = 0;
    if (childSize.height+child->getContentSize().height>mapSize.height) {
        cha = childSize.height+child->getContentSize().height - mapSize.height;
        mapSize = CCSizeMake(mapSize.width, childSize.height+child->getContentSize().height);
    }else {
      
        childSize = CCSizeMake(0, mapSize.height - child->getContentSize().height);
        cha = child->getContentSize().height;
    }
    
    child->setAnchorPoint(ccp(0,0));
    child->setPosition(ccp(40,childSize.height));
    childSize = CCSizeMake(0, childSize.height+child->getContentSize().height+10);
    this->setPosition(ccp(getPosition().x,viewSize.height-mapSize.height+oriPosition.y));
//    CCAction* action = CCMoveTo::create(0.25, ccp(getPosition().x,viewSize.height-mapSize.height+oriPosition.y));
//    action->setTag(moveAction);
//    this->runAction(action);
    if (this->getChildrenCount() > 30) {
        ((CCNode*)this->getChildren()->objectAtIndex(0))->removeFromParentAndCleanup(true);
    }
    
    
    
}

bool GXListView::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent) {
    if (!isEnabled) {
        return false;
    }
    return GXScrollView::ccTouchBegan(pTouch, pEvent);
}

void GXListView::removeChildAction(CCNode* child) {
    if (m_pChildren == NULL)
    {
        return;
    }
    int tag = m_pChildren->indexOfObject(child);
    for (int i = 0; i<tag; i++) {
        CCNode* node = (CCNode*)m_pChildren->objectAtIndex(i);
        node->runAction(CCMoveBy::create(0.2,ccp(0,child->getContentSize().height+10)));
    }
   
    
    removeChild(child,true);
}