//
//  PushTrigger.h
//  ww4
//
//  Created by xiao tang on 13-3-28.
//
//

#ifndef __ww4__PushTrigger__
#define __ww4__PushTrigger__

#include <iostream>
#include "MyBaseTrigger.h"

#define reconncetTag 0
#define logoutTag 1
#define relogTag 2
#define pauseTag 3
#define doNothingTag 4

class PushTrigger : public MyBaseTrigger{
    
public:
    PushTrigger():connectCode(reconncetTag) {}
    static PushTrigger* pushtriggerManagerInstance;
    static PushTrigger* getInstance();
    
    virtual bool excuteMsg(MyBaseMessage* msg);
    virtual bool onRegist();
    virtual bool onUnRegist();
    virtual void clear();
    int connectCode;
    
    CCArray* getUnionDisplayArray();
    CCArray* unionPushArray;

};

#endif /* defined(__ww4__PushTrigger__) */
