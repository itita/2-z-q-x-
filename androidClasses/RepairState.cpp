//
//  RepairState.cpp
//  ww4
//
//  Created by xiao tang on 13-3-31.
//
//

#include "RepairState.h"
#include "SimpleAudioEngine.h"
#include "StartScene.h"
#include "DefineSet.h"
#include "Mathlib.h"
#include "MyGameInfo.h"
#include "MyUtil.h"
#include "UpdateBuildingMessag.h"
#include "MyHttpConnection.h"

RepairState* RepairState::create(int _stateId,int _targetTag,CCSprite* _item) {
    
    RepairState* pState = new RepairState();
    pState->stateId = _stateId;
    pState->autorelease();
    pState->item = _item;
    pState->item->retain();
    pState->targetTag = _targetTag;
//    pState->fileName = fileName;
//    pState->maxLevel = maxLevel;
    //    pState->item = ;
    //    item->setTarget(pState, menu_selector(NormalState::CallBack));
    //    pState->item->retain();
    //    bdItem->setAnchorPoint(ccp(0.5,0.45));
    
    return pState;
}

void RepairState::init(MyBuilding *building) {
    MyState::init(building);
    this->building = building;

    //    item-> setTag(myTiledMenuItemTag);
}

//void UnfinishedState::updateItem() {
//    if (building != NULL) {
//        char str[30] = {0};
//        if (building->contentSizeByTiled.width == 2) {
//            sprintf(str, "%s2x2(%d).png",fileName,level);
//            if (item != NULL) {
//                item->removeFromParentAndCleanup(true);
//                CC_SAFE_RELEASE_NULL(item);
//                item = NULL;
//            }
//            item = CCSprite::createWithSpriteFrameName(str);
//        } else if(building ->contentSizeByTiled.width == 3) {
//            sprintf(str, "%s3x3(%d).png",fileName,level);
//            if (item != NULL) {
//                item->removeFromParentAndCleanup(true);
//                CC_SAFE_RELEASE_NULL(item);
//                item = NULL;
//            }
//            item = CCSprite::createWithSpriteFrameName(str);
//        } else if(building->contentSizeByTiled.width == 4) {
//            sprintf(str, "%s4x4(%d).png",fileName,level);
//            if (item != NULL) {
//                item->removeFromParentAndCleanup(true);
//                CC_SAFE_RELEASE_NULL(item);
//                item = NULL;
//            }
//            item = CCSprite::createWithSpriteFrameName(str);
//        } else {
//            //            CCAssert(1 == 2, "not surport bigger size");
//        }
//        item->retain();
//    }
//}


void RepairState::changeIdCallBack(CCMenuItem *pSender) {
    ((MyMap*)(building->map))->cancelAllBuilding();
    if (MyGameInfo::getInstance()->getResource(building->resourceTag) >= building->getSummaryCount() ) {
        building->getParent()->addChild(MyGameInfo::getInstance()->changeResourceAndFloatText(building->resourceTag, building->getSummaryCount()*-1, ccp(building->getPosition().x,building->getPosition().y+100)),1000000);
        building->getParent()->addChild(MyGameInfo::getInstance()->changeResourceAndFloatText(expTag, building->getSummaryCount(), ccp(building->getPosition().x,building->getPosition().y+160)),1000000);
        building->cacheLoc = building->getPosition();
        building->changeState(RepairTransition);
        building->moveEnabled = true;
        building->setTag(targetTag);
        UpdateBuildingMessag::create(targetTag,0,1)->sendMsg();
        MyHttpConnection::getInstance()->sendRepiarBuildingById(building->pid);
        if (building->contentSizeByTiled.width  > 1) {
            CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sfx_toBuild.mp3");
        }
        building->fsm->deleteState(getId());
    } else {
        building->getParent()->getParent()->addChild(MyUtil::getInstance()->getNoResourceDialog(building->getParent()->getParent(),building->resourceTag));
    }
    pSender->getParent()->getParent()->removeFromParentAndCleanup(true);
}

void RepairState::RepairCallBack(cocos2d::CCObject *pSender) {
    
    StartScene* scene =  ((StartScene*)(building->map->getParent()));
    scene->removeChildByTag(updateLayerTag, true);
    CCLayer* infoLayer = MyUtil::getInstance()->getInfoDialog();
    scene->addChild(infoLayer);
    
    CCLabelTTF* label = CCLabelTTF::create("修  复","Arial",38);
    label->setColor(ccc3(240,147,1));
    CCMenuItemLabel* repairButton = CCMenuItemLabel::create(label,this,menu_selector(RepairState::changeIdCallBack));
    repairButton->setPosition(ccp(0,-130));
    ((CCMenu*)infoLayer->getChildByTag(updateMenuTag))->addChild(repairButton);
        
    if (building->resourceTag == oilTag) {
        CCSprite* resourceIcon = CCSprite::createWithSpriteFrameName("oilIcon.png");
        resourceIcon->setScale(0.5);
        resourceIcon->setPosition(ccp(-43,-170));
        infoLayer->addChild(resourceIcon);
    } else {
        CCSprite* resourceIcon = CCSprite::createWithSpriteFrameName("ironIcon.png");
        resourceIcon->setScale(0.5);
        resourceIcon->setPosition(ccp(-43,-168));
        infoLayer->addChild(resourceIcon);
    }
    char str[12] = {0};
    sprintf(str, "-%d",(int)(building->getSummaryCount()));
            
    CCLabelTTF* summaryResourceCount = CCLabelTTF::create(str, "Arial", 24);
    summaryResourceCount->setColor(ccc3(254,218,130));
    summaryResourceCount->setAnchorPoint(ccp(0.5,0.5));
            
    summaryResourceCount->setPosition(ccp(Mathlib::max(summaryResourceCount->getContentSize().width/2-28, 4),-170) );
    infoLayer->addChild(summaryResourceCount);
}



