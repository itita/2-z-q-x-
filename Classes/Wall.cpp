//
//  Wall.cpp
//  ww4
//
//  Created by xiao tang on 13-5-3.
//
//

#include "Wall.h"
#include "MyContinueTiledSprite.h"
#include "MyContinueBuilding.h"
#include "ContinueState.h"
#include "DefineSet.h"
#include "BeAttackState.h"
#include "StartScene.h"
#include "MyUtil.h"

MyBuilding* Wall::createNormal(CCObject* target,int level) {
    
    MyContinueTiledSprite* wallItem = MyContinueTiledSprite::create(CCString::create("wall1"));
    //    CCSprite* wallItem = CCSprite::createWithSpriteFrameName("wall1c.png");
    wallItem->setAnchorPoint(ccp(0.45,0.37));
    ContinueState* combineState = ContinueState::create(WorkStateTag, wallItem,combineWall5X1Tag);
    
    TransitionInfo* infoItem =  TransitionInfo::create(InfoTransition,"info.png",combineState,menu_selector(MyState::infoCallBack));
    
    
    
#if game_version == soft_version
    MyContinueBuilding* wall1 = MyContinueBuilding::create(wallTag,CCSizeMake(1,1),combineState,level,10);
#endif
#if game_version == hard_version
    MyContinueBuilding* wall1 = MyContinueBuilding::create(wallTag,CCSizeMake(1,1),combineState,level,25);
#endif
    wall1->setLevel(level);
    wall1->setTag(wallTag);
    wall1->setSummaryCount(40);
    wall1->resourceTag = ironTag;
    wall1->setUpdateInfo_selector = (SEL_SetUpdateInfo)(&Wall::setUpdateInfo);
    
    TransitionInfo* updateItem =  TransitionInfo::create(UpdateTransition,"update.png",wall1,menu_selector(MyBuilding::updateLevel));
 
    TransitionInfo* combineItem =  TransitionInfo::create(CombineTransition,"combine.png",combineState,menu_selector(ContinueState::toCombineCallBack));

    
    combineState->addTransition(CombineTransition, WorkStateTag,combineItem);
    combineState->addTransition(UpdateTransition, WorkStateTag,updateItem);
    combineState->addTransition(InfoTransition, WorkStateTag,infoItem);
    
    
    wall1->setBuildingName(CCString::create("路障"),70);
    
    return wall1;
}

MyBattleBuilding* Wall::createBattle(int level,int stateId) {
    
    
    CCSprite* wallItem = MyContinueTiledSprite::create(CCString::create("wall1"));
    wallItem->setAnchorPoint(ccp(0.45,0.37));
    
    BeAttackState* beAttackState = BeAttackState::create(BeAttackStateTag, wallItem,wallBaseHealth);
    beAttackState->addTransition(toRuinsTransition, RuinsStateTag);
    MyBattleBuilding* BDbuilding = MyBattleBuilding::create(wallTag,CCSizeMake(1,1),beAttackState);
    
    BDbuilding->setLevel_selector = (SEL_SetBattleLevel)(&Wall::setBattleLevel);
    BDbuilding->setLevel(level);
    
    BDbuilding->setTag(wallTag);
   
    return BDbuilding;
}

MyBuildingCard* Wall::createCard(CCObject* target,SEL_MenuHandler selector) {
    CCSprite* sprite = CCSprite::createWithSpriteFrameName("wall1lr.png");
    sprite->setAnchorPoint(ccp(0.4,0.8));
    MyBuildingCard* card = MyBuildingCard::create(sprite,wallTag,0,0,ironTag,40,"路  障", target,selector);
    return card;
}

void Wall::setBattleLevel(int level,GXFSM* fsm) {
    BeAttackState* beAttack = dynamic_cast<BeAttackState*>(fsm->getState(BeAttackStateTag));
    if(beAttack != NULL) {
        beAttack->setMaxLife(MyUtil::getInstance()->updateLevelByRate(0,wallBaseHealth, level, wallUpdateHealthRate));
        beAttack->setLife(MyUtil::getInstance()->updateLevelByRate(0,wallBaseHealth, level, wallUpdateHealthRate));
    }
}

void Wall::setUpdateInfo(GXFSMstate* _state,CCLayer* updateLayer) {
    MyState* state = (MyState*)_state;
    float healthLevelData = MyUtil::getInstance()->updateLevelByRate(0,wallBaseHealth, state->building->getLevel(), 1);
    float healthNextData = MyUtil::getInstance()->updateLevelByRate(0,wallBaseHealth, state->building->getLevel()+1, 1);
    float healthMaxData = MyUtil::getInstance()->updateLevelByRate(0,wallBaseHealth, state->building->getMaxLevel(), 1);
    
    CCSprite* healthIcon = CCSprite::createWithSpriteFrameName("healthIcon.png");
    healthIcon->setPosition(ccp(-64,98));
    updateLayer->addChild(healthIcon);
    CCLayer* bar = MyUtil::getInstance()->getUpdateBar(healthNextData/healthMaxData, healthLevelData/healthMaxData, "levelBarUp.png");
    bar->setPosition(ccp(-40,80));
    updateLayer->addChild(bar);
    
    char str[100] = {0};
    if(state->building->getLevel() < state->building->getMaxLevel()) {
        sprintf(str, "耐久度:%d+%d",(int)healthLevelData,(int)(healthNextData-healthLevelData));
    } else {
        sprintf(str, "耐久度:%d",(int)healthLevelData);
    }
    CCLabelTTF* healthLabel = CCLabelTTF::create(str, "Arial", 24);
    healthLabel->setAnchorPoint(ccp(0,0));
    healthLabel->setColor(ccc3(254, 218, 130));
    healthLabel->setPosition(ccp(-40,90));
    
    
    CCLabelTTF* description = CCLabelTTF::create("    路障作为一种防御建筑虽然并不具有攻击力,\n但是可以有效的阻截敌军对建筑的直接攻击", "Arial", 26,CCSizeZero,kCCTextAlignmentLeft,kCCVerticalTextAlignmentTop);
    description->setAnchorPoint(ccp(0,0.5));
    description->setColor(ccc3(254, 218, 130));
    description->setPosition(ccp(-280,-30));
    
    
    CCLabelTTF* nameLabel = CCLabelTTF::create("路  障", "Arial", 24);
    nameLabel->setAnchorPoint(ccp(0.5,0.5));
    nameLabel->setPosition(ccp(-204,172));
    
    updateLayer->addChild(nameLabel);
    updateLayer->addChild(healthLabel);
    updateLayer->addChild(description);
   
}