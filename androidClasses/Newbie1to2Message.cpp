//
//  Newbie1to2Message.cpp
//  ww3
//
//  Created by xiao tang on 12-12-15.
//
//

#include "Newbie1to2Message.h"
#include "MyMessageManage.h"


Newbie1to2Message* Newbie1to2Message::create(){
    Newbie1to2Message* message = new Newbie1to2Message();
    message->autorelease();
    return message;
}

void Newbie1to2Message::sendMsg(){
    MyMessageManage::getInstance()->msgList->addObject(this);
}

