//
//  GXFSMclass.cpp
//  ww2
//
//  Created by DingYu Fu on 12-9-1.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "GXFSMclass.h"

GXFSM::GXFSM(GXFSMstate* c_state) {
    this->currentState = c_state;
    this->stateMap = CCDictionary::create();
    stateMap->retain();
    this->addState(c_state);
}

GXFSM::~GXFSM() {
//    this->stateMap->
//    this->stateMap->release();
    CC_SAFE_RELEASE_NULL(this->stateMap);
}

GXFSM* GXFSM::create(GXFSMstate* c_state) {
    GXFSM* fsm = new GXFSM(c_state);
    
    
    fsm->autorelease();
    return fsm;
}

void GXFSM::setCurrentState(GXFSMstate* _c_state) {
    this->currentState = _c_state;
}

GXFSMstate* GXFSM::getState(int stateId) {
    return (GXFSMstate*)(stateMap->objectForKey(stateId));
}

void GXFSM::addState(GXFSMstate *pState) {
    stateMap->setObject(pState, pState->getId());
//    pState->retain();
}

void GXFSM::deleteState(int iStateId) {
    stateMap->removeObjectForKey(iStateId);
}

CCInteger* GXFSM::stateTransition(int input) {
    return currentState->getOutPut(input);
}

//void GXFSM::release() {
////    CCLog("release fsm:%d",this->m_uReference);
//    CCObject::release();
//}
//
//void GXFSM::retain() {
////    CCLog("restain fsm:%d",this->m_uReference);
//     CCObject::retain();
//}

CCArray* GXFSM::getAllState() {
    return  NULL;
}
