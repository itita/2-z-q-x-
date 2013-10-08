//
//  BattleOverMessage.cpp
//  ww4
//
//  Created by xiao tang on 13-6-8.
//
//

#include "BattleOverMessage.h"
#include "MyMessageManage.h"

BattleOverMessage* BattleOverMessage::create(bool _isVictory) {
    BattleOverMessage* msg = new BattleOverMessage();
    msg->autorelease();
    msg->isVictory = _isVictory;
    return msg;
}

void BattleOverMessage::sendMsg() {
    MyMessageManage::getInstance()->msgList->addObject(this);
}