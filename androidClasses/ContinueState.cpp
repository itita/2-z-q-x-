//
//  ContinueState.cpp
//  ww4
//
//  Created by xiao tang on 13-4-5.
//
//

#include "ContinueState.h"
#include "Mathlib.h"
#include "DefineSet.h"
#include "MyMenuItem.h"
#include "BuildingHeader.h"
#include "SimpleAudioEngine.h"
#include "MyUtil.h"
#include "MyPriorityMenu.h"
#include "GXShieldTouchMenuItem.h"
#include "MyHttpConnection.h"

ContinueState* ContinueState::create(int _stateId, CCSprite* item,int _combineBuildingTag) {
    ContinueState* pState = new ContinueState();
    pState->stateId = _stateId;
    pState->autorelease();
    pState->combineBuildingTag =_combineBuildingTag;
    
    pState->item = item;
    //    item->setTarget(pState, menu_selector(NormalState::CallBack));
    pState->item->retain();
    //    bdItem->setAnchorPoint(ccp(0.5,0.45));
    
    return pState;
}

void ContinueState::init(MyBuilding *building) {
    MyState::init(building);
    this->building = building;
    
}

void ContinueState::clickCallBack(){
    checkContinue();
    MyState::clickCallBack();
}

void ContinueState::doState() {
    
    
}

void ContinueState::setItem(cocos2d::CCSprite *_item) {
    CC_SAFE_RELEASE(item);
    this->item = _item;
    _item->retain();
}

void ContinueState::toCombineCallBack(CCMenuItem *pSender) {
    pSender->setEnabled(false);
    MyMap* map = ((MyMap*)building->map);
    if (MyUtil::getInstance()->getLevelByExperience(MyGameInfo::getInstance()->getExperience()) < 15) {
        map->getParent()->addChild(MyUtil::getInstance()->getCommonTipDialog(CCString::create("『等级15级』以上，我们才能使用『组合』技术！"),map->getParent(), menu_selector(StartScene::cancelTipDialog),0));
        return;
    }
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
    if (lrLoc>0 && udLoc>0) {
        CCLayer* chooseDirLayer = CCLayer::create();
        CCSprite* back = MyUtil::getInstance()->getNormalBox(500,350);
        back->setPosition(ccp(winSize.width/2,winSize.height/2));
        
        CCMenuItemSprite* cancelItem =CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("uiDialogCancelButton.png"), CCSprite::createWithSpriteFrameName("uiDialogCancelButtonP.png"),map->getParent(),menu_selector(StartScene::cancelTipDialog));
        cancelItem->setAnchorPoint(ccp(1,1));
        cancelItem->setPosition(ccp(250+winSize.width/2,175+winSize.height/2));
        
        CCSprite* Light1gray = CCSprite::createWithSpriteFrameName("creatorLight.png");
        Light1gray->setScale(0.88);
        Light1gray->setColor(ccGRAY);
        Light1gray->setOpacity(153);
        
    
        
        CCSprite* lrWallgray = CCSprite::createWithSpriteFrameName("combineWall5x1.png");
        lrWallgray->addChild(Light1gray,-1);
        lrWallgray->setAnchorPoint(ccp(0.5,0.5));
        Light1gray->setPosition(ccp(lrWallgray->getContentSize().width/2,lrWallgray->getContentSize().height/2));
        
        
        CCSprite* Light1 = CCSprite::createWithSpriteFrameName("creatorLight.png");
        Light1->setScale(0.88);
        Light1->setOpacity(153);
        
        
        CCSprite* lrWall = CCSprite::createWithSpriteFrameName("combineWall5x1.png");
        lrWall->addChild(Light1,-1);
        Light1->setPosition(ccp(lrWall->getContentSize().width/2,lrWall->getContentSize().height/2));
        
        
        CCMenuItemSprite* lrItem = CCMenuItemSprite::create(lrWallgray,lrWall,this,menu_selector(ContinueState::toLrCombine));
        lrItem->setPosition(ccp(winSize.width/2-110,winSize.height/2-20));
        
        CCSprite* Light3gray = CCSprite::createWithSpriteFrameName("creatorLight.png");
        Light3gray->setScale(0.88);
        Light3gray->setColor(ccGRAY);
        Light3gray->setOpacity(153);
        
        
        
        CCSprite* lrWall2gray = CCSprite::createWithSpriteFrameName("combineWall1x5.png");
        lrWall2gray->addChild(Light3gray,-1);
        lrWall2gray->setAnchorPoint(ccp(0.5,0.5));
        Light3gray->setPosition(ccp(lrWall2gray->getContentSize().width/2,lrWall2gray->getContentSize().height/2));
        
        
        CCSprite* Light4 = CCSprite::createWithSpriteFrameName("creatorLight.png");
        Light4->setScale(0.88);
        Light4->setOpacity(153);
        
        
        CCSprite* lrWall2 = CCSprite::createWithSpriteFrameName("combineWall1x5.png");
        lrWall2->addChild(Light4,-1);
        Light4->setPosition(ccp(lrWall2->getContentSize().width/2,lrWall2->getContentSize().height/2));
        
        
        CCMenuItemSprite* lrItem2 = CCMenuItemSprite::create(lrWall2gray,lrWall2,this,menu_selector(ContinueState::toUdCombine));
        lrItem2->setPosition(ccp(winSize.width/2+110,winSize.height/2-20));
        
        GXShieldTouchMenuItem* shield = GXShieldTouchMenuItem::create();
        shield->setContentSize(CCSizeMake(500, 350));
        shield->setAnchorPoint(ccp(0.5,0.5));
        shield->setPosition(ccp(winSize.width/2,winSize.height/2));
        MyPriorityMenu* menu  = MyPriorityMenu::create(-511,cancelItem,lrItem,lrItem2,shield,NULL);
        menu->setPosition(ccp(0,0));
        
        CCLabelTTF* label = CCLabelTTF::create("请选择『强化城墙』的组合方向","Arial",30);
        label->setPosition(ccp(winSize.width/2,winSize.height/2+100));
        label->setColor(ccc3(230, 207, 185));
        
        
        
        chooseDirLayer->addChild(back);
        chooseDirLayer->addChild(menu);
        chooseDirLayer->addChild(label);
        chooseDirLayer->setTag(NoResourceTag);
        map->getParent()->addChild(chooseDirLayer);
        return;
    }
    combine();
    
}

void ContinueState::showAllTransition() {
    
    building->getParent()->getParent()->removeChildByTag(zhuyeMenuTag,true);
    CCLayer* layer = CCLayer::create();
    layer->setTag(zhuyeMenuTag);
    CCArray* tags = getAllInput();
    CCObject* obj;
    building->displaySummary();
    MyPriorityMenu* zhuyemenu = MyPriorityMenu::create(-502,NULL,NULL);
    int i = 0;
    float posi = tags->count()*120;
    CCARRAY_FOREACH(tags, obj) {
        
        MyMenuItem* item2 = (MyMenuItem*)dynamic_cast<TransitionInfo*>(itemDictionary->objectForKey(((CCInteger*)obj)->getValue()))->getButton();
        if (item2 ->getTag() == CombineTransition) {
            if (lrLoc > 0 || udLoc > 0) {
                ((MyMenuItem*)item2)->setDisabled(true);
            } else {
                ((MyMenuItem*)item2)->setDisabled(false);
            }
        }
        zhuyemenu->addChild(item2);
        item2->setScale(1.3);
        item2->setOpacity(100-i*20);
        item2->setPosition(ccp(-posi/2+i*120+60,-30));
        item2->runAction(CCSpawn::create(CCSequence::create(CCDelayTime::create(0.07+0.05*(tags->count()-i)),CCFadeTo::create(0.23,255),NULL),CCSequence::create( CCDelayTime::create(0.05*(tags->count()-i)),CCEaseElasticOut::create(CCMoveBy::create(0.3,ccp(0,100)),1.3),NULL),NULL));
        i++;
    }
    
    zhuyemenu->setPosition(ccp(winSize.width/2-10,0));
    
    char str[100] = {0};
    sprintf(str, "%s (等级 %d)",building->getBuildingName(),building->getLevel());
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
    
//    if (building->getChildByTag(transitionMenuTag) != NULL) {
//        CCArray* tags = building->getChildByTag(transitionMenuTag)->getChildren();
//        CCObject* obj;
//        CCMenuItem* menuItem;
//        building->displaySummary();
//        int i = 0;
//        CCARRAY_FOREACH(tags, obj) {
//            menuItem = dynamic_cast<CCMenuItem*>(obj);
//            if (menuItem ->getTag() == CombineTransition) {
//                if (lrLoc > 0 || udLoc > 0) {
//                    ((MyMenuItem*)menuItem)->setDisabled(true);
//                } else {
//                    ((MyMenuItem*)menuItem)->setDisabled(false);
//                }
//            } else {
//                menuItem->setEnabled(true);
//            }
//            i++;
//        }
//        return;
//    }
//    CCArray* tags = getAllInput();
//    CCObject* obj;
//    CCMenuItem* menuItem;
//    //    CCInteger* i;
//    MyPriorityMenu* menu = MyPriorityMenu::create(-502,NULL,NULL);
//    building->displaySummary();
//    int i = 0;
//    CCARRAY_FOREACH(tags, obj) {
//        menuItem = dynamic_cast<TransitionInfo*>(itemDictionary->objectForKey(((CCInteger*)obj)->getValue()))->getButton();
//        if (menuItem ->getTag() == CombineTransition) {
//            if (lrLoc > 0 || udLoc > 0) {
//                ((MyMenuItem*)menuItem)->setDisabled(true);
//            } else {
//                ((MyMenuItem*)menuItem)->setDisabled(false);
//            }
//        } else {
//            menuItem->setEnabled(true);
//        }
//        menuItem->runAction(CCFadeTo::create(0.15,255));
//        menu->addChild(menuItem);
//        i++;
//        
//    }
//    menu->alignItemsHorizontallyWithPadding(25);
//    menu->setTag(transitionMenuTag);
//    menu->setPosition( ccp(0,building->y +60));
//    building->addChild(menu);
//    
    
//    CCArray* tags = getAllInput();
//    CCObject* obj;
//    CCMenuItem* menuitem;
//    //    CCInteger* i;
//    building->displaySummary();
//    int i = 0;
//    CCARRAY_FOREACH(tags, obj) {
//        menuitem = dynamic_cast<CCMenuItem*>(itemDictionary->objectForKey(((CCInteger*)obj)->getValue()));
//        if (menuitem ->getTag() == CombineTransition) {
//            if (lrLoc > 0 || udLoc > 0) {
//                ((MyMenuItem*)menuitem)->setDisabled(true);
//            } else {
//                ((MyMenuItem*)menuitem)->setDisabled(false);
//            }
//        } else {
//            menuitem->setEnabled(true);
//        }
//        CCAssert(menuitem != NULL, "估计没加对应按钮就加流程了");
//        menuitem->setPosition( ccp(building->getPosition().x-(tags->count()-1)*50+i*100,building->getPosition().y+building->contentSizeByTiled.height*20 +100));
//        menuitem->stopAllActions();
//        menuitem->runAction(CCFadeTo::create(0.15,255));
//        
//        if (menuitem->getParent() == NULL) {
//            menuitem->setScale(1);
//            building->map->addChild(menuitem,999999);
//        }
//        i++;
//        
//    }
//    
}

void ContinueState::checkContinue() {
    MyMap* map = dynamic_cast<MyMap*>(building->getParent());
    CCArray* items = map->getItems();
    CCObject* obj;
    MyBuilding* lr[9] = {NULL};
    MyBuilding* ud[9] = {NULL};
    lrLoc = -1;
    udLoc = -1;
    for (int i=0; i<4; i++) {
        destroyBuilding[i] = 0;
    }
    CCARRAY_FOREACH(items, obj) {
        MyBuilding* item = (MyBuilding*)obj;
        if(item->getTag() == building->getTag()) {
            CCPoint itemPos = Mathlib::roundPoint(map->transMapToTiled(item->getPosition()));
            CCPoint thisPos = Mathlib::roundPoint(map->transMapToTiled(building->getPosition()));
            if (itemPos.x - thisPos.x == -4 && itemPos.y == thisPos.y) {
                lr[0] = item;
            } else if (itemPos.x - thisPos.x == -3 && itemPos.y == thisPos.y) {
                lr[1] = item;
            } else if (itemPos.x - thisPos.x == -2 && itemPos.y == thisPos.y) {
                lr[2] = item;
            } else if (itemPos.x - thisPos.x == -1 && itemPos.y == thisPos.y) {
                lr[3] = item;
            } else if (itemPos.x - thisPos.x == 1 && itemPos.y == thisPos.y) {
                lr[5] = item;
            } else if (itemPos.x - thisPos.x == 2 && itemPos.y == thisPos.y) {
                lr[6] = item;
            } else if (itemPos.x - thisPos.x == 3 && itemPos.y == thisPos.y) {
                lr[7] = item;
            } else if (itemPos.x - thisPos.x == 4 && itemPos.y == thisPos.y) {
                lr[8] = item;
            } else if (itemPos.y - thisPos.y == -4 && itemPos.x == thisPos.x) {
                ud[0] = item;
            } else if (itemPos.y - thisPos.y == -3 && itemPos.x == thisPos.x) {
                ud[1] = item;
            } else if (itemPos.y - thisPos.y == -2 && itemPos.x == thisPos.x) {
                ud[2] = item;
            } else if (itemPos.y - thisPos.y == -1 && itemPos.x == thisPos.x) {
                ud[3] = item;
            } else if (itemPos.y - thisPos.y == 1 && itemPos.x == thisPos.x) {
                ud[5] = item;
            } else if (itemPos.y - thisPos.y == 2 && itemPos.x == thisPos.x) {
                ud[6] = item;
            } else if (itemPos.y - thisPos.y == 3 && itemPos.x == thisPos.x) {
                ud[7] = item;
            } else if (itemPos.y - thisPos.y == 4 && itemPos.x == thisPos.x) {
                ud[8] = item;
            }
        }
    }
    bool lFlag = true;
    bool rFlag = true;
    int num = 0;
    for (int i=1; i<5; i++) {
        if (lFlag) {
            if (lr[4-i] == NULL) {
                lFlag = false;
            }else {
                destroyBuilding[num] = lr[4-i];
                num++;
            }
        }
        if (rFlag) {
            if (lr[4+i] == NULL) {
                rFlag = false;
            } else {
                destroyBuilding[num] = lr[4+i];
                num++;
            }
        }
        if (!lFlag & !rFlag ) {
            break;
        }
        if (num == 4) {
            if (lFlag) {
                lrLoc = 6-i;
            } else if(rFlag) {
                lrLoc = 2+i;
            }
            break;
        }
    }
    lFlag = true;
    rFlag = true;
    num = 0;
    for (int i=1; i<5; i++) {
        if (lFlag) {
            if (ud[4-i] == NULL) {
                lFlag = false;
            }else {
                destroyBuilding2[num] = ud[4-i];
                num++;
            }
        }
        if (rFlag) {
            if (ud[4+i] == NULL) {
                rFlag = false;
            } else {
                destroyBuilding2[num] = ud[4+i];
                num++;
            }
        }
        if (!lFlag & !rFlag ) {
            break;
        }
        if (num == 4) {
            if (lFlag) {
                udLoc = 6-i;
            } else if(rFlag) {
                udLoc = 2+i;
            }
            break;
        }
    }
}

void ContinueState::combine() {
    MyMap* map = ((MyMap*)building->map);
    MyBuilding* newBuilding = NULL;
    
    CCPoint oriP = building->map->transMapToTiled(building->getPosition());
    float posX = 0;
    float posY = 0;
    int averageLevel = building->getLevel();
    int dir = 0;
    if (lrLoc > 0) {
        newBuilding = CombineWall::createNormal(combineWall5X1Tag,building->map->getParent(),1);
//        MyGameFactory::createByTag(combineWall5X1Tag,building->map->getParent(),1);
        posX = oriP.x-4+lrLoc;
        posY = oriP.y;
        for (int i = 0; i<4; i++) {
            if (destroyBuilding[i] == map->moveTemp)  {
                map->moveTemp = NULL;
            }
            averageLevel += destroyBuilding[i]->getLevel();
            destroyBuilding[i]->removeFromParentAndCleanup(true);
        }
        
    } else if (udLoc>0) {
        newBuilding = CombineWall::createNormal(combineWall1X5Tag,building->map->getParent(),1);
        posX = oriP.x;
        posY = oriP.y-4+udLoc;
        for (int i = 0; i<4; i++) {
            if (destroyBuilding2[i] == map->moveTemp)  {
                map->moveTemp = NULL;
            }
            averageLevel += destroyBuilding2[i]->getLevel();
            destroyBuilding2[i]->removeFromParentAndCleanup(true);
        }
        dir = 1;
    }
    
    
    if(((int)newBuilding->contentSizeByTiled.width)%2 ==0) {
        posX+=0.5;
    }
    if(((int)newBuilding->contentSizeByTiled.height)%2 ==0) {
        posY+=0.5;
    }
    newBuilding->setPositionByTiled(ccp(posX,posY));
    newBuilding->setLevel(averageLevel/5);
    building->map->addChild(newBuilding);
    //    if (lrLoc > 0) {
    //
    //    } else
    newBuilding->activate();
    map->moveTemp = newBuilding;
    newBuilding->cacheLoc = newBuilding->getPosition();
    newBuilding->pid = MyGameInfo::getInstance()->maxId+1;
//    if (newBuilding->pid - MyGameInfo::getInstance()->maxId != 1) {
//        CCLog("估计有错");
//    }
    MyGameInfo::getInstance()->maxId++;
//    CCLog("maxId:%d",MyGameInfo::getInstance()->maxId);
    building->removeFromParentAndCleanup(true);
    MyHttpConnection::getInstance()->sendContinueBuildingById(building->pid, dir,newBuilding->pid );
}

void ContinueState::toLrCombine(CCMenuItem* item) {
    item->setEnabled(false);
    udLoc = -1;
    this->combine();
    item->getParent()->getParent()->removeFromParentAndCleanup(true);
}

void ContinueState::toUdCombine(CCMenuItem* item){
    item->setEnabled(false);
    lrLoc = -1;
    this->combine();
    item->getParent()->getParent()->removeFromParentAndCleanup(true);
}