//
//  MoveToAttack.cpp
//  ww2
//
//  Created by DingYu Fu on 12-9-7.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#include "MoveToAttack.h"
#include "Mathlib.h"
#include "BattleScene.h"
#include "MyGameFactory.h"

MoveToAttack::~MoveToAttack() {
    CC_SAFE_RELEASE_NULL(target);
//    CC_SAFE_RELEASE_NULL(unit);
//    CCLog("MoveToAttack released");
}

MoveToAttack* MoveToAttack::create(int _stateId,float _speed,float _attackRange) {
    MoveToAttack* pState = new MoveToAttack();
    pState->stateId = _stateId;
    pState->speed = _speed;
    pState->attackRange = _attackRange;
    pState->autorelease();
    pState->target = NULL;
    pState->unit=NULL;
    return pState;
}

void MoveToAttack::doState() {
    if(target == NULL || !target->isAlive()) {
        setTarget(searchTarget());
        if(target == NULL ) {
//            BattleScene* scene = ((BattleScene*)unit->getParent()->getParent());
//            if(scene->getFighting() == fightingTag) {
//                scene->setFighting(afterFightTag);
//                scene->scheduleOnce(schedule_selector(BattleScene::victory),0);
//            }
            return;
        }
    }  
    if(!enemyInRange()) {
        moveToTarget();
    }
}

bool MoveToAttack::enemyInRange() {
    
    
    MyBattleMap* battleMap = (MyBattleMap*)unit->getParent();
    MyBattleBuilding* building;
    //    float minDistance = 9999999;
    CCPoint unitPosi = battleMap->transMapToTiled(unit->getPosition());
    CCPoint targetPosi;
    int i=0;
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
                            unit->changeState(toAttackTransition);
                            return true;
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
                            unit->changeState(toAttackTransition);
                            return true;
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
                            unit->changeState(toAttackTransition);
                            return true;
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
                            unit->changeState(toAttackTransition);
                            return true;
                        }
                    }
                }
            }
        }
        i++;
    }
    
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
//                        unit->changeState(toAttackTransition);
//                        return true;
//                    }
//                }
//            }
//        }
//    }
    return false;
    
//    MyBattleMap* battleMap = (MyBattleMap*)unit->getParent();
//    CCArray* items = battleMap->getItems();
//    CCObject* object;
//    MyBattleBuilding* building;
////    float minDistance = 9999999;
//    CCPoint unitPosi = battleMap->transMapToTiled(unit->getPosition());
//    CCPoint targetPosi;
//    CCARRAY_FOREACH(items, object) {
//        building = dynamic_cast<MyBattleBuilding*>(object);
//        //        distance = battleMap->transMapToTiled(unit->getPosition())-battleMap->transMapToTiled(building->getPosition());
//        targetPosi =  battleMap->transMapToTiled(building->getPosition());
////        Mathlib::getDistance(unitPosi,targetPosi) < attackRange+building->contentSizeByTiled.width/2
//        if (Mathlib::collisionCheck(building->contentSizeByTiled,targetPosi,attackRange,unitPosi)) {
//            unit->changeState(toAttackTransition);
////            int dir = (((int)(angle*180/3.141592654+22.5)+360)%360)/45 ;
////            unit->fsm->getState(this->getOutPut(toAttackTransition)->getValue())->doState();
//            return  true;
//        }
//    }
//    return false;
}

void MoveToAttack::init(MyUnit *_unit) {
//    setUnit(_unit);
    //这里不适合循环持有
    this->unit = _unit;
}

MyBattleBuilding* MoveToAttack::searchTarget() {
   
    MyBattleMap* battleMap = (MyBattleMap*)unit->getParent();
    MyBattleBuilding* building;
    CCPoint unitPosi = battleMap->transMapToTiled(unit->getPosition());
    
    if (battleMap->getItems()->count() > 400) {
        int i=1;
        int unitPosiInt = 0;
//        int processCount = 0;
//        int itemCount = battleMap->getItems()->count();
        //    CCLog("itemCount:%d",battleMap->getItems()->count());
        while (i<60) {
            for (int k = unitPosi.x-i; k<unitPosi.x+i; k++) {
                unitPosiInt = unitPosi.y;
//                processCount++;
                if (unitPosiInt - i +1 >= 0 && unitPosiInt - i +1 < battleMap->getMapSize().height + 2 ) {
                    if (k+1 >= 0 && k+1 < battleMap->getMapSize().width + 2 ) {
                        building = ((MyBattleBuilding*)battleMap->mybuildingMap[k + 1][unitPosiInt - i + 1]);
                        if (building && building->isAlive() && building->getTag() != wallTag) {
                            //                        CCLog("processCount:%d",processCount);
//                            if (processCount > battleMap->getItems()->count()) {
//                                CCLog("processCount:%d,itemCount:%d",processCount,itemCount);
//                            }
                            return building;
                        }
                    }
                }
            }
            for (int k = unitPosi.y-i; k<unitPosi.y+i; k++) {
                unitPosiInt = unitPosi.x;
//                processCount++;
                if (unitPosiInt + i +1 >= 0 && unitPosiInt + i +1 < battleMap->getMapSize().width + 2 ) {
                    if (k+1 >= 0 && k+1 < battleMap->getMapSize().height + 2  ) {
                        building = ((MyBattleBuilding*)battleMap->mybuildingMap[unitPosiInt + i + 1][k+1]);
                        if (building && building->isAlive() && building->getTag() != wallTag) {
                            //                        CCLog("processCount:%d",processCount);
//                            if (processCount > battleMap->getItems()->count()) {
//                                CCLog("processCount:%d,itemCount:%d",processCount,itemCount);
//                            }
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
                        if (building && building->isAlive() && building->getTag() != wallTag) {
                            //                        CCLog("processCount:%d",processCount);
//                            if (processCount > battleMap->getItems()->count()) {
//                                CCLog("processCount:%d,itemCount:%d",processCount,itemCount);
//                            }
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
                        if (building && building->isAlive() && building->getTag() != wallTag) {
                            //                        CCLog("processCount:%d",processCount);
//                            if (processCount > battleMap->getItems()->count()) {
//                                CCLog("processCount:%d,itemCount:%d",processCount,itemCount);
//                            }
                            return building;
                        }
                    }
                }
            }
            i++;
        }
    } else {
//        MyBattleMap* battleMap = (MyBattleMap*)unit->getParent();
        CCArray* items = battleMap->getItems();
        CCObject* object;
        MyBattleBuilding* building;
        float minDistance = 9999999;
        MyBattleBuilding* tempTarget = NULL;
        CCARRAY_FOREACH(items, object) {
            
            building = dynamic_cast<MyBattleBuilding*>(object);
            //        distance = battleMap->transMapToTiled(unit->getPosition())-battleMap->transMapToTiled(building->getPosition());
            if(building->getTag() == wallTag) {
                continue;
            }
            if (building->isAlive()) {
                float distance = Mathlib::getDistance(battleMap->transMapToTiled(unit->getPosition()), battleMap->transMapToTiled(building->getPosition()));
                if (distance< minDistance) {
                    tempTarget = building;
                    minDistance = distance;
                }
            }
        }
        return tempTarget;
    }
    
    return NULL;
    
}

void MoveToAttack::moveToTarget() {
    MyBattleMap* battleMap = (MyBattleMap*)unit->getParent();
    CCPoint unitPosi = battleMap->transMapToTiled(unit->getPosition());
    CCPoint targetPosi =  battleMap->transMapToTiled(target->getPosition());
    if (Mathlib::getDistance(unitPosi, targetPosi)<speed) {
//        CCLog("到达S");
//        target->release();
        CC_SAFE_RELEASE(target);
        target = NULL;
    } else {
        float angle = Mathlib::getAngle(unitPosi, targetPosi);
//        CCLog("移动角度：%d",((int)(angle*180/3.141592654)+360)%360);
        int dir = (((int)(angle*180/3.141592654+22.5)+360)%360)/45 ;
        unit->runMoveAnimate(dir);
        unitPosi = ccp(unitPosi.x+speed*sinf(angle), unitPosi.y+speed*cosf(angle));
        unit->runAction(CCMoveTo::create(unit->aiRate, battleMap->transTiledToMap(unitPosi)));

    }
}

void MoveToAttack::setTarget(MyBattleBuilding *_target) {
//    this->target->release();
    CC_SAFE_RELEASE_NULL(this->target);
    if (_target != NULL) {
        _target->retain();
    }
    this->target = _target;
}

//void MoveToAttack::setUnit(MyUnit *_unit) {
////    CC_SAFE_RELEASE_NULL(unit);
////    CC_SAFE_RETAIN(_unit);
//    this->unit = _unit;
//}

void MoveToAttack::doEnd() {
    CC_SAFE_RELEASE(target);
    target = NULL;
}
