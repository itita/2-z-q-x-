//
//  RemoveWaitLayerMessage.cpp
//  ww4
//
//  Created by xiao tang on 13-7-23.
//
//

#include "RemoveWaitLayerMessage.h"
#include "MyMessageManage.h"

RemoveWaitLayerMessage* RemoveWaitLayerMessage::create() {
    RemoveWaitLayerMessage* msg = new RemoveWaitLayerMessage();
    msg->autorelease();
    return msg;
}

void RemoveWaitLayerMessage::sendMsg() {
    MyMessageManage::getInstance()->msgList->addObject(this);
}