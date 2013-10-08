//
//  ResourceOnlyBeRobberState.cpp
//  ww3
//
//  Created by xiao tang on 12-11-17.
//
//

#include "ResourceOnlyBeRobberState.h"
#include "Mathlib.h"
#include "MyUnit.h"
#include "MyGameInfo.h"
#include "BattleScene.h"

ResourceOnlyBeRobberState* ResourceOnlyBeRobberState::create(int _stateId, CCSprite *item, float life) {
    ResourceOnlyBeRobberState* pState = new ResourceOnlyBeRobberState();
    pState->stateId = _stateId;
    pState->autorelease();
    pState->life = life;
    pState->maxLife = life;
    //  CCSprite* grayBd = CCSprite::create(string);
    //    grayBd->setColor(ccGRAY);
    pState->item = item;
    pState->item->retain();
//    pState->oil = oil;
//    pState->nowOil =oil;
//    pState->iron = iron;
//    pState->nowIron = iron;
    
    return pState;
}

bool ResourceOnlyBeRobberState::beAttack(float damage) {
    
    float life = this->life - damage;
    float chaOil = nowOil - (Mathlib::max(life,0)/maxLife)*oil;
    robberOil+=chaOil;
    MyGameInfo::getInstance()->changeResource(oilTag, chaOil);
    nowOil = (Mathlib::max(life,0)/maxLife)*oil;
    BattleScene* battleScene = (BattleScene*)building->getParent()->getParent();
    if(battleScene->enemyOilLabel->getTargetNumber()>5) {
        battleScene->enemyOilLabel->setNumber(battleScene->enemyOilLabel->getTargetNumber()-chaOil);
        MyGameInfo::getInstance()->enemyOil-=chaOil;
        MyGameInfo::getInstance()->enemyDeltaOil -= chaOil;
    } else {
        battleScene->enemyOilLabel->setNumber(0);
    }
    float chaIron = nowIron - (Mathlib::max(life,0)/maxLife)*iron;
    robberIron+=chaIron;
    MyGameInfo::getInstance()->changeResource(ironTag, chaIron);
    nowIron = (Mathlib::max(life,0)/maxLife)*iron;
    if(battleScene->enemyIronLabel->getTargetNumber()>5) {
        battleScene->enemyIronLabel->setNumber(battleScene->enemyIronLabel->getTargetNumber()-chaIron);
         MyGameInfo::getInstance()->enemyIron-=chaIron;
        MyGameInfo::getInstance()->enemyDeltaIron -= chaIron;
    }else {
        battleScene->enemyIronLabel->setNumber(0);
    }
    return BeAttackState::beAttack(damage);
}

void ResourceOnlyBeRobberState::setIron(float iron) {
    this->iron = iron;
    nowIron = iron;
}

void ResourceOnlyBeRobberState::setOil(float oil) {
    this->oil = oil;
    nowOil = oil;
}

float ResourceOnlyBeRobberState::getIron() {
    return iron;
}

float ResourceOnlyBeRobberState::getOil() {
    return oil;
}
