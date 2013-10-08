//
//  Ghost.cpp
//  ww4
//
//  Created by xiao tang on 13-5-24.
//
//

#include "Ghost.h"
#include "DefineSet.h"
#include "NormalState.h"
#include "GarbageCollectionState.h"
#include "GarbageCollectionNormalState.h"
#include "GXFadeOut.h"
#include "GXShakeAction.h"

MyBuilding* Ghost::createNormal(int resoucreCount) {
    CCSprite* byItem = CCSprite::createWithSpriteFrameName("ghost.png");
    // 普通状态
    
//    byItem->runAction(CCRepeatForever::create(static_cast<CCSequence*>(CCSequence::create(CCFlipX::create(true),CCDelayTime::create(1),CCFlipX::create(false),CCDelayTime::create(1),NULL))));
//    byItem->runAction(CCRepeatForever::create(GXShakeAction::create(2,0.1,0.03,ccp(0.5,0.5))));
    
    GarbageCollectionNormalState* workState = GarbageCollectionNormalState::create(GarbageCollectionStateTag, byItem,resoucreCount);
    
    MyBuilding* BDbuilding = MyBuilding::create(ghostTag,CCSizeMake(1,1),workState,10);
//    BDbuilding->setAnchorPoint(ccp(0.5,0.5));
    
    BDbuilding->setTag(ghostTag);
    BDbuilding->setSummaryCount(0);
    BDbuilding->resourceTag = oilTag;
    BDbuilding->moveEnabled = false;
    
    BDbuilding->setDoStateInterval(1.5);
    
    return BDbuilding;
}
MyBattleBuilding* Ghost::createBattle(int resoucreCount) {
    CCSprite* ghostItem = CCSprite::createWithSpriteFrameName("ghost.png");
    
    GarbageCollectionState* battleState = GarbageCollectionState::create(GarbageCollectionStateTag,ghostItem, resoucreCount);
    
        
    MyBattleBuilding* ghost = MyBattleBuilding::create(ghostTag,CCSizeMake(1,1),battleState);
    
    ghost->AliveInterface::dispose();
    
    return ghost;
}