//
//  BingYing.cpp
//  ww4
//
//  Created by xiao tang on 13-5-2.
//
//

#include "BingYing.h"
#include "NormalState.h"
#include "DefineSet.h"
#include "BeAttackState.h"
#include "StartScene.h"
#include "MyUtil.h"

#define buildCostCount 400
#define updateBaseCostCount 200

MyBuilding* BingYing::createNormal(CCObject* target,int level) {
    CCSprite* byItem = CCSprite::createWithSpriteFrameName("by7.png");
    byItem->setAnchorPoint(ccp(0.5,0.45));
    
    // 普通状态
    
    NormalState* workState = NormalState::create(WorkStateTag, byItem);
    
    TransitionInfo* trainItem =  TransitionInfo::create(CollectTransition,"conscription.png",target,menu_selector(StartScene::toArmyCallBackSimple));
    
    TransitionInfo* infoItem =  TransitionInfo::create(InfoTransition,"info.png",workState,menu_selector(MyState::infoCallBack));
    
    
    workState->addTransition(CollectTransition, WorkStateTag,trainItem);
    workState->addTransition(InfoTransition, WorkStateTag,infoItem);
    
    MyBuilding* BDbuilding = MyBuilding::create(bingyingTag,CCSizeMake(4,4),workState,10);
    
    BDbuilding->setLevel(level);
    BDbuilding->setTag(bingyingTag);
    BDbuilding->setSummaryCount(updateBaseCostCount);
    BDbuilding->resourceTag = oilTag;
    BDbuilding->setUpdateInfo_selector = (SEL_SetUpdateInfo)(&BingYing::setUpdateInfo);
    
    TransitionInfo* updateItem =  TransitionInfo::create(UpdateTransition,"update.png",BDbuilding,menu_selector(MyBuilding::updateLevel));
  
    workState->addTransition(UpdateTransition, WorkStateTag,updateItem);
    BDbuilding->setBuildingName(CCString::create("兵营"),108);
    
    return BDbuilding;
}

MyBattleBuilding* BingYing::createBattle(int level,int stateId) {
    BeAttackState* beAttackState;
    if (stateId == UnfinishedStateTag) {
        beAttackState = BeAttackState::create(UnfinishedStateTag, CCSprite::createWithSpriteFrameName("buildstruct4x4(0).png"), 100);
    } else {
        CCSprite* ytItem = CCSprite::createWithSpriteFrameName("by7.png");
        ytItem->setAnchorPoint(ccp(0.5,0.45));
        beAttackState = BeAttackState::create(BeAttackStateTag, ytItem,byBaseHealth);
    }
    
    MyBattleBuilding* BDbuilding = MyBattleBuilding::create(bingyingTag,CCSizeMake(4,4),beAttackState);
    BDbuilding->setLevel_selector = (SEL_SetBattleLevel)(&BingYing::setBattleLevel);
    BDbuilding->setLevel(level);
    BDbuilding->setTag(bingyingTag);
    BDbuilding->setBuildingName(CCString::create("兵营"),108);
//    BDbuilding->displaySummary();
    return BDbuilding;
}

MyBuildingCard* BingYing::createCard(CCObject* target,SEL_MenuHandler selector) {
    CCSprite* sprite = CCSprite::createWithSpriteFrameName("by7.png");
    sprite->setAnchorPoint(ccp(0.55,0.63));
    sprite->setScale(0.8);
    MyBuildingCard* card = MyBuildingCard::create(sprite,bingyingTag,0,0,oilTag,buildCostCount,"兵  营", target,selector);
    return card;
}

void BingYing::setBattleLevel(int level,GXFSM* fsm) {
    BeAttackState* beAttack = dynamic_cast<BeAttackState*>(fsm->getState(BeAttackStateTag));
    if(beAttack != NULL) {
        float life = MyUtil::getInstance()->updateLevelByRate(0,byBaseHealth, level, 1);
        beAttack->setMaxLife(life);
        beAttack->setLife(life);
    }
}

void BingYing::setUpdateInfo(GXFSMstate* _state,CCLayer* updateLayer)
{
    MyState* state = (MyState*)_state;
    float healthLevelData = MyUtil::getInstance()->updateLevelByRate(0,byBaseHealth, state->building->getLevel(), 1);
    float healthNextData = MyUtil::getInstance()->updateLevelByRate(0,byBaseHealth, state->building->getLevel()+1, 1);
    float healthMaxData = MyUtil::getInstance()->updateLevelByRate(0,byBaseHealth, state->building->getMaxLevel(), 1);
    
    CCSprite* healthIcon = CCSprite::createWithSpriteFrameName("healthIcon.png");
    healthIcon->setPosition(ccp(-68,134));
    updateLayer->addChild(healthIcon);
    
    CCLayer* healthBar = MyUtil::getInstance()->getUpdateBar(healthNextData/healthMaxData, healthLevelData/healthMaxData,"levelBarUp.png");
    healthBar->setPosition(ccp(-40,116));
    
    char str[100] = {0};
    if(state->building->getLevel() < state->building->getMaxLevel()) {
        sprintf(str, "耐久度:%d+%d",(int)healthLevelData,(int)(healthNextData-healthLevelData));
    } else {
        sprintf(str, "耐久度:%d",(int)healthLevelData);
    }
    CCLabelTTF* healthLabel = CCLabelTTF::create(str, "Arial", 24);
    healthLabel->setAnchorPoint(ccp(0,0));
    healthLabel->setColor(ccc3(254, 218, 130));
    healthLabel->setPosition(ccp(-40,126));
    
    
    CCLabelTTF* nameLabel = CCLabelTTF::create("兵  营", "Arial", 24);
    nameLabel->setColor(ccc3(254, 218, 130));
    nameLabel->setAnchorPoint(ccp(0.5,0.5));
    nameLabel->setPosition(ccp(-204,172));
    updateLayer->addChild(nameLabel);
    updateLayer->addChild(healthBar);
    updateLayer->addChild(healthLabel);
    
    CCLabelTTF* description = CCLabelTTF::create("        升级兵营来增加空间，让更多的部队安顿下\n来。兵营可以增加部队的驻扎上限。不断寻找落\n单的部队，组建出一支最强的二战队伍吧！", "Arial",  26,CCSizeZero, kCCTextAlignmentLeft, kCCVerticalTextAlignmentTop);
    description->setAnchorPoint(ccp(0,0.5));
    description->setColor(ccc3(254, 218, 130));
    description->setPosition(ccp(-280,-50));
    updateLayer->addChild(description);
}