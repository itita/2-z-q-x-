//
//  AoeDefendState.cpp
//  ww2
//
//  Created by DingYu Fu on 12-9-23.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "AoeDefendState.h"
#include "cocos2d.h"
#include "GXAnimateFX.h"
#include "MyBattleMap.h"
#include "Mathlib.h"
#include "GXUtil.h"
#include "DefineSet.h"

AoeDefendState::~AoeDefendState() {
//    CCLog("AoeDefendState has release");
}

AoeDefendState* AoeDefendState::create(int _stateId, CCSprite* item,CCString* name,float life,float attackRange,float damage,float _splashRange,float attackRate,int _sfxId) {
    AoeDefendState* pState = new AoeDefendState();
    pState->stateId = _stateId;
    pState->autorelease();
    pState->life = life;
    pState->maxLife = life;
    pState->attackRange = attackRange;
    pState->damage = damage;
    pState->name = name;
    pState->splashRange = _splashRange;
    CC_SAFE_RETAIN(name);
//    pState->animateRate = animateRate;
    pState->doStateTime = attackRate;
    pState->sfxId = _sfxId;
    sprintf(pState->sfx, "sfx_%sf.wav",name->getCString());
    //  CCSprite* grayBd = CCSprite::create(string);
    //    grayBd->setColor(ccGRAY);
    pState->item = item;
    CC_SAFE_RETAIN(item);
    return pState;
}

void AoeDefendState::setItem(CCSprite *_item) {
    building->removeChildByTag(mainTiledSpriteTag, true);
    CC_SAFE_RELEASE(item);
    this->item = _item;
    _item ->setTag(mainTiledSpriteTag);
    _item->retain();
    building->addChild(_item,10);
//    xuetiao->removeFromParentAndCleanup(true);
//    _item->addChild(xuetiao,10);
}


void AoeDefendState::attackTarget(){
    //开炮间隔短于动画播放时间，开了第二炮，其实他已经死了，也没有目标了
    if(target==NULL) {
        setTarget(NULL);
        return;
    }
//    if (!target->isAlive()) {
//        <#statements#>
//    }
//    sprintf(sfx, "sfx_%sf.wav",name->getCString());
//    CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(sfx);
    if (target->fxCount < 1) {
        GXAnimateFX* fx = GXAnimateFX::createWithAnitmateFrameName("antitankBoom", true, false,1,24);
        fx->setScale(0.7);
        fx->setPosition(target->getPosition());
        
        building->map->addChild(fx,9999999);
        target->fxCount++;
    }
    MyBattleMap* battleMap = (MyBattleMap*)building->map;
    CCArray* units = battleMap->getUnits();
    CCObject* obj;
    MyUnit* unit;
    
    CCARRAY_FOREACH(units, obj) {
        unit = dynamic_cast<MyUnit*>(obj);
        
        if (unit->mode != airMode && unit != target && unit->isAlive()&& Mathlib::getDistance(battleMap->transMapToTiled( unit->getPosition()),battleMap->transMapToTiled( target->getPosition())) <splashRange ) {
            if(!unit->setLife(unit->getLife()-damage)) {
                CCPoint buildingPosi = battleMap->transMapToTiled(building->getPosition());
                CCPoint targetPosi = battleMap->transMapToTiled(unit->getPosition());
                unit->dispose();
//                CC_SAFE_RELEASE(target);
            }
        }
    }
    if (!target->isAlive()) {
        CC_SAFE_RELEASE(target);
        target = NULL;
        return;
    }
    if(!target->setLife(target->getLife()-damage)) {
        
        CCPoint buildingPosi = battleMap->transMapToTiled(building->getPosition());
        CCPoint targetPosi = battleMap->transMapToTiled(target->getPosition());
        target->dispose();
        CC_SAFE_RELEASE(target);
        target = NULL;
    }
}

MyUnit* AoeDefendState::rangeTarget() {
    MyBattleMap* battleMap = (MyBattleMap*)building->map;
    CCArray* units = battleMap->getUnits();
    CCObject* object;
    MyUnit* targetUnit;
    //    float minDistance = 9999999;
    CCPoint buildPosi = battleMap->transMapToTiled(building->getPosition());
    CCPoint targetPosi;
    CCARRAY_FOREACH(units, object) {
        targetUnit = dynamic_cast<MyUnit*>(object);
        //        distance = battleMap->transMapToTiled(unit->getPosition())-battleMap->transMapToTiled(building->getPosition());
        targetPosi =  battleMap->transMapToTiled(targetUnit->getPosition());
        if (targetUnit->mode != airMode && targetUnit->isAlive() && Mathlib::getDistance(buildPosi,targetPosi) < attackRange) {
            float angle = Mathlib::getAngle(buildPosi,targetPosi);
            int dir = (((int)(angle*180/3.141592654+22.5)+360)%360)/45 ;
            CCAction* action = CCSequence::create(getFireAnimate(dir),CCCallFunc::create(this,callfunc_selector(DefendState::attackTarget)),NULL);
            this->item->runAction(action);
            return  targetUnit;
        }
    }
    return NULL;
}


//AoeDefendStateCreator* AoeDefendStateCreator::create() {
//    AoeDefendStateCreator* creator = new AoeDefendStateCreator();
//    creator->autorelease();
//    return creator;
//}
//
//CCObject* AoeDefendStateCreator::init() {
//    
//    MyTiledMenuItemSprite* dbItem = MyTiledMenuItemSprite::create(CCSprite::create(CCMenuItemSpriteName), CCSprite::create(CCMenuItemSpriteName));
//    dbItem->setAnchorPoint(itemAnchor);
//    
////    AoeDefendState* defender = AoeDefendState::create(DefendStateTag, dbItem,CCString::create(fireAnimationString),life,attackRange,damage,splashRange);
//    
////    doFill(defender);
//    return NULL;
//}

