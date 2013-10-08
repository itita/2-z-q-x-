//
//  DefendState.cpp
//  ww2
//
//  Created by DingYu Fu on 12-9-9.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "DefendState.h"
#include "MyBattleMap.h"
#include "Mathlib.h"
#include "GXUtil.h"
#include "GXAnimateFX.h"
#include "DefineSet.h"

DefendState::DefendState():
    target(NULL),
    name(NULL),
    damage(0),
    attackRange(0),
    sfxId(1),
    animateCreator(NULL){
        for(int i=0;i<8;i++) {
            animate[i] = NULL;
        }
//    target = NULL;
//    name = NULL;
//    damage = 0;
//    attackRange = 0;
////    animateRate = 0;
}

DefendState::~DefendState() {
    for(int i=0;i<8;i++) {
        CC_SAFE_RELEASE_NULL(animate[i]);
    }
//    CC_SAFE_DELETE(fireAnimation);
    CC_SAFE_RELEASE_NULL(name);
    CC_SAFE_RELEASE_NULL(target);
//    CC_SAFE_DELETE_ARRAY(sfxFireName);
}

DefendState* DefendState::create(int _stateId, CCSprite* item,CCString* name,float life,float attackRange,float damage,float _attackRate,int _sfxId) {
    DefendState* pState = new DefendState();
    pState->stateId = _stateId;
    pState->autorelease();
    pState->life = life;
    pState->maxLife = life;
    pState->attackRange = attackRange;
    pState->damage = damage;
    pState->name = name;
    CC_SAFE_RETAIN(name);
    //  CCSprite* grayBd = CCSprite::create(string);
    //    grayBd->setColor(ccGRAY);
    pState->item = item;
    pState->item->retain();
    pState->doStateTime = _attackRate;
    sprintf(pState->sfx, "sfx_%sf.wav",name->getCString());
    pState->sfxId = _sfxId;
//    pState->animateRate = _animateRate;
    return pState;
}

void DefendState::init(MyBattleBuilding *building) {
    MyBattleState::init(building);
//    char str[64] = {0};
//    sprintf(str, "%sfld", name->getCString());
//    fireAnimation[0] = GXUtil::initAction(str,animateRate);
//    sprintf(str, "%sfd", name->getCString());
//    fireAnimation[1] = GXUtil::initAction(str,animateRate);
//    sprintf(str, "%sfrd", name->getCString());
//    fireAnimation[2] = GXUtil::initAction(str,animateRate);
//    sprintf(str, "%sfr", name->getCString());
//    fireAnimation[3] = GXUtil::initAction(str,animateRate);
//    sprintf(str, "%sfru", name->getCString());
//    fireAnimation[4] = GXUtil::initAction(str,animateRate);
//    sprintf(str, "%sfu", name->getCString());
//    fireAnimation[5] = GXUtil::initAction(str,animateRate);
//    sprintf(str, "%sflu", name->getCString());
//    fireAnimation[6] = GXUtil::initAction(str,animateRate);
//    sprintf(str, "%sfl", name->getCString());
//    fireAnimation[7] = GXUtil::initAction(str,animateRate);
//
    building->costRange = CCSizeMake(building->contentSizeByTiled.width+attackRange, building->contentSizeByTiled.height+attackRange);
    this->building = building;
//    xuetiao=MyXueTiao::create("xuetiao.png");
//  
//    xuetiao->setScaleX((item->getContentSize().width)/xuetiao->getContentSize().width);
//    xuetiao->setScaleY(0.3);
//    xuetiao->setPosition(ccp(0,item->getContentSize().height+10));
//    xuetiao->updatePercentage(0);
//    item->addChild(xuetiao,20);
}

void DefendState::doState() {
    if(building->isAlive()) {
        if (target != NULL && target->isAlive()) {
            MyBattleMap* battleMap = (MyBattleMap*)building->map;
            CCPoint buildingPosi = battleMap->transMapToTiled(building->getPosition());
            CCPoint targetPosi = battleMap->transMapToTiled(target->getPosition());
            if(Mathlib::getDistance(buildingPosi,targetPosi) < attackRange) {
                float angle = Mathlib::getAngle(buildingPosi, targetPosi);
                int dir = (((int)(angle*180/3.141592654+22.5)+360)%360)/45 ;
                CCAction* action = CCSequence::create(getFireAnimate(dir),CCCallFunc::create(this,callfunc_selector(DefendState::attackTarget)),NULL);
                this->item->runAction(action);
            } else {
                CC_SAFE_RELEASE(target);
                target = NULL;
            }
        } else {
            setTarget(rangeTarget());
        }
    } else {
      
    }
//
}

MyUnit* DefendState::rangeTarget() {
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
        if (targetUnit->isAlive() && Mathlib::getDistance(buildPosi,targetPosi) < attackRange) {
            float angle = Mathlib::getAngle(buildPosi,targetPosi);
            int dir = (((int)(angle*180/3.141592654+22.5)+360)%360)/45 ;
            CCAction* action = CCSequence::create(getFireAnimate(dir),CCCallFunc::create(this,callfunc_selector(DefendState::attackTarget)),NULL);
            this->item->runAction(action);
            return  targetUnit;
        }
    }
    return NULL;
}

//CCAnimate* DefendState::getFireAnimate(int dir) {
//    if (animate[dir] == NULL) {
//        animate[dir] = (*animateCreator)(dir);
//        animate[dir]->retain();
//    }
//    return animate[dir];
//}

void DefendState::attackTarget(){
    if(!target->isAlive()) {
        setTarget(NULL);
        return;
    }
//    CCLog("干死你丫的");
    ((MyBattleMap*)building->map)->playUnitEffect(sfx,sfxId);
//    CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(sfx);
    if (target->fxCount/10 < 1) {

        GXAnimateFX* fx = GXAnimateFX::createWithAnitmateFrameName("microboom1", true, false);
        fx->setPosition(target->getPosition());
        building->map->addChild(fx,99999999);
        target->fxCount += 10;
    }
    
    if(!target->setLife(target->getLife()-damage)) {
//        MyBattleMap* battleMap = (MyBattleMap*)building->map;
//        CCPoint buildingPosi = battleMap->transMapToTiled(building->getPosition());
//        CCPoint targetPosi = battleMap->transMapToTiled(target->getPosition());
        target->dispose();
        CC_SAFE_RELEASE(target);
        target = NULL;
    }
}

void DefendState::setTarget(MyUnit *_target) {
    CC_SAFE_RELEASE(this->target);
    //    this->target->release();
    if (_target != NULL &&  _target->isAlive()) {
        _target->retain();
    } 
    if (_target != NULL && _target ->isAlive()) {
        this->target = _target;
    } else {
        this->target = NULL;
    }
}

void DefendState::doEnd() {
    CC_SAFE_RELEASE(target);
    target = NULL;
    item->stopAllActions();
}

void DefendState::setAnimateCreator(SEL_FXCreator _animateCreator) {
    CCAssert(_animateCreator!=NULL, "defend animate not null");
    animateCreator = _animateCreator;
}


//DefendStateCreator::DefendStateCreator() {
//    damage= 0;
//    attackRange = 0;
//}
//
//DefendStateCreator* DefendStateCreator::create() {
//    DefendStateCreator* creator = new DefendStateCreator();
//    creator->autorelease();
//    return creator;
//}
//
//CCObject* DefendStateCreator::createObj() {
//    
//    MyTiledMenuItemSprite* dbItem = MyTiledMenuItemSprite::create(CCSprite::create(CCMenuItemSpriteName), CCSprite::create(CCMenuItemSpriteName));
//    dbItem->setAnchorPoint(itemAnchor);
//    
////    DefendState* defender = DefendState::create(DefendStateTag, dbItem,CCString::create(fireAnimationString),life,attackRange,damage);
//
////    doFill(defender);
//    return NULL;
//}
