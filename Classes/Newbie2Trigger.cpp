//
//  Newbie2Trigger.cpp
//  ww3
//
//  Created by xiao tang on 12-12-15.
//
//

#include "Newbie2Trigger.h"
#include "DefineSet.h"
#include "MyPriorityMenu.h"
#include "GXShieldTouchMenuItem.h"
#include "GXScaleTo.h"
#include "GXRepeatForever.h"
#include "MyMessageManage.h"
#include "SimpleAudioEngine.h"
#include "MyUtil.h"
#include "NewbieQuest1ToBattle.h"
#include "QuestManager.h"
#include "MyMenuItem.h"
#include "DiaLayer.h"
#include "GXJsonUtil.h"
#include "GXPlayAudioEffectCreator.h"

#define avatarMaskTag 60
#define newbieFlowLayerTag 900
#define grayTag 901
#define newbieMenuTag 902
#define questInfoLayer 1066

Newbie2Trigger::~Newbie2Trigger() {
    CCLog("Newbie2Trigger has been released");
}

Newbie2Trigger* Newbie2Trigger::create(NewbieStartScene* node) {
    Newbie2Trigger* trigger = new Newbie2Trigger();
    trigger->autorelease();
    trigger->scene = node;
    return trigger;
}


bool Newbie2Trigger::excuteMsg(MyBaseMessage* msg) {
//    if(dynamic_cast<Newbie1to2Message*>(msg) != NULL) {
//        MyMessageManage::getInstance()->unRegisterTrigger(this);
//    }
    if(msg->tag == DialogCompleteMessageTag) {
        toNextCallBack(NULL);
    }
    return false;
}

void Newbie2Trigger::toNextCallBack(cocos2d::CCNode *node) {
//    CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sfx_click.mp3");
//    if (status == 0) {
//        scene->removeChildByTag(avatarMaskTag, true);
//        CCLabelTTF* avatarLabel = CCLabelTTF::create("这里显示头像、昵称、等级还有经验。", "Arial" , transWindowToGLInRetina(15), CCSizeMake(transWindowToGLInRetina(100),transWindowToGLInRetina(150)), kCCTextAlignmentLeft, kCCVerticalTextAlignmentTop);
//        CCSprite* avatarLabel = CCSprite::createWithSpriteFrameName("newbielabel1.png");
//        avatarLabel->setScale(1.25);
//        scene->getChildByTag(newbieFlowLayerTag)->addChild(avatarLabel);
//        avatarLabel->setPosition(ccp(0,winSize.height-100));
//        avatarLabel->setAnchorPoint(ccp(0,1));
//        status++;
//    } else
    if(status == 0) {
//        scene->removeChildByTag(avatarMaskTag, true);
        
//        CCSprite* spotlight = (CCSprite*)scene->getChildByTag(newbieFlowLayerTag)->getChildByTag(grayTag);
//        spotlight->setScaleX(15);
//        spotlight->setScaleY(2.7);
//        spotlight->setPosition(ccp(winSize.width/2+170,winSize.height-20));
//
//        CCSprite* avartarMask = CCSprite::createWithSpriteFrameName("resourseBar.png");
//        avartarMask->setPosition(ccp(winSize.width/2,winSize.height));
//        avartarMask->setAnchorPoint(ccp(0.5,1));
//        avartarMask->setScale(1.25);
//        scene->addChild(avartarMask,19);
////        avartarMask->setOpacity(0);
//        avartarMask->runAction(CCRepeat::create(static_cast<CCSequence*>(CCSequence::create(CCSpawn::create(CCScaleTo::create(0.5,1.5),CCFadeOut::create(0.5),NULL),CCScaleTo::create(0,1.25),CCFadeIn::create(0),NULL)),4));
//        avartarMask->setTag(avatarMaskTag);
        
        CCSprite* resourseBar = CCSprite::createWithSpriteFrameName("resourseBar.png");
//        resourseBar->setAnchorPoint(ccp(0.5,1));
        resourseBar->setPosition(ccp(winSize.width/2,winSize.height/2));
        resourseBar->setOpacity(0);
        resourseBar->setScale(2);
        resourseBar->setTag(resourceBarTag);
        
        resourseBar->runAction(CCSequence::create(CCSpawn::create(CCFadeIn::create(0.3),CCScaleTo::create(0.3,1.25),CCEaseIn::create(CCMoveTo::create(0.5,ccp(winSize.width/2,winSize.height-resourseBar->getContentSize().height/2)),2),NULL),GXPlayAudioEffectAction::create(CCString::create("sfx_uicrash1.mp3")),NULL));
        
        scene->addChild(resourseBar, 20);
        status++;
    } else if(status == 1) {
        
        CCSprite* createSprite = CCSprite::createWithSpriteFrameName("createIcon.png");
        
        CCSprite* createBack = CCSprite::createWithSpriteFrameName("mainMenuBack.png");
        createBack->setPosition(ccp(createSprite->getContentSize().width/2,createSprite->getContentSize().height/2));
        createSprite->addChild(createBack,-1);
        createSprite->setPosition(ccp(winSize.width/2+150,winSize.height/2));
        createSprite->setScale(1.5);
        
        CCSprite* army = CCSprite::createWithSpriteFrameName("armyIcon.png");
        
        CCSprite* armyBack = CCSprite::createWithSpriteFrameName("mainMenuBack.png");
        armyBack->setPosition(ccp(army->getContentSize().width/2,army->getContentSize().height/2));
        army->addChild(armyBack,-1);
        army->setPosition(ccp(winSize.width/2-150,winSize.height/2));
        army->setScale(1.5);
        
        CCSprite* vip = CCSprite::createWithSpriteFrameName("vipIcon.png");
        
        
        CCSprite* vipBack = CCSprite::createWithSpriteFrameName("mainMenuBack.png");
        vipBack->setPosition(ccp(vip->getContentSize().width/2,vip->getContentSize().height/2));
        vip->addChild(vipBack,-1);
        vip->setPosition(ccp(winSize.width/2,winSize.height/2));
        vip->setScale(1.5);
        
        vip->runAction(CCSequence::create(CCDelayTime::create(0.9),CCSpawn::create(CCScaleTo::create(0.3,1),CCEaseIn::create(CCMoveTo::create(0.5,ccp(winSize.width-60,winSize.height/2+35)),2),NULL),GXPlayAudioEffectAction::create(CCString::create("sfx_uicrash.mp3")),NULL));
        
        army->runAction(CCSequence::create(CCDelayTime::create(0.6),CCSpawn::create(CCScaleTo::create(0.3,1),CCEaseIn::create(CCMoveTo::create(0.5,ccp(winSize.width-60,winSize.height/2+137)),2),NULL),GXPlayAudioEffectAction::create(CCString::create("sfx_uicrash.mp3")),NULL));
        
        createSprite->runAction(CCSequence::create(CCDelayTime::create(1.2),CCSpawn::create(CCScaleTo::create(0.3,1),CCEaseIn::create(CCMoveTo::create(0.5,ccp(winSize.width-60,winSize.height/2-73)),2),NULL),GXPlayAudioEffectAction::create(CCString::create("sfx_uicrash.mp3")),NULL));
        
        scene->addChild(vip, 20);
        scene->addChild(army, 20);
        scene->addChild(createSprite, 20);
        
        status++;
    }
//    else if(status == 2) {
//        scene->removeChildByTag(avatarMaskTag, true);
////        CCLabelTTF* avatarLabel = CCLabelTTF::create("这里显示你所拥有的资源，石油主要用于军事，钢铁主要用于建设，军令主要用于行动。", "Arial" , transWindowToGLInRetina(15), CCSizeMake(transWindowToGLInRetina(250),transWindowToGLInRetina(50)), kCCTextAlignmentLeft, kCCVerticalTextAlignmentTop);
//        CCSprite* avatarLabel = CCSprite::createWithSpriteFrameName("newbielabel2.png");
//        avatarLabel->setScale(1.25);
//        scene->getChildByTag(newbieFlowLayerTag)->addChild(avatarLabel);
//        avatarLabel->setPosition(ccp(winSize.width/2,winSize.height-40));
//        avatarLabel->setAnchorPoint(ccp(0.5,1));
//        status++;
//    }
    else if(status == 2) {
//        scene->removeChildByTag(avatarMaskTag, true);
        scene->getChildByTag(newbieFlowLayerTag)->getChildByTag(grayTag)->runAction(CCFadeTo::create(0.3,0));
//        CCLabelTTF* avatarLabel = CCLabelTTF::create("中间就是基地部分，可以自由的在上面建设。", "Arial" , transWindowToGLInRetina(15));
//        CCSprite* avatarLabel = CCSprite::createWithSpriteFrameName("newbielabel3.png");
//        avatarLabel->setScale(1.25);
//        scene->getChildByTag(newbieFlowLayerTag)->addChild(avatarLabel);
//        avatarLabel->setPosition(ccp(winSize.width/2,winSize.height/2));
//        avatarLabel->setAnchorPoint(ccp(0.5,0.5));
        status++;
    }else if(status == 3) {
        scene->removeChildByTag(newbieFlowLayerTag, true);
        CCLayer* newbieLayer = CCLayer::create();
        newbieLayer->setTag(newbieFlowLayerTag);
     
        MyBaseQuest* quest =  NewbieQuest1ToBattle::create();
        QuestManager::getInstance()->addQuest(quest);
//        scene->addDisplayQuest(quest);
        CCMenu* questMenu = (CCMenu*)scene->getChildByTag(UILayerTag)->getChildByTag(questMenuTag);
        MyMenuItem* questItem = MyMenuItem::create(CCSprite::createWithSpriteFrameName("questButton.png"),this,menu_selector(Newbie2Trigger::displayQuestInfoCallback));
        questItem->setScale(1.5);
        questItem->runAction(CCSequence::create(CCEaseElasticOut::create(CCScaleTo::create(0.8,1),1),CCCallFuncO::create(this,callfuncO_selector(Newbie2Trigger::shakeEffect2),questItem),NULL));
        
        CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sfx_missionAppear.mp3");
        CCSprite* questAppear = CCSprite::createWithSpriteFrameName("questAppear.png");
        questAppear->setPosition(ccp(questItem->getContentSize().width/2,questItem->getContentSize().height/2));
        questItem->getImage()->addChild(questAppear);
        questItem->setPosition(ccp(100,480));
        questItem->setUserData(quest);
        questMenu->addChild(questItem);
        
        
        CCSprite* sprite = CCSprite::create("spotlight.png");
        sprite->setScale(3.5);
        sprite->setAnchorPoint(ccp(0,1));
        sprite->setPosition(ccp(-720,winSize.height+392));
        
        CCSprite* fillBlack = CCSprite::create("whiteImage.jpg");
        fillBlack->setScaleY(winSize.height/fillBlack->getContentSize().height);
        fillBlack->setScaleX(200/fillBlack->getContentSize().width);
        fillBlack->setAnchorPoint(ccp(0,0));
        fillBlack->setPosition(ccp(958,0));
        fillBlack->setColor(ccc3(0,0,0));
        fillBlack->setOpacity(255*0.63);
        
        
        GXShieldTouchMenuItem* nextButton = GXShieldTouchMenuItem::create();
        nextButton->setContentSize(winSize);
        nextButton->setPosition(ccp(winSize.width/2,winSize.height/2));
        MyPriorityMenu* menu = MyPriorityMenu::create(-499, nextButton,NULL);
        menu->setPosition(ccp(0,0));
        menu->setTag(newbieMenuTag);
        
        //        nextButton->setContentSize(winSize);
        //        nextButton->setPosition(ccp(winSize.width-transWindowToGLInRetina(40),transWindowToGLInRetina(30)));
        
        CCLabelTTF* label = CCLabelTTF::create("有紧急任务！\n请点击查看！","Arial",30);
        label->setPosition(ccp(170,490));
        label->setAnchorPoint(ccp(0,0.5));
        
        
        newbieLayer->addChild(menu,10);
        newbieLayer->addChild(sprite,10);
        newbieLayer->addChild(label,10);
        newbieLayer->addChild(fillBlack,10);
        scene->addChild(newbieLayer);
        
//        status++;
    }else if(status == 4) {
        CCLayer* newbieLayer = CCLayer::create();
        newbieLayer->setTag(newbieFlowLayerTag);
        CCSprite* gybattle = CCSprite::createWithSpriteFrameName("battleIcon.png");
        gybattle->setColor(ccGRAY);
        CCMenuItemSprite* battleButton = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("battleIcon.png"), gybattle,this,menu_selector(Newbie2Trigger::toBattleScene));
//        CCSprite* battleBack = CCSprite::createWithSpriteFrameName("mainMenuBack.png");
//        battleBack->setPosition(ccp(battleButton->getContentSize().width/2,battleButton->getContentSize().height/2));
//        battleButton->addChild(battleBack,-1);
        battleButton->setScale(1.5);
//        battleButton->runAction(CCSequence::create(CCEaseElasticOut::create(CCScaleTo::create(0.8,1),1),CCCallFuncO::create(this,callfuncO_selector(Newbie2Trigger::shakeEffect2),battleButton),NULL));
        battleButton->runAction(CCEaseElasticOut::create(CCScaleTo::create(0.8,1),1));
        
        CCSprite* battleShadow = CCSprite::createWithSpriteFrameName("battleIcon.png");
        battleShadow->setPosition(ccp(battleButton->getContentSize().width/2,battleButton->getContentSize().height/2));
        battleShadow->runAction(CCRepeatForever::create(static_cast<CCSequence*>(CCSequence::create(CCSpawn::create(CCScaleTo::create(0.75,1.25),CCFadeOut::create(0.75),NULL),CCScaleTo::create(0,1),NULL))));
        battleButton->addChild(battleShadow,-2);
        
        scene->controlMenu->addChild(battleButton);
        scene->controlMenu->setPosition(0,0);
        battleButton->setPosition(ccp(winSize.width-85,85));
        
        CCLabelTTF* battleLabel = CCLabelTTF::create("点击征战","Arial",30);
        battleLabel->setPosition(ccp(winSize.width-255,225));
//        battleLabel->setPosition(ccp(winSize.width-80,230));
        scene->addChild(battleLabel,100);
        
        CCLabelTTF* battleLabel2 = CCLabelTTF::create("开始进攻!","Arial",40);
        battleLabel2->setPosition(ccp(winSize.width-250,180));
        //        battleLabel->setPosition(ccp(winSize.width-80,230));
        scene->addChild(battleLabel2,100);
        
        CCSprite* sprite = CCSprite::create("spotlight.png");
        sprite->setScale(5);
        sprite->setAnchorPoint(ccp(0.5,0.5));
        sprite->setPosition(ccp(winSize.width-20,75));
//        sprite->runAction(CCRepeatForever::create(static_cast<CCSequence*>(CCSequence::create(CCScaleTo::create(0.25, 4), CCScaleTo::create(0.25,5),NULL))));

        GXShieldTouchMenuItem* nextButton = GXShieldTouchMenuItem::create();
        nextButton->setContentSize(winSize);
        nextButton->setPosition(ccp(winSize.width/2,winSize.height/2));
        MyPriorityMenu* menu = MyPriorityMenu::create(-499, nextButton,NULL);
        menu->setPosition(ccp(0,0));
        menu->setTag(newbieMenuTag);
        
//        nextButton->setContentSize(winSize);
//        nextButton->setPosition(ccp(winSize.width-transWindowToGLInRetina(40),transWindowToGLInRetina(30)));
        newbieLayer->addChild(menu,10);
        newbieLayer->addChild(sprite,10);
        scene->addChild(newbieLayer);
        
//        CCSprite* tipPress = CCSprite::createWithSpriteFrameName("tipPress.png");
//        tipPress->setPosition(ccp(winSize.width-80,60));
//        tipPress->setScale(2);
//        
//        
//        tipPress->runAction(GXRepeatForever::create(CCEaseElasticOut::create(GXScaleTo::create(2, 1), 1) ));
//        newbieLayer->addChild(tipPress);
        
        status++;
    }
}

bool Newbie2Trigger::onRegist() {
    
    CCLayer* newbieLayer = CCLayer::create();
    newbieLayer->setPosition(ccp(0,0));
    newbieLayer->setTag(newbieFlowLayerTag);
    CCSprite* gray = CCSprite::create("whiteImage.jpg");
    gray->setScaleX((winSize.width+100)/gray->getContentSize().width);
    gray->setScaleY((winSize.height+100)/gray->getContentSize().height);
    gray->setPosition(ccp(winSize.width/2,winSize.height/2));
    gray->setTag(grayTag);
    gray->setColor(ccc3(0,0,0));
    gray->setOpacity(153);
    newbieLayer->addChild(gray);
//    CCSprite* sprite = CCSprite::create("spotlight.png");
//    sprite->setScale(7);
//    sprite->setAnchorPoint(ccp(0.5,0.5));
//    sprite->setPosition(ccp(150,winSize.height));
//    sprite->setTag(grayTag);
//    newbieLayer->addChild(sprite);
    
//    CCLayer* uilayer = (CCLayer*)scene->getChildByTag(UILayerTag);
//    CCSprite* avartar = (CCSprite*)scene->getChildByTag(avatarTag);
    CCSprite* avatar =CCSprite::createWithSpriteFrameName("avatar.png");
    //    uiLayer->addChild(avatar);
//    avatar->setAnchorPoint(ccp(0,1));
    avatar->setTag(avatarTag);
    CCSprite* avatarSprite = CCSprite::createWithSpriteFrameName("avatar0.png");
    avatarSprite->setAnchorPoint(ccp(0,1));
    avatarSprite->setPosition(ccp(0,avatar->getContentSize().height));
    avatar->addChild(avatarSprite);
    CCLabelTTF* nickName = CCLabelTTF::create("指挥官","Arial", 18);
    nickName->setAnchorPoint(ccp(0.5,1));
#if(CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    nickName->setPosition(ccp(139,84));
#endif
#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    nickName->setPosition(ccp(139,87));
#endif
    
    CCSprite* level = CCSprite::createWithSpriteFrameName("levelIcon.png");
    level->setScale(24/level->getContentSize().width);
    level->setPosition(ccp(112,46));
    MyLevelBar* levelBar = MyLevelBar::create(CCSprite::create("levelBarUp.png"), CCSprite::create("BarDown.png"),CCSizeMake(84, 8));
    levelBar->setLevel(10);
    levelBar->setContentSize(CCSizeMake(84, 8));
    levelBar->updatePercentage(0.3);
    levelBar->setPosition(ccp(88,30));
    
    avatar->addChild(nickName);
    avatar->addChild(level,2);
    avatar->addChild(levelBar,1);

    scene->addChild(avatar,20);
    
    avatar->setPosition(ccp(winSize.width/2,winSize.height/2));
    
    avatar->setScale(2);
    avatar->setOpacity(0);
    avatar->runAction(CCSequence::create(CCSpawn::create(CCFadeIn::create(0.3),CCScaleTo::create(0.3,1),CCEaseIn::create(CCMoveTo::create(0.5,ccp(avatar->getContentSize().width/2,winSize.height-avatar->getContentSize().height/2)),2),NULL),GXPlayAudioEffectAction::create(CCString::create("sfx_uicrash1.mp3")),NULL));
    
//    CCSprite* avartarMask = CCSprite::createWithSpriteFrameName("avatar.png");
//    avartarMask->setPosition(ccp(avartarMask->getContentSize().width/2,winSize.height-avartarMask->getContentSize().height/2));
////    avartarMask->setAnchorPoint(ccp(0,1));
//    scene->addChild(avartarMask,19);
//    avartarMask->setOpacity(0);
//    avartarMask->runAction(CCRepeatForever::create(static_cast<CCSequence*>(CCSequence::create(CCSpawn::create(CCScaleTo::create(1,1.3),CCFadeOut::create(1),NULL),CCScaleTo::create(0,1),CCFadeIn::create(0),NULL))));
//    avartarMask->setTag(avatarMaskTag);
    CCSprite* trans = CCSprite::create("transparent.png");
    trans->setContentSize(winSize);
    CCMenuItemSprite* nextButton = CCMenuItemSprite::create(trans, CCSprite::create("transparent.png"),this,menu_selector(Newbie2Trigger::toNextCallBack));
//    GXShieldTouchMenuItem* nextButton = GXShieldTouchMenuItem::create();
    MyPriorityMenu* menu = MyPriorityMenu::create(-499, nextButton,NULL);
    menu->setPosition(ccp(0,0));
    menu->setTag(newbieMenuTag);
    nextButton->setPosition(ccp(winSize.width/2,winSize.height/2));
    nextButton->setContentSize(winSize);
    newbieLayer->addChild(menu,10);
    
//    CCLabelTTF* tipLabel = CCLabelTTF::create("点击屏幕继续", "Arial", 30);
//    tipLabel->runAction(CCRepeatForever::create(static_cast<CCSequence*>(CCSequence::create(CCFadeOut::create(1),CCFadeIn::create(1),NULL))));
//    tipLabel->setPosition(ccp(winSize.width/2,winSize.height/2-240));
//    newbieLayer->addChild(tipLabel);
    scene->addChild(newbieLayer,10);
//    
//    CCString* str = GXUtil::readFile("NewbieDialog2.j");
//    newbieLayer->addChild(DiaLayer::create(GXJsonUtil::parseDiaLayerInfoBean(str->getCString())));
    
    
    return false;
}

bool Newbie2Trigger::onUnRegist() {
//    scene->removeChildByTag(newbieFlowLayerTag, true);
    return true;
}

void Newbie2Trigger::getPrizeCallBack(cocos2d::CCNode *pSender) {
    isDialog=true;
    scene->removeChildByTag(newbieFlowLayerTag, true);
    CCLayer* newbieLayer = CCLayer::create();
    
    GXShieldTouchMenuItem* shield = GXShieldTouchMenuItem::create();
    shield->setContentSize(winSize);
    shield->setPosition(ccp(winSize.width/2,winSize.height/2));
    
    CCMenuItemSprite* iKnow =CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("dialogkonw.png"), CCSprite::createWithSpriteFrameName("dialogknowp.png"),this,menu_selector(Newbie2Trigger::toNextCallBack));
    iKnow->setPosition(ccp(winSize.width/2+120,winSize.height/2-90));
    
    MyPriorityMenu* shieldMenu = MyPriorityMenu::create(-600,iKnow, shield,NULL);
    shieldMenu->setPosition(ccp(0,0));
    
    
    CCLabelTTF* desc = CCLabelTTF::create(GXUtil::insertNewline("　　指挥官，我们侦测到敌人的哨所就在附近，趁敌人还未发现我们，赶快对他们进行突袭！",14).c_str(), "Arial" , 30, CCSizeMake(440,200), kCCTextAlignmentLeft, kCCVerticalTextAlignmentTop);
    desc->cocos2d::CCNode::setAnchorPoint(ccp(0.5,1));
#if   (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    desc->setPosition(ccp(winSize.width/2+100,winSize.height/2+90+41/5));
#endif
#if   (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    desc->setPosition(ccp(winSize.width/2+100,winSize.height/2+90));
#endif
    
    desc->setColor(ccc3(230, 207, 185));
    
    newbieLayer->addChild(desc,3);
    newbieLayer->addChild(shieldMenu,2);
    CCSprite* dialogBack = MyUtil::getInstance()->getDialogBack();
    dialogBack->setPosition(ccp(winSize.width/2,winSize.height/2));
    newbieLayer->addChild(dialogBack);
    newbieLayer->setTag(newbieFlowLayerTag);
    scene->addChild(newbieLayer);
    
    
    
    newbieLayer->setScale(0.5);
    newbieLayer->runAction(CCScaleTo::create(0.5, 1));
    shieldMenu->setOpacity(0);
    dialogBack->setOpacity(0);
    shieldMenu->runAction(CCSequence::create(CCDelayTime::create(0.25),CCFadeIn::create(0.25),NULL));
    dialogBack->runAction(CCSequence::create(CCDelayTime::create(0.25),CCFadeIn::create(0.25),NULL));
    desc->setOpacity(0);
    desc->runAction(CCSequence::create(CCDelayTime::create(0.25),CCFadeIn::create(0.25),NULL));
    
    
    
}

void Newbie2Trigger::toBattleScene(cocos2d::CCNode *pSender) {
    MyMessageManage::getInstance()->unRegisterTrigger(this);
    scene->toBattleScene();
}

void Newbie2Trigger::displayQuestInfoCallback(CCMenuItem* item) {
    scene->removeChildByTag(newbieFlowLayerTag,true);
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sfx_click.mp3");
    item->stopAllActions();
    item->setEnabled(false);
    MyBaseQuest* quest = (MyBaseQuest*)item->getUserData();
    item->stopAllActions();
    item->setScale(1);
    MyMenuItem* item1 = (MyMenuItem*)item;
    item1->getImage()->removeAllChildrenWithCleanup(true);
    CCSprite* questIcon = CCSprite::createWithSpriteFrameName(quest->getIconName()->getCString());
    questIcon->setPosition(ccp(item1->getContentSize().width/2,item1->getContentSize().height/2));
    item1->getImage()->addChild(questIcon);
    
    CCLayer* layer = MyUtil::getInstance()->getQuestBack(quest,this,menu_selector(Newbie2Trigger::toGetQuestPrize),false);
    layer->setPosition(ccp(winSize.width/2+40,layer->getContentSize().height/2*-1));
    layer->runAction(CCEaseElasticOut::create(CCMoveTo::create(0.35, ccp(winSize.width/2+40,winSize.height/2)), 1));
    layer->setTag(questInfoLayer);
    
    GXShieldTouchMenuItem* shield = GXShieldTouchMenuItem::create();
    shield->setContentSize(winSize);
    shield->setPosition(ccp(-40,0));
    MyPriorityMenu* shieldMenu = MyPriorityMenu::create(-502,shield,NULL);
    shieldMenu->setPosition(ccp(0,0));
    layer->addChild(shieldMenu);
    
    scene->addChild(layer);
}

void Newbie2Trigger::toGetQuestPrize(CCMenuItem* item) {
    item->setEnabled(false);
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sfx_levelup.mp3");
    MyBaseQuest* quest = (MyBaseQuest*)item->getUserData();
    quest->getPrize();
    status++;
    toNextCallBack(item);
    scene->removeChildByTag(questInfoLayer,true);
}

void Newbie2Trigger::shakeEffect2(CCNode* node) {
    node->runAction(CCRepeatForever::create(static_cast<CCSequence*>(CCSequence::create(CCScaleTo::create(0.25, 0.98), CCScaleTo::create(0.25,1),NULL))));
}