//
//  RuinState.cpp
//  ww3
//
//  Created by xiao tang on 12-10-28.
//
//

#include "RuinState.h"

RuinState* RuinState::create(int _stateId, CCSprite *item) {
    
    RuinState* pState = new RuinState();
    pState->stateId = _stateId;
    pState->autorelease();
    pState->item = item;
//    item->setTarget(pState, menu_selector(NormalState::CallBack));
    pState->item->retain();
    //    bdItem->setAnchorPoint(ccp(0.5,0.45));
    
    return pState;
}

void RuinState::setCurrentId(int id) {
   currentId=id;
}

//RuinStateCreator* RuinStateCreator::create() {
//    RuinStateCreator* ruinState = new RuinStateCreator();
//    ruinState->autorelease();
//    return ruinState;
//}
//
//CCObject* RuinStateCreator::init() {
////    MyTiledMenuItemSprite* ruinItem = MyTiledMenuItemSprite::create(CCSprite::create(CCMenuItemSpriteName), CCSprite::create(CCMenuItemSpriteName));
//    
////    RuinState* ruinstate = RuinState::create(RuinsStateTag, ruinItem);
////    ruinItem->setEnabled(false);
////    ruinItem->setScale(beAttackState->item->getContentSize().width/ruinstate->item->getContentSize().width);
//    return NULL;
//}
