//
//  MyUnitState.cpp
//  ww2
//
//  Created by DingYu Fu on 12-9-5.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "MyUnitState.h"

//MyUnitState::~MyUnitState() {
////    map->release();
//    CCL
//}

MyUnitState::MyUnitState(){
    input_output = cocos2d::CCDictionary::create();
    input_output->retain();
}


MyUnitState* MyUnitState::create(int _stateId) {
    MyUnitState* pState = new MyUnitState();
    pState->stateId = _stateId;
    pState->autorelease();
    return pState;
}

void MyUnitState::doState() {
//    CCLog("unit");
}


void MyUnitState::init(MyUnit *unit) {
    
}
