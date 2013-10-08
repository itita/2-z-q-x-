//
//  DefendScene.cpp
//  ww4
//
//  Created by xiao tang on 13-6-10.
//
//

#include "DefendScene.h"
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
#include "DefendOverMessage.h"
#include "GXRemoveFromParentsAction.h"
#include "GXAntiCrack.h"


#define getVirtoryGloryFromEnemy MyUtil::getInstance()->getVirtoryGloryFromEnemy(MyGameInfo::getInstance()->enemyPower)

#define prizeBoxMenuTag 1000
#define victoryLayerTag 1001
#define victoryBackTag 1002
#define bling1_1Tag 1
#define bling1_2Tag 2


DefendScene* DefendScene::create(cocos2d::CCArray *buildings,CCString* attackerAvatar) {
    DefendScene *pRet = new DefendScene();
    //    pRet->loadResource();
    pRet->trophyRate = 0;
    if (pRet && pRet->init(buildings))
    {
        pRet->autorelease();
        pRet->initUI(attackerAvatar);
        return pRet;
    }
    else
    {
        CC_SAFE_DELETE(pRet);
        return NULL;
    }
}

DefendScene* DefendScene::create() {
    DefendScene *pRet = new DefendScene();
    //    pRet->loadResource();
    pRet->trophyRate = 0;
    if (pRet)
    {
        pRet->autorelease();
        return pRet;
    }
    else
    {
        CC_SAFE_DELETE(pRet);
        return NULL;
    }
}

bool DefendScene::init(cocos2d::CCArray *buildings) {
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
    
    
    
    CCObject* obj;
    
    CCArray* antiArray =CCArray::create();
    CCARRAY_FOREACH(buildings, obj) {
        BuildingBean* bean = dynamic_cast<BuildingBean*>(obj);
        if (bean->tag == -1) {
            CCLog("日扯");
        }
        MyBattleBuilding* building = MyGameFactory::createBattleBuildingByBean(bean, this,false);
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
    }
    
    MyBattleBuilding* zhihuisuo =  (MyBattleBuilding*)battleMap->getChildByTag(zhihuisuoTag);
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
    }
    
    battleMap->setTag(MainMapTag);
    battleMap->displayTip();
    
    
    battleMap->centerView();
    this->addChild(battleMap);
    this->scheduleOnce(schedule_selector(DefendScene::startAttack),4.3);
    return true;
}

bool DefendScene::init() {
    return true;
}


void DefendScene::initUI(CCString* attackerAvatar) {
    CCLayer* uiLayer = CCLayer::create();
    
    CCSprite* avatar =CCSprite::createWithSpriteFrameName("avatar.png");
    avatar->setAnchorPoint(ccp(0,1));
    avatar->setPosition(ccp(0,winSize.height));
    
    CCSprite* avatarSprite =CCSprite::createWithSpriteFrameName(attackerAvatar->getCString());
    avatarSprite->setAnchorPoint(ccp(0,0));
    avatarSprite->setScale(Mathlib::min(80/avatarSprite->getContentSize().width,80/avatarSprite->getContentSize().height));
    avatarSprite->setPosition(ccp(0,10));
    avatar->addChild(avatarSprite);
    
    
    
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
    
    if (MyGameInfo::getInstance()->getUnionBean()->getName()->compare("") != 0) {
        CCSprite* unionBack = CCSprite::createWithSpriteFrameName("unionAvatar.png");
        unionBack->setFlipX(true);
        unionBack->setAnchorPoint(ccp(1,0.5));
        unionBack->setPosition(ccp(avatarAverse->getContentSize().width,-17));
        CCLabelTTF* namelabel = CCLabelTTF::create(MyGameInfo::getInstance()->getUnionBean()->getName()->getCString(),"Arial",19);
        namelabel->setAnchorPoint(ccp(0.5,0.5));
        namelabel->setPosition(ccp(unionBack->getContentSize().width-102,unionBack->getContentSize().height/2));
        CCSprite* emblem = CCSprite::createWithSpriteFrameName(MyGameInfo::getInstance()->getUnionBean()->getEmblem()->getCString());
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
    nickName->setPosition(ccp(winSize.width -139,winSize.height-3));
#endif
#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    nickName->setPosition(ccp(winSize.width -139,winSize.height));
#endif
    
    CCLabelTTF* rankName = CCLabelTTF::create(MyUtil::getInstance()->getRankString(MyGameInfo::getInstance()->getPower()), "Arial", 20);
    uiLayer->addChild(rankName,2);
    rankName->setAnchorPoint(ccp(1,0.5));
    rankName->setPosition(ccp(winSize.width -120,winSize.height-44));
    rankName->setColor(ccWHITE);
    
    CCSprite* rankSprite = MyUtil::getInstance()->getRankSprite(MyGameInfo::getInstance()->getPower());
    rankSprite->setPosition(ccp(winSize.width -100,winSize.height-44));
    rankSprite->setScale(0.50);
    uiLayer->addChild(rankSprite,2);
    
    CCLabelTTF* enemyNickName = MyUtil::getInstance()->getVipColorLabel(MyGameInfo::getInstance()->getEnemyNickname()->getCString(),18,0);
    enemyNickName->setAnchorPoint(ccp(0.5,1));
#if(CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    enemyNickName->setPosition(ccp(139,winSize.height-3));
#endif
#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    enemyNickName->setPosition(ccp(139,winSize.height));
#endif
    
    CCLabelTTF* enemyRankName = CCLabelTTF::create(MyUtil::getInstance()->getRankString(MyGameInfo::getInstance()->enemyPower), "Arial", 20);
    uiLayer->addChild(enemyRankName,2);
    enemyRankName->setAnchorPoint(ccp(0,0.5));
    enemyRankName->setPosition(ccp(120,winSize.height-44));
    enemyRankName->setColor(ccWHITE);
    
    CCSprite* enemyRankSprite = MyUtil::getInstance()->getRankSprite(MyGameInfo::getInstance()->enemyPower);
    enemyRankSprite->setPosition(ccp(100,winSize.height-44));
    enemyRankSprite->setScale(0.50);
    uiLayer->addChild(enemyRankSprite,2);
    
    
    
//    CCSprite* surrender = CCSprite::createWithSpriteFrameName("backToBuild.png");
//    CCSprite* gysurrender = CCSprite::createWithSpriteFrameName("backToBuild.png");
//    gysurrender->setColor(ccGRAY);
//    
//    CCMenuItemSprite* surrenderItem = CCMenuItemSprite::create(surrender, gysurrender, this, menu_selector(DefendScene::toBuildScene));
//    surrenderItem->setPosition(ccp(100,winSize.height/3));
//    //    surrender->setVisible(false);
//    surrenderItem->setTag(surrenderTag);
//    
//    fightMenu = CCMenu::create(surrenderItem,NULL);
//    fightMenu->setPosition(ccp(0,0));
    
    CCSprite* resourseBar = CCSprite::createWithSpriteFrameName("resourseBar.png");
    resourseBar->setScale(1.25);
    resourseBar->setAnchorPoint(ccp(0.5,1));
    resourseBar->setPosition(ccp(winSize.width/2,winSize.height));
    resourseBar->setTag(resourceBarTag);
    
    CCLabelAtlas* oilLabel = MyGameInfo::getInstance()->getOilAtlas();
    oilLabel->setPosition(ccp(26,6));
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
    
    CCSprite* defendLabel = CCSprite::createWithSpriteFrameName("defendLabel.png");
    defendLabel->setPosition(ccp(winSize.width/2,winSize.height/2));
    defendLabel->setScale(2);
    defendLabel->runAction(CCSequence::create(CCDelayTime::create(1.5),CCFadeTo::create(0.5,0),GXRemoveFromParentsAction::create(),NULL));
    
    CCSprite* warningBack = CCSprite::create("whiteImage.jpg");
    warningBack->setScaleX(winSize.width/warningBack->getContentSize().width);
    warningBack->setScaleY(300/warningBack->getContentSize().height);
    warningBack->setPosition(ccp(winSize.width/2,winSize.height/2));
    warningBack->setColor(ccc3(0,0,0));
    warningBack->setOpacity(125);
    warningBack->runAction(CCSequence::create(CCDelayTime::create(1.5),CCFadeTo::create(0.5,0),GXRemoveFromParentsAction::create(),NULL));
    CCSprite* light1 = CCSprite::createWithSpriteFrameName("tipWarningLight.png");
    light1->setScale(4);
    light1->setAnchorPoint(ccp(0.5,0));
    light1->setPosition(ccp(-light1->getContentSize().width,winSize.height/2-150));
    light1->runAction(CCSequence::create(CCDelayTime::create(0.5), CCMoveBy::create(1,ccp(winSize.width+light1->getContentSize().width,0)),CCFadeOut::create(0.5),GXRemoveFromParentsAction::create(),NULL));
    
    CCSprite* light2 = CCSprite::createWithSpriteFrameName("tipWarningLight.png");
    light2->setScale(4);
    light2->setAnchorPoint(ccp(0.5,0));
    light2->setRotation(180);
    light2->setPosition(ccp(winSize.width,winSize.height/2+150));
    light2->runAction(CCSequence::create(CCDelayTime::create(0.5), CCMoveBy::create(1,ccp(-winSize.width+light1->getContentSize().width,0)),CCFadeOut::create(0.5),GXRemoveFromParentsAction::create(), NULL));
    
    enemyOilLabel = MyAtlasNumber::create();
    enemyOilLabel->setVisible(false);
    enemyIronLabel = MyAtlasNumber::create();
    enemyIronLabel->setVisible(false);
    
    
    uiLayer->addChild(avatar);
    uiLayer->addChild(avatarAverse);
    uiLayer->addChild(enemyNickName);
    uiLayer->addChild(nickName);
    
    uiLayer->addChild(warningBack);
    uiLayer->addChild(light1);
    uiLayer->addChild(light2);
    uiLayer->addChild(defendLabel);
    
    this->addChild(enemyOilLabel);
    this->addChild(enemyIronLabel);
    this->addChild(resourseBar,2);
    
    
    //    UnitCreator* tankCreator = UnitCreator::create(tankCreatorTag,CCString::create("tank1"),CCString::create("sfx_deployTank.m4a"),CCString::create("sfx_paoji.m4a"),tankBaseSpeed,tankBaseRange,tankBaseDamage,tankBaseHealth,tankBaseCost);
    //    CCObject* obj = NULL;
    //    char str[30] = {0};
    
    
    
    
    
    //    char* str =
    //    MyJsonUtil::parseBuildingFromJson(str);
    getBaseLoc();
    CCPoint mapLoc;
    
    if (attackerDirection == attackLD) {
        for (int i = 0; i<3; i++) {
            CCSprite* concentPoint = CCSprite::createWithSpriteFrameName("enemyConcentricPoint.png");
            concentPoint->setPosition(battleMap->transTiledToMap(ccp(25+i*5,baseLoc+1)));
            battleMap->CCNode::addChild(concentPoint,999999);
//            battleMap->runAction(CCMoveTo::create(2,ccp(-244,-1613)));
        }
       mapLoc = battleMap->transTiledToMap(ccp(30,baseLoc));
    } else if(attackerDirection == attackLU) {
        for (int i = 0; i<3; i++) {
            CCSprite* concentPoint = CCSprite::createWithSpriteFrameName("enemyConcentricPoint.png");
            concentPoint->setPosition(battleMap->transTiledToMap(ccp(baseLoc-1,25+i*5)));
            battleMap->CCNode::addChild(concentPoint,999999);
        }
       mapLoc = battleMap->transTiledToMap(ccp(baseLoc,30));
    } else if(attackerDirection == attackRU) {
        for (int i = 0; i<3; i++) {
            CCSprite* concentPoint = CCSprite::createWithSpriteFrameName("enemyConcentricPoint.png");
            concentPoint->setPosition(battleMap->transTiledToMap(ccp(25+i*5,baseLoc-2)));
            battleMap->CCNode::addChild(concentPoint,999999);
        }
       mapLoc = battleMap->transTiledToMap(ccp(30,baseLoc));
    } else if(attackerDirection == attackRD) {
        for (int i = 0; i<3; i++) {
            CCSprite* concentPoint = CCSprite::createWithSpriteFrameName("enemyConcentricPoint.png");
            concentPoint->setPosition(battleMap->transTiledToMap(ccp(baseLoc+1,25+i*5)));
            battleMap->CCNode::addChild(concentPoint,9999999);
        }
        mapLoc = battleMap->transTiledToMap(ccp(baseLoc,30));
    }
    float x = -mapLoc.x+battleMap->getViewSize().width/2;
    float y = -mapLoc.y+battleMap->getViewSize().height/2;
    battleMap->runAction(CCSequence::create(CCDelayTime::create(2),CCEaseInOut::create(CCMoveTo::create(2,ccp(x,y)),2),NULL));
    addChild(uiLayer,1);
}

void DefendScene::callback1(cocos2d::CCObject *pSender) {
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sfx_click.mp3");
    battleMap->setCurrentDeployButton(((MyDeployButton*)pSender));
}

void DefendScene::toVictory() {
    if(!isVictory) {
        //把自己推了肯定就输了啊
        isVictory = true;
    } else {
        return;
    }
    isFighting = afterFightTag;
    this->scheduleOnce(schedule_selector(DefendScene::surrender),0);
}

void DefendScene::toBuildSceneWait(CCMenuItem* item) {
    if (item) {
        item->setEnabled(false);
    }
//    addMatchInfo(isVictory);
    
    toBuildScene();
    //    this->runAction(CCSequence::create(CCDelayTime::create(0.5),CCCallFuncND::create(this, callfuncND_selector(BattleScene::addMatchInfo), (void*)isVictory),CCCallFunc::create(this, callfunc_selector(BattleScene::toBuildScene)),NULL));
    
    //    scheduleOnce(schedule_selector(BattleScene::toBuildScene), 0.5);
}


void DefendScene::toBuildScene() {
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



void DefendScene::surrender() {
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
    this->unschedule(schedule_selector(DefendScene::deployUnit));
    this->addChild(getVictoryUI(false),3);
}


void DefendScene::toSurrender() {
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
        
        CCMenuItemSprite* sureItem = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("dialogsure.png"), CCSprite::createWithSpriteFrameName("dialogsurep.png"), this, menu_selector(DefendScene::surrender));
        
        
        CCMenuItemSprite* cancelItem =CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("dialogcancel.png"), CCSprite::createWithSpriteFrameName("dialogcancelp.png"),this,menu_selector(DefendScene::cancelSurrender));
        
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
        this->addChild(layer);
    }
}

void DefendScene::cancelSurrender() {
    this->getChildByTag(surrenderDialogTag)->removeFromParentAndCleanup(true);
}

void DefendScene::toFight(){
    if (isFighting == beforeFightTag) {
        CCLog("开战");
        //TODO 结束战斗有时候会出错
        if (battleMap->getChildByTag(zhihuisuoTag) != NULL) {
            ((MyBattleState*)(((MyBattleBuilding*)battleMap->getChildByTag(zhihuisuoTag))->fsm->getCurrentState()))->getItem()->getChildByTag(battleTipTag)->removeFromParentAndCleanup(true);
            ((MyBattleState*)(((MyBattleBuilding*)battleMap->getChildByTag(zhihuisuoTag))->fsm->getCurrentState()))->getItem()->getChildByTag(battleTipAimTag)->removeFromParentAndCleanup(true);
            
            isFighting = fightingTag;
            CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("bgm_battleScene.mp3",true);
        } else {
            toVictory();
        }
        
//        CCObject* obj;
//        CCARRAY_FOREACH(battleMap->getChildren(), obj) {
//            MyBattleBuilding* bd = dynamic_cast<MyBattleBuilding*>(obj);
//            if (bd != NULL) {
//                bd->removeChildByTag(levelFontTag, true);
//                bd->removeChildByTag(nameFontTag, true);
//            }
//        }
        
        
        
        CCSprite* sprite = CCSprite::create("surrender.png");
        sprite->setColor(ccGRAY);
        
        
        CCMenuItemSprite* surrender = CCMenuItemSprite::create(CCSprite::create("surrender.png"),sprite,this,menu_selector(BattleScene::toSurrender));
        
        surrender->setPosition(ccp(60,winSize.height/4*3));
        
        MyPriorityMenu* surrenderMenu = MyPriorityMenu::create(-510,surrender,NULL);
        surrenderMenu->setPosition(ccp(0,0));
        
        this->addChild(surrenderMenu);
    }
}

void DefendScene::doPause() {
    if (isFighting == fightingTag) {
        //        int robberOil = (int)(MyGameInfo::getInstance()->robberOil-enemyOilLabel->getTargetNumber());
        //        int robberIron = (int) {MyGameInfo::getInstance()->robberIron-enemyIronLabel->getTargetNumber()};
        //        CCLog("robberOil:%d,robberIron:%d",robberOil,robberIron);
        //        MyHttpConnection::getInstance()->addMatch(false,robberOil,robberIron,MyJsonUtil::packBattleUnit(this->getChildByTag(bingzhongmenuTag)->getChildren()));
        //        MyHttpConnection::getInstance()->updateBattleOtherData(MyJsonUtil::packAllBattleBuilding(battleMap->getChildren()));
        //        MyHttpConnection::getInstance()->updateResource(PulsarNative::getDeviceId(), false);
//        addMatchInfo(false);
    }
    if (isFighting == afterFightTag) {
        toBuildSceneWait(NULL);
    } else if(isFighting == beforeFightTag) {
        //    	toReturnHomeWait();
        toBuildScene();
    } else {
        surrender();
    }
}

void DefendScene::doResume() {
    CocosDenshion::SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}


CCLayer* DefendScene::getVictoryUI(bool isVictory) {
    isFighting = afterFightTag;
    CocosDenshion::SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
    CCLayer* victoryLayer = CCLayer::create();
    victoryLayer->setTag(victoryLayerTag);
    char str[100] = {0};
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
    victoryBack->setTag(victoryBackTag);
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
        completeRate = 1;
    } else {
        CCSprite* victoryIcon = CCSprite::createWithSpriteFrameName("loseTitle.png");
        victoryIcon->setPosition(ccp(victoryBack->getContentSize().width/2,victoryBack->getContentSize().height+30));
        victoryIcon->setScale(1.5);
        victoryBack->addChild(victoryIcon);
        CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sfx_lose.mp3",false);
        CCObject* obj;
        CCARRAY_FOREACH(battleMap->getUnits(),obj) {
            MyUnit* unit = (MyUnit*)obj;
            for (int i=0; i<attackerCreatorInfoBeanList->count(); i++) {
                CreatorInfoBean* infoBean = (CreatorInfoBean*)attackerCreatorInfoBeanList->objectAtIndex(i);
                if (infoBean->creator->cardId == unit->getTag() && infoBean->getLevel() == unit->getLevel()) {
                    attackDeployCountList[i] = attackDeployCountList[i]-1;
                }
            }
        }
        float max = 0;
        float now = 0;
        for (int i=0; i<attackerCreatorInfoBeanList->count(); i++) {
            CreatorInfoBean* infoBean = (CreatorInfoBean*)attackerCreatorInfoBeanList->objectAtIndex(i);
            int deployMax = ((GXintValue*)attackerCountList->objectAtIndex(i))->getValue();
            now += attackDeployCountList[i]*infoBean->getLevel()*(infoBean->creator->getRarity())*(infoBean->creator->getRarity());
            max += deployMax*infoBean->getLevel()*(infoBean->creator->getRarity())*(infoBean->creator->getRarity());
        }
        completeRate = Mathlib::max(now/max,0);
        
    }
    
    sprintf(str,"拦截完成度：%%%.1f",(completeRate*100));
    CCLabelTTF* completeRateLabel = CCLabelTTF::create(str,"Arial",20);
    completeRateLabel->setPosition(ccp(winSize.width/2+250,335));
    completeRateLabel->setAnchorPoint(ccp(1,0.5));
    completeRateLabel->setColor(ccc3(237,219,138));
    victoryLayer->addChild(completeRateLabel,2);
    
    this->addChild(gray,1);
    gray->runAction(CCFadeTo::create(0.2,203));
    
    victoryLayer->addChild(victoryBack);
    victoryLayer->setPosition(ccp(0,-winSize.height/2-victoryBack->getContentSize().height/2));
    
    
    MyPriorityMenu* prizeBoxMenu = MyPriorityMenu::create(-510,NULL);
    prizeBoxMenu->setPosition(ccp(victoryBack->getContentSize().width/2,victoryBack->getContentSize().height/2));
    prizeBoxMenu->setTag(prizeBoxMenuTag);
    victoryBack->addChild(prizeBoxMenu);
    
    for (int k=0; k<3; k++) {
        CCSprite* boxUp = CCSprite::createWithSpriteFrameName("prizeBox.png");
        CCSprite* boxClose = CCSprite::createWithSpriteFrameName("prizeBoxClose.png");
        boxClose->setPosition(ccp(boxUp->getContentSize().width/2,boxUp->getContentSize().height/2));
        boxUp->addChild(boxClose);
        CCSprite* boxDown = CCSprite::createWithSpriteFrameName("prizeBox.png");
        CCSprite* boxOpen = CCSprite::createWithSpriteFrameName("prizeBoxOpen.png");
        boxOpen->setPosition(ccp(boxDown->getContentSize().width/2,boxDown->getContentSize().height/2));
        boxDown->addChild(boxOpen);
        
        CCMenuItemSprite* boxButton = CCMenuItemSprite::create(boxUp, boxDown,this,menu_selector(DefendScene::getBoxPrize));
        boxButton->setPosition(ccp(-150+k*150,-60));
        boxButton->setScale(0.8);
        boxButton->runAction(CCRepeatForever::create(static_cast<CCSequence*>(CCSequence::create(CCScaleTo::create(0.25, 0.78), CCScaleTo::create(0.25,0.8),NULL) )));
        boxButton->setTag(k);
        
        CCSprite* bling1_1 = CCSprite::create("armyprizeLight.png");
        bling1_1->setPosition(ccp(boxButton->getContentSize().width/2,boxButton->getContentSize().height/2));
        bling1_1->setScale(1);
        bling1_1->runAction(CCRepeatForever::create(CCRotateBy::create(1000, 7200)));
        boxButton->addChild(bling1_1,-1);
        bling1_1->setTag(bling1_1Tag);
        
        CCSprite* bling1_2 = CCSprite::create("armyprizeLight.png");
        bling1_2->setPosition(ccp(boxButton->getContentSize().width/2,boxButton->getContentSize().height/2));
        bling1_2->runAction(CCRepeatForever::create(CCRotateBy::create(1000, -7200)));
        bling1_2->setScale(0.8);
        boxButton->addChild(bling1_2,-1);
        bling1_2->setTag(bling1_2Tag);
        
        prizeBoxMenu->addChild(boxButton);
    }
    
    CCLabelTTF* expendLabel = CCLabelTTF::create("歼灭敌军:", "Arial", 20);
    expendLabel->setPosition(ccp(winSize.width/2-250,450));
    expendLabel->setAnchorPoint(ccp(0,0.5));
    expendLabel->setColor(ccc3(237,219,138));
    victoryLayer->addChild(expendLabel,2);
    
    
    CCObject* obj;
    int i = 0;
    int j = 0;
    CCLayer* bingzhongLayer = CCLayer::create();
    CCARRAY_FOREACH(attackerCreatorInfoBeanList, obj) {
        CreatorInfoBean* bean = (CreatorInfoBean*)(obj);
//        if(attackDeployCountList[j] > 0) {
            sprintf(str, "deployBack%d.png",bean->creator->getRarity());
            CCSprite* sprite = CCSprite::createWithSpriteFrameName(str);
            sprintf(str, "%sbp.png",bean->creator->getSpriteFileName());
            CCSprite* bing = CCSprite::createWithSpriteFrameName(str);
            bing->setPosition(ccp(53,49));
            bing->setScale(Mathlib::min(115/bing->getContentSize().width, 90/bing->getContentSize().height));
            sprite->addChild(bing);
            sprite->setScale(0.7);
            
            sprite->setPosition(ccp(80*i,0));
            sprite->setAnchorPoint(ccp(0.5,1));
            
            sprintf(str, "/%d",attackDeployCountList[j]);
            CCLabelAtlas* unitCount = CCLabelAtlas::create(str, "number6.png", 24, 36, '/');
            unitCount->setAnchorPoint(ccp(0.5,1));
            unitCount->setScale(0.8);
            unitCount->setPosition(ccp(sprite->getContentSize().width/2,sprite->getContentSize().height));
            sprite->addChild(unitCount);
            bingzhongLayer->addChild(sprite);
            sprintf(str, "Lv:%d",bean->getLevel());
            
            CCLabelTTF* levelLabel = CCLabelTTF::create(str, "Arial", 25);
            levelLabel->setAnchorPoint(ccp(0,0));
            levelLabel->setPosition(ccp(10,5));
            //            levelLabel->setColor(ccc3(200, 147, 45));
            sprite->addChild(levelLabel);
            i++;
//        }
        j++;
    }
    bingzhongLayer->setPosition(ccp(winSize.width/2 - ((i-1)*40),420));
    victoryLayer->addChild(bingzhongLayer);
    
    
    CCSprite* line1 = CCSprite::createWithSpriteFrameName("underline.png");
    line1->setPosition(ccp(winSize.width/2,320));
    line1->setScaleX(1.5);
    victoryLayer->addChild(line1);
    
    
    
    
    victoryLayer->runAction(CCSequence::create(CCEaseElasticOut::create(CCMoveTo::create(0.5, ccp(0,0)), 1),NULL));
    
    
    GXShieldTouchMenuItem* shieldItem = GXShieldTouchMenuItem::create();
    shieldItem->setPosition(ccp(winSize.width/2,winSize.height/2));
    shieldItem->setContentSize(winSize);
    
    MyPriorityMenu* menu = MyPriorityMenu::create(-502,shieldItem,NULL);
    //    menu->runAction(CCFadeIn::create(2));
    //    menu->setOpacity(0);
    menu->setPosition(ccp(0,0));
    
    this->addChild(menu,9);
    
    //发送防御结果消息
    DefendOverMessage::create(isVictory)->sendMsg();
// 更新自己的基地
    MyHttpConnection::getInstance()->sendUpdateDefendGameData(MyJsonUtil::packAllBattleBuilding(battleMap->getChildren()));
    MyHttpConnection::getInstance()->sendFinishCPUWar(cpuWarLevel,isVictory);
    
    return victoryLayer;
}

void DefendScene::addDefendInfo(bool victory) {
    
    
//    MyHttpConnection::getInstance()->sendAddMatchInfo(victory,robberOil,robberIron,MyJsonUtil::packBattleUnit(this->getChildByTag(bingzhongmenuTag)->getChildren()),note);
//    
//    //todo 更新胜利
//    
//    MyHttpConnection::getInstance()->sendUpdateBattleOtherData(MyJsonUtil::packAllBattleBuilding(battleMap->getChildren()));
//    MyHttpConnection::getInstance()->sendUpdateResource(CCString::create(PulsarNative::getItitaId()));
//    if (victory) {
//        MyGameInfo::getInstance()->setPower(MyGameInfo::getInstance()->getPower()+ Mathlib::bound(20*(MyGameInfo::getInstance()->enemyPower/MyGameInfo::getInstance()->getPower()),40,0));
//    }
//    this->removeChildByTag(waitMenuTag, true);
    
}

void DefendScene::loadResource() {
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

void DefendScene::releaseResource() {
//    CCObject* obj;
//    CCARRAY_FOREACH(attackerCreatorInfoBeanList,obj) {
//        CreatorInfoBean* bean = (CreatorInfoBean*)obj;
//        char str[30] = {0};
//        
//        sprintf(str, "%s.plist",bean->creator->getSpriteFileName());
//        CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile(str);
//        
//        sprintf(str, "%s.pvr.ccz",bean->creator->getSpriteFileName());
//        CCTextureCache::sharedTextureCache()->removeTextureForKey(str);
//    }
    
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
    
    CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile("defend.plist");
    CCTextureCache::sharedTextureCache()->removeTextureForKey("defend.pvr.ccz");
    
    CCTextureCache::sharedTextureCache()->removeTextureForKey("battleTipArrow.png");
    CCTextureCache::sharedTextureCache()->removeTextureForKey("surrender.png");
    
    GarbageResourceCollection::getInstance()->GarbageCollection();
    //    CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile("victoryui.plist");
//    CCTextureCache::sharedTextureCache()->dumpCachedTextureInfo();
}

void DefendScene::startAttack() {
    toFight();
    this->schedule(schedule_selector(DefendScene::deployUnit), 0.1);
}

void DefendScene::deployUnit() {
    bool flag = true;
    for (int i=0; i<attackerCreatorInfoBeanList->count(); i++) {
        if (deployTime >= ((GXintValue*)attackerTimeList->objectAtIndex(i))->getValue()) {
            int deployMax = ((GXintValue*)attackerCountList->objectAtIndex(i))->getValue();
            int deployCount = attackDeployCountList[i];
            if (deployMax-deployCount > 0) {
                CreatorInfoBean* infoBean = (CreatorInfoBean*)attackerCreatorInfoBeanList->objectAtIndex(i);
                MyUnit* unit = infoBean->creator->createObj(infoBean->getLevel());
                unit->setTag(infoBean->creator->cardId);
                unit->cost = attackerSummaryList[i];
                if (deployTime == ((GXintValue*)attackerTimeList->objectAtIndex(i))->getValue()) {
                    CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(infoBean->creator->sfxDeployNameString.c_str());
                }
                attackDeployCountList[i] = deployCount+1;
                CCPoint posi;
                if (attackerDirection == attackLD) {
                    float random1 = ((float)(arc4random()%2000))/100.0;
                    float random2 = ((float)(arc4random()%200))/100.0;
                    posi = ccp(20+random1,baseLoc-random2);
                } else if(attackerDirection == attackLU) {
                    float random1 = ((float)(arc4random()%200))/100.0;
                    float random2 = ((float)(arc4random()%2000))/100.0;
                    posi = ccp(baseLoc+2.5-random1,20+random2);
                } else if(attackerDirection == attackRD) {
                    float random1 = ((float)(arc4random()%200))/100.0;
                    float random2 = ((float)(arc4random()%2000))/100.0;
                    posi = ccp(baseLoc-random1,20+random2);
                } else if(attackerDirection == attackRU) {
                    float random1 = ((float)(arc4random()%2000))/100.0;
                    float random2 = ((float)(arc4random()%200))/100.0;
                    posi = ccp(20+random1,baseLoc+random2);
                }
                unit->setPosition(battleMap->transTiledToMap(posi));
                unit->deployPosi = posi;
                
                battleMap->CCNode::addChild(unit,999999);
                battleMap->getUnits()->addObject(unit);
                unit->doAI();
                flag = false;
            }
        } else {
            flag = false;
        }
        
    }
    if (flag) {
        this->unschedule(schedule_selector(DefendScene::deployUnit));
        this->schedule(schedule_selector(DefendScene::checkVictory),3);
    }
    deployTime++;
}

void DefendScene::getBoxPrize(CCMenuItem* item) {
    CCArray* boxs = this->getChildByTag(victoryLayerTag)->getChildByTag(victoryBackTag)->getChildByTag(prizeBoxMenuTag)->getChildren();
    CCObject* obj;
    CCARRAY_FOREACH(boxs,obj) {
        CCMenuItemSprite* box = (CCMenuItemSprite*)obj;
        box->setEnabled(false);
        if (box == item) {
            box->setUserData((void*)1);
            box->runAction(CCScaleTo::create(0.1,0.9));
            openBox(box);
            box->stopAllActions();
            CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sfx_updateBuilding.mp3");
        } else {
            box->stopAllActions();
            box->setScale(0.8);
            box->setUserData((void*)0);
            box->runAction(CCSequence::create(CCScaleTo::create(1,0.7),CCCallFuncO::create(this, callfuncO_selector(DefendScene::openBox),box),NULL));
            box->removeChildByTag(bling1_1Tag,true);
            box->removeChildByTag(bling1_2Tag,true);
            
        }
    }
    CCMenuItemSprite* returnHomeButton = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("returnHomeButton.png"), CCSprite::createWithSpriteFrameName("returnHomeButtonP.png"),this,menu_selector(DefendScene::toBuildSceneWait));
    returnHomeButton->runAction(CCSequence::create(CCScaleTo::create(0.1, 1.15), CCScaleTo::create(0.1, 1.0),NULL));
    returnHomeButton->setPosition(ccp(0,-165));
    item->getParent()->addChild(returnHomeButton);
}

void DefendScene::openBox(CCMenuItemSprite* box) {
    CCSprite* boxDown = CCSprite::createWithSpriteFrameName("prizeBox.png");
    CCSprite* boxOpen = CCSprite::createWithSpriteFrameName("prizeBoxOpen.png");
    boxOpen->setPosition(ccp(boxDown->getContentSize().width/2,boxDown->getContentSize().height/2));
    boxDown->addChild(boxOpen);
    box->setNormalImage(boxDown);
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sfx_pickup.wav");
    int flag =(int) box->getUserData();
    int tag = box->getTag();
    char str[20] = {0};
    long prizeOil =0;
    long prizeIron =0;
    long prizeGlory =0;
    for (int i=0; i<prizeBoxTagList[tag]->count(); i++) {
        int resourceTag = ((GXintValue*)prizeBoxTagList[tag]->objectAtIndex(i))->getValue();
        int resourceCount = ((GXintValue*)prizeBoxCountList[tag]->objectAtIndex(i))->getValue()*completeRate;
        CCSprite* icon = MyUtil::getInstance()->getResourceIcon(resourceTag);
        icon->setPosition(ccp(box->getContentSize().width/2-80,120+i*50));
        icon->setScale(Mathlib::min(45/icon->getContentSize().width,45/icon->getContentSize().height));
        sprintf(str,"%d",resourceCount);
        CCLabelAtlas* count = CCLabelAtlas::create(str, "number6.png", 24, 36, '/');
        count->setAnchorPoint(ccp(0.5,0.5));
        count->setScale(0.8);
        count->setPosition(ccp(box->getContentSize().width/2+20,120+i*50));
        if (flag > 0) {
            count->setColor(ccc3(255,255,0));
            MyGameInfo::getInstance()->changeResource(resourceTag,resourceCount);
            if (resourceTag == oilTag) {
                prizeOil = resourceCount;
            } else if(resourceTag == ironTag) {
                prizeIron = resourceCount;
            } else if(resourceTag == gloryTag) {
                prizeGlory = resourceCount;
            }
        } else {
            count->setColor(ccc3(150,150,150));
        }
        box->addChild(icon);
        box->addChild(count);
    }
    if (flag >0) {
         MyHttpConnection::getInstance()->sendOpenBox(prizeBoxIds[tag],completeRate);
    }
}

void DefendScene::checkVictory() {
    if (battleMap->getUnits()->count() <= 0) {
        this->addChild(getVictoryUI(true),3);
        this->unschedule(schedule_selector(DefendScene::checkVictory));
    }
}

int DefendScene::getBaseLoc() {

    if (attackerDirection == attackLD) {
        bool flag = true;
        baseLoc = 45;
        while (flag) {
            for (int j=-3; j<5; j++) {
                for (int k = 20; k<41; k++) {
                    if (baseLoc + j < 60) {
                        if (battleMap->mybuildingMap[k][baseLoc + j] != NULL && ((MyBattleBuilding*)battleMap->mybuildingMap[k][baseLoc + j])->isAlive()) {
                            goto END1;
                        }
                    }
                }
            }
            flag = false;
            break;
            END1:baseLoc = baseLoc+3;
        }
        return baseLoc;
    } else if(attackerDirection == attackRD) {
        bool flag = true;
        baseLoc = 45;
        while (flag) {
            for (int j=-3; j<5; j++) {
                for (int k = 20; k<41; k++) {
                    if (baseLoc + j < 60) {
                        if (battleMap->mybuildingMap[baseLoc+j][k] != NULL && ((MyBattleBuilding*)battleMap->mybuildingMap[baseLoc+j][k])->isAlive()) {
                            goto END2;
                        }
                    }
                }
            }
            flag = false;
            break;
            END2:baseLoc = baseLoc+3;
        }
        return baseLoc;

    } else if(attackerDirection == attackLU) {
        bool flag = true;
        baseLoc = 15;
        while (flag) {
            for (int j=-3; j<5; j++) {
                for (int k = 20; k<41; k++) {
                    if (baseLoc + j >= 0) {
                        if (battleMap->mybuildingMap[baseLoc + j][k] != NULL && ((MyBattleBuilding*)battleMap->mybuildingMap[baseLoc + j][k])->isAlive()) {
                            goto END3;
                        }
                    }
                }
            }
            flag = false;
            break;
        END3:baseLoc = baseLoc-3;
        }
        return baseLoc;
    } else if(attackerDirection == attackRU) {
        bool flag = true;
        baseLoc = 15;
        while (flag) {
            for (int j=-3; j<5; j++) {
                for (int k = 20; k<41; k++) {
                    if (baseLoc + j >= 0) {
                        if (battleMap->mybuildingMap[k][baseLoc + j] != NULL && ((MyBattleBuilding*)battleMap->mybuildingMap[k][baseLoc + j])->isAlive()) {
                            goto END4;
                        }
                    }
                }
            }
            flag = false;
            break;
        END4:baseLoc = baseLoc-3;
        }
        return baseLoc;
    }
    return baseLoc;
}