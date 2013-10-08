//
//  BattleOverMessage.h
//  ww4
//
//  Created by xiao tang on 13-6-8.
//
//

#ifndef __ww4__BattleOverMessage__
#define __ww4__BattleOverMessage__

#include "MyBaseMessage.h"
#include "MyBaseQuest.h"

class BattleOverMessage : public MyBaseMessage {
    
public:
    BattleOverMessage():
    isVictory(false){
        tag = battleOverMessageTag;
    }
    ~BattleOverMessage(){
        
    }
    static BattleOverMessage* create(bool isVictory);
    virtual void sendMsg();
    bool isVictory;
};

#endif /* defined(__ww4__BattleOverMessage__) */
