//
//  LoginTrigger.cpp
//  ww4
//
//  Created by xiao tang on 13-4-26.
//
//

#include "LoginTrigger.h"
#include "ServerScene.h"
#include "GXMessage.h"
#include "DefineSet.h"
#include "MyUtil.h"
#include "PulsarNative.h"
#include "PushTrigger.h"
#include "MyHttpConnection.h"
#include "GXChatHandler.h"
#include "ThirdLoginCallBackMessage.h"


LoginTrigger* LoginTrigger::create(CCNode* _scene) {
    LoginTrigger* trigger = new LoginTrigger();
    trigger->scene = _scene;
    trigger->autorelease();
    return trigger;
}

bool LoginTrigger::excuteMsg(MyBaseMessage* msg) {
    if(msg->tag == userMessageTag) {
        GXMessage* uMsg = (GXMessage*)(msg);
        if (uMsg->getCmd()->compare("login") == 0) {
            if (uMsg->succ) {
                
                char str[30] = {0};
                
                if (!((ServerScene*)scene)->isFast) {
                    //缓存上次登陆信息 信息有变
                    
                    
                    //                    PulsarNative::setItitaId(((ServerScene*)scene)->loginUsernameTextField->getString());
                    sprintf(str,"s%d_ititaId",((ServerScene*)scene)->cacheServerId);
                    CCUserDefault::sharedUserDefault()->setStringForKey(str,((ServerScene*)scene)->loginUsernameTextField->getString());
                    sprintf(str,"s%d_password",((ServerScene*)scene)->cacheServerId);
                    CCUserDefault::sharedUserDefault()->setStringForKey(str,((ServerScene*)scene)->loginPasswordTextField->getString());
                    sprintf(str,"s%d_nickname",((ServerScene*)scene)->cacheServerId);
                    CCUserDefault::sharedUserDefault()->setStringForKey(str,uMsg->getMsg()->getCString());
                    CCUserDefault::sharedUserDefault()->flush();
                } else {
                    //设置缓存ITITAID
                    
                    sprintf(str,"s%d_ititaId",((ServerScene*)scene)->cacheServerId);
                    //                    PulsarNative::setItitaId(CCUserDefault::sharedUserDefault()->getStringForKey(str,""));
                    sprintf(str,"s%d_nickname",((ServerScene*)scene)->cacheServerId);
                    CCUserDefault::sharedUserDefault()->setStringForKey(str,uMsg->getMsg()->getCString());
                    CCUserDefault::sharedUserDefault()->flush();
                }
                MyJsonUtil::parseLoginInfo(uMsg->getDetail());
                ((ServerScene*)scene)->toStartScene();
                //登陆成功，登陆聊天服务器
                GXChatHandler::getInstance()->startPomelo(((ServerScene*)scene)->getCacheChatServerUrl()->getCString());
            } else {
                ((ServerScene*)scene)->removeChildByTag(waitMenuTag,true);
                ((ServerScene*)scene)->addChild(MyUtil::getInstance()->getServerTipDialog(uMsg->getMsg()->getCString()),10);
                ((ServerScene*)scene)->isFast = false;
                
                PushTrigger::getInstance()->connectCode = doNothingTag;
                MyHttpConnection::getInstance()->sendDisconnect();
            }
        } else if(uMsg->getCmd()->compare("loginNoRegister") == 0) {
            if (uMsg->succ) {
                char str[30] = {0};
                sprintf(str,"s%d_nickname",((ServerScene*)scene)->cacheServerId);
                CCUserDefault::sharedUserDefault()->setStringForKey(str,uMsg->getMsg()->getCString());
                CCUserDefault::sharedUserDefault()->flush();
                MyJsonUtil::parseLoginInfo(uMsg->getDetail());
                ((ServerScene*)scene)->toStartScene();
                //登陆成功，登陆聊天服务器
                GXChatHandler::getInstance()->startPomelo(((ServerScene*)scene)->getCacheChatServerUrl()->getCString());
            } else {
                ((ServerScene*)scene)->removeChildByTag(waitMenuTag,true);
                ((ServerScene*)scene)->addChild(MyUtil::getInstance()->getServerTipDialog(uMsg->getMsg()->getCString()),10);
                
                PushTrigger::getInstance()->connectCode = doNothingTag;
                MyHttpConnection::getInstance()->sendDisconnect();
            }
        } else if(uMsg->getCmd()->compare("register") == 0) {
            if (uMsg->succ) {
                
                char str[30] = {0};
                
                //                PulsarNative::setItitaId(((ServerScene*)scene)->registerUsernameTextField->getString());
                //缓存上次登陆信息
                sprintf(str,"s%d_ititaId",((ServerScene*)scene)->cacheServerId);
                CCUserDefault::sharedUserDefault()->setStringForKey(str,((ServerScene*)scene)->registerUsernameTextField->getString());
                sprintf(str,"s%d_password",((ServerScene*)scene)->cacheServerId);
                CCUserDefault::sharedUserDefault()->setStringForKey(str,((ServerScene*)scene)->registerPasswordTextField->getString());
                sprintf(str,"s%d_nickname",((ServerScene*)scene)->cacheServerId);
                CCUserDefault::sharedUserDefault()->setStringForKey(str,((ServerScene*)scene)->registerNicknameTextField->getString());
                CCUserDefault::sharedUserDefault()->flush();
                MyJsonUtil::parseLoginInfo(uMsg->getDetail());
                //进入游戏场景
                ((ServerScene*)scene)->toStartScene();
                //登陆成功，登陆聊天服务器
                GXChatHandler::getInstance()->startPomelo(((ServerScene*)scene)->getCacheChatServerUrl()->getCString());
            } else {
                ((ServerScene*)scene)->removeChildByTag(waitMenuTag,true);
                ((ServerScene*)scene)->addChild(MyUtil::getInstance()->getServerTipDialog(uMsg->getMsg()->getCString()),10);
                
                PushTrigger::getInstance()->connectCode = doNothingTag;
                MyHttpConnection::getInstance()->sendDisconnect();
            }
        } else if(uMsg->getCmd()->compare("commonThirdRegisterOrLogin") == 0) {
            if (uMsg->succ) {
				char str[30] = {0};
				sprintf(str,"s%d_nickname",((ServerScene*)scene)->cacheServerId);
				CCUserDefault::sharedUserDefault()->setStringForKey(str,uMsg->getMsg()->getCString());
				CCUserDefault::sharedUserDefault()->flush();
				MyJsonUtil::parseLoginInfo(uMsg->getDetail());
				((ServerScene*)scene)->toStartScene();
				//登陆成功，登陆聊天服务器
				GXChatHandler::getInstance()->startPomelo(((ServerScene*)scene)->getSelectBean()->getChatServerUrl()->getCString());
			} else {
				((ServerScene*)scene)->removeChildByTag(waitMenuTag,true);
				((ServerScene*)scene)->addChild(MyUtil::getInstance()->getServerTipDialog("服务器异常，\n请稍候重试。"),10);
				PushTrigger::getInstance()->connectCode = doNothingTag;
				MyHttpConnection::getInstance()->sendDisconnect();
			}
        }
        return false;
    } else if(msg->tag == ThirdLoginCallBackMessageTag) {
        //    	CCLog("过来了：");
		ThirdLoginCallBackMessage* uMsg = (ThirdLoginCallBackMessage*)(msg);
		if(uMsg->userId>0){
			if (MyHttpConnection::getInstance()->initSocket(((ServerScene*)scene)->getSelectBean()->getHostUrl()->getCString(),((ServerScene*)scene)->getSelectBean()->serverId)) {
                
                //                setCacheChatServerUrl(selectBean->getChatServerUrl());
				char str[30] = {0};
				int serverId = ((ServerScene*)scene)->getSelectBean()->serverId;
				sprintf(str,"s%d_ititaId",serverId);
				CCUserDefault::sharedUserDefault()->setIntegerForKey(str,uMsg->userId);
				CCUserDefault::sharedUserDefault()->flush();
				MyHttpConnection::getInstance()->commonThirdRegisterOrLogin(uMsg->userId,false);
                
			} else {
				scene->removeChildByTag(waitMenuTag,true);
				scene->addChild(MyUtil::getInstance()->getServerTipDialog("服务器连接异常\n请检查网络后重试"),10);
			}
            
        } else if(uMsg->userId == -1){
        	((ServerScene*)scene)->removeChildByTag(waitMenuTag,true);
			((ServerScene*)scene)->addChild(MyUtil::getInstance()->getServerTipDialog("登陆失败，请检测网络，\n账户和密码是否正确"),10);
            
        } else {
        	((ServerScene*)scene)->removeChildByTag(waitMenuTag,true);
            
        }
    }
    return false;
}

bool LoginTrigger::onRegist() {
    return true;
}

bool LoginTrigger::onUnRegist() {
    return true;
}
