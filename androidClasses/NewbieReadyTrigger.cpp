//
//  NewbieReadyTrigger.cpp
//  ww4
//
//  Created by xiao tang on 13-1-5.
//
//

#include "NewbieReadyTrigger.h"
#include "DefineSet.h"
#include "MyPriorityMenu.h"
#include "GXShieldTouchMenuItem.h"
#include "SimpleAudioEngine.h"
#include "GXReverseSheild.h"
#include "MyUtil.h"
#include "MyMessageManage.h"
#include "DiaLayer.h"
#include "GXJsonUtil.h"
#include "DialogCompleteMessage.h"

#define newbieFlowLayerTag 900
#define dialogLayerTag 901
#define grayTag 902

NewbieReadyTrigger::~NewbieReadyTrigger(){
    CCLog("NewbieReadyTrigger has been released");
}

NewbieReadyTrigger* NewbieReadyTrigger::create(NewbieReadyScene* node) {
    NewbieReadyTrigger* trigger = new NewbieReadyTrigger();
    trigger->autorelease();
    trigger->scene = node;
    return trigger;
}

bool NewbieReadyTrigger::excuteMsg(MyBaseMessage* msg) {
    if(msg->tag == DialogCompleteMessageTag) {
        DialogCompleteMessage* dMsg = (DialogCompleteMessage*)msg;
        if (dMsg->currentNode  >= 3 ) {
            toNextCallBack(NULL);
            if (dMsg->currentNode == dMsg->maxNode-1) {
                ((DiaLayer*)scene->getChildByTag(dialogLayerTag))->isEnable = false;
            }
        }
    }
    return false;
}

void NewbieReadyTrigger::toNextCallBack(cocos2d::CCNode *node){
//    CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sfx_click.mp3");
    if(status == 0) {
        scene->removeChildByTag(newbieFlowLayerTag, true);
        CCLayer* newbieLayer = CCLayer::create();
        newbieLayer->setPosition(ccp(0,0));
        newbieLayer->setTag(newbieFlowLayerTag);
        
        
        CCSprite* spotLight = CCSprite::create("spotlight.png");
        spotLight->setScale(4);
        spotLight->setPosition(ccp(winSize.width/2-160, 270));
        spotLight->setTag(grayTag);
        
        CCSprite* trans = CCSprite::create("transparent.png");
        trans->setContentSize(winSize);
        CCMenuItemSprite* nextButton = CCMenuItemSprite::create(trans, CCSprite::create("transparent.png"),this,menu_selector(NewbieReadyTrigger::toNextCallBack));
        MyPriorityMenu* menu = MyPriorityMenu::create(-499, nextButton,NULL);
        menu->setPosition(ccp(0,0));
//        menu->setTag(newbieMenuTag);
        nextButton->setPosition(ccp(winSize.width/2,winSize.height/2));
        nextButton->setContentSize(winSize);
        newbieLayer->addChild(menu,10);
    
        scene->addChild(spotLight,10);
        scene->addChild(newbieLayer,9);
        
        status++;
    }
//    else if (status == 1) {
//        CCLabelTTF* label = CCLabelTTF::create(GXUtil::insertNewline("这里显示敌军基地鸟瞰，一共从小到大有5个等级",11).c_str(), "Arial" , 30, CCSizeZero, kCCTextAlignmentLeft, kCCVerticalTextAlignmentTop);
//        label->setColor(ccWHITE);
//        label->setAnchorPoint(ccp(0,0.5));
//#if   (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
//        label->setPosition(ccp(winSize.width/2-110,240));
//#endif
//#if   (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
//        label->setPosition(ccp(winSize.width/2-110,240+24/5));
//#endif
//        scene->getChildByTag(newbieFlowLayerTag)->addChild(label,10);
//        status++;
//    }
    else if (status == 1) {
        scene->reorderChild(scene->getChildByTag(baseMenuTag), 20);
        status++;
    }
//    else if (status == 3) {
//        CCLabelTTF* label = CCLabelTTF::create(GXUtil::insertNewline("这里分别显示了敌人的昵称，等级，军衔，资源范围，防御成功率",11).c_str(), "Arial" , 30, CCSizeZero, kCCTextAlignmentLeft, kCCVerticalTextAlignmentTop);
//        label->setColor(ccWHITE);
//        label->setAnchorPoint(ccp(0,0.5));
//#if   (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
//        label->setPosition(ccp(winSize.width/2-110,370));
//#endif
//#if   (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
//        label->setPosition(ccp(winSize.width/2-110,370+31/5));
//#endif
//        scene->getChildByTag(newbieFlowLayerTag)->addChild(label,10);
//        status++;
//    }
    else if(status == 2) {
        scene->getChildByTag(grayTag)->runAction(CCFadeOut::create(0.2));
        scene->removeChildByTag(newbieFlowLayerTag, true);
//        CCLabelTTF* label = CCLabelTTF::create("　　点击进攻基地！", "Arial" , 55);
//        label->setColor(ccRED);
//        label->runAction(CCRepeatForever::create(static_cast<CCSequence*>(CCSequence::create(CCFadeOut::create(1),CCFadeIn::create(1),NULL))));
//        label->setPosition(ccp(winSize.width/2,150));
//        scene->addChild(label);
//        status++;
        MyMessageManage::getInstance()->unRegisterTrigger(this);
    }
}

bool NewbieReadyTrigger::onRegist() {
    CCLayer* newbieLayer = CCLayer::create();
    
//    GXShieldTouchMenuItem* shield = GXShieldTouchMenuItem::create();
//    shield->setContentSize(winSize);
//    shield->setPosition(ccp(winSize.width/2,winSize.height/2));
    
//    CCMenuItemSprite* iKnow =CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("dialogkonw.png"), CCSprite::createWithSpriteFrameName("dialogknowp.png"),this,menu_selector (NewbieReadyTrigger::toNextCallBack));
//    iKnow->setPosition(ccp(winSize.width/2+120,winSize.height/2-90));
    
//    MyPriorityMenu* shieldMenu = MyPriorityMenu::create(-600,iKnow, shield,NULL);
//    shieldMenu->setPosition(ccp(0,0));
    
    
//    CCLabelTTF* desc = CCLabelTTF::create(GXUtil::insertNewline("　　指挥官，敌人基地就在前方不远处，看上去敌人并没有提高警惕，我们应该当机立断，立刻突袭！",14).c_str(), "Arial" , 30, CCSizeMake(440,200), kCCTextAlignmentLeft, kCCVerticalTextAlignmentTop);
//    desc->cocos2d::CCNode::setAnchorPoint(ccp(0.5,1));
//#if   (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
//    desc->setPosition(ccp(winSize.width/2+100,winSize.height/2+90+46/5));
//#endif
//#if   (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
//    desc->setPosition(ccp(winSize.width/2+100,winSize.height/2+90));
//#endif
    
//    desc->setColor(ccc3(230, 207, 185));
    
//    newbieLayer->addChild(desc,3);
//    newbieLayer->addChild(shieldMenu,2);
//    CCSprite* dialogBack = MyUtil::getInstance()->getDialogBack();
//    dialogBack->setPosition(ccp(winSize.width/2,winSize.height/2));
//    newbieLayer->addChild(dialogBack);
    newbieLayer->setTag(newbieFlowLayerTag);
    scene->addChild(newbieLayer);
    
//    newbieLayer->setScale(0.5);
//    newbieLayer->runAction(CCScaleTo::create(0.5, 1));
//    shieldMenu->setOpacity(0);
//    dialogBack->setOpacity(0);
//    shieldMenu->runAction(CCSequence::create(CCDelayTime::create(0.25),CCFadeIn::create(0.25),NULL));
//    dialogBack->runAction(CCSequence::create(CCDelayTime::create(0.25),CCFadeIn::create(0.25),NULL));
//    desc->setOpacity(0);
//    desc->runAction(CCSequence::create(CCDelayTime::create(0.25),CCFadeIn::create(0.25),NULL));
    CCSprite* gray = CCSprite::create("whiteImage.jpg");
    gray->setScaleX(winSize.width/gray->getContentSize().width);
    gray->setScaleY(winSize.width/gray->getContentSize().height);
    gray->setPosition(ccp(winSize.width/2,winSize.height/2));
    gray->setOpacity(153);
    gray->setColor(ccc3(0,0,0));
    newbieLayer->addChild(gray);
    
    CCString* str = GXUtil::readFile("NewbieDialog3.j");
    DiaLayer* dialog = DiaLayer::create(GXJsonUtil::parseDiaLayerInfoBean(str->getCString()));
    dialog->setTag(dialogLayerTag);
    scene->addChild(dialog,11);
    return false;
}

bool NewbieReadyTrigger::onUnRegist() {
    //    node->removeChildByTag(newbieFlowLayerTag, true);
    return true;
}
