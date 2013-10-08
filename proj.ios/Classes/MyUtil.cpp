//
//  MyUtil.cpp
//  ww2
//
//  Created by DingYu Fu on 12-9-19.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "MyUtil.h"
#include "PulsarNative.h"
#include "DefineSet.h"
#include "MyPriorityMenu.h"
#include "StartScene.h"
#include "Mathlib.h"
#include "MyHttpConnection.h"
#include "MyJsonUtil.h"
#include "GXShieldTouchMenuItem.h"
#include "GXRemovefromParentsAction.h"
#include "MyBaseQuest.h"


MyUtil::MyUtil():loudSpeakerList(NULL) {
    unsigned long long num = 0;
    for (int i = 0; i<100; i++) {
        num+= i*i*i*1000;
        levelMap[i] = num;
    }
}

static MyUtil* instance = NULL;

MyUtil* MyUtil::getInstance() {
    if(instance == NULL) {
        instance = new MyUtil();
    }
    return instance;
}


void MyUtil::releaseInstance() {
    CC_SAFE_RELEASE_NULL(instance);
    instance = NULL;
}



CCLayer* MyUtil::getNetworkDialog() {
    
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    CCMenuItemSprite* sureItem = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("dialogsure.png"), CCSprite::createWithSpriteFrameName("dialogsurep.png"), this, menu_selector(MyUtil::toExit));
    
    MyPriorityMenu* menu  = MyPriorityMenu::create(-511,sureItem,NULL);
#endif
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    CCMenuItemSprite* sureItem = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("dialogsure.png"), CCSprite::createWithSpriteFrameName("dialogsurep.png"), this, menu_selector(MyUtil::toSettingCallBack));
    
    
    CCMenuItemSprite* cancelItem =CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("dialogcancel.png"), CCSprite::createWithSpriteFrameName("dialogcancelp.png"),this,menu_selector(MyUtil::toExit));
    
    MyPriorityMenu* menu  = MyPriorityMenu::create(-511,sureItem,cancelItem,NULL);
#endif
    menu->alignItemsHorizontallyWithPadding(30);
    menu->setPosition(ccp(winSize.width/2+120, winSize.height/2-100));
    CCLayer* layer = CCLayer::create();
    layer->setTouchEnabled(true);
    CCSprite* gray = CCSprite::create("whiteImage.jpg");
    gray->setPosition(ccp(winSize.width/2,winSize.height/2));
    gray->setScaleX(winSize.width/gray->getContentSize().width);
    gray->setScaleY(winSize.height/gray->getContentSize().height);
    gray->setColor(ccc3(0,0,0));
    gray->setOpacity(153);
    CCLabelTTF* label = CCLabelTTF::create("副官:\n　　指挥官，当前网络连接\n不可用，请联网！", "宋体", 32,CCSizeZero, kCCTextAlignmentLeft, kCCVerticalTextAlignmentTop);
    label->setOpacity(0);
    label->setColor(ccc3(230, 207, 185));
    label->setPosition(ccp(winSize.width/2+120,winSize.height/2+40));
    layer->addChild(gray);
    CCSprite* dialogBack = MyUtil::getInstance()->getDialogBack();
    dialogBack->setPosition(ccp(winSize.width/2,winSize.height/2));
    layer->addChild(dialogBack);
    layer->addChild(menu);
    layer->addChild(label);
    layer->setScale(0.5);
    layer->runAction(CCScaleTo::create(0.5, 1));
    menu->setOpacity(0);
    dialogBack->setOpacity(0);
    gray->setOpacity(0);
    menu->runAction(CCSequence::create(CCDelayTime::create(0.25),CCFadeIn::create(0.25),NULL));
    dialogBack->runAction(CCSequence::create(CCDelayTime::create(0.25),CCFadeIn::create(0.25),NULL));
    gray->runAction(CCSequence::create(CCDelayTime::create(0.25),CCFadeIn::create(0.25),NULL));
    label->runAction(CCSequence::create(CCDelayTime::create(0.25),CCFadeIn::create(0.25),NULL));
    return layer;
}

CCLayer* MyUtil::getNoResourceDialog(CCObject* target,int resourceTag) {
    CCMenuItemSprite* sureItem;
    ((CCNode*)target)->removeChildByTag(NoResourceTag,true);
    MyPriorityMenu* menu  = MyPriorityMenu::create(-511,NULL);
    if (resourceTag != diamondTag) {
        if (MyUtil::getInstance()->getLevelByExperience(MyGameInfo::getInstance()->getExperience()) >= 15) {
            CCSprite* up =  CCSprite::createWithSpriteFrameName("unionCommonSingleButton.png");
            up->setScaleX(90/up->getContentSize().width);
            up->setContentSize(CCSizeMake(90,up->getContentSize().height));
            CCSprite* down =  CCSprite::createWithSpriteFrameName("unionCommonSingleButtonP.png");
            down->setScaleX(90/down->getContentSize().width);
            down->setContentSize(CCSizeMake(90,down->getContentSize().height));
            CCMenuItemSprite* goBattle = CCMenuItemSprite::create(up,down, target, menu_selector(StartScene::toBattleScene));
            goBattle->setPosition(ccp(180,-40));
            CCLabelTTF* goBattleLabel = CCLabelTTF::create("去征战","Arial",25);
            goBattleLabel->setPosition(ccp(goBattle->getContentSize().width/2,goBattle->getContentSize().height/2));
            goBattle->addChild(goBattleLabel);
            goBattleLabel->setColor(ccc3(230, 207, 185));
            
            CCSprite* up2 =  CCSprite::createWithSpriteFrameName("unionCommonSingleButton.png");
            up2->setScaleX(90/up2->getContentSize().width);
            up2->setContentSize(CCSizeMake(90,up2->getContentSize().height));
            CCSprite* down2 =  CCSprite::createWithSpriteFrameName("unionCommonSingleButtonP.png");
            down2->setScaleX(90/down2->getContentSize().width);
            down2->setContentSize(CCSizeMake(90,down2->getContentSize().height));
            CCMenuItemSprite* goShop = CCMenuItemSprite::create(up2,down2, target, menu_selector(StartScene::toShopCallBackWait));
            goShop->setPosition(ccp(60,-40));
            CCLabelTTF* goShopLabel = CCLabelTTF::create("去商城","Arial",25);
            goShopLabel->setPosition(ccp(goShop->getContentSize().width/2,goShop->getContentSize().height/2));
            goShop->addChild(goShopLabel);
            goShopLabel->setColor(ccc3(230, 207, 185));
            
            menu->addChild(goShop);
            menu->addChild(goBattle);
        } else {
            sureItem = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("dialogsure.png"), CCSprite::createWithSpriteFrameName("dialogsurep.png"), target, menu_selector(StartScene::toBattleScene));
            
            sureItem->setPosition(ccp(120,-40));
            menu->addChild(sureItem);
        }
    } else {
        sureItem = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("dialogsure.png"), CCSprite::createWithSpriteFrameName("dialogsurep.png"), target, menu_selector(StartScene::toDisplayCharge));
        
        sureItem->setPosition(ccp(120,-40));
        menu->addChild(sureItem);
    }
  
    
    CCMenuItemSprite* cancelItem =CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("uiDialogCancelButton.png"), CCSprite::createWithSpriteFrameName("uiDialogCancelButtonP.png"),this,menu_selector(MyUtil::dismiss));
    
   
    menu->addChild(cancelItem);
    
    menu->setPosition(ccp(winSize.width/2, winSize.height/2 -48));
    CCLayer* layer = CCLayer::create();
    layer->setTouchEnabled(true);
    CCLabelTTF* label;
    if (resourceTag != diamondTag) {
        label = CCLabelTTF::create("副官:\n　　指挥官:资源余额不足,\n去征战获得更多资源！", "宋体", 32,CCSizeZero, kCCTextAlignmentLeft, kCCVerticalTextAlignmentTop);
        label->setPosition(ccp(winSize.width/2+120,winSize.height/2+30));
    } else {
        label = CCLabelTTF::create("副官:\n　　指挥官:钻石余额不足,\n去商城购买钻石,打造完美\n军队！", "宋体", 32,CCSizeZero, kCCTextAlignmentLeft, kCCVerticalTextAlignmentTop);
        label->setPosition(ccp(winSize.width/2+120,winSize.height/2+40));
    }
    
    
    label->setOpacity(0);
    label->setColor(ccc3(230, 207, 185));
    
    
    CCSprite* dialogBack = MyUtil::getInstance()->getDialogBack();
    dialogBack->setPosition(ccp(winSize.width/2,winSize.height/2));
    cancelItem->setPosition(ccp(dialogBack->getContentSize().width/2 - 24,dialogBack->getContentSize().height/2 + 24));
    layer->addChild(dialogBack);
    layer->addChild(menu);
    layer->addChild(label);
    layer->setScale(0.5);
    layer->runAction(CCScaleTo::create(0.5, 1));
    layer->setTag(NoResourceTag);
    menu->setOpacity(0);
    dialogBack->setOpacity(0);
    menu->runAction(CCSequence::create(CCDelayTime::create(0.25),CCFadeIn::create(0.25),NULL));
    dialogBack->runAction(CCSequence::create(CCDelayTime::create(0.25),CCFadeIn::create(0.25),NULL));
    
    label->runAction(CCSequence::create(CCDelayTime::create(0.25),CCFadeIn::create(0.25),NULL));
    return layer;
}

CCLayer* MyUtil::getNoGloryDialog() {
    CCMenuItemSprite* sureItem = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("dialogsure.png"), CCSprite::createWithSpriteFrameName("dialogsurep.png"), this, menu_selector(MyUtil::dismiss));
    sureItem->setPosition(ccp(120,-40));
    
    
    CCMenuItemSprite* cancelItem =CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("uiDialogCancelButton.png"), CCSprite::createWithSpriteFrameName("uiDialogCancelButtonP.png"),this,menu_selector(MyUtil::dismiss));
    
    MyPriorityMenu* menu  = MyPriorityMenu::create(-511,sureItem,cancelItem,NULL);
    
    
    menu->setPosition(ccp(winSize.width/2, winSize.height/2 -48));
    CCLayer* layer = CCLayer::create();
    layer->setTouchEnabled(true);
    CCLabelTTF* label = CCLabelTTF::create("副官:\n　　指挥官：您的功勋不足，去征战获得更多功勋", "宋体", 32,CCSizeMake(300,200), kCCTextAlignmentLeft, kCCVerticalTextAlignmentTop);
    
    label->setOpacity(0);
    label->setColor(ccc3(230, 207, 185));
    label->setPosition(ccp(winSize.width/2+120,winSize.height/2+30));
    
    CCSprite* dialogBack = MyUtil::getInstance()->getDialogBack();
    dialogBack->setPosition(ccp(winSize.width/2,winSize.height/2));
    cancelItem->setPosition(ccp(dialogBack->getContentSize().width/2 - 24,dialogBack->getContentSize().height/2 + 24));
    layer->addChild(dialogBack);
    layer->addChild(menu);
    layer->addChild(label);
    layer->setScale(0.5);
    layer->runAction(CCScaleTo::create(0.5, 1));
    layer->setTag(NoResourceTag);
    menu->setOpacity(0);
    dialogBack->setOpacity(0);
    menu->runAction(CCSequence::create(CCDelayTime::create(0.25),CCFadeIn::create(0.25),NULL));
    dialogBack->runAction(CCSequence::create(CCDelayTime::create(0.25),CCFadeIn::create(0.25),NULL));
    
    label->runAction(CCSequence::create(CCDelayTime::create(0.25),CCFadeIn::create(0.25),NULL));
    return layer;
    
}

void MyUtil::toSettingCallBack() {
    PulsarNative::toSetting();
    CCDirector::sharedDirector()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

void MyUtil::toExit() {
    CCDirector::sharedDirector()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

void MyUtil::dismiss(CCNode* pSender) {
    pSender->getParent()->getParent()->removeFromParentAndCleanup(true);
}

float MyUtil::updateLevelByRate(float ori,float base, float level, float rate) {
    float num = base;
    for (int i = 1; i<level; i++) {
        
        num+= (i*rate*base);
    }
    return num+ori;
}

float MyUtil::updateLevelByCount(float base,int level,float count) {
    float num = base;
    for (int i = 1; i<level; i++) {
        
        num+= count;
    }
    return num;
}
float MyUtil::updateLevelBySquare(float base, int level, int rate) {
    float num = base;
    for (int i = 1; i<level; i++) {
        num+= (i*i*rate*base);
    }
    return num;
}

CCLayer* MyUtil::getWaitLayer(const char* label){
    CCSprite* wait = CCSprite::createWithSpriteFrameName("wait.png");
    GXShieldTouchMenuItem* shieldTouch= GXShieldTouchMenuItem::create();
    wait->setPosition(ccp(winSize.width/2,winSize.height/2+20));
    wait->runAction(CCRepeatForever::create(static_cast<CCSequence*>(CCSequence::create(CCRotateBy::create(0,30),CCDelayTime::create(0.1),NULL))));
    shieldTouch->setContentSize(winSize);
    shieldTouch->setPosition(ccp(winSize.width/2,winSize.height/2));
    CCLabelTTF* waitLabel = CCLabelTTF::create(label, "Arial",30);
    waitLabel->setPosition(ccp(winSize.width/2,winSize.height/2-50));
    
    shieldTouch->addChild(wait);
    shieldTouch->addChild(waitLabel);
    MyPriorityMenu* waitmenu = MyPriorityMenu::create(-509, shieldTouch,NULL);
    waitmenu->setPosition(ccp(0,0));
    waitmenu->setTag(waitMenuTag);
    waitLabel->setOpacity(0);
    wait->setOpacity(0);
    waitLabel->runAction(CCSequence::create(CCDelayTime::create(0.1),CCFadeIn::create(0.1),NULL));
    wait->runAction(CCSequence::create(CCDelayTime::create(0.1),CCFadeIn::create(0.1),NULL));
    return waitmenu;
}

CCLayer* MyUtil::getSaveLayer(){
    CCSprite* wait = CCSprite::createWithSpriteFrameName("saveIcon.png");
    GXShieldTouchMenuItem* shieldTouch= GXShieldTouchMenuItem::create();
    wait->setPosition(ccp(winSize.width/2,winSize.height/2+20));
    shieldTouch->setContentSize(winSize);
    shieldTouch->setPosition(ccp(winSize.width/2,winSize.height/2));
    CCLabelTTF* waitLabel = CCLabelTTF::create("正在与服务器通信，请勿强制退出", "Arial",30);
    waitLabel->setPosition(ccp(winSize.width/2,winSize.height/2-50));
    
    shieldTouch->addChild(wait);
    shieldTouch->addChild(waitLabel);
    MyPriorityMenu* waitmenu = MyPriorityMenu::create(-505, shieldTouch,NULL);
    waitmenu->setPosition(ccp(0,0));
    waitmenu->setTag(waitMenuTag);
    waitLabel->setOpacity(0);
    wait->setOpacity(0);
    waitLabel->runAction(CCSequence::create(CCDelayTime::create(0.1),CCFadeIn::create(0.1),NULL));
    wait->runAction(CCSequence::create(CCDelayTime::create(0.1),CCFadeIn::create(0.1),NULL));
    return waitmenu;
}

int MyUtil::getLevelByExperience(unsigned long long _exp) {
    //    float num = base;
    //    for (int i = 1; i<level; i++) {
    //
    //        num+= (i*rate*base);
    //    }
    for (int i = 1; i<100; i++) {
        if (_exp < levelMap[i]) {
            
            return i;
        }
    }
    return 100;
}

int MyUtil::getUnitLevelByExperience(unsigned long long _exp,float rarity) {
    for (int i = 1; i<100; i++) {
        if (_exp < (levelMap[i]/i)*(rarity/3)) {
            return i;
        }
    }
    return 100;
}

unsigned long long MyUtil::getExperienceByUnitLevel(int _level, float rarity) {
    if (_level < 1) {
        return 0;
    }
    return (levelMap[_level]/_level)*(rarity/3);
}

unsigned long long MyUtil::getExperienceByLevel(int level) {
    return levelMap[level];
}

CCLayer* MyUtil::getScanEnemyLayer(){
    CCSprite* wait = CCSprite::createWithSpriteFrameName("scanEnemy.png");
    wait->setScale(0.7);
    GXShieldTouchMenuItem* shieldTouch= GXShieldTouchMenuItem::create();
    wait->setPosition(ccp(winSize.width/2,winSize.height/2+20));
    shieldTouch->setContentSize(winSize);
    shieldTouch->setPosition(ccp(winSize.width/2,winSize.height/2));
//    CCLabelTTF* waitLabel = CCLabelTTF::create("正在搜索敌情", "Arial", 30);
//    waitLabel->setPosition(ccp(winSize.width/2,winSize.height/2-50));
    
    shieldTouch->addChild(wait);
//    shieldTouch->addChild(waitLabel);
    MyPriorityMenu* waitmenu = MyPriorityMenu::create(-505, shieldTouch,NULL);
    waitmenu->setPosition(ccp(0,0));
    waitmenu->setTag(waitMenuTag);
    wait->setOpacity(0);
    wait->runAction(CCSequence::create(CCDelayTime::create(0.1),CCFadeIn::create(0.1),NULL));
    return waitmenu;
}

const char* MyUtil::getNickNamebyNet() {
//    return MyJsonUtil::parseUserData(MyHttpConnection::getInstance()->getUserData())->getCString();
    return "";
}

CCSprite* MyUtil::getRankSprite(float power) {
    if (power<0) {
        return CCSprite::createWithSpriteFrameName("rank (-1).png");
    } else if(power<20) {
        return CCSprite::createWithSpriteFrameName("rank (0).png");
    } else if(power <50) {
        return CCSprite::createWithSpriteFrameName("rank (1).png");
    } else if(power <100) {
        return CCSprite::createWithSpriteFrameName("rank (2).png");
    } else if(power <500) {
        return CCSprite::createWithSpriteFrameName("rank (3).png");
    } else if(power <1000) {
        return CCSprite::createWithSpriteFrameName("rank (4).png");
    } else if(power <2000) {
        return CCSprite::createWithSpriteFrameName("rank (5).png");
    } else if(power <5000) {
        return CCSprite::createWithSpriteFrameName("rank (6).png");
    } else if(power <10000) {
        return CCSprite::createWithSpriteFrameName("rank (7).png");
    } else if(power <20000) {
        return CCSprite::createWithSpriteFrameName("rank (8).png");
    } else if(power <50000) {
        return CCSprite::createWithSpriteFrameName("rank (9).png");
    } else {
        return CCSprite::createWithSpriteFrameName("rank (10).png");
    }
}

const char* MyUtil::getRankString(float power) {
    if (power < 0) {
        return "不明";
    }else if(power<20) {
        return "列兵";
    } else if(power <50) {
        return "下士";
    } else if(power <100) {
        return "中士";
    } else if(power <500) {
        return "上士";
    } else if(power <1000) {
        return "少尉";
    } else if(power <2000) {
        return "中尉";
    } else if(power <5000) {
        return "上尉";
    } else if(power <10000) {
        return "少校";
    } else if(power <20000) {
        return "中校";
    } else if(power <50000) {
        return "上校";
    } else {
        return "元帅";
    }
}

ConscribeInfoBean* MyUtil::cardLottery(cocos2d::CCArray *conscribeArray) {
    int time = 9 - conscribeArray->count();
    int max = 0;
    CCObject* obj = NULL;
    CCARRAY_FOREACH(conscribeArray, obj) {
        ConscribeInfoBean* bean = (ConscribeInfoBean*)obj;
        max += bean->randomSeed[time];
        //        CCLog("%d",bean->randomSeed[time]);
    }
    int random = arc4random()%max +1;
    int count = conscribeArray->count();
    int sum=0;
    for (int i =0; i<count; i++) {
        ConscribeInfoBean* ibean = (ConscribeInfoBean*)conscribeArray->objectAtIndex(i);
        for (int j=i+1; j<count; j++) {
            ConscribeInfoBean* jbean = (ConscribeInfoBean*)conscribeArray->objectAtIndex(j);
            if (jbean->randomSeed[time] <ibean->randomSeed[time]) {
                conscribeArray->exchangeObject(ibean, jbean);
                ibean = jbean;
            }
        }
        sum+=ibean->randomSeed[time];
        //        CCLog("%d",ibean->randomSeed[time]);
        if (random<=sum) {
            ibean->retain();
            conscribeArray->fastRemoveObject(ibean);
            return ibean;
        }
    }
    //    ConscribeInfoBean* bean = ConscribeInfoBean->downIndex
    return NULL;
}

float MyUtil::getSummaryGloryByFlopTime(int time) {
    if (time == 0) {
        return 100;
    } else if (time == 1) {
        return 200;
    } else if (time == 2) {
        return 500;
    } else if (time == 3) {
        return 1000;
    }
    return 9999999;
}

int MyUtil::getUnitStrenthanExp(CreatorInfoBean *bean) {
    return bean->getExperience()*1.2+500*(bean->creator->getRarity())*(bean->creator->getRarity())*(bean->creator->getRarity());
}

int MyUtil::getVirtoryGloryFromEnemy(float enemyPower) {
    return 30+enemyPower/4;
}

CCSprite* MyUtil::getResourceIcon(int resourceTag) {
    if (resourceTag == oilTag) {
        return CCSprite::createWithSpriteFrameName("oilIcon.png");
    }else if (resourceTag == ironTag) {
        return CCSprite::createWithSpriteFrameName("ironIcon.png");
    } else if (resourceTag == expTag) {
        return CCSprite::createWithSpriteFrameName("expIcon.png");
    } else if (resourceTag == gloryTag) {
        return CCSprite::createWithSpriteFrameName("honorIcon.png");
    } else if (resourceTag == diamondTag) {
        return CCSprite::createWithSpriteFrameName("diamond.png");
    } else if (resourceTag == levelTag) {
        return CCSprite::createWithSpriteFrameName("levelIcon.png");
    } else if (resourceTag == powerTag) {
        return getRankSprite(MyGameInfo::getInstance()->getPower());
    }
    return NULL;
}

CCSprite* MyUtil::getRecordBack() {
    CCSprite* parent = CCSprite::create("transparent.png");
    CCSprite* black = CCSprite::create("whiteImage.jpg");
    black->setColor(ccc3(49,34,21));
    black->setScaleX(752/black->getContentSize().width);
    black->setScaleY(456/black->getContentSize().height);
    parent->setContentSize(CCSizeMake(757,536));
    CCSprite* back = CCSprite::createWithSpriteFrameName("uiDialogBack.png");
    black->setPosition(ccp(378,262));
    back->setPosition(ccp(528,262));
    back->setOpacity(200);
    parent->addChild(black);
    parent->addChild(back);
    
    CCSprite* kuangu = CCSprite::createWithSpriteFrameName("uiDialogCommonKuang.png");
    CCSprite* kuangr = CCSprite::createWithSpriteFrameName("uiDialogCommonKuang.png");
    CCSprite* kuangd = CCSprite::createWithSpriteFrameName("uiDialogCommonKuang.png");
    CCSprite* kuangl = CCSprite::createWithSpriteFrameName("uiDialogCommonKuang.png");
    kuangu->setAnchorPoint(ccp(0.5,1));
    kuangu->setPosition(ccp(378,506));
    kuangu->setScaleX(1.1);
    kuangl->setAnchorPoint(ccp(0.5,1));
    kuangl->setRotation(270);
    kuangl->setPosition(ccp(0,262));
    kuangl->setScaleX(0.7);
    kuangr->setAnchorPoint(ccp(0.5,1));
    kuangr->setRotation(90);
    kuangr->setPosition(ccp(757,262));
    kuangr->setScaleX(0.7);
    kuangd->setAnchorPoint(ccp(0.5,1));
    kuangd->setRotation(180);
    kuangd->setPosition(ccp(378,20));
    kuangd->setScaleX(1.1);
    parent->addChild(kuangu);
    parent->addChild(kuangr);
    parent->addChild(kuangl);
    parent->addChild(kuangd);
    
    
    CCSprite* cornerru = CCSprite::createWithSpriteFrameName("uiDialogNormalCorner.png");
    CCSprite* cornerld = CCSprite::createWithSpriteFrameName("uiDialogMetalCorner.png");
    CCSprite* cornerrd = CCSprite::createWithSpriteFrameName("uiDialogNormalCorner.png");
    cornerru->setAnchorPoint(ccp(0,0));
    cornerru->setPosition(ccp(757,506));
    cornerru->setRotation(180);
    cornerrd->setAnchorPoint(ccp(0,0));
    cornerrd->setPosition(ccp(757,20));
    cornerrd->setRotation(270);
    cornerld->setAnchorPoint(ccp(0,0));
    cornerld->setPosition(ccp(-8,10));
    parent->addChild(cornerru);
    parent->addChild(cornerrd);
    parent->addChild(cornerld);
    
    CCSprite* up = CCSprite::createWithSpriteFrameName("UIDialogCommon1.png");
    up->setAnchorPoint(ccp(0,0));
    up->setPosition(ccp(0,480));
    parent->addChild(up);
    
    return parent;
    //    return  CCSprite::createWithSpriteFrameName("uiDialogBack.png");
}

CCSprite* MyUtil::getVictoryUIBack() {
    //637 493
    CCSprite* parent = CCSprite::create("transparent.png");
    CCSprite* black = CCSprite::create("whiteImage.jpg");
    black->setColor(ccc3(49,34,21));
    black->setScaleX(600/black->getContentSize().width);
    black->setScaleY(400/black->getContentSize().height);
    parent->setContentSize(CCSizeMake(620,420));
    CCSprite* back = CCSprite::createWithSpriteFrameName("uiDialogBack.png");
    black->setPosition(ccp(310,210));
    back->setPosition(ccp(369,210));
    back->setOpacity(200);
    back->setScale(0.85);
    parent->addChild(black);
    parent->addChild(back);
    
    CCSprite* kuangu = CCSprite::createWithSpriteFrameName("uiDialogCommonKuang.png");
    CCSprite* kuangr = CCSprite::createWithSpriteFrameName("uiDialogCommonKuang.png");
    CCSprite* kuangd = CCSprite::createWithSpriteFrameName("uiDialogCommonKuang.png");
    CCSprite* kuangl = CCSprite::createWithSpriteFrameName("uiDialogCommonKuang.png");
    kuangu->setAnchorPoint(ccp(0.5,1));
    kuangu->setPosition(ccp(310,420));
    kuangu->setScaleX(0.85);
    kuangl->setAnchorPoint(ccp(0.5,1));
    kuangl->setRotation(270);
    kuangl->setPosition(ccp(0,210));
    kuangl->setScaleX(0.55);
    kuangr->setAnchorPoint(ccp(0.5,1));
    kuangr->setRotation(90);
    kuangr->setPosition(ccp(620,210));
    kuangr->setScaleX(0.55);
    kuangd->setAnchorPoint(ccp(0.5,1));
    kuangd->setRotation(180);
    kuangd->setScaleX(0.85);
    kuangd->setPosition(ccp(310,0));
    parent->addChild(kuangu);
    parent->addChild(kuangr);
    parent->addChild(kuangl);
    parent->addChild(kuangd);
    
    CCSprite* cornerlu = CCSprite::createWithSpriteFrameName("uiDialogMetalCorner.png");
    CCSprite* cornerru = CCSprite::createWithSpriteFrameName("uiDialogMetalCorner.png");
    CCSprite* cornerld = CCSprite::createWithSpriteFrameName("uiDialogMetalCorner.png");
    CCSprite* cornerrd = CCSprite::createWithSpriteFrameName("uiDialogMetalCorner.png");
    cornerlu->setAnchorPoint(ccp(0,0));
    cornerlu->setPosition(ccp(-10,427));
    cornerlu->setRotation(90);
    cornerru->setAnchorPoint(ccp(0,0));
    cornerru->setPosition(ccp(627,430));
    cornerru->setRotation(180);
    cornerrd->setAnchorPoint(ccp(0,0));
    cornerrd->setPosition(ccp(630,-7));
    cornerrd->setRotation(270);
    cornerld->setAnchorPoint(ccp(0,0));
    cornerld->setPosition(ccp(-7,-10));
    parent->addChild(cornerlu);
    parent->addChild(cornerru);
    parent->addChild(cornerrd);
    parent->addChild(cornerld);
    
    return parent;
}

CCSprite* MyUtil::getDialogBack() {
    //544 334
    CCSprite* parent = CCSprite::create("transparent.png");
    CCSprite* black = CCSprite::create("whiteImage.jpg");
    black->setColor(ccc3(49,34,21));
    black->setScaleX(564/black->getContentSize().width);
    black->setScaleY(334/black->getContentSize().height);
    parent->setContentSize(CCSizeMake(684,334));
    CCSprite* back = CCSprite::createWithSpriteFrameName("uiDialogBack.png");
    black->setPosition(ccp(392,167));
    back->setPosition(ccp(462,167));
    back->setOpacity(200);
    back->setScale(0.7);
    parent->addChild(black);
    parent->addChild(back);
    
    CCSprite* kuangu = CCSprite::createWithSpriteFrameName("uiDialogCommonKuang.png");
    CCSprite* kuangr = CCSprite::createWithSpriteFrameName("uiDialogCommonKuang.png");
    CCSprite* kuangd = CCSprite::createWithSpriteFrameName("uiDialogCommonKuang.png");
    kuangu->setAnchorPoint(ccp(0.5,1));
    kuangu->setPosition(ccp(437,334));
    kuangu->setScaleX(0.7);
    kuangr->setAnchorPoint(ccp(0.5,1));
    kuangr->setRotation(90);
    kuangr->setPosition(ccp(684,167));
    kuangr->setScaleX(0.45);
    kuangd->setAnchorPoint(ccp(0.5,1));
    kuangd->setRotation(180);
    kuangd->setPosition(ccp(342,0));
    kuangd->setScaleX(1);
    parent->addChild(kuangu);
    parent->addChild(kuangr);
    parent->addChild(kuangd);
    
    
    CCSprite* cornerru = CCSprite::createWithSpriteFrameName("uiDialogNormalCorner.png");
    cornerru->setAnchorPoint(ccp(0,0));
    cornerru->setPosition(ccp(684,334));
    cornerru->setRotation(180);
    parent->addChild(cornerru);
    
    CCSprite* up = CCSprite::createWithSpriteFrameName("UIDialogCommon1.png");
    up->setAnchorPoint(ccp(0,0));
    up->setPosition(ccp(80,308));
    parent->addChild(up);
    
    CCSprite* right = CCSprite::createWithSpriteFrameName("uiDialogCommon2.png");
    right->setAnchorPoint(ccp(1,0));
    right->setPosition(ccp(684,0));
    parent->addChild(right);
    
    CCSprite* girl = CCSprite::createWithSpriteFrameName("girl.png");
    girl->setAnchorPoint(ccp(0,0.5));
    girl->setPosition(ccp(-15,177));
    parent->addChild(girl);
    
    return parent;
}

CCSprite* MyUtil::getUnionBack() {
    int width = winSize.width;
    int height = winSize.height;
    float beilv = winSize.width/960;
    CCSprite* parent = CCSprite::create("transparent.png");
    CCSprite* back = CCSprite::createWithSpriteFrameName("armyback.png");
    back->setScaleX(1.371*beilv);
    back->setScaleY(1.371);
    back->setPosition(ccp(winSize.width/2-40,winSize.height/2+1));
    parent->setContentSize(CCSizeMake(width,height));
    
    parent->addChild(back);
    
    
    
    CCSprite* upl = CCSprite::createWithSpriteFrameName("unionCommonUp");
    upl->setAnchorPoint(ccp(0,1));
    upl->setScaleX((winSize.width/2+1)/upl->getContentSize().width);
    upl->setPosition(ccp(0,height));
    parent->addChild(upl);
    
    CCSprite* upr = CCSprite::createWithSpriteFrameName("unionCommonUp");
    upr->setAnchorPoint(ccp(1,1));
    upr->setPosition(ccp(width,height));
    upr->setScaleX((winSize.width/2+1)/upr->getContentSize().width);
    upr->setFlipX(true);
    parent->addChild(upr);
    
    CCSprite* downl = CCSprite::createWithSpriteFrameName("unionCommonDown");
    downl->setAnchorPoint(ccp(0,0));
    downl->setScaleX((winSize.width/2+2)/downl->getContentSize().width);
    downl->setPosition(ccp(0,0));
    parent->addChild(downl);
    
    CCSprite* downr = CCSprite::createWithSpriteFrameName("unionCommonDown");
    downr->setAnchorPoint(ccp(1,0));
    downr->setPosition(ccp(width,0));
    downr->setScaleX((winSize.width/2+2)/downr->getContentSize().width);
    downr->setFlipX(true);
    parent->addChild(downr);
    
    return parent;
}



CCLayer* MyUtil::getCommonTipDialog(CCString* str,cocos2d::CCObject *rec, SEL_MenuHandler selector,int mode) {
    MyPriorityMenu* menu =NULL;
    if (mode == 1) {
        CCMenuItemSprite* sureItem = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("dialogsure.png"), CCSprite::createWithSpriteFrameName("dialogsurep.png"), rec,selector);
        
        
        CCMenuItemSprite* cancelItem =CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("dialogcancel.png"), CCSprite::createWithSpriteFrameName("dialogcancelp.png"),this,menu_selector(MyUtil::cancelTipItem));
        
        menu  = MyPriorityMenu::create(-511,sureItem,cancelItem,NULL);
        menu->alignItemsHorizontallyWithPadding(30);
        menu->setPosition(ccp(winSize.width/2+120, winSize.height/2-100));
        GXShieldTouchMenuItem* shieldTouch= GXShieldTouchMenuItem::create();
        shieldTouch->setContentSize(winSize);
        shieldTouch->setPosition(ccp(winSize.width/2,winSize.height/2));
        menu->addChild(shieldTouch);
    } else {
        CCMenuItemSprite* sureItem = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("dialogkonw.png"), CCSprite::createWithSpriteFrameName("dialogknowp.png"), rec, selector);
        sureItem->setPosition(ccp(winSize.width/2+120, winSize.height/2-100));
        
        GXShieldTouchMenuItem* shieldTouch= GXShieldTouchMenuItem::create();
        shieldTouch->setContentSize(winSize);
        shieldTouch->setPosition(ccp(winSize.width/2,winSize.height/2));
        
        menu  = MyPriorityMenu::create(-611,sureItem,shieldTouch,NULL);
        
        menu->setPosition(ccp(0,0));
    }
    CCLayer* layer = CCLayer::create();
    layer->setTouchEnabled(true);
    CCSprite* gray = CCSprite::create("whiteImage.jpg");
    gray->setPosition(ccp(winSize.width/2,winSize.height/2));
    gray->setScaleX(winSize.width/gray->getContentSize().width);
    gray->setScaleY(winSize.height/gray->getContentSize().height);
    gray->setColor(ccc3(0,0,0));
    gray->setOpacity(0);
    char str123[1000] = {0};
    sprintf(str123,"副官:\n　　指挥官，%s",str->getCString());
    CCLabelTTF* label = CCLabelTTF::create(str123, "Arial", 32,CCSizeMake(390,0), kCCTextAlignmentLeft, kCCVerticalTextAlignmentTop);
    label->setOpacity(0);
    label->setColor(ccc3(230, 207, 185));
    label->setPosition(ccp(winSize.width/2+120,winSize.height/2+40));
    layer->addChild(gray);
    CCSprite* dialogBack = MyUtil::getInstance()->getDialogBack();
    dialogBack->setPosition(ccp(winSize.width/2,winSize.height/2));
    layer->addChild(dialogBack);
    layer->addChild(menu);
    layer->addChild(label);
    layer->setScale(0.5);
    layer->runAction(CCScaleTo::create(0.2, 1));
    menu->setOpacity(0);
    dialogBack->setOpacity(0);
    gray->setOpacity(0);
    menu->runAction(CCSequence::create(CCDelayTime::create(0.1),CCFadeIn::create(0.1),NULL));
    dialogBack->runAction(CCSequence::create(CCDelayTime::create(0.1),CCFadeIn::create(0.1),NULL));
    gray->runAction(CCSequence::create(CCDelayTime::create(0.1),CCFadeTo::create(0.1,153),NULL));
    label->runAction(CCSequence::create(CCDelayTime::create(0.1),CCFadeIn::create(0.1),NULL));
    return layer;
}

void MyUtil::cancelTipItem(CCMenuItem* item) {
    item->getParent()->getParent()->removeFromParentAndCleanup(true);
}


CCSprite* MyUtil::getCreateUnionBack(){
    //836 460
    CCSprite* parent = CCSprite::create("transparent.png");
    CCSprite* black = CCSprite::create("whiteImage.jpg");
    black->setColor(ccc3(0,0,0));
    black->setOpacity(60);
    black->setScaleX(836/black->getContentSize().width);
    black->setScaleY(460/black->getContentSize().height);
    parent->setContentSize(CCSizeMake(836,460));
    black->setPosition(ccp(418,230));
    parent->addChild(black);
    
    CCSprite* kuangu = CCSprite::createWithSpriteFrameName("uiDialogCommonKuang.png");
    CCSprite* kuangr = CCSprite::createWithSpriteFrameName("uiDialogCommonKuang.png");
    CCSprite* kuangd = CCSprite::createWithSpriteFrameName("uiDialogCommonKuang.png");
    CCSprite* kuangl = CCSprite::createWithSpriteFrameName("uiDialogCommonKuang.png");
    kuangu->setAnchorPoint(ccp(0.5,1));
    kuangu->setPosition(ccp(418,460));
    kuangu->setScaleX(1.2);
    kuangl->setAnchorPoint(ccp(0.5,1));
    kuangl->setRotation(270);
    kuangl->setPosition(ccp(0,230));
    kuangl->setScaleX(0.65);
    kuangr->setAnchorPoint(ccp(0.5,1));
    kuangr->setRotation(90);
    kuangr->setPosition(ccp(836,230));
    kuangr->setScaleX(0.65);
    kuangd->setAnchorPoint(ccp(0.5,1));
    kuangd->setRotation(180);
    kuangd->setPosition(ccp(418,0));
    kuangd->setScaleX(1.2);
    parent->addChild(kuangu);
    parent->addChild(kuangr);
    parent->addChild(kuangl);
    parent->addChild(kuangd);
    
    
    CCSprite* cornerru = CCSprite::createWithSpriteFrameName("uiDialogNormalCorner.png");
    CCSprite* cornerld = CCSprite::createWithSpriteFrameName("uiDialogMetalCorner.png");
    CCSprite* cornerrd = CCSprite::createWithSpriteFrameName("uiDialogNormalCorner.png");
    cornerru->setAnchorPoint(ccp(0,0));
    cornerru->setPosition(ccp(836,460));
    cornerru->setRotation(180);
    cornerrd->setAnchorPoint(ccp(0,0));
    cornerrd->setPosition(ccp(836,0));
    cornerrd->setRotation(270);
    cornerld->setAnchorPoint(ccp(0,0));
    cornerld->setPosition(ccp(-8,-10));
    parent->addChild(cornerru);
    parent->addChild(cornerrd);
    parent->addChild(cornerld);
    
    CCSprite* up = CCSprite::createWithSpriteFrameName("UIDialogCommon1.png");
    up->setAnchorPoint(ccp(0,0));
    up->setPosition(ccp(0,434));
    parent->addChild(up);
    
    CCSprite* right = CCSprite::createWithSpriteFrameName("uiDialogCommon2.png");
    right->setAnchorPoint(ccp(1,0));
    right->setPosition(ccp(836,0));
    parent->addChild(right);
    
    CCSprite* dividingLine = CCSprite::createWithSpriteFrameName("uiDialogCommonLine.png");
    dividingLine->setScaleX(2.45);
    dividingLine->setPosition(ccp(150,225));
    dividingLine->setRotation(90);
    parent->addChild(dividingLine);
    
    return parent;
}

CCSprite* MyUtil::getLineBox(float width, float height) {
    CCSprite* parent = CCSprite::create("transparent.png");
    parent->setContentSize(CCSizeMake(width,height));
    CCSprite* l = CCSprite::createWithSpriteFrameName("uiDialogCommonLine.png");
    l->setScaleX(height/l->getContentSize().width);
    l->setAnchorPoint(ccp(0.5,0));
    l->setPosition(ccp(0,height/2));
    l->setRotation(90);
    parent->addChild(l);
    
    CCSprite* u = CCSprite::createWithSpriteFrameName("uiDialogCommonLine.png");
    u->setScaleX(width/l->getContentSize().width);
    u->setAnchorPoint(ccp(0.5,0));
    u->setPosition(ccp(width/2,height));
    u->setRotation(180);
    parent->addChild(u);
    
    CCSprite* r = CCSprite::createWithSpriteFrameName("uiDialogCommonLine.png");
    r->setScaleX(height/l->getContentSize().width);
    r->setAnchorPoint(ccp(0.5,0));
    r->setPosition(ccp(width,height/2));
    r->setRotation(270);
    parent->addChild(r);
    
    CCSprite* d = CCSprite::createWithSpriteFrameName("uiDialogCommonLine.png");
    d->setScaleX(width/l->getContentSize().width);
    d->setAnchorPoint(ccp(0.5,0));
    d->setPosition(ccp(width/2,0));
    d->setRotation(0);
    parent->addChild(d);
    
    return parent;
}

CCSprite* MyUtil::getZhijiaoBox(float width, float height) {
    CCSprite* parent = CCSprite::create("transparent.png");
    parent->setContentSize(CCSizeMake(width,height));
    CCSprite* l = CCSprite::createWithSpriteFrameName("uiDialogCommonKuang.png");
    l->setScaleX(height/l->getContentSize().width);
    l->setAnchorPoint(ccp(0.5,1));
    l->setPosition(ccp(0,height/2));
    l->setRotation(270);
    parent->addChild(l);
    
    CCSprite* u = CCSprite::createWithSpriteFrameName("uiDialogCommonKuang.png");
    u->setScaleX(width/l->getContentSize().width);
    u->setAnchorPoint(ccp(0.5,1));
    u->setPosition(ccp(width/2,height));
    u->setRotation(0);
    parent->addChild(u);
    
    CCSprite* r = CCSprite::createWithSpriteFrameName("uiDialogCommonKuang.png");
    r->setScaleX(height/l->getContentSize().width);
    r->setAnchorPoint(ccp(0.5,1));
    r->setPosition(ccp(width,height/2));
    r->setRotation(90);
    parent->addChild(r);
    
    CCSprite* d = CCSprite::createWithSpriteFrameName("uiDialogCommonKuang.png");
    d->setScaleX(width/l->getContentSize().width);
    d->setAnchorPoint(ccp(0.5,1));
    d->setPosition(ccp(width/2,0));
    d->setRotation(180);
    parent->addChild(d);
    
    
    CCSprite* cornerlu = CCSprite::createWithSpriteFrameName("uiDialogZhijiaoCorner.png");
    CCSprite* cornerru = CCSprite::createWithSpriteFrameName("uiDialogZhijiaoCorner.png");
    CCSprite* cornerld = CCSprite::createWithSpriteFrameName("uiDialogZhijiaoCorner.png");
    CCSprite* cornerrd = CCSprite::createWithSpriteFrameName("uiDialogZhijiaoCorner.png");
    cornerlu->setAnchorPoint(ccp(0,0));
    cornerlu->setPosition(ccp(0,height));
    cornerlu->setRotation(90);
    cornerru->setAnchorPoint(ccp(0,0));
    cornerru->setPosition(ccp(width,height));
    cornerru->setRotation(180);
    cornerrd->setAnchorPoint(ccp(0,0));
    cornerrd->setPosition(ccp(width,0));
    cornerrd->setRotation(270);
    cornerld->setAnchorPoint(ccp(0,0));
    cornerld->setPosition(ccp(0,0));
    parent->addChild(cornerlu);
    parent->addChild(cornerru);
    parent->addChild(cornerrd);
    parent->addChild(cornerld);
    
    return parent;
}

CCSprite* MyUtil::getSecondMenuBox(float width, float height,float locx) {
    //0.7647
    
    
    CCSprite* parent = CCSprite::create("transparent.png");
    parent->setContentSize(CCSizeMake(width,height));
    
    CCSprite* back = CCSprite::create("whiteImage.jpg");
    back->setScaleX((width-5)/back->getContentSize().width);
    back->setScaleY((height-5)/back->getContentSize().height);
    back->setPosition(ccp(width/2,height/2));
    back->setColor(ccc3(49,34,21));
    back->setOpacity(150);
    parent->addChild(back);
    
    CCSprite* l = CCSprite::createWithSpriteFrameName("uiDialogCommonKuang.png");
    l->setScaleX((height-30)/l->getContentSize().width);
    l->setScaleY(0.7647);
    l->setAnchorPoint(ccp(0.5,1));
    l->setPosition(ccp(0,height/2));
    l->setRotation(270);
    parent->addChild(l);
    
    CCSprite* u = CCSprite::createWithSpriteFrameName("uiDialogCommonKuang.png");
    u->setScaleX((width-30)/u->getContentSize().width);
    u->setScaleY(0.7647);
    u->setAnchorPoint(ccp(0.5,1));
    u->setPosition(ccp(width/2,height));
    u->setRotation(0);
    parent->addChild(u);
    
    CCSprite* r = CCSprite::createWithSpriteFrameName("uiDialogCommonKuang.png");
    r->setScaleX((height-30)/r->getContentSize().width);
    r->setScaleY(0.7647);
    r->setAnchorPoint(ccp(0.5,1));
    r->setPosition(ccp(width,height/2));
    r->setRotation(90);
    parent->addChild(r);
    
    CCSprite* d = CCSprite::createWithSpriteFrameName("uiDialogCommonKuang.png");
    d->setScaleX((width-30)/d->getContentSize().width);
    d->setScaleY(0.7647);
    d->setAnchorPoint(ccp(0.5,1));
    d->setPosition(ccp(width/2,0));
    d->setRotation(180);
    parent->addChild(d);
    
    
    
    CCSprite* cornerlu = CCSprite::createWithSpriteFrameName("uiDialogMetalCorner.png");
    CCSprite* cornerru = CCSprite::createWithSpriteFrameName("uiDialogNormalCorner.png");
    CCSprite* cornerld = CCSprite::createWithSpriteFrameName("uiDialogNormalCorner.png");
    CCSprite* cornerrd = CCSprite::createWithSpriteFrameName("uiDialogMetalCorner.png");
    cornerlu->setAnchorPoint(ccp(0.1,0.1));
    cornerlu->setPosition(ccp(0,height));
    cornerlu->setScale(0.7647);
    cornerlu->setRotation(90);
    cornerru->setAnchorPoint(ccp(0,0));
    cornerru->setPosition(ccp(width,height));
    cornerru->setRotation(180);
    cornerru->setScale(0.7647);
    cornerrd->setAnchorPoint(ccp(0.1,0.1));
    cornerrd->setPosition(ccp(width,0));
    cornerrd->setRotation(270);
    cornerrd->setScale(0.7647);
    cornerld->setAnchorPoint(ccp(0,0));
    cornerld->setPosition(ccp(0,0));
    cornerld->setScale(0.7647);
    parent->addChild(cornerlu);
    parent->addChild(cornerru);
    parent->addChild(cornerrd);
    parent->addChild(cornerld);
    
    
    CCSprite* tip = CCSprite::createWithSpriteFrameName("uiDialogCommon3.png");
    if (locx == 0) {
        tip->setPosition(ccp(width/2,0));
    } else {
        tip->setPosition(ccp(locx,0));
    }
    
    parent->addChild(tip);
    
    
    
    return parent;
}

CCSprite* MyUtil::getUpdateDialogBack() {
    //67
    CCSprite* parent = CCSprite::create("transparent.png");
    CCSprite* black = CCSprite::create("whiteImage.jpg");
    black->setColor(ccc3(49,34,21));
    black->setScaleX(640/black->getContentSize().width);
    black->setScaleY(450/black->getContentSize().height);
    parent->setContentSize(CCSizeMake(650,460));
    CCSprite* back = CCSprite::createWithSpriteFrameName("uiDialogBack.png");
    black->setPosition(ccp(325,230));
    back->setPosition(ccp(425,220));
    back->setOpacity(250);
    back->setScale(0.8);
    parent->addChild(black);
    parent->addChild(back);
    
    //    CCSprite* white = CCSprite::create("whiteImage.jpg");
    //    white->setOpacity(100);
    //    white->setColor(ccc3(89,64,41));
    //    white->setScaleX(650/black->getContentSize().width);
    //    white->setScaleY(460/black->getContentSize().height);
    //    white->setPosition(ccp(325,230));
    //    parent->addChild(white);
    
    CCSprite* kuangu = CCSprite::createWithSpriteFrameName("uiDialogCommonKuang.png");
    CCSprite* kuangr = CCSprite::createWithSpriteFrameName("uiDialogCommonKuang.png");
    CCSprite* kuangd = CCSprite::createWithSpriteFrameName("uiDialogCommonKuang.png");
    CCSprite* kuangl = CCSprite::createWithSpriteFrameName("uiDialogCommonKuang.png");
    kuangu->setAnchorPoint(ccp(0.5,1));
    kuangu->setPosition(ccp(325,460));
    kuangu->setScaleX(0.9);
    kuangl->setAnchorPoint(ccp(0.5,1));
    kuangl->setRotation(270);
    kuangl->setPosition(ccp(0,230));
    kuangl->setScaleX(0.65);
    kuangr->setAnchorPoint(ccp(0.5,1));
    kuangr->setRotation(90);
    kuangr->setPosition(ccp(650,230));
    kuangr->setScaleX(0.65);
    kuangd->setAnchorPoint(ccp(0.5,1));
    kuangd->setRotation(180);
    kuangd->setPosition(ccp(325,0));
    kuangd->setScaleX(0.9);
    parent->addChild(kuangu);
    parent->addChild(kuangr);
    parent->addChild(kuangl);
    parent->addChild(kuangd);
    
    
    CCSprite* cornerru = CCSprite::createWithSpriteFrameName("uiDialogNormalCorner.png");
    CCSprite* cornerld = CCSprite::createWithSpriteFrameName("uiDialogMetalCorner.png");
    CCSprite* cornerrd = CCSprite::createWithSpriteFrameName("uiDialogNormalCorner.png");
    cornerru->setAnchorPoint(ccp(0,0));
    cornerru->setPosition(ccp(650,460));
    cornerru->setRotation(180);
    cornerrd->setAnchorPoint(ccp(0,0));
    cornerrd->setPosition(ccp(650,0));
    cornerrd->setRotation(270);
    cornerld->setAnchorPoint(ccp(0.1,0.1));
    cornerld->setPosition(ccp(0,0));
    parent->addChild(cornerru);
    parent->addChild(cornerrd);
    parent->addChild(cornerld);
    
    
    CCSprite* up = CCSprite::createWithSpriteFrameName("UIDialogCommon1.png");
    up->setAnchorPoint(ccp(0,0));
    up->setPosition(ccp(0,434));
    parent->addChild(up);
    
    CCSprite* right = CCSprite::createWithSpriteFrameName("uiDialogCommon2.png");
    right->setAnchorPoint(ccp(1,0));
    right->setPosition(ccp(650,0));
    parent->addChild(right);
    
    CCSprite* gear = CCSprite::createWithSpriteFrameName("uiDialogCommonGear.png");
    gear->setAnchorPoint(ccp(0.3,0.5));
    gear->setPosition(ccp(0,440));
    parent->addChild(gear);
    
    return parent;
}

CCSprite* MyUtil::getDialogBackNoGirl() {
    //544 334
    CCSprite* parent = CCSprite::create("transparent.png");
    CCSprite* black = CCSprite::create("whiteImage.jpg");
    black->setColor(ccc3(49,34,21));
    black->setScaleX(590/black->getContentSize().width);
    black->setScaleY(334/black->getContentSize().height);
    parent->setContentSize(CCSizeMake(684,334));
    CCSprite* back = CCSprite::createWithSpriteFrameName("uiDialogBack.png");
    black->setPosition(ccp(388,167));
    back->setPosition(ccp(462,167));
    back->setOpacity(200);
    back->setScale(0.7);
    parent->addChild(black);
    parent->addChild(back);
    
    CCSprite* kuangu = CCSprite::createWithSpriteFrameName("uiDialogCommonKuang.png");
    CCSprite* kuangr = CCSprite::createWithSpriteFrameName("uiDialogCommonKuang.png");
    CCSprite* kuangd = CCSprite::createWithSpriteFrameName("uiDialogCommonKuang.png");
    CCSprite* kuangl = CCSprite::createWithSpriteFrameName("uiDialogCommonKuang.png");
    kuangu->setAnchorPoint(ccp(0.5,1));
    kuangu->setPosition(ccp(437,334));
    kuangu->setScaleX(0.7);
    kuangr->setAnchorPoint(ccp(0.5,1));
    kuangr->setRotation(90);
    kuangr->setPosition(ccp(684,167));
    kuangr->setScaleX(0.45);
    kuangl->setAnchorPoint(ccp(0.5,1));
    kuangl->setRotation(270);
    kuangl->setPosition(ccp(80,167));
    kuangl->setScaleX(0.44);
    kuangd->setAnchorPoint(ccp(0.5,1));
    kuangd->setRotation(180);
    kuangd->setPosition(ccp(392,0));
    kuangd->setScaleX(0.8);
    parent->addChild(kuangu);
    parent->addChild(kuangr);
    parent->addChild(kuangd);
    parent->addChild(kuangl);
    
    CCSprite* cornerru = CCSprite::createWithSpriteFrameName("uiDialogNormalCorner.png");
    CCSprite* cornerld = CCSprite::createWithSpriteFrameName("uiDialogMetalCorner.png");
    cornerru->setAnchorPoint(ccp(0,0));
    cornerru->setPosition(ccp(684,334));
    cornerru->setRotation(180);
    cornerld->setAnchorPoint(ccp(0.1,0.1));
    cornerld->setPosition(ccp(79,0));
    parent->addChild(cornerru);
    parent->addChild(cornerld);
    
    CCSprite* up = CCSprite::createWithSpriteFrameName("UIDialogCommon1.png");
    up->setAnchorPoint(ccp(0,0));
    up->setPosition(ccp(80,308));
    parent->addChild(up);
    
    CCSprite* right = CCSprite::createWithSpriteFrameName("uiDialogCommon2.png");
    right->setAnchorPoint(ccp(1,0));
    right->setPosition(ccp(684,0));
    parent->addChild(right);
    
    return parent;
}

CCSprite* MyUtil::getNormalBox(float width, float height) {
    CCSprite* parent = CCSprite::create("transparent.png");
    CCSprite* black = CCSprite::create("whiteImage.jpg");
    black->setColor(ccc3(49,34,21));
    black->setScaleX((width-13)/black->getContentSize().width);
    black->setScaleY((height-13)/black->getContentSize().height);
    parent->setContentSize(CCSizeMake(width,height));
    
    black->setPosition(ccp(width/2,height/2));
    parent->addChild(black);
    
    
    CCSprite* kuangu = CCSprite::createWithSpriteFrameName("uiDialogCommonKuang.png");
    CCSprite* kuangr = CCSprite::createWithSpriteFrameName("uiDialogCommonKuang.png");
    CCSprite* kuangd = CCSprite::createWithSpriteFrameName("uiDialogCommonKuang.png");
    CCSprite* kuangl = CCSprite::createWithSpriteFrameName("uiDialogCommonKuang.png");
    
    kuangu->setAnchorPoint(ccp(0.5,1));
    kuangu->setPosition(ccp(width/2,height));
    kuangu->setScaleX((width-30)/kuangu->getContentSize().width);
    
    kuangl->setAnchorPoint(ccp(0.5,1));
    kuangl->setRotation(270);
    kuangl->setPosition(ccp(0,height/2));
    kuangl->setScaleX((height-30)/kuangl->getContentSize().width);
    
    kuangr->setAnchorPoint(ccp(0.5,1));
    kuangr->setRotation(90);
    kuangr->setPosition(ccp(width,height/2));
    kuangr->setScaleX((height-30)/kuangl->getContentSize().width);
    kuangd->setAnchorPoint(ccp(0.5,1));
    kuangd->setRotation(180);
    kuangd->setPosition(ccp(width/2,0));
    kuangd->setScaleX((width-30)/kuangu->getContentSize().width);
    parent->addChild(kuangu);
    parent->addChild(kuangr);
    parent->addChild(kuangl);
    parent->addChild(kuangd);
    
    
    CCSprite* cornerru = CCSprite::createWithSpriteFrameName("uiDialogNormalCorner.png");
    CCSprite* cornerld = CCSprite::createWithSpriteFrameName("uiDialogMetalCorner.png");
    CCSprite* cornerrd = CCSprite::createWithSpriteFrameName("uiDialogNormalCorner.png");
    cornerru->setAnchorPoint(ccp(0,0));
    cornerru->setPosition(ccp(width,height));
    cornerru->setRotation(180);
    cornerrd->setAnchorPoint(ccp(0,0));
    cornerrd->setPosition(ccp(width,0));
    cornerrd->setRotation(270);
    cornerld->setAnchorPoint(ccp(0.1,0.1));
    cornerld->setPosition(ccp(0,0));
    parent->addChild(cornerru);
    parent->addChild(cornerrd);
    parent->addChild(cornerld);
    
    CCSprite* up = CCSprite::createWithSpriteFrameName("UIDialogCommon1.png");
    up->setAnchorPoint(ccp(0,0));
    up->setPosition(ccp(0,height-26));
    up->setScaleX(kuangu->getScaleX());
    parent->addChild(up);
    
    //    CCMenuItemSprite* cancelItem =CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("uiDialogCancelButton.png"), CCSprite::createWithSpriteFrameName("uiDialogCancelButtonP.png"),this,menu_selector(MyUtil::dismiss));
    //    cancelItem->setAnchorPoint(ccp(1,1));
    //    cancelItem->setPosition(ccp(width,height));
    //
    //    MyPriorityMenu* menu  = MyPriorityMenu::create(-511,cancelItem,NULL);
    //    menu->setPosition(ccp(0,0));
    //    parent->addChild(menu);
    
    CCSprite* gear = CCSprite::createWithSpriteFrameName("uiDialogCommonGear.png");
    gear->setAnchorPoint(ccp(0.3,0.5));
    gear->setPosition(ccp(0,height-20));
    parent->addChild(gear);
    
    return parent;
}

CCLayer* MyUtil::getUpdateDialog(bool isAction) {
    //    if (this->getChildByTag(updateLayerTag)!=NULL) {
    //        this->removeChildByTag(updateLayerTag, true);
    //    }
    CCLayer* updateLayer = CCLayer::create();
    updateLayer->setTag(updateLayerTag);
    CCSprite* updateback = MyUtil::getInstance()->getUpdateDialogBack();
    updateback->setPosition(ccp(0,10));
    updateLayer->setPosition(ccp(winSize.width/2,-updateback->getContentSize().height/2));
    
    //    updateback->setScaleX(670/updateback->getContentSize().width);
    //    updateback->setScaleY(488/updateback->getContentSize().height);
    CCSprite* blink = CCSprite::createWithSpriteFrameName("creatorLight.png");
    blink->setPosition(ccp(-204,100));
    blink->setScale(0.675);
    //    blink->setColor(ccGRAY);
    blink->setOpacity(177);
    
    GXShieldTouchMenuItem* shield = GXShieldTouchMenuItem::create();
    shield->setContentSize(CCSizeMake(670, 488));
    shield->setAnchorPoint(ccp(0.5,0.5));
    CCMenuItemSprite* returnItem = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("uiDialogCancelButton.png"), CCSprite::createWithSpriteFrameName("uiDialogCancelButtonP.png"), this,menu_selector(MyUtil::dismiss));
    //    CCMenuItemFont::setFontSize(30);
    //    CCMenuItemFont::setFontName("Arial");
    //    CCMenuItemFont* returnItem = CCMenuItemFont::create("返回", this, menu_selector(StartScene::cancelUpdateDialog));
    //    returnItem->setColor(ccc3(114, 66, 45));
    returnItem->setPosition(ccp(301,216));
    MyPriorityMenu* menu = MyPriorityMenu::create(-503,returnItem,shield,NULL);
    menu->setTag(updateMenuTag);
    menu->setPosition(ccp(0,0));
    
    if (isAction) {
        updateLayer->runAction(CCEaseElasticOut::create(CCMoveTo::create(0.35, ccp(winSize.width/2,winSize.height/2)), 1));
    } else {
        updateLayer->setPosition(ccp(winSize.width/2,winSize.height/2));
    }
    
    
    updateLayer->addChild(updateback);
    updateLayer->addChild(blink);
    updateLayer->addChild(menu);
    //    updateLayer->
    //    this->addChild(updateLayer);
    return updateLayer;
}

CCLayer* MyUtil::getInfoDialog() {
    //    if (this->getChildByTag(updateLayerTag)!=NULL) {
    //        this->removeChildByTag(updateLayerTag, true);
    //    }
    CCLayer* infoLayer = CCLayer::create();
    infoLayer->setTag(updateLayerTag);
    CCSprite* infoback = MyUtil::getInstance()->getUpdateDialogBack();
    infoLayer->setPosition(ccp(winSize.width/2,-infoback->getContentSize().height/2));
    
    
    GXShieldTouchMenuItem* shield = GXShieldTouchMenuItem::create();
    shield->setContentSize(CCSizeMake(670, 488));
    shield->setAnchorPoint(ccp(0.5,0.5));
    CCMenuItemSprite* returnItem = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("uiDialogCancelButton.png"), CCSprite::createWithSpriteFrameName("uiDialogCancelButtonP.png"), this,menu_selector(MyUtil::dismiss));
    returnItem->setPosition(ccp(301,206));
    MyPriorityMenu* menu = MyPriorityMenu::create(-503,returnItem,shield,NULL);
    menu->setTag(updateMenuTag);
    menu->setPosition(ccp(0,0));
    
    infoLayer->runAction(CCEaseElasticOut::create(CCMoveTo::create(0.35, ccp(winSize.width/2,winSize.height/2)), 1));
    
    infoLayer->addChild(infoback);
    infoLayer->addChild(menu);
    //    updateLayer->
    return infoLayer;
}

CCSprite* MyUtil::getShopBack() {
    float beilv = winSize.width/960;
    CCSprite* parent = CCSprite::create("transparent.png");
    CCSprite* back = CCSprite::createWithSpriteFrameName("armyback.png");
    back->setScaleX(1.37*beilv);
    back->setScaleY(1.37);
    
    back->setPosition(ccp(winSize.width/2-40*beilv,winSize.height/2+1));
    parent->setContentSize(CCSizeMake(960,640));
    
    parent->addChild(back);
    
    
    CCSprite* up = CCSprite::createWithSpriteFrameName("UIDialogCommon1.png");
    up->setAnchorPoint(ccp(0,1));
    up->setPosition(ccp(-38,winSize.height+7));
    up->setScaleX((winSize.width+50)/up->getContentSize().width);
    up->setScaleY(0.8);
    up->setFlipX(true);
    up->setFlipY(true);
    parent->addChild(up,1);
    
    CCSprite* kuangmid = CCSprite::createWithSpriteFrameName("uiDialogCommonKuang.png");
    kuangmid->setScaleX(winSize.width+50/kuangmid->getContentSize().width);
    kuangmid->setScaleY(0.8);
    kuangmid->setAnchorPoint(ccp(0.5,1));
    kuangmid->setPosition(ccp(winSize.width/2,winSize.height-110));
    parent->addChild(kuangmid,1);
    
    CCSprite*  black = CCSprite::create("whiteImage.jpg");
    black->setColor(ccc3(0,0,0));
    black->setScaleX(winSize.width/black->getContentSize().width);
    black->setScaleY(115/black->getContentSize().height);
    black->setAnchorPoint(ccp(0,1));
    black->setPosition(ccp(0,winSize.height));
    parent->addChild(black);
    
    CCSprite* kuangu = CCSprite::createWithSpriteFrameName("uiDialogCommonKuang.png");
    CCSprite* kuangr = CCSprite::createWithSpriteFrameName("uiDialogCommonKuang.png");
    CCSprite* kuangd = CCSprite::createWithSpriteFrameName("uiDialogCommonKuang.png");
    CCSprite* kuangl = CCSprite::createWithSpriteFrameName("uiDialogCommonKuang.png");
    int width = 900;
    int height = 430;
    
    kuangu->setAnchorPoint(ccp(0.5,1));
    kuangu->setPosition(ccp(winSize.width/2,450));
    kuangu->setScaleX((width-60)/kuangu->getContentSize().width);
    
    kuangl->setAnchorPoint(ccp(0.5,1));
    kuangl->setRotation(270);
    kuangl->setPosition(ccp(winSize.width/2-450,235));
    kuangl->setScaleX((height-60)/kuangl->getContentSize().width);
    
    kuangr->setAnchorPoint(ccp(0.5,1));
    kuangr->setRotation(90);
    kuangr->setPosition(ccp(winSize.width/2+450,235));
    kuangr->setScaleX((height-60)/kuangl->getContentSize().width);
    kuangd->setAnchorPoint(ccp(0.5,1));
    kuangd->setRotation(180);
    kuangd->setPosition(ccp(winSize.width/2,20));
    kuangd->setScaleX((width-60)/kuangu->getContentSize().width);
    parent->addChild(kuangu);
    parent->addChild(kuangr);
    parent->addChild(kuangl);
    parent->addChild(kuangd);
    
    CCSprite* cornerlu = CCSprite::createWithSpriteFrameName("uiDialogNormalCorner.png");
    CCSprite* cornerru = CCSprite::createWithSpriteFrameName("uiDialogNormalCorner.png");
    CCSprite* cornerld = CCSprite::createWithSpriteFrameName("uiDialogMetalCorner.png");
    CCSprite* cornerrd = CCSprite::createWithSpriteFrameName("uiDialogMetalCorner.png");
    cornerlu->setAnchorPoint(ccp(0,0));
    cornerlu->setPosition(ccp(winSize.width/2-450,450));
    cornerlu->setRotation(90);
    cornerru->setAnchorPoint(ccp(0,0));
    cornerru->setPosition(ccp(winSize.width/2+450,450));
    cornerru->setRotation(180);
    cornerrd->setAnchorPoint(ccp(0.1,0.1));
    cornerrd->setPosition(ccp(winSize.width/2+450,20));
    cornerrd->setRotation(270);
    cornerld->setAnchorPoint(ccp(0.1,0.1));
    cornerld->setPosition(ccp(winSize.width/2-450,20));
    parent->addChild(cornerlu);
    parent->addChild(cornerru);
    parent->addChild(cornerrd);
    parent->addChild(cornerld);
    
    CCSprite* avatarBack = CCSprite::createWithSpriteFrameName("shopAvatarBack.png");
    avatarBack->setAnchorPoint(ccp(0,0.5));
    avatarBack->setScaleX(1.3);
    avatarBack->setScaleY(1.1);
    avatarBack->setPosition(ccp(0,winSize.height-65));
    parent->addChild(avatarBack);
    
    CCSprite* diamondBack = CCSprite::createWithSpriteFrameName("shopDiamondBack.png");
    diamondBack->setPosition(ccp(winSize.width-240,winSize.height-70));
    diamondBack->setScale(1.19);
    parent->addChild(diamondBack);
    
    return parent;
}

CCSprite* MyUtil::getChargeBack() {
    CCSprite* parent = CCSprite::create("transparent.png");
    parent->setContentSize(CCSizeMake(900,600));
    
    CCSprite* kuangu = CCSprite::createWithSpriteFrameName("uiDialogCommonKuang.png");
    CCSprite* kuangr = CCSprite::createWithSpriteFrameName("uiDialogCommonKuang.png");
    CCSprite* kuangd = CCSprite::createWithSpriteFrameName("uiDialogCommonKuang.png");
    CCSprite* kuangl = CCSprite::createWithSpriteFrameName("uiDialogCommonKuang.png");
    int width = 900;
    int height = 600;
    
    kuangu->setAnchorPoint(ccp(0.5,1));
    kuangu->setPosition(ccp(width/2,height));
    kuangu->setScaleX((width-50)/kuangu->getContentSize().width);
    
    kuangl->setAnchorPoint(ccp(0.5,1));
    kuangl->setRotation(270);
    kuangl->setPosition(ccp(0,height/2));
    kuangl->setScaleX((height-50)/kuangl->getContentSize().width);
    
    kuangr->setAnchorPoint(ccp(0.5,1));
    kuangr->setRotation(90);
    kuangr->setPosition(ccp(width,height/2));
    kuangr->setScaleX((height-50)/kuangl->getContentSize().width);
    kuangd->setAnchorPoint(ccp(0.5,1));
    kuangd->setRotation(180);
    kuangd->setPosition(ccp(width/2,0));
    kuangd->setScaleX((width-50)/kuangd->getContentSize().width);
    
    parent->addChild(kuangu);
    parent->addChild(kuangr);
    parent->addChild(kuangl);
    parent->addChild(kuangd);
    
    
    CCSprite* cornerld = CCSprite::createWithSpriteFrameName("uiDialogMetalCorner.png");
    CCSprite* cornerrd = CCSprite::createWithSpriteFrameName("uiDialogMetalCorner.png");
    
    
    cornerrd->setAnchorPoint(ccp(0.1,0.1));
    cornerrd->setPosition(ccp(width,0));
    cornerrd->setRotation(270);
    cornerld->setAnchorPoint(ccp(0.1,0.1));
    cornerld->setPosition(ccp(0,0));
    
    parent->addChild(cornerrd);
    parent->addChild(cornerld);
    
    CCSprite* up = CCSprite::createWithSpriteFrameName("UIDialogCommon1.png");
    up->setAnchorPoint(ccp(0,0));
    up->setPosition(ccp(0,574));
    parent->addChild(up);
    
    CCSprite* chargeLabel = CCSprite::createWithSpriteFrameName("shopChargeLabel.png");
    chargeLabel->setPosition(ccp(96,595));
    parent->addChild(chargeLabel);
    
    return parent;
}

CCSprite* MyUtil::getServerRegistBack() {
    CCSprite* parent = CCSprite::create("transparent.png");
    parent->setContentSize(CCSizeMake(810,584));
    
    CCSprite* black = CCSprite::create("whiteImage.jpg");
    black->setColor(ccc3(0,0,0));
    black->setScaleX(800/black->getContentSize().width);
    black->setScaleY(580/black->getContentSize().height);
    black->setAnchorPoint(ccp(0,0));
    black->setPosition(ccp(0,5));
    black->setOpacity(230);
    parent->addChild(black);
    
    CCSprite* kuangr = CCSprite::createWithSpriteFrameName("serverMetalKuang.png");
    CCSprite* kuangd = CCSprite::createWithSpriteFrameName("serverMetalKuang.png");
    CCSprite* kuangl = CCSprite::createWithSpriteFrameName("serverMetalKuang.png");
    int width = 810;
    int height = 584;
    
    
    kuangl->setAnchorPoint(ccp(0.5,1));
    kuangl->setRotation(270);
    kuangl->setPosition(ccp(0,height/2+15));
    kuangl->setScaleX((height-30)/kuangl->getContentSize().width);
    
    kuangr->setAnchorPoint(ccp(0.5,1));
    kuangr->setRotation(90);
    kuangr->setPosition(ccp(width,height/2+15));
    kuangr->setScaleX((height-30)/kuangr->getContentSize().width);
    
    kuangd->setAnchorPoint(ccp(0.5,1));
    kuangd->setRotation(180);
    kuangd->setPosition(ccp(width/2,0));
    kuangd->setScaleX((width-50)/kuangd->getContentSize().width);
    
    parent->addChild(kuangr);
    parent->addChild(kuangl);
    parent->addChild(kuangd);
    
    
    CCSprite* cornerld = CCSprite::createWithSpriteFrameName("serverMetalCorner.png");
    CCSprite* cornerrd = CCSprite::createWithSpriteFrameName("serverMetalCorner.png");
    
    
    cornerrd->setAnchorPoint(ccp(0.9,0.9));
    cornerrd->setPosition(ccp(width,0));
    cornerrd->setRotation(90);
    cornerld->setAnchorPoint(ccp(0.9,0.9));
    cornerld->setPosition(ccp(0,0));
    cornerld->setRotation(180);
    
    parent->addChild(cornerrd);
    parent->addChild(cornerld);
    
    
    
    
    return parent;
}

CCSprite* MyUtil::getServerTipBack(int width,int height) {
    CCSprite* parent = CCSprite::create("transparent.png");
    CCSprite* black = CCSprite::create("whiteImage.jpg");
    black->setColor(ccc3(0,0,0));
    black->setScaleX((width-13)/black->getContentSize().width);
    black->setScaleY((height-13)/black->getContentSize().height);
    parent->setContentSize(CCSizeMake(width,height));
    
    black->setPosition(ccp(width/2,height/2));
    parent->addChild(black);
    
    
    CCSprite* kuangu = CCSprite::createWithSpriteFrameName("serverMetalKuang.png");
    CCSprite* kuangr = CCSprite::createWithSpriteFrameName("serverMetalKuang.png");
    CCSprite* kuangd = CCSprite::createWithSpriteFrameName("serverMetalKuang.png");
    CCSprite* kuangl = CCSprite::createWithSpriteFrameName("serverMetalKuang.png");
    
    kuangu->setAnchorPoint(ccp(0.5,1));
    kuangu->setPosition(ccp(width/2,height));
    kuangu->setScaleX((width-30)/kuangu->getContentSize().width);
    
    kuangl->setAnchorPoint(ccp(0.5,1));
    kuangl->setRotation(270);
    kuangl->setPosition(ccp(0,height/2));
    kuangl->setScaleX((height-30)/kuangl->getContentSize().width);
    
    kuangr->setAnchorPoint(ccp(0.5,1));
    kuangr->setRotation(90);
    kuangr->setPosition(ccp(width,height/2));
    kuangr->setScaleX((height-30)/kuangl->getContentSize().width);
    kuangd->setAnchorPoint(ccp(0.5,1));
    kuangd->setRotation(180);
    kuangd->setPosition(ccp(width/2,0));
    kuangd->setScaleX((width-30)/kuangu->getContentSize().width);
    parent->addChild(kuangu);
    parent->addChild(kuangr);
    parent->addChild(kuangl);
    parent->addChild(kuangd);
    
    CCSprite* cornerlu = CCSprite::createWithSpriteFrameName("serverMetalCorner.png");
    CCSprite* cornerru = CCSprite::createWithSpriteFrameName("serverMetalCorner.png");
    CCSprite* cornerld = CCSprite::createWithSpriteFrameName("serverMetalCorner.png");
    CCSprite* cornerrd = CCSprite::createWithSpriteFrameName("serverMetalCorner.png");
    
    cornerlu->setAnchorPoint(ccp(0.9,0.9));
    cornerlu->setPosition(ccp(0,height));
    cornerlu->setRotation(270);
    cornerru->setAnchorPoint(ccp(0.9,0.9));
    cornerru->setPosition(ccp(width,height));
    
    cornerrd->setAnchorPoint(ccp(0.9,0.9));
    cornerrd->setPosition(ccp(width,0));
    cornerrd->setRotation(90);
    cornerld->setAnchorPoint(ccp(0.9,0.9));
    cornerld->setPosition(ccp(0,0));
    cornerld->setRotation(180);
    
    parent->addChild(cornerlu);
    parent->addChild(cornerru);
    parent->addChild(cornerrd);
    parent->addChild(cornerld);
    
    
    
    
    return parent;
}

CCLayer* MyUtil::getServerTipDialog(const std::string& msg) {
    CCLayer* tipLayer = CCLayer::create();
    CCSprite* black = CCSprite::create("whiteImage.jpg");
    black->setScaleX(winSize.width/black->getContentSize().width);
    black->setScaleY(winSize.height/black->getContentSize().height);
    black->setPosition(ccp(winSize.width/2,winSize.height/2));
    black->setColor(ccc3(0,0,0));
    black->setOpacity(200);
    
    tipLayer->addChild(black);
    CCSprite* back= getServerTipBack(533,300);
    back->setPosition(ccp(winSize.width/2,winSize.height/2));
    tipLayer->addChild(back);
    
    CCSprite* warnIcon = CCSprite::createWithSpriteFrameName("warn.png");
    warnIcon->setScale(1.25);
    warnIcon->setPosition(ccp(winSize.width/2-155,winSize.height/2+40));
    tipLayer->addChild(warnIcon);
    
    CCMenuItemSprite* cancelItem =CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("dialogsure.png"), CCSprite::createWithSpriteFrameName("dialogsurep.png"),this,menu_selector(MyUtil::dismiss));
    
    cancelItem->setPosition(ccp(winSize.width/2,winSize.height/2-80));
    
    GXShieldTouchMenuItem* shieldTouch= GXShieldTouchMenuItem::create();
    shieldTouch->setContentSize(winSize);
    shieldTouch->setPosition(ccp(winSize.width/2,winSize.height/2));
    
    MyPriorityMenu* menu = MyPriorityMenu::create(-504,cancelItem,shieldTouch,NULL);
    menu->setPosition(ccp(0,0));
    tipLayer->addChild(menu);
    
    CCLabelTTF* label = CCLabelTTF::create(msg.c_str(),"Arial",35);
    label->setPosition(ccp(winSize.width/2+60,winSize.height/2+40));
    label->setColor(ccc3(255,222,0));
    tipLayer->addChild(label);
    
    return tipLayer;
}

CCLayer* MyUtil::getServerTipDialog(const std::string& msg,CCObject* obj,SEL_MenuHandler selector) {
    CCLayer* tipLayer = CCLayer::create();
    CCSprite* black = CCSprite::create("whiteImage.jpg");
    black->setScaleX(winSize.width/black->getContentSize().width);
    black->setScaleY(winSize.height/black->getContentSize().height);
    black->setPosition(ccp(winSize.width/2,winSize.height/2));
    black->setColor(ccc3(0,0,0));
    black->setOpacity(200);
    
    tipLayer->addChild(black);
    CCSprite* back= getServerTipBack(533,300);
    back->setPosition(ccp(winSize.width/2,winSize.height/2));
    tipLayer->addChild(back);
    
    CCSprite* warnIcon = CCSprite::createWithSpriteFrameName("warn.png");
    warnIcon->setScale(1.25);
    warnIcon->setPosition(ccp(winSize.width/2-155,winSize.height/2+40));
    tipLayer->addChild(warnIcon);
    
    CCMenuItemSprite* cancelItem =CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("dialogsure.png"), CCSprite::createWithSpriteFrameName("dialogsurep.png"),obj,selector);
    
    cancelItem->setPosition(ccp(winSize.width/2,winSize.height/2-80));
    
    GXShieldTouchMenuItem* shieldTouch= GXShieldTouchMenuItem::create();
    shieldTouch->setContentSize(winSize);
    shieldTouch->setPosition(ccp(winSize.width/2,winSize.height/2));
    
    MyPriorityMenu* menu = MyPriorityMenu::create(-504,cancelItem,shieldTouch,NULL);
    menu->setPosition(ccp(0,0));
    tipLayer->addChild(menu);
    
    CCLabelTTF* label = CCLabelTTF::create(msg.c_str(),"Arial",35);
    label->setPosition(ccp(winSize.width/2+60,winSize.height/2+40));
    label->setColor(ccc3(255,222,0));
    tipLayer->addChild(label);
    
    return tipLayer;
}

CCLayer* MyUtil::getUpdateBar(float per1, float per2,const char* upName) {
    GXProgressBar* barAdd = GXProgressBar::create(CCSprite::create(upName), CCSprite::create("BarDown.png"));
    
    barAdd->setContentSize(CCSizeMake(316,14));
    barAdd->updatePercentage(per1);
    CCTintTo* tintBy = CCTintTo::create(1, 0,255,0);
    //    healthBarAdd->getUpSprite()->setColor(ccGRAY);
    barAdd->getUpSprite()->runAction(CCRepeatForever::create(static_cast<CCSequence*>(CCSequence::create(tintBy,CCTintTo::create(1, 255,255,255),NULL))));
    
    CCSprite* bar = CCSprite::create(upName);
    bar->setScaleX((316*per2)/bar->getContentSize().width);
    bar->setScaleY(14/bar->getContentSize().height);
    
    bar->setAnchorPoint(ccp(0,0));
    bar->setColor(ccc3(220,220,220));
    barAdd->addChild(bar);
    return barAdd;
}

void MyUtil::removeFromParentCallBack(CCMenuItem* item) {
    item->removeFromParentAndCleanup(true);
}

int MyUtil::getVipLevel(int _vipExperience) {
    if (_vipExperience >= 1000) {
        return 6;
    } else if(_vipExperience >=500) {
        return 5;
    } else if(_vipExperience >=100) {
        return 4;
    } else if(_vipExperience >=50) {
        return 3;
    } else if(_vipExperience >=20) {
        return 2;
    } else if(_vipExperience >=5) {
        return 1;
    }
    return 0;
}

CCLabelTTF* MyUtil::getVipColorLabel(const char *string,int size,int vipExperience) {
    CCLabelTTF* label = CCLabelTTF::create(string,"Arial", size);
//    int level = getVipLevel(vipExperience);
//    if (level == 1) {
//        label->setColor(ccc3(255,255,122));
//    } else if(level == 2) {
//        
//    }
    if (vipExperience > 5) {
        label->setColor(ccc3(255,255,122));
    }
    return label;
}

int MyUtil::getVipExperienceByLevel(int vipLevel) {
    if (vipLevel == 6) {
        return 1000;
    } else if(vipLevel == 5) {
        return 500;
    } else if(vipLevel == 4) {
        return 100;
    } else if(vipLevel ==3) {
        return 50;
    } else if(vipLevel ==2) {
        return 20;
    } else if(vipLevel ==1) {
        return 5;
    } else if(vipLevel ==0) {
        return 0;
    }
    return 10000;
}

CCLayer* MyUtil::getVipDesc(int vipLevel,CCObject* rec,SEL_MenuHandler selector) {
    CCLayer* displayLayer = CCLayer::create();
    displayLayer->setTag(NoResourceTag);
    
    CCSprite* di = NULL;
    int height = 500;
    if (vipLevel == 1) {
        di = getNormalBox(550,500);
    } else if(vipLevel == 2 || vipLevel == 3 || vipLevel == 4) {
        di = getNormalBox(550,400);
        height = 400;
    }
    di->setPosition(ccp(winSize.width/2,winSize.height/2));
    CCSprite* vipSprite = CCSprite::createWithSpriteFrameName("shopVIPIcon.png");
    vipSprite->setPosition(ccp(winSize.width/2-25,500));
    vipSprite->setScale(1.2);
    
    char str[200] = {0};
    sprintf(str,"%d",vipLevel);
    CCLabelAtlas* vipLevelLabel = CCLabelAtlas::create(str, "levelupnumber.png", 40, 32, '0');
    vipLevelLabel->setPosition(ccp(winSize.width/2 + 25,480));
    vipLevelLabel->setScaleY(1.2);
    
    displayLayer->addChild(di);
    displayLayer->addChild(vipSprite);
    displayLayer->addChild(vipLevelLabel);
    
    CCSprite* metalButton = CCSprite::createWithSpriteFrameName("metalButton.png");
    CCSprite* startLabel1 = CCSprite::createWithSpriteFrameName("shopChargeLabel.png");
    startLabel1->setColor(ccc3(200,200,200));
    startLabel1->setScaleX(0.7);
    startLabel1->setScaleY(0.875);
    startLabel1->setPosition(ccp(metalButton->getContentSize().width/2,metalButton->getContentSize().height/2));
    metalButton->addChild(startLabel1);
    
    CCSprite* metalButtonP = CCSprite::createWithSpriteFrameName("metalButtonP.png");
    CCSprite* startLabel2 = CCSprite::createWithSpriteFrameName("shopChargeLabel.png");
    startLabel2->setPosition(ccp(metalButtonP->getContentSize().width/2,metalButtonP->getContentSize().height/2));
    startLabel2->setScaleX(0.7);
    startLabel2->setScaleY(0.875);
    metalButtonP->addChild(startLabel2);
    
    CCSprite* bling1_1 = CCSprite::create("armyprizeLight.png");
    bling1_1->setScale(0.7);
    bling1_1->runAction(CCRepeatForever::create(CCRotateBy::create(1000, 7200)));
    
//    CCSprite* bling1_2 = CCSprite::create("armyprizeLight.png");
//    bling1_2->runAction(CCRepeatForever::create(CCRotateBy::create(1000, -7200)));
//    bling1_2->setScale(0.5);
    
    CCMenuItemSprite* chargeItem = CCMenuItemSprite::create(metalButtonP,metalButton,rec,selector);
    chargeItem->setScaleY(0.8);
    if (vipLevel == 1) {
        CCLabelTTF* power1 = CCLabelTTF::create("特权1:一键收矿" , "Arial",30);
        power1->setAnchorPoint(ccp(0,0.5));
        power1->setPosition(ccp(winSize.width/2-235,450));
        power1->setColor(ccc3(230, 207, 185));
        
        CCSprite* icon = CCSprite::createWithSpriteFrameName("vipArcheiveIcon.png");
        icon->setPosition(ccp(winSize.width/2-170,360));
        bling1_1->setPosition(ccp(icon->getContentSize().width/2,icon->getContentSize().height/2));
        icon->addChild(bling1_1,-1);
        
        CCLabelTTF* power1Desc =CCLabelTTF::create("　　『一键收矿』是对全地图所\n有的可收集建筑（如：炼油厂,\n练钢厂）进行收集操作的特权\n功能。","Arial",25,CCSizeZero, kCCTextAlignmentLeft, kCCVerticalTextAlignmentTop);
        power1Desc->setPosition(ccp(winSize.width/2+70,360));
        power1Desc->setColor(ccc3(255,224,122));
        
        CCLabelTTF* power2 = CCLabelTTF::create("特权2:金色昵称", "Arial",30);
        power2->setAnchorPoint(ccp(0,0.5));
        power2->setPosition(ccp(winSize.width/2-235,270));
        power2->setColor(ccc3(230, 207, 185));
//        CCLabelTTF* nickname = getVipColorLabel(MyGameInfo::getInstance()->getNickName(),30,5);
        CCLabelTTF* nickname = CCLabelTTF::create(MyGameInfo::getInstance()->getNickName(),"Arial", 30);
        nickname->setColor(ccc3(255,255,122));
        nickname->setPosition(ccp(winSize.width/2,230));
        CCLabelTTF* power2Desc =CCLabelTTF::create("　　『金色昵称』会显示在己方基地，\n以及战绩和对战的界面中","Arial",25);
        power2Desc->setPosition(ccp(winSize.width/2,180));
        power2Desc->setColor(ccc3(255,224,122));
        
        displayLayer->addChild(power1);
        displayLayer->addChild(icon);
        displayLayer->addChild(power1Desc);
        displayLayer->addChild(power2);
        displayLayer->addChild(nickname);
        displayLayer->addChild(power2Desc);
        
        CCLabelTTF* lastLabel = CCLabelTTF::create("首次充值，送VIP1","Arial",30);
        lastLabel->setColor(ccc3(255,133,80));
        lastLabel->setPosition(ccp(winSize.width/2-40,120));
        displayLayer->addChild(lastLabel);
        
        chargeItem->setPosition(ccp(winSize.width/2+155,120));
        
    } else if(vipLevel == 2) {
        CCLabelTTF* power1 = CCLabelTTF::create("特权:一键升级" , "Arial",30);
        power1->setAnchorPoint(ccp(0,0.5));
        power1->setPosition(ccp(winSize.width/2-235,410));
        power1->setColor(ccc3(230, 207, 185));
        CCSprite* icon = CCSprite::createWithSpriteFrameName("vipUpdateIcon.png");
        icon->setPosition(ccp(winSize.width/2-170,330));
        bling1_1->setPosition(ccp(icon->getContentSize().width/2,icon->getContentSize().height/2));
        icon->addChild(bling1_1,-1);
        
        CCLabelTTF* power1Desc =CCLabelTTF::create("　　『一键升级』是对全地图\n所有建筑进行统一升级操作的\n特权功能。","Arial",25,CCSizeZero, kCCTextAlignmentLeft, kCCVerticalTextAlignmentTop);
        power1Desc->setPosition(ccp(winSize.width/2+70,330));
        power1Desc->setColor(ccc3(255,224,122));
        
        vipSprite->setPosition(ccp(winSize.width/2-25,460));
        vipLevelLabel->setPosition(ccp(winSize.width/2 + 25,440));
        
        displayLayer->addChild(power1);
        displayLayer->addChild(icon);
        displayLayer->addChild(power1Desc);
        
        int chaju = getVipExperienceByLevel(2)-MyGameInfo::getInstance()->getVipExperience();
        sprintf(str,"距离VIP2，需充值%d元",chaju);
        CCLabelTTF* lastLabel = CCLabelTTF::create(str,"Arial",30);
        lastLabel->setColor(ccc3(255,133,80));
        lastLabel->setPosition(ccp(winSize.width/2,235));
        displayLayer->addChild(lastLabel);
        
        chargeItem->setPosition(ccp(winSize.width/2,175));
    }  else if(vipLevel == 3) {
        CCLabelTTF* power1 = CCLabelTTF::create("特权:资源转换" , "Arial",30);
        power1->setAnchorPoint(ccp(0,0.5));
        power1->setPosition(ccp(winSize.width/2-235,410));
        power1->setColor(ccc3(230, 207, 185));
        CCSprite* icon = CCSprite::createWithSpriteFrameName("vipConversion.png");
        icon->setPosition(ccp(winSize.width/2-170,330));
        bling1_1->setPosition(ccp(icon->getContentSize().width/2,icon->getContentSize().height/2));
        icon->addChild(bling1_1,-1);
        
        CCLabelTTF* power1Desc =CCLabelTTF::create("　　『资源转换』是将油铁互\n相转换的特权，但是在过程中\n会有一部分损耗，消耗钻石可\n以消除损耗。","Arial",25,CCSizeZero, kCCTextAlignmentLeft, kCCVerticalTextAlignmentTop);
        power1Desc->setPosition(ccp(winSize.width/2+70,330));
        power1Desc->setColor(ccc3(255,224,122));
        
        vipSprite->setPosition(ccp(winSize.width/2-25,460));
        vipLevelLabel->setPosition(ccp(winSize.width/2 + 25,440));
        
        displayLayer->addChild(power1);
        displayLayer->addChild(icon);
        displayLayer->addChild(power1Desc);
        
        int chaju = getVipExperienceByLevel(3)-MyGameInfo::getInstance()->getVipExperience();
        sprintf(str,"距离VIP3，需充值%d元",chaju);
        CCLabelTTF* lastLabel = CCLabelTTF::create(str,"Arial",30);
        lastLabel->setColor(ccc3(255,133,80));
        lastLabel->setPosition(ccp(winSize.width/2,235));
        displayLayer->addChild(lastLabel);
        
        chargeItem->setPosition(ccp(winSize.width/2,175));
    } else if(vipLevel == 4) {
        CCLabelTTF* power1 = CCLabelTTF::create("特权:极速生产" , "Arial",30);
        power1->setAnchorPoint(ccp(0,0.5));
        power1->setPosition(ccp(winSize.width/2-235,410));
        power1->setColor(ccc3(230, 207, 185));
        CCSprite* icon = CCSprite::createWithSpriteFrameName("vipBoost.png");
        icon->setPosition(ccp(winSize.width/2-170,330));
        bling1_1->setPosition(ccp(icon->getContentSize().width/2,icon->getContentSize().height/2));
        icon->addChild(bling1_1,-1);
        
        CCLabelTTF* power1Desc =CCLabelTTF::create("　　『极速生产』是把全地图\n所有生产建筑（炼油厂等）立\n刻加满的特权，每天可免费使\n用一次。","Arial",25,CCSizeZero, kCCTextAlignmentLeft, kCCVerticalTextAlignmentTop);
        power1Desc->setPosition(ccp(winSize.width/2+70,330));
        power1Desc->setColor(ccc3(255,224,122));
        
        vipSprite->setPosition(ccp(winSize.width/2-25,460));
        vipLevelLabel->setPosition(ccp(winSize.width/2 + 25,440));
        
        displayLayer->addChild(power1);
        displayLayer->addChild(icon);
        displayLayer->addChild(power1Desc);
        
        int chaju = getVipExperienceByLevel(4)-MyGameInfo::getInstance()->getVipExperience();
        sprintf(str,"距离VIP4，需充值%d元",chaju);
        CCLabelTTF* lastLabel = CCLabelTTF::create(str,"Arial",30);
        lastLabel->setColor(ccc3(255,133,80));
        lastLabel->setPosition(ccp(winSize.width/2,235));
        displayLayer->addChild(lastLabel);
        
        chargeItem->setPosition(ccp(winSize.width/2,175));
    }
    
    CCMenuItemSprite* cancelItem =CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("uiDialogCancelButton.png"), CCSprite::createWithSpriteFrameName("uiDialogCancelButtonP.png"),this,menu_selector(MyUtil::dismiss));
    cancelItem->setAnchorPoint(ccp(1,1));
    cancelItem->setPosition(ccp(winSize.width/2+275,winSize.height/2+height/2));
    MyPriorityMenu* menu = MyPriorityMenu::create(-508,cancelItem,chargeItem,NULL);
    menu->setPosition(ccp(0,0));
    displayLayer->addChild(menu);
    
//    sprintf(str,"首次充值，送VIP1");
    
    return displayLayer;
}

CCLayer* MyUtil::getGarbageCollectionTotal(int resourceCount,int mubeiCount,float rate) {
    CCLayer* displayLayer = CCLayer::create();
    displayLayer->setTag(NoResourceTag);
    CCSprite* di = getNormalBox(580,410);
    di->setPosition(ccp(winSize.width/2,winSize.height/2));
    char str[300] = {0};
    
    sprintf(str,"本次共回收了%d座墓碑",mubeiCount);
    CCLabelTTF* title = CCLabelTTF::create(str,"Arial",30);
    title->setColor(ccc3(255,133,80));
    
    CCSprite* ghostSprite = CCSprite::createWithSpriteFrameName("ghost.png");
    ghostSprite->setScale(0.7);
    
    displayLayer->addChild(di);
    displayLayer->addChild(title);
    displayLayer->addChild(ghostSprite);
    
    float gloryCount = ((float)resourceCount)/20000.0 + mubeiCount;
    //    if (gloryCount>0) {
    title->setPosition(ccp(winSize.width/2-25,470));
    ghostSprite->setPosition(ccp(winSize.width/2+title->getContentSize().width/2,472));
    
    sprintf(str,"一共获得%d功勋",(int)gloryCount);
    
    CCLabelTTF* gloryLabel = CCLabelTTF::create(str,"Arial",30);
    gloryLabel->setAnchorPoint(ccp(0,0.5));
    gloryLabel->setPosition(ccp(winSize.width/2-title->getContentSize().width/2-25,430));
    gloryLabel->setColor(ccc3(255,224,122));
    
    
    CCSprite* glorySprite = getResourceIcon(gloryTag);
    glorySprite->setPosition(ccp(winSize.width/2-title->getContentSize().width/2+gloryLabel->getContentSize().width,426));
    glorySprite->setScale(0.8);
    
    displayLayer->addChild(gloryLabel);
    displayLayer->addChild(glorySprite);
    
    //    }
    //    else {
    //        title->setPosition(ccp(winSize.width/2-25,450));
    //        ghostSprite->setPosition(ccp(winSize.width/2+title->getContentSize().width/2,450));
    //    }
    
    
    CCSprite* line = CCSprite::create("whiteImage.jpg");
    line->setScaleX(520/line->getContentSize().width);
    line->setScaleY(3/line->getContentSize().height);
    line->setPosition(ccp(winSize.width/2,400));
    line->setColor(ccc3(255,224,122));
    
    
    CCLabelTTF* recyclinglabel = CCLabelTTF::create("回收中心回收以下资源","Arial",30);
    recyclinglabel->setPosition(ccp(winSize.width/2+100,365));
    recyclinglabel->setColor(ccc3(255,224,122));
    
    CCSprite* recyclingSprite = CCSprite::createWithSpriteFrameName("Recycling.png");
    recyclingSprite->setPosition(ccp(winSize.width/2-150,260));
    
    sprintf(str,"%d",(int)(resourceCount*rate));
    
    CCSprite* oilIcon = getResourceIcon(oilTag);
    oilIcon->setPosition(ccp(winSize.width/2,310));
    oilIcon->setScale(0.9);
    
    CCLabelAtlas* oilCount = CCLabelAtlas::create(str, "number7.png", 24, 36, '/');
    oilCount->setAnchorPoint(ccp(0,0.5));
    oilCount->setPosition(ccp(winSize.width/2+40,310));
    
    CCSprite* expIcon = getResourceIcon(expTag);
    expIcon->setPosition(ccp(winSize.width/2,250));
    
    CCLabelAtlas* expCount = CCLabelAtlas::create(str, "number7.png", 24, 36, '/');
    expCount->setAnchorPoint(ccp(0,0.5));
    expCount->setPosition(ccp(winSize.width/2+40,250));
    
    sprintf(str,"回收率:%%%d",(int)(rate*100+0.5));
    CCLabelTTF* recyclingRate =  CCLabelTTF::create(str,"Arial",30);
    recyclingRate->setAnchorPoint(ccp(0,0.5));
    recyclingRate->setColor(ccc3(255,224,122));
    recyclingRate->setPosition(ccp(winSize.width/2-13,190));
    
    displayLayer->addChild(line);
    displayLayer->addChild(recyclinglabel);
    displayLayer->addChild(recyclingSprite);
    displayLayer->addChild(oilIcon);
    displayLayer->addChild(oilCount);
    displayLayer->addChild(expIcon);
    displayLayer->addChild(expCount);
    displayLayer->addChild(recyclingRate);
    
    CCMenuItemSprite* cancelItem =CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("uiDialogCancelButton.png"), CCSprite::createWithSpriteFrameName("uiDialogCancelButtonP.png"),this,menu_selector(MyUtil::dismiss));
    cancelItem->setAnchorPoint(ccp(1,1));
    cancelItem->setPosition(ccp(winSize.width/2+290,winSize.height/2+205));
    MyPriorityMenu* menu = MyPriorityMenu::create(-508,cancelItem,NULL);
    menu->setPosition(ccp(0,0));
    displayLayer->addChild(menu);
    
    
    
    //
    //    sprintf(str,"距离VIP1还剩下 %d 的经验",getVipExperienceByLevel(1)-MyGameInfo::getInstance()->getVipExperience());
    //    CCLabelTTF* lastLabel = CCLabelTTF::create(str,"Arial",30);
    //    lastLabel->setColor(ccc3(255,133,80));
    //    lastLabel->setPosition(ccp(winSize.width/2,115));
    //    displayLayer->addChild(lastLabel);
    return displayLayer;
}

CCLayer*  MyUtil::getBuildingUnlockLayer(const char* name,int unlockLevel) {
    
    
    CCMenuItemSprite* cancelItem =CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("uiDialogCancelButton.png"), CCSprite::createWithSpriteFrameName("uiDialogCancelButtonP.png"),this,menu_selector(StartScene::cancelTipDialog));
    
    CCMenuItemSprite* sureItem = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("dialogkonw.png"), CCSprite::createWithSpriteFrameName("dialogknowp.png"),this,menu_selector(StartScene::cancelTipDialog));
    sureItem->setPosition(ccp(120,-52));
    
    
    GXShieldTouchMenuItem* shild = GXShieldTouchMenuItem::create();
    shild->setContentSize(winSize);
    shild->setPosition(ccp(-winSize.width/2,-winSize.height/2));
    shild->setAnchorPoint(ccp(0,0));
    
    MyPriorityMenu* menu  = MyPriorityMenu::create(-511,cancelItem,sureItem,shild,NULL);
    
    
    menu->setPosition(ccp(winSize.width/2, winSize.height/2 -48));
    CCLayer* layer = CCLayer::create();
    //    layer->setTouchEnabled(true);
    char str[70] = {0};
    
    sprintf(str,"%s",name);
    CCLabelTTF* label1 = CCLabelTTF::create("解锁：", "宋体", 25,CCSizeZero, kCCTextAlignmentLeft, kCCVerticalTextAlignmentTop);
    
    label1->setColor(ccc3(230, 207, 185));
    label1->setPosition(ccp(winSize.width/2+15,winSize.height/2+80));
    
    CCLabelTTF* label2 = CCLabelTTF::create(str, "Arial", 30,CCSizeZero, kCCTextAlignmentLeft, kCCVerticalTextAlignmentTop);
    
    label2->setColor(ccc3(249, 155, 6));
    label2->setPosition(ccp(winSize.width/2+120,winSize.height/2+40));
    
    CCSprite* dialogBack = MyUtil::getInstance()->getDialogBack();;
    dialogBack->setPosition(ccp(winSize.width/2,winSize.height/2));
    cancelItem->setPosition(ccp(dialogBack->getContentSize().width/2 - 24,dialogBack->getContentSize().height/2 + 24));
    
    CCLabelTTF* needTipLabel = CCLabelTTF::create("需要               才能解锁", "宋体", 25);
    needTipLabel->setColor(ccc3(230, 207, 185));
    needTipLabel->setPosition(ccp(winSize.width/2+120,winSize.height/2-20));
    
    CCSprite* costIcon = CCSprite::createWithSpriteFrameName("levelIcon.png");
    costIcon->setPosition(ccp(winSize.width/2+80,winSize.height/2-20));
    costIcon->setScale(0.6);
    sprintf(str,"%d",unlockLevel);
    
    CCLabelAtlas* atlas = CCLabelAtlas::create(str, "number5.png", 16, 22, '.');
    atlas->setAnchorPoint(ccp(0.5,0.5));
    atlas->setPosition(ccp(winSize.width/2+120,winSize.height/2-20));
    
    
    layer->addChild(dialogBack);
    layer->addChild(label1);
    layer->addChild(label2);
    //    layer->setTag(armyInfoUnlockLayerTag);
    layer->addChild(costIcon);
    layer->addChild(needTipLabel);
    layer->addChild(atlas);
    layer->addChild(menu);
    //    this->addChild(layer);
    return layer;
}

void MyUtil::addloadSpeakerLayer(CCNode* parent,CCString* content) {
    if (loudSpeakerList == NULL) {
        loudSpeakerList = GXListView::create(-500);
        loudSpeakerList->setEnabled(false);
        loudSpeakerList->setOriPosition(ccp(winSize.width/2-295,500));
        loudSpeakerList->setContentSize(CCSizeMake(590, 100));
        loudSpeakerList->retain();
    }
    if (loudSpeakerList->getParent() !=  parent) {
        loudSpeakerList->removeFromParentAndCleanup(true);
        loudSpeakerList->removeAllChildrenWithCleanup(true);
        parent->addChild(loudSpeakerList,50);
    }
    CCLabelTTF* msgLabel = CCLabelTTF::create(content->getCString(), "Arial",  18,CCSizeZero, kCCTextAlignmentLeft, kCCVerticalTextAlignmentTop);
    CCSprite* black = CCSprite::create("whiteImage.jpg");
    black->setColor(ccc3(0,0,0));
    black->setOpacity(100);
    black->setScaleX(590/black->getContentSize().width);
    black->setScaleY((msgLabel->getContentSize().height+10)/black->getContentSize().height);
    black->setPosition(ccp(290,msgLabel->getContentSize().height/2));
    msgLabel->addChild(black,-1);
    loudSpeakerList->addChild(msgLabel);
    msgLabel->setColor(ccc3(255,255,0));
    msgLabel->setOpacity(0);
    msgLabel->runAction(CCSequence::create(CCDelayTime::create(0.35),CCFadeIn::create(0.25),CCDelayTime::create(5),CCFadeOut::create(1),GXRemoveFromParentsAction::create(),NULL));
    //    scroll->setTag(charScorllTag);
    
}

CCLayer* MyUtil::getQuestBack(CCObject* baseQuest,CCObject* rec,SEL_MenuHandler selector,bool isCancel) {
    MyBaseQuest* quest = (MyBaseQuest*)baseQuest;
    float width = 630;
    float height = 410;
    CCLayer* layer = CCLayer::create();
    CCSprite* parent = CCSprite::create("transparent.png");
    CCSprite* black = CCSprite::create("whiteImage.jpg");
    black->setColor(ccc3(49,34,21));
    black->setScaleX((width-13)/black->getContentSize().width);
    black->setScaleY((height-13)/black->getContentSize().height);
    parent->setContentSize(CCSizeMake(width,height));
    
    black->setPosition(ccp(width/2,height/2));
    parent->addChild(black);
    
    
    CCSprite* kuangu = CCSprite::createWithSpriteFrameName("uiDialogCommonKuang.png");
    CCSprite* kuangr = CCSprite::createWithSpriteFrameName("uiDialogCommonKuang.png");
    CCSprite* kuangd = CCSprite::createWithSpriteFrameName("uiDialogCommonKuang.png");
    CCSprite* kuangl = CCSprite::createWithSpriteFrameName("uiDialogCommonKuang.png");
    
    kuangu->setAnchorPoint(ccp(0.5,1));
    kuangu->setPosition(ccp(width/2,height));
    kuangu->setScaleX((width-30)/kuangu->getContentSize().width);
    kuangu->setScaleY(0.8);
    
    kuangl->setAnchorPoint(ccp(0.5,1));
    kuangl->setRotation(270);
    kuangl->setPosition(ccp(0,height/2));
    kuangl->setScaleX((height-30)/kuangl->getContentSize().width);
    kuangl->setScaleY(0.8);
    
    kuangr->setAnchorPoint(ccp(0.5,1));
    kuangr->setRotation(90);
    kuangr->setPosition(ccp(width,height/2));
    kuangr->setScaleX((height-30)/kuangl->getContentSize().width);
    kuangr->setScaleY(0.8);
    
    kuangd->setAnchorPoint(ccp(0.5,1));
    kuangd->setRotation(180);
    kuangd->setPosition(ccp(width/2,0));
    kuangd->setScaleX((width-30)/kuangu->getContentSize().width);
    kuangd->setScaleY(0.8);
    
    parent->addChild(kuangu);
    parent->addChild(kuangr);
    parent->addChild(kuangl);
    parent->addChild(kuangd);
    
    
    
    CCSprite* cornerld = CCSprite::createWithSpriteFrameName("uiDialogMetalCorner.png");
    CCSprite* cornerrd = CCSprite::createWithSpriteFrameName("uiDialogMetalCorner.png");
    CCSprite* cornerlu = CCSprite::createWithSpriteFrameName("uiDialogMetalCorner.png");
    CCSprite* cornerru =NULL;
    
    cornerlu->setAnchorPoint(ccp(0.1,0.1));
    cornerlu->setPosition(ccp(0,height));
    cornerlu->setRotation(90);
    cornerlu->setScale(0.9);
    if (isCancel) {
        cornerru = CCSprite::createWithSpriteFrameName("uiDialogNormalCorner.png");
        cornerru->setAnchorPoint(ccp(0,0));
        cornerru->setPosition(ccp(width,height));
        cornerru->setRotation(180);
        cornerru->setScale(0.9);
    } else {
        cornerru = CCSprite::createWithSpriteFrameName("uiDialogMetalCorner.png");
        cornerru->setAnchorPoint(ccp(0.1,0.1));
        cornerru->setPosition(ccp(width,height));
        cornerru->setRotation(180);
        cornerru->setScale(0.9);
    }
    
    
    
    cornerrd->setAnchorPoint(ccp(0.1,0.1));
    cornerrd->setPosition(ccp(width,0));
    cornerrd->setRotation(270);
    cornerrd->setScale(0.9);
    
    cornerld->setAnchorPoint(ccp(0.1,0.1));
    cornerld->setPosition(ccp(0,0));
    cornerld->setScale(0.9);
    
    parent->addChild(cornerlu);
    parent->addChild(cornerru);
    parent->addChild(cornerrd);
    parent->addChild(cornerld);
    
    CCSprite* upsprite =NULL;
    if (quest->getCompleteStatus() == questFinishedTag) {
        upsprite= CCSprite::createWithSpriteFrameName("getPrizeButton.png");
        CCSprite* fxSptite = CCSprite::createWithSpriteFrameName("getPrizeButtonP.png");
        fxSptite->runAction(CCRepeatForever::create(static_cast<CCSequence*>(CCSequence::create(CCFadeIn::create(1),CCFadeOut::create(1),NULL))));
        fxSptite->setPosition(ccp(upsprite->getContentSize().width/2,upsprite->getContentSize().height/2));
        upsprite->addChild(fxSptite);
    } else {
        upsprite= CCSprite::createWithSpriteFrameName("getPrizeButton.png");
        upsprite->setColor(ccc3(100,100,100));
    }
    
    CCMenuItemSprite* archeivePrizeItem =CCMenuItemSprite::create(upsprite, CCSprite::createWithSpriteFrameName("getPrizeButtonP.png"),rec,selector);
    if (quest->getCompleteStatus() != questFinishedTag) {
        archeivePrizeItem->setEnabled(false);
    }
    
    
    archeivePrizeItem->setPosition(ccp(width-20,20));
    archeivePrizeItem->setAnchorPoint(ccp(1,0));
    archeivePrizeItem->setUserData(baseQuest);
    
    MyPriorityMenu* menu  = MyPriorityMenu::create(-508,archeivePrizeItem,NULL);
    menu->setPosition(ccp(0,0));
    if (isCancel) {
        CCMenuItemSprite* cancelItem = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("uiDialogCancelButton.png"), CCSprite::createWithSpriteFrameName("uiDialogCancelButtonP.png"),this,menu_selector(MyUtil::dismiss));
        cancelItem->setAnchorPoint(ccp(1,1));
        cancelItem->setPosition(ccp(width,height));
        cancelItem->setScale(0.9);
        menu->addChild(cancelItem);
    }
    
    CCSprite* title = CCSprite::createWithSpriteFrameName("qusetTitle.png");
    title->setPosition(ccp(width/2,height-8));
    
    CCSprite* dividingLine = CCSprite::createWithSpriteFrameName("uiDialogCommonLine.png");
    dividingLine->setScaleX((height-30)/dividingLine->getContentSize().width);
    dividingLine->setScaleY(2);
    dividingLine->setAnchorPoint(ccp(1,0.5));
    dividingLine->setPosition(ccp(390,10));
    dividingLine->setRotation(90);
    
    CCSprite* dividingLine1 = CCSprite::createWithSpriteFrameName("uiDialogCommonLine.png");
    dividingLine1->setScaleX(375/dividingLine->getContentSize().width);
    dividingLine1->setScaleY(2);
    dividingLine1->setAnchorPoint(ccp(0,0.5));
    dividingLine1->setPosition(ccp(10,70));
    
    CCSprite* dividingLine2 = CCSprite::createWithSpriteFrameName("uiDialogCommonLine.png");
    dividingLine2->setScaleX(130/dividingLine->getContentSize().width);
    dividingLine2->setScaleY(0.9);
    dividingLine2->setAnchorPoint(ccp(0.5,0.5));
    dividingLine2->setPosition(ccp(385+(width-385)/2,340));
    
    CCLabelTTF* prizeLabel = CCLabelTTF::create("任务奖励","Arial",25);
    prizeLabel->setPosition(ccp(385+(width-385)/2,360));
    prizeLabel->setColor(ccc3(255,120,0));
    
    CCLabelTTF* titleLabel = quest->getTitle();
    titleLabel->setPosition(ccp(width/2,height-5));
    titleLabel->setColor(ccc3(255,222,0));
    
    layer->addChild(parent);
    parent->addChild(dividingLine);
    parent->addChild(dividingLine1);
    parent->addChild(dividingLine2);
    parent->addChild(prizeLabel);
    parent->addChild(title);
    parent->addChild(titleLabel);
    parent->addChild(menu);
    parent->addChild(quest->getDescLayer());
//    parent->addChild(quest->getSchedule());
    parent->addChild(quest->getPrizeInfo());
    
    
    
    
    return layer;
}

const char* MyUtil::getCountStrByCount(int count) {
    if (count < 0) {
        return "不明";
    } else if (count < 10) {
        return "几个";
    } else if(count < 20) {
        return "少量";
    } else if(count<50) {
        return "一群";
    } else if(count<100) {
        return "大量";
    } else if(count<250) {
        return "众多";
    } else if(count <500) {
        return "蜂拥";
    }  else if(count <1000) {
        return "海量";
    } else {
        return "无数";
    }
}

CCLayer* MyUtil::getTitleBack(int width,int height,bool isCancel,const char* titleStr) {
    
    CCLayer* layer = CCLayer::create();
    CCSprite* parent = CCSprite::create("transparent.png");
    CCSprite* black = CCSprite::create("whiteImage.jpg");
    black->setColor(ccc3(49,34,21));
    black->setScaleX((width-13)/black->getContentSize().width);
    black->setScaleY((height-13)/black->getContentSize().height);
    parent->setContentSize(CCSizeMake(width,height));
    
    black->setPosition(ccp(width/2,height/2));
    parent->addChild(black);
    
    
    CCSprite* kuangu = CCSprite::createWithSpriteFrameName("uiDialogCommonKuang.png");
    CCSprite* kuangr = CCSprite::createWithSpriteFrameName("uiDialogCommonKuang.png");
    CCSprite* kuangd = CCSprite::createWithSpriteFrameName("uiDialogCommonKuang.png");
    CCSprite* kuangl = CCSprite::createWithSpriteFrameName("uiDialogCommonKuang.png");
    
    kuangu->setAnchorPoint(ccp(0.5,1));
    kuangu->setPosition(ccp(width/2,height));
    kuangu->setScaleX((width-30)/kuangu->getContentSize().width);
    kuangu->setScaleY(0.8);
    
    kuangl->setAnchorPoint(ccp(0.5,1));
    kuangl->setRotation(270);
    kuangl->setPosition(ccp(0,height/2));
    kuangl->setScaleX((height-30)/kuangl->getContentSize().width);
    kuangl->setScaleY(0.8);
    
    kuangr->setAnchorPoint(ccp(0.5,1));
    kuangr->setRotation(90);
    kuangr->setPosition(ccp(width,height/2));
    kuangr->setScaleX((height-30)/kuangl->getContentSize().width);
    kuangr->setScaleY(0.8);
    
    kuangd->setAnchorPoint(ccp(0.5,1));
    kuangd->setRotation(180);
    kuangd->setPosition(ccp(width/2,0));
    kuangd->setScaleX((width-30)/kuangu->getContentSize().width);
    kuangd->setScaleY(0.8);
    
    parent->addChild(kuangu);
    parent->addChild(kuangr);
    parent->addChild(kuangl);
    parent->addChild(kuangd);
    
    
    
    CCSprite* cornerld = CCSprite::createWithSpriteFrameName("uiDialogMetalCorner.png");
    CCSprite* cornerrd = CCSprite::createWithSpriteFrameName("uiDialogMetalCorner.png");
    CCSprite* cornerlu = CCSprite::createWithSpriteFrameName("uiDialogMetalCorner.png");
    CCSprite* cornerru =NULL;
    
    cornerlu->setAnchorPoint(ccp(0.1,0.1));
    cornerlu->setPosition(ccp(0,height));
    cornerlu->setRotation(90);
    cornerlu->setScale(0.9);
    if (isCancel) {
        cornerru = CCSprite::createWithSpriteFrameName("uiDialogNormalCorner.png");
        cornerru->setAnchorPoint(ccp(0,0));
        cornerru->setPosition(ccp(width,height));
        cornerru->setRotation(180);
        cornerru->setScale(0.9);
    } else {
        cornerru = CCSprite::createWithSpriteFrameName("uiDialogMetalCorner.png");
        cornerru->setAnchorPoint(ccp(0.1,0.1));
        cornerru->setPosition(ccp(width,height));
        cornerru->setRotation(180);
        cornerru->setScale(0.9);
    }
    
    
    
    cornerrd->setAnchorPoint(ccp(0.1,0.1));
    cornerrd->setPosition(ccp(width,0));
    cornerrd->setRotation(270);
    cornerrd->setScale(0.9);
    
    cornerld->setAnchorPoint(ccp(0.1,0.1));
    cornerld->setPosition(ccp(0,0));
    cornerld->setScale(0.9);
    
    parent->addChild(cornerlu);
    parent->addChild(cornerru);
    parent->addChild(cornerrd);
    parent->addChild(cornerld);
    
    
    CCSprite* title = CCSprite::createWithSpriteFrameName("qusetTitle.png");
    title->setPosition(ccp(width/2,height-8));
    
    
    CCLabelTTF* titleLabel = CCLabelTTF::create(titleStr,"Arial",35);
    titleLabel->setPosition(ccp(width/2,height-5));
    titleLabel->setColor(ccc3(255,222,0));
    
    layer->addChild(parent);
    parent->addChild(title);
    parent->addChild(titleLabel);
   
    
    
    
    
    return layer;
}