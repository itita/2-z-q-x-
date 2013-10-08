//
//  ResourceBeAttackState.cpp
//  ww3
//
//  Created by xiao tang on 12-10-27.
//
//

#include "ResourceBeAttackState.h"
#include "Mathlib.h"
#include "BattleScene.h"



ResourceBeAttackState* ResourceBeAttackState::create(int _stateId, cocos2d::CCSprite *item, float life,float output,float maxCapacity,int resourceTag) {
    ResourceBeAttackState* pState = new ResourceBeAttackState();
    pState->stateId = _stateId;
    pState->autorelease();
    pState->life = life;
    pState->maxLife = life;
    //  CCSprite* grayBd = CCSprite::create(string);
    //    grayBd->setColor(ccGRAY);
    pState->item = item;
    pState->item->retain();
    pState->baseOutputPsecond = output;
    pState->outputPsecond = output;
    pState->baseMaxCapacity = maxCapacity;
    pState->maxCapacity = maxCapacity;
    pState->resourceTag = resourceTag;
    
    
    return pState;
    
}

void ResourceBeAttackState::setCapacity(float _capacity, long dt,float _rate) {
    float totalCapacity = Mathlib::bound(_capacity+outputPsecond*dt, maxCapacity, 0);
    this->capacity = totalCapacity;
//    float rate = Mathlib::bound((MyGameInfo::getInstance()->enemyPower/MyGameInfo::getInstance()->getPower())*0.2, 0.4, 0);
//    CCLog("rate:%f",rate);
    this->trophyRate = _rate;
    nowResource = this->capacity*_rate ;
//    nowResource = this->capacity*0.2 ;
}

float ResourceBeAttackState::getBaseMaxCapacity() {
    return baseMaxCapacity;
}

float ResourceBeAttackState::getBaseOutputPsecond() {
    return baseOutputPsecond;
}

void ResourceBeAttackState::setMaxCapacity(float maxCapacity) {
    this->maxCapacity = maxCapacity;
}

void ResourceBeAttackState::setOutputPsecond(float outputPsecond) {
    this->outputPsecond = outputPsecond;
}



bool ResourceBeAttackState::beAttack(float damage) {
//    float rate = Mathlib::bound((MyGameInfo::getInstance()->enemyPower/MyGameInfo::getInstance()->getPower())*0.2, 0.4, 0);
    float life = this->life - damage;
    float cha = nowResource - (Mathlib::max(life,0)/maxLife)*capacity*trophyRate;
    beRobberResource(cha);
    return BeAttackState::beAttack(damage);
}

void ResourceBeAttackState::beRobberResource(float num) {
    num = Mathlib::min(num,nowResource);
    robberResource+=num;
    MyGameInfo::getInstance()->changeResource(resourceTag, num);
    nowResource = nowResource-num;
    BattleScene* battleScene = (BattleScene*)building->getParent()->getParent();
    if (resourceTag == oilTag) {
        if(battleScene->enemyOilLabel->getTargetNumber()>5) {
            battleScene->enemyOilLabel->setNumber(battleScene->enemyOilLabel->getTargetNumber()-num);
        } else {
            battleScene->enemyOilLabel->setNumber(0);
        }
    } else {
        if(battleScene->enemyIronLabel->getTargetNumber()>5) {
            battleScene->enemyIronLabel->setNumber(battleScene->enemyIronLabel->getTargetNumber()-num);
        }else {
            battleScene->enemyIronLabel->setNumber(0);
        }
    }
}

float ResourceBeAttackState::getCapacity() {
    return capacity;
}

float ResourceBeAttackState::getLastCapacity() {
    return capacity-robberResource;
}

float ResourceBeAttackState::getArg0() {
    return getLastCapacity();
}

//ResourceBeAttackStateCreator* ResourceBeAttackStateCreator::create() {
//    ResourceBeAttackStateCreator* creator = new ResourceBeAttackStateCreator();
//    creator->autorelease();
//    return creator;
//}
//
//CCObject* ResourceBeAttackStateCreator::init() {
//    MyTiledMenuItemSprite* bdItem = MyTiledMenuItemSprite::create(CCSprite::create(CCMenuItemSpriteName), CCSprite::create(CCMenuItemSpriteName));
//    bdItem->setAnchorPoint(ccp(0.5,0.35));
////    ResourceBeAttackState* beAttackState = ResourceBeAttackState::create(BeAttackStateTag, bdItem,life,maxCapacity,maxCapacity,resourceTag);
////    doFill(beAttackState);
//    return NULL;
//}