//
//  GarbageCenter.cpp
//  ww4
//
//  Created by xiao tang on 13-5-25.
//
//

#include "GarbageCenter.h"
#include "NormalState.h"
#include "DefineSet.h"
#include "BeAttackState.h"
#include "StartScene.h"
#include "MyUtil.h"
#include "SuperYouTian.h"
#include "YouTian.h"
#include "MathLib.h"

BuildingInfo* GarbageCenter::buildingInfo = NULL;

MyBuilding* GarbageCenter::createNormal(CCObject* target,int level) {
    CCSprite* byItem = CCSprite::createWithSpriteFrameName("Recycling.png");
    byItem->setAnchorPoint(ccp(0.5,0.4));
    // 普通状态
    
    NormalState* workState = NormalState::create(WorkStateTag, byItem);
    
    
    
    TransitionInfo* infoItem =  TransitionInfo::create(InfoTransition,"info.png",workState,menu_selector(MyState::infoCallBack));
    
  
    
    MyBuilding* BDbuilding = MyBuilding::create(bingyingTag,CCSizeMake(4,4),workState,10);
    
    BDbuilding->setLevel(level);
    BDbuilding->setTag(GarbageCenterTag);
    BDbuilding->setSummaryCount(5000);
    BDbuilding->resourceTag = ironTag;
    BDbuilding->setUpdateInfo_selector = (SEL_SetUpdateInfo)(&GarbageCenter::setUpdateInfo);
    
    TransitionInfo* updateItem =  TransitionInfo::create(UpdateTransition,"update.png",BDbuilding,menu_selector(MyBuilding::updateLevel));
    
    workState->addTransition(UpdateTransition, WorkStateTag,updateItem);
    workState->addTransition(InfoTransition, WorkStateTag,infoItem);
    
    BDbuilding->setBuildingName(CCString::create("回收中心"),108);
    getGarbageCenterInfo()->count++;
    BDbuilding->setUserData(getGarbageCenterInfo());
    
    return BDbuilding;
}

MyBattleBuilding* GarbageCenter::createBattle(int level,int stateId) {
    BeAttackState* beAttackState;
    if (stateId == UnfinishedStateTag) {
        beAttackState = BeAttackState::create(UnfinishedStateTag, CCSprite::createWithSpriteFrameName("buildstruct4x4(0).png"), 100);
    } else {
        CCSprite* ytItem = CCSprite::createWithSpriteFrameName("Recycling.png");
        ytItem->setAnchorPoint(ccp(0.5,0.4));
        beAttackState = BeAttackState::create(BeAttackStateTag, ytItem,hszxBaseHealth);
    }
    
    MyBattleBuilding* BDbuilding = MyBattleBuilding::create(bingyingTag,CCSizeMake(4,4),beAttackState);
    BDbuilding->setLevel_selector = (SEL_SetBattleLevel)(&GarbageCenter::setBattleLevel);
    BDbuilding->setLevel(level);
    BDbuilding->setTag(GarbageCenterTag);
    BDbuilding->setBuildingName(CCString::create("回收中心"),108);
//    BDbuilding->displaySummary();
    return BDbuilding;
}

MyBuildingCard* GarbageCenter::createCard(CCObject* target,SEL_MenuHandler selector) {
    CCSprite* sprite = CCSprite::createWithSpriteFrameName("Recycling.png");
    sprite->setAnchorPoint(ccp(0.50,0.63));
    sprite->setScale(0.8);
    MyBuildingCard* card = MyBuildingCard::create(sprite,GarbageCenterTag,garbageCenterMaxCount,getGarbageCenterInfo()->count,ironTag,20000,15,"回收中心", target,selector);
    return card;
}

void GarbageCenter::setBattleLevel(int level,GXFSM* fsm) {
    BeAttackState* beAttack = dynamic_cast<BeAttackState*>(fsm->getState(BeAttackStateTag));
    if(beAttack != NULL) {
        float life = MyUtil::getInstance()->updateLevelByRate(0,hszxBaseHealth, level, 1);
        beAttack->setMaxLife(life);
        beAttack->setLife(life);
    }
}

void GarbageCenter::setUpdateInfo(GXFSMstate* _state,CCLayer* updateLayer)
{
    MyState* state = (MyState*)_state;
    float healthLevelData = MyUtil::getInstance()->updateLevelByRate(0,hszxBaseHealth, state->building->getLevel(), 1);
    float healthNextData = MyUtil::getInstance()->updateLevelByRate(0,hszxBaseHealth, state->building->getLevel()+1, 1);
    float healthMaxData = MyUtil::getInstance()->updateLevelByRate(0,hszxBaseHealth, state->building->getMaxLevel(), 1);
    
    CCSprite* healthIcon = CCSprite::createWithSpriteFrameName("healthIcon.png");
    healthIcon->setPosition(ccp(-68,160));
    updateLayer->addChild(healthIcon);
    CCLayer* healthBar = MyUtil::getInstance()->getUpdateBar(healthNextData/healthMaxData, healthLevelData/healthMaxData,"levelBarUp.png");
    healthBar->setPosition(ccp(-40,142));
    
    
    char str[100] = {0};
    if (state->building->getLevel() < state->building->getMaxLevel()) {
        sprintf(str, "耐久度:%d+%d",(int)healthLevelData,(int)(healthNextData-healthLevelData));
    } else {
        sprintf(str, "耐久度:%d",(int)healthLevelData);
    }
    
    CCLabelTTF* healthLabel = CCLabelTTF::create(str, "Arial", 24);
    healthLabel->setAnchorPoint(ccp(0,0));
    healthLabel->setColor(ccc3(254, 218, 130));
    healthLabel->setPosition(ccp(-40,152));
    updateLayer->addChild(healthBar);
    updateLayer->addChild(healthLabel);
    
    float recyclingLevelData = MyUtil::getInstance()->updateLevelByCount(hszxBaseMaxRecycling,state->building->getLevel(),hszxUpdateMaxRecyclingCount);
    float recyclingNextData = MyUtil::getInstance()->updateLevelByCount(hszxBaseMaxRecycling,state->building->getLevel()+1,hszxUpdateMaxRecyclingCount);
    float recyclingMaxData = MyUtil::getInstance()->updateLevelByCount(hszxBaseMaxRecycling,state->building->getMaxLevel(),hszxUpdateMaxRecyclingCount);
    
    CCSprite* capacityIcon = CCSprite::createWithSpriteFrameName("recyclingIcon.png");
    capacityIcon->setPosition(ccp(-68,106));
    updateLayer->addChild(capacityIcon);
    CCLayer* capacityBar = MyUtil::getInstance()->getUpdateBar(recyclingNextData/recyclingMaxData, recyclingLevelData/recyclingMaxData,"levelBarUp.png");
    
    capacityBar->setPosition(ccp(-40,88));
    
    
    if (state->building->getLevel() < state->building->getMaxLevel()) {
        sprintf(str, "最大回收比例:%%%d+%%2.5",(int)(recyclingLevelData*100+0.5));
    } else {
        sprintf(str, "最大回收比例:%%%d",(int)(recyclingLevelData*100+0.5));
    }
    
    CCLabelTTF* capacityLabel = CCLabelTTF::create(str, "Arial", 24);
    capacityLabel->setAnchorPoint(ccp(0,0));
    capacityLabel->setColor(ccc3(254, 218, 130));
    capacityLabel->setPosition(ccp(-40,98));
    updateLayer->addChild(capacityBar);
    updateLayer->addChild(capacityLabel);
    
    float rate = Mathlib::min(recyclingLevelData,(YouTian::getYouTianInfo()->count+SuperYouTian::getSuperYouTianInfo()->count*3) * 0.01);
    CCPoint loc = ccp(-78,35);
//    int ytCount = YouTian::getYouTianInfo()->count;
//    int sytCount = SuperYouTian::getSuperYouTianInfo()->count;
    if (rate>=recyclingLevelData-0.001) {
        sprintf(str,"当前回收率:%%%d(已最大)",(int)((recyclingLevelData+0.001)*100));
    } else  {
        sprintf(str,"当前回收率:%%%d(建设油厂提升)",(int)((rate+0.001)*100));
    }
//    else if(ytCount > 0 && sytCount>0) {
//        sprintf(str,"当前回收率:\n%d(油厂)x1+%d(超油)x3=%%%d",ytCount,sytCount,(int)((rate+0.001)*100));
//        loc.y = 20;
//    } else if(ytCount > 0){
//        sprintf(str,"当前回收率:%d(油厂)x1=%%%d",ytCount,(int)((rate+0.001)*100));
//    } else if(sytCount > 0){
//        sprintf(str,"当前回收率:%d(超级油厂)x3=%%%d",sytCount,(int)((rate+0.001)*100));
//    } else {
//        sprintf(str,"当前回收率:%%0(需要建造油厂)");
//    }
    
    CCLabelTTF* currentCollectRateLabel = CCLabelTTF::create(str, "Arial", 24,CCSizeZero, kCCTextAlignmentLeft, kCCVerticalTextAlignmentCenter);
    currentCollectRateLabel->setAnchorPoint(ccp(0,0));
    currentCollectRateLabel->setColor(ccc3(255,133,80));
    currentCollectRateLabel->setPosition(loc);
    updateLayer->addChild(currentCollectRateLabel);
    
    
    CCLabelTTF* nameLabel = CCLabelTTF::create("回收中心", "Arial", 24);
    nameLabel->setColor(ccc3(254, 218, 130));
    nameLabel->setAnchorPoint(ccp(0.5,0.5));
    nameLabel->setPosition(ccp(-204,172));
    updateLayer->addChild(nameLabel);
    
    
    CCLabelTTF* description = CCLabelTTF::create("　　注意：回收中心只负责回收，每一座油矿增\n加%1的回收率，最大回收率不超过面板数值.回\n收中心从敌人的残骸中搜集可以利用的物资，然\n后交由油厂来重新炼化成油矿。", "Arial",  26,CCSizeZero, kCCTextAlignmentLeft, kCCVerticalTextAlignmentTop);
    description->setAnchorPoint(ccp(0,0.5));
    description->setColor(ccc3(254, 218, 130));
    description->setPosition(ccp(-280,-50));
    updateLayer->addChild(description);
}

BuildingInfo* GarbageCenter::getGarbageCenterInfo() {
    if(buildingInfo == NULL) {
        buildingInfo = BuildingInfo::create();
    }
    return buildingInfo;
}