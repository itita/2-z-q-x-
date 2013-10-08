//
//  ServerScene.cpp
//  ww4
//
//  Created by xiao tang on 13-4-24.
//
//

#include "ServerScene.h"
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


#define loginLayerTag 10
#define loginDisplayLayerTag 11
#define displayJiemianLayerTag 12
#define serverInfoLayerTag 16


ServerScene::~ServerScene() {
    CC_SAFE_RELEASE_NULL(loginUsernameTextField);
    CC_SAFE_RELEASE_NULL(loginPasswordTextField);
    CC_SAFE_RELEASE_NULL(registerUsernameTextField);
    CC_SAFE_RELEASE_NULL(registerPasswordTextField);
    CC_SAFE_RELEASE_NULL(registerSurePasswordTextField);
    CC_SAFE_RELEASE_NULL(registerNicknameTextField);
    CC_SAFE_RELEASE_NULL(registerMailTextField);
    CC_SAFE_RELEASE_NULL(registerSignatureTextField);
    CC_SAFE_RELEASE_NULL(beans);
    if (loginTrigger != NULL) {
        MyMessageManage::getInstance()->unRegisterTrigger(loginTrigger);
        CC_SAFE_RELEASE(loginTrigger);
    }
    
    releaseResource();
    CocosDenshion::SimpleAudioEngine::sharedEngine()->stopBackgroundMusic("bgm_server.mp3");
}

ServerScene* ServerScene::create() {
    ServerScene* scene = new ServerScene();
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

void ServerScene::myInit() {
    
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
    logo->setPosition(ccp(background->getContentSize().width/2,winSize.height-182));
    background->addChild(logo,2);
    
    CCSprite* kuangUp1 = CCSprite::createWithSpriteFrameName("serverListUpUI.png");
    kuangUp1->setAnchorPoint(ccp(1,1));
    kuangUp1->setPosition(ccp(background->getContentSize().width/2,winSize.height-290));
    kuangUp1->setScaleX((winSize.width/2)/kuangUp1->getContentSize().width);
    background->addChild(kuangUp1,1);
    
    CCSprite* kuangUp2 = CCSprite::createWithSpriteFrameName("serverListUpUI.png");
    kuangUp2->setAnchorPoint(ccp(0,1));
    kuangUp2->setFlipX(true);
    kuangUp2->setPosition(ccp(background->getContentSize().width/2,winSize.height-290));
    kuangUp2->setScaleX((winSize.width/2)/kuangUp2->getContentSize().width);
    background->addChild(kuangUp2,1);
    
    CCSprite* kuangDown1 = CCSprite::createWithSpriteFrameName("serverListDownUI.png");
    kuangDown1->setAnchorPoint(ccp(1,0));
    kuangDown1->setPosition(ccp(background->getContentSize().width/2,0));
    kuangDown1->setScaleX((winSize.width/2)/kuangDown1->getContentSize().width);

    background->addChild(kuangDown1,1);
    
    CCSprite* kuangDown2 = CCSprite::createWithSpriteFrameName("serverListDownUI.png");
    kuangDown2->setAnchorPoint(ccp(0,0));
    kuangDown2->setFlipX(true);
    kuangDown2->setPosition(ccp(background->getContentSize().width/2,0));
    kuangDown2->setScaleX((winSize.width/2)/kuangDown2->getContentSize().width);
    background->addChild(kuangDown2,1);
    
    CCSprite* black = CCSprite::create("whiteImage.jpg");
    black->setAnchorPoint(ccp(0.5,0));
    black->setScaleX(winSize.width/black->getContentSize().width);
    black->setScaleY((winSize.height-287-kuangUp1->getContentSize().height)/black->getContentSize().height);
    black->setColor(ccc3(0,0,0));
    black->setOpacity(255*0.9);
    black->setPosition(ccp(background->getContentSize().width/2,0));
    background->addChild(black);
    
    
    
    CCSprite* listLabel = CCSprite::createWithSpriteFrameName("serverListLabel.png");
    listLabel->setAnchorPoint(ccp(0,1));
    listLabel->setPosition(ccp(winSize.width/2-240,261));
    backLayer->addChild(listLabel,0);
    
//    CCSprite* kuang = MyUtil::getInstance()->getLineBox(500, 70);
//    kuang->setPosition(ccp(winSize.width/2,140));
//    backLayer->addChild(kuang,0);
    
//    GXScrollView* scroll = GXScrollView::create(-501);
//    scroll->setOriPosition(ccp(0,35));
//    scroll->setContentSize(CCSizeMake(960, 200));
    
//    GXRadioMenu* menu = GXRadioMenu::create(-501,NULL);
    
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

void ServerScene::initServerInfo(SeverInfoBean* bean) {
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
    
    CCMenuItemSprite* leftButton = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("serverButton.png"),CCSprite::createWithSpriteFrameName("serverButtonP.png"));
    leftButton->setPosition(ccp(116,162));
    CCSprite* registLabel;
    if (ititaIdFlag) {
        registLabel = CCSprite::createWithSpriteFrameName("serverSwitchLabel.png");
        leftButton->setTarget(this,menu_selector(ServerScene::toLogin));
    } else {
        registLabel = CCSprite::createWithSpriteFrameName("severRegisterLabel.png");
        leftButton->setTarget(this,menu_selector(ServerScene::toRegister));
    }
    registLabel->setPosition(ccp(leftButton->getContentSize().width/2,leftButton->getContentSize().height/2));
    leftButton->addChild(registLabel);
    
    
    
    
    CCMenuItemSprite* rightButton = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("serverButton.png"),CCSprite::createWithSpriteFrameName("serverButtonP.png"),this,menu_selector(ServerScene::fastEnterGameWait));
    rightButton->setPosition(ccp(winSize.width-116,162));
    
    
    CCSprite* newLabel;
    if (ititaIdFlag) {
        newLabel = CCSprite::createWithSpriteFrameName("serverEnterGame.png");
    } else {
        newLabel = CCSprite::createWithSpriteFrameName("serverFastStartLabel.png");
        CCSprite* buttonFire = CCSprite::createWithSpriteFrameName("serverButtonFire.png");
        buttonFire->setPosition(ccp(rightButton->getContentSize().width/2,rightButton->getContentSize().height/2));
        rightButton->addChild(buttonFire);
    }
    
    newLabel->setPosition(ccp(rightButton->getContentSize().width/2,rightButton->getContentSize().height/2));
    rightButton->addChild(newLabel);
    
    MyPriorityMenu* menu = MyPriorityMenu::create(-501,leftButton,rightButton,NULL);
    menu->setPosition(ccp(0,0));
    serverInfoLayer->addChild(menu);
    
    sprintf(str,"s%d_nickname",bean->serverId);
    std::string nickname = CCUserDefault::sharedUserDefault()->getStringForKey(str,"");
    
    if (nickname.compare("") != 0) {
        CCLabelTTF* id = CCLabelTTF::create("ID:","Arial",40);
        id->setColor(ccc3(255,222,0));
        
        CCLabelTTF* nicknameLabel = CCLabelTTF::create(nickname.c_str(),"Arial",40);
        float locx = id->getContentSize().width+nicknameLabel->getContentSize().width;
        id->setAnchorPoint(ccp(0,0.5));
        id->setPosition(ccp(winSize.width/2-locx/2,290));
        nicknameLabel->setAnchorPoint(ccp(0,0.5));
        nicknameLabel->setPosition(ccp(winSize.width/2-locx/2+id->getContentSize().width,290));
        serverInfoLayer->addChild(id);
        serverInfoLayer->addChild(nicknameLabel);
    }
    
    CCLayer* layer = CCLayer::create();
    
    CCSprite* bullet = CCSprite::createWithSpriteFrameName("serverBullet.png");
    bullet->setAnchorPoint(ccp(0,0.5));
    bullet->setPosition(ccp(0,0));
    layer->addChild(bullet,1);
    
    CCLabelTTF* label = CCLabelTTF::create(bean->getServerName()->getCString(),"Arial",45);
    label->setPosition(ccp(224,10));
    label->setColor(ccc3(255,222,0));
    layer->addChild(label);
    label->setTag(serverNameLabelTag);
    
    CCLabelTTF* stateLabel =CCLabelTTF::create(bean->getServerStatus()->getCString(),"Arial",30);
    stateLabel->setPosition(ccp(380,0));
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
    if (bean->serverStatusId == tuijianTag) {
        CCSprite* newLabel = CCSprite::createWithSpriteFrameName("serverNewLabel.png");
        newLabel->setPosition(ccp(bullet->getContentSize().width/2,0));
        layer->addChild(newLabel,2);
    } else {
        CCSprite* newLabel = CCSprite::createWithSpriteFrameName("serverHotLabel.png");
        newLabel->setPosition(ccp(bullet->getContentSize().width/2,0));
        layer->addChild(newLabel,2);
    }
    
    CCSprite* underLine = CCSprite::createWithSpriteFrameName("serverUnderLine.png");
    underLine->setAnchorPoint(ccp(0,1));
    underLine->setPosition(ccp(75,-bullet->getContentSize().height/2+5));
    layer->addChild(underLine);
    
    layer->setPosition(ccp(winSize.width/2-205,160));
    serverInfoLayer->addChild(layer);
    
    CCMenuItemSprite* selectServerButton = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("serverSelectButton.png"),CCSprite::createWithSpriteFrameName("serverSelectButtonP.png"),this,menu_selector(ServerScene::toServerList));
    selectServerButton->setPosition(winSize.width/2,80);
    menu->addChild(selectServerButton);
    
    this->addChild(serverInfoLayer,2);
}


void ServerScene::loadResource() {
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("server.plist","server.pvr.ccz");
}

void ServerScene::releaseResource() {
    CCTextureCache::sharedTextureCache()->removeTextureForKey("loading.jpg");
    CCTextureCache::sharedTextureCache()->removeTextureForKey("logo.png");
    CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile("server.plist");
    CCTextureCache::sharedTextureCache()->removeTextureForKey("server.pvr.ccz");
    GarbageResourceCollection::getInstance()->GarbageCollection();
//    CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile("avatar.plist");
//    CCTextureCache::sharedTextureCache()->removeTextureForKey("avatar.pvr.ccz");
}

void ServerScene::toLogin() {
    
    CCNode* node = this->getChildByTag(loginLayerTag);
    if (node != NULL) {
        node->removeAllChildrenWithCleanup(true);
        node->removeFromParentAndCleanup(true);
    }
    CCLayer* loginLayer = CCLayer::create();
    loginLayer->setTag(loginLayerTag);
    loginLayer->setPosition(ccp(0,0));
    
    
    
    CCLayer* displayLayer = CCLayer::create();
    CCSprite* loginBack = MyUtil::getInstance()->getServerRegistBack();
    loginBack->setPosition(ccp(winSize.width/2,winSize.height-loginBack->getContentSize().height/2));
    displayLayer->addChild(loginBack);
    displayLayer->setTag(loginDisplayLayerTag);
    loginLayer->addChild(displayLayer);
    displayLayer->setPosition(ccp(0,960));
    
    
    CCSprite* loginButtonSprite = CCSprite::createWithSpriteFrameName("serverMetalButton.png");
    CCSprite* loginButtonLabel = CCSprite::createWithSpriteFrameName("serverLoginButtonLabel.png");
    loginButtonLabel->setPosition(ccp(loginButtonSprite->getContentSize().width/2+5,loginButtonSprite->getContentSize().height/2+15));
    loginButtonLabel->setColor(ccc3(215,132,0));
    loginButtonSprite->addChild(loginButtonLabel);
    
    CCSprite* loginButtonSpriteP = CCSprite::createWithSpriteFrameName("serverMetalButtonP.png");
    CCSprite* loginButtonLabel2 = CCSprite::createWithSpriteFrameName("serverLoginButtonLabel.png");
    loginButtonLabel2->setPosition(ccp(loginButtonSpriteP->getContentSize().width/2,loginButtonSpriteP->getContentSize().height/2));
    loginButtonLabel2->setScale(1.25);
    loginButtonLabel2->setColor(ccc3(255,204,0));
    loginButtonSpriteP->addChild(loginButtonLabel2);
    
    CCMenuItemSprite*  loginButton = CCMenuItemSprite::create(loginButtonSprite,loginButtonSpriteP,this,menu_selector(ServerScene::toDisplayLogin));
    
    
    CCSprite* registerButtonSprite = CCSprite::createWithSpriteFrameName("serverMetalButton.png");
    CCSprite* registerButtonLabel = CCSprite::createWithSpriteFrameName("serverRegisterButtonLabel.png");
    registerButtonLabel->setPosition(ccp(registerButtonSprite->getContentSize().width/2+5,registerButtonSprite->getContentSize().height/2+15));
    registerButtonLabel->setColor(ccc3(215,132,0));
    registerButtonSprite->addChild(registerButtonLabel);
    
    CCSprite* registerButtonSpriteP = CCSprite::createWithSpriteFrameName("serverMetalButtonP.png");
    CCSprite* registerButtonLabel2 = CCSprite::createWithSpriteFrameName("serverRegisterButtonLabel.png");
    registerButtonLabel2->setPosition(ccp(registerButtonSpriteP->getContentSize().width/2,registerButtonSpriteP->getContentSize().height/2));
    registerButtonLabel2->setScale(1.25);
    registerButtonLabel2->setColor(ccc3(255,204,0));
    registerButtonSpriteP->addChild(registerButtonLabel2);
    
    CCMenuItemSprite*  registerButton = CCMenuItemSprite::create(registerButtonSprite,registerButtonSpriteP,this,menu_selector(ServerScene::toDisplayRegister));
    
    GXRadioMenu* menu = GXRadioMenu::create(-503,loginButton,registerButton,NULL);
//    menu->setPosition(ccp(839,495));
    menu->setPosition(ccp(winSize.width/2+359,495+960));
    menu->alignItemsVerticallyWithPadding(0);
    
    loginLayer->addChild(menu);
    
    
//    this->getChildByTag(charDialogTag)->runAction(CCEaseElasticOut::create(CCMoveTo::create(0.35, ccp(-16,0)), 1));
    
    this->addChild(loginLayer,3);
    
}

//

void ServerScene::toRegister() {
    
    
    if (this->getChildByTag(loginLayerTag) != NULL) {
        return;
    }
    CCLayer* loginLayer = CCLayer::create();
    loginLayer->setTag(loginLayerTag);
    loginLayer->setPosition(ccp(0,0));
    
    
    
    CCLayer* displayLayer = CCLayer::create();
    CCSprite* loginBack = MyUtil::getInstance()->getServerRegistBack();
    loginBack->setPosition(ccp(winSize.width/2,winSize.height-loginBack->getContentSize().height/2));
    displayLayer->addChild(loginBack);
    displayLayer->setTag(loginDisplayLayerTag);
    loginLayer->addChild(displayLayer);
    displayLayer->setPosition(ccp(0,960));
    
    
    CCSprite* loginButtonSprite = CCSprite::createWithSpriteFrameName("serverMetalButton.png");
    CCSprite* loginButtonLabel = CCSprite::createWithSpriteFrameName("serverLoginButtonLabel.png");
    loginButtonLabel->setPosition(ccp(loginButtonSprite->getContentSize().width/2+5,loginButtonSprite->getContentSize().height/2+15));
    loginButtonLabel->setColor(ccc3(215,132,0));
    loginButtonSprite->addChild(loginButtonLabel);
    
    CCSprite* loginButtonSpriteP = CCSprite::createWithSpriteFrameName("serverMetalButtonP.png");
    CCSprite* loginButtonLabel2 = CCSprite::createWithSpriteFrameName("serverLoginButtonLabel.png");
    loginButtonLabel2->setPosition(ccp(loginButtonSpriteP->getContentSize().width/2,loginButtonSpriteP->getContentSize().height/2));
    loginButtonLabel2->setScale(1.25);
    loginButtonLabel2->setColor(ccc3(255,204,0));
    loginButtonSpriteP->addChild(loginButtonLabel2);
    
    CCMenuItemSprite*  loginButton = CCMenuItemSprite::create(loginButtonSprite,loginButtonSpriteP,this,menu_selector(ServerScene::toDisplayLogin));
    
    
    CCSprite* registerButtonSprite = CCSprite::createWithSpriteFrameName("serverMetalButton.png");
    CCSprite* registerButtonLabel = CCSprite::createWithSpriteFrameName("serverRegisterButtonLabel.png");
    registerButtonLabel->setPosition(ccp(registerButtonSprite->getContentSize().width/2+5,registerButtonSprite->getContentSize().height/2+15));
    registerButtonLabel->setColor(ccc3(215,132,0));
    registerButtonSprite->addChild(registerButtonLabel);
    
    CCSprite* registerButtonSpriteP = CCSprite::createWithSpriteFrameName("serverMetalButtonP.png");
    CCSprite* registerButtonLabel2 = CCSprite::createWithSpriteFrameName("serverRegisterButtonLabel.png");
    registerButtonLabel2->setPosition(ccp(registerButtonSpriteP->getContentSize().width/2,registerButtonSpriteP->getContentSize().height/2));
    registerButtonLabel2->setScale(1.25);
    registerButtonLabel2->setColor(ccc3(255,204,0));
    registerButtonSpriteP->addChild(registerButtonLabel2);
    
    CCMenuItemSprite*  registerButton = CCMenuItemSprite::create(registerButtonSprite,registerButtonSpriteP,this,menu_selector(ServerScene::toDisplayRegister));
    
    GXRadioMenu* menu = GXRadioMenu::create(-503,registerButton,loginButton,NULL);
    menu->setPosition(ccp(winSize.width/2+359,495+960));
    menu->alignItemsVerticallyWithPadding(0);
    
    loginLayer->addChild(menu);
    
    this->addChild(loginLayer,3);
    
}

void ServerScene::toServerList() {
    if (this->getChildByTag(loginLayerTag) != NULL) {
        this->removeChildByTag(loginLayerTag,true);
    }
    CCLayer* loginLayer = CCLayer::create();
    loginLayer->setTag(loginLayerTag);
    loginLayer->setPosition(ccp(0,510));
    
    CCLayer* displayLayer = CCLayer::create();
    CCSprite* loginBack = MyUtil::getInstance()->getServerRegistBack();
    loginBack->setPosition(ccp(winSize.width/2,winSize.height-loginBack->getContentSize().height/2));
    displayLayer->addChild(loginBack);
    displayLayer->setTag(loginDisplayLayerTag);
    loginLayer->addChild(displayLayer);
    displayLayer->setPosition(ccp(0,250));
    
    CCSprite* metalBack = CCSprite::createWithSpriteFrameName("serverMetalButtonP.png");
    CCSprite* serverListLabel = CCSprite::createWithSpriteFrameName("serverlistTipLabel.png");
    serverListLabel->setPosition(ccp(metalBack->getContentSize().width/2,metalBack->getContentSize().height/2));
    serverListLabel->setScaleY(0.9);
    metalBack->setScaleY(1.11);
    serverListLabel->setColor(ccc3(255,204,0));
    metalBack->addChild(serverListLabel);
    metalBack->setPosition(ccp(winSize.width/2+359,555));
    loginLayer->addChild(metalBack);
    
    CCSprite* upTip = CCSprite::createWithSpriteFrameName("serverlistTipCornor.png");
    upTip->setPosition(ccp(winSize.width/2-300,555));
    upTip->setRotation(180);
    upTip->setScale(0.66);
    upTip->setColor(ccc3(200,200,200));
    upTip->setTag(upTipTag);
    upTip->runAction(CCRepeatForever::create(static_cast<CCSequence*>(CCSequence::create( CCEaseIn::create(CCMoveBy::create(0.25,ccp(0,10)),1.5),CCEaseOut::create(CCMoveBy::create(0.25,ccp(0,-10)),1.5),NULL))));
    loginLayer->addChild(upTip);
    
    CCSprite* downTip = CCSprite::createWithSpriteFrameName("serverlistTipCornor.png");
    downTip->setPosition(ccp(winSize.width/2-300,455));
    downTip->setScale(0.66);
    downTip->setColor(ccc3(200,200,200));
    downTip->setTag(downTipTag);
    downTip->runAction(CCRepeatForever::create(static_cast<CCSequence*>(CCSequence::create( CCEaseIn::create(CCMoveBy::create(0.25,ccp(0,-10)),1.5),CCEaseOut::create(CCMoveBy::create(0.25,ccp(0,10)),1.5),NULL))));
    loginLayer->addChild(downTip);
    loginLayer->runAction(CCEaseElasticOut::create(CCMoveTo::create(0.35, ccp(0,0)), 1));
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sfx_popCreator.mp3");
    CCArray* array = CCArray::create();
    CCObject* obj;
    int serverIndex = -1;
    int i = 0;
    CCARRAY_FOREACH(beans,obj) {
        SeverInfoBean* bean = (SeverInfoBean*)obj;
        CCLayer* layer = CCLayer::create();
        //        CCSprite* transParent = CCSprite::create("transparent.png");
        //        transParent->setScaleX(435/transParent->getContentSize().width);
        if (bean->serverId == cacheServerId) {
            serverIndex = i;
        }
        CCSprite* bullet = CCSprite::createWithSpriteFrameName("serverBullet.png");
        bullet->setAnchorPoint(ccp(0,0.5));
        bullet->setPosition(ccp(0,0));
        layer->addChild(bullet,1);
        
        CCLabelTTF* label = CCLabelTTF::create(bean->getServerName()->getCString(),"Arial",45);
        label->setPosition(ccp(224,10));
        label->setColor(ccc3(155,155,155));
        layer->addChild(label);
        label->setTag(serverNameLabelTag);
        
        CCLabelTTF* stateLabel =CCLabelTTF::create(bean->getServerStatus()->getCString(),"Arial",30);
        stateLabel->setPosition(ccp(380,0));
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
        if (bean->serverStatusId == tuijianTag) {
            CCSprite* newLabel = CCSprite::createWithSpriteFrameName("serverNewLabel.png");
            newLabel->setPosition(ccp(bullet->getContentSize().width/2,0));
            layer->addChild(newLabel,2);
        } else {
            CCSprite* newLabel = CCSprite::createWithSpriteFrameName("serverHotLabel.png");
            newLabel->setPosition(ccp(bullet->getContentSize().width/2,0));
            layer->addChild(newLabel,2);
        }
        
        CCSprite* underLine = CCSprite::createWithSpriteFrameName("serverUnderLine.png");
        underLine->setAnchorPoint(ccp(0,1));
        underLine->setPosition(ccp(75,-bullet->getContentSize().height/2+5));
        layer->addChild(underLine);
        //        CCLog("%f",380+stateLabel->getContentSize().width/2);
        
        //        layer->setPosition(ccp(265,200-70*i));
        //        backLayer->addChild(layer);
        array->addObject(layer);
        layer->setUserObject(bean);
        i++;
    }

    scroll = ServerSelectScroll::create(-500,array,serverIndex);
    loginLayer->addChild(scroll,5);
    scroll->scaleDis();
    
    CCSprite* sprite1 = CCSprite::createWithSpriteFrameName("serverChangeServerList.png");
    sprite1->setScale(1.3);
    sprite1->setContentSize(CCSizeMake(sprite1->getContentSize().width*1.3,sprite1->getContentSize().height*1.3));
    
    MyMenuItem* changeButton = MyMenuItem::create(sprite1,this,menu_selector(ServerScene::toChangeServer));
    changeButton->setPosition(ccp(winSize.width/2-100,120));
    
    CCSprite* sprite2 = CCSprite::createWithSpriteFrameName("serverCancelServerList.png");
    sprite2->setScale(1.3);
    sprite2->setContentSize(CCSizeMake(sprite2->getContentSize().width*1.3,sprite2->getContentSize().height*1.3));
    
    MyMenuItem* cancelButton = MyMenuItem::create(sprite2,this,menu_selector(ServerScene::toCancelServer));
    cancelButton->setPosition(ccp(winSize.width/2+100,120));
    MyPriorityMenu* menu = MyPriorityMenu::create(-508,changeButton,cancelButton,NULL);
    menu->setPosition(ccp(0,0));
    displayLayer->addChild(menu);
    
    this->addChild(loginLayer,1);
    
}

void ServerScene::toChangeServer(CCMenuItem* item) {
    item->setEnabled(false);
    
    SeverInfoBean* bean = (SeverInfoBean*)(scroll->getSelectServer());
    initServerInfo(bean);
    CCUserDefault::sharedUserDefault()->setIntegerForKey("serverId",bean->serverId);
    CCUserDefault::sharedUserDefault()->flush();
    
    this->getChildByTag(loginLayerTag)->runAction(CCSequence::create(CCEaseElasticIn::create(CCMoveTo::create(0.35, ccp(0,510)), 1),GXRemoveFromParentsAction::create(),NULL));
    
}

void ServerScene::toCancelServer(CCMenuItem* item) {
    item->setEnabled(false);
    this->getChildByTag(loginLayerTag)->runAction(CCSequence::create(CCEaseElasticIn::create(CCMoveTo::create(0.35, ccp(0,510)), 1),GXRemoveFromParentsAction::create(),NULL));
}

void ServerScene::toDisplayLogin(CCMenuItem* item) {
    
    char str[30] = {0};
    
    if (item->getParent()->getPosition().y > 960) {
        item->getParent()->runAction(CCEaseElasticOut::create(CCMoveTo::create(0.35, ccp(winSize.width/2+359,495)), 1));
        CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sfx_popCreator.mp3");
    }
    CCNode* parent = this->getChildByTag(loginLayerTag)->getChildByTag(loginDisplayLayerTag);
    
    if (parent->getPosition().y <240) {
        CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sfx_popCreator.mp3");
    }
    parent->runAction(CCEaseElasticOut::create(CCMoveTo::create(0.35, ccp(0,250)), 1));
    
    parent->removeChildByTag(displayJiemianLayerTag,true);
    
    CCLayer* layer = CCLayer::create();
    parent->addChild(layer);
    layer->setTag(displayJiemianLayerTag);
    
    CCLabelTTF* username = CCLabelTTF::create("账 号:","Arial",40);
    username->setPosition(ccp(winSize.width/2-250,320));
    username->setColor(ccc3(255,222,0));
    layer->addChild(username);
    
    
    
    CCSprite* sprite1 = CCSprite::createWithSpriteFrameName("serverMetalEditText.png");
    sprite1->setScale(2);
    sprite1->setContentSize(CCSizeMake(sprite1->getContentSize().width*2,sprite1->getContentSize().height*2));
    
    MyMenuItem* light1 = MyMenuItem::create(sprite1,this,menu_selector(ServerScene::toAttachIME));
    light1->setPosition(ccp(winSize.width/2+20,320));
    
    
    
    if (loginUsernameTextField == NULL) {
        loginUsernameTextField = CCTextFieldTTF::textFieldWithPlaceHolder("",CCSizeMake(light1->getContentSize().width,light1->getContentSize().height), kCCTextAlignmentLeft,"Arial",35);
        //    loginUsernameTextField->setColor(ccc3(254,185,0));
        loginUsernameTextField->setPosition(ccp(winSize.width/2+30,315));
        loginUsernameTextField->setAnchorPoint(ccp(0.5,0.5));
        loginUsernameTextField->setDelegate(this);
        CC_SAFE_RETAIN(loginUsernameTextField);
        
    }
    sprintf(str,"s%d_ititaId",cacheServerId);
    std::string ititaId = CCUserDefault::sharedUserDefault()->getStringForKey(str,"");
    if (ititaId.compare("") != 0 && ititaId.compare(PulsarNative::getDeviceId()) != 0) {
        loginUsernameTextField->setString(ititaId.c_str());
    }
    
    light1->setUserObject(loginUsernameTextField);
    layer->addChild(loginUsernameTextField);
    
    
    CCLabelTTF* password = CCLabelTTF::create("密 码:","Arial",40);
    password->setPosition(ccp(winSize.width/2-250,220));
    password->setColor(ccc3(255,222,0));
    layer->addChild(password);
    
    
    CCSprite* sprite2 = CCSprite::createWithSpriteFrameName("serverMetalEditText.png");
    sprite2->setScale(2);
    sprite2->setContentSize(CCSizeMake(sprite2->getContentSize().width*2,sprite2->getContentSize().height*2));
    MyMenuItem* light2 = MyMenuItem::create(sprite2,this,menu_selector(ServerScene::toAttachIME));
    light2->setPosition(ccp(winSize.width/2+20,220));
    if (loginPasswordTextField == NULL) {
        loginPasswordTextField = CCTextFieldTTF::textFieldWithPlaceHolder("",CCSizeMake(light2->getContentSize().width,light2->getContentSize().height), kCCTextAlignmentLeft,"Arial",35);
        //    loginUsernameTextField->setColor(ccc3(254,185,0));
        loginPasswordTextField->setPosition(ccp(winSize.width/2+30,215));
        loginPasswordTextField->setAnchorPoint(ccp(0.5,0.5));
        loginPasswordTextField->setDelegate(this);
        CC_SAFE_RETAIN(loginPasswordTextField);
        
    }
    sprintf(str,"s%d_password",cacheServerId);
    std::string pwd = CCUserDefault::sharedUserDefault()->getStringForKey(str,"").c_str();
    if (pwd.compare("") != 0) {
        loginPasswordTextField->setString(pwd.c_str());
    }
    
    light2->setUserObject(loginPasswordTextField);
    layer->addChild(loginPasswordTextField);
    
    CCSprite* sprite3 = CCSprite::createWithSpriteFrameName("serverLoginLabelButton.png");
    sprite3->setScale(1.5);
    sprite3->setContentSize(CCSizeMake(sprite3->getContentSize().width*1.5,sprite3->getContentSize().height*1.5));
    
    MyMenuItem* loginButton = MyMenuItem::create(sprite3,this,menu_selector(ServerScene::loginEnterGameWait));
    
    loginButton->setPosition(ccp(winSize.width/2,120));
    
    MyPriorityMenu* menu = MyPriorityMenu::create(-502,light1,light2,loginButton,NULL);
    
    menu->setPosition(ccp(0,0));
    layer->addChild(menu);
    
    
}

void ServerScene::toDisplayRegister(CCMenuItem* item) {
    
    char str[30] = {0};
    
    if (item->getParent()->getPosition().y > 960) {
        item->getParent()->runAction(CCEaseElasticOut::create(CCMoveTo::create(0.35, ccp(winSize.width/2+359,495)), 1));
    }
    CCNode* parent = this->getChildByTag(loginLayerTag)->getChildByTag(loginDisplayLayerTag);
    
    if (parent->getPosition().y >240) {
        CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sfx_popCreator.mp3");
    }
    parent->runAction(CCEaseElasticOut::create(CCMoveTo::create(0.35, ccp(0,30)), 1));
    
    parent->removeChildByTag(displayJiemianLayerTag,true);
    
    CCLayer* layer = CCLayer::create();
    parent->addChild(layer);
    layer->setTag(displayJiemianLayerTag);
    
    CCLabelTTF* username = CCLabelTTF::create("输入账号:","Arial",35);
    username->setPosition(ccp(winSize.width/2-270,580));
    username->setColor(ccc3(255,222,0));
    layer->addChild(username);
    
    CCLabelTTF* usernameXing = CCLabelTTF::create("※","Arial",25);
    usernameXing->setPosition(ccp(winSize.width/2-363,583));
    usernameXing->setColor(ccc3(255,0,0));
    layer->addChild(usernameXing);
    
    CCLabelTTF* usernamePS = CCLabelTTF::create("注:首次注册绑定\n“快速登陆”账号","Arial",20);
    usernamePS->setPosition(ccp(winSize.width/2+120,580));
    usernamePS->setAnchorPoint(ccp(0,0.5));
    usernamePS->setColor(ccc3(255,222,0));
    layer->addChild(usernamePS);
    
    
    CCSprite* sprite1 = CCSprite::createWithSpriteFrameName("serverMetalEditText.png");
    sprite1->setScale(1.5);
    sprite1->setContentSize(CCSizeMake(sprite1->getContentSize().width*1.5,sprite1->getContentSize().height*1.5));
    
    MyMenuItem* light1 = MyMenuItem::create(sprite1,this,menu_selector(ServerScene::toAttachIME));
    light1->setPosition(ccp(winSize.width/2-30,580));
    
    if (registerUsernameTextField == NULL) {
        registerUsernameTextField = CCTextFieldTTF::textFieldWithPlaceHolder("输入4-11位英文或数字",CCSizeMake(light1->getContentSize().width,light1->getContentSize().height), kCCTextAlignmentLeft,"Arial",29);
        //    loginUsernameTextField->setColor(ccc3(254,185,0));
        registerUsernameTextField->setPosition(ccp(winSize.width/2-25,580));
        registerUsernameTextField->setAnchorPoint(ccp(0.5,0.5));
        registerUsernameTextField->setDelegate(this);
        CC_SAFE_RETAIN(registerUsernameTextField);
    }
    
    light1->setUserObject(registerUsernameTextField);
    layer->addChild(registerUsernameTextField);
    
    CCLabelTTF* password = CCLabelTTF::create("输入密码:","Arial",35);
    password->setPosition(ccp(winSize.width/2-270,530));
    password->setColor(ccc3(255,222,0));
    layer->addChild(password);
    
    CCLabelTTF* passwordXing = CCLabelTTF::create("※","Arial",25);
    passwordXing->setPosition(ccp(winSize.width/2-363,533));
    passwordXing->setColor(ccc3(255,0,0));
    layer->addChild(passwordXing);
    
    CCSprite* sprite2 = CCSprite::createWithSpriteFrameName("serverMetalEditText.png");
    sprite2->setScale(1.5);
    sprite2->setContentSize(CCSizeMake(sprite2->getContentSize().width*1.5,sprite2->getContentSize().height*1.5));
    MyMenuItem* light2 = MyMenuItem::create(sprite2,this,menu_selector(ServerScene::toAttachIME));
    light2->setPosition(ccp(winSize.width/2-30,530));
    
    if (registerPasswordTextField == NULL) {
        registerPasswordTextField = CCTextFieldTTF::textFieldWithPlaceHolder("输入6-11位英文或数字",CCSizeMake(light2->getContentSize().width,light2->getContentSize().height), kCCTextAlignmentLeft,"Arial",29);
        //    loginUsernameTextField->setColor(ccc3(254,185,0));
        registerPasswordTextField->setPosition(ccp(winSize.width/2-25,530));
        registerPasswordTextField->setAnchorPoint(ccp(0.5,0.5));
        registerPasswordTextField->setDelegate(this);
        CC_SAFE_RETAIN(registerPasswordTextField);
    }
    
    light2->setUserObject(registerPasswordTextField);
    layer->addChild(registerPasswordTextField);
    
    ////
    
    
    CCLabelTTF* surePass = CCLabelTTF::create("确认密码:","Arial",35);
    surePass->setPosition(ccp(winSize.width/2-270,480));
    surePass->setColor(ccc3(255,222,0));
    layer->addChild(surePass);
    
    CCLabelTTF* surePassXing = CCLabelTTF::create("※","Arial",25);
    surePassXing->setPosition(ccp(winSize.width/2-363,483));
    surePassXing->setColor(ccc3(255,0,0));
    layer->addChild(surePassXing);
    
    CCSprite* sprite3 = CCSprite::createWithSpriteFrameName("serverMetalEditText.png");
    sprite3->setScale(1.5);
    sprite3->setContentSize(CCSizeMake(sprite3->getContentSize().width*1.5,sprite3->getContentSize().height*1.5));
    MyMenuItem* light3 = MyMenuItem::create(sprite3,this,menu_selector(ServerScene::toAttachIME));
    light3->setPosition(ccp(winSize.width/2-30,480));
    
    if (registerSurePasswordTextField == NULL) {
        registerSurePasswordTextField = CCTextFieldTTF::textFieldWithPlaceHolder("再次输入上面的密码",CCSizeMake(light3->getContentSize().width,light3->getContentSize().height), kCCTextAlignmentLeft,"Arial",30);
        //    loginUsernameTextField->setColor(ccc3(254,185,0));
        registerSurePasswordTextField->setPosition(ccp(winSize.width/2-25,480));
        registerSurePasswordTextField->setAnchorPoint(ccp(0.5,0.5));
        registerSurePasswordTextField->setDelegate(this);
        CC_SAFE_RETAIN(registerSurePasswordTextField);
    }
    
    light3->setUserObject(registerSurePasswordTextField);
    layer->addChild(registerSurePasswordTextField);
    
   ////
    
    CCLabelTTF* nickname = CCLabelTTF::create("输入昵称:","Arial",35);
    nickname->setPosition(ccp(winSize.width/2 - 270,430));
    nickname->setColor(ccc3(255,222,0));
    layer->addChild(nickname);
    
    CCLabelTTF* nicknameXing = CCLabelTTF::create("※","Arial",25);
    nicknameXing->setPosition(ccp(winSize.width/2-363,430));
    nicknameXing->setColor(ccc3(255,0,0));
    layer->addChild(nicknameXing);
    
    
    CCSprite* sprite4 = CCSprite::createWithSpriteFrameName("serverMetalEditText.png");
    sprite4->setScale(1.5);
    sprite4->setContentSize(CCSizeMake(sprite4->getContentSize().width*1.5,sprite4->getContentSize().height*1.5));
    MyMenuItem* light4 = MyMenuItem::create(sprite4,this,menu_selector(ServerScene::toAttachIME));
    light4->setPosition(ccp(winSize.width/2-30,430));
    
    
    
    if (registerNicknameTextField == NULL) {
        registerNicknameTextField = CCTextFieldTTF::textFieldWithPlaceHolder("输入6位以下昵称",CCSizeMake(light4->getContentSize().width,light4->getContentSize().height), kCCTextAlignmentLeft,"Arial",30);
        //    loginUsernameTextField->setColor(ccc3(254,185,0));
        registerNicknameTextField->setPosition(ccp(winSize.width/2-25,430));
        registerNicknameTextField->setAnchorPoint(ccp(0.5,0.5));
        registerNicknameTextField->setDelegate(this);
        CC_SAFE_RETAIN(registerNicknameTextField);
    }
    sprintf(str,"s%d_nickname",cacheServerId);
    std::string cacheNickname = CCUserDefault::sharedUserDefault()->getStringForKey(str,"");
    sprintf(str,"s%d_ititaId",cacheServerId);
    std::string ititaId = CCUserDefault::sharedUserDefault()->getStringForKey(str,"");
    if (cacheNickname.compare("") != 0 && !(ititaId.compare("") != 0 && ititaId.compare(PulsarNative::getDeviceId()) != 0)) {
        registerNicknameTextField->setString(cacheNickname.c_str());
    }
    
    light4->setUserObject(registerNicknameTextField);
    layer->addChild(registerNicknameTextField);

    ////
    
    
    CCLabelTTF* mail = CCLabelTTF::create("QQ号码:","Arial",35);
    mail->setPosition(ccp(winSize.width/2-270,380));
    mail->setColor(ccc3(255,222,0));
    layer->addChild(mail);
    
    
    CCSprite* sprite5 = CCSprite::createWithSpriteFrameName("serverMetalEditText.png");
    sprite5->setScale(1.5);
    sprite5->setContentSize(CCSizeMake(sprite5->getContentSize().width*1.5,sprite5->getContentSize().height*1.5));
    MyMenuItem* light5 = MyMenuItem::create(sprite5,this,menu_selector(ServerScene::toAttachIME));
    light5->setPosition(ccp(winSize.width/2-30,380));
    
    if (registerMailTextField == NULL) {
        registerMailTextField = CCTextFieldTTF::textFieldWithPlaceHolder("",CCSizeMake(light5->getContentSize().width,light5->getContentSize().height), kCCTextAlignmentLeft,"Arial",30);
        //    loginUsernameTextField->setColor(ccc3(254,185,0));
        registerMailTextField->setPosition(ccp(winSize.width/2-25,380));
        registerMailTextField->setAnchorPoint(ccp(0.5,0.5));
        registerMailTextField->setDelegate(this);
        CC_SAFE_RETAIN(registerMailTextField);
    }
    
    light5->setUserObject(registerMailTextField);
    layer->addChild(registerMailTextField);
    
    
////
    

    CCLabelTTF* signature = CCLabelTTF::create("签名档:","Arial",35);
    signature->setPosition(ccp(winSize.width/2-270,320));
    signature->setColor(ccc3(255,222,0));
    layer->addChild(signature);
    
    
    CCSprite* sprite6 = CCSprite::createWithSpriteFrameName("serverMetalEditText.png");
    sprite6->setScaleX(2.3);
    sprite6->setScaleY(4.5);
    sprite6->setContentSize(CCSizeMake(sprite6->getContentSize().width*2.3,sprite6->getContentSize().height*4.5));
    MyMenuItem* light6 = MyMenuItem::create(sprite6,this,menu_selector(ServerScene::toAttachIME));
    light6->setPosition(ccp(winSize.width/2+50,275));
    
    if (registerSignatureTextField == NULL) {
        registerSignatureTextField = CCTextFieldTTF::textFieldWithPlaceHolder("输入签名在40字以内",CCSizeMake(light6->getContentSize().width-10,light6->getContentSize().height), kCCTextAlignmentLeft,"Arial",30);
        //    loginUsernameTextField->setColor(ccc3(254,185,0));
        registerSignatureTextField->setPosition(ccp(winSize.width/2+55,275));
        registerSignatureTextField->setAnchorPoint(ccp(0.5,0.5));
        registerSignatureTextField->setDelegate(this);
        CC_SAFE_RETAIN(registerSignatureTextField);
    }
    
    light6->setUserObject(registerSignatureTextField);
    layer->addChild(registerSignatureTextField);
    
    /////
    
    CCLabelTTF* avatarLabel = CCLabelTTF::create("选择头像:","Arial",35);
    avatarLabel->setPosition(ccp(winSize.width/2-270,200));
    avatarLabel->setColor(ccc3(255,222,0));
    layer->addChild(avatarLabel);
    
    
    
    CCSprite* sprite7 = CCSprite::createWithSpriteFrameName("serverRegisterLabelButton.png");
    sprite7->setScale(2);
    sprite7->setContentSize(CCSizeMake(sprite7->getContentSize().width*2,sprite7->getContentSize().height*2));
    
    MyMenuItem* loginButton = MyMenuItem::create(sprite7,this,menu_selector(ServerScene::toSureRegister));
    
    loginButton->setPosition(ccp(winSize.width/2+250,120));
    
    GXShieldTouchMenuItem* shieldItem = GXShieldTouchMenuItem::create();
    shieldItem->setPosition(ccp(winSize.width/2,winSize.height/2-30));
    shieldItem->setContentSize(winSize);
    
    MyPriorityMenu* menu = MyPriorityMenu::create(-502,light1,light2,light3,light4,light5,light6,loginButton,shieldItem,NULL);
    menu->setPosition(ccp(0,0));
    
    CCSprite* avatar = CCSprite::createWithSpriteFrameName("avatar0.png");
    avatar->setScale(1.3);
    avatar->setContentSize(CCSizeMake(avatar->getContentSize().width*1.3,avatar->getContentSize().height*1.3));
    CCSprite* kuang = MyUtil::getInstance()->getLineBox(86,86);
    kuang->setPosition(ccp(avatar->getContentSize().width/2-10,avatar->getContentSize().height/2-10));
    avatar->addChild(kuang);
    
    CCMenuItemSprite* avatarButton = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("avatar0.png"),avatar,NULL,NULL);
    
    avatarButton->setPosition(winSize.width/2-130,130);
    
    
    GXRadioMenu* avatarMenu = GXRadioMenu::create(-502,avatarButton,NULL);
    avatarMenu->setPosition(ccp(0,0));

    layer->addChild(menu);
    layer->addChild(avatarMenu);
    
}

void ServerScene::toAttachIME(CCMenuItem* item) {
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sfx_click.mp3");
    CCTextFieldTTF* textField = (CCTextFieldTTF*)item->getUserObject();
    textField->attachWithIME();
}

void ServerScene::toSureRegister() {
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sfx_click.mp3");
    const char* str = registerUsernameTextField->getString();
    bool flag = GXUtil::checkWordandNum(str) && strlen(str)<=11 && strlen(str)>=4 ;
    if(!flag) {
        this->addChild(MyUtil::getInstance()->getServerTipDialog("请输入正确的账号\n4-11个英文或数字"),10);
        return;
    }
    str = registerPasswordTextField->getString();
    flag = GXUtil::checkWordandNum(str) && strlen(str)<=11 && strlen(str)>=6 ;
    if(!flag) {
        this->addChild(MyUtil::getInstance()->getServerTipDialog("请输入正确的密码\n6-11个英文或数字"),10);
        return;
    }
    const char* str2 = registerSurePasswordTextField->getString();
    flag = (strcmp(str,str2) == 0);
    if (!flag) {
        this->addChild(MyUtil::getInstance()->getServerTipDialog("两次密码输入不一致"),10);
        return;
    }
    str = registerNicknameTextField->getString();
    flag = (strlen(str) <= 18 && strlen(str)>=1);
    if (!flag) {
        this->addChild(MyUtil::getInstance()->getServerTipDialog("昵称请在6字以内"),10);
        return;
    }
    str = registerSignatureTextField->getString();
    flag = (strlen(str) <= 120);
    if (!flag) {
        this->addChild(MyUtil::getInstance()->getServerTipDialog("签名档请在40字以内"),10);
        return;
    }
    
    CCLayer* tipLayer = CCLayer::create();
    CCSprite* black = CCSprite::create("whiteImage.jpg");
    black->setScaleX(winSize.width/black->getContentSize().width);
    black->setScaleY(winSize.height/black->getContentSize().height);
    black->setPosition(ccp(winSize.width/2,winSize.height/2));
    black->setColor(ccc3(0,0,0));
    black->setOpacity(200);
    
    tipLayer->addChild(black);
    CCSprite* back= MyUtil::getInstance()->getServerTipBack(600,338);
    back->setPosition(ccp(winSize.width/2,winSize.height/2));
    tipLayer->addChild(back);
    
    CCMenuItemSprite* cancelItem =CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("dialogcancel.png"), CCSprite::createWithSpriteFrameName("dialogcancelp.png"),this,menu_selector(MyUtil::cancelTipItem));
    cancelItem->setPosition(ccp(winSize.width/2-100,winSize.height/2-110));
    
    CCMenuItemSprite* sureItem =CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("dialogsure.png"), CCSprite::createWithSpriteFrameName("dialogsurep.png"),this,menu_selector(ServerScene::registerGameWait));
    
    sureItem->setPosition(ccp(winSize.width/2+100,winSize.height/2-110));
    
    GXShieldTouchMenuItem* shieldTouch= GXShieldTouchMenuItem::create();
    shieldTouch->setContentSize(winSize);
    shieldTouch->setPosition(ccp(winSize.width/2,winSize.height/2));
    
    MyPriorityMenu* menu = MyPriorityMenu::create(-504,sureItem,cancelItem,shieldTouch,NULL);
    menu->setPosition(ccp(0,0));
    tipLayer->addChild(menu);
    
    char str3[300] = {0};
    sprintf(str3,"账号:%s", registerUsernameTextField->getString());
    CCLabelTTF* username =CCLabelTTF::create(str3,"Arial",30);
    username->setAnchorPoint(ccp(0,0.5));
    username->setPosition(ccp(winSize.width/2-230,winSize.height/2+80));
    username->setColor(ccc3(255,222,0));
    tipLayer->addChild(username);
    
    sprintf(str3,"密码:%s", registerPasswordTextField->getString());
    CCLabelTTF* password =CCLabelTTF::create(str3,"Arial",30);
    password->setAnchorPoint(ccp(0,0.5));
    password->setPosition(ccp(winSize.width/2-230,winSize.height/2+20));
    password->setColor(ccc3(255,222,0));
    tipLayer->addChild(password);
    
    sprintf(str3,"昵称:%s", registerNicknameTextField->getString());
    CCLabelTTF* nickname =CCLabelTTF::create(str3,"Arial",30);
    nickname->setAnchorPoint(ccp(0,0.5));
    nickname->setPosition(ccp(winSize.width/2-230,winSize.height/2-40));
    nickname->setColor(ccc3(255,222,0));
    tipLayer->addChild(nickname);
    
    sprintf(str3,"QQ:%s", registerMailTextField->getString());
    CCLabelTTF* qq =CCLabelTTF::create(str3,"Arial",30);
    qq->setAnchorPoint(ccp(0,0.5));
    qq->setPosition(ccp(winSize.width/2+60,winSize.height/2+80));
    qq->setColor(ccc3(255,222,0));
    tipLayer->addChild(qq);
    
    CCLabelTTF* avatarLabel =CCLabelTTF::create("头像:","Arial",30);
    avatarLabel->setAnchorPoint(ccp(0,0.5));
    avatarLabel->setPosition(ccp(winSize.width/2+60,winSize.height/2+20));
    avatarLabel->setColor(ccc3(255,222,0));
    tipLayer->addChild(avatarLabel);
    
    CCSprite* avatarSprite = CCSprite::createWithSpriteFrameName("avatar0.png");
    avatarSprite->setScale(1.3);
    avatarSprite->setPosition(ccp(winSize.width/2+190,winSize.height/2-20));
    tipLayer->addChild(avatarSprite);
    
    this->addChild(tipLayer,6);
}

void ServerScene::dismissTip(CCNode* pSender) {
    pSender->getParent()->getParent()->removeFromParentAndCleanup(true);
}

void ServerScene::loginEnterGameWait() {
    this->addChild(MyUtil::getInstance()->getWaitLayer("正在登陆账号"),15);
    this->scheduleOnce(schedule_selector(ServerScene::loginEnterGame),0.5);
}

void ServerScene::loginEnterGame() {
    
    CCLog("服务器名字为：%s",selectBean->getServerName()->getCString());
    if(selectBean->serverStatusId == weihuTag){
        this->removeChildByTag(waitMenuTag,true);
        this->addChild(MyUtil::getInstance()->getServerTipDialog("服务器正在维护,详\n情请关注官方QQ群"),10);
    } else if(selectBean->serverStatusId == baomanTag){
        this->removeChildByTag(waitMenuTag,true);
        this->addChild(MyUtil::getInstance()->getServerTipDialog("服务器已经爆满,\n请稍微等待或进入\n新服游玩"),10);
    } else  {
        if (MyHttpConnection::getInstance()->initSocket(selectBean->getHostUrl()->getCString(),selectBean->serverId)) {
            UserBean* bean = UserBean::create();
            bean->setItitaId(CCString::create(loginUsernameTextField->getString()));
            bean->setPassword(CCString::create(loginPasswordTextField->getString()));
            setCacheChatServerUrl(selectBean->getChatServerUrl());
            MyHttpConnection::getInstance()->sendLogin(bean,false);
        } else {
            this->removeChildByTag(waitMenuTag,true);
            this->addChild(MyUtil::getInstance()->getServerTipDialog("服务器连接异常\n请检查网络后重试"),10);
        }
    } 
}

void ServerScene::fastEnterGameWait() {
    this->addChild(MyUtil::getInstance()->getWaitLayer("正在进入游戏"),15);
    this->scheduleOnce(schedule_selector(ServerScene::fastEnterGame),0.5);
}

void ServerScene::fastEnterGame() {
    
    CCLog("服务器名字为：%s",selectBean->getServerName()->getCString());
    if(selectBean->serverStatusId == weihuTag){
        this->removeChildByTag(waitMenuTag,true);
        this->addChild(MyUtil::getInstance()->getServerTipDialog("服务器正在维护,详\n情请关注官方QQ群"),10);
    } else if(selectBean->serverStatusId == baomanTag){
        this->removeChildByTag(waitMenuTag,true);
        this->addChild(MyUtil::getInstance()->getServerTipDialog("服务器已经爆满,\n请稍微等待或进入\n新服游玩"),10);
    } else  {
        char str[30] = {0};
        if (MyHttpConnection::getInstance()->initSocket(selectBean->getHostUrl()->getCString(),selectBean->serverId)) {
            UserBean* bean = UserBean::create();
            sprintf(str,"s%d_ititaId",cacheServerId);
            std::string ititaId = CCUserDefault::sharedUserDefault()->getStringForKey(str,"");
            setCacheChatServerUrl(selectBean->getChatServerUrl());
            if (ititaId.compare("") != 0) {
                isFast = true;
                bean->setItitaId(CCString::create(ititaId.c_str()));
                sprintf(str,"s%d_password",cacheServerId);
                bean->setPassword(CCString::create(CCUserDefault::sharedUserDefault()->getStringForKey(str,"").c_str()));
                MyHttpConnection::getInstance()->sendLogin(bean,false);
            } else {
                MyHttpConnection::getInstance()->sendFastEnterGame(false);
            }
        } else {
            this->removeChildByTag(waitMenuTag,true);
            this->addChild(MyUtil::getInstance()->getServerTipDialog("服务器连接异常\n请检查网络后重试"),10);
        }
    } 
}

void ServerScene::registerGameWait() {
    this->addChild(MyUtil::getInstance()->getWaitLayer("正在注册账号"),15);
    this->scheduleOnce(schedule_selector(ServerScene::registerGame),0.5);
}

void ServerScene::registerGame() {
   
    CCLog("服务器名字为：%s",selectBean->getServerName()->getCString());
    if(selectBean->serverStatusId == weihuTag){
        this->removeChildByTag(waitMenuTag,true);
        this->addChild(MyUtil::getInstance()->getServerTipDialog("服务器正在维护,详\n情请关注官方QQ群"),10);
    } else if(selectBean->serverStatusId == baomanTag){
        this->removeChildByTag(waitMenuTag,true);
        this->addChild(MyUtil::getInstance()->getServerTipDialog("服务器已经爆满,\n请稍微等待或进入\n新服游玩"),10);
    } else  {
        if (MyHttpConnection::getInstance()->initSocket(selectBean->getHostUrl()->getCString(),selectBean->serverId)) {
            UserBean* bean = UserBean::create();
            bean->setItitaId(CCString::create(registerUsernameTextField->getString()));
            bean->setPassword(CCString::create(registerPasswordTextField->getString()));
            bean->setNickname(CCString::create(registerNicknameTextField->getString()));
            bean->setQQ(CCString::create(registerMailTextField->getString()));
            bean->setSignature(CCString::create(registerSignatureTextField->getString()));
            bean->setAvatar(CCString::create("avatar.png"));
            setCacheChatServerUrl(selectBean->getChatServerUrl());
            MyHttpConnection::getInstance()->sendRegister(bean);
        } else {
            this->removeChildByTag(waitMenuTag,true);
            this->addChild(MyUtil::getInstance()->getServerTipDialog("服务器连接异常\n请检查网络后重试"),10);
        }
    }
}

void ServerScene::toStartScene() {
    PushTrigger::getInstance()->connectCode = reconncetTag;
    CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.2, TransitonScene::create(startSceneTag,CCString::create("true")), ccBLACK));
}

UserBean* UserBean::create() {
    UserBean* userbean = new UserBean();
    userbean->autorelease();
    return userbean;
}

void ServerScene::keyBackClicked() {
    CCDirector::sharedDirector()->end();
}

void ServerScene::onEnter() {
    GXBaseScene::onEnter();
    CCDirector::sharedDirector()->getKeypadDispatcher()->addDelegate(this);
}

void ServerScene::onExit() {
    GXBaseScene::onExit();
    CCDirector::sharedDirector()->getKeypadDispatcher()->removeDelegate(this);
}

void ServerScene::onEnterTransitionDidFinish() {
    MyGameInfo::getInstance()->clear();
    MyGameInfo::getInstance()->creatorArray->removeAllObjects();
    PushTrigger::getInstance()->clear();
    QuestManager::getInstance()->clear();
    if (MyHttpConnection::isConn == true) {
        CCDirector::sharedDirector()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
        exit(0);
#endif
    }
    if (GXChatHandler::isConn == true) {
        GXChatHandler::getInstance()->sendDisconnect();
    }
}

void ServerScene::exitGame() {
    CCDirector::sharedDirector()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

void ServerScene::updateGame() {
    PulsarNative::toUpdateGame();
    CCDirector::sharedDirector()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

//void ServerScene::onEnterTransitionDidFinish() {
//    GXBaseScene::onEnterTransitionDidFinish();
//    loadResource();
//    init();
//}

SeverInfoBean* SeverInfoBean::create() {
    SeverInfoBean* bean = new SeverInfoBean();
    bean->autorelease();
    return bean;
}


