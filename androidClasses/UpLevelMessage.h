//
//  UpLevelMessage.h
//  ww4
//
//  Created by xiao tang on 13-6-3.
//
//

#ifndef __ww4__UpLevelMessage__
#define __ww4__UpLevelMessage__

#include <iostream>
#include "MyBaseMessage.h"

class UpLevelMessage : public MyBaseMessage {
    
public:
    UpLevelMessage() {
        tag = UpLevelMessageTag;
    }
    ~UpLevelMessage(){
        
    }
    static UpLevelMessage* create(int level);
    virtual void sendMsg();
    int level;
};


#endif /* defined(__ww4__UpLevelMessage__) */
