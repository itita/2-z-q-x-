//
//  Jammer.cpp
//  ww4
//
//  Created by xiao tang on 13-9-23.
//
//

#include "Jammer.h"
#include "DefendInCreateState.h"
#include "DefineSet.h"
#include "JammerDefend.h"
#include "StartScene.h"
#include "MyUtil.h"

#define jammerMaxLevel 25
#define jammerUnlockLevel 25

#define jammerBaseHealth 100
#define jammerHealthUpdateRate 0.65
#define jammerSfxName "sfx_fizz.mp3"

#define jammerBaseControlCount 1
#define jammerControlCountUpdateCount 0.17

#define jammerBaseAttackRange 9
#define jammerAttackRangeUpdateRate 0.22

#define jammerConstructCost 100000
#define jammerUpdateSummary 600

BuildingInfo* Jammer::buildingInfo = NULL;

MyBuilding* Jammer::createNormal(CCObject* target,int level) {
    CCSprite* byItem = CCSprite::createWithSpriteFrameName("jammer.png");
    byItem->setAnchorPoint(ccp(0.41,0.18));
    // 普通状态
    
    DefendInCreateState* workState = DefendInCreateState::create(WorkStateTag, byItem);
//    workState->setAttackRange(12);
    
    
    TransitionInfo* infoItem =  TransitionInfo::create(InfoTransition,"info.png",workState,menu_selector(MyState::infoCallBack));
    
    
    
    MyBuilding* BDbuilding = MyBuilding::create(JammerTag,CCSizeMake(2,2),workState,jammerMaxLevel);
    BDbuilding->setLevel_selector = (SEL_SetLevel)(&Jammer::setNormalLevel);
    BDbuilding->setLevel(level);
    BDbuilding->setSummaryCount(jammerUpdateSummary);
    BDbuilding->resourceTag = ironTag;
    BDbuilding->setUpdateInfo_selector = (SEL_SetUpdateInfo)(Jammer::setUpdateInfo);
    
    TransitionInfo* updateItem =  TransitionInfo::create(UpdateTransition,"update.png",BDbuilding,menu_selector(MyBuilding::updateLevel));
    
    workState->addTransition(UpdateTransition, WorkStateTag,updateItem);
    workState->addTransition(InfoTransition, WorkStateTag,infoItem);
    
    BDbuilding->setBuildingName(CCString::create("干扰发射器"),160);
    getJammerInfo()->count++;
    BDbuilding->setUserData(getJammerInfo());
    
    return BDbuilding;
}

MyBattleBuilding* Jammer::createBattle(int level,int stateId,float arg0) {
    BeAttackState* beAttack;
    
    if(stateId != UnfinishedStateTag) {
        CCSprite* dbItem = CCSprite::createWithSpriteFrameName("jammer.png");
        dbItem->setAnchorPoint(ccp(0.41,0.18));
        
//        float attackRateLevelData = MyUtil::getInstance()->updateLevelByCount(dbBaseAttackRate, level, dbUpdateAttackRateRate);
        
        JammerDefend* defender = JammerDefend::create(DefendStateTag, dbItem,CCString::create(jammerSfxName),jammerBaseHealth,jammerBaseAttackRange,0,0.5,jammerBaseControlCount,1000);
        
//        defender->setAnimateCreator((SEL_FXCreator)(&DiaoBao::getFireAnimate));
        beAttack = defender;
    } else {
        CCSprite* unfinishItem = CCSprite::createWithSpriteFrameName("buildstruct2x2(0).png");
        beAttack = BeAttackState::create(UnfinishedStateTag, unfinishItem, 100);
    }
    
    
    
    
#if game_version == soft_version
    MyBattleBuilding* diaobao = MyBattleBuilding::create(JammerTag,CCSizeMake(3,3),beAttack,level);
#endif
#if game_version == hard_version
    MyBattleBuilding* diaobao = MyBattleBuilding::create(JammerTag,CCSizeMake(2,2),beAttack);
#endif
//    diaobao->setLevel_selector = (SEL_SetBattleLevel)(&DiaoBao::setBattleLevel);
    
    diaobao->setLevel_selector = (SEL_SetBattleLevel)(&Jammer::setBattleLevel);
    diaobao->setLevel(level);
    
    diaobao->setTag(JammerTag);
    diaobao->setBuildingName(CCString::create("干扰发射器"),160);
    //    diaobao->displaySummary();
    
    return diaobao;
}

void Jammer::setNormalLevel(int level,GXFSM* fsm) {
    DefendInCreateState* defendState = dynamic_cast<DefendInCreateState*>(fsm->getState(WorkStateTag));
    if (defendState != NULL) {
        float rangeLevelData = MyUtil::getInstance()->updateLevelByCount(jammerBaseAttackRange,level, jammerAttackRangeUpdateRate);
        defendState->setAttackRange(rangeLevelData);
    }
}

void Jammer::setBattleLevel(int level,GXFSM* fsm) {
    JammerDefend* defendstate = dynamic_cast<JammerDefend*>(fsm->getState(DefendStateTag));
    if(defendstate != NULL) {
        defendstate->setMaxTarget(MyUtil::getInstance()->updateLevelByCount(jammerBaseControlCount, level, jammerControlCountUpdateCount));
        defendstate->attackRange = MyUtil::getInstance()->updateLevelByCount(jammerBaseAttackRange, level, jammerAttackRangeUpdateRate);
        float life = MyUtil::getInstance()->updateLevelByRate(0,jammerBaseHealth, level, jammerHealthUpdateRate);
        defendstate->setMaxLife(life);
        defendstate->setLife(life);
        
        //            CCLog("level:%d,range:%f",building->getLevel(),defendstate->attackRange);
    }
}

MyBuildingCard* Jammer::createCard(CCObject* target,SEL_MenuHandler selector) {
    CCSprite* sprite = CCSprite::createWithSpriteFrameName("jammer.png");
    sprite->setAnchorPoint(ccp(0.41,0.63));
    sprite->setScale(0.8);
    MyBuildingCard* card = MyBuildingCard::create(sprite,JammerTag,JammerMaxCount,getJammerInfo()->count,ironTag,jammerConstructCost,jammerUnlockLevel,"干扰发射器", target,selector);
    return card;
}

void Jammer::setUpdateInfo(GXFSMstate* _state,CCLayer* updateLayer)
{
    MyState* state = (MyState*)_state;
    
    char str[100] = {0};
    float healthLevelData = MyUtil::getInstance()->updateLevelByRate(0,jammerBaseHealth, state->building->getLevel(), jammerHealthUpdateRate);
    float healthNextData = MyUtil::getInstance()->updateLevelByRate(0,jammerBaseHealth, state->building->getLevel()+1, jammerHealthUpdateRate);
    float healthMaxData = MyUtil::getInstance()->updateLevelByRate(0,jammerBaseHealth, state->building->getMaxLevel(), jammerHealthUpdateRate);
    
    CCSprite* healthIcon = CCSprite::createWithSpriteFrameName("healthIcon.png");
    healthIcon->setPosition(ccp(-68,160));
    updateLayer->addChild(healthIcon);
    
    CCLayer* healthBar = MyUtil::getInstance()->getUpdateBar(healthNextData/healthMaxData, healthLevelData/healthMaxData,"levelBarUp.png");
    healthBar->setPosition(ccp(-40,142));
    
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
    
    float controlCountLevelData = MyUtil::getInstance()->updateLevelByCount(jammerBaseControlCount, state->building->getLevel(), jammerControlCountUpdateCount);
    float controlCountNextData = MyUtil::getInstance()->updateLevelByCount(jammerBaseControlCount, state->building->getLevel()+1, jammerControlCountUpdateCount);
    float controlCountMaxData = MyUtil::getInstance()->updateLevelByCount(jammerBaseControlCount, state->building->getMaxLevel(), jammerControlCountUpdateCount);
    CCSprite* attackIcon = CCSprite::createWithSpriteFrameName("electrification.png");
    attackIcon->setPosition(ccp(-68,106));
    updateLayer->addChild(attackIcon);
    
    CCLayer* controlCountBar = MyUtil::getInstance()->getUpdateBar(controlCountNextData/controlCountMaxData, controlCountLevelData/controlCountMaxData,"levelBarUp.png");
    controlCountBar->setPosition(ccp(-40,88));
    
    if(state->building->getLevel() < state->building->getMaxLevel()) {
        sprintf(str, "控制部队数量:%d+%d",(int)(controlCountLevelData),(int)(controlCountNextData - controlCountLevelData));
    } else {
        sprintf(str, "控制部队数量:%d",(int)(controlCountLevelData));
    }
    CCLabelTTF* damageLabel = CCLabelTTF::create(str, "Arial", 24);
    damageLabel->setAnchorPoint(ccp(0,0));
    damageLabel->setColor(ccc3(254, 218, 130));
    damageLabel->setPosition(ccp(-40,98));
    updateLayer->addChild(controlCountBar);
    updateLayer->addChild(damageLabel);
    
    float rangeLevelData = MyUtil::getInstance()->updateLevelByCount(jammerBaseAttackRange, state->building->getLevel(), jammerAttackRangeUpdateRate);
    float rangeNextData = MyUtil::getInstance()->updateLevelByCount(jammerBaseAttackRange, state->building->getLevel()+1, jammerAttackRangeUpdateRate);
    float rangeMaxData = MyUtil::getInstance()->updateLevelByCount(jammerBaseAttackRange, state->building->getMaxLevel(), jammerAttackRangeUpdateRate);
    
    
    CCSprite* rangeIcon = CCSprite::createWithSpriteFrameName("attackRangeIcon.png");
    rangeIcon->setPosition(ccp(-68,38));
    updateLayer->addChild(rangeIcon);
    
    CCLayer* rangeBar = MyUtil::getInstance()->getUpdateBar(rangeNextData/rangeMaxData, rangeLevelData/rangeMaxData,"levelBarUp.png");
    
    rangeBar->setPosition(ccp(-40,30));
    
    if (state->building->getLevel() < state->building->getMaxLevel()) {
        sprintf(str, "攻击范围:%d格+%.1f格",(int)(rangeLevelData),jammerAttackRangeUpdateRate);
    } else {
        sprintf(str, "攻击范围:%d格",(int)(rangeLevelData));
    }
    
    CCLabelTTF* rangeLabel = CCLabelTTF::create(str, "Arial", 24);
    rangeLabel->setAnchorPoint(ccp(0,0));
    rangeLabel->setColor(ccc3(254, 218, 130));
    rangeLabel->setPosition(ccp(-40,40));
    updateLayer->addChild(rangeBar);
    updateLayer->addChild(rangeLabel);
    
    
    CCLabelTTF* nameLabel = CCLabelTTF::create("干扰发射器", "Arial", 24);
    nameLabel->setColor(ccc3(254, 218, 130));
    nameLabel->setAnchorPoint(ccp(0.5,0.5));
    nameLabel->setPosition(ccp(-204,172));
    updateLayer->addChild(nameLabel);
    
    //        updateLayer->addChild(rangeLabel);
//    sprintf(str, "攻击范围:%d格",dbBaseRange);
//    CCLabelTTF* description1 = CCLabelTTF::create(str, "Arial",  26);
//    description1->setAnchorPoint(ccp(0,0.5));
//    description1->setColor(ccc3(254, 218, 130));
//    description1->setPosition(ccp(-80,-16));
//    updateLayer->addChild(description1);
//    
//    CCSprite* underline1 = CCSprite::createWithSpriteFrameName("underline.png");
//    underline1->setPosition(ccp(0,-32));
//    updateLayer->addChild(underline1);
    
    
    //        sprintf(str, "攻击溅射范围:%d格",1);
    //        CCLabelTTF* description2 = CCLabelTTF::create(str, "Arial",  transWindowToGLInRetina(13));
    //        description2->setAnchorPoint(ccp(0,0.5));
    //        description2->setColor(ccc3(114, 66, 45));
    //        description2->setPosition(transWindowToGLInRetina(-55,-21));
    //        updateLayer->addChild(description2);
    //
    //        CCSprite* underline2 = CCSprite::createWithSpriteFrameName("underline.png");
    //        underline2->setPosition(transWindowToGLInRetina(0,-29));
    //        updateLayer->addChild(underline2);
    
    
    CCLabelTTF* description3 = CCLabelTTF::create("目标部队:地面", "Arial",  26);
    description3->setAnchorPoint(ccp(0.5,0.5));
    description3->setColor(ccc3(254, 218, 130));
    description3->setPosition(ccp(-5,-58));
    updateLayer->addChild(description3);
    
    CCSprite* underline3 = CCSprite::createWithSpriteFrameName("underline.png");
    underline3->setPosition(ccp(0,-74));
    updateLayer->addChild(underline3);
}

BuildingInfo* Jammer::getJammerInfo() {
    if(buildingInfo == NULL) {
        buildingInfo = BuildingInfo::create();
    }
    return buildingInfo;
}