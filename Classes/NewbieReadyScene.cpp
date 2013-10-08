//
//  NewbieReadyScene.cpp
//  ww4
//
//  Created by xiao tang on 13-1-5.
//
//

#include "NewbieReadyScene.h"
#include "MyUtil.h"
#include "DefineSet.h"
#include "Mathlib.h"
#include "MyGameFactory.h"
#include "MyMessageManage.h"
#include "NewbieReadyTrigger.h"
#include "TransitonScene.h"


NewbieReadyScene* NewbieReadyScene::create() {
    NewbieReadyScene *pRet = new NewbieReadyScene();
    pRet->myInit();
    pRet->autorelease();
    return pRet;
}

void NewbieReadyScene::myInit(){
    loadResource();
    CCLayer* backLayer = CCLayer::create();
    backLayer->setPosition(ccp(0,0));
    
    CCSprite* back = CCSprite::createWithSpriteFrameName("area1.jpg");
    back->setPosition(ccp(winSize.width/2,winSize.height/2));
    backLayer->addChild(back);
    this->addChild(backLayer);
    
//    bean
    CCMenu* menu =CCMenu::create();
    menu->setPosition(ccp(0,0));

    CCSprite* baseIcon1Sprite = CCSprite::createWithSpriteFrameName("baseIcon5.png");
    baseIcon1Sprite->setColor(ccGRAY);
    CCMenuItemSprite* baseIcon1 = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("baseIcon5.png"),baseIcon1Sprite,this,menu_selector(NewbieReadyScene::toNewbieBattleCallback));
    
    baseIcon1->setPosition(ccp(winSize.width/2-200,270));
    
    CCMenuItemSprite* baseui1 = getBaseInfoItem();
   
    baseui1->setPosition(ccp(winSize.width/2-200,380));
    menu->addChild(baseIcon1);
    menu->addChild(baseui1);
    this->addChild(menu);
    menu->setTag(baseMenuTag);
    
    initCloud();
    MyMessageManage::getInstance()->registerTrigger(NewbieReadyTrigger::create(this));
}

CCMenuItemSprite* NewbieReadyScene::getBaseInfoItem() {
    CCSprite* baseui1Sprite = CCSprite::create("baseui.png");
    baseui1Sprite->setColor(ccGRAY);
    CCMenuItemSprite* baseui1 = CCMenuItemSprite::create(CCSprite::create("baseui.png"), baseui1Sprite,this,menu_selector(NewbieReadyScene::toNewbieBattleCallback));
    //    CCMenuItemSprite*
    
    CCSprite* rank1 =  MyUtil::getInstance()->getRankSprite(5555);
    rank1->setAnchorPoint(ccp(0.5,0.5));
    rank1->setPosition(ccp(20,25));
    rank1->setScale(0.4);
    baseui1->addChild(rank1);
    
    CCLabelTTF* rankname = CCLabelTTF::create(MyUtil::getInstance()->getRankString(5555), "Arial", 16);
    rankname->setAnchorPoint(ccp(0.5,0.5));
    rankname->setPosition(ccp(50,25));
    rankname->setColor(ccc3(246, 255, 0));
    baseui1->addChild(rankname);
    
    CCLabelAtlas* level1 = CCLabelAtlas::create("15", "levelupnumber.png", 40, 32, '0');
    level1->setAnchorPoint(ccp(0.5,0.5));
    level1->setPosition(ccp(50,44));
    level1->setScale(0.4);
    baseui1->addChild(level1);
    
    CCLabelTTF* name = CCLabelTTF::create("德军前哨", "Arial", 17);
    name->setAnchorPoint(ccp(0.5,0.5));
    name->setPosition(ccp(120,88));
    name->setColor(ccBLACK);
    baseui1->addChild(name);
    
    CCLabelTTF* resourceCount = CCLabelTTF::create("略少", "Arial", 20);
    resourceCount->setAnchorPoint(ccp(0.5,0.5));
    resourceCount->setPosition(ccp(138,56));
    resourceCount->setColor(ccc3(246, 255, 0));
    baseui1->addChild(resourceCount);
    
    CCLabelTTF* defenSucc = CCLabelTTF::create("82%", "Arial", 20);
    defenSucc->setAnchorPoint(ccp(0.5,0.5));
    defenSucc->setPosition(ccp(138,31));
    defenSucc->setColor(ccc3(246, 255, 0));
    baseui1->addChild(defenSucc);
    return baseui1;
}

void NewbieReadyScene::toNewbieBattleCallback() {
    CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.2, TransitonScene::create(NewbieBattleSceneClassTag, CCString::create("NewbieBattleBase.j")) , ccBLACK));
}
