//
//  ThirdLoginCallBackMessage.cpp
//  ww4
//
//  Created by xiao tang on 13-9-28.
//
//

#include "ThirdLoginCallBackMessage.h"
#include "MyMessageManage.h"

ThirdLoginCallBackMessage* ThirdLoginCallBackMessage::create(int _userId) {
    ThirdLoginCallBackMessage* msg = new ThirdLoginCallBackMessage();
    msg->userId = _userId;
    return msg;
}

void ThirdLoginCallBackMessage::sendMsg() {
    int ret = pthread_mutex_lock(&MyMessageManage::msgMutex);
    CCAssert(ret == 0, "lock error ,error code ");
    MyMessageManage::getInstance()->msgList->addObject(this);
    pthread_mutex_unlock(&MyMessageManage::msgMutex);
    this->release();
}