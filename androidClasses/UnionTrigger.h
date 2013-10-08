//
//  UnionTrigger.h
//  ww4
//
//  Created by xiao tang on 13-3-19.
//
//

#ifndef __ww4__UnionTrigger__
#define __ww4__UnionTrigger__

#include <iostream>
#include "MyBaseTrigger.h"
#include "StartScene.h"
#include "GXMessage.h"

class UnionTrigger : public MyBaseTrigger {
        
public:
    UnionTrigger():
    isRefresh(false) {
    
    }
    ~UnionTrigger(){
    
    }
    virtual bool excuteMsg(MyBaseMessage* msg);
    static UnionTrigger* create(StartScene* node);
    virtual bool onRegist();
    virtual bool onUnRegist();
    StartScene* startScene;
private:
    bool isRefresh;
};

#endif /* defined(__ww4__UnionTrigger__) */
