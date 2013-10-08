//
//  TransitionTrigger.cpp
//  ww4
//
//  Created by xiao tang on 13-4-27.
//
//

#include "TransitionTrigger.h"
#include "GXMessage.h"
#include "TransitonScene.h"
#include "MyJsonUtil.h"
#include "MyHttpConnection.h"

TransitionTrigger* TransitionTrigger::create(CCNode* _scene) {
    TransitionTrigger* trigger = new TransitionTrigger();
    trigger->scene = _scene;
    trigger->autorelease();
    return trigger;
}

bool TransitionTrigger::excuteMsg(MyBaseMessage* msg) {
    
    if(msg->tag == gameDataMessageTag) {
        GXMessage* uMsg = (GXMessage*)(msg);
        if (uMsg->getCmd()->compare("getMyself") == 0) {
            ((TransitonScene*)scene)->setResponse(CCString::create(uMsg->getDetail()->getCString()));
            ((TransitonScene*)scene)->toStartScene();
        } else if(uMsg->getCmd()->compare("getGameDataList") == 0)
        {
           ((TransitonScene*)scene)->toReadytoBattleScene(MyJsonUtil::parseReadyNativeInfo(CCString::create(uMsg->getDetail()->getCString())));
        }else if(uMsg->getCmd()->compare("getOthers") == 0) {
            ((TransitonScene*)scene)->setResponse(CCString::create(uMsg->getDetail()->getCString()));
            ((TransitonScene*)scene)->toBattleScene();
        } else if(uMsg->getCmd()->compare("getForDefend") == 0) {
            ((TransitonScene*)scene)->setResponse(CCString::create(uMsg->getDetail()->getCString()));
            ((TransitonScene*)scene)->toDefendScene();
        } else if(uMsg->getCmd()->compare("getRobInfo") == 0) {
            CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.2, MyJsonUtil::parseChiefSceneInfo(CCString::create(uMsg->getDetail()->getCString())), ccBLACK));
        }

        MyHttpConnection::getInstance()->setCecheCmd(NULL);
        return false;
    }
    return false;
}

bool TransitionTrigger::onRegist() {
    return true;
}

bool TransitionTrigger::onUnRegist() {
    return true;
}