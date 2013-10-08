//
//  MyBuilding.cpp
//  ww2
//
//  Created by DingYu Fu on 12-9-2.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "MyBuilding.h"
#include "MyState.h"
#include "MyBattleMap.h"
#include "MyGameFactory.h"
#include "GXFadeOut.h"
#include "DefineSet.h"
#include "Mathlib.h"
#include "MyGameInfo.h"
#include "MyUtil.h"
#include "SimpleAudioEngine.h"
#include "GXAnimateFX.h"
#include "GXRemoveFromParentsAction.h"
#include "GXFadeOutAndRemoveWhenStop.h"
#include "UpdateBuildingMessag.h"
#include "BuildingHeader.h"
#include "MyHttpConnection.h"

//MyBuilding::MyBuilding() {
//    this->schedule(schedule_selector(MyBuilding::doCurrentState),1);
    
    
    
//}


//MyBuilding* MyBuilding::create(int tag,const CCSize& _contentSizebyTiled,GXFSMstate *state,int level,CCMenuItem* item, ...) {
//    va_list args;
//    va_start(args,item);
//    MyBuilding *pRet = new MyBuilding();
////    pRet->map = NULL;
//    if (pRet && pRet->initWithItems(item, args))
//    {
//        pRet->autorelease();
//        va_end(args);
//        pRet->positionByTiled.x = 9999999;
////        MyTiledMenuItemSprite* myItem= dynamic_cast<MyTiledMenuItemSprite*>(item);
////        if(myItem != NULL) {
////            myItem -> setTag(myTiledMenuItemTag);
////        }
//        pRet->setTag(tag);
//        
//        
//        pRet->contentSizeByTiled =_contentSizebyTiled;
//        MyState* myState = dynamic_cast<MyState*>(state);
//        CCAssert(myState != NULL, "没办法，不能循环声明，咋整咯？？");
//        pRet->fsm = GXFSM::create(state);
//        pRet->fsm->retain();
////        myState->building = pRet;
//        myState->init(pRet);
//        pRet->addChild(myState->getItem());
//
////        pRet->schedule(schedule_selector(pRet->doCurrentState));
//        CCMenuItem *i = va_arg(args, CCMenuItem*);
//        while (i) {
//            i->setVisible(false);
//            i = va_arg(args, CCMenuItem*);
//        }
//        
//        pRet->setLevel(level);
//        return pRet;
//    }
//    va_end(args);
//    CC_SAFE_DELETE(pRet);
//    return NULL;
//    return NULL;
//}
MyBuilding* MyBuilding::create(int tag,const CCSize& _contentSizebyTiled,GXFSMstate *state,int _maxLevel) {
    
//    MyTiledMenuItem *pRet = new MyTiledMenuItem();
//    if (pRet && pRet->initWithTarget(pRet, menu_selector(MyTiledMenuItem::runTouchAction)))
//    {
//        pRet->autorelease();
//        pRet->normalImage = normalImage;
//        pRet->addChild(normalImage);
//        pRet->contentSizeByTiled = contentSize;
//        return pRet;
//    }
//    CC_SAFE_DELETE(pRet);
//    return NULL;
    
    MyBuilding *pRet = new MyBuilding();
//    pRet->map = NULL;
    if (pRet && pRet->initWithTarget(pRet, menu_selector(MyBuilding::runTouchAction)))
    {
        pRet->autorelease();
        pRet->positionByTiled.x = 9999999;
//        MyTiledMenuItemSprite* myItem= dynamic_cast<MyTiledMenuItemSprite*>(item);
//        if(myItem != NULL) {
//            myItem -> setTag(myTiledMenuItemTag);
//        }
        pRet->setTag(tag);


        pRet->contentSizeByTiled =_contentSizebyTiled;
        MyState* myState = dynamic_cast<MyState*>(state);
        CCAssert(myState != NULL, "没办法，不能循环声明，咋整咯？？");
        pRet->fsm = GXFSM::create(state);
        pRet->fsm->retain();
//        myState->building = pRet;
        pRet->addState(myState);
        pRet->setNormalImage(myState->getItem());
        pRet->setMaxLevel(_maxLevel);

        return pRet;
    }
    CC_SAFE_DELETE(pRet);
    return NULL;
}

void MyBuilding::setDoStateInterval(float _doStateInterval) {
    if (_doStateInterval>=0) {
        if (this->doStateInterval > 0) {
             this->unschedule(schedule_selector(MyBuilding::doCurrentState));
        }
        this->schedule(schedule_selector(MyBuilding::doCurrentState),_doStateInterval);
    } else {
        this->unschedule(schedule_selector(MyBuilding::doCurrentState));
    }
    this->doStateInterval = _doStateInterval;
}


MyBuilding* MyBuilding::create() {
    MyBuilding *pRet = new MyBuilding();
//    if (pRet && pRet->initWithTarget(NULL, SEL_MenuHandler selector)) {
//        pRet->autorelease();
//        pRet->positionByTiled.x = 9999999;
//    }
    return pRet;
}

void MyBuilding::setRoad(cocos2d::CCSprite *_road) {
    if (road !=NULL) {
        road->removeFromParentAndCleanup(true);
        _road->setPosition(road->getPosition());
        _road->setAnchorPoint(road->getAnchorPoint());
        CC_SAFE_RELEASE_NULL(road);
        road = _road;
        _road->retain();
    } else {
        road = _road;
        road->setPosition(this->getPosition());
        _road->retain();
    }
    if (map!=NULL) {
#if game_version == soft_version
        ((MyMap*)map)->roadSheet->addChild(road);
#endif
    }
}

MyBuilding::~MyBuilding() {
    if (this->getUserData() != NULL) {
        ((BuildingInfo*)this->getUserData())->count--;
    }
//    this->fsm->release();
    CC_SAFE_RELEASE_NULL(this->fsm);
    CC_SAFE_RELEASE_NULL(maxLevel);
    CC_SAFE_RELEASE_NULL(level);
    CC_SAFE_RELEASE_NULL(summaryCount);
    CC_SAFE_RELEASE_NULL(buildingName);
//    CCLog("MyBuilding released");
}

void MyBuilding::doCurrentState() {
    //活着的时候才动吧 播死亡动画 复活什么的可以在谈
    
//    if (isAlive()) {
        fsm->getCurrentState()->doState();
//    }
}

//void MyBuilding::release(){
////    CCLog("release building:%d",this->m_uReference);
//    CCMenuItem::release();
//}

//void MyBuilding::retain(){
////    CCLog("retain building:%d",this->m_uReference);
//    CCMenuItem::retain();
//}

//void MyBuilding::showAllTransition() {
//    CCArray* children = this->getChildren();
//    CCObject* obj;
//    CCMenuItemSprite* item;
//    CCARRAY_FOREACH(children, obj) {
//        item = dynamic_cast<CCMenuItemSprite*>(obj);
//        if (item && item->getTag() != myTiledMenuItemTag) {
//            item->setVisible(true);
//            item->setEnabled(true);
////            item->setOpacity(0);
//            item->runAction(CCFadeIn::create(0.15));
//        }
//    }
//}

void MyBuilding::showCurrentTransition() {
    ((MyState*)fsm->getCurrentState())->showAllTransition();
}

void MyBuilding::dismissAllTransition() {
//    CCArray* children = this->getChildren();
//    CCObject* obj;
//    CCMenuItem* item;
//    CCARRAY_FOREACH(children, obj) {
//        item = dynamic_cast<CCMenuItem*>(obj);
//        if (item != NULL && item->getTag() != myTiledMenuItemTag && item->isEnabled()) {
//            item->setEnabled(false);
//            //            item->setOpacity(0);
//            item->runAction(CCFadeOut::create(0.15));
//        }
//    }
    ((MyState*)fsm->getCurrentState())->dismissAllTransition();
}

void MyBuilding::runTouchAction() {
    if (fsm->getCurrentState()!=NULL) {
        ((MyState*)(fsm->getCurrentState()))->clickCallBack();
    }
}

void MyBuilding::setPositionByTiled(const cocos2d::CCPoint &pos) {
    if(map != NULL) {
        if (road != NULL) {
            road->setPosition(map->transTiledToMap(pos));
        }
        this->setPosition(map->transTiledToMap(pos));
        this->positionByTiled = pos;
//        MyState* state = (MyState*)fsm->getCurrentState();
//        CCArray* tags = state->getAllInput();
//        CCObject* obj;
//        CCMenuItem* menuitem;
//        int i = 0;
//        CCARRAY_FOREACH(tags, obj) {
//            
//            menuitem = dynamic_cast<CCMenuItem*>(state->itemDictionary->objectForKey(((CCInteger*)obj)->getValue()));
//            if (menuitem->getParent() != NULL ) {
//                //            item->setOpacity(0);
//                menuitem->setPosition(ccp(this->getPosition().x-(tags->count()-1)*50+i*100,this->getPosition().y+this->contentSizeByTiled.height*20 +100));
//                //            item->setVisible(false);
//                i++;
//            }
//        }
    } else {
        this->positionByTiled = pos;
    }
}


//void MyBuilding::showTransition(CCArray* tags) {
////    CCArray* children = this->getChildren();
//    CCObject* obj;
//    CCMenuItem* item;
////    CCInteger* i;
//    
//    
//    CCARRAY_FOREACH(tags, obj) {
//        
//        item = dynamic_cast<CCMenuItem*>(this->getChildByTag(((CCInteger*)obj)->getValue()));
//        CCAssert(item != NULL, "估计没加对应按钮就加流程了");
//        item->setVisible(true);
//        item->setEnabled(true);
//        //            item->setOpacity(0);
//        item->runAction(CCFadeIn::create(0.15));
//    }
////    item->setVisible(true);
////    item->setEnabled(true);
////    //            item->setOpacity(0);
////    item->runAction(CCFadeIn::create(0.15));
//    //            }
//}

void MyBuilding::addState(GXFSMstate *state) {
    MyState* mystate = (MyState*)state;
    fsm->addState(state);
    mystate->init(this);
}

void MyBuilding::changeState(int inputId) {
    CCInteger* out = fsm->stateTransition(inputId);
    MyState* mystate = dynamic_cast<MyState*>(fsm->getState(out->getValue()));
    MyState* current = (MyState*)(fsm->getCurrentState());
//    current->removeAllTransiton();
    this->setNormalImage(mystate->getItem());
    current->dismissAllTransition();
    current->doEnd();
    if(map != NULL) {
        mystate->doStart();
    }
    fsm->setCurrentState(mystate);
    mystate->showAllTransition();
    setActive(true);
//    displaySummary();
}

void MyBuilding::changeStateById(int id) {
    if (id != fsm->getCurrentState()->getId() && id != 0 ) {
        MyState* mystate = (MyState*)(fsm->getState(id));
        if (mystate == NULL) {
            return;
        }
        MyState* current = (MyState*)(fsm->getCurrentState());
//        current->removeAllTransiton();
        this->setNormalImage(mystate->getItem());
        current->doEnd();
        if(map != NULL) {
            mystate->doStart();
        }
//        current->getItem()->removeFromParentAndCleanup(true);
        fsm->setCurrentState(mystate);
        dismissAllTransition();
    }
}

//void MyBuilding::dispose() {
//
//    GXAnimateFX* animate = GXAnimateFX::createWithAnitmateFrameNameByFadeout("collapse", 2, false);
//    animate->setPosition(this->getPosition());
//    map->addChild(animate,999999-this->getPosition().y);
//    animate->setAnchorPoint(ccp(0.51,0.361));
//    
//    animate->setScale(this->contentSizeByTiled.width*transWindowToGLInRetina(30)/transWindowToGLInRetina(145));
//    
//    MyBattleMap* battleMap = (MyBattleMap*)map;
//    ((MyBattleMap*)map)->getItems()->removeObject(this);
//    //去掉地皮的提示
//    float width = this->costRange.width;
//    float height = this->costRange.height;
//    CCPoint posi = map->transMapToTiled(this->getPosition());
//    CCTMXLayer* layer = map->layerNamed("tiled");
//    for (int i=(int)(posi.x-width/2+0.5); i<posi.x+width/2+0.5; ++i) {
//        for (int j=(int)(posi.y-height/2+0.5); j<posi.y+height/2+0.5; ++j) {
//            if (map->checkTiledBound(i, j)) {
//                battleMap->costMap[i][j] -= 5;
//                if ( battleMap->costMap[i][j] <5) {
//                    layer->tileAt(ccp(i,j))->stopAllActions();
//                    layer->tileAt(ccp(i,j))->runAction(CCTintTo::create(0, 255, 255, 255));
//                }
//
//            }
//        }
//    }
//    
//    AliveInterface::dispose();
//    changeState(toRuinsTransition);
////    fsm->stateMap->removeAllObjects();
//}

//bool MyBuilding::isAlive() {
//    return alive;
//}


void MyBuilding::displaySummary() {
    CCNode* exist = getChildByTag(nameFontTag);
    if (exist) {
//        return;
        exist->removeFromParentAndCleanup(true);
        this->removeChildByTag(levelFontTag,true);
    }
    char str[30] = {0};
    CCLabelTTF* name = CCLabelTTF::create(getBuildingName(),"Arial",25);
    name->setColor(ccWHITE);
    name->setPosition(ccp(0,y));
    name->setTag(nameFontTag);
    name->runAction(CCFadeTo::create(0.15,255));
    
    sprintf(str, "等级 %d",getLevel());
    CCLabelTTF* levelFont = CCLabelTTF::create(str,"Arial",21);
    levelFont -> setPosition(ccp(0,y-22));
    levelFont->setColor(ccWHITE);
    levelFont->setTag(levelFontTag);
    levelFont->runAction(CCFadeTo::create(0.15,255));
    
    this->addChild(name,20);
    this->addChild(levelFont,20);
    
}

bool MyBuilding::dismissSummary() {
    bool flag = false;
    CCNode* name = getChildByTag(nameFontTag);
    CCNode* level = getChildByTag(levelFontTag);
    if (name!=NULL) {
//        name->setVisible(true);
        name->stopAllActions();
        name->runAction(GXFadeOutAndRemoveWhenStop::create(0.15));
        flag= true;
    }
    if (level!=NULL) {
        level->stopAllActions();
        level->runAction(GXFadeOutAndRemoveWhenStop::create(0.15));
        flag = true;
    }
    return flag;
}

//void MyBuilding::ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent) {
//    MyMenu::ccTouchEnded(pTouch, pEvent);
//}
void MyBuilding::updateLevel(CCMenuItem* item) {
    
    StartScene* scene = dynamic_cast<StartScene*>(map->getParent());
//    if (scene->getChildByTag(updateLayerTag)!=NULL) {
    scene->removeChildByTag(updateLayerTag, true);
//    }
    CCLayer* updateLayer = NULL;
    if (item != NULL) {
        updateLayer = MyUtil::getInstance()->getUpdateDialog(true);
    } else {
        updateLayer = MyUtil::getInstance()->getUpdateDialog(false);
    }
    
    scene->addChild(updateLayer);
    char str[50] = {0};
    if (getLevel() < getMaxLevel()-1) {
        sprintf(str, "等级 %d     %d",getLevel(),getLevel()+1);
        CCLabelTTF* levelLabel = CCLabelTTF::create(str, "Arial", 24);
        levelLabel->setColor(ccc3(254,218,130));
        levelLabel->setAnchorPoint(ccp(0.5,0.5));
        levelLabel->setPosition(ccp(-214,32));
        updateLayer->addChild(levelLabel);
        CCSprite* updateTip = CCSprite::createWithSpriteFrameName("updateTipIcon.png");
        updateTip->setPosition(ccp(-186,32));
        updateLayer->addChild(updateTip);
    }else if (getLevel() == getMaxLevel()-1) {
        
        sprintf(str, "等级 %d     max",getLevel());
        CCLabelTTF* levelLabel = CCLabelTTF::create(str, "Arial", 24);
        levelLabel->setColor(ccc3(254,218,130));
        levelLabel->setAnchorPoint(ccp(0.5,0.5));
        levelLabel->setPosition(ccp(-198,32));
        updateLayer->addChild(levelLabel);
        CCSprite* updateTip = CCSprite::createWithSpriteFrameName("updateTipIcon.png");
        updateTip->setPosition(ccp(-186,32));
        updateLayer->addChild(updateTip);
    } else {
        sprintf(str, "等级max");
        CCLabelTTF* levelLabel = CCLabelTTF::create(str, "Arial", 24);
        levelLabel->setColor(ccc3(254,218,130));
        levelLabel->setAnchorPoint(ccp(0.5,0.5));
        levelLabel->setPosition(ccp(-204,32));
        updateLayer->addChild(levelLabel);
    }
   
    
    sprintf(str, "No.%d",getTag());
    CCLabelTTF* NoLabel = CCLabelTTF::create(str, "Arial", 16);
    NoLabel->setColor(ccc3(254,218,130));
    NoLabel->setAnchorPoint(ccp(0,0.5));
    NoLabel->setPosition(ccp(-260,192));
    updateLayer->addChild(NoLabel);
    
    
    CCSprite* currentSprite =  ((MyState*)fsm->getCurrentState())->getItem();
//    ((MyState*)fsm->getCurrentState())->setUpdateInfo(updateLayer);
    CCSprite* image =  CCSprite::createWithTexture(currentSprite->getTexture(),currentSprite->getTextureRect());
    image->setTextureRect(currentSprite->getTextureRect(), currentSprite->isTextureRectRotated(), currentSprite->getContentSize());
    image->setPosition(ccp(-204,100));
    image->setScale(0.675);
    updateLayer->addChild(image);
    if (setUpdateInfo_selector != NULL) {
        (*setUpdateInfo_selector)(fsm->getCurrentState(),updateLayer);
    }
//    MyGameFactory::setStateUpdateInfo(((MyState*)fsm->getCurrentState()), updateLayer);
    
   
    if (getLevel()< getMaxLevel()) {
        
        CCSprite* metalButton = CCSprite::createWithSpriteFrameName("metalButton.png");
        CCSprite* startLabel1 = CCSprite::createWithSpriteFrameName("updateButtonLabel.png");
        startLabel1->setScaleY(1.1111);
        startLabel1->setPosition(ccp(metalButton->getContentSize().width/2,metalButton->getContentSize().height/2+3));
        startLabel1->setColor(ccc3(222,222,222));
        metalButton->addChild(startLabel1);
        
        CCSprite* metalButtonP = CCSprite::createWithSpriteFrameName("metalButtonP.png");
        CCSprite* startLabel2 = CCSprite::createWithSpriteFrameName("updateButtonLabel.png");
        startLabel2->setPosition(ccp(metalButtonP->getContentSize().width/2,metalButtonP->getContentSize().height/2+3));
        startLabel2->setScaleY(1.1111);
        metalButtonP->addChild(startLabel2);
        
        CCMenuItemSprite* updateButton = CCMenuItemSprite::create(metalButton,metalButtonP,this,menu_selector(MyBuilding::updateCallBack));
        updateButton->setScaleY(0.9);
        updateButton->setPosition(ccp(0,-140));
        ((CCMenu*)updateLayer->getChildByTag(updateMenuTag))->addChild(updateButton);
        
        CCSprite* resourceIcon = MyUtil::getInstance()->getResourceIcon(resourceTag);
        resourceIcon->setScale(25/resourceIcon->getContentSize().height);
        resourceIcon->setPosition(ccp(-40,-178));
        updateLayer->addChild(resourceIcon);
        
        
        sprintf(str, "%d",(int)getUpdateSummary(getSummaryCount(),getLevel()));
        CCLabelTTF* summaryResourceCount = CCLabelTTF::create(str, "Arial", 24);
        summaryResourceCount->setColor(ccc3(254, 218, 130));
        summaryResourceCount->setAnchorPoint(ccp(0.5,0.5));
        
        summaryResourceCount->setPosition(ccp(Mathlib::max(summaryResourceCount->getContentSize().width/2-26, 6),-180) );
        updateLayer->addChild(summaryResourceCount);
        
    } else {
        CCLabelTTF* maxLeveltip = CCLabelTTF::create("已达到最大等级", "Arial", 24);
        maxLeveltip->setColor(ccc3(254,218,130));
        maxLeveltip->setPosition(ccp(0,-160));
        updateLayer->addChild(maxLeveltip);
    }
    
    
//    setLevel(level);
}

void MyBuilding::setLevel(int _level) {
    
    if(_level > getMaxLevel()) {
        CCLog("level not above maxLevel");
        if (setLevel_selector != NULL) {
            (*setLevel_selector)(1,fsm);
        }
        return;
    }
    level->setValue(_level);
    if (setLevel_selector != NULL) {
        (*setLevel_selector)(_level,fsm);
    }
//    CCArray* states = fsm->getAllState();
//    CCObject* obj;
//    CCARRAY_FOREACH(states, obj) {
//        MyState* state = (MyState*)obj;
//        state->updateLevel(level);
//    }
}

int MyBuilding::getLevel() {
    return level->getValue();
}

void MyBuilding::updateCallBack(CCMenuItem *pSender) {
    pSender->setEnabled(false);
    if (updateBuilding() >= 0) {
        
        CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sfx_updateBuilding.mp3");
        UpdateBuildingMessag::create(this->getTag(),getLevel()-1,getLevel())->sendMsg();
        MyHttpConnection::getInstance()->sendUpdateBuildingById(pid);
        this->updateLevel(NULL);
    } else {
        this->getParent()->getParent()->addChild(MyUtil::getInstance()->getNoResourceDialog(this->getParent()->getParent(),resourceTag));
        pSender->getParent()->getParent()->removeFromParentAndCleanup(true);
    }
}

float MyBuilding::updateBuilding() {
    
    float  summaryFinalCount =getUpdateSummary(getSummaryCount(),getLevel());
    if (MyGameInfo::getInstance()->getResource(resourceTag) >= summaryFinalCount ) {
        setLevel(getLevel()+1);
        this->getParent()->addChild(MyGameInfo::getInstance()->changeResourceAndFloatText(resourceTag, summaryFinalCount*-1, ccp(this->getPosition().x,this->getPosition().y+100)),1000000);
        this->getParent()->addChild(MyGameInfo::getInstance()->changeResourceAndFloatText(expTag, summaryFinalCount, ccp(this->getPosition().x,this->getPosition().y+160)),1000000);
        CCLabelTTF* levelFont = dynamic_cast<CCLabelTTF*>(this->getChildByTag(levelFontTag));
        //        CCLog("%f,%f",levelFont->getPosition().x,levelFont->getPosition().y);
        //        float x = levelFont->getPosition().x;
        //        float y = levelFont->getPosition().y;
        
        if (levelFont) {
            char str[20] = {0};
            sprintf(str, "等级 %d",getLevel());
            levelFont->setString(str);
            levelFont->setFontName("Arial");
        }
//        MyHttpConnection::getInstance()->sendUpdateBuildingById(pid);
        
        //        CCMenuItemFont::setFontSize(transWindowToGLInRetina(9));
        //        CCMenuItemFont::setFontName("Arial");
        //        CCMenuItemFont* levelFont2 = CCMenuItemFont::create(str);
        //        levelFont2->setPosition(ccp(x,y));
        //        levelFont2->setTag(levelFontTag);
        //        this->addChild(levelFont2,1000000);
        //        levelFont->removeFromParentAndCleanup(true);
    } else {
        return -1;
    }
    //    pSender->getParent()->getParent()->removeFromParentAndCleanup(true);
    return summaryFinalCount;
}

void MyBuilding::sellCallBack(cocos2d::CCNode *pSender) {
    ((MyMap*)map)->cancelAllBuilding();
    float  summaryFinalCount = 0;
    if (resourceTag == diamondTag) {
        summaryFinalCount = MyUtil::getInstance()->updateLevelBySquare(getSummaryCount()*10, getLevel()-1, updateSummaryRate)/2;
    } else {
        summaryFinalCount = MyUtil::getInstance()->updateLevelBySquare(getSummaryCount(), getLevel()-1, updateSummaryRate)/2;;
    }
     
    
    if (this->getTag() >= ornamentsDefineTag) {
        
        if (MyGameInfo::getInstance()->getResource(resourceTag) >= summaryFinalCount ) {
            CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sfx_updateBuilding.mp3");
            this->getParent()->addChild(MyGameInfo::getInstance()->changeResourceAndFloatText(resourceTag, summaryFinalCount*-1, ccp(this->getPosition().x,this->getPosition().y+100)),1000000);
            this->getParent()->addChild(MyGameInfo::getInstance()->changeResourceAndFloatText(expTag, summaryFinalCount, ccp(this->getPosition().x,this->getPosition().y+160)),1000000);
            this->setEnabled(false);
#if game_version == soft_version
            if (this->road != NULL) {
                this->road->runAction(CCSequence::create(CCFadeOut::create(3),GXRemoveFromParentsAction::create(),NULL));
            }
#endif
            ((MyState*)this->fsm->getCurrentState())->getItem()->runAction(CCFadeOut::create(1.5));
            this->runAction(CCSequence::create(CCDelayTime::create(1.5),GXRemoveFromParentsAction::create(),NULL));
            MyHttpConnection::getInstance()->sendRemoveBuildingById(pid);
            //        removeFromParentAndCleanup(true);
        } else {
            this->getParent()->getParent()->addChild(MyUtil::getInstance()->getNoResourceDialog(this->getParent()->getParent(),resourceTag));
        }
    } else {
        this->getParent()->addChild(MyGameInfo::getInstance()->changeResourceAndFloatText(resourceTag != diamondTag ?resourceTag:ironTag, summaryFinalCount/2, ccp(this->getPosition().x,this->getPosition().y+100)),1000000);
        this->getParent()->addChild(MyGameInfo::getInstance()->changeResourceAndFloatText(expTag, summaryFinalCount/2, ccp(this->getPosition().x,this->getPosition().y+160)),1000000);
        this->setEnabled(false);
#if game_version == soft_version 
        if (this->road != NULL) {
            this->road->runAction(CCSequence::create(CCFadeOut::create(3),GXRemoveFromParentsAction::create(),NULL));
        }
#endif
        ((MyState*)this->fsm->getCurrentState())->getItem()->runAction(CCFadeOut::create(1.5));
        this->runAction(CCSequence::create(CCDelayTime::create(1.5),GXRemoveFromParentsAction::create(),NULL));
        MyHttpConnection::getInstance()->sendRemoveBuildingById(pid);
        if (this->getUserData() != NULL) {
            ((BuildingInfo*)this->getUserData())->count--;
            this->setUserData(NULL);
        }
        //        removeFromParentAndCleanup(true);
    }
    pSender->getParent()->getParent()->removeFromParentAndCleanup(true);
    
}

void MyBuilding::setSummaryCount(int count) {
    summaryCount->setValue(count);
}
int MyBuilding::getSummaryCount() {
    return summaryCount->getValue();
}


void MyBuilding::setMaxLevel(int _maxLevel) {
    maxLevel->setValue(_maxLevel);
}

int MyBuilding::getMaxLevel() {
    return maxLevel->getValue();
}

float MyBuilding::getUpdateSummary(float base,int level) {
    if (resourceTag != diamondTag) {
        return MyUtil::getInstance()->updateLevelBySquare(base, level, updateSummaryRate);
    } else {
        return MyUtil::getInstance()->updateLevelByCount(base, level, base);
    }
}




//bool MyBuilding::ccTouchBegan(cocos2d::CCTouch *touch, cocos2d::CCEvent *event) {
//    
//    if (isActive) {
//        cacheTouch  = map->transMapToTiled(map->convertToNodeSpace(touch->getLocation()));
//        if (CCMenu::ccTouchBegan(touch, event)) {
//            if (m_pSelectedItem->getTag() == myTiledMenuItemTag) {
//                moveEnabled = true;
//                isMoved = false;
//                cacheLoc = this->getPosition();
//                ((MyMap*)map)->moveTemp = this;
//                MyMenu::reorderZandTouchPriority(1000000, -499);
//            } else {
//                moveEnabled = false;
//                isMoved = false;
//            }
//            return true;
//        }
//        return false;
//    }
//    if (((MyMap*)map)->isBuild()) {
//        return false;
//    }
//    CC_UNUSED_PARAM(event);
//    if (m_eState != kCCMenuStateWaiting || ! m_bIsVisible || !m_bEnabled)
//    {
//        return false;
//    }
//    
//    for (CCNode *c = this->m_pParent; c != NULL; c = c->getParent())
//    {
//        if (c->isVisible() == false)
//        {
//            return false;
//        }
//    }
//    
//    m_pSelectedItem = this->itemForTouch(touch);
//    if (m_pSelectedItem)
//    {
//        m_eState = kCCMenuStateTrackingTouch;
//        m_pSelectedItem->selected();
//        return true;
//    }
//    return false;
//}



CCObject* BuildingCreator::creatObj() {
    return NULL;
}

void BuildingCreator::doFill(cocos2d::CCObject *entity) {
    
}

BuildingCreator* BuildingCreator::create() {
    BuildingCreator* creator = new BuildingCreator();
    creator->autorelease();
    return creator;
}

DescInfo* DescInfo::create() {
    DescInfo* info = new DescInfo();
    info->autorelease();
    return info;
}
