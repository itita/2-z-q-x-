//
//  UpdateArmyMessage.h
//  ww4
//
//  Created by xiao tang on 13-5-9.
//
//

#ifndef __ww4__UpdateArmyMessage__
#define __ww4__UpdateArmyMessage__

#include <iostream>
#include "MyBaseMessage.h"

using namespace cocos2d;

class UpdateArmyMessage : public MyBaseMessage {
    
public:
    UpdateArmyMessage() {
        tag = updateArmyMessageTag;
    }
    ~UpdateArmyMessage(){
        
    }
    static UpdateArmyMessage* create(int armyId,int preLevel,int nextLevel);
    virtual void sendMsg();
    int armyId;
    int preLevel;
    int nextLevel;
};

#endif /* defined(__ww4__UpdateArmyMessage__) */
