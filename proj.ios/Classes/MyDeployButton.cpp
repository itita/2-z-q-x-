//
//  MyDeployButton.cpp
//  ww2
//
//  Created by DingYu Fu on 12-9-6.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "MyDeployButton.h"
#include "DefineSet.h"
#include "MyGameFactory.h"
#include "MyUtil.h"
#include "MyGameInfo.h"
#include "Mathlib.h"
#include "SimpleAudioEngine.h"
#include "NoResourceToDeployMessage.h"
#include "GarbageResourceCollection.h"


MyDeployButton* MyDeployButton::create(CreatorInfoBean* _bean, cocos2d::CCObject *target, SEL_MenuHandler selector) {
    MyDeployButton *pRet = new MyDeployButton();
    char str[30] = {0};
    sprintf(str, "deployBack%d.png",_bean->creator->getRarity());
    CCSprite* normalSprite = CCSprite::createWithSpriteFrameName(str);
    CCSprite* selectSprite = CCSprite::createWithSpriteFrameName("deployBackP.png");
    
    pRet->currentCool = pRet->cooldown;

    selectSprite->setPosition(ccp(-10,-10));
    if (pRet && pRet->initWithNormalSprite(normalSprite, selectSprite, NULL, target, selector))
    {
        char str1[30] = {0};
        sprintf(str, "%s.plist",_bean->creator->getSpriteFileName());
        sprintf(str1, "%s.pvr.ccz",_bean->creator->getSpriteFileName());
        GXUtil::loadResourceUtilSucc(str,str1);
        GarbageResourceCollection::getInstance()->addGarbage(str,CCString::create(str1));
        pRet->bean = _bean;
        pRet->bean->retain();
        pRet->reorderChild(selectSprite, -1);
        pRet->autorelease();
        pRet->initDescription();
        
        CCSprite* _blackBack = CCSprite::create("whiteImage.jpg");
        _blackBack->setScaleX(normalSprite->getContentSize().width/_blackBack->getContentSize().width);
        _blackBack->setScaleY(0);
        _blackBack->setColor(ccc3(0,0,0));
        _blackBack->setOpacity(150);
        _blackBack->setAnchorPoint(ccp(0.5,0));
        _blackBack->setPosition(ccp(normalSprite->getContentSize().width/2,0));
        _blackBack->retain();
        pRet->addChild(_blackBack);
        pRet->blackBack = _blackBack;
    
        pRet->schedule(schedule_selector(MyDeployButton::recovereyCoolDown),1);
        
        return pRet;
    }
//
    CC_SAFE_DELETE(pRet);
    return NULL;
}

MyDeployButton::~MyDeployButton(){
//    char str[30] = {0};
//    
//    sprintf(str, "%s.plist",bean->creator->getSpriteFileName());
//    CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile(str);
//    
//    sprintf(str, "%s.pvr.ccz",bean->creator->getSpriteFileName());
//    CCTextureCache::sharedTextureCache()->removeTextureForKey(str);
    

    CC_SAFE_RELEASE_NULL(bean);
    CC_SAFE_RELEASE_NULL(blackBack);
    CC_SAFE_RELEASE_NULL(summaryCount);

//    CCLog("MyDeployButton released");
//    spriteName->release();
}

void MyDeployButton::initDescription() {
    char str[22] = {0};
    sprintf(str, "%sbp.png",bean->creator->getSpriteFileName());
    CCSprite* bp = CCSprite::createWithSpriteFrameName(str);
    bp->setScale(Mathlib::min(115/bp->getContentSize().width, 90/bp->getContentSize().height));
    this->addChild(bp);
    bp->setPosition(ccp(53,49));
    CCSprite* sprite = CCSprite::createWithSpriteFrameName("oilIcon.png");
    sprite->setPosition(ccp(10,-20));
    sprite->setScale(0.6);
    this->addChild(sprite);
    
    summaryCount->setValue((int)MyUtil::getInstance()->updateLevelByRate(bean->creator->summaryOriOil,bean->creator->getSummaryOil(), bean->getLevel(), bean->creator->updateCostRate));
    
    sprintf(str, "%d",summaryCount->getValue());
    CCLabelTTF* label = CCLabelTTF::create(str, "arial", 30);
    label->setAnchorPoint(ccp(0,0.5));
    label->setPosition(ccp(22,-20));
    this->addChild(label);
    sprintf(str, "Lv:%d", bean->getLevel());
    CCLabelTTF* levelLabel = CCLabelTTF::create(str, "arial", 26);
    levelLabel->setAnchorPoint(ccp(0,0));
    levelLabel->setPosition(ccp(5,5));
    this->addChild(levelLabel);
    
    
}

void MyDeployButton::selected() {
    CCMenuItem::selected();
    if (m_pNormalImage)
    {
        if (m_pDisabledImage)
        {
            m_pDisabledImage->setVisible(false);
        }
        
        if (m_pSelectedImage)
        {
            m_pNormalImage->setVisible(true);
            m_pSelectedImage->setVisible(true);
        }
    }
}

MyUnit* MyDeployButton::deployUnit() {
    float coolDelta = bean->getCostCool();
    if (currentCool-coolDelta < 0) {
        CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sfx_error.wav");
        return NULL;
    }
    int costLevelData = summaryCount->getValue();
    if (MyGameInfo::getInstance()->getOil()-costLevelData>=0) {
        MyGameInfo::getInstance()->changeResource(oilTag, -costLevelData);
        MyUnit* unit = bean->creator->createObj(bean->getLevel());
        unit->cost = costLevelData;
        
        blackBack->setScaleY(blackBack->getScaleX()*(((float)(cooldown-currentCool))/cooldown));
        currentCool = currentCool-coolDelta;
        CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(bean->creator->sfxDeployNameString.c_str());
        return unit;
    } else {
        CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sfx_error.wav");
        NoResourceToDeployMessage::create(bean->creator)->sendMsg();
    }
    return NULL;
}

void MyDeployButton::recovereyCoolDown() {
    if (currentCool < 100) {
        currentCool = currentCool + 1;
    }
    blackBack->setScaleY(blackBack->getScaleX()*(((float)(cooldown-currentCool))/cooldown));
}
