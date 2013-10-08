//
//  ArmyQuest.cpp
//  ww4
//
//  Created by xiao tang on 13-6-8.
//
//

#include "ArmyQuest.h"
#include "MyMessageManage.h"
#include "MyGameInfo.h"
#include "MyUtil.h"
#include "DefineSet.h"
#include "Mathlib.h"
#include "GXAntiCrack.h"
#include "UpdateArmyMessage.h"
#include "QuestUpdateMessage.h"

ArmyQuest* ArmyQuest::create() {
    ArmyQuest* task = new ArmyQuest();
    task->autorelease();
    //    task->power = _power;
    task->questTag = armyQuestTag;
    //    task->setIconName(CCString::create("questEveryDay.png"));
    return task;
}

bool ArmyQuest::excuteMsg(MyBaseMessage* msg) {
    if (msg->tag == updateArmyMessageTag) {
        UpdateArmyMessage* uMsg = (UpdateArmyMessage*)msg;
        int flag = 1;
        for (int i=0; i<needArmyTagList->count(); i++) {

            int needTag = ((GXintValue*)needArmyTagList->objectAtIndex(i))->getValue();
            int needLevel = ((GXintValue*)needArmyLevelList->objectAtIndex(i))->getValue();
            int finishLevel = ((GXintValue*)finishArmyList->objectAtIndex(i))->getValue();
            if (finishLevel >= needLevel) {
                continue;
            }
            if (needTag == uMsg->armyId) {
                finishLevel++;
                ((GXintValue*)finishArmyList->objectAtIndex(i))->setValue(finishLevel);
            }
            if (finishLevel < needLevel) {
                flag = 0;
            }
        }
        completeFlag = flag;
        if (flag) {
            QuestUpdateMessage::create(this)->sendMsg();
        }
    }
    return MyBaseQuest::excuteMsg(msg);
}

int ArmyQuest::getCompleteStatus() {
    checkCompleteStatues();
    if (completeFlag == 0) {
        return questUnfinishedTag;
    }
    if (deadLine > 0) {
        struct cc_timeval now;
        CCTime::gettimeofdayCocos2d(&now, NULL);
        if (now.tv_sec > deadLine/1000 ) {
            return questUnfinishedTag;
        }
    }
    return questFinishedTag;
}

void ArmyQuest::getPrize() {
    
    for (int i=0; i<prizeResourceTagList->count(); i++) {
        int prizeTag = ((GXintValue*)prizeResourceTagList->objectAtIndex(i))->getValue();
        int prizeCount = ((GXintValue*)prizeResourceCountList->objectAtIndex(i))->getValue();
        
        MyGameInfo::getInstance()->changeResource(prizeTag,prizeCount);
    }
    
}

CCLayer* ArmyQuest::getDescLayer()  {
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
    char str[200] = {0};
    int i=0;
    float preHeight =0;
    for (i=0; i<needArmyTagList->count(); i++) {
        
        int needLevel = ((GXintValue*)needArmyLevelList->objectAtIndex(i))->getValue();
        CCString* needLabel = (CCString*)needArmyLabelList->objectAtIndex(i);
        int finishLevel = ((GXintValue*)finishArmyList->objectAtIndex(i))->getValue();
        
        CCSprite* tixing;
        if (finishLevel >= needLevel) {
            if (needLevel <= 1) {
                sprintf(str,"　　[已完成]　解锁兵种『%s』",needLabel->getCString());
            } else {
                sprintf(str,"　　[已完成]　升级兵种『%s』至%d级",needLabel->getCString(),needLevel);
            }
            tixing = CCSprite::createWithSpriteFrameName("questAppear.png");
            tixing->setScale(0.45);
            tixing->setPosition(ccp(55,293-desc->getContentSize().height-preHeight-5));
            tixing->runAction(CCRepeatForever::create(static_cast<CCSequence*>(CCSequence::create(CCScaleTo::create(1, 0.5), CCScaleTo::create(1,0.45),NULL) )));
        } else {
            if (needLevel <= 1) {
                sprintf(str,"　　[未完成]　解锁兵种『%s』",needLabel->getCString());
            } else {
                sprintf(str,"　　[未完成]　升级兵种『%s』至%d级,进度:%d/%d",needLabel->getCString(),needLevel,finishLevel,needLevel);
            }
            tixing = CCSprite::createWithSpriteFrameName("questQuestion.png");
            tixing->setScale(0.45);
            tixing->setPosition(ccp(55,293-desc->getContentSize().height-preHeight-5));
        }
        
        
        CCLabelTTF* dest = CCLabelTTF::create(GXUtil::insertNewline(str,15).c_str(),"Arial",23,CCSizeZero, kCCTextAlignmentLeft, kCCVerticalTextAlignmentTop);
        dest->setAnchorPoint(ccp(0,1));
        dest->setPosition(ccp(25,305-desc->getContentSize().height-preHeight-5));
        dest->setColor(ccc3(230, 207, 185));
        
        preHeight = preHeight + dest->getContentSize().height+5;
        
        
        layer->addChild(dest);
        layer->addChild(tixing);
        
        
    }
    
    if(deadLine > 0) {
        struct cc_timeval now;
        CCTime::gettimeofdayCocos2d(&now, NULL);
        
        CCSprite* tixing1;
        if (now.tv_sec <= deadLine/1000 ) {
            sprintf(str,"　　需在[%s]之前完成",getdeadLineLabel()->getCString());
            tixing1 = CCSprite::createWithSpriteFrameName("questAppear.png");
            tixing1->setScale(0.45);
            tixing1->setPosition(ccp(55,293-desc->getContentSize().height-i*32));
            tixing1->runAction(CCRepeatForever::create(static_cast<CCSequence*>(CCSequence::create(CCScaleTo::create(1, 0.5), CCScaleTo::create(1,0.45),NULL) )));
        } else {
            sprintf(str,"　　已经超过[%s],无法完成",getdeadLineLabel()->getCString());
            tixing1 = CCSprite::createWithSpriteFrameName("questQuestion.png");
            tixing1->setScale(0.45);
            tixing1->setPosition(ccp(55,293-desc->getContentSize().height-i*32));
        }
        
        
        CCLabelTTF* dest1 = CCLabelTTF::create(str,"Arial",23);
        dest1->setAnchorPoint(ccp(0,1));
        dest1->setPosition(ccp(25,305-desc->getContentSize().height-preHeight));
        dest1->setColor(ccc3(230, 207, 185));
        
        layer->addChild(dest1);
        layer->addChild(tixing1);
    }
    
    
    
    layer->addChild(descTitle);
    layer->addChild(desc);
    layer->addChild(destTitle);
    
    
    return layer;
}


CCLayer* ArmyQuest::getPrizeInfo() {
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

CCLabelTTF* ArmyQuest::getTitle() {
    return CCLabelTTF::create(getTitleStr()->getCString(),"Arial",30);
}

void ArmyQuest::checkCompleteStatues() {
    if (completeFlag < 0) {
        CCObject* obj1;
        CCObject* obj2;
        int j=0;
        CCARRAY_FOREACH(needArmyTagList,obj1){
            int tag = ((GXintValue*)(obj1))->getValue();
            int beanLevel = 0;
            if (MyGameInfo::getInstance()->creatorArray->count() == 0) {
                return;
            }
            CCARRAY_FOREACH(MyGameInfo::getInstance()->creatorArray,obj2) {
                CreatorInfoBean* bean = (CreatorInfoBean*)obj2;
                if (bean->creator->cardId == tag) {
                    if (bean->getLevel() > beanLevel) {
                        beanLevel = bean->getLevel();
                    }
                }
            }
            ((GXintValue*)finishArmyList->objectAtIndex(j))->setValue(beanLevel);
            j++;
        }
        for (int i=0; i<needArmyTagList->count(); i++) {
            int needLevel = ((GXintValue*)needArmyLevelList->objectAtIndex(i))->getValue();
            int finishLevel = ((GXintValue*)finishArmyList->objectAtIndex(i))->getValue();
            if (finishLevel < needLevel) {
                completeFlag = 0;
                return;
            }
        }
        completeFlag = 1;
    }
}
