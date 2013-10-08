//
//  FlyMoveToAttack.cpp
//  ww4
//
//  Created by xiao tang on 13-5-11.
//
//

#include "FlyMoveToAttack.h"
#include "Mathlib.h"
#include "BattleScene.h"
#include "MyGameFactory.h"
#include "DefineSet.h"

FlyMoveToAttack::~FlyMoveToAttack() {
  
//    CCLog("FlyMoveToAttack released");
}

FlyMoveToAttack* FlyMoveToAttack::create(int _stateId,float _speed,float _attackRange) {
    FlyMoveToAttack* pState = new FlyMoveToAttack();
    pState->stateId = _stateId;
    pState->speed = _speed;
    pState->attackRange = _attackRange;
    pState->autorelease();
    pState->target = NULL;
    pState->unit=NULL;
    return pState;
}


bool FlyMoveToAttack::enemyInRange() {
    MyBattleMap* battleMap = (MyBattleMap*)unit->getParent();
    MyBattleBuilding* building;
    //    float minDistance = 9999999;
    CCPoint unitPosi = battleMap->transMapToTiled(unit->getPosition());
    CCPoint targetPosi;
    
    for (int i = (int) (unitPosi.x - attackRange - 0.5); i < unitPosi.x
         + attackRange + 0.5; ++i) {
        for (int j = (int) (unitPosi.y - attackRange - 0.5); j < unitPosi.y
             + attackRange + 0.5; ++j) {
            if (i+1 >= 0 && i+1 < battleMap->getMapSize().width + 2 && j+1 >= 0
                && j+1 < battleMap->getMapSize().height + 2) {
                building = ((MyBattleBuilding*)battleMap->mybuildingMap[i + 1][j + 1]);
                
                if (building !=NULL && building->isAlive() && building->getTag() != wallTag && building->getTag() != combineWall1X5Tag && building->getTag() != combineWall5X1Tag) {
                    targetPosi =  battleMap->transMapToTiled(building->getPosition());
                    if (Mathlib::collisionCheck(building->contentSizeByTiled,targetPosi,attackRange,unitPosi)) {
                        unit->changeState(toAttackTransition);
                        return true;
                    }
                }
            }
        }
    }
    return false;
    
    
    
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
//        //        Mathlib::getDistance(unitPosi,targetPosi) < attackRange+building->contentSizeByTiled.width/2
//        if (building->getTag() != wallTag && building->getTag() != combineWall1X5Tag && building->getTag() != combineWall5X1Tag && Mathlib::collisionCheck(building->contentSizeByTiled,targetPosi,attackRange,unitPosi)) {
//            unit->changeState(toAttackTransition);
//            //            int dir = (((int)(angle*180/3.141592654+22.5)+360)%360)/45 ;
//            //            unit->fsm->getState(this->getOutPut(toAttackTransition)->getValue())->doState();
//            return  true;
//        }
//    }
//    return false;
}

MyBattleBuilding* FlyMoveToAttack::searchTarget() {
    MyBattleMap* battleMap = (MyBattleMap*)unit->getParent();
    CCArray* items = battleMap->getItems();
    CCObject* object;
    MyBattleBuilding* building;
    float minDistance = 9999999;
    MyBattleBuilding* tempTarget = NULL;
    CCARRAY_FOREACH(items, object) {
        
        building = dynamic_cast<MyBattleBuilding*>(object);
        //        distance = battleMap->transMapToTiled(unit->getPosition())-battleMap->transMapToTiled(building->getPosition());
        if(building->getTag() == wallTag || building->getTag() == combineWall5X1Tag || building->getTag() == combineWall1X5Tag) {
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
