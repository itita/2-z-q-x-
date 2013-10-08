//
//  HummingBird.cpp
//  ww4
//
//  Created by xiao tang on 13-5-10.
//
//

#include "HummingBird.h"
#include "MyUtil.h"
#include "FlyMoveToAttack.h"
#include "FlyAttackState.h"
#include "SimpleAudioEngine.h"
#include "GXFX.h"
#include "GXAnimateWithFx.h"
#include "SimpleAudioEngine.h"
#include "NoResourceToDeployMessage.h"
#include "GXShakeAction.h"

#define nameStr "蜂鸟直升机"
#define rarity 3

#define oriDamage 100
#define oriHealth 200
#define oriCost 1000

#define baseSpeed 3
#define baseAttackRange 3.5
#define baseDamage 8
#define baseHealth 40
#define baseCost 70
#define baseAttackRate 1

#define updateHealthRate 0.3
#define updateDamageRate 0.8
#define updateCostRate 1.4
#define updateSpeedRate 0.1
#define updateAttackRate -0.02

#define sfxDeployNameStr "sfx_helicopter.mp3"
#define sfxFireNameStr "sfx_diaobao1f.wav"
#define spriteFileNameStr "HummingBird"

#define moveAnimateRate 0.15
#define fireAnimateRate 0.15
#define dieAnimateRate 0.075

#define moveAnimateReverse false
#define fireAnimateReverse false
#define dieAnimateReverse false

#define fireFxStartFrame 0
#define fireFxZorder 1
#define fireFxScale 0.8
#define fireFxSpriteStr "gunlight"

#define baseCostCool 2

UnitBean* HummingBird::unitBean = NULL;

MyUnit* HummingBird::createUnit(int level) {
    //    float costLevelData = 100;
    //    costLevelData = MyUtil::getInstance()->updateLevelByRate(oriCost,baseCost, level, updateCostRate);
    //    if(MyGameInfo::getInstance()->getOil()-costLevelData>=0) {
    float speedLevelData = 0;
    float damageLevelData = 0;
    
    float healthLevelData = 0;
    speedLevelData = MyUtil::getInstance()->updateLevelByCount(baseSpeed, level, updateSpeedRate);
    healthLevelData = MyUtil::getInstance()->updateLevelByRate(oriHealth,baseHealth, level, updateHealthRate);
    damageLevelData = MyUtil::getInstance()->updateLevelByRate(oriDamage,baseDamage, level, updateDamageRate);
    
    float attackLevelRate = MyUtil::getInstance()->updateLevelByCount(baseAttackRate, level, updateAttackRate);
    
    
    FlyMoveToAttack* moveToAttack = FlyMoveToAttack::create(MoveToAttackTag,speedLevelData*attackLevelRate,baseAttackRange);
    FlyAttackState* attack = FlyAttackState::create(AttackStateTag,CCString::create(sfxFireNameStr), baseAttackRange,damageLevelData*attackLevelRate,10);
    moveToAttack->addTransition(toAttackTransition, AttackStateTag);
    attack->addTransition(toMoveTransition, MoveToAttackTag);
    MyUnit* unit = MyUnit::create(moveToAttack,healthLevelData,attackLevelRate,level);
    unit->addState(attack);
    unit->mode = airMode;
    
    CCSprite* propeller = CCSprite::create();
    CCAnimate* animate = CCAnimate::create(GXUtil::initAction("propeller",0.05,false));
    propeller->runAction(CCRepeatForever::create(animate));
    propeller->setPosition(ccp(100,175));
    
    unit->addChild(propeller);
    unit->setAnchorPoint(ccp(0.5,0));
    
    CCSprite* shadow = CCSprite::createWithSpriteFrameName("HummingBirdshadow (0).png");
    shadow->setScale(0.75);
    shadow->setOpacity(150);
    shadow->setPosition(ccp(100,0));
    
    unit->addChild(shadow,-1);
    unit->runAction(CCRepeatForever::create(CCEaseInOut::create(GXShakeAction::create(2,10.0/200.0,7.0/215.0,unit->getAnchorPoint()),0.8)));
    
    
    //    MyGameInfo::getInstance()->changeResource(oilTag, -costLevelData);
    //    CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(sfxDeployNameStr);
    
    unit->moveAnimateCreator = (SEL_UnitFXCreator)(&HummingBird::getMoveAnimate);
    unit->fireAnimateCreator = (SEL_UnitFXCreator)(&HummingBird::getFireAnimate);
    unit->dieAnimateCreator = (SEL_UnitFXCreator)(&HummingBird::getDieAnimate);
    
    //        unit->cost = costLevelData;
    
    return unit;
    //    } else {
    //        CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sfx_error.wav");
    //        NoResourceToDeployMessage::create(unitBean)->sendMsg();
    //        return NULL;
    //    }
}

CCAnimate* HummingBird::getFireAnimate(int dir) {
    CCArray* fxArray = CCArray::create();
    char str[50] = {0};
    if (dir == 0) {
        sprintf(str, "%sld",fireFxSpriteStr);
        GXFX* fx1 = GXFX::create(GXUtil::initAction(str, 1,false), fireFxStartFrame,fireFxZorder);
        fx1->setPosition(ccp(64,150));
        fx1->setScale(fireFxScale);
        
        fxArray->addObject(fx1);
        
        GXFX* fx2 = GXFX::create(GXUtil::initAction(str, 1,false), fireFxStartFrame,fireFxZorder);
        fx2->setPosition(ccp(90,131));
        fx2->setScale(fireFxScale);
        
        fxArray->addObject(fx2);
        
        sprintf(str, "%smld",spriteFileNameStr);
    } else if(dir == 1) {
        sprintf(str, "%sd",fireFxSpriteStr);
        
        GXFX* fx1 = GXFX::create(GXUtil::initAction(str, 1,false), fireFxStartFrame,fireFxZorder);
        fx1->setPosition(ccp(80,133));
        fx1->setScale(fireFxScale);
        
        fxArray->addObject(fx1);
        
        GXFX* fx2 = GXFX::create(GXUtil::initAction(str, 1,false), fireFxStartFrame,fireFxZorder);
        fx2->setPosition(ccp(120,133));
        fx2->setScale(fireFxScale);
        
        fxArray->addObject(fx2);
        
        sprintf(str, "%smd",spriteFileNameStr);
    } else if(dir == 2) {
        sprintf(str, "%srd",fireFxSpriteStr);
        
        GXFX* fx1 = GXFX::create(GXUtil::initAction(str, 1,false), fireFxStartFrame,fireFxZorder);
        fx1->setPosition(ccp(107,133));
        fx1->setScale(fireFxScale);
        
        fxArray->addObject(fx1);
        
        GXFX* fx2 = GXFX::create(GXUtil::initAction(str, 1,false), fireFxStartFrame,fireFxZorder);
        fx2->setPosition(ccp(135,149));
        fx2->setScale(fireFxScale);
        
        fxArray->addObject(fx2);
        
        sprintf(str, "%smrd",spriteFileNameStr);
    } else if(dir == 3) {
        sprintf(str, "%sr",fireFxSpriteStr);
        
        GXFX* fx1 = GXFX::create(GXUtil::initAction(str, 1,false), fireFxStartFrame,fireFxZorder);
        fx1->setPosition(ccp(132,140));
        fx1->setScale(fireFxScale);
        
        fxArray->addObject(fx1);
        
        GXFX* fx2 = GXFX::create(GXUtil::initAction(str, 1,false), fireFxStartFrame,fireFxZorder);
        fx2->setPosition(ccp(132,167));
        fx2->setScale(fireFxScale);
        
        fxArray->addObject(fx2);
        
        sprintf(str, "%smr",spriteFileNameStr);
    } else if(dir == 4) {
        sprintf(str, "%sru",fireFxSpriteStr);
        
        GXFX* fx1 = GXFX::create(GXUtil::initAction(str, 1,false), fireFxStartFrame,fireFxZorder);
        fx1->setPosition(ccp(138,158));
        fx1->setScale(fireFxScale);
        
        fxArray->addObject(fx1);
        
        GXFX* fx2 = GXFX::create(GXUtil::initAction(str, 1,false), fireFxStartFrame,-1);
        fx2->setPosition(ccp(106,180));
        fx2->setScale(fireFxScale);
        
        fxArray->addObject(fx2);
        
        sprintf(str, "%smru",spriteFileNameStr);
    } else if(dir == 5) {
        sprintf(str, "%su",fireFxSpriteStr);
        
        GXFX* fx1 = GXFX::create(GXUtil::initAction(str, 1,false), fireFxStartFrame,fireFxZorder);
        fx1->setPosition(ccp(79,173));
        fx1->setScale(fireFxScale);
        
        fxArray->addObject(fx1);
        
        GXFX* fx2 = GXFX::create(GXUtil::initAction(str, 1,false), fireFxStartFrame,fireFxZorder);
        fx2->setPosition(ccp(120,173));
        fx2->setScale(fireFxScale);
        
        fxArray->addObject(fx2);
        
        sprintf(str, "%smu",spriteFileNameStr);
    } else if(dir == 6) {
        sprintf(str, "%slu",fireFxSpriteStr);
        
        GXFX* fx1 = GXFX::create(GXUtil::initAction(str, 1,false), fireFxStartFrame,fireFxZorder);
        fx1->setPosition(ccp(61,158));
        fx1->setScale(fireFxScale);
        
        fxArray->addObject(fx1);
        
        GXFX* fx2 = GXFX::create(GXUtil::initAction(str, 1,false), fireFxStartFrame,-1);
        fx2->setPosition(ccp(96,175));
        fx2->setScale(fireFxScale);
        
        fxArray->addObject(fx2);
        
        sprintf(str, "%smlu",spriteFileNameStr);
    } else if(dir == 7) {
        sprintf(str, "%sl",fireFxSpriteStr);
        
        GXFX* fx1 = GXFX::create(GXUtil::initAction(str, 1,false), fireFxStartFrame,fireFxZorder);
        fx1->setPosition(ccp(67,140));
        fx1->setScale(fireFxScale);
        
        fxArray->addObject(fx1);
        
        GXFX* fx2 = GXFX::create(GXUtil::initAction(str, 1,false), fireFxStartFrame,fireFxZorder);
        fx2->setPosition(ccp(67,165));
        fx2->setScale(fireFxScale);
        
        fxArray->addObject(fx2);
        
        sprintf(str, "%sml",spriteFileNameStr);
    }
    
    return GXAnimateWithFx::create(GXUtil::initAction(str,fireAnimateRate,fireAnimateReverse), fxArray);
}

CCAnimate* HummingBird::getMoveAnimate(int dir){
    char str[40] = {0};
    if (dir == 0) {
        sprintf(str, "%smld",spriteFileNameStr);
    } else if(dir == 1) {
        sprintf(str, "%smd",spriteFileNameStr);
    } else if(dir == 2) {
        sprintf(str, "%smrd",spriteFileNameStr);
    } else if(dir == 3) {
        sprintf(str, "%smr",spriteFileNameStr);
    } else if(dir == 4) {
        sprintf(str, "%smru",spriteFileNameStr);
    } else if(dir == 5) {
        sprintf(str, "%smu",spriteFileNameStr);
    } else if(dir == 6) {
        sprintf(str, "%smlu",spriteFileNameStr);
    } else if(dir == 7) {
        sprintf(str, "%sml",spriteFileNameStr);
    }
    return CCAnimate::create(GXUtil::initAction(str,moveAnimateRate,moveAnimateReverse));
}

CCAnimate* HummingBird::getDieAnimate(int dir){
    return CCAnimate::create(GXUtil::initAction("airboom",dieAnimateRate,dieAnimateReverse));
}

UnitBean* HummingBird::getUnitBean() {
    if (unitBean == NULL) {
        unitBean = UnitBean::create(HummingBirdCardId,CCString::create(nameStr),CCString::create(spriteFileNameStr),baseCost,updateCostRate,rarity);
        unitBean->createUnit_selector = (SEL_CreateUnit)(&HummingBird::createUnit);
        unitBean->getUnitCardInfo_selector = (SEL_GetUnitCardInfo)(&HummingBird::getUnitCardDesc);
        unitBean->getAttackSprite_selector = (SEL_GetAttackSprite)(&HummingBird::getAttackSprite);
        unitBean->summaryOriOil = oriCost;
        unitBean->unlockCostResourceTag = diamondTag;
        unitBean->unlockCostCount = 500;
        unitBean->retain();
        unitBean->costCool = baseCostCool;
        unitBean->sfxDeployNameString = sfxDeployNameStr;
    }
    return unitBean;
}


CCLayer* HummingBird::getUnitCardDesc(int level,bool isAll) {
    CCLayer* layer = CCLayer::create();
    float attackLevelData = MyUtil::getInstance()->updateLevelByRate(oriDamage,baseDamage, level, updateDamageRate);
    float attackMaxData = MyUtil::getInstance()->updateLevelByRate(oriDamage,baseDamage, unitBean->getMaxLevel(), updateDamageRate);
    CCSprite* attackIcon = CCSprite::createWithSpriteFrameName("damageIcon.png");
    attackIcon->setPosition(ccp(40,390));
    layer->addChild(attackIcon);
    //    attackIcon->setScale((30/attackIcon->getContentSize().width+30/attackIcon->getContentSize().height)/2);
    attackIcon->setScale(1.3);
    GXProgressBar* attackBar = GXProgressBar::create(CCSprite::create("levelBarUp.png"), CCSprite::create("BarDown.png"));
    
    attackBar->setContentSize(CCSizeMake(416,20));
    attackBar->updatePercentage((attackLevelData+baseDamage*unitBean->getMaxLevel())/(attackMaxData+baseDamage*unitBean->getMaxLevel()));
    attackBar->setPosition(ccp(70,367));
    
    
    char str[100] = {0};
    sprintf(str, "每秒造成伤害:%d",(int)(attackLevelData));
    
    CCLabelTTF* attackLabel = CCLabelTTF::create(str, "Arial", 28);
    attackLabel->setAnchorPoint(ccp(0,0));
    attackLabel->setColor(ccc3(238,204,122));
    attackLabel->setPosition(ccp(70,382));
    layer->addChild(attackBar);
    layer->addChild(attackLabel);
    
    //    CCLog("damageRate:%f",attackLevelData/attackMaxData);
    
    float speedLevelData = MyUtil::getInstance()->updateLevelByCount(baseSpeed, level, updateSpeedRate);
    
    float speedMaxData = MyUtil::getInstance()->updateLevelByCount(baseSpeed, unitBean->getMaxLevel(), updateSpeedRate);
    
    CCSprite* speedIcon = CCSprite::createWithSpriteFrameName("speedIcon.png");
    //    speedIcon->setScale((50/speedIcon->getContentSize().width+50/speedIcon->getContentSize().height)/2);
    speedIcon->setScale(1.2);
    speedIcon->setPosition(ccp(40,335));
    layer->addChild(speedIcon);
    GXProgressBar* speedBar = GXProgressBar::create(CCSprite::create("levelBarUp.png"), CCSprite::create("BarDown.png"));
    
    speedBar->setContentSize(CCSizeMake(416,20));
    speedBar->updatePercentage(speedLevelData/speedMaxData);
    speedBar->setPosition(ccp(70,312));
    
    sprintf(str, "移动速度:%d",(int)(speedLevelData*10));
    
    CCLabelTTF* speedLabel = CCLabelTTF::create(str, "Arial", 24);
    speedLabel->setAnchorPoint(ccp(0,0));
    speedLabel->setColor(ccc3(238,204,122));
    speedLabel->setPosition(ccp(70,327));
    layer->addChild(speedBar);
    layer->addChild(speedLabel);
    
    //    CCLog("speedRate:%f",speedLevelData/speedMaxData);
    
    float healthLevelData = MyUtil::getInstance()->updateLevelByRate(oriHealth,baseHealth, level, updateHealthRate);
    float healthMaxData = MyUtil::getInstance()->updateLevelByRate(oriHealth,baseHealth, unitBean->getMaxLevel(),updateHealthRate);
    
    
    CCSprite* healthIcon = CCSprite::createWithSpriteFrameName("healthIcon.png");
    //    healthIcon->setScale((30/healthIcon->getContentSize().width+30/healthIcon->getContentSize().height)/2);
    healthIcon->setScale(1.3);
    healthIcon->setPosition(ccp(40,280));
    layer->addChild(healthIcon);
    GXProgressBar* healthBar = GXProgressBar::create(CCSprite::create("levelBarUp.png"), CCSprite::create("BarDown.png"));
    
    healthBar->setContentSize(CCSizeMake(416,20));
    healthBar->updatePercentage((healthLevelData+baseHealth*unitBean->getMaxLevel())/(healthMaxData+baseHealth*unitBean->getMaxLevel()));
    
    healthBar->setPosition(ccp(70,257));
    
    sprintf(str, "耐久度:%d",(int)healthLevelData);
    
    CCLabelTTF* healthLabel = CCLabelTTF::create(str, "Arial", 24);
    healthLabel->setAnchorPoint(ccp(0,0));
    healthLabel->setColor(ccc3(238,204,122));
    healthLabel->setPosition(ccp(70,272));
    layer->addChild(healthBar);
    layer->addChild(healthLabel);
    
    //    CCLog("lifeRate:%f",healthLevelData/healthMaxData);
    
    float costLevelData = MyUtil::getInstance()->updateLevelByRate(oriCost,baseCost, level, updateCostRate);
    float costMaxData = MyUtil::getInstance()->updateLevelByRate(oriCost,baseCost, unitBean->getMaxLevel(), updateCostRate);
    
    CCSprite* costIcon = CCSprite::createWithSpriteFrameName("oilIcon.png");
    costIcon->setPosition(ccp(40,225));
    costIcon->setScale(40/costIcon->getContentSize().width);
    layer->addChild(costIcon);
    
    
    GXProgressBar* costBar = GXProgressBar::create(CCSprite::create("levelBarUp.png"), CCSprite::create("BarDown.png"));
    
    costBar->setContentSize(CCSizeMake(416,20));
    costBar->updatePercentage((costLevelData+baseCost*unitBean->getMaxLevel())/(costMaxData+baseCost*unitBean->getMaxLevel()));
    
    costBar->setPosition(ccp(70,202));
    
    
    sprintf(str, "派遣使用油料:%d",(int)(costLevelData));
    CCLabelTTF* costLabel = CCLabelTTF::create(str, "Arial", 24);
    costLabel->setAnchorPoint(ccp(0,0));
    costLabel->setColor(ccc3(238,204,122));
    costLabel->setPosition(ccp(70,217));
    layer->addChild(costBar);
    layer->addChild(costLabel);
    
    float attackRateLevelData = MyUtil::getInstance()->updateLevelByCount(baseAttackRate, level, updateAttackRate);
    float attackRateMaxData = MyUtil::getInstance()->updateLevelByCount(baseAttackRate, unitBean->getMaxLevel(), updateAttackRate);
    
    CCSprite* attackRateIcon = CCSprite::createWithSpriteFrameName("attackRateIcon.png");
    //    attackRateIcon->setScale((30/attackRateIcon->getContentSize().width+30/attackRateIcon->getContentSize().height)/2);
    attackRateIcon->setScale(1.3);
    attackRateIcon->setPosition(ccp(40,170));
    //    attackRateIcon->setScale(24/attackRateIcon->getContentSize().width);
    layer->addChild(attackRateIcon);
    
    
    GXProgressBar* attackRateBar = GXProgressBar::create(CCSprite::create("levelBarUp.png"), CCSprite::create("BarDown.png"));
    
    attackRateBar->setContentSize(CCSizeMake(416,20));
    attackRateBar->updatePercentage((1-attackRateLevelData)/(1-attackRateMaxData));
    
    attackRateBar->setPosition(ccp(70,147));
    
    
    sprintf(str, "攻击速度:%.2f秒一次攻击",attackRateLevelData);
    CCLabelTTF* attackRateLabel = CCLabelTTF::create(str, "Arial", 24);
    attackRateLabel->setAnchorPoint(ccp(0,0));
    attackRateLabel->setColor(ccc3(238,204,122));
    attackRateLabel->setPosition(ccp(70,162));
    layer->addChild(attackRateBar);
    layer->addChild(attackRateLabel);
    
    if (!isAll) {
        return layer;
    }
    
    
    sprintf(str, "最大等级:%d",(int)unitBean->getMaxLevel());
    CCLabelTTF* description1 = CCLabelTTF::create(str, "Arial",  26);
    description1->setAnchorPoint(ccp(0.5,0.5));
    description1->setColor(ccc3(238,204,122));
    description1->setPosition(ccp(260,110));
    layer->addChild(description1);
    
    
    CCSprite* underline1 = CCSprite::createWithSpriteFrameName("underline.png");
    underline1->setPosition(ccp(260,95));
    layer->addChild(underline1);
    
    
    sprintf(str, "攻击距离:%d格",(int)baseAttackRange);
    CCLabelTTF* description2 = CCLabelTTF::create(str, "Arial",  26);
    description2->setAnchorPoint(ccp(0.5,0.5));
    description2->setColor(ccc3(238,204,122));
    description2->setPosition(ccp(260,70));
    layer->addChild(description2);
    
    CCSprite* underline2 = CCSprite::createWithSpriteFrameName("underline.png");
    underline2->setPosition(ccp(260,55));
    layer->addChild(underline2);
    
    
    CCLabelTTF* description3 = CCLabelTTF::create("主要目标:任意目标", "Arial",  26);
    description3->setAnchorPoint(ccp(0.5,0.5));
    description3->setColor(ccc3(238,204,122));
    description3->setPosition(ccp(260,30));
    layer->addChild(description3);
    
    CCSprite* underline3 = CCSprite::createWithSpriteFrameName("underline.png");
    underline3->setPosition(ccp(260,15));
    layer->addChild(underline3);
    return layer;
}

CCSprite* HummingBird::getAttackSprite(int dir) {
    CCSprite* army;
    char str[50] = {0};
    if (dir == attackLD) {
        sprintf(str,"%smru (0).png",spriteFileNameStr);
        army = CCSprite::createWithSpriteFrameName(str);
    } else if(dir == attackRD) {
        sprintf(str,"%smlu (0).png",spriteFileNameStr);
        army = CCSprite::createWithSpriteFrameName(str);
    } else if(dir == attackLU) {
        sprintf(str,"%smrd (0).png",spriteFileNameStr);
        army = CCSprite::createWithSpriteFrameName(str);
    } else {
        sprintf(str,"%smld (0).png",spriteFileNameStr);
        army = CCSprite::createWithSpriteFrameName(str);
    }
    
    CCSprite* propeller = CCSprite::create();
    CCAnimate* animate = CCAnimate::create(GXUtil::initAction("propeller",0.05,false));
    propeller->runAction(CCRepeatForever::create(animate));
    propeller->setPosition(ccp(100,175));
    
    army->addChild(propeller);
    army->setAnchorPoint(ccp(0.5,0.5));
    
    CCSprite* shadow = CCSprite::createWithSpriteFrameName("HummingBirdshadow (0).png");
    shadow->setScale(0.75);
    shadow->setOpacity(150);
    shadow->setPosition(ccp(100,-50));
    
    army->addChild(shadow,-1);
    army->runAction(CCRepeatForever::create(CCEaseInOut::create(GXShakeAction::create(2,10.0/200.0,7.0/215.0,army->getAnchorPoint()),0.8)));
    
    return army;
}