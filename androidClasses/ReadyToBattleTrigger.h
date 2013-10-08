//
//  ReadyToBattleTrigger.h
//  ww4
//
//  Created by xiao tang on 13-8-2.
//
//

#ifndef __ww4___ReadyToBattleTrigger__
#define __ww4___ReadyToBattleTrigger__

#include "MyBaseTrigger.h"
#include "MyBaseMessage.h"

class ReadyToBattleTrigger : public MyBaseTrigger {
    
public:
    ~ReadyToBattleTrigger() {
    }
    
    ReadyToBattleTrigger():
    scene(NULL){
        
    }
    static ReadyToBattleTrigger* create(CCNode* _scene);
    virtual bool excuteMsg(MyBaseMessage* msg);
    virtual bool onRegist();
    virtual bool onUnRegist();

    CCNode* scene;
};

#endif /* defined(__ww4___ReadyToBattleTrigger__) */
