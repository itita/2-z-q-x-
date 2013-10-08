//
//  Newbie1Message.cpp
//  ww3
//
//  Created by xiao tang on 12-12-14.
//
//

#include "Newbie1Message.h"
#include "MyMessageManage.h"


Newbie1Message* Newbie1Message::create(){
    Newbie1Message* message = Newbie1Message::create();
    message->autorelease();
    return message;
}

void Newbie1Message::sendMsg(){
    MyMessageManage::getInstance()->msgList->addObject(this);
}


