//
//  StoreTrigger.h
//  ww4
//
//  Created by xiao tang on 13-5-9.
//
//

#ifndef __ww4__StoreTrigger__
#define __ww4__StoreTrigger__

#include <iostream>

#include "MyBaseTrigger.h"
#include "MyBaseMessage.h"

class StoreTrigger : public MyBaseTrigger  {
    
    
public:
    ~StoreTrigger() {
//        CC_SAFE_RELEASE(m_pScheduler);
//        CC_SAFE_RELEASE(msgArray);
    }
    
    StoreTrigger():
    scene(NULL){
        
    }
    static StoreTrigger* create(CCNode* _scene);
    virtual bool excuteMsg(MyBaseMessage* msg);
    virtual bool onRegist();
    virtual bool onUnRegist();
//    CC_PROPERTY(CCScheduler*, m_pScheduler, Scheduler);
    CCNode* scene;
//    void sendBuyInfo(bool isUpdate);
private:
//    inline void scheduleOnce(SEL_SCHEDULE selector, float delay);
//
//    inline void unschedule(SEL_SCHEDULE selector);
//    
//    void sendBuyInfoAuto();
//
//    CCArray* msgArray;
};

#endif /* defined(__ww4__StoreTrigger__) */
