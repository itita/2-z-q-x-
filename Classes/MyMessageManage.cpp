//
//  MessageManage.cpp
//  ww3
//
//  Created by xiao tang on 12-12-14.
//
//

#include "MyMessageManage.h"
//#include ""

MyMessageManage* MyMessageManage::msgManagerInstance = NULL;
pthread_mutex_t MyMessageManage::msgMutex = PTHREAD_MUTEX_INITIALIZER;

MyMessageManage::MyMessageManage() {
    m_pScheduler = CCDirector::sharedDirector()->getScheduler();
    m_pScheduler->retain();
}

MyMessageManage::~MyMessageManage() {
    CC_SAFE_RELEASE(m_pScheduler);
    CC_SAFE_RELEASE_NULL(msgList);
    CC_SAFE_RELEASE_NULL(triggerList);
}

MyMessageManage* MyMessageManage::create() {
    MyMessageManage* manage = new MyMessageManage();
    manage->msgList = CCArray::create();
    manage->msgList->retain();
    manage->triggerList = CCArray::create();
    manage->triggerList->retain();
    manage->toRemoveArray = CCArray::create();
    manage->toRemoveArray->retain();
    manage->toAddArray = CCArray::create();
    manage->toAddArray->retain();
    manage->autorelease();
    manage->schedule(schedule_selector(MyMessageManage::excuteMsg),0.1,kCCRepeatForever,0);
    return manage;
}

void MyMessageManage::schedule(SEL_SCHEDULE selector, float interval, unsigned int repeat, float delay)
{
    CCAssert( selector, "Argument must be non-nil");
    CCAssert( interval >=0, "Argument must be positive");
    
    m_pScheduler->scheduleSelector(selector, this, interval, repeat, delay, false);
}

MyMessageManage* MyMessageManage::getInstance(){
    if (!msgManagerInstance) {
        msgManagerInstance = MyMessageManage::create();
    }
    return msgManagerInstance;
}

void MyMessageManage::excuteMsg() {
    CCObject* obj;
    MyBaseTrigger* trigger;
    if (msgList->count()>0) {
        CCARRAY_FOREACH(toAddArray, obj) {
            triggerList->addObject(obj);
        }
        toAddArray->removeAllObjects();
        
        CCARRAY_FOREACH(toRemoveArray, obj) {
            triggerList->removeObject(obj);
        }
        toRemoveArray->removeAllObjects();
        
        int ret = pthread_mutex_lock(&MyMessageManage::msgMutex);
        CCAssert(ret == 0, "lock error ,error code ");
        MyBaseMessage* msg = (MyBaseMessage*)msgList->objectAtIndex(0);
        msg->retain();
        msgList->removeObjectAtIndex(0);
        pthread_mutex_unlock(&MyMessageManage::msgMutex);
        
        CCARRAY_FOREACH_REVERSE(triggerList, obj) {
            trigger = (MyBaseTrigger*)obj;
            if(trigger->excuteMsg(msg)) {
                break;
            }
        }
        msg->release();
    }
}

CCScheduler* MyMessageManage::getScheduler()
{
    return m_pScheduler;
}

void MyMessageManage::setScheduler(CCScheduler* scheduler)
{
    if( scheduler != m_pScheduler ) {
//        this->unscheduleAllSelectors();
        CC_SAFE_RETAIN(scheduler);
        CC_SAFE_RELEASE(m_pScheduler);
        m_pScheduler = scheduler;
    }
}

void MyMessageManage::registerTrigger(MyBaseTrigger *trigger) {
    trigger->onRegist();
    toAddArray->addObject(trigger);
}

void MyMessageManage::unRegisterTrigger(MyBaseTrigger *trigger) {
    trigger->onUnRegist();
    toRemoveArray->addObject(trigger);
}
