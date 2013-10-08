//
//  UpLevelMessage.cpp
//  ww4
//
//  Created by xiao tang on 13-6-3.
//
//

#include "UpLevelMessage.h"
#include "MyMessageManage.h"

UpLevelMessage* UpLevelMessage::create(int _level) {
    UpLevelMessage* msg = new UpLevelMessage();
    msg->autorelease();
    msg->level = _level;
    return msg;
}

void UpLevelMessage::sendMsg() {
    MyMessageManage::getInstance()->msgList->addObject(this);
}