//
//  Newbie1Message.h
//  ww3
//
//  Created by xiao tang on 12-12-14.
//
//

#ifndef ww3_Newbie1Message_h
#define ww3_Newbie1Message_h

#include "MyBaseMessage.h"

class Newbie1Message : public MyBaseMessage{
    
public:
    Newbie1Message(){
        tag = newbie1MessageTag;
    }
    virtual void sendMsg();
    Newbie1Message* create();
};

#endif
