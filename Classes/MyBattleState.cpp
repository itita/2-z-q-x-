//
//  MyBattleState.cpp
//  ww3
//
//  Created by xiao tang on 12-12-3.
//
//

#include "MyBattleState.h"

MyBattleState::MyBattleState() {
    item = NULL;
    building = NULL;
    doStateTime = -1;
    input_output = cocos2d::CCDictionary::create();
    input_output->retain();
}

MyBattleState::~MyBattleState() {
    CC_SAFE_RELEASE_NULL(item);
}

MyBattleState* MyBattleState::create(int _stateId,CCSprite* item,int _dostateTime) {
    MyBattleState* pState = new MyBattleState();
    pState->stateId = _stateId;
    pState->autorelease();
    pState->doStateTime = _dostateTime;
    pState->item = item;
    pState->item->retain();
    return pState;
}

void MyBattleState::init(MyBattleBuilding* building) {
    this->building = building;
}

void MyBattleState::doState() {
    
}

void MyBattleState::setItem(CCSprite *item) {
    
}

CCSprite* MyBattleState::getItem() {
    if (item) {
        item->setTag(mainTiledSpriteTag);
    }
    return item;
}

float MyBattleState::getArg0() {
    return -1;
}

