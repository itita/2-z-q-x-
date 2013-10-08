//
//  NewbieBattleScene.cpp
//  ww3
//
//  Created by xiao tang on 12-12-17.
//
//

#include "NewbieBattleScene.h"
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
#include "NewbieMovieScene.h"
#include "TransitonScene.h"
#include "DefineSet.h"

NewbieBattleScene* NewbieBattleScene::create(cocos2d::CCArray *buildings) {
    NewbieBattleScene *pRet = new NewbieBattleScene();
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

bool NewbieBattleScene::init(cocos2d::CCArray *buildings) {
    isFighting = false;
    isVictory = false;
    MyGameInfo::getInstance()->enemyOil = 15000;
    MyGameInfo::getInstance()->enemyIron = 15000;
    
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
    battleMap->displayTip();
    
    
    initUI();
    battleMap->centerView();
    this->addChild(battleMap);
    MyMessageManage::getInstance()->registerTrigger(Newbie3Trigger::create(this));
    return true;
}

void NewbieBattleScene::initUI() {
    
    CCLayer* uiLayer = CCLayer::create();
    uiLayer->setTag(UILayerTag);
    
//    CCSprite* avatar =CCSprite::createWithSpriteFrameName("avatar.png");
//    //    uiLayer->addChild(avatar);
//    avatar->setAnchorPoint(ccp(0,1));
//    avatar->setPosition(ccp(0,winSize.height));
//    avatar->setTag(avatarTag);
//    CCSprite* avatarSprite = CCSprite::createWithSpriteFrameName("avatar0.png");
//    avatarSprite->setAnchorPoint(ccp(0,0));
//    avatarSprite->setPosition(ccp(5,5));
//    avatar->addChild(avatarSprite);
//    
//    
//    CCSprite* avatarAverse =CCSprite::createWithSpriteFrameName("avatar.png");
//    avatarAverse->setTag(avatarAverseTag);
//    avatarAverse->setFlipX(true);
//    avatarAverse->setAnchorPoint(ccp(1,1));
//    avatarAverse->setPosition(ccp(winSize.width,winSize.height));
//    CCSprite* avatarAverseSprite = CCSprite::createWithSpriteFrameName("avatar0.png");
//    avatarAverseSprite->setFlipX(true);
//    avatarAverseSprite->setAnchorPoint(ccp(1,0));
//    avatarAverseSprite->setPosition(ccp(avatarAverse->getContentSize().width-5,5));
//    avatarAverse->addChild(avatarAverseSprite);
//    
//    
//    //    CCLabelTTF* nickName = CCLabelTTF::create(string.c_str(),"Arial", 54);
//    
//    CCLabelTTF* nickName = CCLabelTTF::create("指挥官","Arial", 18);
//    nickName->setAnchorPoint(ccp(0.5,1));
//    nickName->setPosition(ccp(135,84));
//    
//    CCLabelTTF* rankName = CCLabelTTF::create(MyUtil::getInstance()->getRankString(1200), "Arial", 20);
//    avatar->addChild(rankName,2);
//    rankName->setAnchorPoint(ccp(0,0.5));
//    rankName->setPosition(ccp(126,44));
//    rankName->setColor(ccWHITE);
//    
//    CCSprite* rankSprite = MyUtil::getInstance()->getRankSprite(1200);
//    rankSprite->setPosition(ccp(106,44));
//    rankSprite->setScale(0.50);
//    avatar->addChild(rankSprite,2);
//    
//    CCLabelTTF* enemyNickName = CCLabelTTF::create("德军前哨","Arial", 18);
//    enemyNickName->setAnchorPoint(ccp(0.5,1));
//    
//    enemyNickName->setPosition(ccp(avatarAverse->getContentSize().width -136,84));
//    
//    CCLabelTTF* enemyRankName = CCLabelTTF::create(MyUtil::getInstance()->getRankString(480), "Arial", 20);
//    avatarAverse->addChild(enemyRankName,2);
//    enemyRankName->setAnchorPoint(ccp(1,0.5));
//    enemyRankName->setPosition(ccp(avatarAverse->getContentSize().width -126,44));
//    enemyRankName->setColor(ccWHITE);
//    
//    CCSprite* enemyRankSprite = MyUtil::getInstance()->getRankSprite(480);
//    enemyRankSprite->setPosition(ccp(avatarAverse->getContentSize().width -106,44));
//    enemyRankSprite->setScale(0.50);
//    avatarAverse->addChild(enemyRankSprite,2);
    
//    CCSprite* next = CCSprite::create("next.png");
    CCSprite* gynext = CCSprite::createWithSpriteFrameName("next.png");
    gynext->setColor(ccGRAY);
    
    
    CCSprite* surrender = CCSprite::createWithSpriteFrameName("backToBuild.png");
    CCSprite* gysurrender = CCSprite::createWithSpriteFrameName("backToBuild.png");
    gysurrender->setColor(ccGRAY);
    
    CCMenuItemSprite* surrenderItem = CCMenuItemSprite::create(surrender, gysurrender, this, menu_selector(BattleScene::toSurrender));
    surrenderItem->setPosition(ccp(100,winSize.height/3));
    //    surrender->setVisible(false);
    surrenderItem->setTag(surrenderTag);
    
    fightMenu = CCMenu::create(surrenderItem,NULL);
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
//
//    
//    enemyOilLabel = MyAtlasNumber::create();
//    enemyOilLabel->setNumberNoFx(MyGameInfo::getInstance()->getRobberOil());
//    enemyOilLabel->setAnchorPoint(ccp(0,0.5));
//    enemyOilLabel->setPosition(ccp(73,42));
//    enemyOilLabel->setScale(2);
//    CCSprite* oilIcon = CCSprite::createWithSpriteFrameName("oilIcon.png");
//    oilIcon->setScale(0.5);
//    oilIcon->setPosition(ccp(winSize.width-130,520));
//    oilIcon->setTag(enemyOilIconTag);
//    oilIcon->setOpacity(0);
//    
//    enemyIronLabel = MyAtlasNumber::create();
//    enemyIronLabel->setNumberNoFx(MyGameInfo::getInstance()->getRobberIron());
//    enemyIronLabel->setAnchorPoint(ccp(0,0.5));
//    enemyIronLabel->setPosition(ccp(73,30));
//    enemyIronLabel->setScale(2);
//    CCSprite* ironIcon = CCSprite::createWithSpriteFrameName("ironIcon.png");
//    ironIcon->setScale(0.5);
//    ironIcon->setPosition(ccp(winSize.width-130,460));
//    ironIcon->setTag(enemyIronIconTag);
//    ironIcon->setOpacity(0);
//    
//    enemyHonorLabel = MyAtlasNumber::create();
//    
//    enemyHonorLabel->setNumberNoFx(Mathlib::bound((MyGameInfo::getInstance()->enemyPower/MyGameInfo::getInstance()->getPower())*20, 40, 0));
//    enemyHonorLabel->setAnchorPoint(ccp(0,0.5));
//    enemyHonorLabel->setPosition(ccp(35,25));
//    CCSprite* honorIcon = CCSprite::createWithSpriteFrameName("honorIcon.png");
//    //    honorIcon->setScale(0.5);
//    honorIcon->setPosition(ccp(winSize.width-130,400));
//    honorIcon->setTag(enemyHonorIconTag);
//    honorIcon->setOpacity(0);
////    this->addChild(avatar,10);
////    avatar->addChild(nickName);
////    this->addChild(avatarAverse,10);
////    avatarAverse->addChild(enemyNickName);
////    uiLayer->addChild(fightMenu);
    this->addChild(resourseBar,2);
//    this->addChild(oilIcon,2);
//    oilIcon->addChild(enemyOilLabel);
//    this->addChild(ironIcon,2);
//    ironIcon->addChild(enemyIronLabel);
//    this->addChild(honorIcon,2);
//    honorIcon->addChild(enemyHonorLabel);
    
    
    
    
    //    char* str =
    //    MyJsonUtil::parseBuildingFromJson(str);
    
    addChild(uiLayer,1);
    
}

void NewbieBattleScene::toFight() {
    if (isFighting == 0) {
        CCLog("开战");
        ToFightMessage::create()->sendMsg();
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
        
        isFighting = 1;
        CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("bgm_battleScene.mp3",true);
//        CCMenuItemSprite* surrender = (CCMenuItemSprite*)fightMenu->getChildByTag(surrenderTag);
//        
//        CCSprite* sprite = CCSprite::create("surrender.png");
//        sprite->setColor(ccGRAY);
        
//        surrender->setNormalImage(CCSprite::create("surrender.png"));
//        
//        surrender->setSelectedImage(sprite);
//        surrender->setPosition(ccp(transWindowToGLInRetina(30),winSize.height/4*3));
        
    }

}


void NewbieBattleScene::callback1(cocos2d::CCObject *pSender) {
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sfx_click.mp3");
    battleMap->setCurrentDeployButton(((MyDeployButton*)pSender));
    if (strcmp( ((MyDeployButton*)pSender)->bean->creator->getSpriteFileName(),"M5Stuart") == 0) {
        NewbieClickMessage::create()->sendMsg();
    }
}


CCLayer* NewbieBattleScene::getVictoryUI(bool isVictory) {
    isFighting = 3;
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
    
    CCMenuItemSprite* returnHomeButton = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("returnHomeButton.png"), CCSprite::createWithSpriteFrameName("returnHomeButtonP.png"),this,menu_selector(NewbieBattleScene::toBuildScene));
    returnHomeButton->setPosition(ccp(0,-160));
    
      
    MyPriorityMenu* actionMenu = MyPriorityMenu::create(-510, returnHomeButton,NULL);
    actionMenu->setPosition(ccp(victoryBack->getContentSize().width/2,victoryBack->getContentSize().height/2));
    victoryBack->addChild(actionMenu);
    
    CCLabelTTF* robberLabel = CCLabelTTF::create("合计掠夺资源:", "Arial", 20);
    robberLabel->setAnchorPoint(ccp(0,0.5));
    robberLabel->setPosition(ccp(winSize.width/2-250,460));
    robberLabel->setColor(ccc3(237,219,138));
    victoryLayer->addChild(robberLabel,2);
    
    
    int robberOil = (int)(MyGameInfo::getInstance()->getRobberOil()-enemyOilLabel->getTargetNumber());
    int robberIron = (int) (MyGameInfo::getInstance()->getRobberIron()-enemyIronLabel->getTargetNumber());
    
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
        sprintf(str, "%d",300);
    } else {
        sprintf(str, "%d",0);
    }
    
    CCLabelAtlas* powerCount = CCLabelAtlas::create(str, "number6.png", 24, 36, '/');
    powerCount->setPosition(ccp(winSize.width/2+20,330));
    powerCount->setAnchorPoint(ccp(1,0.5));
    powerCount->setScale(0.7);
    powerCount->setColor(ccc3(231,219,138));
    victoryLayer->addChild(powerCount,2);
    
    
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
            costOil += (MyUtil::getInstance()->updateLevelByRate(0,button->bean->creator->getSummaryOil(), button->bean->getLevel(), button->bean->creator->updateCostRate))*button->count;
            
            
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
    heidi->setColor(ccc3(0,0,0));
    //    CCLog("%f,%f",heidi->getContentSize().width,heidi->getContentSize().height);
    heidi->setScaleX(531/heidi->getContentSize().width);
    heidi->setScaleY(63/heidi->getContentSize().height);
    heidi->setOpacity(150);
    //    CCLog("%f,%f",heidi->getContentSize().width,heidi->getContentSize().height);
    MyMenuItem* bpItem = MyMenuItem::create(heidi,NULL,NULL);
    bpItem->setPosition(ccp(0,-105));
    bpItem->setContentSize(CCSizeMake(531,63));
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
        m_TextField->setPlaceHolder("德国鬼子们，见鬼去吧！！！");
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
    
    return victoryLayer;
}

void NewbieBattleScene::toBuildScene() {
    
    
//    NewbieMoveSceneCreator* creator = (NewbieMoveSceneCreator*)MyGameFactory::createCreatorbyJsonScriptFile("NewbieBase.j",NewbieMovieSceneClassTag);
    CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.2, TransitonScene::create(NewbieMovieSceneClassTag,CCString::create("NewbieBase.j")), ccBLACK));
    
}

void NewbieBattleScene::doPause() {
    
}

void NewbieBattleScene::toSurrender() {

}

void NewbieBattleScene::loadResource() {
    BattleScene::loadResource();
    GXUtil::loadResourceUtilSucc("newbie2.plist","newbie2.pvr.ccz");
}

void NewbieBattleScene::releaseResource() {
    CCTextureCache::sharedTextureCache()->removeTextureForKey("avatarWhiteMask.png");
    CCTextureCache::sharedTextureCache()->removeTextureForKey("transparent.png");
    CCTextureCache::sharedTextureCache()->removeTextureForKey("avatarAverseMask.png");
    CCTextureCache::sharedTextureCache()->removeTextureForKey("spotlight.png");
    
    CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile("newbie2.plist");
    CCTextureCache::sharedTextureCache()->removeTextureForKey("newbie2.pvr.ccz");
    
}




NewbieBattleSceneCreator* NewbieBattleSceneCreator::create(cocos2d::CCArray *array) {
    NewbieBattleSceneCreator* creator = new NewbieBattleSceneCreator();
    creator->buildingBeans = array;
    creator->buildingBeans->retain();
    creator->autorelease();
    return creator;
}

void NewbieBattleSceneCreator::doFill(cocos2d::CCObject *entity) {
    
}


CCObject* NewbieBattleSceneCreator::creatObj() {
    NewbieBattleScene* scene = NewbieBattleScene::create(buildingBeans);
    doFill(scene);
    return scene;
}

NewbieBattleSceneCreator::~NewbieBattleSceneCreator() {
    CC_SAFE_RELEASE(buildingBeans);
}
