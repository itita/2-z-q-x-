//
//  ToFightMessage.cpp
//  ww3
//
//  Created by xiao tang on 12-12-19.
//
//

#include "ToFightMessage.h"
#include "MyMessageManage.h"

ToFightMessage* ToFightMessage::create() {
    ToFightMessage* msg = new ToFightMessage();
    msg->autorelease();
    return msg;
}

void ToFightMessage::sendMsg() {
    MyMessageManage::getInstance()->msgList->addObject(this);
}