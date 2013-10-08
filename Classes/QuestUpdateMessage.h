//
//  QuestUpdateMessage.h
//  ww4
//
//  Created by xiao tang on 13-6-8.
//
//

#ifndef __ww4__QuestUpdateMessage__
#define __ww4__QuestUpdateMessage__

#include <iostream>
#include "MyBaseMessage.h"
#include "MyBaseQuest.h"

class QuestUpdateMessage : public MyBaseMessage {
    
public:
    QuestUpdateMessage() {
        tag = questUpdateMessageTag;
    }
    ~QuestUpdateMessage(){
        
    }
    static QuestUpdateMessage* create(MyBaseQuest* quest);
    virtual void sendMsg();
    MyBaseQuest* quest;
};

#endif /* defined(__ww4__QuestUpdateMessage__) */
