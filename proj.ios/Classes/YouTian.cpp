//
//  YouTian.cpp
//  ww4
//
//  Created by xiao tang on 13-5-3.
//
//

#include "YouTian.h"
#include "CollectState.h"
#include "DefineSet.h"
#include "ResourceBeAttackState.h"
#include "StartScene.h"
#include "MyUtil.h"

BuildingInfo* YouTian::buildingInfo = NULL;

MyBuilding* YouTian::createNormal(CCObject* target,int level,float ori,long dt) {
    
    CCSprite* byItem = CCSprite::createWithSpriteFrameName("yt2.png");
    byItem->setAnchorPoint(ccp(0.5,0.35));
    
    CollectState* workState = CollectState::create(WorkStateTag, byItem,ytBaseColletSpeed,ytBaseColletMaxCapacity,oilTag);
    TransitionInfo* collectItem =  TransitionInfo::create(CollectTransition,"collect.png",workState,menu_selector(CollectState::doCollectPlaysfx));
    
    TransitionInfo* infoItem =  TransitionInfo::create(InfoTransition,"info.png",workState,menu_selector(MyState::infoCallBack));
#if game_version == soft_version
    MyBuilding* BDbuilding = MyBuilding::create(youtianTag,CCSizeMake(4,4),workState,level,10);
#endif
#if game_version == hard_version
    MyBuilding* BDbuilding = MyBuilding::create(youtianTag,CCSizeMake(3,3),workState,10);
#endif
    BDbuilding->setLevel_selector = (SEL_SetLevel)(&YouTian::setNormalLevel);
    BDbuilding->setLevel(level);
    BDbuilding->setUpdateInfo_selector = (SEL_SetUpdateInfo)(&YouTian::setUpdateInfo);
    
    BDbuilding->setSummaryCount(200);
    BDbuilding->resourceTag = ironTag;
    
    TransitionInfo* updateItem =  TransitionInfo::create(UpdateTransition, "update.png",BDbuilding,menu_selector(MyBuilding::updateLevel));;
    
    
    workState->addTransition(UpdateTransition, WorkStateTag,updateItem);
    workState->addTransition(CollectTransition, WorkStateTag,collectItem);
    workState->addTransition(InfoTransition, WorkStateTag,infoItem);
    
    BDbuilding->setTag(youtianTag);
    BDbuilding->setBuildingName(CCString::create("炼油厂"),108);
    BDbuilding->setUserData(getYouTianInfo());
    getYouTianInfo()->count++;
    workState->setCapacity(ori,dt);
    BDbuilding->setDoStateInterval(1);
    
    return BDbuilding;
}

MyBattleBuilding* YouTian::createBattle(int level,int stateId,float ori,float rate) {
    CCSprite* bdItem;
    BeAttackState* beAttackState = NULL;

    if (stateId == UnfinishedStateTag) {
        CCSprite* unfinishItem = CCSprite::createWithSpriteFrameName("buildstruct3x3(0).png");
        beAttackState = BeAttackState::create(UnfinishedStateTag, unfinishItem, 100);
    } else {
        bdItem = CCSprite::createWithSpriteFrameName("yt2.png");
        bdItem->setAnchorPoint(ccp(0.5,0.35));
        beAttackState = ResourceBeAttackState::create(BeAttackStateTag, bdItem,ytBaseHealth,ytBaseColletSpeed,ytBaseColletMaxCapacity,oilTag);
    }
    
    MyBattleBuilding* BDbuilding;
    
#if game_version == soft_version
        BDbuilding = MyBattleBuilding::create(youtianTag,CCSizeMake(4,4),beAttackState,level);
#endif
#if game_version == hard_version
        BDbuilding = MyBattleBuilding::create(youtianTag,CCSizeMake(3,3),beAttackState);
#endif
    BDbuilding->setLevel_selector = (SEL_SetBattleLevel)(&YouTian::setBattleLevel);
    BDbuilding->setLevel(level);
    
    BDbuilding->setBuildingName(CCString::create("炼油厂"),108);
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

MyBuildingCard* YouTian::createCard(CCObject* target,SEL_MenuHandler selector) {
    CCSprite* sprite = CCSprite::createWithSpriteFrameName("yt2.png");
    sprite->setScale(0.8);
    sprite->setAnchorPoint(ccp(0.5,0.6));
    MyBuildingCard* card = MyBuildingCard::create(sprite,youtianTag,0,0,ironTag,400,"炼油厂", target,selector);
    return card;
}

void YouTian::setNormalLevel(int level,GXFSM* fsm) {

    CollectState* collectState = dynamic_cast<CollectState*>(fsm->getState(WorkStateTag));
    if (collectState != NULL) {
        collectState->setMaxCapacity(MyUtil::getInstance()->updateLevelByRate(0,collectState->getBaseMaxCapacity(), level, ytUpdateColletMaxCapacityRate));
        collectState->setOutputPsecond(MyUtil::getInstance()->updateLevelByRate(0,collectState->getBaseOutputPsecond(), level, ytUpdateColletSpeedRate));
    }

}

void YouTian::setBattleLevel(int level,GXFSM* fsm) {
    ResourceBeAttackState* beAttack = dynamic_cast<ResourceBeAttackState*>(fsm->getState(BeAttackStateTag));
    if(beAttack != NULL) {
        beAttack->setMaxCapacity(MyUtil::getInstance()->updateLevelByRate(0,beAttack->getBaseMaxCapacity(), level, ytUpdateColletMaxCapacityRate));
        beAttack->setOutputPsecond(MyUtil::getInstance()->updateLevelByRate(0,beAttack->getBaseOutputPsecond(), level, ytUpdateColletSpeedRate));
        float life = MyUtil::getInstance()->updateLevelByRate(0,ytBaseHealth, level, ytUpdateHealthRate);
        beAttack->setMaxLife(life);
        beAttack->setLife(life);
    }
}

void YouTian::setUpdateInfo(GXFSMstate* _state,CCLayer* updateLayer) {
    
    MyState* state = (MyState*)_state;
    float healthLevelData = MyUtil::getInstance()->updateLevelByRate(0,ytBaseHealth, state->building->getLevel(), ytUpdateHealthRate);
    float healthNextData = MyUtil::getInstance()->updateLevelByRate(0,ytBaseHealth, state->building->getLevel()+1, ytUpdateHealthRate);
    float healthMaxData = MyUtil::getInstance()->updateLevelByRate(0,ytBaseHealth, state->building->getMaxLevel(), ytUpdateHealthRate);
    
    CCSprite* healthIcon = CCSprite::createWithSpriteFrameName("healthIcon.png");
    healthIcon->setPosition(ccp(-68,160));
    updateLayer->addChild(healthIcon);
    CCLayer* healthBar = MyUtil::getInstance()->getUpdateBar(healthNextData/healthMaxData, healthLevelData/healthMaxData,"levelBarUp.png");
    healthBar->setPosition(ccp(-40,142));
    
    
    char str[100] = {0};
    if(state->building->getLevel() < state->building->getMaxLevel()) {
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
    
    
    float capacityLevelData = MyUtil::getInstance()->updateLevelByRate(0,((CollectState*)state)->getBaseMaxCapacity(), state->building->getLevel(), ytUpdateColletMaxCapacityRate);
    float capacityNextData = MyUtil::getInstance()->updateLevelByRate(0,((CollectState*)state)->getBaseMaxCapacity(), state->building->getLevel()+1, ytUpdateColletMaxCapacityRate);
    float capacityMaxData = MyUtil::getInstance()->updateLevelByRate(0,((CollectState*)state)->getBaseMaxCapacity(), state->building->getMaxLevel(), ytUpdateColletMaxCapacityRate);
    
    CCSprite* capacityIcon = CCSprite::createWithSpriteFrameName("oilCapacity.png");
    capacityIcon->setPosition(ccp(-68,106));
    updateLayer->addChild(capacityIcon);
    CCLayer* capacityBar = MyUtil::getInstance()->getUpdateBar(capacityNextData/capacityMaxData, capacityLevelData/capacityMaxData,"levelBarUp.png");
    
    capacityBar->setPosition(ccp(-40,88));
    
    if(state->building->getLevel() < state->building->getMaxLevel()) {
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
    
    float speedLevelData = MyUtil::getInstance()->updateLevelByRate(0,((CollectState*)state)->getBaseOutputPsecond(), state->building->getLevel(), ytUpdateColletSpeedRate);
    float speedNextData = MyUtil::getInstance()->updateLevelByRate(0,((CollectState*)state)->getBaseOutputPsecond(), state->building->getLevel()+1, ytUpdateColletSpeedRate);
    float speedMaxData = MyUtil::getInstance()->updateLevelByRate(0,((CollectState*)state)->getBaseOutputPsecond(), state->building->getMaxLevel(), ytUpdateColletSpeedRate);
    
    CCSprite* speedIcon = CCSprite::createWithSpriteFrameName("OilcollectSpeedIcon.png");
    speedIcon->setPosition(ccp(-68,48));
    updateLayer->addChild(speedIcon);
    
    CCLayer* speedBar = MyUtil::getInstance()->getUpdateBar(speedNextData/speedMaxData, speedLevelData/speedMaxData,"levelBarUp.png");
    
    speedBar->setPosition(ccp(-40,30));
    
    if(state->building->getLevel() < state->building->getMaxLevel()) {
        sprintf(str, "每小时采集数量:%d+%d",(int)(speedLevelData*3600),(int)((speedNextData-speedLevelData)*3600));
    } else {
        sprintf(str, "每小时采集数量:%d",(int)(speedLevelData*3600));
    }
    CCLabelTTF* speedLabel = CCLabelTTF::create(str, "Arial", 24);
    speedLabel->setAnchorPoint(ccp(0,0));
    speedLabel->setColor(ccc3(254, 218, 130));
    speedLabel->setPosition(ccp(-40,40));
    
    
    CCLabelTTF* nameLabel = CCLabelTTF::create("炼油厂", "Arial", 24);
    nameLabel->setColor(ccc3(254, 218, 130));
    nameLabel->setAnchorPoint(ccp(0.5,0.5));
    nameLabel->setPosition(ccp(-204,172));
    updateLayer->addChild(nameLabel);
    updateLayer->addChild(speedBar);
    updateLayer->addChild(speedLabel);
    
    CCLabelTTF* description = CCLabelTTF::create("        石油是重要的军需物资，关于征战的任何方\n面都离不开石油，升级油泵来提高石油产量！这\n就可以不断的征战，征战，征战！", "Arial",  26,CCSizeZero, kCCTextAlignmentLeft, kCCVerticalTextAlignmentTop);
    description->setAnchorPoint(ccp(0,0.5));
    description->setColor(ccc3(254, 218, 130));
    description->setPosition(ccp(-280,-50));
    updateLayer->addChild(description);
}

BuildingInfo* YouTian::getYouTianInfo() {
    if(buildingInfo == NULL) {
        buildingInfo = BuildingInfo::create();
    }
    return buildingInfo;
}