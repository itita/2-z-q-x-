//
//  DefendInCreateState.cpp
//  ww4
//
//  Created by xiao tang on 13-8-17.
//
//

#include "DefendInCreateState.h"

#define attackRangeTipTag 2000


DefendInCreateState* DefendInCreateState::create(int _stateId,CCSprite* item) {
    DefendInCreateState* pState = new DefendInCreateState();
    pState->stateId = _stateId;
    pState->autorelease();
    pState->item = item;
    CC_SAFE_RETAIN(item);
    return pState;
}

void DefendInCreateState::dismissAllTransition() {
    building->removeChildByTag(attackRangeTipTag,true);
    NormalState::dismissAllTransition();
}

void DefendInCreateState::showAllTransition() {
    if (attackRange > 0) {
        CCSprite* attackRangeTip = (CCSprite*)building->getChildByTag(attackRangeTipTag);
        if (attackRangeTip == NULL) {
            attackRangeTip = CCSprite::createWithSpriteFrameName("attackRangeTip.png");
            building->addChild(attackRangeTip);
        } else {
            attackRangeTip->stopAllActions();
            attackRangeTip->setScale(1);
        }
        
        
//        building->setPosition(ccp(building->contentSizeByTiled.width/2*60,building));
        attackRangeTip->setOpacity(0);
        float scale = (attackRange*60)/attackRangeTip->getContentSize().width;
        attackRangeTip->runAction(CCSpawn::create(CCFadeIn::create(0.3),CCEaseElasticOut::create(CCScaleTo::create(0.3,scale),1),NULL));
        attackRangeTip->setTag(attackRangeTipTag);
    }
    NormalState::showAllTransition();
    
}

void DefendInCreateState::setAttackRange(float _attackRange) {
    attackRange = _attackRange;
    if (attackRange > 0 && building != NULL && building->getActive()) {
        CCSprite* attackRangeTip = (CCSprite*)building->getChildByTag(attackRangeTipTag);
        if (attackRangeTip == NULL) {
            attackRangeTip = CCSprite::createWithSpriteFrameName("attackRangeTip.png");
            building->addChild(attackRangeTip);
        } else {
            attackRangeTip->stopAllActions();
            attackRangeTip->setScale(1);
        }
        
        
        //        building->setPosition(ccp(building->contentSizeByTiled.width/2*60,building));
        attackRangeTip->setOpacity(0);
        float scale = (attackRange*60)/attackRangeTip->getContentSize().width;
        attackRangeTip->runAction(CCSpawn::create(CCFadeIn::create(0.3),CCEaseElasticOut::create(CCScaleTo::create(0.3,scale),1),NULL));
        attackRangeTip->setTag(attackRangeTipTag);
    }
}
