//
//  NewbieStartScene.cpp
//  ww3
//
//  Created by xiao tang on 12-12-10.
//
//

#include "NewbieStartScene.h"
#include <iostream>
#include "cocos2d.h"
#include "MyBattleMap.h"
#include "MyMenu.h"
#include "MyTiledMenuItemSprite.h"
#include "MyBuilding.h"
#include "MyState.h"
#include "MyUnit.h"
#include "BattleScene.h"
#include "GXJsonUtil.h"
#include "NormalState.h"
#include "MyGameFactory.h"
#include "MyJsonUtil.h"
#include "PulsarNative.h"
#include "MyHttpConnection.h"
#include "MyContinueTiledMenuItemSprite.h"
#include <string>
#include "GXUtil.h"
#include "MyGameInfo.h"
#include "MyUtil.h"
//#include "GXScrollView.h"
#include "MyPriorityMenu.h"
#include "CoordinateTrans.h"
#include "DefineSet.h"
#include "MyBuildingCard.h"
#include "Mathlib.h"
#include "ReadyToBuild.h"
#include "LoadingScene.h"
#include "SimpleAudioEngine.h"
#include "MyProgressBar.h"
#include "MyLevelBar.h"
#include "CollectState.h"
#include "GXShieldTouchMenuItem.h"
#include "MyUnitCard.h"
#include "GXAnimateFX.h"
#include "GXMsg.h"
#include "GXListView.h"
#include "GXRemoveFromParentsAction.h"
#include "GXRadioMenu.h"
#include "MyContinueTiledSprite.h"
#include "MyMessageManage.h"
#include "Newbie1Trigger.h"
#include "NewbieBattleScene.h"
#include "TransitonScene.h"
#include "AoeDefendState.h"

#define transScorllTag 12
#define recordContentLayerTag 13
#define recordBackSpriteTag 14


using namespace cocos2d;

bool NewbieStartScene::init() {
    this->initUI();
    return true;
}

NewbieStartScene::~NewbieStartScene() {
    //    CocosDenshion::SimpleAudioEngine::sharedEngine()->unloadEffect("sfx_pickup.wav");
    //    CocosDenshion::SimpleAudioEngine::sharedEngine()->unloadEffect("sfx_place.wav");
    //    CocosDenshion::SimpleAudioEngine::sharedEngine()->unloadEffect("sfx_");
    releaseResource();
    CCLog("StartScene released");
}

NewbieStartScene* NewbieStartScene::create(cocos2d::CCArray *buildings) {
    NewbieStartScene *pRet = new NewbieStartScene();
    pRet->loadResource();
    if (pRet && pRet->init(buildings))
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



void NewbieStartScene::doPause() {
//    updateMyData();
//    CCDirector::sharedDirector()->replaceScene(LoadingScene::create());
    CCLog("pause");
}

bool NewbieStartScene::init(cocos2d::CCArray *buildings) {
    
    CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect("sfx_missionAppear.mp3");
    
    
    pageNo = 1;
    MyBattleMap* battleMap = MyBattleMap::create("ditu002.tmx");
    battleMap->setOriPosition(ccp(0,0));
    battleMap->setEnabled(false);
    
    CCSprite* backd = CCSprite::createWithSpriteFrameName("backgroundud.png");
    
    backd->setAnchorPoint(ccp(0,0));
    backd->setPosition(ccp(0,0));
    backd->setScale(1800/backd->getContentSize().width);
    battleMap->CCNode::addChild(backd,-1);
    
    
    this->addChild(battleMap);
    battleMap->setTag(MainMapTag);
    
    
    CCObject* obj;
    
    CCArray* antiArray =CCArray::create();
    CCARRAY_FOREACH(buildings, obj) {
        BuildingBean* bean = dynamic_cast<BuildingBean*>(obj);
        MyBattleBuilding* building = MyGameFactory::createBattleBuildingByBean(bean, this,false);
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
    ((MyBattleState*)(zhihuisuo->fsm->getCurrentState()))->getItem()->getChildByTag(battleTipTag)->removeFromParentAndCleanup(true);
    ((MyBattleState*)(zhihuisuo->fsm->getCurrentState()))->getItem()->getChildByTag(battleTipAimTag)->removeFromParentAndCleanup(true);
    char str[20] = {0};
    CCARRAY_FOREACH(antiArray, obj) {
        MyBattleBuilding* building = dynamic_cast<MyBattleBuilding*>(obj);
        
        float angle = Mathlib::getAngle(zhihuisuo->getPositionByTiled(), building->getPositionByTiled());
        int dir = (((int)(angle*180/3.141592654+22.5)+360)%360)/45 ;
        AoeDefendState* state =  dynamic_cast<AoeDefendState*>(building->fsm->getState(DefendStateTag));
        
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
    
    battleMap->setOriPosition(ccp(-battleMap->getContentSize().width/4,-battleMap->getContentSize().height/4));
    battleMap->setContentMapSize(CCSizeMake(battleMap->getContentSize().width/2,battleMap->getContentSize().height/2));
    battleMap->centerView();
    battleMap->setPosition(ccp(battleMap->getPositionX()+500,battleMap->getPositionY()+500));
    
    CCTMXLayer* tiledLayer = battleMap->layerNamed("tiled");
    
    for (int i=10; i<50; ++i) {
        for (int j=10; j<50; ++j) {
            tiledLayer->tileAt(ccp(i,j))->setColor(ccc3(255,255,255));
        }
    }
    
    //    MyGameFactory::createBuildingbyJsonScriptFile("by.j");
    
    
    initControl();
    
    
    return true;
}


void NewbieStartScene::initControl() {
    
    MyGameInfo::getInstance()->setOil(500);
    MyGameInfo::getInstance()->setIron(500);
    
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("bgm_startScene.mp3",true);
    
    CCLayer* uiLayer = CCLayer::create();
    uiLayer->setTag(UILayerTag);
    
    MyMessageManage::getInstance()->registerTrigger(Newbie1Trigger::create(this));
    
//    CCSprite* resourseBar = CCSprite::createWithSpriteFrameName("resourseBar.png");
//    resourseBar->setScale(1.25);
//    resourseBar->setAnchorPoint(ccp(0.5,1));
//    resourseBar->setPosition(ccp(winSize.width/2,winSize.height));
//    resourseBar->setTag(resourceBarTag);
    
    
//    CCSprite* avatar =CCSprite::createWithSpriteFrameName("avatar.png");
//    //    uiLayer->addChild(avatar);
//    avatar->setAnchorPoint(ccp(0,1));
//    avatar->setPosition(ccp(0,winSize.height));
//    avatar->setTag(avatarTag);
//    CCSprite* avatarSprite = CCSprite::createWithSpriteFrameName("avatar0.png");
//    avatarSprite->setAnchorPoint(ccp(0,0));
//    avatarSprite->setPosition(ccp(5,5));
//    avatar->addChild(avatarSprite);
    
//    CCSprite* bottom = CCSprite::createWithSpriteFrameName("bottom.png");
//    bottom->setScale(1.25);
//    bottom->setAnchorPoint(ccp(1,0));
//    bottom->setPosition(ccp(winSize.width,0));
//    bottom->setTag(UIBottomTag);

//    CCSprite* gybattle = CCSprite::create("battleIcon.png");
//    gybattle->setColor(ccGRAY);
//    CCMenuItemSprite* battleButton = CCMenuItemSprite::create(CCSprite::create("battleIcon.png"), gybattle,this,menu_selector(NewbieStartScene::toBattleScene));
//    CCSprite* createSprite = CCSprite::create("createIcon.png");
//    createSprite->setColor(ccGRAY);
//    CCMenuItemSprite* createButton = CCMenuItemSprite::create(CCSprite::create("createIcon.png"), createSprite,this,menu_selector(NewbieStartScene::toCreateCallBack));
//    
//    CCSprite* recordSprite1 = CCSprite::create("recordIcon.png");
//    recordSprite1->setColor(ccGRAY);
//    CCMenuItemSprite* recordButton1 = CCMenuItemSprite::create(CCSprite::create("recordIcon.png"), recordSprite1);
//    
//    CCSprite* recordSprite2 = CCSprite::create("recordIcon.png");
//    recordSprite2->setColor(ccGRAY);
//    CCMenuItemSprite* recordButton2 = CCMenuItemSprite::create(recordSprite2,CCSprite::create("recordIcon.png"));
//    
//    CCMenuItemToggle* recordtButton = CCMenuItemToggle::createWithTarget(this,menu_selector(NewbieStartScene::toggleRecorder),recordButton1,recordButton2,NULL);
//    recordtButton->setTag(recordToggleTag);
//    
//    CCSprite* gyShow = CCSprite::create("showIcon.png");
//    gyShow->setColor(ccGRAY);
//    CCMenuItemSprite* showButton = CCMenuItemSprite::create(CCSprite::create("showIcon.png"), gyShow,this,menu_selector(NewbieStartScene::toShowCallBack));
//    
//    CCSprite* gyArmy = CCSprite::create("armyIcon.png");
//    gyArmy->setColor(ccGRAY);
//    CCMenuItemSprite* armyButton = CCMenuItemSprite::create(CCSprite::create("armyIcon.png"), gyArmy,this,menu_selector(NewbieStartScene::toArmyCallBack));
//    
//    
//    
//    //    CCMenuItem::create(this, menu_selector(NewbieStartScene::toCreateCallBack));
//
//    
//    
//    MyPriorityMenu* battlem = MyPriorityMenu::create(-500,armyButton,showButton,recordtButton,createButton,battleButton,NULL);
    
    MyPriorityMenu* battlem = MyPriorityMenu::create(-500,NULL);

//    battlem->alignItemsHorizontallyWithPadding(30);
    battlem->setPosition(ccp(670,60));
    battlem->setTag(controlMenuTag);
//
//    
//    
    //    CCLabelTTF* nickName = CCLabelTTF::create(string.c_str(),"Arial", 54);
//    CCLabelTTF* nickName = CCLabelTTF::create("指挥官","Arial", 18);
//    nickName->setAnchorPoint(ccp(0.5,1));
//    nickName->setPosition(ccp(135,84));
//
//    
//    
//    CCSprite* level = CCSprite::createWithSpriteFrameName("levelIcon.png");
//    level->setScale(24/level->getContentSize().width);
//    level->setPosition(ccp(112,46));
    
    
    
//    MyLevelBar* levelBar = MyLevelBar::create(CCSprite::create("levelBarUp.png"), CCSprite::create("BarDown.png"),CCSizeMake(84, 8));
//    levelBar->setLevel(10);
//    
//    levelBar->setContentSize(transWindowToGLInRetina(CCSizeMake(42, 4)));
//    levelBar->updatePercentage(0.3);
//    levelBar->setPosition(ccp(88,30));
    
//    avatar->addChild(nickName);
//    avatar->addChild(level,2);
//    avatar->addChild(levelBar,1);
//
//    
//    
//    CCLabelAtlas* oilLabel = MyGameInfo::getInstance()->getOilAtlas();
//    oilLabel->setPosition(ccp(35.2,4.8));
//    oilLabel->setAnchorPoint(ccp(0,0));
//    oilLabel->setScale(0.52);
//    oilLabel->removeFromParentAndCleanup(true);
//    resourseBar->addChild(oilLabel);
//    
//    CCLabelAtlas* ironLabel = MyGameInfo::getInstance()->getIronAtlas();
//    ironLabel->setPosition(ccp(144,4.8));
//    ironLabel->setAnchorPoint(ccp(0,0));
//    ironLabel->setScale(0.52);
//    ironLabel->removeFromParentAndCleanup(true);
//    resourseBar->addChild(ironLabel);
    
//    CCSprite* military = CCSprite::createWithSpriteFrameName("militaryIcon.png");
//    military->setScale(18.4/military->getContentSize().width);
//    military->setPosition(ccp(292*0.8,14*0.8));
//    
//    MyProgressBar* militaryBar = MyProgressBar::create(CCSprite::create("militaryBarUp.png"),CCSprite::create("BarDown.png"),26);
//    militaryBar->setContentSize(CCSizeMake(90*0.8, 20*0.8));
//    militaryBar->setCapacity(3);
//    militaryBar->setPosition(ccp(248,3.2));

    
    
    
//    resourseBar->addChild(military);
//    resourseBar->addChild(militaryBar);
    
    MyPriorityMenu* questMenu = MyPriorityMenu::create(-502,NULL);
    questMenu->setPosition(ccp(-22.5,10));
    questMenu->setTag(questMenuTag);
    
//    uiLayer->addChild(bottom);
    uiLayer->addChild(battlem);
    uiLayer->addChild(questMenu);
//    addChild(avatar);
//
//    
    controlMenu = battlem;
//
    addChild(uiLayer);
//    addChild(resourseBar);
    
    
    
    
    
}

void NewbieStartScene::toBattleScene() {
    // 去掉MAP的注册
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sfx_click.mp3");
    //    if(map != NULL) {
    //        if(!MyHttpConnection::getInstance()->updateStartSceneData(MyJsonUtil::packAllBuilding(map->getItems()))) {
    //            this->addChild(MyUtil::getInstance()->getNetworkDialog());
    //            return;
    //        };
    //    }
    this->getChildByTag(MainMapTag)->pauseSchedulerAndActions();
    
    
    //    char str[65535] = {0};
    //    sprintf(str, "http://192.168.0.222:8080/DEFENDDIAOYUISLAND/servlet/getgamedata?itita_id=%s",PulsarNative::getDeviceId());
//    const char* response = MyHttpConnection::getInstance()->getOtherData();
//    if (strcmp(response, "failed") == 0 || strcmp(response, "\0") == 0) {
//        this->addChild(MyUtil::getInstance()->getNetworkDialog());
//        
//        return;
//    }
    MyGameInfo::getInstance()->enemyIron = 0;
    MyGameInfo::getInstance()->enemyOil = 0;
    
//    NewbieBattleSceneCreator* creator = (NewbieBattleSceneCreator*)MyGameFactory::createCreatorbyJsonScriptFile("NewbieBattleBase.j",NewbieBattleSceneClassTag);
//    NewbieBattleScene* battleScene = (NewbieBattleScene*)creator->creatObj();
    
//    CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.2, TransitonScene::create(NewbieBattleSceneClassTag, "NewbieBattleBase.j") , ccBLACK));
    
     CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.2, TransitonScene::create(NewbieReadySceneClassTag) , ccBLACK));
    
    CocosDenshion::SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
}




void NewbieStartScene::hiddenControlUI() {
    CCNode* node = getChildByTag(UILayerTag);
    
    CCSprite* avatar = (CCSprite*)node->getChildByTag(avatarTag);
    CCSprite* bottom = (CCSprite*)node->getChildByTag(UIBottomTag);
    //    controlMenu->setPosition(transWindowToGLInRetina(360,30));
    if(controlMenu != NULL) {
        controlMenu->runAction(CCMoveTo::create(0.15, ccp(670,-72)) );
    }
    //    resourseBar->setPosition(ccp(winSize.width/2,winSize.height));
    if(avatar != NULL) {
        avatar->runAction(CCMoveTo::create(0.15, ccp(-avatar->getContentSize().width,winSize.height)));
    }
    if (bottom != NULL) {
         bottom->runAction(CCMoveTo::create(0.15, ccp(winSize.width,-bottom->getContentSize().height)));
    }
    
    //    resourceBar->
}

void NewbieStartScene::displayControlUI() {
    CCNode* node = getChildByTag(UILayerTag);
    CCSprite* avatar = (CCSprite*)node->getChildByTag(avatarTag);
    CCSprite* bottom = (CCSprite*)node->getChildByTag(UIBottomTag);
    //    controlMenu->setPosition(transWindowToGLInRetina(360,30));
    if(controlMenu != NULL) {
        controlMenu->runAction(CCMoveTo::create(0.15, ccp(670,60)));
    }
    if (avatar != NULL) {
        
        //    resourseBar->setPosition(ccp(winSize.width/2,winSize.height));
        avatar->runAction(CCMoveTo::create(0.15, ccp(0,winSize.height)));
    }
    if (bottom!=NULL) {
        bottom->runAction(CCMoveTo::create(0.15, ccp(winSize.width,0)));
    }
    
}

void NewbieStartScene::releaseResource() {
    CCTextureCache::sharedTextureCache()->removeTextureForKey("spotlight.png");
    CCTextureCache::sharedTextureCache()->removeTextureForKey("avatarWhiteMask.png");
    CCTextureCache::sharedTextureCache()->removeTextureForKey("transparent.png");
    CCTextureCache::sharedTextureCache()->removeTextureForKey("resourceBarWhiteMask.png");
    
    
    CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile("Newbie1.plist");
    CCTextureCache::sharedTextureCache()->removeTextureForKey("Newbie1.pvr.ccz");
    
    CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile("collapse.plist");
    CCTextureCache::sharedTextureCache()->removeTextureForKey("collapse.pvr.ccz");
    
    CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile("microboom1.plist");
    CCTextureCache::sharedTextureCache()->removeTextureForKey("microboom1.pvr.ccz");
    
    CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile("boom.plist");
    CCTextureCache::sharedTextureCache()->removeTextureForKey("boom.pvr.ccz");
    
    CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile("antitankBoom.plist");
    CCTextureCache::sharedTextureCache()->removeTextureForKey("antitankBoom.png");
    
    CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile("antiTankF.plist");
    CCTextureCache::sharedTextureCache()->removeTextureForKey("antiTankF.png");
    
    CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile("firelight.plist");
    CCTextureCache::sharedTextureCache()->removeTextureForKey("firelight.pvr.ccz");
    
    CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile("gunlight.plist");
    CCTextureCache::sharedTextureCache()->removeTextureForKey("gunlight.pvr.ccz");
    
    CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile("rockethead.plist");
    CCTextureCache::sharedTextureCache()->removeTextureForKey("rockethead.pvr.ccz");
    
    CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile("rockettail.plist");
    CCTextureCache::sharedTextureCache()->removeTextureForKey("rockettail.pvr.ccz");
    
    CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile("victoryui.plist");
    CCTextureCache::sharedTextureCache()->removeTextureForKey("victoryui.pvr.ccz");
    
    CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile("questUI.plist");
    CCTextureCache::sharedTextureCache()->removeTextureForKey("questUI.pvr.ccz");
    
    CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile("tipTiled.plist");
    CCTextureCache::sharedTextureCache()->removeTextureForKey("tipTiled.pvr.ccz");
    
    CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile("Volksgrenadier.plist");
    CCTextureCache::sharedTextureCache()->removeTextureForKey("Volksgrenadier.pvr.ccz");
    
    CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile("Infanterie.plist");
    CCTextureCache::sharedTextureCache()->removeTextureForKey("Infanterie.pvr.ccz");
    
    CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile("tipTiled.plist");
    CCTextureCache::sharedTextureCache()->removeTextureForKey("tipTiled.pvr.ccz");
    
    CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile("Panzergrenadier.plist");
    CCTextureCache::sharedTextureCache()->removeTextureForKey("Panzergrenadier.pvr.ccz");
    
    CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile("HummingBird.plist");
    CCTextureCache::sharedTextureCache()->removeTextureForKey("HummingBird.pvr.ccz");
    
    CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile("PanzerIV.plist");
    CCTextureCache::sharedTextureCache()->removeTextureForKey("PanzerIV.pvr.ccz");
    
    CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile("tiger.plist");
    CCTextureCache::sharedTextureCache()->removeTextureForKey("tiger.pvr.ccz");
    GarbageResourceCollection::getInstance()->GarbageCollection();
}

NewbieStartSceneCreator* NewbieStartSceneCreator::create(cocos2d::CCArray *array) {
    NewbieStartSceneCreator* creator = new NewbieStartSceneCreator();
    creator->buildingBeans = array;
    creator->buildingBeans->retain();
    creator->autorelease();
    return creator;
}

void NewbieStartSceneCreator::doFill(cocos2d::CCObject *entity) {
    
}


CCObject* NewbieStartSceneCreator::creatObj() {
    NewbieStartScene* scene = NewbieStartScene::create(buildingBeans);
    doFill(scene);
    return scene;
}

NewbieStartSceneCreator::~NewbieStartSceneCreator() {
    CC_SAFE_RELEASE(buildingBeans);
}

void NewbieStartScene::toExit() {
    if(!isClickExit) {
        PulsarNative::showExitMessage();
        isClickExit = true;
        this->scheduleOnce(schedule_selector(StartScene::cancelClickExit), 2);
    } else {
        PulsarNative::toHome();
    }
}

void NewbieStartScene::loadResource() {
    
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
    GXUtil::loadResourceUtilSucc("questUI.plist","questUI.pvr.ccz");
    GXUtil::loadResourceUtilSucc("tipTiled.plist","tipTiled.pvr.ccz");
    GXUtil::loadResourceUtilSucc("normalButton.plist","normalButton.pvr.ccz");
    GXUtil::loadResourceUtilSucc("antiTank.plist","antiTank.png");
    GXUtil::loadResourceUtilSucc("startSceneIcon.plist","startSceneIcon.pvr.ccz");
    GXUtil::loadResourceUtilSucc("Newbie1.plist","Newbie1.pvr.ccz");
    GXUtil::loadResourceUtilSucc("Volksgrenadier.plist","Volksgrenadier.pvr.ccz");
    GXUtil::loadResourceUtilSucc("Infanterie.plist","Infanterie.pvr.ccz");
    GXUtil::loadResourceUtilSucc("Panzergrenadier.plist","Panzergrenadier.pvr.ccz");
    GXUtil::loadResourceUtilSucc("HummingBird.plist","HummingBird.pvr.ccz");
    GXUtil::loadResourceUtilSucc("PanzerIV.plist","PanzerIV.pvr.ccz");
    GXUtil::loadResourceUtilSucc("tiger.plist","tiger.pvr.ccz");
   
}
