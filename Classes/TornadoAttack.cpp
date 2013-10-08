//
//  TornadoAttack.cpp
//  ww4
//
//  Created by xiao tang on 13-9-3.
//
//

#include "TornadoAttack.h"
#include "AttackState.h"
#include "Mathlib.h"
#include "cocos2d.h"
#include "GXAnimateFX.h"
#include "BeAttackState.h"

TornadoAttack* TornadoAttack::create(int _stateId,CCString* _sfxFireName,float _attackRange,float damage,int _sfxId,float _splashRange,float _speed) {
    TornadoAttack* pState = new TornadoAttack();
    pState->stateId = _stateId;
    pState->speed = _speed;
    pState->attackRange = _attackRange;
    pState->damage = damage;
    pState->sfxFireName = _sfxFireName;
    pState->sfxFireName->retain();
    pState->sfxId = _sfxId;
    pState->splashRange = _splashRange;
    pState->attackTargets = CCArray::create();
    pState->attackTargets->retain();
    pState->autorelease();
    return pState;
}

void TornadoAttack::doState() {
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
    }
    if(target != NULL && target->isAlive()) {
        MyBattleMap* battleMap = (MyBattleMap*)unit->getParent();
        CCPoint unitPosi = battleMap->transMapToTiled(unit->getPosition());
        CCPoint targetPosi = battleMap->transMapToTiled(target->getPosition());
        if(Mathlib::getDistance(unitPosi,targetPosi) < attackRange+target->contentSizeByTiled.width/2) {
            CCAnimate* fAction = unit->runFireAnimate(4);
            CCAction* action = CCSequence::create(fAction,CCCallFunc::create(this,callfunc_selector(AttackState::attackTarget)),NULL);
            //这句很关键。等于说是这句拯救了 currentActionTag
            action->setTag(currentActionTag);
            //            CCAction* action = CCSequence::create(fAction,NULL);
            
            unit->runAction(action);
        } else {
            float angle = Mathlib::getAngle(unitPosi, targetPosi);
            //        CCLog("移动角度：%d",((int)(angle*180/3.141592654)+360)%360);
//            int dir = (((int)(angle*180/3.141592654+22.5)+360)%360)/45 ;
            unitPosi = ccp(unitPosi.x+speed*sinf(angle), unitPosi.y+speed*cosf(angle));
            unit->runAction(CCMoveTo::create(unit->aiRate, battleMap->transTiledToMap(unitPosi)));
            
            CCAnimate* fAction = unit->runFireAnimate(4);
            CCAction* action = CCSequence::create(fAction,CCCallFunc::create(this,callfunc_selector(AttackState::attackTarget)),NULL);
            action->setTag(currentActionTag);
            //            CCAction* action = CCSequence::create(fAction,NULL);
            unit->runAction(action);
            
        }
    }
}

//MyBattleBuilding* AttackState::rangeTarget() {
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
//            //            CCAction* action = CCSequence::create(fAction,NULL);
//            unit->runAction(action);
//            return  building;
//        }
//    }
//    return NULL;
//}

void TornadoAttack::attackTarget() {
    
    if(target==NULL || !target->isAlive()) {
        CC_SAFE_RELEASE(target);
        target = NULL;
        return;
    }
    
    
    MyBattleMap* battleMap = (MyBattleMap*)unit->getParent();
    battleMap->playUnitEffect(sfxFireName->getCString(),sfxId);
//    GXAnimateFX* fx = GXAnimateFX::createWithAnitmateFrameName("antitankBoom", true, false);
    
    CCPoint unitPosi = battleMap->transMapToTiled(unit->getPosition());
//    CCPoint targetPosi = battleMap->transMapToTiled(target->getPosition());
//    float angle = Mathlib::getAngle(unitPosi, targetPosi);
//    unitPosi = ccp(unitPosi.x+attackRange*sinf(angle), unitPosi.y+attackRange*cosf(angle));
//    fx->setPosition(battleMap->transTiledToMap(unitPosi));
//    battleMap->CCNode::addChild(fx,999999);
//    BeAttackState* beAttackState = dynamic_cast<BeAttackState*>(target->fsm->getCurrentState());
//    if (beAttackState) {
//        if(beAttackState->beAttack(damage)) {
//            
//        } else{
//            CC_SAFE_RELEASE(target);
//            target = NULL;
//        }
//    }
    CCObject* obj;
    for (int i = (int) (unitPosi.x - splashRange + 0.5); i < unitPosi.x
         + splashRange + 0.5; ++i) {
        for (int j = (int) (unitPosi.y - splashRange + 0.5); j < unitPosi.y
             + splashRange + 0.5; ++j) {
            if (i+1 >= 0 && i+1 < battleMap->getMapSize().width + 2 && j+1 >= 0
                && j+1 < battleMap->getMapSize().height + 2) {
                if (battleMap->mybuildingMap[i + 1][j + 1] != NULL && ((MyBattleBuilding*)battleMap->mybuildingMap[i + 1][j + 1])->isAlive()) {
                    CCARRAY_FOREACH(attackTargets,obj) {
                        if (battleMap->mybuildingMap[i + 1][j + 1] == obj) {
                            goto endTurn;
                        }
                    }
                    attackTargets->addObject((MyBattleBuilding*)battleMap->mybuildingMap[i + 1][j + 1]);
                }
            endTurn:continue;
            }
        }
    }
    int k=0;
//    bool isDonext =false;
    int dieCount = 0;
    CCARRAY_FOREACH(attackTargets,obj) {
        MyBattleBuilding* build = (MyBattleBuilding*)obj;
        BeAttackState* beAttackState = dynamic_cast<BeAttackState*>(build->fsm->getCurrentState());
        if (beAttackState) {
            if(!beAttackState->beAttack(damage)) {
                if (build == target) {
                    CC_SAFE_RELEASE_NULL(target);
                }
                dieCount++;
//                CC_SAFE_RELEASE_NULL(target);
            }
        }
        k++;
    }
    if (dieCount == attackTargets->count()) {
        unit->changeState(toMoveTransition);
    }
    attackTargets->removeAllObjects();
//    if (isDonext) {
//        doNext();
//    }
}

MyBattleBuilding* TornadoAttack::rangeTarget() {
    MyBattleMap* battleMap = (MyBattleMap*)unit->getParent();
    MyBattleBuilding* building;
    //    float minDistance = 9999999;
    CCPoint unitPosi = battleMap->transMapToTiled(unit->getPosition());
    CCPoint targetPosi;
    int i =0;
    int unitPosiInt = 0;
    while (i < 60) {
        for (int k = unitPosi.x-i; k<unitPosi.x+i; k++) {
            unitPosiInt = unitPosi.y;
            if (unitPosiInt - i +1 >= 0 && unitPosiInt - i +1 < battleMap->getMapSize().height + 2 ) {
                if (k+1 >= 0 && k+1 < battleMap->getMapSize().width + 2 ) {
                    building = ((MyBattleBuilding*)battleMap->mybuildingMap[k + 1][unitPosiInt - i + 1]);
                    if (building && building->isAlive() && building->getTag() != wallTag ) {
                        return building;
                    }
                }
            }
        }
        for (int k = unitPosi.y-i; k<unitPosi.y+i; k++) {
            unitPosiInt = unitPosi.x;
            if (unitPosiInt + i +1 >= 0 && unitPosiInt + i +1 < battleMap->getMapSize().width + 2 ) {
                if (k+1 >= 0 && k+1 < battleMap->getMapSize().height + 2  ) {
                    building = ((MyBattleBuilding*)battleMap->mybuildingMap[unitPosiInt + i + 1][k+1]);
                    if (building && building->isAlive() && building->getTag() != wallTag ) {
                        return building;
                    }
                }
            }
        }
        for (int k = unitPosi.x+i; k>unitPosi.x-i; k--) {
            unitPosiInt = unitPosi.y;
            if (unitPosiInt + i +1 >= 0 && unitPosiInt + i +1 < battleMap->getMapSize().height + 2 ) {
                if (k+1 >= 0 && k+1 < battleMap->getMapSize().height + 2 ) {
                    building = ((MyBattleBuilding*)battleMap->mybuildingMap[k + 1][unitPosiInt+i+1]);
                    if (building && building->isAlive() && building->getTag() != wallTag ) {
                         return building;
                    }
                }
            }
        }
        for (int k = unitPosi.y+i; k>unitPosi.y-i; k--) {
            unitPosiInt = unitPosi.x;
            if (unitPosiInt - i +1 >= 0 && unitPosiInt - i +1 < battleMap->getMapSize().width + 2 ) {
                if (k+1 >= 0 && k+1 < battleMap->getMapSize().height + 2 ) {
                    building = ((MyBattleBuilding*)battleMap->mybuildingMap[unitPosiInt- i + 1][k + 1]);
                    if (building && building->isAlive() && building->getTag() != wallTag ) {
                        return building;
                    }
                }
            }
        }
        i++;
    }
    return NULL;
    
    
    
//    MyBattleMap* battleMap = (MyBattleMap*)unit->getParent();
//    CCArray* items = battleMap->getItems();
//    CCObject* object;
//    MyBattleBuilding* building;
//    //    float minDistance = 9999999;
//    CCPoint unitPosi = battleMap->transMapToTiled(unit->getPosition());
//    CCPoint targetPosi;
//    MyBattleBuilding* tempTarget = NULL;
//    float minDistance = 9999999;
    
//    CCARRAY_FOREACH(items, object) {
//        building = dynamic_cast<MyBattleBuilding*>(object);
//        //        distance = battleMap->transMapToTiled(unit->getPosition())-battleMap->transMapToTiled(building->getPosition());
////        targetPosi =  battleMap->transMapToTiled(building->getPosition());
////        
////        if (building->getTag() != wallTag && building->isAlive()) {
////            return  building;
////        }
//        if (building->getTag() == wallTag) {
//            continue;
//        }
//        float distance = Mathlib::getDistance(battleMap->transMapToTiled(unit->getPosition()), battleMap->transMapToTiled(building->getPosition()));
//        if (distance< minDistance) {
//            tempTarget = building;
//            minDistance = distance;
//        }
//    }
//    return tempTarget;
//    MyBattleMap* battleMap = (MyBattleMap*)unit->getParent();
//    return (MyBattleBuilding*)battleMap->getChildByTag(zhihuisuoTag);
}

//MyBattleBuilding* TornadoAttack::doNext() {
//    MyBattleBuilding* tempbuilding = rangeTarget();
//    if (tempbuilding == NULL) {
//        unit->changeState(toMoveTransition);
//        CC_SAFE_RELEASE(target);
//        target = NULL;
//    } else {
//        setTarget(tempbuilding);
//    }
//}
