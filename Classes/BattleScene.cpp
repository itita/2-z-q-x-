//
//  BattleScene.cpp
//  ww2
//
//  Created by DingYu Fu on 12-9-5.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "cocos2d.h"
#include "BattleScene.h"
#include "StartScene.h"
#include "MyBattleMap.h"
#include "GXRadioMenu.h"
#include "MyDeployButton.h"
#include "MyUnit.h"
#include "BeAttackState.h"
#include "AoeDefendState.h"
#include "SimpleAudioEngine.h"
#include "NormalState.h"
#include "MyGameFactory.h"
#include "MyContinueTiledSprite.h"
#include "MyHttpConnection.h"
#include "MyJsonUtil.h"
#include "MyGameInfo.h"
#include "PulsarNative.h"
#include "MyUtil.h"
#include "DefineSet.h"
#include "MyUnitCard.h"
#include "ResourceBeAttackState.h"
#include "MyPriorityMenu.h"
#include "GXShieldTouchMenuItem.h"
#include "Mathlib.h"
#include "MyBattleBuilding.h"
#include "TransitonScene.h"
#include "BattleOverMessage.h"
#include "ResourceOnlyBeRobberState.h"

#define getVirtoryGloryFromEnemy MyUtil::getInstance()->getVirtoryGloryFromEnemy(MyGameInfo::getInstance()->enemyPower)


BattleScene::~BattleScene() {
    CC_SAFE_RELEASE_NULL(battleMap);
    CC_SAFE_RELEASE_NULL(m_TextField);
//    CocosDenshion::SimpleAudioEngine::sharedEngine()->unloadEffect("sfx_deploySoldier.m4a");
//    CocosDenshion::SimpleAudioEngine::sharedEngine()->unloadEffect("sfx_deployTank.m4a");
//    CocosDenshion::SimpleAudioEngine::sharedEngine()->unloadEffect("sfx_diaobao1f.wav");
//    CocosDenshion::SimpleAudioEngine::sharedEngine()->unloadEffect("sfx_paoji.m4a");
    releaseResource();
    CCLog("BattleScene released!");
}

BattleScene* BattleScene::create(cocos2d::CCArray *buildings,float _trophyRate,UnionBean* bean,int _enemyVipExperience) {
    BattleScene *pRet = new BattleScene();
//    pRet->loadResource();
    pRet->trophyRate = _trophyRate;
    
    CCLog("trophyRate:%f",_trophyRate);
    if (pRet && pRet->init(buildings))
    {
        pRet->autorelease();
        pRet->initUI(bean,_enemyVipExperience);
        return pRet;
    }
    else
    {
        CC_SAFE_DELETE(pRet);
        return NULL;
    }
}

bool BattleScene::init(cocos2d::CCArray *buildings) {
    isFighting = beforeFightTag;
    isVictory = false;
    battleMap = MyBattleMap::create("ditu002.tmx");
    battleMap->retain();
    battleMap->setOriPosition(ccp(0,0));
//    initSound();
    
    
    CCSprite* backl = CCSprite::createWithSpriteFrameName("backgroundlr.png");
    CCSprite* backr = CCSprite::createWithSpriteFrameName("backgroundlr.png");
    CCSprite* backu = CCSprite::createWithSpriteFrameName("backgroundud.png");
    CCSprite* backd = CCSprite::createWithSpriteFrameName("backgroundud.png");
    
    backl->setAnchorPoint(ccp(0,1));
    backl->setScale(1800/backl->getContentSize().width);
    backl->setPosition(ccp(0,battleMap->getContentSize().height));
    battleMap->CCNode::addChild(backl,-1);
    
    backu->setAnchorPoint(ccp(1,1));
    backu->setScale(1800/backu->getContentSize().width);
    backu->setPosition(ccp(battleMap->getContentSize().width,battleMap->getContentSize().height));
    battleMap->CCNode::addChild(backu,-1);
    
    backd->setAnchorPoint(ccp(0,0));
    backd->setPosition(ccp(0,0));
    backd->setScale(1800/backd->getContentSize().width);
    battleMap->CCNode::addChild(backd,-1);
    
    backr->setAnchorPoint(ccp(1,0));
    backr->setPosition(ccp(battleMap->getContentSize().width,0));
    backr->setScale(1800/backr->getContentSize().width);
    battleMap->CCNode::addChild(backr,-1);
    
    MyBattleBuilding* zhihuisuo  = NULL;
//    MyBattleBuilding* cellar = NULL;
    CCObject* obj;
    
    CCArray* antiArray =CCArray::create();
    
    CCARRAY_FOREACH(buildings, obj) {
        BuildingBean* bean = dynamic_cast<BuildingBean*>(obj);
        if (bean->tag == -1) {
            CCLog("日扯");
        }
        MyBattleBuilding* building = MyGameFactory::createBattleBuildingByBean(bean, this);
        if (building == NULL) {
            continue;
        }
        
        if (building->getTag() == dapaoTag) {
            antiArray->addObject(building);
        }
        battleMap->addChild(building);
        MyContinueTiledSprite* item = dynamic_cast<MyContinueTiledSprite*>(((MyBattleState*)building->fsm->getCurrentState())->getItem());
        if (item != NULL) {
            item->updateLoc(1);
        }
        if (building->getTag() == zhihuisuoTag) {
            zhihuisuo = building;
        }
        if (building->getTag() == CellarTag) {
            cellarProtectCount = bean->arg0*0.3;
        }
    }

    char str[20] = {0};
    if (zhihuisuo != NULL) {
        CCARRAY_FOREACH(antiArray, obj) {
            MyBattleBuilding* building = dynamic_cast<MyBattleBuilding*>(obj);
            
            float angle = Mathlib::getAngle(zhihuisuo->getPositionByTiled(), building->getPositionByTiled());
            int dir = (((int)(angle*180/3.141592654+22.5)+360)%360)/45 ;
            AoeDefendState* state =  dynamic_cast<AoeDefendState*>(building->fsm->getState(DefendStateTag));
            if (state == NULL) {
                continue;
            }
            
            if (dir == 0) {
                sprintf(str, "antiTankfld (0).png");
            } else if (dir == 1) {
                sprintf(str, "antiTankfd (0).png");
            } else if (dir == 2) {
                sprintf(str, "antiTankfrd (0).png");
            } else if (dir == 3) {
                sprintf(str, "antiTankfr (0).png");
            } else if (dir == 4) {
                sprintf(str, "antiTankfru (0).png");
            } else if (dir == 5) {
                sprintf(str, "antiTankfu (0).png");
            } else if (dir == 6) {
                sprintf(str, "antiTankflu (0).png");
            } else if (dir == 7) {
                sprintf(str, "antiTankfl (0).png");
            }
            
            CCSprite* byItem =CCSprite::createWithSpriteFrameName(str);
            byItem->setAnchorPoint(ccp(0.5,0.5));
            CCSprite* zhendi = CCSprite::createWithSpriteFrameName("position.png");
            zhendi->setPosition(ccp(byItem->getContentSize().width/2,byItem->getContentSize().height/2));
            byItem->addChild(zhendi,-1);
            state->setItem(byItem);
            
        }
        ResourceOnlyBeRobberState* state = ((ResourceOnlyBeRobberState*)zhihuisuo->fsm->getCurrentState());
        state->setOil(Mathlib::max(state->getOil()-cellarProtectCount,0));
        state->setIron(Mathlib::max(state->getIron()-cellarProtectCount,0));
    }
    

    battleMap->setTag(MainMapTag);
    battleMap->displayTip();
    
    
    battleMap->centerView();
    this->addChild(battleMap);
    this->schedule(schedule_selector(BattleScene::countdown),1);
    return true;
}   

bool BattleScene::init() {
//    battleMap = MyBattleMap::create("ditu001.tmx");
//    battleMap->retain();
//    battleMap->setOriPosition(ccp(0,0));
////    initSound();
//    
//    this->addChild(battleMap);
//    
//   
//    
////    for (int i=0; i<10; ++i) {
////        for (int j=0; j<10; ++j) {
//            MyBattleBuilding* BDbuilding = MyGameFactory::createCreateInBattle(54,this,1);
//            //        BDbuilding->setPosition(ccp(900,900));
////            BDbuilding->setPositionByTiled(ccp(1+i*5,1+j*5));
//    BDbuilding->setPositionByTiled(ccp(1,1));
//            MyBattleBuilding* diaobao = MyGameFactory::createBattleDiaoBao(this,1);
////            diaobao->setPositionByTiled(ccp(3.5+i*5,3.5+j*5));
//            diaobao->setPositionByTiled(ccp(3.5,3.5));
//            
//    
//    MyBattleBuilding* dapao = MyGameFactory::createBattleDaPao(this,1);
//    dapao->setPositionByTiled(ccp(20,20));
//            battleMap->addChild(BDbuilding);
//            battleMap->addChild(diaobao);
//    battleMap->addChild(dapao);
//
//    MyBattleBuilding* wall = MyGameFactory::createBattleWall(this,1);
//    wall->setPositionByTiled(ccp(25,25));
//    
//    MyBattleBuilding* wall1 = MyGameFactory::createBattleWall(this,1);
//    wall1->setPositionByTiled(ccp(24,25));
//    
//    MyBattleBuilding* wall2 = MyGameFactory::createBattleWall(this,1);
//    wall2->setPositionByTiled(ccp(23,25));
//    
//    MyBattleBuilding* wall3 = MyGameFactory::createBattleWall(this,1);
//    wall3->setPositionByTiled(ccp(25,24));
//    
//    MyBattleBuilding* wall4 = MyGameFactory::createBattleWall(this,1);
//    wall4->setPositionByTiled(ccp(25,24));
//    
//    MyBattleBuilding* wall5 = MyGameFactory::createBattleWall(this,1);
//    wall5->setPositionByTiled(ccp(25,23));
//    
//    
//    battleMap->addChild(wall);
//    battleMap->addChild(wall1);
//    battleMap->addChild(wall2);
//    battleMap->addChild(wall3);
//    battleMap->addChild(wall4);
//    battleMap->addChild(wall5);
//    
//    
////        }
////    }
////    
//    battleMap->displayTip();
////
//    UnitCreator* tankCreator = UnitCreator::create(101,CCString::create("tank1"),CCString::create("sfx_deployTank.m4a"),CCString::create("sfx_paoji.m4a"),2,5,5,20,70);
//    UnitCreator* tankCreator2 = UnitCreator::create(102,CCString::create("bubing1"),CCString::create("sfx_deploySoldier.m4a"),CCString::create("sfx_diaobao1f.wav"),1,4,3,10,20);
//    
//    CCSprite* tank = CCSprite::create("deployTank1.png");
//    CCSprite* gytank = CCSprite::create("deployTank1.png");
//    gytank->setColor(ccGRAY);
//    
//    MyDeployButton* deploy4 = MyDeployButton::create(tankCreator,this,menu_selector(BattleScene::callback1));
//    
//    CCSprite* soldier = CCSprite::create("deploySoldier1.png");
//    CCSprite* gysoldier = CCSprite::create("deploySoldier1.png");
//    gysoldier->setColor(ccGRAY);
//    
//    MyDeployButton* deploy3 = MyDeployButton::create(tankCreator2,this,menu_selector(BattleScene::callback1));
//
//    
////    CCMenuItemToggle* bingzhongUI2 = CCMenuItemToggle::create(map, menu_selector(BattleScene::callback1),CCMenuItemSprite::create(sprite, gysprite),CCMenuItemSprite::create(gysprite2, sprite2), NULL);
//    GXRadioMenu* bingzhongMenu = GXRadioMenu::create(-505,deploy3,deploy4,NULL);
//    bingzhongMenu->alignItemsHorizontallyWithPadding(10);
//    //    uiLayer->addChild(bingzhongMenu);
//    this->addChild(bingzhongMenu);
////    bingzhongMenu->setPosition(ccp(50,50));
//    bingzhongMenu->setPosition(ccp(50,50));
//    bingzhongMenu->setTag(bingzhongmenuTag);
//    
////    CCSprite* asd = CCSprite::create("xuetiao.png");
////    CCProgressTimer* progressTimer = CCProgressTimer::create(asd);
//////    progressTimer->setScale((building->contentSizeByTiled.width*60)/xuetiao->getContentSize().width);
////    progressTimer->setOpacity(0);
//////    progressTimer->setColor(ccRED);
////    progressTimer->setPosition(ccp(-50,-50));
////    progressTimer->setType(kCCProgressTimerTypeBar);
////    progressTimer->setPercentage(100);
////    BDbuilding->addChild(progressTimer);
////    BDbuilding->setOpacity(255);
////    asd->setOpacity(255);
////    progressTimer->getSprite()->setOpacity(0);
//////    for (int i=0; i<BDbuilding->getChildrenCount(); ++i) {
//////        BDbuilding->getChildren()->objectAtIndex(i)->
//////    }
//    initUI();
//    
    return true;
}


void BattleScene::initUI(UnionBean* unionBean ,int _enemyVipExperience) {
    CCLayer* uiLayer = CCLayer::create();
    
    CCSprite* avatar =CCSprite::createWithSpriteFrameName("avatar.png");
    avatar->setAnchorPoint(ccp(0,1));
    avatar->setPosition(ccp(0,winSize.height));
  
    CCSprite* avatarSprite = CCSprite::createWithSpriteFrameName("avatar0.png");
    avatarSprite->setAnchorPoint(ccp(0,1));
    avatarSprite->setPosition(ccp(0,avatar->getContentSize().height));
    avatar->addChild(avatarSprite);
    
    if (MyGameInfo::getInstance()->getUnionBean()->getName()->compare("") != 0) {
        CCSprite* unionBack = CCSprite::createWithSpriteFrameName("unionAvatar.png");
        unionBack->setAnchorPoint(ccp(0,0.5));
        unionBack->setPosition(ccp(0,-17));
        CCLabelTTF* namelabel = CCLabelTTF::create(MyGameInfo::getInstance()->getUnionBean()->getName()->getCString(),"Arial",19);
        namelabel->setAnchorPoint(ccp(0.5,0.5));
        namelabel->setPosition(ccp(102,unionBack->getContentSize().height/2));
        CCSprite* emblem = CCSprite::createWithSpriteFrameName(MyGameInfo::getInstance()->getUnionBean()->getEmblem()->getCString());
        emblem->setAnchorPoint(ccp(0.5,0.5));
        emblem->setPosition(ccp(22,unionBack->getContentSize().height/2+2));
        emblem->setScale(0.3);
        unionBack->addChild(namelabel);
        unionBack->addChild(emblem);
        avatar->addChild(unionBack);
    }
    
    CCSprite* avatarAverse =CCSprite::createWithSpriteFrameName("avatar.png");
    //    uiLayer->addChild(avatar);
    avatarAverse->setFlipX(true);
    avatarAverse->setAnchorPoint(ccp(1,1));
    avatarAverse->setPosition(ccp(winSize.width,winSize.height));
    CCSprite* avatarAverseSprite = CCSprite::createWithSpriteFrameName("avatar0.png");
    avatarAverseSprite->setFlipX(true);
    avatarAverseSprite->setAnchorPoint(ccp(1,1));
    avatarAverseSprite->setPosition(ccp(avatarAverse->getContentSize().width,avatarAverse->getContentSize().height));
    avatarAverse->addChild(avatarAverseSprite);
    
    bool enemyUnionFlag = (unionBean->getName()->compare("") != 0);
    if (enemyUnionFlag) {
        CCSprite* unionBack = CCSprite::createWithSpriteFrameName("unionAvatar.png");
        unionBack->setFlipX(true);
        unionBack->setAnchorPoint(ccp(1,0.5));
        unionBack->setPosition(ccp(avatarAverse->getContentSize().width,-17));
        CCLabelTTF* namelabel = CCLabelTTF::create(unionBean->getName()->getCString(),"Arial",19);
        namelabel->setAnchorPoint(ccp(0.5,0.5));
        namelabel->setPosition(ccp(unionBack->getContentSize().width-102,unionBack->getContentSize().height/2));
        CCSprite* emblem = CCSprite::createWithSpriteFrameName(unionBean->getEmblem()->getCString());
        emblem->setAnchorPoint(ccp(0.5,0.5));
        emblem->setPosition(ccp(unionBack->getContentSize().width-22,unionBack->getContentSize().height/2+2));
        emblem->setScale(0.3);
        unionBack->addChild(namelabel);
        unionBack->addChild(emblem);
        avatarAverse->addChild(unionBack);
    }
    
    
    //    CCLabelTTF* nickName = CCLabelTTF::create(string.c_str(),"Arial", 54);
    
    CCLabelTTF* nickName = MyUtil::getInstance()->getVipColorLabel(MyGameInfo::getInstance()->getNickName(),18,MyGameInfo::getInstance()->getVipExperience());
    nickName->setAnchorPoint(ccp(0.5,1));
#if(CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    nickName->setPosition(ccp(139,winSize.height-3));
#endif
#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    nickName->setPosition(ccp(139,winSize.height));
#endif
    
    
    CCLabelTTF* rankName = CCLabelTTF::create(MyUtil::getInstance()->getRankString(MyGameInfo::getInstance()->getPower()), "Arial", 20);
    uiLayer->addChild(rankName,2);
    rankName->setAnchorPoint(ccp(0,0.5));
    rankName->setPosition(ccp(120,winSize.height-44));
    rankName->setColor(ccWHITE);
    
    CCSprite* rankSprite = MyUtil::getInstance()->getRankSprite(MyGameInfo::getInstance()->getPower());
    rankSprite->setPosition(ccp(100,winSize.height-44));
    rankSprite->setScale(0.50);
    uiLayer->addChild(rankSprite,2);
    
    CCLabelTTF* enemyNickName = MyUtil::getInstance()->getVipColorLabel(MyGameInfo::getInstance()->getEnemyNickname()->getCString(),18,_enemyVipExperience);
    enemyVipExperience = _enemyVipExperience;
    enemyNickName->setAnchorPoint(ccp(0.5,1));
#if(CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    enemyNickName->setPosition(ccp(winSize.width -139,winSize.height-3));
#endif
#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    enemyNickName->setPosition(ccp(winSize.width -139,winSize.height));
#endif
    
    CCLabelTTF* enemyRankName = CCLabelTTF::create(MyUtil::getInstance()->getRankString(MyGameInfo::getInstance()->enemyPower), "Arial", 20);
    uiLayer->addChild(enemyRankName,2);
    enemyRankName->setAnchorPoint(ccp(1,0.5));
    enemyRankName->setPosition(ccp(winSize.width -120,winSize.height-44));
    enemyRankName->setColor(ccWHITE);
    
    CCSprite* enemyRankSprite = MyUtil::getInstance()->getRankSprite(MyGameInfo::getInstance()->enemyPower);
    enemyRankSprite->setPosition(ccp(winSize.width -100,winSize.height-44));
    enemyRankSprite->setScale(0.50);
    uiLayer->addChild(enemyRankSprite,2);
    
    CCSprite* next = CCSprite::createWithSpriteFrameName("next.png");
    CCSprite* gynext = CCSprite::createWithSpriteFrameName("next.png");
    gynext->setColor(ccGRAY);
    
    CCMenuItemSprite* nextItem = CCMenuItemSprite::create(next, gynext, this, menu_selector(BattleScene::toNext));
    nextItem->setPosition(ccp(winSize.width - 100,winSize.height/3));
    nextItem->setTag(nextTag);
    
    CCSprite* surrender = CCSprite::createWithSpriteFrameName("backToBuild.png");
    CCSprite* gysurrender = CCSprite::createWithSpriteFrameName("backToBuild.png");
    gysurrender->setColor(ccGRAY);
    
    CCMenuItemSprite* surrenderItem = CCMenuItemSprite::create(surrender, gysurrender, this, menu_selector(BattleScene::toBuildScene));
    surrenderItem->setPosition(ccp(100,winSize.height/3));
//    surrender->setVisible(false);
    surrenderItem->setTag(surrenderTag);
    
    fightMenu = CCMenu::create(nextItem,surrenderItem,NULL);
    fightMenu->setPosition(ccp(0,0));
    
    CCSprite* resourseBar = CCSprite::createWithSpriteFrameName("resourseBar.png");
    resourseBar->setScale(1.25);
    resourseBar->setAnchorPoint(ccp(0.5,1));
    resourseBar->setPosition(ccp(winSize.width/2,winSize.height));
    resourseBar->setTag(resourceBarTag);
    
    CCLabelAtlas* oilLabel = MyGameInfo::getInstance()->getOilAtlas();
    oilLabel->setPosition(ccp(27,6));
    oilLabel->setAnchorPoint(ccp(0,0));
    oilLabel->setScale(0.52);
    oilLabel->removeFromParentAndCleanup(true);
    resourseBar->addChild(oilLabel);
    
    CCLabelAtlas* ironLabel = MyGameInfo::getInstance()->getIronAtlas();
    ironLabel->setPosition(ccp(130,6));
    ironLabel->setAnchorPoint(ccp(0,0));
    ironLabel->setScale(0.52);
    ironLabel->removeFromParentAndCleanup(true);
    resourseBar->addChild(ironLabel);
    
    
    enemyOilLabel = MyAtlasNumber::create();
    enemyOilLabel->setNumberNoFx(MyGameInfo::getInstance()->getRobberOil());
    enemyOilLabel->setAnchorPoint(ccp(0,0.5));
    enemyOilLabel->setScale(0.9);
    enemyOilLabel->setPosition(ccp(winSize.width-140,enemyUnionFlag?480:520));
    CCSprite* oilIcon = CCSprite::createWithSpriteFrameName("oilIcon.png");
    oilIcon->setScale(0.7);
    oilIcon->setPosition(ccp(winSize.width-164,enemyUnionFlag?480:520));
    
    enemyIronLabel = MyAtlasNumber::create();
    enemyIronLabel->setNumberNoFx(MyGameInfo::getInstance()->getRobberIron());
    enemyIronLabel->setAnchorPoint(ccp(0,0.5));
    enemyIronLabel->setScale(0.9);
    enemyIronLabel->setPosition(ccp(winSize.width-140,enemyUnionFlag?435:475));
    CCSprite* ironIcon = CCSprite::createWithSpriteFrameName("ironIcon.png");
    ironIcon->setScale(0.7);
    ironIcon->setPosition(ccp(winSize.width-164,enemyUnionFlag?435:475));
    
    enemyHonorLabel = MyAtlasNumber::create();
    //TODO 新版的honor不是战斗力
    
    enemyHonorLabel->setNumberNoFx(getVirtoryGloryFromEnemy*trophyRate);
    enemyHonorLabel->setAnchorPoint(ccp(0,0.5));
    enemyHonorLabel->setScale(0.9);
    enemyHonorLabel->setPosition(ccp(winSize.width-140,enemyUnionFlag?390:430));
    CCSprite* honorIcon = CCSprite::createWithSpriteFrameName("honorIcon.png");
    honorIcon->setScale(0.7);
    honorIcon->setPosition(ccp(winSize.width-164,enemyUnionFlag?390:430));
    
    
    enemyPowerLabel = MyAtlasNumber::create();
    enemyPowerLabel->setNumberNoFx(Mathlib::bound((20*(MyGameInfo::getInstance()->enemyPower/MyGameInfo::getInstance()->getPower())*trophyRate),40,0));
    enemyPowerLabel->setAnchorPoint(ccp(0,0.5));
    enemyPowerLabel->setScale(0.9);
    enemyPowerLabel->setPosition(ccp(winSize.width-140,enemyUnionFlag?345:385));
    CCSprite* powerIcon = CCSprite::createWithSpriteFrameName("powerIcon.png");
    powerIcon->setScale(0.7);
    powerIcon->setPosition(ccp(winSize.width-164,enemyUnionFlag?345:385));
    
    
    lastTimeLabel = CCLabelAtlas::create("400", "number6.png", 24, 36, '/');
    lastTimeLabel->setScale(1.5);
    lastTimeLabel->setAnchorPoint(ccp(0.5,0.5));
    lastTimeLabel->setPosition(ccp(winSize.width/2,550));
    lastTimeLabel->setVisible(false);
    
    uiLayer->addChild(avatar);
    uiLayer->addChild(nickName);
    uiLayer->addChild(avatarAverse);
    uiLayer->addChild(enemyNickName);
    uiLayer->addChild(fightMenu);
    this->addChild(resourseBar,2);
    uiLayer->addChild(oilIcon);
    this->addChild(enemyOilLabel,1);
    uiLayer->addChild(ironIcon);
    this->addChild(enemyIronLabel,1);
    uiLayer->addChild(honorIcon);
    this->addChild(enemyHonorLabel,1);
    uiLayer->addChild(powerIcon);
    this->addChild(enemyPowerLabel,1);
    uiLayer->addChild(lastTimeLabel);
    
    
    
//    UnitCreator* tankCreator = UnitCreator::create(tankCreatorTag,CCString::create("tank1"),CCString::create("sfx_deployTank.m4a"),CCString::create("sfx_paoji.m4a"),tankBaseSpeed,tankBaseRange,tankBaseDamage,tankBaseHealth,tankBaseCost);
//    CCObject* obj = NULL;
//    char str[30] = {0};
    GXRadioMenu* bingzhongMenu = GXRadioMenu::create(-505);
    bingzhongMenu->setPosition(ccp(0,0));
    bingzhongMenu->setTag(bingzhongmenuTag);
    for (int i=0; i<5 && i<MyGameInfo::getInstance()->creatorArray->count(); i++) {        
        MyDeployButton* button = MyDeployButton::create((CreatorInfoBean*)MyGameInfo::getInstance()->creatorArray->objectAtIndex(i), this,menu_selector(BattleScene::callback1));
        
        
        button->setPosition(ccp(80+i*130,100));
        bingzhongMenu->addChild(button);
    }
    bingzhongMenu->setSelect(0);
    
    
    
    this->addChild(bingzhongMenu,1);
    
    
    
    //    char* str = 
    //    MyJsonUtil::parseBuildingFromJson(str);
    
    addChild(uiLayer,1);
}

void BattleScene::callback1(cocos2d::CCObject *pSender) {
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sfx_click.mp3");
    battleMap->setCurrentDeployButton(((MyDeployButton*)pSender));
}

void BattleScene::toVictory() {
    if(!isVictory) {
        isVictory = true;
    } else {
        return;
    }
    isFighting = afterFightTag;
    this->unschedule(schedule_selector(BattleScene::countdown));
    this->scheduleOnce(schedule_selector(BattleScene::victory),0);
}

void BattleScene::victory() {
    battleMap->setEnabled(false);
    battleMap->pauseSchedulerAndActions();
    MyGameInfo::getInstance()->changeResource(gloryTag,  enemyHonorLabel->getTargetNumber());
    enemyHonorLabel->setNumber(0);
    enemyPowerLabel->setNumber(0);
    CCObject* obj = NULL;
    MyBattleBuilding* build = NULL;
//    CCLog("%d",battleMap->getItems()->count());
//    int i = 0;
    CCArray* bufferArray = CCArray::create();
    CCARRAY_FOREACH(battleMap->getItems(), obj) {
//        if(obj!=NULL) {
//            obj = NULL;
            
            build = dynamic_cast<MyBattleBuilding*>(obj);
//            i++;
        //TODO
            if (build != NULL
//                && build->isAlive()
                ) {
                //有的时候会出现类型强制转换错误，预计是野指针错误释放，先用专用集合对付用着。
//                BeAttackState* state = dynamic_cast<BeAttackState*>(build->fsm->getCurrentState());
//                state->beAttack(99999999);
                bufferArray->addObject(build);
            }
//            else {
//                CCLog("死了的坑货:");
//            }
//        }
    }
    
    CCARRAY_FOREACH(bufferArray, obj) {
        build = dynamic_cast<MyBattleBuilding*>(obj);
        if (build->isAlive()) {
            ResourceBeAttackState* state = dynamic_cast<ResourceBeAttackState*>(build->fsm->getCurrentState());
            if (state) {
                state->beRobberResource(9999999);
            }
        }
        
//        if(build == NULL&& !build->isAlive()) {
//            
//            CCLog("还是日扯的");
//        }
    }
    
//    int robberOil = (int)(MyGameInfo::getInstance()->robberOil);
//    int robberIron = (int) (MyGameInfo::getInstance()->robberIron);
//    
//    
//    if (!MyHttpConnection::getInstance()->addMatch(true,robberOil,robberIron,MyJsonUtil::packBattleUnit(this->getChildByTag(bingzhongmenuTag)->getChildren()))) {
//        this->addChild(MyUtil::getInstance()->getNetworkDialog());
//        return;
//    }
//    
//    //todo 更新胜利
//    
//    MyHttpConnection::getInstance()->updateBattleOtherData(MyJsonUtil::packAllBattleBuilding(battleMap->getChildren()));
//    MyHttpConnection::getInstance()->updateResource(PulsarNative::getDeviceId(), false);
//    CocosDenshion::SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
    
    this->addChild(getVictoryUI(true),3);
}

void BattleScene::toBuildSceneWait(CCMenuItem* item) {
    if (item) {
        item->setEnabled(false);
    }
    addMatchInfo(isVictory);
    toBuildScene();
//    this->runAction(CCSequence::create(CCDelayTime::create(0.5),CCCallFuncND::create(this, callfuncND_selector(BattleScene::addMatchInfo), (void*)isVictory),CCCallFunc::create(this, callfunc_selector(BattleScene::toBuildScene)),NULL));
    
//    scheduleOnce(schedule_selector(BattleScene::toBuildScene), 0.5);
}


void BattleScene::toBuildScene() {
//    CocosDenshion::SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
//    CCArray* children =  this->getChildren();
//    CCObject* obj;
//    GXScrollTMXTileMap* map;
//    CCARRAY_FOREACH(children, obj) {
//        map = dynamic_cast<GXScrollTMXTileMap*>(obj);
//        if(map != NULL) {
//            map->unRegisterWithTouchDispatcher();
//        }
//        map = NULL;
//    }
    
    MyGameInfo::getInstance()->enemyIron = 0;
    MyGameInfo::getInstance()->enemyOil = 0;
    MyGameInfo::getInstance()->setRobberOil(0);
    MyGameInfo::getInstance()->setRobberIron(0);
    
    CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.2, TransitonScene::create(startSceneTag), ccBLACK));
    
}

void BattleScene::toNextWait(CCMenuItem* item) {
    item->setEnabled(false);
    this->addChild(MyUtil::getInstance()->getWaitLayer("正在搜索基地"),1000);
    addMatchInfo(isVictory);
    toNext();
//    this->runAction(CCSequence::create(CCDelayTime::create(0.5),CCCallFuncND::create(this, callfuncND_selector(BattleScene::addMatchInfo), (void*)isVictory),CCCallFunc::create(this, callfunc_selector(BattleScene::toNext)),NULL));
//    this->scheduleOnce(schedule_selector(BattleScene::toNext), 0.5);
}

void BattleScene::toNext() {
//    CCArray* children =  this->getChildren();
//    CCObject* obj;
//    GXScrollTMXTileMap* map;
//    CCARRAY_FOREACH(children, obj) {
//        map = dynamic_cast<GXScrollTMXTileMap*>(obj);
//        if(map != NULL) {
//            map->unRegisterWithTouchDispatcher();
//        }
//        map = NULL;
//    }
//    const char* response = MyHttpConnection::getInstance()->getOtherData();
//    if (strcmp(response, "failed") == 0|| strcmp(response, "\0") == 0) {
//        this->addChild(MyUtil::getInstance()->getNetworkDialog());
//        this->removeChildByTag(waitMenuTag, true);
//        return;
//    }
    MyGameInfo::getInstance()->enemyIron = 0;
    MyGameInfo::getInstance()->enemyOil = 0;
    MyGameInfo::getInstance()->setRobberIron(0);
    MyGameInfo::getInstance()->setRobberOil(0);
    CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.2,TransitonScene::create(ReadyToBattleTag), ccBLACK));
}

//void BattleScene::toReturnHomeWait() {
//    scheduleOnce(schedule_selector(BattleScene::toBuildScene));
//}

//void BattleScene::toContinueWarWait() {
//    this->scheduleOnce(schedule_selector(BattleScene::toNext));
//}

void BattleScene::surrender() {
    this->unschedule(schedule_selector(BattleScene::countdown));
    if (this->getChildByTag(surrenderDialogTag) != NULL) {
        this->getChildByTag(surrenderDialogTag)->removeFromParentAndCleanup(true);
    }
    battleMap->setEnabled(false);
    battleMap->pauseSchedulerAndActions();
   
        
//    int robberOil = (int)(MyGameInfo::getInstance()->robberOil-enemyOilLabel->getTargetNumber());
//    int robberIron = (int) {MyGameInfo::getInstance()->robberIron-enemyIronLabel->getTargetNumber()};
//    CCLog("robberOil:%d,robberIron:%d",robberOil,robberIron);
//    if (!MyHttpConnection::getInstance()->addMatch(false,robberOil,robberIron,MyJsonUtil::packBattleUnit(this->getChildByTag(bingzhongmenuTag)->getChildren()))) {
//        this->addChild(MyUtil::getInstance()->getNetworkDialog());
//        return;
//    }
//    
////    isFighting=false;
//    
//    //上传服务器失败
//    MyHttpConnection::getInstance()->updateBattleOtherData(MyJsonUtil::packAllBattleBuilding(battleMap->getChildren()));
//    MyHttpConnection::getInstance()->updateResource(PulsarNative::getDeviceId(), false);
    
    this->addChild(getVictoryUI(false),3);
}


void BattleScene::toSurrender() {
    if (isFighting == afterFightTag) {
        toBuildSceneWait(NULL);
    } else if(isFighting == beforeFightTag) {
//    	toReturnHomeWait();
        toBuildScene();
    } else if(this->getChildByTag(surrenderDialogTag)!=NULL){
//        if (!MyHttpConnection::getInstance()->addMatch(false)) {
//            this->addChild(MyUtil::getInstance()->getNetworkDialog());
//            return;
//        }
//        toBuildScene();
        surrender();
    }else {
        
        CCMenuItemSprite* sureItem = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("dialogsure.png"), CCSprite::createWithSpriteFrameName("dialogsurep.png"), this, menu_selector(BattleScene::surrender));
        
        
        CCMenuItemSprite* cancelItem =CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("dialogcancel.png"), CCSprite::createWithSpriteFrameName("dialogcancelp.png"),this,menu_selector(BattleScene::cancelSurrender));
        
        CCMenu* menu  = CCMenu::create(sureItem,cancelItem, NULL);
        menu->alignItemsHorizontallyWithPadding(30);
        menu->setPosition(ccp(winSize.width/2+120, winSize.height/2 -100));
        CCLayer* layer = CCLayer::create();
        layer->setTouchEnabled(true);
        CCLabelTTF* label = CCLabelTTF::create("副官：\n    指挥官，确定要投降么？", "宋体", 32,CCSizeZero, kCCTextAlignmentLeft, kCCVerticalTextAlignmentTop);
        label->setOpacity(0);
        label->setColor(ccc3(230, 207, 185));
        label->setPosition(ccp(winSize.width/2+120,winSize.height/2+50));
        CCSprite* dialogBack = MyUtil::getInstance()->getDialogBack();
        dialogBack->setPosition(ccp(winSize.width/2,winSize.height/2));
        layer->addChild(dialogBack);
        layer->addChild(menu);
        layer->addChild(label);
        layer->setScale(0.5);
        layer->runAction(CCScaleTo::create(0.5, 1));
        menu->setOpacity(0);
        dialogBack->setOpacity(0);
        menu->runAction(CCSequence::create(CCDelayTime::create(0.25),CCFadeIn::create(0.25),NULL));
        dialogBack->runAction(CCSequence::create(CCDelayTime::create(0.25),CCFadeIn::create(0.25),NULL));
        label->runAction(CCSequence::create(CCDelayTime::create(0.25),CCFadeIn::create(0.25),NULL));
        layer->setTag(surrenderDialogTag);
        this->addChild(layer,2);
    } 
}

void BattleScene::cancelSurrender() {
    this->getChildByTag(surrenderDialogTag)->removeFromParentAndCleanup(true);
}

void BattleScene::toFight(){
    if (isFighting == beforeFightTag) {
        CCLog("开战");
        lastTime = 240;
        char str[4] = {0};
        sprintf(str,"%d",lastTime);
        lastTimeLabel->setString(str);
        lastTimeLabel->setVisible(true);
        //TODO 结束战斗有时候会出错
        if (battleMap->getChildByTag(zhihuisuoTag) != NULL) {
            ((MyBattleState*)(((MyBattleBuilding*)battleMap->getChildByTag(zhihuisuoTag))->fsm->getCurrentState()))->getItem()->getChildByTag(battleTipTag)->removeFromParentAndCleanup(true);
            ((MyBattleState*)(((MyBattleBuilding*)battleMap->getChildByTag(zhihuisuoTag))->fsm->getCurrentState()))->getItem()->getChildByTag(battleTipAimTag)->removeFromParentAndCleanup(true);
            
            isFighting = fightingTag;
            CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("bgm_battleScene.mp3",true);
        } else {
            toVictory();
        }
        
        CCObject* obj;
        CCARRAY_FOREACH(battleMap->getChildren(), obj) {
            MyBattleBuilding* bd = dynamic_cast<MyBattleBuilding*>(obj);
            if (bd != NULL) {
                bd->removeChildByTag(levelFontTag, true);
                bd->removeChildByTag(nameFontTag, true);
            }
        }
        
        
        
        fightMenu->removeChildByTag(nextTag, true);
        
        CCMenuItemSprite* surrender = (CCMenuItemSprite*)fightMenu->getChildByTag(surrenderTag);
        
        CCSprite* sprite = CCSprite::create("surrender.png");
        sprite->setColor(ccGRAY);
        
        surrender->setNormalImage(CCSprite::create("surrender.png"));
        
        surrender->setSelectedImage(sprite);
        surrender->setPosition(ccp(60,winSize.height/4*3));
        surrender->setTarget(this,menu_selector(BattleScene::toSurrender));
        
    }
}

//void BattleScene::retain() {
//    CCScene::retain();
//}

void BattleScene::doPause() {
    if (isFighting == fightingTag) {
//        int robberOil = (int)(MyGameInfo::getInstance()->robberOil-enemyOilLabel->getTargetNumber());
//        int robberIron = (int) {MyGameInfo::getInstance()->robberIron-enemyIronLabel->getTargetNumber()};
//        CCLog("robberOil:%d,robberIron:%d",robberOil,robberIron);
//        MyHttpConnection::getInstance()->addMatch(false,robberOil,robberIron,MyJsonUtil::packBattleUnit(this->getChildByTag(bingzhongmenuTag)->getChildren()));
//        MyHttpConnection::getInstance()->updateBattleOtherData(MyJsonUtil::packAllBattleBuilding(battleMap->getChildren()));
//        MyHttpConnection::getInstance()->updateResource(PulsarNative::getDeviceId(), false);
        //todo 更新战斗照成影响胜利
        int robberOil = (int)(MyGameInfo::getInstance()->getRobberOil()-enemyOilLabel->getTargetNumber());
        int robberIron = (int) (MyGameInfo::getInstance()->getRobberIron()-enemyIronLabel->getTargetNumber());
        int costOil = 0;
        CCObject* obj;
        CCArray* bzarray =  this->getChildByTag(bingzhongmenuTag)->getChildren();
        CCARRAY_FOREACH(bzarray, obj) {
            MyDeployButton* button = dynamic_cast<MyDeployButton*>(obj);
            if(button->count > 0) {
                costOil += (MyUtil::getInstance()->updateLevelByRate(button->bean->creator->summaryOriOil,button->bean->creator->getSummaryOil(), button->bean->getLevel(), button->bean->creator->updateCostRate))*button->count;
            }
        }
        
        
        MyHttpConnection::getInstance()->sendUpdateBattleOtherData(MyJsonUtil::packAllBattleBuilding(battleMap->getChildren()),robberOil,robberIron);
        MyHttpConnection::getInstance()->sendUpdateResource(robberOil-costOil,robberIron,0);
        MyHttpConnection::getInstance()->sendAddMatchInfo(false,robberOil,robberIron,MyJsonUtil::packBattleUnit(this->getChildByTag(bingzhongmenuTag)->getChildren()),attackType);
        addMatchInfo(false);
    }
    toBuildScene();
}

void BattleScene::doResume() {
    CocosDenshion::SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}


CCLayer* BattleScene::getVictoryUI(bool isVictory) {
    isFighting = afterFightTag;
    CocosDenshion::SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
    CCLayer* victoryLayer = CCLayer::create();
    
    CCSprite* gray = CCSprite::create("whiteImage.jpg");
    gray->setScaleX(winSize.width/gray->getContentSize().width);
    gray->setScaleY(winSize.height/gray->getContentSize().height);
    gray->setPosition(ccp(winSize.width/2,winSize.height/2));
    gray->setColor(ccc3(0,0,0));
    gray->setOpacity(0);
//    CCSprite* victoryBack = CCSprite::createWithSpriteFrameName("victoryBack.png");
//    victoryBack->setScale(1.464);
//    victoryBack->setScaleY(1.600);
    CCSprite* victoryBack = MyUtil::getInstance()->getVictoryUIBack();
    victoryBack->setPosition(ccp(winSize.width/2,winSize.height/2-30));
    if (isVictory) {
        CCSprite* victoryIcon = CCSprite::createWithSpriteFrameName("victoryTitle.png");
        victoryIcon->setPosition(ccp(victoryBack->getContentSize().width/2,victoryBack->getContentSize().height+30));
        victoryIcon->setScale(1.5);
        victoryBack->addChild(victoryIcon);
        
        CCSprite* bling = CCSprite::createWithSpriteFrameName("bling.png");
        bling->setScale(2);
        bling->setPosition(ccp(winSize.width/2,winSize.height/2+80));
        bling->runAction(CCRepeatForever::create(CCRotateBy::create(50, 360)));
        victoryLayer->addChild(bling);
        CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sfx_win.mp3",false);
    } else {
        CCSprite* victoryIcon = CCSprite::createWithSpriteFrameName("loseTitle.png");
        victoryIcon->setPosition(ccp(victoryBack->getContentSize().width/2,victoryBack->getContentSize().height+30));
        victoryIcon->setScale(1.5);
        victoryBack->addChild(victoryIcon);
         CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sfx_lose.mp3",false);
    }
    
    this->addChild(gray,1);
    gray->runAction(CCFadeTo::create(0.2,203));
    
    victoryLayer->addChild(victoryBack);
    victoryLayer->setPosition(ccp(0,-winSize.height/2-victoryBack->getContentSize().height/2));
    
    CCMenuItemSprite* returnHomeButton = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("returnHomeButton.png"), CCSprite::createWithSpriteFrameName("returnHomeButtonP.png"),this,menu_selector(BattleScene::toBuildSceneWait));
    returnHomeButton->setPosition(ccp(-80,-160));
    
    CCMenuItemSprite* goFightButton = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("goFightButton.png"), CCSprite::createWithSpriteFrameName("goFightButtonP.png"),this,menu_selector(BattleScene::toNextWait));
    goFightButton->setPosition(ccp(80,-160));
    
    MyPriorityMenu* actionMenu = MyPriorityMenu::create(-510, returnHomeButton,goFightButton,NULL);
    actionMenu->setPosition(ccp(victoryBack->getContentSize().width/2,victoryBack->getContentSize().height/2));
    victoryBack->addChild(actionMenu);
    
    CCLabelTTF* robberLabel = CCLabelTTF::create("合计掠夺资源:", "Arial", 20);
    robberLabel->setAnchorPoint(ccp(0,0.5));
    robberLabel->setPosition(ccp(winSize.width/2-250,460));
    robberLabel->setColor(ccc3(237,219,138));
    victoryLayer->addChild(robberLabel,2);
    
    
    int robberOil = (int)(MyGameInfo::getInstance()->getRobberOil()-enemyOilLabel->getTargetNumber());
    int robberIron = (int) (MyGameInfo::getInstance()->getRobberIron()-enemyIronLabel->getTargetNumber());
    int robberGlory = isVictory?(int)(getVirtoryGloryFromEnemy*trophyRate):0;
    
    CCSprite* ironIcon = CCSprite::createWithSpriteFrameName("ironIcon.png");
    ironIcon->setScale(0.6);
    ironIcon->setPosition(ccp(winSize.width/2+44,430));
    CCSprite* line1 = CCSprite::createWithSpriteFrameName("underline.png");
    line1->setPosition(ccp(winSize.width/2,406));
    victoryLayer->addChild(line1);
    victoryLayer->addChild(ironIcon);
    char str[140] = {0};
    sprintf(str, "%d",robberIron);
    CCLabelAtlas* ironCount = CCLabelAtlas::create(str, "number6.png", 24, 36, '/');
    ironCount->setPosition(ccp(winSize.width/2+20,430));
    ironCount->setAnchorPoint(ccp(1,0.5));
    ironCount->setScale(0.7);
    ironCount->setColor(ccc3(231,219,138));
    victoryLayer->addChild(ironCount,2);
    
    CCSprite* oilIcon = CCSprite::createWithSpriteFrameName("oilIcon.png");
    oilIcon->setScale(0.6);
    oilIcon->setPosition(ccp(winSize.width/2+44,380));
    CCSprite* line2 = CCSprite::createWithSpriteFrameName("underline.png");
    line2->setPosition(ccp(winSize.width/2,356));
    victoryLayer->addChild(line2);
    victoryLayer->addChild(oilIcon);
    sprintf(str, "%d",robberOil);
    CCLabelAtlas* oilCount = CCLabelAtlas::create(str, "number7.png", 24, 36, '/');
    oilCount->setPosition(ccp(winSize.width/2+20,380));
    oilCount->setAnchorPoint(ccp(1,0.5));
    oilCount->setScale(0.7);
    victoryLayer->addChild(oilCount,2);
    
    CCSprite* honorIcon = CCSprite::createWithSpriteFrameName("honorIcon.png");
    honorIcon->setScale(0.6);
    honorIcon->setPosition(ccp(winSize.width/2+44,330));
    CCSprite* line3 = CCSprite::createWithSpriteFrameName("underline.png");
    line3->setPosition(ccp(winSize.width/2,306));
    victoryLayer->addChild(line3);
    victoryLayer->addChild(honorIcon);
    if (isVictory) {
        sprintf(str, "%d",(int)(getVirtoryGloryFromEnemy*trophyRate));
    } else {
        sprintf(str, "%d",0);
    }
    
    CCLabelAtlas* honorCount = CCLabelAtlas::create(str, "number6.png", 24, 36, '/');
    honorCount->setPosition(ccp(winSize.width/2+20,330));
    honorCount->setAnchorPoint(ccp(1,0.5));
    honorCount->setScale(0.7);
    honorCount->setColor(ccc3(231,219,138));
    victoryLayer->addChild(honorCount,2);
    
    if (isVictory) {
        MyGameInfo::getInstance()->setPower(MyGameInfo::getInstance()->getPower()+ Mathlib::bound(20*(MyGameInfo::getInstance()->enemyPower/MyGameInfo::getInstance()->getPower()),40,0));
    }
    
    
    CCLabelTTF* expendLabel = CCLabelTTF::create("派兵:", "Arial", 20);
    expendLabel->setPosition(ccp(winSize.width/2-250,280));
    expendLabel->setAnchorPoint(ccp(0,0.5));
    expendLabel->setColor(ccc3(237,219,138));
    victoryLayer->addChild(expendLabel,2);
    
    CCArray* bzarray =  this->getChildByTag(bingzhongmenuTag)->getChildren();
    CCObject* obj;
    int i = 0;
    int costOil = 0;
    CCLayer* bingzhongLayer = CCLayer::create();
    CCARRAY_FOREACH(bzarray, obj) {
        MyDeployButton* button = dynamic_cast<MyDeployButton*>(obj);
        if(button->count > 0) {
            sprintf(str, "deployBack%d.png",button->bean->creator->getRarity());
            CCSprite* sprite = CCSprite::createWithSpriteFrameName(str);
            sprintf(str, "%sbp.png",button->bean->creator->getSpriteFileName());
            CCSprite* bing = CCSprite::createWithSpriteFrameName(str);
            bing->setPosition(ccp(53,49));
            bing->setScale(Mathlib::min(115/bing->getContentSize().width, 90/bing->getContentSize().height));
            sprite->addChild(bing);
            sprite->setScale(0.7);
            
            sprite->setPosition(ccp(80*i,0));
            sprite->setAnchorPoint(ccp(0.5,1));
            
            sprintf(str, "/%d",button->count);
            CCLabelAtlas* unitCount = CCLabelAtlas::create(str, "number6.png", 24, 36, '/');
            unitCount->setAnchorPoint(ccp(0.5,1));
            unitCount->setScale(0.8);
            unitCount->setPosition(ccp(sprite->getContentSize().width/2,sprite->getContentSize().height));
            sprite->addChild(unitCount);
            bingzhongLayer->addChild(sprite);
            sprintf(str, "Lv:%d",button->bean->getLevel());
            costOil += (MyUtil::getInstance()->updateLevelByRate(button->bean->creator->summaryOriOil,button->bean->creator->getSummaryOil(), button->bean->getLevel(), button->bean->creator->updateCostRate))*button->count;
            
            
            CCLabelTTF* levelLabel = CCLabelTTF::create(str, "Arial", 25);
            levelLabel->setAnchorPoint(ccp(0,0));
            levelLabel->setPosition(ccp(10,5));
//            levelLabel->setColor(ccc3(200, 147, 45));
            sprite->addChild(levelLabel);
            i++;
        }
    }
    bingzhongLayer->setPosition(ccp(winSize.width/2 - ((i-1)*40),290));
    victoryLayer->addChild(bingzhongLayer);
    
    
    
    
    if (robberOil - costOil > 0) {
         sprintf(str, "%d",robberOil - costOil);
    } else {
         sprintf(str, "/%d",costOil - robberOil);
    }
   
    oilCount->setString(str);
    
    
    CCSprite* heidi = CCSprite::create("whiteImage.jpg");
//    CCLog("%f,%f",heidi->getContentSize().width,heidi->getContentSize().height);
    heidi->setColor(ccc3(0,0,0));
    heidi->setScaleX(531/heidi->getContentSize().width);
    heidi->setScaleY(64/heidi->getContentSize().height);
    heidi->setOpacity(150);
//    CCLog("%f,%f",heidi->getContentSize().width,heidi->getContentSize().height);
    MyMenuItem* bpItem = MyMenuItem::create(heidi, this, menu_selector(BattleScene::displayIME));
    bpItem->setPosition(ccp(0,-105));
    bpItem->setContentSize(CCSizeMake(531,64));
    actionMenu->addChild(bpItem);
    
//    
//    CCLabelTTF* notelabel = CCLabelTTF::create(str, "Arial", 22,CCSizeMake(545,100), kCCTextAlignmentLeft, kCCVerticalTextAlignmentTop);
//    notelabel->setColor(ccc3(254,185,0));
//    notelabel->setAnchorPoint(ccp(0,0.5));
//    notelabel->setPosition(ccp(winSize.width/2-267,winSize.height/2-155));
//    victoryLayer->addChild(notelabel);
   
//    m_TextField = CCTextFieldTTF::textFieldWithPlaceHolder(str,CCSizeMake(545,100), kCCTextAlignmentLeft,"Arial",22);
//    m_TextField->setColorSpaceHolder(ccc3(254,185,0));
//    m_TextField->setString(str);
//    m_TextField->setColor(ccc3(254,185,0));
    if (isVictory) {
        sprintf(str,"【点击此处更改留言】%s", CCUserDefault::sharedUserDefault()->getStringForKey("victoryNoteTag","你的基地就像纸糊的一样！！！").c_str());
        m_TextField->setPlaceHolder(str);
    }
    m_TextField->setPosition(ccp(winSize.width/2-267,winSize.height/2-155));
//    m_TextField->setAnchorPoint(ccp(0,0.5));
//    m_TextField->setDelegate(this);
    victoryLayer->addChild(m_TextField);
//    m_TextField->setTag(9999);
    
    victoryLayer->runAction(CCSequence::create(CCEaseElasticOut::create(CCMoveTo::create(0.5, ccp(0,0)), 1),NULL));
    
    
    GXShieldTouchMenuItem* shieldItem = GXShieldTouchMenuItem::create();
    shieldItem->setPosition(ccp(winSize.width/2,winSize.height/2));
    shieldItem->setContentSize(winSize);
    
    MyPriorityMenu* menu = MyPriorityMenu::create(-502,shieldItem,NULL);
    //    menu->runAction(CCFadeIn::create(2));
    //    menu->setOpacity(0);
    menu->setPosition(ccp(0,0));
    
    this->addChild(menu,9);
    
    //发送战斗结果消息
    BattleOverMessage::create(isVictory)->sendMsg();
    
    //todo 更新战斗照成影响胜利，战斗完成后立刻更新
    MyHttpConnection::getInstance()->sendUpdateBattleOtherData(MyJsonUtil::packAllBattleBuilding(battleMap->getChildren()),robberOil,robberIron);
    MyHttpConnection::getInstance()->sendUpdateResource(robberOil - costOil,robberIron,robberGlory);
    MyHttpConnection::getInstance()->sendAddMatchInfo(isVictory,robberOil,robberIron,MyJsonUtil::packBattleUnit(this->getChildByTag(bingzhongmenuTag)->getChildren()),attackType);
    
    return victoryLayer;
}

void BattleScene::addMatchInfo(bool victory) {
    
//    int robberOil = (int)(MyGameInfo::getInstance()->getRobberOil()-enemyOilLabel->getTargetNumber());
//    int robberIron = (int) (MyGameInfo::getInstance()->getRobberIron()-enemyIronLabel->getTargetNumber());
    CCString* note = NULL;
    if (strcmp(m_TextField->getString(),"") != 0) {
        note = CCString::create(m_TextField->getString());
//        CCLog("%d",note->length());
        if (note->length() < 119) {
            
            //        note->m_sString.substr(0,120);
            //        CCLog("after:%s",note->getCString());
            if (victory) {
                CCUserDefault::sharedUserDefault()->setStringForKey("victoryNoteTag",note->getCString());
            } else {
                CCUserDefault::sharedUserDefault()->setStringForKey("loseNoteTag",note->getCString());
            }
            CCUserDefault::sharedUserDefault()->flush();
        }  else {
            if (victory) {
                note = CCString::create(CCUserDefault::sharedUserDefault()->getStringForKey("victoryNoteTag","你的基地就像纸糊的一样！！！"));
            } else {
                note = CCString::create(CCUserDefault::sharedUserDefault()->getStringForKey("loseNoteTag","我还会回来的！！！"));
            }
        }
    } else {
        if (victory) {
            note = CCString::create(CCUserDefault::sharedUserDefault()->getStringForKey("victoryNoteTag","你的基地就像纸糊的一样！！！"));
        } else {
            note = CCString::create(CCUserDefault::sharedUserDefault()->getStringForKey("loseNoteTag","我还会回来的！！！"));
        }
    }
    
    MyHttpConnection::getInstance()->sendAddMatchNote(note);
    
    
//    this->removeChildByTag(waitMenuTag, true);
    
}

void BattleScene::loadResource() {
    GXUtil::loadResourceUtilSucc("battleui.plist","battleui.pvr.ccz");
    
    
    //    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("tank1.plist","tank1.pvr.ccz");
    //    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("bubing1.plist", "bubing1.pvr.ccz");
    GXUtil::loadResourceUtilSucc("collapse.plist","collapse.pvr.ccz");
    GXUtil::loadResourceUtilSucc("microboom1.plist","microboom1.pvr.ccz");
    GXUtil::loadResourceUtilSucc("boom.plist","boom.pvr.ccz");
    GXUtil::loadResourceUtilSucc("antitankBoom.plist","antitankBoom.png");
    GXUtil::loadResourceUtilSucc("antiTankF.plist","antiTankF.png");
    GXUtil::loadResourceUtilSucc("firelight.plist","firelight.pvr.ccz");
    GXUtil::loadResourceUtilSucc("gunlight.plist","gunlight.pvr.ccz");
    GXUtil::loadResourceUtilSucc("rockethead.plist","rockethead.pvr.ccz");
    GXUtil::loadResourceUtilSucc("rockettail.plist","rockettail.pvr.ccz");
    GXUtil::loadResourceUtilSucc("victoryui.plist","victoryui.pvr.ccz");
    
}

void BattleScene::releaseResource() {
    
    CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile("antiTankF.plist");
    CCTextureCache::sharedTextureCache()->removeTextureForKey("antiTankF.png");
    
    
    
    CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile("firelight.plist");
    CCTextureCache::sharedTextureCache()->removeTextureForKey("firelight.pvr.ccz");
    
    CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile("gunlight.plist");
    CCTextureCache::sharedTextureCache()->removeTextureForKey("gunlight.pvr.ccz");
    
    CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile("gunlight.plist");
    CCTextureCache::sharedTextureCache()->removeTextureForKey("gunlight.pvr.ccz");
    
    CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile("rockethead.plist");
    CCTextureCache::sharedTextureCache()->removeTextureForKey("rockethead.pvr.ccz");
    
    CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile("rockettail.plist");
    CCTextureCache::sharedTextureCache()->removeTextureForKey("rockettail.pvr.ccz");
    
//    CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile("tank1.plist");
//    CCTextureCache::sharedTextureCache()->removeTextureForKey("tank1.pvr.ccz");
//    CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile("bubing1.plist");
//    CCTextureCache::sharedTextureCache()->removeTextureForKey("bubing1.pvr.ccz");
    
    CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile("collapse.plist");
    CCTextureCache::sharedTextureCache()->removeTextureForKey("collapse.pvr.ccz");
    
    CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile("microboom1.plist");
    CCTextureCache::sharedTextureCache()->removeTextureForKey("microboom1.pvr.ccz");
    
    
    CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile("boom.plist");
    CCTextureCache::sharedTextureCache()->removeTextureForKey("boom.pvr.ccz");
    
    CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile("antitankBoom.plist");
    CCTextureCache::sharedTextureCache()->removeTextureForKey("antitankBoom.png");
    
    CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile("victoryui.plist");
    CCTextureCache::sharedTextureCache()->removeTextureForKey("victoryui.pvr.ccz");
    
    CCTextureCache::sharedTextureCache()->removeTextureForKey("battleTipArrow.png");
    CCTextureCache::sharedTextureCache()->removeTextureForKey("surrender.png");

//    CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile("victoryui.plist");
    GarbageResourceCollection::getInstance()->GarbageCollection();
    
//    CCTextureCache::sharedTextureCache()->dumpCachedTextureInfo();
}

void BattleScene::displayIME(cocos2d::CCNode *node) {
//    m_TextField->setString("");
    m_TextField->attachWithIME();
}

void BattleScene::countdown() {
    lastTime = lastTime-1;
    char str[4] = {0};
    sprintf(str,"%d",lastTime);
    lastTimeLabel->setString(str);
    if (lastTime <= 240) {
        if(lastTime == 0) {
            surrender();
            
        } else if (lastTime < 10) {
            lastTimeLabel->setColor(ccc3(255,0,0));
            lastTimeLabel->setScale(2.5);
            lastTimeLabel->runAction(CCScaleTo::create(0.2,2));
            CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sfx_countdown.mp3");
        } 
    } else if (lastTime == 270) {
        lastTimeLabel->setVisible(true);
    } else if (lastTime == 241) {
        toFight();
    }
}
