//
//  GarbageCollectionNormalState.cpp
//  ww4
//
//  Created by xiao tang on 13-5-24.
//
//

#include "GarbageCollectionNormalState.h"
#include "DefineSet.h"
#include "SimpleAudioEngine.h"
#include "MyGameInfo.h"
#include "GXFadeOutAndRemoveWhenStop.h"
#include "StartScene.h"
#include "MyUtil.h"
#include "MathLib.h"
#include "BuildingHeader.h"
#include "MyHttpConnection.h"

GarbageCollectionNormalState* GarbageCollectionNormalState::create(int _stateId,CCSprite* item,int _resourceCount) {
    GarbageCollectionNormalState* pState = new GarbageCollectionNormalState();
    pState->stateId = _stateId;
    pState->autorelease();
    pState->item = item;
    //    item->setTarget(pState, menu_selector(NormalState::CallBack));
    CC_SAFE_RETAIN(item);
    //    bdItem->setAnchorPoint(ccp(0.5,0.45));
    pState->resourceCount = _resourceCount;
    
    return pState;
}

void GarbageCollectionNormalState::clickCallBack() {
    StartScene* scene = (StartScene*)building->getParent()->getParent();
//    scene->toOneKeyArchieveGhost(NULL);
    scene->subMubei();
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sfx_collect.mp3");
    
    MyBuilding* huishouCenter = (MyBuilding*)building->map->getChildByTag(GarbageCenterTag);
    float rate = 0;
    if(huishouCenter != NULL) {
        float maxRate = MyUtil::getInstance()->updateLevelByCount(hszxBaseMaxRecycling,huishouCenter->getLevel(),hszxUpdateMaxRecyclingCount);
        rate = Mathlib::min(maxRate,(YouTian::getYouTianInfo()->count+SuperYouTian::getSuperYouTianInfo()->count*3) * 0.01);
    }
    doCollect(rate);
    MyHttpConnection::getInstance()->sendCollectMubeiById(building->pid);
    
    MyMap* map = (MyMap*)(building->map);
    map->setBuild(false,NULL);
    map->dispearTip();
    map->dispearArrowTip();
    dismissAllTransition();
    map->moveTemp = NULL;
    building->setEnabled(false);
    isDestroy = true;
    item->runAction(CCFadeOut::create(1.5));
    
    
//    building->runAction(GXFadeOutAndRemoveWhenStop::create(1.5));
    
    
}

int GarbageCollectionNormalState::doCollect(float rate) {
    int addCount = (int)resourceCount*rate;
    if (addCount>0) {
        CCLayer* floatLayer = MyGameInfo::getInstance()->changeResourceAndFloatText(oilTag, resourceCount*rate, ccp(building->getPosition().x,building->getPosition().y+30*building->contentSizeByTiled.height+100));
        CCLayer* expFloatLayer = MyGameInfo::getInstance()->changeResourceAndFloatText(expTag, resourceCount*rate, ccp(building->getPosition().x,building->getPosition().y+30*building->contentSizeByTiled.height+160));
        building->map->addChild(floatLayer,1000001);
        building->map->addChild(expFloatLayer,1000001);
    }
    CCLayer* gloryFloatLayer = MyGameInfo::getInstance()->changeResourceAndFloatText(gloryTag, (resourceCount/20000)+1, ccp(building->getPosition().x,building->getPosition().y+30*building->contentSizeByTiled.height+40));
    building->map->addChild(gloryFloatLayer,1000001);
    return resourceCount;
}

void GarbageCollectionNormalState::doState() {
    if (isDestroy) {
//        MyMap* map = (MyMap*)(building->map);
//        map->setBuild(false,NULL);
//        map->dispearTip();
//        map->dispearArrowTip();
//        dismissAllTransition();
//        map->moveTemp = NULL;
        MyMap* map = (MyMap*)building->getParent();
        map->removeChild(building,true);
//        building->removeFromParentAndCleanup(true);
    }
}