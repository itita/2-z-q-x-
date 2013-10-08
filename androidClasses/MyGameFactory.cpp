//
//  MyGameFactory.cpp
//  ww2
//
//  Created by DingYu Fu on 12-9-15.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "MyGameFactory.h"
#include "StartScene.h"
#include "NormalState.h"
#include "BeAttackState.h"
#include "DefendState.h"
#include "MyContinueTiledMenuItemSprite.h"
#include "MyGameInfo.h"
#include "PulsarNative.h"
#include "AoeDefendState.h"
#include "DefineSet.h"
#include "ReadyToBuild.h"
#include "MyMenuItem.h"
#include "CollectState.h"
#include "UnfinishedState.h"
#include "Mathlib.h"
#include "ResourceBeAttackState.h"
#include "RuinState.h"
#include "CreatorRuinState.h"
#include "GXProgressBar.h"
#include "MyUtil.h"
#include "ResourceOnlyBeRobberState.h"
#include "MyContinueTiledSprite.h"
#include "BattleRuinState.h"
#include "MyContinueBuilding.h"
#include "GXUtil.h"
#include "NewbieStartScene.h"
#include "NewbieBattleScene.h"
#include "NewbieMovieScene.h"
#include "GXAnimateWithFx.h"
#include "GXFX.h"
#include "AliveInterface.h"
#include "GXMessage.h"
#include "RepairState.h"
#include "ContinueState.h"
#include "SplitState.h"
#include "GXChatHandler.h"
#include "BuildingHeader.h"

//#define robberRate  Mathlib::bound((MyGameInfo::getInstance()->enemyPower/MyGameInfo::getInstance()->getPower())*0.2, 0.4, 0)

#define robberRate 0.3

staticInit* staticInit::create() {
    MyGameFactory::creatorMap = CCDictionary::create();
    MyGameFactory::creatorMap->retain();
    return NULL;
}
CCDictionary* MyGameFactory::creatorMap = NULL;

staticInit* MyGameFactory::init = staticInit::create();

//MyBuilding* MyGameFactory::createBingYing(CCObject* target,int level) {
//    
//    //创建建造结构
//    
////    CCSprite* grayBd = CCSprite::create("buildStruct.png");
////    grayBd->setColor(ccGRAY);
////    MyTiledMenuItemSprite* buildStructItem = MyTiledMenuItemSprite::create(CCSprite::create("buildStruct.png"), grayBd);
//    
//    
////    NormalState* unfinishedState = NormalState::create(UnfinishedStateTag,buildStructItem);
//    
////    CCSprite* grayBy = CCSprite::create("by7.png");
////    grayBy->setColor(ccGRAY);
//    CCSprite* byItem = CCSprite::createWithSpriteFrameName("by7.png");
//    byItem->setAnchorPoint(ccp(0.5,0.45));
//    
//// 普通状态
//    
//    NormalState* workState = NormalState::create(WorkStateTag, byItem);
//    
//    TransitionInfo* trainItem =  TransitionInfo::create(CollectTransition,"conscription.png",target,menu_selector(StartScene::toArmyCallBackSimple));
////    trainItem->setVisible(false);
////    trainItem->setPosition(ccp(0,160));
////    trainItem->setTag(CollectTransition);
//    
//    TransitionInfo* infoItem =  TransitionInfo::create(InfoTransition,"info.png",workState,menu_selector(MyState::infoCallBack));
////    infoItem->setVisible(false);
////    infoItem->setTag(InfoTransition);
//    
//    
//    
//    
//    
//    workState->addTransition(CollectTransition, WorkStateTag,trainItem);
//    workState->addTransition(InfoTransition, WorkStateTag,infoItem);
//    
////    MyBuilding* BDbuilding = MyBuilding::create(CCSizeMake(4,4),unfinishedState,buildItem,cancelItem,trainItem,infoItem,updateItem,sellitem,NULL);
//    
//    
//    
////    MyBuilding* BDbuilding = MyBuilding::create(CCSizeMake(4,4),unfinishedState,buildItem,trainItem,infoItem,updateItem,sellitem,NULL);
//    MyBuilding* BDbuilding = MyBuilding::create(bingyingTag,CCSizeMake(4,4),workState,level,10);
//    BDbuilding->addState(workState);
//    BDbuilding->setTag(bingyingTag);
//    BDbuilding->setSummaryCount(200);
//    BDbuilding->resourceTag = oilTag;
//    
//    TransitionInfo* updateItem =  TransitionInfo::create(UpdateTransition,"update.png",BDbuilding,menu_selector(MyBuilding::updateLevel));
////    updateItem->setVisible(false);
////    updateItem->setPosition(ccp(-96,160));
////    updateItem->setTag(UpdateTransition);
////    BDbuilding->addChild(updateItem);
//    workState->addTransition(UpdateTransition, WorkStateTag,updateItem);
//    BDbuilding->setBuildingName(CCString::create("兵营"),108);
// 
////    CCLabelTTF* name = CCLabelTTF::create("兵营", "Arial", 22);
////
////  
////    name->setColor(ccWHITE);
////    name->setPosition(ccp(0,108));
////    name->setTag(nameFontTag);
////    name->setVisible(false);
////    char str[5] = {0};
////    sprintf(str, "等级 %d",level);
////    CCLabelTTF* levelFont = CCLabelTTF::create(str, "Arial", 18);
////
////    levelFont -> setPosition(ccp(0,86));
////    levelFont->setColor(ccWHITE);
////    levelFont->setTag(levelFontTag);
////    levelFont->setVisible(false);
////    BDbuilding->addChild(name,20);
////    BDbuilding->addChild(levelFont,20);
//    return BDbuilding;
//}



//非功能战斗建筑在图多之后可以根据大功能合并

//MyBattleBuilding* MyGameFactory::createBattleBingYing(cocos2d::CCObject *target,int level) {
//
//    
//    CCSprite* ytItem = CCSprite::createWithSpriteFrameName("by7.png");
//    ytItem->setAnchorPoint(ccp(0.5,0.45));
//    BeAttackState* beAttackState = BeAttackState::create(BeAttackStateTag, ytItem,byBaseHealth);
////    beAttackState->addTransition(toRuinsTransition, RuinsStateTag);
//    
////    MyTiledMenuItemSprite* ruinItem = MyTiledMenuItemSprite::create(CCSprite::create("ruins.png"), CCSprite::create("ruins.png"));
//    
//    
////    RuinState* ruinstate = RuinState::create(RuinsStateTag, ruinItem);
////    ruinItem->setEnabled(false);
////    ruinItem->setScale(beAttackState->item->getContentSize().width/ruinstate->item->getContentSize().width);
//    
//
//    BeAttackState* unfinished = BeAttackState::create(UnfinishedStateTag, CCSprite::createWithSpriteFrameName("buildstruct2x2(0).png"), 100);
////    unfinished->addTransition(toRuinsTransition, RuinsStateTag);
//    
//    
//    MyBattleBuilding* BDbuilding = MyBattleBuilding::create(bingyingTag,CCSizeMake(4,4),beAttackState,level);
//    
//
//    BDbuilding->addState(unfinished);
//    BDbuilding->setTag(bingyingTag);
//    BDbuilding->setBuildingName(CCString::create("兵营"),108);
//    BDbuilding->displaySummary();
////    CCLabelTTF* name = CCLabelTTF::create("兵营", "Arial", 22);
////    //    name->setFontSize(transWindowToGLInRetina(1));
////    
////    name->setColor(ccWHITE);
////    name->setPosition(ccp(0,108));
////    name->setTag(nameFontTag);
////    
////    char str[5] = {0};
////    sprintf(str, "等级 %d",level);
////    CCLabelTTF* levelFont = CCLabelTTF::create(str, "Arial", 18);
////    
////    levelFont -> setPosition(ccp(0,86));
////    levelFont->setColor(ccWHITE);
////    levelFont->setTag(levelFontTag);
////    BDbuilding->addChild(name,20);
////    BDbuilding->addChild(levelFont,20);;
//    return BDbuilding;
//}

//MyBuilding* MyGameFactory::createWall(CCObject* target,int level) {
//    
//    
//    MyContinueTiledSprite* wallItem = MyContinueTiledSprite::create(CCString::create("wall1"));
////    CCSprite* wallItem = CCSprite::createWithSpriteFrameName("wall1c.png");
//    wallItem->setAnchorPoint(ccp(0.45,0.37));
//    ContinueState* combineState = ContinueState::create(WorkStateTag, wallItem,combineWall5X1Tag);
//    
//    TransitionInfo* infoItem =  TransitionInfo::create(InfoTransition,"info.png",combineState,menu_selector(MyState::infoCallBack));
//    
////    infoItem->setPosition(ccp(0,70));
////    infoItem->setTag(InfoTransition);
//    
//    
//#if game_version == soft_version
//    MyContinueBuilding* wall1 = MyContinueBuilding::create(wallTag,CCSizeMake(1,1),combineState,level,10);
//#endif
//#if game_version == hard_version
//    MyContinueBuilding* wall1 = MyContinueBuilding::create(wallTag,CCSizeMake(1,1),combineState,level,25);
//#endif
//    
//    wall1->setTag(wallTag);
//    wall1->setSummaryCount(40);
//    wall1->resourceTag = ironTag;
//    
//    TransitionInfo* updateItem =  TransitionInfo::create(UpdateTransition,"update.png",wall1,menu_selector(MyBuilding::updateLevel));
////    updateItem->setVisible(false);
////    updateItem->setPosition(ccp(-56,140));
////    updateItem->setTag(UpdateTransition);
//    
//    TransitionInfo* combineItem =  TransitionInfo::create(CombineTransition,"combine.png",combineState,menu_selector(ContinueState::toCombineCallBack));
//    //    updateItem->setVisible(false);
////    combineItem->setTag(CombineTransition);
//    
//    combineState->addTransition(CombineTransition, WorkStateTag,combineItem);
//    combineState->addTransition(UpdateTransition, WorkStateTag,updateItem);
//    combineState->addTransition(InfoTransition, WorkStateTag,infoItem);
//    
//    
//    wall1->setBuildingName(CCString::create("路障"),70);
//   
////    CCLabelTTF* name = CCLabelTTF::create("路障","Arial",22);
////    //    name->setFontSize(transWindowToGLInRetina(1));
////    
////    name->setColor(ccWHITE);
////    name->setPosition(ccp(0,80));
////    name->setTag(nameFontTag);
////    name->setVisible(false);
////    char str[5] = {0};
////    sprintf(str, "等级 %d",level);
////    CCLabelTTF* levelFont = CCLabelTTF::create(str,"Arial",18);
////    
////    levelFont -> setPosition(ccp(0,60));
////    levelFont->setColor(ccWHITE);
////    levelFont->setTag(levelFontTag);
////    levelFont->setVisible(false);
////    wall1->addChild(name,20);
////    wall1->addChild(levelFont,20);
//    return wall1;
//}

//MyBattleBuilding* MyGameFactory::createBattleWall(cocos2d::CCObject *target,int level) {
//    
//    
//    CCSprite* wallItem = MyContinueTiledSprite::create(CCString::create("wall1"));
//    wallItem->setAnchorPoint(ccp(0.45,0.37));
//    
//    BeAttackState* beAttackState = BeAttackState::create(BeAttackStateTag, wallItem,wallBaseHealth);
//    beAttackState->addTransition(toRuinsTransition, RuinsStateTag);
//    
////    MyTiledMenuItemSprite* ruinItem = MyTiledMenuItemSprite::create(CCSprite::create("ruins.png"), CCSprite::create("ruins.png"));
////    
////    RuinState* ruinstate = RuinState::create(RuinsStateTag, ruinItem);
////    ruinItem->setEnabled(false);
////    ruinItem->setScale(beAttackState->item->getContentSize().width/ruinstate->item->getContentSize().width);
//    
//    MyBattleBuilding* BDbuilding = MyBattleBuilding::create(wallTag,CCSizeMake(1,1),beAttackState,level);
//    BDbuilding->setTag(wallTag);
////    CCLabelTTF* name = CCLabelTTF::create("路障","Arial", transWindowToGLInRetina(11));
////    name -> setPosition(ccp(0,wallItem->getContentSize().height - transWindowToGLInRetina(15)));
////    name->setTag(nameTag);
////    CCLabelTTF* level = CCLabelTTF::create("等级 1","Arial", transWindowToGLInRetina(9));
////    
////    level -> setPosition(transWindowToGLInRetina(0,30));
////    level->setTag(levelTag);
////    
////    BDbuilding->addChild(name);
////    BDbuilding->addChild(level);
//    return BDbuilding;
//}

//MyBuilding* MyGameFactory::createYouTian(CCObject* target,int level) {
//    
//    
////    UnfinishedState* unfinishedState = NormalState::create(UnfinishedStateTag,"buildstruct",);
////    
////    MyMenuItem* buildItem =  MyMenuItem::create(CCSprite::create("build.png"),unfinishedState,menu_selector(NormalState::changeIdCallBack));
////    buildItem->setPosition(transWindowToGLInRetina(-28,80));
////    buildItem->setTag(BuildTransition);
////    buildItem->setVisible(false);
////    
////    MyMenuItem* sellItem =  MyMenuItem::create(CCSprite::create("sell.png"),unfinishedState,menu_selector(NormalState::sellCallBack));
////    sellItem->setPosition(transWindowToGLInRetina(28,80));
////    sellItem->setTag(sellTransition);
////    sellItem->setVisible(false);
////    
////    unfinishedState->addTransition(BuildTransition, WorkStateTag);
////    unfinishedState->addTransition(sellTransition, DestroyStateTag);
//
//    CCSprite* byItem = CCSprite::createWithSpriteFrameName("yt2.png");
//    byItem->setAnchorPoint(ccp(0.5,0.35));
//    
//    CollectState* workState = CollectState::create(WorkStateTag, byItem,ytBaseColletSpeed,ytBaseColletMaxCapacity,oilTag);
//    TransitionInfo* collectItem =  TransitionInfo::create(CollectTransition,"collect.png",workState,menu_selector(CollectState::doCollect));
////    collectItem->setPosition(ccp(0,160));
////    collectItem->setTag(CollectTransition);
//
//    TransitionInfo* infoItem =  TransitionInfo::create(InfoTransition,"info.png",workState,menu_selector(MyState::infoCallBack));
////    infoItem->setPosition(ccp(96,160));
////    infoItem->setTag(InfoTransition);
//    
//   
//    
//    
//   
//    
////    MyBuilding* BDbuilding = MyBuilding::create(CCSizeMake(3,3),unfinishedState,buildItem,sellItem,collectItem,infoItem,updateItem ,NULL);
//#if game_version == soft_version
//    MyBuilding* BDbuilding = MyBuilding::create(youtianTag,CCSizeMake(4,4),workState,level,10);
//#endif
//#if game_version == hard_version
//    MyBuilding* BDbuilding = MyBuilding::create(youtianTag,CCSizeMake(3,3),workState,level,10);
//#endif
//    BDbuilding->setSummaryCount(200);
//    BDbuilding->resourceTag = ironTag;
//    
//    TransitionInfo* updateItem =  TransitionInfo::create(UpdateTransition, "update.png",BDbuilding,menu_selector(MyBuilding::updateLevel));
////    updateItem->setVisible(false);
////    updateItem->setPosition(ccp(-96,160));
////    updateItem->setTag(UpdateTransition);
////    BDbuilding->addChild(updateItem);
//    
//    
//    workState->addTransition(UpdateTransition, WorkStateTag,updateItem);
//    workState->addTransition(CollectTransition, WorkStateTag,collectItem);
//    workState->addTransition(InfoTransition, WorkStateTag,infoItem);
//    
//    BDbuilding->addState(workState);
//    BDbuilding->setTag(youtianTag);
//    BDbuilding->setBuildingName(CCString::create("炼油厂"),108);
//
////    CCLabelTTF* name = CCLabelTTF::create("炼油厂","Arial",22);
////    //    name->setFontSize(transWindowToGLInRetina(1));
////    
////    name->setColor(ccWHITE);
////    name->setPosition(ccp(0,108));
////    name->setTag(nameFontTag);
////    name->setVisible(false);
////    char str[5] = {0};
////    sprintf(str, "等级 %d",level);
////    CCLabelTTF* levelFont = CCLabelTTF::create(str,"Arial",18);
////    
////    levelFont -> setPosition(ccp(0,86));
////    levelFont->setColor(ccWHITE);
////    levelFont->setTag(levelFontTag);
////    levelFont->setVisible(false);
////    BDbuilding->addChild(name,20);
////    BDbuilding->addChild(levelFont,20);
//    
//    return BDbuilding;
//}



//MyBattleBuilding* MyGameFactory::createCreateInBattle(int tag,cocos2d::CCObject *target,int level) {
//    CCSprite* bdItem;
//    BeAttackState* beAttackState = NULL;
//    
//    
////    if (tag == youtianTag) {
////         bdItem = CCSprite::createWithSpriteFrameName("yt2.png");
////         bdItem->setAnchorPoint(ccp(0.5,0.35));
////        beAttackState = ResourceBeAttackState::create(BeAttackStateTag, bdItem,ytBaseHealth,ytBaseColletSpeed,ytBaseColletMaxCapacity,oilTag);
//////        name = CCLabelTTF::create("炼油厂","Arial",22);
//////        //    name->setFontSize(transWindowToGLInRetina(1));
//////        
//////        name->setColor(ccWHITE);
//////        name->setPosition(ccp(0,108));
//////        name->setTag(nameFontTag);
////    } else if(tag == kuangchangTag) {
////        bdItem = CCSprite::createWithSpriteFrameName("kc.png");
////        bdItem->setAnchorPoint(ccp(0.45,0.4));
////        beAttackState = ResourceBeAttackState::create(BeAttackStateTag, bdItem,kcBaseHealth,kcBaseColletSpeed,kcBaseColletMaxCapacity,ironTag);
//////        name = CCLabelTTF::create("钢铁厂","Arial",22);
//////        //    name->setFontSize(transWindowToGLInRetina(1));
//////        
//////        name->setColor(ccWHITE);
//////        name->setPosition(ccp(0,108));
//////        name->setTag(nameFontTag);
////    } else if(tag == zhihuisuoTag) {
////        bdItem = CCSprite::createWithSpriteFrameName("zhs1.png");
////        bdItem->setAnchorPoint(ccp(0.5,0.45));
////        CCSprite* tipArray = CCSprite::createWithSpriteFrameName("newbiearrow.png");
////        bdItem->addChild(tipArray,2);
////        CCSprite* tipAim = CCSprite::createWithSpriteFrameName("battleTipAim.png");
////        bdItem->addChild(tipAim);
////        
//////        name = CCLabelTTF::create("基地","Arial",18);
//////        //    name->setFontSize(transWindowToGLInRetina(1));
//////        
//////        name->setColor(ccWHITE);
//////        name->setPosition(ccp(0,108));
//////        name->setTag(nameFontTag);
////        
////        tipAim->setScale(0.5);
////        tipAim->setTag(battleTipAimTag);
////        tipAim->setPosition(ccp(bdItem->getContentSize().width/2,bdItem->getContentSize().height- 30));
////        tipArray->setPosition(ccp(bdItem->getContentSize().width/2,bdItem->getContentSize().height+20));
////        tipArray->runAction(CCRepeatForever::create(static_cast<CCSequence*>(CCSequence::create(CCEaseInOut::create( CCMoveTo::create(0.5, ccp(bdItem->getContentSize().width/2,bdItem->getContentSize().height)), 2),CCEaseInOut::create(CCMoveTo::create(0.5, ccp(bdItem->getContentSize().width/2,bdItem->getContentSize().height+20)),2),NULL))));
////        tipArray->setTag(battleTipTag);
////        tipArray->setScale(0.7);
////        //指挥所的抢劫
////        float rate = robberRate*((BattleScene*)target)->trophyRate;
//////        CCLog("rate:%f",rate);
////        float robberOil = Mathlib::max(MyGameInfo::getInstance()->enemyOil*rate,0);
////        float robberIron = Mathlib::max(MyGameInfo::getInstance()->enemyIron*rate,0);
////        beAttackState = ResourceOnlyBeRobberState::create(BeAttackStateTag, bdItem,jdBaseHealth,robberOil,robberIron);
////    } else
//    if(tag == lianluozhongxinTag) {
//        bdItem = CCSprite::createWithSpriteFrameName("communication.png");
//        bdItem->setAnchorPoint(ccp(0.4,0.29));
//        bdItem->setScale(0.9);
//        beAttackState =  BeAttackState::create(BeAttackStateTag, bdItem,byBaseHealth);
////        name = CCLabelTTF::create("联络中心","Arial",22);
////        //    name->setFontSize(transWindowToGLInRetina(1));
////        name->setColor(ccWHITE);
////        name->setPosition(ccp(0,108));
////        name->setTag(nameFontTag);
//    }
////    MyTiledMenuItemSprite* ytItem = MyTiledMenuItemSprite::create(CCSprite::create("yt.png"), CCSprite::create("yt.png"));
//    
//    
//    
//    
//    CCSprite* unfinishItem = CCSprite::createWithSpriteFrameName("buildstruct2x2(0).png");
//    BeAttackState* unfinished = BeAttackState::create(UnfinishedStateTag, unfinishItem, 100);
////    unfinished->addTransition(toRuinsTransition, RuinsStateTag);
//    
//    MyBattleBuilding* BDbuilding;
//    
////    if (tag == youtianTag) {
////#if game_version == soft_version
////        BDbuilding = MyBattleBuilding::create(youtianTag,CCSizeMake(4,4),beAttackState,level);
////#endif
////#if game_version == hard_version
////        BDbuilding = MyBattleBuilding::create(youtianTag,CCSizeMake(3,3),beAttackState,level);
////#endif
////        BDbuilding->setBuildingName(CCString::create("炼油厂"),108);
////    } else if(tag == kuangchangTag) {
////#if game_version == soft_version
////        BDbuilding = MyBattleBuilding::create(kuangchangTag,CCSizeMake(4,4),beAttackState,level);
////#endif
////#if game_version == hard_version
////        BDbuilding = MyBattleBuilding::create(kuangchangTag,CCSizeMake(3,3),beAttackState,level);
////#endif
////        BDbuilding->setBuildingName(CCString::create("炼钢厂"),108);
////    } else
////    if(tag == zhihuisuoTag) {
////        
////#if game_version == soft_version
////        BDbuilding = MyBattleBuilding::create(zhihuisuoTag,CCSizeMake(5,5),beAttackState,level);
////#endif
////#if game_version == hard_version
////        BDbuilding = MyBattleBuilding::create(zhihuisuoTag,CCSizeMake(4,4),beAttackState,level);
////#endif
////        BDbuilding->setBuildingName(CCString::create("基地"),80);
////    } else
//    if(tag == lianluozhongxinTag) {
//    
//#if game_version == soft_version
//        BDbuilding = MyBattleBuilding::create(lianluozhongxinTag,CCSizeMake(4,4),beAttackState,level);
//#endif
//#if game_version == hard_version
//        BDbuilding = MyBattleBuilding::create(lianluozhongxinTag,CCSizeMake(3,3),beAttackState,level);
//#endif
//        BDbuilding->setBuildingName(CCString::create("联络中心"),108);
//    }
//    BDbuilding->displaySummary();
//    BDbuilding->addState(unfinished);
//    BDbuilding->setTag(tag);
//    
////    char str[5] = {0};
////    sprintf(str, "等级 %d",level);
////
////    CCLabelTTF* levelFont = CCLabelTTF::create(str,"Arial",18);
////    
////    levelFont -> setPosition(ccp(0,86));
////    levelFont->setColor(ccWHITE);
////    levelFont->setTag(levelFontTag);
////
////    BDbuilding->addChild(name,20);
////    BDbuilding->addChild(levelFont,20);
//    
//    return BDbuilding;
//}


//MyBuilding* MyGameFactory::createDestoryBuilding(int tag,CCObject* target,int level) {
//    CCSprite* buildItem;
//    
//    if(tag == lianluozhongxinDestroyTag) {
//        buildItem = CCSprite::createWithSpriteFrameName("communicationDestroy.png");
//        buildItem->setAnchorPoint(ccp(0.4,0.45));
//        buildItem->setScale(0.9);
//    }
//    
//    MyBuilding* destory;
//    
//   
//    RepairState* repairState = RepairState::create(RepairStateTag, lianluozhongxinTag, buildItem);
//    
//    
//    TransitionInfo* repairItem =  TransitionInfo::create(RepairTransition,"repair.png",repairState,menu_selector(RepairState::RepairCallBack));
////    repairItem->setPosition(ccp(0,160));
////    repairItem->setTag(RepairTransition);
//   
//    repairState->addTransition(RepairTransition, WorkStateTag,repairItem);
//    
// 
//    if(tag == lianluozhongxinDestroyTag) {
//        destory = LianLuoZhongXin::createNormal(target,level);
//    }
//    destory->addState(repairState);
//    destory->changeStateById(RepairStateTag);
//    destory->setTag(tag);
//    destory->moveEnabled = false;
//    
//    return destory;
//}

//MyBattleBuilding* MyGameFactory::createBattleDestory(int tag,CCObject* target,int level) {
//    CCSprite* destroyItem;
//    
//    if(tag  == lianluozhongxinDestroyTag) {
//
//        destroyItem = CCSprite::createWithSpriteFrameName("communicationDestroy.png");
//        destroyItem->setAnchorPoint(ccp(0.4,0.45));
//        destroyItem->setScale(0.9);
//        
//    }
//    
//    
//    BeAttackState* battleState = BeAttackState::create(RepairStateTag, destroyItem, 100);
//    
//    
//    MyBattleBuilding* destroy;
//    
//    if(tag == lianluozhongxinDestroyTag) {
//        //        ornament = MyBuilding::create(tag,CCSizeMake(tag%stoneBaseTag+1,tag%stoneBaseTag+1),wallState,1);
//        destroy = MyBattleBuilding::create(bingyingTag,CCSizeMake(3,3),battleState,level);
//        destroy->setBuildingName(CCString::create("联络中心"),108);
////        CCLabelTTF* name = CCLabelTTF::create("联络中心","Arial",22);
////        //    name->setFontSize(transWindowToGLInRetina(1));
////        
////        name->setColor(ccWHITE);
////        name->setPosition(ccp(0,104));
////        name->setTag(nameFontTag);
////        name->setVisible(false);
////        destroy->addChild(name,20);
//        
//    }
//    destroy->displaySummary();
//    destroy->setTag(tag);
//    destroy->AliveInterface::dispose();
//    
//    
//    return destroy;
//}

//MyBattleBuilding* MyGameFactory::createBattleDiaoBao(cocos2d::CCObject *target,int level) {
//    
//    CCSprite* dbItem = CCSprite::createWithSpriteFrameName("diaobao.png");
//    
//    DefendState* defender = DefendState::create(DefendStateTag, dbItem,CCString::create("diaobao1"),dbBaseHealth,dbBaseRange,dbBaseDamage,1);
//    
//    
//    defender->setAnimate(CCAnimate::create(GXUtil::initAction("diaobao1fld", 0.03,false)), 0);
//    defender->setAnimate(CCAnimate::create(GXUtil::initAction("diaobao1fd", 0.03,false)), 1);
//    defender->setAnimate(CCAnimate::create(GXUtil::initAction("diaobao1frd", 0.03,false)), 2);
//    defender->setAnimate(CCAnimate::create(GXUtil::initAction("diaobao1fr", 0.03,false)), 3);
//    defender->setAnimate(CCAnimate::create(GXUtil::initAction("diaobao1fru", 0.03,false)), 4);
//    defender->setAnimate(CCAnimate::create(GXUtil::initAction("diaobao1fu", 0.03,false)), 5);
//    defender->setAnimate(CCAnimate::create(GXUtil::initAction("diaobao1flu", 0.03,false)), 6);
//    defender->setAnimate(CCAnimate::create(GXUtil::initAction("diaobao1fl", 0.03,false)), 7);
//    
//    
//    
////    defender->addTransition(toRuinsTransition, RuinsStateTag);
//    
//    CCSprite* unfinishItem = CCSprite::createWithSpriteFrameName("buildstruct2x2(0).png");
//    BeAttackState* unfinished = BeAttackState::create(UnfinishedStateTag, unfinishItem, 100);
////    unfinished->addTransition(toRuinsTransition, RuinsStateTag);
////    
////    
////     MyTiledMenuItemSprite* ruinItem = MyTiledMenuItemSprite::create(CCSprite::create("ruins.png"), CCSprite::create("ruins.png"));
////    RuinState* ruinstate2 = RuinState::create(RuinsStateTag, ruinItem);
////    ruinItem->setEnabled(false);
////    ruinItem->setScale(dbItem->getContentSize().width/ruinstate2->item->getContentSize().width);
//#if game_version == soft_version
//    MyBattleBuilding* diaobao = MyBattleBuilding::create(diaobaoTag,CCSizeMake(3,3),defender,level);
//#endif
//#if game_version == hard_version
//    MyBattleBuilding* diaobao = MyBattleBuilding::create(diaobaoTag,CCSizeMake(2,2),defender,level);
//#endif
////    diaobao->addState(ruinstate2);
//    diaobao->addState(unfinished);
//    diaobao->setTag(diaobaoTag);
//    diaobao->setBuildingName(CCString::create("机枪碉堡"),88);
//    diaobao->displaySummary();
//    
//
////    CCLabelTTF* name = CCLabelTTF::create("机枪碉堡","Arial",22);
////    //    name->setFontSize(transWindowToGLInRetina(1));
////    
////    name->setColor(ccWHITE);
////    name->setPosition(ccp(0,88));
////    name->setTag(nameFontTag);
////
////    char str[5] = {0};
////    sprintf(str, "等级 %d",level);
////
////    CCLabelTTF* levelFont = CCLabelTTF::create(str,"Arial",18);
////    
////    levelFont -> setPosition(ccp(0,66));
////    levelFont->setColor(ccWHITE);
////    levelFont->setTag(levelFontTag);
////    diaobao->addChild(name,20);
////    diaobao->addChild(levelFont,20);
//
//    return diaobao;
//}

//MyBuilding* MyGameFactory::createDefenderInCreate(int tag,cocos2d::CCObject *target,int level) {
//
//    
//    CCSprite* byItem;
//    if(tag == dapaoTag) {
////        CCSprite* grayBy = CCSprite::createWithSpriteFrameName("antiTankld.png");
////        grayBy->setColor(ccGRAY);
////        byItem = CCSprite::createWithSpriteFrameName("antiTankld.png");
////        byItem->setAnchorPoint(ccp(0.5,0.4));
////        CCSprite* zhendi = CCSprite::createWithSpriteFrameName("position.png");
////        zhendi->setPosition(ccp(93,54));
////        byItem->addChild(zhendi,-1);
////
//        byItem = NULL;
//    } else {
////        CCSprite* grayBy = CCSprite::create("diaobao.png");
////        grayBy->setColor(ccGRAY);
//        byItem = CCSprite::createWithSpriteFrameName("diaobao.png");
//        byItem->setAnchorPoint(ccp(0.5,0.5));
//    }
//    
//    
//    
//    
//    
//    NormalState* workState = NormalState::create(WorkStateTag, byItem);
//    
//    TransitionInfo* infoItem =  TransitionInfo::create(InfoTransition,"info.png",workState,menu_selector(MyState::infoCallBack));
////    infoItem->setVisible(false);
////    infoItem->setPosition(ccp(56,140));
////    infoItem->setTag(InfoTransition);
//    
//    
//    MyBuilding* BDbuilding;
//    if(tag == dapaoTag) {
////        BDbuilding = MyBuilding::create(CCSizeMake(3,3),unfinishedState,buildItem,sellItem,infoItem,updateItem ,NULL);
//#if game_version == soft_version
//        BDbuilding = MyBuilding::create(dapaoTag,CCSizeMake(4,4),workState,level,10);
//#endif
//#if game_version == hard_version
//        BDbuilding = MyBuilding::create(dapaoTag,CCSizeMake(3,3),workState,level,25);
//#endif
//        BDbuilding->setTag(dapaoTag);
//        BDbuilding->setBuildingName(CCString::create("反坦克炮"),88);
//      
//        BDbuilding->setSummaryCount(500);
//        BDbuilding->resourceTag = ironTag;
//
////        CCLabelTTF* name = CCLabelTTF::create("反坦克炮","Arial",22);
////        name->setFontSize(transWindowToGLInRetina(1));
////        name->setColor(ccWHITE);
////        name->setPosition(ccp(0,88));
////        name->setTag(nameFontTag);
////        name->setVisible(false);
////    
////        char str[5] = {0};
////        sprintf(str, "等级 %d",level);
////     
////        CCLabelTTF* levelFont = CCLabelTTF::create(str,"Arial",18);
////        
////        levelFont -> setPosition(ccp(0,66));
////        levelFont->setColor(ccWHITE);
////        levelFont->setTag(levelFontTag);
////        levelFont->setVisible(false);
////        BDbuilding->addChild(name,20);
////        BDbuilding->addChild(levelFont,20);
//    } else {
//#if game_version == soft_version
//        BDbuilding = MyBuilding::create(diaobaoTag,CCSizeMake(3,3),workState,level,10);
//#endif
//#if game_version == hard_version
//        BDbuilding = MyBuilding::create(diaobaoTag,CCSizeMake(2,2),workState,level,25);
//#endif
//        BDbuilding->setTag(diaobaoTag);
//        BDbuilding->setSummaryCount(400);
//        BDbuilding->resourceTag = ironTag;
//        BDbuilding->setBuildingName(CCString::create("机枪碉堡"),70);
//       
////        CCLabelTTF* name = CCLabelTTF::create("机枪碉堡","Arial",22);
////        //    name->setFontSize(transWindowToGLInRetina(1));
////        
////        name->setColor(ccWHITE);
////        name->setPosition(ccp(0,70));
////        name->setTag(nameFontTag);
////        name->setVisible(false);
////        
////        char str[5] = {0};
////        sprintf(str, "等级 %d",level);
////
////        CCLabelTTF* levelFont = CCLabelTTF::create(str,"Arial",18);
////        
////        levelFont -> setPosition(ccp(0,50));
////        levelFont->setColor(ccWHITE);
////        levelFont->setTag(levelFontTag);
////        levelFont->setVisible(false);
////        BDbuilding->addChild(name,20);
////        BDbuilding->addChild(levelFont,20);
//    }
//    TransitionInfo* updateItem =  TransitionInfo::create(UpdateTransition,"update.png",BDbuilding,menu_selector(MyBuilding::updateLevel));
//    
//    
////    updateItem->setVisible(false);
////    updateItem->setPosition(ccp(-56,140));
////    updateItem->setTag(UpdateTransition);
//    
//    workState->addTransition(UpdateTransition, WorkStateTag,updateItem);
//    workState->addTransition(InfoTransition, WorkStateTag,infoItem);
//    
////    BDbuilding->addChild(updateItem);
//    
//    BDbuilding->addState(workState);
//    return BDbuilding;
//}

//MyBattleBuilding* MyGameFactory::createBattleDaPao(cocos2d::CCObject *target,int level) {
//    
////    CCSprite* dbItem = CCSprite::createWithSpriteFrameName("antiTankfld (0).png");
////    dbItem->setAnchorPoint(ccp(0.5,0.4));
////    CCSprite* zhendi = CCSprite::createWithSpriteFrameName("position.png");
////    zhendi->setPosition(ccp(92,54));
////    dbItem->addChild(zhendi,-1);
//    
//    AoeDefendState* defender = AoeDefendState::create(DefendStateTag, NULL,CCString::create("antiTank"),dpBaseHealth,dpBaseRange,dpBaseDamage,dpBaseSplash,1.3);
//    
//    
//    GXFX* fx0 = GXFX::create(GXUtil::initAction("firelightld", 0.12,false), 4,0);
//    fx0->setPosition(ccp(19,14));
//    CCArray* ani0 = CCArray::create();
//    ani0->addObject(fx0);
//    defender->setAnimate(GXAnimateWithFx::create(GXUtil::initAction("antiTankfld", 0.12,false),ani0), 0);
//    
//    GXFX* fx1 = GXFX::create(GXUtil::initAction("firelightd", 0.12,false), 4,0);
//    fx1->setPosition(ccp(94,-12));
//    CCArray* ani1 = CCArray::create();
//    ani1->addObject(fx1);
//    defender->setAnimate(GXAnimateWithFx::create(GXUtil::initAction("antiTankfd", 0.12,false),ani1), 1);
//    
//    GXFX* fx2 = GXFX::create(GXUtil::initAction("firelightrd", 0.12,false), 4,0);
//    fx2->setPosition(ccp(167,17));
//    CCArray* ani2 = CCArray::create();
//    ani2->addObject(fx2);
//    defender->setAnimate(GXAnimateWithFx::create(GXUtil::initAction("antiTankfrd", 0.12,false),ani2), 2);
//    
//    GXFX* fx3 = GXFX::create(GXUtil::initAction("firelightr", 0.12,false), 4,0);
//    fx3->setPosition(ccp(207,70));
//    CCArray* ani3 = CCArray::create();
//    ani3->addObject(fx3);
//    defender->setAnimate(GXAnimateWithFx::create(GXUtil::initAction("antiTankfr", 0.12,false),ani3), 3);
//    
//    GXFX* fx4 = GXFX::create(GXUtil::initAction("firelightru", 0.03,false), 4,0);
//    fx4->setPosition(ccp(181,127));
//    CCArray* ani4 = CCArray::create();
//    ani4->addObject(fx4);
//    defender->setAnimate(GXAnimateWithFx::create(GXUtil::initAction("antiTankfru", 0.12,false),ani4), 4);
//    
//    GXFX* fx5 = GXFX::create(GXUtil::initAction("firelightu", 0.03,false), 4,0);
//    fx5->setPosition(ccp(91,164));
//    CCArray* ani5 = CCArray::create();
//    ani5->addObject(fx5);
//    defender->setAnimate(GXAnimateWithFx::create(GXUtil::initAction("antiTankfu", 0.12,false),ani5), 5);
//    
//    GXFX* fx6 = GXFX::create(GXUtil::initAction("firelightlu", 0.03,false), 4,0);
//    fx6->setPosition(ccp(13,120));
//    CCArray* ani6 = CCArray::create();
//    ani6->addObject(fx6);
//    defender->setAnimate(GXAnimateWithFx::create(GXUtil::initAction("antiTankflu", 0.12,false),ani6), 6);
//    
//    GXFX* fx7 = GXFX::create(GXUtil::initAction("firelightl", 0.03,false), 4,0);
//    fx7->setPosition(ccp(-14,65));
//    CCArray* ani7 = CCArray::create();
//    ani7->addObject(fx7);
//    defender->setAnimate(GXAnimateWithFx::create(GXUtil::initAction("antiTankfl", 0.12,false),ani7), 7);
//    
////    defender->addTransition(toRuinsTransition, RuinsStateTag);
//    
////    MyTiledMenuItemSprite* ruinItem = MyTiledMenuItemSprite::create(CCSprite::create("ruins.png"), CCSprite::create("ruins.png"));
////    RuinState* ruinstate2 = RuinState::create(RuinsStateTag, ruinItem);
////    ruinItem->setEnabled(false);
////    ruinItem->setScale(dbItem->getContentSize().width/ruinstate2->item->getContentSize().width);
//    
//    CCSprite* unfinishItem = CCSprite::createWithSpriteFrameName("buildstruct2x2(0).png");
//    BeAttackState* unfinished = BeAttackState::create(UnfinishedStateTag, unfinishItem, 100);
////    unfinished->addTransition(toRuinsTransition, RuinsStateTag);
//    
//    MyBattleBuilding* dapao = MyBattleBuilding::create(dapaoTag,CCSizeMake(3,3),defender,level);
////    dapao->addState(ruinstate2);
//    dapao->addState(unfinished);
//    dapao->setTag(dapaoTag);
//    dapao->setBuildingName(CCString::create("机枪碉堡"),70);
//    dapao->displaySummary();
////    CCLabelTTF* name = CCLabelTTF::create("反坦克炮","Arial",22);
////    //    name->setFontSize(transWindowToGLInRetina(1));
////    
////    name->setColor(ccWHITE);
////    name->setPosition(ccp(0,108));
////    name->setTag(nameFontTag);
////
////    char str[5] = {0};
////    sprintf(str, "等级 %d",level);
////    CCLabelTTF* levelFont = CCLabelTTF::create(str,"Arial",18);
////    
////    levelFont -> setPosition(ccp(0,86));
////    levelFont->setColor(ccWHITE);
////    levelFont->setTag(levelFontTag);
////    dapao->addChild(name,20);
////    dapao->addChild(levelFont,20);
//    
//    return dapao;
//}

//MyBuilding* MyGameFactory::createKuangchang(CCObject* target,int level) {
//  
//    
//    
////    CCSprite* grayBd = CCSprite::create("buildStruct.png");
////    grayBd->setColor(ccGRAY);
////    MyTiledMenuItemSprite* buildStructItem = MyTiledMenuItemSprite::create(CCSprite::create("buildStruct.png"), grayBd);
////    
////    
////    NormalState* unfinishedState = NormalState::create(UnfinishedStateTag,buildStructItem);
////    
////    
////    MyMenuItem* buildItem =  MyMenuItem::create(CCSprite::create("build.png"),unfinishedState,menu_selector(NormalState::changeIdCallBack));
////    buildItem->setPosition(transWindowToGLInRetina(-28,80));
////    buildItem->setTag(BuildTransition);
////    buildItem->setVisible(false);
////    
////    MyMenuItem* sellItem =  MyMenuItem::create(CCSprite::create("sell.png"),target,menu_selector(NormalState::sellCallBack));
////    sellItem->setPosition(transWindowToGLInRetina(28,80));
////    sellItem->setTag(sellTransition);
////    sellItem->setVisible(false);
////    
////    unfinishedState->addTransition(BuildTransition, WorkStateTag);
////    unfinishedState->addTransition(sellTransition, DestroyStateTag);
//    
//    
//    
//    
//    CCSprite* byItem = CCSprite::createWithSpriteFrameName("kc.png");
//    byItem->setAnchorPoint(ccp(0.45,0.4));
//    CollectState* workState = CollectState::create(WorkStateTag, byItem,kcBaseColletSpeed,kcBaseColletMaxCapacity,ironTag);
//    
//    TransitionInfo* collectItem =  TransitionInfo::create(CollectTransition,"collect.png",workState,menu_selector(CollectState::doCollect));
////    collectItem->setVisible(false);
////    collectItem->setPosition(ccp(0,160));
////    collectItem->setTag(CollectTransition);
//    
//    TransitionInfo* infoItem =  TransitionInfo::create(InfoTransition,"info.png",workState,menu_selector(MyState::infoCallBack));
////    infoItem->setVisible(false);
////    infoItem->setPosition(ccp(96,160));
////    infoItem->setTag(InfoTransition);
//    
//    
//#if game_version == soft_version
//    MyBuilding* BDbuilding = MyBuilding::create(kuangchangTag,CCSizeMake(4,4),workState,level,10);
//#endif
//#if game_version == hard_version
//    MyBuilding* BDbuilding = MyBuilding::create(kuangchangTag,CCSizeMake(3,3),workState,level,10);
//#endif
//    BDbuilding->addState(workState);
//    BDbuilding->setTag(kuangchangTag);
//    BDbuilding->setSummaryCount(200);
//    BDbuilding->resourceTag = oilTag;
//    
//    TransitionInfo* updateItem =  TransitionInfo::create(UpdateTransition,"update.png",BDbuilding,menu_selector(MyBuilding::updateLevel));
////    updateItem->setVisible(false);
////    updateItem->setPosition(ccp(-96,160));
////    updateItem->setTag(UpdateTransition);
////    BDbuilding->addChild(updateItem);
//    
//    workState->addTransition(UpdateTransition, WorkStateTag,updateItem);
//    workState->addTransition(CollectTransition, WorkStateTag,collectItem);
//    workState->addTransition(InfoTransition, WorkStateTag,infoItem);
//    
//    
//    BDbuilding->setBuildingName(CCString::create("炼钢厂"),108);
//   
////    CCLabelTTF* name = CCLabelTTF::create("炼钢场","Arial",22);
////    //    name->setFontSize(transWindowToGLInRetina(1));
////    
////    name->setColor(ccWHITE);
////    name->setPosition(ccp(0,108));
////    name->setTag(nameFontTag);
////    name->setVisible(false);
////    char str[5] = {0};
////    sprintf(str, "等级 %d",level);
////    CCLabelTTF* levelFont = CCLabelTTF::create(str,"Arial",18);
////    
////    
////    levelFont -> setPosition(ccp(0,86));
////    levelFont->setColor(ccWHITE);
////    levelFont->setTag(levelFontTag);
////    levelFont->setVisible(false);
////    BDbuilding->addChild(name,20);
////    BDbuilding->addChild(levelFont,20);
//    return BDbuilding;
//}


//MyBuilding* MyGameFactory::createZhihuisuo(CCObject* target,int level) {
//    
//    
//      
////    CCSprite* grayBd = CCSprite::create("buildStruct.png");
////    grayBd->setColor(ccGRAY);
////    MyTiledMenuItemSprite* buildStructItem = MyTiledMenuItemSprite::create(CCSprite::create("buildStruct.png"), grayBd);
////    
////    
////    NormalState* unfinishedState = NormalState::create(UnfinishedStateTag,buildStructItem);
////    
////    MyMenuItem* buildItem =  MyMenuItem::create(CCSprite::create("build.png"),unfinishedState,menu_selector(NormalState::changeIdCallBack));
////    buildItem->setPosition(transWindowToGLInRetina(-28,80));
////    buildItem->setTag(BuildTransition);
////    buildItem->setVisible(false);
////    
////    MyMenuItem* sellItem =  MyMenuItem::create(CCSprite::create("sell.png"),target,menu_selector(NormalState::sellCallBack));
////    sellItem->setPosition(transWindowToGLInRetina(28,80));
////    sellItem->setTag(sellTransition);
////    sellItem->setVisible(false);
////    
////    unfinishedState->addTransition(BuildTransition, WorkStateTag);
////    unfinishedState->addTransition(sellTransition, DestroyStateTag);
//    
////    CCSprite* grayBy = CCSprite::create("zhs1.png");
////    grayBy->setColor(ccGRAY);
//    CCSprite* byItem =CCSprite::createWithSpriteFrameName("zhs1.png");
//    byItem->setAnchorPoint(ccp(0.5,0.45));
//    NormalState* workState = NormalState::create(WorkStateTag, byItem);
//    
//    TransitionInfo* infoItem =  TransitionInfo::create(InfoTransition,"info.png",workState,menu_selector(MyState::infoCallBack));
////    infoItem->setVisible(false);
////    infoItem->setPosition(ccp(56,160));
////    infoItem->setTag(InfoTransition);
//    
//    
//
//    
//    
//#if game_version == soft_version
//    MyBuilding* BDbuilding = MyBuilding::create(zhihuisuoTag,CCSizeMake(5,5),workState,level,10);
//#endif
//#if game_version == hard_version
//    MyBuilding* BDbuilding = MyBuilding::create(zhihuisuoTag,CCSizeMake(4,4),workState,level,25);
//#endif
//    BDbuilding->addState(workState);
//    BDbuilding->setTag(zhihuisuoTag);
//    BDbuilding->setSummaryCount(2000);
//    BDbuilding->resourceTag = ironTag;
//    
//    TransitionInfo* updateItem =  TransitionInfo::create(UpdateTransition,"update.png",BDbuilding,menu_selector(MyBuilding::updateLevel));
////    updateItem->setVisible(false);
////    updateItem->setPosition(ccp(-56,160));
////    updateItem->setTag(UpdateTransition);
////    BDbuilding->addChild(updateItem);
//    
//    workState->addTransition(UpdateTransition, WorkStateTag,updateItem);
//    workState->addTransition(InfoTransition, WorkStateTag,infoItem);
//
//    BDbuilding->setBuildingName(CCString::create("基地"),124);
//    
////    CCLabelTTF* name = CCLabelTTF::create("基地","Arial",22);
////    
////    //    name->setFontSize(transWindowToGLInRetina(1));
////    
////    name->setColor(ccWHITE);
////    name->setPosition(ccp(0,124));
////    name->setTag(nameFontTag);
////    name->setVisible(false);
////    
////    char str[5] = {0};
////    sprintf(str, "等级 %d",level);
////    
////    CCLabelTTF* levelFont = CCLabelTTF::create(str,"Arial",18);
////    
////    levelFont -> setPosition(ccp(0,102));
////    levelFont->setColor(ccWHITE);
////    levelFont->setTag(levelFontTag);
////    levelFont->setVisible(false);
////    BDbuilding->addChild(name,20);
////    BDbuilding->addChild(levelFont,20);
//    return BDbuilding;
//}


//MyBuilding* MyGameFactory::createLianluozhongxin(CCObject* target,int level) {
//    
//    CCSprite* byItem =CCSprite::createWithSpriteFrameName("communication.png");
//    byItem->setAnchorPoint(ccp(0.4,0.29));
//    byItem->setScale(0.9);
//    NormalState* workState = NormalState::create(WorkStateTag, byItem);
//    
//    TransitionInfo* infoItem =  TransitionInfo::create(InfoTransition,"info.png",workState,menu_selector(MyState::infoCallBack));
//    //    infoItem->setVisible(false);
////    infoItem->setPosition(ccp(0,160));
////    infoItem->setTag(InfoTransition);
//    
//    
//#if game_version == soft_version
//    MyBuilding* BDbuilding = MyBuilding::create(lianluozhongxinTag,CCSizeMake(4,4),workState,level,1);
//#endif
//#if game_version == hard_version
//    MyBuilding* BDbuilding = MyBuilding::create(lianluozhongxinTag,CCSizeMake(3,3),workState,level,1);
//#endif
//    BDbuilding->addState(workState);
//    BDbuilding->setTag(lianluozhongxinTag);
//    BDbuilding->setSummaryCount(500000);
//    BDbuilding->resourceTag = ironTag;
//    
//    //    BDbuilding->addChild(updateItem);
//    ;
//    workState->addTransition(InfoTransition, WorkStateTag,infoItem);
//
//    BDbuilding->setBuildingName(CCString::create("联络中心"),104);
//    
////    CCLabelTTF* name = CCLabelTTF::create("联络中心","Arial",22);
////    
////    //    name->setFontSize(transWindowToGLInRetina(1));
////    
////    name->setColor(ccWHITE);
////    name->setPosition(ccp(0,104));
////    name->setTag(nameFontTag);
////    name->setVisible(false);
////
////    BDbuilding->addChild(name,20);
//  
//    return BDbuilding;
//}

//MyBuilding* MyGameFactory::createCombineWall(int tag,CCObject* target,int level) {
//    CCSprite* wallItem = NULL;
//    if (tag == combineWall5X1Tag) {
//        wallItem = CCSprite::createWithSpriteFrameName("combineWall5x1.png");
//        wallItem->setAnchorPoint(ccp(0.5,0.445));
//        wallItem->setScale(0.965);
//    } else if(tag == combineWall1X5Tag){
//        wallItem = CCSprite::createWithSpriteFrameName("combineWall1x5.png");
//        wallItem->setAnchorPoint(ccp(0.483,0.46));
//        wallItem->setScale(0.965);
//    }
//
//    SplitState* wallState = SplitState::create(WorkStateTag, wallItem,wallTag);
//    
//    
//    TransitionInfo* infoItem =  TransitionInfo::create(InfoTransition,"info.png",wallState,menu_selector(MyState::infoCallBack));
//    
////    infoItem->setPosition(ccp(28,70));
////    infoItem->setTag(InfoTransition);
//    
//    MyBuilding* wall1;
//    if (tag == combineWall5X1Tag) {
//#if game_version == soft_version
//        wall1= MyBuilding::create(combineWall5X1Tag,CCSizeMake(5,1),wallState,level,10);
//#endif
//#if game_version == hard_version
//        wall1 = MyBuilding::create(combineWall5X1Tag,CCSizeMake(5,1),wallState,level,25);
//#endif
//    } else if(tag == combineWall1X5Tag) {
//#if game_version == soft_version
//        wall1 = MyBuilding::create(combineWall1X5Tag,CCSizeMake(1,5),wallState,level,10);
//#endif
//#if game_version == hard_version
//        wall1 = MyBuilding::create(combineWall1X5Tag,CCSizeMake(1,5),wallState,level,25);
//#endif
//    }
//    wall1->setSummaryCount(200);
//    wall1->resourceTag = ironTag;
//    
//    TransitionInfo* updateItem =  TransitionInfo::create(UpdateTransition,"update.png",wall1,menu_selector(MyBuilding::updateLevel));
//    //    updateItem->setVisible(false);
////    updateItem->setPosition(ccp(-56,140));
////    updateItem->setTag(UpdateTransition);
//    
//    
//    TransitionInfo* splitItem =  TransitionInfo::create(SplitTransition,"split.png",wallState,menu_selector(SplitState::toSplitCallBack));
//    //    updateItem->setVisible(false);
////    splitItem->setPosition(ccp(-56,140));
////    splitItem->setTag(SplitTransition);
//    
//    wallState->addTransition(SplitTransition, WorkStateTag,splitItem);
//    wallState->addTransition(UpdateTransition, WorkStateTag,updateItem);
//    wallState->addTransition(InfoTransition, WorkStateTag,infoItem);
//    
//    wall1->setBuildingName(CCString::create("强化路障"),80);
//    
//    //    CCLabelTTF* name = CCLabelTTF::create("路障","Arial",22);
//    //    //    name->setFontSize(transWindowToGLInRetina(1));
//    //
//    //    name->setColor(ccWHITE);
//    //    name->setPosition(ccp(0,80));
//    //    name->setTag(nameFontTag);
//    //    name->setVisible(false);
//    //    char str[5] = {0};
//    //    sprintf(str, "等级 %d",level);
//    //    CCLabelTTF* levelFont = CCLabelTTF::create(str,"Arial",18);
//    //
//    //    levelFont -> setPosition(ccp(0,60));
//    //    levelFont->setColor(ccWHITE);
//    //    levelFont->setTag(levelFontTag);
//    //    levelFont->setVisible(false);
//    //    wall1->addChild(name,20);
//    //    wall1->addChild(levelFont,20);
//    return wall1;
//    
//}

//MyBattleBuilding* MyGameFactory::createBattleCombineWall(int tag,CCObject* target,int level) {
//    
//    CCSprite* wallItem = NULL;
//    if (tag == combineWall5X1Tag) {
//        wallItem = CCSprite::createWithSpriteFrameName("combineWall5x1.png");
//        wallItem->setAnchorPoint(ccp(0.5,0.445));
//        wallItem->setScale(0.965);
//    } else if(tag == combineWall1X5Tag){
//        wallItem = CCSprite::createWithSpriteFrameName("combineWall1x5.png");
//        wallItem->setAnchorPoint(ccp(0.483,0.46));
//        wallItem->setScale(0.965);
//    }
//    
//    
//    BeAttackState* beAttackState = BeAttackState::create(BeAttackStateTag, wallItem,wallBaseHealth);
//    beAttackState->addTransition(toRuinsTransition, RuinsStateTag);
//    
//    
//    MyBattleBuilding* BDbuilding = NULL;
//    
//    if (tag == combineWall5X1Tag) {
//        BDbuilding= MyBattleBuilding::create(combineWall5X1Tag,CCSizeMake(5,1),beAttackState,level);
//    } else if(tag == combineWall1X5Tag) {
//        BDbuilding = MyBattleBuilding::create(combineWall1X5Tag,CCSizeMake(1,5),beAttackState,level);
//    }
//    
//    
//    return BDbuilding;
//
//}

//MyBuilding* MyGameFactory::createByTag(int tag, cocos2d::CCObject *target,int level) {
//    MyBuilding* building =NULL;
//    if (tag == bingyingTag) {
//        building = BingYing::createNormal(target,level);
//    } else if (tag == wallTag) {
//        building = Wall::createNormal(target,level);
//    } else if (tag == diaobaoTag) {
//        building = DiaoBao::createNormal(target,level);
//    } else if(tag == dapaoTag) {
//        building = DaPao::createNormal(target,level);
//    } else if (tag == youtianTag) {
//        building = YouTian::createNormal(target,level,bean->arg0);
//    } else if (tag == kuangchangTag) {
////        building = MyGameFactory::createKuangchang(target,level);
//        building = KuangChang::createNormal(target,level,bean->arg0);
//    } else if (tag == zhihuisuoTag) {
//        building = ZhiHuiSuo::createNormal(target,level);
//    } else if (tag == lianluozhongxinTag) {
//        building = LianLuoZhongXin::createNormal(target, level);
//    } else if (tag == lianluozhongxinDestroyTag) {
//        building = LianLuoZhongXin::createDestroy(target,level);
//    } else if (tag == combineWall5X1Tag) {
//        building = CombineWall::createNormal(combineWall5X1Tag,target,level);
//    } else if (tag == combineWall1X5Tag) {
//        building = CombineWall::createNormal(combineWall1X5Tag,target,level);
//    } else if (tag == superKuangChangTag) {
//        building = SuperKuangChang::createNormal(target,level,bean->arg0);
//    } else if (tag == superYouTianTag) {
//        building = SuperYouTian::createNormal(target,level,bean->arg0);
//    }
//    else if (tag >= ornamentsDefineTag) {
//        building = Ornament::createNormal(tag, target);
//    }  
//    return building;
//}

MyBuilding* MyGameFactory::createReadyToBuildByTag(int tag, cocos2d::CCObject *target) {
    MyBuilding* building =NULL;
    CCSprite* byItem = NULL;
    
    ReadyToBuild* readyState = ReadyToBuild::create(ReadyToBuildStateTag, byItem);
    TransitionInfo* cancelItem = TransitionInfo::create(CancelTransition,"cancel.png",readyState,menu_selector(ReadyToBuild::cancelCallBack));
    
    readyState->addTransition(CancelTransition, DestroyStateTag,cancelItem);
    TransitionInfo* sureItem = TransitionInfo::create(sureTransition,"buildsure.png", readyState,menu_selector(ReadyToBuild::toBuildCallback));
    readyState->addTransition(sureTransition, UnfinishedStateTag,sureItem);
    
    if (tag == bingyingTag) {
//        building = MyGameFactory::createBingYing(target,1);
        building = BingYing::createNormal(target,1);
//        CCSprite* whiteBy = CCSprite::create("by7.png");
//        whiteBy->setColor(ccGRAY);
//        CCSprite* transby = CCSprite::create("by7.png");
//        transby->setColor(ccWHITE);
        byItem = CCSprite::createWithSpriteFrameName("by7.png");
        byItem->setAnchorPoint(ccp(0.5,0.45));
       
    } else if (tag == wallTag) {
        building = Wall::createNormal(target,1);
//        CCSprite* whiteBy = CCSprite::createWithSpriteFrameName("wall1c.png");
//        whiteBy->setColor(ccGRAY);
//        CCSprite* transby = CCSprite::createWithSpriteFrameName("wall1c.png");
//        transby->setColor(ccWHITE);
        byItem = CCSprite::createWithSpriteFrameName("wall1c.png");
        byItem->setAnchorPoint(ccp(0.45,0.37));
    } else if (tag == dapaoTag) {
        building = DaPao::createReady(target,1);
//        CCSprite* whiteBy = CCSprite::createWithSpriteFrameName("antiTankld.png");
//        whiteBy->setColor(ccGRAY);
//        CCSprite* transby = CCSprite::createWithSpriteFrameName("antiTankld.png");
//        transby->setColor(ccWHITE);
        byItem = CCSprite::createWithSpriteFrameName("antiTankld.png");
        byItem->setAnchorPoint(ccp(0.5,0.5));
        CCSprite* zhendi = CCSprite::createWithSpriteFrameName("position.png");
        zhendi->setPosition(ccp(byItem->getContentSize().width/2,byItem->getContentSize().height/2));
        byItem->addChild(zhendi,-1);
    } else if(tag == diaobaoTag) {
        building = DiaoBao::createNormal(target,1);
//        CCSprite* whiteBy = CCSprite::create("diaobao.png");
//        whiteBy->setColor(ccGRAY);
//        CCSprite* transby = CCSprite::create("diaobao.png");
//        transby->setColor(ccWHITE);
        byItem = CCSprite::createWithSpriteFrameName("diaobao.png");
        byItem->setAnchorPoint(ccp(0.45,0.5));
    } else if (tag == youtianTag) {
        building = YouTian::createNormal(target,1,0,0);
//        CCSprite* whiteBy = CCSprite::create("yt2.png");
//        whiteBy->setColor(ccGRAY);
//        CCSprite* transby = CCSprite::create("yt2.png");
//        transby->setColor(ccWHITE);
        byItem = CCSprite::createWithSpriteFrameName("yt2.png");
        byItem->setAnchorPoint(ccp(0.5,0.35));
    } else if (tag == kuangchangTag) {
//        building = MyGameFactory::createKuangchang(target,1);
        building = KuangChang::createNormal(target,1,0,0);
//        CCSprite* whiteBy = CCSprite::create("kc.png");
//        whiteBy->setColor(ccGRAY);
//        CCSprite* transby = CCSprite::create("kc.png");
//        transby->setColor(ccWHITE);
        byItem = CCSprite::createWithSpriteFrameName("kc.png");
        byItem->setAnchorPoint(ccp(0.45,0.4));
    } else if (tag == zhihuisuoTag) {
        building = ZhiHuiSuo::createNormal(target,1);
//        CCSprite* whiteBy = CCSprite::create("zhs1.png");
//        whiteBy->setColor(ccGRAY);
//        CCSprite* transby = CCSprite::create("zhs1.png");
//        transby->setColor(ccWHITE);
        byItem = CCSprite::createWithSpriteFrameName("zhs1.png");
        byItem->setAnchorPoint(ccp(0.5,0.45));
    } else if (tag == lianluozhongxinTag ) {
        building = LianLuoZhongXin::createNormal(target,1);
        byItem = CCSprite::createWithSpriteFrameName("communication.png");
        byItem->setScale(0.9);
        byItem->setAnchorPoint(ccp(0.4,0.29));
    } else if(tag == superKuangChangTag) {
        building = SuperKuangChang::createNormal(target,1,0,0);
        byItem = CCSprite::createWithSpriteFrameName("superKC.png");
        byItem->setAnchorPoint(ccp(0.38,0.30));
    } else if(tag == superYouTianTag) {
        building = SuperYouTian::createNormal(target,1,0,0);
        byItem = CCSprite::createWithSpriteFrameName("superYT.png");
        byItem->setAnchorPoint(ccp(0.4,0.27));
    }else if(tag == GarbageCenterTag) {
        building = GarbageCenter::createNormal(target,1);
        byItem = CCSprite::createWithSpriteFrameName("Recycling.png");
        byItem->setAnchorPoint(ccp(0.5,0.4));
        readyState->maxCount = garbageCenterMaxCount;
        readyState->buildingInfo = GarbageCenter::getGarbageCenterInfo();
    } else if(tag == CellarTag) {
        building = Cellar::createNormal(target,1);
        byItem = CCSprite::createWithSpriteFrameName("cellar.png");
        byItem->setAnchorPoint(ccp(0.45,0.47));
        readyState->maxCount = CellarMaxCount;
        readyState->buildingInfo = Cellar::getCellarInfo();
    }  else if(tag == JammerTag) {
        building = Jammer::createNormal(target,1);
        byItem = CCSprite::createWithSpriteFrameName("jammer.png");
        byItem->setAnchorPoint(ccp(0.41,0.18));
        readyState->maxCount = JammerMaxCount;
        readyState->buildingInfo = Jammer::getJammerInfo();
    }
    
    readyState->setItem(byItem);
    
    if (tag != wallTag) {
        addState(building, UnfinishedStateTag,target);
    }
    building->addState(readyState);
    building->changeStateById(ReadyToBuildStateTag);
    
    return building;
}

CCSprite* MyGameFactory::getBuildingSpriteByTag(int tag) {
    CCSprite* byItem = NULL;
    if (tag == bingyingTag) {
        byItem = CCSprite::createWithSpriteFrameName("by7.png");
        byItem->setAnchorPoint(ccp(0.5,0.45));
    } else if (tag == wallTag) {
        byItem = CCSprite::createWithSpriteFrameName("wall1c.png");
//        byItem->setAnchorPoint(ccp(0.45,0.37));
    } else if (tag == dapaoTag) {
        byItem = CCSprite::createWithSpriteFrameName("antiTankld.png");
        byItem->setAnchorPoint(ccp(0.5,0.5));
        CCSprite* zhendi = CCSprite::createWithSpriteFrameName("position.png");
        zhendi->setPosition(ccp(byItem->getContentSize().width/2,byItem->getContentSize().height/2));
        byItem->addChild(zhendi,-1);
    } else if(tag == diaobaoTag) {
        byItem = CCSprite::createWithSpriteFrameName("diaobao.png");
        byItem->setAnchorPoint(ccp(0.45,0.5));
    } else if (tag == youtianTag) {
        byItem = CCSprite::createWithSpriteFrameName("yt2.png");
//        byItem->setAnchorPoint(ccp(0.5,0.35));
    } else if (tag == kuangchangTag) {
        byItem = CCSprite::createWithSpriteFrameName("kc.png");
//        byItem->setAnchorPoint(ccp(0.45,0.4));
    } else if (tag == zhihuisuoTag) {
        byItem = CCSprite::createWithSpriteFrameName("zhs1.png");
        byItem->setAnchorPoint(ccp(0.5,0.5));
    } else if (tag == lianluozhongxinTag ) {
        byItem = CCSprite::createWithSpriteFrameName("communication.png");
        byItem->setAnchorPoint(ccp(0.4,0.5));
    } else if(tag == superKuangChangTag) {
        byItem = CCSprite::createWithSpriteFrameName("superKC.png");
//        byItem->setAnchorPoint(ccp(0.38,0.30));
    } else if(tag == superYouTianTag) {
        byItem = CCSprite::createWithSpriteFrameName("superYT.png");
//        byItem->setAnchorPoint(ccp(0.4,0.27));
    }else if(tag == GarbageCenterTag) {
        byItem = CCSprite::createWithSpriteFrameName("Recycling.png");
        byItem->setAnchorPoint(ccp(0.5,0.5));
    } else if(tag == CellarTag) {
        byItem = CCSprite::createWithSpriteFrameName("cellar.png");
        byItem->setAnchorPoint(ccp(0.45,0.47));
    } else if(tag == JammerTag) {
        byItem = CCSprite::createWithSpriteFrameName("jammer.png");
        byItem->setAnchorPoint(ccp(0.41,0.43));
    } else if (tag == combineWall5X1Tag) {
        byItem = CCSprite::createWithSpriteFrameName("combineWall5x1.png");
        byItem->setAnchorPoint(ccp(0.5,0.445));
    } else if(tag == combineWall1X5Tag){
        byItem = CCSprite::createWithSpriteFrameName("combineWall1x5.png");
        byItem->setAnchorPoint(ccp(0.483,0.46));
    }

    return byItem;
}

CCLabelTTF* MyGameFactory::getBuildingNameByTag(int tag, int size) {
    CCLabelTTF* label = NULL;
    if (tag == bingyingTag) {
        label = CCLabelTTF::create("兵 营","Arial",size);
    } else if (tag == wallTag) {
        label = CCLabelTTF::create("路 障","Arial",size);
    } else if (tag == dapaoTag) {
        label = CCLabelTTF::create("反坦克炮","Arial",size);
    } else if(tag == diaobaoTag) {
        label = CCLabelTTF::create("机枪碉堡","Arial",size);
    } else if (tag == youtianTag) {
        label = CCLabelTTF::create("炼油厂","Arial",size);
    } else if (tag == kuangchangTag) {
        label = CCLabelTTF::create("炼钢厂","Arial",size);
    } else if (tag == zhihuisuoTag) {
        label = CCLabelTTF::create("基 地","Arial",size);
    } else if (tag == lianluozhongxinTag ) {
        label = CCLabelTTF::create("联络中心","Arial",size);
    } else if(tag == superKuangChangTag) {
        label = CCLabelTTF::create("超级炼钢厂","Arial",size);
    } else if(tag == superYouTianTag) {
        label = CCLabelTTF::create("超级炼油厂","Arial",size);
    }else if(tag == GarbageCenterTag) {
        label = CCLabelTTF::create("回收中心","Arial",size);
    } else if(tag == CellarTag) {
        label = CCLabelTTF::create("地下金库","Arial",size);
    } else if(tag == JammerTag) {
        label = CCLabelTTF::create("干扰发射器","Arial",size);
    }  else if (tag == combineWall5X1Tag) {
        label = CCLabelTTF::create("强化路障","Arial",size);
    } else if(tag == combineWall1X5Tag){
        label = CCLabelTTF::create("强化路障","Arial",size);
    }
    
    return label;
}

MyBuilding* MyGameFactory::createBuildingByBean(BuildingBean* bean,CCObject* target) {
    MyBuilding* building =NULL;
    int tag = bean->tag;
    int level = bean->level;
    if (tag == bingyingTag) {
        building = BingYing::createNormal(target,level);
    } else if (tag == wallTag) {
        building = Wall::createNormal(target,level);
    } else if (tag == diaobaoTag) {
        building = DiaoBao::createNormal(target,level);
    } else if(tag == dapaoTag) {
        building = DaPao::createNormal(target,level);
    } else if (tag == youtianTag) {
        long dt = (MyGameInfo::getInstance()->nowTime - MyGameInfo::getInstance()->lastTime)/1000;
//         CCLog("PID:%d",bean->pid);
        building = YouTian::createNormal(target,level,bean->arg0,dt);
    } else if (tag == kuangchangTag) {
        //        building = MyGameFactory::createKuangchang(target,level);
        long dt = (MyGameInfo::getInstance()->nowTime - MyGameInfo::getInstance()->lastTime)/1000;
//         CCLog("PID:%d",bean->pid);
        building = KuangChang::createNormal(target,level,bean->arg0,dt);
    } else if (tag == zhihuisuoTag) {
        building = ZhiHuiSuo::createNormal(target,level);
    } else if (tag == lianluozhongxinTag) {
        building = LianLuoZhongXin::createNormal(target, level);
    } else if (tag == lianluozhongxinDestroyTag) {
        building = LianLuoZhongXin::createDestroy(target,level);
    } else if (tag == combineWall5X1Tag) {
        building = CombineWall::createNormal(combineWall5X1Tag,target,level);
    } else if (tag == combineWall1X5Tag) {
        building = CombineWall::createNormal(combineWall1X5Tag,target,level);
    } else if (tag == superKuangChangTag) {
        long dt = (MyGameInfo::getInstance()->nowTime - MyGameInfo::getInstance()->lastTime)/1000;
        building = SuperKuangChang::createNormal(target,level,bean->arg0,dt);
    } else if (tag == superYouTianTag) {
        long dt = (MyGameInfo::getInstance()->nowTime - MyGameInfo::getInstance()->lastTime)/1000;
        building = SuperYouTian::createNormal(target,level,bean->arg0,dt);
    } else if(tag == ghostTag) {
        building = Ghost::createNormal(bean->arg0);
    } else if(tag == GarbageCenterTag) {
        building = GarbageCenter::createNormal(target,level);
    } else if(tag == CellarTag) {
        building = Cellar::createNormal(target,level);
    } else if(tag == JammerTag) {
        building = Jammer::createNormal(target,level);
    }
    else if (tag >= ornamentsDefineTag) {
        building = Ornament::createNormal(tag, target);
    }  
    
    building->pid = bean->pid;
//    char str[500] = {0};
#if game_version == soft_version
    if(dynamic_cast<UnfinishedState*>(building->fsm->getCurrentState()) == 0) {
        if (building->contentSizeByTiled.width == 3 && building->getTag() < ornamentsDefineTag) {
            CCSprite* road = CCSprite::createWithSpriteFrameName("road3x3.png");
            building->setRoad(road);
        }else if (building->contentSizeByTiled.width == 4) {
            CCSprite* road = CCSprite::createWithSpriteFrameName("road4x4.png");
            building->setRoad(road);
        }else if (building->contentSizeByTiled.width == 5) {
            CCSprite* road = CCSprite::createWithSpriteFrameName("road5x5.png");
            building->setRoad(road);
        }
    }
#endif
   
    
//    if (dynamic_cast<CollectState*>(building->fsm->getState(WorkStateTag)) != NULL) {
//        long dt = (MyGameInfo::getInstance()->nowTime - MyGameInfo::getInstance()->lastTime)/1000;
//        ((CollectState*)building->fsm->getState(WorkStateTag))->setCapacity(bean->arg0,dt);
//    }
    
    
    CCAssert(building != NULL, "Tag 不合法 ");
    building->setPositionByTiled(ccp(bean->posX,bean->posY));
    if (bean->currentStateId == UnfinishedStateTag) {
        //state其实可以需要什么建什么
        
        addState(building, UnfinishedStateTag, target);
    }
    int minbian = Mathlib::min(building->contentSizeByTiled.width,building->contentSizeByTiled.height);
    //判断是否损毁
    if (bean->lifePercentage < 100) {
        char str[500] = {0};
        CCSprite* ruinItem;
        if(minbian == 1) {
            ruinItem = CCSprite::createWithSpriteFrameName("ruins (2).png");
            CCSize size = ((MyState*)building->fsm->getCurrentState())->getItem()->getContentSize();
            ruinItem->setScale(55/ruinItem->getContentSize().width);
        } else {
#if game_version == soft_version
            sprintf(str, "ruins (%d).png",(int)minbian-1);
#endif
#if game_version == hard_version
            sprintf(str, "ruins (%d).png",(int)minbian);
#endif
            ruinItem = CCSprite::createWithSpriteFrameName(str);
        }
        
        
        CreatorRuinState* ruinstate = CreatorRuinState::create(RuinsStateTag, ruinItem,bean->lifePercentage);
        ruinstate->setCurrentId(bean->currentStateId);
        building->setEnabled(false);
        
        building->addState(ruinstate);
        building->changeStateById(RuinsStateTag);
        if (building->doStateInterval < 0) {
            building->setDoStateInterval(1);
        }
    } else {
        //非损毁~进入应该状态
        building->changeStateById(bean->currentStateId);
    }
    return building;
}

MyBattleBuilding* MyGameFactory::createBattleBuildingByBean(BuildingBean* bean,CCObject* target,bool isDisplaySummary) {
    MyBattleBuilding* building = NULL;
    //得到抢劫率
    float rate = robberRate*((BattleScene*)target)->trophyRate;
  
    if (bean->tag == bingyingTag) {
//        building = MyGameFactory::createBattleBingYing(target,bean->level);
        building = BingYing::createBattle(bean->level,bean->currentStateId);
        if(isDisplaySummary) {
            building->displaySummary();
        }
    } else if (bean->tag == wallTag) {
        building = Wall::createBattle(bean->level,bean->currentStateId);
    } else if (bean->tag == dapaoTag) {
        building = DaPao::createBattle(bean->level,bean->currentStateId);
        if(isDisplaySummary) {
            building->displaySummary();
        }
    } else if (bean->tag == diaobaoTag) {
        building = DiaoBao::createBattle(bean->level,bean->currentStateId);
        if(isDisplaySummary) {
            building->displaySummary();
        }
    } else if (bean->tag == youtianTag) {
        building = YouTian::createBattle(bean->level,bean->currentStateId,bean->arg0,rate);
        if(isDisplaySummary) {
            building->displaySummary();
        }
    } else if (bean->tag == kuangchangTag) {
        building = KuangChang::createBattle(bean->level,bean->currentStateId,bean->arg0,rate);
        if(isDisplaySummary) {
            building->displaySummary();
        }
//        MyGameFactory::createCreateInBattle(kuangchangTag, target,bean->level);
    } else if (bean->tag == zhihuisuoTag) {
        building = ZhiHuiSuo::createBattle(bean->level,bean->currentStateId,rate);
        if(isDisplaySummary) {
            building->displaySummary();
        }
    } else if (bean->tag == lianluozhongxinTag) {
        building = LianLuoZhongXin::createBattle(bean->level,bean->currentStateId);
        if(isDisplaySummary) {
            building->displaySummary();
        }
    } else if(bean->tag == lianluozhongxinDestroyTag) {
        building = LianLuoZhongXin::createBattleDestroy(bean->level,bean->currentStateId);
    } else if(bean->tag == combineWall5X1Tag || bean->tag == combineWall1X5Tag) {
        building = CombineWall::createBattle(bean->tag,bean->level,bean->currentStateId);
    } else if(bean->tag == superYouTianTag) {
        building = SuperYouTian::createBattle(bean->level,bean->currentStateId,bean->arg0,rate);
        if(isDisplaySummary) {
            building->displaySummary();
        }
    } else if(bean->tag == superKuangChangTag) {
        building = SuperKuangChang::createBattle(bean->level,bean->currentStateId,bean->arg0,rate);
        if(isDisplaySummary) {
            building->displaySummary();
        }
    } else if(bean->tag == ghostTag) {
        building = Ghost::createBattle(bean->arg0);
    } else if(bean->tag == GarbageCenterTag) {
        building = GarbageCenter::createBattle(bean->level,bean->currentStateId);
        if(isDisplaySummary) {
            building->displaySummary();
        }
    } else if(bean->tag == CellarTag) {
        building = Cellar::createBattle(bean->level,bean->currentStateId,bean->arg0);
        if(isDisplaySummary) {
            building->displaySummary();
        }
    }  else if(bean->tag == JammerTag) {
        building = Jammer::createBattle(bean->level,bean->currentStateId,bean->arg0);
        if(isDisplaySummary) {
            building->displaySummary();
        }
    }
    else if (bean->tag >= ornamentsDefineTag) {
        building = Ornament::createBattle(bean->tag,bean->level,bean->currentStateId);
        
    }
//    else if (bean->tag == songshuTag) {
//        building = MyGameFactory::createBattleWall(target,bean->level);
//    }
    else {
        return NULL;
    }
    //添加废墟
    building->pid = bean->pid;
    building->changeStateById(bean->currentStateId);
    building->fsm->getCurrentState()->addTransition(toRuinsTransition, RuinsStateTag);
    
    
    BattleRuinState* ruinstate = BattleRuinState::create(RuinsStateTag, "ruins");
//    ruinItem->setScale(((MyState*)(building->fsm->getCurrentState()))->item->getContentSize().width/ruinstate->item->getContentSize().width);
    building->addState(ruinstate);
    
    //bean 不合法
   
    CCAssert(building != NULL, "Tag 不合法");
    building->setPositionByTiled(ccp(bean->posX,bean->posY));
    
//    if (dynamic_cast<ResourceBeAttackState*>(building->fsm->getCurrentState()) != NULL) {
//        long long nowtime = MyGameInfo::getInstance()->nowTime;
//        long long lasttime = MyGameInfo::getInstance()->lastTime;
//        long dt = (nowtime-lasttime)/1000;
//        float rate = robberRate*((BattleScene*)target)->trophyRate;
//        ((ResourceBeAttackState*)building->fsm->getState(BeAttackStateTag))->setCapacity(bean->arg0, dt,rate);
//        if( ((ResourceBeAttackState*)building->fsm->getState(BeAttackStateTag))->resourceTag == oilTag) {
//            //抢劫叠加油
//            //                float rate = robberRate*((BattleScene*)target)->trophyRate;
//            MyGameInfo::getInstance()->setRobberOil(MyGameInfo::getInstance()->getRobberOil() + ((ResourceBeAttackState*)building->fsm->getState(BeAttackStateTag))->getCapacity()*rate);
//            //                MyGameInfo::getInstance()->robberOil += ((ResourceBeAttackState*)building->fsm->getState(BeAttackStateTag))->getCapacity()*rate;
//            //                CCLog("ohe:%f",MyGameInfo::getInstance()->robberOil);
//            //                CCLog("ihe:%f",MyGameInfo::getInstance()->robberIron);
//        } else {
//            //抢劫叠加钢铁
//            //                float rate = robberRate*((BattleScene*)target)->trophyRate;
//            MyGameInfo::getInstance()->setRobberIron( MyGameInfo::getInstance()->getRobberIron()+ ((ResourceBeAttackState*)building->fsm->getState(BeAttackStateTag))->getCapacity()*rate);
//            //                MyGameInfo::getInstance()->robberIron += ((ResourceBeAttackState*)building->fsm->getState(BeAttackStateTag))->getCapacity()*rate;
//            //                CCLog("ohe:%f",MyGameInfo::getInstance()->robberOil);
//            //                CCLog("ihe:%f",MyGameInfo::getInstance()->robberIron);
//        }
//    }
    
//    if(building->getTag() == zhihuisuoTag) {
//        float rate = robberRate*((BattleScene*)target)->trophyRate;
//        //        CCLog("rate:%f",rate);
//        ResourceOnlyBeRobberState* currentState = dynamic_cast<ResourceOnlyBeRobberState*>(building->fsm->getCurrentState());
//        currentState->setOil(Mathlib::max(MyGameInfo::getInstance()->enemyOil*rate,0));
//        currentState->setIron(Mathlib::max(MyGameInfo::getInstance()->enemyIron*rate,0));
//        
//        if (currentState != NULL) {
//            //指挥所叠加
//            MyGameInfo::getInstance()->setRobberOil(MyGameInfo::getInstance()->getRobberOil() + ((ResourceOnlyBeRobberState*)building->fsm->getState(BeAttackStateTag))->getOil());
////            MyGameInfo::getInstance()->robberOil += ((ResourceOnlyBeRobberState*)building->fsm->getState(BeAttackStateTag))->getOil();
//            MyGameInfo::getInstance()->setRobberIron(MyGameInfo::getInstance()->getRobberIron() + ((ResourceOnlyBeRobberState*)building->fsm->getState(BeAttackStateTag))->getIron());
////            MyGameInfo::getInstance()->robberIron += ((ResourceOnlyBeRobberState*)building->fsm->getState(BeAttackStateTag))->getIron();
////            CCLog("ohe:%f",MyGameInfo::getInstance()->robberOil);
////            CCLog("ihe:%f",MyGameInfo::getInstance()->robberIron);
//        }
//    }
    return building;
}

//MyBuilding* MyGameFactory::createOrnaments(int tag, cocos2d::CCObject *target) {
//    
//    
//    
//    CCSprite* ornamentItem;
//    
//    if(tag / stoneBaseTag == 1) {
//        char str[10] = {0};
//        sprintf(str, "stone%d.png",tag%stoneBaseTag);
//        ornamentItem = CCSprite::createWithSpriteFrameName(str);
//        ornamentItem->setAnchorPoint(ccp(0.45,0.45));
//        
//    }else if(tag == songshuTag){
////        CCSprite* gray = CCSprite::create("songshu3.png");
////        gray->setColor(ccGRAY);
//        ornamentItem = CCSprite::createWithSpriteFrameName("songshu3.png");
//        ornamentItem->setAnchorPoint(ccp(0.5,0.25));
//    }
//    
//    NormalState* wallState = NormalState::create(WorkStateTag, ornamentItem);
////    wallState->addTransition(UpdateTransition, WorkStateTag);
//    MyBuilding* ornament;
//    
//    TransitionInfo* infoItem =  TransitionInfo::create(InfoTransition,"remove.png",wallState,menu_selector(MyState::infoCallBack));
//    //    infoItem->setVisible(false);
////    infoItem->setPosition(ccp(56,160));
////    infoItem->setTag(InfoTransition);
//    wallState->addTransition(InfoTransition, WorkStateTag,infoItem);
//    
////    CCMenuItemSprite* sellitem =  CCMenuItemSprite::create(CCSprite::create("sell.png"),CCSprite::create("sell.png"),target,menu_selector(StartScene::collectCallBack));
////    
////    sellitem->setPosition(transWindowToGLInRetina(0,40));
////    sellitem->setTag(UpdateTransition);
////    sellitem->setVisible(false);
////  
//    if(tag / stoneBaseTag == 1) {
//        ornament = MyBuilding::create(tag,CCSizeMake(tag%stoneBaseTag+1,tag%stoneBaseTag+1),wallState,1,100);
//        ornament->setTag(songshuTag);
//        ornament->moveEnabled = false;
//        
//        ornament->setSummaryCount(2000);
//        ornament->resourceTag = ironTag;
//        ornament->setLevel(3+tag%stoneBaseTag*3);
//        //    name->setFontSize(transWindowToGLInRetina(1));
//    
//        ornament->setBuildingName(CCString::create("巨石"),ornamentItem->getContentSize().height*(1-ornamentItem->getAnchorPoint().y)+30);
//
////        CCLabelTTF* name = CCLabelTTF::create("巨石","Arial",22);
////        name->setColor(ccWHITE);
////        name->setPosition(ccp(0,ornamentItem->getContentSize().height*(1-ornamentItem->getAnchorPoint().y)+30));
////        name->setTag(nameFontTag);
////        name->setVisible(false);
////        
////        ornament->addChild(name,20);
//        
//        
//        
//    }else if(tag == songshuTag){
//        ornament = MyBuilding::create(songshuTag,CCSizeMake(2,2),wallState,1,100);
//        ornament->setTag(songshuTag);
//        ornament->moveEnabled = false;
//        ornament->setSummaryCount(5000);
//        ornament->setLevel(5);
//        ornament->resourceTag = oilTag;
//        ornament->setBuildingName(CCString::create("松树"),116);
//        
////        CCLabelTTF* name = CCLabelTTF::create("松树","Arial",22);
////        //    name->setFontSize(transWindowToGLInRetina(1));
////        
////        name->setColor(ccWHITE);
////        name->setPosition(ccp(0,116));
////        name->setTag(nameFontTag);
////        name->setVisible(false);
//    }
//    ornament->setTag(tag);
//    return ornament;
//}

//MyBattleBuilding* MyGameFactory::createBattleOrnaments(int tag, cocos2d::CCObject *target) {
//    CCSprite* ornamentItem;
//    
//    if(tag / stoneBaseTag == 1) {
//        char str[10] = {0};
//        sprintf(str, "stone%d.png",tag%stoneBaseTag);
//        ornamentItem = CCSprite::createWithSpriteFrameName(str);
//        ornamentItem->setAnchorPoint(ccp(0.45,0.45));
//        
//    }else if(tag == songshuTag){
//        //        CCSprite* gray = CCSprite::create("songshu3.png");
//        //        gray->setColor(ccGRAY);
//        ornamentItem = CCSprite::createWithSpriteFrameName("songshu3.png");
//        ornamentItem->setAnchorPoint(ccp(0.5,0.25));
//    }
//    
//    
//    BeAttackState* battleState = BeAttackState::create(WorkStateTag, ornamentItem, 100);
//    
//    
//    MyBattleBuilding* ornament;
//    
//    if(tag / stoneBaseTag == 1) {
////        ornament = MyBuilding::create(tag,CCSizeMake(tag%stoneBaseTag+1,tag%stoneBaseTag+1),wallState,1);
//        ornament = MyBattleBuilding::create(bingyingTag,CCSizeMake(tag%stoneBaseTag+1,tag%stoneBaseTag+1),battleState,3+tag%stoneBaseTag*3);
//        ornament->setTag(songshuTag);
////        ornament->setBuildingName(CCString::create("松树"),ornamentItem->getContentSize().height*(1-ornamentItem->getAnchorPoint().y)+30);
//        
////        CCLabelTTF* name = CCLabelTTF::create("巨石","Arial",22);
////        //    name->setFontSize(transWindowToGLInRetina(1));
////        
////        name->setColor(ccWHITE);
////        name->setPosition(ccp(0,ornamentItem->getContentSize().height*(1-ornamentItem->getAnchorPoint().y)+30));
////        name->setTag(nameFontTag);
////        name->setVisible(false);
//    
//        
//        
//    }else if(tag == songshuTag){
//        
//        ornament = MyBattleBuilding::create(bingyingTag,CCSizeMake(2,2),battleState,5);
//        
//        ornament->setTag(songshuTag);
//        ornament->setLevel(5);
////        ornament->setBuildingName(CCString::create("松树"),116);
//        
////        CCLabelTTF* name = CCLabelTTF::create("松树","Arial",22);
////        //    name->setFontSize(transWindowToGLInRetina(1));
////
////        name->setColor(ccWHITE);
////        name->setPosition(ccp(0,116));
////        name->setTag(nameFontTag);
////        name->setVisible(false);
//        
////        ornament->addChild(name,20);
//    }
//    ornament->setTag(tag);
//    ornament->AliveInterface::dispose();
//    
//   
//    return ornament;
//}

//MyBuildingCard* MyGameFactory::createCard(int tag, cocos2d::CCObject *target) {
//    MyBuildingCard* card = NULL;
//    if (tag == bingyingTag) {
////        CCSprite* sprite = CCSprite::createWithSpriteFrameName("by7.png");
////        sprite->setAnchorPoint(ccp(0.55,0.63));
////        sprite->setScale(0.8);
////        card = MyBuildingCard::create(sprite,tag,10,1,0,400,30,"兵  营", target,menu_selector(StartScene::toReadyCallback));
//    } else if (tag == wallTag) {
////        CCSprite* sprite = CCSprite::createWithSpriteFrameName("wall1lr.png");
////        sprite->setAnchorPoint(ccp(0.4,0.8));
////        card = MyBuildingCard::create(sprite,tag,10,1,40,0,30,"路  障", target,menu_selector(StartScene::toReadyCallback));
//    } else if (tag == dapaoTag) {
////        CCSprite* sprite = CCSprite::createWithSpriteFrameName("antiTankld.png");
//////        sprite->setAnchorPoint(ccp(0.5,0.4));
////        card = MyBuildingCard::create(sprite,tag,10,1,300,0,30,"反坦克炮", target,menu_selector(StartScene::toReadyCallback));
////        CCSprite* zhendi = CCSprite::createWithSpriteFrameName("position.png");
////        zhendi->setPosition(ccp(93,54));
////        sprite->addChild(zhendi,-1);
//    } else if (tag == diaobaoTag) {
////        CCSprite* sprite = CCSprite::createWithSpriteFrameName("diaobao.png");
////        sprite->setAnchorPoint(ccp(0.45,0.65));
////        card = MyBuildingCard::create(sprite,tag,10,1,200,0,30,"机枪碉堡", target,menu_selector(StartScene::toReadyCallback));
//    } else if (tag == youtianTag) {
////        CCSprite* sprite = CCSprite::createWithSpriteFrameName("yt2.png");
////        sprite->setScale(0.8);
////        sprite->setAnchorPoint(ccp(0.5,0.6));
////        card = MyBuildingCard::create(sprite,tag,10,1,400,0,30,"炼油厂", target,menu_selector(StartScene::toReadyCallback));
//    } else if (tag == kuangchangTag) {
////        CCSprite* sprite = CCSprite::createWithSpriteFrameName("kc.png");
////        sprite->setScale(0.8);
////        sprite->setAnchorPoint(ccp(0.5,0.6));
////        card = MyBuildingCard::create(sprite,tag,10,1,0,400,30,"炼钢厂", target,menu_selector(StartScene::toReadyCallback));
//    } else if (tag == zhihuisuoTag) {
////        card = MyBuildingCard::create(CCSprite::createWithSpriteFrameName("zhs1.png"),tag,10,1,100,100,30,"基  地", target,menu_selector(StartScene::toReadyCallback));
//    } else if (tag == lianluozhongxinTag) {
////        CCSprite* sprite = CCSprite::createWithSpriteFrameName("communication.png");
////        sprite->setScale(0.75);
////        sprite->setAnchorPoint(ccp(0.4,0.55));
////        card = MyBuildingCard::create(sprite,tag,10,1,500000,0,30,10,"联络中心", target,menu_selector(StartScene::toReadyCallback));
//    }
////    else if (tag == songshuTag) {
////        building = MyGameFactory::createBattleWall(target);
////    }
//    return card;
//}

CCArray* MyGameFactory::createAllCard(cocos2d::CCObject *target,int filter) {
    CCArray* array =CCArray::create();
    if (filter == 0 || filter == 1) {
        array->addObject(YouTian::createCard(target,menu_selector(StartScene::toReadyCallback)));
    }
    if (filter == 0 || filter == 1) {
        array->addObject(KuangChang::createCard(target,menu_selector(StartScene::toReadyCallback)));
    }
    if (filter == 0 || filter == 2) {
        array->addObject(DiaoBao::createCard(target,menu_selector(StartScene::toReadyCallback)));
    }
    if (filter == 0 || filter == 2) {
        array->addObject(DaPao::createCard(target,menu_selector(StartScene::toReadyCallback)));
    }
    if (filter == 0 || filter == 2) {
        array->addObject(Wall::createCard(target,menu_selector(StartScene::toReadyCallback)));
    }
    if (filter == 0 || filter == 1) {
        array->addObject(SuperYouTian::createCard(target,menu_selector(StartScene::toReadyCallback)));
    }
    
    if (filter == 0 || filter == 1) {
        array->addObject(SuperKuangChang::createCard(target,menu_selector(StartScene::toReadyCallback)));
    }
    if (filter == 0 || filter == 2) {
        array->addObject(LianLuoZhongXin::createCard(target,menu_selector(StartScene::toReadyCallback)));
    }
    if (filter == 0 || filter == 1) {
        array->addObject(GarbageCenter::createCard(target,menu_selector(StartScene::toReadyCallback)));
    }
    if (filter == 0 || filter == 1) {
        array->addObject(Cellar::createCard(target,menu_selector(StartScene::toReadyCallback)));
    }
    if (filter == 0 || filter == 2) {
        array->addObject(BingYing::createCard(target,menu_selector(StartScene::toReadyCallback)));
    }
    if (filter == 0 || filter == 2) {
        array->addObject(Jammer::createCard(target,menu_selector(StartScene::toReadyCallback)));
    }
//    array->addObject(createCard(zhihuisuoTag,target));
    return array;
}

void MyGameFactory::addState(MyBuilding *building, int stateTag,CCObject* target) {
    if (stateTag == UnfinishedStateTag) {
        UnfinishedState* unfinishedState = UnfinishedState::create(UnfinishedStateTag, "buildstruct", 1);
        
        
        TransitionInfo* buildItem =  TransitionInfo::create(BuildTransition,"build.png",unfinishedState,menu_selector(UnfinishedState::changeIdCallBack));
//        buildItem->setPosition(ccp(0,160));
//        buildItem->setTag(BuildTransition);
//        buildItem->setVisible(false);
        
        
//        MyMenuItem* sellitem = MyMenuItem::create(CCSprite::createWithSpriteFrameName("sell.png"),unfinishedState,menu_selector(NormalState::sellCallBack));
//        
//        sellitem->setPosition(ccp(56,160));
//        sellitem->setTag(sellTransition);
//        sellitem->setVisible(false);
        
        
        //未完成状态
        
//        unfinishedState->addTransition(sellTransition, DestroyStateTag,sellitem);
        unfinishedState->addTransition(BuildTransition, WorkStateTag,buildItem);
        building->addState(unfinishedState);
    }

}

GXCreator* MyGameFactory::createCreatorbyJsonScriptFile(const std::string& relativePath,int classtag) {
    CCObject* obj = creatorMap->objectForKey(relativePath);
    if (obj != NULL) {
        return (GXCreator*)obj;
    } else {
        CCString* str = GXUtil::readFile(relativePath);
       
        if (classtag == NewbieStartSceneClassTag) {
            NewbieStartSceneCreator* creator = NewbieStartSceneCreator::create(MyJsonUtil::parseBuildingFromJsonNoCompress(str));
            return  creator;
        }else if (classtag == NewbieBattleSceneClassTag) {
            NewbieBattleSceneCreator* creator = NewbieBattleSceneCreator::create(MyJsonUtil::parseBuildingFromJsonNoCompress(str));
            return  creator;
        } else if (classtag == NewbieMovieSceneClassTag ){
            NewbieMoveSceneCreator* creator = NewbieMoveSceneCreator::create(MyJsonUtil::parseBuildingFromJsonNoCompress(str));
            return  creator;
        } else if (classtag == unitCreatorClassTag) {
//            UnitCreator* creator = MyJsonUtil::parseUnitCreator(str);
//            creatorMap->setObject(creator, relativePath);
//            return creator;
        } else if (classtag == buildingCreatorClassTag) {
            BuildingCreator* creator = MyJsonUtil::parseBuildingCreator(str);
            creatorMap->setObject(creator, relativePath);
            return creator;
        }
        
    }
    
    
    
    return NULL;
}

//void MyGameFactory::setStateUpdateInfo(MyState *state, cocos2d::CCLayer *updateLayer) {
//    if(state->building->getTag() == wallTag) {
//        
//        float healthLevelData = MyUtil::getInstance()->updateLevelByRate(wallBaseHealth, state->building->getLevel(), 1);
//        float healthNextData = MyUtil::getInstance()->updateLevelByRate(wallBaseHealth, state->building->getLevel()+1, 1);
//        float healthMaxData = MyUtil::getInstance()->updateLevelByRate(wallBaseHealth, state->building->getMaxLevel(), 1);
//        
//        CCSprite* healthIcon = CCSprite::createWithSpriteFrameName("healthIcon.png");
//        healthIcon->setPosition(ccp(-64,98));
//        updateLayer->addChild(healthIcon);
//        CCLayer* bar = MyUtil::getInstance()->getUpdateBar(healthNextData/healthMaxData, healthLevelData/healthMaxData, "levelBarUp.png");
//        bar->setPosition(ccp(-40,80));
//        updateLayer->addChild(bar);
//        
//        char str[100] = {0};
//        if(state->building->getLevel() < state->building->getMaxLevel()) {
//            sprintf(str, "耐久度:%d+%d",(int)healthLevelData,(int)(healthNextData-healthLevelData));
//        } else {
//            sprintf(str, "耐久度:%d",(int)healthLevelData);
//        }
//        CCLabelTTF* healthLabel = CCLabelTTF::create(str, "Arial", 24);
//        healthLabel->setAnchorPoint(ccp(0,0));
//        healthLabel->setColor(ccc3(254, 218, 130));
//        healthLabel->setPosition(ccp(-40,90));
//
//        
//        CCLabelTTF* description = CCLabelTTF::create("    路障作为一种防御建筑虽然并不具有攻击力,\n但是可以有效的阻截敌军对建筑的直接攻击", "Arial", 26,CCSizeZero,kCCTextAlignmentLeft,kCCVerticalTextAlignmentTop);
//        description->setAnchorPoint(ccp(0,0.5));
//        description->setColor(ccc3(254, 218, 130));
//        description->setPosition(ccp(-280,-30));
//        
////        CCLabelTTF* mainUp = CCLabelTTF::create("主要升级属性:耐久度", "Arial", transWindowToGLInRetina(15));
////        mainUp->setColor(ccc3(114, 66, 45));
////        mainUp->setPosition(transWindowToGLInRetina(0,-40));
////        
////        CCSprite* underLine = CCSprite::createWithSpriteFrameName("underline.png");
////        underLine->setPosition(transWindowToGLInRetina(0,-50));
//        
//        CCLabelTTF* nameLabel = CCLabelTTF::create("路  障", "Arial", 24);
////        nameLabel->setColor(ccc3(114,66,45));
//        nameLabel->setAnchorPoint(ccp(0.5,0.5));
//        nameLabel->setPosition(ccp(-204,172));
//        
//        updateLayer->addChild(nameLabel);
//        updateLayer->addChild(healthLabel);
//        updateLayer->addChild(description);
////        updateLayer->addChild(mainUp);
////        updateLayer->addChild(underLine);
//    }
//    else if(state->building->getTag() == zhihuisuoTag) {
//        
//        float healthLevelData = MyUtil::getInstance()->updateLevelByRate(jdBaseHealth, state->building->getLevel(), 1);
//        float healthNextData = MyUtil::getInstance()->updateLevelByRate(jdBaseHealth, state->building->getLevel()+1, 1);
//        float healthMaxData = MyUtil::getInstance()->updateLevelByRate(jdBaseHealth, state->building->getMaxLevel(), 1);
//        
//        CCSprite* healthIcon = CCSprite::createWithSpriteFrameName("healthIcon.png");
//        healthIcon->setPosition(ccp(-68,134));
//        updateLayer->addChild(healthIcon);
//        CCLayer* healthBar = MyUtil::getInstance()->getUpdateBar(healthNextData/healthMaxData, healthLevelData/healthMaxData,"levelBarUp.png");
//        
//        healthBar->setPosition(ccp(-40,116));
//        updateLayer->addChild(healthBar);
//        
//        char str[100] = {0};
//        if(state->building->getLevel() < state->building->getMaxLevel()) {
//            sprintf(str, "耐久度:%d+%d",(int)healthLevelData,(int)(healthNextData - healthLevelData));
//        } else {
//            sprintf(str, "耐久度:%d",(int)healthLevelData);
//        }
//        CCLabelTTF* healthLabel = CCLabelTTF::create(str, "Arial", 24);
//        healthLabel->setAnchorPoint(ccp(0,0));
//        healthLabel->setColor(ccc3(254, 218, 130));
//        healthLabel->setPosition(ccp(-40,126));
//        
//        
//        CCLabelTTF* nameLabel = CCLabelTTF::create("基  地", "Arial", 24);
//        nameLabel->setColor(ccc3(254, 218, 130));
//        nameLabel->setAnchorPoint(ccp(0.5,0.5));
//        nameLabel->setPosition(ccp(-204,172));
//        updateLayer->addChild(nameLabel);
//        updateLayer->addChild(healthLabel);
//        
//        CCLabelTTF* description = CCLabelTTF::create("        基地作为通讯、指挥、物资的中心，是最\n重要的单位，通过基地，可以提供最大军令数\n量并且每隔一段时间恢复军令。在征战中，击\n破基地即获得胜利。                                        ", "Arial", 26);
//        description->setAnchorPoint(ccp(0,0.5));
//        description->setColor(ccc3(254, 218, 130));
//        description->setPosition(ccp(-280,-50));
//        updateLayer->addChild(description);
//    }
//    
//    else if(state->building->getTag() == youtianTag) {
//        
//        float healthLevelData = MyUtil::getInstance()->updateLevelByRate(ytBaseHealth, state->building->getLevel(), ytUpdateHealthRate);
//        float healthNextData = MyUtil::getInstance()->updateLevelByRate(ytBaseHealth, state->building->getLevel()+1, ytUpdateHealthRate);
//        float healthMaxData = MyUtil::getInstance()->updateLevelByRate(ytBaseHealth, state->building->getMaxLevel(), ytUpdateHealthRate);
//        
//        CCSprite* healthIcon = CCSprite::createWithSpriteFrameName("healthIcon.png");
//        healthIcon->setPosition(ccp(-68,160));
//        updateLayer->addChild(healthIcon);
//        CCLayer* healthBar = MyUtil::getInstance()->getUpdateBar(healthNextData/healthMaxData, healthLevelData/healthMaxData,"levelBarUp.png");
//        healthBar->setPosition(ccp(-40,142));
//        
//        
//        char str[100] = {0};
//        if(state->building->getLevel() < state->building->getMaxLevel()) {
//            sprintf(str, "耐久度:%d+%d",(int)healthLevelData,(int)(healthNextData-healthLevelData));
//        } else {
//            sprintf(str, "耐久度:%d",(int)healthLevelData);
//        }
//        CCLabelTTF* healthLabel = CCLabelTTF::create(str, "Arial", 24);
//        healthLabel->setAnchorPoint(ccp(0,0));
//        healthLabel->setColor(ccc3(254, 218, 130));
//        healthLabel->setPosition(ccp(-40,152));
//        updateLayer->addChild(healthBar);
//        updateLayer->addChild(healthLabel);
//        
//        
//        float capacityLevelData = MyUtil::getInstance()->updateLevelByRate(((CollectState*)state)->getBaseMaxCapacity(), state->building->getLevel(), ytUpdateColletMaxCapacityRate);
//        float capacityNextData = MyUtil::getInstance()->updateLevelByRate(((CollectState*)state)->getBaseMaxCapacity(), state->building->getLevel()+1, ytUpdateColletMaxCapacityRate);
//        float capacityMaxData = MyUtil::getInstance()->updateLevelByRate(((CollectState*)state)->getBaseMaxCapacity(), state->building->getMaxLevel(), ytUpdateColletMaxCapacityRate);
//        
//        CCSprite* capacityIcon = CCSprite::createWithSpriteFrameName("oilCapacity.png");
//        capacityIcon->setPosition(ccp(-68,106));
//        updateLayer->addChild(capacityIcon);
//        CCLayer* capacityBar = MyUtil::getInstance()->getUpdateBar(capacityNextData/capacityMaxData, capacityLevelData/capacityMaxData,"levelBarUp.png");
//      
//        capacityBar->setPosition(ccp(-40,88));
//        
//        if(state->building->getLevel() < state->building->getMaxLevel()) {
//            sprintf(str, "最大存储数量:%d+%d",(int)capacityLevelData,(int)(capacityNextData-capacityLevelData));
//        } else {
//            sprintf(str, "最大存储数量:%d",(int)capacityLevelData);
//        }
//        CCLabelTTF* capacityLabel = CCLabelTTF::create(str, "Arial", 24);
//        capacityLabel->setAnchorPoint(ccp(0,0));
//        capacityLabel->setColor(ccc3(254, 218, 130));
//        capacityLabel->setPosition(ccp(-40,98));
//        updateLayer->addChild(capacityBar);
//        updateLayer->addChild(capacityLabel);
//        
//        float speedLevelData = MyUtil::getInstance()->updateLevelByRate(((CollectState*)state)->getBaseOutputPsecond(), state->building->getLevel(), ytUpdateColletSpeedRate);
//        float speedNextData = MyUtil::getInstance()->updateLevelByRate(((CollectState*)state)->getBaseOutputPsecond(), state->building->getLevel()+1, ytUpdateColletSpeedRate);
//        float speedMaxData = MyUtil::getInstance()->updateLevelByRate(((CollectState*)state)->getBaseOutputPsecond(), state->building->getMaxLevel(), ytUpdateColletSpeedRate);
//        
//        CCSprite* speedIcon = CCSprite::createWithSpriteFrameName("OilcollectSpeedIcon.png");
//        speedIcon->setPosition(ccp(-68,48));
//        updateLayer->addChild(speedIcon);
//        
//        CCLayer* speedBar = MyUtil::getInstance()->getUpdateBar(speedNextData/speedMaxData, speedLevelData/speedMaxData,"levelBarUp.png");
//        
//        speedBar->setPosition(ccp(-40,30));
//        
//        if(state->building->getLevel() < state->building->getMaxLevel()) {
//            sprintf(str, "每小时采集数量:%d+%d",(int)(speedLevelData*3600),(int)((speedNextData-speedLevelData)*3600));
//        } else {
//            sprintf(str, "每小时采集数量:%d",(int)(speedLevelData*3600));
//        }
//        CCLabelTTF* speedLabel = CCLabelTTF::create(str, "Arial", 24);
//        speedLabel->setAnchorPoint(ccp(0,0));
//        speedLabel->setColor(ccc3(254, 218, 130));
//        speedLabel->setPosition(ccp(-40,40));
//        
//        
//        CCLabelTTF* nameLabel = CCLabelTTF::create("炼油厂", "Arial", 24);
//        nameLabel->setColor(ccc3(254, 218, 130));
//        nameLabel->setAnchorPoint(ccp(0.5,0.5));
//        nameLabel->setPosition(ccp(-204,172));
//        updateLayer->addChild(nameLabel);
//        updateLayer->addChild(speedBar);
//        updateLayer->addChild(speedLabel);
//    
//        CCLabelTTF* description = CCLabelTTF::create("        石油是重要的军需物资，关于征战的任何方\n面都离不开石油，升级油泵来提高石油产量！这\n就可以不断的征战，征战，征战！", "Arial",  26,CCSizeZero, kCCTextAlignmentLeft, kCCVerticalTextAlignmentTop);
//        description->setAnchorPoint(ccp(0,0.5));
//        description->setColor(ccc3(254, 218, 130));
//        description->setPosition(ccp(-280,-50));
//        updateLayer->addChild(description);
//    }
//    else if(state->building->getTag() == kuangchangTag) {
//        
//        float healthLevelData = MyUtil::getInstance()->updateLevelByRate(kcBaseHealth, state->building->getLevel(), kcUpdateHealthRate);
//        float healthNextData = MyUtil::getInstance()->updateLevelByRate(kcBaseHealth, state->building->getLevel()+1, kcUpdateHealthRate);
//        float healthMaxData = MyUtil::getInstance()->updateLevelByRate(kcBaseHealth, state->building->getMaxLevel(), kcUpdateHealthRate);
//        
//        CCSprite* healthIcon = CCSprite::createWithSpriteFrameName("healthIcon.png");
//        healthIcon->setPosition(ccp(-68,160));
//        updateLayer->addChild(healthIcon);
//        CCLayer* healthBar = MyUtil::getInstance()->getUpdateBar(healthNextData/healthMaxData, healthLevelData/healthMaxData,"levelBarUp.png");
//        healthBar->setPosition(ccp(-40,142));
//
//        
//        char str[100] = {0};
//        if (state->building->getLevel() < state->building->getMaxLevel()) {
//            sprintf(str, "耐久度:%d+%d",(int)healthLevelData,(int)(healthNextData-healthLevelData));
//        } else {
//            sprintf(str, "耐久度:%d",(int)healthLevelData);
//        }
//        
//        CCLabelTTF* healthLabel = CCLabelTTF::create(str, "Arial", 24);
//        healthLabel->setAnchorPoint(ccp(0,0));
//        healthLabel->setColor(ccc3(254, 218, 130));
//        healthLabel->setPosition(ccp(-40,152));
//        updateLayer->addChild(healthBar);
//        updateLayer->addChild(healthLabel);
//        
//        float capacityLevelData = MyUtil::getInstance()->updateLevelByRate(((CollectState*)state)->getBaseMaxCapacity(), state->building->getLevel(), kcUpdateColletMaxCapacityRate);
//        float capacityNextData = MyUtil::getInstance()->updateLevelByRate(((CollectState*)state)->getBaseMaxCapacity(), state->building->getLevel()+1, kcUpdateColletMaxCapacityRate);
//        float capacityMaxData = MyUtil::getInstance()->updateLevelByRate(((CollectState*)state)->getBaseMaxCapacity(), state->building->getMaxLevel(), kcUpdateColletMaxCapacityRate);
//        
//        CCSprite* capacityIcon = CCSprite::createWithSpriteFrameName("ironCapacity.png");
//        capacityIcon->setPosition(ccp(-68,106));
//        updateLayer->addChild(capacityIcon);
//        CCLayer* capacityBar = MyUtil::getInstance()->getUpdateBar(capacityNextData/capacityMaxData, capacityLevelData/capacityMaxData,"levelBarUp.png");
//        
//        capacityBar->setPosition(ccp(-40,88));
//       
//        
//        if (state->building->getLevel() < state->building->getMaxLevel()) {
//            sprintf(str, "最大存储数量:%d+%d",(int)capacityLevelData,(int)(capacityNextData-capacityLevelData));
//        } else {
//            sprintf(str, "最大存储数量:%d",(int)capacityLevelData);
//        }
//        
//        CCLabelTTF* capacityLabel = CCLabelTTF::create(str, "Arial", 24);
//        capacityLabel->setAnchorPoint(ccp(0,0));
//        capacityLabel->setColor(ccc3(254, 218, 130));
//        capacityLabel->setPosition(ccp(-40,98));
//        updateLayer->addChild(capacityBar);
//        updateLayer->addChild(capacityLabel);
//        
//        float speedLevelData = MyUtil::getInstance()->updateLevelByRate(((CollectState*)state)->getBaseOutputPsecond(), state->building->getLevel(), kcUpdateColletSpeedRate);
//        float speedNextData = MyUtil::getInstance()->updateLevelByRate(((CollectState*)state)->getBaseOutputPsecond(), state->building->getLevel()+1, kcUpdateColletSpeedRate);
//        float speedMaxData = MyUtil::getInstance()->updateLevelByRate(((CollectState*)state)->getBaseOutputPsecond(), state->building->getMaxLevel(), kcUpdateColletSpeedRate);
//        
//        CCSprite* speedIcon = CCSprite::createWithSpriteFrameName("ironCollectSpeedIcon.png");
//        speedIcon->setPosition(ccp(-68,48));
//        updateLayer->addChild(speedIcon);
//        CCLayer* speedBar = MyUtil::getInstance()->getUpdateBar(speedNextData/speedMaxData, speedLevelData/speedMaxData,"levelBarUp.png");
//        speedBar->setPosition(ccp(-40,30));
//        
//        if (state->building->getLevel() < state->building->getMaxLevel()) {
//            sprintf(str, "每小时采集数量:%d+%d",(int)(speedLevelData*3600),(int)((speedNextData-speedLevelData)*3600));
//        } else {
//            sprintf(str, "每小时采集数量:%d",(int)(speedLevelData*3600));
//        }
//        CCLabelTTF* speedLabel = CCLabelTTF::create(str, "Arial", 24);
//        speedLabel->setAnchorPoint(ccp(0,0));
//        speedLabel->setColor(ccc3(254, 218, 130));
//        speedLabel->setPosition(ccp(-40,40));
//        
//        
//        CCLabelTTF* nameLabel = CCLabelTTF::create("炼钢厂", "Arial", 24);
//        nameLabel->setColor(ccc3(254, 218, 130));
//        nameLabel->setAnchorPoint(ccp(0.5,0.5));
//        nameLabel->setPosition(ccp(-204,172));
//        updateLayer->addChild(nameLabel);
//        updateLayer->addChild(speedBar);
//        updateLayer->addChild(speedLabel);
//        
//        CCLabelTTF* description = CCLabelTTF::create("        钢铁是重要的建造物资，关于建造的任何方\n面都离不开钢铁，升级钢炉来提高钢铁产量！让\n侵略者在你的钢铁要塞面前颤抖吧！", "Arial",  26,CCSizeZero, kCCTextAlignmentLeft, kCCVerticalTextAlignmentTop);
//        description->setAnchorPoint(ccp(0,0.5));
//        description->setColor(ccc3(254, 218, 130));
//        description->setPosition(ccp(-280,-50));
//        updateLayer->addChild(description);
//    
//    }
//    else if(state->building->getTag() == bingyingTag) {
//        
//        float healthLevelData = MyUtil::getInstance()->updateLevelByRate(byBaseHealth, state->building->getLevel(), 1);
//        float healthNextData = MyUtil::getInstance()->updateLevelByRate(byBaseHealth, state->building->getLevel()+1, 1);
//        float healthMaxData = MyUtil::getInstance()->updateLevelByRate(byBaseHealth, state->building->getMaxLevel(), 1);
//        
//        CCSprite* healthIcon = CCSprite::createWithSpriteFrameName("healthIcon.png");
//        healthIcon->setPosition(ccp(-68,134));
//        updateLayer->addChild(healthIcon);
//        
//        CCLayer* healthBar = MyUtil::getInstance()->getUpdateBar(healthNextData/healthMaxData, healthLevelData/healthMaxData,"levelBarUp.png");
//        healthBar->setPosition(ccp(-40,116));
//        
//        char str[100] = {0};
//        if(state->building->getLevel() < state->building->getMaxLevel()) {
//            sprintf(str, "耐久度:%d+%d",(int)healthLevelData,(int)(healthNextData-healthLevelData));
//        } else {
//            sprintf(str, "耐久度:%d",(int)healthLevelData);
//        }
//        CCLabelTTF* healthLabel = CCLabelTTF::create(str, "Arial", 24);
//        healthLabel->setAnchorPoint(ccp(0,0));
//        healthLabel->setColor(ccc3(254, 218, 130));
//        healthLabel->setPosition(ccp(-40,126));
//        
//        
//        CCLabelTTF* nameLabel = CCLabelTTF::create("兵  营", "Arial", 24);
//        nameLabel->setColor(ccc3(254, 218, 130));
//        nameLabel->setAnchorPoint(ccp(0.5,0.5));
//        nameLabel->setPosition(ccp(-204,172));
//        updateLayer->addChild(nameLabel);
//        updateLayer->addChild(healthBar);
//        updateLayer->addChild(healthLabel);
//        
//        CCLabelTTF* description = CCLabelTTF::create("        升级兵营来增加空间，让更多的部队安顿下\n来。兵营可以增加部队的驻扎上限。不断寻找落\n单的部队，组建出一支最强的二战队伍吧！", "Arial",  26,CCSizeZero, kCCTextAlignmentLeft, kCCVerticalTextAlignmentTop);
//        description->setAnchorPoint(ccp(0,0.5));
//        description->setColor(ccc3(254, 218, 130));
//        description->setPosition(ccp(-280,-50));
//        updateLayer->addChild(description);
//    }
//    else if(state->building->getTag() == dapaoTag) {
//        
//        float attackLevelData = MyUtil::getInstance()->updateLevelByRate(dpBaseDamage, state->building->getLevel(), dpUpdateDamageRate);
//        float attackNextData = MyUtil::getInstance()->updateLevelByRate(dpBaseDamage, state->building->getLevel()+1, dpUpdateDamageRate);
//        float attackMaxData = MyUtil::getInstance()->updateLevelByRate(dpBaseDamage, state->building->getMaxLevel(), dpUpdateDamageRate);
//        
//        CCSprite* attackIcon = CCSprite::createWithSpriteFrameName("damageIcon.png");
//        attackIcon->setPosition(ccp(-68,134));
//        updateLayer->addChild(attackIcon);
//        
//        CCLayer* attackBar = MyUtil::getInstance()->getUpdateBar(attackNextData/attackMaxData, attackLevelData/attackMaxData,"levelBarUp.png");
//        attackBar->setPosition(ccp(-40,116));
//        
//        
//        char str[100] = {0};
//        if (state->building->getLevel() <state->building->getMaxLevel()) {
//            sprintf(str, "每秒造成伤害:%d+%d",(int)(attackLevelData),(int)(attackNextData-attackLevelData));
//        } else {
//            sprintf(str, "每秒造成伤害:%d",(int)(attackLevelData));
//        }
//        
//        CCLabelTTF* damageLabel = CCLabelTTF::create(str, "Arial", 24);
//        damageLabel->setAnchorPoint(ccp(0,0));
//        damageLabel->setColor(ccc3(254, 218, 130));
//        damageLabel->setPosition(ccp(-40,126));
//        updateLayer->addChild(attackBar);
//        updateLayer->addChild(damageLabel);
//        
//        float rangeLevelData = MyUtil::getInstance()->updateLevelByCount(dpBaseRange, state->building->getLevel(), dpUpdateRangeCount);
//        float rangeNextData = MyUtil::getInstance()->updateLevelByCount(dpBaseRange, state->building->getLevel()+1, dpUpdateRangeCount);
//        float rangeMaxData = MyUtil::getInstance()->updateLevelByCount(dpBaseRange, state->building->getMaxLevel(), dpUpdateRangeCount);
//        
//        
//        CCSprite* rangeIcon = CCSprite::createWithSpriteFrameName("attackRangeIcon.png");
//        rangeIcon->setPosition(ccp(-68,80));
//        updateLayer->addChild(rangeIcon);
//        
//        CCLayer* rangeBar = MyUtil::getInstance()->getUpdateBar(rangeNextData/rangeMaxData, rangeLevelData/rangeMaxData,"levelBarUp.png");
//        
//        rangeBar->setPosition(ccp(-40,62));
//        
//        if (state->building->getLevel() < state->building->getMaxLevel()) {
//            sprintf(str, "攻击范围:%d格+0.5格",(int)(rangeLevelData));
//        } else {
//            sprintf(str, "攻击范围:%d格",(int)(rangeLevelData));
//        }
//        
//        CCLabelTTF* rangeLabel = CCLabelTTF::create(str, "Arial", 24);
//        rangeLabel->setAnchorPoint(ccp(0,0));
//        rangeLabel->setColor(ccc3(254, 218, 130));
//        rangeLabel->setPosition(ccp(-40,72));
//        updateLayer->addChild(rangeBar);
//        updateLayer->addChild(rangeLabel);
//        
//        CCLabelTTF* nameLabel = CCLabelTTF::create("反坦克炮", "Arial", 24);
//        nameLabel->setColor(ccc3(254, 218, 130));
//        nameLabel->setAnchorPoint(ccp(0.5,0.5));
//        nameLabel->setPosition(ccp(-204,172));
//        updateLayer->addChild(nameLabel);
//        
////        updateLayer->addChild(rangeLabel);
//        sprintf(str, "耐久度:%d",dpBaseHealth);
//        CCLabelTTF* description1 = CCLabelTTF::create(str, "Arial",  26);
//        description1->setAnchorPoint(ccp(0,0.5));
//        description1->setColor(ccc3(254, 218, 130));
//        description1->setPosition(ccp(-110,-6));
//        updateLayer->addChild(description1);
//        
//        CCSprite* underline1 = CCSprite::createWithSpriteFrameName("underline.png");
//        underline1->setPosition(ccp(0,-22));
//        updateLayer->addChild(underline1);
//        
//        
//        sprintf(str, "攻击溅射范围:%d格",dpBaseSplash);
//        CCLabelTTF* description2 = CCLabelTTF::create(str, "Arial",  26);
//        description2->setAnchorPoint(ccp(0,0.5));
//        description2->setColor(ccc3(254, 218, 130));
//        description2->setPosition(ccp(-110,-42));
//        updateLayer->addChild(description2);
//        
//        CCSprite* underline2 = CCSprite::createWithSpriteFrameName("underline.png");
//        underline2->setPosition(ccp(0,-58));
//        updateLayer->addChild(underline2);
//        
//        
//        CCLabelTTF* description3 = CCLabelTTF::create("目标部队:地面", "Arial",  26);
//        description3->setAnchorPoint(ccp(0,0.5));
//        description3->setColor(ccc3(254, 218, 130));
//        description3->setPosition(ccp(-110,-78));
//        updateLayer->addChild(description3);
//        
//        CCSprite* underline3 = CCSprite::createWithSpriteFrameName("underline.png");
//        underline3->setPosition(ccp(0,-94));
//        updateLayer->addChild(underline3);
//        
//    }
//    else if(state->building->getTag() == diaobaoTag) {
//        
//        float attackLevelData = MyUtil::getInstance()->updateLevelByRate(dbBaseDamage, state->building->getLevel(), dbUpdateDamageRate);
//        float attackNextData = MyUtil::getInstance()->updateLevelByRate(dbBaseDamage, state->building->getLevel()+1, dbUpdateDamageRate);
//        float attackMaxData = MyUtil::getInstance()->updateLevelByRate(dbBaseDamage, state->building->getMaxLevel(), dbUpdateDamageRate);
//        CCSprite* attackIcon = CCSprite::createWithSpriteFrameName("damageIcon.png");
//        attackIcon->setPosition(ccp(-68,134));
//        updateLayer->addChild(attackIcon);
//        
//        CCLayer* attackBar = MyUtil::getInstance()->getUpdateBar(attackNextData/attackMaxData, attackLevelData/attackMaxData,"levelBarUp.png");
//        attackBar->setPosition(ccp(-40,116));
//        
//        char str[100] = {0};
//        if(state->building->getLevel() < state->building->getMaxLevel()) {
//            sprintf(str, "每秒造成伤害:%d+%d",(int)(attackLevelData),(int)(attackNextData - attackLevelData));
//        } else {
//            sprintf(str, "每秒造成伤害:%d",(int)(attackLevelData));
//        }
//        CCLabelTTF* damageLabel = CCLabelTTF::create(str, "Arial", 24);
//        damageLabel->setAnchorPoint(ccp(0,0));
//        damageLabel->setColor(ccc3(254, 218, 130));
//        damageLabel->setPosition(ccp(-40,126));
//        updateLayer->addChild(attackBar);
//        updateLayer->addChild(damageLabel);
//        
//        float healthLevelData = MyUtil::getInstance()->updateLevelByRate(dbBaseHealth, state->building->getLevel(), dbUpdateHealthRate);
//        float healthNextData = MyUtil::getInstance()->updateLevelByRate(dbBaseHealth, state->building->getLevel()+1, dbUpdateHealthRate);
//        float healthMaxData = MyUtil::getInstance()->updateLevelByRate(dbBaseHealth, state->building->getMaxLevel(), dbUpdateHealthRate);
//        
//        CCSprite* healthIcon = CCSprite::createWithSpriteFrameName("healthIcon.png");
//        healthIcon->setPosition(ccp(-68,80));
//        updateLayer->addChild(healthIcon);
//        
//        CCLayer* healthBar = MyUtil::getInstance()->getUpdateBar(healthNextData/healthMaxData, healthLevelData/healthMaxData,"levelBarUp.png");
//        
//        healthBar->setPosition(ccp(-40,62));
//        
//        
//        if(state->building->getLevel() < state->building->getMaxLevel()) {
//            sprintf(str, "耐久度:%d+%d",(int)healthLevelData,(int)(healthNextData-healthLevelData));
//        } else {
//            sprintf(str, "耐久度:%d",(int)healthLevelData);
//        }
//        CCLabelTTF* healthLabel = CCLabelTTF::create(str, "Arial", 24);
//        healthLabel->setAnchorPoint(ccp(0,0));
//        healthLabel->setColor(ccc3(254, 218, 130));
//        healthLabel->setPosition(ccp(-40,72));
//        updateLayer->addChild(healthBar);
//        updateLayer->addChild(healthLabel);
//        
//        CCLabelTTF* nameLabel = CCLabelTTF::create("机枪碉堡", "Arial", 24);
//        nameLabel->setColor(ccc3(254, 218, 130));
//        nameLabel->setAnchorPoint(ccp(0.5,0.5));
//        nameLabel->setPosition(ccp(-204,172));
//        updateLayer->addChild(nameLabel);
//        
//        //        updateLayer->addChild(rangeLabel);
//        sprintf(str, "攻击范围:%d格",dbBaseRange);
//        CCLabelTTF* description1 = CCLabelTTF::create(str, "Arial",  26);
//        description1->setAnchorPoint(ccp(0,0.5));
//        description1->setColor(ccc3(254, 218, 130));
//        description1->setPosition(ccp(-80,-16));
//        updateLayer->addChild(description1);
//        
//        CCSprite* underline1 = CCSprite::createWithSpriteFrameName("underline.png");
//        underline1->setPosition(ccp(0,-32));
//        updateLayer->addChild(underline1);
//        
//        
////        sprintf(str, "攻击溅射范围:%d格",1);
////        CCLabelTTF* description2 = CCLabelTTF::create(str, "Arial",  transWindowToGLInRetina(13));
////        description2->setAnchorPoint(ccp(0,0.5));
////        description2->setColor(ccc3(114, 66, 45));
////        description2->setPosition(transWindowToGLInRetina(-55,-21));
////        updateLayer->addChild(description2);
////        
////        CCSprite* underline2 = CCSprite::createWithSpriteFrameName("underline.png");
////        underline2->setPosition(transWindowToGLInRetina(0,-29));
////        updateLayer->addChild(underline2);
//        
//        
//        CCLabelTTF* description3 = CCLabelTTF::create("目标部队:地面", "Arial",  26);
//        description3->setAnchorPoint(ccp(0,0.5));
//        description3->setColor(ccc3(254, 218, 130));
//        description3->setPosition(ccp(-80,-58));
//        updateLayer->addChild(description3);
//        
//        CCSprite* underline3 = CCSprite::createWithSpriteFrameName("underline.png");
//        underline3->setPosition(ccp(0,-74));
//        updateLayer->addChild(underline3);
//    } else if(state->building->getTag() == combineWall5X1Tag || state->building->getTag() == combineWall1X5Tag) {
//        
//        float healthLevelData = MyUtil::getInstance()->updateLevelByRate(combineWallBaseHealth, state->building->getLevel(), 1);
//        float healthNextData = MyUtil::getInstance()->updateLevelByRate(combineWallBaseHealth, state->building->getLevel()+1, 1);
//        float healthMaxData = MyUtil::getInstance()->updateLevelByRate(combineWallBaseHealth, state->building->getMaxLevel(), 1);
//        
//        CCSprite* healthIcon = CCSprite::createWithSpriteFrameName("healthIcon.png");
//        healthIcon->setPosition(ccp(-64,98));
//        updateLayer->addChild(healthIcon);
//        CCLayer* bar = MyUtil::getInstance()->getUpdateBar(healthNextData/healthMaxData, healthLevelData/healthMaxData, "levelBarUp.png");
//        bar->setPosition(ccp(-40,80));
//        updateLayer->addChild(bar);
//        
//        char str[100] = {0};
//        if(state->building->getLevel() < state->building->getMaxLevel()) {
//            sprintf(str, "耐久度:%d+%d",(int)healthLevelData,(int)(healthNextData-healthLevelData));
//        } else {
//            sprintf(str, "耐久度:%d",(int)healthLevelData);
//        }
//        CCLabelTTF* healthLabel = CCLabelTTF::create(str, "Arial", 24);
//        healthLabel->setAnchorPoint(ccp(0,0));
//        healthLabel->setColor(ccc3(254, 218, 130));
//        healthLabel->setPosition(ccp(-40,90));
//        
//        
//        CCLabelTTF* description = CCLabelTTF::create("    强化路障是由5块路障组合而成，但是拥有更高\n的耐久度，灵活的摆放往往会成为阻击敌人的\n利器。", "Arial", 26,CCSizeZero,kCCTextAlignmentLeft,kCCVerticalTextAlignmentTop);
//        description->setAnchorPoint(ccp(0,0.5));
//        description->setColor(ccc3(254, 218, 130));
//        description->setPosition(ccp(-280,-30));
//        
//        //        CCLabelTTF* mainUp = CCLabelTTF::create("主要升级属性:耐久度", "Arial", transWindowToGLInRetina(15));
//        //        mainUp->setColor(ccc3(114, 66, 45));
//        //        mainUp->setPosition(transWindowToGLInRetina(0,-40));
//        //
//        //        CCSprite* underLine = CCSprite::createWithSpriteFrameName("underline.png");
//        //        underLine->setPosition(transWindowToGLInRetina(0,-50));
//        
//        CCLabelTTF* nameLabel = CCLabelTTF::create("强化路障", "Arial", 24);
//        //        nameLabel->setColor(ccc3(114,66,45));
//        nameLabel->setAnchorPoint(ccp(0.5,0.5));
//        nameLabel->setPosition(ccp(-204,172));
//        
//        updateLayer->addChild(nameLabel);
//        updateLayer->addChild(healthLabel);
//        updateLayer->addChild(description);
//        //        updateLayer->addChild(mainUp);
//        //        updateLayer->addChild(underLine);
//    }
//}

//void MyGameFactory::setLevel(int level, int tag,GXFSM* fsm ) {
//    CCLog("tag:%d",building->getTag());
//    if(tag == wallTag) {
//        BeAttackState* beAttack = dynamic_cast<BeAttackState*>(fsm->getState(BeAttackStateTag));
//        if(beAttack != NULL) {
//            beAttack->setMaxLife(MyUtil::getInstance()->updateLevelByRate(wallBaseHealth, level, 1));
//            beAttack->setLife(MyUtil::getInstance()->updateLevelByRate(wallBaseHealth, level, 1));
//        }
//    }
//    else if(tag == combineWall1X5Tag || tag == combineWall5X1Tag) {
//        BeAttackState* beAttack = dynamic_cast<BeAttackState*>(fsm->getState(BeAttackStateTag));
//        if(beAttack != NULL) {
//            beAttack->setMaxLife(MyUtil::getInstance()->updateLevelByRate(combineWallBaseHealth, level, 1));
//            beAttack->setLife(MyUtil::getInstance()->updateLevelByRate(combineWallBaseHealth, level, 1));
//        }
//    }
//    else if(tag == zhihuisuoTag) {
//        BeAttackState* beAttack = dynamic_cast<BeAttackState*>(fsm->getState(BeAttackStateTag));
//        if(beAttack != NULL) {
//            beAttack->setMaxLife(MyUtil::getInstance()->updateLevelByRate(jdBaseHealth, level, 1));
//            beAttack->setLife(MyUtil::getInstance()->updateLevelByRate(jdBaseHealth, level, 1));
//        }
//    }
//    else if(tag == youtianTag) {
//        ResourceBeAttackState* beAttack = dynamic_cast<ResourceBeAttackState*>(fsm->getState(BeAttackStateTag));
//        if(beAttack != NULL) {
//            beAttack->setMaxCapacity(MyUtil::getInstance()->updateLevelByRate(beAttack->getBaseMaxCapacity(), level, ytUpdateColletMaxCapacityRate));
//            beAttack->setOutputPsecond(MyUtil::getInstance()->updateLevelByRate(beAttack->getBaseOutputPsecond(), level, ytUpdateColletSpeedRate));
//            float life = MyUtil::getInstance()->updateLevelByRate(ytBaseHealth, level, ytUpdateHealthRate);
//            beAttack->setMaxLife(life);
//            beAttack->setLife(life);
//        }
//        CollectState* collectState = dynamic_cast<CollectState*>(fsm->getState(WorkStateTag));
//        if (collectState != NULL) {
//            collectState->setMaxCapacity(MyUtil::getInstance()->updateLevelByRate(collectState->getBaseMaxCapacity(), level, ytUpdateColletMaxCapacityRate));
//            collectState->setOutputPsecond(MyUtil::getInstance()->updateLevelByRate(collectState->getBaseOutputPsecond(), level, ytUpdateColletSpeedRate));
//        }
//    }
//    else if(tag == kuangchangTag) {
//        ResourceBeAttackState* beAttack = dynamic_cast<ResourceBeAttackState*>(fsm->getState(BeAttackStateTag));
//        if(beAttack != NULL) {
//            beAttack->setMaxCapacity(MyUtil::getInstance()->updateLevelByRate(beAttack->getBaseMaxCapacity(), level, kcUpdateColletMaxCapacityRate));
//            beAttack->setOutputPsecond(MyUtil::getInstance()->updateLevelByRate(beAttack->getBaseOutputPsecond(), level, kcUpdateColletSpeedRate));
//            float life =MyUtil::getInstance()->updateLevelByRate(kcBaseHealth, level, kcUpdateHealthRate);
//            beAttack->setMaxLife(life);
//            beAttack->setLife(life);
//        }
//        CollectState* collectState = dynamic_cast<CollectState*>(fsm->getState(WorkStateTag));
//        if (collectState != NULL) {
//            collectState->setMaxCapacity(MyUtil::getInstance()->updateLevelByRate(collectState->getBaseMaxCapacity(), level, kcUpdateColletMaxCapacityRate));
//            collectState->setOutputPsecond(MyUtil::getInstance()->updateLevelByRate(collectState->getBaseOutputPsecond(), level, kcUpdateColletSpeedRate));
//        }
//        
//    }
//    else if(tag == bingyingTag) {
//        BeAttackState* beAttack = dynamic_cast<BeAttackState*>(fsm->getState(BeAttackStateTag));
//        if(beAttack != NULL) {
//            float life = MyUtil::getInstance()->updateLevelByRate(byBaseHealth, level, 1);
//            beAttack->setMaxLife(life);
//            beAttack->setLife(life);
//        }
//    }
//    else if(tag == dapaoTag) {
//        AoeDefendState* defendstate = dynamic_cast<AoeDefendState*>(fsm->getState(DefendStateTag));
//        if(defendstate != NULL) {
//            defendstate->damage = MyUtil::getInstance()->updateLevelByRate(dpBaseDamage, level, dpUpdateDamageRate);
//            defendstate->attackRange = MyUtil::getInstance()->updateLevelByCount(dpBaseRange, level, dpUpdateRangeCount);
////            CCLog("level:%d,range:%f",building->getLevel(),defendstate->attackRange);
//        }
//        
//    }
//    else if(tag == diaobaoTag) {
//        DefendState* defendstate = dynamic_cast<DefendState*>(fsm->getState(DefendStateTag));
//        if (defendstate != NULL) {
//            float life = MyUtil::getInstance()->updateLevelByRate(dbBaseHealth, level, dbUpdateHealthRate);
//            defendstate->setMaxLife(life);
//            defendstate->setLife(life);
//            defendstate->damage = MyUtil::getInstance()->updateLevelByRate(dbBaseDamage, level, dbUpdateDamageRate);
//        }
//        
//    }
//}

//CCLayer* MyGameFactory::getUpdateBar(float per1, float per2,const char* upName) {
//    GXProgressBar* barAdd = GXProgressBar::create(CCSprite::create(upName), CCSprite::create("BarDown.png"));
//    
//    barAdd->setContentSize(CCSizeMake(316,14));
//    barAdd->updatePercentage(per1);
//    CCTintTo* tintBy = CCTintTo::create(1, 0,255,0);
//    //    healthBarAdd->getUpSprite()->setColor(ccGRAY);
//    barAdd->getUpSprite()->runAction(CCRepeatForever::create(static_cast<CCSequence*>(CCSequence::create(tintBy,CCTintTo::create(1, 255,255,255),NULL))));
//    
//    CCSprite* bar = CCSprite::create(upName);
//    bar->setScaleX((316*per2)/bar->getContentSize().width);
//    bar->setScaleY(14/bar->getContentSize().height);
//    
//    bar->setAnchorPoint(ccp(0,0));
//    bar->setColor(ccc3(220,220,220));
//    barAdd->addChild(bar);
//    return barAdd;
//}

//CCLayer* MyGameFactory::getUnitCardDescriptTag(CreatorInfoBean* bean,bool isAll) {
//    CCLayer* layer = CCLayer::create();
    
//    CCLog("damageRate:%f",bean->creator->updateDamageRate);
    
//    float attackLevelData = MyUtil::getInstance()->updateLevelByRate(0,bean->creator->getDamage(), bean->getLevel(), bean->creator->updateDamageRate);
//    float attackMaxData = MyUtil::getInstance()->updateLevelByRate(0,bean->creator->getDamage(), bean->creator->getMaxLevel(), bean->creator->updateDamageRate);
//    CCSprite* attackIcon = CCSprite::createWithSpriteFrameName("damageIcon.png");
//    attackIcon->setPosition(ccp(40,360));
//    layer->addChild(attackIcon);
//    attackIcon->setScale(1.3);
//    GXProgressBar* attackBar = GXProgressBar::create(CCSprite::create("levelBarUp.png"), CCSprite::create("BarDown.png"));
//    
//    attackBar->setContentSize(CCSizeMake(416,20));
//    attackBar->updatePercentage((attackLevelData+bean->creator->getDamage()*bean->creator->getMaxLevel())/(attackMaxData+bean->creator->getDamage()*bean->creator->getMaxLevel()));
//    attackBar->setPosition(ccp(70,337));
//    
//    
//    char str[100] = {0};
//    sprintf(str, "每秒造成伤害:%d",(int)(attackLevelData));
//    
//    CCLabelTTF* attackLabel = CCLabelTTF::create(str, "Arial", 28);
//    attackLabel->setAnchorPoint(ccp(0,0));
//    attackLabel->setColor(ccc3(238,204,122));
//    attackLabel->setPosition(ccp(70,352));
//    layer->addChild(attackBar);
//    layer->addChild(attackLabel);
//    
////    CCLog("damageRate:%f",attackLevelData/attackMaxData);
//    
//    float speedLevelData = MyUtil::getInstance()->updateLevelByCount(bean->creator->getSpeed(), bean->getLevel(), bean->creator->updateSpeedRate);
//    
//    float speedMaxData = MyUtil::getInstance()->updateLevelByCount(bean->creator->getSpeed(), bean->creator->getMaxLevel(), bean->creator->updateSpeedRate);
//    
//    CCSprite* speedIcon = CCSprite::createWithSpriteFrameName("speedIcon.png");
//    speedIcon->setScale(1.3);
//    speedIcon->setPosition(ccp(40,300));
//    layer->addChild(speedIcon);
//    GXProgressBar* speedBar = GXProgressBar::create(CCSprite::create("levelBarUp.png"), CCSprite::create("BarDown.png"));
//    
//    speedBar->setContentSize(CCSizeMake(416,20));
//    speedBar->updatePercentage(speedLevelData/speedMaxData);
//    speedBar->setPosition(ccp(70,277));
//    
//    sprintf(str, "移动速度:%d",(int)(speedLevelData*10));
//    
//    CCLabelTTF* speedLabel = CCLabelTTF::create(str, "Arial", 24);
//    speedLabel->setAnchorPoint(ccp(0,0));
//    speedLabel->setColor(ccc3(238,204,122));
//    speedLabel->setPosition(ccp(70,292));
//    layer->addChild(speedBar);
//    layer->addChild(speedLabel);
//    
////    CCLog("speedRate:%f",speedLevelData/speedMaxData);
//    
//    float healthLevelData = MyUtil::getInstance()->updateLevelByRate(0,bean->creator->getLife(), bean->getLevel(), bean->creator->updateHealthRate);
//    float healthMaxData = MyUtil::getInstance()->updateLevelByRate(0,bean->creator->getLife(), bean->creator->getMaxLevel(), bean->creator->updateHealthRate);
//    
//    
//    CCSprite* healthIcon = CCSprite::createWithSpriteFrameName("healthIcon.png");
//    healthIcon->setScale(1.3);
//    healthIcon->setPosition(ccp(40,240));
//    layer->addChild(healthIcon);
//    GXProgressBar* healthBar = GXProgressBar::create(CCSprite::create("levelBarUp.png"), CCSprite::create("BarDown.png"));
//    
//    healthBar->setContentSize(CCSizeMake(416,20));
//    healthBar->updatePercentage((healthLevelData+bean->creator->getLife()*bean->creator->getMaxLevel())/(healthMaxData+bean->creator->getLife()*bean->creator->getMaxLevel()));
//    
//    healthBar->setPosition(ccp(70,217));
//
//    sprintf(str, "耐久度:%d",(int)healthLevelData);
//    
//    CCLabelTTF* healthLabel = CCLabelTTF::create(str, "Arial", 24);
//    healthLabel->setAnchorPoint(ccp(0,0));
//    healthLabel->setColor(ccc3(238,204,122));
//    healthLabel->setPosition(ccp(70,232));
//    layer->addChild(healthBar);
//    layer->addChild(healthLabel);
//    
////    CCLog("lifeRate:%f",healthLevelData/healthMaxData);
//    
//    float costLevelData = MyUtil::getInstance()->updateLevelByRate(0,bean->creator->getSummaryOil(), bean->getLevel(), bean->creator->updateCostRate);
//    float costMaxData = MyUtil::getInstance()->updateLevelByRate(0,bean->creator->getSummaryOil(), bean->creator->getMaxLevel(), bean->creator->updateCostRate);
//    
//    CCSprite* costIcon = CCSprite::createWithSpriteFrameName("oilIcon.png");
//    costIcon->setScale(1.3);
//    costIcon->setPosition(ccp(40,180));
//    costIcon->setScale(24/costIcon->getContentSize().width);
//    layer->addChild(costIcon);
//    
//    
//    GXProgressBar* costBar = GXProgressBar::create(CCSprite::create("levelBarUp.png"), CCSprite::create("BarDown.png"));
//    
//    costBar->setContentSize(CCSizeMake(416,20));
//    costBar->updatePercentage((costLevelData+bean->creator->getSummaryOil()*bean->creator->getMaxLevel())/(costMaxData+bean->creator->getSummaryOil()*bean->creator->getMaxLevel()));
//    
//    costBar->setPosition(ccp(70,157));
//    
//   
//    sprintf(str, "派遣使用油料:%d",(int)(costLevelData));
//    CCLabelTTF* costLabel = CCLabelTTF::create(str, "Arial", 24);
//    costLabel->setAnchorPoint(ccp(0,0));
//    costLabel->setColor(ccc3(238,204,122));
//    costLabel->setPosition(ccp(70,172));
//    layer->addChild(costBar);
//    layer->addChild(costLabel);
//    
//    if (!isAll) {
//        return layer;
//    }
//
//    
//    sprintf(str, "最大等级:%d",(int)bean->creator->getMaxLevel());
//    CCLabelTTF* description1 = CCLabelTTF::create(str, "Arial",  26);
//    description1->setAnchorPoint(ccp(0.5,0.5));
//    description1->setColor(ccc3(238,204,122));
//    description1->setPosition(ccp(260,110));
//    layer->addChild(description1);
//    
//    CCSprite* underline1 = CCSprite::createWithSpriteFrameName("underline.png");
//    underline1->setPosition(ccp(260,95));
//    layer->addChild(underline1);
//    
//    
//    sprintf(str, "攻击距离:%d格",(int)bean->creator->getAttackRange());
//    CCLabelTTF* description2 = CCLabelTTF::create(str, "Arial",  26);
//    description2->setAnchorPoint(ccp(0.5,0.5));
//    description2->setColor(ccc3(238,204,122));
//    description2->setPosition(ccp(260,70));
//    layer->addChild(description2);
//    
//    CCSprite* underline2 = CCSprite::createWithSpriteFrameName("underline.png");
//    underline2->setPosition(ccp(260,55));
//    layer->addChild(underline2);
//    
//    
//    CCLabelTTF* description3 = CCLabelTTF::create("主要目标:任意目标", "Arial",  26);
//    description3->setAnchorPoint(ccp(0.5,0.5));
//    description3->setColor(ccc3(238,204,122));
//    description3->setPosition(ccp(260,30));
//    layer->addChild(description3);
//    
//    CCSprite* underline3 = CCSprite::createWithSpriteFrameName("underline.png");
//    underline3->setPosition(ccp(260,15));
//    layer->addChild(underline3);
    
    
    
    
    
    
    
//    } else if(unitCard->cardId == tankCreatorTag) {
//        float attackLevelData = MyUtil::getInstance()->updateLevelByRate(tankBaseDamage, unitCard->getLevel(), tankUpdateDamageRate);
//        float attackNextData = MyUtil::getInstance()->updateLevelByRate(tankBaseDamage, unitCard->getLevel()+1, tankUpdateDamageRate);
//        float attackMaxData = MyUtil::getInstance()->updateLevelByRate(tankBaseDamage, unitCard->maxLevel, tankUpdateDamageRate);
//        
//        CCSprite* attackIcon = CCSprite::createWithSpriteFrameName("damageIcon.png");
//        attackIcon->setPosition(ccp(-68,160));
//        layer->addChild(attackIcon);
//        CCLayer* attackBar = getUpdateBar(attackNextData/attackMaxData, attackLevelData/attackMaxData);
//        attackBar->setPosition(ccp(-40,142));
//        
//        
//        char str[100] = {0};
//        if (unitCard->getLevel() <unitCard->maxLevel) {
//            sprintf(str, "每秒造成伤害:%d+%d",(int)(attackLevelData),(int)(attackNextData-attackLevelData));
//        } else {
//            sprintf(str, "每秒造成伤害:%d",(int)(attackLevelData));
//        }
//        
//        CCLabelTTF* attackLabel = CCLabelTTF::create(str, "Arial", 24);
//        attackLabel->setAnchorPoint(ccp(0,0));
//        attackLabel->setColor(ccc3(114, 66, 45));
//        attackLabel->setPosition(ccp(-40,152));
//        layer->addChild(attackBar);
//        layer->addChild(attackLabel);
//        
//        float healthLevelData = MyUtil::getInstance()->updateLevelByRate(tankBaseHealth, unitCard->getLevel(), tankUpdateHealthRate);
//        float healthNextData = MyUtil::getInstance()->updateLevelByRate(tankBaseHealth, unitCard->getLevel()+1, tankUpdateHealthRate);
//        float healthMaxData = MyUtil::getInstance()->updateLevelByRate(tankBaseHealth, unitCard->maxLevel, tankUpdateHealthRate);
//        
//        CCSprite* healthIcon = CCSprite::createWithSpriteFrameName("healthIcon.png");
//        healthIcon->setPosition(ccp(-68,106));
//        layer->addChild(healthIcon);
//        CCLayer* healthBar = getUpdateBar(healthNextData/healthMaxData, healthLevelData/healthMaxData);
//        
//        healthBar->setPosition(ccp(-40,88));
//        
//        
//        if (unitCard->getLevel() <unitCard->maxLevel) {
//            sprintf(str, "耐久度:%d+%d",(int)(healthLevelData),(int)((healthNextData-healthLevelData)));
//        } else {
//            sprintf(str, "耐久度:%d",(int)healthLevelData);
//        }
//        
//        CCLabelTTF* healthLabel = CCLabelTTF::create(str, "Arial", 24);
//        healthLabel->setAnchorPoint(ccp(0,0));
//        healthLabel->setColor(ccc3(114, 66, 45));
//        healthLabel->setPosition(ccp(-40,98));
//        layer->addChild(healthBar);
//        layer->addChild(healthLabel);
//        
//        float costLevelData = MyUtil::getInstance()->updateLevelByRate(tankBaseCost, unitCard->getLevel(), tankUpdateCostRate);
//        float costNextData = MyUtil::getInstance()->updateLevelByRate(tankBaseCost, unitCard->getLevel()+1, tankUpdateCostRate);
//        float costMaxData = MyUtil::getInstance()->updateLevelByRate(tankBaseCost, unitCard->maxLevel, tankUpdateCostRate);
//        
//        CCSprite* costIcon = CCSprite::createWithSpriteFrameName("oilIcon.png");
//        costIcon->setPosition(ccp(-68,48));
//        costIcon->setScale(24/costIcon->getContentSize().width);
//        layer->addChild(costIcon);
//        CCLayer* costBar = getUpdateBar(costNextData/costMaxData, costLevelData/costMaxData);
//        costBar->setPosition(ccp(-40,30));
//        
//        if (unitCard->getLevel() <unitCard->maxLevel) {
//            sprintf(str, "派遣使用油料:%d+%d",(int)(costLevelData),(int)((costNextData-costLevelData)));
//        } else {
//            sprintf(str, "派遣使用油料:%d",(int)(costLevelData));
//        }
//        CCLabelTTF* costLabel = CCLabelTTF::create(str, "Arial", 24);
//        costLabel->setAnchorPoint(ccp(0,0));
//        costLabel->setColor(ccc3(114, 66, 45));
//        costLabel->setPosition(ccp(-40,40));
//        layer->addChild(costBar);
//        layer->addChild(costLabel);
//        
//        CCLabelTTF* nameLabel = CCLabelTTF::create("重型坦克", "Arial", 24);
//        nameLabel->setColor(ccc3(114,66,45));
//        nameLabel->setAnchorPoint(ccp(0.5,0.5));
//        nameLabel->setPosition(ccp(-204,168));
//        layer->addChild(nameLabel);
//        
//        //        updateLayer->addChild(rangeLabel);
//        sprintf(str, "移动速度:%d",tankBaseSpeed*10);
//        CCLabelTTF* description1 = CCLabelTTF::create(str, "Arial",  26);
//        description1->setAnchorPoint(ccp(0,0.5));
//        description1->setColor(ccc3(114, 66, 45));
//        description1->setPosition(ccp(-110,-6));
//        layer->addChild(description1);
//        
//        CCSprite* underline1 = CCSprite::createWithSpriteFrameName("underline.png");
//        underline1->setPosition(ccp(0,-22));
//        layer->addChild(underline1);
//        
//        
//        sprintf(str, "攻击距离:%d格",tankBaseRange);
//        CCLabelTTF* description2 = CCLabelTTF::create(str, "Arial",  26);
//        description2->setAnchorPoint(ccp(0,0.5));
//        description2->setColor(ccc3(114, 66, 45));
//        description2->setPosition(ccp(-110,-42));
//        layer->addChild(description2);
//        
//        CCSprite* underline2 = CCSprite::createWithSpriteFrameName("underline.png");
//        underline2->setPosition(ccp(0,-58));
//        layer->addChild(underline2);
//        
//        
//        CCLabelTTF* description3 = CCLabelTTF::create("主要目标:任意目标", "Arial",  26);
//        description3->setAnchorPoint(ccp(0,0.5));
//        description3->setColor(ccc3(114, 66, 45));
//        description3->setPosition(ccp(-110,-78));
//        layer->addChild(description3);
//        
//        CCSprite* underline3 = CCSprite::createWithSpriteFrameName("underline.png");
//        underline3->setPosition(ccp(0,-94));
//        layer->addChild(underline3);
//    }
//    return layer;
//}
MyBaseMessage* MyGameFactory::getMessageByCommander(char* commanderStr) {
    GXCommander* comm =  MyJsonUtil::parseGXCommanderByString(commanderStr);
    unsigned pos = comm->cmd->m_sString.find(".");
    std::string str3 = comm->cmd->m_sString.substr(0,pos);
    GXMessage* mess = GXMessage::create();
    GXString* GXcmd = GXString::create(comm->cmd->m_sString.substr(pos+1));
    mess->setCmd(GXcmd);
    GXcmd->release();
    mess->setMsg(comm->msg);
    mess->succ = comm->succ;
    if(str3.compare("push") ==0) {
//        if (mess->getCmd()->compare("chatWorld") == 0) {
//            GXMsg* gxmsg =  MyJsonUtil::parseGXMsg(comm->detail);
//            gxmsg->mode = worldMode;
//            //            CCLog("%s：%s",gxmsg->name.c_str(),gxmsg->msg.c_str());
//            comm->release();
//            free(commanderStr);
//            mess->release();
//            GXChatHandler::getInstance()->handleWorldMessage(gxmsg);
//            return NULL;
//        } else if (mess->getCmd()->compare("chatUnion")  == 0) {
//            GXMsg* gxmsg =  MyJsonUtil::parseGXMsg(comm->detail);
//            gxmsg->mode = unionMode;
////            CCLog("%s：%s",gxmsg->name.c_str(),gxmsg->msg.c_str());
//            comm->release();
//            free(commanderStr);
//            mess->release();
//            GXChatHandler::getInstance()->handleUnionMessage(gxmsg);
//            return NULL;
//        } else
        if (mess->getCmd()->compare("loudSpeak") == 0) {
            mess->tag = loadSpeakerMessageTag;
            //            CCLog("%s：%s",gxmsg->name.c_str(),gxmsg->msg.c_str());
            
        } else if(mess->getCmd()->compare("missions") == 0) {
            mess->tag = questMessageTag;
        } else if(mess->getCmd()->compare("unionApplyJoin") == 0) {
            mess->tag = unionPushMessageTag;
//            GXArray* array = MyJsonUtil::parsePushUnionApplyJoin(comm->detail);
//            CCObject* obj;
//            CCARRAY_FOREACH(array,obj) {
//                GXMessage* gxmsg = (GXMessage*)obj;
//                gxmsg->tag = unionPushTag;
//                gxmsg->sendMsg();
//            }
//            comm->release();
//            free(commanderStr);
//            array->release();
//            mess->release();
//            return NULL;
        } else if(mess->getCmd()->compare("unionApplyApproveResult") == 0) {
            mess->tag = unionPushMessageTag;
//            if (mess->succ) {
//                MyJsonUtil::parseUserUnion(comm->detail,mess);
//            }
        }
        else if(mess->getCmd()->compare("unionRemoved") == 0) {
            mess->tag = unionPushMessageTag;
        }else if(mess->getCmd()->compare("getCPUWar") == 0){
            mess->tag = gameDataMessageTag;
        }else if(mess->getCmd()->compare("dissolveUnion") == 0) {
            mess->tag = unionPushMessageTag;
        }else {
            mess->tag = pushMessageTag;
        }
    } else if(str3.compare("gameData") == 0) {
        mess->tag = gameDataMessageTag;
//        mess->varMap->setObject(comm->detail,"detail");
    } else if(str3.compare("match") == 0) {
        mess->tag = gameDataMessageTag;
//        mess->varMap->setObject(comm->detail,"detail");
    } else if(str3.compare("cpuwar") ==0) {
        mess->tag = gameDataMessageTag;
    }else if(str3.compare("union") == 0) {
        mess->tag = unionMessageTag;
//        if(mess->cmd->compare("members") == 0) {
//            GXArray* members = MyJsonUtil::parseUnionMember(comm->detail);
//            mess->tag = unionMessageTag;
//            mess->varMap->setObject(members,"members");
//            members->release();
//        } else {
//            MyJsonUtil::parseUserUnion(comm->detail,mess);
//            mess->tag = unionMessageTag;
//        }
    } else if(str3.compare("user") == 0) {
        mess->tag = userMessageTag;
    } else if(str3.compare("system") == 0) {
        mess->tag = systemMessageTag;
    } else if(str3.compare("store") == 0) {
        mess->tag = storeMessageTag;
    } else if(str3.compare("mission") == 0) {
        mess->tag = gameDataMessageTag;
    } else if(str3.compare("building") == 0) {
        mess->tag = gameDataMessageTag;
    }
    mess->setDetail(comm->detail);
    comm->release();
    free(commanderStr);
    return mess;
}

//CCLayer* MyGameFactory::getUnitClassDescript(UnitCreator* bean) {
//    CCLayer* layer = CCLayer::create();
//    
//    //    CCLog("damageRate:%f",bean->creator->updateDamageRate);
//    
//    float attackMaxData = MyUtil::getInstance()->updateLevelByRate(0,bean->getDamage(), bean->getMaxLevel(), bean->updateDamageRate);
//    CCSprite* attackIcon = CCSprite::createWithSpriteFrameName("damageIcon.png");
//    attackIcon->setPosition(ccp(0,335));
//    layer->addChild(attackIcon);
//    attackIcon->setScale(1.3);
//    
//    
//    
//    char str[100] = {0};
//    sprintf(str, "每秒伤害:%d~%d",(int)(bean->getDamage()),(int)(attackMaxData));
//    
//    CCLabelTTF* attackLabel = CCLabelTTF::create(str, "Arial", 38);
//    attackLabel->setAnchorPoint(ccp(0,0.5));
//    attackLabel->setColor(ccc3(255,224,122));
//    attackLabel->setPosition(ccp(30,332));
//
//    layer->addChild(attackLabel);
//    
////    CCSprite* underline3 = CCSprite::createWithSpriteFrameName("underline.png");
////    underline3->setPosition(ccp(130,340));
////    layer->addChild(underline3);
//   
//    
////    float speedStartData = MyUtil::getInstance()->updateLevelByCount(bean->getSpeed(), 1, bean->updateSpeedRate);
//    
//    float speedMaxData = MyUtil::getInstance()->updateLevelByCount(bean->getSpeed(), bean->getMaxLevel(), bean->updateSpeedRate);
//    
//    CCSprite* speedIcon = CCSprite::createWithSpriteFrameName("speedIcon.png");
//    speedIcon->setScale(1.3);
//    speedIcon->setPosition(ccp(0,280));
//    layer->addChild(speedIcon);
//      
//    sprintf(str, "移动速度:%d~%d",(int)(bean->getSpeed()*10),(int)(speedMaxData*10));
//    
//    CCLabelTTF* speedLabel = CCLabelTTF::create(str, "Arial", 38);
//    speedLabel->setAnchorPoint(ccp(0,0.5));
//    speedLabel->setColor(ccc3(255,224,122));
//    speedLabel->setPosition(ccp(30,277));
//    layer->addChild(speedLabel);
//    
//    //    CCLog("speedRate:%f",speedLevelData/speedMaxData);
//    
//
//    float healthMaxData = MyUtil::getInstance()->updateLevelByRate(0,bean->getLife(), bean->getMaxLevel(), bean->updateHealthRate);
//
//    
//    CCSprite* healthIcon = CCSprite::createWithSpriteFrameName("healthIcon.png");
//    healthIcon->setScale(1.3);
//    healthIcon->setPosition(ccp(0,225));
//    layer->addChild(healthIcon);
//    
//    
//    sprintf(str, "耐久度:%d~%d",(int)bean->getLife(),(int)healthMaxData);
//    
//    CCLabelTTF* healthLabel = CCLabelTTF::create(str, "Arial", 38);
//    healthLabel->setAnchorPoint(ccp(0,0.5));
//    healthLabel->setColor(ccc3(255,224,122));
//    healthLabel->setPosition(ccp(30,222));
//    layer->addChild(healthLabel);
//    
//    //    CCLog("lifeRate:%f",healthLevelData/healthMaxData);
//    
//    float costMaxData = MyUtil::getInstance()->updateLevelByRate(0,bean->getSummaryOil(), bean->getMaxLevel(), bean->updateCostRate);
////
//    CCSprite* costIcon = CCSprite::createWithSpriteFrameName("oilIcon.png");
//    costIcon->setPosition(ccp(0,170));
//    costIcon->setScale(27/costIcon->getContentSize().width);
//    layer->addChild(costIcon);
//        
//    
//    sprintf(str, "派遣用油:%d~%d",(int)bean->getSummaryOil(),(int)(costMaxData));
//    CCLabelTTF* costLabel = CCLabelTTF::create(str, "Arial", 38);
//    costLabel->setAnchorPoint(ccp(0,0.5));
//    costLabel->setColor(ccc3(255,224,122));
//    costLabel->setPosition(ccp(30,167));
//    layer->addChild(costLabel);
//    
//    CCSprite* rangeIcon = CCSprite::createWithSpriteFrameName("attackRangeIcon.png");
//    rangeIcon->setScale(1.3);
//    rangeIcon->setPosition(ccp(0,115));
//    layer->addChild(rangeIcon);
//    
//    sprintf(str, "攻击距离:%d格",(int)bean->getAttackRange());
//    CCLabelTTF* rangeLabel = CCLabelTTF::create(str, "Arial",  38);
//    rangeLabel->setAnchorPoint(ccp(0,0.5));
//    rangeLabel->setColor(ccc3(255,224,122));
//    rangeLabel->setPosition(ccp(30,112));
//    layer->addChild(rangeLabel);

    
    
//
//    if (!isAll) {
//        return layer;
//    }
//    
//    
//    sprintf(str, "最大等级:%d",(int)bean->creator->getMaxLevel());
//    CCLabelTTF* description1 = CCLabelTTF::create(str, "Arial",  26);
//    description1->setAnchorPoint(ccp(0.5,0.5));
//    description1->setColor(ccc3(238,204,122));
//    description1->setPosition(ccp(260,110));
//    layer->addChild(description1);
//    
//    CCSprite* underline1 = CCSprite::createWithSpriteFrameName("underline.png");
//    underline1->setPosition(ccp(260,95));
//    layer->addChild(underline1);
//    
//    
//
//    CCSprite* underline2 = CCSprite::createWithSpriteFrameName("underline.png");
//    underline2->setPosition(ccp(260,55));
//    layer->addChild(underline2);
//    
//    
//    CCLabelTTF* description3 = CCLabelTTF::create("主要目标:任意目标", "Arial",  26);
//    description3->setAnchorPoint(ccp(0.5,0.5));
//    description3->setColor(ccc3(238,204,122));
//    description3->setPosition(ccp(260,30));
//    layer->addChild(description3);
//    

    
//    return layer;
//}

CCLayer* MyGameFactory::getBuildingClassDescript(BuildingCreator* bean) {
    CCLayer* layer = CCLayer::create();
    
    CCObject* obj;
    int i=0;
    CCARRAY_FOREACH(bean->descInfos,obj) {
        DescInfo* info = (DescInfo*)obj;

        
        CCSprite* icon = CCSprite::createWithSpriteFrameName(info->icon.c_str());
        icon->setScale((45/icon->getContentSize().height+45/icon->getContentSize().width)/2);
        icon->setPosition(ccp(0,i*55));
        layer->addChild(icon);
        
        char str[100] = {0};
        sprintf(str, "%s",info->label.c_str());
        
        CCLabelTTF* label = CCLabelTTF::create(str, "Arial", 38);
        label->setAnchorPoint(ccp(0,0.5));
        label->setColor(ccc3(255,224,122));
        label->setPosition(ccp(30,i*55));
        layer->addChild(label);
        i++;
    }
    layer->setContentSize(CCSizeMake(0,i*55));
    return layer;
}

CCNode* MyGameFactory::getShopResourceIcon(int resourceTag,int displayLevel) {
    CCNode* bp =NULL;
    if (resourceTag == gloryTag) {
        if (displayLevel == 1) {
            bp = CCSprite::createWithSpriteFrameName("shopGloryIcon.png");
            
            CCSprite* armystar = CCSprite::createWithSpriteFrameName("armystar.png");
            armystar->setPosition(ccp(bp->getContentSize().width/2,bp->getContentSize().height/2));
            armystar->setScale(1.5);
            bp->addChild(armystar);
        } else if(displayLevel == 2) {
            bp = CCSprite::createWithSpriteFrameName("shopGloryIcon.png");
            
            CCSprite* armystar = CCSprite::createWithSpriteFrameName("armystar.png");
            armystar->setPosition(ccp(bp->getContentSize().width/2,bp->getContentSize().height/2));
            armystar->setScale(1.5);
            bp->addChild(armystar);
            CCSprite* armystar2 = CCSprite::createWithSpriteFrameName("armystar.png");
            armystar2->setPosition(ccp(bp->getContentSize().width/2,bp->getContentSize().height/2+40));
            armystar2->setScale(1.5);
            bp->addChild(armystar2);
            CCSprite* armystar3 = CCSprite::createWithSpriteFrameName("armystar.png");
            armystar3->setPosition(ccp(bp->getContentSize().width/2,bp->getContentSize().height/2-40));
            armystar3->setScale(1.5);
            bp->addChild(armystar3);
        } else if(displayLevel == 3) {
            bp = CCSprite::createWithSpriteFrameName("shopGloryIcon.png");
            
            CCSprite* armystar = CCSprite::createWithSpriteFrameName("armystar.png");
            armystar->setPosition(ccp(bp->getContentSize().width/2-20,bp->getContentSize().height/2));
            armystar->setScale(1.2);
            bp->addChild(armystar);
            CCSprite* armystar11 = CCSprite::createWithSpriteFrameName("armystar.png");
            armystar11->setPosition(ccp(bp->getContentSize().width/2+20,bp->getContentSize().height/2));
            armystar11->setScale(1.2);
            bp->addChild(armystar11);
            CCSprite* armystar2 = CCSprite::createWithSpriteFrameName("armystar.png");
            armystar2->setPosition(ccp(bp->getContentSize().width/2-20,bp->getContentSize().height/2+40));
            armystar2->setScale(1.2);
            bp->addChild(armystar2);
            CCSprite* armystar22 = CCSprite::createWithSpriteFrameName("armystar.png");
            armystar22->setPosition(ccp(bp->getContentSize().width/2+20,bp->getContentSize().height/2+40));
            armystar22->setScale(1.2);
            bp->addChild(armystar22);
            CCSprite* armystar3 = CCSprite::createWithSpriteFrameName("armystar.png");
            armystar3->setPosition(ccp(bp->getContentSize().width/2,bp->getContentSize().height/2-40));
            armystar3->setScale(1.5);
            bp->addChild(armystar3);
        }
        bp->setScale(Mathlib::min(195/bp->getContentSize().width,154/bp->getContentSize().height)*0.5);
    } else if(resourceTag == ironTag) {
        if (displayLevel == 1) {
            bp = CCSprite::createWithSpriteFrameName("shopIronIcon.png");
            bp->setScale(Mathlib::min(195/bp->getContentSize().width,154/bp->getContentSize().height)*0.5);
            
        } else if(displayLevel ==2) {
            CCSpriteBatchNode* sheet = CCSpriteBatchNode::create("shopUI.pvr.ccz");
            for (int i=0; i<2; i++) {
                CCSprite* sprite = CCSprite::createWithSpriteFrameName("shopIronIcon.png");
                sprite->setPosition(ccp(-28+i*56,2-i*4));
                sheet->addChild(sprite);
            }
            bp = sheet;
            sheet->setScale(0.57);
        } else if(displayLevel == 3) {
            CCSpriteBatchNode* sheet = CCSpriteBatchNode::create("shopUI.pvr.ccz");
            for (int i=0; i<2; i++) {
                CCSprite* sprite = CCSprite::createWithSpriteFrameName("shopIronIcon.png");
                sprite->setPosition(ccp(-28+i*56,-15-i*4));
                sheet->addChild(sprite);
            }
            CCSprite* sprite2= CCSprite::createWithSpriteFrameName("shopIronIcon.png");
            sprite2->setPosition(ccp(0,30));
            sheet->addChild(sprite2);
            bp = sheet;
            sheet->setScale(0.45);
        }
    } else if(resourceTag == oilTag) {
        if (displayLevel == 1) {
            bp = CCSprite::createWithSpriteFrameName("shopOilIcon.png");
            bp->setScale(Mathlib::min(195/bp->getContentSize().width,154/bp->getContentSize().height)*0.5);
            
        } else if(displayLevel ==2) {
            CCSpriteBatchNode* sheet = CCSpriteBatchNode::create("shopUI.pvr.ccz");
            for (int i=0; i<3; i++) {
                CCSprite* sprite = CCSprite::createWithSpriteFrameName("shopOilIcon.png");
                sprite->setPosition(ccp(20-i*20,20-i*20));
                sheet->addChild(sprite);
            }
            bp = sheet;
            sheet->setScale(0.57);
        } else if(displayLevel == 3) {
            CCSpriteBatchNode* sheet = CCSpriteBatchNode::create("shopUI.pvr.ccz");
            for (int i=0; i<3; i++) {
                CCSprite* sprite = CCSprite::createWithSpriteFrameName("shopOilIcon.png");
                sprite->setPosition(ccp(40+20-i*20,20-i*20));
                sheet->addChild(sprite);
                CCSprite* sprite2 = CCSprite::createWithSpriteFrameName("shopOilIcon.png");
                sprite2->setPosition(ccp(-40+20-i*20,25-i*20));
                sheet->addChild(sprite2);
            }
            
            bp = sheet;
            sheet->setScale(0.45);
        }
    }
    return bp;
}