//
//  NormalState.cpp
//  ww2
//
//  Created by DingYu Fu on 12-9-14.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "NormalState.h"
#include "DefineSet.h"
#include "GXProgressBar.h"
#include "MyContinueTiledSprite.h"



NormalState* NormalState::create(int _stateId, CCSprite* item) {
    NormalState* pState = new NormalState();
    pState->stateId = _stateId;
    pState->autorelease();
    pState->item = item;
//    item->setTarget(pState, menu_selector(NormalState::CallBack));
    CC_SAFE_RETAIN(item);
    //    bdItem->setAnchorPoint(ccp(0.5,0.45));
    
    return pState;
}

void NormalState::init(MyBuilding *building) {
    MyState::init(building);
    this->building = building;
    
}

//void NormalState::clickCallBack(){
//    MyState::clickCallBack();
//    if (dynamic_cast<MyContinueTiledSprite*>(item)) {
//        ((MyContinueTiledSprite*)item)->updateLoc(1);
//    }
//}

//void NormalState::doState() {
//    
//    
//}

void NormalState::setItem(cocos2d::CCSprite *_item) {
//    building->removeChildByTag(myTiledMenuItemTag, true);
    CC_SAFE_RELEASE(item);
    this->item = _item;
//    _item ->setTag(myTiledMenuItemTag);
//    _item->setTarget(this, menu_selector(NormalState::CallBack));
    CC_SAFE_RETAIN(_item);
}

//void NormalState::changeIdCallBack(cocos2d::CCObject *pSender) {
//    MyBuilding* building = (MyBuilding*)((CCMenuItem*)pSender) ->getParent();
//    building->changeState(BuildTransition);
//}
//
//void NormalState::sellCallBack(cocos2d::CCObject *pSender) {
//
//}

//NormalStateCreator* NormalStateCreator::create() {
//    NormalStateCreator* creator = new NormalStateCreator();
//    creator->autorelease();
//    return creator;
//}
//
//CCObject* NormalStateCreator::createObj() {
//    CCSprite* grayBy = CCSprite::create(CCMenuItemSpriteName);
//    grayBy->setColor(ccGRAY);
//    MyTiledMenuItemSprite* byItem = MyTiledMenuItemSprite::create(CCSprite::create(CCMenuItemSpriteName), grayBy);
//    byItem->setAnchorPoint(itemAnchor);
//    
//    // 普通状态
////    NormalState* workState = NormalState::create(WorkStateTag, byItem);
//    return  NULL;
//}
