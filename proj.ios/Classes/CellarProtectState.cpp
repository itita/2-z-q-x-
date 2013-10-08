//
//  CellarProtectState.cpp
//  ww4
//
//  Created by xiao tang on 13-7-8.
//
//

#include "CellarProtectState.h"
#include "MyBattleMap.h"

CellarProtectState* CellarProtectState::create(int _stateId,CCSprite* item,float _protectCount) {
    CellarProtectState* pState = new CellarProtectState();
    pState->stateId = _stateId;
    pState->protectCount = _protectCount;
    pState->autorelease();
    pState->item = item;
    pState->item->retain();
    return pState;
}

float CellarProtectState::getArg0() {
    return protectCount;
}

void CellarProtectState::doStart() {
    ((MyBattleMap*)building->map)->getItems()->removeObject(building);
    this->building->AliveInterface::dispose();
}