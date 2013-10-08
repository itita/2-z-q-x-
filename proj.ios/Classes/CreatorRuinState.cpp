//
//  CreatorRuinState.cpp
//  ww3
//
//  Created by xiao tang on 12-10-29.
//
//

#include "CreatorRuinState.h"
#include "DefineSet.h"

CreatorRuinState::~CreatorRuinState() {
//    CCLog("CreatorRuinState released");
}

CreatorRuinState* CreatorRuinState::create(int _stateId, cocos2d::CCSprite *item, int _lifePercentage) {
    
    CreatorRuinState* pState = new CreatorRuinState();
    pState->stateId = _stateId;
    pState->autorelease();
    pState->item = item;
//    item->setTarget(pState, menu_selector(NormalState::CallBack));
    pState->item->retain();
    pState->lifePercentage = _lifePercentage;
    //    bdItem->setAnchorPoint(ccp(0.5,0.45));
    return pState;
}

void CreatorRuinState::doState() {
    lifePercentage+=5;
    xuetiao->updatePercentage((float)lifePercentage/100);
    if(currentId == 0 || currentId>100) {
    	currentId = 17;
    }
    if (lifePercentage >= 100) {
        building->changeStateById(currentId);
        building->removeChild(item, true);
        building->setEnabled(true);
        GXFSMstate* nextState = building->fsm->getState(currentId);
        for (int i = 0; i<20; i++) {
            nextState->doState();
        }
        building->fsm->deleteState(RuinsStateTag);
    }
}

void CreatorRuinState::init(MyBuilding* building) {
    RuinState::init(building);
    
    xuetiao=MyXueTiao::create("xuetiao.png");
    
    xuetiao->setScaleX((item->getContentSize().width)/xuetiao->getContentSize().width);
    xuetiao->setScaleY(0.3);
    xuetiao->setPosition(ccp(0,item->getContentSize().height+10));
    xuetiao->updatePercentage(0);
    item->addChild(xuetiao,5);
}

//CreatorRuinStateCreator* CreatorRuinStateCreator::create() {
//    CreatorRuinStateCreator* creator = new CreatorRuinStateCreator();
//    creator->autorelease();
//    return creator;
//}
//
//CCObject* CreatorRuinStateCreator::init(cocos2d::CCObject *entity) {
////    MyTiledMenuItemSprite* ruinItem = MyTiledMenuItemSprite::create(CCSprite::create("ruins.png"), CCSprite::create("ruins.png"));
//    
////    
////    CreatorRuinState* ruinstate = CreatorRuinState::create(RuinsStateTag, ruinItem,lifePercentage);
////    ruinItem->setEnabled(false);
////    doFill(ruinstate);
////    return ruinstate;
//    return NULL;
//}

