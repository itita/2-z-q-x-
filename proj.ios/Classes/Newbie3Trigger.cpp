//
//  Newbie3Trigger.cpp
//  ww3
//
//  Created by xiao tang on 12-12-18.
//
//

#include "Newbie3Trigger.h"
#include "DefineSet.h"
#include "MyPriorityMenu.h"
#include "GXShieldTouchMenuItem.h"
#include "GXScaleTo.h"
#include "GXRepeatForever.h"
#include "MyMessageManage.h"
#include "MyGameFactory.h"
#include "GXRadioMenu.h"
#include "MyDeployButton.h"
#include "GXReverseSheild.h"
#include "ToFightMessage.h"
#include "NoResourceToDeployMessage.h"
#include "SimpleAudioEngine.h"
#include "NewbieClickMessage.h"
#include "MyGameInfo.h"
#include "MyUtil.h"
#include "GXJsonUtil.h"
#include "DiaLayer.h"
#include "DialogCompleteMessage.h"
#include "GXPlayAudioEffectCreator.h"
#include "Mathlib.h"


#define avatarMaskTag 60
#define descLabelTag 903
#define newbieFlowLayerTag 900
#define grayTag 901
#define newbieMenuTag 902
#define nextButtonTag 903
#define tipArrowTag 904
#define tipCircleTag 905
#define tipSpotTag 906
#define tipPressTag 907
#define dialogLayerTag 908
#define stuartDeployButtonTag 909
#define avatarLabelTag 910


Newbie3Trigger::~Newbie3Trigger() {
    CCLog("Newbie3Trigger has been released");
}

Newbie3Trigger* Newbie3Trigger::create(NewbieBattleScene* node) {
    Newbie3Trigger* trigger = new Newbie3Trigger();
    trigger->autorelease();
//    trigger->status = -1;
    trigger->scene = node;
    return trigger;
}


bool Newbie3Trigger::excuteMsg(MyBaseMessage* msg) {
    if(msg->tag == DialogCompleteMessageTag) {
//        DialogCompleteMessage* dMsg = (DialogCompleteMessage*)msg;
//        if (dMsg->currentNode  >= 1 ) {
            toNextCallBack(NULL);
//        }
    }
    if(msg->tag == toFightMessageTag) {
        status++;
        toNextCallBack(NULL);
    }
    else if(msg->tag == noResourceToDeployMessageTag && status == 10) {
        status++;
        toNextCallBack(NULL);
    } else if(msg->tag == newbieClickMessageTag  && status == 13) {
        status++;
        toNextCallBack(NULL);
    }
    
    return false;
}

void Newbie3Trigger::toNextCallBack(cocos2d::CCNode *node) {
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sfx_click.mp3");
    if(status == 0) {
        scene->removeChildByTag(newbieFlowLayerTag, true);
        scene->removeChildByTag(avatarMaskTag, true);
        CCLayer* newbieLayer = CCLayer::create();
        newbieLayer->setPosition(ccp(0,0));
        newbieLayer->setTag(newbieFlowLayerTag);
        CCSprite* gray = CCSprite::create("whiteImage.jpg");
        gray->setScaleX(winSize.width/gray->getContentSize().width);
        gray->setScaleY(winSize.height/gray->getContentSize().height);
        gray->setPosition(ccp(winSize.width/2,winSize.height/2));
        gray->setTag(grayTag);
        gray->setColor(ccc3(0,0,0));
        gray->setOpacity(153);
        newbieLayer->addChild(gray);
        
        //    CCLayer* uilayer = (CCLayer*)scene->getChildByTag(UILayerTag);
//        CCSprite* avartar = (CCSprite*)scene->getChildByTag(avatarTag);
//        scene->reorderChild(avartar, 20);
        CCSprite* avatar =CCSprite::createWithSpriteFrameName("avatar.png");
//        avatar->setAnchorPoint(ccp(0,1));
//        avatar->setPosition(ccp(0,winSize.height));
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
        avatar->addChild(nickName);
        
        CCLabelTTF* rankName = CCLabelTTF::create(MyUtil::getInstance()->getRankString(1200), "Arial", 20);
        avatar->addChild(rankName,2);
        rankName->setAnchorPoint(ccp(0,0.5));
        rankName->setPosition(ccp(126,44));
        rankName->setColor(ccWHITE);
        
        CCSprite* rankSprite = MyUtil::getInstance()->getRankSprite(1200);
        rankSprite->setPosition(ccp(106,44));
        rankSprite->setScale(0.50);
        avatar->addChild(rankSprite,2);
        
        scene->addChild(avatar,20);
        
        avatar->setOpacity(0);
        avatar->setScale(2);
        avatar->setPosition(ccp(winSize.width/2,winSize.height/2));
        avatar->runAction(CCSequence::create(CCSpawn::create(CCFadeIn::create(0.3),CCScaleTo::create(0.3,1),CCEaseIn::create(CCMoveTo::create(0.5,ccp(avatar->getContentSize().width/2,winSize.height-avatar->getContentSize().height/2)),2),NULL),GXPlayAudioEffectAction::create(CCString::create("sfx_uicrash1.mp3")),NULL));
        
//        CCSprite* avartarMask = CCSprite::create("avatarWhiteMask.png");
//        avartarMask->setPosition(ccp(0,winSize.height));
////        avartarMask->setScaleX(1.05);
////        avartarMask->setScaleY(1.2);
//        avartarMask->setAnchorPoint(ccp(0,1));
//        scene->addChild(avartarMask,19);
//        avartarMask->setOpacity(0);
//        avartarMask->runAction(CCRepeat::create(static_cast<CCSequence*>(CCSequence::create(CCFadeTo::create(0.25, 170),CCFadeTo::create(0.25,0),NULL)),4));
//        avartarMask->setTag(avatarMaskTag);
        CCSprite* trans = CCSprite::create("transparent.png");
        trans->setContentSize(winSize);
        CCMenuItemSprite* nextButton = CCMenuItemSprite::create(trans, CCSprite::create("transparent.png"),this,menu_selector(Newbie3Trigger::toNextCallBack));
        nextButton->setTag(nextButtonTag);
        //    GXShieldTouchMenuItem* nextButton = GXShieldTouchMenuItem::create();
        MyPriorityMenu* menu = MyPriorityMenu::create(-600, nextButton,NULL);
        menu->setPosition(ccp(0,0));
        menu->setTag(newbieMenuTag);
        nextButton->setPosition(ccp(winSize.width/2,winSize.height/2));
        nextButton->setContentSize(winSize);
        newbieLayer->addChild(menu,10);
        scene->addChild(newbieLayer,10);
        status++;
    }
//    else if (status == 1) {
//        scene->removeChildByTag(avatarMaskTag, true);
////        CCLabelTTF* avatarLabel = CCLabelTTF::create("这里显示进攻方昵称，军衔。", "Arial" , transWindowToGLInRetina(15), CCSizeMake(transWindowToGLInRetina(100),transWindowToGLInRetina(150)), kCCTextAlignmentLeft, kCCVerticalTextAlignmentTop);
//        CCSprite* avatarLabel = CCSprite::createWithSpriteFrameName("newbielabel4.png");
//        avatarLabel->setScale(1.25);
//        scene->getChildByTag(newbieFlowLayerTag)->addChild(avatarLabel);
//        avatarLabel->setPosition(ccp(0,winSize.height-100));
//        avatarLabel->setAnchorPoint(ccp(0,1));
//        status++;
//    }
    else if(status == 1) {
//        CCSprite* avartarMask = CCSprite::create("avatarAverseMask.png");
//        avartarMask->setPosition(ccp(winSize.width,winSize.height));
//        avartarMask->setAnchorPoint(ccp(1,1));
//        scene->addChild(avartarMask,19);
//        avartarMask->setOpacity(0);
//        avartarMask->runAction(CCRepeatForever::create(static_cast<CCSequence*>(CCSequence::create(CCFadeTo::create(1, 170),CCFadeTo::create(1,0),NULL))));
//        avartarMask->setTag(avatarMaskTag);
//        scene->reorderChild((CCSprite*)scene->getChildByTag(avatarAverseTag), 20);
        

        CCSprite* avatarAverse =CCSprite::createWithSpriteFrameName("avatar.png");
        avatarAverse->setTag(avatarAverseTag);
        avatarAverse->setFlipX(true);
//        avatarAverse->setAnchorPoint(ccp(1,1));
        avatarAverse->setPosition(ccp(winSize.width,winSize.height));
        CCSprite* avatarAverseSprite = CCSprite::createWithSpriteFrameName("avatar0.png");
        avatarAverseSprite->setFlipX(true);
        avatarAverseSprite->setAnchorPoint(ccp(1,1));
        avatarAverseSprite->setPosition(ccp(avatarAverse->getContentSize().width,avatarAverse->getContentSize().height));
        avatarAverse->addChild(avatarAverseSprite);
        
        CCLabelTTF* enemyNickName = CCLabelTTF::create("德军前哨","Arial", 18);
        enemyNickName->setAnchorPoint(ccp(0.5,1));
#if(CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
        enemyNickName->setPosition(ccp(avatarAverse->getContentSize().width -139,84));
#endif
#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
        enemyNickName->setPosition(ccp(avatarAverse->getContentSize().width -139,87));
#endif
        
        
        avatarAverse->addChild(enemyNickName);
        CCLabelTTF* enemyRankName = CCLabelTTF::create(MyUtil::getInstance()->getRankString(480), "Arial", 20);
        avatarAverse->addChild(enemyRankName,2);
        enemyRankName->setAnchorPoint(ccp(1,0.5));
        enemyRankName->setPosition(ccp(avatarAverse->getContentSize().width -126,44));
        enemyRankName->setColor(ccWHITE);
        
        CCSprite* enemyRankSprite = MyUtil::getInstance()->getRankSprite(480);
        enemyRankSprite->setPosition(ccp(avatarAverse->getContentSize().width -106,44));
        enemyRankSprite->setScale(0.50);
        avatarAverse->addChild(enemyRankSprite,2);
        
        avatarAverse->setOpacity(0);
        avatarAverse->setScale(2);
        avatarAverse->setPosition(ccp(winSize.width/2,winSize.height/2));
        avatarAverse->runAction(CCSequence::create(CCSpawn::create(CCFadeIn::create(0.3),CCScaleTo::create(0.3,1),CCEaseIn::create(CCMoveTo::create(0.5,ccp(winSize.width-avatarAverse->getContentSize().width/2,winSize.height-avatarAverse->getContentSize().height/2)),2),NULL),GXPlayAudioEffectAction::create(CCString::create("sfx_uicrash1.mp3")),NULL));
        scene->addChild(avatarAverse,20);
        status++;
    }
//    else if(status == 3) {
//        scene->removeChildByTag(avatarMaskTag, true);
////        CCLabelTTF* avatarLabel = CCLabelTTF::create("这里显示防守方昵称，军衔。", "Arial" , transWindowToGLInRetina(15), CCSizeMake(transWindowToGLInRetina(100),transWindowToGLInRetina(150)), kCCTextAlignmentLeft, kCCVerticalTextAlignmentTop);
//        CCSprite* avatarLabel = CCSprite::createWithSpriteFrameName("newbielabel5.png");
//        avatarLabel->setScale(1.25);
//        avatarLabel->setTag(descLabelTag);
//        scene->getChildByTag(newbieFlowLayerTag)->addChild(avatarLabel);
//        avatarLabel->setPosition(ccp(winSize.width,winSize.height-100));
//        avatarLabel->setAnchorPoint(ccp(1,1));
//        status++;
//    }
    else if(status == 2) {
//        scene->reorderChild(scene->getChildByTag(UILayerTag),30);
//        scene->getChildByTag(newbieFlowLayerTag)->removeChildByTag(descLabelTag, true);
//        CCLabelTTF* avatarLabel = CCLabelTTF::create("这里显示可以获得的战利品，分别是石油，钢铁和荣誉", "Arial" , transWindowToGLInRetina(15),CCSizeMake(transWindowToGLInRetina(100),transWindowToGLInRetina(150)),kCCTextAlignmentLeft, kCCVerticalTextAlignmentTop);
//        CCSprite* avatarLabel = CCSprite::createWithSpriteFrameName("newbielabel6.png");
//        avatarLabel->setScale(1.25);
//        scene->getChildByTag(newbieFlowLayerTag)->addChild(avatarLabel);
//        avatarLabel->setPosition(ccp(winSize.width-160,winSize.height - 100));
//        avatarLabel->setAnchorPoint(ccp(1,1));
        
        
        scene->enemyOilLabel = MyAtlasNumber::create();
        scene->enemyOilLabel->setNumberNoFx(MyGameInfo::getInstance()->getRobberOil());
        scene->enemyOilLabel->setAnchorPoint(ccp(0,0.5));
        scene->enemyOilLabel->setPosition(ccp(53,26));
        scene->enemyOilLabel->setScale(1.285);
        CCSprite* oilIcon = CCSprite::createWithSpriteFrameName("oilIcon.png");
        oilIcon->setScale(0.7);
        oilIcon->setPosition(ccp(winSize.width/2-80,winSize.height/2+100));
        oilIcon->setTag(enemyOilIconTag);
        
        scene->enemyIronLabel = MyAtlasNumber::create();
        scene->enemyIronLabel->setNumberNoFx(MyGameInfo::getInstance()->getRobberIron());
        scene->enemyIronLabel->setAnchorPoint(ccp(0,0.5));
        scene->enemyIronLabel->setPosition(ccp(53,24));
        scene->enemyIronLabel->setScale(1.285);
        CCSprite* ironIcon = CCSprite::createWithSpriteFrameName("ironIcon.png");
        ironIcon->setScale(0.7);
        ironIcon->setPosition(ccp(winSize.width/2+40,winSize.height/2+100));
        ironIcon->setTag(enemyIronIconTag);
        
        scene->enemyHonorLabel = MyAtlasNumber::create();
        
        scene->enemyHonorLabel->setNumberNoFx(300);
        scene->enemyHonorLabel->setAnchorPoint(ccp(0,0.5));
        scene->enemyHonorLabel->setPosition(ccp(53,26));
        scene->enemyHonorLabel->setScale(1.285);
        CCSprite* honorIcon = CCSprite::createWithSpriteFrameName("honorIcon.png");
        honorIcon->setPosition(ccp(winSize.width/2-80,winSize.height/2+50));
        honorIcon->setScale(0.7);
        honorIcon->setTag(enemyHonorIconTag);
        
        scene->enemyPowerLabel = MyAtlasNumber::create();
        scene->enemyPowerLabel->setNumberNoFx(20);
        scene->enemyPowerLabel->setAnchorPoint(ccp(0,0.5));
        scene->enemyPowerLabel->setScale(1.285);
        scene->enemyPowerLabel->setPosition(ccp(53,26));
        CCSprite* powerIcon = CCSprite::createWithSpriteFrameName("powerIcon.png");
        powerIcon->setScale(0.7);
        powerIcon->setPosition(ccp(winSize.width/2+40,winSize.height/2+50));
    
        scene->addChild(oilIcon,30);
        oilIcon->addChild(scene->enemyOilLabel);
        scene->addChild(ironIcon,30);
        ironIcon->addChild(scene->enemyIronLabel);
        scene->addChild(honorIcon,30);
        honorIcon->addChild(scene->enemyHonorLabel);
        scene->addChild(powerIcon,30);
        powerIcon->addChild(scene->enemyPowerLabel);
        
        oilIcon->runAction(CCSequence::create(CCDelayTime::create(0.3),CCSpawn::create(CCFadeIn::create(0.3),CCEaseIn::create(CCMoveTo::create(0.5,ccp(winSize.width-164,520)),2),NULL),GXPlayAudioEffectAction::create(CCString::create("sfx_uicrash.mp3")),NULL));
        ironIcon->runAction(CCSequence::create(CCDelayTime::create(0.6),CCSpawn::create(CCFadeIn::create(0.3),CCEaseIn::create(CCMoveTo::create(0.5,ccp(winSize.width-164,475)),2),NULL),GXPlayAudioEffectAction::create(CCString::create("sfx_uicrash.mp3")),NULL));
        honorIcon->runAction(CCSequence::create(CCDelayTime::create(0.9),CCSpawn::create(CCFadeIn::create(0.3),CCEaseIn::create(CCMoveTo::create(0.5,ccp(winSize.width-164,430)),2),NULL),GXPlayAudioEffectAction::create(CCString::create("sfx_uicrash.mp3")),NULL));
        powerIcon->runAction(CCSequence::create(CCDelayTime::create(1.2),CCSpawn::create(CCFadeIn::create(0.3),CCEaseIn::create(CCMoveTo::create(0.5,ccp(winSize.width-164,385)),2),NULL),GXPlayAudioEffectAction::create(CCString::create("sfx_uicrash.mp3")),NULL));
        
        status++;
    }
    else if(status == 3){
        scene->getChildByTag(newbieFlowLayerTag)->removeChildByTag(grayTag, true);
        CCSprite* spotLight = CCSprite::create("spotlight.png");
        spotLight->setScale(6);
        spotLight->setPosition(ccp(winSize.width/2+70,winSize.height/2));
        scene->getChildByTag(newbieFlowLayerTag)->addChild(spotLight);
        status++;
    }
//    else if(status == 4) {
//        scene->getChildByTag(newbieFlowLayerTag)->removeChildByTag(descLabelTag, true);
////        CCLabelTTF* avatarLabel = CCLabelTTF::create("主要目标是摧毁敌军基地，摧毁即可获得胜利", "Arial" , transWindowToGLInRetina(15));
//        CCSprite* avatarLabel = CCSprite::createWithSpriteFrameName("newbielabel7.png");
//        avatarLabel->setScale(1.25);
//        scene->getChildByTag(newbieFlowLayerTag)->addChild(avatarLabel);
//        avatarLabel->setPosition(ccp(winSize.width/2,winSize.height/2-140));
//    
//        status++;
//    }
    else if(status == 4) {
//        scene->removeChildByTag(newbieFlowLayerTag,true);
//        CCLayer* newbieLayer = CCLayer::create();
//        
//        GXShieldTouchMenuItem* shield = GXShieldTouchMenuItem::create();
//        shield->setContentSize(winSize);
//        shield->setPosition(ccp(winSize.width/2,winSize.height/2));
//        
//        CCMenuItemSprite* iKnow =CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("dialogkonw.png"), CCSprite::createWithSpriteFrameName("dialogknowp.png"),this,menu_selector(Newbie3Trigger::toNextCallBack));
//        iKnow->setPosition(ccp(winSize.width/2+120,winSize.height/2-90));
//        
//        MyPriorityMenu* shieldMenu = MyPriorityMenu::create(-600,iKnow, shield,NULL);
//        shieldMenu->setPosition(ccp(0,0));
//        
//        
//        CCLabelTTF* desc = CCLabelTTF::create(GXUtil::insertNewline("　　指挥官，我们已经摸清敌人的情报，请立即出击！",14).c_str(), "Arial" , 30, CCSizeMake(440,200), kCCTextAlignmentLeft, kCCVerticalTextAlignmentTop);
//        desc->cocos2d::CCNode::setAnchorPoint(ccp(0.5,1));
//#if   (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
//        desc->setPosition(ccp(winSize.width/2+100,winSize.height/2+90+33/5));
//#endif
//#if   (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
//        desc->setPosition(ccp(winSize.width/2+100,winSize.height/2+90));
//#endif
//        desc->setColor(ccc3(230, 207, 185));
//        
//        newbieLayer->addChild(desc,3);
//        newbieLayer->addChild(shieldMenu,2);
//        CCSprite* dialogBack = MyUtil::getInstance()->getDialogBack();
//        dialogBack->setPosition(ccp(winSize.width/2,winSize.height/2));
//        newbieLayer->addChild(dialogBack);
//        newbieLayer->setTag(newbieFlowLayerTag);
//        scene->addChild(newbieLayer);
//        
//        newbieLayer->setScale(0.5);
//        newbieLayer->runAction(CCScaleTo::create(0.5, 1));
//        shieldMenu->setOpacity(0);
//        dialogBack->setOpacity(0);
//        shieldMenu->runAction(CCSequence::create(CCDelayTime::create(0.25),CCFadeIn::create(0.25),NULL));
//        dialogBack->runAction(CCSequence::create(CCDelayTime::create(0.25),CCFadeIn::create(0.25),NULL));
//        desc->setOpacity(0);
//        desc->runAction(CCSequence::create(CCDelayTime::create(0.25),CCFadeIn::create(0.25),NULL));
        status++;
    }
    else if(status == 5) {
        scene->removeChildByTag(newbieFlowLayerTag, true);
        CCLayer* newbieLayer = CCLayer::create();
        newbieLayer->setPosition(ccp(0,0));
        newbieLayer->setTag(newbieFlowLayerTag);
        CCSprite* gray = CCSprite::create("whiteImage.jpg");
        gray->setScaleX(winSize.width/gray->getContentSize().width);
        gray->setScaleY(winSize.height/gray->getContentSize().height);
        gray->setPosition(ccp(winSize.width/2,winSize.height/2));
        gray->setTag(grayTag);
        gray->setColor(ccc3(0,0,0));
        gray->setOpacity(153);
        newbieLayer->addChild(gray);
        
        //    CCLayer* uilayer = (CCLayer*)scene->getChildByTag(UILayerTag);
        CCSprite* avartar = (CCSprite*)scene->getChildByTag(avatarTag);
        scene->reorderChild(avartar, 20);
        
        
        
        CCSprite* trans = CCSprite::create("transparent.png");
        trans->setContentSize(winSize);
        CCMenuItemSprite* nextButton = CCMenuItemSprite::create(trans, CCSprite::create("transparent.png"),this,menu_selector(Newbie3Trigger::toNextCallBack));
        //    GXShieldTouchMenuItem* nextButton = GXShieldTouchMenuItem::create();
        MyPriorityMenu* menu = MyPriorityMenu::create(-600, nextButton,NULL);
        menu->setPosition(ccp(0,0));
        menu->setTag(newbieMenuTag);
        nextButton->setPosition(ccp(winSize.width/2,winSize.height/2));
        nextButton->setContentSize(winSize);
        newbieLayer->addChild(menu,10);
        scene->addChild(newbieLayer,10);
        
//        MyGameInfo::getInstance()->tankLevel = 6;
//        MyGameInfo::getInstance()->bubingLevel = 2;
//        UnitCreator* tankCreator2 = UnitCreator::create(bubingCreatorTag,CCString::create("bubing1"),CCString::create("sfx_deploySoldier.m4a"),CCString::create("sfx_diaobao1f.wav"),bubingBaseSpeed,bubingBaseRange,bubingBaseDamage,bubingBaseHealth,bubingBaseCost);
        CreatorInfoBean* bean = CreatorInfoBean::create(garadeCardId);
        bean->setExperience(MyUtil::getInstance()->getExperienceByUnitLevel(2, 2)-1);
        
        
        
//        CCSprite* soldier = CCSprite::create("deploySoldier1.png");
//        CCSprite* gysoldier = CCSprite::create("deploySoldier1.png");
//        gysoldier->setColor(ccGRAY);
        
//        MyDeployButton* deploy3 = MyDeployButton::create("deploySoldier1.png",tankCreator2,soldier,gysoldier,scene,menu_selector(NewbieBattleScene::callback1));
        MyDeployButton* deploy = MyDeployButton::create(bean, scene, menu_selector(NewbieBattleScene::callback1));
        
        GXRadioMenu* bingzhongMenu = GXRadioMenu::create(-506,deploy,NULL);
        bingzhongMenu->setTag(bingzhongmenuTag);
        bingzhongMenu->alignItemsHorizontallyWithPadding(20);
        deploy->setPosition(ccp(80,100));
        
        
        scene->addChild(bingzhongMenu,10);
//
        bingzhongMenu->setPosition(ccp(0,0));
        
        
        ((DiaLayer*)scene->getChildByTag(dialogLayerTag))->isEnable = false;
        
//        status++;
//    }
//    else if(status == 6){
//        scene->reorderChild(scene->getChildByTag(UILayerTag),30);
//        scene->getChildByTag(newbieFlowLayerTag)->removeChildByTag(descLabelTag, true);
////        CCLabelTTF* avatarLabel = CCLabelTTF::create("这里显示可以派遣的兵种，选中后可以派遣", "Arial" , transWindowToGLInRetina(15),CCSizeMake(transWindowToGLInRetina(100),transWindowToGLInRetina(100)),kCCTextAlignmentLeft, kCCVerticalTextAlignmentTop);
//        CCSprite* avatarLabel = CCSprite::createWithSpriteFrameName("newbielabel8.png");
//        avatarLabel->setScale(1.25);
//        scene->getChildByTag(newbieFlowLayerTag)->addChild(avatarLabel);
//        avatarLabel->setPosition(ccp(260, 160));
//        avatarLabel->setAnchorPoint(ccp(1,0));
//        status++;
//    }
//    else if(status == 7) {
        scene->getMap()->runAction(CCSequence::create(CCEaseInOut::create(CCMoveBy::create(1, ccp(580,380)), 2),CCCallFunc::create(this,callfunc_selector(Newbie3Trigger::mapMoveCallBack)),NULL) );
        scene->getChildByTag(newbieFlowLayerTag)->removeChildByTag(grayTag, true);
        CCSprite* spotLight = CCSprite::create("spotlight.png");
        spotLight->setScale(6);
        spotLight->setPosition(ccp(1300,800));
        scene->getMap()->CCNode::addChild(spotLight,1000000);
        spotLight->setTag(tipSpotTag);
        
        CCSprite* tipArrow = CCSprite::createWithSpriteFrameName("newbiearrow.png");
        tipArrow->setPosition(ccp(1230,860));
        scene->getMap()->CCNode::addChild(tipArrow,1000000);
        CCMoveBy* moveBy = CCMoveBy::create(0.5, ccp(0,-50));
        tipArrow->runAction(CCRepeatForever::create(static_cast<CCSequence*>(CCSequence::create(CCEaseInOut::create(moveBy, 2),CCEaseInOut::create(moveBy->reverse(),2),NULL))));
        tipArrow->setTag(tipArrowTag);
        
        CCSprite* tipCircle = CCSprite::createWithSpriteFrameName("tipCircle.png");
        tipCircle->setPosition(ccp(1230,740));
        scene->getMap()->CCNode::addChild(tipCircle,1000000);
        tipCircle->setScale(1.5);
        CCScaleBy* scaleBy = CCScaleBy::create(0.5, 0.5);
        tipCircle->runAction(CCRepeatForever::create(static_cast<CCSequence*>(CCSequence::create(CCEaseIn::create(scaleBy, 2),CCEaseOut::create(scaleBy->reverse(),2),NULL))));
        tipCircle->setTag(tipCircleTag);

        status++;
    }else if(status == 7){
        scene->reorderChild(scene->getChildByTag(UILayerTag),20);
        scene->getChildByTag(newbieFlowLayerTag)->removeChildByTag(descLabelTag, true);
//        CCLabelTTF* avatarLabel = CCLabelTTF::create("点击箭头指引处\n派遣兵力摧毁敌人", "Arial" , transWindowToGLInRetina(15));
//        CCSprite* avatarLabel = CCSprite::createWithSpriteFrameName("newbielabel7.png");
//        avatarLabel->setScale(1.25);
//        scene->getChildByTag(newbieFlowLayerTag)->addChild(avatarLabel);
//        avatarLabel->setPosition(ccp(winSize.width/2, winSize.height/2-200));
        
        scene->getChildByTag(newbieFlowLayerTag)->removeChildByTag(newbieMenuTag, true);
        
//        GXReverseSheild* reverseSheild = GXReverseSheild::create(-600);
//        reverseSheild->setContentSize(CCSizeMake(240, 240));
//        reverseSheild->setPosition(ccp(avatarLabel->getPosition().x-110, avatarLabel->getPosition().y+40));
        
//        scene->getChildByTag(newbieFlowLayerTag)->addChild(reverseSheild);
        
        
        
        status++;
    } else if (status == 9) {
        scene->removeChildByTag(dialogLayerTag,true);
        scene->removeChildByTag(newbieFlowLayerTag, true);
        scene->getMap()->removeChildByTag(tipSpotTag, true);
        scene->getMap()->removeChildByTag(tipCircleTag, true);
        scene->getMap()->removeChildByTag(tipArrowTag, true);
        status++;
    } else if (status == 11) {
        scene->removeChildByTag(newbieFlowLayerTag,true);
        CCLayer* newbieLayer = CCLayer::create();
        
//        GXShieldTouchMenuItem* shield = GXShieldTouchMenuItem::create();
//        shield->setContentSize(winSize);
//        shield->setPosition(ccp(winSize.width/2,winSize.height/2));
        
//        CCMenuItemSprite* iKnow =CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("dialogkonw.png"), CCSprite::createWithSpriteFrameName("dialogknowp.png"),this,menu_selector(Newbie3Trigger::toNextCallBack));
//        iKnow->setPosition(ccp(winSize.width/2+120,winSize.height/2-90));
        
//        MyPriorityMenu* shieldMenu = MyPriorityMenu::create(-600, shield,NULL);
//        shieldMenu->setPosition(ccp(0,0));
        
        
//        CCLabelTTF* desc = CCLabelTTF::create(GXUtil::insertNewline("　　指挥官，敌军营地后方防守薄弱，我们可以派遣装甲部队从后方包抄！",14).c_str(), "Arial" , 30, CCSizeMake(440,200), kCCTextAlignmentLeft, kCCVerticalTextAlignmentTop);
//        desc->cocos2d::CCNode::setAnchorPoint(ccp(0.5,1));
//        
//#if   (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
//        desc->setPosition(ccp(winSize.width/2+100,winSize.height/2+90+33/5));
//#endif
//#if   (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
//        desc->setPosition(ccp(winSize.width/2+100,winSize.height/2+90));
//#endif
//        
//        desc->setColor(ccc3(230, 207, 185));
//        
//        newbieLayer->addChild(desc,3);
//        newbieLayer->addChild(shieldMenu,2);
//        CCSprite* dialogBack = MyUtil::getInstance()->getDialogBack();
//        dialogBack->setPosition(ccp(winSize.width/2,winSize.height/2));
//        newbieLayer->addChild(dialogBack);
        newbieLayer->setTag(newbieFlowLayerTag);
        scene->addChild(newbieLayer);
        
        CCString* str = GXUtil::readFile("NewbieDialog5.j");
        DiaLayer* dialog = DiaLayer::create(GXJsonUtil::parseDiaLayerInfoBean(str->getCString()));
        dialog->setTag(dialogLayerTag);
        scene->addChild(dialog,11);
        
//        newbieLayer->setScale(0.5);
//        newbieLayer->runAction(CCScaleTo::create(0.5, 1));
//        shieldMenu->setOpacity(0);
//        dialogBack->setOpacity(0);
//        shieldMenu->runAction(CCSequence::create(CCDelayTime::create(0.25),CCFadeIn::create(0.25),NULL));
//        dialogBack->runAction(CCSequence::create(CCDelayTime::create(0.25),CCFadeIn::create(0.25),NULL));
//        desc->setOpacity(0);
//        desc->runAction(CCSequence::create(CCDelayTime::create(0.25),CCFadeIn::create(0.25),NULL));
        status++;
    } else if(status == 12) {
        scene->removeChildByTag(newbieFlowLayerTag, true);
        CCLayer* newbieLayer = CCLayer::create();
        newbieLayer->setPosition(ccp(0,0));
        newbieLayer->setTag(newbieFlowLayerTag);
        CCSprite* gray = CCSprite::create("whiteImage.jpg");
        gray->setScaleX(winSize.width/gray->getContentSize().width);
        gray->setScaleY(winSize.height/gray->getContentSize().height);
        gray->setPosition(ccp(winSize.width/2,winSize.height/2));
        gray->setTag(grayTag);
        gray->setOpacity(153);
        gray->setColor(ccc3(0,0,0));
        newbieLayer->addChild(gray);
        
        

        CCSprite* trans = CCSprite::create("transparent.png");
        trans->setContentSize(winSize);
        CCMenuItemSprite* nextButton = CCMenuItemSprite::create(trans, CCSprite::create("transparent.png"),this,menu_selector(Newbie3Trigger::toNextCallBack));
        nextButton->setTag(nextButtonTag);
        //    GXShieldTouchMenuItem* nextButton = GXShieldTouchMenuItem::create();
        MyPriorityMenu* menu = MyPriorityMenu::create(-504, nextButton,NULL);
        menu->setPosition(ccp(0,0));
        menu->setTag(newbieMenuTag);
        nextButton->setPosition(ccp(winSize.width/2,winSize.height/2));
        nextButton->setContentSize(winSize);
        newbieLayer->addChild(menu,10);
        scene->addChild(newbieLayer,9);
        scene->getChildByTag(newbieFlowLayerTag)->removeChildByTag(descLabelTag, true);
        CCLabelTTF* avatarLabel = CCLabelTTF::create("点击选中坦克", "Arial" , 30);
        avatarLabel->setAnchorPoint(ccp(0.5,0.5));
//        CCSprite* avatarLabel = CCSprite::createWithSpriteFrameName("newbielabel9.png");
//        avatarLabel->setScale(1.25);
        newbieLayer->addChild(avatarLabel);
        avatarLabel->setPosition(ccp(200, 180));
        avatarLabel->setTag(avatarLabelTag);
    
//        avatarLabel->setAnchorPoint(ccp(1,0));
        
//        CCSprite* tipPress = CCSprite::createWithSpriteFrameName("tipPress.png");
//        tipPress->setPosition(ccp(200,100));
//        tipPress->setScale(2);
//        
//        
//        tipPress->runAction(GXRepeatForever::create(CCEaseElasticOut::create(GXScaleTo::create(2, 1), 1) ));
//        scene->addChild(tipPress,35);
//        tipPress->setTag(tipPressTag);
        
        
        CreatorInfoBean* bean = CreatorInfoBean::create(M5StuartCardId);
        bean->setExperience(MyUtil::getInstance()->getExperienceByUnitLevel(6, 2)-1);
        
        
        MyDeployButton* deploy = MyDeployButton::create(bean, scene, menu_selector(NewbieBattleScene::callback1));
//
        scene->getChildByTag(bingzhongmenuTag)->addChild(deploy);
        deploy->setPosition(ccp(200,100));
        deploy->setTag(stuartDeployButtonTag);
//        deploy->runAction(CCEaseElasticOut::create(CCScaleTo::create(0.8,1),1));
        deploy->runAction(CCEaseElasticOut::create(CCScaleTo::create(0.8,1),1));
//        deploy->runAction(CCSequence::create(CCEaseElasticOut::create(CCScaleTo::create(0.8,1),1),CCCallFuncO::create(this,callfuncO_selector(Newbie3Trigger::shakeEffect2),deploy),NULL));
        
        CCSprite* sprite = CCSprite::createWithSpriteFrameName("deployBack2.png");
        sprite->setPosition(ccp(200,100));
        sprite->runAction(CCRepeatForever::create(static_cast<CCSequence*>(CCSequence::create(CCSpawn::create(CCScaleTo::create(0.5,1.5),CCFadeOut::create(0.5),NULL),CCScaleTo::create(0,1),NULL))));
        newbieLayer->addChild(sprite,0);
        
        
        status++;
    } else if(status == 14) {
        CCNode* node  =scene->getChildByTag(bingzhongmenuTag)->getChildByTag(stuartDeployButtonTag);
        node->setScale(1);
        node->stopAllActions();
        scene->removeChildByTag(tipPressTag, true);
        MyGameInfo::getInstance()->changeResource(oilTag, 20000);
        scene->getMap()->runAction(CCSequence::create(CCEaseInOut::create(CCMoveTo::create(1, ccp(-2000,-1200)), 2),CCCallFunc::create(this,callfunc_selector(Newbie3Trigger::mapMoveCallBack)),NULL) );
        scene->getChildByTag(newbieFlowLayerTag)->getChildByTag(grayTag)->runAction(CCFadeTo::create(1,0));
        
        CCSprite* tipArrow = CCSprite::createWithSpriteFrameName("newbiearrow.png");
        tipArrow->setPosition(ccp(2380,1580));
        scene->getMap()->CCNode::addChild(tipArrow,1000000);
        CCMoveBy* moveBy = CCMoveBy::create(0.5, ccp(0,-50));
        tipArrow->runAction(CCRepeatForever::create(static_cast<CCSequence*>(CCSequence::create(CCEaseInOut::create(moveBy, 2),CCEaseInOut::create(moveBy->reverse(),2),NULL))));
        tipArrow->setTag(tipArrowTag);
        
        CCSprite* tipCircle = CCSprite::createWithSpriteFrameName("tipCircle.png");
        tipCircle->setPosition(ccp(2380,1460));
        scene->getMap()->CCNode::addChild(tipCircle,1000000);
        tipCircle->setScale(1.5);
        CCScaleBy* scaleBy = CCScaleBy::create(0.5, 0.5);
        tipCircle->runAction(CCRepeatForever::create(static_cast<CCSequence*>(CCSequence::create(CCEaseIn::create(scaleBy, 2),CCEaseOut::create(scaleBy->reverse(),2),NULL))));
        tipCircle->setTag(tipCircleTag);
        
        status++;
    } else if(status == 16) {
        scene->getChildByTag(newbieFlowLayerTag)->removeChildByTag(avatarLabelTag,true);
        status++;
    } else if (status == 17) {
        scene->removeChildByTag(newbieFlowLayerTag, true);
        scene->getMap()->removeChildByTag(tipSpotTag, true);
        scene->getMap()->removeChildByTag(tipCircleTag, true);
        scene->getMap()->removeChildByTag(tipArrowTag, true);
        status++;
        MyMessageManage::getInstance()->unRegisterTrigger(this);
    }
}

bool Newbie3Trigger::onRegist() {
    
    CCLayer* newbieLayer = CCLayer::create();
    
//    GXShieldTouchMenuItem* shield = GXShieldTouchMenuItem::create();
//    shield->setContentSize(winSize);
//    shield->setPosition(ccp(winSize.width/2,winSize.height/2));
//    
//    CCMenuItemSprite* iKnow =CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("dialogkonw.png"), CCSprite::createWithSpriteFrameName("dialogknowp.png"),this,menu_selector (Newbie3Trigger::toNextCallBack));
//    iKnow->setPosition(ccp(winSize.width/2+120,winSize.height/2-90));
    
//    MyPriorityMenu* shieldMenu = MyPriorityMenu::create(-600,iKnow, shield,NULL);
//    shieldMenu->setPosition(ccp(0,0));
//    
//    
//    CCLabelTTF* desc = CCLabelTTF::create(GXUtil::insertNewline("　　指挥官，敌人集结的速度已经出乎我们意料，看样子敌军主力即将到达了，趁现在碾碎他们！",14).c_str(), "Arial" , 30, CCSizeMake(440,200), kCCTextAlignmentLeft, kCCVerticalTextAlignmentTop);
//    desc->cocos2d::CCNode::setAnchorPoint(ccp(0.5,1));
//#if   (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
//    desc->setPosition(ccp(winSize.width/2+100,winSize.height/2+90+43/5));
//#endif
//#if   (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
//    desc->setPosition(ccp(winSize.width/2+100,winSize.height/2+90));
//#endif
//    desc->setColor(ccc3(230, 207, 185));
//    
//    newbieLayer->addChild(desc,3);
//    newbieLayer->addChild(shieldMenu,2);
//    CCSprite* dialogBack = MyUtil::getInstance()->getDialogBack();;
//    dialogBack->setPosition(ccp(winSize.width/2,winSize.height/2));
//    newbieLayer->addChild(dialogBack);
    newbieLayer->setTag(newbieFlowLayerTag);
    scene->addChild(newbieLayer,11);
    
    CCSprite* gray = CCSprite::create("whiteImage.jpg");
    gray->setScaleX(winSize.width/gray->getContentSize().width);
    gray->setScaleY(winSize.height/gray->getContentSize().height);
    gray->setColor(ccc3(0,0,0));
    gray->setOpacity(153);
    gray->setPosition(ccp(winSize.width/2,winSize.height/2));
    newbieLayer->addChild(gray);
    
    CCString* str = GXUtil::readFile("NewbieDialog4.j");
    DiaLayer* dialog = DiaLayer::create(GXJsonUtil::parseDiaLayerInfoBean(str->getCString()));
    dialog->setTag(dialogLayerTag);
    scene->addChild(dialog,11);
    
//    newbieLayer->setScale(0.5);
//    newbieLayer->runAction(CCScaleTo::create(0.5, 1));
//    shieldMenu->setOpacity(0);
//    dialogBack->setOpacity(0);
//    shieldMenu->runAction(CCSequence::create(CCDelayTime::create(0.25),CCFadeIn::create(0.25),NULL));
//    dialogBack->runAction(CCSequence::create(CCDelayTime::create(0.25),CCFadeIn::create(0.25),NULL));
//    desc->setOpacity(0);
//    desc->runAction(CCSequence::create(CCDelayTime::create(0.25),CCFadeIn::create(0.25),NULL));
    return false;
}

bool Newbie3Trigger::onUnRegist() {
    //    scene->removeChildByTag(newbieFlowLayerTag, true);
    return true;
}

void Newbie3Trigger::getPrizeCallBack(cocos2d::CCNode *pSender) {
    isDialog=true;
    scene->removeChildByTag(newbieFlowLayerTag, true);
    CCLayer* newbieLayer = CCLayer::create();
    
//    GXShieldTouchMenuItem* shield = GXShieldTouchMenuItem::create();
//    shield->setContentSize(winSize);
//    shield->setPosition(ccp(winSize.width/2,winSize.height/2));
//    
//    CCMenuItemSprite* iKnow =CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("dialogkonw.png"), CCSprite::createWithSpriteFrameName("dialogknowp.png"),this,menu_selector(Newbie3Trigger::toNextCallBack));
//    iKnow->setPosition(ccp(winSize.width/2+120,winSize.height/2-120));
//    
//    MyPriorityMenu* shieldMenu = MyPriorityMenu::create(-504,iKnow, shield,NULL);
//    shieldMenu->setPosition(ccp(0,0));
    
    
//    CCLabelTTF* desc = CCLabelTTF::create(GXUtil::insertNewline("　　指挥官，我们侦测到敌人的哨所就在附近，趁敌人还未发现我们，赶快对他们进行突袭！",14).c_str(), "Arial" , 30, CCSizeMake(440,200), kCCTextAlignmentLeft, kCCVerticalTextAlignmentTop);
//    desc->cocos2d::CCNode::setAnchorPoint(ccp(0.5,1));
//#if   (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
//    desc->setPosition(ccp(winSize.width/2+100,winSize.height/2+90+41/5));
//#endif
//#if   (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
//    desc->setPosition(ccp(winSize.width/2+100,winSize.height/2+90));
//#endif
//    desc->setColor(ccc3(230, 207, 185));
//    
//    newbieLayer->addChild(desc,3);
//    newbieLayer->addChild(shieldMenu,2);
//    CCSprite* dialogBack = MyUtil::getInstance()->getDialogBack();
//    dialogBack->setPosition(ccp(winSize.width/2,winSize.height/2));
//    newbieLayer->addChild(dialogBack);
    newbieLayer->setTag(newbieFlowLayerTag);
    scene->addChild(newbieLayer);
    
    
    
    CCString* str = GXUtil::readFile("NewbieDialog4.j");
    DiaLayer* dialog = DiaLayer::create(GXJsonUtil::parseDiaLayerInfoBean(str->getCString()));
    scene->addChild(dialog,10);
    
    
//    newbieLayer->setScale(0.5);
//    newbieLayer->runAction(CCScaleTo::create(0.5, 1));
//    shieldMenu->setOpacity(0);
//    dialogBack->setOpacity(0);
//    shieldMenu->runAction(CCSequence::create(CCDelayTime::create(0.25),CCFadeIn::create(0.25),NULL));
//    dialogBack->runAction(CCSequence::create(CCDelayTime::create(0.25),CCFadeIn::create(0.25),NULL));
//    desc->setOpacity(0);
//    desc->runAction(CCSequence::create(CCDelayTime::create(0.25),CCFadeIn::create(0.25),NULL));
    
    
    
}

void Newbie3Trigger::toBattleScene(cocos2d::CCNode *pSender) {
    MyMessageManage::getInstance()->unRegisterTrigger(this);
//    scene->toBattleScene();
}

void Newbie3Trigger::mapMoveCallBack() {
    status++;
    toNextCallBack(NULL);
}

void Newbie3Trigger::shakeEffect2(CCNode* node) {
    node->runAction(CCRepeatForever::create(static_cast<CCSequence*>(CCSequence::create(CCScaleTo::create(0.2, 1), CCScaleTo::create(0.2,1.05),NULL))));
}