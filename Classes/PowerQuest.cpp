//
//  PowerQuest.cpp
//  ww4
//
//  Created by xiao tang on 13-6-8.
//
//

#include "PowerQuest.h"
#include "MyMessageManage.h"
#include "MyGameInfo.h"
#include "MyUtil.h"
#include "DefineSet.h"
#include "Mathlib.h"
#include "GXAntiCrack.h"
#include "MyHttpConnection.h"

PowerQuest* PowerQuest::create() {
    PowerQuest* task = new PowerQuest();
    task->autorelease();
    //    task->power = _power;
    task->questTag = powerQuestTag;
    //    task->setIconName(CCString::create("questEveryDay.png"));
    return task;
}

bool PowerQuest::excuteMsg(MyBaseMessage* msg) {
 
    return MyBaseQuest::excuteMsg(msg);
}

int PowerQuest::getCompleteStatus() {
    
    for (int i=0; i<costResourceTagList->count(); i++) {
        int costTag = ((GXintValue*)costResourceTagList->objectAtIndex(i))->getValue();
        int costCount = ((GXintValue*)costResourceCountList->objectAtIndex(i))->getValue();
        if (MyGameInfo::getInstance()->getResource(costTag) < costCount ) {
            return false;
        }
    }
    if (deadLine > 0) {
        struct cc_timeval now;
        CCTime::gettimeofdayCocos2d(&now, NULL);
        if (now.tv_sec > deadLine/1000 ) {
            return false;
        }
    }
    return true;
}

void PowerQuest::getPrize() {
    for (int i=0; i<costResourceTagList->count(); i++) {
        int costTag = ((GXintValue*)costResourceTagList->objectAtIndex(i))->getValue();
        int costCount = ((GXintValue*)costResourceCountList->objectAtIndex(i))->getValue();
        
        MyGameInfo::getInstance()->changeResource(costTag,-1*costCount);
    }
    
    MyGameInfo::getInstance()->setPower(MyGameInfo::getInstance()->getPower()+prizePower->getValue());
    
}

CCLayer* PowerQuest::getDescLayer()  {
    CCLayer* layer = CCLayer::create();
    CCLabelTTF* descTitle = CCLabelTTF::create("任务简报：","Arial",25);
    descTitle->setAnchorPoint(ccp(0,0.5));
    descTitle->setPosition(ccp(25,360));
    descTitle->setColor(ccc3(255,120,0));
    
    CCLabelTTF* desc = CCLabelTTF::create(GXUtil::insertNewline(getDescStr()->getCString(),15).c_str(),"Arial",23,CCSizeZero, kCCTextAlignmentLeft, kCCVerticalTextAlignmentTop);
    desc->setAnchorPoint(ccp(0,1));
    desc->setPosition(ccp(25,340));
    desc->setColor(ccc3(230, 207, 185));
    
    CCLabelTTF* destTitle = CCLabelTTF::create("任务目标：","Arial",25);
    destTitle->setAnchorPoint(ccp(0,1));
    destTitle->setPosition(ccp(25,337-desc->getContentSize().height));
    destTitle->setColor(ccc3(255,120,0));
    char str[100] = {0};
    int i=0;
    for (i=0; i<costResourceTagList->count(); i++) {
        int costTag = ((GXintValue*)costResourceTagList->objectAtIndex(i))->getValue();
        int costCount = ((GXintValue*)costResourceCountList->objectAtIndex(i))->getValue();
        
        CCSprite* tixing;
        if (MyGameInfo::getInstance()->getResource(costTag) >= costCount ) {
            sprintf(str,"　　[已完成]　需消耗%d",costCount);
            tixing = CCSprite::createWithSpriteFrameName("questAppear.png");
            tixing->setScale(0.45);
            tixing->setPosition(ccp(55,293-desc->getContentSize().height-i*32));
            tixing->runAction(CCRepeatForever::create(static_cast<CCSequence*>(CCSequence::create(CCScaleTo::create(1, 0.5), CCScaleTo::create(1,0.45),NULL) )));
        } else {
            sprintf(str,"　　[未完成]　需消耗%d",costCount);
            tixing = CCSprite::createWithSpriteFrameName("questQuestion.png");
            tixing->setScale(0.45);
            tixing->setPosition(ccp(55,293-desc->getContentSize().height-i*32));
        }
        
        
        CCLabelTTF* dest = CCLabelTTF::create(str,"Arial",23);
        dest->setAnchorPoint(ccp(0,1));
        dest->setPosition(ccp(25,305-desc->getContentSize().height-i*32));
        dest->setColor(ccc3(230, 207, 185));
        
        CCSprite* icon = MyUtil::getInstance()->getResourceIcon(costTag);
        icon->setScale(Mathlib::min(32/icon->getContentSize().width,32/icon->getContentSize().height));
        icon->setPosition(ccp(35+dest->getContentSize().width,293-desc->getContentSize().height-i*32));
        
        
        
        layer->addChild(dest);
        layer->addChild(icon);
        layer->addChild(tixing);
        
        
    }
    
    if(deadLine > 0) {
        struct cc_timeval now;
        CCTime::gettimeofdayCocos2d(&now, NULL);
        
        CCSprite* tixing1;
        if (now.tv_sec <= deadLine/1000 ) {
            sprintf(str,"　　需在『%s』之前完成",getdeadLineLabel()->getCString());
            tixing1 = CCSprite::createWithSpriteFrameName("questAppear.png");
            tixing1->setScale(0.45);
            tixing1->setPosition(ccp(55,293-desc->getContentSize().height-i*32));
            tixing1->runAction(CCRepeatForever::create(static_cast<CCSequence*>(CCSequence::create(CCScaleTo::create(1, 0.5), CCScaleTo::create(1,0.45),NULL) )));
        } else {
            sprintf(str,"　　已经超过『%s』,无法完成",getdeadLineLabel()->getCString());
            tixing1 = CCSprite::createWithSpriteFrameName("questQuestion.png");
            tixing1->setScale(0.45);
            tixing1->setPosition(ccp(55,293-desc->getContentSize().height-i*32));
        }
        
        
        CCLabelTTF* dest1 = CCLabelTTF::create(str,"Arial",23);
        dest1->setAnchorPoint(ccp(0,1));
        dest1->setPosition(ccp(25,305-desc->getContentSize().height-i*32));
        dest1->setColor(ccc3(230, 207, 185));
        
        layer->addChild(dest1);
        layer->addChild(tixing1);
    }
    
    
    layer->addChild(descTitle);
    layer->addChild(desc);
    layer->addChild(destTitle);

    return layer;
}


CCLayer* PowerQuest::getPrizeInfo() {
    CCLayer* prizeLayer = CCLayer::create();
        
    
    
//    CCSprite* icon1 = MyUtil::getInstance()->getResourceIcon(prizeTag);
//    icon1->setScale(Mathlib::min(40/icon1->getContentSize().width,40/icon1->getContentSize().height));
    CCSprite* icon1 = CCSprite::createWithSpriteFrameName("powerIcon.png");
    icon1->setScale(Mathlib::min(40/icon1->getContentSize().width,40/icon1->getContentSize().height));
    
    icon1->setPosition(ccp(430,307));
    
    CCSprite* sprite1 = CCSprite::createWithSpriteFrameName("questLight.png");
    sprite1->setScale(1.15);
    sprite1->setOpacity(200);
    sprite1->setPosition(ccp(430,307));

    
    char str[30] = {0};
    sprintf(str,"%d",(int)prizePower->getValue());
    CCLabelAtlas* count1 = CCLabelAtlas::create(str, "number7.png", 24, 36, '/');
    count1->setPosition(ccp(603.5,307));
    count1->setScale(0.6);
    count1->setColor(ccc3(230, 207, 185));
    count1->setAnchorPoint(ccp(1,0.5));
    
    
    CCSprite* dividingLine1 = CCSprite::createWithSpriteFrameName("uiDialogCommonLine.png");
    dividingLine1->setScaleX(190/dividingLine1->getContentSize().width);
    dividingLine1->setPosition(ccp(508.5,295));
    dividingLine1->setScaleY(2/dividingLine1->getContentSize().height);
    
    CCSprite* dividingLine2 = CCSprite::createWithSpriteFrameName("uiDialogCommonLine.png");
    dividingLine2->setScaleX(80/dividingLine2->getContentSize().width);
    dividingLine2->setScaleY(2/dividingLine2->getContentSize().height);
    dividingLine2->setAnchorPoint(ccp(1,0.5));
    dividingLine2->setPosition(ccp(603,290));
    
    
    prizeLayer->addChild(dividingLine1);
    prizeLayer->addChild(dividingLine2);
    prizeLayer->addChild(sprite1);
    prizeLayer->addChild(icon1);
    prizeLayer->addChild(count1);
    
    
    
    return prizeLayer;
}

CCLabelTTF* PowerQuest::getTitle() {
   
    return CCLabelTTF::create(getTitleStr()->getCString(),"Arial",30);
}