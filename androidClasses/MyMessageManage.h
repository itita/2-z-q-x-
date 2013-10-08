//
//  MessageManage.h
//  ww3
//
//  Created by xiao tang on 12-12-14.
//
//

#ifndef ww3_MyMessageManage_h
#define ww3_MyMessageManage_h
#include "cocos2d.h"
#include "MyBaseTrigger.h"

using namespace cocos2d;

class MyMessageManage : public CCObject {
    
public:
    
    MyMessageManage();
    ~MyMessageManage();
    CCArray* msgList;
    CCArray* triggerList;
    static MyMessageManage* msgManagerInstance;
    static MyMessageManage* getInstance();
    static MyMessageManage* create();
    CC_PROPERTY(CCScheduler*, m_pScheduler, Scheduler);
    void registerTrigger(MyBaseTrigger* quest);
    void unRegisterTrigger(MyBaseTrigger* quest);
    static pthread_mutex_t msgMutex;
private:
    void excuteMsg();
    CCArray* toRemoveArray;
    CCArray* toAddArray;
    void schedule(SEL_SCHEDULE selector, float interval, unsigned int repeat, float delay);

    
};


#endif
