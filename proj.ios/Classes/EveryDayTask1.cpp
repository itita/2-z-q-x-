//
//  EveryDayTask1.cpp
//  ww4
//
//  Created by xiao tang on 13-6-3.
//
//

#include "EveryDayTask1.h"
#include "MyMessageManage.h"
#include "MyGameInfo.h"
#include "MyUtil.h"
#include "DefineSet.h"
#include "Mathlib.h"
#include "GXAntiCrack.h"

EveryDayTask1* EveryDayTask1::create() {
    EveryDayTask1* task = new EveryDayTask1();
    task->autorelease();
//    task->power = _power;
    task->questTag = everyDayTaskTag;
//    task->setIconName(CCString::create("questEveryDay.png"));
    return task;
}

bool EveryDayTask1::excuteMsg(MyBaseMessage* msg) {
//    if (msg->tag == newbie1MessageTag) {
//        
//        return true;
//    }
    return MyBaseQuest::excuteMsg(msg);
}

int EveryDayTask1::getCompleteStatus() {
    
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

void EveryDayTask1::getPrize() {
    for (int i=0; i<costResourceTagList->count(); i++) {
        int costTag = ((GXintValue*)costResourceTagList->objectAtIndex(i))->getValue();
        int costCount = ((GXintValue*)costResourceCountList->objectAtIndex(i))->getValue();
        
        MyGameInfo::getInstance()->changeResource(costTag,-1*costCount);
    }
    for (int i=0; i<prizeResourceTagList->count(); i++) {
        int prizeTag = ((GXintValue*)prizeResourceTagList->objectAtIndex(i))->getValue();
        int prizeCount = ((GXintValue*)prizeResourceCountList->objectAtIndex(i))->getValue();
        
        MyGameInfo::getInstance()->changeResource(prizeTag,prizeCount);
    }
    
}

CCLayer* EveryDayTask1::getDescLayer()  {
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
        if (costTag != powerTag) {
            if (MyGameInfo::getInstance()->getResource(costTag) >= costCount ) {
                sprintf(str,"　　[已完成]　需消耗%d",costCount);
                tixing = CCSprite::createWithSpriteFrameName("questAppear.png");
                tixing->setScale(0.45);
                tixing->setPosition(ccp(55,293-desc->getContentSize().height-i*32));
                tixing->runAction(CCRepeatForever::create(static_cast<CCSequence*>(CCSequence::create(CCScaleTo::create(1, 0.5), CCScaleTo::create(1,0.45),NULL) )));
            } else {
                sprintf(str,"　　[未完成]　需消耗%d,进度%d/%d",costCount,(int)MyGameInfo::getInstance()->getResource(costTag),costCount);
                tixing = CCSprite::createWithSpriteFrameName("questQuestion.png");
                tixing->setScale(0.45);
                tixing->setPosition(ccp(55,293-desc->getContentSize().height-i*32));
            }
        } else {
            if (MyGameInfo::getInstance()->getResource(costTag) >= costCount ) {
                sprintf(str,"　　[已完成]　成功晋升为『%s』",MyUtil::getInstance()->getRankString(costCount));
                
                tixing = CCSprite::createWithSpriteFrameName("questAppear.png");
                tixing->setScale(0.45);
                tixing->setPosition(ccp(55,293-desc->getContentSize().height-i*32));
                tixing->runAction(CCRepeatForever::create(static_cast<CCSequence*>(CCSequence::create(CCScaleTo::create(1, 0.5), CCScaleTo::create(1,0.45),NULL) )));
            } else {
                sprintf(str,"　　[未完成]　晋升为『%s』,需\n%d点战斗力　　,进度%d/%d",MyUtil::getInstance()->getRankString(costCount),costCount,(int)MyGameInfo::getInstance()->getResource(costTag),costCount);
    
                tixing = CCSprite::createWithSpriteFrameName("questQuestion.png");
                tixing->setScale(0.45);
                tixing->setPosition(ccp(55,293-desc->getContentSize().height-i*32));
                
                CCSprite* powerIcon = CCSprite::createWithSpriteFrameName("powerIcon.png");
                powerIcon->setScale(0.65);
                powerIcon->setPosition(ccp(200,260-desc->getContentSize().height-i*32));
                layer->addChild(powerIcon);
            }
        }
        
        
        CCLabelTTF* dest = CCLabelTTF::create(str,"Arial",23);
        dest->setAnchorPoint(ccp(0,1));
        dest->setPosition(ccp(25,305-desc->getContentSize().height-i*32));
        dest->setColor(ccc3(230, 207, 185));
        
        if (costTag != powerTag) {
            CCSprite* icon = MyUtil::getInstance()->getResourceIcon(costTag);
            icon->setScale(Mathlib::min(32/icon->getContentSize().width,32/icon->getContentSize().height));
            icon->setPosition(ccp(35+dest->getContentSize().width,293-desc->getContentSize().height-i*32));
            layer->addChild(icon,1);
        }
        
        layer->addChild(dest);
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
        
        
        CCLabelTTF* dest1 = CCLabelTTF::create(GXUtil::insertNewline(str,15).c_str(),"Arial",23);
        dest1->setAnchorPoint(ccp(0,1));
        dest1->setPosition(ccp(25,305-desc->getContentSize().height-i*32));
        dest1->setColor(ccc3(230, 207, 185));
        
        layer->addChild(dest1);
        layer->addChild(tixing1);
    }
    
//    CCLabelTTF* dest = CCLabelTTF::create("　　获得足够多的功勋","Arial",20);
//    dest->setAnchorPoint(ccp(0,1));
//    dest->setPosition(ccp(25,280-desc->getContentSize().height));
//    dest->setColor(ccc3(230, 207, 185));
    
//    CCSprite* sprite = MyUtil::getInstance()->getResourceIcon(gloryTag);
//    sprite->setPosition(ccp(35+dest->getContentSize().width,275-desc->getContentSize().height-12.5));
//    sprite->setScale(0.7);
    
    layer->addChild(descTitle);
    layer->addChild(desc);
    layer->addChild(destTitle);
//    layer->addChild(dest);
//    layer->addChild(sprite);
    
    return layer;
}
//CCLayer* EveryDayTask1::getSchedule()  {
//    CCLayer* layer = CCLayer::create();
//    CCLabelTTF* jindu = CCLabelTTF::create("进度:","Arial",25);
//    jindu->setAnchorPoint(ccp(0,0.5));
//    jindu->setPosition(ccp(25,40));
//    jindu->setColor(ccc3(255,120,0));
// 
//    char str[100] = {0};
//    sprintf(str,"%d/%d",(int)MyGameInfo::getInstance()->getGlory(),999);
//    CCLabelTTF* process = CCLabelTTF::create(str,"Arial",25);
//    process->setAnchorPoint(ccp(0,0.5));
//    process->setPosition(ccp(50+jindu->getContentSize().width,40));
//    process->setColor(ccc3(230, 207, 185));
//    
//    CCSprite* sprite = MyUtil::getInstance()->getResourceIcon(gloryTag);
//    sprite->setPosition(ccp(40+jindu->getContentSize().width,40));
//    sprite->setScale(0.7);
//    
//    layer->addChild(jindu);
//    layer->addChild(sprite);
//    layer->addChild(process);
//    return layer;
//}

CCLayer* EveryDayTask1::getPrizeInfo() {
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
    
//    CCSprite* icon2 = MyUtil::getInstance()->getResourceIcon(expTag);
//    icon2->setScale(Mathlib::min(45/icon2->getContentSize().width,45/icon2->getContentSize().height));
//    
//    icon2->setPosition(ccp(430,202));
//    
//    CCSprite* sprite2 = CCSprite::createWithSpriteFrameName("questLight.png");
//    sprite2->setScale(1.15);
//    sprite2->setOpacity(200);
//    sprite2->setPosition(ccp(430,202));
//    
//    CCLabelAtlas* count2 = CCLabelAtlas::create("99999999", "number7.png", 24, 36, '/');
//    count2->setScaleX(0.8);
//    count2->setScaleY(0.9);
//    count2->setPosition(ccp(535,202));
//    count2->setColor(ccc3(230, 207, 185));
//    count2->setAnchorPoint(ccp(0.5,0.5));
    
//    prizeLayer->addChild(sprite1);
//    prizeLayer->addChild(sprite2);
//    prizeLayer->addChild(icon1);
//    prizeLayer->addChild(icon2);
//    prizeLayer->addChild(count1);
//    prizeLayer->addChild(count2);
    
    return prizeLayer;
}

CCLabelTTF* EveryDayTask1::getTitle() {
//    char str[100] = {0};
//    sprintf(str,"每日任务【%s】",MyUtil::getInstance()->getRankString(power));
    return CCLabelTTF::create(getTitleStr()->getCString(),"Arial",30);
}

//int EveryDayTask1::getNeedGlory() {
//    if(power<20) {
//        return 24;
//    } else if(power <50) {
//        return 30;
//    } else if(power <100) {
//        return 50;
//    } else if(power <500) {
//        return 120;
//    } else if(power<1000) {
//        return 220;
//    } else if(power <2000) {
//        return 400;
//    } else if(power <5000) {
//        return 1000;
//    } else if(power <10000) {
//        return 2000;
//    } else if(power <20000) {
//        return 4000;
//    } else if(power <50000) {
//        return 10000;
//    } else {
//        return 20000;
//    }
//}