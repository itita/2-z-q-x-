//
//  StoreTrigger.cpp
//  ww4
//
//  Created by xiao tang on 13-5-9.
//
//

#include "StoreTrigger.h"
#include "GXMessage.h"
#include "StartScene.h"
#include "MyJsonUtil.h"
#include "DefineSet.h"
#include "UpdateBuildingMessag.h"
#include "UpdateArmyMessage.h"
#include "UnitSet.h"
#include "PulsarNative.h"
#include "MyHttpConnection.h"

StoreTrigger* StoreTrigger::create(CCNode* _scene) {
    StoreTrigger* trigger = new StoreTrigger();
    trigger->scene = _scene;
//    trigger->m_pScheduler = CCDirector::sharedDirector()->getScheduler();
//    trigger->m_pScheduler->retain();
//    trigger->msgArray = CCArray::create();
//    trigger->msgArray->retain();
    trigger->autorelease();
    return trigger;
}

bool StoreTrigger::excuteMsg(MyBaseMessage* msg) {
    
    if(msg->tag == storeMessageTag) {
        GXMessage* uMsg = (GXMessage*)(msg);
        if (uMsg->getCmd()->compare("bought") == 0 ) {
            if(uMsg->succ) {
                MyGameInfo::getInstance()->boughtArray->removeAllObjects();
                MyJsonUtil::parseBoughtInfo(uMsg->getDetail());
            }
           ((StartScene*)scene)->toShopCallBack();
        }
        return true;
    }
//    else if(msg->tag == updateBuildingMessageTag) {
//        UpdateBuildingMessag* uMsg =(UpdateBuildingMessag*)(msg);
//        if (uMsg->buildingId == superYouTianTag || uMsg->buildingId == superKuangChangTag) {
//            unschedule(schedule_selector(StoreTrigger::sendBuyInfoAuto));
//            scheduleOnce(schedule_selector(StoreTrigger::sendBuyInfoAuto),15);
//            
//            char str[300] = {0};
//            int tag = 10000+uMsg->buildingId*100+uMsg->nextLevel;
//            sprintf(str,"{\"cmd\":\"store.buy\",\"ititaId\":\"%s\",\"tag\":\"%d\"}\r\n",PulsarNative::getItitaId(),tag);
//            msgArray->addObject(CCString::create(str));
//        }
//    } else if(msg->tag == updateArmyMessageTag) {
//        UpdateArmyMessage* uMsg = (UpdateArmyMessage*)(msg);
//        if (uMsg->armyId == panzergrenadierCardId || uMsg->armyId == InfanterieCardId || uMsg->armyId == HummingBirdCardId) {
//            unschedule(schedule_selector(StoreTrigger::sendBuyInfoAuto));
//            scheduleOnce(schedule_selector(StoreTrigger::sendBuyInfoAuto),15);
//    
//            char str[300] = {0};
//            int tag = 20000+uMsg->armyId*100+uMsg->nextLevel;
//            sprintf(str,"{\"cmd\":\"store.buy\",\"ititaId\":\"%s\",\"tag\":\"%d\"}\r\n",PulsarNative::getItitaId(),tag);
//            msgArray->addObject(CCString::create(str));
//        }
//    }
    
    return false;
}

bool StoreTrigger::onRegist() {
    return true;
}

bool StoreTrigger::onUnRegist() {
    return true;
}

//CCScheduler* StoreTrigger::getScheduler()
//{
//    return m_pScheduler;
//}
//
//void StoreTrigger::setScheduler(CCScheduler* scheduler)
//{
//    if( scheduler != m_pScheduler ) {
////        this->unscheduleAllSelectors();
//        CC_SAFE_RETAIN(scheduler);
//        CC_SAFE_RELEASE(m_pScheduler);
//        m_pScheduler = scheduler;
//    }
//}
//
//void StoreTrigger::scheduleOnce(SEL_SCHEDULE selector, float delay) {
//    m_pScheduler->scheduleSelector(selector, this, 0.0f, false, 0, delay);
//}
//
//void StoreTrigger::unschedule(SEL_SCHEDULE selector) {
//    m_pScheduler->unscheduleSelector(selector, this);
//}

//void StoreTrigger::sendBuyInfoAuto() {
//    if (msgArray->count() >0) {
//        CCLog("自动发送购买信息");
//        unschedule(schedule_selector(StoreTrigger::sendBuyInfoAuto));
//        MyHttpConnection::getInstance()->sendBuyList(msgArray);
//        msgArray->removeAllObjects();
//        ((StartScene*)scene)->updateMyData();
//    }
//}
//
//void StoreTrigger::sendBuyInfo(bool isUpdate) {
//    if (msgArray->count() >0) {
//        CCLog("被动发送购买信息");
//        unschedule(schedule_selector(StoreTrigger::sendBuyInfoAuto));
//        MyHttpConnection::getInstance()->sendBuyList(msgArray);
//        msgArray->removeAllObjects();
//        if (isUpdate) {
//            ((StartScene*)scene)->updateMyData();
//        }
//    }
//}