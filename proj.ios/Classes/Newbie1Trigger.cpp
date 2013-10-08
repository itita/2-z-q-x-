//
//  Newbie1Trigger.cpp
//  ww3
//
//  Created by xiao tang on 12-12-15.
//
//

#include "Newbie1Trigger.h"
#include "GXShieldTouchMenuItem.h"
#include "MyPriorityMenu.h"
#include "DefineSet.h"
#include "Newbie1to2Message.h"
#include "MyMessageManage.h"
#include "Newbie2Trigger.h"
#include "SimpleAudioEngine.h"
#include "MyUtil.h"
#include "GXJsonUtil.h"
#include "DiaLayer.h"
#include "DialogCompleteMessage.h"
#include "GXRemoveFromParentsAction.h"
#include "TransitonScene.h"
#include "MyGameInfo.h"
#include "MyMenuItem.h"

#define newbieFlowLayerTag 900
#define skipMenuLayerTag 901

Newbie1Trigger::~Newbie1Trigger(){
    CCLog("Newbie1Trigger has been released");
}

Newbie1Trigger* Newbie1Trigger::create(CCNode* node) {
    Newbie1Trigger* trigger = new Newbie1Trigger();
    trigger->autorelease();
    trigger->node = node;
    return trigger;
}

bool Newbie1Trigger::excuteMsg(MyBaseMessage* msg) {
    if(msg->tag == newbie1to2MessageTag) {
        MyMessageManage::getInstance()->unRegisterTrigger(this);
        MyMessageManage::getInstance()->registerTrigger(Newbie2Trigger::create((NewbieStartScene*)node));
    } else if(msg->tag == DialogCompleteMessageTag) {
        DialogCompleteMessage* dMsg = (DialogCompleteMessage*)msg;
        node->removeChildByTag(skipMenuLayerTag,true);
        if (dMsg->currentNode >= 2 ) {
            toNextCallBack(NULL);
        }
    }
    return false;
}

void Newbie1Trigger::toNextCallBack(cocos2d::CCNode *pSender) {
    if (statues == 0) {
        node->removeChildByTag(newbieFlowLayerTag,true);
        CCLayer* newbieLayer = CCLayer::create();
        
        CCSprite* gray = CCSprite::create("whiteImage.jpg");
        gray->setPosition(ccp(winSize.width/2,winSize.height/2));
        gray->setScaleX(winSize.width/gray->getContentSize().width);
        gray->setScaleY(winSize.height/gray->getContentSize().height);
        gray->setColor(ccc3(0,0,0));
        gray->setOpacity(0);
        gray->runAction(CCFadeTo::create(0.5,150));
        
        newbieLayer->addChild(gray);
        
        CCString* str = GXUtil::readFile("NewbieDialog1.j");
        node->addChild(DiaLayer::create(GXJsonUtil::parseDiaLayerInfoBean(str->getCString())),11);
        
        
        newbieLayer->setTag(newbieFlowLayerTag);
        node->addChild(newbieLayer);
        
        MyMenuItem* sprite = MyMenuItem::create(CCSprite::create("skipTutorials.png"),this,menu_selector(Newbie1Trigger::toSkip));
        sprite->setPosition(ccp(winSize.width-200,550));
        
        MyPriorityMenu* skipMenu = MyPriorityMenu::create(-601,sprite,NULL);
        skipMenu->setPosition(ccp(0,0));
        skipMenu->setTag(skipMenuLayerTag);
        node->addChild(skipMenu);
        statues++;
    } else if(statues == 1) {
        Newbie1to2Message::create()->sendMsg();
    }
//    CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sfx_click.mp3");
}

bool Newbie1Trigger::onRegist() {
//    CCLayer* newbieLayer = CCLayer::create();
//    
//    CCSprite* gray = CCSprite::create("whiteImage.jpg");
//    gray->setPosition(ccp(winSize.width/2,winSize.height/2));
//    gray->setScaleX(winSize.width/gray->getContentSize().width);
//    gray->setScaleY(winSize.height/gray->getContentSize().height);
//    gray->setColor(ccc3(0,0,0));
//    gray->setOpacity(150);
//    
//    newbieLayer->addChild(gray);
//    
//    CCString* str = GXUtil::readFile("NewbieDialog1.j");
//    node->addChild(DiaLayer::create(GXJsonUtil::parseDiaLayerInfoBean(str->getCString())),11);
    
    
//    newbieLayer->setTag(newbieFlowLayerTag);
//    node->addChild(newbieLayer);
    CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect("sfx_uicrash.mp3");
    CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect("sfx_uicrash1.mp3");

    CCLayer* newbieLayer = CCLayer::create();
    newbieLayer->setTag(newbieFlowLayerTag);
    
    CCSprite* black = CCSprite::create("whiteImage.jpg");
    black->setColor(ccc3(0,0,0));
    black->setScaleX(winSize.width/black->getContentSize().width);
    black->setScaleY(winSize.height/black->getContentSize().height);
    newbieLayer->addChild(black);
//    black->setTag(newbieBlackTag);
    black->setPosition(ccp(winSize.width/2,winSize.height/2));
    
    CCLabelTTF* label = CCLabelTTF::create("1939.10.30\n天气　晴\n欧洲战场前线基地", "Arial", 36,CCSizeZero, kCCTextAlignmentLeft, kCCVerticalTextAlignmentTop);
    label->setPosition(ccp(200,150));
    label->setOpacity(0);
    label->runAction(CCSequence::create(CCFadeIn::create(0.5),CCDelayTime::create(1.5),CCFadeOut::create(3),GXRemoveFromParentsAction::create(),NULL));
    black->runAction(CCSequence::create(CCDelayTime::create(2),CCFadeOut::create(3),NULL));
    
    newbieLayer->addChild(label);
    
    GXShieldTouchMenuItem* nextButton = GXShieldTouchMenuItem::create();
    nextButton->setContentSize(winSize);
    nextButton->setPosition(ccp(winSize.width/2,winSize.height/2));
    MyPriorityMenu* menu = MyPriorityMenu::create(-499, nextButton,NULL);
    menu->setPosition(ccp(0,0));
//    menu->setTag(newbieMenuTag);
    
    newbieLayer->addChild(menu);
    node->addChild(newbieLayer);
//    node->runAction(CCRepeat::create(static_cast<CCSequence*>(CCSequence::create(CCCallFunc::create(this,callfunc_selector(Newbie1Trigger::deployUnit)),CCDelayTime::create(1),NULL)),20));
    
    
    MyBattleMap* battleMap = (MyBattleMap*)node->getChildByTag(MainMapTag);
    
    battleMap->runAction(CCSequence::create(CCDelayTime::create(3),CCEaseIn::create(CCMoveBy::create(9,ccp(-500,-500)),2),CCCallFunc::create(this,callfunc_selector(Newbie1Trigger::toNextCallBack)),NULL));
    
    CCArray* unitArray = CCArray::create();
    CreatorInfoBean* PanzerIVBean = CreatorInfoBean::create(PanzerIVCardId);
    CreatorInfoBean* VolksgrenadierBean = CreatorInfoBean::create(volksgrenaierCardId);
//    CreatorInfoBean* InfanterieBean = CreatorInfoBean::create(InfanterieCardId);
    CreatorInfoBean* PanzergrenadierBean = CreatorInfoBean::create(panzergrenadierCardId);
//    CreatorInfoBean* HummingBirdBean = CreatorInfoBean::create(HummingBirdCardId);
//    CreatorInfoBean* tigerBean = CreatorInfoBean::create(TigerCardId);
    
    MyUnit* unit1 = PanzerIVBean->creator->createObj(PanzerIVBean->getLevel());
    unit1->setTag(PanzerIVBean->creator->cardId);
    unit1->setPosition(battleMap->transTiledToMap(ccp(25,50)));
    unit1->deployPosi = ccp(25,50);
    unitArray->addObject(unit1);
    
    MyUnit* unit2 = PanzerIVBean->creator->createObj(PanzerIVBean->getLevel());
    unit2->setTag(PanzerIVBean->creator->cardId);
    unit2->setPosition(battleMap->transTiledToMap(ccp(30,55)));
    unit2->deployPosi = ccp(30,55);
    unitArray->addObject(unit2);
    
    MyUnit* unit3 = VolksgrenadierBean->creator->createObj(1);
    unit3->setTag(VolksgrenadierBean->creator->cardId);
    unit3->setPosition(battleMap->transTiledToMap(ccp(24,54)));
    unit3->deployPosi = ccp(24,54);
    unitArray->addObject(unit3);
    
    MyUnit* unit4 = VolksgrenadierBean->creator->createObj(1);
    unit4->setTag(VolksgrenadierBean->creator->cardId);
    unit4->setPosition(battleMap->transTiledToMap(ccp(35,50)));
    unit4->deployPosi = ccp(35,50);
    unitArray->addObject(unit4);
    
    MyUnit* unit5 = VolksgrenadierBean->creator->createObj(1);
    unit5->setTag(VolksgrenadierBean->creator->cardId);
    unit5->setPosition(battleMap->transTiledToMap(ccp(33,59)));
    unit5->deployPosi = ccp(33,59);
    unitArray->addObject(unit5);
    
    MyUnit* unit6 = PanzergrenadierBean->creator->createObj(1);
    unit6->setTag(PanzergrenadierBean->creator->cardId);
    unit6->setPosition(battleMap->transTiledToMap(ccp(23,52)));
    unit6->deployPosi = ccp(23,52);
    unitArray->addObject(unit6);
    
    MyUnit* unit7 = PanzergrenadierBean->creator->createObj(1);
    unit7->setTag(PanzergrenadierBean->creator->cardId);
    unit7->setPosition(battleMap->transTiledToMap(ccp(25,59)));
    unit7->deployPosi = ccp(25,59);
    unitArray->addObject(unit7);
    
    MyUnit* unit8 = PanzergrenadierBean->creator->createObj(1);
    unit8->setTag(PanzergrenadierBean->creator->cardId);
    unit8->setPosition(battleMap->transTiledToMap(ccp(33,65)));
    unit8->deployPosi = ccp(33,65);
    unitArray->addObject(unit8);
    
    MyUnit* unit9 = PanzerIVBean->creator->createObj(1);
    unit9->setTag(PanzerIVBean->creator->cardId);
    unit9->setPosition(battleMap->transTiledToMap(ccp(40,63)));
    unit9->deployPosi = ccp(33,65);
    unitArray->addObject(unit9);
    
    CCObject* obj;
    CCARRAY_FOREACH(unitArray,obj) {
        MyUnit* testUnit = (MyUnit*)(obj);
        battleMap->CCNode::addChild(testUnit,999999);
        battleMap->getUnits()->addObject(testUnit);
        testUnit->doAI();
    }
    
    CCLabelBMFont::create("","basicfont.fnt");
    
//    CCSprite* mopian = CCSprite::create("mopian.png");
//    mopian->setScaleX(winSize.width/mopian->getContentSize().width);
//    mopian->setScaleY(winSize.width/mopian->getContentSize().height);
//    mopian->setOpacity(220);
//    node->addChild(mopian,20);
//    mopian->runAction(CCSequence::create(CCDelayTime::create(10),CCFadeOut::create(1),NULL));
    
    return false;
}

bool Newbie1Trigger::onUnRegist() {
    node->removeChildByTag(newbieFlowLayerTag, true);
    node->removeChildByTag(skipMenuLayerTag,true);
    return true;
}

void Newbie1Trigger::toSkip() {
    CCUserDefault::sharedUserDefault()->setBoolForKey("newbieTag", true);
    CCUserDefault::sharedUserDefault()->flush();
    CCDirector::sharedDirector()->replaceScene(TransitonScene::create(ServerSceneTag));
    MyMessageManage::getInstance()->unRegisterTrigger(this);
}

void Newbie1Trigger::toDisplayMisson() {
    
}

//void Newbie1Trigger::deployUnit() {
//    MyBattleMap* battleMap = (MyBattleMap*)node->getChildByTag(MainMapTag);
//    CreatorInfoBean* infoBean = CreatorInfoBean::create(PanzerIVCardId);
//    MyUnit* unit = infoBean->creator->createObj(infoBean->getLevel());
//    unit->setTag(infoBean->creator->cardId);
//
//    unit->setPosition(battleMap->transTiledToMap(ccp(25,50)));
//    unit->deployPosi = ccp(25,50);
//    
//    battleMap->CCNode::addChild(unit,999999);
//    battleMap->getUnits()->addObject(unit);
//    unit->doAI();
//}