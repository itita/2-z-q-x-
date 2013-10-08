//
//  NoResourceToDeployMessage.cpp
//  ww3
//
//  Created by xiao tang on 12-12-19.
//
//

#include "NoResourceToDeployMessage.h"
#include "MyMessageManage.h"

NoResourceToDeployMessage* NoResourceToDeployMessage::create(UnitBean* creator) {
    NoResourceToDeployMessage* msg = new NoResourceToDeployMessage();
    msg->creator = creator;
//    creator->retain();
    msg->autorelease();
    return msg;
}

void NoResourceToDeployMessage::sendMsg() {
    MyMessageManage::getInstance()->msgList->addObject(this);
}