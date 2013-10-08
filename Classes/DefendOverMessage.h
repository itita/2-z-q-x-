//
//  DefendOverMessage.h
//  ww4
//
//  Created by xiao tang on 13-6-18.
//
//

#ifndef __ww4__DefendOverMessage__
#define __ww4__DefendOverMessage__

#include "MyBaseMessage.h"
#include "MyBaseQuest.h"

class DefendOverMessage : public MyBaseMessage {
    
public:
    DefendOverMessage():
    isVictory(false){
        tag = defendOverMessageTag;
    }
    ~DefendOverMessage(){
        
    }
    static DefendOverMessage* create(bool isVictory);
    virtual void sendMsg();
    bool isVictory;
};

#endif /* defined(__ww4__DefendOverMessage__) */
