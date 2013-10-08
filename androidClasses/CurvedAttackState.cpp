//
//  CurvedAttackState.cpp
//  ww4
//
//  Created by xiao tang on 13-9-12.
//
//

#include "CurvedAttackState.h"
#include "Mathlib.h"
#include "GXAnimateFX.h"
#include "BeAttackState.h"
#include "SimpleAudioEngine.h"

CurvedAttackState::~CurvedAttackState() {
    CCLog("attackstate released");
    //    sfxFireName = NULL;
    //已经在UNIT中释放的样子因为传的是指针
    //    CC_SAFE_DELETE(sfxFireName);
}

CurvedAttackState* CurvedAttackState::create(int _stateId,CCString* _sfxFireName, float _attackRange,float _damage,int _sfxId){
    CurvedAttackState* pState = new CurvedAttackState();
    pState->stateId = _stateId;
    //    pState->speed = _speed;
    pState->attackRange = _attackRange;
    pState->damage = _damage;
    pState->sfxFireName = _sfxFireName;
    pState->sfxFireName->retain();
    pState->sfxId = _sfxId;
    pState->autorelease();
    return pState;
}


MyBattleBuilding* CurvedAttackState::rangeTarget() {
    
    MyBattleMap* battleMap = (MyBattleMap*)unit->getParent();
    MyBattleBuilding* building;
    //    float minDistance = 9999999;
    CCPoint unitPosi = battleMap->transMapToTiled(unit->getPosition());
    CCPoint targetPosi;
    int i =0;
    int unitPosiInt = 0;
    MyBattleBuilding* tempTarget = NULL;
    while (i < attackRange + 1) {
        for (int k = unitPosi.x-i; k<unitPosi.x+i; k++) {
            unitPosiInt = unitPosi.y;
            if (unitPosiInt - i +1 >= 0 && unitPosiInt - i +1 < battleMap->getMapSize().height + 2 ) {
                if (k+1 >= 0 && k+1 < battleMap->getMapSize().width + 2 ) {
                    building = ((MyBattleBuilding*)battleMap->mybuildingMap[k + 1][unitPosiInt - i + 1]);
                    if (building && building->isAlive()) {
                        targetPosi =  battleMap->transMapToTiled(building->getPosition());
                        if (Mathlib::collisionCheck(building->contentSizeByTiled,targetPosi,attackRange,unitPosi)) {
                            if (building->getTag() != wallTag && building->getTag() != combineWall5X1Tag && building->getTag() != combineWall1X5Tag) {
                                float angle = Mathlib::getAngle(unitPosi, targetPosi);
                                int dir = (((int)(angle*180/3.141592654+22.5)+360)%360)/45 ;
                                CCAnimate* fAction = unit->runFireAnimate(dir);
                                CCAction* action = CCSequence::create(fAction,CCCallFunc::create(this,callfunc_selector(AttackState::attackTarget)),NULL);
                                action->setTag(currentActionTag);
                                unit->runAction(action);
                                return  building;
                            } else {
                                if (tempTarget == NULL) {
                                    tempTarget = building;
                                }
                            }
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
                            if (building->getTag() != wallTag && building->getTag() != combineWall5X1Tag && building->getTag() != combineWall1X5Tag) {
                                float angle = Mathlib::getAngle(unitPosi, targetPosi);
                                int dir = (((int)(angle*180/3.141592654+22.5)+360)%360)/45 ;
                                CCAnimate* fAction = unit->runFireAnimate(dir);
                                CCAction* action = CCSequence::create(fAction,CCCallFunc::create(this,callfunc_selector(AttackState::attackTarget)),NULL);
                                action->setTag(currentActionTag);
                                unit->runAction(action);
                                return  building;
                            } else {
                                if (tempTarget == NULL) {
                                    tempTarget = building;
                                }
                            }
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
                            if (building->getTag() != wallTag && building->getTag() != combineWall5X1Tag && building->getTag() != combineWall1X5Tag) {
                                float angle = Mathlib::getAngle(unitPosi, targetPosi);
                                int dir = (((int)(angle*180/3.141592654+22.5)+360)%360)/45 ;
                                CCAnimate* fAction = unit->runFireAnimate(dir);
                                CCAction* action = CCSequence::create(fAction,CCCallFunc::create(this,callfunc_selector(AttackState::attackTarget)),NULL);
                                action->setTag(currentActionTag);
                                unit->runAction(action);
                                return  building;
                            } else {
                                if (tempTarget == NULL) {
                                    tempTarget = building;
                                }
                            }
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
                            if (building->getTag() != wallTag && building->getTag() != combineWall5X1Tag && building->getTag() != combineWall1X5Tag) {
                                float angle = Mathlib::getAngle(unitPosi, targetPosi);
                                int dir = (((int)(angle*180/3.141592654+22.5)+360)%360)/45 ;
                                CCAnimate* fAction = unit->runFireAnimate(dir);
                                CCAction* action = CCSequence::create(fAction,CCCallFunc::create(this,callfunc_selector(AttackState::attackTarget)),NULL);
                                action->setTag(currentActionTag);
                                unit->runAction(action);
                                return  building;
                            } else {
                                if (tempTarget == NULL) {
                                    tempTarget = building;
                                }
                            }
                        }
                    }
                }
            }
        }
        i++;
    }
    
    if (tempTarget != NULL) {
        targetPosi =  battleMap->transMapToTiled(tempTarget->getPosition());
        float angle = Mathlib::getAngle(unitPosi, targetPosi);
        int dir = (((int)(angle*180/3.141592654+22.5)+360)%360)/45 ;
        CCAnimate* fAction = unit->runFireAnimate(dir);
        CCAction* action = CCSequence::create(fAction,CCCallFunc::create(this,callfunc_selector(AttackState::attackTarget)),NULL);
        action->setTag(currentActionTag);
        //            CCAction* action = CCSequence::create(fAction,NULL);
        unit->runAction(action);
        return  tempTarget;
    }

    return NULL;
    
    
//    MyBattleMap* battleMap = (MyBattleMap*)unit->getParent();
//    MyBattleBuilding* building;
//    //    float minDistance = 9999999;
//    CCPoint unitPosi = battleMap->transMapToTiled(unit->getPosition());
//    CCPoint targetPosi;
//    MyBattleBuilding* tempTarget = NULL;
//    for (int i = (int) (unitPosi.x - attackRange - 0.5); i < unitPosi.x
//         + attackRange + 0.5; ++i) {
//        for (int j = (int) (unitPosi.y - attackRange - 0.5); j < unitPosi.y
//             + attackRange + 0.5; ++j) {
//            if (i+1 >= 0 && i+1 < battleMap->getMapSize().width + 2 && j+1 >= 0
//                && j+1 < battleMap->getMapSize().height + 2) {
//                building = ((MyBattleBuilding*)battleMap->mybuildingMap[i + 1][j + 1]);
//                
//                if (building !=NULL && building->isAlive()) {
//                    if (building->getTag() != wallTag && building->getTag() != combineWall5X1Tag && building->getTag() != combineWall1X5Tag) {
//                        targetPosi =  battleMap->transMapToTiled(building->getPosition());
//                        if (Mathlib::collisionCheck(building->contentSizeByTiled,targetPosi,attackRange,unitPosi)) {
//                            float angle = Mathlib::getAngle(unitPosi, targetPosi);
//                            int dir = (((int)(angle*180/3.141592654+22.5)+360)%360)/45 ;
//                            CCAnimate* fAction = unit->runFireAnimate(dir);
//                            CCAction* action = CCSequence::create(fAction,CCCallFunc::create(this,callfunc_selector(AttackState::attackTarget)),NULL);
//                            action->setTag(currentActionTag);
//                            //            CCAction* action = CCSequence::create(fAction,NULL);
//                            unit->runAction(action);
//                            return  building;
//                        }
//                    } else {
//                        if (tempTarget != NULL) {
//                            tempTarget = building;
//                        }
//                    }
//                    
//                    
//                }
//            }
//        }
//    }
//    if (tempTarget != NULL) {
//        targetPosi =  battleMap->transMapToTiled(tempTarget->getPosition());
//        if (Mathlib::collisionCheck(tempTarget->contentSizeByTiled,targetPosi,attackRange,unitPosi)) {
//            float angle = Mathlib::getAngle(unitPosi, targetPosi);
//            int dir = (((int)(angle*180/3.141592654+22.5)+360)%360)/45 ;
//            CCAnimate* fAction = unit->runFireAnimate(dir);
//            CCAction* action = CCSequence::create(fAction,CCCallFunc::create(this,callfunc_selector(AttackState::attackTarget)),NULL);
//            action->setTag(currentActionTag);
//            //            CCAction* action = CCSequence::create(fAction,NULL);
//            unit->runAction(action);
//            return  tempTarget;
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
    //        if (building->getTag() != wallTag && building->getTag() != combineWall5X1Tag && building->getTag() != combineWall1X5Tag && building->isAlive() && Mathlib::collisionCheck(building->contentSizeByTiled,targetPosi,attackRange,unitPosi)) {
    //            float angle = Mathlib::getAngle(unitPosi, targetPosi);
    //            int dir = (((int)(angle*180/3.141592654+22.5)+360)%360)/45 ;
    //            CCAnimate* fAction = unit->runFireAnimate(dir);
    //            CCAction* action = CCSequence::create(fAction,CCCallFunc::create(this,callfunc_selector(AttackState::attackTarget)),NULL);
    //            action->setTag(currentActionTag);
    //            //            CCAction* action = CCSequence::create(fAction,NULL);
    //            unit->runAction(action);
    //            return  building;
    //        }
    //    }
    //    return NULL;
}