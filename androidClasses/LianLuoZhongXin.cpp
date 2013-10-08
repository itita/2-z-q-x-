//
//  LianLuoZhongXin.cpp
//  ww4
//
//  Created by xiao tang on 13-5-3.
//
//

#include "LianLuoZhongXin.h"
#include "NormalState.h"
#include "DefineSet.h"
#include "BeAttackState.h"
#include "RepairState.h"
#include "StartScene.h"

MyBuilding* LianLuoZhongXin::createNormal(CCObject* target,int level) {
    
    CCSprite* byItem =CCSprite::createWithSpriteFrameName("communication.png");
    byItem->setAnchorPoint(ccp(0.4,0.29));
    byItem->setScale(0.9);
    NormalState* workState = NormalState::create(WorkStateTag, byItem);
    
    TransitionInfo* infoItem =  TransitionInfo::create(InfoTransition,"info.png",workState,menu_selector(MyState::infoCallBack));
    
    
#if game_version == soft_version
    MyBuilding* BDbuilding = MyBuilding::create(lianluozhongxinTag,CCSizeMake(4,4),workState,level,1);
#endif
#if game_version == hard_version
    MyBuilding* BDbuilding = MyBuilding::create(lianluozhongxinTag,CCSizeMake(3,3),workState,level);
#endif
    BDbuilding->setLevel(level);
    BDbuilding->setTag(lianluozhongxinTag);
    BDbuilding->setSummaryCount(500000);
    BDbuilding->resourceTag = ironTag;
   
    workState->addTransition(InfoTransition, WorkStateTag,infoItem);
    
    BDbuilding->setBuildingName(CCString::create("联络中心"),104);
    
    
    return BDbuilding;
}

MyBattleBuilding* LianLuoZhongXin::createBattle(int level,int stateId) {
    CCSprite* bdItem;
    BeAttackState* beAttackState = NULL;
    
    if (stateId == UnfinishedStateTag) {
        CCSprite* unfinishItem = CCSprite::createWithSpriteFrameName("buildstruct2x2(0).png");
        beAttackState = BeAttackState::create(UnfinishedStateTag, unfinishItem, 100);
    } else {
        
        bdItem = CCSprite::createWithSpriteFrameName("communication.png");
        bdItem->setAnchorPoint(ccp(0.4,0.29));
        bdItem->setScale(0.9);
        beAttackState =  BeAttackState::create(BeAttackStateTag, bdItem,byBaseHealth);
    }
    
    MyBattleBuilding* BDbuilding;
    
    
#if game_version == soft_version
    BDbuilding = MyBattleBuilding::create(lianluozhongxinTag,CCSizeMake(4,4),beAttackState,level);
#endif
#if game_version == hard_version
    BDbuilding = MyBattleBuilding::create(lianluozhongxinTag,CCSizeMake(3,3),beAttackState);
#endif
    BDbuilding->setLevel(level);
    BDbuilding->setBuildingName(CCString::create("联络中心"),108);
//    BDbuilding->displaySummary();
    
    return BDbuilding;
}

MyBuilding* LianLuoZhongXin::createDestroy(CCObject* target,int level) {
    CCSprite* buildItem;
    
    buildItem = CCSprite::createWithSpriteFrameName("communicationDestroy.png");
    buildItem->setAnchorPoint(ccp(0.4,0.45));
    buildItem->setScale(0.9);
    
    MyBuilding* destory;
    
    
    RepairState* repairState = RepairState::create(RepairStateTag, lianluozhongxinTag, buildItem);
    
    
    TransitionInfo* repairItem =  TransitionInfo::create(RepairTransition,"repair.png",repairState,menu_selector(RepairState::RepairCallBack));
    //    repairItem->setPosition(ccp(0,160));
    //    repairItem->setTag(RepairTransition);
    
    repairState->addTransition(RepairTransition, WorkStateTag,repairItem);
    
    
    
    destory = LianLuoZhongXin::createNormal(target,level);
    destory->addState(repairState);
    destory->changeStateById(RepairStateTag);
    destory->setTag(lianluozhongxinDestroyTag);
    destory->moveEnabled = false;
    
    return destory;
}


MyBattleBuilding* LianLuoZhongXin::createBattleDestroy(int level,int stateId) {
    CCSprite* destroyItem;
    
    
    destroyItem = CCSprite::createWithSpriteFrameName("communicationDestroy.png");
    destroyItem->setAnchorPoint(ccp(0.4,0.45));
    destroyItem->setScale(0.9);
    
    
    BeAttackState* battleState = BeAttackState::create(RepairStateTag, destroyItem, 100);
    
    
    MyBattleBuilding* destroy;
    
    
    destroy = MyBattleBuilding::create(lianluozhongxinDestroyTag,CCSizeMake(3,3),battleState);
    destroy->setBuildingName(CCString::create("联络中心"),108);
   
    destroy->displaySummary();
    destroy->setTag(lianluozhongxinDestroyTag);
    destroy->AliveInterface::dispose();
    
    
    return destroy;
}

MyBuildingCard* LianLuoZhongXin::createCard(CCObject* target,SEL_MenuHandler selector) {
    CCSprite* sprite = CCSprite::createWithSpriteFrameName("communication.png");
    sprite->setScale(0.75);
    sprite->setAnchorPoint(ccp(0.4,0.55));
    MyBuildingCard* card = MyBuildingCard::create(sprite,lianluozhongxinTag,0,0,ironTag,500000,10,"联络中心", target,selector);
    return card;
}

void LianLuoZhongXin::setUpdateInfo(GXFSMstate* _state,CCLayer* updateLayer) {
    
   
}