//
//  SuperYouTian.cpp
//  ww4
//
//  Created by xiao tang on 13-5-6.
//
//

#include "SuperYouTian.h"
#include "DefineSet.h"
#include "CollectState.h"
#include "MyUtil.h"
#include "ResourceBeAttackState.h"

BuildingInfo* SuperYouTian::buildingInfo = NULL;

MyBuilding* SuperYouTian::createNormal(CCObject* target,int level,float ori,long dt) {
    
    CCSprite* byItem = CCSprite::createWithSpriteFrameName("superYT.png");
    byItem->setAnchorPoint(ccp(0.4,0.27));
    CollectState* workState = CollectState::create(WorkStateTag, byItem,superYtBaseColletSpeed,superYtBaseColletMaxCapacity,oilTag);
    
    TransitionInfo* collectItem =  TransitionInfo::create(CollectTransition,"collect.png",workState,menu_selector(CollectState::doCollectPlaysfx));
    
    TransitionInfo* infoItem =  TransitionInfo::create(InfoTransition,"info.png",workState,menu_selector(MyState::infoCallBack));
    
    
#if game_version == soft_version
    MyBuilding* BDbuilding = MyBuilding::create(superYouTianTag,CCSizeMake(4,4),workState,level,10);
#endif
#if game_version == hard_version
    MyBuilding* BDbuilding = MyBuilding::create(superYouTianTag,CCSizeMake(3,3),workState,10);
#endif
    
    BDbuilding->setLevel_selector = (SEL_SetLevel)(&SuperYouTian::setNormalLevel);
    BDbuilding->setLevel(level);
    BDbuilding->setSummaryCount(1000);
    BDbuilding->resourceTag = ironTag;
    BDbuilding->setUpdateInfo_selector = (SEL_SetUpdateInfo)(&SuperYouTian::setUpdateInfo);
    
    TransitionInfo* updateItem =  TransitionInfo::create(UpdateTransition,"update.png",BDbuilding,menu_selector(MyBuilding::updateLevel));
    
    workState->addTransition(UpdateTransition, WorkStateTag,updateItem);
    workState->addTransition(CollectTransition, WorkStateTag,collectItem);
    workState->addTransition(InfoTransition, WorkStateTag,infoItem);
    
    
    BDbuilding->setBuildingName(CCString::create("超级炼油厂"),108);
    
    workState->setCapacity(ori,dt);
    
    BDbuilding->setUserData(getSuperYouTianInfo());
    getSuperYouTianInfo()->count++;
    
    BDbuilding->setDoStateInterval(1);
    
    return BDbuilding;
}

MyBattleBuilding* SuperYouTian::createBattle(int level,int stateId,float ori,float rate) {
    
    BeAttackState* beAttackState = NULL;
    
    if (stateId == UnfinishedStateTag) {
        CCSprite* unfinishItem = CCSprite::createWithSpriteFrameName("buildstruct3x3(0).png");
        beAttackState = BeAttackState::create(UnfinishedStateTag, unfinishItem, 100);
    } else {
        CCSprite* bdItem = CCSprite::createWithSpriteFrameName("superYT.png");
        bdItem->setAnchorPoint(ccp(0.4,0.27));
        beAttackState = ResourceBeAttackState::create(BeAttackStateTag, bdItem,superYtBaseHealth,superYtBaseColletSpeed,superYtBaseColletMaxCapacity,oilTag);
    }
    
    
    
    //    CCSprite* unfinishItem = CCSprite::createWithSpriteFrameName("buildstruct2x2(0).png");
    //    BeAttackState* unfinished = BeAttackState::create(UnfinishedStateTag, unfinishItem, 100);
    //    unfinished->addTransition(toRuinsTransition, RuinsStateTag);
    
    MyBattleBuilding* BDbuilding;
    
#if game_version == soft_version
    BDbuilding = MyBattleBuilding::create(superYouTianTag,CCSizeMake(4,4),beAttackState,level);
#endif
#if game_version == hard_version
    BDbuilding = MyBattleBuilding::create(superYouTianTag,CCSizeMake(3,3),beAttackState);
#endif
    BDbuilding->setLevel_selector = (SEL_SetBattleLevel)(&SuperYouTian::setBattleLevel);
    BDbuilding->setLevel(level);
    
    BDbuilding->setBuildingName(CCString::create("超级炼油厂"),108);
//    BDbuilding->displaySummary();

    if(stateId == BeAttackStateTag) {
        //计算抢劫部分,但是要在设置等级之后
        long long nowtime = MyGameInfo::getInstance()->nowTime;
        long long lasttime = MyGameInfo::getInstance()->lastTime;
        long dt = (nowtime-lasttime)/1000;
        ((ResourceBeAttackState*)beAttackState)->setCapacity(ori, dt,rate);
        
        //抢劫叠加油
        
        MyGameInfo::getInstance()->setRobberOil(MyGameInfo::getInstance()->getRobberOil() + ((ResourceBeAttackState*)beAttackState)->getCapacity()*rate);
        
    }

    
    return BDbuilding;
}

MyBuildingCard* SuperYouTian::createCard(CCObject* target,SEL_MenuHandler selector) {
    CCSprite* sprite = CCSprite::createWithSpriteFrameName("superYT.png");
    sprite->setAnchorPoint(ccp(0.5,0.6));
    MyBuildingCard* card = MyBuildingCard::create(sprite,superYouTianTag,0,0,diamondTag,500,0,"超级炼油厂", target, selector);
    return card;
}

void SuperYouTian::setNormalLevel(int level,GXFSM* fsm) {
    CollectState* collectState = dynamic_cast<CollectState*>(fsm->getState(WorkStateTag));
    if (collectState != NULL) {
        collectState->setMaxCapacity(MyUtil::getInstance()->updateLevelByRate(superYtOriMaxCapacity,collectState->getBaseMaxCapacity(), level, superYtUpdateColletMaxCapacityRate));
        collectState->setOutputPsecond(MyUtil::getInstance()->updateLevelByRate(superYtOriCollectSpeed,collectState->getBaseOutputPsecond(), level, superYtUpdateColletSpeedRate));
    }
}

void SuperYouTian::setBattleLevel(int level,GXFSM* fsm) {
    ResourceBeAttackState* beAttack = dynamic_cast<ResourceBeAttackState*>(fsm->getState(BeAttackStateTag));
    if(beAttack != NULL) {
        beAttack->setMaxCapacity(MyUtil::getInstance()->updateLevelByRate(superYtOriMaxCapacity,beAttack->getBaseMaxCapacity(), level, superYtUpdateColletMaxCapacityRate));
        beAttack->setOutputPsecond(MyUtil::getInstance()->updateLevelByRate(superYtOriCollectSpeed,beAttack->getBaseOutputPsecond(), level, superYtUpdateColletSpeedRate));
        float life =MyUtil::getInstance()->updateLevelByRate(superYtOriBaseHealth,superYtBaseHealth, level, superYtUpdateHealthRate);
        beAttack->setMaxLife(life);
        beAttack->setLife(life);
    }
}

void SuperYouTian::setUpdateInfo(GXFSMstate* _state,CCLayer* updateLayer) {
    
    MyState* state = (MyState*)_state;
    float healthLevelData = MyUtil::getInstance()->updateLevelByRate(superYtOriBaseHealth,superYtBaseHealth, state->building->getLevel(), superYtUpdateHealthRate);
    float healthNextData = MyUtil::getInstance()->updateLevelByRate(superYtOriBaseHealth,superYtBaseHealth, state->building->getLevel()+1, superYtUpdateHealthRate);
    float healthMaxData = MyUtil::getInstance()->updateLevelByRate(superYtOriBaseHealth,superYtBaseHealth, state->building->getMaxLevel(), superYtUpdateHealthRate);
    
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
    
    float capacityLevelData = MyUtil::getInstance()->updateLevelByRate(superYtOriMaxCapacity,((CollectState*)state)->getBaseMaxCapacity(), state->building->getLevel(), superYtUpdateColletMaxCapacityRate);
    float capacityNextData = MyUtil::getInstance()->updateLevelByRate(superYtOriMaxCapacity,((CollectState*)state)->getBaseMaxCapacity(), state->building->getLevel()+1, superYtUpdateColletMaxCapacityRate);
    float capacityMaxData = MyUtil::getInstance()->updateLevelByRate(superYtOriMaxCapacity,((CollectState*)state)->getBaseMaxCapacity(), state->building->getMaxLevel(), superYtUpdateColletMaxCapacityRate);
    
    CCSprite* capacityIcon = CCSprite::createWithSpriteFrameName("oilCapacity.png");
    capacityIcon->setPosition(ccp(-68,106));
    updateLayer->addChild(capacityIcon);
    CCLayer* capacityBar = MyUtil::getInstance()->getUpdateBar(capacityNextData/capacityMaxData, capacityLevelData/capacityMaxData,"levelBarUp.png");
    
    capacityBar->setPosition(ccp(-40,88));
    
    
    if (state->building->getLevel() < state->building->getMaxLevel()) {
        sprintf(str, "最大存储数量:%d+%d",(int)capacityLevelData,(int)(capacityNextData-capacityLevelData));
    } else {
        sprintf(str, "最大存储数量:%d",(int)capacityLevelData);
    }
    
    CCLabelTTF* capacityLabel = CCLabelTTF::create(str, "Arial", 24);
    capacityLabel->setAnchorPoint(ccp(0,0));
    capacityLabel->setColor(ccc3(254, 218, 130));
    capacityLabel->setPosition(ccp(-40,98));
    updateLayer->addChild(capacityBar);
    updateLayer->addChild(capacityLabel);
    
    float speedLevelData = MyUtil::getInstance()->updateLevelByRate(superYtOriCollectSpeed,((CollectState*)state)->getBaseOutputPsecond(), state->building->getLevel(), superYtUpdateColletSpeedRate);
    float speedNextData = MyUtil::getInstance()->updateLevelByRate(superYtOriCollectSpeed,((CollectState*)state)->getBaseOutputPsecond(), state->building->getLevel()+1, superYtUpdateColletSpeedRate);
    float speedMaxData = MyUtil::getInstance()->updateLevelByRate(superYtOriCollectSpeed,((CollectState*)state)->getBaseOutputPsecond(), state->building->getMaxLevel(), superYtUpdateColletSpeedRate);
    
    CCSprite* speedIcon = CCSprite::createWithSpriteFrameName("OilcollectSpeedIcon.png");
    speedIcon->setPosition(ccp(-68,48));
    updateLayer->addChild(speedIcon);
    CCLayer* speedBar = MyUtil::getInstance()->getUpdateBar(speedNextData/speedMaxData, speedLevelData/speedMaxData,"levelBarUp.png");
    speedBar->setPosition(ccp(-40,30));
    
    if (state->building->getLevel() < state->building->getMaxLevel()) {
        sprintf(str, "每小时采集数量:%d+%d",(int)(speedLevelData*3600),(int)((speedNextData-speedLevelData)*3600));
    } else {
        sprintf(str, "每小时采集数量:%d",(int)(speedLevelData*3600));
    }
    CCLabelTTF* speedLabel = CCLabelTTF::create(str, "Arial", 24);
    speedLabel->setAnchorPoint(ccp(0,0));
    speedLabel->setColor(ccc3(254, 218, 130));
    speedLabel->setPosition(ccp(-40,40));
    
    
    CCLabelTTF* nameLabel = CCLabelTTF::create("超级炼油厂", "Arial", 24);
    nameLabel->setColor(ccc3(254, 218, 130));
    nameLabel->setAnchorPoint(ccp(0.5,0.5));
    nameLabel->setPosition(ccp(-204,172));
    updateLayer->addChild(nameLabel);
    updateLayer->addChild(speedBar);
    updateLayer->addChild(speedLabel);
    
    CCLabelTTF* description = CCLabelTTF::create("　　超级炼油厂是每一个战争狂人的标志，机械\n化部队已经整装待发，犯我基地者，虽远必诛！", "Arial",  26,CCSizeZero, kCCTextAlignmentLeft, kCCVerticalTextAlignmentTop);
    description->setAnchorPoint(ccp(0,0.5));
    description->setColor(ccc3(254, 218, 130));
    description->setPosition(ccp(-280,-50));
    updateLayer->addChild(description);
}

BuildingInfo* SuperYouTian::getSuperYouTianInfo() {
    if(buildingInfo == NULL) {
        buildingInfo = BuildingInfo::create();
    }
    return buildingInfo;
}