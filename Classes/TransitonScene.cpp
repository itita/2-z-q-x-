 //
//  TransitonScene.cpp
//  ww3
//
//  Created by xiao tang on 12-12-21.
//
//

//#define game_style EZQX //EZZHG

#include "TransitonScene.h"
#include "DefineSet.h"
#include "MyHttpConnection.h"
#include "MyUtil.h"
#include "MyJsonUtil.h"
#include "NewbieBattleScene.h"
#include "NewbieMovieScene.h"
#include "MyGameFactory.h"
#include "NewbieReadyScene.h"
#include "TestScene.h"
#include "ChthiefScene.h"
#include "ThiefScene.h"
#if game_style == ezqx
#include "ServerScene.h"
#endif
#if game_style == ezzhg
#include "ServerScene2.h"
#endif
#if game_style == ezzhgThird
#include "ThirdServerScene.h"
#endif
#include "DefendScene.h"
#include "PushTrigger.h"
#include "QuestManager.h"
#include "PulsarNative.h"

TransitonScene::~TransitonScene() {
    CCLog("transitonScene has release");
//    CC_SAFE_RELEASE_NULL(tempScene);
    if (trigger != NULL) {
        MyMessageManage::getInstance()->unRegisterTrigger(trigger);
        CC_SAFE_RELEASE(trigger);
    }
    CC_SAFE_RELEASE_NULL(data);
}

TransitonScene* TransitonScene::create(int sceneTag,CCObject* response){
    TransitonScene* t = new TransitonScene();
    t->init();
    t->data = response;
    t->data->retain();
    t->autorelease();
    t->toSceneTag = sceneTag;
    CCSprite* sprite = CCSprite::create("whiteImage.jpg");
    sprite->setColor(ccc3(0,0,0));
    sprite->setScaleX(winSize.width/sprite->getContentSize().width);
    sprite->setScaleY(winSize.height/sprite->getContentSize().height);
    sprite->setPosition(ccp(winSize.width/2,winSize.height/2));
    t->addChild(sprite);
    
    CCSprite* sprite2 = CCSprite::create("transitionTip.png");
    sprite2->setAnchorPoint(ccp(0.5,0));
    sprite2->setPosition(ccp(winSize.width/2,50));
    sprite2->setOpacity(0);
    sprite2->runAction(CCSequence::create(CCDelayTime::create(0.5),CCFadeIn::create(0.1),NULL));
    t->addChild(sprite2);
//    if (sceneTag == battleSceneTag) {
//        t->addChild(MyUtil::getInstance()->getScanEnemyLayer());
//    } else {
        t->addChild(MyUtil::getInstance()->getWaitLayer(""));
//    }
    CCLabelTTF* waitLabel = CCLabelTTF::create("努力加载中", "Arial",30);
    waitLabel->setPosition(ccp(winSize.width/2,winSize.height/2-50));

    waitLabel->setOpacity(0);
    waitLabel->runAction(CCSequence::create(CCDelayTime::create(0.1),CCFadeIn::create(0.1),NULL));
    t->addChild(waitLabel);
    
    return t;
}

TransitonScene* TransitonScene::create(int sceneTag) {
    TransitonScene* t = new TransitonScene();
    t->init();
    t->autorelease();
    t->toSceneTag = sceneTag;
//    t->scheduleOnce(schedule_selector(TransitonScene::toChangeScene), 0.5);
    CCSprite* sprite = CCSprite::create("whiteImage.jpg");
    sprite->setColor(ccc3(0,0,0));
    sprite->setScaleX(winSize.width/sprite->getContentSize().width);
    sprite->setScaleY(winSize.height/sprite->getContentSize().height);
    sprite->setPosition(ccp(winSize.width/2,winSize.height/2));
    t->addChild(sprite);
    
    CCSprite* sprite2 = CCSprite::create("transitionTip.png");
    sprite2->setAnchorPoint(ccp(0.5,0));
    sprite2->setPosition(ccp(winSize.width/2,50));
    sprite2->runAction(CCSequence::create(CCDelayTime::create(0.5),CCFadeIn::create(0.1),NULL));
    sprite2->setOpacity(0);
    t->addChild(sprite2);
//    if (sceneTag == ReadyToBattleTag) {
//        t->addChild(MyUtil::getInstance()->getScanEnemyLayer());
//    } else {
        t->addChild(MyUtil::getInstance()->getWaitLayer(""));
//    }
    
    CCLabelTTF* waitLabel = CCLabelTTF::create("努力加载中", "Arial",30);
    waitLabel->setPosition(ccp(winSize.width/2,winSize.height/2-50));
    
    waitLabel->setOpacity(0);
    waitLabel->runAction(CCSequence::create(CCDelayTime::create(0.1),CCFadeIn::create(0.1),NULL));
    t->addChild(waitLabel);
    return t;
}

void TransitonScene::toChangeScene() {
    if (toSceneTag == battleSceneTag) {
        MyHttpConnection::getInstance()->sendGetOthers(((CCInteger*)data)->getValue());
        CC_SAFE_RELEASE_NULL(data);
        this->schedule(schedule_selector(TransitonScene::toBattleSceneWait));
    } else if (toSceneTag == battleSceneBySearchTag) {
        MyHttpConnection::getInstance()->sendGetOthers(((CCInteger*)data)->getValue(),true);
        CC_SAFE_RELEASE_NULL(data);
        this->schedule(schedule_selector(TransitonScene::toBattleSceneWait));
    }  else  if (toSceneTag == defendSceneTag) {
        MyHttpConnection::getInstance()->sendGetDefend(((CCInteger*)data)->getValue());
        CC_SAFE_RELEASE_NULL(data);
        this->schedule(schedule_selector(TransitonScene::toDefendSceneWait));
    } else if (toSceneTag == startSceneTag) {
        if (data == NULL) {
            MyHttpConnection::getInstance()->sendGetGameData(false);
        } else {
            MyHttpConnection::getInstance()->sendGetGameData(true);
        }
        CC_SAFE_RELEASE_NULL(data);
        this->schedule(schedule_selector(TransitonScene::toStartSceneWait));
    } else if (toSceneTag == NewbieBattleSceneClassTag) {
        NewbieBattleSceneCreator* creator = (NewbieBattleSceneCreator*)MyGameFactory::createCreatorbyJsonScriptFile(((CCString*)data)->getCString(),NewbieBattleSceneClassTag);
        NewbieBattleScene* battleScene = (NewbieBattleScene*)creator->creatObj();
        MyGameFactory::creatorMap->removeObjectForKey(((CCString*)data)->getCString());
        CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.2, battleScene, ccBLACK));
        
    } else if (toSceneTag == NewbieStartSceneClassTag) {
        

    }else if (toSceneTag == NewbieMovieSceneClassTag) {
        NewbieMoveSceneCreator* creator = (NewbieMoveSceneCreator*)MyGameFactory::createCreatorbyJsonScriptFile(((CCString*)data)->getCString(),NewbieMovieSceneClassTag);
        CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.2, (NewbieMovieScene*)creator->creatObj(), ccBLACK));
        MyGameFactory::creatorMap->removeObjectForKey(((CCString*)data)->getCString());
    }else if (toSceneTag == ReadyToBattleTag) {
        MyHttpConnection::getInstance()->sendGetGameDataList();
//        CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.2, TestScene::create(), ccBLACK));
    }else if(toSceneTag == NewbieReadySceneClassTag) {
        CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.2, NewbieReadyScene::create(), ccBLACK));
    }else if(toSceneTag == ChthiefSceneClassTag ) {
         MyHttpConnection::getInstance()->sendGetRobInfo();
    }else if(toSceneTag == ServerSceneTag ) {
//        MyGameInfo::getInstance()->clear();
//        MyGameInfo::getInstance()->creatorArray->removeAllObjects();
//        PushTrigger::getInstance()->clear();
//        QuestManager::getInstance()->clear();
#if game_style == ezzhg
        ServerScene2* scene = ServerScene2::create();
#endif
#if game_style == ezzhgThird
        ThirdServerScene* scene = ThirdServerScene::create();
#endif
#if game_style == ezqx
        ServerScene* scene = ServerScene::create();
#endif

        
        if (data && ((CCString*)data)->compare("") != 0) {
            scene->addChild(MyUtil::getInstance()->getServerTipDialog(((CCString*)data)->getCString()),10);
        }
//
        CCDirector::sharedDirector()->replaceScene(scene);
    } else {
        CCAssert(1 == 2, "SCENE TAG IS WRONG");
    }
//    unscheduleAllSelectors();
//    stopAllActions();
//    CCLog("一次");
}

void TransitonScene::onEnterTransitionDidFinish() {
    GXBaseScene::onEnterTransitionDidFinish();
    this->runAction(CCSequence::create(CCDelayTime::create(0.5),CCCallFunc::create(this, callfunc_selector(TransitonScene::toChangeScene)),NULL));
//   this->scheduleOnce(schedule_selector(TransitonScene::toChangeScene), 0.5);
}

void TransitonScene::toStartSceneWait() {
    if (step == 0) {
        CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("createui.plist","createui.pvr.ccz");
        if(CCTextureCache::sharedTextureCache()->textureForKey("createui.pvr.ccz") !=NULL) {
            step++;
        };
    } else if(step == 1) {
        CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("tipTiled.plist", "tipTiled.pvr.ccz");
        if(CCTextureCache::sharedTextureCache()->textureForKey("tipTiled.pvr.ccz") != NULL) {
            step++;
        };
    } else if(step == 2) {
        CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("armyui.plist", "armyui.pvr.ccz");
        if(CCTextureCache::sharedTextureCache()->textureForKey("armyui.pvr.ccz") != NULL) {
            step++;
        }
    } else if(step == 3) {
        CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("armyui2.plist", "armyui2.pvr.ccz");
        if(CCTextureCache::sharedTextureCache()->textureForKey("armyui2.pvr.ccz") != NULL) {
            step++;
        }
    } else if(step == 4) {
        CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("chardialog.plist","chardialog.pvr.ccz");
        if(CCTextureCache::sharedTextureCache()->textureForKey("chardialog.pvr.ccz") != NULL) {
            step++;
        }else {
            CCAssert(1 == 2,"读取不成功，重试");
        };
    } else if(step == 5) {
        CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("recordui.plist","recordui.pvr.ccz");
        if(CCTextureCache::sharedTextureCache()->textureForKey("recordui.pvr.ccz") != NULL) {
            step++;
        }else {
            CCAssert(1 == 2,"读取不成功，重试");
        };
    } else if(step == 6) {
        CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("normalButton.plist","normalButton.pvr.ccz");
        if(CCTextureCache::sharedTextureCache()->textureForKey("normalButton.pvr.ccz") != NULL) {
            step++;
        }
    } else if(step == 7) {
        CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("antiTank.plist","antiTank.png");
        if(CCTextureCache::sharedTextureCache()->textureForKey("antiTank.png") != NULL) {
            step++;
        }
    } else if(step == 8) {
        CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("armycardflop.plist","armycardflop.pvr.ccz");
        if(CCTextureCache::sharedTextureCache()->textureForKey("armycardflop.pvr.ccz") != NULL) {
            step++;
        }
    } else if(step == 9) {
        CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("startSceneIcon.plist","startSceneIcon.pvr.ccz");
        if(CCTextureCache::sharedTextureCache()->textureForKey("startSceneIcon.pvr.ccz") != NULL) {
            step++;
        }
    }else if(step == 10) {
        CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("huodong.plist","huodong.pvr.ccz");
        if(CCTextureCache::sharedTextureCache()->textureForKey("huodong.pvr.ccz") != NULL) {
            step++;
        }
    }else if(step == 11) {
        CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("unionUI.plist","unionUI.pvr.ccz");
        if(CCTextureCache::sharedTextureCache()->textureForKey("unionUI.pvr.ccz") != NULL) {
            step++;
        }
    }else if(step == 12) {
        CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("shopUI.plist","shopUI.pvr.ccz");
        if(CCTextureCache::sharedTextureCache()->textureForKey("shopUI.pvr.ccz") != NULL) {
            step++;
        }
    }else if(step == 13) {
        CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("shopUI8888.plist","shopUI8888.pvr.ccz");
        if(CCTextureCache::sharedTextureCache()->textureForKey("shopUI8888.pvr.ccz") != NULL) {
            step++;
        }
    }else if(step == 14) {
        CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("questUI.plist","questUI.pvr.ccz");
        if(CCTextureCache::sharedTextureCache()->textureForKey("questUI.pvr.ccz") != NULL) {
            step++;
        }
    } else if(step == 15) {
        CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("defendNormal.plist","defendNormal.pvr.ccz");
        if(CCTextureCache::sharedTextureCache()->textureForKey("defendNormal.pvr.ccz") != NULL) {
            step++;
        }
    }
    else if(step == 16) {
        step = 10001;
        this->unschedule(schedule_selector(TransitonScene::toStartSceneWait));
        
//        CCTextureCache::sharedTextureCache()->dumpCachedTextureInfo();
        
        toStartScene();
        
        
//        CCString* response = NULL;
//        if (string == NULL) {
//            response = MyHttpConnection::getInstance()->getStartSceneData();
//        } else {
//            response = string;
//        }
//        if (response->compare("failed") == 0 || response->compare("\0") == 0) {
//            this->addChild(MyUtil::getInstance()->getNetworkDialog());
//            return;
//        }
//        StartScene* scene = MyJsonUtil::parseNativeInfo(response);
//        CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.2, scene, ccBLACK));
        
        
    }
}

void TransitonScene::toStartScene() {
    if (data != NULL && step > 10000) {
        StartScene* scene = MyJsonUtil::parseNativeInfo(((CCString*)data));
        if (scene == NULL) {
            MyGameInfo::getInstance()->clear();
            MyGameInfo::getInstance()->creatorArray->removeAllObjects();
            PushTrigger::getInstance()->clear();
            QuestManager::getInstance()->clear();
            ServerScene* scene = ServerScene::create();
            if (data && ((CCString*)data)->compare("") != 0) {
                scene->addChild(MyUtil::getInstance()->getServerTipDialog("数据异常"),10);
            }
            CCDirector::sharedDirector()->replaceScene(scene);
            return;
        }
        CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.2, scene, ccBLACK));
        
    }
}



void TransitonScene::toReadytoBattleScene(CCScene* readyScene) {
    CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.2, readyScene, ccBLACK));
}


void TransitonScene::toBattleSceneWait() {
    
    //    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("tank1.plist","tank1.pvr.ccz");
    //    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("bubing1.plist", "bubing1.pvr.ccz");
   
   if(step == 0) {
        GXUtil::loadResourceUtilSucc("battleui.plist","battleui.pvr.ccz");
        step++;
    } else if(step == 1) {
        GXUtil::loadResourceUtilSucc("collapse.plist","collapse.pvr.ccz");
        step++;
    } else if(step == 2) {
        GXUtil::loadResourceUtilSucc("boom.plist","boom.pvr.ccz");
        step++;
    } else if(step == 3) {
        GXUtil::loadResourceUtilSucc("antitankBoom.plist","antitankBoom.png");
        step++;
    } else if(step == 4) {
        GXUtil::loadResourceUtilSucc("antiTankF.plist","antiTankF.png");
        step++;
    } else if(step == 5) {
        GXUtil::loadResourceUtilSucc("firelight.plist","firelight.pvr.ccz");
        step++;
    } else if(step == 6) {
        GXUtil::loadResourceUtilSucc("gunlight.plist","gunlight.pvr.ccz");
        step++;
    } else if(step == 7) {
        GXUtil::loadResourceUtilSucc("rockethead.plist","rockethead.pvr.ccz");
        step++;
    }else if(step == 8) {
        GXUtil::loadResourceUtilSucc("rockettail.plist","rockettail.pvr.ccz");
        step++;
    }else if(step == 9) {
        GXUtil::loadResourceUtilSucc("victoryui.plist","victoryui.pvr.ccz");
        step++;
    }else if(step == 10) {
        GXUtil::loadResourceUtilSucc("microboom1.plist","microboom1.pvr.ccz");
        step++;
    }else if(step == 11) {
        step = 10001;
        this->unschedule(schedule_selector(TransitonScene::toBattleSceneWait));
        
        //        CCTextureCache::sharedTextureCache()->dumpCachedTextureInfo();
        
        toBattleScene();
        
        
        //        CCString* response = NULL;
        //        if (string == NULL) {
        //            response = MyHttpConnection::getInstance()->getStartSceneData();
        //        } else {
        //            response = string;
        //        }
        //        if (response->compare("failed") == 0 || response->compare("\0") == 0) {
        //            this->addChild(MyUtil::getInstance()->getNetworkDialog());
        //            return;
        //        }
        //        StartScene* scene = MyJsonUtil::parseNativeInfo(response);
        //        CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.2, scene, ccBLACK));
        
        
    }
    
}

void TransitonScene::toBattleScene() {
    if (data != NULL && step > 10000) {
        CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.2, MyJsonUtil::parseBattleNativeInfo(((CCString*)data)), ccBLACK));
    }
}

void TransitonScene::toDefendSceneWait() {
    
    
    if(step == 0) {
        GXUtil::loadResourceUtilSucc("battleui.plist","battleui.pvr.ccz");
        step++;
    } else if(step == 1) {
        GXUtil::loadResourceUtilSucc("collapse.plist","collapse.pvr.ccz");
        step++;
    } else if(step == 2) {
        GXUtil::loadResourceUtilSucc("boom.plist","boom.pvr.ccz");
        step++;
    } else if(step == 3) {
        GXUtil::loadResourceUtilSucc("antitankBoom.plist","antitankBoom.png");
        step++;
    } else if(step == 4) {
        GXUtil::loadResourceUtilSucc("antiTankF.plist","antiTankF.png");
        step++;
    } else if(step == 5) {
        GXUtil::loadResourceUtilSucc("firelight.plist","firelight.pvr.ccz");
        step++;
    } else if(step == 6) {
        GXUtil::loadResourceUtilSucc("gunlight.plist","gunlight.pvr.ccz");
        step++;
    } else if(step == 7) {
        GXUtil::loadResourceUtilSucc("rockethead.plist","rockethead.pvr.ccz");
        step++;
    }else if(step == 8) {
        GXUtil::loadResourceUtilSucc("rockettail.plist","rockettail.pvr.ccz");
        step++;
    }else if(step == 9) {
        GXUtil::loadResourceUtilSucc("victoryui.plist","victoryui.pvr.ccz");
        step++;
    }else if(step == 10) {
        GXUtil::loadResourceUtilSucc("microboom1.plist","microboom1.pvr.ccz");
        step++;
    }
    else if(step == 11) {
        GXUtil::loadResourceUtilSucc("defend.plist","defend.pvr.ccz");
        step++;
    }else if(step == 12) {
        step = 10001;
        this->unschedule(schedule_selector(TransitonScene::toDefendSceneWait));
        
        toDefendScene();
        
    }
    
}

void TransitonScene::toDefendScene() {
    if (data != NULL && step > 10000) {
        CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.2, MyJsonUtil::parseDefendNativeInfo(((CCString*)data)), ccBLACK));
    }
}