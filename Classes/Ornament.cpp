//
//  Ornament.cpp
//  ww4
//
//  Created by xiao tang on 13-5-4.
//
//

#include "Ornament.h"
#include "DefineSet.h"
#include "NormalState.h"
#include "BeAttackState.h"

MyBuilding* Ornament::createNormal(int tag, cocos2d::CCObject *target) {
    
    
    
    CCSprite* ornamentItem;
    
    if(tag / stoneBaseTag == 1) {
        char str[10] = {0};
        sprintf(str, "stone%d.png",tag%stoneBaseTag);
        ornamentItem = CCSprite::createWithSpriteFrameName(str);
        ornamentItem->setAnchorPoint(ccp(0.45,0.45));
        
    }else if(tag == songshuTag){
        ornamentItem = CCSprite::createWithSpriteFrameName("songshu3.png");
        ornamentItem->setAnchorPoint(ccp(0.5,0.25));
    }
    
    NormalState* wallState = NormalState::create(WorkStateTag, ornamentItem);
    MyBuilding* ornament;
    
    TransitionInfo* infoItem =  TransitionInfo::create(InfoTransition,"remove.png",wallState,menu_selector(MyState::infoCallBack));
   
    wallState->addTransition(InfoTransition, WorkStateTag,infoItem);
    
    if(tag / stoneBaseTag == 1) {
        ornament = MyBuilding::create(tag,CCSizeMake(tag%stoneBaseTag+1,tag%stoneBaseTag+1),wallState,100);
        ornament->setTag(songshuTag);
        ornament->moveEnabled = false;
        
        ornament->setSummaryCount(2000);
        ornament->resourceTag = ironTag;
        ornament->setLevel(3+tag%stoneBaseTag*3);

        
        ornament->setBuildingName(CCString::create("巨石"),ornamentItem->getContentSize().height*(1-ornamentItem->getAnchorPoint().y)+30);
        
        
        
    }else if(tag == songshuTag){
        ornament = MyBuilding::create(songshuTag,CCSizeMake(2,2),wallState,100);
        ornament->setTag(songshuTag);
        ornament->moveEnabled = false;
        ornament->setSummaryCount(5000);
        ornament->setLevel(5);
        ornament->resourceTag = oilTag;
        ornament->setBuildingName(CCString::create("松树"),116);

    }
    ornament->setTag(tag);
    return ornament;
}

MyBattleBuilding* Ornament::createBattle(int tag, int level,int stateId) {
    CCSprite* ornamentItem;
    
    if(tag / stoneBaseTag == 1) {
        char str[10] = {0};
        sprintf(str, "stone%d.png",tag%stoneBaseTag);
        ornamentItem = CCSprite::createWithSpriteFrameName(str);
        ornamentItem->setAnchorPoint(ccp(0.45,0.45));
        
    }else if(tag == songshuTag){
   
        ornamentItem = CCSprite::createWithSpriteFrameName("songshu3.png");
        ornamentItem->setAnchorPoint(ccp(0.5,0.25));
    }
    
    
    BeAttackState* battleState = BeAttackState::create(WorkStateTag, ornamentItem, 100);
    
    
    MyBattleBuilding* ornament;
    
    if(tag / stoneBaseTag == 1) {
       
        ornament = MyBattleBuilding::create(tag,CCSizeMake(tag%stoneBaseTag+1,tag%stoneBaseTag+1),battleState);
        ornament->setLevel(3+tag%stoneBaseTag*3);
        ornament->setTag(songshuTag);
        
        
    }else if(tag == songshuTag){
        
        ornament = MyBattleBuilding::create(tag,CCSizeMake(2,2),battleState);
        ornament->setTag(songshuTag);
        ornament->setLevel(5);
        
    }
    ornament->setTag(tag);
    ornament->AliveInterface::dispose();
    
    
    return ornament;
}