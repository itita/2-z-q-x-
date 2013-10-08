//
//  NewbieMovieScene.cpp
//  ww3
//
//  Created by xiao tang on 12-12-20.
//
//

#include "NewbieMovieScene.h"
#include "MyBattleBuilding.h"
#include "MyContinueTiledSprite.h"
#include "MyJsonUtil.h"
#include "MyGameFactory.h"
#include "Mathlib.h"
#include "AoeDefendState.h"
#include "GXRadioMenu.h"
#include "MyGameInfo.h"
#include "MyUtil.h"
#include "MyMessageManage.h"
#include "Newbie3Trigger.h"
#include "ToFightMessage.h"
#include "SimpleAudioEngine.h"
#include "NewbieClickMessage.h"
#include "MyPriorityMenu.h"
#include "GXShieldTouchMenuItem.h"
#include "Newbie4Trigger.h"

NewbieMovieScene* NewbieMovieScene::create(cocos2d::CCArray *buildings) {
    NewbieMovieScene *pRet = new NewbieMovieScene();
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


bool NewbieMovieScene::init(cocos2d::CCArray *buildings) {
    isFighting = false;
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
    
    battleMap->setTag(MainMapTag);
    
    CCTMXLayer* tiledLayer = battleMap->layerNamed("tiled");
    
    for (int i=10; i<50; ++i) {
        for (int j=10; j<50; ++j) {
            tiledLayer->tileAt(ccp(i,j))->setColor(ccc3(255,255,255));
        }
    }
    
    initUI();
//    battleMap->centerView();
    this->addChild(battleMap);
    
    toFight();
    MyMessageManage::getInstance()->registerTrigger(Newbie4Trigger::create(this));
    return true;
}

void NewbieMovieScene::toSurrender() {

}


void NewbieMovieScene::toFight(){
    if (!isFighting) {

        ((MyBattleState*)(((MyBattleBuilding*)battleMap->getChildByTag(zhihuisuoTag))->fsm->getCurrentState()))->getItem()->getChildByTag(battleTipTag)->removeFromParentAndCleanup(true);
        ((MyBattleState*)(((MyBattleBuilding*)battleMap->getChildByTag(zhihuisuoTag))->fsm->getCurrentState()))->getItem()->getChildByTag(battleTipAimTag)->removeFromParentAndCleanup(true);
//        CCObject* obj;
//        CCARRAY_FOREACH(battleMap->getChildren(), obj) {
//            MyBattleBuilding* bd = dynamic_cast<MyBattleBuilding*>(obj);
//            if (bd != NULL) {
//                bd->removeChildByTag(levelFontTag, true);
//                bd->removeChildByTag(nameFontTag, true);
//            }
//        }
        
        isFighting = true;
//        CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("bgm_battleScene.mp3",true);
        
    }
}

void NewbieMovieScene::initUI() {
    
    CCLayer* uiLayer = CCLayer::create();
    uiLayer->setTag(UILayerTag);
    
    
    
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
   
    //    uiLayer->addChild(fightMenu);
//    this->addChild(resourseBar,2);
   
    addChild(uiLayer,1);
    
}


void NewbieMovieScene::victory() {
    
}



void NewbieMovieScene::toBuildScene() {
    
    //    StartScene* scene = MyJsonUtil::parseNativeInfo(MyHttpConnection::getInstance()->getStartSceneData());
    //    CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(1.0, scene, ccWHITE));
    
}

void NewbieMovieScene::doPause() {
    
}

void NewbieMovieScene::loadResource() {
    BattleScene::loadResource();
    GXUtil::loadResourceUtilSucc("cloud.plist","cloud.pvr.ccz");
}

void NewbieMovieScene::releaseResource() {
    CCTextureCache::sharedTextureCache()->removeTextureForKey("plane.png");
    CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile("cloud.plist");
    CCTextureCache::sharedTextureCache()->removeTextureForKey("cloud.pvr.ccz");
    
}



NewbieMoveSceneCreator* NewbieMoveSceneCreator::create(cocos2d::CCArray *array) {
    NewbieMoveSceneCreator* creator = new NewbieMoveSceneCreator();
    creator->buildingBeans = array;
    creator->buildingBeans->retain();
    creator->autorelease();
    return creator;
}

void NewbieMoveSceneCreator::doFill(cocos2d::CCObject *entity) {
    
}


CCObject* NewbieMoveSceneCreator::creatObj() {
    NewbieMovieScene* scene = NewbieMovieScene::create(buildingBeans);
    doFill(scene);
    return scene;
}

NewbieMoveSceneCreator::~NewbieMoveSceneCreator() {
    CC_SAFE_RELEASE(buildingBeans);
}