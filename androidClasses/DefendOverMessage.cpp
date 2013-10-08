//
//  DefendOverMessage.cpp
//  ww4
//
//  Created by xiao tang on 13-6-18.
//
//

#include "DefendOverMessage.h"
#include "MyMessageManage.h"

DefendOverMessage* DefendOverMessage::create(bool _isVictory) {
    DefendOverMessage* msg = new DefendOverMessage();
    msg->autorelease();
    msg->isVictory = _isVictory;
    return msg;
}

void DefendOverMessage::sendMsg() {
    MyMessageManage::getInstance()->msgList->addObject(this);
}