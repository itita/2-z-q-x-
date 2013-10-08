//
//  LevelQuest.cpp
//  ww4
//
//  Created by xiao tang on 13-6-19.
//
//

#include "LevelQuest.h"
#include "MyMessageManage.h"
#include "MyGameInfo.h"
#include "MyUtil.h"
#include "DefineSet.h"
#include "Mathlib.h"
#include "GXAntiCrack.h"
#include "UpLevelMessage.h"
#include "MyHttpConnection.h"
#include "QuestUpdateMessage.h"

LevelQuest* LevelQuest::create() {
    LevelQuest* task = new LevelQuest();
    task->autorelease();
    //    task->power = _power;
    task->questTag = battleQuestTag;
    //    task->setIconName(CCString::create("questEveryDay.png"));
    return task;
}

bool LevelQuest::excuteMsg(MyBaseMessage* msg) {
    if (msg->tag == UpLevelMessageTag) {
        if (((UpLevelMessage*)msg)->level >= needLevel->getValue()) {
            QuestUpdateMessage::create(this)->sendMsg();
            isComplete = 1;
        }
    }
    
    return MyBaseQuest::excuteMsg(msg);
}

int LevelQuest::getCompleteStatus() {
    
    
    if (deadLine > 0) {
        struct cc_timeval now;
        CCTime::gettimeofdayCocos2d(&now, NULL);
        if (now.tv_sec > deadLine/1000 ) {
            return false;
        }
    }
    int level = MyUtil::getInstance()->getLevelByExperience(MyGameInfo::getInstance()->getExperience());
    if (level<=1) {
        return false;
    }
    if (isComplete == -1) {
        
        if (level < needLevel->getValue()) {
            isComplete = 0;
            return false;
        } else {
            isComplete = 1;
            return true;
        }
    }else {
        return isComplete;
    }
}

void LevelQuest::getPrize() {
    
    for (int i=0; i<prizeResourceTagList->count(); i++) {
        int prizeTag = ((GXintValue*)prizeResourceTagList->objectAtIndex(i))->getValue();
        int prizeCount = ((GXintValue*)prizeResourceCountList->objectAtIndex(i))->getValue();
        
        MyGameInfo::getInstance()->changeResource(prizeTag,prizeCount);
    }
    
}

CCLayer* LevelQuest::getDescLayer()  {
    int level = MyUtil::getInstance()->getLevelByExperience(MyGameInfo::getInstance()->getExperience());
    
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
    
    CCSprite* tixing;
    if (level >= needLevel->getValue() ) {
        sprintf(str,"　　[已完成]　成功升至%d级",needLevel->getValue());
        tixing = CCSprite::createWithSpriteFrameName("questAppear.png");
        tixing->setScale(0.45);
        tixing->setPosition(ccp(55,293-desc->getContentSize().height));
        tixing->runAction(CCRepeatForever::create(static_cast<CCSequence*>(CCSequence::create(CCScaleTo::create(1, 0.5), CCScaleTo::create(1,0.45),NULL) )));
    } else {
        sprintf(str,"　　[未完成]　需升至%d级,进度:%d/%d",needLevel->getValue(),level,needLevel->getValue());
        tixing = CCSprite::createWithSpriteFrameName("questQuestion.png");
        tixing->setScale(0.45);
        tixing->setPosition(ccp(55,293-desc->getContentSize().height));
    }
    
    
    CCLabelTTF* dest = CCLabelTTF::create(str,"Arial",23,CCSizeZero, kCCTextAlignmentLeft, kCCVerticalTextAlignmentTop);
    dest->setAnchorPoint(ccp(0,1));
    dest->setPosition(ccp(25,305-desc->getContentSize().height));
    dest->setColor(ccc3(230, 207, 185));
    
    
    
    layer->addChild(dest);
    layer->addChild(tixing);
    
    
    
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


CCLayer* LevelQuest::getPrizeInfo() {
    CCLayer* prizeLayer = CCLayer::create();
    for (int i=0; i<prizeResourceTagList->count(); i++) {
        
        int prizeTag = ((GXintValue*)prizeResourceTagList->objectAtIndex(i))->getValue();
        int prizeCount = ((GXintValue*)prizeResourceCountList->objectAtIndex(i))->getValue();
        
        CCSprite* icon1 = MyUtil::getInstance()->getResourceIcon(prizeTag);
        icon1->setScale(Mathlib::min(40/icon1->getContentSize().width,40/icon1->getContentSize().height));
        
        icon1->setPosition(ccp(430,307-50*i));
        
        CCSprite* sprite1 = CCSprite::createWithSpriteFrameName("questLight.png");
        sprite1->setScale(1.15);
        sprite1->setOpacity(200);
        sprite1->setPosition(ccp(430,307-50*i));
        
        char str[30] = {0};
        sprintf(str,"%d",prizeCount);
        CCLabelAtlas* count1 = CCLabelAtlas::create(str, "number7.png", 24, 36, '/');
        count1->setPosition(ccp(603.5,307-50*i));
        count1->setScale(0.6);
        count1->setColor(ccc3(230, 207, 185));
        count1->setAnchorPoint(ccp(1,0.5));
        
        
        CCSprite* dividingLine1 = CCSprite::createWithSpriteFrameName("uiDialogCommonLine.png");
        dividingLine1->setScaleX(190/dividingLine1->getContentSize().width);
        dividingLine1->setPosition(ccp(508.5,295-50*i));
        dividingLine1->setScaleY(2/dividingLine1->getContentSize().height);
        
        CCSprite* dividingLine2 = CCSprite::createWithSpriteFrameName("uiDialogCommonLine.png");
        dividingLine2->setScaleX(80/dividingLine2->getContentSize().width);
        dividingLine2->setScaleY(2/dividingLine2->getContentSize().height);
        dividingLine2->setAnchorPoint(ccp(1,0.5));
        dividingLine2->setPosition(ccp(603,290-50*i));
        
        
        prizeLayer->addChild(dividingLine1);
        prizeLayer->addChild(dividingLine2);
        prizeLayer->addChild(sprite1);
        prizeLayer->addChild(icon1);
        prizeLayer->addChild(count1);
        
    }
    
    
    return prizeLayer;
}

CCLabelTTF* LevelQuest::getTitle() {
    return CCLabelTTF::create(getTitleStr()->getCString(),"Arial",30);
}
