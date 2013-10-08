//
//  RobotMoveToAttack.cpp
//  ww4
//
//  Created by xiao tang on 13-9-3.
//
//

#include "RobotMoveToAttack.h"
#include "Mathlib.h"
#include "BattleScene.h"
#include "MyGameFactory.h"

RobotMoveToAttack* RobotMoveToAttack::create(int _stateId,float _speed,float _animateRate,float _attackRange) {
    RobotMoveToAttack* pState = new RobotMoveToAttack();
    pState->stateId = _stateId;
    pState->animateRate = _animateRate;
    pState->speed = _speed;
    pState->attackRange = _attackRange;
    pState->autorelease();
    pState->target = NULL;
    pState->unit=NULL;
    return pState;
}

void RobotMoveToAttack::moveToTarget() {
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
        float attackRate = unit->aiRate;
        int beishu = attackRate/animateRate;
        float x = speed*(animateRate/attackRate)*sinf(angle);
        float y = speed*(animateRate/attackRate)*cosf(angle);
        CCArray* array = CCArray::create();
        for (int i=0; i<beishu; i++) {
            array->addObject(CCEaseIn::create(CCMoveTo::create(animateRate,battleMap->transTiledToMap(ccp(unitPosi.x+(i+1)*x,unitPosi.y+(i+1)*y))),3.5));
        }
        unit->runAction(CCSequence::create(array));
    }
}

//bool RobotMoveToAttack::enemyInRange() {
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
//        if (Mathlib::collisionCheck(building->contentSizeByTiled,targetPosi,attackRange,unitPosi)) {
//            unit->changeState(toAttackTransition);
//            //            int dir = (((int)(angle*180/3.141592654+22.5)+360)%360)/45 ;
//            //            unit->fsm->getState(this->getOutPut(toAttackTransition)->getValue())->doState();
//            return  true;
//        }
//    }
//    return false;
//}
