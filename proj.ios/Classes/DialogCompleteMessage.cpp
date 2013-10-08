//
//  DialogCompleteMessage.cpp
//  ww4
//
//  Created by xiao tang on 13-8-24.
//
//

#include "DialogCompleteMessage.h"
#include "MyMessageManage.h"

DialogCompleteMessage* DialogCompleteMessage::create(int _maxNode,int _currentNode,int _dialogTag) {
    DialogCompleteMessage* msg = new DialogCompleteMessage();
    msg->maxNode = _maxNode;
    msg->currentNode = _currentNode;
    msg->dialogTag = _dialogTag;
    msg->autorelease();
    return msg;
}

void DialogCompleteMessage::sendMsg() {
    MyMessageManage::getInstance()->msgList->addObject(this);
}