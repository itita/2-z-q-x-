//
//  UnionTrigger.cpp
//  ww4
//
//  Created by xiao tang on 13-3-19.
//
//

#include "UnionTrigger.h"
#include "GXMessage.h"
#include "GXInteger.h"
#include "GXArray.h"
#include "MyGameInfo.h"
#include "MyUtil.h"
#include "DefineSet.h"
#include "AsyUnionBean.h"
#include "DefineSet.h"
#include "MyBaseQuest.h"
#include "QuestManager.h"
#include "QuestUpdateMessage.h"
#include "MyHttpConnection.h"
#include "PulsarNative.h"
#include "PushTrigger.h"

bool UnionTrigger::excuteMsg(MyBaseMessage* msg) {
    
    if(msg->tag == unionMessageTag) {
        GXMessage* uMsg = (GXMessage*)(msg);
       if (uMsg->getCmd()->compare("getByItitaId") == 0) {
           UnionBean* bean = MyJsonUtil::parseUserUnion(uMsg->getDetail());
           int i = bean->unionId;
            if(i >0) {
                MyGameInfo::getInstance()->setUnionBean(bean);
                startScene->toUnionMainUI();
                
            } else {
                startScene->toUnionJoinOrCreate();
            }
       } else if(uMsg->getCmd()->compare("members")==0) {
           startScene->getChildByTag(creatorLayerTag)->removeChildByTag(displayUnionLayerTag,true);
           startScene->displayUnionMember(MyJsonUtil::parseUnionMember(uMsg->getDetail()));
       }  else if(uMsg->getCmd()->compare("publishNotice") == 0) {
           startScene->addChild(MyUtil::getInstance()->getCommonTipDialog(uMsg->getMsg(),startScene,menu_selector(StartScene::cancelTipDialog),0));
           startScene->removeWaitMenu();
           if (uMsg->succ) {
               CCString* newNotice = (CCString*)startScene->getChildByTag(creatorLayerTag)->getChildByTag(displayUnionLayerTag)->getChildByTag(unionManagerLayerTag)->getUserObject();
               MyGameInfo::getInstance()->getUnionBean()->setNotice(newNotice);
               startScene->unionManagerNotice();
           }
           
       }else if(uMsg->getCmd()->compare("pagging") == 0) {
           CCArray* array = MyJsonUtil::parseUnionList(uMsg->getDetail());
           
           startScene->displayUnionJoin(array);
       } else  if (uMsg->getCmd()->compare("create") == 0) {
           if (uMsg->succ) {
               MyGameInfo::getInstance()->setUnionBean(MyJsonUtil::parseUserUnion(uMsg->getDetail()));
               startScene->addUnionLayerInAvatar();
           }
           startScene->createUnionResult(uMsg->succ,CCString::create(uMsg->getMsg()->getCString()));
       } else if (uMsg->getCmd()->compare("exit") == 0) {
           if (uMsg->succ) {
               startScene->removeUnionLayerInAvatar();
               MyGameInfo::getInstance()->setUnionBean(UnionBean::create());
           }
       } else if(uMsg->getCmd()->compare("dissolve") == 0) {
           startScene->addChild(MyUtil::getInstance()->getCommonTipDialog(uMsg->getMsg(),startScene,menu_selector(StartScene::cancelTipDialog),0));
           if (uMsg->succ) {
               startScene->removeUnionLayerInAvatar();
               MyGameInfo::getInstance()->setUnionBean(UnionBean::create());
           }
       }
        return true;
    }else if (msg->tag == unionPushMessageTag) {
        GXMessage* uMsg = (GXMessage*)(msg);
        if (uMsg->getCmd()->compare("unionApplyJoin") == 0) {
            CCArray* array = MyJsonUtil::parsePushUnionApplyJoin(uMsg->getDetail());
            CCObject* obj;
            CCARRAY_FOREACH(array,obj) {
                startScene->checkNewUnionMessage((CCDictionary*)obj);
            }
            PushTrigger::getInstance()->unionPushArray->addObjectsFromArray(array);
            return true;
        } else {
            if (uMsg->getCmd()->compare("unionApplyApproveResult") == 0 && uMsg->succ) {
                MyGameInfo::getInstance()->setUnionBean(MyJsonUtil::parseUserUnion(uMsg->getDetail()));
                startScene->addUnionLayerInAvatar();
            } else if (uMsg->getCmd()->compare("unionRemoved") == 0 && uMsg->succ) {
                startScene->removeUnionLayerInAvatar();
                MyGameInfo::getInstance()->setUnionBean(UnionBean::create());
            }  else if (uMsg->getCmd()->compare("dissolveUnion") == 0 && uMsg->succ) {
                startScene->removeUnionLayerInAvatar();
                MyGameInfo::getInstance()->setUnionBean(UnionBean::create());
            }
            startScene->quitCreator();
            startScene->addChild(MyUtil::getInstance()->getCommonTipDialog(uMsg->getMsg(),startScene,menu_selector(StartScene::cancelTipDialog),0),10);
        }
    } else if(msg->tag == gameDataMessageTag) {
        GXMessage* uMsg = dynamic_cast<GXMessage*>(msg);
        if(uMsg->getCmd()->compare("getWhoAttackedMe") == 0) {
            if (uMsg->succ) {
                if (startScene->getChildByTag(waitMenuTag) == NULL) {
                    startScene->addChild(MyUtil::getInstance()->getWaitLayer("正在读取战绩"));
                }
                startScene->disPlayRecordView(MyJsonUtil::parseMatches(uMsg->getDetail()));
            } else {
                startScene->removeWaitMenu();
            }
        } else if(uMsg->getCmd()->compare("getPowerRank") == 0) {
            if (uMsg->succ) {
                startScene->displayTopRankView(MyJsonUtil::parseTopRank(uMsg->getDetail()));
            } else {
                startScene->removeWaitMenu();
            }
        } else if(uMsg->getCmd()->compare("getCPUWar") == 0){
            if (uMsg->succ) {
                startScene->addAttackInfo(MyJsonUtil::parseAttackInfoBean(uMsg->getDetail()));
            }
        } else if(uMsg->getCmd()->compare("finished") == 0) {
            if (uMsg->succ == true) {
                startScene->toArchieveQuestPrize(atoi(uMsg->getMsg()->getCString()));
                return true;
            }
        } else if(uMsg->getCmd()->compare("isBoost") == 0) {
            startScene->removeWaitMenu();
            startScene->displayBoostProduceView(uMsg->succ);
        } else if(uMsg->getCmd()->compare("addOrUpdateBuilding") == 0) {
            startScene->addorUpdateBuilding(MyJsonUtil::parseBuildBean(uMsg->getDetail()));
        }
    } else if(msg->tag == pushMessageTag) {
        GXMessage* uMsg = dynamic_cast<GXMessage*>(msg);
        if (uMsg->getCmd()->compare("diamond") == 0) {
            startScene->addChild(MyUtil::getInstance()->getCommonTipDialog(uMsg->getMsg(),startScene, menu_selector(StartScene::cancelTipDialog),0),10);
        } else if(uMsg->getCmd()->compare("match") == 0) {
            // 干脆并不直接显示，先显示新字
//            startScene->disPlayRecordView(MyJsonUtil::parsePushMatch(uMsg->getDetail()));
            MyJsonUtil::parsePushMatch(uMsg->getDetail());
            startScene->addRecordNewIcon();
            
        } else if(uMsg->getCmd()->compare("orderId") == 0) {
            MyHttpConnection::getInstance()->sendResendGameDataListArray(atoi(uMsg->getMsg()->getCString()));
        } else if(uMsg->getCmd()->compare("getCPUWarList") == 0) {
            startScene->removeWaitMenu();
            startScene->displayDefendList(MyJsonUtil::parseDefendList(uMsg->getDetail()));
        } else if(uMsg->getCmd()->compare("sessionExpired") == 0) {
            startScene->addChild(MyUtil::getInstance()->getCommonTipDialog(CCString::create("你的网络不给力啊~!"),startScene, menu_selector(StartScene::toRefreshStartScene),0),10);
            isRefresh =true;
        }
    } else if(msg->tag == questMessageTag) {
        GXMessage* uMsg = dynamic_cast<GXMessage*>(msg);
        if (uMsg->getCmd()->compare("missions") == 0) {
            if (uMsg->getDetail() != NULL) {
                CCArray* missions = MyJsonUtil::parseQuest(uMsg->getDetail());
                CCObject* obj;
                int i = QuestManager::getInstance()->questList->count();
                bool flag = false;
                CCARRAY_FOREACH(missions,obj) {
                    MyBaseQuest* quest = (MyBaseQuest*)obj;
                    flag = QuestManager::getInstance()->addQuest(quest);
                    if(!flag) {
                        continue;
                    }
                    startScene->addDisplayQuest(quest,true);
//                    item->setPosition(ccp(100,470-i*100));
                    i++;
                }
                uMsg->setDetail(NULL);
            } else {
                int tag = atoi(uMsg->getMsg()->getCString());
                for (int i=tag; i<QuestManager::getInstance()->questList->count(); i++) {
                    MyBaseQuest* quest = (MyBaseQuest*)QuestManager::getInstance()->questList->objectAtIndex(i);
                    startScene->addDisplayQuest(quest,true);
//                    item->setPosition(ccp(100,470-i*100));
                }
            }
            
        }
    } else if(msg->tag == questUpdateMessageTag) {
        QuestUpdateMessage* uMsg = (QuestUpdateMessage*)msg;
        startScene->updateQuestUI(((MyBaseQuest*)uMsg->quest)->questId);
    } else if(msg->tag == userMessageTag) {
        GXMessage* uMsg = dynamic_cast<GXMessage*>(msg);
        if (uMsg->getCmd()->compare("login") == 0 || uMsg->getCmd()->compare("loginNoRegister") == 0) {
            if (uMsg->succ && !isRefresh) {
                MyHttpConnection::getInstance()->sendGetOrderId();
            } 
        } else if(uMsg->getCmd()->compare("updateNickname") == 0) {
            startScene->removeWaitMenu();
            if (uMsg->succ) {
                char str[30] = {0};
                startScene->quitCreator();
                ((CCLabelTTF*)startScene->getChildByTag(UILayerTag)->getChildByTag(avatarTag)->getChildByTag(nicknameLabelTag))->setString(uMsg->getMsg()->getCString());
                MyGameInfo::getInstance()->setNickName(CCString::create(uMsg->getMsg()->getCString()));
                sprintf(str,"s%d_nickname",PulsarNative::serverId);
                CCUserDefault::sharedUserDefault()->setStringForKey(str,uMsg->getMsg()->getCString());
                CCUserDefault::sharedUserDefault()->flush();
                startScene->addChild(MyUtil::getInstance()->getCommonTipDialog(CCString::create("修改昵称成功！"),startScene,menu_selector(StartScene::cancelTipDialog),0));
                MyGameInfo::getInstance()->changeResource(diamondTag,-3000);
            } else {
                startScene->addChild(MyUtil::getInstance()->getCommonTipDialog(uMsg->getMsg(),startScene,menu_selector(StartScene::cancelTipDialog),0));
            }
        }
    } else if(msg->tag == RemoveWaitLayerMessageTag) {
        startScene->removeWaitMenu();
    }
    return false;
}

UnionTrigger* UnionTrigger::create(StartScene* scene) {
    UnionTrigger* trigger = new UnionTrigger();
    trigger->autorelease();
    trigger->startScene = scene;
    return trigger;
}

//inline void UnionTrigger::setInfoUnion(GXMessage* uMsg) {
//    GXInteger* i = ((GXInteger*)uMsg->varMap->objectForKey("unionId"));
//    GXString* name = ((GXString*)uMsg->varMap->objectForKey("name"));
//    GXString* emblemStr =(GXString*)uMsg->varMap->objectForKey("emblem");
//    GXString* descStr = (GXString*)uMsg->varMap->objectForKey("description");
//    GXString* noticeStr = (GXString*)uMsg->varMap->objectForKey("notice");
//    GXInteger* role = (GXInteger*)uMsg->varMap->objectForKey("role");
//    if (name != NULL) {
//        MyGameInfo::getInstance()->unionBean->setName(CCString::create(name->getCString()));
//    }
//    if (descStr != NULL) {
//        MyGameInfo::getInstance()->unionBean->setDesc(CCString::create(descStr->getCString()));
//    }
//    if (emblemStr != NULL) {
//        MyGameInfo::getInstance()->unionBean->setEmblem(CCString::create(emblemStr->getCString()));
//    }
//    if (noticeStr != NULL) {
//        MyGameInfo::getInstance()->unionBean->setNotice(CCString::create(noticeStr->getCString()));
//    }
//    if (role != NULL) {
//        MyGameInfo::getInstance()->unionBean->role = role->getValue();
//    }
//    if (i!=NULL) {
//        MyGameInfo::getInstance()->unionBean->unionId = i->getValue();
//    }
//}

bool UnionTrigger::onRegist() {
    return true;
}

bool UnionTrigger::onUnRegist() {
    return false;
}