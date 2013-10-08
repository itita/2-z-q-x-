//
//  ToFightMessage.h
//  ww3
//
//  Created by xiao tang on 12-12-19.
//
//

#ifndef __ww3__ToFightMessage__
#define __ww3__ToFightMessage__

#include "MyBaseMessage.h"

using namespace cocos2d;

class ToFightMessage : public MyBaseMessage {

public:
    ToFightMessage() {
        tag = toFightMessageTag;
    }
    ~ToFightMessage(){
        CCLog("tofigtMessge has been release");
    }
    static ToFightMessage* create();
    virtual void sendMsg();
};

#endif /* defined(__ww3__ToFightMessage__) */
