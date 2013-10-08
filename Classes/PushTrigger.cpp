//
//  PushTrigger.cpp
//  ww4
//
//  Created by xiao tang on 13-3-28.
//
//

#include "PushTrigger.h"
#include "MyMessageManage.h"
#include "GXMessage.h"
#include "MyJsonUtil.h"
#include "LoadingScene.h"
#include "TransitonScene.h"
#include "MyHttpConnection.h"
#include "ServerScene.h"
#include "PulsarNative.h"
#include "MyUtil.h"
#include "MyJsonUtil.h"
#include "QuestManager.h"
#include "GXChatHandler.h"


PushTrigger* PushTrigger::pushtriggerManagerInstance = NULL;

PushTrigger* PushTrigger::getInstance(){
    if (!pushtriggerManagerInstance) {
        //CREATE
        PushTrigger* trigger = new PushTrigger();
        trigger->unionPushArray = CCArray::create();
        trigger->unionPushArray->retain();
        MyMessageManage::getInstance()->registerTrigger(trigger);
        pushtriggerManagerInstance = trigger;
    }
    return pushtriggerManagerInstance;
}

bool PushTrigger::excuteMsg(MyBaseMessage* msg) {
    if (msg->tag == loadSpeakerMessageTag) {
        GXMessage* uMsg = (GXMessage*)msg;
        GXBaseScene* scene = dynamic_cast<GXBaseScene*>(CCDirector::sharedDirector()->getRunningScene());
        if (scene != NULL && scene->isEnter == true) {
            MyUtil::getInstance()->addloadSpeakerLayer(scene,CCString::create(GXUtil::insertNewline(uMsg->getMsg()->getCString(),30)));
        }
    }else if(msg->tag == unionPushMessageTag) {
        GXMessage* uMsg = (GXMessage*)msg;
        if (uMsg->getCmd()->compare("unionApplyJoin") == 0) {
            unionPushArray->addObjectsFromArray(MyJsonUtil::parsePushUnionApplyJoin(uMsg->getDetail()));
        }
        return false;
    } else if(msg->tag == systemMessageTag) {
        GXMessage* uMsg = (GXMessage*)msg;
        if (uMsg->getCmd()->compare("disconnect")==0) {
            GXBaseScene* scene = dynamic_cast<GXBaseScene*>(CCDirector::sharedDirector()->getRunningScene());
            if (connectCode == reconncetTag) {
                if(MyHttpConnection::getInstance()->initSocket(MyHttpConnection::getInstance()->getCacheHostUrl()->getCString(), PulsarNative::serverId)) {
                    char str[30] = {0};
                    sprintf(str,"s%d_ititaId",PulsarNative::serverId);
#if game_style != ezzhgThird
                    std::string ititaId = CCUserDefault::sharedUserDefault()->getStringForKey(str,"");
                    if (ititaId.compare("") != 0) {
                        UserBean* bean = UserBean::create();
                        bean->setItitaId(CCString::create(ititaId.c_str()));
                        sprintf(str,"s%d_password",PulsarNative::serverId);
                        bean->setPassword(CCString::create(CCUserDefault::sharedUserDefault()->getStringForKey(str,"").c_str()));
                        MyHttpConnection::getInstance()->sendLogin(bean,true);
                    } else {
                        MyHttpConnection::getInstance()->sendFastEnterGame(true);
                    }
#endif
#if game_style == ezzhgThird
                    int userId = CCUserDefault::sharedUserDefault()->getIntegerForKey(str,-1);
                    if (userId > 0) {
                        MyHttpConnection::getInstance()->commonThirdRegisterOrLogin(userId,true);;
                    } else {
                        CCLog("userId,%d",userId);
                    }
#endif
//                    MyHttpConnection::getInstance()->sendGetOrderId();
                    MyHttpConnection::getInstance()->sendCecheCmd();
                    //重连聊天服务器
                    if (!GXChatHandler::isConn && GXChatHandler::getInstance()->getCacheChatServerUrl() != NULL) {
                        GXChatHandler::getInstance()->startPomelo(GXChatHandler::getInstance()->getCacheChatServerUrl()->getCString());
                    }
                } else if (scene && scene->isEnter) {
                    CCDirector::sharedDirector()->replaceScene(TransitonScene::create(ServerSceneTag,CCString::create("与服务器连接已断开")));
                    MyHttpConnection::getInstance()->setCecheCmd(NULL);
                    //强制退出聊天服务器
                    GXChatHandler::getInstance()->sendDisconnect();
                    connectCode = reconncetTag;
                }
            } else if(connectCode == logoutTag) {
                if (scene && scene->isEnter) {
                    CCDirector::sharedDirector()->replaceScene(TransitonScene::create(ServerSceneTag));
                    MyHttpConnection::getInstance()->setCecheCmd(NULL);
                }
                connectCode = reconncetTag;
            } else if(connectCode == relogTag) {
                if (scene && scene->isEnter) {
                    CCDirector::sharedDirector()->replaceScene(TransitonScene::create(ServerSceneTag,CCString::create("账号在另一台设备\n上登陆,您逼迫下线")));
                    MyHttpConnection::getInstance()->setCecheCmd(NULL);
                }
                //强制退出聊天服务器
                GXChatHandler::getInstance()->sendDisconnect();
                connectCode = reconncetTag;
            } else if(connectCode == pauseTag) {
                if(MyHttpConnection::getInstance()->initSocket(MyHttpConnection::getInstance()->getCacheHostUrl()->getCString(), PulsarNative::serverId)) {
                    char str[30] = {0};
                    sprintf(str,"s%d_ititaId",PulsarNative::serverId);
#if game_style != ezzhgThird
                    std::string ititaId = CCUserDefault::sharedUserDefault()->getStringForKey(str,"");
                    if (ititaId.compare("") != 0) {
                        UserBean* bean = UserBean::create();
                        bean->setItitaId(CCString::create(ititaId.c_str()));
                        sprintf(str,"s%d_password",PulsarNative::serverId);
                        bean->setPassword(CCString::create(CCUserDefault::sharedUserDefault()->getStringForKey(str,"").c_str()));
                        MyHttpConnection::getInstance()->sendLogin(bean,true);
                    } else {
                        MyHttpConnection::getInstance()->sendFastEnterGame(true);
                    }
#endif
#if game_style == ezzhgThird
                    int userId = CCUserDefault::sharedUserDefault()->getIntegerForKey(str,-1);
                    if (userId > 0) {
                        MyHttpConnection::getInstance()->commonThirdRegisterOrLogin(userId,true);;
                    } else {
                        CCLog("userId,%d",userId);
                    }
#endif
                    CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.2, TransitonScene::create(startSceneTag), ccBLACK));
                    //重连聊天服务器
                    if (!GXChatHandler::isConn && GXChatHandler::getInstance()->getCacheChatServerUrl() != NULL) {
                        GXChatHandler::getInstance()->startPomelo(GXChatHandler::getInstance()->getCacheChatServerUrl()->getCString());
                    }
                } else if (scene && scene->isEnter) {
                    CCDirector::sharedDirector()->replaceScene(TransitonScene::create(ServerSceneTag,CCString::create("与服务器连接已断开")));
                    MyHttpConnection::getInstance()->setCecheCmd(NULL);
                    //强制退出聊天服务器
                    GXChatHandler::getInstance()->sendDisconnect();
                    connectCode = reconncetTag;
                }
                connectCode = reconncetTag;
            }
        } else if(uMsg->getCmd()->compare("multiLogin")==0) {
            connectCode = relogTag;
        }
    } else if(msg->tag == pushMessageTag) {
        GXMessage* uMsg = dynamic_cast<GXMessage*>(msg);
        if (uMsg->getCmd()->compare("diamond") == 0) {
            if (MyJsonUtil::parseChargeInfo(uMsg->getDetail())) {
#if game_style == ezqx
                if (MyGameInfo::getInstance()->creatorArray->count()>0) {
                    //初始化部队已完成，检测蜂鸟直升机，获得后更新
                    CCObject* obj;
                    bool flag = false;
                    CCARRAY_FOREACH(MyGameInfo::getInstance()->creatorArray,obj) {
                        CreatorInfoBean* testBean = (CreatorInfoBean*)obj;
                        if(testBean->creator->cardId == HummingBirdCardId) {
                            flag = true;
                            break;
                        }
                    }
                    if (!flag) {
                        MyGameInfo::getInstance()->creatorArray->addObject(CreatorInfoBean::create(HummingBirdCardId));
                    }
                }
#endif
            }
        } else if(uMsg->getCmd()->compare("exit") == 0) {
            CCDirector::sharedDirector()->replaceScene(TransitonScene::create(ServerSceneTag,uMsg->getMsg()));
            MyHttpConnection::getInstance()->sendDisconnect();
            GXChatHandler::getInstance()->sendDisconnect();
            connectCode = doNothingTag;
            MyHttpConnection::getInstance()->setCecheCmd(NULL);
        } else if(uMsg->getCmd()->compare("resourceChange") == 0) {
            MyJsonUtil::parseResourceChange(uMsg->getDetail());
        }
    } else if(msg->tag == gameDataMessageTag) {
        GXMessage* uMsg = dynamic_cast<GXMessage*>(msg);
        if(uMsg->getCmd()->compare("finished") == 0) {
            if (uMsg->succ == true) {
                int missionId = atoi(uMsg->getMsg()->getCString());
                CCArray* questArray = QuestManager::getInstance()->questList;
                CCObject* obj;
                MyBaseQuest* quest;
                int flag = -1;
                int i=0;
                CCARRAY_FOREACH(questArray,obj) {
                    MyBaseQuest* tempQuest = (MyBaseQuest*)obj;
                    if (tempQuest->questId == missionId) {
                        quest = tempQuest;
                        flag = i;
                        break;
                    }
                    i++;
                }
                quest->getPrize();
                questArray->removeObjectAtIndex(flag);
            }
        }
    }
    return false;
}

void PushTrigger::clear() {
    unionPushArray->removeAllObjects();
}

bool PushTrigger::onRegist() {
    return true;
}

bool PushTrigger::onUnRegist() {
    return true;
}
