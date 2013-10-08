//
//  MyGameInfo.cpp
//  ww2
//
//  Created by DingYu Fu on 12-9-18.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#include "MyGameInfo.h"
#include "StartScene.h"
#include "MyHttpConnection.h"
#include "MyJsonUtil.h"
#include "MyUtil.h"
#include "PulsarNative.h"
#include "DefineSet.h"
#include "GXRemoveFromParentsAction.h"
#include "SimpleAudioEngine.h"
#include "TransitonScene.h"
#include "MyGameFactory.h"
#include "Mathlib.h"
#include "UpLevelMessage.h"


MyGameInfo::~MyGameInfo() {
    
    CC_SAFE_RELEASE_NULL(oil);
    CC_SAFE_RELEASE_NULL(iron);
    CC_SAFE_RELEASE_NULL(glory);
//    CC_SAFE_RELEASE_NULL(deltaOil);
//    CC_SAFE_RELEASE_NULL(deltaIron);
//    CC_SAFE_RELEASE_NULL(deltaGlory);
    CC_SAFE_RELEASE_NULL(experience);
//    CC_SAFE_RELEASE_NULL(robMultiple);
    CC_SAFE_RELEASE_NULL(creatorArray);
    CC_SAFE_RELEASE_NULL(unionBean);
    CC_SAFE_RELEASE_NULL(nickname);
    CC_SAFE_RELEASE_NULL(enemyUserId);
    CC_SAFE_RELEASE_NULL(enemyNickname);
    CCLog("myGameInfo released");
}

MyGameInfo* MyGameInfo::infoInstance = NULL;

MyGameInfo* MyGameInfo::getInstance() {
    if (infoInstance == NULL) {
        infoInstance = new MyGameInfo();
        infoInstance->autorelease();
        infoInstance->retain();
    }
    return infoInstance;
}

void MyGameInfo::setIron(float _iron) {
//    deltaIron->setValue(_iron - iron->getValue() + deltaIron->getValue());
    iron->setValue(_iron);
    getIronAtlas()->setNumber(_iron);
}

void MyGameInfo::setOil(float _oil) {
    
//    deltaOil->setValue(_oil - oil->getValue() + deltaOil->getValue());
    oil->setValue(_oil);
    
//    deltaOil = _oil+keyNum - oil + deltaOil;
//    oil = _oil+keyNum;
    getOilAtlas()->setNumber(_oil);
}

void MyGameInfo::setGlory(float _glory) {
    
//    deltaGlory->setValue(_glory - glory->getValue() + deltaGlory->getValue());
    glory->setValue(_glory);
    
//    deltaGlory = _glory+keyNum- glory + deltaGlory;
//    glory = _glory+keyNum;
    getGloryAtlas()->setNumber(_glory);
}

void MyGameInfo::setDiamond(float _diamond) {
    
    diamond->setValue(_diamond);
    getDiamondAtlas()->setNumber(_diamond);
    
}

void MyGameInfo::setExperience(unsigned long long _exp)
{
    experience->setValue(_exp);
    int level = getLevelBar()->getLevel();
             
    unsigned long long maxCapacity = MyUtil::getInstance()->getExperienceByLevel(level)-MyUtil::getInstance()->getExperienceByLevel(level-1);
    int i = 0;
    while (maxCapacity > INT_MAX) {
        maxCapacity = maxCapacity / 10;
        i++;
    }
    unsigned long long capacity = experience->getValue()-MyUtil::getInstance()->getExperienceByLevel(level-1);
    for (int j=0; j<i; j++) {
        capacity = capacity / 10;
    }
//    if (level!=getLevelBar()->getLevel()&& getLevelBar()->getParent() != NULL && getLevelBar()->getParent()->getParent()!=NULL) {
//        getLevelBar()->getParent()->getParent()->removeChildByTag(levelUpLayerTag, true);
//        CCLayer* levelUpLayer = CCLayer::create();
//        
//        levelUpLayer->setTag(levelUpLayerTag);
//        CCSprite* levelUpBack = CCSprite::create("levelUpBack.png");
////        levelUpBack->setScale(1.38);
//        levelUpBack->setPosition(ccp(winSize.width/2,winSize.height/2));
//        levelUpBack->runAction(CCSequence::create(CCDelayTime::create(3),CCFadeOut::create(1),NULL));
//        CCSprite* bling = CCSprite::createWithSpriteFrameName("bling.png");
//        bling->setScale(2);
//        bling->setPosition(ccp(winSize.width/2,winSize.height/2));
//        bling->runAction(CCRepeatForever::create(CCRotateBy::create(50, 360)));
//        bling->runAction(CCSequence::create(CCDelayTime::create(3),CCFadeOut::create(1),NULL));
//        
//        char str[4] = {0};
//        sprintf(str,"%d", level);
//        CCLabelAtlas* lvCount = CCLabelAtlas::create(str, "levelupnumber.png", 40, 32, '0');
//        lvCount->setPosition(ccp(winSize.width/2,winSize.height/2));
//        lvCount->runAction(CCSequence::create(CCDelayTime::create(3),CCFadeOut::create(1),NULL));;
//        lvCount->setAnchorPoint(ccp(0.5,0.5));
//        lvCount->setScale(2);
//        UpLevelMessage::create(level)->sendMsg();
//        levelUpLayer->setPosition(ccp(0,-bling->getContentSize().height));
//        levelUpLayer->addChild(bling);
//        levelUpLayer->addChild(levelUpBack);
//        levelUpLayer->addChild(lvCount);
//        levelBar->getParent()->getParent()->addChild(levelUpLayer,30);
//        CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sfx_levelup.mp3");
//        levelUpLayer->runAction(CCSequence::create( CCEaseElasticOut::create(CCMoveTo::create(1, ccp(0,0)), 1),CCDelayTime::create(3),GXRemoveFromParentsAction::create(),NULL));
//        getLevelBar()->setLevel(level);
//    }else if (level!=getLevelBar()->getLevel()){
//        getLevelBar()->setLevel(level);
//    }
    getLevelBar()->updatePercentage(Mathlib::min(((float)capacity/(float)maxCapacity),1));
}

void MyGameInfo::setExperienceNoFx(unsigned long long _exp) {
    experience->setValue(_exp);
}

void MyGameInfo::setUpdateLevel(unsigned long long _exp) {
    experience->setValue(_exp);
    int level = MyUtil::getInstance()->getLevelByExperience(experience->getValue());
    
    unsigned long long maxCapacity = MyUtil::getInstance()->getExperienceByLevel(level)-MyUtil::getInstance()->getExperienceByLevel(level-1);
    int i = 0;
    while (maxCapacity > INT_MAX) {
        maxCapacity = maxCapacity / 10;
        i++;
    }
    unsigned long long capacity = _exp-MyUtil::getInstance()->getExperienceByLevel(level-1);
    for (int j=0; j<i; j++) {
        capacity = capacity / 10;
    }
    if (getLevelBar()->getParent() != NULL && getLevelBar()->getParent()->getParent()!=NULL) {
        getLevelBar()->getParent()->getParent()->removeChildByTag(levelUpLayerTag, true);
        CCLayer* levelUpLayer = CCLayer::create();
        
        levelUpLayer->setTag(levelUpLayerTag);
        CCSprite* levelUpBack = CCSprite::create("levelUpBack.png");
        //        levelUpBack->setScale(1.38);
        levelUpBack->setPosition(ccp(winSize.width/2,winSize.height/2));
        levelUpBack->runAction(CCSequence::create(CCDelayTime::create(3),CCFadeOut::create(1),NULL));
        CCSprite* bling = CCSprite::createWithSpriteFrameName("bling.png");
        bling->setScale(2);
        bling->setPosition(ccp(winSize.width/2,winSize.height/2));
        bling->runAction(CCRepeatForever::create(CCRotateBy::create(50, 360)));
        bling->runAction(CCSequence::create(CCDelayTime::create(3),CCFadeOut::create(1),NULL));
        
        char str[4] = {0};
        sprintf(str,"%d", level);
        CCLabelAtlas* lvCount = CCLabelAtlas::create(str, "levelupnumber.png", 40, 32, '0');
        lvCount->setPosition(ccp(winSize.width/2,winSize.height/2));
        lvCount->runAction(CCSequence::create(CCDelayTime::create(3),CCFadeOut::create(1),NULL));;
        lvCount->setAnchorPoint(ccp(0.5,0.5));
        lvCount->setScale(2);
        UpLevelMessage::create(level)->sendMsg();
        levelUpLayer->setPosition(ccp(0,-bling->getContentSize().height));
        levelUpLayer->addChild(bling);
        levelUpLayer->addChild(levelUpBack);
        levelUpLayer->addChild(lvCount);
        levelBar->getParent()->getParent()->addChild(levelUpLayer,30);
        CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sfx_levelup.mp3");
        levelUpLayer->runAction(CCSequence::create( CCEaseElasticOut::create(CCMoveTo::create(1, ccp(0,0)), 1),CCDelayTime::create(3),GXRemoveFromParentsAction::create(),NULL));
        getLevelBar()->setLevel(level);
    }else if (level!=getLevelBar()->getLevel()){
        getLevelBar()->setLevel(level);
    }
    getLevelBar()->updatePercentage((float)capacity/(float)maxCapacity);
}


unsigned long long MyGameInfo::getExperience() {
    return experience->getValue();
}


void MyGameInfo::setInitIron(float _iron) {
//    iron = _iron+keyNum;
    iron->setValue(_iron);
    
    getIronAtlas()->setNumberNoFx(_iron);
}

void MyGameInfo::setInitOil(float _oil) {
//    oil = _oil+keyNum;
    oil->setValue(_oil);
    
    getOilAtlas()->setNumberNoFx(_oil);
}

void MyGameInfo::setInitGlory(float _glory) {
//    glory = _glory+keyNum;
    glory->setValue(_glory);
    
    getGloryAtlas()->setNumberNoFx(_glory);
}

//void MyGameInfo::changeBaseOil(int resourceCount) {
////    oil->setValue(resourceCount+getDeltaOil());
//    getOilAtlas()->setNumber(oil->getValue());
//}
//
//void MyGameInfo::changeBaseIron(int resourceCount) {
////    iron->setValue(resourceCount+getDeltaIron());
//    getIronAtlas()->setNumber(iron->getValue());
//}

//int MyGameInfo::getRobMultiple() {
//    int level = MyUtil::getInstance()->getLevelByExperience(getExperience());
//    if (robMultiple->getValue() < level) {
//        return robMultiple->getValue();
//    }
//    return level;
//}

//void MyGameInfo::setRobMultiple(int multiple) {
//    int level = MyUtil::getInstance()->getLevelByExperience(getExperience());
//    CCAssert(multiple >=0 ,"multiple error");
//    if (multiple < level) {
//        return robMultiple->setValue(multiple);
//    } 
//    robMultiple->setValue(level);
//}

//void MyGameInfo::setRobMultipleByTime(unsigned long long deltaRobtime){
//    robMultiple->setValue(deltaRobtime/1800000);
//}


float MyGameInfo::getOil() {
    return oil->getValue();
}

float MyGameInfo::getIron() {
    return iron->getValue();
}

float MyGameInfo::getGlory() {
    return glory->getValue();
}

float MyGameInfo::getDiamond() {
    return diamond->getValue();
}

//float MyGameInfo::getDeltaIron() {
//    return deltaIron->getValue();
//}
//
//float MyGameInfo::getDeltaOil() {
//    return deltaOil->getValue();
//}

//float MyGameInfo::getDeltaGlory() {
////    CCLog("glory:%f",deltaGlory);
//    return deltaGlory->getValue();
//}
//
//void MyGameInfo::initDelta() {
//    deltaOil->setValue(0);
//    deltaIron->setValue(0);
//    deltaGlory->setValue(0);
//}

float MyGameInfo::getResource(int tag) {
    if (tag == oilTag) {
        return getOil();
    } else if(tag == ironTag) {
        return getIron();
    } else if(tag == expTag || tag == levelTag) {
        return getExperience();
    } else if(tag == gloryTag) {
        return getGlory();
    } else if(tag == diamondTag) {
        return getDiamond();
    } else if(tag == powerTag) {
        return getPower();
    }
    return 0;
}

CCLayer*  MyGameInfo::changeResourceAndFloatText(int tag, int resourceCount, const cocos2d::CCPoint &pos) {
    //    CCLayer* floatLayer = CCLayer::create();
    char str[50] = {0};
    if (resourceCount>=0) {
        sprintf(str, "/%d",(int)resourceCount);
    } else if(resourceCount == 0){
        sprintf(str, "");
    } else {
        sprintf(str, ".%d",resourceCount*-1);
    }
    CCLabelAtlas* label = CCLabelAtlas::create(str, "number.png", 24, 30, '.');
    CCLayer* floatLayer =CCLayer::create();
    label->setAnchorPoint(ccp(0,0.5));
    label->runAction(CCFadeOut::create(2));
    
    CCSprite* icon = MyUtil::getInstance()->getResourceIcon(tag);
    icon->setAnchorPoint(ccp(0.5,0.5));
    icon->setPosition(ccp(label->getContentSize().width+22,0));
    icon->setScale(0.7);
    icon->runAction(CCFadeOut::create(2));
    
    floatLayer->addChild(label);
    floatLayer->addChild(icon);
    float tep = (label->getContentSize().width + 160/icon->getContentSize().height  + 8)/2;
    floatLayer->setPosition(ccp(pos.x-tep,pos.y));
    
    floatLayer->runAction(CCSequence::create(CCMoveTo::create(2, ccp(pos.x-tep,pos.y+80)),GXRemoveFromParentsAction::create(),NULL));
//    setOil(getOil()+resourceCount);
    changeResource(tag,resourceCount);
    
    
//    if (tag ==  oilTag) {
////        if (getOil() +resourceCount <0) {
////            return NULL;
////        }
//        
//        CCSprite* icon = CCSprite::createWithSpriteFrameName ("oilIcon.png");
//        icon->setAnchorPoint(ccp(0.5,0.5));
//        
//        icon->setPosition(ccp(label->getContentSize().width+22,0));
//        icon->setScale(40/icon->getContentSize().height);
//        icon->runAction(CCFadeOut::create(2));
//        
//        floatLayer->addChild(label);
//        floatLayer->addChild(icon);
//        float tep = (label->getContentSize().width + 160/icon->getContentSize().height  + 8)/2;
//        floatLayer->setPosition(ccp(pos.x-tep,pos.y));
//        
//        floatLayer->runAction(CCSequence::create(CCMoveTo::create(2, ccp(pos.x-tep,pos.y+80)),GXRemoveFromParentsAction::create(),NULL));
//        setOil(getOil()+resourceCount);
//    } else if (tag == ironTag) {
////        if (getIron() +resourceCount <0) {
////            return NULL;
////        }
//
//        CCSprite* icon = CCSprite::createWithSpriteFrameName ("ironIcon.png");
//        icon->setAnchorPoint(ccp(0.5,0.5));
//        
//        icon->setPosition(ccp(label->getContentSize().width+22,0));
//        icon->setScale(40/icon->getContentSize().height);
//        icon->runAction(CCFadeOut::create(2));
//        
//        floatLayer->addChild(label);
//        floatLayer->addChild(icon);
//        float tep = (label->getContentSize().width + 160/icon->getContentSize().height  + 8)/2;
//        floatLayer->setPosition(ccp(pos.x-tep,pos.y));
//        
//        floatLayer->runAction(CCSequence::create(CCMoveTo::create(2, ccp(pos.x-tep,pos.y+80)),GXRemoveFromParentsAction::create(),NULL));
////        iron += resourceCount;
////        ironAtlas->setNumber(iron);
//        setIron(getIron()+resourceCount);
//    } else if (tag == expTag) {
//        CCSprite* icon = CCSprite::createWithSpriteFrameName ("expIcon.png");
//        icon->setAnchorPoint(ccp(0.5,0.5));
//        
//        icon->setPosition(ccp(label->getContentSize().width+22,0));
//        icon->setScale(40/icon->getContentSize().height);
//        icon->runAction(CCFadeOut::create(2));
//        
//        floatLayer->addChild(label);
//        floatLayer->addChild(icon);
//        float tep = (label->getContentSize().width + 160/icon->getContentSize().height  + 8)/2;
//        floatLayer->setPosition(ccp(pos.x-tep,pos.y));
//        
//        floatLayer->runAction(CCSequence::create(CCMoveTo::create(2, ccp(pos.x-tep,pos.y+80)),GXRemoveFromParentsAction::create(),NULL));
//        //        iron += resourceCount;
//        //        ironAtlas->setNumber(iron);
//        setExperience(getExperience() + resourceCount);
//    } else if (tag == gloryTag) {
//        CCSprite* icon = CCSprite::createWithSpriteFrameName ("honorIcon.png");
//        icon->setAnchorPoint(ccp(0.5,0.5));
//        
//        icon->setPosition(ccp(label->getContentSize().width+22,0));
//        icon->setScale(40/icon->getContentSize().height);
//        icon->runAction(CCFadeOut::create(2));
//        
//        floatLayer->addChild(label);
//        floatLayer->addChild(icon);
//        float tep = (label->getContentSize().width + 160/icon->getContentSize().height  + 8)/2;
//        floatLayer->setPosition(ccp(pos.x-tep,pos.y));
//        
//        floatLayer->runAction(CCSequence::create(CCMoveTo::create(2, ccp(pos.x-tep,pos.y+80)),GXRemoveFromParentsAction::create(),NULL));
//        //        iron += resourceCount;
//        //        ironAtlas->setNumber(iron);
//        setGlory(getGlory() + resourceCount);
//    } else if(tag == diamondTag){
//        CCSprite* diamondSprite = CCSprite::createWithSpriteFrameName("diamond.png");
//        diamondSprite->setAnchorPoint(ccp(0.5,0.5));
//        
//        diamondSprite->setPosition(ccp(label->getContentSize().width+22,0));
//        diamondSprite->setScale(40/icon->getContentSize().height);
//        diamondSprite->runAction(CCFadeOut::create(2));
//        
//        floatLayer->addChild(label);
//        floatLayer->addChild(icon);
//        float tep = (label->getContentSize().width + 160/icon->getContentSize().height  + 8)/2;
//        floatLayer->setPosition(ccp(pos.x-tep,pos.y));
//        
//        floatLayer->runAction(CCSequence::create(CCMoveTo::create(2, ccp(pos.x-tep,pos.y+80)),GXRemoveFromParentsAction::create(),NULL));
//        //        iron += resourceCount;
//        //        ironAtlas->setNumber(iron);
//        setGlory(getGlory() + resourceCount);
//    }
    return floatLayer;
}

void MyGameInfo::clear() {
    
    lastTime = 0;
    nowTime = 0;
//    robdeltaTime = 0;
    enemyOil = 0;
    enemyIron = 0;
    enemyDeltaOil = 0;
    enemyDeltaIron = 0;
    enemyUserId->setValue(0);
    maxId = -1;
    getOilAtlas()->setNumberNoFx(0),
    getIronAtlas()->setNumberNoFx(0),
    getGloryAtlas()->setNumberNoFx(0),
    getDiamondAtlas()->setNumberNoFx(0),
    robberOil = 1;
    robberIron = 1;
    power = 21;
    enemyPower = 20;
    creatorArray->removeAllObjects();
    experience->setValue(1);
//    deltaOil->setValue(0);
//    deltaIron->setValue(0);
//    deltaGlory->setValue(0);
//    robMultiple->setValue(0);
    vipExperience->setValue(0);
    diamond->setValue(0);
    
    CC_SAFE_RELEASE_NULL(unionBean);
    unionBean = UnionBean::create();
    unionBean->retain();
    
    MyHttpConnection::getInstance()->clearGameDataListArray();

}

void MyGameInfo::changeResource(int tag, int resourceCount){
    if (tag == ironTag) {
//        iron += resourceCount;
//        ironAtlas->setNumber(iron);
        setIron(getIron() + resourceCount);
    } else if(tag == oilTag){
//        oil += resourceCount;
//        oilAtlas->setNumber(oil);
        setOil(getOil() + resourceCount);
    } else if(tag == gloryTag) {
        setGlory(getGlory()+resourceCount);
    }else if(tag == expTag){
        setExperience(getExperience() + resourceCount);
    } else if(tag == diamondTag) {
        setDiamond(getDiamond() + resourceCount);
    }
}

MyAtlasNumber* MyGameInfo::getOilAtlas() {
    if (oilAtlas == NULL) {
//        char str[10] = {0};
        oilAtlas = MyAtlasNumber::create();
        oilAtlas->retain();
        oilAtlas->setNumberNoFx(getOil());
//        oilAtlas->setNumber(get);
//        oilAtlas->setNowNumber(oil);
//        sprintf(str, "%d",(int)oil);
//        oilAtlas->setString(str);
    }
    return oilAtlas;
}


MyAtlasNumber* MyGameInfo::getIronAtlas() {
    if (ironAtlas == NULL) {
//        char str[10] = {0};
        ironAtlas = MyAtlasNumber::create();
        ironAtlas->retain();
        ironAtlas->setNumberNoFx(getIron());
//        ironAtlas->setNumber(iron);
//        ironAtlas->setNowNumber(iron);
//        sprintf(str, "%d",(int)iron);
//        ironAtlas->setString(str);
    }
    return ironAtlas;
}



MyAtlasNumber* MyGameInfo::getGloryAtlas() {
    if (gloryAtlas == NULL) {
        //        char str[10] = {0};
        gloryAtlas = MyAtlasNumber::create();
        gloryAtlas->retain();
        gloryAtlas->setNumberNoFx(getGlory());
        //        ironAtlas->setNumber(iron);
        //        ironAtlas->setNowNumber(iron);
        //        sprintf(str, "%d",(int)iron);
        //        ironAtlas->setString(str);
    }
    return gloryAtlas;
}

MyAtlasNumber* MyGameInfo::getDiamondAtlas() {
    if (diamondAtlas == NULL) {
        //        char str[10] = {0};
        diamondAtlas = MyAtlasNumber::create();
        diamondAtlas->retain();
        diamondAtlas->setNumberNoFx(getDiamond());
        //        ironAtlas->setNumber(iron);
        //        ironAtlas->setNowNumber(iron);
        //        sprintf(str, "%d",(int)iron);
        //        ironAtlas->setString(str);
    }
    return diamondAtlas;
}

MyLevelBar* MyGameInfo::getLevelBar() {
    if(levelBar == NULL) {
        int level =  MyUtil::getInstance()->getLevelByExperience(getExperience());
        unsigned long long maxCapacity = MyUtil::getInstance()->getExperienceByLevel(level)-MyUtil::getInstance()->getExperienceByLevel(level-1);
        int i = 0;
        while (maxCapacity > INT_MAX) {
            maxCapacity = maxCapacity / 10;
            i++;
        }
        unsigned long long capacity = getExperience()-MyUtil::getInstance()->getExperienceByLevel(level-1);
        for (int j=0; j<i; j++) {
            capacity = capacity / 10;
        }
        levelBar = MyLevelBar::create(CCSprite::create("levelBarUp.png"), CCSprite::create("BarDown.png"),CCSizeMake(84, 8));
//        levelBar->setContentSize(transWindowToGLInRetina(CCSizeMake(42, 4)));
        levelBar->setLevel(level);
        levelBar->updatePercentage((float)capacity/(float)maxCapacity);
        levelBar->retain();
    }
    return levelBar;
}

//void MyGameInfo::release() {
//    CCLog("MatchInfoBean release %d",m_uReference);
//    CCObject::release();
//}
//
//void MyGameInfo::retain() {
//    CCLog("MatchInfoBean retain %d",m_uReference);
//    CCObject::retain();
//}



float MyGameInfo::getRobberOil() {
//    CCLog("roilget:%f", robberOil);
    return robberOil-keyNum;
}
void MyGameInfo::setRobberOil(float _robberOil){
//    CCLog("oriOil:%f",robberOil);
    robberOil = _robberOil+keyNum;
//    CCLog("roilset:%f",_robberOil+keyNum);
}
float MyGameInfo::getRobberIron(){
//    CCLog("rIronget:%f",robberIron);
    return robberIron-keyNum;
}
void MyGameInfo::setRobberIron(float _robberIron){
//    CCLog("oriIron:%f",robberIron);
    robberIron= _robberIron+keyNum;
//    CCLog("rIronset:%f",_robberIron+keyNum);
}


float MyGameInfo::getPower(){
    return power;
}
void MyGameInfo::setPower(float _power){
    power= _power;
}

MatchInfoBean* MatchInfoBean::create() {
    MatchInfoBean* info = new MatchInfoBean();
    info->autorelease();
    info->frameNameArray = CCArray::create();
    info->frameNameArray->retain();
    info->unitCountArray = CCArray::create();
    info->unitCountArray->retain();
    info->levelArray = CCArray::create();
    info->levelArray->retain();
    info->rarityArray = CCArray::create();
    info->rarityArray->retain();
//    info->attackId = info->CCString::create("");
    return info;
}

CCMenuItemSprite* MatchInfoBean::getReverageButton() {
    CCMenuItemSprite* reverageItem = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("revenge.png"),CCSprite::createWithSpriteFrameName("revengeButtonP.png"),this,menu_selector(MatchInfoBean::toReverageCallBack));
    CC_SAFE_RETAIN(this);
    return reverageItem;
}

void MatchInfoBean::toReverageCallBack(cocos2d::CCObject *pSender) {
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sfx_click.mp3");
    CCNode* item = ((CCNode*)pSender);
    StartScene* scene = dynamic_cast<StartScene*>(item->getParent()->getParent()->getParent()->getParent());
    scene->toCancelRecorder(scene);
    MyMap* map = dynamic_cast<MyMap*>(scene->getChildByTag(MainMapTag));
    if(map != NULL) {
        scene->updateMyData();
        map->pauseSchedulerAndActions();
        scene->cleanup();
        MyGameInfo::getInstance()->enemyIron = 0;
        MyGameInfo::getInstance()->enemyOil = 0;
//        map->unRegisterWithTouchDispatcher();
    }
    map = NULL;
    
//    char str[20] = {0};
//    sprintf(str, "%s",attackId);
//    const char* response = MyHttpConnection::getInstance()->getOtherData(attackId);
//    if (strcmp(response, "failed") == 0) {
//        scene->addChild(MyUtil::getInstance()->getNetworkDialog());
//        return;
//    }
    if (attackType == 0 ) {
        CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.2, TransitonScene::create(battleSceneTag, CCInteger::create(attackUserId)), ccBLACK));
    } else if(attackType == 1) {
        CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.2, TransitonScene::create(battleSceneBySearchTag, CCInteger::create(attackUserId)), ccBLACK));
    }
    
    CC_SAFE_RELEASE(this);
    CocosDenshion::SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
}



//void MatchInfoBean::retain() {
//    CCLog("MatchInfoBean retain %d",m_uReference);
//    CCObject::retain();
//}
//
//void MatchInfoBean::release() {
//    CCLog("MatchInfoBean release %d",m_uReference);
//    CCObject::release();
//}

CreatorInfoBean* CreatorInfoBean::create(int unitTag) {
    CreatorInfoBean* bean = new CreatorInfoBean();
//    bean->scriptName = _scriptName;
//    bean->creator = (UnitCreator*)MyGameFactory::createCreatorbyJsonScriptFile(_scriptName->getCString(), unitCreatorClassTag);
//    bean->creator->retain();
//    bean->scriptName->retain();
    if (unitTag == garadeCardId) {
        bean->creator = Garade::getUnitBean();
    } else if(unitTag == M5StuartCardId) {
        bean->creator = M5Stuart::getUnitBean();
    } else if(unitTag == panzergrenadierCardId) {
        bean->creator = Panzergrenadier::getUnitBean();
    } else if(unitTag == WillysMBCardId) {
        bean->creator = WillysMB::getUnitBean();
    } else if(unitTag == InfanterieCardId) {
        bean->creator = Infanterie::getUnitBean();
    } else if(unitTag == M3HalfTrackCardId) {
        bean->creator = M3HalfTrack::getUnitBean();
    } else if(unitTag == M4ShermanCardId) {
        bean->creator = M4Sherman::getUnitBean();
    } else if(unitTag == CalliopeCardId) {
        bean->creator = Calliope::getUnitBean();
    } else if(unitTag == HummingBirdCardId) {
        bean->creator = HummingBird::getUnitBean();
    } else if(unitTag == volksgrenaierCardId) {
        bean->creator = Volksgrenaier::getUnitBean();
    } else if(unitTag == PanzerIVCardId) {
        bean->creator = PanzerIV::getUnitBean();
    } else if(unitTag == TigerCardId) {
        bean->creator = Tiger::getUnitBean();
    } else if(unitTag == tornadoCardId){
        bean->creator = Tornado::getUnitBean();
    } else if(unitTag == ThorCardId) {
        bean->creator = Thor::getUnitBean();
    } else {
        CCAssert(1 == 2,"UNITCARD不合法");
    }
    
    bean->autorelease();
    return bean;
}

int CreatorInfoBean::getLevel() {
    int levelInt = level->getValue();
    int maxLevel = creator->getMaxLevel();
    if(levelInt < 0) {
        levelInt =MyUtil::getInstance()->getUnitLevelByExperience(getExperience(), creator->getRarity());
        if (levelInt > maxLevel) {
            setExperience(MyUtil::getInstance()->getExperienceByUnitLevel(maxLevel,creator->getRarity()));
        }
        levelInt = Mathlib::bound(levelInt,maxLevel,1);
        level->setValue(levelInt);
        return levelInt;
    }
    if (levelInt > 0 && levelInt <= maxLevel) {
        return levelInt;
    }
    setExperience(MyUtil::getInstance()->getExperienceByUnitLevel(maxLevel,creator->getRarity()));
    level->setValue(Mathlib::bound(MyUtil::getInstance()->getUnitLevelByExperience(getExperience(), creator->getRarity()),creator->getMaxLevel(),1));
    return creator->getMaxLevel();
}

CCLayer* CreatorInfoBean::getUnitCardDesc(bool isAll) {
    return creator->getUnitCardInfo(getLevel(),isAll);
}

float CreatorInfoBean::getCostCool(){
    return creator->getCostCool(getLevel());
}

UnionBean* UnionBean::create() {
    UnionBean* bean = new UnionBean();
    bean->autorelease();
    bean->name = CCString::create("");
    bean->name->retain();
    bean->desc = CCString::create("");
    bean->desc->retain();
    bean->notice = CCString::create("");
    bean->notice->retain();
    bean->emblem = CCString::create("");
    bean->emblem->retain();
    return bean;
}

void UnionBean::setName(CCString* nameStr) {
    CC_SAFE_RELEASE_NULL(name);
    name = nameStr;
    name->retain();
}

CCString* UnionBean::getName() {
    return name;
}

void UnionBean::setDesc(CCString* descStr) {
    CC_SAFE_RELEASE_NULL(desc);
    desc = descStr;
    desc->retain();
}

CCString* UnionBean::getDesc() {
    return desc;
}

void UnionBean::setNotice(CCString* noticeStr) {
    CC_SAFE_RELEASE_NULL(notice);
    notice = noticeStr;
    notice->retain();
}

CCString* UnionBean::getNotice() {
    return notice;
}

void UnionBean::setEmblem(CCString* emblemStr) {
    CC_SAFE_RELEASE_NULL(emblem);
    emblem = emblemStr;
    emblem->retain();
}

CCString* UnionBean::getEmblem() {
    return emblem;
}