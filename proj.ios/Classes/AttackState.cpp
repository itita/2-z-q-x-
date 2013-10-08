//
//  AttackState.cpp
//  ww2
//
//  Created by DingYu Fu on 12-9-8.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "AttackState.h"
#include "Mathlib.h"
#include "cocos2d.h"
#include "GXAnimateFX.h"
#include "BeAttackState.h"

AttackState::~AttackState() {
    CC_SAFE_RELEASE_NULL(target);
    CC_SAFE_RELEASE_NULL(sfxFireName);
//    CCLog("attackstate released");
//    sfxFireName = NULL;
    //已经在UNIT中释放的样子因为传的是指针
//    CC_SAFE_DELETE(sfxFireName);
}

AttackState* AttackState::create(int _stateId,CCString* _sfxFireName, float _attackRange,float damage,int _sfxId){
    AttackState* pState = new AttackState();
    pState->stateId = _stateId;
//    pState->speed = _speed;
    pState->attackRange = _attackRange;
    pState->damage = damage;
    pState->sfxFireName = _sfxFireName;
    pState->sfxFireName->retain();
    pState->sfxId = _sfxId;
    pState->autorelease();
    return pState;
}

void AttackState::init(MyUnit *_unit) {
    this->unit = _unit;
}

void AttackState::doState() {
    if(target == NULL || !target->isAlive()) {
        if (target != NULL ) {
            CC_SAFE_RELEASE(target);
            target = NULL;
        }
        MyBattleBuilding* tempbuilding = rangeTarget();
        if (tempbuilding == NULL) {
            unit->changeState(toMoveTransition);
            CC_SAFE_RELEASE(target);
            target = NULL;
        } else {
            setTarget(tempbuilding);
        }
    } else {
        MyBattleMap* battleMap = (MyBattleMap*)unit->getParent();
        CCPoint unitPosi = battleMap->transMapToTiled(unit->getPosition());
        CCPoint targetPosi = battleMap->transMapToTiled(target->getPosition());
        if(Mathlib::getDistance(unitPosi,targetPosi) < attackRange+target->contentSizeByTiled.width/2) {
            float angle = Mathlib::getAngle(unitPosi, targetPosi);
            int dir = (((int)(angle*180/3.141592654+22.5)+360)%360)/45; 
            CCAnimate* fAction = unit->runFireAnimate(dir);
            CCAction* action = CCSequence::create(fAction,CCCallFunc::create(this,callfunc_selector(AttackState::attackTarget)),NULL);
            action->setTag(currentActionTag);
//            CCAction* action = CCSequence::create(fAction,NULL);
            unit->runAction(action);
        } else {
            CC_SAFE_RELEASE(target);
            target = NULL;
        }
    }
}

MyBattleBuilding* AttackState::rangeTarget() {
    
    MyBattleMap* battleMap = (MyBattleMap*)unit->getParent();
    MyBattleBuilding* building;
    //    float minDistance = 9999999;
    CCPoint unitPosi = battleMap->transMapToTiled(unit->getPosition());
    CCPoint targetPosi;
    int i =0;
    int unitPosiInt = 0;
    while (i < attackRange + 1) {
        for (int k = unitPosi.x-i; k<unitPosi.x+i; k++) {
            unitPosiInt = unitPosi.y;
            if (unitPosiInt - i +1 >= 0 && unitPosiInt - i +1 < battleMap->getMapSize().height + 2 ) {
                if (k+1 >= 0 && k+1 < battleMap->getMapSize().width + 2 ) {
                    building = ((MyBattleBuilding*)battleMap->mybuildingMap[k + 1][unitPosiInt - i + 1]);
                    if (building && building->isAlive()) {
                        targetPosi =  battleMap->transMapToTiled(building->getPosition());
                        if (Mathlib::collisionCheck(building->contentSizeByTiled,targetPosi,attackRange,unitPosi)) {
                            float angle = Mathlib::getAngle(unitPosi, targetPosi);
                            int dir = (((int)(angle*180/3.141592654+22.5)+360)%360)/45 ;
                            CCAnimate* fAction = unit->runFireAnimate(dir);
                            CCAction* action = CCSequence::create(fAction,CCCallFunc::create(this,callfunc_selector(AttackState::attackTarget)),NULL);
                            action->setTag(currentActionTag);
                            unit->runAction(action);
                            return  building;
                        }
                    }
                }
            }
        }
        for (int k = unitPosi.y-i; k<unitPosi.y+i; k++) {
            unitPosiInt = unitPosi.x;
            if (unitPosiInt + i +1 >= 0 && unitPosiInt + i +1 < battleMap->getMapSize().width + 2 ) {
                if (k+1 >= 0 && k+1 < battleMap->getMapSize().height + 2  ) {
                    building = ((MyBattleBuilding*)battleMap->mybuildingMap[unitPosiInt + i + 1][k+1]);
                    if (building && building->isAlive()) {
                        targetPosi =  battleMap->transMapToTiled(building->getPosition());
                        if (Mathlib::collisionCheck(building->contentSizeByTiled,targetPosi,attackRange,unitPosi)) {
                            float angle = Mathlib::getAngle(unitPosi, targetPosi);
                            int dir = (((int)(angle*180/3.141592654+22.5)+360)%360)/45 ;
                            CCAnimate* fAction = unit->runFireAnimate(dir);
                            CCAction* action = CCSequence::create(fAction,CCCallFunc::create(this,callfunc_selector(AttackState::attackTarget)),NULL);
                            action->setTag(currentActionTag);
                            unit->runAction(action);
                            return  building;
                        }
                    }
                }
            }
        }
        for (int k = unitPosi.x+i; k>unitPosi.x-i; k--) {
            unitPosiInt = unitPosi.y;
            if (unitPosiInt + i +1 >= 0 && unitPosiInt + i +1 < battleMap->getMapSize().height + 2 ) {
                if (k+1 >= 0 && k+1 < battleMap->getMapSize().height + 2 ) {
                    building = ((MyBattleBuilding*)battleMap->mybuildingMap[k + 1][unitPosiInt+i+1]);
                    if (building && building->isAlive()) {
                        targetPosi =  battleMap->transMapToTiled(building->getPosition());
                        if (Mathlib::collisionCheck(building->contentSizeByTiled,targetPosi,attackRange,unitPosi)) {
                            float angle = Mathlib::getAngle(unitPosi, targetPosi);
                            int dir = (((int)(angle*180/3.141592654+22.5)+360)%360)/45 ;
                            CCAnimate* fAction = unit->runFireAnimate(dir);
                            CCAction* action = CCSequence::create(fAction,CCCallFunc::create(this,callfunc_selector(AttackState::attackTarget)),NULL);
                            action->setTag(currentActionTag);
                            unit->runAction(action);
                            return  building;
                        }
                    }
                }
            }
        }
        for (int k = unitPosi.y+i; k>unitPosi.y-i; k--) {
            unitPosiInt = unitPosi.x;
            if (unitPosiInt - i +1 >= 0 && unitPosiInt - i +1 < battleMap->getMapSize().width + 2 ) {
                if (k+1 >= 0 && k+1 < battleMap->getMapSize().height + 2 ) {
                    building = ((MyBattleBuilding*)battleMap->mybuildingMap[unitPosiInt- i + 1][k + 1]);
                    if (building && building->isAlive()) {
                        targetPosi =  battleMap->transMapToTiled(building->getPosition());
                        if (Mathlib::collisionCheck(building->contentSizeByTiled,targetPosi,attackRange,unitPosi)) {
                            float angle = Mathlib::getAngle(unitPosi, targetPosi);
                            int dir = (((int)(angle*180/3.141592654+22.5)+360)%360)/45 ;
                            CCAnimate* fAction = unit->runFireAnimate(dir);
                            CCAction* action = CCSequence::create(fAction,CCCallFunc::create(this,callfunc_selector(AttackState::attackTarget)),NULL);
                            action->setTag(currentActionTag);
                            unit->runAction(action);
                            return  building;
                        }
                    }
                }
            }
        }
        i++;
    }
    return NULL;
    
    
//    for (int i = (int) (unitPosi.x - attackRange - 0.5); i < unitPosi.x
//         + attackRange + 0.5; ++i) {
//        for (int j = (int) (unitPosi.y - attackRange - 0.5); j < unitPosi.y
//             + attackRange + 0.5; ++j) {
//            if (i+1 >= 0 && i+1 < battleMap->getMapSize().width + 2 && j+1 >= 0
//                && j+1 < battleMap->getMapSize().height + 2) {
//                building = ((MyBattleBuilding*)battleMap->mybuildingMap[i + 1][j + 1]);
//
//                if (building !=NULL && building->isAlive()) {
//                    targetPosi =  battleMap->transMapToTiled(building->getPosition());
//                    if (Mathlib::collisionCheck(building->contentSizeByTiled,targetPosi,attackRange,unitPosi)) {
//                        float angle = Mathlib::getAngle(unitPosi, targetPosi);
//                        int dir = (((int)(angle*180/3.141592654+22.5)+360)%360)/45 ;
//                        CCAnimate* fAction = unit->runFireAnimate(dir);
//                        CCAction* action = CCSequence::create(fAction,CCCallFunc::create(this,callfunc_selector(AttackState::attackTarget)),NULL);
//                        action->setTag(currentActionTag);
//                        //            CCAction* action = CCSequence::create(fAction,NULL);
//                        unit->runAction(action);
//                        return  building;
//                    }
//                }
//            }
//        }
//    }
//    return NULL;
//    MyBattleMap* battleMap = (MyBattleMap*)unit->getParent();
//    CCArray* items = battleMap->getItems();
//    CCObject* object;
//    MyBattleBuilding* building;
//    //    float minDistance = 9999999;
//    CCPoint unitPosi = battleMap->transMapToTiled(unit->getPosition());
//    CCPoint targetPosi;
//    CCARRAY_FOREACH(items, object) {
//        building = dynamic_cast<MyBattleBuilding*>(object);
//        //        distance = battleMap->transMapToTiled(unit->getPosition())-battleMap->transMapToTiled(building->getPosition());
//        targetPosi =  battleMap->transMapToTiled(building->getPosition());
//        
//        if (building->isAlive() && Mathlib::collisionCheck(building->contentSizeByTiled,targetPosi,attackRange,unitPosi)) {
//            float angle = Mathlib::getAngle(unitPosi, targetPosi);
//            int dir = (((int)(angle*180/3.141592654+22.5)+360)%360)/45 ;
//            CCAnimate* fAction = unit->runFireAnimate(dir);
//            CCAction* action = CCSequence::create(fAction,CCCallFunc::create(this,callfunc_selector(AttackState::attackTarget)),NULL);
//            action->setTag(currentActionTag);
////            CCAction* action = CCSequence::create(fAction,NULL);
//            unit->runAction(action);
//            return  building;
//        }
//    }
//    return NULL;
}
void AttackState::attackTarget() {
    if(target == NULL || !target->isAlive()) {
        CC_SAFE_RELEASE(target);
        target = NULL;
        return;
    }
    MyBattleMap* battleMap = (MyBattleMap*)unit->getParent();
    battleMap->playUnitEffect(sfxFireName->getCString(),sfxId);
    GXAnimateFX* fx = GXAnimateFX::createWithAnitmateFrameName("microboom1", true, false);

    CCPoint unitPosi = battleMap->transMapToTiled(unit->getPosition());
    CCPoint targetPosi = battleMap->transMapToTiled(target->getPosition());
    float angle = Mathlib::getAngle(unitPosi, targetPosi);
    unitPosi = ccp(unitPosi.x+attackRange*sinf(angle), unitPosi.y+attackRange*cosf(angle));
    fx->setPosition(battleMap->transTiledToMap(unitPosi));
    battleMap->CCNode::addChild(fx,999999);
    BeAttackState* beAttackState = dynamic_cast<BeAttackState*>(target->fsm->getCurrentState());
    if (beAttackState) {
        if(beAttackState->beAttack(damage)) {
            
        } else{
            CC_SAFE_RELEASE(target);
            target = NULL;
//            doNext();
        }
    }
}

void AttackState::setTarget(MyBattleBuilding *_target) {
    CC_SAFE_RELEASE_NULL(this->target);
    CC_SAFE_RETAIN(_target);
//    this->target->release();
//    if (_target != NULL) {
//        _target->retain();
//    }
    this->target = _target;
}

void AttackState::doEnd() {
    CC_SAFE_RELEASE(target);
    target = NULL;
}

void AttackState::doStart() {
    doState();
}

//void AttackState::doNext() {

    
    
    
    
//    if (tempbuilding == NULL) {
//        unit->changeState(toMoveTransition);
//        CC_SAFE_RELEASE(target);
//        target = NULL;
//    } else {
//        setTarget(tempbuilding);
//    }
//}