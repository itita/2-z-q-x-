//
//  Thor.cpp
//  ww4
//
//  Created by xiao tang on 13-9-5.
//
//

#include "Thor.h"
#include "MyUtil.h"
#include "TornadoMoveToAttack.h"
#include "AoeAttackState.h"
#include "SimpleAudioEngine.h"
#include "GXFX.h"
#include "GXAnimateWithFx.h"


#define nameStr "雷神试验机甲"
#define rarity 5


#define oriDamage 1800
//#define oriDamage 0
#define oriHealth 6000
#define oriCost 10000

#define baseSpeed 1.2
#define baseAttackRange 5
#define baseDamage 2000
//#define baseDamage 0
#define baseHealth 30000
#define baseCost 24000
#define baseSplashRange 1.5

#define updateHealthRate 0.014
#define updateDamageRate 0.02
#define updateCostRate 0.03
#define updateSpeedRate 0
#define attackRate 0.501

#define sfxDeployNameStr "sfx_robot.mp3"
#define sfxFireNameStr "sfx_paoji.m4a"
#define spriteFileNameStr "thor"

#define moveAnimateRate 0.25
#define fireAnimateRate 0.1
#define dieAnimateRate 0.1

#define moveAnimateReverse false
#define fireAnimateReverse false
#define dieAnimateReverse false

#define baseCostCool 50
#define updateCostCool -1.5

#define fireFxStartFrame 0
#define fireFxZorder 1
#define fireFxScale 0.8
#define fireFxSpriteStr "firelight"

UnitBean* Thor::unitBean = NULL;

MyUnit* Thor::createUnit(int level) {
    //    float costLevelData = 100;
    //    costLevelData = MyUtil::getInstance()->updateLevelByRate(0,baseCost, level, updateCostRate);
    //    if(MyGameInfo::getInstance()->getOil()-costLevelData>=0) {
    float speedLevelData = 0;
    float damageLevelData = 0;
    float healthLevelData = 0;
    speedLevelData = MyUtil::getInstance()->updateLevelByCount(baseSpeed, level, updateSpeedRate);
    healthLevelData = MyUtil::getInstance()->updateLevelByRate(oriHealth,baseHealth, level, updateHealthRate);
    damageLevelData = MyUtil::getInstance()->updateLevelByRate(oriDamage,baseDamage, level, updateDamageRate);
    RobotMoveToAttack* moveToAttack = NULL;
    if (MyGameInfo::getInstance()->enemyLevel < 35) {
        moveToAttack = RobotMoveToAttack::create(MoveToAttackTag,speedLevelData*attackRate,moveAnimateRate,baseAttackRange);
    } else if(MyGameInfo::getInstance()->enemyLevel < 51 && level > 17){
        moveToAttack = RobotMoveToAttack::create(MoveToAttackTag,speedLevelData*attackRate,moveAnimateRate,baseAttackRange);
    } else if(MyGameInfo::getInstance()->enemyLevel < 56 && level > 20){
        moveToAttack = RobotMoveToAttack::create(MoveToAttackTag,speedLevelData*attackRate,moveAnimateRate,baseAttackRange);
    } else {
        moveToAttack = TornadoMoveToAttack::create(MoveToAttackTag,speedLevelData*attackRate,moveAnimateRate,baseAttackRange);
    }
    
    AoeAttackState* attack = AoeAttackState::create(AttackStateTag,CCString::create(sfxFireNameStr), baseAttackRange,damageLevelData*attackRate,10,baseSplashRange);
    //    AttackState* attack = AttackState::create(AttackStateTag,CCString::create(sfxFireNameStr), baseAttackRange,damageLevelData*attackRate,100);
    moveToAttack->addTransition(toAttackTransition, AttackStateTag);
    attack->addTransition(toMoveTransition, MoveToAttackTag);
    MyUnit* unit = MyUnit::create(moveToAttack,healthLevelData,attackRate,level);
    unit->addState(attack);
    unit->mode = heavyVehicles;
    unit->setAnchorPoint(ccp(0.5,0.5));
    
    unit->moveAnimateCreator = (SEL_UnitFXCreator)(&Thor::getMoveAnimate);
    unit->fireAnimateCreator = (SEL_UnitFXCreator)(&Thor::getFireAnimate);
    unit->dieAnimateCreator = (SEL_UnitFXCreator)(&Thor::getDieAnimate);
    
    //    unit->cost = costLevelData;
    
    return unit;
    //    } else {
    //        CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sfx_error.wav");
    //        NoResourceToDeployMessage::create(unitBean)->sendMsg();
    //        return NULL;
    //    }
}

CCAnimate* Thor::getFireAnimate(int dir) {
    CCArray* fxArray = CCArray::create();
    char str[50] = {0};
    if (dir == 0) {
        sprintf(str, "%sld",fireFxSpriteStr);
        GXFX* fx1 = GXFX::create(GXUtil::initAction(str, 1,false), fireFxStartFrame,fireFxZorder);
        fx1->setPosition(ccp(12,58));
        fx1->setScale(fireFxScale);
        
        fxArray->addObject(fx1);
        
        GXFX* fx2 = GXFX::create(GXUtil::initAction(str, 1,false), fireFxStartFrame,fireFxZorder);
        fx2->setPosition(ccp(47,36));
        fx2->setScale(fireFxScale);
        
        fxArray->addObject(fx2);
        
        sprintf(str, "%sfld",spriteFileNameStr);
    } else if(dir == 1) {
        sprintf(str, "%sd",fireFxSpriteStr);
        
        GXFX* fx1 = GXFX::create(GXUtil::initAction(str, 1,false), fireFxStartFrame,fireFxZorder);
        fx1->setPosition(ccp(50,35));
        fx1->setScale(fireFxScale);
        
        fxArray->addObject(fx1);
        
        GXFX* fx2 = GXFX::create(GXUtil::initAction(str, 1,false), fireFxStartFrame,fireFxZorder);
        fx2->setPosition(ccp(98,35));
        fx2->setScale(fireFxScale);
        
        fxArray->addObject(fx2);
        
        sprintf(str, "%sfd",spriteFileNameStr);
    } else if(dir == 2) {
        sprintf(str, "%srd",fireFxSpriteStr);
        
        GXFX* fx1 = GXFX::create(GXUtil::initAction(str, 1,false), fireFxStartFrame,fireFxZorder);
        fx1->setPosition(ccp(98,39));
        fx1->setScale(fireFxScale);
        
        fxArray->addObject(fx1);
        
        GXFX* fx2 = GXFX::create(GXUtil::initAction(str, 1,false), fireFxStartFrame,fireFxZorder);
        fx2->setPosition(ccp(131,62));
        fx2->setScale(fireFxScale);
        
        fxArray->addObject(fx2);
        
        sprintf(str, "%sfrd",spriteFileNameStr);
    } else if(dir == 3) {
        sprintf(str, "%sr",fireFxSpriteStr);
        
        GXFX* fx1 = GXFX::create(GXUtil::initAction(str, 1,false), fireFxStartFrame,fireFxZorder);
        fx1->setPosition(ccp(131,61));
        fx1->setScale(fireFxScale);
        
        fxArray->addObject(fx1);
        
        GXFX* fx2 = GXFX::create(GXUtil::initAction(str, 1,false), fireFxStartFrame,fireFxZorder);
        fx2->setPosition(ccp(131,93));
        fx2->setScale(fireFxScale);
        
        fxArray->addObject(fx2);
        
        sprintf(str, "%sfr",spriteFileNameStr);
    } else if(dir == 4) {
        sprintf(str, "%sru",fireFxSpriteStr);
        
        GXFX* fx1 = GXFX::create(GXUtil::initAction(str, 1,false), fireFxStartFrame,fireFxZorder);
        fx1->setPosition(ccp(133,95));
        fx1->setScale(fireFxScale);
        
        fxArray->addObject(fx1);
        
        GXFX* fx2 = GXFX::create(GXUtil::initAction(str, 1,false), fireFxStartFrame,-1);
        fx2->setPosition(ccp(101,117));
        fx2->setScale(fireFxScale);
        
        fxArray->addObject(fx2);
        
        sprintf(str, "%sfru",spriteFileNameStr);
    } else if(dir == 5) {
        sprintf(str, "%su",fireFxSpriteStr);
        
        GXFX* fx1 = GXFX::create(GXUtil::initAction(str, 1,false), fireFxStartFrame,fireFxZorder);
        fx1->setPosition(ccp(97,123));
        fx1->setScale(fireFxScale);
        
        fxArray->addObject(fx1);
        
        GXFX* fx2 = GXFX::create(GXUtil::initAction(str, 1,false), fireFxStartFrame,fireFxZorder);
        fx2->setPosition(ccp(46,123));
        fx2->setScale(fireFxScale);
        
        fxArray->addObject(fx2);
        
        sprintf(str, "%sfu",spriteFileNameStr);
    } else if(dir == 6) {
        sprintf(str, "%slu",fireFxSpriteStr);
        
        GXFX* fx1 = GXFX::create(GXUtil::initAction(str, 1,false), fireFxStartFrame,fireFxZorder);
        fx1->setPosition(ccp(16,95));
        fx1->setScale(fireFxScale);
        
        fxArray->addObject(fx1);
        
        GXFX* fx2 = GXFX::create(GXUtil::initAction(str, 1,false), fireFxStartFrame,-1);
        fx2->setPosition(ccp(47,118));
        fx2->setScale(fireFxScale);
        
        fxArray->addObject(fx2);
        
        sprintf(str, "%sflu",spriteFileNameStr);
    } else if(dir == 7) {
        sprintf(str, "%sl",fireFxSpriteStr);
        
        GXFX* fx1 = GXFX::create(GXUtil::initAction(str, 1,false), fireFxStartFrame,fireFxZorder);
        fx1->setPosition(ccp(11,93));
        fx1->setScale(fireFxScale);
        
        fxArray->addObject(fx1);
        
        GXFX* fx2 = GXFX::create(GXUtil::initAction(str, 1,false), fireFxStartFrame,fireFxZorder);
        fx2->setPosition(ccp(11,60));
        fx2->setScale(fireFxScale);
        
        fxArray->addObject(fx2);
        
        sprintf(str, "%sfl",spriteFileNameStr);
    }
    
    return GXAnimateWithFx::create(GXUtil::initAction(str,fireAnimateRate,fireAnimateReverse), fxArray);
}

CCAnimate* Thor::getMoveAnimate(int dir){
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

CCAnimate* Thor::getDieAnimate(int dir){
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
    } else {
        sprintf(str, "%sdld",spriteFileNameStr);
    }
    return CCAnimate::create(GXUtil::initAction(str,dieAnimateRate,dieAnimateReverse));
}

UnitBean* Thor::getUnitBean() {
    if (unitBean == NULL) {
        unitBean = UnitBean::create(ThorCardId,CCString::create(nameStr),CCString::create(spriteFileNameStr),baseCost,updateCostRate,rarity);
        unitBean->createUnit_selector = (SEL_CreateUnit)(&Thor::createUnit);
        unitBean->getUnitCardInfo_selector = (SEL_GetUnitCardInfo)(&Thor::getUnitCardDesc);
        unitBean->getAttackSprite_selector = (SEL_GetAttackSprite)(&Thor::getAttackSprite);
        unitBean->summaryOriOil = oriCost;
        unitBean->unlockNeedCount = 189225001;
        unitBean->unlockCostCount = 10000;
        unitBean->retain();
        //        unitBean->costCool = baseCostCool;
        unitBean->getCostCool_selector = (SEL_GetCostCool)(&Thor::getCostCool);
        unitBean->sfxDeployNameString = sfxDeployNameStr;
    }
    return unitBean;
}


CCLayer* Thor::getUnitCardDesc(int level,bool isAll) {
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
    
    float coolDownLevelData = MyUtil::getInstance()->updateLevelByCount(baseCostCool, level, updateCostCool);
    float coolDownMaxData = MyUtil::getInstance()->updateLevelByCount(baseCostCool, unitBean->getMaxLevel(), updateCostCool);
    
    CCSprite* coolDownIcon = CCSprite::createWithSpriteFrameName("costCoolIcon.png");
    //    attackRateIcon->setScale((30/attackRateIcon->getContentSize().width+30/attackRateIcon->getContentSize().height)/2);
    coolDownIcon->setScale(1.3);
    coolDownIcon->setPosition(ccp(40,170));
    //    attackRateIcon->setScale(24/attackRateIcon->getContentSize().width);
    layer->addChild(coolDownIcon);
    
    
    GXProgressBar* coolDownBar = GXProgressBar::create(CCSprite::create("levelBarUp.png"), CCSprite::create("BarDown.png"));
    
    coolDownBar->setContentSize(CCSizeMake(416,20));
    coolDownBar->updatePercentage((100/coolDownLevelData)/(100/coolDownMaxData));
    
    coolDownBar->setPosition(ccp(70,147));
    
    
    sprintf(str, "同时派遣数量:%d",(int)(100/coolDownLevelData+0.001));
    CCLabelTTF* costCoolLabel = CCLabelTTF::create(str, "Arial", 24);
    costCoolLabel->setAnchorPoint(ccp(0,0));
    costCoolLabel->setColor(ccc3(238,204,122));
    costCoolLabel->setPosition(ccp(70,162));
    layer->addChild(coolDownBar);
    layer->addChild(costCoolLabel);
    
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

CCSprite* Thor::getAttackSprite(int dir) {
    CCSprite* army;
    CCAnimate* action;
    char str[50] = {0};
    if (dir == attackLD) {
        sprintf(str,"%smru (0).png",spriteFileNameStr);
        army = CCSprite::createWithSpriteFrameName(str);
        action = Thor::getMoveAnimate(4);
    } else if(dir == attackRD) {
        sprintf(str,"%smlu (0).png",spriteFileNameStr);
        army = CCSprite::createWithSpriteFrameName(str);
        action = Thor::getMoveAnimate(6);
    } else if(dir == attackLU) {
        sprintf(str,"%smrd (0).png",spriteFileNameStr);
        army = CCSprite::createWithSpriteFrameName(str);
        action = Thor::getMoveAnimate(2);
    } else {
        sprintf(str,"%smld (0).png",spriteFileNameStr);
        army = CCSprite::createWithSpriteFrameName(str);
        action = Thor::getMoveAnimate(0);
    }
    army->setContentSize(CCSizeMake(200,200));
    army->runAction(CCRepeatForever::create(action));
    return army;
}

float Thor::getCostCool(int level) {
    return MyUtil::getInstance()->updateLevelByCount(baseCostCool, level, updateCostCool);;
}