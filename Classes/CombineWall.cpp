//
//  CombineWall.cpp
//  ww4
//
//  Created by xiao tang on 13-5-3.
//
//

#include "CombineWall.h"
#include "DefineSet.h"
#include "SplitState.h"
#include "BeAttackState.h"
#include "MyUtil.h"

MyBuilding* CombineWall::createNormal(int tag,CCObject* target,int level) {
    CCSprite* wallItem = NULL;
    if (tag == combineWall5X1Tag) {
        wallItem = CCSprite::createWithSpriteFrameName("combineWall5x1.png");
        wallItem->setAnchorPoint(ccp(0.5,0.445));
        wallItem->setScale(0.965);
    } else if(tag == combineWall1X5Tag){
        wallItem = CCSprite::createWithSpriteFrameName("combineWall1x5.png");
        wallItem->setAnchorPoint(ccp(0.483,0.46));
        wallItem->setScale(0.965);
    }
    
    SplitState* wallState = SplitState::create(WorkStateTag, wallItem,wallTag);
    
    
    TransitionInfo* infoItem =  TransitionInfo::create(InfoTransition,"info.png",wallState,menu_selector(MyState::infoCallBack));
       
    MyBuilding* wall1;
    if (tag == combineWall5X1Tag) {
#if game_version == soft_version
        wall1= MyBuilding::create(combineWall5X1Tag,CCSizeMake(5,1),wallState,level,10);
#endif
#if game_version == hard_version
        wall1 = MyBuilding::create(combineWall5X1Tag,CCSizeMake(5,1),wallState,25);
#endif
    } else if(tag == combineWall1X5Tag) {
#if game_version == soft_version
        wall1 = MyBuilding::create(combineWall1X5Tag,CCSizeMake(1,5),wallState,level,10);
#endif
#if game_version == hard_version
        wall1 = MyBuilding::create(combineWall1X5Tag,CCSizeMake(1,5),wallState,25);
#endif
    }
    wall1->setLevel(level);
    wall1->setSummaryCount(200);
    wall1->resourceTag = ironTag;
    wall1->setUpdateInfo_selector = (SEL_SetUpdateInfo)(&CombineWall::setUpdateInfo);
    
    TransitionInfo* updateItem =  TransitionInfo::create(UpdateTransition,"update.png",wall1,menu_selector(MyBuilding::updateLevel));
 
    
    
    TransitionInfo* splitItem =  TransitionInfo::create(SplitTransition,"split.png",wallState,menu_selector(SplitState::toSplitCallBack));
  
    
    wallState->addTransition(SplitTransition, WorkStateTag,splitItem);
    wallState->addTransition(UpdateTransition, WorkStateTag,updateItem);
    wallState->addTransition(InfoTransition, WorkStateTag,infoItem);
    
    wall1->setBuildingName(CCString::create("强化路障"),80);
    
    return wall1;
    
}

MyBattleBuilding* CombineWall::createBattle(int tag,int level,int stateId) {
    
    CCSprite* wallItem = NULL;
    if (tag == combineWall5X1Tag) {
        wallItem = CCSprite::createWithSpriteFrameName("combineWall5x1.png");
        wallItem->setAnchorPoint(ccp(0.5,0.445));
        wallItem->setScale(0.965);
    } else if(tag == combineWall1X5Tag){
        wallItem = CCSprite::createWithSpriteFrameName("combineWall1x5.png");
        wallItem->setAnchorPoint(ccp(0.483,0.46));
        wallItem->setScale(0.965);
    }
    
    
    BeAttackState* beAttackState = BeAttackState::create(BeAttackStateTag, wallItem,wallBaseHealth);
    beAttackState->addTransition(toRuinsTransition, RuinsStateTag);
    
    
    MyBattleBuilding* BDbuilding = NULL;
    
    if (tag == combineWall5X1Tag) {
        BDbuilding= MyBattleBuilding::create(combineWall5X1Tag,CCSizeMake(5,1),beAttackState);
    } else if(tag == combineWall1X5Tag) {
        BDbuilding = MyBattleBuilding::create(combineWall1X5Tag,CCSizeMake(1,5),beAttackState);
    }
    BDbuilding->setLevel_selector = (SEL_SetBattleLevel)(&CombineWall::setBattleLevel);
    BDbuilding->setLevel(level);
    
    
    return BDbuilding;
    
}

void CombineWall::setBattleLevel(int level, GXFSM* fsm) {
    BeAttackState* beAttack = dynamic_cast<BeAttackState*>(fsm->getState(BeAttackStateTag));
    if(beAttack != NULL) {
        beAttack->setMaxLife(MyUtil::getInstance()->updateLevelByRate(0,combineWallBaseHealth, level, 1));
        beAttack->setLife(MyUtil::getInstance()->updateLevelByRate(0,combineWallBaseHealth, level, 1));
    }
}

void CombineWall::setUpdateInfo(GXFSMstate* _state,CCLayer* updateLayer) {
    MyState* state = (MyState*)_state;
    float healthLevelData = MyUtil::getInstance()->updateLevelByRate(0,combineWallBaseHealth, state->building->getLevel(), 1);
    float healthNextData = MyUtil::getInstance()->updateLevelByRate(0,combineWallBaseHealth, state->building->getLevel()+1, 1);
    float healthMaxData = MyUtil::getInstance()->updateLevelByRate(0,combineWallBaseHealth, state->building->getMaxLevel(), 1);
    
    CCSprite* healthIcon = CCSprite::createWithSpriteFrameName("healthIcon.png");
    healthIcon->setPosition(ccp(-64,98));
    updateLayer->addChild(healthIcon);
    CCLayer* bar = MyUtil::getInstance()->getUpdateBar(healthNextData/healthMaxData, healthLevelData/healthMaxData, "levelBarUp.png");
    bar->setPosition(ccp(-40,80));
    updateLayer->addChild(bar);
    
    char str[100] = {0};
    if(state->building->getLevel() < state->building->getMaxLevel()) {
        sprintf(str, "耐久度:%d+%d",(int)healthLevelData,(int)(healthNextData-healthLevelData));
    } else {
        sprintf(str, "耐久度:%d",(int)healthLevelData);
    }
    CCLabelTTF* healthLabel = CCLabelTTF::create(str, "Arial", 24);
    healthLabel->setAnchorPoint(ccp(0,0));
    healthLabel->setColor(ccc3(254, 218, 130));
    healthLabel->setPosition(ccp(-40,90));
    
    
    CCLabelTTF* description = CCLabelTTF::create("    强化路障是由5块路障组合而成，但是拥有更高\n的耐久度，灵活的摆放往往会成为阻击敌人的\n利器。", "Arial", 26,CCSizeZero,kCCTextAlignmentLeft,kCCVerticalTextAlignmentTop);
    description->setAnchorPoint(ccp(0,0.5));
    description->setColor(ccc3(254, 218, 130));
    description->setPosition(ccp(-280,-30));
    
    //        CCLabelTTF* mainUp = CCLabelTTF::create("主要升级属性:耐久度", "Arial", transWindowToGLInRetina(15));
    //        mainUp->setColor(ccc3(114, 66, 45));
    //        mainUp->setPosition(transWindowToGLInRetina(0,-40));
    //
    //        CCSprite* underLine = CCSprite::createWithSpriteFrameName("underline.png");
    //        underLine->setPosition(transWindowToGLInRetina(0,-50));
    
    CCLabelTTF* nameLabel = CCLabelTTF::create("强化路障", "Arial", 24);
    //        nameLabel->setColor(ccc3(114,66,45));
    nameLabel->setAnchorPoint(ccp(0.5,0.5));
    nameLabel->setPosition(ccp(-204,172));
    
    updateLayer->addChild(nameLabel);
    updateLayer->addChild(healthLabel);
    updateLayer->addChild(description);
    //        updateLayer->addChild(mainUp);
    //        updateLayer->addChild(underLine);

}