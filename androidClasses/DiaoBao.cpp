//
//  DiaoBao.cpp
//  ww4
//
//  Created by xiao tang on 13-5-3.
//
//

#include "DiaoBao.h"
#include "DefendInCreateState.h"
#include "DefineSet.h"
#include "DefendState.h"
#include "GXUtil.h"
#include "StartScene.h"
#include "MyUtil.h"



#define fireFxSpriteStr "gunlight"


MyBuilding* DiaoBao::createNormal(cocos2d::CCObject *target,int level) {
    
    
    CCSprite* byItem;
    
    byItem = CCSprite::createWithSpriteFrameName("diaobao.png");
    byItem->setAnchorPoint(ccp(0.45,0.5));
//    byItem->setScale(0.8);
    
    
    DefendInCreateState* workState = DefendInCreateState::create(WorkStateTag, byItem);
    workState->setAttackRange(dbBaseRange);
    TransitionInfo* infoItem =  TransitionInfo::create(InfoTransition,"info.png",workState,menu_selector(MyState::infoCallBack));

    MyBuilding* BDbuilding;
  
#if game_version == soft_version
    BDbuilding = MyBuilding::create(diaobaoTag,CCSizeMake(3,3),workState,level,10);
#endif
#if game_version == hard_version
    BDbuilding = MyBuilding::create(diaobaoTag,CCSizeMake(2,2),workState,25);
#endif
    BDbuilding->setLevel(level);
    BDbuilding->setTag(diaobaoTag);
    BDbuilding->setSummaryCount(400);
    BDbuilding->resourceTag = ironTag;
    BDbuilding->setBuildingName(CCString::create("机枪碉堡"),70);
    BDbuilding->setUpdateInfo_selector = (SEL_SetUpdateInfo)(&DiaoBao::setUpdateInfo);
    
    TransitionInfo* updateItem =  TransitionInfo::create(UpdateTransition,"update.png",BDbuilding,menu_selector(MyBuilding::updateLevel));

    workState->addTransition(UpdateTransition, WorkStateTag,updateItem);
    workState->addTransition(InfoTransition, WorkStateTag,infoItem);
    
 
    return BDbuilding;
}


MyBattleBuilding* DiaoBao::createBattle(int level,int stateId) {
    
   
    BeAttackState* beAttack;
    
    if(stateId != UnfinishedStateTag) {
        CCSprite* dbItem = CCSprite::createWithSpriteFrameName("diaobao.png");
        dbItem->setAnchorPoint(ccp(0.45,0.5));
        
        float attackRateLevelData = MyUtil::getInstance()->updateLevelByCount(dbBaseAttackRate, level, dbUpdateAttackRateRate);
        
        DefendState* defender = DefendState::create(DefendStateTag, dbItem,CCString::create("diaobao1"),dbBaseHealth,dbBaseRange,dbBaseDamage,attackRateLevelData,1);
        
        defender->setAnimateCreator((SEL_FXCreator)(&DiaoBao::getFireAnimate));
        beAttack = defender;
    } else {
        CCSprite* unfinishItem = CCSprite::createWithSpriteFrameName("buildstruct2x2(0).png");
        beAttack = BeAttackState::create(UnfinishedStateTag, unfinishItem, 100);
    }
    
        
    
    
#if game_version == soft_version
    MyBattleBuilding* diaobao = MyBattleBuilding::create(diaobaoTag,CCSizeMake(3,3),beAttack,level);
#endif
#if game_version == hard_version
    MyBattleBuilding* diaobao = MyBattleBuilding::create(diaobaoTag,CCSizeMake(2,2),beAttack);
#endif
    diaobao->setLevel_selector = (SEL_SetBattleLevel)(&DiaoBao::setBattleLevel);
    diaobao->setLevel(level);

    diaobao->setTag(diaobaoTag);
    diaobao->setBuildingName(CCString::create("机枪碉堡"),88);
//    diaobao->displaySummary();
    
    return diaobao;
}

MyBuildingCard* DiaoBao::createCard(CCObject* target,SEL_MenuHandler selector) {
    CCSprite* sprite = CCSprite::createWithSpriteFrameName("diaobao.png");
    sprite->setAnchorPoint(ccp(0.45,0.65));
    MyBuildingCard* card = MyBuildingCard::create(sprite,diaobaoTag,0,0,ironTag,200,"机枪碉堡", target,selector);
    return card;
}

void DiaoBao::setBattleLevel(int level,GXFSM* fsm) {
    DefendState* defendstate = dynamic_cast<DefendState*>(fsm->getState(DefendStateTag));
    if (defendstate != NULL) {
        float life = MyUtil::getInstance()->updateLevelByRate(0,dbBaseHealth, level, dbUpdateHealthRate);
        defendstate->setMaxLife(life);
        defendstate->setLife(life);
        defendstate->damage = MyUtil::getInstance()->updateLevelByRate(0,dbBaseDamage, level, dbUpdateDamageRate);
    }
}

void DiaoBao::setUpdateInfo(GXFSMstate* _state,CCLayer* updateLayer) {
    
    MyState* state = (MyState*)_state;
    float attackLevelData = MyUtil::getInstance()->updateLevelByRate(0,dbBaseDamage, state->building->getLevel(), dbUpdateDamageRate);
    float attackNextData = MyUtil::getInstance()->updateLevelByRate(0,dbBaseDamage, state->building->getLevel()+1, dbUpdateDamageRate);
    float attackMaxData = MyUtil::getInstance()->updateLevelByRate(0,dbBaseDamage, state->building->getMaxLevel(), dbUpdateDamageRate);
    CCSprite* attackIcon = CCSprite::createWithSpriteFrameName("damageIcon.png");
    attackIcon->setPosition(ccp(-68,160));
    updateLayer->addChild(attackIcon);
    
    CCLayer* attackBar = MyUtil::getInstance()->getUpdateBar(attackNextData/attackMaxData, attackLevelData/attackMaxData,"levelBarUp.png");
    attackBar->setPosition(ccp(-40,142));
    
    char str[100] = {0};
    if(state->building->getLevel() < state->building->getMaxLevel()) {
        sprintf(str, "每秒造成伤害:%d+%d",(int)(attackLevelData),(int)(attackNextData - attackLevelData));
    } else {
        sprintf(str, "每秒造成伤害:%d",(int)(attackLevelData));
    }
    CCLabelTTF* damageLabel = CCLabelTTF::create(str, "Arial", 24);
    damageLabel->setAnchorPoint(ccp(0,0));
    damageLabel->setColor(ccc3(254, 218, 130));
    damageLabel->setPosition(ccp(-40,152));
    updateLayer->addChild(attackBar);
    updateLayer->addChild(damageLabel);
    
    float healthLevelData = MyUtil::getInstance()->updateLevelByRate(0,dbBaseHealth, state->building->getLevel(), dbUpdateHealthRate);
    float healthNextData = MyUtil::getInstance()->updateLevelByRate(0,dbBaseHealth, state->building->getLevel()+1, dbUpdateHealthRate);
    float healthMaxData = MyUtil::getInstance()->updateLevelByRate(0,dbBaseHealth, state->building->getMaxLevel(), dbUpdateHealthRate);
    
    CCSprite* healthIcon = CCSprite::createWithSpriteFrameName("healthIcon.png");
    healthIcon->setPosition(ccp(-68,106));
    updateLayer->addChild(healthIcon);
    
    CCLayer* healthBar = MyUtil::getInstance()->getUpdateBar(healthNextData/healthMaxData, healthLevelData/healthMaxData,"levelBarUp.png");
    
    healthBar->setPosition(ccp(-40,88));
    
    
    if(state->building->getLevel() < state->building->getMaxLevel()) {
        sprintf(str, "耐久度:%d+%d",(int)healthLevelData,(int)(healthNextData-healthLevelData));
    } else {
        sprintf(str, "耐久度:%d",(int)healthLevelData);
    }
    CCLabelTTF* healthLabel = CCLabelTTF::create(str, "Arial", 24);
    healthLabel->setAnchorPoint(ccp(0,0));
    healthLabel->setColor(ccc3(254, 218, 130));
    healthLabel->setPosition(ccp(-40,98));
    updateLayer->addChild(healthBar);
    updateLayer->addChild(healthLabel);
    
    
    float attackRateLevelData = MyUtil::getInstance()->updateLevelByCount(dbBaseAttackRate, state->building->getLevel(), dbUpdateAttackRateRate);
    float attackRateNextData = MyUtil::getInstance()->updateLevelByCount(dbBaseAttackRate, state->building->getLevel()+1, dbUpdateAttackRateRate);
    float attackRateMaxData = MyUtil::getInstance()->updateLevelByCount(dbBaseAttackRate, state->building->getMaxLevel(), dbUpdateAttackRateRate);
    
    CCSprite* attackRateIcon = CCSprite::createWithSpriteFrameName("attackRateIcon.png");
    //    attackRateIcon->setScale((30/attackRateIcon->getContentSize().width+30/attackRateIcon->getContentSize().height)/2);
    
    attackRateIcon->setPosition(ccp(-68,48));
    //    attackRateIcon->setScale(24/attackRateIcon->getContentSize().width);
    updateLayer->addChild(attackRateIcon);
    
    CCLayer* attackRateBar = MyUtil::getInstance()->getUpdateBar( (dbBaseAttackRate-attackRateNextData)/(dbBaseAttackRate-attackRateMaxData),(dbBaseAttackRate-attackRateLevelData)/(dbBaseAttackRate-attackRateMaxData),"levelBarUp.png");
    
    attackRateBar->setPosition(ccp(-40,30));
    
    if(state->building->getLevel() < state->building->getMaxLevel()) {
        sprintf(str, "攻击速度:%.3f-%.3f",attackRateLevelData,dbUpdateAttackRateRate);
    } else {
        sprintf(str, "攻击速度:%.3f",attackRateMaxData);
    }
    
    CCLabelTTF* attackRateLabel = CCLabelTTF::create(str, "Arial", 24);
    attackRateLabel->setAnchorPoint(ccp(0,0));
    attackRateLabel->setColor(ccc3(254, 218, 130));
    attackRateLabel->setPosition(ccp(-40,40));
    updateLayer->addChild(attackRateBar);
    updateLayer->addChild(attackRateLabel);
    
    
    CCLabelTTF* nameLabel = CCLabelTTF::create("机枪碉堡", "Arial", 24);
    nameLabel->setColor(ccc3(254, 218, 130));
    nameLabel->setAnchorPoint(ccp(0.5,0.5));
    nameLabel->setPosition(ccp(-204,172));
    updateLayer->addChild(nameLabel);
    
    //        updateLayer->addChild(rangeLabel);
    sprintf(str, "攻击范围:%d格",dbBaseRange);
    CCLabelTTF* description1 = CCLabelTTF::create(str, "Arial",  26);
    description1->setAnchorPoint(ccp(0,0.5));
    description1->setColor(ccc3(254, 218, 130));
    description1->setPosition(ccp(-80,-16));
    updateLayer->addChild(description1);
    
    CCSprite* underline1 = CCSprite::createWithSpriteFrameName("underline.png");
    underline1->setPosition(ccp(0,-32));
    updateLayer->addChild(underline1);
    
    
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
    
    
    CCLabelTTF* description3 = CCLabelTTF::create("目标部队:地面，空中", "Arial",  26);
    description3->setAnchorPoint(ccp(0.5,0.5));
    description3->setColor(ccc3(254, 218, 130));
    description3->setPosition(ccp(-5,-58));
    updateLayer->addChild(description3);
    
    CCSprite* underline3 = CCSprite::createWithSpriteFrameName("underline.png");
    underline3->setPosition(ccp(0,-74));
    updateLayer->addChild(underline3);
}

CCAnimate* DiaoBao::getFireAnimate(int dir) {
    char str[40] = {0};
    GXFX* fx;
    if (dir == 0) {
        sprintf(str, "%sld",fireFxSpriteStr);
        fx = GXFX::create(GXUtil::initAction(str, 0.1,false), 0,1);
        fx->setPosition(ccp(36,34));
//        fx->setScale(fireFxScale);
    } else if(dir == 1) {
        sprintf(str, "%sd",fireFxSpriteStr);
        fx = GXFX::create(GXUtil::initAction(str, 0.1,false), 0,1);
        fx->setPosition(ccp(47,18));
//        fx->setScale(fireFxScale);
    } else if(dir == 2) {
        sprintf(str, "%srd",fireFxSpriteStr);
        fx = GXFX::create(GXUtil::initAction(str, 0.1,false), 0,1);
        fx->setPosition(ccp(74,37));
//        fx->setScale(fireFxScale);
    } else if(dir == 3) {
        sprintf(str, "%sr",fireFxSpriteStr);
        fx = GXFX::create(GXUtil::initAction(str, 0.1,false), 0,1);
        fx->setPosition(ccp(92,52));
//        fx->setScale(fireFxScale);
    } else if(dir == 4) {
        sprintf(str, "%sru",fireFxSpriteStr);
        fx = GXFX::create(GXUtil::initAction(str, 0.1,false), 0,1);
        fx->setPosition(ccp(76,71));
//        fx->setScale(fireFxScale);
    } else if(dir == 5) {
        sprintf(str, "%su",fireFxSpriteStr);
        fx = GXFX::create(GXUtil::initAction(str, 0.1,false), 0,1);
        fx->setPosition(ccp(50,83));
//        fx->setScale(fireFxScale);
    } else if(dir == 6) {
        sprintf(str, "%slu",fireFxSpriteStr);
        fx = GXFX::create(GXUtil::initAction(str, 0.1,false), 0,1);
        fx->setPosition(ccp(25,68));
//        fx->setScale(fireFxScale);
    } else if(dir == 7) {
        sprintf(str, "%sl",fireFxSpriteStr);
        fx = GXFX::create(GXUtil::initAction(str, 0.1,false), 0,1);
        fx->setPosition(ccp(6,50));
//        fx->setScale(fireFxScale);
    }
    CCArray* actions = CCArray::create();
    actions->addObject(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("diaobao.png"));
    return GXAnimateWithFx::create(CCAnimation::createWithSpriteFrames(actions,0.2), fx);
    
}