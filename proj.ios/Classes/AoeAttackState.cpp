//
//  AoeAttackState.cpp
//  ww4
//
//  Created by xiao tang on 13-7-11.
//
//

#include "AoeAttackState.h"
#include "Mathlib.h"
#include "cocos2d.h"
#include "GXAnimateFX.h"
#include "BeAttackState.h"

AoeAttackState* AoeAttackState::create(int _stateId,CCString* _sfxFireName, float _attackRange,float damage,int _sfxId,float _splashRange){
    AoeAttackState* pState = new AoeAttackState();
    pState->stateId = _stateId;
    //    pState->speed = _speed;
    pState->attackRange = _attackRange;
    pState->damage = damage;
    pState->sfxFireName = _sfxFireName;
    pState->sfxFireName->retain();
    pState->sfxId = _sfxId;
    pState->splashRange = _splashRange;
    pState->autorelease();
    return pState;
}

void AoeAttackState::attackTarget() {
    
    if(target==NULL || !target->isAlive()) {
        CC_SAFE_RELEASE(target);
        target = NULL;
        return;
    }
    
    MyBattleMap* battleMap = (MyBattleMap*)unit->getParent();
    battleMap->playUnitEffect(sfxFireName->getCString(),sfxId);
    GXAnimateFX* fx = GXAnimateFX::createWithAnitmateFrameName("antitankBoom", true, false,1,24);
    fx->setScale(0.8);
    CCPoint unitPosi = battleMap->transMapToTiled(unit->getPosition());
    CCPoint targetPosi = battleMap->transMapToTiled(target->getPosition());
    float angle = Mathlib::getAngle(unitPosi, targetPosi);
    unitPosi = ccp(unitPosi.x+attackRange*sinf(angle), unitPosi.y+attackRange*cosf(angle));
    fx->setPosition(battleMap->transTiledToMap(unitPosi));
    battleMap->CCNode::addChild(fx,999999);
    BeAttackState* beAttackState = dynamic_cast<BeAttackState*>(target->fsm->getCurrentState());
//    bool isDonext = false;
    if (beAttackState) {
        if(beAttackState->beAttack(damage)) {
            
        } else{
            CC_SAFE_RELEASE(target);
            target = NULL;
//            isDonext = true;
        }
    }
    for (int i =0; i<10; i++) {
        attackTargets[i] = NULL;
    }
    
    for (int i = (int) (targetPosi.x - splashRange + 0.5); i < targetPosi.x
         + splashRange + 0.5; ++i) {
        for (int j = (int) (targetPosi.y - splashRange + 0.5); j < targetPosi.y
             + splashRange + 0.5; ++j) {
            if (i+1 >= 0 && i+1 < battleMap->getMapSize().width + 2 && j+1 >= 0
                && j+1 < battleMap->getMapSize().height + 2) {
                if (battleMap->mybuildingMap[i + 1][j + 1] != NULL && battleMap->mybuildingMap[i + 1][j + 1]!= target && ((MyBattleBuilding*)battleMap->mybuildingMap[i + 1][j + 1])->isAlive()) {
                    int k=0;
                    while (attackTargets[k] != NULL) {
                        if (battleMap->mybuildingMap[i + 1][j + 1] == attackTargets[k]) {
                            goto endTurn;
                        }
                        k++;
                    }
                    attackTargets[k] =(MyBattleBuilding*)battleMap->mybuildingMap[i + 1][j + 1];
                }
            endTurn:continue;
            }
        }
    }
    int k=0;
    while (attackTargets[k] != NULL && k<10) {
        BeAttackState* beAttackState = dynamic_cast<BeAttackState*>(attackTargets[k]->fsm->getCurrentState());
        if (beAttackState) {
            beAttackState->beAttack(damage);
        }
        k++;
    }
//    if (isDonext) {
//        doNext();
//    }
}

