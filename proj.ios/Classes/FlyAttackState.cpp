//
//  FlyAttackState.cpp
//  ww4
//
//  Created by xiao tang on 13-5-11.
//
//

#include "FlyAttackState.h"
#include "AttackState.h"
#include "Mathlib.h"
#include "cocos2d.h"
#include "GXAnimateFX.h"
#include "BeAttackState.h"
#include "SimpleAudioEngine.h"

FlyAttackState::~FlyAttackState() {
//    CCLog("attackstate released");
    //    sfxFireName = NULL;
    //已经在UNIT中释放的样子因为传的是指针
    //    CC_SAFE_DELETE(sfxFireName);
}

FlyAttackState* FlyAttackState::create(int _stateId,CCString* _sfxFireName, float _attackRange,float _damage,int _sfxId){
    FlyAttackState* pState = new FlyAttackState();
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


MyBattleBuilding* FlyAttackState::rangeTarget() {
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
                
                if (building !=NULL && building->isAlive() && building->getTag() != wallTag && building->getTag() != combineWall5X1Tag && building->getTag() != combineWall1X5Tag) {
                    targetPosi =  battleMap->transMapToTiled(building->getPosition());
                    if (Mathlib::collisionCheck(building->contentSizeByTiled,targetPosi,attackRange,unitPosi)) {
                        float angle = Mathlib::getAngle(unitPosi, targetPosi);
                        int dir = (((int)(angle*180/3.141592654+22.5)+360)%360)/45 ;
                        CCAnimate* fAction = unit->runFireAnimate(dir);
                        CCAction* action = CCSequence::create(fAction,CCCallFunc::create(this,callfunc_selector(AttackState::attackTarget)),NULL);
                        action->setTag(currentActionTag);
                        //            CCAction* action = CCSequence::create(fAction,NULL);
                        unit->runAction(action);
                        return  building;
                    }
                }
            }
        }
    }
    return NULL;
    
    
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

