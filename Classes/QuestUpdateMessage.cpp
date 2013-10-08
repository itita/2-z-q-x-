//
//  QuestUpdateMessage.cpp
//  ww4
//
//  Created by xiao tang on 13-6-8.
//
//

#include "QuestUpdateMessage.h"
#include "MyMessageManage.h"

QuestUpdateMessage* QuestUpdateMessage::create(MyBaseQuest* _quest) {
    QuestUpdateMessage* msg = new QuestUpdateMessage();
    msg->autorelease();
    msg->quest = _quest;
    return msg;
}

void QuestUpdateMessage::sendMsg() {
    MyMessageManage::getInstance()->msgList->addObject(this);
}