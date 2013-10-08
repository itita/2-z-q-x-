//
//  Calliope.cpp
//  ww4
//
//  Created by xiao tang on 13-5-9.
//
//

#include "Calliope.h"

#include "MyUtil.h"
#include "MoveToAttack.h"
#include "CurvedAttackState.h"
#include "SimpleAudioEngine.h"
#include "GXFX.h"
#include "GXAnimateWithFx.h"
#include "SimpleAudioEngine.h"
#include "NoResourceToDeployMessage.h"

#define nameStr "管风琴火箭炮"
#define rarity 5

#define baseSpeed 1
#define baseAttackRange 8
#define baseDamage 20
#define baseHealth 80
#define baseCost 180

#define updateHealthRate 2
#define updateDamageRate 3
#define updateCostRate 2.5
#define updateSpeedRate 0

#define sfxDeployNameStr "sfx_deployTank.m4a"
#define sfxFireNameStr "sfx_rocket.mp3"
#define spriteFileNameStr "Calliope"

#define moveAnimateRate 0.2
#define fireAnimateRate 0.15
#define dieAnimateRate 0.1

#define moveAnimateReverse false
#define fireAnimateReverse true
#define dieAnimateReverse false

#define fireFxStartFrame 0
#define fireFxZorder 1
#define fireFxScale 1
//#define fireFxSpriteStr "firelight"

#define attackRate 1

//#define baseCostCool 1.5
#define baseCostCool 3

UnitBean* Calliope::unitBean = NULL;

MyUnit* Calliope::createUnit(int level) {
//    float costLevelData = 100;
//    costLevelData = MyUtil::getInstance()->updateLevelByRate(0,baseCost, level, updateCostRate);
//    if(MyGameInfo::getInstance()->getOil()-costLevelData>=0) {
    float speedLevelData = 0;
    float damageLevelData = 0;
    
    float healthLevelData = 0;
    speedLevelData = MyUtil::getInstance()->updateLevelByCount(baseSpeed, level, updateSpeedRate);
    healthLevelData = MyUtil::getInstance()->updateLevelByRate(0,baseHealth, level, updateHealthRate);
    damageLevelData = MyUtil::getInstance()->updateLevelByRate(0,baseDamage, level, updateDamageRate);
    
    
    
    MoveToAttack* moveToAttack = MoveToAttack::create(MoveToAttackTag,speedLevelData*attackRate,baseAttackRange);
    CurvedAttackState* attack = CurvedAttackState::create(AttackStateTag,CCString::create(sfxFireNameStr), baseAttackRange,damageLevelData*attackRate,1000);
    moveToAttack->addTransition(toAttackTransition, AttackStateTag);
    attack->addTransition(toMoveTransition, MoveToAttackTag);
    MyUnit* unit = MyUnit::create(moveToAttack,healthLevelData,attackRate,level);
    unit->addState(attack);
    unit->mode = heavyVehicles;
//    MyGameInfo::getInstance()->changeResource(oilTag, -costLevelData);
//    CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(sfxDeployNameStr);
    
    unit->moveAnimateCreator = (SEL_UnitFXCreator)(&Calliope::getMoveAnimate);
    unit->fireAnimateCreator = (SEL_UnitFXCreator)(&Calliope::getFireAnimate);
    unit->dieAnimateCreator = (SEL_UnitFXCreator)(&Calliope::getDieAnimate);
    
//    unit->cost = costLevelData;
    
    return unit;
//    } else {
//        CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sfx_error.wav");
//        NoResourceToDeployMessage::create(unitBean)->sendMsg();
//        return NULL;
//    }
}

CCAnimate* Calliope::getFireAnimate(int dir) {
    char str[40] = {0};
    CCArray* fxArray = CCArray::create();
    if (dir == 0) {
        
        GXFX* fx1 = GXFX::create(GXUtil::initAction("rockettailld", 1,false), fireFxStartFrame,1);
        fx1->setPosition(ccp(83,101));
        
        fxArray->addObject(fx1);
        
        GXFX* fx2 = GXFX::create(GXUtil::initAction("rocketheadld", 1,false), fireFxStartFrame,1);
        fx2->setScale(0.7);
        fx2->setPosition(ccp(21,76));
        
        fxArray->addObject(fx2);
        
        
        sprintf(str, "%sfld",spriteFileNameStr);
    } else if(dir == 1) {
        GXFX* fx1 = GXFX::create(GXUtil::initAction("rockettaild", 1,false), fireFxStartFrame,-1);
        fx1->setPosition(ccp(57,102));
        
        fxArray->addObject(fx1);
        
        GXFX* fx2 = GXFX::create(GXUtil::initAction("rocketheadd", 1,false), fireFxStartFrame,1);
        fx2->setScale(0.7);
        fx2->setPosition(ccp(57,58));
        
        fxArray->addObject(fx2);
        
        sprintf(str, "%sfd",spriteFileNameStr);
    } else if(dir == 2) {
        GXFX* fx1 = GXFX::create(GXUtil::initAction("rockettailrd", 1,false), fireFxStartFrame,1);
        fx1->setPosition(ccp(35,89));
        
        fxArray->addObject(fx1);
        
        GXFX* fx2 = GXFX::create(GXUtil::initAction("rocketheadrd", 1,false), fireFxStartFrame,1);
        fx2->setScale(0.7);
        fx2->setPosition(ccp(97,66));
        
        fxArray->addObject(fx2);
        
        sprintf(str, "%sfrd",spriteFileNameStr);
    } else if(dir == 3) {
        GXFX* fx1 = GXFX::create(GXUtil::initAction("rockettailr", 1,false), fireFxStartFrame,1);
        fx1->setPosition(ccp(23,72));
        
        fxArray->addObject(fx1);
        
        GXFX* fx2 = GXFX::create(GXUtil::initAction("rocketheadr", 1,false), fireFxStartFrame,1);
        fx2->setScale(0.7);
        fx2->setPosition(ccp(127,87));
        
        fxArray->addObject(fx2);
        sprintf(str, "%sfr",spriteFileNameStr);
    } else if(dir == 4) {
        
        GXFX* fx1 = GXFX::create(GXUtil::initAction("rockettailru", 1,false), fireFxStartFrame,1);
        fx1->setPosition(ccp(58,59));
        
        fxArray->addObject(fx1);
        
        GXFX* fx2 = GXFX::create(GXUtil::initAction("rocketheadru", 1,false), fireFxStartFrame,1);
        fx2->setScale(0.7);
        fx2->setPosition(ccp(119,114));
        
        fxArray->addObject(fx2);
        
        sprintf(str, "%sfru",spriteFileNameStr);
    } else if(dir == 5) {
        GXFX* fx1 = GXFX::create(GXUtil::initAction("rockettailu", 1,false), fireFxStartFrame,1);
        fx1->setPosition(ccp(57,62));
        
        fxArray->addObject(fx1);
        
        GXFX* fx2 = GXFX::create(GXUtil::initAction("rocketheadu", 1,false), fireFxStartFrame,1);
        fx2->setScale(0.7);
        fx2->setPosition(ccp(57,133));
        fxArray->addObject(fx2);
        sprintf(str, "%sfu",spriteFileNameStr);
    } else if(dir == 6) {
        GXFX* fx1 = GXFX::create(GXUtil::initAction("rockettaillu", 1,false), fireFxStartFrame,1);
        fx1->setPosition(ccp(85,58));
        
        fxArray->addObject(fx1);
        
        GXFX* fx2 = GXFX::create(GXUtil::initAction("rocketheadlu", 1,false), fireFxStartFrame,1);
        fx2->setScale(0.7);
        fx2->setPosition(ccp(24,116));
        fxArray->addObject(fx2);
        sprintf(str, "%sflu",spriteFileNameStr);
    } else if(dir == 7) {
        GXFX* fx1 = GXFX::create(GXUtil::initAction("rockettaill", 1,false), fireFxStartFrame,1);
        fx1->setPosition(ccp(105,69));
        
        fxArray->addObject(fx1);
        
        GXFX* fx2 = GXFX::create(GXUtil::initAction("rocketheadl", 1,false), fireFxStartFrame,1);
        fx2->setScale(0.7);
        fx2->setPosition(ccp(17,83));
        fxArray->addObject(fx2);
        sprintf(str, "%sfl",spriteFileNameStr);
    }
    
    return GXAnimateWithFx::create(GXUtil::initAction(str,fireAnimateRate,fireAnimateReverse), fxArray);;
    
}

CCAnimate* Calliope::getMoveAnimate(int dir){
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

CCAnimate* Calliope::getDieAnimate(int dir){
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

UnitBean* Calliope::getUnitBean() {
    if (unitBean == NULL) {
        unitBean = UnitBean::create(CalliopeCardId,CCString::create(nameStr),CCString::create(spriteFileNameStr),baseCost,updateCostRate,rarity);
        unitBean->createUnit_selector = (SEL_CreateUnit)(&Calliope::createUnit);
        unitBean->getUnitCardInfo_selector = (SEL_GetUnitCardInfo)(&Calliope::getUnitCardDesc);
        unitBean->getAttackSprite_selector = (SEL_GetAttackSprite)(&Calliope::getAttackSprite);
        unitBean->unlockNeedCount = 44100001;
        unitBean->unlockCostCount = 1500;
        unitBean->retain();
        unitBean->costCool = baseCostCool;
        unitBean->sfxDeployNameString = sfxDeployNameStr;
    }
    return unitBean;
}


CCLayer* Calliope::getUnitCardDesc(int level,bool isAll) {
    CCLayer* layer = CCLayer::create();
    float attackLevelData = MyUtil::getInstance()->updateLevelByRate(0,baseDamage, level, updateDamageRate);
    float attackMaxData = MyUtil::getInstance()->updateLevelByRate(0,baseDamage, unitBean->getMaxLevel(), updateDamageRate);
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
    
    float healthLevelData = MyUtil::getInstance()->updateLevelByRate(0,baseHealth, level, updateHealthRate);
    float healthMaxData = MyUtil::getInstance()->updateLevelByRate(0,baseHealth, unitBean->getMaxLevel(),updateHealthRate);
    
    
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
    
    float costLevelData = MyUtil::getInstance()->updateLevelByRate(0,baseCost, level, updateCostRate);
    float costMaxData = MyUtil::getInstance()->updateLevelByRate(0,baseCost, unitBean->getMaxLevel(), updateCostRate);
    
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

CCSprite* Calliope::getAttackSprite(int dir) {
    CCSprite* army;
    CCAnimate* action;
    char str[50] = {0};
    if (dir == attackLD) {
        sprintf(str,"%smru (0).png",spriteFileNameStr);
        army = CCSprite::createWithSpriteFrameName(str);
        action = Calliope::getMoveAnimate(4);
    } else if(dir == attackRD) {
        sprintf(str,"%smlu (0).png",spriteFileNameStr);
        army = CCSprite::createWithSpriteFrameName(str);
        action = Calliope::getMoveAnimate(6);
    } else if(dir == attackLU) {
        sprintf(str,"%smrd (0).png",spriteFileNameStr);
        army = CCSprite::createWithSpriteFrameName(str);
        action = Calliope::getMoveAnimate(2);
    } else {
        sprintf(str,"%smld (0).png",spriteFileNameStr);
        army = CCSprite::createWithSpriteFrameName(str);
        action = Calliope::getMoveAnimate(0);
    }
    army->runAction(CCRepeatForever::create(action));
    return army;
}