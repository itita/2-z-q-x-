//
//  TornadoMoveToAttack.cpp
//  ww4
//
//  Created by xiao tang on 13-9-4.
//
//

#include "TornadoMoveToAttack.h"

TornadoMoveToAttack* TornadoMoveToAttack::create(int _stateId,float _speed,float _animateRate,float _attackRange) {
    TornadoMoveToAttack* pState = new TornadoMoveToAttack();
    pState->stateId = _stateId;
    pState->animateRate = _animateRate;
    pState->speed = _speed;
    pState->attackRange = _attackRange;
    pState->autorelease();
    pState->target = NULL;
    pState->unit=NULL;
    return pState;
}

MyBattleBuilding* TornadoMoveToAttack::searchTarget() {
    MyBattleMap* battleMap = (MyBattleMap*)unit->getParent();
    return (MyBattleBuilding*)battleMap->getChildByTag(zhihuisuoTag);
}