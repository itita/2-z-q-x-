//
//  UpdateArmyMessage.cpp
//  ww4
//
//  Created by xiao tang on 13-5-9.
//
//

#include "UpdateArmyMessage.h"
#include "MyMessageManage.h"

UpdateArmyMessage* UpdateArmyMessage::create(int _armyId,int _preLevel,int _nextLevel) {
    UpdateArmyMessage* msg = new UpdateArmyMessage();
    msg->armyId = _armyId;
    msg->preLevel = _preLevel;
    msg->nextLevel = _nextLevel;
    msg->autorelease();
    return msg;
}

void UpdateArmyMessage::sendMsg() {
    MyMessageManage::getInstance()->msgList->addObject(this);
}