//
//  GarbageCollectionState.cpp
//  ww4
//
//  Created by xiao tang on 13-5-24.
//
//

#include "GarbageCollectionState.h"

GarbageCollectionState* GarbageCollectionState::create(int _stateId,CCSprite* sprite,int _resourceCount) {
    GarbageCollectionState* pState = new GarbageCollectionState();
    pState->stateId = _stateId;
    pState->autorelease();
    pState->item = sprite;
    pState->item->retain();
    pState->resourceCount = _resourceCount;
    return pState;
}

void GarbageCollectionState::addResource(int _resourceCount) {
    this->resourceCount += _resourceCount;
}

float GarbageCollectionState::getArg0() {
    return resourceCount;
}
