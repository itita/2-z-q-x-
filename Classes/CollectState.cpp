//
//  CollectState.cpp
//  ww3
//
//  Created by xiao tang on 12-10-13.
//
//
#include "CollectState.h"
#include "MyMenuItem.h"
#include "Mathlib.h"
#include "DefineSet.h"
#include "GXFadeOut.h"
#include "GXRemoveFromParentsAction.h"
#include "SimpleAudioEngine.h"
#include "MyGameInfo.h"
#include "MyMap.h"
#include "MyPriorityMenu.h"
#include "MyHttpConnection.h"
#include "MyUtil.h"

#define canCollectTag 1500

CollectState* CollectState::create(int _stateId, cocos2d::CCSprite *item,float output,float maxCapacity,int tag) {
    CollectState* pState = new CollectState(output,maxCapacity);
    pState->stateId = _stateId;
    pState->autorelease();
    pState->item = item;
//    item->setTarget(pState, menu_selector(CollectState::CallBack));
    pState->item->retain();
    pState->checkCollect();
    pState->resourceTag = tag;
    //    bdItem->setAnchorPoint(ccp(0.5,0.45));
    return pState;
}

bool CollectState::checkCollect() {
    if (getCapacity()/getMaxCapacity() > 0.2) {
        isCollect = true;
        return true;
    } else {
        isCollect =false;
        return false;
    }
}

void CollectState::dismissAllTransition() {
    if(!isCollect) {
        building->removeChildByTag(canCollectTag,true);
    }
    //zhuyeMenu本质上是会野指针化，但是不持有来减少内存，多测测看流程有没有问题吧。
    zhuyeMenu = NULL;
    MyState::dismissAllTransition();
//    CCMenu* transitionMenu = (CCMenu*)building->getChildByTag(transitionMenuTag);
//    if (transitionMenu == NULL) {
//        return;
//    }
//    CCArray* tags = transitionMenu->getChildren();
//    CCObject* obj;
//    CCMenuItem* menuitem;
//    if (isCollect){
//        CCARRAY_FOREACH(tags, obj) {
//            //TODO
//            menuitem = dynamic_cast<CCMenuItem*>(obj);
//            if (isCollect && menuitem->getTag() == CollectTransition){
//                continue;
//            }
//            menuitem->setEnabled(false);
//            menuitem->runAction(CCFadeOut::create(0.15));
//        }
//    } else {
//        CCARRAY_FOREACH(tags, obj) {
//            //TODO
//            menuitem = dynamic_cast<CCMenuItem*>(obj);
//            if (menuitem->getParent() != NULL ) {
//                menuitem->stopAllActions();
//                menuitem->runAction(CCFadeOut::create(0.15));
//                menuitem->setEnabled(false);
//            }
//        }
//        transitionMenu->setTag(-1);
//        transitionMenu->runAction(CCSequence::create(CCDelayTime::create(0.15),GXRemoveFromParentsAction::create(),NULL));
//    }
    
    
//    CCArray* tags = getAllInput();
//    CCObject* obj;
//    CCMenuItem* menuitem;
//    CCARRAY_FOREACH(tags, obj) {
//        menuitem = dynamic_cast<CCMenuItem*>(itemDictionary->objectForKey(((CCInteger*)obj)->getValue()));
//        if (menuitem->getParent() != NULL) {
//            if (isCollect && menuitem->getTag() == CollectTransition){
//                continue;
//            }
//            menuitem->setEnabled(false);
//            menuitem->runAction(CCSequence::create(CCFadeOut::create(0.15),GXRemoveFromParentsAction::create(),NULL));
//        }
//    }
}

void CollectState::doState() {
    setCapacity(getCapacity(),1);
    dt++;
//    Mathlib::bound(getCapacity()+outputPsecond, getMaxCapacity(), 0);
    if (!isCollect && checkCollect()) {
        doStart();
//        MyMenuItem* menuitem = dynamic_cast<MyMenuItem*>(this->getTransition(CollectTransition));
//        menuitem->setPosition(ccp(building->getPosition().x,building->getPosition().y+building->contentSizeByTiled.height*20 +100));
//        menuitem->stopAllActions();
//        menuitem->runAction(CCFadeTo::create(0.15,255));
//        if(menuitem->getParent() == NULL) {
//            building->map->addChild(menuitem,999999);
//        }
    } else if( (int)getCapacity()==1) {
        if (zhuyeMenu) {
            ((MyMenuItem*)zhuyeMenu->getChildByTag(CollectTransition))->setDisabled(true);
            //        CCLog("%f",getCapacity());
        }
    }
}


float CollectState::getBaseMaxCapacity() {
    return baseMaxCapacity->getValue();
}

float CollectState::getBaseOutputPsecond() {
    return baseOutputPsecond->getValue();
}

void CollectState::setMaxCapacity(float maxCapacity) {
    this->maxCapacity->setValue(maxCapacity);
}

void CollectState::setOutputPsecond(float outputPsecond) {
    this->outputPsecond->setValue(outputPsecond);
}

void CollectState::showAllTransition() {
    
    building->getParent()->getParent()->removeChildByTag(zhuyeMenuTag,true);
    
    CCLayer* layer = CCLayer::create();
    layer->setTag(zhuyeMenuTag);
    
    CCArray* tags = getAllInput();
    CCObject* obj;
    //    CCMenuItem* menuItem;
    //    CCInteger* i;
    //    MyPriorityMenu* menu = MyPriorityMenu::create(-502,NULL,NULL);
    building->displaySummary();
    zhuyeMenu = MyPriorityMenu::create(-502,NULL,NULL);
    //    building->displaySummary();
    int i = 0;
    float posi = tags->count()*120;
    CCARRAY_FOREACH(tags, obj) {
        //        menuItem = dynamic_cast<TransitionInfo*>(itemDictionary->objectForKey(((CCInteger*)obj)->getValue()))->getButton();
        //
        //        menuItem->runAction(CCFadeTo::create(0.15,255));
        //        menu->addChild(menuItem);
        
        MyMenuItem* item2 = (MyMenuItem*)dynamic_cast<TransitionInfo*>(itemDictionary->objectForKey(((CCInteger*)obj)->getValue()))->getButton();
        if (item2->getTag() == CollectTransition) {
            if (getCapacity()>1) {
                item2->setDisabled(true);
            } else {
                item2->setDisabled(false);
            }
        }
        zhuyeMenu->addChild(item2);
        item2->setScale(1.3);
        item2->setOpacity(100-i*20);
        //        item2->setOpacity(0);
        item2->setPosition(ccp(-posi/2+i*120+60,-30));
        item2->runAction(CCSpawn::create(CCSequence::create(CCDelayTime::create(0.07+0.05*(tags->count()-i)),CCFadeTo::create(0.23,255),NULL),CCSequence::create( CCDelayTime::create(0.05*(tags->count()-i)),CCEaseElasticOut::create(CCMoveBy::create(0.3,ccp(0,100)),1.3),NULL),NULL));
        i++;
    }
    zhuyeMenu->setPosition(ccp(winSize.width/2-10,0));
    
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
    
    
    layer->addChild(zhuyeMenu);
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
//        menu->isSwallow = false;
//        building->displaySummary();
//        int i = 0;
//        CCARRAY_FOREACH(tags, obj) {
//            menuItem = dynamic_cast<TransitionInfo*>(itemDictionary->objectForKey(((CCInteger*)obj)->getValue()))->getButton();
//            if (menuItem->getTag() == CollectTransition) {
//                if (getCapacity()>1) {
//                    ((MyMenuItem*)menuItem)->setDisabled(true);
//                } else {
//                    ((MyMenuItem*)menuItem)->setDisabled(false);
//                }
//            }
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
//        return;
//        CCArray* tags = exist->getChildren();
//        CCObject* obj;
//        CCMenuItem* menuItem;
//        //    CCInteger* i;
//        building->displaySummary();
//        int i = 0;
//        CCARRAY_FOREACH(tags, obj) {
//            menuItem = dynamic_cast<CCMenuItem*>(obj);
//            if (menuItem->getTag() == CollectTransition) {
//                if (getCapacity()>1) {
//                    ((MyMenuItem*)menuItem)->setDisabled(true);
//                } else {
//                    ((MyMenuItem*)menuItem)->setDisabled(false);
//                }
//            } else {
//                menuItem->runAction(CCFadeTo::create(0.15,255));
//                menuItem->setEnabled(true);
//            }
//            i++;
//        }
//    }
    
//    CCArray* tags = getAllInput();
//    CCObject* obj;
//    CCMenuItem* menuitem;
//    //    CCInteger* i;
//    building->displaySummary();
//    int i = 0;
//    CCARRAY_FOREACH(tags, obj) {
//        menuitem = dynamic_cast<CCMenuItem*>(itemDictionary->objectForKey(((CCInteger*)obj)->getValue()));
//        if (menuitem ->getTag() == CollectTransition) {
//            if (getCapacity()>1) {
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
}

void CollectState::init(MyBuilding* building) {
    MyState::init(building);
    this->building = building;
}

void CollectState::clickCallBack() {
    if (!building->getActive()&&isCollect) {
        //播放收集声音
        CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sfx_collect.mp3");
        MyHttpConnection::getInstance()->sendCollectResource(building->pid);
        doCollect();
        return;
    }
    MyState::clickCallBack();
}

void CollectState::doCollect() {
    
    
    CCLayer* floatLayer = MyGameInfo::getInstance()->changeResourceAndFloatText(resourceTag, getCapacity(), ccp(building->getPosition().x,building->getPosition().y+30*building->contentSizeByTiled.height+40));
    CCLayer* expFloatLayer = MyGameInfo::getInstance()->changeResourceAndFloatText(expTag, getCapacity(), ccp(building->getPosition().x,building->getPosition().y+30*building->contentSizeByTiled.height+100));
//    CCAssert(floatLayer != NULL, "XXXXXXXX");
    building->map->addChild(floatLayer,1000001);
    building->map->addChild(expFloatLayer,1000001);
//    CCLog("capacity:%f",getCapacity());
//    CCLog("dt:%d",dt);
//    CCLog("pid:%d,capacity:%f,dt:%d",building->pid,capacity,dt);
    capacity->setValue(0);
    dt = 0;
    isCollect = false;
    
//    building->setActive(false);
//    ((MyMap*)building->map)->dispearArrowTip();
    if (building->getActive()) {
        ((MyMap*)building->map)->cancelAllBuilding();
    } else {
        dismissAllTransition();
    }
    
    return;
}

void CollectState::doCollectPlaysfx() {
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sfx_collect.mp3");
    MyHttpConnection::getInstance()->sendCollectResource(building->pid);
    doCollect();
}

void CollectState::doCollectCheckCapacity() {
    if (capacity->getValue()<=20) {
        return;
    }
    doCollect();
}

void CollectState::doStart() {
    if (checkCollect()) {
//        CCSprite* canCollect = CCSprite::createWithSpriteFrameName("collectTip1.png");
//        canCollect->setPosition(ccp(0,building->y));
//        canCollect->setTag(canCollectTag);
//        CCSprite* resourceIcon = MyUtil::getInstance()->getResourceIcon(resourceTag);
//        resourceIcon->setPosition(ccp(canCollect->getContentSize().width/2,canCollect->getContentSize().height/2+10));
//        resourceIcon->setScale(Mathlib::min(40/resourceIcon->getContentSize().width,40/resourceIcon->getContentSize().height));
//        canCollect->addChild(resourceIcon);
        
        
//        CCSprite* canCollect = CCSprite::createWithSpriteFrameName("collectTip2.png");
//        canCollect->setPosition(ccp(0,building->y));
//        canCollect->setTag(canCollectTag);
//        CCSprite* resourceIcon = MyUtil::getInstance()->getResourceIcon(resourceTag);
//        resourceIcon->setPosition(ccp(canCollect->getContentSize().width/2,canCollect->getContentSize().height/2+5));
//        resourceIcon->setScale(Mathlib::min(40/resourceIcon->getContentSize().width,40/resourceIcon->getContentSize().height));
//        canCollect->addChild(resourceIcon);
        
//        CCSprite* canCollect = CCSprite::createWithSpriteFrameName("collectTip6.png");
//        canCollect->setPosition(ccp(0,building->y));
//        canCollect->setTag(canCollectTag);
//        canCollect->setScale(1);
//        CCSprite* resourceIcon = MyUtil::getInstance()->getResourceIcon(resourceTag);
//        resourceIcon->setPosition(ccp(canCollect->getContentSize().width/2,canCollect->getContentSize().height/2+7));
//        resourceIcon->setScale((36/resourceIcon->getContentSize().width+36/resourceIcon->getContentSize().height)/2);
//        canCollect->addChild(resourceIcon);
        
        CCSprite* canCollect = NULL;
        if (resourceTag == oilTag) {
            canCollect = CCSprite::createWithSpriteFrameName("collectTip7.png");
//            canCollect->setPosition(ccp(0,building->y));
//            canCollect->setTag(canCollectTag);
        } else if(resourceTag == ironTag) {
            canCollect = CCSprite::createWithSpriteFrameName("collectTip8.png");
        }
        canCollect->setPosition(ccp(0,building->y));
        canCollect->setTag(canCollectTag);
        canCollect->runAction(CCRepeatForever::create(static_cast<CCSequence*>(CCSequence::create(CCEaseInOut::create( CCMoveBy::create(0.5, ccp(0,5)), 2),CCEaseInOut::create(CCMoveBy::create(0.5, ccp(0,-5)),2),NULL))));
        building->addChild(canCollect);
//        CCArray* tags = getAllInput();
//        CCObject* obj;
//        CCMenuItem* menuItem;
//        //    CCInteger* i;
//        MyPriorityMenu* menu = MyPriorityMenu::create(-502,false,NULL,NULL);
//        menu->isSwallow = false;
//        int i = 0;
//        CCARRAY_FOREACH(tags, obj) {
//            menuItem = dynamic_cast<TransitionInfo*>(itemDictionary->objectForKey(((CCInteger*)obj)->getValue()))->getButton();
//            if (menuItem->getTag() == CollectTransition) {
//                if (getCapacity()>1) {
//                    ((MyMenuItem*)menuItem)->setDisabled(true);
//                } else {
//                    ((MyMenuItem*)menuItem)->setDisabled(false);
//                }
//                menuItem->runAction(CCFadeTo::create(0.15,255));
//            } else {
//                menuItem->setVisible(false);
//            }
//            
//            menu->addChild(menuItem);
//            i++;
//            
//        }
//        menu->alignItemsHorizontallyWithPadding(25);
//        menu->setTag(transitionMenuTag);
//        menu->setPosition( ccp(0,building->y +60));
//        building->addChild(menu);
        
//        MyMenuItem* menuitem = dynamic_cast<MyMenuItem*>(this->getTransition(CollectTransition));
//        menuitem->setPosition(ccp(building->getPosition().x,building->getPosition().y+building->contentSizeByTiled.height*20 +100));
//        menuitem->stopAllActions();
//        menuitem->runAction(CCFadeTo::create(0.15,255));
//        building->map->addChild(menuitem,999999);
    }
}

void CollectState::setCapacity(float _capacity,long dt) {
//    CCLog("原始是:%f,采集了%f,获得了%f的资源",_capacity,outputPsecond->getValue()*dt,_capacity+outputPsecond->getValue()*dt);
    capacity->setValue(Mathlib::bound(_capacity+outputPsecond->getValue()*dt, getMaxCapacity(), 0));
}

float CollectState::getMaxCapacity() {
    return maxCapacity->getValue();
}

//CollectStateCreator* CollectStateCreator::create() {
//    CollectStateCreator* creator = new CollectStateCreator();
//    creator->autorelease();
//    return creator;
//}
//
//CCObject* CollectStateCreator::init() {
//    CCSprite* grayBy = CCSprite::create(CCMenuItemSpriteName);
//    grayBy->setColor(ccGRAY);
//    MyTiledMenuItemSprite* byItem = MyTiledMenuItemSprite::create(CCSprite::create(CCMenuItemSpriteName), grayBy);
//    byItem->setAnchorPoint(itemAnchor);
//    
////    CollectState* workState = CollectState::create(WorkStateTag, byItem,outputPsecond,maxCapacity,resourceTag);
////    doFill(workState);
//    return NULL;
//}
