//
//  Newbie4Trigger.cpp
//  ww3
//
//  Created by xiao tang on 12-12-20.
//
//

#include "Newbie4Trigger.h"
#include "DefineSet.h"
#include "GXShieldTouchMenuItem.h"
#include "MyPriorityMenu.h"
#include "SimpleAudioEngine.h"
#include "GXRemoveFromParentsAction.h"
#include "Mathlib.h"
#include "GXAnimateFX.h"
#include "MyBattleBuilding.h"
#include "GXFadeIn.h"
#include "GXFadeOut.h"
#include "LoadingScene.h"
#include "MyMessageManage.h"
#include "MyUtil.h"
#include "DialogCompleteMessage.h"
#include "GXJsonUtil.h"
#include "DiaLayer.h"

#define newbieFlowLayerTag 900
#define newbieMenuTag 901
#define planeLayerTag 902
#define cloudLayerTag 903
#define newbieBlackTag 904

Newbie4Trigger::~Newbie4Trigger(){
    CCLog("Newbie4Trigger has been released");
}

Newbie4Trigger* Newbie4Trigger::create(NewbieMovieScene* node) {
    Newbie4Trigger* trigger = new Newbie4Trigger();
    trigger->autorelease();
    trigger->scene = node;
    return trigger;
}

bool Newbie4Trigger::excuteMsg(MyBaseMessage* msg) {
//    if(dynamic_cast<Newbie1to2Message*>(msg) != NULL) {
//        MyMessageManage::getInstance()->unRegisterTrigger(this);
//        MyMessageManage::getInstance()->registerTrigger(Newbie2Trigger::create((NewbieStartScene*)node));
//    }
    if(msg->tag == DialogCompleteMessageTag) {
        DialogCompleteMessage* dMsg = (DialogCompleteMessage*)msg;
        if (dMsg->currentNode  >= dMsg->maxNode ) {
            toBeginScene(NULL);
        }
    }
    return false;
}

void Newbie4Trigger::toNextCallBack() {
//    CCLayer* newbieLayer = (CCLayer*)scene->getChildByTag(newbieFlowLayerTag);
//    
//    
//    CCMenuItemSprite* iKnow =CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("dialogkonw.png"), CCSprite::createWithSpriteFrameName("dialogknowp.png"),this,menu_selector(Newbie4Trigger::toBeginScene));
//    iKnow->setPosition(ccp(winSize.width/2+120,winSize.height/2-90));
//    
//    MyPriorityMenu* shieldMenu = (MyPriorityMenu*)newbieLayer->getChildByTag(newbieMenuTag);
//    shieldMenu->addChild(iKnow,-1);
    
    
//    CCLabelTTF* desc = CCLabelTTF::create(GXUtil::insertNewline("　　指挥官！我军基地遭到敌军空中打击，必须要进行战略转移，请立即下令。",14).c_str(), "Arial" , 30, CCSizeMake(440,200), kCCTextAlignmentLeft, kCCVerticalTextAlignmentTop);
//    desc->cocos2d::CCNode::setAnchorPoint(ccp(0.5,1));
//#if   (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
//    desc->setPosition(ccp(winSize.width/2+100,winSize.height/2+90+33/5));
//#endif
//#if   (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
//    desc->setPosition(ccp(winSize.width/2+100,winSize.height/2+90));
//#endif
//    desc->setColor(ccc3(230, 207, 185));
//    
//    newbieLayer->addChild(desc,3);
//    CCSprite* dialogBack = MyUtil::getInstance()->getDialogBack();
//    dialogBack->setPosition(ccp(winSize.width/2,winSize.height/2));
//    newbieLayer->addChild(dialogBack);
//    
//    iKnow->setOpacity(0);
////    newbieLayer->setScale(0.5);
////    newbieLayer->runAction(CCScaleTo::create(0.5, 1));
//    dialogBack->setOpacity(0);
//    shieldMenu->runAction(CCSequence::create(CCDelayTime::create(0.25),CCFadeIn::create(0.25),NULL));
//    dialogBack->runAction(CCSequence::create(CCDelayTime::create(0.25),CCFadeIn::create(0.25),NULL));
//    desc->setOpacity(0);
//    desc->runAction(CCSequence::create(CCDelayTime::create(0.25),CCFadeIn::create(0.25),NULL));
    CCString* str = GXUtil::readFile("NewbieDialog6.j");
    DiaLayer* dialog = DiaLayer::create(GXJsonUtil::parseDiaLayerInfoBean(str->getCString()));
    scene->addChild(dialog,31);
}

bool Newbie4Trigger::onRegist() {
    
    CCLayer* newbieLayer = CCLayer::create();
    newbieLayer->setTag(newbieFlowLayerTag);
    
    CCSprite* black = CCSprite::create("whiteImage.jpg");
    black->setColor(ccc3(0,0,0));
    black->setScaleX(winSize.width/black->getContentSize().width);
    black->setScaleY(winSize.height/black->getContentSize().height);
    newbieLayer->addChild(black);
    black->setTag(newbieBlackTag);
    black->setPosition(ccp(winSize.width/2,winSize.height/2));
    
    CCLabelTTF* label = CCLabelTTF::create("1939.10.31\n天气　晴\n于我军进攻同时", "Arial", 36,CCSizeZero, kCCTextAlignmentLeft, kCCVerticalTextAlignmentTop);
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
    menu->setTag(newbieMenuTag);
    
    CCLayer* planeLayer = CCLayer::create();
    planeLayer->setTag(planeLayerTag);
    
    CCSprite* plane1 =CCSprite::create("plane.png");
    plane1->setPosition(ccp(winSize.width/2+180,winSize.height/2+120));
    planeLayer->addChild(plane1,-1);
    
    CCSprite* plane2 =CCSprite::create("plane.png");
    plane2->setPosition(ccp(winSize.width/2+140,winSize.height/2-220));
    planeLayer->addChild(plane2,-1);
    
    CCSprite* plane3 =CCSprite::create("plane.png");
    plane3->setPosition(ccp(winSize.width/2-360,winSize.height/2+140));
    planeLayer->addChild(plane3,-1);
    planeLayer->setPosition(ccp(-960,-640));
    planeLayer->runAction(CCSequence::create(CCDelayTime::create(3), CCMoveTo::create(1, ccp(0,0)),CCCallFunc::create(this,callfunc_selector(Newbie4Trigger::inCallBack)), NULL));

    newbieLayer->addChild(menu,10);
//    scene->getMap()->runAction();
    
//    scene->getMap()->runAction(cocos2d::CCAction *action)
    scene->getMap()->setPosition(ccp(0,0));
    
    
    CCLayer* cloudLayer = CCLayer::create();
    CCSprite* cloud1 = CCSprite::createWithSpriteFrameName("cloud1.png");
    cloud1->setPosition(ccp(arc4random()%960,arc4random()%640));
    cloud1->setRotation(arc4random()%360);
    cloud1->setOpacity(arc4random()%100+155);
    cloud1->setScale(((float)((arc4random()%70))/100 +0.3)*2);
    float distanceX =  -cloud1->getContentSize().width - cloud1->getPositionX();
//    CCLog("%f",distanceX);
    cloud1->runAction(CCSequence::create(CCMoveBy::create(4,ccp(120,80)),CCMoveBy::create(-(distanceX/480),ccp(distanceX,distanceX*0.6666)),CCCallFuncND::create(this, callfuncND_selector(Newbie4Trigger::cloudCallBack), (void*)cloud1),NULL));
    
    CCSprite* cloud2 = CCSprite::createWithSpriteFrameName("cloud2.png");
    cloud2->setPosition(ccp(arc4random()%960,arc4random()%640));
    cloud2->setRotation(arc4random()%360);
    cloud2->setOpacity(arc4random()%100+155);
    cloud2->setScale((((float)(arc4random()%70))/100 +0.3)*2);
    distanceX =  -cloud2->getContentSize().width - cloud2->getPositionX();
    //    CCLog("%f",distanceX);
    cloud2->runAction(CCSequence::create(CCMoveBy::create(4,ccp(120,80)),CCMoveBy::create(-(distanceX/480),ccp(distanceX,distanceX*0.6666)),CCCallFuncND::create(this, callfuncND_selector(Newbie4Trigger::cloudCallBack), (void*)cloud2),NULL));
    
    CCSprite* cloud3 = CCSprite::createWithSpriteFrameName("cloud3.png");
    cloud3->setPosition(ccp(arc4random()%960,arc4random()%640));
    cloud3->setRotation(arc4random()%360);
    cloud3->setOpacity(arc4random()%100+155);
    cloud3->setScale((((float)(arc4random()%70))/100 +0.3)*2);
    distanceX =  -cloud3->getContentSize().width - cloud3->getPositionX();
    //    CCLog("%f",distanceX);
    cloud3->runAction(CCSequence::create(CCMoveBy::create(4,ccp(120,80)),CCMoveBy::create(-(distanceX/480),ccp(distanceX,distanceX*0.6666)),CCCallFuncND::create(this, callfuncND_selector(Newbie4Trigger::cloudCallBack), (void*)cloud3),NULL));
    
    
    scene->getMap()->runAction(CCSequence::create(CCDelayTime::create(15),CCCallFuncND::create(this, callfuncND_selector(Newbie4Trigger::crashCallBack), (void*)scene->getMap()), NULL));
    
    cloudLayer->addChild(cloud1);
    cloudLayer->addChild(cloud2);
    cloudLayer->addChild(cloud3);
    cloudLayer->setTag(cloudLayerTag);
    
    scene->addChild(newbieLayer,30);
    scene->addChild(planeLayer,29);
    scene->addChild(cloudLayer,28);
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("sfx_planeflying.mp3",false);
    
    CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect("sfx_planehongzha.mp3");
    return false;
}

bool Newbie4Trigger::onUnRegist() {
//    node->removeChildByTag(newbieFlowLayerTag, true);
    return true;
}

void Newbie4Trigger::inCallBack()
{
    scene->getMap()->runAction(CCSequence::create(CCMoveTo::create(30,ccp( -3600+winSize.width,-2400+winSize.height)),CCCallFunc::create(this, callfunc_selector(Newbie4Trigger::outCallBack)),NULL));
//    scene->getChildByTag(cloudLayerTag)->
}

void Newbie4Trigger::outCallBack(cocos2d::CCNode *pSender){
    scene->getChildByTag(planeLayerTag)->runAction(CCSequence::create(CCMoveTo::create(1,ccp(winSize.width,winSize.height)),GXRemoveFromParentsAction::create(),NULL));
    CCLayer* cloudLayer = (CCLayer*)scene->getChildByTag(cloudLayerTag);
    CCObject* obj =NULL;
    CCARRAY_FOREACH(cloudLayer->getChildren(), obj) {
        CCSprite* cloud = (CCSprite*)obj;
        cloud->stopAllActions();
        cloud->runAction(CCMoveBy::create(80,ccp(2400,1600)));
    }
//    scene->getChildByTag(newbieFlowLayerTag)->getChildByTag(newbieBlackTag)->runAction(CCSequence::create(CCCallFunc::create(this,callfunc_selector(Newbie4Trigger::toNextCallBack)),CCFadeIn::create(2),NULL));
}

void Newbie4Trigger::cloudCallBack(CCNode* pSender,CCSprite* cloud) {
    float posiX= 960+cloud->getContentSize().width;
    cloud->setPosition(ccp(posiX,200+arc4random()%1280));
    cloud->setRotation(arc4random()%360);
    cloud->setOpacity(arc4random()%100+155);
    cloud->setScale((((float)(arc4random()%70))/100 +0.3)*2);
    float distanceX =  -cloud->getContentSize().width - cloud->getPositionX();
    //    CCLog("%f",distanceX);
    cloud->runAction(CCSequence::create(CCMoveBy::create(-(distanceX/480),ccp(distanceX,distanceX*0.6666)),CCCallFuncND::create(this, callfuncND_selector(Newbie4Trigger::cloudCallBack), (void*)cloud),NULL));
}

void Newbie4Trigger::crashCallBack(cocos2d::CCNode *pSender,MyBattleMap* map) {
    if (status == 0) {
        CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sfx_planehongzha.mp3");
        map->runAction(CCSequence::create(CCDelayTime::create(1),CCCallFuncND::create(this, callfuncND_selector(Newbie4Trigger::crashCallBack), (void*)map), NULL));
        
//        scheduleOnce(schedule_selector(Newbie4Trigger::crashCallBack), 1);
        status++;
    } else if(status < 6) {
        CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sfx_planeBoom.mp3");
        for (int i = 0; i<5; i++) {
            GXAnimateFX* fx = GXAnimateFX::createWithAnitmateFrameName("antitankBoom", true, false);
            fx->setPosition(map->transTiledToMap(ccp(20+i*4,41-status*4)));
            map->CCNode::addChild(fx,9999999);
        }
        CCObject* obj;
        CCARRAY_FOREACH(map->getItems(), obj) {
            MyBattleBuilding* building = (MyBattleBuilding*)obj;
            if (building->isAlive()&& building->getPositionByTiled().y>41-status*4) {
                building->dispose();
            }
        }
        
        
        map->runAction(CCSequence::create(CCDelayTime::create(2),CCCallFuncND::create(this, callfuncND_selector(Newbie4Trigger::crashCallBack), (void*)map), NULL));
        
        status++;
    } else {
        scene->getChildByTag(newbieFlowLayerTag)->getChildByTag(newbieBlackTag)->runAction(CCSequence::create(CCDelayTime::create(3),CCCallFunc::create(this,callfunc_selector(Newbie4Trigger::toNextCallBack)),CCFadeIn::create(2),NULL));
    }
    
}

void Newbie4Trigger::toBeginScene(cocos2d::CCNode *pSender) {
    CCUserDefault::sharedUserDefault()->setBoolForKey("newbieTag", true);
    CCUserDefault::sharedUserDefault()->flush();
    LoadingScene* scene = LoadingScene::create();
    CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.2, scene, ccBLACK));
    MyMessageManage::getInstance()->unRegisterTrigger(this);
}