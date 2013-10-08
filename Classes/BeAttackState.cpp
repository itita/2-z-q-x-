//
//  BeAttackState.cpp
//  ww2
//
//  Created by DingYu Fu on 12-9-9.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "BeAttackState.h"
#include "DefineSet.h"
#include "MyGameInfo.h"
#include "BattleScene.h"
#include "Mathlib.h"
#include "MyGameFactory.h"

//#include "MyTiledMenuItemSprite.h"
BeAttackState::~BeAttackState() {
//    xuetiao->release();
}

BeAttackState* BeAttackState::create(int _stateId, CCSprite* item,float life) {
    BeAttackState* pState = new BeAttackState();
    pState->stateId = _stateId;
    pState->autorelease();
    pState->life = life;
    pState->maxLife = life;
    //  CCSprite* grayBd = CCSprite::create(string);
//    grayBd->setColor(ccGRAY);
    pState->item = item;
    pState->item->retain();
    
    
    
    return pState;
}


void BeAttackState::init(MyBattleBuilding *building) {
    MyBattleState::init(building);
    item->setTag(mainTiledSpriteTag);
    CCSize normalCost = CCSizeMake(building->contentSizeByTiled.width+2, building->contentSizeByTiled.height+2);
    if (building->costRange.width < normalCost.width && building->costRange.height <normalCost.height) {
        building->costRange = normalCost;
    }
    this->building = building;
//    CCSprite* xuetiao = CCSprite::create("xuetiao.png");
//    xuetiao->setScale((building->contentSizeByTiled.width)/xuetiao->getContentSize().width);
//    progressTimer = CCProgressTimer::create(xuetiao);
////    progressTimer->setScale((building->contentSizeByTiled.width*60)/xuetiao->getContentSize().width);
//    xuetiao->setPosition(ccp(0,building->contentSizeByTiled.height/2*30));
////    progressTimer->setOpacity(255);
////    progressTimer->setColor(ccRED);
//    progressTimer->setPosition(ccp(0,building->contentSizeByTiled.height/2*30));
//    progressTimer->setType(kCCProgressTimerTypeBar);
//    progressTimer->setPercentage(100);
    
}

bool BeAttackState::beAttack(float damage) {
    this->life = life-damage;
    
    if(life < 0) {
        if (building->getTag() == zhihuisuoTag) {
            //
            ((BattleScene*)building->map->getParent())->toVictory();
        }
        building->dispose();
        return false;
    } else {
        if (xuetiao == NULL) {
            xuetiao=MyXueTiao::create("xuetiao.png");
            
            xuetiao->setScaleX((item->getContentSize().width)/xuetiao->getContentSize().width);
            xuetiao->setScaleY(0.3);
            xuetiao->setPosition(ccp(0,item->getContentSize().height+10));
            xuetiao->updatePercentage(0);
            item->addChild(xuetiao);
        }
        if (life < maxLife) {
            xuetiao->setVisible(true);
            xuetiao->updatePercentage(this->life/maxLife);
        } else {
            xuetiao->setVisible(false);
            xuetiao->updatePercentage(1);
        }
    }
    return true;
}

//bool BeAttackState::setLife(float life) {
//    }

void BeAttackState::doState() {
//    progressTimer->setPercentage(progressTimer->getPercentage()-2);
//    xuetiao->updatePercentage(xuetiao->percentage-2);
//    progressTimer->setOpacity(255);
//    CCLog("透明你妈逼：%d",progressTimer->getOpacity());
}



//BeAttackStateCreator::BeAttackStateCreator() {
//    life=0;
//}
//
//BeAttackStateCreator* BeAttackStateCreator::create() {
//    BeAttackStateCreator* creator = new BeAttackStateCreator();
//    creator->autorelease();
//    return creator;
//}
//
//CCObject* BeAttackStateCreator::createObj() {
//    
////    beAttackState->addTransition(toRuinsTransition, RuinsStateTag);
////    doFill(beAttackState);
//    return NULL;
//}
