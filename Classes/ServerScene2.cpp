//
//  ServerScene2.cpp
//  ww4
//
//  Created by xiao tang on 13-9-17.
//
//

#include "ServerScene2.h"
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

ServerScene2::ServerScene2(){

}


ServerScene2* ServerScene2::create() {
    ServerScene2* scene = new ServerScene2();
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

void ServerScene2::myInit() {
    
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

void ServerScene2::initServerInfo(SeverInfoBean* bean) {
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
        leftButton->setTarget(this,menu_selector(ServerScene2::toLogin));
    } else {
        registLabel = CCSprite::createWithSpriteFrameName("serverBindLabel.png");
        leftButton->setTarget(this,menu_selector(ServerScene2::toRegister));
    }
    registLabel->setAnchorPoint(ccp(0,0.5));
    registLabel->setPosition(ccp(30,leftButton->getContentSize().height/2));
    leftButton->addChild(registLabel);
    
    
    
    MyMenuItem* rightButton = MyMenuItem::create(CCSprite::createWithSpriteFrameName("serverButton.png"),this,menu_selector(ServerScene2::fastEnterGameWait));
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
    
    sprintf(str,"s%d_nickname",bean->serverId);
    std::string nickname = CCUserDefault::sharedUserDefault()->getStringForKey(str,"");
    
    if (nickname.compare("") != 0) {
        CCLabelTTF* id = CCLabelTTF::create("ID:","Arial",40);
        id->setColor(ccc3(255,222,0));
        
        CCLabelTTF* nicknameLabel = CCLabelTTF::create(nickname.c_str(),"Arial",40);
        float locx = id->getContentSize().width+nicknameLabel->getContentSize().width;
        id->setAnchorPoint(ccp(0,0.5));
        id->setPosition(ccp(winSize.width-locx/2-180,400));
        nicknameLabel->setAnchorPoint(ccp(0,0.5));
        nicknameLabel->setPosition(ccp(winSize.width-locx/2+id->getContentSize().width-190,400));
        serverInfoLayer->addChild(id);
        serverInfoLayer->addChild(nicknameLabel);
    }
    
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
    
    MyMenuItem* selectServerButton = MyMenuItem::create(CCSprite::createWithSpriteFrameName("serverButton.png"),this,menu_selector(ServerScene2::toServerList));
    
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


void ServerScene2::loadResource() {
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

void ServerScene2::toLogin() {
    
    CCNode* node = this->getChildByTag(loginLayerTag);
    if (node != NULL) {
        node->removeAllChildrenWithCleanup(true);
        node->removeFromParentAndCleanup(true);
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
    
    
    CCSprite* loginButtonSprite = CCSprite::createWithSpriteFrameName("serverDialogButton.png");
    CCSprite* loginButtonLabel = CCSprite::createWithSpriteFrameName("serverLoginLabelButton.png");
    loginButtonLabel->setPosition(ccp(loginButtonSprite->getContentSize().width/2,loginButtonSprite->getContentSize().height/2));
    loginButtonSprite->addChild(loginButtonLabel);
    
    CCSprite* loginButtonSpriteP = CCSprite::createWithSpriteFrameName("serverDialogButtonP.png");
    CCSprite* loginButtonLabel2 = CCSprite::createWithSpriteFrameName("serverLoginLabelButtonP.png");
    loginButtonLabel2->setPosition(ccp(loginButtonSpriteP->getContentSize().width/2,loginButtonSpriteP->getContentSize().height/2));
    loginButtonSpriteP->addChild(loginButtonLabel2);
    
    CCMenuItemSprite*  loginButton = CCMenuItemSprite::create(loginButtonSprite,loginButtonSpriteP,this,menu_selector(ServerScene2::toDisplayLogin));
    loginButton->setPosition(ccp(0,40));
    
    CCSprite* registerButtonSprite = CCSprite::createWithSpriteFrameName("serverDialogButton.png");
    CCSprite* registerButtonLabel = CCSprite::createWithSpriteFrameName("serverRegisterButtonLabel.png");
    registerButtonLabel->setPosition(ccp(registerButtonSprite->getContentSize().width/2,registerButtonSprite->getContentSize().height/2));
    registerButtonSprite->addChild(registerButtonLabel);
    
    CCSprite* registerButtonSpriteP = CCSprite::createWithSpriteFrameName("serverDialogButtonP.png");
    CCSprite* registerButtonLabel2 = CCSprite::createWithSpriteFrameName("serverRegisterButtonLabelP.png");
    registerButtonLabel2->setPosition(ccp(registerButtonSpriteP->getContentSize().width/2,registerButtonSpriteP->getContentSize().height/2));
    registerButtonSpriteP->addChild(registerButtonLabel2);
    
    CCMenuItemSprite*  registerButton = CCMenuItemSprite::create(registerButtonSprite,registerButtonSpriteP,this,menu_selector(ServerScene2::toDisplayRegister));
    registerButton->setPosition(ccp(25,-25));
    
    GXRadioMenu* menu = GXRadioMenu::create(-503,loginButton,registerButton,NULL);
    menu->setPosition(ccp(winSize.width-1100,550+580));
//    menu->alignItemsVerticallyWithPadding(10);
    
    loginLayer->addChild(menu);
    
    
    //    this->getChildByTag(charDialogTag)->runAction(CCEaseElasticOut::create(CCMoveTo::create(0.35, ccp(-16,0)), 1));
    
    this->addChild(loginLayer,3);
    
}

//

void ServerScene2::toRegister() {
    
    
    if (this->getChildByTag(loginLayerTag) != NULL) {
        return;
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
    
    
    CCSprite* loginButtonSprite = CCSprite::createWithSpriteFrameName("serverDialogButton.png");
    CCSprite* loginButtonLabel = CCSprite::createWithSpriteFrameName("serverLoginLabelButton.png");
    loginButtonLabel->setPosition(ccp(loginButtonSprite->getContentSize().width/2,loginButtonSprite->getContentSize().height/2));
    loginButtonSprite->addChild(loginButtonLabel);
    
    CCSprite* loginButtonSpriteP = CCSprite::createWithSpriteFrameName("serverDialogButtonP.png");
    CCSprite* loginButtonLabel2 = CCSprite::createWithSpriteFrameName("serverLoginLabelButtonP.png");
    loginButtonLabel2->setPosition(ccp(loginButtonSpriteP->getContentSize().width/2,loginButtonSpriteP->getContentSize().height/2));
    loginButtonSpriteP->addChild(loginButtonLabel2);
    
    CCMenuItemSprite*  loginButton = CCMenuItemSprite::create(loginButtonSprite,loginButtonSpriteP,this,menu_selector(ServerScene2::toDisplayLogin));
    loginButton->setPosition(ccp(0,40));
    
    CCSprite* registerButtonSprite = CCSprite::createWithSpriteFrameName("serverDialogButton.png");
    CCSprite* registerButtonLabel = CCSprite::createWithSpriteFrameName("serverRegisterButtonLabel.png");
    registerButtonLabel->setPosition(ccp(registerButtonSprite->getContentSize().width/2,registerButtonSprite->getContentSize().height/2));
    registerButtonSprite->addChild(registerButtonLabel);
    
    CCSprite* registerButtonSpriteP = CCSprite::createWithSpriteFrameName("serverDialogButtonP.png");
    CCSprite* registerButtonLabel2 = CCSprite::createWithSpriteFrameName("serverRegisterButtonLabelP.png");
    registerButtonLabel2->setPosition(ccp(registerButtonSpriteP->getContentSize().width/2,registerButtonSpriteP->getContentSize().height/2));
    registerButtonSpriteP->addChild(registerButtonLabel2);
    
    CCMenuItemSprite*  registerButton = CCMenuItemSprite::create(registerButtonSprite,registerButtonSpriteP,this,menu_selector(ServerScene2::toDisplayRegister));
    registerButton->setPosition(ccp(25,-25));
    
    GXRadioMenu* menu = GXRadioMenu::create(-503,registerButton,loginButton,NULL);
    menu->setPosition(ccp(winSize.width-1100,550+740));
    
    loginLayer->addChild(menu);
    
    this->addChild(loginLayer,3);
    
}

void ServerScene2::toServerList() {
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
        
        
        MyMenuItem* serverItem = MyMenuItem::create(layer,this,menu_selector(ServerScene2::toChangeServer));
        
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
    
    MyMenuItem* cancelButton = MyMenuItem::create(sprite2,this,menu_selector(ServerScene2::toCancelServer));
    cancelButton->setPosition(ccp(-170,50));
    MyPriorityMenu* menu = MyPriorityMenu::create(-508,cancelButton,NULL);
    menu->setPosition(ccp(0,0));
    displayLayer->addChild(menu);
    
    this->addChild(loginLayer,1);
    
}

void ServerScene2::toDisplayLogin(CCMenuItem* item) {
    
    char str[30] = {0};
    
    if (item->getParent()->getPosition().y > 960) {
        item->getParent()->runAction(CCEaseElasticOut::create(CCMoveTo::create(0.35, ccp(winSize.width-900,565)), 1));
        CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sfx_popCreator.mp3");
    }
    CCNode* parent = this->getChildByTag(loginLayerTag)->getChildByTag(loginDisplayLayerTag);
    
    if (parent->getPosition().y <240) {
        CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sfx_popCreator.mp3");
    }
    parent->runAction(CCEaseElasticOut::create(CCMoveTo::create(0.35, ccp(winSize.width-430,380)), 1));
    
    parent->removeChildByTag(displayJiemianLayerTag,true);
    
    CCLayer* layer = CCLayer::create();
    parent->addChild(layer);
    layer->setTag(displayJiemianLayerTag);
    
    CCSprite* username = CCSprite::createWithSpriteFrameName("serverUsernameLabel.png");
    username->setPosition(ccp(-360,200));
    layer->addChild(username);
    
    
    
    CCSprite* sprite1 = CCSprite::createWithSpriteFrameName("serverMetalEditText.png");
    
    MyMenuItem* light1 = MyMenuItem::create(sprite1,this,menu_selector(ServerScene::toAttachIME));
    light1->setPosition(ccp(-205,200));
    
    
    
    if (loginUsernameTextField == NULL) {
        loginUsernameTextField = CCTextFieldTTF::textFieldWithPlaceHolder("",CCSizeMake(light1->getContentSize().width,light1->getContentSize().height), kCCTextAlignmentLeft,"Arial",27);
        //    loginUsernameTextField->setColor(ccc3(254,185,0));
        loginUsernameTextField->setPosition(ccp(-195,200));
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
    layer->addChild(loginUsernameTextField,2);
    
    
    CCSprite* password = CCSprite::createWithSpriteFrameName("serverPasswordLabel.png");
    password->setPosition(ccp(-345,150));
    layer->addChild(password);
    
    
    CCSprite* sprite2 = CCSprite::createWithSpriteFrameName("serverMetalEditText.png");
    MyMenuItem* light2 = MyMenuItem::create(sprite2,this,menu_selector(ServerScene::toAttachIME));
    light2->setPosition(ccp(-190,150));
    if (loginPasswordTextField == NULL) {
        loginPasswordTextField = CCTextFieldTTF::textFieldWithPlaceHolder("",CCSizeMake(light2->getContentSize().width,light2->getContentSize().height), kCCTextAlignmentLeft,"Arial",27);
        //    loginUsernameTextField->setColor(ccc3(254,185,0));
        loginPasswordTextField->setPosition(ccp(-180,150));
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
    layer->addChild(loginPasswordTextField,2);
    
    CCSprite* sprite3 = CCSprite::createWithSpriteFrameName("serverLoginButton.png");
//    sprite3->setScale(1.3);
    sprite3->setContentSize(CCSizeMake(sprite3->getContentSize().width*1.5,sprite3->getContentSize().height*1.5));
    
    MyMenuItem* loginButton = MyMenuItem::create(sprite3,this,menu_selector(ServerScene::loginEnterGameWait));
    
    loginButton->setPosition(ccp(-195,65));
    
    MyPriorityMenu* menu = MyPriorityMenu::create(-502,light1,light2,loginButton,NULL);
    
    menu->setPosition(ccp(0,0));
    layer->addChild(menu);
    
    
}

void ServerScene2::toDisplayRegister(CCMenuItem* item) {
    
    char str[30] = {0};
    
    if (item->getParent()->getPosition().y > 960) {
        item->getParent()->runAction(CCEaseElasticOut::create(CCMoveTo::create(0.35, ccp(winSize.width-900,565)), 1));
    }
    CCNode* parent = this->getChildByTag(loginLayerTag)->getChildByTag(loginDisplayLayerTag);
    
    if (parent->getPosition().y >240) {
        CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sfx_popCreator.mp3");
    }
//    parent->runAction(CCEaseElasticOut::create(CCMoveTo::create(0.35, ccp(0,30)), 1));
    parent->runAction(CCEaseElasticOut::create(CCMoveTo::create(0.35, ccp(winSize.width-372,220)), 1));
    
    parent->removeChildByTag(displayJiemianLayerTag,true);
    
    CCLayer* layer = CCLayer::create();
    parent->addChild(layer);
    layer->setTag(displayJiemianLayerTag);
    
    CCSprite* username = CCSprite::createWithSpriteFrameName("serverInputUsernameLabel.png");
    username->setPosition(ccp(-425,380));
    layer->addChild(username);
    
    
//    CCLabelTTF* usernamePS = CCLabelTTF::create("注:首次注册绑定\n“快速登陆”账号","Arial",20);
//    usernamePS->setPosition(ccp(winSize.width/2+120,580));
//    usernamePS->setAnchorPoint(ccp(0,0.5));
//    usernamePS->setColor(ccc3(255,222,0));
//    layer->addChild(usernamePS);
    
    
    CCSprite* sprite1 = CCSprite::createWithSpriteFrameName("serverMetalEditText.png");
    
    MyMenuItem* light1 = MyMenuItem::create(sprite1,this,menu_selector(ServerScene::toAttachIME));
    light1->setPosition(ccp(-255,380));
    
    if (registerUsernameTextField == NULL) {
        registerUsernameTextField = CCTextFieldTTF::textFieldWithPlaceHolder("输入4-11位英文或数字",CCSizeMake(light1->getContentSize().width,21), kCCTextAlignmentLeft,"Arial",21);
        //    loginUsernameTextField->setColor(ccc3(254,185,0));
        registerUsernameTextField->setPosition(ccp(-245,380));
        registerUsernameTextField->setAnchorPoint(ccp(0.5,0.5));
        registerUsernameTextField->setDelegate(this);
        CC_SAFE_RETAIN(registerUsernameTextField);
    }
    
    light1->setUserObject(registerUsernameTextField);
    layer->addChild(registerUsernameTextField,2);
    
    CCSprite* password = CCSprite::createWithSpriteFrameName("serverInputPasswordLabel.png");
    password->setPosition(ccp(-408,335));
    layer->addChild(password);
    
//    CCLabelTTF* passwordXing = CCLabelTTF::create("※","Arial",25);
//    passwordXing->setPosition(ccp(winSize.width/2-363,533));
//    passwordXing->setColor(ccc3(255,0,0));
//    layer->addChild(passwordXing);
    
    CCSprite* sprite2 = CCSprite::createWithSpriteFrameName("serverMetalEditText.png");

    MyMenuItem* light2 = MyMenuItem::create(sprite2,this,menu_selector(ServerScene::toAttachIME));
    light2->setPosition(ccp(-238,335));
    
    if (registerPasswordTextField == NULL) {
        registerPasswordTextField = CCTextFieldTTF::textFieldWithPlaceHolder("输入6-11位英文或数字",CCSizeMake(light2->getContentSize().width,21), kCCTextAlignmentLeft,"Arial",21);
        //    loginUsernameTextField->setColor(ccc3(254,185,0));
        registerPasswordTextField->setPosition(ccp(-228,335));
        registerPasswordTextField->setAnchorPoint(ccp(0.5,0.5));
        registerPasswordTextField->setDelegate(this);
        CC_SAFE_RETAIN(registerPasswordTextField);
    }
    
    light2->setUserObject(registerPasswordTextField);
    layer->addChild(registerPasswordTextField,2);
    
    ////
    
    
    CCSprite* surePass = CCSprite::createWithSpriteFrameName("serverSurePasswordLabel.png");
    surePass->setPosition(ccp(-391,290));
    layer->addChild(surePass);

    CCSprite* sprite3 = CCSprite::createWithSpriteFrameName("serverMetalEditText.png");
    
    MyMenuItem* light3 = MyMenuItem::create(sprite3,this,menu_selector(ServerScene::toAttachIME));
    light3->setPosition(ccp(-221,290));
    
    if (registerSurePasswordTextField == NULL) {
        registerSurePasswordTextField = CCTextFieldTTF::textFieldWithPlaceHolder("再次输入上面的密码",CCSizeMake(light3->getContentSize().width,21), kCCTextAlignmentLeft,"Arial",21);
        //    loginUsernameTextField->setColor(ccc3(254,185,0));
        registerSurePasswordTextField->setPosition(ccp(-211,290));
        registerSurePasswordTextField->setAnchorPoint(ccp(0.5,0.5));
        registerSurePasswordTextField->setDelegate(this);
        CC_SAFE_RETAIN(registerSurePasswordTextField);
    }
    
    light3->setUserObject(registerSurePasswordTextField);
    layer->addChild(registerSurePasswordTextField,2);
    
    ////
    
    CCSprite* nickname = CCSprite::createWithSpriteFrameName("serverInputNicknameLabel.png");
    nickname->setPosition(ccp(-374,245));
    layer->addChild(nickname);
    
    
    CCSprite* sprite4 = CCSprite::createWithSpriteFrameName("serverMetalEditText.png");

    MyMenuItem* light4 = MyMenuItem::create(sprite4,this,menu_selector(ServerScene::toAttachIME));
    light4->setPosition(ccp(-204,245));
    
    
    
    if (registerNicknameTextField == NULL) {
        registerNicknameTextField = CCTextFieldTTF::textFieldWithPlaceHolder("输入6位以下昵称",CCSizeMake(light4->getContentSize().width,21), kCCTextAlignmentLeft,"Arial",21);
        //    loginUsernameTextField->setColor(ccc3(254,185,0));
        registerNicknameTextField->setPosition(ccp(-194,245));
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
    layer->addChild(registerNicknameTextField,2);
    
    ////
    
    
    CCSprite* mail = CCSprite::createWithSpriteFrameName("serverInputQQLabel.png");
    mail->setPosition(ccp(-357,200));
    layer->addChild(mail);
    
    
    CCSprite* sprite5 = CCSprite::createWithSpriteFrameName("serverMetalEditText.png");
 
    MyMenuItem* light5 = MyMenuItem::create(sprite5,this,menu_selector(ServerScene::toAttachIME));
    light5->setPosition(ccp(-187,200));
    
    if (registerMailTextField == NULL) {
        registerMailTextField = CCTextFieldTTF::textFieldWithPlaceHolder("",CCSizeMake(light5->getContentSize().width,21), kCCTextAlignmentLeft,"Arial",21);
        //    loginUsernameTextField->setColor(ccc3(254,185,0));
        registerMailTextField->setPosition(ccp(-177,200));
        registerMailTextField->setAnchorPoint(ccp(0.5,0.5));
        registerMailTextField->setDelegate(this);
        CC_SAFE_RETAIN(registerMailTextField);
    }
    
    light5->setUserObject(registerMailTextField);
    layer->addChild(registerMailTextField,2);
    
    
    ////
    
    
    CCSprite* signature = CCSprite::createWithSpriteFrameName("serverInputSignatureLabel.png");
    signature->setPosition(ccp(-340,155));
    layer->addChild(signature);
    
    
    CCSprite* sprite6 = CCSprite::createWithSpriteFrameName("serverMetalEditText2.png");
    sprite6->setScale(1.9);
    sprite6->setContentSize(CCSizeMake(sprite6->getContentSize().width*1.9,sprite6->getContentSize().height*1.9));
    MyMenuItem* light6 = MyMenuItem::create(sprite6,this,menu_selector(ServerScene::toAttachIME));
    
    light6->setAnchorPoint(ccp(0.5,1));
    light6->setPosition(ccp(-170,168));
    
    if (registerSignatureTextField == NULL) {
        registerSignatureTextField = CCTextFieldTTF::textFieldWithPlaceHolder("输入签名在40字以内",CCSizeMake(light6->getContentSize().width-60,light6->getContentSize().height), kCCTextAlignmentLeft,"Arial",16);
        //    loginUsernameTextField->setColor(ccc3(254,185,0));
        registerSignatureTextField->setPosition(ccp(-170,163));
        registerSignatureTextField->setAnchorPoint(ccp(0.5,1));
        registerSignatureTextField->setDelegate(this);
        CC_SAFE_RETAIN(registerSignatureTextField);
    }
    
    light6->setUserObject(registerSignatureTextField);
    layer->addChild(registerSignatureTextField,2);
    
    /////
//    
//    CCSprite* avatarLabel = CCSprite::createWithSpriteFrameName("serverInputChooseAvatarLabelpng");
//    avatarLabel->setPosition(ccp(-300,60));
//    layer->addChild(avatarLabel);
    
    
    
    CCSprite* sprite7 = CCSprite::createWithSpriteFrameName("serverRegisterLabelButton.png");
    sprite7->setScale(1.2);
    sprite7->setContentSize(CCSizeMake(sprite7->getContentSize().width*1.2,sprite7->getContentSize().height*1.2));
    
    MyMenuItem* loginButton = MyMenuItem::create(sprite7,this,menu_selector(ServerScene::toSureRegister));
    
    loginButton->setPosition(ccp(-100,25));
    
    GXShieldTouchMenuItem* shieldItem = GXShieldTouchMenuItem::create();
    shieldItem->setPosition(ccp(winSize.width/2,winSize.height/2-30));
    shieldItem->setContentSize(winSize);
    
    MyPriorityMenu* menu = MyPriorityMenu::create(-502,light1,light2,light3,light4,light5,light6,loginButton,shieldItem,NULL);
    menu->setPosition(ccp(0,0));
    
//    CCSprite* avatar = CCSprite::createWithSpriteFrameName("avatar0.png");
//    avatar->setScale(0.8);
//    avatar->setContentSize(CCSizeMake(avatar->getContentSize().width*0.8,avatar->getContentSize().height*0.8));
//    CCSprite* kuang = MyUtil::getInstance()->getLineBox(70,70);
//    kuang->setPosition(ccp(avatar->getContentSize().width/2,avatar->getContentSize().height/2));
//    avatar->addChild(kuang);
//    
//    CCMenuItemSprite* avatarButton = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("avatar0.png"),avatar,NULL,NULL);
//    
//    avatarButton->setPosition(-200,50);
//    
//    
//    GXRadioMenu* avatarMenu = GXRadioMenu::create(-502,avatarButton,NULL);
//    avatarMenu->setPosition(ccp(0,0));
//    
    layer->addChild(menu);
//    layer->addChild(avatarMenu);
    
}

void ServerScene2::toChangeServer(CCMenuItem* item) {
    item->setEnabled(false);
    
    SeverInfoBean* bean = (SeverInfoBean*)(item->getUserObject());
    initServerInfo(bean);
    CCUserDefault::sharedUserDefault()->setIntegerForKey("serverId",bean->serverId);
    CCUserDefault::sharedUserDefault()->flush();
    
    this->getChildByTag(loginLayerTag)->runAction(CCSequence::create(CCEaseElasticIn::create(CCMoveTo::create(0.35, ccp(-251,680)), 1),GXRemoveFromParentsAction::create(),NULL));
    
}

void ServerScene2::toCancelServer(CCMenuItem* item) {
    item->setEnabled(false);
    this->getChildByTag(loginLayerTag)->runAction(CCSequence::create(CCEaseElasticIn::create(CCMoveBy::create(0.35, ccp(-251,680)), 1),GXRemoveFromParentsAction::create(),NULL));
}

