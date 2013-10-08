//
//  GXMessage.cpp
//  ww4
//
//  Created by xiao tang on 13-3-19.
//
//

#include "GXMessage.h"
#include "MyMessageManage.h"

GXMessage* GXMessage::create() {
    GXMessage* msg = new GXMessage();
    return msg;
}

void GXMessage::sendMsg() {
    int ret = pthread_mutex_lock(&MyMessageManage::msgMutex);
    CCAssert(ret == 0, "lock error ,error code ");
    MyMessageManage::getInstance()->msgList->addObject(this);
    pthread_mutex_unlock(&MyMessageManage::msgMutex);
    this->release();
}