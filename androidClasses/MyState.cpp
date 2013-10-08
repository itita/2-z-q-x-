//
//  MyState.cpp
//  ww2
//
//  Created by DingYu Fu on 12-9-2.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "MyState.h"
#include "GXFadeOut.h"
#include "MyGameFactory.h"
#include "DefineSet.h"
#include "MyGameInfo.h"
#include "MyUtil.h"
#include "Mathlib.h"
#include "GXRemoveFromParentsAction.h"
#include "MyPriorityMenu.h"


MyState::MyState() {
    building = NULL;
    input_output = cocos2d::CCDictionary::create();
    input_output->retain();
    itemDictionary = CCDictionary::create();
    itemDictionary->retain();
    item = NULL;
}

MyState::~MyState() {
    CC_SAFE_RELEASE_NULL(item);
//    CCMenuItem* menuitem;
//    CCArray* tags = getAllInput();
//    CCObject* obj;
//    CCARRAY_FOREACH(tags, obj) {
//        menuitem = dynamic_cast<CCMenuItem*>(itemDictionary->objectForKey(((CCInteger*)obj)->getValue()));
//        menuitem->setVisible(false);
//        menuitem->scheduleOnce(schedule_selector(CCMenuItem::removeFromParentAndCleanup), 0);
//        removeFromParentAndCleanup(true);
//    }
    CC_SAFE_RELEASE_NULL(itemDictionary);
}

MyState* MyState::create(int _stateId,CCSprite* item) {
    MyState* pState = new MyState();
    pState->stateId = _stateId;
//    pState->input_output = cocos2d::CCDictionary::create();
//    pState->input_output->retain();
    pState->autorelease();
//    pState->itemDictionary = CCDictionary::create();
//    pState->itemDictionary->retain();
    return pState;
}

void MyState::doState() {
//    CCLog("do child");
}

void MyState::init(MyBuilding* building) {
    this->building = building;
}

void MyState::dismissAllTransition() {
//    CCMenu* transitionMenu = (CCMenu*)building->getChildByTag(transitionMenuTag);
//    if (transitionMenu == NULL) {
//        return;
//    }
//    CCArray* tags = transitionMenu->getChildren();
//    CCObject* obj;
//    CCMenuItem* menuitem;
//    CCARRAY_FOREACH(tags, obj) {
//       //TODO
//        menuitem = dynamic_cast<CCMenuItem*>(obj);
//        if (menuitem->getParent() != NULL ) {
//            //            item->setOpacity(0);
//            menuitem->stopAllActions();
//            menuitem->runAction(CCFadeOut::create(0.15));
////            item->setVisible(false);
//            menuitem->setEnabled(false);
//        }
//    }
//    transitionMenu->setTag(-1);
//    transitionMenu->runAction(CCSequence::create(CCDelayTime::create(0.15),GXRemoveFromParentsAction::create(),NULL));
    if(building->getParent() != NULL) {
        building->getParent()->getParent()->removeChildByTag(zhuyeMenuTag,true);
    }
}

void MyState::showAllTransition() {
//    if (building->getParent()->getParent()->getChildByTag(zhuyeMenuTag) != NULL) {
//        return;
//    }
    building->getParent()->getParent()->removeChildByTag(zhuyeMenuTag,true);
    
    CCLayer* layer = CCLayer::create();
    layer->setTag(zhuyeMenuTag);
    
    CCArray* tags = getAllInput();
    CCObject* obj;
//    CCMenuItem* menuItem;
    //    CCInteger* i;
//    MyPriorityMenu* menu = MyPriorityMenu::create(-502,NULL,NULL);
    building->displaySummary();
    MyPriorityMenu* zhuyemenu = MyPriorityMenu::create(-502,NULL,NULL);
//    building->displaySummary();
    int i = 0;
    float posi = tags->count()*120;
    CCARRAY_FOREACH(tags, obj) {
//        menuItem = dynamic_cast<TransitionInfo*>(itemDictionary->objectForKey(((CCInteger*)obj)->getValue()))->getButton();
//        
//        menuItem->runAction(CCFadeTo::create(0.15,255));
//        menu->addChild(menuItem);
       
        MyMenuItem* item2 = (MyMenuItem*)dynamic_cast<TransitionInfo*>(itemDictionary->objectForKey(((CCInteger*)obj)->getValue()))->getButton();
        zhuyemenu->addChild(item2);
        item2->setScale(1.3);
        item2->setOpacity(100-i*20);
//        item2->setOpacity(0);
        item2->setPosition(ccp(-posi/2+i*120+60,-30));
        item2->runAction(CCSpawn::create(CCSequence::create(CCDelayTime::create(0.07+0.05*(tags->count()-i)),CCFadeTo::create(0.23,255),NULL),CCSequence::create( CCDelayTime::create(0.05*(tags->count()-i)),CCEaseElasticOut::create(CCMoveBy::create(0.3,ccp(0,100)),1.3),NULL),NULL));
       i++;
    }
//    menu->alignItemsHorizontallyWithPadding(25);
//    menu->setTag(transitionMenuTag);
//    menu->setPosition( ccp(0,building->y +60));
//    building->addChild(menu);
  
    zhuyemenu->setPosition(ccp(winSize.width/2-10,0));
//    zhuyemenu->alignItemsHorizontallyWithPadding(15);
   
    char str[100] = {0};
    sprintf(str, "%s (等级 %d)",building->getBuildingName(),building->getLevel());
    CCLabelTTF* name = CCLabelTTF::create(str,"Arial",30);
    name->setColor(ccWHITE);
    name->setPosition(ccp(winSize.width/2-10,150));
    name->runAction(CCFadeIn::create(0.3));
    
    CCSprite* nameBackCenter = CCSprite::createWithSpriteFrameName("nameKuang2.png");
    nameBackCenter->setPosition(ccp(winSize.width/2-10,150));
    nameBackCenter->setScaleX((name->getContentSize().width+20)/nameBackCenter->getContentSize().width);
    nameBackCenter->runAction(CCFadeIn::create(0.3));
    
    CCSprite* nameBackLeft = CCSprite::createWithSpriteFrameName("nameKuang1.png");
    nameBackLeft->setAnchorPoint(ccp(1,0.5));
    nameBackLeft->setPosition(ccp(winSize.width/2-18-name->getContentSize().width/2 ,150));
    nameBackLeft->runAction(CCFadeIn::create(0.3));
    
    CCSprite* nameBackRight = CCSprite::createWithSpriteFrameName("nameKuang1.png");
    nameBackRight->setAnchorPoint(ccp(1,0.5));
    nameBackRight->setRotation(180);
    nameBackRight->setPosition(ccp(winSize.width/2+name->getContentSize().width/2-2 ,150));
    nameBackRight->runAction(CCFadeIn::create(0.3));
    
    
    layer->addChild(zhuyemenu);
    layer->addChild(nameBackLeft);
    layer->addChild(nameBackCenter);
    layer->addChild(nameBackRight);
    layer->addChild(name);
    building->getParent()->getParent()->addChild(layer);
    
}


void MyState::addTransition(int inputId, int ioutputId, cocos2d::CCObject *menuitem) {
    GXFSMstate::addTransition(inputId, ioutputId);
    itemDictionary->setObject(menuitem, inputId);
}

TransitionInfo* MyState::getTransition(int inputId) {
    return (TransitionInfo*)(itemDictionary->objectForKey(inputId));
}


void MyState::infoCallBack(cocos2d::CCObject *pSender) {
    StartScene* scene =  ((StartScene*)(building->map->getParent()));
    scene->removeChildByTag(updateLayerTag, true);
    CCLayer* infoLayer = MyUtil::getInstance()->getInfoDialog();
    scene->addChild(infoLayer);
    
    CCSprite* metalButton = CCSprite::createWithSpriteFrameName("metalButton.png");
    CCSprite* startLabel1 = CCSprite::createWithSpriteFrameName("sellButtonLabel.png");
    startLabel1->setScaleY(1.1111);
    startLabel1->setPosition(ccp(metalButton->getContentSize().width/2,metalButton->getContentSize().height/2+3));
    startLabel1->setColor(ccc3(200,222,222));
    metalButton->addChild(startLabel1);
    
    CCSprite* metalButtonP = CCSprite::createWithSpriteFrameName("metalButtonP.png");
    CCSprite* startLabel2 = CCSprite::createWithSpriteFrameName("sellButtonLabel.png");
    startLabel2->setPosition(ccp(metalButtonP->getContentSize().width/2,metalButtonP->getContentSize().height/2+3));
    startLabel2->setScaleY(1.1111);
    startLabel2->setColor(ccc3(200,222,222));
    metalButtonP->addChild(startLabel2);
    
    CCMenuItemSprite* sellButton = CCMenuItemSprite::create(metalButton, metalButtonP,building,menu_selector(MyBuilding::sellCallBack));
    sellButton->setPosition(ccp(0,-140));
    sellButton->setScaleY(0.9);
    if(building->getTag()!=zhihuisuoTag) {
        ((CCMenu*)infoLayer->getChildByTag(updateMenuTag))->addChild(sellButton);
        
        if (building->resourceTag != diamondTag) {
            CCSprite* resourceIcon = MyUtil::getInstance()->getResourceIcon(building->resourceTag);
            resourceIcon->setScale(25/resourceIcon->getContentSize().height);
            resourceIcon->setPosition(ccp(-40,-178));
            infoLayer->addChild(resourceIcon);
        } else {
            CCSprite* resourceIcon = CCSprite::createWithSpriteFrameName("ironIcon.png");
            resourceIcon->setScale(25/resourceIcon->getContentSize().height);
            resourceIcon->setPosition(ccp(-40,-178));
            infoLayer->addChild(resourceIcon);
        }
        char str[12] = {0};
        if (building->getTag() >= ornamentsDefineTag) {
            
            sprintf(str, "-%d",(int)(MyUtil::getInstance()->updateLevelBySquare(building->getSummaryCount(), building->getLevel()-1, updateSummaryRate)/2));
            
        } else {
            
            if (building->resourceTag != diamondTag) {
                sprintf(str, "+%d",(int)(MyUtil::getInstance()->updateLevelBySquare(building->getSummaryCount(), building->getLevel()-1, updateSummaryRate)/4));
            } else {
                sprintf(str, "+%d",(int)(MyUtil::getInstance()->updateLevelBySquare(building->getSummaryCount()*10, building->getLevel()-1, updateSummaryRate)/4));
            }
        }
        CCLabelTTF* summaryResourceCount = CCLabelTTF::create(str, "Arial", 24);
        summaryResourceCount->setColor(ccc3(254,218,130));
        summaryResourceCount->setAnchorPoint(ccp(0.5,0.5));
        
        summaryResourceCount->setPosition(ccp(Mathlib::max(summaryResourceCount->getContentSize().width/2-24, 6),-180) );
        infoLayer->addChild(summaryResourceCount);
    }
}




void MyState::clickCallBack() {
    item->runAction(CCSequence::create(CCScaleTo::create(0.1, 1.15), CCScaleTo::create(0.1, 1.0),NULL));
    //同时把提示也给显示了吧
    building->setActive(true);
    //在building 里面重写
    showAllTransition();
}

void MyState::setItem(CCSprite* item) {
    
}

CCSprite* MyState::getItem() {
    return item;
}

//void MyState::removeAllTransiton() {
//    CCArray* tags = getAllInput();
//    CCObject* obj;
//    CCMenuItem* menuitem;
//    CCARRAY_FOREACH(tags, obj) {
//        //TODO
//        menuitem = dynamic_cast<CCMenuItem*>(itemDictionary->objectForKey(((CCInteger*)obj)->getValue()));
//        if (menuitem->getParent() != NULL ) {
//            //            item->setOpacity(0);
//            menuitem->stopAllActions();
//            menuitem->setVisible(false);
//            menuitem->runAction(GXRemoveFromParentsAction::create());
//        }
//    }
//}

CCMenuItem* TransitionInfo::getButton() {
    CCMenuItem* item = MyMenuItem::create(CCSprite::createWithSpriteFrameName(spriteName.c_str()),rec,selector);
    item->setTag(this->tag);
    return item;
}

TransitionInfo* TransitionInfo::create(int _tag,const std::string& _spriteName,CCObject* _rec,SEL_MenuHandler _selector) {
    TransitionInfo* info = new TransitionInfo();
    info->autorelease();
    info->tag = _tag;
    info->spriteName = _spriteName;
    info->rec = _rec;
    //为避免循环持有，rec不retain也不release;
    info->selector = _selector;
    return info;
}

//MyStateCreator::MyStateCreator() {
//    stateId=0;
//    CCMenuItemSpriteName=NULL;
//    transitionMap = CCDictionary::create();
//    itemAnchor= ccp(0.5,0.5);
//    transitionMap->retain();
//}
//
//MyStateCreator* MyStateCreator::create() {
//    MyStateCreator* creator = new MyStateCreator();    
//    creator->autorelease();
//    return creator;
//}
//
//CCObject* MyStateCreator::createObj() {
//    
//    return NULL;
//}

//void MyStateCreator::doFill(cocos2d::CCObject *entity) {
//    CCArray* keys =  transitionMap->allKeys();
//    CCObject* obj;
//    CCARRAY_FOREACH(keys, obj) {
//        
//    }
//}

