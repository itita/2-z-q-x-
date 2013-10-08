//
//  Tiger.cpp
//  ww4
//
//  Created by xiao tang on 13-7-11.
//
//

#include "Tiger.h"
#include "MyUtil.h"
#include "MoveToAttack.h"
#include "AoeAttackState.h"
#include "SimpleAudioEngine.h"
#include "GXFX.h"
#include "GXAnimateWithFx.h"
#include "SimpleAudioEngine.h"
#include "NoResourceToDeployMessage.h"

#define nameStr "虎式坦克"
#define rarity 4

#define oriDamage 1500
//#define oriDamage 0
#define oriHealth 50000
#define oriCost 500000

#define baseSpeed 1
#define baseAttackRange 4
#define baseDamage 400
//#define baseDamage 0
#define baseHealth 1500
#define baseCost 8000

#define updateHealthRate 5
#define updateDamageRate 2
#define updateCostRate 2
#define updateSpeedRate 0

#define sfxDeployNameStr "sfx_deployTank.m4a"
#define sfxFireNameStr "sfx_paoji.m4a"
#define spriteFileNameStr "tiger"

#define moveAnimateRate 0.3
#define fireAnimateRate 0.1
#define dieAnimateRate 0.1

#define moveAnimateReverse false
#define fireAnimateReverse true
#define dieAnimateReverse false

#define fireFxStartFrame 1
#define fireFxZorder 1
#define fireFxScale 1.5
#define fireFxSpriteStr "firelight"

#define attackRate 2.5

#define baseCostCool 1.25

UnitBean* Tiger::unitBean = NULL;

MyUnit* Tiger::createUnit(int level) {
    //    float costLevelData = 100;
    //    costLevelData = MyUtil::getInstance()->updateLevelByRate(0,baseCost, level, updateCostRate);
    //    if(MyGameInfo::getInstance()->getOil()-costLevelData>=0) {
    float speedLevelData = 0;
    float damageLevelData = 0;
    
    float healthLevelData = 0;
    speedLevelData = MyUtil::getInstance()->updateLevelByCount(baseSpeed, level, updateSpeedRate);
    healthLevelData = MyUtil::getInstance()->updateLevelByRate(oriHealth,baseHealth, level, updateHealthRate);
    damageLevelData = MyUtil::getInstance()->updateLevelByRate(oriDamage,baseDamage, level, updateDamageRate);
    
    
    
    MoveToAttack* moveToAttack = MoveToAttack::create(MoveToAttackTag,speedLevelData*attackRate,baseAttackRange);
    AoeAttackState* attack = AoeAttackState::create(AttackStateTag,CCString::create(sfxFireNameStr), baseAttackRange,damageLevelData*attackRate,10,1.5);
    moveToAttack->addTransition(toAttackTransition, AttackStateTag);
    attack->addTransition(toMoveTransition, MoveToAttackTag);
    MyUnit* unit = MyUnit::create(moveToAttack,healthLevelData,attackRate,level);
    unit->addState(attack);
    unit->mode = special;
    //    MyGameInfo::getInstance()->changeResource(oilTag, -costLevelData);
    //    CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(sfxDeployNameStr);
    
    unit->moveAnimateCreator = (SEL_UnitFXCreator)(&Tiger::getMoveAnimate);
    unit->fireAnimateCreator = (SEL_UnitFXCreator)(&Tiger::getFireAnimate);
    unit->dieAnimateCreator = (SEL_UnitFXCreator)(&Tiger::getDieAnimate);
    
    //        unit->cost = costLevelData;
    
    return unit;
    //    } else {
    //        CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sfx_error.wav");
    //        NoResourceToDeployMessage::create(unitBean)->sendMsg();
    //        return NULL;
    //    }
}

CCAnimate* Tiger::getFireAnimate(int dir) {
    char str[40] = {0};
    GXFX* fx;
    if (dir == 0) {
        sprintf(str, "%sld",fireFxSpriteStr);
        fx = GXFX::create(GXUtil::initAction(str, 1,false), fireFxStartFrame,fireFxZorder);
        fx->setPosition(ccp(9,40));
        fx->setScale(fireFxScale);
        sprintf(str, "%sfld",spriteFileNameStr);
    } else if(dir == 1) {
        sprintf(str, "%sd",fireFxSpriteStr);
        fx = GXFX::create(GXUtil::initAction(str, 1,false), fireFxStartFrame,fireFxZorder);
        fx->setPosition(ccp(88,10));
        fx->setScale(fireFxScale);
        sprintf(str, "%sfd",spriteFileNameStr);
    } else if(dir == 2) {
        sprintf(str, "%srd",fireFxSpriteStr);
        fx = GXFX::create(GXUtil::initAction(str, 1,false), fireFxStartFrame,fireFxZorder);
        fx->setPosition(ccp(178,38));
        fx->setScale(fireFxScale);
        sprintf(str, "%sfrd",spriteFileNameStr);
    } else if(dir == 3) {
        sprintf(str, "%sr",fireFxSpriteStr);
        fx = GXFX::create(GXUtil::initAction(str, 1,false), fireFxStartFrame,fireFxZorder);
        fx->setPosition(ccp(213,90));
        fx->setScale(fireFxScale);
        sprintf(str, "%sfr",spriteFileNameStr);
    } else if(dir == 4) {
        sprintf(str, "%sru",fireFxSpriteStr);
        fx = GXFX::create(GXUtil::initAction(str, 1,false), fireFxStartFrame,fireFxZorder);
        fx->setPosition(ccp(177,144));
        fx->setScale(fireFxScale);
        sprintf(str, "%sfru",spriteFileNameStr);
    } else if(dir == 5) {
        sprintf(str, "%su",fireFxSpriteStr);
        fx = GXFX::create(GXUtil::initAction(str, 1,false), fireFxStartFrame,fireFxZorder);
        fx->setPosition(ccp(92,178));
        fx->setScale(fireFxScale);
        sprintf(str, "%sfu",spriteFileNameStr);
    } else if(dir == 6) {
        sprintf(str, "%slu",fireFxSpriteStr);
        fx = GXFX::create(GXUtil::initAction(str, 1,false), fireFxStartFrame,fireFxZorder);
        fx->setPosition(ccp(8,150));
        fx->setScale(fireFxScale);
        sprintf(str, "%sflu",spriteFileNameStr);
    } else if(dir == 7) {
        sprintf(str, "%sl",fireFxSpriteStr);
        fx = GXFX::create(GXUtil::initAction(str, 1,false), fireFxStartFrame,fireFxZorder);
        fx->setPosition(ccp(-27,95));
        fx->setScale(fireFxScale);
        sprintf(str, "%sfl",spriteFileNameStr);
    }
    
    return GXAnimateWithFx::create(GXUtil::initAction(str,fireAnimateRate,fireAnimateReverse), fx);;
    
}

CCAnimate* Tiger::getMoveAnimate(int dir){
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

CCAnimate* Tiger::getDieAnimate(int dir){
    char str[40] = {0};
    if (dir == 0) {
        sprintf(str, "%sdld",spriteFileNameStr);
    } else if(dir == 1) {
        sprintf(str, "%sdd",spriteFileNameStr);
    } else if(dir == 2) {
        sprintf(str, "%sdrd",spriteFileNameStr);
    } else if(dir == 3) {
        sprintf(str, "%sdr",spriteFileNameStr);
    } else if(dir == 4) {
        sprintf(str, "%sdru",spriteFileNameStr);
    } else if(dir == 5) {
        sprintf(str, "%sdu",spriteFileNameStr);
    } else if(dir == 6) {
        sprintf(str, "%sdlu",spriteFileNameStr);
    } else if(dir == 7) {
        sprintf(str, "%sdl",spriteFileNameStr);
    }
    return CCAnimate::create(GXUtil::initAction(str,dieAnimateRate,dieAnimateReverse));
}

UnitBean* Tiger::getUnitBean() {
    if (unitBean == NULL) {
        unitBean = UnitBean::create(TigerCardId,CCString::create(nameStr),CCString::create(spriteFileNameStr),baseCost,updateCostRate,rarity);
        unitBean->createUnit_selector = (SEL_CreateUnit)(&Tiger::createUnit);
        unitBean->getUnitCardInfo_selector = (SEL_GetUnitCardInfo)(&Tiger::getUnitCardDesc);
        unitBean->getAttackSprite_selector = (SEL_GetAttackSprite)(&Tiger::getAttackSprite);
        unitBean->summaryOriOil = oriCost;
        unitBean->unlockNeedCount = 14400001;
        unitBean->unlockCostCount = 1000;
        unitBean->retain();
        unitBean->costCool = baseCostCool;
        unitBean->sfxDeployNameString = sfxDeployNameStr;
    }
    return unitBean;
}


CCLayer* Tiger::getUnitCardDesc(int level,bool isAll) {
    CCLayer* layer = CCLayer::create();
    float attackLevelData = MyUtil::getInstance()->updateLevelByRate(oriDamage,baseDamage, level, updateDamageRate);
    float attackMaxData = MyUtil::getInstance()->updateLevelByRate(oriDamage,baseDamage, unitBean->getMaxLevel(), updateDamageRate);
    CCSprite* attackIcon = CCSprite::createWithSpriteFrameName("damageIcon.png");
    attackIcon->setPosition(ccp(40,360));
    layer->addChild(attackIcon);
    attackIcon->setScale(1.3);
    GXProgressBar* attackBar = GXProgressBar::create(CCSprite::create("levelBarUp.png"), CCSprite::create("BarDown.png"));
    
    attackBar->setContentSize(CCSizeMake(416,20));
    attackBar->updatePercentage((attackLevelData+baseDamage*unitBean->getMaxLevel())/(attackMaxData+baseDamage*unitBean->getMaxLevel()));
    attackBar->setPosition(ccp(70,337));
    
    
    char str[100] = {0};
    sprintf(str, "每秒造成伤害:%d",(int)(attackLevelData));
    
    CCLabelTTF* attackLabel = CCLabelTTF::create(str, "Arial", 28);
    attackLabel->setAnchorPoint(ccp(0,0));
    attackLabel->setColor(ccc3(238,204,122));
    attackLabel->setPosition(ccp(70,352));
    layer->addChild(attackBar);
    layer->addChild(attackLabel);
    
    //    CCLog("damageRate:%f",attackLevelData/attackMaxData);
    
    float speedLevelData = MyUtil::getInstance()->updateLevelByCount(baseSpeed, level, updateSpeedRate);
    
    float speedMaxData = MyUtil::getInstance()->updateLevelByCount(baseSpeed, unitBean->getMaxLevel(), updateSpeedRate);
    
    CCSprite* speedIcon = CCSprite::createWithSpriteFrameName("speedIcon.png");
    speedIcon->setScale(1.3);
    speedIcon->setPosition(ccp(40,300));
    layer->addChild(speedIcon);
    GXProgressBar* speedBar = GXProgressBar::create(CCSprite::create("levelBarUp.png"), CCSprite::create("BarDown.png"));
    
    speedBar->setContentSize(CCSizeMake(416,20));
    speedBar->updatePercentage(speedLevelData/speedMaxData);
    speedBar->setPosition(ccp(70,277));
    
    sprintf(str, "移动速度:%d",(int)(speedLevelData*10));
    
    CCLabelTTF* speedLabel = CCLabelTTF::create(str, "Arial", 24);
    speedLabel->setAnchorPoint(ccp(0,0));
    speedLabel->setColor(ccc3(238,204,122));
    speedLabel->setPosition(ccp(70,292));
    layer->addChild(speedBar);
    layer->addChild(speedLabel);
    
    //    CCLog("speedRate:%f",speedLevelData/speedMaxData);
    
    float healthLevelData = MyUtil::getInstance()->updateLevelByRate(oriHealth,baseHealth, level, updateHealthRate);
    float healthMaxData = MyUtil::getInstance()->updateLevelByRate(oriHealth,baseHealth, unitBean->getMaxLevel(),updateHealthRate);
    
    
    CCSprite* healthIcon = CCSprite::createWithSpriteFrameName("healthIcon.png");
    healthIcon->setScale(1.3);
    healthIcon->setPosition(ccp(40,240));
    layer->addChild(healthIcon);
    GXProgressBar* healthBar = GXProgressBar::create(CCSprite::create("levelBarUp.png"), CCSprite::create("BarDown.png"));
    
    healthBar->setContentSize(CCSizeMake(416,20));
    healthBar->updatePercentage((healthLevelData+baseHealth*unitBean->getMaxLevel())/(healthMaxData+baseHealth*unitBean->getMaxLevel()));
    
    healthBar->setPosition(ccp(70,217));
    
    sprintf(str, "耐久度:%d",(int)healthLevelData);
    
    CCLabelTTF* healthLabel = CCLabelTTF::create(str, "Arial", 24);
    healthLabel->setAnchorPoint(ccp(0,0));
    healthLabel->setColor(ccc3(238,204,122));
    healthLabel->setPosition(ccp(70,232));
    layer->addChild(healthBar);
    layer->addChild(healthLabel);
    
    //    CCLog("lifeRate:%f",healthLevelData/healthMaxData);
    
    float costLevelData = MyUtil::getInstance()->updateLevelByRate(oriCost,baseCost, level, updateCostRate);
    float costMaxData = MyUtil::getInstance()->updateLevelByRate(oriCost,baseCost, unitBean->getMaxLevel(), updateCostRate);
    
    CCSprite* costIcon = CCSprite::createWithSpriteFrameName("oilIcon.png");
    costIcon->setPosition(ccp(40,180));
    costIcon->setScale(40/costIcon->getContentSize().width);
    layer->addChild(costIcon);
    
    
    GXProgressBar* costBar = GXProgressBar::create(CCSprite::create("levelBarUp.png"), CCSprite::create("BarDown.png"));
    
    costBar->setContentSize(CCSizeMake(416,20));
    costBar->updatePercentage((costLevelData+baseCost*unitBean->getMaxLevel())/(costMaxData+baseCost*unitBean->getMaxLevel()));
    
    costBar->setPosition(ccp(70,157));
    
    
    sprintf(str, "派遣使用油料:%d",(int)(costLevelData));
    CCLabelTTF* costLabel = CCLabelTTF::create(str, "Arial", 24);
    costLabel->setAnchorPoint(ccp(0,0));
    costLabel->setColor(ccc3(238,204,122));
    costLabel->setPosition(ccp(70,172));
    layer->addChild(costBar);
    layer->addChild(costLabel);
    
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

CCSprite* Tiger::getAttackSprite(int dir) {
    CCSprite* army;
    CCAnimate* action;
    char str[50] = {0};
    if (dir == attackLD) {
        sprintf(str,"%smru (0).png",spriteFileNameStr);
        army = CCSprite::createWithSpriteFrameName(str);
        action = Tiger::getMoveAnimate(4);
    } else if(dir == attackRD) {
        sprintf(str,"%smlu (0).png",spriteFileNameStr);
        army = CCSprite::createWithSpriteFrameName(str);
        action = Tiger::getMoveAnimate(6);
    } else if(dir == attackLU) {
        sprintf(str,"%smrd (0).png",spriteFileNameStr);
        army = CCSprite::createWithSpriteFrameName(str);
        action = Tiger::getMoveAnimate(2);
    } else {
        sprintf(str,"%smld (0).png",spriteFileNameStr);
        army = CCSprite::createWithSpriteFrameName(str);
        action = Tiger::getMoveAnimate(0);
    }
    army->runAction(CCRepeatForever::create(action));
    return army;
}