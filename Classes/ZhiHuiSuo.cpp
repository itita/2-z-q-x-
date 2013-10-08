//
//  ZhiHuiSuo.cpp
//  ww4
//
//  Created by xiao tang on 13-5-3.
//
//

#include "ZhiHuiSuo.h"
#include "NormalState.h"
#include "DefineSet.h"
#include "ResourceOnlyBeRobberState.h"
#include "MathLib.h"
#include "MyGameInfo.h"
#include "StartScene.h"
#include "MyUtil.h"

MyBuilding* ZhiHuiSuo::createNormal(CCObject* target,int level) {
    
    CCSprite* byItem =CCSprite::createWithSpriteFrameName("zhs1.png");
    byItem->setAnchorPoint(ccp(0.5,0.45));
    NormalState* workState = NormalState::create(WorkStateTag, byItem);
    
    TransitionInfo* infoItem =  TransitionInfo::create(InfoTransition,"info.png",workState,menu_selector(MyState::infoCallBack));
        
#if game_version == soft_version
    MyBuilding* BDbuilding = MyBuilding::create(zhihuisuoTag,CCSizeMake(5,5),workState,level,10);
#endif
#if game_version == hard_version
    MyBuilding* BDbuilding = MyBuilding::create(zhihuisuoTag,CCSizeMake(4,4),workState,25);
#endif
    
    BDbuilding->setLevel(level);
    BDbuilding->setTag(zhihuisuoTag);
    BDbuilding->setSummaryCount(2000);
    BDbuilding->resourceTag = ironTag;
    BDbuilding->setUpdateInfo_selector = (SEL_SetUpdateInfo)(&ZhiHuiSuo::setUpdateInfo);
    
    TransitionInfo* updateItem =  TransitionInfo::create(UpdateTransition,"update.png",BDbuilding,menu_selector(MyBuilding::updateLevel));
   
    workState->addTransition(UpdateTransition, WorkStateTag,updateItem);
    workState->addTransition(InfoTransition, WorkStateTag,infoItem);
    
    BDbuilding->setBuildingName(CCString::create("基地"),124);

    return BDbuilding;
}

MyBattleBuilding* ZhiHuiSuo::createBattle(int level,int stateId,float rate) {
    CCSprite* bdItem;
    BeAttackState* beAttackState = NULL;
    
    if (stateId == UnfinishedStateTag) {
        CCSprite* unfinishItem = CCSprite::createWithSpriteFrameName("buildstruct4x4(0).png");
        beAttackState = BeAttackState::create(UnfinishedStateTag, unfinishItem, 100);
    }else {
        bdItem = CCSprite::createWithSpriteFrameName("zhs1.png");
        bdItem->setAnchorPoint(ccp(0.5,0.45));
        CCSprite* tipArray = CCSprite::createWithSpriteFrameName("newbiearrow.png");
        bdItem->addChild(tipArray,2);
        CCSprite* tipAim = CCSprite::createWithSpriteFrameName("battleTipAim.png");
        bdItem->addChild(tipAim);
        
        
        tipAim->setScale(0.5);
        tipAim->setTag(battleTipAimTag);
        tipAim->setPosition(ccp(bdItem->getContentSize().width/2,bdItem->getContentSize().height- 30));
        tipArray->setPosition(ccp(bdItem->getContentSize().width/2,bdItem->getContentSize().height+20));
        tipArray->runAction(CCRepeatForever::create(static_cast<CCSequence*>(CCSequence::create(CCEaseInOut::create( CCMoveTo::create(0.5, ccp(bdItem->getContentSize().width/2,bdItem->getContentSize().height)), 2),CCEaseInOut::create(CCMoveTo::create(0.5, ccp(bdItem->getContentSize().width/2,bdItem->getContentSize().height+20)),2),NULL))));
        tipArray->setTag(battleTipTag);
        tipArray->setScale(0.7);
        
        beAttackState = ResourceOnlyBeRobberState::create(BeAttackStateTag, bdItem,jdBaseHealth);
    }
    
    
    
    MyBattleBuilding* BDbuilding;
   
#if game_version == soft_version
    BDbuilding = MyBattleBuilding::create(zhihuisuoTag,CCSizeMake(5,5),beAttackState,level);
#endif
#if game_version == hard_version
    BDbuilding = MyBattleBuilding::create(zhihuisuoTag,CCSizeMake(4,4),beAttackState);
#endif
    BDbuilding->setLevel_selector = (SEL_SetBattleLevel)(&ZhiHuiSuo::setBattleLevel);
    BDbuilding->setLevel(level);
    
    BDbuilding->setBuildingName(CCString::create("基地"),80);
//    BDbuilding->displaySummary();

    
    if(stateId == BeAttackStateTag) {
        //        CCLog("rate:%f",rate);
        ResourceOnlyBeRobberState* robberState = (ResourceOnlyBeRobberState*)beAttackState;
        robberState->setOil(Mathlib::max(MyGameInfo::getInstance()->enemyOil*rate,0));
        robberState->setIron(Mathlib::max(MyGameInfo::getInstance()->enemyIron*rate,0));
        
        //指挥所叠加
        MyGameInfo::getInstance()->setRobberOil(MyGameInfo::getInstance()->getRobberOil() + robberState->getOil());
        
        MyGameInfo::getInstance()->setRobberIron(MyGameInfo::getInstance()->getRobberIron() + robberState->getIron());
    
    }
    
    
    return BDbuilding;
}

MyBuildingCard* ZhiHuiSuo::createCard(CCObject* target,SEL_MenuHandler selector) {
    MyBuildingCard* card = MyBuildingCard::create(CCSprite::createWithSpriteFrameName("zhs1.png"),zhihuisuoTag,0,0,ironTag,2000,"基  地", target,selector);
    return card;
}

void ZhiHuiSuo::setBattleLevel(int level,GXFSM* fsm) {
    BeAttackState* beAttack = dynamic_cast<BeAttackState*>(fsm->getState(BeAttackStateTag));
    if(beAttack != NULL) {
        beAttack->setMaxLife(MyUtil::getInstance()->updateLevelByRate(0,jdBaseHealth, level, jdUpdateHealthRate));
        beAttack->setLife(MyUtil::getInstance()->updateLevelByRate(0,jdBaseHealth, level, jdUpdateHealthRate));
    }
}

void ZhiHuiSuo::setUpdateInfo(GXFSMstate* _state,CCLayer* updateLayer) {
    
    MyState* state = (MyState*)_state;
    
    float healthLevelData = MyUtil::getInstance()->updateLevelByRate(0,jdBaseHealth, state->building->getLevel(), 1);
    float healthNextData = MyUtil::getInstance()->updateLevelByRate(0,jdBaseHealth, state->building->getLevel()+1, 1);
    float healthMaxData = MyUtil::getInstance()->updateLevelByRate(0,jdBaseHealth, state->building->getMaxLevel(), 1);
    
    CCSprite* healthIcon = CCSprite::createWithSpriteFrameName("healthIcon.png");
    healthIcon->setPosition(ccp(-68,134));
    updateLayer->addChild(healthIcon);
    CCLayer* healthBar = MyUtil::getInstance()->getUpdateBar(healthNextData/healthMaxData, healthLevelData/healthMaxData,"levelBarUp.png");
    
    healthBar->setPosition(ccp(-40,116));
    updateLayer->addChild(healthBar);
    
    char str[100] = {0};
    if(state->building->getLevel() < state->building->getMaxLevel()) {
        sprintf(str, "耐久度:%d+%d",(int)healthLevelData,(int)(healthNextData - healthLevelData));
    } else {
        sprintf(str, "耐久度:%d",(int)healthLevelData);
    }
    CCLabelTTF* healthLabel = CCLabelTTF::create(str, "Arial", 24);
    healthLabel->setAnchorPoint(ccp(0,0));
    healthLabel->setColor(ccc3(254, 218, 130));
    healthLabel->setPosition(ccp(-40,126));
    
    
    CCLabelTTF* nameLabel = CCLabelTTF::create("基  地", "Arial", 24);
    nameLabel->setColor(ccc3(254, 218, 130));
    nameLabel->setAnchorPoint(ccp(0.5,0.5));
    nameLabel->setPosition(ccp(-204,172));
    updateLayer->addChild(nameLabel);
    updateLayer->addChild(healthLabel);
    
    CCLabelTTF* description = CCLabelTTF::create("        基地作为通讯、指挥、物资的中心，是最\n重要的单位，通过基地，可以提供最大军令数\n量并且每隔一段时间恢复军令。在征战中，击\n破基地即获得胜利。                                        ", "Arial", 26);
    description->setAnchorPoint(ccp(0,0.5));
    description->setColor(ccc3(254, 218, 130));
    description->setPosition(ccp(-280,-50));
    updateLayer->addChild(description);
}