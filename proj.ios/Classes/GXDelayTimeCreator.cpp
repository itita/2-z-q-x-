//
//  GXDelayTimeCreator.cpp
//  Dialog2
//
//  Created by xiao tang on 13-8-23.
//
//

#include "GXDelayTimeCreator.h"


GXDelayTimeCreator* GXDelayTimeCreator::create() {
    GXDelayTimeCreator*  creator = new GXDelayTimeCreator();
    creator->autorelease();
    return creator;
}

CCAction* GXDelayTimeCreator::getAction() {
    return CCDelayTime::create(duration);
}