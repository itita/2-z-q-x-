//
//  BattleRuinState.cpp
//  ww3
//
//  Created by xiao tang on 12-12-3.
//
//

#include "BattleRuinState.h"
#include "Mathlib.h"

BattleRuinState* BattleRuinState::create(int _stateId, const std::string& _spriteName) {
    
    BattleRuinState* pState = new BattleRuinState();
    pState->stateId = _stateId;
    pState->autorelease();
    pState->spriteName = _spriteName;
    //    bdItem->setAnchorPoint(ccp(0.5,0.45));
    
    return pState;
}

void BattleRuinState::doStart() {
    currentId= building->fsm->getCurrentState()->getId();
    if (currentId ==0 || currentId > 100) {
        CCAssert(currentId!=0, "statechangeError");
    }
}


CCSprite* BattleRuinState::getItem() {
    char str[100] = {0};
    CCSprite* ruinItem =NULL;
    int maxBian = (int)Mathlib::max(building->contentSizeByTiled.width,building->contentSizeByTiled.height);
    int minBian = (int)Mathlib::min(building->contentSizeByTiled.width,building->contentSizeByTiled.height);
    if(maxBian <= 1) {
        return CCSprite::create();
    } else {
#if game_version == soft_version
        sprintf(str, "ruins (%d).png",(int)Mathlib::bound(minBian-1,4,2));
#endif
#if game_version == hard_version
        sprintf(str, "ruins (%d).png",(int)Mathlib::bound(minBian,4,2));
#endif
        ruinItem = CCSprite::createWithSpriteFrameName(str);
    }
    return ruinItem;
}