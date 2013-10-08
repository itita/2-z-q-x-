//
//  BuildingQuest.cpp
//  ww4
//
//  Created by xiao tang on 13-6-8.
//
//

#include "BuildingQuest.h"
#include "MyMessageManage.h"
#include "MyGameInfo.h"
#include "MyUtil.h"
#include "DefineSet.h"
#include "Mathlib.h"
#include "GXAntiCrack.h"
#include "UpdateBuildingMessag.h"
#include "QuestUpdateMessage.h"
#include "MyHttpConnection.h"

BuildingQuest* BuildingQuest::create() {
    BuildingQuest* task = new BuildingQuest();
    task->autorelease();
    //    task->power = _power;
    task->questTag = everyDayTaskTag;
    //    task->setIconName(CCString::create("questEveryDay.png"));
    return task;
}

bool BuildingQuest::excuteMsg(MyBaseMessage* msg) {
    if (msg->tag == updateBuildingMessageTag) {
        UpdateBuildingMessag* uMsg = (UpdateBuildingMessag*)msg;
        bool flag = true;
        for (int i=0; i<needBuildingTagList->count(); i++) {
            int needCount = ((GXintValue*)needBuildingCountList->objectAtIndex(i))->getValue();
            int needTag = ((GXintValue*)needBuildingTagList->objectAtIndex(i))->getValue();
            int needLevel = ((GXintValue*)needBuildingLevelList->objectAtIndex(i))->getValue();
            int finishCount = ((GXintValue*)finishBuildingCountList->objectAtIndex(i))->getValue();
            if (finishCount >= needCount) {
                continue;
            }
            if (needTag == uMsg->buildingId && uMsg->nextLevel == needLevel) {
                finishCount = finishCount + uMsg->count;
                ((GXintValue*)finishBuildingCountList->objectAtIndex(i))->setValue(finishCount);
                //联网更新任务进度
                
                std::vector<char> sendBuffer;
                sendBuffer.clear();
                char tempStr[10] = {0};
                for (int i=0; i<finishBuildingCountList->count(); i++) {
                    int finishCount = ((GXintValue*)finishBuildingCountList->objectAtIndex(i))->getValue();
                    if (finishBuildingCountList->count() == 1) {
                        sprintf(tempStr,"[%d]",finishCount);
                    }else if (i == 0) {
                        sprintf(tempStr,"[%d,",finishCount);
                    } else if(i == finishBuildingCountList->count()-1) {
                        sprintf(tempStr,"%d]",finishCount);
                    } else {
                        sprintf(tempStr,"%d,",finishCount);
                    }
    
                    sendBuffer.insert(sendBuffer.end(), tempStr, tempStr+strlen(tempStr));
                }
                char* str = GXUtil::transCharVectorToCCString(&sendBuffer);
                MyHttpConnection::getInstance()->sendUpdateMissionProgress(str,questId);
                free(str);
            }
            if (finishCount < needCount) {
                flag = false;
            }
        }
        completeFlag = flag;
        if (flag) {
            QuestUpdateMessage::create(this)->sendMsg();
        }
    }
    return MyBaseQuest::excuteMsg(msg);
}

int BuildingQuest::getCompleteStatus() {
    if (completeFlag == false) {
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

void BuildingQuest::getPrize() {
    
    for (int i=0; i<prizeResourceTagList->count(); i++) {
        int prizeTag = ((GXintValue*)prizeResourceTagList->objectAtIndex(i))->getValue();
        int prizeCount = ((GXintValue*)prizeResourceCountList->objectAtIndex(i))->getValue();
        
        MyGameInfo::getInstance()->changeResource(prizeTag,prizeCount);

    }
    
}

CCLayer* BuildingQuest::getDescLayer()  {
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
    for (i=0; i<needBuildingTagList->count(); i++) {
        int needCount = ((GXintValue*)needBuildingCountList->objectAtIndex(i))->getValue();
        int needLevel = ((GXintValue*)needBuildingLevelList->objectAtIndex(i))->getValue();
        CCString* needLabel = (CCString*)needBuildingLabelList->objectAtIndex(i);
        int finishCount = ((GXintValue*)finishBuildingCountList->objectAtIndex(i))->getValue();
        
        CCSprite* tixing;
        if (finishCount >= needCount) {
            if (needLevel <= 1) {
                sprintf(str,"　　[已完成]　建设%d座『%s』",needCount,needLabel->getCString());
            } else {
                sprintf(str,"　　[已完成]　升级%d座『%s』至%d级",needCount,needLabel->getCString(),needLevel);
            }
            tixing = CCSprite::createWithSpriteFrameName("questAppear.png");
            tixing->setScale(0.45);
            tixing->setPosition(ccp(55,293-desc->getContentSize().height-preHeight-5));
            tixing->runAction(CCRepeatForever::create(static_cast<CCSequence*>(CCSequence::create(CCScaleTo::create(1, 0.5), CCScaleTo::create(1,0.45),NULL) )));
        } else {
            if (needLevel <= 1) {
                sprintf(str,"　　[未完成]　建设%d座『%s』,进度:%d/%d",needCount,needLabel->getCString(),finishCount,needCount);
            } else {
                sprintf(str,"　　[未完成]　升级%d座『%s』至%d级,进度:%d/%d",needCount,needLabel->getCString(),needLevel,finishCount,needCount);
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


CCLayer* BuildingQuest::getPrizeInfo() {
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

CCLabelTTF* BuildingQuest::getTitle() {
    return CCLabelTTF::create(getTitleStr()->getCString(),"Arial",30);
}

bool BuildingQuest::checkCompleteStatues() {
    for (int i=0; i<needBuildingTagList->count(); i++) {
        int needCount = ((GXintValue*)needBuildingCountList->objectAtIndex(i))->getValue();
        int finishCount = ((GXintValue*)finishBuildingCountList->objectAtIndex(i))->getValue();
        if (finishCount < needCount) {
            completeFlag = false;
            return false;
        }
    }
    completeFlag = true;
    return true;
}
