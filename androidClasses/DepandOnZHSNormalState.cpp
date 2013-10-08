//
//  DepandOnZHSNormalState.cpp
//  ww4
//
//  Created by xiao tang on 13-5-1.
//
//

#include "DepandOnZHSNormalState.h"

DepandOnZHSNormalState* DepandOnZHSNormalState::create(int _stateId,CCString* _spriteFileName) {
    DepandOnZHSNormalState* pState = new DepandOnZHSNormalState();
    pState->stateId = _stateId;
    pState->autorelease();
    pState->spriteFileName = _spriteFileName;
    CC_SAFE_RETAIN(_spriteFileName);
    
    return pState;
}


CCSprite* DepandOnZHSNormalState::getItem() {
//    if (item == NULL) {
//        if (building->getParent()->getChildByTag(zhihuisuotag) != NULL) {
//            
//        }
//    } else {
//        return item;
//    }
    return item;
}