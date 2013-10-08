//
//  SplitState.cpp
//  ww4
//
//  Created by xiao tang on 13-4-7.
//
//

#include "SplitState.h"
#include "SimpleAudioEngine.h"
#include "BuildingHeader.h"
#include "MyGameInfo.h"
#include "MyHttpConnection.h"

SplitState* SplitState::create(int _stateId, CCSprite* item,int _splitBuildingTag) {
    SplitState* pState = new SplitState();
    pState->stateId = _stateId;
    pState->autorelease();
    pState->splitBuildingTag =_splitBuildingTag;
    
    pState->item = item;
    //    item->setTarget(pState, menu_selector(NormalState::CallBack));
    pState->item->retain();
    //    bdItem->setAnchorPoint(ccp(0.5,0.45));
    
    return pState;
}

void SplitState::init(MyBuilding *building) {
    MyState::init(building);
    this->building = building;
    
}



void SplitState::doState() {
    
}

void SplitState::setItem(cocos2d::CCSprite *_item) {
    CC_SAFE_RELEASE(item);
    this->item = _item;
    _item->retain();
}

void SplitState::toSplitCallBack(CCMenuItem *pSender) {
    pSender->setEnabled(false);
    MyMap* map = ((MyMap*)building->map);
    if (map->collisionDetection(building)) {
        building->toReLoc();
        CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sfx_error.wav");
        return;
    }
    building->dismissAllTransition();
    building->dismissSummary();
    building->setActive(false);
    if (map->moveTemp == building) {
        map->moveTemp = NULL;
    }
    map->dispearArrowTip();
    map->dispearTip();
    int i=0;
    int j=0;
    int cWidth = 0;
    int cHeight = 0;
    int x = building->contentSizeByTiled.width;
    int y = building->contentSizeByTiled.height;
    CCPoint tiledPos = map->transMapToTiled(building->getPosition());
    MyBuilding* acBuild = NULL;
    while (i<x) {
        while (j<y) {
            //todo 先写死，以后直接传 createNormal函数过来就行了
            MyBuilding* newBuilding = Wall::createNormal(building->map->getParent(),building->getLevel());
            cWidth = newBuilding->contentSizeByTiled.width;
            cHeight = newBuilding->contentSizeByTiled.height;
            newBuilding->setPositionByTiled(ccp(tiledPos.x+i-x/2,tiledPos.y+j-y/2));
            newBuilding->pid = MyGameInfo::getInstance()->maxId+1;
//            if (newBuilding->pid - MyGameInfo::getInstance()->maxId != 1) {
//                CCLog("估计有错");
//            }
            MyGameInfo::getInstance()->maxId++;
//            CCLog("maxId:%d",MyGameInfo::getInstance()->maxId);
            map->addChild(newBuilding);
            if (i/cWidth == x/2 && j/cHeight == y/2) {
                acBuild = newBuilding;
            }
            j=j+cHeight;
        }
        j=0;
        i=i+cWidth;
    }
//    int cWidth = newBuilding->contentSizeByTiled.width;
//    int cHeight = newBuilding->contentSizeByTiled.height;
//    int x = building->contentSizeByTiled.width / cWidth;
//    int y = building->contentSizeByTiled.height/ cHeight;
//    
//    
//    for (int i = 0; i<x; i++) {
//        for (int j = 0; j<y; j++) {
//            MyBuilding* newBuilding = MyGameFactory::createByTag(splitBuildingTag,building->map->getParent(),building->getLevel());
//            
//            
//        }
//    }
    MyHttpConnection::getInstance()->sendSplitBuilding(building->pid);
    //在移除后building有可能变成野指针
    building->removeFromParentAndCleanup(true);
    if (acBuild != NULL) {
        acBuild->activate();
        map->moveTemp = acBuild;
        acBuild->cacheLoc = acBuild->getPosition();
    }
    
//    CCPoint oriP = building->map->transMapToTiled(building->getPosition());
//    float posX = oriP.x;
//    float posY = oriP.y;
//    if (lrLoc > 0) {
//        posX = posX-4+lrLoc;
//    }
//    
//    if(((int)newBuilding->contentSizeByTiled.width)%2 ==0) {
//        posX+=0.5;
//    }
//    if(((int)newBuilding->contentSizeByTiled.height)%2 ==0) {
//        posY+=0.5;
//    }
//    newBuilding->setPositionByTiled(ccp(posX,posY));
//    building->map->addChild(newBuilding);
//    for (int i = 0; i<4; i++) {
//        if (destroyBuilding[i] == map->moveTemp)  {
//            map->moveTemp = NULL;
//        }
//        destroyBuilding[i]->removeFromParentAndCleanup(true);
//    }
  
    
    
}
