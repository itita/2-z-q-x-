//
//  NewbieClickMessage.cpp
//  ww3
//
//  Created by xiao tang on 12-12-19.
//
//

#include "NewbieClickMessage.h"
#include "MyMessageManage.h"

NewbieClickMessage* NewbieClickMessage::create(){
    NewbieClickMessage* message = new NewbieClickMessage();
    message->autorelease();
    return message;
}

void NewbieClickMessage::sendMsg(){
    MyMessageManage::getInstance()->msgList->addObject(this);
}