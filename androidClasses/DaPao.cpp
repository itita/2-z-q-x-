//
//  DaPao.cpp
//  ww4
//
//  Created by xiao tang on 13-5-3.
//
//

#include "DaPao.h"
#include "DefendInCreateState.h"
#include "DefineSet.h"
#include "AoeDefendState.h"
#include "GXUtil.h"
#include "StartScene.h"
#include "MyUtil.h"


MyBuilding* DaPao::createNormal(cocos2d::CCObject *target,int level) {
    
    
    CCSprite* byItem;
    
    byItem = NULL;
    
    DefendInCreateState* workState = DefendInCreateState::create(WorkStateTag, byItem);
    
    TransitionInfo* infoItem =  TransitionInfo::create(InfoTransition,"info.png",workState,menu_selector(MyState::infoCallBack));
   
    
    MyBuilding* BDbuilding;
        
#if game_version == soft_version
    BDbuilding = MyBuilding::create(dapaoTag,CCSizeMake(4,4),workState,level,10);
#endif
#if game_version == hard_version
    BDbuilding = MyBuilding::create(dapaoTag,CCSizeMake(3,3),workState,25);
#endif
    BDbuilding->setLevel_selector = (SEL_SetLevel)(&DaPao::setNormalLevel);
    BDbuilding->setLevel(level);
    BDbuilding->setTag(dapaoTag);
    BDbuilding->setBuildingName(CCString::create("反坦克炮"),88);
    BDbuilding->setUpdateInfo_selector = (SEL_SetUpdateInfo)(&DaPao::setUpdateInfo);
    BDbuilding->setSummaryCount(500);
    BDbuilding->resourceTag = ironTag;
    
    
    
    TransitionInfo* updateItem =  TransitionInfo::create(UpdateTransition,"update.png",BDbuilding,menu_selector(MyBuilding::updateLevel));
    

    
    workState->addTransition(UpdateTransition, WorkStateTag,updateItem);
    workState->addTransition(InfoTransition, WorkStateTag,infoItem);
    
    return BDbuilding;
}

void DaPao::setNormalLevel(int level,GXFSM* fsm) {
    DefendInCreateState* defendState = dynamic_cast<DefendInCreateState*>(fsm->getState(WorkStateTag));
    if (defendState != NULL) {
        float rangeLevelData = MyUtil::getInstance()->updateLevelByCount(dpBaseRange,level, dpUpdateRangeCount);
        defendState->setAttackRange(rangeLevelData);
    }
}

MyBuilding* DaPao::createReady(cocos2d::CCObject *target,int level) {
    
    CCSprite* byItem;
    
    CCSprite* grayBy = CCSprite::createWithSpriteFrameName("antiTankld.png");
    grayBy->setColor(ccGRAY);
    byItem = CCSprite::createWithSpriteFrameName("antiTankld.png");
    byItem->setAnchorPoint(ccp(0.5,0.5));
    CCSprite* zhendi = CCSprite::createWithSpriteFrameName("position.png");
    zhendi->setPosition(ccp(byItem->getContentSize().width/2,byItem->getContentSize().height/2));
    byItem->addChild(zhendi,-1);
    
    DefendInCreateState* workState = DefendInCreateState::create(WorkStateTag, byItem);
//    workState->setAttackRange(dpBaseRange);
    TransitionInfo* infoItem =  TransitionInfo::create(InfoTransition,"info.png",workState,menu_selector(MyState::infoCallBack));
    
    
    MyBuilding* BDbuilding;
    
#if game_version == soft_version
    BDbuilding = MyBuilding::create(dapaoTag,CCSizeMake(4,4),workState,level,10);
#endif
#if game_version == hard_version
    BDbuilding = MyBuilding::create(dapaoTag,CCSizeMake(3,3),workState,25);
#endif
    BDbuilding->setLevel_selector = (SEL_SetLevel)(&DaPao::setNormalLevel);
    BDbuilding->setLevel(level);
    BDbuilding->setTag(dapaoTag);
    BDbuilding->setBuildingName(CCString::create("反坦克炮"),88);
    BDbuilding->setUpdateInfo_selector = (SEL_SetUpdateInfo)(&DaPao::setUpdateInfo);
    
    BDbuilding->setSummaryCount(500);
    BDbuilding->resourceTag = ironTag;
    
    TransitionInfo* updateItem =  TransitionInfo::create(UpdateTransition,"update.png",BDbuilding,menu_selector(MyBuilding::updateLevel));
    
    
    workState->addTransition(UpdateTransition, WorkStateTag,updateItem);
    workState->addTransition(InfoTransition, WorkStateTag,infoItem);
    
    return BDbuilding;
}

MyBattleBuilding* DaPao::createBattle(int level,int stateId) {
    
    BeAttackState* beAttack;
    
    if (stateId == UnfinishedStateTag) {
        CCSprite* unfinishItem = CCSprite::createWithSpriteFrameName("buildstruct2x2(0).png");
        beAttack = BeAttackState::create(UnfinishedStateTag, unfinishItem, 50);
    } else {
        AoeDefendState* defender = AoeDefendState::create(DefendStateTag, NULL,CCString::create("antiTank"),dpBaseHealth,dpBaseRange,dpBaseDamage,dpBaseSplash,1.3,10);
        
        defender->setAnimateCreator((SEL_FXCreator)(&DaPao::getFireAnimate));
        beAttack = defender;
    }
    
    MyBattleBuilding* dapao = MyBattleBuilding::create(dapaoTag,CCSizeMake(3,3),beAttack);
    dapao->setLevel_selector = (SEL_SetBattleLevel)(&DaPao::setBattleLevel);
    dapao->setLevel(level);

   
    dapao->setTag(dapaoTag);
    dapao->setBuildingName(CCString::create("反坦克炮"),70);
//    dapao->displaySummary();
   
    
    return dapao;
}

MyBuildingCard* DaPao::createCard(CCObject* target,SEL_MenuHandler selector) {
    CCSprite* sprite = CCSprite::createWithSpriteFrameName("antiTankld.png");
    //        sprite->setAnchorPoint(ccp(0.5,0.4));
    MyBuildingCard* card = MyBuildingCard::create(sprite,dapaoTag,0,0,ironTag,300,4,"反坦克炮", target,selector);
    CCSprite* zhendi = CCSprite::createWithSpriteFrameName("position.png");
    zhendi->setPosition(ccp(sprite->getContentSize().width/2,sprite->getContentSize().height/2));
    sprite->addChild(zhendi,-1);
    return card;
}

void DaPao::setBattleLevel(int level,GXFSM* fsm) {
    AoeDefendState* defendstate = dynamic_cast<AoeDefendState*>(fsm->getState(DefendStateTag));
    if(defendstate != NULL) {
        defendstate->damage = MyUtil::getInstance()->updateLevelByRate(0,dpBaseDamage, level, dpUpdateDamageRate);
        defendstate->attackRange = MyUtil::getInstance()->updateLevelByCount(dpBaseRange, level, dpUpdateRangeCount);
        //            CCLog("level:%d,range:%f",building->getLevel(),defendstate->attackRange);
    }
}

void DaPao::setUpdateInfo(GXFSMstate* _state,CCLayer* updateLayer) {
    MyState* state = (MyState*)_state;
    float attackLevelData = MyUtil::getInstance()->updateLevelByRate(0,dpBaseDamage, state->building->getLevel(), dpUpdateDamageRate);
    float attackNextData = MyUtil::getInstance()->updateLevelByRate(0,dpBaseDamage, state->building->getLevel()+1, dpUpdateDamageRate);
    float attackMaxData = MyUtil::getInstance()->updateLevelByRate(0,dpBaseDamage, state->building->getMaxLevel(), dpUpdateDamageRate);
    
    CCSprite* attackIcon = CCSprite::createWithSpriteFrameName("damageIcon.png");
    attackIcon->setPosition(ccp(-68,134));
    updateLayer->addChild(attackIcon);
    
    CCLayer* attackBar = MyUtil::getInstance()->getUpdateBar(attackNextData/attackMaxData, attackLevelData/attackMaxData,"levelBarUp.png");
    attackBar->setPosition(ccp(-40,116));
    
    
    char str[100] = {0};
    if (state->building->getLevel() <state->building->getMaxLevel()) {
        sprintf(str, "每秒造成伤害:%d+%d",(int)(attackLevelData),(int)(attackNextData-attackLevelData));
    } else {
        sprintf(str, "每秒造成伤害:%d",(int)(attackLevelData));
    }
    
    CCLabelTTF* damageLabel = CCLabelTTF::create(str, "Arial", 24);
    damageLabel->setAnchorPoint(ccp(0,0));
    damageLabel->setColor(ccc3(254, 218, 130));
    damageLabel->setPosition(ccp(-40,126));
    updateLayer->addChild(attackBar);
    updateLayer->addChild(damageLabel);
    
    float rangeLevelData = MyUtil::getInstance()->updateLevelByCount(dpBaseRange, state->building->getLevel(), dpUpdateRangeCount);
    float rangeNextData = MyUtil::getInstance()->updateLevelByCount(dpBaseRange, state->building->getLevel()+1, dpUpdateRangeCount);
    float rangeMaxData = MyUtil::getInstance()->updateLevelByCount(dpBaseRange, state->building->getMaxLevel(), dpUpdateRangeCount);
    
    
    CCSprite* rangeIcon = CCSprite::createWithSpriteFrameName("attackRangeIcon.png");
    rangeIcon->setPosition(ccp(-68,80));
    updateLayer->addChild(rangeIcon);
    
    CCLayer* rangeBar = MyUtil::getInstance()->getUpdateBar(rangeNextData/rangeMaxData, rangeLevelData/rangeMaxData,"levelBarUp.png");
    
    rangeBar->setPosition(ccp(-40,62));
    
    if (state->building->getLevel() < state->building->getMaxLevel()) {
        sprintf(str, "攻击范围:%d格+0.5格",(int)(rangeLevelData));
    } else {
        sprintf(str, "攻击范围:%d格",(int)(rangeLevelData));
    }
    
    CCLabelTTF* rangeLabel = CCLabelTTF::create(str, "Arial", 24);
    rangeLabel->setAnchorPoint(ccp(0,0));
    rangeLabel->setColor(ccc3(254, 218, 130));
    rangeLabel->setPosition(ccp(-40,72));
    updateLayer->addChild(rangeBar);
    updateLayer->addChild(rangeLabel);
    
    CCLabelTTF* nameLabel = CCLabelTTF::create("反坦克炮", "Arial", 24);
    nameLabel->setColor(ccc3(254, 218, 130));
    nameLabel->setAnchorPoint(ccp(0.5,0.5));
    nameLabel->setPosition(ccp(-204,172));
    updateLayer->addChild(nameLabel);
    
    //        updateLayer->addChild(rangeLabel);
    sprintf(str, "耐久度:%d",dpBaseHealth);
    CCLabelTTF* description1 = CCLabelTTF::create(str, "Arial",  26);
    description1->setAnchorPoint(ccp(0,0.5));
    description1->setColor(ccc3(254, 218, 130));
    description1->setPosition(ccp(-110,-6));
    updateLayer->addChild(description1);
    
    CCSprite* underline1 = CCSprite::createWithSpriteFrameName("underline.png");
    underline1->setPosition(ccp(0,-22));
    updateLayer->addChild(underline1);
    
    
    sprintf(str, "攻击溅射范围:%d格",dpBaseSplash);
    CCLabelTTF* description2 = CCLabelTTF::create(str, "Arial",  26);
    description2->setAnchorPoint(ccp(0,0.5));
    description2->setColor(ccc3(254, 218, 130));
    description2->setPosition(ccp(-110,-42));
    updateLayer->addChild(description2);
    
    CCSprite* underline2 = CCSprite::createWithSpriteFrameName("underline.png");
    underline2->setPosition(ccp(0,-58));
    updateLayer->addChild(underline2);
    
    
    CCLabelTTF* description3 = CCLabelTTF::create("目标部队:地面", "Arial",  26);
    description3->setAnchorPoint(ccp(0,0.5));
    description3->setColor(ccc3(254, 218, 130));
    description3->setPosition(ccp(-110,-78));
    updateLayer->addChild(description3);
    
    CCSprite* underline3 = CCSprite::createWithSpriteFrameName("underline.png");
    underline3->setPosition(ccp(0,-94));
    updateLayer->addChild(underline3);

}

CCAnimate* DaPao::getFireAnimate(int dir) {

    if (dir == 0) {
        
        GXFX* fx0 = GXFX::create(GXUtil::initAction("firelightld", 0.12,false), 0,0);
        fx0->setPosition(ccp(27,53));
        CCArray* ani0 = CCArray::create();
        ani0->addObject(fx0);
        return GXAnimateWithFx::create(GXUtil::initAction("antiTankfld", 0.12,true),ani0);
        
    } else if(dir == 1) {
        GXFX* fx1 = GXFX::create(GXUtil::initAction("firelightd", 0.12,false), 0,0);
        fx1->setPosition(ccp(89,33));
        CCArray* ani1 = CCArray::create();
        ani1->addObject(fx1);
        return GXAnimateWithFx::create(GXUtil::initAction("antiTankfd", 0.12,true),ani1);
    } else if(dir == 2) {
        GXFX* fx2 = GXFX::create(GXUtil::initAction("firelightrd", 0.12,false), 0,0);
        fx2->setPosition(ccp(150,55));
        CCArray* ani2 = CCArray::create();
        ani2->addObject(fx2);
        return GXAnimateWithFx::create(GXUtil::initAction("antiTankfrd", 0.12,true),ani2);
    
    } else if(dir == 3) {
        GXFX* fx3 = GXFX::create(GXUtil::initAction("firelightr", 0.12,false), 0,0);
        fx3->setPosition(ccp(172,96));
        CCArray* ani3 = CCArray::create();
        ani3->addObject(fx3);
        return GXAnimateWithFx::create(GXUtil::initAction("antiTankfr", 0.12,true),ani3);

    } else if(dir == 4) {
    
        GXFX* fx4 = GXFX::create(GXUtil::initAction("firelightru", 0.03,false), 0,0);
        fx4->setPosition(ccp(149,136));
        CCArray* ani4 = CCArray::create();
        ani4->addObject(fx4);
        return GXAnimateWithFx::create(GXUtil::initAction("antiTankfru", 0.12,true),ani4);

    } else if(dir == 5) {
        GXFX* fx5 = GXFX::create(GXUtil::initAction("firelightu", 0.03,false), 0,0);
        fx5->setPosition(ccp(87,160));
        CCArray* ani5 = CCArray::create();
        ani5->addObject(fx5);
        return GXAnimateWithFx::create(GXUtil::initAction("antiTankfu", 0.12,true),ani5);
    
    } else if(dir == 6) {
        GXFX* fx6 = GXFX::create(GXUtil::initAction("firelightlu", 0.03,false), 0,0);
        fx6->setPosition(ccp(26,136));
        CCArray* ani6 = CCArray::create();
        ani6->addObject(fx6);
        return GXAnimateWithFx::create(GXUtil::initAction("antiTankflu", 0.12,true),ani6);
    
    } else if(dir == 7) {
        GXFX* fx7 = GXFX::create(GXUtil::initAction("firelightl", 0.03,false), 0,0);
        fx7->setPosition(ccp(1,95));
        CCArray* ani7 = CCArray::create();
        ani7->addObject(fx7);
        return GXAnimateWithFx::create(GXUtil::initAction("antiTankfl", 0.12,true),ani7);
    }
    return NULL;
}