//
//  Garade.cpp
//  ww4
//
//  Created by xiao tang on 13-5-7.
//
//

#include "Garade.h"
#include "MyUtil.h"
#include "MoveToAttack.h"
#include "AttackState.h"
#include "SimpleAudioEngine.h"


#define nameStr "步枪兵"
#define rarity 2

#define baseSpeed 1
#define baseAttackRange 4
#define baseDamage 8
#define baseHealth 20
#define baseCost 40

#define updateHealthRate 0
#define updateDamageRate 1
#define updateCostRate 1
#define updateSpeedRate 0.2

#define sfxDeployNameStr "sfx_deploySoldier.m4a"
#define sfxFireNameStr "sfx_garade.mp3"
#define spriteFileNameStr "bubing1"

#define moveAnimateRate 0.1
#define fireAnimateRate 0.1
#define dieAnimateRate 0.1

#define moveAnimateReverse false
#define fireAnimateReverse false
#define dieAnimateReverse false

#define baseCostCool 0.5

UnitBean* Garade::unitBean = NULL;

MyUnit* Garade::createUnit(int level) {
    //    float costLevelData = 100;
    //    costLevelData = MyUtil::getInstance()->updateLevelByRate(0,baseCost, level, updateCostRate);
    //    if(MyGameInfo::getInstance()->getOil()-costLevelData>=0) {
    float speedLevelData = 0;
    float damageLevelData = 0;
    float healthLevelData = 0;
    speedLevelData = MyUtil::getInstance()->updateLevelByCount(baseSpeed, level, updateSpeedRate);
    healthLevelData = MyUtil::getInstance()->updateLevelByRate(0,baseHealth, level, updateHealthRate);
    damageLevelData = MyUtil::getInstance()->updateLevelByRate(0,baseDamage, level, updateDamageRate);
    
    MoveToAttack* moveToAttack = MoveToAttack::create(MoveToAttackTag,speedLevelData,baseAttackRange);
    AttackState* attack = AttackState::create(AttackStateTag,CCString::create(sfxFireNameStr), baseAttackRange,damageLevelData,100);
    moveToAttack->addTransition(toAttackTransition, AttackStateTag);
    attack->addTransition(toMoveTransition, MoveToAttackTag);
    MyUnit* unit = MyUnit::create(moveToAttack,healthLevelData,1,level);
    unit->addState(attack);
    unit->mode = soldier;
    
    //        CCArray* moveArray[8];
    //        for (int i = 0; i<8; i++) {
    //            moveArray[i] = CCArray::create();
    //        }
    //        CCArray* fireArray[8];
    //        for (int i = 0; i<8; i++) {
    //            fireArray[i] = CCArray::create();
    //        }
    //        CCArray* dieArray[8];
    //        for (int i = 0; i<8; i++) {
    //            dieArray[i] = CCArray::create();
    //        }
    
    //        CCObject* obj;
    //        UnitFXCreator* fxCreator = NULL;
    //        CCARRAY_FOREACH(fxArray, obj) {
    //            fxCreator  = (UnitFXCreator*)obj;
    //            if (fxCreator->getActionName()->compare("move") == 0) {
    //                GXFX* fx = GXFX::create(GXUtil::initAction(fxCreator->getFxname()->getCString(), 1,false), fxCreator->startFrameCount,fxCreator->zOrder);
    //                fx->setPosition(ccp(fxCreator->posX,fxCreator->posY));
    //                fx->setScale(fxCreator->scale);
    //                moveArray[fxCreator->dir]->addObject(fx);
    //            } else if (fxCreator->getActionName()->compare("fire") == 0) {
    //                GXFX* fx = GXFX::create(GXUtil::initAction(fxCreator->getFxname()->getCString(), 1,false), fxCreator->startFrameCount,fxCreator->zOrder);
    //                fx->setPosition(ccp(fxCreator->posX,fxCreator->posY));
    //                fx->setScale(fxCreator->scale);
    //                fireArray[fxCreator->dir]->addObject(fx);
    //            }else if (fxCreator->getActionName()->compare("die") == 0) {
    //                GXFX* fx = GXFX::create(GXUtil::initAction(fxCreator->getFxname()->getCString(), 1,false), fxCreator->startFrameCount,fxCreator->zOrder);
    //                fx->setPosition(ccp(fxCreator->posX,fxCreator->posY));
    //                fx->setScale(fxCreator->scale);
    //                dieArray[fxCreator->dir]->addObject(fx);
    //            }
    //        }
    //        char str[64] = {0};
    //        sprintf(str, "%smld",spriteFileName->getCString());
    //        if (moveArray[0]->count() == 0) {
    //            unit->move[0] = CCAnimate::create(GXUtil::initAction(str,moveAnimateRate,moveAnimateReverse));
    //        } else {
    //            unit->move[0] = GXAnimateWithFx::create(GXUtil::initAction(str,moveAnimateRate,moveAnimateReverse), moveArray[0]);
    //        }
    //        CC_SAFE_RETAIN(unit->move[0]);
    //
    //        sprintf(str, "%smd",spriteFileName->getCString());
    //        if (moveArray[1]->count() == 0) {
    //            unit->move[1] = CCAnimate::create(GXUtil::initAction(str,moveAnimateRate,moveAnimateReverse));
    //        } else {
    //            unit->move[1] = GXAnimateWithFx::create(GXUtil::initAction(str,moveAnimateRate,moveAnimateReverse), moveArray[1]);
    //        }
    //        CC_SAFE_RETAIN(unit->move[1]);
    //
    //        sprintf(str, "%smrd",spriteFileName->getCString());
    //        if (moveArray[2]->count() == 0) {
    //            unit->move[2] = CCAnimate::create(GXUtil::initAction(str,moveAnimateRate,moveAnimateReverse));
    //        } else {
    //            unit->move[2] = GXAnimateWithFx::create(GXUtil::initAction(str,moveAnimateRate,moveAnimateReverse), moveArray[2]);
    //        }
    //        CC_SAFE_RETAIN(unit->move[2]);
    //
    //        sprintf(str, "%smr",spriteFileName->getCString());
    //        if (moveArray[3]->count() == 0) {
    //            unit->move[3] = CCAnimate::create(GXUtil::initAction(str,moveAnimateRate,moveAnimateReverse));
    //        } else {
    //            unit->move[3] = GXAnimateWithFx::create(GXUtil::initAction(str,moveAnimateRate,moveAnimateReverse), moveArray[3]);
    //        }
    //        CC_SAFE_RETAIN(unit->move[3]);
    //
    //        sprintf(str, "%smru",spriteFileName->getCString());
    //        if (moveArray[4]->count() == 0) {
    //            unit->move[4] = CCAnimate::create(GXUtil::initAction(str,moveAnimateRate,moveAnimateReverse));
    //        } else {
    //            unit->move[4] = GXAnimateWithFx::create(GXUtil::initAction(str,moveAnimateRate,moveAnimateReverse), moveArray[4]);
    //        }
    //        CC_SAFE_RETAIN(unit->move[4]);
    //
    //        sprintf(str, "%smu",spriteFileName->getCString());
    //        if (moveArray[5]->count() == 0) {
    //            unit->move[5] = CCAnimate::create(GXUtil::initAction(str,moveAnimateRate,moveAnimateReverse));
    //        } else {
    //            unit->move[5] = GXAnimateWithFx::create(GXUtil::initAction(str,moveAnimateRate,moveAnimateReverse), moveArray[5]);
    //        }
    //        CC_SAFE_RETAIN(unit->move[5]);
    //
    //        sprintf(str, "%smlu",spriteFileName->getCString());
    //        if (moveArray[6]->count() == 0) {
    //            unit->move[6] = CCAnimate::create(GXUtil::initAction(str,moveAnimateRate,moveAnimateReverse));
    //        } else {
    //            unit->move[6] = GXAnimateWithFx::create(GXUtil::initAction(str,moveAnimateRate,moveAnimateReverse), moveArray[6]);
    //        }
    //        CC_SAFE_RETAIN(unit->move[6]);
    //
    //        sprintf(str, "%sml",spriteFileName->getCString());
    //        if (moveArray[7]->count() == 0) {
    //            unit->move[7] = CCAnimate::create(GXUtil::initAction(str,moveAnimateRate,moveAnimateReverse));
    //        } else {
    //            unit->move[7] = GXAnimateWithFx::create(GXUtil::initAction(str,moveAnimateRate,moveAnimateReverse), moveArray[7]);
    //        }
    //        CC_SAFE_RETAIN(unit->move[7]);
    //
    //
    //        sprintf(str, "%sfld",spriteFileName->getCString());
    //        if (fireArray[0]->count() == 0) {
    //            unit->fire[0] = CCAnimate::create(GXUtil::initAction(str,fireAnimateRate,fireAnimateReverse));
    //        } else {
    //            unit->fire[0] = GXAnimateWithFx::create(GXUtil::initAction(str,fireAnimateRate,fireAnimateReverse), fireArray[0]);
    //        }
    //        CC_SAFE_RETAIN(unit->fire[0]);
    //
    //        sprintf(str, "%sfd",spriteFileName->getCString());
    //        if (fireArray[1]->count() == 0) {
    //            unit->fire[1] = CCAnimate::create(GXUtil::initAction(str,fireAnimateRate,fireAnimateReverse));
    //        } else {
    //            unit->fire[1] = GXAnimateWithFx::create(GXUtil::initAction(str,fireAnimateRate,fireAnimateReverse), fireArray[1]);
    //        }
    //        CC_SAFE_RETAIN(unit->fire[1]);
    //
    //        sprintf(str, "%sfrd",spriteFileName->getCString());
    //        if (fireArray[2]->count() == 0) {
    //            unit->fire[2] = CCAnimate::create(GXUtil::initAction(str,fireAnimateRate,fireAnimateReverse));
    //        } else {
    //            unit->fire[2] = GXAnimateWithFx::create(GXUtil::initAction(str,fireAnimateRate,fireAnimateReverse), fireArray[2]);
    //        }
    //        CC_SAFE_RETAIN(unit->fire[2]);
    //
    //        sprintf(str, "%sfr",spriteFileName->getCString());
    //        if (fireArray[3]->count() == 0) {
    //            unit->fire[3] = CCAnimate::create(GXUtil::initAction(str,fireAnimateRate,fireAnimateReverse));
    //        } else {
    //            unit->fire[3] = GXAnimateWithFx::create(GXUtil::initAction(str,fireAnimateRate,fireAnimateReverse), fireArray[3]);
    //        }
    //        CC_SAFE_RETAIN(unit->fire[3]);
    //
    //        sprintf(str, "%sfru",spriteFileName->getCString());
    //        if (fireArray[4]->count() == 0) {
    //            unit->fire[4] = CCAnimate::create(GXUtil::initAction(str,fireAnimateRate,fireAnimateReverse));
    //        } else {
    //            unit->fire[4] = GXAnimateWithFx::create(GXUtil::initAction(str,fireAnimateRate,fireAnimateReverse), fireArray[4]);
    //        }
    //        CC_SAFE_RETAIN(unit->fire[4]);
    //
    //        sprintf(str, "%sfu",spriteFileName->getCString());
    //        if (fireArray[5]->count() == 0) {
    //            unit->fire[5] = CCAnimate::create(GXUtil::initAction(str,fireAnimateRate,fireAnimateReverse));
    //        } else {
    //            unit->fire[5] = GXAnimateWithFx::create(GXUtil::initAction(str,fireAnimateRate,fireAnimateReverse), fireArray[5]);
    //        }
    //        CC_SAFE_RETAIN(unit->fire[5]);
    //
    //        sprintf(str, "%sflu",spriteFileName->getCString());
    //        if (fireArray[6]->count() == 0) {
    //            unit->fire[6] = CCAnimate::create(GXUtil::initAction(str,fireAnimateRate,fireAnimateReverse));
    //        } else {
    //            unit->fire[6] = GXAnimateWithFx::create(GXUtil::initAction(str,fireAnimateRate,fireAnimateReverse), fireArray[6]);
    //        }
    //        CC_SAFE_RETAIN(unit->fire[6]);
    //
    //        sprintf(str, "%sfl",spriteFileName->getCString());
    //        if (fireArray[7]->count() == 0) {
    //            unit->fire[7] = CCAnimate::create(GXUtil::initAction(str,fireAnimateRate,fireAnimateReverse));
    //        } else {
    //            unit->fire[7] = GXAnimateWithFx::create(GXUtil::initAction(str,fireAnimateRate,fireAnimateReverse), fireArray[7]);
    //        }
    //        CC_SAFE_RETAIN(unit->fire[7]);
    //
    //        sprintf(str, "%sdld",spriteFileName->getCString());
    //        if (dieArray[0]->count() == 0) {
    //            unit->die[0] = CCAnimate::create(GXUtil::initAction(str,dieAnimateRate,dieAnimateRerverse));
    //        } else {
    //            unit->die[0] = GXAnimateWithFx::create(GXUtil::initAction(str,dieAnimateRate,dieAnimateRerverse), dieArray[0]);
    //        }
    //        CC_SAFE_RETAIN(unit->die[0]);
    //
    //        sprintf(str, "%sdd",spriteFileName->getCString());
    //        if (dieArray[1]->count() == 0) {
    //            unit->die[1] = CCAnimate::create(GXUtil::initAction(str,dieAnimateRate,dieAnimateRerverse));
    //        } else {
    //            unit->die[1] = GXAnimateWithFx::create(GXUtil::initAction(str,dieAnimateRate,dieAnimateRerverse), dieArray[1]);
    //        }
    //        CC_SAFE_RETAIN(unit->die[1]);
    //
    //        sprintf(str, "%sdrd",spriteFileName->getCString());
    //        if (dieArray[2]->count() == 0) {
    //            unit->die[2] = CCAnimate::create(GXUtil::initAction(str,dieAnimateRate,dieAnimateRerverse));
    //        } else {
    //            unit->die[2] = GXAnimateWithFx::create(GXUtil::initAction(str,dieAnimateRate,dieAnimateRerverse), dieArray[2]);
    //        }
    //        CC_SAFE_RETAIN(unit->die[2]);
    //
    //        sprintf(str, "%sdr",spriteFileName->getCString());
    //        if (dieArray[3]->count() == 0) {
    //            unit->die[3] = CCAnimate::create(GXUtil::initAction(str,dieAnimateRate,dieAnimateRerverse));
    //        } else {
    //            unit->die[3] = GXAnimateWithFx::create(GXUtil::initAction(str,dieAnimateRate,dieAnimateRerverse), dieArray[3]);
    //        }
    //        CC_SAFE_RETAIN(unit->die[3]);
    //
    //        sprintf(str, "%sdru",spriteFileName->getCString());
    //        if (dieArray[4]->count() == 0) {
    //            unit->die[4] = CCAnimate::create(GXUtil::initAction(str,dieAnimateRate,dieAnimateRerverse));
    //        } else {
    //            unit->die[4] = GXAnimateWithFx::create(GXUtil::initAction(str,dieAnimateRate,dieAnimateRerverse), dieArray[4]);
    //        }
    //        CC_SAFE_RETAIN(unit->die[4]);
    //
    //        sprintf(str, "%sdu",spriteFileName->getCString());
    //        if (dieArray[5]->count() == 0) {
    //            unit->die[5] = CCAnimate::create(GXUtil::initAction(str,dieAnimateRate,dieAnimateRerverse));
    //        } else {
    //            unit->die[5] = GXAnimateWithFx::create(GXUtil::initAction(str,dieAnimateRate,dieAnimateRerverse), dieArray[5]);
    //        }
    //        CC_SAFE_RETAIN(unit->die[5]);
    //
    //        sprintf(str, "%sdlu",spriteFileName->getCString());
    //        if (dieArray[6]->count() == 0) {
    //            unit->die[6] = CCAnimate::create(GXUtil::initAction(str,dieAnimateRate,dieAnimateRerverse));
    //        } else {
    //            unit->die[6] = GXAnimateWithFx::create(GXUtil::initAction(str,dieAnimateRate,dieAnimateRerverse), dieArray[6]);
    //        }
    //        CC_SAFE_RETAIN(unit->die[6]);
    //
    //        sprintf(str, "%sdl",spriteFileName->getCString());
    //        if (dieArray[7]->count() == 0) {
    //            unit->die[7] = CCAnimate::create(GXUtil::initAction(str,dieAnimateRate,dieAnimateRerverse));
    //        } else {
    //            unit->die[7] = GXAnimateWithFx::create(GXUtil::initAction(str,dieAnimateRate,dieAnimateRerverse), dieArray[7]);
    //        }
    //        CC_SAFE_RETAIN(unit->die[7]);
    //
    //        CCAction* action = CCRepeatForever::create(unit->move[0]);
    //        action->setTag(currentAction);
    //        unit->runAction(action);
    //
    //    MyGameInfo::getInstance()->changeResource(oilTag, -costLevelData);
    //    CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(sfxDeployNameStr);
    
    unit->moveAnimateCreator = (SEL_UnitFXCreator)(&Garade::getMoveAnimate);
    unit->fireAnimateCreator = (SEL_UnitFXCreator)(&Garade::getFireAnimate);
    unit->dieAnimateCreator = (SEL_UnitFXCreator)(&Garade::getDieAnimate);
    
    //    unit->cost = costLevelData;
    
    return unit;
    //    } else {
    //        CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sfx_error.wav");
    //        NoResourceToDeployMessage::create(unitBean)->sendMsg();
    //        return NULL;
    //    }
}

CCAnimate* Garade::getFireAnimate(int dir) {
    char str[40] = {0};
    if (dir == 0) {
        sprintf(str, "%sfld",spriteFileNameStr);
    } else if(dir == 1) {
        sprintf(str, "%sfd",spriteFileNameStr);
    } else if(dir == 2) {
        sprintf(str, "%sfrd",spriteFileNameStr);
    } else if(dir == 3) {
        sprintf(str, "%sfr",spriteFileNameStr);
    } else if(dir == 4) {
        sprintf(str, "%sfru",spriteFileNameStr);
    } else if(dir == 5) {
        sprintf(str, "%sfu",spriteFileNameStr);
    } else if(dir == 6) {
        sprintf(str, "%sflu",spriteFileNameStr);
    } else if(dir == 7) {
        sprintf(str, "%sfl",spriteFileNameStr);
    }
    return CCAnimate::create(GXUtil::initAction(str,fireAnimateRate,fireAnimateReverse));
    
}

CCAnimate* Garade::getMoveAnimate(int dir){
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

CCAnimate* Garade::getDieAnimate(int dir){
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

UnitBean* Garade::getUnitBean() {
    if (unitBean == NULL) {
        unitBean = UnitBean::create(garadeCardId,CCString::create(nameStr),CCString::create(spriteFileNameStr),baseCost,updateCostRate,rarity);
        unitBean->createUnit_selector = (SEL_CreateUnit)(&Garade::createUnit);
        unitBean->getUnitCardInfo_selector = (SEL_GetUnitCardInfo)(&Garade::getUnitCardDesc);
        unitBean->getAttackSprite_selector = (SEL_GetAttackSprite)(&Garade::getAttackSprite);
        unitBean->retain();
        unitBean->costCool = baseCostCool;
        unitBean->sfxDeployNameString = sfxDeployNameStr;
    }
    return unitBean;
}


CCLayer* Garade::getUnitCardDesc(int level,bool isAll) {
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

CCSprite* Garade::getAttackSprite(int dir) {
    CCSprite* army;
    CCAnimate* action;
    char str[50] = {0};
    if (dir == attackLD) {
        sprintf(str,"%smru (0).png",spriteFileNameStr);
        army = CCSprite::createWithSpriteFrameName(str);
        action = Garade::getMoveAnimate(4);
    } else if(dir == attackRD) {
        sprintf(str,"%smlu (0).png",spriteFileNameStr);
        army = CCSprite::createWithSpriteFrameName(str);
        action = Garade::getMoveAnimate(6);
    } else if(dir == attackLU) {
        sprintf(str,"%smrd (0).png",spriteFileNameStr);
        army = CCSprite::createWithSpriteFrameName(str);
        action = Garade::getMoveAnimate(2);
    } else {
        sprintf(str,"%smld (0).png",spriteFileNameStr);
        army = CCSprite::createWithSpriteFrameName(str);
        action = Garade::getMoveAnimate(0);
    }
    army->runAction(CCRepeatForever::create(action));
    return army;
}