//
//  LoadingScene.cpp
//  ww2
//
//  Created by DingYu Fu on 12-9-16.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "LoadingScene.h"
#include "MyHttpConnection.h"
#include "PulsarNative.h"
//#include "MyJsonUtil.h"
//#include "MyUtil.h"
//#include "MyGameInfo.h"
//#include "DefineSet.h"
#include "SimpleAudioEngine.h"
#include "NewbieStartScene.h"
#include "MyGameFactory.h"
#include "MyMessageManage.h"
//#include "NewbieMovieScene.h"
#include "PushTrigger.h"
#include "GXResourceLoader.h"
#if game_style == ezzhg
#include "ServerScene2.h"
#endif
#if game_style == ezqx
#include "ServerScene.h"
#endif
#if game_style == ezzhgThird
#include "ThirdServerScene.h"
#endif

#include "QuestManager.h"
#include "GXChatHandler.h"

#define tipString1  "小提示：抓小偷每隔30分钟会翻一倍\n倍数可以累计至等级上限"
#define tipString2  "小提示：反坦克炮和碉堡混合使用\n才能发挥出最大的防御力。"
#define tipString3  "小提示：击垮敌军基地即可获得胜利\n寻找敌人最薄弱的位子猛烈攻击。"
#define tipString4  "小提示：不同兵种对应不同的防御\n配合才是王道。"
#define tipString5  "小提示：二战前线官方群：279759221\n寻找一起玩的战友。"
#define tipString6  "小提示：点击外交进入论坛\n可以切换账号，修改昵称。"
#define tipString7  "小提示：修复破损的联络中心\n就可以加入各大联盟，或者自立门户。"
#define tipString8  "小提示：建造回收中心，\n回收敌方进攻者的资源。"
#define tipString9  "小提示：防守战每隔30分钟提升一级，\n击败满级敌军敌人就会更强"
#define tipString10  "小提示：官方网站：17erzhan.com\n新手指南,游戏资料,应有尽有"

bool LoadingScene::isLoaded = false;

bool LoadingScene::init() {
    CCSize winsize = CCDirector::sharedDirector()->getWinSize();
   
//    if (CCUserDefault::sharedUserDefault()->getBoolForKey("newbieTag",false)) {
        CCLayer* backLayer = CCLayer::create();
        CCSprite* background = CCSprite::create("loading.jpg");
        //    background->setScale(winsize.height/background->getContentSize().height);
        background->setAnchorPoint(ccp(0.5,0.5));
        background->setPosition(ccp(winsize.width/2,winsize.height/2));
        
        backLayer->addChild(background);
        this->addChild(backLayer);
        
        CCLabelTTF* label = CCLabelTTF::create("正在加载，请稍后", "Arial", 30);
        label->setAnchorPoint(ccp(1,0.5));
        label->setPosition(ccp(winsize.width-100,30));
        
        int rand = arc4random()%10;
        CCLabelTTF* TIP = NULL;
        if (rand == 0) {
            TIP = CCLabelTTF::create(tipString1, "Arial", 35);
        } else if(rand == 1) {
            TIP = CCLabelTTF::create(tipString2, "Arial", 35);
        } else if(rand == 2) {
            TIP = CCLabelTTF::create(tipString3, "Arial", 35);
        } else if(rand == 3) {
            TIP = CCLabelTTF::create(tipString4, "Arial", 35);
        } else if(rand == 4) {
            TIP = CCLabelTTF::create(tipString5, "Arial", 35);
        } else if(rand == 5) {
            TIP = CCLabelTTF::create(tipString6, "Arial", 35);
        } else if(rand == 6) {
            TIP = CCLabelTTF::create(tipString7, "Arial", 35);
        } else if(rand == 7) {
            TIP = CCLabelTTF::create(tipString8, "Arial", 35);
        } else if(rand == 8) {
            TIP = CCLabelTTF::create(tipString9, "Arial", 35);
        } else if(rand == 9) {
            TIP = CCLabelTTF::create(tipString10, "Arial", 35);
        }
        TIP->setAnchorPoint(ccp(0.5,0.5));
        TIP->setPosition(ccp(winsize.width/2,100));
        
        CCSprite* back = CCSprite::create("whiteImage.jpg");
        back->setColor(ccc3(0,0,0));
        back->setScaleX((TIP->getContentSize().width+20)/back->getContentSize().width);
        back->setScaleY((TIP->getContentSize().height+20)/back->getContentSize().height);
        back->setPosition(ccp(winsize.width/2,100));
        back->setOpacity(150);
        
        CCSprite* logo = CCSprite::create("logo.png");
    //    logo->setScale((TIP->getContentSize().width+20)/back->getContentSize().width);
#if game_style == ezzhg
    logo->setPosition(ccp(winsize.width/2,winsize.height-200));
#endif
#if game_style == ezzhgThird
    logo->setPosition(ccp(winsize.width/2,winsize.height-200));
#endif
#if game_style == ezqx
    logo->setPosition(ccp(0,winsize.height));
    logo->setScale(0.9);
    logo->setAnchorPoint(ccp(0,1));
#endif
        
        
        backLayer->addChild(label);
        backLayer->addChild(back);
        backLayer->addChild(TIP);
        backLayer->addChild(logo);
//    }
    
//    backLayer->setPosition(ccp(winsize.width/2,winsize.height/2));
    
    MyMessageManage::getInstance();
//    CCUserDefault::sharedUserDefault()->setBoolForKey("newbieTag", true);
//    isConn = false;
    return true;
}

void LoadingScene::loadingReplace() {
//    CCTextureCache::sharedTextureCache()->dumpCachedTextureInfo();
//    return;
    if (!CCUserDefault::sharedUserDefault()->getBoolForKey("newbieTag",false)) {
        NewbieStartSceneCreator* creator = (NewbieStartSceneCreator*)MyGameFactory::createCreatorbyJsonScriptFile("NewbieBase.j",NewbieStartSceneClassTag);
        NewbieStartScene* startScene = (NewbieStartScene*)creator->creatObj();
        MyGameFactory::creatorMap->removeObjectForKey("NewbieBase.j");
        CCDirector::sharedDirector()->replaceScene(startScene);
    } else {
//        MyGameInfo::getInstance()->clear();
//        MyGameInfo::getInstance()->creatorArray->removeAllObjects();
//        PushTrigger::getInstance()->clear();
//        QuestManager::getInstance()->clear();
        
#if game_style == ezzhg
        CCDirector::sharedDirector()->replaceScene(ServerScene2::create());
#endif
#if game_style == ezzhgThird
        CCDirector::sharedDirector()->replaceScene(ThirdServerScene::create());
#endif
#if game_style == ezqx
        CCDirector::sharedDirector()->replaceScene(ServerScene::create());
#endif
//        MyGameInfo::getInstance()->clear();
//        //获得游戏基础数据
//        CCString* response = MyHttpConnection::getInstance()->getStartSceneData(true);
//
//        
//        
//        if (response->compare( "SB") == 0) {
//            MyGameInfo::getInstance()->setIron(2000);
//            MyGameInfo::getInstance()->setOil(2000);
//            MyGameFactory::createCreatorbyJsonScriptFile("garade.j", unitCreatorClassTag);
//            MyGameInfo::getInstance()->creatorArray->addObject(CreatorInfoBean::create(CCString::create("garade.j")));
//            MyGameFactory::createCreatorbyJsonScriptFile("M5Stuart.j", unitCreatorClassTag);
//            MyGameInfo::getInstance()->creatorArray->addObject(CreatorInfoBean::create(CCString::create("M5Stuart.j")));
//            
//            
//            
//            
//            //    NewbieMoveSceneCreator* creator = (NewbieMoveSceneCreator*)MyGameFactory::createCreatorbyJsonScriptFile("NewbieBase.j",NewbieMovieSceneClassTag);
//            //    CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(1.0, (NewbieMovieScene*)creator->creatObj(), ccWHITE));
//            
//            
//            //获得网名
//            MyGameInfo::getInstance()->setNickName(CCString::create(MyUtil::getInstance()->getNickNamebyNet()));
//            StartScene* startScene = StartScene::create();
//            MyMap* map = dynamic_cast<MyMap*>(startScene->getChildByTag(MainMapTag));
//            if (!MyHttpConnection::getInstance()->createAccount(MyJsonUtil::packAllBuilding(map->getItems()))) {
//                this->addChild(MyUtil::getInstance()->getNetworkDialog());
//                this->removeChildByTag(waitMenuTag, true);
//            };
//            
//            
//            //初始化SOCKET
//            MyHttpConnection::getInstance()->initSSL();
//            MyGameInfo::getInstance()->getXmppHandler()->startThread();
//            CCDirector::sharedDirector()->replaceScene(startScene);
//        } else if(response->compare( "failed") == 0 || response->compare( "\0") == 0) {
//            this->addChild(MyUtil::getInstance()->getNetworkDialog());
//            this->removeChildByTag(waitMenuTag, true);
//            //        isConn = true;
//        } else {
//            CCDirector::sharedDirector()->replaceScene(MyJsonUtil::parseNativeInfo(response));
//            MyHttpConnection::getInstance()->initSSL();
//            MyGameInfo::getInstance()->getXmppHandler()->startThread();
//        }
    }
}

void LoadingScene::loadPublicResource() {
    if (isLoaded) {
        loadingReplace();
        return;
    }
#if(CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    PulsarNative::setServerInfoStr();
#endif
    CCTexture2D::PVRImagesHavePremultipliedAlpha(true);
    CCArray* fileArray = CCArray::create();
    fileArray->addObject(CCString::create("dialog"));
    fileArray->addObject(CCString::create("buildings"));
    fileArray->addObject(CCString::create("rank"));
    fileArray->addObject(CCString::create("resourceIcon"));
    fileArray->addObject(CCString::create("ui"));
    fileArray->addObject(CCString::create("buildstruct"));
    fileArray->addObject(CCString::create("ornaments"));
    fileArray->addObject(CCString::create("ruins"));
    fileArray->addObject(CCString::create("uizhuangshi"));
    fileArray->addObject(CCString::create("deployBack"));
    fileArray->addObject(CCString::create("background"));
    fileArray->addObject(CCString::create("uiDialogCommon"));
    fileArray->addObject(CCString::create("unionEmblem"));
    fileArray->addObject(CCString::create("avatar"));
    
    GXResourceLoader::create(fileArray,0.05,this,callfunc_selector(LoadingScene::loadingReplace));
    isLoaded = true;
    
//    GXUtil::loadResourceUtilSucc("dialog.plist","dialog.pvr.ccz");
//    GXUtil::loadResourceUtilSucc("buildings.plist","buildings.pvr.ccz");
////    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("diaobao1.plist","diaobao1.pvr.ccz");
////    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("dapao1.plist","dapao1.pvr.ccz");
////    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("antiTank.plist","antiTank.pvr.ccz");
////    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("tiparrow.plist","tiparrow.pvr.ccz");
////    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("tank1.plist","tank1.pvr.ccz");
//    GXUtil::loadResourceUtilSucc("rank.plist","rank.pvr.ccz");
//    
////    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("crowellmk4.plist","crowellmk4.pvr.ccz");
//    
//    
////    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("bubing1.plist", "bubing1.pvr.ccz");
//    
////    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("collapse.plist","collapse.pvr.ccz");
//    
////    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("creatorui.plist","creatorui.pvr.ccz");
//    
////    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("microboom1.plist","microboom1.pvr.ccz");
//    
//    
////    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("boom.plist","boom.pvr.ccz");
////    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("antitankBoom.plist","antitankBoom.png");
//    GXUtil::loadResourceUtilSucc("resourceIcon.plist","resourceIcon.pvr.ccz");
//    GXUtil::loadResourceUtilSucc("ui.plist","ui.pvr.ccz");
//    GXUtil::loadResourceUtilSucc("buildstruct.plist","buildstruct.pvr.ccz");
//    GXUtil::loadResourceUtilSucc("ornaments.plist","ornaments.pvr.ccz");
////    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("tipTiled.plist", "tipTiled.pvr.ccz");
//    GXUtil::loadResourceUtilSucc("ruins.plist", "ruins.pvr.ccz");
////    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("chardialog.plist","chardialog.pvr.ccz");
//    GXUtil::loadResourceUtilSucc("uizhuangshi.plist","uizhuangshi.pvr.ccz");
//    GXUtil::loadResourceUtilSucc("deployBack.plist","deployBack.pvr.ccz");
//    GXUtil::loadResourceUtilSucc("background.plist","background.pvr.ccz");
//    GXUtil::loadResourceUtilSucc("uiDialogCommon.plist","uiDialogCommon.pvr.ccz");
//    GXUtil::loadResourceUtilSucc("unionEmblem.plist","unionEmblem.pvr.ccz");
//    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("recordui.plist","recordui.pvr.ccz");
    //加载战斗背景音乐
    CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic("bgm_battleScene.mp3");
    CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic("bgm_startScene.mp3");
    CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect("sfx_win.mp3");
    //loading startscene初始场景的数据
}

void LoadingScene::releaseResource() {
    CCTextureCache::sharedTextureCache()->removeTextureForKey("loading.jpg");
    CCTextureCache::sharedTextureCache()->removeTextureForKey("logo.png");
}

//void LoadingScene::loadStartResource() {
//    
//    CCArray* fileArray = CCArray::create();
//    fileArray->addObject(CCString::create("createui"));
//    fileArray->addObject(CCString::create("tipTiled"));
//    fileArray->addObject(CCString::create("armyui"));
//    fileArray->addObject(CCString::create("armyui2"));
//    fileArray->addObject(CCString::create("chardialog"));
//    fileArray->addObject(CCString::create("recordui"));
//    fileArray->addObject(CCString::create("normalButton"));
//    fileArray->addObject(CCString::create("antiTank"));
//    fileArray->addObject(CCString::create("armycardflop"));
//    fileArray->addObject(CCString::create("startSceneIcon"));
//    fileArray->addObject(CCString::create("huodong"));
//    fileArray->addObject(CCString::create("shopUI"));
//    fileArray->addObject(CCString::create("unionUI"));
//    fileArray->addObject(CCString::create("shopUI8888"));
//    fileArray->addObject(CCString::create("avatar"));
//    
//    GXResourceLoader::create(fileArray,0.05,this,callfunc_selector(LoadingScene::loadingReplace));
//    
////    GXUtil::loadResourceUtilSucc("createui.plist","createui.pvr.ccz");
////    GXUtil::loadResourceUtilSucc("tipTiled.plist","tipTiled.pvr.ccz");
////    GXUtil::loadResourceUtilSucc("armyui.plist","armyui.pvr.ccz");
////    GXUtil::loadResourceUtilSucc("armyui2.plist","armyui2.pvr.ccz");
////    GXUtil::loadResourceUtilSucc("chardialog.plist","chardialog.pvr.ccz");
////    GXUtil::loadResourceUtilSucc("recordui.plist","recordui.pvr.ccz");
////    GXUtil::loadResourceUtilSucc("normalButton.plist","normalButton.pvr.ccz");
////    GXUtil::loadResourceUtilSucc("antiTank.plist","antiTank.pvr.ccz");
////    GXUtil::loadResourceUtilSucc("armycardflop.plist","armycardflop.pvr.ccz");
////    GXUtil::loadResourceUtilSucc("startSceneIcon.plist","startSceneIcon.pvr.ccz");

////    GXUtil::loadResourceUtilSucc("huodong.plist","huodong.pvr.ccz");
////    GXUtil::loadResourceUtilSucc("unionUI.plist","unionUI.pvr.ccz");
////    GXUtil::loadResourceUtilSucc("shopUI.plist","shopUI.pvr.ccz");
////    GXUtil::loadResourceUtilSucc("shopUI8888.plist","shopUI8888.pvr.ccz");
////    GXUtil::loadResourceUtilSucc("avatar.plist","avatar.pvr.ccz");
//}

void LoadingScene::onEnterTransitionDidFinish() {
    CCScene::onEnterTransitionDidFinish();
    this->scheduleOnce(schedule_selector(LoadingScene::loadPublicResource), 0.05);
}