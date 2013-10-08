//
//  GXFSMstate.cpp
//  ww2
//
//  Created by DingYu Fu on 12-9-1.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "GXFSMstate.h"
#include "cocos2d.h"

using namespace cocos2d;



GXFSMstate::~GXFSMstate() {
    CC_SAFE_RELEASE_NULL(input_output);
}

GXFSMstate* GXFSMstate::create(int _stateId) {
    GXFSMstate* pState = new GXFSMstate();
    pState->stateId = _stateId;
    pState->input_output = cocos2d::CCDictionary::create();
    pState->input_output->retain();
    pState->autorelease();
    return pState;
}

void GXFSMstate::addTransition(int inputId, int ioutputId) {
    input_output->setObject(ccint(ioutputId),inputId);
}

void GXFSMstate::deleteTransition(int inputId) {
    input_output->removeObjectForKey(inputId);
}

CCInteger* GXFSMstate::getOutPut(int inputId) {
   return  dynamic_cast<CCInteger*>(input_output->objectForKey(inputId));
}

//void GXFSMstate::release(){
////    CCLog("release fsmState:%d",this->m_uReference);
//    CCObject::release();
//}

void GXFSMstate::doState() {
    CCLog("base doState");
}

//void GXFSMstate::retain() {
////    CCLog("retain fsmState:%d",this->m_uReference);
//    CCObject::retain();
//}

CCArray* GXFSMstate::getAllInput() {
    return input_output->allKeys();
}

void GXFSMstate::doStart() {

}

void GXFSMstate::doEnd() {

}
