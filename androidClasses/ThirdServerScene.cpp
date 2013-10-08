//
//  ThirdServerScene.cpp
//  ww4
//
//  Created by xiao tang on 13-9-26.
//
//

#include "ThirdServerScene.h"
#include "GXUtil.h"
#include "defineSet.h"
#include "MyPriorityMenu.h"
#include "PulsarNative.h"
#include "MyUtil.h"
#include "GXRadioMenu.h"
#include "MyMenuItem.h"
#include "SimpleAudioEngine.h"
#include "GXShieldTouchMenuItem.h"
#include "GXUtil.h"
#include "MyHttpConnection.h"
#include "LoginTrigger.h"
#include "TransitonScene.h"
#include "PushTrigger.h"
#include "GXRemoveFromParentsAction.h"
#include "QuestManager.h"
#include "ServerSelectScroll2.h"


#define loginLayerTag 10
#define loginDisplayLayerTag 11
#define displayJiemianLayerTag 12
#define serverInfoLayerTag 16



ThirdServerScene* ThirdServerScene::create() {
    ThirdServerScene* scene = new ThirdServerScene();
    scene->autorelease();
    scene->loadResource();
#if(CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    if(strcmp("update",PulsarNative::getServerInfos()) == 0) {
        scene->addChild(MyUtil::getInstance()->getServerTipDialog("二战前线已发布最新版\n请更新后重进！",scene,menu_selector(ServerScene::updateGame)),5);
        return scene;
    }
#endif
    scene->beans = MyJsonUtil::parseServerInfo();
    CC_SAFE_RETAIN(scene->beans);
    scene->myInit();
    return scene;
}

void ThirdServerScene::myInit() {
    
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("bgm_server.mp3",true);
    
    cacheServerId = CCUserDefault::sharedUserDefault()->getIntegerForKey("serverId",-1);
    
    loginTrigger = LoginTrigger::create(this);
    loginTrigger->retain();
    MyMessageManage::getInstance()->registerTrigger(loginTrigger);
    
    CCLayer* backLayer = CCLayer::create();
    CCSprite* background = CCSprite::create("loading.jpg");
    //    background->setScale(winSize.height/background->getContentSize().height);
    background->setAnchorPoint(ccp(0.5,0));
    background->setPositionX(winSize.width/2);
    backLayer->addChild(background);
    CCSprite* logo = CCSprite::create("logo.png");
    logo->setPosition(ccp(winSize.width-190,winSize.height-120));
    backLayer->addChild(logo,2);
    
    
    CCSprite* shadow = CCSprite::createWithSpriteFrameName("serverShadow.png");
    shadow->setScale((winSize.height+10)/shadow->getContentSize().height);
    shadow->setPosition(ccp(winSize.width-138,winSize.height/2));
    backLayer->addChild(shadow);
    
    CCSprite* listLabel = CCSprite::createWithSpriteFrameName("serverListLabel.png");
    listLabel->setAnchorPoint(ccp(0,1));
    listLabel->setPosition(ccp(winSize.width-270,100));
    backLayer->addChild(listLabel,1);
    
    
    if (beans->count() == 0) {
        this->addChild(MyUtil::getInstance()->getServerTipDialog("连接服务器失败,\n请检测网络！",this,menu_selector(ServerScene::exitGame)),5);
        return;
    }
    
    SeverInfoBean* bean = NULL;
    CCObject* obj;
    CCARRAY_FOREACH(beans,obj) {
        if (cacheServerId == ((SeverInfoBean*)obj)->serverId) {
            bean = (SeverInfoBean*)obj;
            break;
        }
    }
    if (bean == NULL) {
        bean =(SeverInfoBean*) beans->objectAtIndex(beans->count()-1);
    }
    
    initServerInfo(bean);
    
    this->addChild(backLayer);
    
    
}

void ThirdServerScene::initServerInfo(SeverInfoBean* bean) {
    this->removeChildByTag(serverInfoLayerTag,true);
    selectBean = bean;
    CCLayer* serverInfoLayer = CCLayer::create();
    serverInfoLayer->setTag(serverInfoLayerTag);
    serverInfoLayer->setPosition(ccp(0,0));
    
    this->cacheServerId = bean->serverId;
    char str[30] = {0};
    
    sprintf(str,"s%d_ititaId",bean->serverId);
    std::string ititaId = CCUserDefault::sharedUserDefault()->getStringForKey(str,"");
    bool ititaIdFlag = false;
    if (ititaId.compare("") != 0 && ititaId.compare(PulsarNative::getDeviceId()) != 0) {
        ititaIdFlag = true;
    }
    
    MyMenuItem* leftButton = MyMenuItem::create(CCSprite::createWithSpriteFrameName("serverButton.png"),NULL,NULL);
    leftButton->setAnchorPoint(ccp(1,0.5));
    //    leftButton->setPosition(ccp(winSize.width+100,240));
    leftButton->setPosition(ccp(winSize.width+422,240));
    leftButton->runAction(CCSequence::create(CCDelayTime::create(0.1),CCEaseElasticOut::create(CCMoveTo::create(0.3,ccp(winSize.width+100,240)),1),NULL));
    
    CCSprite* registLabel;
    if (ititaIdFlag) {
        registLabel = CCSprite::createWithSpriteFrameName("serverSwitchLabel.png");
        leftButton->setTarget(this,menu_selector(ThirdServerScene::toLogin));
    } else {
        registLabel = CCSprite::createWithSpriteFrameName("serverBindLabel.png");
        leftButton->setTarget(this,menu_selector(ThirdServerScene::toRegister));
    }
    registLabel->setAnchorPoint(ccp(0,0.5));
    registLabel->setPosition(ccp(30,leftButton->getContentSize().height/2));
    leftButton->addChild(registLabel);
    
    
    
    MyMenuItem* rightButton = MyMenuItem::create(CCSprite::createWithSpriteFrameName("serverButton.png"),this,menu_selector(ThirdServerScene::fastEnterGameWait));
    rightButton->setAnchorPoint(ccp(1,0.5));
    //    rightButton->setPosition(ccp(winSize.width+20,330));
    rightButton->setPosition(ccp(winSize.width+342,330));
    rightButton->runAction(CCSequence::create(CCEaseElasticOut::create(CCMoveTo::create(0.3,ccp(winSize.width+20,330)),1),NULL));
    
    CCSprite* newLabel;
    if (ititaIdFlag) {
        newLabel = CCSprite::createWithSpriteFrameName("serverEnterGame.png");
    } else {
        newLabel = CCSprite::createWithSpriteFrameName("serverFastStartLabel.png");
    }
    newLabel->setAnchorPoint(ccp(0,0.5));
    newLabel->setPosition(ccp(30,rightButton->getContentSize().height/2));
    rightButton->addChild(newLabel);
    
    MyPriorityMenu* menu = MyPriorityMenu::create(-501,leftButton,rightButton,NULL);
    menu->setPosition(ccp(0,0));
    serverInfoLayer->addChild(menu);
    
//    sprintf(str,"s%d_nickname",bean->serverId);
//    std::string nickname = CCUserDefault::sharedUserDefault()->getStringForKey(str,"");
//    
//    if (nickname.compare("") != 0) {
//        CCLabelTTF* id = CCLabelTTF::create("ID:","Arial",40);
//        id->setColor(ccc3(255,222,0));
//        
//        CCLabelTTF* nicknameLabel = CCLabelTTF::create(nickname.c_str(),"Arial",40);
//        float locx = id->getContentSize().width+nicknameLabel->getContentSize().width;
//        id->setAnchorPoint(ccp(0,0.5));
//        id->setPosition(ccp(winSize.width-locx/2-180,400));
//        nicknameLabel->setAnchorPoint(ccp(0,0.5));
//        nicknameLabel->setPosition(ccp(winSize.width-locx/2+id->getContentSize().width-190,400));
//        serverInfoLayer->addChild(id);
//        serverInfoLayer->addChild(nicknameLabel);
//    }
    
    CCLayer* layer = CCLayer::create();
    
    CCLabelTTF* label = CCLabelTTF::create(bean->getServerName()->getCString(),"Arial",33);
    label->setPosition(ccp(224,2));
    layer->addChild(label);
    label->setTag(serverNameLabelTag);
    
    CCLabelTTF* stateLabel =CCLabelTTF::create(bean->getServerStatus()->getCString(),"Arial",30);
    stateLabel->setPosition(ccp(340,0));
    if (bean->getServerStatus()->compare("正常") == 0 || bean->getServerStatus()->compare("推荐") == 0) {
        stateLabel->setColor(ccc3(0,255,0));
    } else if (bean->getServerStatus()->compare("繁忙") == 0) {
        stateLabel->setColor(ccc3(255,255,0));
    } else if (bean->getServerStatus()->compare("火爆") == 0) {
        stateLabel->setColor(ccc3(167,87,168));
    } else {
        stateLabel->setColor(ccc3(166,166,166));
    }
    
    
    layer->addChild(stateLabel);
    
    CCSprite* serverBack = CCSprite::createWithSpriteFrameName("serverCurentServerBack.png");
    //    serverBack->setPosition(ccp(winSize.width+35,48));
    serverBack->setPosition(ccp(winSize.width+357,48));
    serverBack->runAction(CCSequence::create(CCDelayTime::create(0.3),CCEaseElasticOut::create(CCMoveTo::create(0.3,ccp(winSize.width+35,48)),1),NULL));
    serverBack->setAnchorPoint(ccp(1,0.5));
    serverInfoLayer->addChild(serverBack);
    
    //    layer->setPosition(ccp(winSize.width-380,45));
    layer->setPosition(ccp(winSize.width-58,45));
    layer->runAction(CCSequence::create(CCDelayTime::create(0.3),CCEaseElasticOut::create(CCMoveTo::create(0.3,ccp(winSize.width-380,45)),1),NULL));
    serverInfoLayer->addChild(layer);
    
    MyMenuItem* selectServerButton = MyMenuItem::create(CCSprite::createWithSpriteFrameName("serverButton.png"),this,menu_selector(ThirdServerScene::toServerList));
    
    CCSprite* selectServerLabel = CCSprite::createWithSpriteFrameName("serverSelectButton.png");
    selectServerLabel->setAnchorPoint(ccp(0,0.5));
    selectServerLabel->setPosition(ccp(30,rightButton->getContentSize().height/2));
    
    
    selectServerButton->setAnchorPoint(ccp(1,0.5));
    //    selectServerButton->setPosition(winSize.width+130,150);
    selectServerButton->setPosition(ccp(winSize.width+452,150));
    selectServerButton->runAction(CCSequence::create(CCDelayTime::create(0.2),CCEaseElasticOut::create(CCMoveTo::create(0.3,ccp(winSize.width+130,150)),1),NULL));
    selectServerButton->addChild(selectServerLabel);
    menu->addChild(selectServerButton);
    
    this->addChild(serverInfoLayer,2);
}


void ThirdServerScene::loadResource() {
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("server.plist","server.pvr.ccz");
}

//void ServerScene2::releaseResource() {
//    CCTextureCache::sharedTextureCache()->removeTextureForKey("loading.jpg");
//    CCTextureCache::sharedTextureCache()->removeTextureForKey("logo.png");
//    CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile("server2.plist");
//    CCTextureCache::sharedTextureCache()->removeTextureForKey("server2.pvr.ccz");
//    GarbageResourceCollection::getInstance()->GarbageCollection();
//    //    CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile("avatar.plist");
//    //    CCTextureCache::sharedTextureCache()->removeTextureForKey("avatar.pvr.ccz");
//}

#if   (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)

void ThirdServerScene::toLogin() {
	this->addChild(MyUtil::getInstance()->getWaitLayer("正在登陆账号"),15);
	PulsarNative::thirdAccountlogin();
}

//

void ThirdServerScene::toRegister() {
	this->addChild(MyUtil::getInstance()->getWaitLayer("正在登陆账号"),15);
	PulsarNative::thirdAccountlogin();
}

void ThirdServerScene::fastEnterGameWait() {
	this->addChild(MyUtil::getInstance()->getWaitLayer("正在登陆账号"),15);
	PulsarNative::thirdGuestLogin();
}

void ThirdServerScene::onEnterTransitionDidFinish() {
    ServerScene::onEnterTransitionDidFinish();
    PulsarNative::thirdAccountlogout();
}

void ThirdServerScene::exitGame() {
    PulsarNative::thirdExitGame();
}

void ThirdServerScene::keyBackClicked() {
    PulsarNative::thirdExitGame();
}

#endif
void ThirdServerScene::toServerList() {
    if (this->getChildByTag(loginLayerTag) != NULL) {
        this->removeChildByTag(loginLayerTag,true);
    }
    CCLayer* loginLayer = CCLayer::create();
    loginLayer->setTag(loginLayerTag);
    loginLayer->setPosition(ccp(0,0));
    
    CCLayer* displayLayer = CCLayer::create();
    CCSprite* loginBack = CCSprite::createWithSpriteFrameName("serverShadow.png");
    loginBack->setPosition(ccp(0,0));
    loginBack->setAnchorPoint(ccp(1,0));
    loginBack->setScale(2);
    displayLayer->addChild(loginBack);
    displayLayer->setTag(loginDisplayLayerTag);
    loginLayer->addChild(displayLayer);
    displayLayer->setPosition(ccp(winSize.width-645,960));
    
    CCSprite* serverListLabel = CCSprite::createWithSpriteFrameName("serverlistTipLabel.png");
    serverListLabel->setPosition(ccp(-285,325));
    displayLayer->addChild(serverListLabel);
    
    //    CCSprite* upTip = CCSprite::createWithSpriteFrameName("serverlistTipCornor.png");
    //    upTip->setPosition(ccp(-300,65));
    //    upTip->setRotation(180);
    //    upTip->setScale(0.66);
    //    upTip->setColor(ccc3(200,200,200));
    //    upTip->setTag(upTipTag);
    //
    //    displayLayer->addChild(upTip);
    
    CCSprite* downTip = CCSprite::createWithSpriteFrameName("serverlistTipCornor.png");
    downTip->setPosition(ccp(-300,50));
    downTip->setScale(0.66);
    downTip->setColor(ccc3(200,200,200));
    downTip->setTag(downTipTag);
    downTip->runAction(CCRepeatForever::create(static_cast<CCSequence*>(CCSequence::create( CCEaseIn::create(CCMoveBy::create(0.25,ccp(0,-10)),1.5),CCEaseOut::create(CCMoveBy::create(0.25,ccp(0,10)),1.5),NULL))));
    
    displayLayer->addChild(downTip);
    displayLayer->runAction(CCEaseElasticOut::create(CCMoveTo::create(0.35, ccp(winSize.width-394,280)), 1));
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sfx_popCreator.mp3");
    CCObject* obj;
    int i = 0;
    
    ServerSelectScroll2* scroll = ServerSelectScroll2::create(-507);
    scroll->setOriPosition(ccp(winSize.width-890,370));
    scroll->setContentSize(CCSizeMake(450, 200));
    
    scroll->setMapSize(CCSizeMake(450, 50*(beans->count()+3)));
    scroll->setPosition(ccp(winSize.width-765+0.33*50*(beans->count()-1)-224,-scroll->getMapSize().height+scroll->getViewSize().height+scroll->getOriPosition().y+680));
    
    scroll->runAction(CCEaseElasticOut::create(CCMoveBy::create(0.35, ccp(224,-680)), 1));
    CCARRAY_FOREACH(beans,obj) {
        SeverInfoBean* bean = (SeverInfoBean*)obj;
        CCSprite* layer = CCSprite::create("transparent.png");
        //        CCSprite* transParent = CCSprite::create("transparent.png");
        layer->setScaleX(270/layer->getContentSize().width);
        layer->setScaleY(33/layer->getContentSize().height);
        layer->setContentSize(CCSizeMake(225,33));
        layer->setOpacity(100);
        
        
        CCLabelTTF* label = CCLabelTTF::create(bean->getServerName()->getCString(),"Arial",33);
        label->setPosition(ccp(90/layer->getScaleX(),16/layer->getScaleY()));
        layer->addChild(label,2);
        label->setTag(serverNameLabelTag);
        label->setScaleX(1/layer->getScaleX());
        label->setScaleY(1/layer->getScaleY());
        if (bean->serverId == cacheServerId) {
            label->setColor(ccc3(155,155,155));
        }
        CCLabelTTF* stateLabel =CCLabelTTF::create(bean->getServerStatus()->getCString(),"Arial",30);
        stateLabel->setPosition(ccp(236/layer->getScaleX(),16/layer->getScaleY()));
        if (bean->getServerStatus()->compare("正常") == 0 || bean->getServerStatus()->compare("推荐") == 0) {
            stateLabel->setColor(ccc3(0,255,0));
        } else if (bean->getServerStatus()->compare("繁忙") == 0) {
            stateLabel->setColor(ccc3(255,255,0));
        } else if (bean->getServerStatus()->compare("火爆") == 0) {
            stateLabel->setColor(ccc3(167,87,168));
        } else {
            stateLabel->setColor(ccc3(166,166,166));
        }
        stateLabel->setScaleX(1/layer->getScaleX());
        stateLabel->setScaleY(1/layer->getScaleY());
        layer->addChild(stateLabel,2);
        
        
        MyMenuItem* serverItem = MyMenuItem::create(layer,this,menu_selector(ThirdServerScene::toChangeServer));
        
        serverItem->setPosition(ccp(-(i+3)*17+135,26+50*(i+3)));
        //        serverItem->setAnchorPoint(ccp(0,0));
        serverItem->setUserObject(bean);
        scroll->addChild(serverItem);
        //        dividingLength*i+33
        
        i++;
    }
    
    //    scroll = ServerSelectScroll::create(-500,array,serverIndex);
    
    
    loginLayer->addChild(scroll,5);
    //    scroll->scaleDis();
    //
    //    CCSprite* sprite1 = CCSprite::createWithSpriteFrameName("serverChangeServerList.png");
    //    sprite1->setScale(1.2);
    //    sprite1->setContentSize(CCSizeMake(sprite1->getContentSize().width*1.2,sprite1->getContentSize().height*1.2));
    //
    //    MyMenuItem* changeButton = MyMenuItem::create(sprite1,this,menu_selector(ServerScene::toChangeServer));
    //    changeButton->setPosition(ccp(-200,50));
    
    CCSprite* sprite2 = CCSprite::createWithSpriteFrameName("serverCancelServerList.png");
    //    sprite2->setScale(1.2);
    //    sprite2->setContentSize(CCSizeMake(sprite2->getContentSize().width*1.2,sprite2->getContentSize().height*1.2));
    
    MyMenuItem* cancelButton = MyMenuItem::create(sprite2,this,menu_selector(ThirdServerScene::toCancelServer));
    cancelButton->setPosition(ccp(-170,50));
    MyPriorityMenu* menu = MyPriorityMenu::create(-508,cancelButton,NULL);
    menu->setPosition(ccp(0,0));
    displayLayer->addChild(menu);
    
    this->addChild(loginLayer,1);
    
}


void ThirdServerScene::toChangeServer(CCMenuItem* item) {
    item->setEnabled(false);
    
    SeverInfoBean* bean = (SeverInfoBean*)(item->getUserObject());
    initServerInfo(bean);
    CCUserDefault::sharedUserDefault()->setIntegerForKey("serverId",bean->serverId);
    CCUserDefault::sharedUserDefault()->flush();
    
    this->getChildByTag(loginLayerTag)->runAction(CCSequence::create(CCEaseElasticIn::create(CCMoveTo::create(0.35, ccp(-251,680)), 1),GXRemoveFromParentsAction::create(),NULL));
    
}

void ThirdServerScene::toCancelServer(CCMenuItem* item) {
    item->setEnabled(false);
    this->getChildByTag(loginLayerTag)->runAction(CCSequence::create(CCEaseElasticIn::create(CCMoveBy::create(0.35, ccp(-251,680)), 1),GXRemoveFromParentsAction::create(),NULL));
}

