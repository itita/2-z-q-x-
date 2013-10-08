//
//  Newbie1to2Message.h
//  ww3
//
//  Created by xiao tang on 12-12-15.
//
//

#ifndef ww3_Newbie1to2Message_h
#define ww3_Newbie1to2Message_h

#include "MyBaseMessage.h"

class Newbie1to2Message : public MyBaseMessage{
    
public:
    Newbie1to2Message(){
        tag = newbie1to2MessageTag ;
    }
    void sendMsg();
    static Newbie1to2Message* create();
};


#endif
