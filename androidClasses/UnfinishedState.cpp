//
//  UnfinishedState.cpp
//  ww3
//
//  Created by xiao tang on 12-10-18.
//
//

#include "UnfinishedState.h"
#include "GXFadeOut.h"
#include "DefineSet.h"
#include "GXRemoveFromParentsAction.h"
#include "SimpleAudioEngine.h"
#include "MyPriorityMenu.h"
#include "MyMenuItem.h"
#include "MyHttpConnection.h"

UnfinishedState::~UnfinishedState() {
    CCLog("UnfinishedState has released");
}

UnfinishedState* UnfinishedState::create(int _stateId, const char *fileName, int maxLevel) {
    UnfinishedState* pState = new UnfinishedState();
    pState->stateId = _stateId;
    pState->autorelease();
    pState->fileName = fileName;
    pState->maxLevel = maxLevel;
//    pState->item = ;
//    item->setTarget(pState, menu_selector(NormalState::CallBack));
//    pState->item->retain();
    //    bdItem->setAnchorPoint(ccp(0.5,0.45));
    
    return pState;
}

void UnfinishedState::init(MyBuilding *building) {
    MyState::init(building);
    this->building = building;
    updateItem();
//    item-> setTag(myTiledMenuItemTag);
}

void UnfinishedState::updateItem() {
    if (building != NULL) {
        char str[30] = {0};
        if (building->contentSizeByTiled.width == 2) {
            sprintf(str, "%s2x2(%d).png",fileName,level);
            if (item != NULL) {
                item->removeFromParentAndCleanup(true);
                CC_SAFE_RELEASE_NULL(item);
                item = NULL;
            }
            item = CCSprite::createWithSpriteFrameName(str);
        } else if(building ->contentSizeByTiled.width == 3) {
            sprintf(str, "%s3x3(%d).png",fileName,level);
            if (item != NULL) {
                item->removeFromParentAndCleanup(true);
                CC_SAFE_RELEASE_NULL(item);
                item = NULL;
            }
            item = CCSprite::createWithSpriteFrameName(str);
        } else if(building->contentSizeByTiled.width == 4) {
            sprintf(str, "%s4x4(%d).png",fileName,level);
            if (item != NULL) {
                item->removeFromParentAndCleanup(true);
                CC_SAFE_RELEASE_NULL(item);
                item = NULL;
            }
            item = CCSprite::createWithSpriteFrameName(str);
        } else {
//            CCAssert(1 == 2, "not surport bigger size");
        }
        item->retain();
    }
}
void UnfinishedState::CallBack(cocos2d::CCObject *pSender){
    if(!building->getActive()) {
        //同时把提示也给显示了吧
        building->setActive(true);
    }
    ((MyTiledMenuItemSprite*)pSender)->runTouchAction();
    if(building!=NULL) {
        showAllTransition();
    }
}

void UnfinishedState::changeIdCallBack(cocos2d::CCObject *pSender) {
    ((MyMap*)(building->map))->cancelAllBuilding();
    building->cacheLoc = building->getPosition();
    building->changeState(BuildTransition);
    int out = ((CCInteger*)this->getOutPut(BuildTransition))->getValue();
    MyHttpConnection::getInstance()->sendChangeStateById(building->pid,out);
    if (building->contentSizeByTiled.width  > 1) {
//        sprintf(str, "road%dx%d.png",(int)building->contentSizeByTiled.width,(int)building->contentSizeByTiled.width);
//        CCSprite* road = CCSprite::createWithSpriteFrameName(str);
//        road->runAction(CCFadeIn::create(1));
//        building->setRoad(road);
        CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sfx_toBuild.mp3");
    }
    building->fsm->deleteState(getId());
}

void UnfinishedState::sellCallBack(cocos2d::CCObject *pSender) {
    
}


//void UnfinishedState::dismissAllTransition() {

//    CCMenu* transitionMenu = (CCMenu*)building->getChildByTag(transitionMenuTag);
//    if (transitionMenu == NULL) {
//        return;
//    }
//    CCArray* tags = transitionMenu->getChildren();
//    CCObject* obj;
//    CCMenuItem* menuitem;
//    CCARRAY_FOREACH(tags, obj) {
//        //TODO
//        menuitem = dynamic_cast<CCMenuItem*>(obj);
//        if (menuitem->getTag() == BuildTransition){
//            continue;
//        }
//        menuitem->setEnabled(false);
//        menuitem->runAction(CCFadeOut::create(0.15));
//    }
    
//    CCArray* tags = getAllInput();
//    CCObject* obj;
//    CCMenuItem* menuitem;
//    CCARRAY_FOREACH(tags, obj) {
//        //TODO
//        menuitem = dynamic_cast<CCMenuItem*>(itemDictionary->objectForKey(((CCInteger*)obj)->getValue()));
////        CCLog("uid:%d",menuitem->getTag());
//        if (menuitem->getParent() != NULL ) {
//            //            item->setOpacity(0);
//            
//            if (menuitem->getTag() == BuildTransition){
//                menuitem->setPosition( ccp(building->getPosition().x,building->getPosition().y+building->contentSizeByTiled.height*20 +100));
//                continue;
//            }
//
//            menuitem->stopAllActions();
//            menuitem->setEnabled(false);
//            menuitem->runAction(CCSequence::create(CCFadeOut::create(0.15),GXRemoveFromParentsAction::create(),NULL));
//            //            item->setVisible(false);
//        }
//    }
    
//    CCArray* children = 
//    CCObject* obj;
//    CCMenuItem* item;
//    CCARRAY_FOREACH(children, obj) {
//        item = dynamic_cast<CCMenuItem*>(obj);
//        if (item != NULL ) {
//            if (item->getTag() == BuildTransition){
//                item->stopAllActions();
//                item->runAction(CCFadeIn::create(0.15));
//                item->setPosition(transWindowToGLInRetina(0,60));
//                continue;
//            }
//            item->setEnabled(false);
//            item->runAction(GXFadeOut::create(0.15));
//        }
//    }
//}


void UnfinishedState::showAllTransition() {
    building->getParent()->getParent()->removeChildByTag(zhuyeMenuTag,true);
    
    CCLayer* layer = CCLayer::create();
    layer->setTag(zhuyeMenuTag);
    
    CCArray* tags = getAllInput();
    CCObject* obj;
    //    CCMenuItem* menuItem;
    //    CCInteger* i;
    //    MyPriorityMenu* menu = MyPriorityMenu::create(-502,NULL,NULL);
    building->displaySummary();
    MyPriorityMenu* zhuyemenu = MyPriorityMenu::create(-502,NULL,NULL);
    //    building->displaySummary();
    int i = 0;
    float posi = tags->count()*120;
    CCARRAY_FOREACH(tags, obj) {
        //        menuItem = dynamic_cast<TransitionInfo*>(itemDictionary->objectForKey(((CCInteger*)obj)->getValue()))->getButton();
        //
        //        menuItem->runAction(CCFadeTo::create(0.15,255));
        //        menu->addChild(menuItem);
        
        MyMenuItem* item2 = (MyMenuItem*)dynamic_cast<TransitionInfo*>(itemDictionary->objectForKey(((CCInteger*)obj)->getValue()))->getButton();
        zhuyemenu->addChild(item2);
        item2->setScale(1.3);
        item2->setOpacity(100-i*20);
        //        item2->setOpacity(0);
        item2->setPosition(ccp(-posi/2+i*120+60,-30));
        item2->runAction(CCSpawn::create(CCSequence::create(CCDelayTime::create(0.07+0.05*(tags->count()-i)),CCFadeTo::create(0.23,255),NULL),CCSequence::create( CCDelayTime::create(0.05*(tags->count()-i)),CCEaseElasticOut::create(CCMoveBy::create(0.3,ccp(0,100)),1.3),NULL),NULL));
        i++;
    }
    //    menu->alignItemsHorizontallyWithPadding(25);
    //    menu->setTag(transitionMenuTag);
    //    menu->setPosition( ccp(0,building->y +60));
    //    building->addChild(menu);
    
    zhuyemenu->setPosition(ccp(winSize.width/2-10,0));
    //    zhuyemenu->alignItemsHorizontallyWithPadding(15);
    
    char str[100] = {0};
    sprintf(str, "%s (建造中)",building->getBuildingName());
    CCLabelTTF* name = CCLabelTTF::create(str,"Arial",30);
    name->setColor(ccWHITE);
    name->setPosition(ccp(winSize.width/2-10,150));
    name->runAction(CCFadeIn::create(0.3));
    
    CCSprite* nameBackCenter = CCSprite::createWithSpriteFrameName("nameKuang2.png");
    nameBackCenter->setPosition(ccp(winSize.width/2-10,150));
    nameBackCenter->setScaleX((name->getContentSize().width+20)/nameBackCenter->getContentSize().width);
    nameBackCenter->runAction(CCFadeIn::create(0.3));
    
    CCSprite* nameBackLeft = CCSprite::createWithSpriteFrameName("nameKuang1.png");
    nameBackLeft->setAnchorPoint(ccp(1,0.5));
    nameBackLeft->setPosition(ccp(winSize.width/2-18-name->getContentSize().width/2 ,150));
    nameBackLeft->runAction(CCFadeIn::create(0.3));
    
    CCSprite* nameBackRight = CCSprite::createWithSpriteFrameName("nameKuang1.png");
    nameBackRight->setAnchorPoint(ccp(1,0.5));
    nameBackRight->setRotation(180);
    nameBackRight->setPosition(ccp(winSize.width/2+name->getContentSize().width/2-2 ,150));
    nameBackRight->runAction(CCFadeIn::create(0.3));
    
    
    layer->addChild(zhuyemenu);
    layer->addChild(nameBackLeft);
    layer->addChild(nameBackCenter);
    layer->addChild(nameBackRight);
    layer->addChild(name);
    building->getParent()->getParent()->addChild(layer);
//    CCMenu* exist = (CCMenu*)building->getChildByTag(transitionMenuTag);
//    if (exist ==NULL) {
//        CCArray* tags = getAllInput();
//        CCObject* obj;
//        CCMenuItem* menuItem;
//        //    CCInteger* i;
//        MyPriorityMenu* menu = MyPriorityMenu::create(-502,NULL,NULL);
//        building->displaySummary();
//        int i = 0;
//        CCARRAY_FOREACH(tags, obj) {
//            menuItem = dynamic_cast<TransitionInfo*>(itemDictionary->objectForKey(((CCInteger*)obj)->getValue()))->getButton();
//            menuItem->runAction(CCFadeTo::create(0.15,255));
//            menu->addChild(menuItem);
//            i++;
//            
//        }
//        menu->alignItemsHorizontallyWithPadding(25);
//        menu->setTag(transitionMenuTag);
//        menu->setPosition( ccp(0,building->y +60));
//        building->addChild(menu);
//    } else {
//        //        return;
//        CCArray* tags = exist->getChildren();
//        CCObject* obj;
//        CCMenuItem* menuItem;
//        //    CCInteger* i;
//        building->displaySummary();
//        int i = 0;
//        CCARRAY_FOREACH(tags, obj) {
//            menuItem = dynamic_cast<CCMenuItem*>(obj);
//            menuItem->runAction(CCFadeTo::create(0.15,255));
//            menuItem->setEnabled(true);
//            i++;
//        }
//    }
//    
////    CCArray* tags = getAllInput();
////    CCObject* obj;
////    CCMenuItem* menuItem;
////    //    CCInteger* i;
////    
////    building->displaySummary();
////    int i = 0;
////    CCARRAY_FOREACH(tags, obj) {
////        menuItem = dynamic_cast<CCMenuItem*>(itemDictionary->objectForKey(((CCInteger*)obj)->getValue()));
////        menuItem->setEnabled(true);
////        if (menuItem->getTag() == BuildTransition) {
////            menuItem->stopAllActions();
////            menuItem->setPosition(ccp(building->getPosition().x-(tags->count()-1)*50+i*100,building->getPosition().y+building->contentSizeByTiled.height*20 +100));
////            menuItem->runAction(CCFadeIn::create(0.15));
////        } else {
////            menuItem->stopAllActions();
////            menuItem->setPosition( ccp(building->getPosition().x-(tags->count()-1)*50+i*100,building->getPosition().y+building->contentSizeByTiled.height*20 +100));
////            menuItem->runAction(CCFadeIn::create(0.15));
////            if(menuItem->getParent() == NULL) {
////                building->map->addChild(menuItem,1000000);
////            }
////        }
////        i++;
////        
////        
////    }
//    
}

void UnfinishedState::doStart() {
    //ADD图标
//    CCMenuItem* menuItem = dynamic_cast<CCMenuItem*>(itemDictionary->objectForKey(BuildTransition));
////    CCLog("uid:%d",menuItem->getTag());
//    menuItem->setPosition(ccp(building->getPosition().x,building->getPosition().y+building->contentSizeByTiled.height*20 +100));
//    menuItem->runAction(CCFadeTo::create(0.15,255));
//    building->map->addChild(menuItem,1000000);
    CCArray* tags = getAllInput();
    CCObject* obj;
    MyMenuItem* menuItem;
    //    CCInteger* i;
    MyPriorityMenu* menu = MyPriorityMenu::create(-502,NULL,NULL);
    building->displaySummary();
    CCARRAY_FOREACH(tags, obj) {
        menuItem = (MyMenuItem*)dynamic_cast<TransitionInfo*>(itemDictionary->objectForKey(((CCInteger*)obj)->getValue()))->getButton();
        if (menuItem->getTag() == BuildTransition) {
            menuItem->runAction(CCFadeTo::create(0.15,255));
        } else {
            menuItem->setOpacity(0);
            menuItem->setEnabled(false);
        }
        menu->addChild(menuItem);
    }
    menu->alignItemsHorizontallyWithPadding(25);
    menu->setTag(transitionMenuTag);
    menu->setPosition( ccp(0,building->y +60));
    building->addChild(menu);
}


void UnfinishedState::doEnd() {
    //TODO
    building->removeChildByTag(transitionMenuTag,true);
   

    MyState::dismissAllTransition();
}

//UnfinishedStateCreator* UnfinishedStateCreator::create() {
//    UnfinishedStateCreator* creator = new UnfinishedStateCreator();
//    creator->autorelease();
//    return creator;
//}
//
//CCObject* UnfinishedStateCreator::init() {
//    UnfinishedState* unfinishedState = UnfinishedState::create(UnfinishedStateTag, CCMenuItemSpriteName, maxLevel);
//    return unfinishedState;
//}
