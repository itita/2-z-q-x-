//
//  TransitionTrigger.h
//  ww4
//
//  Created by xiao tang on 13-4-27.
//
//

#ifndef __ww4__TransitionTrigger__
#define __ww4__TransitionTrigger__

#include <iostream>
#include "MyBaseTrigger.h"
#include "MyBaseMessage.h"

class TransitionTrigger : public MyBaseTrigger  {
    
    
public:
    ~TransitionTrigger() {
        
    }
    
    TransitionTrigger():
    scene(NULL){
        
    }
    static TransitionTrigger* create(CCNode* _scene);
    virtual bool excuteMsg(MyBaseMessage* msg);
    virtual bool onRegist();
    virtual bool onUnRegist();
    CCNode* scene;
};

#endif /* defined(__ww4__TransitionTrigger__) */
