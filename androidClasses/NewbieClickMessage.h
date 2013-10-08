//
//  NewbieClickMessage.h
//  ww3
//
//  Created by xiao tang on 12-12-19.
//
//

#ifndef __ww3__NewbieClickMessage__
#define __ww3__NewbieClickMessage__
#include "MyBaseMessage.h"

class NewbieClickMessage : public MyBaseMessage{
    
public:
    NewbieClickMessage() {
        tag = newbieClickMessageTag;
    }
    void sendMsg();
    static NewbieClickMessage* create();
};


#endif /* defined(__ww3__NewbieClickMessage__) */
