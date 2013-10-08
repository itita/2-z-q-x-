//
//  ReadyToBuild.cpp
//  ww2
//
//  Created by xiao tang on 12-10-9.
//
//

#include "ReadyToBuild.h"
#include "StartScene.h"
#include "SimpleAudioEngine.h"
#include "MyGameInfo.h"
#include "MyGameFactory.h"
#include "MyContinueTiledSprite.h"
#include "GXRemoveFromParentsAction.h"
#include "MyPriorityMenu.h"
#include "MyUtil.h"
#include "UpdateBuildingMessag.h"
#include "MyHttpConnection.h"

ReadyToBuild::~ReadyToBuild() {
    CC_SAFE_RELEASE_NULL(resourceTag);
    CC_SAFE_RELEASE_NULL(summaryCount);
    CC_SAFE_RELEASE_NULL(addExp);
    CCLog("ReadyToBuild release");
}

ReadyToBuild* ReadyToBuild::create(int _stateId, CCSprite* item) {
    ReadyToBuild* pState = new ReadyToBuild();
    pState->stateId = _stateId;
    pState->autorelease();
    pState->item = item;
//    item->setTarget(pState, menu_selector(NormalState::CallBack));
    CC_SAFE_RETAIN(item);
    //    bdItem->setAnchorPoint(ccp(0.5,0.45));
    
    return pState;
}

void ReadyToBuild::doEnd() {
    //删除会导致 这边的transition 在map 的 m_pselected上出错。
//    building->fsm->deleteState(getId());
    building->removeChildByTag(transitionMenuTag,true);
//    CCArray* tags = getAllInput();
//    CCObject* obj;
//    CCMenuItem* menuitem;
//    CCARRAY_FOREACH(tags, obj) {
//        //TODO
//        menuitem = dynamic_cast<CCMenuItem*>(itemDictionary->objectForKey(((CCInteger*)obj)->getValue()));
//        menuitem->removeFromParentAndCleanup(true);
//    }
}

//void ReadyToBuild::dismissAllTransition() {
//    CCArray* tags = getAllInput();
//    CCObject* obj;
//    CCMenuItem* menuitem;
//    CCARRAY_FOREACH(tags, obj) {
//        //TODO
//        menuitem = dynamic_cast<CCMenuItem*>(itemDictionary->objectForKey(((CCInteger*)obj)->getValue()));
//        if (menuitem->isVisible()) {
//            menuitem->stopAllActions();
//            menuitem->setVisible(false);
//        }
//    }
//}

void ReadyToBuild::showAllTransition() {
    
    if (building->getChildByTag(transitionMenuTag) != NULL) {
        return;
    }
    
    CCArray* tags = getAllInput();
    CCObject* obj;
    CCMenuItem* menuItem;
    //    CCInteger* i;
    MyPriorityMenu* menu = MyPriorityMenu::create(-504,NULL,NULL);
    building->displaySummary();
    int i = 0;
    CCARRAY_FOREACH(tags, obj) {
        menuItem = dynamic_cast<TransitionInfo*>(itemDictionary->objectForKey(((CCInteger*)obj)->getValue()))->getButton();
        
        menuItem->runAction(CCFadeTo::create(0.15,255));
        menu->addChild(menuItem);
        i++;
        
    }
    menu->alignItemsHorizontallyWithPadding(25);
    menu->setTag(transitionMenuTag);
    menu->setPosition( ccp(0,building->y +60));
    building->addChild(menu);
    
//    CCArray* tags = getAllInput();
//    CCObject* obj;
//    CCMenuItem* menuItem;
//    //    CCInteger* i;
//    
//    building->displaySummary();
//    int i = 0;
//    CCARRAY_FOREACH(tags, obj) {
//        menuItem = dynamic_cast<CCMenuItem*>(itemDictionary->objectForKey(((CCInteger*)obj)->getValue()));
//        if (menuItem->getParent() == NULL) {
//            menuItem->stopAllActions();
//            menuItem->setVisible(true);
//            menuItem->setPosition( ccp(building->getPosition().x-(tags->count()-1)*50+i*100,building->getPosition().y+building->contentSizeByTiled.height*20 +100));
//            menuItem->runAction(CCFadeTo::create(0.15,255));
//            building->map->addChild(menuItem,1000000);
//            menuItem->setEnabled(true);
//            i++;
//        }
//        
//        
//    }
}


void ReadyToBuild::cancelCallBack(cocos2d::CCObject *pSender) {
    MyMap* map = (MyMap*)(building->map);
    
    map->setBuild(false,NULL);
    map->dispearTip();
    map->dispearArrowTip();
    dismissAllTransition();
    map->moveTemp = NULL;
    building->removeFromParentAndCleanup(true);
    ((StartScene*)(map->getParent()))->displayControlUI();
}

//ReadyToBuildCreator* ReadyToBuildCreator::create() {
//    ReadyToBuildCreator* creator = new ReadyToBuildCreator();
//    creator->autorelease();
//    return creator;
//}
//
//
//CCObject* ReadyToBuildCreator::init() {
//    CCSprite* whiteBy = CCSprite::create("zhs1.png");
//    whiteBy->setColor(ccGRAY);
//    CCSprite* transby = CCSprite::create("zhs1.png");
//    transby->setColor(ccWHITE);
////    MyTiledMenuItemSprite* byItem = MyTiledMenuItemSprite::create(transby, whiteBy);
//
////    ReadyToBuild* readyState = ReadyToBuild::create(ReadyToBuildStateTag, byItem);
////    doFill(readyState);
//    return  NULL;
//}

void ReadyToBuild::toBuildCallback(cocos2d::CCNode *pSender) {
    MyMap* map = (MyMap*)(building->getParent());
    StartScene* scene = (StartScene*)(map->getParent());
    if (map->collisionDetection(building)) {
        
        //可以弹弹警告
        CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sfx_error.wav");
        return;
    }
    
    ReadyToBuild* readyState = (ReadyToBuild*)building->fsm->getState(ReadyToBuildStateTag);
    if (readyState && MyGameInfo::getInstance()->getResource(readyState->getResourceTag()) >= readyState->getSummaryCount() ) {
//        if (readyState->getSummaryOil()!=0) {
        CCPoint pos = ccp(building->getPosition().x,building->getPosition().y+ building->contentSizeByTiled.height/2 *40 +60);
        map->addChild(MyGameInfo::getInstance()->changeResourceAndFloatText(readyState->getResourceTag(), readyState->getSummaryCount()*-1,pos),1000001);
        map->addChild(MyGameInfo::getInstance()->changeResourceAndFloatText(expTag, readyState->getSummaryCount(),ccp(pos.x,pos.y+60)),1000001);
        UpdateBuildingMessag::create(building->getTag(),0,1)->sendMsg();
//        }
    } else {
        scene->removeChildByTag(NoResourceTag,true);
        scene->addChild(MyUtil::getInstance()->getNoResourceDialog(scene,readyState->getResourceTag()));
        return;
    }
    
    //如果数量够的话
    
    //    map->setBuild(false);
    
    //    displayControlUI();
    CCPoint loc = building->getPositionByTiled();
    building->reorderZandTouchPriority(999999-building->getPosition().y);
    building->cacheLoc = ccp(building->getPosition().x,building->getPosition().y);
    building->pid = MyGameInfo::getInstance()->maxId + 1;
//    if (building->pid - MyGameInfo::getInstance()->maxId != 1) {
//        CCLog("估计有错");
//    }
    MyGameInfo::getInstance()->maxId++;
//    CCLog("maxId:%d",MyGameInfo::getInstance()->maxId);
//    CCLog("maxId:%d",MyGameInfo::getInstance()->maxId);
    MyHttpConnection::getInstance()->sendConstructBuilding(building->pid,building->getTag(),loc.x,loc.y);
    
    
    MyBuilding* newbuilding = scene->createReady(building->getTag());
    ((ReadyToBuild*)newbuilding->fsm->getCurrentState())->setResourceTag(((ReadyToBuild*)building->fsm->getState(ReadyToBuildStateTag))->getResourceTag());
    ((ReadyToBuild*)newbuilding->fsm->getCurrentState())->setSummaryCount(((ReadyToBuild*)building->fsm->getState(ReadyToBuildStateTag))->getSummaryCount());
    
    //    ((ReadyToBuild*)build->fsm->getCurrentState())->addExp = card->addExp;
    //    CCLog("%f,%f",map->oriBuildPos.x,map->oriBuildPos.y);
    if(loc.x - map->oriBuildPos.x >0) {
        loc.x +=newbuilding->contentSizeByTiled.width;
    } else if(loc.x - map->oriBuildPos.x <0){
        loc.x -=newbuilding->contentSizeByTiled.width;
    }
    if(loc.y - map->oriBuildPos.y >0) {
        loc.y +=newbuilding->contentSizeByTiled.height;
    } else if(loc.y - map->oriBuildPos.y <0){
        loc.y -=newbuilding->contentSizeByTiled.height;
    }
    
    
    
    newbuilding->setPositionByTiled(loc);
    if (!map->checkScreenBound(newbuilding->getPosition().x, newbuilding->getPosition().y)) {
        ((ReadyToBuild*)newbuilding->fsm->getState(ReadyToBuildStateTag))->cancelCallBack(NULL);
    } else {
    //    int dir = (((int)(angle*180/3.141592654+22.5)+360)%360)/45 ;
        map->oriBuildPos = building->getPositionByTiled();
        map->moveArrowTip(newbuilding->getPositionByTiled(), newbuilding->contentSizeByTiled);
        //    map->
        map->initTip(newbuilding->getPosition(), newbuilding->contentSizeByTiled);
        map->collisionDetection(newbuilding);
        map->getTip();
    }
    if (building->getTag() == wallTag) {
        building->changeStateById(WorkStateTag);
        //TODO
        ((MyContinueTiledSprite*)((MyState*)building->fsm->getCurrentState())->getItem())->updateLoc(1);
    } else {
        building->changeStateById(UnfinishedStateTag);
    }
    
    if (maxCount > 0) {
        if (buildingInfo->count-1 >= maxCount) {
            ((ReadyToBuild*)newbuilding->fsm->getState(ReadyToBuildStateTag))->cancelCallBack(NULL);
        }
    }
}

void ReadyToBuild::setResourceTag(int _resourceTag) {
    resourceTag->setValue(_resourceTag);
}

int ReadyToBuild::getResourceTag() {
    return resourceTag->getValue();
}

void ReadyToBuild::setSummaryCount(int _summaryCount) {
    summaryCount->setValue(_summaryCount);
}

int ReadyToBuild::getSummaryCount() {
    return summaryCount->getValue();
}

void ReadyToBuild::setAddExp(int _addExp) {
    addExp->setValue(_addExp);
}

int ReadyToBuild::getAddExp() {
    return addExp->getValue();
}
