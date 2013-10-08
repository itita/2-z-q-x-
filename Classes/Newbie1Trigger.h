//
//  Newbie1Trigger.h
//  ww3
//
//  Created by xiao tang on 12-12-15.
//
//

#ifndef ww3_Newbie1Trigger_h
#define ww3_Newbie1Trigger_h
#include "MyBaseTrigger.h"
#include "cocos2d.h"

using namespace cocos2d;

class Newbie1Trigger : public MyBaseTrigger  {
    
public:
    Newbie1Trigger():
    statues(0) {
    }
    ~Newbie1Trigger();
    virtual bool excuteMsg(MyBaseMessage* msg);
    static Newbie1Trigger* create(CCNode* node);
    void toNextCallBack(CCNode* node);
    virtual bool onRegist();
    virtual bool onUnRegist();
    void toSkip();
    void toDisplayMisson();
    CCNode* node;
private:
    int statues;
//    void deployUnit();
};

#endif
