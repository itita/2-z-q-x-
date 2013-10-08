//
//  MyBaseQuest.cpp
//  ww4
//
//  Created by xiao tang on 13-8-31.
//
//

#include "MyBaseQuest.h"
#include "DialogCompleteMessage.h"
#include "StartScene.h"

bool MyBaseQuest::excuteMsg(MyBaseMessage* msg) {
    if(msg->tag == DialogCompleteMessageTag ) {
        DialogCompleteMessage* uMsg = (DialogCompleteMessage*)msg;
        if(uMsg->currentNode >= uMsg->maxNode && uMsg->dialogTag == this->questId) {
            setDialog(NULL);
            StartScene* scene = dynamic_cast<StartScene*>(CCDirector::sharedDirector()->getRunningScene());
            if(scene != NULL) {
                scene->displayMissionInfo(this);
            }
        }
        return true;
    }
    return false;
}