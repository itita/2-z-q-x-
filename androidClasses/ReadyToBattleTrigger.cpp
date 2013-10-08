//
//   ReadyToBattleTrigger.cpp
//  ww4
//
//  Created by xiao tang on 13-8-2.
//
//

#include "ReadyToBattleTrigger.h"
#include "GXMessage.h"
#include "TestScene.h"
#include "MyJsonUtil.h"
#include "DefineSet.h"
#include "UpdateBuildingMessag.h"
#include "UpdateArmyMessage.h"
#include "UnitSet.h"
#include "PulsarNative.h"
#include "MyHttpConnection.h"

ReadyToBattleTrigger* ReadyToBattleTrigger::create(CCNode* _scene) {
    ReadyToBattleTrigger* trigger = new ReadyToBattleTrigger();
    trigger->scene = _scene;
    trigger->autorelease();
    return trigger;
}

bool ReadyToBattleTrigger::excuteMsg(MyBaseMessage* msg) {
    if(msg->tag == gameDataMessageTag) {
        GXMessage* uMsg = (GXMessage*)(msg);
        if (uMsg->getCmd()->compare("searchByNickname") == 0 ) {
            scene->removeChildByTag(waitMenuTag,true);
            ((TestScene*)scene)->displaySearchResultList(MyJsonUtil::parseBaseInfoBean(uMsg->getDetail()));
        }
    }
//    if(msg->tag == storeMessageTag) {
//        GXMessage* uMsg = (GXMessage*)(msg);
//        if (uMsg->getCmd()->compare("bought") == 0 ) {
//            if(uMsg->succ) {
//                MyGameInfo::getInstance()->boughtArray->removeAllObjects();
//                MyJsonUtil::parseBoughtInfo(uMsg->getDetail());
//            }
//            ((StartScene*)scene)->toShopCallBack();
//        }
//        return true;
//    }
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

bool ReadyToBattleTrigger::onRegist() {
    return true;
}

bool ReadyToBattleTrigger::onUnRegist() {
    return true;
}
