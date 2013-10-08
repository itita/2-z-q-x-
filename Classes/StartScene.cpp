//
//  StartScene.cpp
//  WW2
//
//  Created by DingYu Fu on 12-8-26.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "cocos2d.h"
#include "StartScene.h"
#include "MyMap.h"
#include "MyMenu.h"
#include "MyTiledMenuItemSprite.h"
#include "MyBuilding.h"
#include "MyState.h"
#include "MyUnit.h"
#include "BattleScene.h"
#include "GXJsonUtil.h"
#include "NormalState.h"
#include "MyGameFactory.h"
#include "MyJsonUtil.h"
#include "PulsarNative.h"
#include "MyHttpConnection.h"
#include "MyContinueTiledMenuItemSprite.h"
#include <string>
#include "GXUtil.h"
#include "MyGameInfo.h"
#include "MyUtil.h"
//#include "GXScrollView.h"
#include "MyPriorityMenu.h"
#include "CoordinateTrans.h"
#include "DefineSet.h"
#include "MyBuildingCard.h"
#include "Mathlib.h"
#include "ReadyToBuild.h"
#include "LoadingScene.h"
#include "SimpleAudioEngine.h"
#include "MyProgressBar.h"
#include "MyLevelBar.h"
#include "CollectState.h"
#include "GXShieldTouchMenuItem.h"
#include "MyUnitCard.h"
#include "GXAnimateFX.h"
#include "pthread.h"
#include "GXMsg.h"
#include "GXRemoveFromParentsAction.h"
#include "GXRadioMenu.h"
#include "MyContinueTiledSprite.h"
#include "TransitonScene.h"
#include "cocos-ext.h"
#include "UnionTrigger.h"
#include "StoreTrigger.h"
#include "GXMessage.h"
#include "MyMessageManage.h"
#include "UnionJoinScroll.h"
#include "MyMemberBean.h"
#include "PushTrigger.h"
#include "GXInteger.h"
#include "GXChatHandler.h"
#include "MyShopCard.h"
#include "BuildingHeader.h"
#include "UpdateArmyMessage.h"
#include "GarbageCollectionNormalState.h"
#include "GXFadeOutAndRemoveWhenStop.h"
#include "QuestManager.h"
#include "MyBaseQuest.h"
#include "GXScaleTo.h"
#include "GXRepeatForever.h"
#include "NewbieQuest1ToBattle.h"
#include "BattleQuest.h"
#include "GXAntiCrack.h"
#include "AttackerInfoBean.h"
#include "GXScrollViewNoScissor.h"
#include "GXScissorNode.h"
#include "GXScrollBar.h"
#include "UpdateBuildingMessag.h"
#include "MainMenuScroll2.h"


#define charScorllTag 1001
#define transScorllTag 1002
#define recordContentLayerTag 1003
#define recordBackSpriteTag 1004
#define displayBuduiLayerTag 1005
#define zhengBingLayerTag 1006
#define buduiMenuTag 1007
#define buduiScrollTag 1008
#define zhengbingCardMenuTag 1009
#define zhengbingLingquMenuTag 1010
#define zhengbingkuangTag 1011
#define zhengbingInfobackTag 1012
#define zhengbingInfobackSummaryLabelTag 1026
#define zhengbingTipTag 1013
#define lingquLayerTag 1014
#define bling1Tag 1015
#define bling2Tag 1016
#define armyInfoLayerTag 1017
#define armyInfoInfoLayerTag 1018
#define armyInfoStrenthenDivideLayerTag 1019
#define armyInfoStrenthenDivideLayerMenuTag 1020
#define armyInfoInfoLayerMenuTag 1022
#define armyInfoInfoStrenthenInfoLayerTag 1023
#define armyInfoInfoStrenthenBlackTag 1024
#define armyInfoRadioMenuTag 1025
#define armyInfoInfoStrenthenInfoLayerLevelAtlasTag 1027
#define armyInfoInfoStrenthenInfoLayerCostAtlasTag 1028
#define armyInfoInfoStrenthenInfoLayerExpBarUPTag 1029
#define armyInfoInfoStrenthenInfoLayerExpBarDownTag 1030
#define armyInfoUnlockLayerTag 1032
#define buduiLockTag 1033
//#define huodongMenuTag 1034
#define bugeiButtonTag 1035
#define bugeiButtonMultipleTag 1036
#define controlSecondMenuTag 1037
#define showToggleTag 1038
#define joinUnionTipLayerTag 1045
#define sureKickMemberLayerTag 1046
#define avatarUnionLayerTag 1047
#define totalFliterTag 1048
#define unionFliterTag 1049
#define privateFliterTag 1050
#define sendIconTag 1051
#define charmenuTag 1052
#define vipToggleTag 1053
#define displayShopLayerTag 1054
#define displayChargeLayerTag 1055
#define displayShopInfoLayerTag 1055
#define optionMenuTag 1056
#define optionAchievementButtonTag 1057
#define optionButton1Tag 1058
#define mubeiButtonTag 1059
#define mubeiButtonCountTag 1060
#define appearQuestTag 1061
#define cpuWarQuestTag 1062
#define cpuWarMapTag 1063
#define recordNewIcon 1064
#define oneKeyUpdateNextButtonTag 1065
#define oneKeyUpdatePreButtonTag 1066
#define oneKeyUpdateLevelLabelTag 1067
#define oneKeyUpdateCountLabelTag 1068
#define onekeyUpdateCostLabelTag 1069
#define oneKeyUpdateCostIconLabelTag 1070
#define conversionOilTag 1071
#define conversionIronTag 1072
#define conversionResourceCountLabel1 1073
#define conversionResourceCountLabel2 1074
#define conversionDiamondCountLabel 1075
#define createBuildingScrollTag 1076
#define createArmyScrollTag 1077
#define battleMenuTag 1078


using namespace cocos2d;

bool StartScene::init() {
    this->initUI();
    return true;
}

StartScene::~StartScene() {
    if (unionTrigger) {
        MyMessageManage::getInstance()->unRegisterTrigger(unionTrigger);
    }
    if (storeTrigger) {
        MyMessageManage::getInstance()->unRegisterTrigger(storeTrigger);
    }
    CC_SAFE_RELEASE_NULL(unionTrigger);
    CC_SAFE_RELEASE_NULL(storeTrigger);
    MyHttpConnection::getInstance()->clearGameDataListArray();
    releaseResource();
    CCLog("StartScene released");
}

StartScene* StartScene::create(cocos2d::CCArray *buildings) {
    StartScene *pRet = new StartScene();
    //    CCTextureCache::sharedTextureCache()->dumpCachedTextureInfo();
    //    pRet->loadResource();
    if (pRet && pRet->init(buildings))
    {
        
        pRet->autorelease();
        pRet->isClickExit = false;
        return pRet;
    }
    else
    {
        CC_SAFE_DELETE(pRet);
        return NULL;
    }
}

bool StartScene::init(cocos2d::CCArray *buildings) {
    
    //    MyGameInfo::getInstance()->experience = 10000000000000;
    //    CCLog("EXP:%lld",MyGameInfo::getInstance()->experience);
    
    MyMap* map = MyMap::create("ditu002.tmx");
    map->setOriPosition(ccp(0,0));
    
    CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect("sfx_levelup.mp3");
    
    CCSprite* backl = CCSprite::createWithSpriteFrameName("backgroundlr.png");
    CCSprite* backr = CCSprite::createWithSpriteFrameName("backgroundlr.png");
    CCSprite* backu = CCSprite::createWithSpriteFrameName("backgroundud.png");
    CCSprite* backd = CCSprite::createWithSpriteFrameName("backgroundud.png");
    
    backl->setAnchorPoint(ccp(0,1));
    backl->setScale(1800/backl->getContentSize().width);
    backl->setPosition(ccp(0,map->getContentSize().height));
    map->addChild(backl,-1);
    
    backu->setAnchorPoint(ccp(1,1));
    backu->setScale(1800/backu->getContentSize().width);
    backu->setPosition(ccp(map->getContentSize().width,map->getContentSize().height));
    map->addChild(backu,-1);
    
    backd->setAnchorPoint(ccp(0,0));
    backd->setPosition(ccp(0,0));
    backd->setScale(1800/backd->getContentSize().width);
    map->addChild(backd,-1);
    
    backr->setAnchorPoint(ccp(1,0));
    backr->setPosition(ccp(map->getContentSize().width,0));
    backr->setScale(1800/backr->getContentSize().width);
    map->addChild(backr,-1);
    
    //    CCSprite* total=CCSprite::create("totalmaprd.jpg");
    //    total->setPosition(ccp(map->getContentSize().width,0));
    //    total->setAnchorPoint(ccp(1,0));
    //    total->setScale(2);
    
    
    this->addChild(map);
    //    map->addChild(total,-1);
    map->setTag(MainMapTag);
    
    
    //    MyBuilding* zhihuisuo = MyGameFactory::createZhihuisuo(this,1);
    //    zhihuisuo->setPositionByTiled(ccp(30.5,30.5));
    //    zhihuisuo->changeStateById(WorkStateTag);
    //    map->addChild(zhihuisuo);
    //
    //    MyBuilding* oil = MyGameFactory::createYouTian(this,1);
    //    oil->setPositionByTiled(ccp(34,34));
    //    oil->changeStateById(WorkStateTag);
    //    ((CollectState*)oil->fsm->getState(WorkStateTag))->setCapacity(200, 0);
    //    map->addChild(oil);
    //
    //    MyBuilding* iron = MyGameFactory::createKuangchang(this,1);
    //    iron->setPositionByTiled(ccp(34,30));
    //    iron->changeStateById(WorkStateTag);
    //    ((CollectState*)iron->fsm->getState(WorkStateTag))->setCapacity(200, 0);
    //    map->addChild(iron);
    //
    //
    //
    //    MyBuilding* diaobao = MyGameFactory::createDefenderInCreate(diaobaoTag, this,1);
    //    diaobao->setPositionByTiled(ccp(30.5,33.5));
    //    diaobao->changeStateById(WorkStateTag);
    //    map->addChild(diaobao);
    map->centerView();
    //    this->addChild(MyUtil::getInstance()->getWaitLayer());
    
    CCObject* obj;
    CCArray* antiArray =CCArray::create();
    int ghostCount =0;
    CCARRAY_FOREACH(buildings, obj) {
        BuildingBean* bean = dynamic_cast<BuildingBean*>(obj);
        MyBuilding* building = MyGameFactory::createBuildingByBean(bean, this);
        
#if game_version == hard_version
        
        //修复 半格问题
        
        //        if(((int)building->contentSizeByTiled.width)%2 == 1) {
        //            CCLog("%f,%f",building->getPositionByTiled().x,building->getPositionByTiled().y);
        //            building->setPositionByTiled(ccp((int)(building->getPositionByTiled().x+0.02),(int)(building->getPositionByTiled().y+0.02)));
        //        } else {
        //            building->setPositionByTiled(ccp((int)(building->getPositionByTiled().x+0.02)+0.5,(int)(building->getPositionByTiled().y+0.02)+0.5));
        //        }
#endif
        
        if (building->getTag() == ghostTag) {
            //            map->addChild(building);
            ghostCount++;
        }
        //        else if ( building->getTag() == zhihuisuoTag || !map->collisionDetection(building)) {
        //            map->addChild(building);
        //        }
        //        else {
        //            CCLog("die jian zu shi bu yun xu de");
        map->addChild(building);
        //        }
        
        if (building->getTag() == dapaoTag) {
            antiArray->addObject(building);
        }
        MyContinueTiledSprite* item = dynamic_cast<MyContinueTiledSprite*>(((MyState*)building->fsm->getCurrentState())->getItem());
        if (item != NULL && building->getParent() != NULL) {
            item->updateLoc(1);
        }
    }
    this->setUserData(CCInteger::create(ghostCount));
    MyBuilding* zhihuisuo =  (MyBuilding*)map->getChildByTag(zhihuisuoTag);
    //    zhihuisuo->setPositionByTiled(ccp(zhihuisuo->getPositionByTiled().x+0.5,zhihuisuo->getPositionByTiled().y+0.5));
    if (zhihuisuo != NULL) {
        char str[20] = {0};
        CCARRAY_FOREACH(antiArray, obj) {
            MyBuilding* building = dynamic_cast<MyBuilding*>(obj);
            float angle = Mathlib::getAngle(zhihuisuo->getPositionByTiled(), building->getPositionByTiled());
            int dir = (((int)(angle*180/3.141592654+22.5)+360)%360)/45 ;
            NormalState* state =  dynamic_cast<NormalState*>(building->fsm->getState(WorkStateTag));
            if (dir == 0) {
                sprintf(str, "antiTankld.png");
            } else if (dir == 1) {
                sprintf(str, "antiTankd.png");
            } else if (dir == 2) {
                sprintf(str, "antiTankrd.png");
            } else if (dir == 3) {
                sprintf(str, "antiTankr.png");
            } else if (dir == 4) {
                sprintf(str, "antiTankru.png");
            } else if (dir == 5) {
                sprintf(str, "antiTanku.png");
            } else if (dir == 6) {
                sprintf(str, "antiTanklu.png");
            } else if (dir == 7) {
                sprintf(str, "antiTankl.png");
            }
            
            CCSprite* byItem = CCSprite::createWithSpriteFrameName(str);
            byItem->setAnchorPoint(ccp(0.5,0.5));
            CCSprite* zhendi = CCSprite::createWithSpriteFrameName("position.png");
            zhendi->setPosition(ccp(byItem->getContentSize().width/2,byItem->getContentSize().height/2));
            state->setItem(byItem);
            byItem->addChild(zhendi,-1);
            if (building->fsm->getCurrentState()->getId() == WorkStateTag) {
                building->setNormalImage(byItem);
            }
        }
    } else {
        //        CCDirector::sharedDirector()->end();
        //#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
        //        exit(0);
        //#endif
    }
    
#if game_version == hard_version
    
    
    //修复 重复卡牌
    //    int index[6] = {0};
    //    CCObject* obj2;
    //    CCArray* array = MyGameInfo::getInstance()->creatorArray;
    //    CCArray* deleteArray = CCArray::create();
    //    CCARRAY_FOREACH(array,obj2) {
    //        CreatorInfoBean* bean = (CreatorInfoBean*)obj2;
    //
    //        if (bean->getScriptName()->compare("garade.j") ==0 ) {
    //            index[0]+=1;
    //            if (bean->getLevel() <2  && index[0]>1) {
    //                deleteArray->addObject(bean);
    //            }
    //        } else if (bean->getScriptName()->compare("M5Stuart.j") ==0 ) {
    //            index[1]+=1;
    //            if (bean->getLevel() <2  && index[1]>1) {
    //                deleteArray->addObject(bean);
    //            }
    //        } else if (bean->getScriptName()->compare("WillysMB.j") ==0 ) {
    //            index[2]+=1;
    //            if (bean->getLevel() < 2  && index[2]>1) {
    //                deleteArray->addObject(bean);
    //            }
    //        } else if(bean->getScriptName()->compare("M3HalfTrack.j") ==0 ) {
    //            index[3]+=1;
    //            if (bean->getLevel() < 2 && index[3]>1) {
    //                deleteArray->addObject(bean);
    //            }
    //        } else if (bean->getScriptName()->compare("M4Sherman.j") ==0 ) {
    //            index[4]+=1;
    //            if (bean->getLevel() < 2  && index[4]>1) {
    //                deleteArray->addObject(bean);
    //            }
    //        } else if (bean->getScriptName()->compare("Calliope.j") ==0 ) {
    //            index[5]+=1;
    //            if (bean->getLevel() < 2  && index[5]>1) {
    //                deleteArray->addObject(bean);
    //            }
    //        }
    //    }
    //
    //    CCARRAY_FOREACH(deleteArray,obj2) {
    //        CreatorInfoBean* bean = (CreatorInfoBean*)obj2;
    //        array->removeObject(bean);
    //    }
    
    
#endif
    //    map->setOriPosition(ccp(-map->getContentSize().width/4,-map->getContentSize().height/4));
    //    map->setContentMapSize(CCSizeMake(map->getContentSize().width/2,map->getContentSize().height/2));
    //    MyGameFactory::createBuildingbyJsonScriptFile("by.j");
    
    
    //    MyBuilding* songshu = MyGameFactory::createOrnaments(songshuTag, this);
    //    MyBuilding* stone0 = MyGameFactory::createOrnaments(stoneBaseTag, this);
    //    MyBuilding* stone1 = MyGameFactory::createOrnaments(stoneBaseTag+1, this);
    //    MyBuilding* stone2 = MyGameFactory::createOrnaments(stoneBaseTag+2, this);
    //
    //    songshu->setPositionByTiled(ccp(1,1));
    //    stone0->setPositionByTiled(ccp(3,5));
    //    stone1->setPositionByTiled(ccp(5,3));
    //    stone2->setPositionByTiled(ccp(7,7));
    
    //    map->addChild(songshu);
    //    map->addChild(stone0);
    //    map->addChild(stone1);
    //    map->addChild(stone2);
    //    for(int i=0;i<10;i++) {
    //        MyGameInfo::getInstance()->creatorArray->addObject(CCString::create("tank.j"));
    //    }
    
    
    initControl();
    //    MyBuilding* cw = MyGameFactory::createCombineWall(this,1);
    //
    //    float posX= 33;
    //    float posY= 33;
    //    if(((int)cw->contentSizeByTiled.width)%2 ==0) {
    //        posX = 33.5;
    //    }
    //    if(((int)cw->contentSizeByTiled.height)%2 ==0) {
    //        posY = 33.5;
    //    }
    //    cw->setPositionByTiled(ccp(posX,posY));
    //    map->addChild(cw);
    //
    //    for (int i =0; i <16; i++) {
    //        MyGameInfo::getInstance()->creatorArray->addObject(CCString::create("tank.j"));
    //    }
    //    MyGameInfo::getInstance()->creatorArray->addObject(CreatorInfoBean::create(CCString::create("M3HalfTrack.j")));
    //    MyGameInfo::getInstance()->creatorArray->addObject(CreatorInfoBean::create(CCString::create("WillysMB.j")));
    
    //    CreatorInfoBean* bean = CreatorInfoBean::create(CCString::create("Calliope.j"));
    //    bean->setExperience(800999);
    //    MyGameInfo::getInstance()->creatorArray->addObject(bean);
    //    MyGameInfo::getInstance()->creatorArray->addObject(CreatorInfoBean::create(CCString::create("Panzergrenadier.j")));
    //    MyGameInfo::getInstance()->creatorArray->addObject(CreatorInfoBean::create(CCString::create("Infanterie.j")));
    //    MyGameInfo::getInstance()->creatorArray->addObject(CreatorInfoBean::create(ThorCardId));
    //    CreatorInfoBean* bean = CreatorInfoBean::create(tornadoCardId);
    //    bean->setExperience(999999);
    //    MyGameInfo::getInstance()->creatorArray->addObject(bean);
    return true;
}



void StartScene::initUI() {
    
    //    initSound();
    MyMap* map = MyMap::create("ditu002.tmx");
    map->setOriPosition(ccp(0,0));
    map->setTag(MainMapTag);
    //    map->setOriPosition(ccp(-map->getContentSize().width/4,-map->getContentSize().height/4));
    //    map->setContentMapSize(CCSizeMake(map->getContentSize().width/2,map->getContentSize().height/2));
    this->addChild(map);
    
    CCSprite* backl = CCSprite::createWithSpriteFrameName("backgroundlr.png");
    CCSprite* backr = CCSprite::createWithSpriteFrameName("backgroundlr.png");
    CCSprite* backu = CCSprite::createWithSpriteFrameName("backgroundud.png");
    CCSprite* backd = CCSprite::createWithSpriteFrameName("backgroundud.png");
    
    backl->setAnchorPoint(ccp(0,1));
    backl->setScale(1800/backl->getContentSize().width);
    backl->setPosition(ccp(0,map->getContentSize().height));
    map->addChild(backl,-1);
    
    backu->setAnchorPoint(ccp(1,1));
    backu->setScale(1800/backu->getContentSize().width);
    backu->setPosition(ccp(map->getContentSize().width,map->getContentSize().height));
    map->addChild(backu,-1);
    
    backd->setAnchorPoint(ccp(0,0));
    backd->setPosition(ccp(0,0));
    backd->setScale(1800/backd->getContentSize().width);
    map->addChild(backd,-1);
    
    backr->setAnchorPoint(ccp(1,0));
    backr->setPosition(ccp(map->getContentSize().width,0));
    backr->setScale(1800/backr->getContentSize().width);
    map->addChild(backr,-1);
    
#if game_version == soft_version
    MyBuilding* zhihuisuo = MyGameFactory::createZhihuisuo(this,1);
    zhihuisuo->setPositionByTiled(ccp(29,29));
    zhihuisuo->changeStateById(WorkStateTag);
    zhihuisuo->setRoad(CCSprite::createWithSpriteFrameName("road5x5.png"));
    map->addChild(zhihuisuo);
    
    MyBuilding* oil = MyGameFactory::createYouTian(this,1);
    oil->setPositionByTiled(ccp(33.5,33.5));
    oil->setRoad(CCSprite::createWithSpriteFrameName("road4x4.png"));
    oil->changeStateById(WorkStateTag);
    ((CollectState*)oil->fsm->getState(WorkStateTag))->setCapacity(200, 0);
    map->addChild(oil);
    
    MyBuilding* iron = MyGameFactory::createKuangchang(this,1);
    iron->setPositionByTiled(ccp(33.5,29.5));
    iron->changeStateById(WorkStateTag);
    iron->setRoad(CCSprite::createWithSpriteFrameName("road4x4.png"));
    ((CollectState*)iron->fsm->getState(WorkStateTag))->setCapacity(200, 0);
    map->addChild(iron);
    
    
    
    MyBuilding* diaobao = MyGameFactory::createDefenderInCreate(diaobaoTag, this,1);
    diaobao->setPositionByTiled(ccp(30,33));
    diaobao->setRoad(CCSprite::createWithSpriteFrameName("road3x3.png"));
    diaobao->changeStateById(WorkStateTag);
    map->addChild(diaobao);
#endif
#if game_version == hard_version
    MyBuilding* zhihuisuo = ZhiHuiSuo::createNormal(this,1);
    zhihuisuo->setPositionByTiled(ccp(28.5,28.5));
    zhihuisuo->changeStateById(WorkStateTag);
    map->addChild(zhihuisuo);
    
    MyBuilding* oil = YouTian::createNormal(this,1,200,0);
    oil->setPositionByTiled(ccp(32,32));
    oil->changeStateById(WorkStateTag);
    map->addChild(oil);
    
    MyBuilding* iron = KuangChang::createNormal(this,1,200,0);
    iron->setPositionByTiled(ccp(32,29));
    iron->changeStateById(WorkStateTag);
    map->addChild(iron);
    
    
    
    MyBuilding* diaobao = DiaoBao::createNormal(this,1);
    diaobao->setPositionByTiled(ccp(29.5,31.5));
    diaobao->changeStateById(WorkStateTag);
    map->addChild(diaobao);
#endif
    
    
    for (int i = 0; i<30; i++) {
        MyBuilding* stone0 = Ornament::createNormal(stoneBaseTag, this);
        stone0->setPositionByTiled(ccp(15,15));
        map->addChild(stone0,99999);
        bool flag = true;
        while (flag) {
            float posX = arc4random()%60;
            float posY = arc4random()%60;
            if(((int)stone0->contentSizeByTiled.width)%2 ==0) {
                posX+=0.5;
            }
            if(((int)stone0->contentSizeByTiled.height)%2 ==0) {
                posY+=0.5;
            }
            stone0->setPositionByTiled(ccp(posX,posY));
            if(((posX > 2 && posX < 25) || posX >35) && ((posY > 2 && posY < 25) || posY >35) && !map->collisionDetection(stone0)) {
                flag = false;
            };
        }
        //        stone0->setPositionByTiled(arc4random()%60)
    }
    
    for (int i = 0; i<10; i++) {
        MyBuilding* stone0 = Ornament::createNormal(stoneBaseTag+1, this);
        stone0->setPositionByTiled(ccp(15,15));
        map->addChild(stone0,99999);
        bool flag = true;
        while (flag) {
            float posX = arc4random()%60;
            float posY = arc4random()%60;
            if(((int)stone0->contentSizeByTiled.width)%2 ==0) {
                posX+=0.5;
            }
            if(((int)stone0->contentSizeByTiled.height)%2 ==0) {
                posY+=0.5;
            }
            stone0->setPositionByTiled(ccp(posX,posY));
            if(((posX > 3 && posX < 25) || posX >35) && ((posY > 3 && posY < 25) || posY >35) && !map->collisionDetection(stone0)) {
                flag = false;
            };
        }
        //        stone0->setPositionByTiled(arc4random()%60)
    }
    
    for (int i = 0; i<8; i++) {
        MyBuilding* stone0 = Ornament::createNormal(stoneBaseTag+2, this);
        stone0->setPositionByTiled(ccp(15,15));
        map->addChild(stone0,99999);
        bool flag = true;
        while (flag) {
            float posX = arc4random()%60;
            float posY = arc4random()%60;
            if(((int)stone0->contentSizeByTiled.width)%2 ==0) {
                posX+=0.5;
            }
            if(((int)stone0->contentSizeByTiled.height)%2 ==0) {
                posY+=0.5;
            }
            stone0->setPositionByTiled(ccp(posX,posY));
            if(((posX > 4 && posX < 20) || posX >40) && ((posY > 4 && posY < 20) || posY >30) &&!map->collisionDetection(stone0)) {
                flag = false;
            };
        }
        //        stone0->setPositionByTiled(arc4random()%60)
    }
    
    for (int i = 0; i<10; i++) {
        MyBuilding* stone0 = Ornament::createNormal(songshuTag, this);
        stone0->setPositionByTiled(ccp(15,15));
        map->addChild(stone0,99999);
        bool flag = true;
        while (flag) {
            float posX = arc4random()%60;
            float posY = arc4random()%60;
            if(((int)stone0->contentSizeByTiled.width)%2 ==0) {
                posX+=0.5;
            }
            if(((int)stone0->contentSizeByTiled.height)%2 ==0) {
                posY+=0.5;
            }
            stone0->setPositionByTiled(ccp(posX,posY));
            if(((posX > 4 && posX < 25) || posX >35) && ((posY > 4 && posY < 25) || posY >35) && !map->collisionDetection(stone0)) {
                flag = false;
            };
        }
        //        stone0->setPositionByTiled(arc4random()%60)
    }
    
    MyBuilding* destroy = LianLuoZhongXin::createDestroy(this,1);
    destroy->setPositionByTiled(ccp(15,15));
    map->addChild(destroy,99999);
    bool flag = true;
    while (flag) {
        float posX = arc4random()%60;
        float posY = arc4random()%60;
        if(((int)destroy->contentSizeByTiled.width)%2 ==0) {
            posX+=0.5;
        }
        if(((int)destroy->contentSizeByTiled.height)%2 ==0) {
            posY+=0.5;
        }
        destroy->setPositionByTiled(ccp(posX,posY));
        if((((posX > 20 && posX < 23) || (posX >37 && posX <40)) && ((posY > 20 && posY < 25) || (posY >35 && posY<40))) && !map->collisionDetection(destroy)) {
            flag = false;
        };
    }
    
    map->centerView();
    initControl();
    
    
}

void StartScene::initControl() {
    
    //刷新orderId频率
    this->schedule(schedule_selector(StartScene::getServerOrderId),180);
    //    this->schedule(schedule_selector(StartScene::sendTestMsg),0.5);
    
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("bgm_startScene.mp3",true);
    
    unionTrigger = UnionTrigger::create(this);
    unionTrigger->retain();
    MyMessageManage::getInstance()->registerTrigger(unionTrigger);
    
    storeTrigger = StoreTrigger::create(this);
    storeTrigger->retain();
    MyMessageManage::getInstance()->registerTrigger(storeTrigger);
    
    CCLayer* uiLayer = CCLayer::create();
    uiLayer->setTag(UILayerTag);
    CCSprite* resourseBar = CCSprite::createWithSpriteFrameName("resourseBar.png");
    resourseBar->setScale(542/resourseBar->getContentSize().width);
    resourseBar->setAnchorPoint(ccp(0.5,1));
    resourseBar->setPosition(ccp(winSize.width/2+5,winSize.height));
    resourseBar->setTag(resourceBarTag);
    
    
    CCSprite* avatar =CCSprite::createWithSpriteFrameName("avatar.png");
    //    uiLayer->addChild(avatar);
    avatar->setAnchorPoint(ccp(0,1));
    avatar->setPosition(ccp(0,winSize.height));
    avatar->setTag(avatarTag);
    CCSprite* avatarSprite = CCSprite::createWithSpriteFrameName("avatar0.png");
    avatarSprite->setAnchorPoint(ccp(0,1));
    avatarSprite->setPosition(ccp(0,avatar->getContentSize().height));
    avatar->addChild(avatarSprite);
    
    
    
    
    
    CCSprite* createSprite = CCSprite::createWithSpriteFrameName("createIcon.png");
    createSprite->setColor(ccGRAY);
    CCMenuItemSprite* createButton = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("createIcon.png"), createSprite,this,menu_selector(StartScene::toCreateCallBack));
    createButton->setPosition(70,200);
    CCSprite* createBack = CCSprite::createWithSpriteFrameName("mainMenuBack.png");
    createBack->setPosition(ccp(createButton->getContentSize().width/2,createButton->getContentSize().height/2));
    createButton->addChild(createBack,-1);
    createButton->setScale(1.1);
    
    CCSprite* recordSprite1 = CCSprite::createWithSpriteFrameName("recordIcon.png");
    recordSprite1->setColor(ccGRAY);
    CCMenuItemSprite* recordButton1 = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("recordIcon.png"), recordSprite1);
    
    CCSprite* recordSprite2 = CCSprite::createWithSpriteFrameName("recordIcon.png");
    recordSprite2->setColor(ccGRAY);
    CCMenuItemSprite* recordButton2 = CCMenuItemSprite::create(recordSprite2,CCSprite::createWithSpriteFrameName("recordIcon.png"));
    
    CCMenuItemToggle* recordtButton = CCMenuItemToggle::createWithTarget(this,menu_selector(StartScene::toggleRecorder),recordButton1,recordButton2,NULL);
    recordtButton->setTag(recordToggleTag);
    recordtButton->setPosition(70,450);
    CCSprite* recordBack = CCSprite::createWithSpriteFrameName("mainMenuBack.png");
    recordBack->setPosition(ccp(recordtButton->getContentSize().width/2,recordtButton->getContentSize().height/2));
    recordtButton->addChild(recordBack,-1);
    recordtButton->setScale(1.1);
    
    CCSprite* gyShow = CCSprite::createWithSpriteFrameName("diplomacyIcon.png");
    gyShow->setColor(ccGRAY);
    CCMenuItemSprite* showButton1 = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("diplomacyIcon.png"), gyShow);
    
    CCSprite* gyShow2 = CCSprite::createWithSpriteFrameName("diplomacyIcon.png");
    gyShow2->setColor(ccGRAY);
    CCMenuItemSprite* showButton2 = CCMenuItemSprite::create(gyShow2,CCSprite::createWithSpriteFrameName("diplomacyIcon.png"));
    
    CCMenuItemToggle* showButton = CCMenuItemToggle::createWithTarget(this,menu_selector(StartScene::displayConmunication),showButton1,showButton2,NULL);
    showButton->setTag(showToggleTag);
    CCSprite* showBack = CCSprite::createWithSpriteFrameName("mainMenuBack.png");
    showBack->setPosition(ccp(showButton->getContentSize().width/2,showButton->getContentSize().height/2));
    showButton->addChild(showBack,-1);
    showButton->setScale(1.1);
    
    CCSprite* gyArmy = CCSprite::createWithSpriteFrameName("armyIcon.png");
    gyArmy->setColor(ccGRAY);
    CCMenuItemSprite* armyButton = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("armyIcon.png"), gyArmy,this,menu_selector(StartScene::toArmyCallBackSimple));
    CCSprite* armyBack = CCSprite::createWithSpriteFrameName("mainMenuBack.png");
    armyBack->setPosition(ccp(armyButton->getContentSize().width/2,armyButton->getContentSize().height/2));
    armyButton->addChild(armyBack,-1);
    armyButton->setScale(1.1);
    
    CCSprite* gyVip = CCSprite::createWithSpriteFrameName("vipIcon.png");
    gyVip->setColor(ccGRAY);
    CCMenuItemSprite* vipButton1 = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("vipIcon.png"), gyVip);
    
    CCSprite* gyVip2 = CCSprite::createWithSpriteFrameName("vipIcon.png");
    gyVip2->setColor(ccGRAY);
    CCMenuItemSprite* vipButton2 = CCMenuItemSprite::create(gyVip2,CCSprite::createWithSpriteFrameName("vipIcon.png"));
    
    CCMenuItemToggle* vipButton = CCMenuItemToggle::createWithTarget(this,menu_selector(StartScene::displayVip),vipButton1,vipButton2,NULL);
    vipButton->setTag(vipToggleTag);
    
    CCSprite* vipBack = CCSprite::createWithSpriteFrameName("mainMenuBack.png");
    vipBack->setPosition(ccp(vipButton->getContentSize().width/2,vipButton->getContentSize().height/2));
    vipButton->addChild(vipBack,-1);
    vipButton->setScale(1.1);
    //    vipButton->setPosition(75,575);
    
    CCSprite* grayAchievementButton = CCSprite::createWithSpriteFrameName("achievementIcon.png");
    grayAchievementButton->setColor(ccGRAY);
    CCMenuItemSprite* achievementButton = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("achievementIcon.png"),grayAchievementButton);
    CCSprite* achievementBack = CCSprite::createWithSpriteFrameName("mainMenuBack.png");
    achievementBack->setPosition(ccp(achievementButton->getContentSize().width/2,achievementButton->getContentSize().height/2));
    achievementButton->addChild(achievementBack,-1);
    achievementButton->setScale(1.1);
    
    CCSprite* grayLogoutButton = CCSprite::createWithSpriteFrameName("logoutIcon.png");
    grayLogoutButton->setColor(ccGRAY);
    CCMenuItemSprite* logoutButton = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("logoutIcon.png"),grayLogoutButton,this,menu_selector(StartScene::doLogout));
    CCSprite* logoutBack = CCSprite::createWithSpriteFrameName("mainMenuBack.png");
    logoutBack->setPosition(ccp(logoutButton->getContentSize().width/2,logoutButton->getContentSize().height/2));
    logoutButton->addChild(logoutBack,-1);
    logoutButton->setScale(1.1);
    
    CCSprite* grayCampaignButton = CCSprite::createWithSpriteFrameName("campaignIcon.png");
    grayCampaignButton->setColor(ccGRAY);
    CCMenuItemSprite* campaignButton = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("campaignIcon.png"),grayCampaignButton);
    CCSprite* campaignBack = CCSprite::createWithSpriteFrameName("mainMenuBack.png");
    campaignBack->setPosition(ccp(campaignButton->getContentSize().width/2,campaignButton->getContentSize().height/2));
    campaignButton->addChild(campaignBack,-1);
    campaignButton->setScale(1.1);
    //    CCSprite* mainMenuTipUp = CCSprite::createWithSpriteFrameName("mainMenuTip.png");
    //    mainMenuTipUp->setPosition(ccp(winSize.width-67.5,520));
    //    mainMenuTipUp->setOpacity(0);
    
    MainMenuScroll2* scollView = MainMenuScroll2::create(-500);
    //    scollView->menuUpTip = mainMenuTipUp;
    scollView->setContentSize(CCSizeMake(150,320));
    scollView->setOriPosition(ccp(winSize.width-135,190));
    scollView->setTag(controlMenuTag);
    
    //    battleButton->setPosition(oriPoint.x,oriPoint.y+this->getChildrenCount()*space);
    //    scollView->addChild(battleButton);
    logoutButton->setPosition(70,60);
    scollView->addChild(createButton);
    achievementButton->setPosition(70,60+110);
    scollView->addChild(armyButton);
    campaignButton->setPosition(70,60+220);
    scollView->addChild(recordtButton);
    showButton->setPosition(70,60+330);
    scollView->addChild(vipButton);
    recordtButton->setPosition(70,60+440);
    scollView->addChild(showButton);
    
    scollView->addChild(logoutButton);
    createButton->setPosition(70,60+550);
    scollView->addChild(achievementButton);
    vipButton->setPosition(70,60+660);
    scollView->addChild(campaignButton);
    armyButton->setPosition(70,60+770);
    scollView->setMapSize(CCSizeMake(125,880));
    scollView->setPositionY(510-880);
    
    //    CCSprite* menuLight = CCSprite::createWithSpriteFrameName("menuLight.png");
    //    menuLight->setScaleY(winSize.height/menuLight->getContentSize().height);
    //    menuLight->setScaleX(1.5);
    //    menuLight->setAnchorPoint(ccp(1,0.5));
    //    menuLight->setPosition(ccp(winSize.width,winSize.height/2));
    //    menuLight->setOpacity(0);
    //    menuLight->setColor(ccc3(20,20,20));
    //    uiLayer->addChild(menuLight);
    //    MyPriorityMenu* battlem = MyPriorityMenu::create(-500,vipButton,armyButton,showButton,recordtButton,createButton,battleButton,NULL);
    //
    //    battlem->alignItemsVerticallyWithPadding(10);
    //    battlem->setPosition(ccp(winSize.width-75,winSize.height/2));
    //    battlem->setTag(controlMenuTag);
    
    //    int huodongCount = 0;
    //    MyPriorityMenu* huodongMenu = MyPriorityMenu::create(-500,NULL);
    
    MyPriorityMenu* questMenu = MyPriorityMenu::create(-502,NULL);
    questMenu->setPosition(ccp(0,0));
    questMenu->setTag(questMenuTag);
    
    CCArray* questArray = QuestManager::getInstance()->questList;
    CCObject* questObj;
    int i = 1;
    CCARRAY_FOREACH(questArray,questObj) {
        MyBaseQuest* quest = (MyBaseQuest*)questObj;
        //        if (quest->getCompleteStatus() == questFinishedTag) {
        //            addDisplayQuest(questMenu, quest,true);
        ////            questItem->setPosition(ccp(100,570-i*100));
        //        } else {
        addDisplayQuest(questMenu,quest,true);
        //            questItem->setPosition(ccp(100,570-i*100));
        //        }
        i++;
    }
    
    //补给BUTTON
//    if(MyGameInfo::getInstance()->getRobMultiple() <= MyUtil::getInstance()->getLevelByExperience(MyGameInfo::getInstance()->getExperience())/10) {
//        
//    } else {
//        CCMenuItem*  bugeiButton = this->addBugeiButton();
//        //        bugeiButton->runAction(CCMoveBy::create(3,ccp(-150,0)));
//        CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sfx_bugeiLaugh.mp3");
//        this->addDisplayHuodong(questMenu,bugeiButton);
//        //        bugeiButton->setPosition(100,570-questMenu->getChildrenCount()*100);
//    }
//    //    int abc = MyGameInfo::getInstance()->robdeltaTime%1200000;
//    this->schedule(schedule_selector(StartScene::bugeiMultipleTimer),1800,kCCRepeatForever,1800-(MyGameInfo::getInstance()->robdeltaTime%1800000)/1000);
    
    //墓碑
    CCInteger* mubeiCount = ((CCInteger*)this->getUserData());
    if(mubeiCount != NULL && mubeiCount->getValue() > 0) {
        
        //        CCSprite* grayMubei = CCSprite::createWithSpriteFrameName("ghostButton.png");
        //        grayMubei->setColor(ccGRAY);
        //        CCMenuItemSprite* mubeiButton = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("ghostButton.png"),grayMubei,this,menu_selector(StartScene::toOneKeyArchieveGhost));
        //        mubeiButton->setPosition(ccp(0,130*huodongCount));
        //        mubeiButton->setTag(mubeiButtonTag);
        //
        //        CCSprite* mubeibling1_1 = CCSprite::create("armyprizeLight.png");
        //        mubeibling1_1->setPosition(ccp(mubeiButton->getContentSize().width/2,mubeiButton->getContentSize().height/2));
        //        mubeibling1_1->setScale(0.7);
        //        mubeibling1_1->runAction(CCRepeatForever::create(CCRotateBy::create(1000, 7200)));
        //        mubeiButton->addChild(mubeibling1_1,-1);
        //
        //        CCSprite* mubeibling1_2 = CCSprite::create("armyprizeLight.png");
        //        mubeibling1_2->setPosition(ccp(mubeiButton->getContentSize().width/2,mubeiButton->getContentSize().height/2));
        //        mubeibling1_2->runAction(CCRepeatForever::create(CCRotateBy::create(1000, -7200)));
        //        mubeibling1_2->setScale(0.5);
        //        mubeiButton->addChild(mubeibling1_2,-1);
        //
        //        char str[5] = {0};
        //        sprintf(str,"/%d",mubeiCount->getValue());
        //        CCLabelAtlas* mubeiCountLabel = CCLabelAtlas::create(str, "number6.png", 24, 36, '/');
        //        mubeiCountLabel->setUserData((void*) mubeiCount->getValue());
        //        mubeiCountLabel->setAnchorPoint(ccp(0.5,0.5));
        //        mubeiCountLabel->setScale(0.7);
        //        mubeiCountLabel->setTag(mubeiButtonCountTag);
        //        mubeiButton->addChild(mubeiCountLabel);
        //        mubeiCountLabel->setPosition(ccp(mubeiButton->getContentSize().width/2,-15.4));
        CCMenuItem* mubeiButton = displayMubeiInfo(mubeiCount->getValue());
        this->addDisplayHuodong(questMenu,mubeiButton);
        //        mubeiButton->setPosition(ccp(100,570-questMenu->getChildrenCount()*100));
        //        huodongMenu->addChild(displayMubeiInfo(mubeiCount->getValue(),huodongCount));
    }
    
    //    huodongMenu->setPosition(ccp(winSize.width-180,300));
    //    huodongMenu->setTag(huodongMenuTag);
    
    
    //    CCLabelTTF* nickName = CCLabelTTF::create(string.c_str(),"Arial", 54);
    CCLabelTTF* nickName = MyUtil::getInstance()->getVipColorLabel(MyGameInfo::getInstance()->getNickName(),18,MyGameInfo::getInstance()->getVipExperience());
    nickName->setAnchorPoint(ccp(0.5,1));
#if(CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    nickName->setPosition(ccp(139,84));
#endif
#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    nickName->setPosition(ccp(139,87));
#endif
    nickName->setTag(nicknameLabelTag);
    
    
    
    CCSprite* level = CCSprite::createWithSpriteFrameName("levelIcon.png");
    level->setScale(24/level->getContentSize().width);
    level->setPosition(ccp(112,46));
    
    
    
    MyLevelBar* levelBar = MyGameInfo::getInstance()->getLevelBar();
    
    //    levelBar->setContentSize(transWindowToGLInRetina(CCSizeMake(42, 4)));
    levelBar->setPosition(ccp(88,30));
    
    avatar->addChild(nickName);
    avatar->addChild(level,2);
    //    if(levelBar->getParent() != NULL) {
    //        levelBar->getParent()->getParent()->getParent()->release();
    //    }
    avatar->addChild(levelBar,1);
    
    
    
    CCLabelAtlas* oilLabel = MyGameInfo::getInstance()->getOilAtlas();
    oilLabel->setPosition(ccp(27,6));
    oilLabel->setAnchorPoint(ccp(0,0));
    oilLabel->setScale(0.52);
    oilLabel->removeFromParentAndCleanup(true);
    resourseBar->addChild(oilLabel);
    
    CCLabelAtlas* ironLabel = MyGameInfo::getInstance()->getIronAtlas();
    ironLabel->setPosition(ccp(130,6));
    ironLabel->setAnchorPoint(ccp(0,0));
    ironLabel->setScale(0.52);
    ironLabel->removeFromParentAndCleanup(true);
    resourseBar->addChild(ironLabel);
    
    CCLabelAtlas* gloryLabel = MyGameInfo::getInstance()->getGloryAtlas();
    gloryLabel->setPosition(ccp(234,6));
    gloryLabel->setAnchorPoint(ccp(0,0));
    gloryLabel->setScale(0.52);
    gloryLabel->removeFromParentAndCleanup(true);
    resourseBar->addChild(gloryLabel);
    
    CCLabelAtlas* diamondLabel = MyGameInfo::getInstance()->getDiamondAtlas();
    diamondLabel->setPosition(ccp(338,6));
    diamondLabel->setAnchorPoint(ccp(0,0));
    diamondLabel->setScale(0.52);
    diamondLabel->setColor(ccc3(255,224,57));
    diamondLabel->removeFromParentAndCleanup(true);
    resourseBar->addChild(diamondLabel);
    
    CCSprite* grayUiChargeButton = CCSprite::createWithSpriteFrameName("uiChargeButton.png");
    grayUiChargeButton->setColor(ccGRAY);
    CCMenuItemSprite* uiChargeButton = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("uiChargeButton.png"),grayUiChargeButton,this,menu_selector(StartScene::toDisplayCharge));
    uiChargeButton->setPosition(ccp(430,13));
    uiChargeButton->setScale(0.8);
    //    uiChargeButton->setContentSize(CCSizeMake(75,75));
    
    MyPriorityMenu* chargeMenu = MyPriorityMenu::create(-510,uiChargeButton,NULL);
    chargeMenu->setPosition(ccp(0,0));
    resourseBar->addChild(chargeMenu);
    
    
    
    CCLayer* chardialog = CCLayer::create();
    
    CCSprite* charback = CCSprite::createWithSpriteFrameName("chardialog.jpg");
    charback->setContentSize(CCSizeMake(380, 640));
    charback->setPosition(ccp(0,0));
    charback->setAnchorPoint(ccp(0,0));
    charback->setScale(1.333333);
    
    
    
    
    chardialog->addChild(charback);
    CCSprite* popgy = CCSprite::createWithSpriteFrameName("charButton.png");
    popgy->setColor(ccGRAY);
    
    CCMenuItemSprite* popChar = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("charButton.png"), popgy);
    CCSprite* backgy = CCSprite::createWithSpriteFrameName("charButtonR.png");
    backgy->setColor(ccGRAY);
    CCMenuItemSprite* popChar2 = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("charButtonR.png"), backgy);
    
    CCMenuItemToggle* popcharButton = CCMenuItemToggle::createWithTarget(this,menu_selector(StartScene::toCharDialog),popChar,popChar2,NULL);
    
    CCMenuItemSprite* kuangButton = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("charKuang.png"), CCSprite::createWithSpriteFrameName("charKuang.png"),this,menu_selector(StartScene::displayIME));
    kuangButton->setPosition(ccp(4,charback->getContentSize().height - 40));
    kuangButton->setAnchorPoint(ccp(0,0.5));
    
    m_TextField = CCTextFieldTTF::textFieldWithPlaceHolder("点击此处输入文字","Arial",20);
    m_TextField->setColor(ccc3(200, 200, 200));
    kuangButton->addChild(m_TextField);
    m_TextField->setPosition(ccp(20,32));
    m_TextField->setAnchorPoint(ccp(0,0));
    m_TextField->setDelegate(this);
    //
    CCMenuItemSprite* sendButton = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("sendButton.png"), CCSprite::createWithSpriteFrameName("sendButtonP.png"),this,menu_selector(StartScene::sendCallBack));
    sendButton->setPosition(ccp(charback->getContentSize().width,charback->getContentSize().height - 40));
    sendButton->setAnchorPoint(ccp(1,0.5));
    CCSprite* sendLabel = CCSprite::createWithSpriteFrameName("sendIcon.png");
    sendLabel->setPosition(ccp(sendButton->getContentSize().width/2-5,sendButton->getContentSize().height/2-1));
    sendLabel->setColor(ccc3(249, 155, 6));
    sendLabel->setTag(sendIconTag);
    sendButton->addChild(sendLabel);
    
    CCMenuItemSprite* totalFliterButton = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("totalFliterButton.png"),CCSprite::createWithSpriteFrameName("totalFliterButtonP.png"),this,menu_selector(StartScene::changeCharFliter));
    totalFliterButton->setAnchorPoint(ccp(0,0.5));
    totalFliterButton->setPosition(ccp(22,34));
    totalFliterButton->setScale(1.333333);
    totalFliterButton->setTag(totalFliterTag);
    
    CCMenuItemSprite* unionFliterButton = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("unionFliterButton.png"),CCSprite::createWithSpriteFrameName("unionFliterButtonP.png"),this,menu_selector(StartScene::changeCharFliter));
    unionFliterButton->setAnchorPoint(ccp(0,0.5));
    unionFliterButton->setPosition(ccp(totalFliterButton->getContentSize().width*1.33+24,34));
    unionFliterButton->setScale(1.333333);
    unionFliterButton->setTag(unionFliterTag);
    
    CCMenuItemSprite* privateFliterButton = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("privateFliterButton.png"),CCSprite::createWithSpriteFrameName("privateFliterButtonP.png"),this,menu_selector(StartScene::changeCharFliter));
    privateFliterButton->setAnchorPoint(ccp(0,0.5));
    privateFliterButton->setPosition(ccp(totalFliterButton->getContentSize().width*2.66+27,34));
    privateFliterButton->setScale(1.333333);
    privateFliterButton->setTag(privateFliterTag);
    
    totalCharListView = GXListView::create(-501);
    totalCharListView->setOriPosition(ccp(-382,58));
    totalCharListView->setContentSize(CCSizeMake(380, 490));
    //    scroll->setTag(charScorllTag);
    chardialog->addChild(totalCharListView);
    
    GXListView* transScroll = GXListView::create(-501);
    transScroll->setEnabled(false);
    transScroll->setOriPosition(ccp(-20,0));
    transScroll->setContentSize(CCSizeMake(360, 230));
    transScroll->setTag(transScorllTag);
    this->addChild(transScroll,20);
    
    unionCharListView = GXListView::create(-501);
    unionCharListView->setOriPosition(ccp(-382,58));
    unionCharListView->setContentSize(CCSizeMake(380, 490));
    //    scroll->setTag(charScorllTag);
    chardialog->addChild(unionCharListView);
    
    
    
    GXRadioMenu* radio = GXRadioMenu::create(-510,totalFliterButton,unionFliterButton,privateFliterButton,NULL);
    radio->setPosition(ccp(0,0));
    chardialog->addChild(radio);
    
    
    MyPriorityMenu* charmenu = MyPriorityMenu::create(-510,sendButton,kuangButton,popcharButton,NULL);
    charmenu->setPosition(ccp(0,0));
    charmenu->setTag(charmenuTag);
    charmenu->setUserObject(sendButton);
    chardialog->addChild(charmenu);
    
    
    popcharButton->setPosition(ccp(charback->getContentSize().width,charback->getContentSize().height/2));
    popcharButton->setAnchorPoint(ccp(0,0.5));
    chardialog->setPosition(ccp(-charback->getContentSize().width,0));
    chardialog->setTag(charDialogTag);
    StartScene::updateChar();
    //    this->schedule(schedule_selector(StartScene::updateChar),1);
    
    //    CCSprite* grayOptionButton1 = CCSprite::createWithSpriteFrameName("menuButton1.png");
    //    grayOptionButton1->setColor(ccGRAY);
    //    CCMenuItemSprite* optionButton = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("menuButton1.png"),grayOptionButton1,this,menu_selector(StartScene::popMenuMenu));
    //    optionButton->setAnchorPoint(ccp(1,1));
    //    optionButton->setPosition(ccp(winSize.width,winSize.height));
    //    optionButton->setTag(optionButton1Tag);
    //
    //    CCSprite* grayOptionButton2 = CCSprite::createWithSpriteFrameName("menuButton2.png");
    //    grayOptionButton2->setColor(ccGRAY);
    //    CCMenuItemSprite* optionButton2 = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("menuButton2.png"),grayOptionButton2,this,menu_selector(StartScene::popMenuMenu));
    //    optionButton2->setAnchorPoint(ccp(1,1));
    //    optionButton2->setPosition(ccp(winSize.width,winSize.height-25));
    //
    //    CCSprite* blackback = CCSprite::create("whiteImage.jpg");
    //    blackback->setColor(ccc3(20,10,0));
    //    blackback->setScaleX(grayOptionButton2->getContentSize().width-2/blackback->getContentSize().width);
    //    blackback->setScaleY(270/blackback->getContentSize().height);
    //    blackback->setAnchorPoint(ccp(0,0));
    //    blackback->setPosition(ccp(2,40));
    //
    //    optionButton2->addChild(blackback,-1);
    //
    //
    //
    //    CCSprite* grayAchievementButton = CCSprite::createWithSpriteFrameName("archAchievement.png");
    //    grayAchievementButton->setColor(ccGRAY);
    //    CCMenuItemSprite* achievementButton = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("archAchievement.png"),grayAchievementButton);
    //    achievementButton->setPosition(ccp(winSize.width-grayOptionButton2->getContentSize().width/2-1,745));
    //    achievementButton->setTag(optionAchievementButtonTag);
    //    achievementButton->setEnabled(false);
    //    achievementButton->setVisible(false);
    //
    //
    //    CCSprite* grayLogoutButton = CCSprite::createWithSpriteFrameName("logoutButton.png");
    //    grayLogoutButton->setColor(ccGRAY);
    //    CCMenuItemSprite* logoutButton = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("logoutButton.png"),grayLogoutButton,this,menu_selector(StartScene::doLogout));
    //    logoutButton->setPosition(ccp(winSize.width-grayOptionButton2->getContentSize().width/2-1,655));
    //    logoutButton->setEnabled(false);
    //
    //    MyPriorityMenu* optionMenu = MyPriorityMenu::create(-502,optionButton2,achievementButton,logoutButton,optionButton,NULL);
    //    optionMenu->setPosition(ccp(0,0));
    //    optionMenu->setTag(optionMenuTag);
    //
    //
    //
    
    CCSprite* gybattle = CCSprite::createWithSpriteFrameName("battleIcon.png");
    gybattle->setColor(ccGRAY);
    CCMenuItemSprite* battleButton = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("battleIcon.png"), gybattle,this,menu_selector(StartScene::toBattleScene));
    battleButton->setPosition(winSize.width-85,85);
    MyPriorityMenu* battleMenu = MyPriorityMenu::create(-500,battleButton,NULL);
    battleMenu->setPosition(ccp(0,0));
    battleMenu->setTag(battleMenuTag);
    
    //    uiLayer->addChild(bottom);
    //    uiLayer->addChild(battlem);
    //    uiLayer->addChild(mainMenuTipUp);
    uiLayer->addChild(scollView);
    uiLayer->addChild(battleMenu);
    uiLayer->addChild(avatar);
    //    uiLayer->addChild(huodongMenu);
    //    uiLayer->addChild(optionMenu);
    uiLayer->addChild(questMenu);
    this->addChild(chardialog,21);
    //    uiLayer->addChild(resourseBar);
    controlMenu = scollView;
    addChild(uiLayer);
    addUnionLayerInAvatar();
    
    addChild(resourseBar,20);
    
    
    //
    //    BattleQuest* quest2 = BattleQuest::create();
    //    quest2->setTitleStr(CCString::create("每日任务3，日扯"));
    //    quest2->setDescStr(CCString::create("测试战斗力"));
    //    quest2->needBattleTimes = 2;
    //    QuestManager::getInstance()->addQuest(quest2);
    //    if (quest2->getCompleteStatus() == questFinishedTag) {
    //        CCMenuItem* questItem = addDisplayQuest(quest2,true);
    //        questItem->setPosition(ccp(100,570-QuestManager::getInstance()->questList->count()*100));
    //    } else {
    //        CCMenuItem* questItem = addDisplayQuest(quest2);
    //        questItem->setPosition(ccp(100,570-QuestManager::getInstance()->questList->count()*100));
    //    }
    
    //    ArmyQuest* quest2 = ArmyQuest::create();
    //    quest2->setTitleStr(CCString::create("每日任务3，日扯"));
    //    quest2->setDescStr(CCString::create("测试战斗力"));
    
    //    CCArray* needArmyTagList;
    //    CCArray* needArmyLevelList;
    //    CCArray* needArmyLabelList;
    //    CCArray* finishArmyList;
    
    //    quest2->needArmyTagList->addObject(GXintValue::create(garadeCardId));
    //    quest2->needArmyTagList->addObject(GXintValue::create(WillysMBCardId));
    //    quest2->needArmyLevelList->addObject(GXintValue::create(1));
    //    quest2->needArmyLevelList->addObject(GXintValue::create(10));
    //    quest2->needArmyLabelList->addObject(CCString::create("步枪兵"));
    //    quest2->needArmyLabelList->addObject(CCString::create("吉普车"));
    //    CCObject* obj1;
    //    CCObject* obj2;
    //    CCARRAY_FOREACH(quest2->needArmyTagList,obj1){
    //        int tag = ((GXintValue*)(obj1))->getValue();
    //        int beanLevel = 0;
    //        CCARRAY_FOREACH(MyGameInfo::getInstance()->creatorArray,obj2) {
    //            CreatorInfoBean* bean = (CreatorInfoBean*)obj2;
    //            if (bean->creator->cardId == tag) {
    //                if (bean->getLevel() > beanLevel) {
    //                    beanLevel = bean->getLevel();
    //                }
    //            }
    //        }
    //        quest2->finishArmyList->addObject(GXintValue::create(beanLevel));
    //    }
    //
    //    QuestManager::getInstance()->addQuest(quest2);
    //    if (quest2->getCompleteStatus() == questFinishedTag) {
    //        CCMenuItem* questItem = addDisplayQuest(quest2,true);
    //        questItem->setPosition(ccp(100,570-QuestManager::getInstance()->questList->count()*100));
    //    } else {
    //        CCMenuItem* questItem = addDisplayQuest(quest2);
    //        questItem->setPosition(ccp(100,570-QuestManager::getInstance()->questList->count()*100));
    //    }
    
    MyHttpConnection::getInstance()->sendGetNoReadedMatches();
    MyHttpConnection::getInstance()->sendGetCpuWar();
    MyHttpConnection::getInstance()->sendGetRecharge();
    //    MyGameInfo::getInstance()->creatorArray->addObject(CreatorInfoBean::create(HummingBirdCardId));
    
}

CCMenuItem* StartScene::displayMubeiInfo(int mubeiCount) {
    //        CCSprite* grayMubei = CCSprite::createWithSpriteFrameName("ghostButton.png");
    //        grayMubei->setColor(ccGRAY);
    
    CCSprite*  normalSprite = CCSprite::createWithSpriteFrameName("huodongButton.png");
    
    MyMenuItem* mubeiButton = MyMenuItem::create(normalSprite,this,menu_selector(StartScene::toOneKeyArchieveGhost));
    CCSprite* mubeiIcon = CCSprite::createWithSpriteFrameName("ghostButton.png");
    mubeiIcon->setPosition(ccp(mubeiButton->getContentSize().width/2,mubeiButton->getContentSize().height/2+10));
    mubeiIcon->setScale(Mathlib::min(70/mubeiIcon->getContentSize().width,70/mubeiIcon->getContentSize().height));
    //    mubeiButton->setScale(0.9);
    mubeiButton->setTag(mubeiButtonTag);
    normalSprite->addChild(mubeiIcon);
    
    //        CCMenuItemSprite* mubeiButton = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("ghostButton.png"),grayMubei,this,menu_selector(StartScene::toOneKeyArchieveGhost));
    //        mubeiButton->setPosition(ccp(0,130*huodongCount));
    //        mubeiButton->setTag(mubeiButtonTag);
    //
    //        CCSprite* mubeibling1_1 = CCSprite::create("armyprizeLight.png");
    //        mubeibling1_1->setPosition(ccp(mubeiButton->getContentSize().width/2,mubeiButton->getContentSize().height/2));
    //        mubeibling1_1->setScale(0.7);
    //        mubeibling1_1->runAction(CCRepeatForever::create(CCRotateBy::create(1000, 7200)));
    //        mubeiButton->addChild(mubeibling1_1,-1);
    //
    //        CCSprite* mubeibling1_2 = CCSprite::create("armyprizeLight.png");
    //        mubeibling1_2->setPosition(ccp(mubeiButton->getContentSize().width/2,mubeiButton->getContentSize().height/2));
    //        mubeibling1_2->runAction(CCRepeatForever::create(CCRotateBy::create(1000, -7200)));
    //        mubeibling1_2->setScale(0.5);
    //        mubeiButton->addChild(mubeibling1_2,-1);
    
    char str[5] = {0};
    sprintf(str,"/%d",mubeiCount);
    CCLabelAtlas* mubeiCountLabel = CCLabelAtlas::create(str, "number6.png", 24, 36, '/');
    mubeiCountLabel->setUserData((void*) mubeiCount);
    mubeiCountLabel->setAnchorPoint(ccp(0,0));
    mubeiCountLabel->setScale(0.7);
    mubeiCountLabel->setTag(mubeiButtonCountTag);
    mubeiButton->addChild(mubeiCountLabel);
    mubeiCountLabel->setPosition(ccp(5,0));
    //        huodongMenu->addChild(mubeiButton);
    return mubeiButton;
    //    }
}



//void StartScene::popMenuMenu() {
//    CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sfx_click.mp3");
//    CCNode* item = this->getChildByTag(UILayerTag)->getChildByTag(optionMenuTag);
//    CCObject* obj;
//    int count = item->getChildrenCount();
//    CCARRAY_FOREACH(item->getChildren(),obj) {
//        CCNode* node = (CCNode*)obj;
//        if (node->getTag() != optionButton1Tag) {
//            if (node->getPosition().y < 610) {
//                if (node->getPosition().y >534- (count-3)*90) {
//                    ((CCMenuItem*)node)->setEnabled(false);
//                }
//                node->runAction(CCEaseElasticInOut::create(CCMoveBy::create(0.55, ccp(0,195)), 1));
//            } else {
//                if (node->getPosition().y >744- (count-3)*90) {
//                    ((CCMenuItem*)node)->setEnabled(true);
//                }
//                node->runAction(CCEaseElasticInOut::create(CCMoveBy::create(0.55, ccp(0,-195)), 1));
//            }
//        }
//    }
////    if (item->getPosition().y < 550) {
////        item->runAction(CCEaseElasticInOut::create(CCMoveTo::create(0.55, ccp(960,615)), 1));
////    } else {
////        item->runAction(CCEaseElasticInOut::create(CCMoveTo::create(0.55, ccp(960,420)), 1));
////    }
//}

void StartScene::addUnionLayerInAvatar() {
    this->getChildByTag(UILayerTag)->getChildByTag(avatarTag)->removeChildByTag(avatarUnionLayerTag,true);
    if (MyGameInfo::getInstance()->getUnionBean()->getName()->compare("") != 0) {
        CCSprite* unionBack = CCSprite::createWithSpriteFrameName("unionAvatar.png");
        unionBack->setAnchorPoint(ccp(0,0.5));
        unionBack->setPosition(ccp(0,-17));
        CCLabelTTF* namelabel = CCLabelTTF::create(MyGameInfo::getInstance()->getUnionBean()->getName()->getCString(),"Arial",19);
        namelabel->setAnchorPoint(ccp(0.5,0.5));
        namelabel->setPosition(ccp(102,unionBack->getContentSize().height/2));
        CCSprite* emblem = CCSprite::createWithSpriteFrameName(MyGameInfo::getInstance()->getUnionBean()->getEmblem()->getCString());
        emblem->setAnchorPoint(ccp(0.5,0.5));
        emblem->setPosition(ccp(22,unionBack->getContentSize().height/2+2));
        emblem->setScale(0.3);
        unionBack->addChild(namelabel);
        unionBack->addChild(emblem);
        unionBack->setTag(avatarUnionLayerTag);
        this->getChildByTag(UILayerTag)->getChildByTag(avatarTag)->addChild(unionBack);
        GXChatHandler::getInstance()->sendAddUnion(MyGameInfo::getInstance()->getUnionBean()->getName()->getCString());
    }
}

void StartScene::removeUnionLayerInAvatar() {
    this->getChildByTag(UILayerTag)->getChildByTag(avatarTag)->removeChildByTag(avatarUnionLayerTag,true);
    GXChatHandler::getInstance()->sendExitUnion(MyGameInfo::getInstance()->getUnionBean()->getName()->getCString());
}


void StartScene::doLogout() {
    this->updateMyData();
    PushTrigger::getInstance()->connectCode = logoutTag;
    MyHttpConnection::getInstance()->sendDisconnect();
    GXChatHandler::getInstance()->sendDisconnect();
}


void StartScene::toBattleScene() {
    // 去掉MAP的注册
    this->addChild(MyUtil::getInstance()->getWaitLayer("正在搜索基地"));
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sfx_click.mp3");
    MyMap* map = dynamic_cast<MyMap*>(this->getChildByTag(MainMapTag));
    //    if(map != NULL) {
    //        if(!MyHttpConnection::getInstance()->updateStartSceneData(MyJsonUtil::packAllBuilding(map->getItems()))) {
    //            this->addChild(MyUtil::getInstance()->getNetworkDialog());
    //            return;
    //        };
    //    }
    updateMyData();
    map->pauseSchedulerAndActions();
    this->cleanup();
    
    //    char str[65535] = {0};
    //    sprintf(str, "http://192.168.0.222:8080/DEFENDDIAOYUISLAND/servlet/getgamedata?itita_id=%s",PulsarNative::getDeviceId());
    //    const char* response = MyHttpConnection::getInstance()->getOtherData();
    //    if (strcmp(response, "failed") == 0 || strcmp(response, "\0") == 0) {
    //        this->addChild(MyUtil::getInstance()->getNetworkDialog());
    //        this->removeChildByTag(waitMenuTag, true);
    //        return;
    //    }
    MyGameInfo::getInstance()->enemyIron = 0;
    MyGameInfo::getInstance()->enemyOil = 0;
    CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.2, TransitonScene::create(ReadyToBattleTag),ccBLACK));
    CocosDenshion::SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
    //TODO 解决空schedule问题，不知道对不对
    //    unscheduleAllSelectors();
}


bool StartScene::updateMyData() {
    //    MyMap* map = dynamic_cast<MyMap*>(this->getChildByTag(MainMapTag));
    //    if(map->isBuild()) {
    //        ReadyToBuild* state =  dynamic_cast<ReadyToBuild*>(((MyBuilding*)map->moveTemp)->fsm->getCurrentState());
    //        if (state != NULL) {
    //            state->cancelCallBack(NULL);
    //        }else {
    //            map->moveTemp->removeFromParentAndCleanup(true);
    //        }
    ////        map->setBuild(bool __isbuild, cocos2d::CCMenu *moveTemp)
    //    } else if(map->moveTemp != NULL) {
    //        ((MyTiledMenuItem*)map->moveTemp)->toReLoc();
    //    }
    //    if (storeTrigger != NULL) {
    //        ((StoreTrigger*)storeTrigger)->sendBuyInfo(false);
    //    }
    MyHttpConnection::getInstance()->sendUpdateGameData();
    return true;
}

bool StartScene::cancelUpdateDialog(cocos2d::CCNode *pSender) {
    if (this->getChildByTag(updateLayerTag)!=NULL) {
        this->removeChildByTag(updateLayerTag, true);
        return true;
    }
    return false;
}

//void StartScene::conscriptionCallBack(cocos2d::CCObject *pSender){
//
//}
//
//void StartScene::sellCallBack(cocos2d::CCObject *pSender) {
//    CCLog("卖钱啦");
//}

void StartScene::toCreateCallBack(cocos2d::CCObject *pSender) {
    float scaleBeilv = winSize.width/960.0;
    cancelAllDialog();
    this->getChildByTag(resourceBarTag)->setVisible(false);
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sfx_popCreator.mp3");
    
    CCLayer* creatorLayer = CCLayer::create();
    CCSprite* back = CCSprite::createWithSpriteFrameName("armyback.png");
    back->setScaleX(winSize.width/back->getContentSize().width);
    back->setScaleY(winSize.height/back->getContentSize().height);
    back->setAnchorPoint(ccp(0,0));
    creatorLayer->addChild(back);
    this->addChild(creatorLayer);
    creatorLayer->setTag(creatorLayerTag);
    
    CCLayer* displayLayer = CCLayer::create();
    displayLayer->setPosition(ccp(0,0));
    creatorLayer->addChild(displayLayer,3);
    
    CCSprite* banyue = CCSprite::createWithSpriteFrameName("banyuan.png");
    banyue->setScale(1.25);
    banyue->setAnchorPoint(ccp(0,0));
    banyue->setPosition(ccp(-banyue->getContentSize().width,0));
    creatorLayer->addChild(banyue,2);
    banyue->runAction(CCSequence::create(CCDelayTime::create(0.15),CCEaseBackOut::create(CCMoveTo::create(0.5, ccp(0,0))),NULL));
    
    
    
    
    
    MyGameInfo::getInstance()->getOilAtlas()->removeFromParentAndCleanup(true);
    MyGameInfo::getInstance()->getIronAtlas()->removeFromParentAndCleanup(true);
    MyGameInfo::getInstance()->getGloryAtlas()->removeFromParentAndCleanup(true);
    MyGameInfo::getInstance()->getDiamondAtlas()->removeFromParentAndCleanup(true);
    
    
    
    creatorLayer->setPosition(ccp(0,-back->getContentSize().height));
    //    armyLayer->setPosition(ccp(0,0));
    creatorLayer->runAction(CCMoveTo::create(0.15, ccp(0,0)));
    //
    CCMenuItemSprite* totalItem = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("totalBuildingButton.png"), CCSprite::createWithSpriteFrameName("totalBuildingButtonP.png"),this,menu_selector(StartScene::displayBuildingScroll));
    totalItem->setAnchorPoint(ccp(1,0));
    totalItem->setScale(1.25);
    totalItem->setUserData((void*)0);
    //    totalItem->setPosition(ccp(263,493));
    totalItem->setPosition(ccp(0,493));
    totalItem->runAction(CCSequence::create(CCDelayTime::create(0.15),CCEaseBackOut::create(CCMoveTo::create(1, ccp(263,493))),NULL));
    
    
    CCMenuItemSprite* resourceItem = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("resourceBuildingButton.png"), CCSprite::createWithSpriteFrameName("resourceBuildingButtonP.png"),this,menu_selector(StartScene::displayBuildingScroll));
    resourceItem->setAnchorPoint(ccp(1,0));
    resourceItem->setScale(1.25);
    resourceItem->setUserData((void*)1);
    //    groundItem->setPosition(ccp(263,355));
    resourceItem->setPosition(ccp(0,355));
    resourceItem->runAction(CCSequence::create(CCDelayTime::create(0.25),CCEaseBackOut::create(CCMoveTo::create(1, ccp(263,355))),NULL));
    
    CCMenuItemSprite* armyItem = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("armyBuildingButton.png"), CCSprite::createWithSpriteFrameName("armyBuildingButtonP.png"),this,menu_selector(StartScene::displayBuildingScroll));
    armyItem->setAnchorPoint(ccp(1,0));
    armyItem->setScale(1.25);
    armyItem->setUserData((void*)2);
    //    armorItem->setPosition(ccp(263,215));
    armyItem->setPosition(ccp(0,215));
    armyItem->runAction(CCSequence::create(CCDelayTime::create(0.35),CCEaseBackOut::create(CCMoveTo::create(1, ccp(263,215))),NULL));
    
    CCMenuItemSprite* ornamentItem = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("ornamentBuildingButton.png"), CCSprite::createWithSpriteFrameName("ornamentBuildingButtonP.png"),this,menu_selector(StartScene::displayBuildingScroll));
    ornamentItem->setAnchorPoint(ccp(1,0));
    ornamentItem->setScale(1.25);
    ornamentItem->setUserData((void*)3);
    //    airItem->setPosition(ccp(263,70));
    ornamentItem->setPosition(ccp(0,70));
    ornamentItem->runAction(CCSequence::create(CCDelayTime::create(0.45),CCEaseBackOut::create(CCMoveTo::create(1, ccp(263,70))),NULL));
    
    GXRadioMenu* radio = GXRadioMenu::create(-505, totalItem,resourceItem,armyItem,ornamentItem,NULL);
    radio->setPosition(ccp(0,0));
    
    displayLayer->addChild(radio);
    radio->setTag(buduiMenuTag);
    
    
    CCMenuItemSprite* quitItem = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("quitarmy.png"), CCSprite::createWithSpriteFrameName("quitarmyP.png"),this,menu_selector(StartScene::quitCreator));
    quitItem->setContentSize(CCSizeMake(70, 70));
    
    
    
    GXShieldTouchMenuItem* shild = GXShieldTouchMenuItem::create();
    shild->setContentSize(winSize);
    shild->setPosition(ccp(0,0));
    shild->setAnchorPoint(ccp(0,0));
    
    MyPriorityMenu* menu = MyPriorityMenu::create(-502,quitItem,shild,NULL);
    menu->setPosition(ccp(0,0));
    
    quitItem->setPosition(ccp(winSize.width-61*scaleBeilv,winSize.height-24));
    //
    //    displayLayer->addChild(scroll);
    creatorLayer->addChild(menu,2);
    
    
    CCSprite* oilBack = CCSprite::createWithSpriteFrameName("armyResourceBack.png");
    oilBack->setAnchorPoint(ccp(0,1));
    oilBack->setScale(1.075);
    oilBack->setPosition(ccp(10,winSize.height));
    creatorLayer->addChild(oilBack);
    
    CCSprite* oilIcon = CCSprite::createWithSpriteFrameName("oilIcon.png");
    oilIcon->setScale(0.6);
    oilIcon->setAnchorPoint(ccp(0.5,0.5));
    oilIcon->setPosition(ccp(28,winSize.height-26));
    creatorLayer->addChild(oilIcon);
    
    CCSprite* ironBack = CCSprite::createWithSpriteFrameName("armyResourceBack.png");
    ironBack->setAnchorPoint(ccp(0,1));
    ironBack->setScale(1.075);
    ironBack->setPosition(ccp(oilBack->getPosition().x+oilBack->getContentSize().width-1,winSize.height));
    creatorLayer->addChild(ironBack);
    
    CCSprite* ironIcon = CCSprite::createWithSpriteFrameName("ironIcon.png");
    ironIcon->setScale(0.6);
    ironIcon->setAnchorPoint(ccp(0.5,0.5));
    ironIcon->setPosition(ccp(oilBack->getPosition().x+oilBack->getContentSize().width+15,winSize.height-24));
    creatorLayer->addChild(ironIcon);
    
    CCSprite* gloryBack = CCSprite::createWithSpriteFrameName("armyResourceBack.png");
    gloryBack->setAnchorPoint(ccp(0,1));
    gloryBack->setScale(1.075);
    gloryBack->setPosition(ccp(ironBack->getPosition().x+ironBack->getContentSize().width-1,winSize.height));
    creatorLayer->addChild(gloryBack);
    
    CCSprite* gloryIcon = CCSprite::createWithSpriteFrameName("honorIcon.png");
    gloryIcon->setScale(0.6);
    gloryIcon->setAnchorPoint(ccp(0.5,0.5));
    gloryIcon->setPosition(ccp(ironBack->getPosition().x+ironBack->getContentSize().width+18,winSize.height-26));
    creatorLayer->addChild(gloryIcon);
    
    CCSprite* diamondBack = CCSprite::createWithSpriteFrameName("armyResourceBack.png");
    diamondBack->setAnchorPoint(ccp(0,1));
    diamondBack->setScale(1.075);
    diamondBack->setPosition(ccp(gloryBack->getPosition().x+gloryBack->getContentSize().width-1,winSize.height));
    creatorLayer->addChild(diamondBack);
    
    CCSprite* diamondIcon = CCSprite::createWithSpriteFrameName("diamond.png");
    diamondIcon->setScale(0.75);
    diamondIcon->setAnchorPoint(ccp(0.5,0.5));
    diamondIcon->setPosition(ccp(gloryBack->getPosition().x+gloryBack->getContentSize().width+22,winSize.height-17));
    creatorLayer->addChild(diamondIcon);
    
    
    MyGameInfo::getInstance()->getOilAtlas()->setPosition(ccp(44,605));
    MyGameInfo::getInstance()->getOilAtlas()->setScale(0.65);
    MyGameInfo::getInstance()->getIronAtlas()->setPosition(ccp(187,605));
    MyGameInfo::getInstance()->getIronAtlas()->setScale(0.65);
    MyGameInfo::getInstance()->getGloryAtlas()->setPosition(ccp(335,605));
    MyGameInfo::getInstance()->getGloryAtlas()->setScale(0.65);
    MyGameInfo::getInstance()->getDiamondAtlas()->setPosition(ccp(485,605));
    MyGameInfo::getInstance()->getDiamondAtlas()->setScale(0.65);
    
    creatorLayer->addChild(MyGameInfo::getInstance()->getOilAtlas());
    creatorLayer->addChild(MyGameInfo::getInstance()->getIronAtlas());
    creatorLayer->addChild(MyGameInfo::getInstance()->getGloryAtlas());
    creatorLayer->addChild(MyGameInfo::getInstance()->getDiamondAtlas());
    
}

void StartScene::displayBuildingScroll(CCMenuItem* pSender) {
    float scaleBeilv = winSize.width/960.0;
    pSender->getParent()->getParent()->removeChildByTag(createBuildingScrollTag,true);
    GXScrollView* scroll = GXScrollView::create(-504);
    //    CCSprite* test = CCSprite::create("loading.jpg");
    //    test->setAnchorPoint(ccp(0,0));
    //    scroll->addChild(test);
    scroll->setOriPosition(ccp(0,60));
    scroll->setContentSize(CCSizeMake(winSize.width, 505));
    
    int i=0;
    int filter = (int)pSender->getUserData();
    
    CCArray* buildingCards = MyGameFactory::createAllCard(this,filter);
    if (buildingCards->count() >= 6) {
        scroll->setMapSize(CCSizeMake(winSize.width, 250*(buildingCards->count()/3+1)));
        scroll->setPosition(ccp(scroll->getOriPosition().x,-scroll->getMapSize().height+scroll->getViewSize().height+scroll->getOriPosition().y));
    }
    
    CCObject* obj;
    
    
    CCARRAY_FOREACH(buildingCards,obj) {
        MyBuildingCard* card = ((MyBuildingCard*)obj);
        card->setPosition(ccp(387*scaleBeilv + (i%3)*220,scroll->getMapSize().height-130-(i/3)*250));
        scroll->addChild(card);
        i++;
    }
    scroll->setTag(createBuildingScrollTag);
    pSender->getParent()->getParent()->addChild(scroll);
}

void StartScene::quitCreator(){
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sfx_click.mp3");
    this->removeChildByTag(creatorLayerTag, true);
    this->getChildByTag(resourceBarTag)->setVisible(true);
    if (MyGameInfo::getInstance()->getOilAtlas()->getParent() == NULL) {
        MyGameInfo::getInstance()->getOilAtlas()->setPosition(ccp(27,6));
        MyGameInfo::getInstance()->getOilAtlas()->setScale(0.52);
        MyGameInfo::getInstance()->getIronAtlas()->setPosition(ccp(130,6));
        MyGameInfo::getInstance()->getIronAtlas()->setScale(0.52);
        MyGameInfo::getInstance()->getGloryAtlas()->setPosition(ccp(235,6));
        MyGameInfo::getInstance()->getGloryAtlas()->setScale(0.52);
        MyGameInfo::getInstance()->getDiamondAtlas()->setPosition(ccp(338,6));
        MyGameInfo::getInstance()->getDiamondAtlas()->setScale(0.52);
        this->getChildByTag(resourceBarTag)->addChild(MyGameInfo::getInstance()->getOilAtlas());
        this->getChildByTag(resourceBarTag)->addChild(MyGameInfo::getInstance()->getIronAtlas());
        this->getChildByTag(resourceBarTag)->addChild(MyGameInfo::getInstance()->getGloryAtlas());
        this->getChildByTag(resourceBarTag)->addChild(MyGameInfo::getInstance()->getDiamondAtlas());
    }
    this->setUserObject(NULL);
}

void StartScene::toReadyCallback(cocos2d::CCObject *pSender) {
    MyBuildingCard* card = (MyBuildingCard*)pSender;
    int level = MyUtil::getInstance()->getLevelByExperience(MyGameInfo::getInstance()->getExperience());
    if (level < card->getUnlockLevel()) {
        
        CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sfx_click.mp3");
        CCLayer* layer = MyUtil::getInstance()->getBuildingUnlockLayer(card->name,card->getUnlockLevel());
        
        layer->setTag(armyInfoUnlockLayerTag);
        this->addChild(layer);
        
        return;
    }
    if (card->maxCount>0 && card->count >= card->maxCount) {
        CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sfx_error.wav");
        this->addChild(MyUtil::getInstance()->getCommonTipDialog(CCString::create("已经达到建筑的建造上限，无法建造。"),this,menu_selector(StartScene::cancelTipDialog),0));
        return;
    }
    hiddenControlUI();
    MyMap* map = (MyMap*)getChildByTag(MainMapTag);
    map->oriBuildPos=ccp(0,0);
    quitCreator();
    MyBuilding* build = createReady(((CCMenuItem*)pSender)->getTag());
    ((ReadyToBuild*)build->fsm->getCurrentState())->setResourceTag(card->getResourceTag());
    ((ReadyToBuild*)build->fsm->getCurrentState())->setSummaryCount(card->getSummaryCount());
    
    //    ((ReadyToBuild*)build->fsm->getCurrentState())->addExp = card->addExp;
}

//void StartScene::toBuildCallback(cocos2d::CCNode *pSender) {
//    MyMap* map = (MyMap*)getChildByTag(MainMapTag);
//    MyBuilding* building = dynamic_cast<MyBuilding*>(map->moveTemp);
//
//    if (map->collisionDetection(building)) {
//
//        //可以弹弹警告
//        CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sfx_error.wav");
//        return;
//    }
//
//    ReadyToBuild* readyState = (ReadyToBuild*)building->fsm->getState(ReadyToBuildStateTag);
//    if (checkSummary(readyState->summaryOil, readyState->summaryIron, readyState->summaryMilitary)) {
//        if (readyState->summaryOil!=0) {
//            CCPoint pos = ccp(building->getPosition().x,building->getPosition().y+ building->contentSizeByTiled.height/2 *transWindowToGLInRetina(20) +transWindowToGLInRetina(30));
//            map->addChild(MyGameInfo::getInstance()->changeResourceAndFloatText(oilTag, readyState->summaryOil*-1,pos),1000001);
//        }
//        if (readyState->summaryIron!=0) {
//            CCPoint pos = ccp(building->getPosition().x,building->getPosition().y+ building->contentSizeByTiled.height/2 *transWindowToGLInRetina(20) +transWindowToGLInRetina(30));
//            map->addChild(MyGameInfo::getInstance()->changeResourceAndFloatText(ironTag, readyState->summaryIron*-1,pos),1000001);
//        }
//    } else {
//        return;
//    }
//
//    //如果数量够的话
//
////    map->setBuild(false);
//
////    displayControlUI();
//    CCPoint loc = building->getPositionByTiled();
//    building->reorderZandTouchPriority(999999-building->getPosition().y);
//    if (building->getTag() == wallTag) {
//        building->changeStateById(WorkStateTag);
//        //TODO
////        ((MyContinueTiledMenuItemSprite*)building->getChildByTag(myTiledMenuItemTag))->updateLoc(1);
//    } else {
//        building->changeStateById(UnfinishedStateTag);
//    }
//
//
//
//    MyBuilding* newbuilding = createReady(building->getTag());
//    ((ReadyToBuild*)newbuilding->fsm->getCurrentState())->summaryOil = ((ReadyToBuild*)building->fsm->getState(ReadyToBuildStateTag))->summaryOil;
//    ((ReadyToBuild*)newbuilding->fsm->getCurrentState())->summaryIron = ((ReadyToBuild*)building->fsm->getState(ReadyToBuildStateTag))->summaryIron;
//    ((ReadyToBuild*)newbuilding->fsm->getCurrentState())->summaryMilitary = ((ReadyToBuild*)building->fsm->getState(ReadyToBuildStateTag))->summaryMilitary;
//    //    ((ReadyToBuild*)build->fsm->getCurrentState())->addExp = card->addExp;
////    CCLog("%f,%f",map->oriBuildPos.x,map->oriBuildPos.y);
//    if(loc.x - map->oriBuildPos.x >0) {
//        loc.x +=newbuilding->contentSizeByTiled.width;
//    } else if(loc.x - map->oriBuildPos.x <0){
//        loc.x -=newbuilding->contentSizeByTiled.width;
//    }
//    if(loc.y - map->oriBuildPos.y >0) {
//        loc.y +=newbuilding->contentSizeByTiled.height;
//    } else if(loc.y - map->oriBuildPos.y <0){
//        loc.y -=newbuilding->contentSizeByTiled.height;
//    }
//
//    newbuilding->setPositionByTiled(loc);
//    if (!map->checkScreenBound(newbuilding->getPosition().x, newbuilding->getPosition().y)) {
//        ((ReadyToBuild*)newbuilding->fsm->getState(ReadyToBuildStateTag))->cancelCallBack(NULL);
//        return;
//    }
////    int dir = (((int)(angle*180/3.141592654+22.5)+360)%360)/45 ;
//    map->oriBuildPos = building->getPositionByTiled();
//    map->moveArrowTip(newbuilding->getPositionByTiled(), newbuilding->contentSizeByTiled.width);
//    //    map->
//    map->initTip(newbuilding->getPosition(), newbuilding->contentSizeByTiled.width);
//    map->collisionDetection(newbuilding);
//    map->getTip();
//}

MyBuilding* StartScene::createReady(int tag) {
    MyBuilding* building = MyGameFactory::createReadyToBuildByTag(tag, this);
    MyMap* map = (MyMap*)getChildByTag(MainMapTag);
    map->cancelAllBuilding();
    map->setBuild(true,building);
    
    //    map->transMapToTiled(ccp(-map->getPosition().x+map->getViewSize().width/2,-map->getPosition().y+map->getViewSize().height/2));
    CCPoint pos = Mathlib::roundPoint(map->transMapToTiled(ccp(-map->getPosition().x+map->getViewSize().width/2,-map->getPosition().y+map->getViewSize().height/2)));
    if(((int)building->contentSizeByTiled.width)%2 ==0) {
        pos.x+=0.5;
    }
    if(((int)building->contentSizeByTiled.height)%2 ==0) {
        pos.y+=0.5;
    }
    
    //    building->setPosition(ccp(map->getContentSize().width/4+1,map->getContentSize().height/4+1));
    building->setPositionByTiled(pos);
    
    map->addChild(building,1000000);
    //    building->setPositionByTiled(pos);
    
    //显示在最顶层
    building->setActive(true);
    //    building->displaySummary();
    map->moveArrowTip(building->getPositionByTiled(), building->contentSizeByTiled);
    //    map->
    map->initTip(building->getPosition(), building->contentSizeByTiled);
    map->collisionDetection(building);
    map->getTip();
    building->showCurrentTransition();
    //    building->setActive(true);
    return building;
}

void StartScene::toggleRecorder(cocos2d::CCObject *pSender) {
    CCMenuItemToggle* toggle = ((CCMenuItemToggle*)pSender);
    cancelAllDialog();
    if(toggle->getSelectedIndex() == 1) {
        toggle->removeChildByTag(recordNewIcon,true);
        toRecordCallBack(pSender);
    } else {
        this->removeChildByTag(recorderLayerTag,true);
    }
}
#define backSize recordBack->getContentSize()
#define scrollMapHeight matchInfos->count()*120


void StartScene::toRecordCallBack(cocos2d::CCObject *pSender) {
    //    CCLog("看战绩");
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sfx_click.mp3");
    CCLayer* recordLayer = CCLayer::create();
    recordLayer->setTag(recorderLayerTag);
    //    CCSprite* recordBack = CCSprite::createWithSpriteFrameName("recordBack.png");
    CCSprite* recordBack = MyUtil::getInstance()->getRecordBack();
    recordBack->setTag(recordBackSpriteTag);
    //    recordBack->setPosition(ccp(-20,-20));
    recordBack->setPosition(ccp(winSize.width/2+40,winSize.height/2));
    
    CCLabelTTF* rankName = CCLabelTTF::create(MyUtil::getInstance()->getRankString(MyGameInfo::getInstance()->getPower()), "Arial", 34);
    recordBack->addChild(rankName,2);
    rankName->setPosition(ccp(100,recordBack->getContentSize().height-35));
    rankName->setColor(ccc3(30, 25, 22));
    
    CCSprite* rankSprite = MyUtil::getInstance()->getRankSprite(MyGameInfo::getInstance()->getPower());
    rankSprite->setPosition(ccp(40,recordBack->getContentSize().height-33));
    rankSprite->setScale(0.65);
    recordBack->addChild(rankSprite,2);
    
    recordLayer->addChild(recordBack,0);
    CCMenuItemSprite* cancelRecord = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("uiDialogCancelButton.png"), CCSprite::createWithSpriteFrameName("uiDialogCancelButtonP.png"), this, menu_selector(StartScene::toCancelRecorder));
    MyPriorityMenu* menu = MyPriorityMenu::create(-501,cancelRecord,NULL);
    recordLayer->addChild(menu,1);
    cancelRecord->setPosition(ccp(recordBack->getContentSize().width/2+16,recordBack->getContentSize().height/2-54));
    
    recordLayer->setScale(0.75);
    recordLayer->runAction(CCScaleTo::create(0.25, 1));
    
    CCMenuItemSprite* recordButton1 = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("recordButton.png"),CCSprite::createWithSpriteFrameName("recordButtonP.png"),this,menu_selector(StartScene::displayRecordCallBack));
    
    recordButton1->setPosition(ccp(winSize.width/2-367,444));
    
    
    
    CCMenuItemSprite* topButton1 = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("topButton.png"),CCSprite::createWithSpriteFrameName("topButtonP.png"),this,menu_selector(StartScene::displayTopRankCallBack));
    
    topButton1->setPosition(ccp(winSize.width/2-367,230));
    
    
    GXRadioMenu* recordRadioMenu = GXRadioMenu::create(-505,recordButton1,topButton1,NULL);
    //    recordRadioMenu->alignItemsHorizontallyWithPadding(10);
    //    uiLayer->addChild(bingzhongMenu);
    recordLayer->addChild(recordRadioMenu);
    //    bingzhongMenu->setPosition(ccp(50,50));
    recordRadioMenu->setPosition(ccp(0,0));
    
    //    CCMenuItemSprite* succItem = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("unionCommonSingleButton.png"),CCSprite::createWithSpriteFrameName("unionCommonSingleButtonP.png"),this,menu_selector(StartScene::displayWonRecordCallBack));
    //    succItem->setPosition(ccp(winSize.width/2-40,120));
    //    succItem->setScaleX(3);
    //
    //    CCLabelTTF* succLabel = CCLabelTTF::create("只看胜利","Arial",25);
    //    succLabel->setScaleX(0.33);
    //    succLabel->setPosition(ccp(succItem->getContentSize().width/2,succItem->getContentSize().height/2));
    //    succItem->addChild(succLabel);
    //
    //    CCMenuItemSprite* failItem = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("unionCommonSingleButton.png"),CCSprite::createWithSpriteFrameName("unionCommonSingleButtonP.png"),this,menu_selector(StartScene::displayLoseRecordCallBack));
    //    failItem->setPosition(ccp(winSize.width/2+100,120));
    //    failItem->setScaleX(3);
    //
    //    CCLabelTTF* failLabel = CCLabelTTF::create("只看失败","Arial",25);
    //    failLabel->setScaleX(0.33);
    //    failLabel->setPosition(ccp(failItem->getContentSize().width/2,failItem->getContentSize().height/2));
    //    failItem->addChild(failLabel);
    //
    //
    //    MyPriorityMenu* succFailMenu = MyPriorityMenu::create(-505,succItem,failItem,NULL);
    //    succFailMenu->setPosition(ccp(0,0));
    //
    //    recordLayer->addChild(succFailMenu);
    
    //    recordRadioMenu->setTag();
    
    //    menu->seshitOpacity(0);
    //    recordBack->setOpacity(0);
    //    menu->runAction(CCSequence::create(CCFadeIn::create(0.25),NULL));
    //    recordBack->runAction(CCSequence::create(CCFadeIn::create(0.25),CCCallFuncO::create(this, callfuncO_selector(StartScene::getAllMatches),recordBack), NULL));
    
    
    //    this->addChild(shieldTouch);
    
    this->addChild(recordLayer);
    //    this->addChild(MyUtil::getInstance()->getWaitLayer(),1000);
}


//void StartScene::getAllMatches(CCNode* pSender) {
//
//
//    MyHttpConnection::getInstance()->sendGetWhoAttackMeMatch();
////    CCLog(response);
////    if (response->compare("failed")==0 || response->compare( "\0") == 0) {
////
////        //这里是回调的this,并不是startscene
////
////        this->addChild(MyUtil::getInstance()->getNetworkDialog());
////        this->removeChildByTag(waitMenuTag, true);
////        return;
////    }
//
//    this->scheduleOnce(schedule_selector(StartScene::removeWaitMenu), 0.2);
//    CCLayer* recordLayer = dynamic_cast<CCLayer*>(pSender->getParent());
//    CCSprite* recordBack = dynamic_cast<CCSprite*>(pSender);
//
//    pageNo = 1;
//
//    if (recordLayer == NULL) {
//        return;
//    }
//    if( !((StartScene*) recordLayer->getParent())->updateMyData()) {
//        return;
//    }
////    disPlayRecordView(recordBack,MyJsonUtil::parseMatches(response));
//}

void StartScene::disPlayRecordView(CCArray* matchInfos) {
    this->scheduleOnce(schedule_selector(StartScene::removeWaitMenu),0.2);
    CCSprite* recordBack = NULL;
    if (this->getChildByTag(recorderLayerTag) == NULL) {
        CCLayer* recordLayer = CCLayer::create();
        recordLayer->setTag(recorderLayerTag);
        recordBack = MyUtil::getInstance()->getRecordBack();
        recordBack->setTag(recordBackSpriteTag);
        //    recordBack->setPosition(ccp(-20,-20));
        recordBack->setPosition(ccp(winSize.width/2+40,winSize.height/2));
        
        CCLabelTTF* rankName = CCLabelTTF::create(MyUtil::getInstance()->getRankString(MyGameInfo::getInstance()->getPower()), "Arial", 34);
        recordBack->addChild(rankName,2);
        rankName->setPosition(ccp(100,recordBack->getContentSize().height-35));
        rankName->setColor(ccc3(30, 25, 22));
        
        CCSprite* rankSprite = MyUtil::getInstance()->getRankSprite(MyGameInfo::getInstance()->getPower());
        rankSprite->setPosition(ccp(40,recordBack->getContentSize().height-33));
        rankSprite->setScale(0.65);
        recordBack->addChild(rankSprite,2);
        
        recordLayer->addChild(recordBack,0);
        CCMenuItemSprite* cancelRecord = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("uiDialogCancelButton.png"), CCSprite::createWithSpriteFrameName("uiDialogCancelButtonP.png"), this, menu_selector(StartScene::toCancelRecorder));
        MyPriorityMenu* menu = MyPriorityMenu::create(-501,cancelRecord,NULL);
        recordLayer->addChild(menu,1);
        cancelRecord->setPosition(ccp(recordBack->getContentSize().width/2+16,recordBack->getContentSize().height/2-54));
        
        recordLayer->setScale(0.75);
        recordLayer->runAction(CCScaleTo::create(0.25, 1));
        
        recordBack->runAction(CCFadeIn::create(0.25));
        this->addChild(recordLayer);
    } else {
        recordBack = (CCSprite*)this->getChildByTag(recorderLayerTag)->getChildByTag(recordBackSpriteTag);
    }
    
    CCLayer* contentLayer = dynamic_cast<CCLayer*>(recordBack->getParent());
    CCLayer* recordLayer = CCLayer::create();
    recordLayer->setTag(recordContentLayerTag);
    
    CCObject* obj;
    MatchInfoBean* infobean;
    GXScrollView* scollView = GXScrollView::create(-500);
    //    CCArray* itemArray = CCArray::create();
    //    MyPriorityMenu* menu = MyPriorityMenu::createWithArray(-500,NULL);
    int i = 0;
    char str[400] = {0};
    
    scollView->setOriPosition(ccp(winSize.width/2-backSize.width/2+40,winSize.height/2-backSize.height/2+30));
    
    CCMenuItemSprite* succItem = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("unionCommonSingleButton.png"),CCSprite::createWithSpriteFrameName("unionCommonSingleButtonP.png"),this,menu_selector(StartScene::displayWonRecordCallBack));
    succItem->setPosition(ccp(backSize.width/2+75,scrollMapHeight*2+30));
    succItem->setScaleX(3);
    scollView->addChild(succItem);
    
    CCLabelTTF* succLabel = CCLabelTTF::create("只看胜利","Arial",25);
    succLabel->setScaleX(0.33);
    succLabel->setPosition(ccp(succItem->getContentSize().width/2,succItem->getContentSize().height/2));
    succItem->addChild(succLabel);
    
    CCMenuItemSprite* failItem = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("unionCommonSingleButton.png"),CCSprite::createWithSpriteFrameName("unionCommonSingleButtonP.png"),this,menu_selector(StartScene::displayLoseRecordCallBack));
    failItem->setPosition(ccp(backSize.width/2-75,scrollMapHeight*2+30));
    failItem->setScaleX(3);
    
    CCLabelTTF* failLabel = CCLabelTTF::create("只看失败","Arial",25);
    failLabel->setScaleX(0.33);
    failLabel->setPosition(ccp(failItem->getContentSize().width/2,failItem->getContentSize().height/2));
    failItem->addChild(failLabel);
    scollView->addChild(failItem);
    
    //    scollView->setContentSize(CCSize(backSize.width,backSize.height));
    CCARRAY_FOREACH(matchInfos, obj) {
        infobean = ((MatchInfoBean*)obj);
        CCLabelTTF* attackNameLabel = NULL;
        CCLabelTTF* unionNameLabel = NULL;
        CCSprite* attackRank = MyUtil::getInstance()->getRankSprite(infobean->enemyPower);
        attackRank->setPosition(ccp(backSize.width/2-320,(scrollMapHeight-10-120*i-10)*2));
        attackRank->setScale(0.8);
        attackRank->setAnchorPoint(ccp(0.5,0));
        
        CCSprite* heidi = CCSprite::create("whiteImage.jpg");
        heidi->setColor(ccc3(0,0,0));
        heidi->setScaleX(630/heidi->getContentSize().width);
        heidi->setScaleY(74/heidi->getContentSize().height);
        heidi->setOpacity(150);
        heidi->setPosition(ccp(backSize.width/2,(scrollMapHeight-97-120*i)*2));
        
        sprintf(str,"%s留言说：%s",infobean->getAttackNickName()->getCString(),infobean->getNote()->getCString());
        
        CCLabelTTF* notelabel = CCLabelTTF::create(str, "Arial", 24,CCSizeMake(620,100), kCCTextAlignmentLeft, kCCVerticalTextAlignmentTop);
        notelabel->setColor(ccc3(254,185,0));
        notelabel->setAnchorPoint(ccp(0,0.5));
        notelabel->setPosition(ccp(backSize.width/2-310,(scrollMapHeight-107.5-120*i)*2));
        
        CCSprite* titleSprite = NULL;
        CCSprite* dividLine = CCSprite::createWithSpriteFrameName("dividingline.png");
        dividLine->setPosition(ccp(backSize.width/2,(scrollMapHeight-10-120*i)*2));
        dividLine->setOpacity(200);
        
        if (infobean->getAttackNickName()->compare(MyGameInfo::getInstance()->getNickName()) ==0) {
            continue;
        } else {
            if (infobean->isWin) {
                
                titleSprite = CCSprite::createWithSpriteFrameName("lose.png");
                titleSprite->setPosition(ccp(backSize.width/2+16,(scrollMapHeight-10-120*i)*2));
                
                attackNameLabel = MyUtil::getInstance()->getVipColorLabel(infobean->getAttackNickName()->getCString(),30,infobean->vipExperience);
                //                CCLog("VIP经验值：%d",infobean->vipExperience);
                attackNameLabel->setPosition(ccp(backSize.width/2-200,(scrollMapHeight-10-120*i-5)*2));
                
                if ((infobean->getUnionName()->compare("") != 0)) {
                    sprintf(str,"[%s]",infobean->getUnionName()->getCString());
                    unionNameLabel = CCLabelTTF::create(str, "Arial", 20);
                    unionNameLabel->setAnchorPoint(ccp(0,0.5));
                    unionNameLabel->setPosition(ccp(backSize.width/2-285,(scrollMapHeight-120*i)*2-6));
                    unionNameLabel->setOpacity(180);
                }
                
                CCMenuItemSprite* reverageItem = infobean->getReverageButton();
                reverageItem->setPosition(ccp(backSize.width/2+270,(scrollMapHeight-65-120*i)*2));
                //                reverageItem->setAnchorPoint(ccp(0.5,1));
                scollView->addChild(reverageItem);
                //其实这里的this已经是回调的回调了
            } else {
                titleSprite = CCSprite::createWithSpriteFrameName("win.png");
                titleSprite->setPosition(ccp(backSize.width/2+16,(scrollMapHeight-10-120*i)*2));
                
                
                attackNameLabel = CCLabelTTF::create(infobean->getAttackNickName()->getCString(), "Arial", 30);
                attackNameLabel->setPosition(ccp(backSize.width/2-200,(scrollMapHeight-10-120*i-5)*2));
                attackNameLabel->setColor(ccWHITE);
                
                if ((infobean->getUnionName()->compare("") != 0)) {
                    sprintf(str,"[%s]",infobean->getUnionName()->getCString());
                    unionNameLabel = CCLabelTTF::create(str, "Arial", 20);
                    unionNameLabel->setAnchorPoint(ccp(0,0.5));
                    unionNameLabel->setPosition(ccp(backSize.width/2-285,(scrollMapHeight-120*i)*2-5));
                    unionNameLabel->setOpacity(180);
                }
                
                
            }
        }
        CCLabelTTF* time = CCLabelTTF::create(infobean->getTime()->getCString(), "Arial", 18);
        time->setPosition(ccp(backSize.width/2+330,(scrollMapHeight-10-120*i+5)*2));
        time->setAnchorPoint(ccp(1,0.5));
        CCObject* obj2;
        int j =0;
        CCARRAY_FOREACH(infobean->frameNameArray, obj2) {
            sprintf(str, "%sbp.pvr.ccz",((CCString*)obj2)->getCString());
            
            if(CCTextureCache::sharedTextureCache()->textureForKey(str) == NULL) {
                char str1[30] = {0};
                char str2[30] = {0};
                sprintf(str1, "%sbp.plist",((CCString*)obj2)->getCString());
                sprintf(str2, "%sbp.pvr.ccz",((CCString*)obj2)->getCString());
                GXUtil::loadResourceUtilSucc(str1,str2);
                GarbageResourceCollection::getInstance()->addGarbage(str1,CCString::create(str2));
            }
            sprintf(str, "%sbp.png",((CCString*)obj2)->getCString());
            CCSprite* bp = CCSprite::createWithSpriteFrameName(str);
            if (infobean->rarityArray->count() == 0) {
                break;
            }
            sprintf(str, "deployBack%d.png",((CCInteger*)infobean->rarityArray->objectAtIndex(j))->getValue());
            CCSprite* sprite = CCSprite::createWithSpriteFrameName(str);
            bp->setPosition(ccp(53,49));
            bp->setScale(Mathlib::min(115/bp->getContentSize().width, 90/bp->getContentSize().height));
            sprite->addChild(bp);
            sprite->setScale(0.75);
            
            sprite->setPosition(ccp(70+j*80,(scrollMapHeight-45-120*i)*2));
            sprintf(str, "/%d",((CCInteger*)infobean->unitCountArray->objectAtIndex(j))->getValue());
            CCLabelAtlas* unitCount = CCLabelAtlas::create(str, "number6.png", 24, 36, '/');
            unitCount->setAnchorPoint(ccp(0.5,1));
            unitCount->setScale(0.7);
            unitCount->setPosition(ccp(sprite->getContentSize().width/2,0));
            sprite->addChild(unitCount);
            scollView->addChild(sprite);
            if (j< infobean->levelArray->count()) {
                sprintf(str, "Lv:%d",((CCInteger*)infobean->levelArray->objectAtIndex(j))->getValue());
                CCLabelTTF* levelLabel = CCLabelTTF::create(str, "Arial", 25);
                levelLabel->setAnchorPoint(ccp(0,0));
                levelLabel->setPosition(ccp(10,5));
                sprite->addChild(levelLabel);
            } else {
                CCLabelTTF* levelLabel = CCLabelTTF::create("Lv:1", "Arial", 25);
                levelLabel->setAnchorPoint(ccp(0,0));
                levelLabel->setPosition(ccp(10,5));
                sprite->addChild(levelLabel);
            }
            j++;
        }
        
        
        CCSprite* oilIcon = CCSprite::createWithSpriteFrameName("oilIcon.png");
        oilIcon->setPosition(ccp(backSize.width/2+200,(scrollMapHeight-32-120*i)*2));
        oilIcon->setScale(0.6);
        char str1[10] = {0};
        sprintf(str1, "%d",infobean->robberOil*-1);
        CCLabelTTF* robberOil = CCLabelTTF::create(str1, "Arial", 22);
        robberOil->setPosition(ccp(backSize.width/2+224,(scrollMapHeight-33-120*i)*2));
        robberOil->setAnchorPoint(ccp(0,0.5));
        
        CCSprite* ironIcon = CCSprite::createWithSpriteFrameName("ironIcon.png");
        ironIcon->setPosition(ccp(backSize.width/2+200,(scrollMapHeight-47-120*i)*2));
        ironIcon->setScale(0.6);
        sprintf(str1, "%d",infobean->robberIron*-1);
        CCLabelTTF* robberIron = CCLabelTTF::create(str1, "Arial", 22);
        robberIron->setPosition(ccp(backSize.width/2+224,(scrollMapHeight-49-120*i)*2));
        robberIron->setAnchorPoint(ccp(0,0.5));
        
        CCSprite* honorIcon = CCSprite::createWithSpriteFrameName("powerIcon.png");
        honorIcon->setPosition(ccp(backSize.width/2+200,(scrollMapHeight-17-120*i)*2));
        honorIcon->setScale(0.6);
        if (infobean->isWin) {
            sprintf(str1, "%d",infobean->deltaPower*-1);
        } else {
            sprintf(str1, "%d",infobean->deltaPower);
        }
        
        CCLabelTTF* robberHonor = CCLabelTTF::create(str1, "Arial", 22);
        robberHonor->setPosition(ccp(backSize.width/2+224,(scrollMapHeight-17-120*i)*2));
        robberHonor->setAnchorPoint(ccp(0,0.5));
        
        scollView->addChild(dividLine,2);
        scollView->addChild(titleSprite,2);
        scollView->addChild(oilIcon,2);
        scollView->addChild(robberOil,2);
        scollView->addChild(ironIcon,2);
        scollView->addChild(robberIron,2);
        scollView->addChild(honorIcon,2);
        scollView->addChild(robberHonor,2);
        if ((infobean->getUnionName()->compare("") != 0)) {
            scollView->addChild(unionNameLabel,2);
        }
        scollView->addChild(attackNameLabel,2);
        scollView->addChild(attackRank,2);
        scollView->addChild(heidi,2);
        scollView->addChild(notelabel,20);
        
        scollView->addChild(time,2);
        i++;
        
        //        scollView->setPosition(ccp(winSize.width/2,winSize.height/2));
    }
    
    
    //    menu->setPosition(transWindowToGLInRetina(0,0));
    //    scollView->addChild(menu,10);
    scollView->setContentSize(CCSizeMake(backSize.width, backSize.height-90));
    scollView->setMapSize(CCSizeMake(200,scrollMapHeight*2+60));
    //    CCLog("matchInfo:%d",matchInfos->count()*30);
    //    float asd = -scollView->getMapSize().height;
    scollView->setPosition(ccp(winSize.width/2-backSize.width/2+40,-scollView->getMapSize().height+scollView->getViewSize().height+scollView->getOriPosition().y+60));
    //    scollView->setPosition(ccp(winSize.width/2-backSize.width/2,winSize.height/2-backSize.height/2+matchInfos->count()*30-scollView->getContentSize().height));
    //    this->scheduleOnce(schedule_selector(StartScene::toChangeTouchPriority), 0);
    recordLayer->addChild(scollView);
    contentLayer->addChild(recordLayer);
    //    CCSprite* sprite = CCSprite::create("loading.jpg");
    //    sprite->setAnchorPoint(ccp(0,0));
    //    sprite->setPosition(ccp(-scollView->getOriPosition().x,-scollView->getOriPosition().y));
    //    scollView->addChild(sprite);
    
}

//void StartScene::toReverageCallBack(cocos2d::CCObject *pSender) {
//    MatchInfoBean* infoBean = (MatchInfoBean*)pSender;
//    CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sfx_click.mp3");
////    StartScene* scene = dynamic_cast<StartScene*>(infoBean->getParent()->getParent()->getParent()->getParent());
//    MyMap* map = dynamic_cast<MyMap*>(this->getChildByTag(MainMapTag));
//
//    if(map != NULL) {
//        if(!updateMyData()) {
//            this->addChild(MyUtil::getInstance()->getNetworkDialog());
//            return;
//        };
//    }
//    map->pauseSchedulerAndActions();
//    const char* response = MyHttpConnection::getInstance()->getOtherData(infoBean->attackId);
//
//    if (strcmp(response, "failed") == 0) {
//        this->addChild(MyUtil::getInstance()->getNetworkDialog());
//        return;
//    }
//    CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(1.0, MyJsonUtil::parseBattleNativeInfo(response), ccWHITE));
//    CocosDenshion::SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
//
////    CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sfx_click.mp3");
////    MyMap* map = dynamic_cast<MyMap*>(this->getChildByTag(MainMapTag));
////    //    if(map != NULL) {
////    //        if(!MyHttpConnection::getInstance()->updateStartSceneData(MyJsonUtil::packAllBuilding(map->getItems()))) {
////    //            this->addChild(MyUtil::getInstance()->getNetworkDialog());
////    //            return;
////    //        };
////    //    }
////    if(!updateMyData()) {
////        return;
////    }
////    map->pauseSchedulerAndActions();
////http://192.168.0.103:8080/DEFENDDIAOYUISLAND/servlet/getothersgamedata
////
////    //    char str[65535] = {0};
////    //    sprintf(str, "http://192.168.0.222:8080/DEFENDDIAOYUISLAND/servlet/getgamedata?itita_id=%s",PulsarNative::getDeviceId());
////    const char* response = MyHttpConnection::getInstance()->getOtherData();
////    if (strcmp(response, "failed") == 0 || strcmp(response, "\0") == 0) {
////        this->addChild(MyUtil::getInstance()->getNetworkDialog());
////        return;
////    }
////    CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(1.0, MyJsonUtil::parseBattleNativeInfo(response), ccWHITE));
////    CocosDenshion::SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
//}

void StartScene::toCancelRecorder(cocos2d::CCObject *pSender) {
    if (this->getChildByTag(recorderLayerTag) == NULL) {
        return;
    }
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sfx_click.mp3");
    CCMenuItemToggle* item = ((CCMenuItemToggle*)controlMenu->getChildByTag(recordToggleTag));
    if (item->getSelectedIndex() == 1) {
        item->setSelectedIndex(0);
    }
    this->getChildByTag(recorderLayerTag)->removeFromParentAndCleanup(true);
}

void StartScene::cancelAllDialog() {
    toCancelRecorder(NULL);
    if (this->getChildByTag(NoResourceTag)) {
        this->removeChildByTag(NoResourceTag, true);
    }
    cancelUpdateDialog(NULL);
    this->removeChildByTag(creatorLayerTag, true);
    toCancelSecond();
}

void StartScene::toExit() {
    cancelAllDialog();
    if(!isClickExit) {
        PulsarNative::showExitMessage();
        isClickExit = true;
        this->scheduleOnce(schedule_selector(StartScene::cancelClickExit), 2);
    } else {
        //        PulsarNative::toHome();
        CocosDenshion::SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
        this->scheduleOnce(schedule_selector(StartScene::doSaveToExit),0.1);
        //        CCDirector::sharedDirector()->replaceScene(LoadingScene::create());
        
    }
}

void StartScene::cancelClickExit() {
    if(isClickExit) {
        isClickExit = false;
    }
}


void StartScene::toShowCallBack(cocos2d::CCObject *psender) {
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sfx_click.mp3");
    PulsarNative::toShow();
    //    cancelAllDialog();
}


void StartScene::doPause() {
    updateMyData();
    if(MyHttpConnection::isConn) {
    	MyHttpConnection::sendbyPipline();
    }
    PushTrigger::getInstance()->connectCode = pauseTag;
    //    updateMyData();
    //    CCDirector::sharedDirector()->replaceScene(TransitonScene::create(startSceneTag));
}

void StartScene::doSaveToExit() {
    bool flag = true;
    while (flag) {
        flag = !updateMyData();
        CCLog("发送中。。");
    }
    PushTrigger::getInstance()->connectCode = logoutTag;
    MyHttpConnection::getInstance()->sendDisconnect();
    GXChatHandler::getInstance()->sendDisconnect();
}

void StartScene::hiddenControlUI() {
    CCNode* node = getChildByTag(UILayerTag);
    controlMenu->stopAllActions();
    CCSprite* avatar = (CCSprite*)node->getChildByTag(avatarTag);
    //    controlMenu->setPosition(transWindowToGLInRetina(360,30));
    controlMenu->runAction(CCMoveBy::create(0.15, ccp(150,0)));
    
    //    resourseBar->setPosition(ccp(winSize.width/2,winSize.height));
    avatar->stopAllActions();
    avatar->runAction(CCMoveTo::create(0.15, ccp(-avatar->getContentSize().width,winSize.height)));
    node->getChildByTag(battleMenuTag)->runAction(CCMoveBy::create(0.15, ccp(150,0)));
    //    node->getChildByTag(huodongMenuTag)->stopAllActions();
    //    node->getChildByTag(huodongMenuTag)->runAction(CCMoveBy::create(0.15, ccp(150,0)));
    
    this->getChildByTag(UILayerTag)->getChildByTag(questMenuTag)->runAction(CCMoveBy::create(0.15, ccp(-150,0)));
    //    resourceBar->
}

void StartScene::displayControlUI() {
    CCNode* node = getChildByTag(UILayerTag);
    CCSprite* avatar = (CCSprite*)node->getChildByTag(avatarTag);
    //    controlMenu->setPosition(transWindowToGLInRetina(360,30));
    controlMenu->stopAllActions();
    controlMenu->runAction(CCMoveBy::create(0.15, ccp(-150,0)));
    //    resourseBar->setPosition(ccp(winSize.width/2,winSize.height));
    avatar->stopAllActions();
    avatar->runAction(CCMoveTo::create(0.15, ccp(0,winSize.height)));
    node->getChildByTag(battleMenuTag)->runAction(CCMoveBy::create(0.15, ccp(-150,0)));
    //    node->getChildByTag(huodongMenuTag)->stopAllActions();
    //    node->getChildByTag(huodongMenuTag)->runAction(CCMoveBy::create(0.15, ccp(-150,0)));
    this->getChildByTag(UILayerTag)->getChildByTag(questMenuTag)->runAction(CCMoveBy::create(0.15, ccp(150,0)));
}

void StartScene::toArmyCallBackSimple(cocos2d::CCObject *psender) {
    float beilv = winSize.width/960.0;
    cancelAllDialog();
    this->getChildByTag(resourceBarTag)->setVisible(false);
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sfx_army.mp3");
    
    CCLayer* armyLayer = CCLayer::create();
    CCSprite* back = CCSprite::createWithSpriteFrameName("armyback.png");
    back->setScaleX(winSize.width/back->getContentSize().width);
    back->setScaleY(winSize.height/back->getContentSize().height);
    back->setAnchorPoint(ccp(0,0));
    armyLayer->addChild(back);
    this->addChild(armyLayer);
    armyLayer->setTag(creatorLayerTag);
    
    CCLayer* displayLayer = CCLayer::create();
    displayLayer->setTag(displayBuduiLayerTag);
    displayLayer->setPosition(ccp(0,0));
    armyLayer->addChild(displayLayer,3);
    
    CCSprite* banyue = CCSprite::createWithSpriteFrameName("banyuan.png");
    banyue->setScale(1.25);
    banyue->setAnchorPoint(ccp(0,0));
    banyue->setPosition(ccp(-banyue->getContentSize().width,0));
    armyLayer->addChild(banyue,2);
    banyue->runAction(CCSequence::create(CCDelayTime::create(0.15),CCEaseBackOut::create(CCMoveTo::create(0.5, ccp(0,0))),NULL));
    
    
    
    
    
    MyGameInfo::getInstance()->getOilAtlas()->removeFromParentAndCleanup(true);
    MyGameInfo::getInstance()->getIronAtlas()->removeFromParentAndCleanup(true);
    MyGameInfo::getInstance()->getGloryAtlas()->removeFromParentAndCleanup(true);
    MyGameInfo::getInstance()->getDiamondAtlas()->removeFromParentAndCleanup(true);
    
    
    
    
    armyLayer->setPosition(ccp(0,-back->getContentSize().height));
    //    armyLayer->setPosition(ccp(0,0));
    armyLayer->runAction(CCMoveTo::create(0.15, ccp(0,0)));
    //
    CCMenuItemSprite* totalItem = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("totalarmyP.png"), CCSprite::createWithSpriteFrameName("totalarmy.png"),this,menu_selector(StartScene::displayArmyScroll));
    totalItem->setAnchorPoint(ccp(1,0));
    totalItem->setUserData((void*)0);
    //    totalItem->setPosition(ccp(263,493));
    totalItem->setPosition(ccp(0,493));
    totalItem->runAction(CCSequence::create(CCDelayTime::create(0.15),CCEaseBackOut::create(CCMoveTo::create(1, ccp(263,493))),NULL));
    
    
    CCMenuItemSprite* groundItem = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("groundarmyP.png"), CCSprite::createWithSpriteFrameName("groundarmy.png"),this,menu_selector(StartScene::displayArmyScroll));
    groundItem->setAnchorPoint(ccp(1,0));
    groundItem->setUserData((void*)1);
    //    groundItem->setPosition(ccp(263,355));
    groundItem->setPosition(ccp(0,355));
    groundItem->runAction(CCSequence::create(CCDelayTime::create(0.25),CCEaseBackOut::create(CCMoveTo::create(1, ccp(263,355))),NULL));
    
    CCMenuItemSprite* armorItem = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("armorarmyP.png"), CCSprite::createWithSpriteFrameName("armorarmy.png"),this,menu_selector(StartScene::displayArmyScroll));
    armorItem->setAnchorPoint(ccp(1,0));
    armorItem->setUserData((void*)2);
    //    armorItem->setPosition(ccp(263,215));
    armorItem->setPosition(ccp(0,215));
    armorItem->runAction(CCSequence::create(CCDelayTime::create(0.35),CCEaseBackOut::create(CCMoveTo::create(1, ccp(263,215))),NULL));
    
    CCMenuItemSprite* airItem = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("airarmyP.png"), CCSprite::createWithSpriteFrameName("airarmy.png"),this,menu_selector(StartScene::displayArmyScroll));
    airItem->setAnchorPoint(ccp(1,0));
    airItem->setUserData((void*)3);
    //    airItem->setPosition(ccp(263,70));
    airItem->setPosition(ccp(0,70));
    airItem->runAction(CCSequence::create(CCDelayTime::create(0.45),CCEaseBackOut::create(CCMoveTo::create(1, ccp(263,70))),NULL));
    
    GXRadioMenu* radio = GXRadioMenu::create(-504, totalItem,groundItem,armorItem,airItem,NULL);
    radio->setPosition(ccp(0,0));
    
    displayLayer->addChild(radio);
    radio->setTag(buduiMenuTag);
    
    
    CCMenuItemSprite* quitItem = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("quitarmy.png"), CCSprite::createWithSpriteFrameName("quitarmyP.png"),this,menu_selector( StartScene::quitCreator));
    quitItem->setContentSize(CCSizeMake(70, 70));
    
    
    
    GXShieldTouchMenuItem* shild = GXShieldTouchMenuItem::create();
    shild->setContentSize(winSize);
    shild->setPosition(ccp(0,0));
    shild->setAnchorPoint(ccp(0,0));
    
    MyPriorityMenu* menu = MyPriorityMenu::create(-502,quitItem,shild,NULL);
    menu->setPosition(ccp(0,0));
    
    quitItem->setPosition(ccp(winSize.width-61*beilv,winSize.height-24));
    //
    //    displayLayer->addChild(scroll);
    armyLayer->addChild(menu,2);
    
    CCSprite* oilBack = CCSprite::createWithSpriteFrameName("armyResourceBack.png");
    oilBack->setAnchorPoint(ccp(0,1));
    oilBack->setScale(1.075);
    oilBack->setPosition(ccp(10,winSize.height));
    armyLayer->addChild(oilBack);
    
    CCSprite* oilIcon = CCSprite::createWithSpriteFrameName("oilIcon.png");
    oilIcon->setScale(0.6);
    oilIcon->setAnchorPoint(ccp(0.5,0.5));
    oilIcon->setPosition(ccp(28,winSize.height-26));
    armyLayer->addChild(oilIcon);
    
    CCSprite* ironBack = CCSprite::createWithSpriteFrameName("armyResourceBack.png");
    ironBack->setAnchorPoint(ccp(0,1));
    ironBack->setScale(1.075);
    ironBack->setPosition(ccp(oilBack->getPosition().x+oilBack->getContentSize().width-1,winSize.height));
    armyLayer->addChild(ironBack);
    
    CCSprite* ironIcon = CCSprite::createWithSpriteFrameName("ironIcon.png");
    ironIcon->setScale(0.6);
    ironIcon->setAnchorPoint(ccp(0.5,0.5));
    ironIcon->setPosition(ccp(oilBack->getPosition().x+oilBack->getContentSize().width+15,winSize.height-24));
    armyLayer->addChild(ironIcon);
    
    CCSprite* gloryBack = CCSprite::createWithSpriteFrameName("armyResourceBack.png");
    gloryBack->setAnchorPoint(ccp(0,1));
    gloryBack->setScale(1.075);
    gloryBack->setPosition(ccp(ironBack->getPosition().x+ironBack->getContentSize().width-1,winSize.height));
    armyLayer->addChild(gloryBack);
    
    CCSprite* gloryIcon = CCSprite::createWithSpriteFrameName("honorIcon.png");
    gloryIcon->setScale(0.6);
    gloryIcon->setAnchorPoint(ccp(0.5,0.5));
    gloryIcon->setPosition(ccp(ironBack->getPosition().x+ironBack->getContentSize().width+18,winSize.height-26));
    armyLayer->addChild(gloryIcon);
    
    CCSprite* diamondBack = CCSprite::createWithSpriteFrameName("armyResourceBack.png");
    diamondBack->setAnchorPoint(ccp(0,1));
    diamondBack->setScale(1.075);
    diamondBack->setPosition(ccp(gloryBack->getPosition().x+gloryBack->getContentSize().width-1,winSize.height));
    armyLayer->addChild(diamondBack);
    
    CCSprite* diamondIcon = CCSprite::createWithSpriteFrameName("diamond.png");
    diamondIcon->setScale(0.75);
    diamondIcon->setAnchorPoint(ccp(0.5,0.5));
    diamondIcon->setPosition(ccp(gloryBack->getPosition().x+gloryBack->getContentSize().width+22,winSize.height-17));
    armyLayer->addChild(diamondIcon);
    
    
    MyGameInfo::getInstance()->getOilAtlas()->setPosition(ccp(44,605));
    MyGameInfo::getInstance()->getOilAtlas()->setScale(0.65);
    MyGameInfo::getInstance()->getIronAtlas()->setPosition(ccp(187,605));
    MyGameInfo::getInstance()->getIronAtlas()->setScale(0.65);
    MyGameInfo::getInstance()->getGloryAtlas()->setPosition(ccp(335,605));
    MyGameInfo::getInstance()->getGloryAtlas()->setScale(0.65);
    MyGameInfo::getInstance()->getDiamondAtlas()->setPosition(ccp(485,605));
    MyGameInfo::getInstance()->getDiamondAtlas()->setScale(0.65);
    
    armyLayer->addChild(MyGameInfo::getInstance()->getOilAtlas());
    armyLayer->addChild(MyGameInfo::getInstance()->getIronAtlas());
    armyLayer->addChild(MyGameInfo::getInstance()->getGloryAtlas());
    armyLayer->addChild(MyGameInfo::getInstance()->getDiamondAtlas());
    armyLayer->setUserData(quitItem);
}

void StartScene::displayArmyScroll(CCMenuItem* pSender) {
    float beilv = winSize.width/960.0;
    pSender->getParent()->getParent()->removeChildByTag(buduiScrollTag,true);
    GXScrollView* scroll = GXScrollView::create(-503);
    scroll->setTag(buduiScrollTag);
    //    CCSprite* test = CCSprite::create("loading.jpg");
    //    test->setAnchorPoint(ccp(0,0));
    //    scroll->addChild(test);
    scroll->setOriPosition(ccp(0,60));
    scroll->setContentSize(CCSizeMake(winSize.width, 505));
    CCArray* array = MyGameInfo::getInstance()->creatorArray;
    
    char str[30] = {0};
    int i=0;
    
    
    CCArray* existCards = CCArray::create();
    int filter = (int) pSender->getUserData();
    if (filter == 0 || filter == 1) {
        CreatorInfoBean* garadeCreatorBean = CreatorInfoBean::create(garadeCardId);
        garadeCreatorBean->setExperience(0);
        MyUnitCard* garadeCard = MyUnitCard::create(garadeCreatorBean,NULL,NULL);
        existCards->addObject(garadeCard);
    }
    if (filter == 0 || filter == 2) {
        CreatorInfoBean* M5StuartCreatorBean = CreatorInfoBean::create(M5StuartCardId);
        M5StuartCreatorBean->setExperience(0);
        MyUnitCard* M5StuartCard = MyUnitCard::create(M5StuartCreatorBean,NULL,NULL);
        existCards->addObject(M5StuartCard);
    }
    if (filter == 0 || filter == 1) {
        CreatorInfoBean* PanzergrenadierCreatorBean = CreatorInfoBean::create(panzergrenadierCardId);
        PanzergrenadierCreatorBean->setExperience(0);
        MyUnitCard* PanzergrenadierCard = MyUnitCard::create(PanzergrenadierCreatorBean,NULL,NULL);
        existCards->addObject(PanzergrenadierCard);
    }
    
    if (filter == 0 || filter == 1) {
        CreatorInfoBean* WillysMBCreatorBean = CreatorInfoBean::create(WillysMBCardId);
        WillysMBCreatorBean->setExperience(0);
        MyUnitCard* WillysMBCard = MyUnitCard::create(WillysMBCreatorBean,NULL,NULL);
        existCards->addObject(WillysMBCard);
    }
    
    if (filter == 0 || filter == 1) {
        CreatorInfoBean* InfanterieCreatorBean = CreatorInfoBean::create(InfanterieCardId);
        InfanterieCreatorBean->setExperience(0);
        MyUnitCard* InfanterieCard = MyUnitCard::create(InfanterieCreatorBean,NULL,NULL);
        existCards->addObject(InfanterieCard);
    }
    if (filter == 0 || filter == 3) {
        CreatorInfoBean* HummingBirdCreatorBean = CreatorInfoBean::create(HummingBirdCardId);
        HummingBirdCreatorBean->setExperience(0);
        MyUnitCard* HummingBirdCard = MyUnitCard::create(HummingBirdCreatorBean,NULL,NULL);
        existCards->addObject(HummingBirdCard);
    }
    if (filter == 0 || filter == 2) {
        CreatorInfoBean* M3HalfTrackCreatorBean = CreatorInfoBean::create(M3HalfTrackCardId);
        M3HalfTrackCreatorBean->setExperience(0);
        MyUnitCard* M3HalfTrackCard = MyUnitCard::create(M3HalfTrackCreatorBean,NULL,NULL);
        existCards->addObject(M3HalfTrackCard);
    }
    if (filter == 0 || filter == 2) {
        CreatorInfoBean* M4ShermanCreatorBean = CreatorInfoBean::create(M4ShermanCardId);
        M4ShermanCreatorBean->setExperience(0);
        MyUnitCard* M4ShermanCard = MyUnitCard::create(M4ShermanCreatorBean,NULL,NULL);
        existCards->addObject(M4ShermanCard);
    }
    if (filter == 0 || filter == 2) {
        CreatorInfoBean* CalliopeCreatorBean = CreatorInfoBean::create(CalliopeCardId);
        CalliopeCreatorBean->setExperience(0);
        MyUnitCard* CalliopeCreatorCard = MyUnitCard::create(CalliopeCreatorBean,NULL,NULL);
        existCards->addObject(CalliopeCreatorCard);
    }
    if (filter == 0 || filter == 1) {
        CreatorInfoBean* ThorCreatorBean = CreatorInfoBean::create(ThorCardId);
        ThorCreatorBean->setExperience(0);
        MyUnitCard* ThorCreatorCard = MyUnitCard::create(ThorCreatorBean,NULL,NULL);
        existCards->addObject(ThorCreatorCard);
    }
    //
    
    if (existCards->count() >= 6) {
        scroll->setMapSize(CCSizeMake(winSize.width, 250*(existCards->count()/3+1)));
        scroll->setPosition(ccp(scroll->getOriPosition().x,-scroll->getMapSize().height+scroll->getViewSize().height+scroll->getOriPosition().y));
    }
    CCObject* obj;
    CCObject* obj2;
    unsigned long long exp = 0;
    
    CCARRAY_FOREACH(existCards,obj) {
        MyUnitCard* existCard = ((MyUnitCard*)obj);
        CCARRAY_FOREACH(array,obj) {
            CreatorInfoBean* bean = ((CreatorInfoBean*)obj);
            if (bean->creator->cardId == existCard->bean->creator->cardId) {
                
                if (bean->getExperience() > exp) {
                    exp = bean->getExperience();
                    existCard->bean->release();
                    existCard->bean = bean;
                    sprintf(str,"Lv:%d",bean->getLevel());
                    ((CCLabelTTF*)existCard->getChildByTag(lvFontTag))->setString(str);
                    bean->retain();
                }
            }
        }
        exp=0;
    }
    
    //    CCARRAY_FOREACH(array, obj) {
    //        CreatorInfoBean* bean = ((CreatorInfoBean*)obj);
    //        CCARRAY_FOREACH(existCards,obj2) {
    //            MyUnitCard* existCard = ((MyUnitCard*)obj2);
    //            if (bean->getScriptName()->compare(existCard->bean->getScriptName()->getCString()) == 0) {
    //
    //                if (bean->getExperience() > exp) {
    //                    exp = existCard->bean->getExperience();
    //                    existCard->bean->release();
    //                    existCard->bean = bean;
    //                    sprintf(str,"Lv:%d",bean->getLevel());
    //                    ((CCLabelTTF*)existCard->getChildByTag(lvFontTag))->setString(str);
    //                    bean->retain();
    //                }
    //            }
    //        }
    //        exp = 0;
    //    }
    
    CCARRAY_FOREACH(existCards,obj) {
        MyUnitCard* card = ((MyUnitCard*)obj);
        //        sprintf(str, "%sbp.png",bean->creator->getSpriteFileName());
        if (card->bean->getExperience() > 0) {
            card->setTarget(this,menu_selector(StartScene::toArmyInfoInfo));
        } else {
            card->setTarget(this,menu_selector(StartScene::toUnlockBudui));
            CCARRAY_FOREACH(card->getChildren(),obj2) {
                CCRGBAProtocol* color = dynamic_cast<CCRGBAProtocol*>(obj2);
                if(color) {
                    color->setColor(ccc3(100,100,100));
                }
            }
            ((CCLabelTTF*)card->getChildByTag(lvFontTag))->setOpacity(0);
            CCSprite* lock = CCSprite::create("lock.png");
            lock->setPosition(ccp(40,80));
            lock->setOpacity(180);
            lock->setTag(buduiLockTag);
            card->addChild(lock,20);
            
        }
        card->setPosition(ccp(387*beilv + (i%3)*220,scroll->getMapSize().height-130-(i/3)*250));
        scroll->addChild(card);
        i++;
    }
    pSender->getParent()->getParent()->addChild(scroll);
}

void StartScene::toUnlockBudui(CCMenuItem* item) {
    //    CCMenuItemSprite* sureItem = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("dialogsure.png"), CCSprite::createWithSpriteFrameName("dialogsurep.png"), target, menu_selector(StartScene::toBattleScene));
    //    sureItem->setPosition(ccp(120,-40));
    
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sfx_click.mp3");
    //
    //
    CCMenuItemSprite* cancelItem =CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("uiDialogCancelButton.png"), CCSprite::createWithSpriteFrameName("uiDialogCancelButtonP.png"),this,menu_selector(StartScene::cancelTipDialog));
    MyUnitCard* mainCard = (MyUnitCard*)item;
    
    
    GXShieldTouchMenuItem* shild = GXShieldTouchMenuItem::create();
    shild->setContentSize(winSize);
    shild->setPosition(ccp(-winSize.width/2,-winSize.height/2));
    shild->setAnchorPoint(ccp(0,0));
    
    MyPriorityMenu* menu  = MyPriorityMenu::create(-511,cancelItem,shild,NULL);
    
    
    menu->setPosition(ccp(winSize.width/2, winSize.height/2 -48));
    CCLayer* layer = CCLayer::create();
    layer->setTouchEnabled(true);
    char str[70] = {0};
    sprintf(str,"%s(%d★)",mainCard->bean->creator->getName(),mainCard->bean->creator->getRarity());
    CCLabelTTF* label1 = CCLabelTTF::create("解锁：", "宋体", 25,CCSizeZero, kCCTextAlignmentLeft, kCCVerticalTextAlignmentTop);
    
    label1->setColor(ccc3(230, 207, 185));
    label1->setPosition(ccp(winSize.width/2+15,winSize.height/2+80));
    
    CCLabelTTF* label2 = CCLabelTTF::create(str, "Arial", 30,CCSizeZero, kCCTextAlignmentLeft, kCCVerticalTextAlignmentTop);
    
    label2->setColor(ccc3(249, 155, 6));
    label2->setPosition(ccp(winSize.width/2+120,winSize.height/2+40));
    
    CCLabelTTF* costFontLabel = CCLabelTTF::create("花费：", "宋体", 25);
    
    
    costFontLabel->setColor(ccc3(230, 207, 185));
    costFontLabel->setPosition(ccp(winSize.width/2+15,winSize.height/2));
    
    CCSprite* costIcon = MyUtil::getInstance()->getResourceIcon(mainCard->bean->creator->unlockCostResourceTag);
    costIcon->setPosition(ccp(winSize.width/2+50,winSize.height/2-50));
    costIcon->setScale(1.1);
    
    
    sprintf(str,"%d",(int)mainCard->bean->creator->unlockCostCount);
    CCLabelAtlas* costLabel = CCLabelAtlas::create(str, "number6.png", 24, 36, '/');
    costLabel->setPosition(ccp(winSize.width/2+100,winSize.height/2-70));
    costLabel->setScaleY(1);
    costLabel->setScaleX(0.9);
    costLabel->setColor(ccc3(231,219,138));
    
    CCSprite* dialogBack = MyUtil::getInstance()->getDialogBack();;
    dialogBack->setPosition(ccp(winSize.width/2,winSize.height/2));
    cancelItem->setPosition(ccp(dialogBack->getContentSize().width/2 - 24,dialogBack->getContentSize().height/2 + 24));
    layer->addChild(dialogBack);
    layer->addChild(menu);
    layer->addChild(label1);
    layer->addChild(label2);
    layer->addChild(costFontLabel);
    layer->addChild(costIcon);
    layer->addChild(costLabel);
    layer->setTag(armyInfoUnlockLayerTag);
    
    if (MyGameInfo::getInstance()->getResource(mainCard->bean->creator->unlockNeedResourceTag) >= mainCard->bean->creator->unlockNeedCount) {
        CCMenuItemSprite* unlockButton = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("unlockButton.png"),CCSprite::createWithSpriteFrameName("unlockButtonP.png"),this,menu_selector(StartScene::unlockBuduiAndReturn));
        unlockButton->setPosition(ccp(100,-60));
        unlockButton->setScale(1.2);
        menu->addChild(unlockButton);
        unlockButton->setUserData(mainCard);
    } else {
        CCLabelTTF* needTipLabel = CCLabelTTF::create("需要               才能解锁", "宋体", 25);
        needTipLabel->setColor(ccc3(230, 207, 185));
        needTipLabel->setPosition(ccp(winSize.width/2+120,winSize.height/2-120));
        layer->addChild(needTipLabel);
        
        CCSprite* costIcon = MyUtil::getInstance()->getResourceIcon(mainCard->bean->creator->unlockNeedResourceTag);
        costIcon->setPosition(ccp(winSize.width/2+80,winSize.height/2-120));
        costIcon->setScale(0.6);
        layer->addChild(costIcon);
        sprintf(str,"%d",MyUtil::getInstance()->getLevelByExperience(mainCard->bean->creator->unlockNeedCount));
        
        CCLabelAtlas* atlas = CCLabelAtlas::create(str, "number5.png", 16, 22, '.');
        atlas->setAnchorPoint(ccp(0.5,0.5));
        atlas->setPosition(ccp(winSize.width/2+120,winSize.height/2-120));
        layer->addChild(atlas);
    }
    
    this->getChildByTag(creatorLayerTag)->getChildByTag(displayBuduiLayerTag)->addChild(layer);
    //    return layer;
}

//void StartScene::toDismissUnlock(CCMenuItem* item) {
//    this->getChildByTag(creatorLayerTag)->getChildByTag(displayBuduiLayerTag)->removeChildByTag(armyInfoUnlockLayerTag,true);
//}

void StartScene::unlockBuduiAndReturn(CCMenuItem* item) {
    
    MyUnitCard* card = (MyUnitCard*)item->getUserData();
    
    if (MyGameInfo::getInstance()->getResource(card->bean->creator->unlockCostResourceTag) >= card->bean->creator->unlockCostCount) {
        MyGameInfo::getInstance()->changeResource(card->bean->creator->unlockCostResourceTag,card->bean->creator->unlockCostCount*-1);
        CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sfx_updateBuilding.mp3");
        UpdateArmyMessage::create(card->bean->creator->cardId,0,1)->sendMsg();
        //发送解锁指令
        MyHttpConnection::getInstance()->sendUpdateArmyId(card->bean->creator->cardId);
        
    } else {
        CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sfx_error.wav");
        this->removeChildByTag(NoResourceTag,true);
        this->addChild(MyUtil::getInstance()->getNoResourceDialog(this,card->bean->creator->unlockCostResourceTag));
        return;
    }
    
    
    
    
    MyGameInfo::getInstance()->creatorArray->addObject(card->bean);
    card->bean->setExperience(1);
    CCObject* obj;
    
    CCARRAY_FOREACH(card->getChildren(),obj) {
        CCRGBAProtocol* color = dynamic_cast<CCRGBAProtocol*>(obj);
        if(color) {
            color->setColor(ccc3(255,255,255));
        }
    }
    ((CCLabelTTF*)card->getChildByTag(lvFontTag))->setOpacity(255);
    card->removeChildByTag(buduiLockTag,true);
    card->setTarget(this,menu_selector(StartScene::toArmyInfoInfo));
    cancelTipDialog(item);
}

void StartScene::toArmyCallBack(cocos2d::CCObject *psender) {
    this->getChildByTag(resourceBarTag)->setVisible(false);
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sfx_army.mp3");
    
    CCLayer* armyLayer = CCLayer::create();
    CCSprite* back = CCSprite::createWithSpriteFrameName("armyback.png");
    back->setScale(960/back->getContentSize().width);
    back->setAnchorPoint(ccp(0,0));
    armyLayer->addChild(back);
    this->addChild(armyLayer);
    armyLayer->setTag(creatorLayerTag);
    
    CCLayer* displayLayer = CCLayer::create();
    displayLayer->setTag(displayBuduiLayerTag);
    displayLayer->setPosition(ccp(0,0));
    armyLayer->addChild(displayLayer,3);
    
    CCSprite* banyue = CCSprite::createWithSpriteFrameName("banyuan.png");
    banyue->setScale(1.25);
    banyue->setAnchorPoint(ccp(0,0));
    banyue->setPosition(ccp(-banyue->getContentSize().width,0));
    armyLayer->addChild(banyue,2);
    banyue->runAction(CCSequence::create(CCDelayTime::create(0.15),CCEaseBackOut::create(CCMoveTo::create(0.5, ccp(0,0))),NULL));
    
    
    
    
    GXScrollView* scroll = GXScrollView::create(-501);
    scroll->setTag(buduiScrollTag);
    //    CCSprite* test = CCSprite::create("loading.jpg");
    //    test->setAnchorPoint(ccp(0,0));
    //    scroll->addChild(test);
    scroll->setOriPosition(ccp(0,60));
    scroll->setContentSize(CCSizeMake(960, 505));
    CCArray* array = MyGameInfo::getInstance()->creatorArray;
    CCObject* obj;
    char str[30] = {0};
    int i=0;
    if (array->count() >= 6) {
        scroll->setMapSize(CCSizeMake(960, 250*(array->count()/3+1)));
        scroll->setPosition(ccp(scroll->getOriPosition().x,-scroll->getMapSize().height+scroll->getViewSize().height+scroll->getOriPosition().y));
    }
    
    CCARRAY_FOREACH_REVERSE(array, obj) {
        CreatorInfoBean* bean = ((CreatorInfoBean*)obj);
        sprintf(str, "%sbp.png",bean->creator->getSpriteFileName());
        MyUnitCard* unitCard = MyUnitCard::create(bean,this,menu_selector(StartScene::toArmyInfoInfo));
        unitCard->setPosition(ccp(387 + (i%3)*220,scroll->getMapSize().height-130-(i/3)*250));
        scroll->addChild(unitCard);
        i++;
    }
    
    MyMenuItem* zhengbing = MyMenuItem::create(CCSprite::createWithSpriteFrameName("armyzhengbingcardback.png"), this, menu_selector(StartScene::toZhengbingCallBack));
    zhengbing->setPosition(ccp(387 + (i%3)*220,scroll->getMapSize().height-130-(i/3)*250+5));
    zhengbing->setScale(202/zhengbing->getContentSize().width);
    scroll->addChild(zhengbing);
    
    MyGameInfo::getInstance()->getOilAtlas()->removeFromParentAndCleanup(true);
    MyGameInfo::getInstance()->getIronAtlas()->removeFromParentAndCleanup(true);
    MyGameInfo::getInstance()->getGloryAtlas()->removeFromParentAndCleanup(true);
    MyGameInfo::getInstance()->getDiamondAtlas()->removeFromParentAndCleanup(true);
    
    
    
    
    armyLayer->setPosition(ccp(0,-back->getContentSize().height));
    //    armyLayer->setPosition(ccp(0,0));
    armyLayer->runAction(CCMoveTo::create(0.15, ccp(0,0)));
    //
    CCMenuItemSprite* totalItem = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("totalarmyP.png"), CCSprite::createWithSpriteFrameName("totalarmy.png"));
    totalItem->setAnchorPoint(ccp(1,0));
    //    totalItem->setPosition(ccp(263,493));
    totalItem->setPosition(ccp(0,493));
    totalItem->runAction(CCSequence::create(CCDelayTime::create(0.15),CCEaseBackOut::create(CCMoveTo::create(1, ccp(263,493))),NULL));
    
    
    CCMenuItemSprite* groundItem = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("groundarmyP.png"), CCSprite::createWithSpriteFrameName("groundarmy.png"));
    groundItem->setAnchorPoint(ccp(1,0));
    //    groundItem->setPosition(ccp(263,355));
    groundItem->setPosition(ccp(0,355));
    groundItem->runAction(CCSequence::create(CCDelayTime::create(0.25),CCEaseBackOut::create(CCMoveTo::create(1, ccp(263,355))),NULL));
    
    CCMenuItemSprite* armorItem = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("armorarmyP.png"), CCSprite::createWithSpriteFrameName("armorarmy.png"));
    armorItem->setAnchorPoint(ccp(1,0));
    //    armorItem->setPosition(ccp(263,215));
    armorItem->setPosition(ccp(0,215));
    armorItem->runAction(CCSequence::create(CCDelayTime::create(0.35),CCEaseBackOut::create(CCMoveTo::create(1, ccp(263,215))),NULL));
    
    CCMenuItemSprite* airItem = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("airarmyP.png"), CCSprite::createWithSpriteFrameName("airarmy.png"));
    airItem->setAnchorPoint(ccp(1,0));
    //    airItem->setPosition(ccp(263,70));
    airItem->setPosition(ccp(0,70));
    airItem->runAction(CCSequence::create(CCDelayTime::create(0.45),CCEaseBackOut::create(CCMoveTo::create(1, ccp(263,70))),NULL));
    
    GXRadioMenu* radio = GXRadioMenu::create(-502, totalItem,groundItem,armorItem,airItem,NULL);
    radio->setPosition(ccp(0,0));
    
    displayLayer->addChild(radio);
    radio->setTag(buduiMenuTag);
    
    
    CCMenuItemSprite* quitItem = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("quitarmy.png"), CCSprite::createWithSpriteFrameName("quitarmyP.png"),this,menu_selector( StartScene::quitCreator));
    quitItem->setContentSize(CCSizeMake(70, 70));
    
    
    
    GXShieldTouchMenuItem* shild = GXShieldTouchMenuItem::create();
    shild->setContentSize(winSize);
    shild->setPosition(ccp(0,0));
    shild->setAnchorPoint(ccp(0,0));
    
    MyPriorityMenu* menu = MyPriorityMenu::create(-500,quitItem,shild,NULL);
    menu->setPosition(ccp(0,0));
    
    quitItem->setPosition(ccp(winSize.width-61,winSize.height-24));
    //
    displayLayer->addChild(scroll);
    armyLayer->addChild(menu,2);
    
    
    
    MyGameInfo::getInstance()->getOilAtlas()->setPosition(ccp(44,605));
    MyGameInfo::getInstance()->getOilAtlas()->setScale(0.65);
    MyGameInfo::getInstance()->getIronAtlas()->setPosition(ccp(187,605));
    MyGameInfo::getInstance()->getIronAtlas()->setScale(0.65);
    MyGameInfo::getInstance()->getGloryAtlas()->setPosition(ccp(335,605));
    MyGameInfo::getInstance()->getGloryAtlas()->setScale(0.65);
    
    armyLayer->addChild(MyGameInfo::getInstance()->getOilAtlas());
    armyLayer->addChild(MyGameInfo::getInstance()->getIronAtlas());
    armyLayer->addChild(MyGameInfo::getInstance()->getGloryAtlas());
    armyLayer->setUserData(quitItem);
    
}

void StartScene::toZhengbingCallBack(cocos2d::CCMenuItem *pSender) {
    CCLayer* zhengbingLayer = CCLayer::create();
    zhengbingLayer->setTag(zhengBingLayerTag);
    if(dismissDisplayArmyLayer()) {
        CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sfx_popCreator.mp3");
        CCSprite* kuang = getArmyKuang();
        kuang->setPosition(ccp(5-kuang->getContentSize().width,590));
        kuang->runAction(CCEaseElasticOut::create(CCMoveTo::create(0.7, ccp(5,590)), 0.7));
        kuang->setTag(zhengbingkuangTag);
        CCSprite* infoBack = CCSprite::createWithSpriteFrameName("armyinfoback.png");
        infoBack->setPosition(ccp(960+infoBack->getContentSize().width,374));
        infoBack->runAction(CCEaseElasticOut::create(CCMoveTo::create(0.7, ccp(818,374)), 0.7));
        infoBack->setTag(zhengbingInfobackTag);
        
        CCLabelTTF* tip = CCLabelTTF::create("提示：\n点击征兵键开始征兵", "Arial", 26, CCSizeMake(220,350),kCCTextAlignmentLeft , kCCVerticalTextAlignmentTop);
        tip->setTag(zhengbingTipTag);
        tip->setAnchorPoint(ccp(0,1));
        tip->setPosition(ccp(15,infoBack->getContentSize().height-20));
        infoBack->addChild(tip);
        
        zhengbingLayer->addChild(kuang);
        zhengbingLayer->addChild(infoBack);
        MyPriorityMenu* menu = MyPriorityMenu::create(-502,NULL,NULL);
        for (int i=0; i<9; i++) {
            MyMenuItem* cardBack =MyMenuItem::create(CCSprite::createWithSpriteFrameName("armycardbeimian.png"),this, menu_selector(StartScene::flopArmycard));
            cardBack->setEnabled(false);
            cardBack->setPosition(ccp(225+(i%3)*165,446-(i/3)*152));
            menu->addChild(cardBack);
        }
        menu->setTag(zhengbingCardMenuTag);
        CCSprite* GRAY = CCSprite::createWithSpriteFrameName("armyzhengbingbutton.png");
        GRAY->setColor(ccGRAY);
        
        CCMenuItemSprite* zhengbingButton = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("armyzhengbingbutton.png"),CCSprite::createWithSpriteFrameName("armyzhengbingbuttonP.png"),GRAY,this,menu_selector(StartScene::zhengbingWaitServerCallBack));
        MyPriorityMenu* menu1 = MyPriorityMenu::create(-502, zhengbingButton,NULL);
        menu1->setPosition(ccp(960+infoBack->getContentSize().width,100));
        menu1->runAction(CCEaseElasticOut::create(CCMoveTo::create(0.7, ccp(808,100)), 0.7));
        menu1->setTag(zhengbingLingquMenuTag);
        
        zhengbingLayer->addChild(menu1);
        
        menu->setPosition(ccp(-kuang->getContentSize().width,0));
        menu->runAction(CCEaseElasticOut::create(CCMoveTo::create(0.7, ccp(0,0)), 0.7));
        
        zhengbingLayer->addChild(menu);
        this->getChildByTag(creatorLayerTag)->addChild(zhengbingLayer);
        
    } else {
        
        this->getChildByTag(resourceBarTag)->setVisible(false);
        CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sfx_army.mp3");
        
        CCLayer* armyLayer = CCLayer::create();
        CCSprite* back = CCSprite::createWithSpriteFrameName("armyback.png");
        back->setScale(960/back->getContentSize().width);
        back->setAnchorPoint(ccp(0,0));
        armyLayer->addChild(back);
        this->addChild(armyLayer);
        armyLayer->setTag(creatorLayerTag);
        armyLayer->setPosition(ccp(0,-back->getContentSize().height));
        armyLayer->runAction(CCMoveTo::create(0.15, ccp(0,0)));
        //半月牙
        CCSprite* banyue = CCSprite::createWithSpriteFrameName("banyuan.png");
        banyue->setScale(1.25);
        banyue->setAnchorPoint(ccp(0,0));
        banyue->setPosition(ccp(0,0));
        armyLayer->addChild(banyue,2);
        
        CCMenuItemSprite* quitItem = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("quitarmy.png"), CCSprite::createWithSpriteFrameName("quitarmyP.png"),this,menu_selector( StartScene::quitCreator));
        
        
        //退出与屏蔽
        GXShieldTouchMenuItem* shild = GXShieldTouchMenuItem::create();
        shild->setContentSize(winSize);
        shild->setPosition(ccp(0,0));
        shild->setAnchorPoint(ccp(0,0));
        
        MyPriorityMenu* menu2 = MyPriorityMenu::create(-500,quitItem,shild,NULL);
        menu2->setPosition(ccp(0,0));
        
        quitItem->setPosition(ccp(winSize.width-71,winSize.height-29));
        armyLayer->addChild(menu2,2);
        armyLayer->setUserData(quitItem);
        
        //更改资源点显示位置
        MyGameInfo::getInstance()->getOilAtlas()->removeFromParentAndCleanup(true);
        MyGameInfo::getInstance()->getIronAtlas()->removeFromParentAndCleanup(true);
        MyGameInfo::getInstance()->getGloryAtlas()->removeFromParentAndCleanup(true);
        MyGameInfo::getInstance()->getDiamondAtlas()->removeFromParentAndCleanup(true);
        
        MyGameInfo::getInstance()->getOilAtlas()->setPosition(ccp(44,605));
        MyGameInfo::getInstance()->getOilAtlas()->setScale(0.65);
        MyGameInfo::getInstance()->getIronAtlas()->setPosition(ccp(187,605));
        MyGameInfo::getInstance()->getOilAtlas()->setScale(0.65);
        MyGameInfo::getInstance()->getGloryAtlas()->setPosition(ccp(335,605));
        MyGameInfo::getInstance()->getGloryAtlas()->setScale(0.65);
        
        armyLayer->addChild(MyGameInfo::getInstance()->getOilAtlas());
        armyLayer->addChild(MyGameInfo::getInstance()->getIronAtlas());
        armyLayer->addChild(MyGameInfo::getInstance()->getGloryAtlas());
        //征兵解界面
        CCSprite* kuang = getArmyKuang();
        kuang->setPosition(ccp(5,590));
        kuang->setTag(zhengbingkuangTag);
        CCSprite* infoBack = CCSprite::createWithSpriteFrameName("armyinfoback.png");
        infoBack->setPosition(ccp(818,374));
        infoBack->setTag(zhengbingInfobackTag);
        
        CCLabelTTF* tip = CCLabelTTF::create("提示：\n点击征兵键开始征兵", "Arial", 26, CCSizeMake(220,350),kCCTextAlignmentLeft , kCCVerticalTextAlignmentTop);
        tip->setTag(zhengbingTipTag);
        tip->setAnchorPoint(ccp(0,1));
        tip->setPosition(ccp(15,infoBack->getContentSize().height-20));
        infoBack->addChild(tip);
        
        zhengbingLayer->addChild(kuang);
        zhengbingLayer->addChild(infoBack);
        MyPriorityMenu* menu = MyPriorityMenu::create(-502,NULL,NULL);
        for (int i=0; i<9; i++) {
            MyMenuItem* cardBack =MyMenuItem::create(CCSprite::createWithSpriteFrameName("armycardbeimian.png"),this, menu_selector(StartScene::flopArmycard));
            cardBack->setEnabled(false);
            cardBack->setPosition(ccp(225+(i%3)*165,446-(i/3)*152));
            menu->addChild(cardBack);
        }
        menu->setTag(zhengbingCardMenuTag);
        CCSprite* GRAY = CCSprite::createWithSpriteFrameName("armyzhengbingbutton.png");
        GRAY->setColor(ccGRAY);
        
        CCMenuItemSprite* zhengbingButton = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("armyzhengbingbutton.png"),CCSprite::createWithSpriteFrameName("armyzhengbingbuttonP.png"),GRAY,this,menu_selector(StartScene::zhengbingWaitServerCallBack));
        MyPriorityMenu* menu1 = MyPriorityMenu::create(-502, zhengbingButton,NULL);
        menu1->setPosition(ccp(808,100));
        menu1->setTag(zhengbingLingquMenuTag);
        zhengbingLayer->addChild(menu1);
        menu->setPosition(ccp(0,0));
        
        zhengbingLayer->addChild(menu);
        armyLayer->addChild(zhengbingLayer);
    }
}

void StartScene::zhengbingWaitServerCallBack(cocos2d::CCMenuItem *pSender) {
    pSender->setVisible(false);
    ((CCMenuItem*)this->getChildByTag(creatorLayerTag)->getUserData())->setEnabled(false);
    if (MyGameInfo::getInstance()->getGlory() < MyUtil::getInstance()->getSummaryGloryByFlopTime(0)) {
        this->addChild(MyUtil::getInstance()->getNoGloryDialog());
        return;
    }
    
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sfx_click.mp3");
    this->addChild(MyUtil::getInstance()->getWaitLayer("努力加载中"),99);
    pSender->runAction(CCSequence::create(CCDelayTime::create(0.2),CCCallFuncO::create(this, callfuncO_selector(StartScene::zhengbingCallBack), pSender),NULL));
}

void StartScene::zhengbingCallBack(cocos2d::CCMenuItem *pSender) {
    //    CCString* jsonStr = MyHttpConnection::getInstance()->getConscrbeList();
    CCString* jsonStr = CCString::create("");
    if (jsonStr == NULL || (jsonStr->compare("failed") == 0) || (jsonStr->compare("") == 0)) {
        this->addChild(MyUtil::getInstance()->getNetworkDialog(),99);
        this->removeChildByTag(creatorLayerTag, true);
        return;
    }
    CCArray* conscribBeans = MyJsonUtil::parseConscribeList(jsonStr);
    
    pSender->setVisible(false);
    this->removeWaitMenu();
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sfx_card.mp3");
    CCMenu* menu = (CCMenu*)this->getChildByTag(creatorLayerTag)->getChildByTag(zhengBingLayerTag)->getChildByTag(zhengbingCardMenuTag);
    menu->setUserObject(conscribBeans);
    int count = menu->getChildrenCount();
    int i = 0;
    for (i = 0; i<count-1; i++) {
        MyMenuItem* item = (MyMenuItem*)(menu->getChildren()->objectAtIndex(i));
        item->setUserData(conscribBeans->objectAtIndex(i));
        item->getImage()->runAction(CCSequence::create(GXUtil::flipFX(false),CCCallFuncO::create(this, callfuncO_selector(StartScene::displayCardInfo), item),CCDelayTime::create(3+i*0.1),CCCallFuncO::create(this, callfuncO_selector(StartScene::dismissCardInfo), item),GXUtil::flipFX(true),NULL));
        item->runAction(CCSequence::create(CCDelayTime::create(4.5+i*0.1),CCEaseInOut::create(CCMoveTo::create(0.5, ccp(390-5+i*2,294-5+i*2)), 3),NULL));
    }
    MyMenuItem* item = (MyMenuItem*)(menu->getChildren()->lastObject());
    item->setUserData(conscribBeans->objectAtIndex(8));
    item->getImage()->runAction(CCSequence::create(GXUtil::flipFX(false),CCCallFuncO::create(this, callfuncO_selector(StartScene::displayCardInfo), item),CCDelayTime::create(3+i*0.1),CCCallFuncO::create(this, callfuncO_selector(StartScene::dismissCardInfo), item),GXUtil::flipFX(true),NULL));
    item->runAction(CCSequence::create(CCDelayTime::create(4.5+i*0.1),CCEaseInOut::create(CCMoveTo::create(0.5, ccp(390-5+i*2,294-5+i*2)), 3),CCCallFuncND::create(this, callfuncND_selector(StartScene::armyUpCard), (void*)menu),NULL));
    ((CCLabelTTF*)this->getChildByTag(creatorLayerTag)->getChildByTag(zhengBingLayerTag)->getChildByTag(zhengbingInfobackTag)->getChildByTag(zhengbingTipTag))->setString("提示:\n等待系统洗牌中...");
    
}

void StartScene::displayCardInfo(cocos2d::CCMenuItem *pSender) {
    //    ConscribeInfoBean* bean = (ConscribeInfoBean*)pSender->getUserData();
    //    MyMenuItem* item = (MyMenuItem*)pSender;
    //    char str[32] = {0};
    //    UnitBean* creator = (UnitCreator*)MyGameFactory::createCreatorbyJsonScriptFile(bean->getJsonName()->getCString(), unitCreatorClassTag);
    //    sprintf(str, "%sbp.png",creator->getSpriteFileName());
    //    CCSprite* unitSprite = CCSprite::createWithSpriteFrameName(str);
    ////    210*0.6=126, 246 148
    //    unitSprite->setPosition(ccp(63,148-63+18));
    //    unitSprite->setScale(Mathlib::min(108/unitSprite->getContentSize().width, 78/unitSprite->getContentSize().height));
    //    unitSprite->setTag(unitSpriteTag);
    //    //    unitSprite->setAnchorPoint(ccp(0,0));
    //    CCSprite* lightSprite = CCSprite::createWithSpriteFrameName("creatorLight.png");
    //    lightSprite->setScale(0.48);
    //    lightSprite->setOpacity(153+18);
    //    //    lightSprite->setAnchorPoint(ccp(0,0));
    //    lightSprite->setPosition(ccp(63,148-63+18));
    //    //    buildingSprite->setScale((itemImage->getContentSize().width-transWindowToGLInRetina(20))/buildingSprite->getContentSize().width);
    //
    //    CCLabelTTF* nameLabel = CCLabelTTF::create(creator->getName(), "Arial", 13);
    //    nameLabel->setPosition(ccp(80,150));
    //    nameLabel->setAnchorPoint(ccp(0.5,0.5));
    //    nameLabel->setColor(ccWHITE);
    //
    //
    //    sprintf(str,"No.%d", creator->cardId);
    //
    //    CCLabelTTF* idLabel = CCLabelTTF::create(str, "Arial", 11);
    //    idLabel->setPosition(ccp(6,139+18));
    //    idLabel->setAnchorPoint(ccp(0,0.5));
    //    idLabel->setColor(ccBLACK);
    //
    //    sprintf(str,"Lv:%d", bean->level);
    //
    //    CCLabelTTF* levelLabel = CCLabelTTF::create(str, "Arial", 15);
    //    levelLabel->setPosition(ccp(6,48));
    //    levelLabel->setAnchorPoint(ccp(0,0));
    //    levelLabel->setColor(ccWHITE);
    ////    levelLabel->setTag(lvFontTag);
    //    if (creator->getRarity()>2) {
    //        CCSprite* bling1_1 = CCSprite::create("armyprizeLight.png");
    //        bling1_1->setTag(bling1Tag);
    //        //    bling1_1->setScale(0);
    //        bling1_1->setPosition(ccp(item->getImage()->getContentSize().width/2,item->getImage()->getContentSize().height/2));
    //        bling1_1->runAction(CCRotateBy::create(1000, 7200));
    //        bling1_1->runAction(CCScaleTo::create(1,1.3));
    //        item->addChild(bling1_1,-1);
    //    }
    //    if (creator->getRarity()>4) {
    //        CCSprite* bling1_2 = CCSprite::create("armyprizeLight.png");
    //        bling1_2->setTag(bling2Tag);
    //        bling1_2->setPosition(ccp(item->getImage()->getContentSize().width/2,item->getImage()->getContentSize().height/2));
    //        bling1_2->runAction(CCRotateBy::create(1000, -7200));
    //        bling1_2->setScale(0.5);
    //        bling1_2->runAction(CCSequence::create(CCDelayTime::create(1), CCScaleTo::create(1,1.2),NULL));
    //        item->addChild(bling1_2,-1);
    //    }
    //
    //
    //    item->getImage()->addChild(lightSprite,1);
    //    item->getImage()->addChild(unitSprite,3);
    //     item->getImage()->addChild(idLabel,2);
    //     item->getImage()->addChild(nameLabel,2);
    //     item->getImage()->addChild(levelLabel,2);
    //
    //    float posi = (creator->getRarity()-1)*18;
    //    for (int i = 0; i<creator->getRarity(); i++) {
    //        CCSprite* star = CCSprite::createWithSpriteFrameName("armystar.png");
    //        star->setPosition(ccp(63-posi/2 + i*18,42));
    //        star->setScale(0.6);
    //        item->getImage()->addChild(star);
    //    }
}

void StartScene::dismissCardInfo(cocos2d::CCMenuItem *pSender) {
    MyMenuItem* item = (MyMenuItem*)pSender;
    item->getImage()->removeAllChildrenWithCleanup(true);
    if (item->getChildByTag(bling1Tag)) {
        item->getChildByTag(bling1Tag)->runAction(CCSequence::create(CCFadeOut::create(1.4),GXRemoveFromParentsAction::create(),NULL));
    }
    
    if (item->getChildByTag(bling2Tag)) {
        item->getChildByTag(bling2Tag)->runAction(CCSequence::create(CCFadeOut::create(1.4),GXRemoveFromParentsAction::create(),NULL));
    }
}

void StartScene::armyUpCard(CCMenuItem* pSender, CCMenu* menu) {
    CCMenuItem* item1 = (CCMenuItem*)menu->getChildren()->lastObject();
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sfx_card.mp3");
    if (item1->getZOrder() > -90) {
        item1->runAction(CCSequence::create(CCEaseInOut::create(CCMoveBy::create(0.1,ccp(0,150)), 4),CCCallFuncND::create(this, callfuncND_selector(StartScene::armydowncard), (void*)menu),NULL));
    } else {
        CCObject* obj=NULL;
        int i = 0;
        CCARRAY_FOREACH(menu->getChildren(), obj) {
            MyMenuItem* item = (MyMenuItem*)(obj);
            item->setEnabled(true);
            item->runAction(CCSequence::create(CCDelayTime::create(0.5+i*0.1),CCEaseInOut::create(CCEaseInOut::create(CCMoveTo::create(0.5, ccp(225+(i%3)*165,446-(i/3)*152)), 3), 4) ,NULL));
            i++;
        }
        CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sfx_card.mp3");
        //        tip->setPosition(ccp(810,368));
        CCLayer* layer = (CCLayer*)menu->getParent()->getChildByTag(zhengbingInfobackTag);
        ((CCLabelTTF*)layer->getChildByTag(zhengbingTipTag))->setString("提示：\n点击左边兵牌抽取兵种");
        CCLabelTTF* label = CCLabelTTF::create("本次抽兵-100", "Arail", 25, CCSizeMake(200,25), kCCTextAlignmentRight, kCCVerticalTextAlignmentTop);
        
        label->setTag(zhengbingInfobackSummaryLabelTag);
        layer->addChild(label);
        label->setColor(ccc3(255, 246, 0));
        label->setPosition(ccp(-100,365));
        label->setAnchorPoint(ccp(1,0.5));
        CCSprite* gloryIcon = CCSprite::createWithSpriteFrameName("honorIcon.png");
        gloryIcon->setPosition(ccp(215,13));
        label->addChild(gloryIcon);
        
    }
    
}

void StartScene::armydowncard(CCMenuItem* pSender, CCMenu* menu) {
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sfx_card.mp3");
    menu->reorderChild(pSender, -90);
    pSender->runAction(CCSequence::create(CCEaseInOut::create(CCMoveBy::create(0.1,ccp(0,-150)), 4),CCCallFuncND::create(this, callfuncND_selector(StartScene::armyUpCard), (void*)menu),NULL));
    
}

void StartScene::flopArmycard(CCMenuItem* pSender) {
    CCArray* conscribeArray = (CCArray*)pSender->getParent()->getUserObject();
    int time = 9-conscribeArray->count();
    if (MyGameInfo::getInstance()->getGlory() < MyUtil::getInstance()->getSummaryGloryByFlopTime(time)) {
        CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sfx_error.wav");
        return;
    }
    char str[50] = {0};
    sprintf(str, "本次消耗-%d",(int)MyUtil::getInstance()->getSummaryGloryByFlopTime(time+1));
    ((CCLabelTTF*) pSender->getParent()->getParent()->getChildByTag(zhengbingInfobackTag)->getChildByTag(zhengbingInfobackSummaryLabelTag))->setString(str);
    pSender->getParent()->getParent()->addChild( MyGameInfo::getInstance()->changeResourceAndFloatText(gloryTag, -MyUtil::getInstance()->getSummaryGloryByFlopTime(time), pSender->getPosition()));
    
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sfx_card.mp3");
    MyMenuItem* item = (MyMenuItem*)pSender;
    item->setEnabled(false);
    
    ConscribeInfoBean* bean = MyUtil::getInstance()->cardLottery(conscribeArray);
    item->setUserData(bean);
    CCMenu* menu1 = (CCMenu*)item->getParent()->getParent()->getChildByTag(zhengbingLingquMenuTag);
    menu1->removeAllChildrenWithCleanup(true);
    CCMenuItemSprite* lingqu1 = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("armyzhengbinglingqubutton.png"), CCSprite::createWithSpriteFrameName("armyzhengbinglingqubuttonP.png"),this,menu_selector(StartScene::displayOtherCard));
    menu1->addChild(lingqu1);
    CCArray* achieveArray = (CCArray*)menu1->getUserObject();
    if (!achieveArray) {
        achieveArray = CCArray::create();
        menu1->setUserObject(achieveArray);
    }
    
    achieveArray->addObject(item);
    
    
    
    if (achieveArray->count() < 4) {
        item->getImage()->runAction(CCSequence::create(GXUtil::flipFX(false),CCCallFuncO::create(this, callfuncO_selector(StartScene::displayCardInfo), item),NULL));
        //12 为已添加TAG
        item->setTag(12);
    } else {
        lingqu1->setEnabled(false);
        this->getChildByTag(creatorLayerTag)->getChildByTag(zhengBingLayerTag)->getChildByTag(zhengbingInfobackTag)->removeChildByTag(zhengbingInfobackSummaryLabelTag, true);
        ((CCMenu*)item->getParent())->setEnabled(false);
        item->getImage()->runAction(CCSequence::create( GXUtil::flipFX(false) ,CCCallFuncO::create(this, callfuncO_selector(StartScene::displayCardInfo), item),CCDelayTime::create(2.5),CCCallFunc::create(this, callfunc_selector(StartScene::archieveArmy)),NULL));
        item->setTag(12);
        CCArray* other = item->getParent()->getChildren();
        CCObject* obj;
        int i=0;
        CCARRAY_FOREACH(other, obj) {
            MyMenuItem* node = (MyMenuItem*) obj;
            if (node->getTag() != 12) {
                node->setUserData(conscribeArray->objectAtIndex(i));
                node->getImage()->runAction(CCSequence::create(CCDelayTime::create(0.8),GXUtil::flipFX(false),CCCallFuncO::create(this, callfuncO_selector(StartScene::displayCardInfo), node),NULL));
                i++;
            }
        }
    }
}

bool StartScene::dismissDisplayArmyLayer() {
    if ((CCLayer*)this->getChildByTag(creatorLayerTag) ==NULL) {
        return false;
    }
    CCLayer* layer = (CCLayer*)this->getChildByTag(creatorLayerTag)->getChildByTag(displayBuduiLayerTag);
    if(layer != NULL) {
        layer->getChildByTag(buduiMenuTag)->runAction(CCEaseElasticIn::create(CCMoveTo::create(1, ccp(-300,0)), 0.9));
        GXScrollView* scroll =  ((GXScrollView*)layer->getChildByTag(buduiScrollTag));
        scroll->runAction(CCEaseElasticIn::create(CCMoveTo::create(1, ccp(1500,scroll->getPosition().y)), 0.9));
        scroll->setEnabled(false);
        layer->runAction(CCSequence::create(CCDelayTime::create(2.5),GXRemoveFromParentsAction::create(),NULL));
        //        scroll->setOriPosition(ccp(285,60));
        //        scroll->setContentSize(CCSizeMake(648, 505));
        return true;
    }
    return false;
}

void StartScene::displayOtherCard(CCMenuItem* pSender) {
    pSender->setEnabled(false);
    CCMenu* cardMenu = (CCMenu*)this->getChildByTag(creatorLayerTag)->getChildByTag(zhengBingLayerTag)->getChildByTag(zhengbingCardMenuTag);
    
    cardMenu->setEnabled(false);
    CCArray* other = cardMenu->getChildren();
    CCArray* conscribeArray = (CCArray*)cardMenu->getUserObject();
    CCObject* obj;
    int i=0;
    bool flag = true;
    CCARRAY_FOREACH(other, obj) {
        MyMenuItem* node = (MyMenuItem*) obj;
        if (node->getTag() != 12) {
            if (flag ==true) {
                node->setUserData(conscribeArray->objectAtIndex(i));
                node->getImage()->runAction(CCSequence::create(GXUtil::flipFX(false),CCCallFuncO::create(this, callfuncO_selector(StartScene::displayCardInfo), node),CCDelayTime::create(1.7),CCCallFunc::create(this, callfunc_selector(StartScene::archieveArmy)),NULL));
                flag = false;
            } else {
                node->setUserData(conscribeArray->objectAtIndex(i));
                node->getImage()->runAction(CCSequence::create(GXUtil::flipFX(false),CCCallFuncO::create(this, callfuncO_selector(StartScene::displayCardInfo), node),CCDelayTime::create(1.7),NULL));
            }
            i++;
        }
    }
    
}

void StartScene::archieveArmy() {
    //    this->getChildByTag(creatorLayerTag)->getChildByTag(zhengBingLayerTag)->getChildByTag(zhengbingInfobackTag)->removeChildByTag(zhengbingInfobackSummaryLabelTag, true);
    //    CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sfx_win.mp3");
    //
    //    CCMenu* menu = (CCMenu*)this->getChildByTag(creatorLayerTag)->getChildByTag(zhengBingLayerTag)->getChildByTag(zhengbingLingquMenuTag);
    //    CCMenu* menu1 = (CCMenu*)this->getChildByTag(creatorLayerTag)->getChildByTag(zhengBingLayerTag)->getChildByTag(zhengbingCardMenuTag);
    //    menu1->setEnabled(false);
    //    menu->setEnabled(false);
    //
    //
    //    CCSprite* infoBack = (CCSprite*)this->getChildByTag(creatorLayerTag)->getChildByTag(zhengBingLayerTag)->getChildByTag(zhengbingInfobackTag);
    //    infoBack->runAction(CCEaseElasticIn::create(CCMoveTo::create(1, ccp(960+infoBack->getContentSize().width,374)), 1));
    //
    //
    //    CCSprite* kuang = (CCSprite*)this->getChildByTag(creatorLayerTag)->getChildByTag(zhengBingLayerTag)->getChildByTag(zhengbingkuangTag);
    //    kuang->runAction(CCEaseElasticIn::create(CCMoveTo::create(0.7, ccp(5-kuang->getContentSize().width,590)), 0.7));
    //
    //    menu->runAction(CCEaseElasticIn::create(CCMoveTo::create(0.7, ccp(960+infoBack->getContentSize().width,100)), 0.7));
    //    menu1->runAction(CCEaseElasticIn::create(CCMoveTo::create(0.7, ccp(-kuang->getContentSize().width,0)), 0.7));
    //
    //
    //    CCLayer* achieveLayer =CCLayer::create();
    //    achieveLayer->setPosition(ccp(0,0));
    //    achieveLayer->setTag(lingquLayerTag);
    //
    //    CCMenuItemSprite* returnbutton = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("armyzhengbingreturnbutton.png"),CCSprite::createWithSpriteFrameName("armyzhengbingreturnbuttonP.png"),this,menu_selector(StartScene::zhengbingtoBudui));
    //
    //
    //    MyPriorityMenu* returnMenu = MyPriorityMenu::create(-502, returnbutton,NULL);
    //    returnMenu->setPosition(ccp(winSize.width/2,-returnMenu->getContentSize().height/2));
    //    returnMenu->runAction(CCEaseElasticOut::create(CCMoveTo::create(0.8, ccp(winSize.width/2,100)), 0.8));
    //    achieveLayer->addChild(returnMenu);
    //
    //    CCArray* array = (CCArray*)menu->getUserObject();
    //    int i=0;
    //    CCObject* obj = NULL;
    //    int count  = Mathlib::min(array->count(),4);
    //    float posi = (count-1)*250;
    //    CCARRAY_FOREACH(array, obj) {
    //        CCMenuItem* item = (CCMenuItem*)obj;
    //        item->removeFromParentAndCleanup(false);
    //        achieveLayer->addChild(item,i);
    //        item->runAction(CCMoveTo::create(1, ccp(480-posi/2+i*250,320)));
    //        item->runAction(CCScaleTo::create(1, 210/item->getContentSize().width));
    //        i++;
    //        ConscribeInfoBean* bean = (ConscribeInfoBean*)item->getUserData();
    //        CreatorInfoBean* creatorBean = CreatorInfoBean::create(CCString::create(bean->getJsonName()->getCString()));
    //        MyGameInfo::getInstance()->creatorArray->addObject(creatorBean);
    //        item->setUserData(creatorBean);
    //        bean->release();
    //    }
    //    this->getChildByTag(creatorLayerTag)->addChild(achieveLayer,4);
    //    ((CCMenuItem*)this->getChildByTag(creatorLayerTag)->getUserData())->setEnabled(true);
    //    returnbutton->setUserObject(array);
}

void StartScene::zhengbingtoBudui(CCMenuItem* pSender) {
    pSender->setEnabled(false);
    pSender->runAction(CCEaseElasticIn::create(CCMoveTo::create(0.8, ccp(0,-240)), 0.6));
    CCArray* newCreatorArray  = (CCArray*)pSender->getUserObject();
    
    int j = 0;
    int newCreatorArrayCount = newCreatorArray->count();
    for (j = 0; j<newCreatorArrayCount; j++) {
        MyMenuItem* item = (MyMenuItem*) newCreatorArray->objectAtIndex(j);
        int a = newCreatorArrayCount-1-j;
        if (j == 0 ) {
            item->runAction( CCSequence::create(CCDelayTime::create(0.8),CCEaseElasticOut::create(CCMoveTo::create(0.7, ccp(387+(a%3)*220,440-(a/3)*250)), 0.7),CCCallFuncND::create(this, callfuncND_selector(StartScene::displayNewArmyFromZhengbing),(void*)item),NULL));
        } else {
            item->runAction( CCSequence::create(CCDelayTime::create(0.8),CCEaseElasticOut::create(CCMoveTo::create(0.7, ccp(387+(a%3)*220,440-(a/3)*250)), 0.7),NULL));
        }
        
        if (item->getChildByTag(bling1Tag)) {
            item->getChildByTag(bling1Tag)->runAction(CCFadeOut::create(1.4));
        }
        
        if (item->getChildByTag(bling2Tag)) {
            item->getChildByTag(bling2Tag)->runAction(CCFadeOut::create(1.4));
        }
        
        //TODO 把新兵牌设置为USERDATA
    }
    
    
    //    newCreatorArray->release();
    
    CCLayer* armyLayer = (CCLayer*)this->getChildByTag(creatorLayerTag);
    
    CCLayer* displayLayer = CCLayer::create();
    displayLayer->setTag(displayBuduiLayerTag);
    displayLayer->setPosition(ccp(0,0));
    armyLayer->addChild(displayLayer,3);
    
    CCSprite* banyue = CCSprite::createWithSpriteFrameName("banyuan.png");
    banyue->setScale(1.25);
    banyue->setAnchorPoint(ccp(0,0));
    banyue->setPosition(ccp(-banyue->getContentSize().width,0));
    armyLayer->addChild(banyue,2);
    banyue->runAction(CCSequence::create(CCDelayTime::create(0.15),CCEaseBackOut::create(CCMoveTo::create(0.5, ccp(0,0))),NULL));
    
    
    
    
    GXScrollView* scroll = GXScrollView::create(-501);
    scroll->setTag(buduiScrollTag);
    //    CCSprite* test = CCSprite::create("loading.jpg");
    //    test->setAnchorPoint(ccp(0,0));
    //    scroll->addChild(test);
    scroll->setOriPosition(ccp(0,60));
    scroll->setContentSize(CCSizeMake(960, 505));
    CCArray* array = MyGameInfo::getInstance()->creatorArray;
    
    char str[30] = {0};
    int i=0;
    if (array->count() > 6) {
        scroll->setMapSize(CCSizeMake(960, 250*(array->count()/3+1)));
        scroll->setPosition(ccp(scroll->getOriPosition().x,-scroll->getMapSize().height+scroll->getOriPosition().y));
    }
    scroll->setEnabled(false);
    scroll->runAction(CCEaseElasticOut::create(CCMoveTo::create(1, ccp(scroll->getOriPosition().x,-scroll->getMapSize().height+scroll->getViewSize().height+scroll->getOriPosition().y)), 0.7));
    //    scroll->setPosition(ccp(scroll->getOriPosition().x,-scroll->getMapSize().height+scroll->getViewSize().height+scroll->getOriPosition().y));
    CCObject* obj;
    CCObject* obj1;
    CCARRAY_FOREACH_REVERSE(array, obj) {
        CreatorInfoBean* bean = ((CreatorInfoBean*)obj);
        sprintf(str, "%sbp.png",bean->creator->getSpriteFileName());
        MyUnitCard* unitCard = MyUnitCard::create(bean,this,menu_selector(StartScene::toArmyInfoInfo));
        unitCard->setPosition(ccp(387 + (i%3)*220,scroll->getMapSize().height-130-(i/3)*250));
        scroll->addChild(unitCard);
        
        CCARRAY_FOREACH(newCreatorArray, obj1) {
            CCMenuItem* item = ((CCMenuItem*)obj1);
            if (item->getUserData() == bean) {
                unitCard->setVisible(false);
                item->setUserObject(unitCard);
                newCreatorArray->removeObject(item);
                break;
            }
        }
        
        i++;
    }
    
    MyMenuItem* zhengbing = MyMenuItem::create(CCSprite::createWithSpriteFrameName("armyzhengbingcardback.png"), this, menu_selector(StartScene::toZhengbingCallBack));
    zhengbing->setPosition(ccp(387 + (i%3)*220,scroll->getMapSize().height-130-(i/3)*250+5));
    zhengbing->setScale(202/zhengbing->getContentSize().width);
    scroll->addChild(zhengbing);
    
    
    
    CCMenuItemSprite* totalItem = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("totalarmyP.png"), CCSprite::createWithSpriteFrameName("totalarmy.png"));
    totalItem->setAnchorPoint(ccp(1,0));
    //    totalItem->setPosition(ccp(263,493));
    totalItem->setPosition(ccp(0,493));
    totalItem->runAction(CCSequence::create(CCDelayTime::create(0.15),CCEaseBackOut::create(CCMoveTo::create(1, ccp(263,493))),NULL));
    
    
    CCMenuItemSprite* groundItem = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("groundarmyP.png"), CCSprite::createWithSpriteFrameName("groundarmy.png"));
    groundItem->setAnchorPoint(ccp(1,0));
    //    groundItem->setPosition(ccp(263,355));
    groundItem->setPosition(ccp(0,355));
    groundItem->runAction(CCSequence::create(CCDelayTime::create(0.25),CCEaseBackOut::create(CCMoveTo::create(1, ccp(263,355))),NULL));
    
    CCMenuItemSprite* armorItem = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("armorarmyP.png"), CCSprite::createWithSpriteFrameName("armorarmy.png"));
    armorItem->setAnchorPoint(ccp(1,0));
    //    armorItem->setPosition(ccp(263,215));
    armorItem->setPosition(ccp(0,215));
    armorItem->runAction(CCSequence::create(CCDelayTime::create(0.35),CCEaseBackOut::create(CCMoveTo::create(1, ccp(263,215))),NULL));
    
    CCMenuItemSprite* airItem = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("airarmyP.png"), CCSprite::createWithSpriteFrameName("airarmy.png"));
    airItem->setAnchorPoint(ccp(1,0));
    //    airItem->setPosition(ccp(263,70));
    airItem->setPosition(ccp(0,70));
    airItem->runAction(CCSequence::create(CCDelayTime::create(0.45),CCEaseBackOut::create(CCMoveTo::create(1, ccp(263,70))),NULL));
    
    GXRadioMenu* radio = GXRadioMenu::create(-502, totalItem,groundItem,armorItem,airItem,NULL);
    radio->setPosition(ccp(0,0));
    
    displayLayer->addChild(radio);
    radio->setTag(buduiMenuTag);
    
    
    displayLayer->addChild(scroll);
}

void StartScene::displayNewArmyFromZhengbing(CCNode* target,CCMenuItem* pSender) {
    
    ((GXScrollView*)this->getChildByTag(creatorLayerTag)->getChildByTag(displayBuduiLayerTag)->getChildByTag(buduiScrollTag))->setEnabled(true);
    //TODO 显示新兵牌
    CCLayer* lingquLayer = (CCLayer*) this->getChildByTag(creatorLayerTag)->getChildByTag(lingquLayerTag);
    CCObject* obj = NULL;
    CCARRAY_FOREACH(lingquLayer->getChildren(), obj) {
        CCNode* node = (CCNode*)obj;
        
        MyUnitCard* card = dynamic_cast<MyUnitCard*>(node->getUserObject());
        if (card) {
            card->setVisible(true);
        }
    }
    pSender->removeFromParentAndCleanup(true);
    lingquLayer->removeFromParentAndCleanup(true);
    this->getChildByTag(creatorLayerTag)->removeChildByTag(zhengBingLayerTag, true);
}

void StartScene::toArmyInfoInfo(cocos2d::CCMenuItem *pSender) {
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sfx_click.mp3");
    CCLayer* infoLayer = CCLayer::create();
    this->getChildByTag(creatorLayerTag)->addChild(infoLayer,3);
    infoLayer->setTag(armyInfoLayerTag);
    infoLayer->setUserData(pSender);
    infoLayer->setPosition(ccp(0,0));
    pSender->retain();
    GXScrollView* scroll = (GXScrollView*)this->getChildByTag(creatorLayerTag)->getChildByTag(displayBuduiLayerTag)->getChildByTag(buduiScrollTag);
    CCPoint pos = ccp(pSender->getPosition().x+scroll->getPosition().x,pSender->getPosition().y+scroll->getPosition().y);
    pSender->setPosition(pos);
    pSender->removeFromParentAndCleanup(true);
    infoLayer->addChild(pSender,2);
    pSender->runAction(CCSequence::create(CCEaseBackInOut::create(CCMoveTo::create(1, ccp(120,444))),CCCallFuncO::create(this, callfuncO_selector(StartScene::toRunInfoAction), pSender) ,NULL));
    pSender->runAction(CCEaseBackInOut::create(CCScaleTo::create(1,1.2)));
    pSender->runAction(CCSequence::create(CCDelayTime::create(0.4),CCCallFunc::create(this, callfunc_selector(StartScene::dismissDisplayArmyLayer)),NULL));
    pSender->release();
    //    dismissDisplayArmyLayer();
}

void StartScene::toRunInfoAction(cocos2d::CCMenuItem *pSender) {
    CCMenuItemSprite* infoinfoButton = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("armyinfobuttonP.png"), CCSprite::createWithSpriteFrameName("armyinfobutton.png"),this,menu_selector(StartScene::toInfoInfoCallBack));
    CCMenuItemSprite* infoStrenthenButton = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("armyinfostrenthenbuttonP.png"), CCSprite::createWithSpriteFrameName("armyinfostrenthenbutton.png"),this,menu_selector(StartScene::toInfoStrenthenCallBackSimple));
    infoinfoButton->setScale(1.1);
    infoStrenthenButton->setScale(1.1);
    infoinfoButton->setPosition(ccp(132,438));
    infoStrenthenButton->setPosition(ccp(132,438));
    
    
    
    
    GXRadioMenu* radioMenu = GXRadioMenu::create(-505,infoinfoButton,infoStrenthenButton,NULL);
    radioMenu->setTag(armyInfoRadioMenuTag);
    
    radioMenu->setPosition(ccp(0,0));
    infoinfoButton->runAction(CCSequence::create(CCDelayTime::create(0.4),CCEaseElasticOut::create(CCMoveTo::create(0.8, ccp(132,238)), 0.7),NULL));
    infoStrenthenButton->runAction(CCSequence::create(CCDelayTime::create(0.4),CCEaseElasticOut::create(CCMoveTo::create(1.049, ccp(132,110)), 0.7),NULL));
    
    
    
    this->getChildByTag(creatorLayerTag)->getChildByTag(armyInfoLayerTag)->addChild(radioMenu);
    
    CCSprite* kuang = getArmyKuang();
    kuang->setScaleX((winSize.width-246)/kuang->getContentSize().width);
    kuang->setPosition(ccp(winSize.width+kuang->getContentSize().width,580));
    kuang->runAction(CCSequence::create(CCDelayTime::create(0.4),CCEaseElasticOut::create(CCMoveTo::create(1, ccp(232,580)), 0.7),NULL));
    this->getChildByTag(creatorLayerTag)->getChildByTag(armyInfoLayerTag)->addChild(kuang);
    
    CCMenuItemSprite* returnButton = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("armyreturnbutton.png"), CCSprite::createWithSpriteFrameName("armyreturnbuttonP.png"),this,menu_selector(StartScene::toArmyCallBackSimple));
    returnButton->setPosition(ccp(winSize.width+60,winSize.height));
    returnButton->setAnchorPoint(ccp(0.5,1));
    returnButton->setScale(1.25);
    returnButton->runAction(CCSequence::create(CCDelayTime::create(0.5),CCEaseElasticOut::create(CCMoveTo::create(0.9, ccp(winSize.width-170,winSize.height)), 0.7),NULL));
    MyPriorityMenu* menu = MyPriorityMenu::create(-502,returnButton,NULL);
    menu->setPosition(ccp(0,0));
    this->getChildByTag(creatorLayerTag)->getChildByTag(armyInfoLayerTag)->addChild(menu,-1);
}

void StartScene::toInfoInfoCallBack() {
    this->getChildByTag(creatorLayerTag)->getChildByTag(armyInfoLayerTag)->removeChildByTag(armyInfoInfoLayerTag,true);
    
    MyUnitCard* mainCard = (MyUnitCard*)this->getChildByTag(creatorLayerTag)->getChildByTag(armyInfoLayerTag)->getUserData();
    
    CCLayer* infoinfoLayer = mainCard->bean->getUnitCardDesc(true);
    infoinfoLayer->setPosition(ccp(winSize.width+638,100));
    infoinfoLayer->runAction(CCSequence::create(CCDelayTime::create(0.4),CCEaseElasticOut::create(CCMoveTo::create(1, ccp(winSize.width/2-180,100)), 0.7),NULL));
    
    infoinfoLayer->setTag(armyInfoInfoLayerTag);
    this->getChildByTag(creatorLayerTag)->getChildByTag(armyInfoLayerTag)->addChild(infoinfoLayer);
}

#define  strenthenHonorCost MyUtil::getInstance()->updateLevelByRate(0,50*rarity/2,mainCard->bean->getLevel()+1,rarity/2)

#define strenthenIronCost MyUtil::getInstance()->updateLevelByRate(0,1000*rarity/2,mainCard->bean->getLevel()+1,rarity)

#define strenthenDiamondCost MyUtil::getInstance()->updateLevelByCount(50,mainCard->bean->getLevel()+1,50)

void StartScene::toInfoStrenthenCallBackSimple() {
    this->getChildByTag(creatorLayerTag)->getChildByTag(armyInfoLayerTag)->removeChildByTag(armyInfoInfoLayerTag,true);
    
    MyUnitCard* mainCard = (MyUnitCard*)this->getChildByTag(creatorLayerTag)->getChildByTag(armyInfoLayerTag)->getUserData();
    
    CCLayer* infoinfolayer = CCLayer::create();
    infoinfolayer->setPosition(ccp(0,0));
    
    
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sfx_click.mp3");
    infoinfolayer->setTag(armyInfoInfoLayerTag);
    
    
    MyPriorityMenu* menu = MyPriorityMenu::create(-505,NULL,NULL);
    menu->setPosition(ccp(0,0));
    menu->setTag(armyInfoInfoLayerMenuTag);
    
    CCLayer* infoinfoStrenthenLayer = CCLayer::create();
    infoinfoStrenthenLayer->setPosition(ccp(0,0));
    infoinfoStrenthenLayer->setTag(armyInfoInfoStrenthenInfoLayerTag);
    
    
    
    //    CCLabelTTF* levelTipLabel = CCLabelTTF::create("等 级：", "Arial", 24);
    //    levelTipLabel->setColor(ccc3(238,204,122));
    //    levelTipLabel->setAnchorPoint(ccp(0,0.5));
    //    levelTipLabel->setPosition(ccp(450,341));
    
    
    
    char str[5] = {0};
    
    if (mainCard->bean->getLevel() >= mainCard->bean->creator->getMaxLevel()) {
        CCLabelTTF* maxLevelLabel = CCLabelTTF::create("已经达到最大等级", "Arail", 35);
        maxLevelLabel->cocos2d::CCNode::setAnchorPoint(ccp(0.5,0.5));
        maxLevelLabel->setColor(ccc3(238,204,122));
        maxLevelLabel->setPosition(ccp(winSize.width/2+75,120));
        infoinfoStrenthenLayer->addChild(maxLevelLabel);
        
        sprintf(str, "%d", mainCard->bean->getLevel());
        
        CCSprite* levelIcon = CCSprite::createWithSpriteFrameName("levelIcon.png"
                                                                  );
        levelIcon->setPosition(ccp(470,191));
        levelIcon->setScale(0.7);
        
        CCLabelAtlas* levelLabel1 = CCLabelAtlas::create(str, "levelupnumber.png", 40, 32, '0');
        levelLabel1->setAnchorPoint(ccp(0,0.5));
        levelLabel1->setPosition(ccp(winSize.width/2+85,191));
        levelLabel1->setScaleY(1.2);
        levelLabel1->setTag(armyInfoInfoStrenthenInfoLayerLevelAtlasTag);
        
        CCLayer* descriptionLayer = mainCard->bean->getUnitCardDesc(false);
        descriptionLayer->setPosition(ccp(winSize.width/2-180,100));
        infoinfoStrenthenLayer->addChild(levelIcon);
        infoinfoStrenthenLayer->addChild(levelLabel1);
        infoinfolayer->addChild(infoinfoStrenthenLayer);
        infoinfolayer->addChild(descriptionLayer);
        this->getChildByTag(creatorLayerTag)->getChildByTag(armyInfoLayerTag)->addChild(infoinfolayer);
        return;
    }
    
    CCSprite* levelIcon = CCSprite::createWithSpriteFrameName("levelIcon.png"
                                                              );
    levelIcon->setPosition(ccp(winSize.width/2-30,221));
    levelIcon->setScale(0.7);
    
    sprintf(str, "%d", mainCard->bean->getLevel());
    
    CCLabelAtlas* levelLabel1 = CCLabelAtlas::create(str, "levelupnumber.png", 40, 32, '0');
    levelLabel1->setAnchorPoint(ccp(0,0.5));
    levelLabel1->setPosition(ccp(winSize.width/2+65,221));
    levelLabel1->setScaleY(1.2);
    levelLabel1->setTag(armyInfoInfoStrenthenInfoLayerLevelAtlasTag);
    
    CCSprite* upArrow =CCSprite::createWithSpriteFrameName("updateTipIcon.png");
    upArrow->setPosition(ccp(levelLabel1->getPosition().x+levelLabel1->getContentSize().width+5,221));
    upArrow->setAnchorPoint(ccp(0,0.5));
    upArrow->setScale(1.4);
    infoinfoStrenthenLayer->addChild(upArrow);
    
    sprintf(str, "%d",mainCard->bean->getLevel()+1);
    CCLabelAtlas* levelLabel2 = CCLabelAtlas::create(str, "levelupnumber.png", 40, 32, '0');
    levelLabel2->setAnchorPoint(ccp(0,0.5));
    levelLabel2->setPosition(ccp(upArrow->getPosition().x+upArrow->getContentSize().width*1.4+5,221));
    levelLabel2->setScaleY(1.2);
    infoinfoStrenthenLayer->addChild(levelLabel2);
    
    
    if (mainCard->bean->creator->unlockCostResourceTag == diamondTag) {
        CCSprite* costIcon = CCSprite::createWithSpriteFrameName("diamond.png");
        costIcon->setPosition(ccp(winSize.width/2+20,171));
        costIcon->setScale(37/costIcon->getContentSize().height);
        //        int rarity = mainCard->bean->creator->getRarity();
        float costCount = strenthenDiamondCost;
        
        CCLabelTTF* costFont = CCLabelTTF::create("花费:", "Arial", 20);
        costFont->setColor(ccc3(238,204,122));
        costFont->setAnchorPoint(ccp(0,0.5));
        costFont->setPosition(ccp(winSize.width/2+35,161));
        
        //    sprintf(str, "/%d",(int)(upResource+0.5));
        MyAtlasNumber* costLabel =MyAtlasNumber::create();
        //    MyAtlasNumber* costLabel =NULL;
        if (costCount > 10000000) {
            costLabel->setScale(0.8);
        }
        costLabel->setNumberNoFx(costCount);
        costLabel->setTag(armyInfoInfoStrenthenInfoLayerCostAtlasTag);
        
        //    CCLabelAtlas::create(str, "number7.png", 24, 36, '/');
        costLabel->setColor(ccc3(238,204,122));
        costLabel->setAnchorPoint(ccp(0,0.5));
        costLabel->setPosition(ccp(winSize.width/2+80,171));
        //    costLabel->setScale();
        infoinfoStrenthenLayer->addChild(costIcon,1);
        infoinfoStrenthenLayer->addChild(costFont,1);
        infoinfoStrenthenLayer->addChild(costLabel,1);
    } else {
        CCSprite* costIcon = CCSprite::createWithSpriteFrameName("ironIcon.png");
        costIcon->setPosition(ccp(winSize.width/2-70,171));
        costIcon->setScale(0.8);
        int rarity = mainCard->bean->creator->getRarity();
        float costCount = strenthenIronCost;
        
        CCLabelTTF* costFont = CCLabelTTF::create("花费:", "Arial", 20);
        costFont->setColor(ccc3(238,204,122));
        costFont->setAnchorPoint(ccp(0,0.5));
        costFont->setPosition(ccp(winSize.width/2-50,161));
        
        //    sprintf(str, "/%d",(int)(upResource+0.5));
        MyAtlasNumber* costLabel =MyAtlasNumber::create();
        //    MyAtlasNumber* costLabel =NULL;
        if (costCount > 10000000) {
            costLabel->setScale(0.8);
        }
        costLabel->setNumberNoFx(costCount);
        costLabel->setTag(armyInfoInfoStrenthenInfoLayerCostAtlasTag);
        
        //    CCLabelAtlas::create(str, "number7.png", 24, 36, '/');
        costLabel->setColor(ccc3(238,204,122));
        costLabel->setAnchorPoint(ccp(0,0.5));
        costLabel->setPosition(ccp(winSize.width/2-5,171));
        //    costLabel->setScale();
        float costHonorCount = strenthenHonorCost;
        
        CCSprite* costHonorIcon = CCSprite::createWithSpriteFrameName("honorIcon.png");
        costHonorIcon->setPosition(ccp(winSize.width/2+130,171));
        costHonorIcon->setScale(0.8);
        
        CCLabelTTF* costHonorFont = CCLabelTTF::create("花费:", "Arial", 20);
        costHonorFont->setColor(ccc3(238,204,122));
        costHonorFont->setAnchorPoint(ccp(0,0.5));
        costHonorFont->setPosition(ccp(winSize.width/2+150,161));
        
        //    sprintf(str, "/%d",(int)(upResource+0.5));
        MyAtlasNumber* costHonorLabel =MyAtlasNumber::create();
        costHonorLabel->setNumberNoFx(costHonorCount);
        costHonorLabel->setTag(armyInfoInfoStrenthenInfoLayerCostAtlasTag);
        if (costHonorCount > 10000000) {
            costHonorLabel->setScale(0.8);
        }
        //    CCLabelAtlas::create(str, "number7.png", 24, 36, '/');
        costHonorLabel->setColor(ccc3(238,204,122));
        costHonorLabel->setAnchorPoint(ccp(0,0.5));
        costHonorLabel->setPosition(ccp(winSize.width/2+195,171));
        
        infoinfoStrenthenLayer->addChild(costIcon,1);
        infoinfoStrenthenLayer->addChild(costHonorIcon,1);
        infoinfoStrenthenLayer->addChild(costFont,1);
        infoinfoStrenthenLayer->addChild(costLabel,1);
        infoinfoStrenthenLayer->addChild(costHonorFont,1);
        infoinfoStrenthenLayer->addChild(costHonorLabel,1);
    }
    
    
    
    CCMenuItemSprite* strenthButton = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("armyinfoinnerstrenthenbutton.png"), CCSprite::createWithSpriteFrameName("armyinfoinnerstrenthenbuttonP.png"),this,   menu_selector(StartScene::toSureStrenthenSimple));
    
    strenthButton->setPosition(ccp(winSize.width/2+85,100));
    menu->addChild(strenthButton);
    
    
    
    
    CCLayer* descriptionLayer = mainCard->bean->getUnitCardDesc(false);
    descriptionLayer->setPosition(ccp(winSize.width/2-180,100));
    infoinfoStrenthenLayer->addChild(levelIcon);
    infoinfoStrenthenLayer->addChild(levelLabel1);
    //    infoinfoStrenthenLayer->addChild(levelLabel2);
    //    infoinfoStrenthenLayer->addChild(upArrow);
    infoinfolayer->addChild(infoinfoStrenthenLayer);
    infoinfolayer->addChild(menu,-1);
    infoinfolayer->addChild(descriptionLayer);
    this->getChildByTag(creatorLayerTag)->getChildByTag(armyInfoLayerTag)->addChild(infoinfolayer);
}

void StartScene::toInfoStrenthenCallBack() {
    //TODO 可能是获取信息页面
    CCLayer* layer = (CCLayer*) this->getChildByTag(creatorLayerTag)->getChildByTag(armyInfoLayerTag)->getChildByTag(armyInfoInfoLayerTag);
    CCArray* array = NULL;
    
    MyUnitCard* mainCard = (MyUnitCard*)this->getChildByTag(creatorLayerTag)->getChildByTag(armyInfoLayerTag)->getUserData();
    
    CCLayer* infoinfolayer = CCLayer::create();
    infoinfolayer->setPosition(ccp(0,0));
    int mainRarity = mainCard->bean->creator->getRarity();
    unsigned long long upExp = 0;
    float upResource = 0;
    if (layer != NULL) {
        array =  (CCArray*)layer->getUserObject();
    }
    if (array != NULL) {
        infoinfolayer->setUserObject(array);
        CCObject* obj;
        CCARRAY_FOREACH(array, obj) {
            CreatorInfoBean* creatorbean = (CreatorInfoBean*)((CCNode*)obj)->getUserData();
            upExp += MyUtil::getInstance()->getUnitStrenthanExp(creatorbean);
        }
        upResource = MyUtil::getInstance()->updateLevelByRate(0,100*mainRarity*mainRarity, mainCard->bean->getLevel(), 3)* array->count();
    }
    if (layer) {
        layer->removeFromParentAndCleanup(true);
    }
    
    //    this->getChildByTag(creatorLayerTag)->getChildByTag(armyInfoLayerTag)->removeChildByTag(armyInfoInfoLayerTag, true);
    
    
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sfx_click.mp3");
    infoinfolayer->setTag(armyInfoInfoLayerTag);
    
    CCSprite* plus =CCSprite::createWithSpriteFrameName("armyinfoplus.png");
    
    MyPriorityMenu* menu = MyPriorityMenu::create(-502,NULL,NULL);
    menu->setPosition(ccp(0,0));
    menu->setTag(armyInfoInfoLayerMenuTag);
    
    plus->setPosition(ccp(302,442));
    for (int i = 0; i<5; i++) {
        CCSprite* empty =  CCSprite::createWithSpriteFrameName("armystrenthenempty.png");
        empty->setColor(ccGRAY);
        CCMenuItemSprite* emptyitem = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("armystrenthenempty.png"), empty,this,menu_selector(StartScene::toChooseArmytobeStrenthen));
        emptyitem->setPosition(ccp(376+i*104,442));
        menu->addChild(emptyitem);
    }
    
    CCLayer* infoinfoStrenthenLayer = CCLayer::create();
    infoinfoStrenthenLayer->setPosition(ccp(0,0));
    infoinfoStrenthenLayer->setTag(armyInfoInfoStrenthenInfoLayerTag);
    
    
    if (array != NULL) {
        CCObject* obj;
        CCARRAY_FOREACH(array, obj) {
            MyMenuItem* item = (MyMenuItem*)obj;
            infoinfoStrenthenLayer->addChild(item);
        }
    }
    
    CCSprite* levelIcon = CCSprite::createWithSpriteFrameName("levelIcon.png"
                                                              );
    levelIcon->setPosition(ccp(420,351));
    levelIcon->setScale(0.9);
    //    CCLabelTTF* levelTipLabel = CCLabelTTF::create("等 级：", "Arial", 24);
    //    levelTipLabel->setColor(ccc3(238,204,122));
    //    levelTipLabel->setAnchorPoint(ccp(0,0.5));
    //    levelTipLabel->setPosition(ccp(450,341));
    
    
    
    char str[5] = {0};
    
    
    sprintf(str, "%d", mainCard->bean->getLevel());
    
    CCLabelAtlas* levelLabel1 = CCLabelAtlas::create(str, "levelupnumber.png", 40, 32, '0');
    levelLabel1->setAnchorPoint(ccp(0,0.5));
    levelLabel1->setPosition(ccp(545,351));
    levelLabel1->setScaleY(1.2);
    levelLabel1->setTag(armyInfoInfoStrenthenInfoLayerLevelAtlasTag);
    
    CCLabelTTF* levelFont = CCLabelTTF::create("等级:", "Arial", 24);
    levelFont->setColor(ccc3(238,204,122));
    levelFont->setAnchorPoint(ccp(0,0.5));
    levelFont->setPosition(ccp(450,336));
    
    
    int upLevel = MyUtil::getInstance()->getUnitLevelByExperience(mainCard->bean->getExperience()+upExp, mainCard->bean->creator->getRarity());
    if (upLevel > mainCard->bean->getLevel()) {
        CCSprite* upArrow =CCSprite::createWithSpriteFrameName("updateTipIcon.png");
        upArrow->setPosition(ccp(levelLabel1->getPosition().x+levelLabel1->getContentSize().width+5,351));
        upArrow->setAnchorPoint(ccp(0,0.5));
        upArrow->setScale(1.4);
        infoinfoStrenthenLayer->addChild(upArrow);
        
        sprintf(str, "%d",upLevel);
        CCLabelAtlas* levelLabel2 = CCLabelAtlas::create(str, "levelupnumber.png", 40, 32, '0');
        levelLabel2->setAnchorPoint(ccp(0,0.5));
        levelLabel2->setPosition(ccp(upArrow->getPosition().x+upArrow->getContentSize().width*1.4+5,351));
        levelLabel2->setScaleY(1.2);
        infoinfoStrenthenLayer->addChild(levelLabel2);
        
        
    }
    
    
    
    
    
    CCSprite* costIcon = CCSprite::createWithSpriteFrameName("ironIcon.png");
    costIcon->setPosition(ccp(410,271));
    costIcon->setScale(0.75);
    
    
    CCLabelTTF* costFont = CCLabelTTF::create("花费:", "Arial", 24);
    costFont->setColor(ccc3(238,204,122));
    costFont->setAnchorPoint(ccp(0,0.5));
    costFont->setPosition(ccp(450,261));
    
    //    sprintf(str, "/%d",(int)(upResource+0.5));
    MyAtlasNumber* costLabel =MyAtlasNumber::create();
    costLabel->setNumberNoFx(upResource);
    costLabel->setTag(armyInfoInfoStrenthenInfoLayerCostAtlasTag);
    
    //    CCLabelAtlas::create(str, "number7.png", 24, 36, '/');
    costLabel->setColor(ccc3(238,204,122));
    costLabel->setAnchorPoint(ccp(0.5,0.5));
    costLabel->setPosition(ccp(600,271));
    costLabel->setScale(1.2);
    
    unsigned long exp = mainCard->bean->getExperience() - MyUtil::getInstance()-> getExperienceByUnitLevel(mainCard->bean->getLevel()-1, mainCard->bean->creator->getRarity());
    int levelCha = MyUtil::getInstance()-> getExperienceByUnitLevel(mainCard->bean->getLevel(), mainCard->bean->creator->getRarity()) - MyUtil::getInstance()-> getExperienceByUnitLevel(mainCard->bean->getLevel()-1, mainCard->bean->creator->getRarity());
    
    unsigned long newExp = mainCard->bean->getExperience()+upExp - MyUtil::getInstance()->getExperienceByUnitLevel(upLevel-1, mainCard->bean->creator->getRarity());
    
    int newlevelCha = MyUtil::getInstance()-> getExperienceByUnitLevel(upLevel, mainCard->bean->creator->getRarity()) - MyUtil::getInstance()-> getExperienceByUnitLevel(upLevel-1, mainCard->bean->creator->getRarity());
    
    
    float per = (exp*1.0)/(levelCha*1.0);
    
    float per2 = (newExp*1.0)/(newlevelCha*1.0);
    
    CCSprite* expIcon = CCSprite::createWithSpriteFrameName("expIcon.png");
    expIcon->setPosition(ccp(418,191));
    expIcon->setScale(1.15);
    CCLabelTTF* expLabel = CCLabelTTF::create("经验值：", "Arial", 24);
    expLabel->setColor(ccc3(238,204,122));
    expLabel->setAnchorPoint(ccp(0,0.5));
    expLabel->setPosition(ccp(450,211));
    
    GXProgressBar* barAdd = GXProgressBar::create(CCSprite::create("expBarUp.png"), CCSprite::create("BarDown.png"));
    
    barAdd->setContentSize(CCSizeMake(285,25));
    barAdd->updatePercentage(per2);
    CCTintTo* tintBy = CCTintTo::create(1, 255,150,255);
    //    healthBarAdd->getUpSprite()->setColor(ccGRAY);
    barAdd->getUpSprite()->runAction(CCRepeatForever::create(static_cast<CCSequence*>(CCSequence::create(tintBy,CCTintTo::create(1, 255,255,255),NULL))));
    
    
    CCSprite* bar = CCSprite::create("expBarUp.png");
    bar->setTag(armyInfoInfoStrenthenInfoLayerExpBarDownTag);
    if (upLevel >mainCard->bean->getLevel()) {
        bar->setScaleX(0);
    } else {
        bar->setScaleX((285*per)/bar->getContentSize().width);
    }
    bar->setScaleY(25/bar->getContentSize().height);
    
    bar->setAnchorPoint(ccp(0,0));
    bar->setColor(ccc3(255,255,255));
    barAdd->addChild(bar);
    barAdd->setPosition(ccp(450,171));
    barAdd->setTag(armyInfoInfoStrenthenInfoLayerExpBarUPTag);
    
    
    
    CCMenuItemSprite* strenthButton = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("armyinfoinnerstrenthenbutton.png"), CCSprite::createWithSpriteFrameName("armyinfoinnerstrenthenbuttonP.png"),this,menu_selector(StartScene::toSureStrenthen));
    
    strenthButton->setPosition(ccp(565,100));
    menu->addChild(strenthButton);
    
    if (mainCard->bean->getLevel() > mainCard->bean->creator->getMaxLevel()) {
        CCLabelTTF* maxLevelLabel = CCLabelTTF::create("已经达到最大等级", "Arail", 35);
        maxLevelLabel->cocos2d::CCNode::setAnchorPoint(ccp(0.5,0.5));
        maxLevelLabel->setColor(ccc3(238,204,122));
        maxLevelLabel->setPosition(ccp(565,150));
        infoinfoStrenthenLayer->addChild(maxLevelLabel);
        strenthButton->setEnabled(false);
    }
    
    
    
    infoinfolayer->addChild(plus,-1);
    infoinfoStrenthenLayer->addChild(levelFont);
    infoinfoStrenthenLayer->addChild(levelIcon);
    infoinfoStrenthenLayer->addChild(costIcon);
    infoinfoStrenthenLayer->addChild(expIcon);
    infoinfoStrenthenLayer->addChild(levelLabel1);
    //    infoinfoStrenthenLayer->addChild(levelLabel2);
    //    infoinfoStrenthenLayer->addChild(upArrow);
    infoinfoStrenthenLayer->addChild(costFont);
    infoinfoStrenthenLayer->addChild(costLabel);
    infoinfoStrenthenLayer->addChild(expLabel);
    infoinfoStrenthenLayer->addChild(barAdd);
    infoinfolayer->addChild(infoinfoStrenthenLayer);
    infoinfolayer->addChild(menu,-1);
    
    this->getChildByTag(creatorLayerTag)->getChildByTag(armyInfoLayerTag)->addChild(infoinfolayer);
    //    infoinfolayer->
}

void StartScene::toSureStrenthenSimple(cocos2d::CCMenuItem *pSender) {
    
    MyUnitCard* mainCard = (MyUnitCard*)this->getChildByTag(creatorLayerTag)->getChildByTag(armyInfoLayerTag)->getUserData();
    int rarity = mainCard->bean->creator->getRarity();
    if (mainCard->bean->creator->unlockCostResourceTag == diamondTag) {
        float diamondCost = strenthenDiamondCost;
        if (MyGameInfo::getInstance()->getDiamond() < diamondCost) {
            this->addChild(MyUtil::getInstance()->getNoResourceDialog(this,diamondTag));
            CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sfx_error.wav");
            return;
        }
        MyGameInfo::getInstance()->changeResource(diamondTag, diamondCost*-1);
    } else {
        float ironCost = strenthenIronCost;
        float honorCost = strenthenHonorCost;
        if (MyGameInfo::getInstance()->getIron() < ironCost ||  MyGameInfo::getInstance()->getGlory() < honorCost) {
            this->addChild(MyUtil::getInstance()->getNoResourceDialog(this,0));
            CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sfx_error.wav");
            return;
        }
        MyGameInfo::getInstance()->changeResource(ironTag, ironCost*-1);
        MyGameInfo::getInstance()->changeResource(gloryTag, honorCost*-1);
    }
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sfx_updateBuilding.mp3");
    mainCard->bean->setExperience(MyUtil::getInstance()->getExperienceByUnitLevel(mainCard->bean->getLevel(),mainCard->bean->creator->getRarity())+1);
    char str[12] = {0};
    sprintf(str,"Lv:%d",mainCard->bean->getLevel());
    ((CCLabelTTF*)mainCard->getChildByTag(lvFontTag))->setString(str);
    UpdateArmyMessage::create(mainCard->bean->creator->cardId,mainCard->bean->getLevel()-1,mainCard->bean->getLevel())->sendMsg();
    //发送升级指令
    MyHttpConnection::getInstance()->sendUpdateArmyId(mainCard->bean->creator->cardId);
    toInfoStrenthenCallBackSimple();
}

void StartScene::toSureStrenthen(cocos2d::CCMenuItem *pSender) {
    
    
    
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sfx_click.mp3");
    CCLayer* infoinfoLayer = (CCLayer*)pSender->getParent()->getParent();
    CCLabelAtlas* numAtlas =(CCLabelAtlas*) infoinfoLayer->getChildByTag(armyInfoInfoStrenthenInfoLayerTag)->getChildByTag(armyInfoInfoStrenthenInfoLayerCostAtlasTag);
    int cost = atoi(numAtlas->getString());
    
    if (MyGameInfo::getInstance()->getIron() < cost) {
        this->addChild(MyUtil::getInstance()->getNoResourceDialog(this,0));
        return;
    }
    
    pSender->setEnabled(false);
    CCArray* myArmyList = (CCArray*)infoinfoLayer->getUserObject();
    if (!myArmyList || myArmyList->count() == 0) {
        toChooseArmytobeStrenthen(pSender);
        return;
    }
    
    CCSprite* black =CCSprite::create("whiteImage.jpg");
    black->setColor(ccc3(0,0,0));
    black->setScaleX(winSize.width/black->getContentSize().width);
    black->setScaleY(winSize.height/black->getContentSize().height);
    black->setOpacity(0);
    black->setAnchorPoint(ccp(0,0));
    black->setPosition(ccp(0,0));
    black->setTag(armyInfoInfoStrenthenBlackTag);
    infoinfoLayer->addChild(black,-1);
    black->runAction(CCFadeTo::create(0.7, 220));
    
    
    
    MyUnitCard* mainCard = (MyUnitCard*)infoinfoLayer->getParent()->getUserData();
    mainCard->runAction(CCSequence::create(CCEaseInOut::create(CCMoveBy::create(0.7, ccp(50,-120)), 4),CCCallFuncND::create(this, callfuncND_selector(StartScene::runSureStrenthenHeChengAction), myArmyList),NULL));
    
    
    infoinfoLayer->getChildByTag(armyInfoInfoStrenthenInfoLayerTag);
    
}

void StartScene::runSureStrenthenHeChengAction(CCNode* target,CCNode* data) {
    MyUnitCard* mainCard = (MyUnitCard*)target;
    
    CCSprite* bling1_1 = CCSprite::create("armyprizeLight.png");
    bling1_1->setTag(bling1Tag);
    //    bling1_1->setScale(0);
    bling1_1->setPosition(ccp(mainCard->getImage()->getContentSize().width/2,mainCard->getImage()->getContentSize().height/2));
    bling1_1->setScale(2);
    bling1_1->runAction(CCRotateBy::create(1000, 7200));
    bling1_1->runAction(CCFadeIn::create(2.5));
    
    CCSprite* bling1_2 = CCSprite::create("armyprizeLight.png");
    bling1_2->setTag(bling2Tag);
    bling1_2->setPosition(ccp(mainCard->getImage()->getContentSize().width/2,mainCard->getImage()->getContentSize().height/2));
    bling1_2->setScale(0.5);
    bling1_2->runAction(CCRotateBy::create(1000, -7200));
    bling1_2->runAction(CCSequence::create(CCDelayTime::create(1),CCScaleTo::create(2.5, 1.7) ,NULL));
    
    mainCard->addChild(bling1_1,-1);
    mainCard->addChild(bling1_2,-1);
    
    CCArray* myArmyArray = (CCArray*)data;
    //TODO 吃经验与升级
    int i = 0;
    unsigned long long upExp = 0;
    float actionTime = 0;
    for (i=0; i<myArmyArray->count(); i++) {
        
        MyMenuItem* item = (MyMenuItem*)(myArmyArray->objectAtIndex(i));
        item->runAction(CCSequence::create(CCDelayTime::create(0.8*i),CCEaseInOut::create(CCMoveTo::create(0.4+0.3*i, ccp(mainCard->getPosition().x,mainCard->getPosition().y)), 4),GXRemoveFromParentsAction::create(),NULL));
        upExp += MyUtil::getInstance()->getUnitStrenthanExp((CreatorInfoBean*)item->getUserData());
        MyGameInfo::getInstance()->creatorArray->fastRemoveObject((CreatorInfoBean*)item->getUserData());
        actionTime+=1.3;
    }
    
    //    MyMenuItem* item1 = (MyMenuItem*)(myArmyArray->lastObject());
    //    item1->runAction(CCSequence::create(CCDelayTime::create(0.8*i),CCEaseInOut::create(CCMoveTo::create(0.4+0.3*i, ccp(mainCard->getPosition().x,mainCard->getPosition().y)), 4),GXPlayEffectAction::create("sfx_updateBuilding.mp3"),CCCallFunc::create(this, callfunc_selector(StartScene::runSureStrenthenReturnAction)),GXRemoveFromParentsAction::create(),NULL));
    myArmyArray->removeAllObjects();
    
    CCLayer* infoStrenthInfoLayer = (CCLayer*) this->getChildByTag(creatorLayerTag)->getChildByTag(armyInfoLayerTag)->getChildByTag(armyInfoInfoLayerTag)->getChildByTag(armyInfoInfoStrenthenInfoLayerTag);
    
    
    MyAtlasNumber* atlas = ((MyAtlasNumber*)infoStrenthInfoLayer->getChildByTag(armyInfoInfoStrenthenInfoLayerCostAtlasTag));
    MyGameInfo::getInstance()->changeResource(ironTag, atlas->getTargetNumber()*-1);
    
    atlas->setNumber(0);
    GXProgressBar* barDown = ((GXProgressBar*)infoStrenthInfoLayer->getChildByTag(armyInfoInfoStrenthenInfoLayerExpBarUPTag));
    CCSprite* baradd = ((CCSprite*)barDown->getChildByTag(armyInfoInfoStrenthenInfoLayerExpBarDownTag));
    int upLevel = MyUtil::getInstance()->getUnitLevelByExperience(mainCard->bean->getExperience()+upExp, mainCard->bean->creator->getRarity());
    
    unsigned long exp = mainCard->bean->getExperience() - MyUtil::getInstance()-> getExperienceByUnitLevel(mainCard->bean->getLevel()-1, mainCard->bean->creator->getRarity());
    int levelCha = MyUtil::getInstance()-> getExperienceByUnitLevel(mainCard->bean->getLevel(), mainCard->bean->creator->getRarity()) - MyUtil::getInstance()-> getExperienceByUnitLevel(mainCard->bean->getLevel()-1, mainCard->bean->creator->getRarity());
    
    float first = (1-(exp*1.0)/(levelCha*1.0));
    float xunhuanTimes = barDown->percentage + first + upLevel-mainCard->bean->getLevel();
    
    CCArray* actionArray = CCArray::create();
    float scaleY = baradd->getScaleY();
    if (upLevel > mainCard->bean->getLevel()) {
        baradd->setScaleX((1-first)*285/baradd->getContentSize().width);
        actionArray->addObject(CCScaleTo::create((first/xunhuanTimes)*actionTime, 285/baradd->getContentSize().width,scaleY));
        actionArray->addObject(CCScaleTo::create(0,0,scaleY));
        actionArray->addObject(CCCallFuncND::create(this, callfuncND_selector(StartScene::changeStrenthanInfoInStrenthaning), (void*)mainCard));
        for (int i=0; i < upLevel-mainCard->bean->getLevel()-1; i++) {
            actionArray->addObject(CCScaleTo::create((1/xunhuanTimes)*actionTime, 285/baradd->getContentSize().width,scaleY));
            actionArray->addObject(CCScaleTo::create(0, 0,scaleY));
            actionArray->addObject(CCCallFuncND::create(this, callfuncND_selector(StartScene::changeStrenthanInfoInStrenthaning), (void*)mainCard));
        }
        actionArray->addObject(CCScaleTo::create((barDown->percentage/xunhuanTimes)*actionTime, (285*barDown->percentage)/baradd->getContentSize().width,scaleY));
    } else {
        actionArray->addObject(CCScaleTo::create(actionTime, (285*barDown->percentage)/baradd->getContentSize().width,scaleY));
    }
    actionArray->addObject(CCCallFunc::create(this, callfunc_selector(StartScene::runSureStrenthenReturnAction)));
    
    barDown->updatePercentage(0);
    
    baradd->runAction(CCSequence::create(actionArray));
    //加入经验
    mainCard->bean->setExperience(upExp+ mainCard->bean->getExperience());
}

void StartScene::changeStrenthanInfoInStrenthaning(cocos2d::CCNode *target, cocos2d::CCNode *data) {
    MyUnitCard* mainCard = (MyUnitCard*)data;
    CCLabelAtlas* atlas = (CCLabelAtlas*)target->getParent()->getParent()->getChildByTag(armyInfoInfoStrenthenInfoLayerLevelAtlasTag);
    int num = atoi(atlas->getString());
    char str[8] = {0};
    sprintf(str, "%d",num+1);
    atlas->setString(str);
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sfx_updateBuilding.mp3");
    
    CCLabelTTF* lvfont = (CCLabelTTF*)mainCard->getChildByTag(lvFontTag);
    sprintf(str, "Lv:%d",num+1);
    lvfont->setString(str);
    lvfont->setScale(2);
    lvfont->runAction(CCScaleTo::create(0.1, 1));
}

void StartScene::runSureStrenthenReturnAction() {
    CCLayer* infoinfoLayer = (CCLayer*) this->getChildByTag(creatorLayerTag)->getChildByTag(armyInfoLayerTag)->getChildByTag(armyInfoInfoLayerTag);
    MyUnitCard* mainCard = (MyUnitCard*)infoinfoLayer->getParent()->getUserData();
    mainCard->runAction(CCEaseInOut::create(CCMoveBy::create(1, ccp(100,0)), 4));
    CCLayer* strenthenInfoLayer = (CCLayer*) infoinfoLayer->getChildByTag(armyInfoInfoStrenthenInfoLayerTag);
    strenthenInfoLayer->runAction(CCEaseInOut::create(CCMoveBy::create(1, ccp(30,70)), 4));
    
    CCMenuItemSprite* returnButton = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("armyzhengbingreturnbutton.png"),CCSprite::createWithSpriteFrameName("armyzhengbingreturnbuttonP.png"),this,menu_selector(StartScene::zhengbingReturnToInfo));
    returnButton->setPosition(ccp(winSize.width/2,0));
    MyPriorityMenu* menu = MyPriorityMenu::create(-502, returnButton,NULL)
    ;
    menu->setPosition(ccp(0,-returnButton->getContentSize().height));
    menu->runAction(CCEaseElasticOut::create(CCMoveTo::create(1,ccp(0,100)), 0.7));
    infoinfoLayer->addChild(menu);
    
    
}

void StartScene::zhengbingReturnToInfo(cocos2d::CCMenuItem *pSender) {
    pSender->getParent()->runAction(CCSequence::create(CCEaseElasticOut::create(CCMoveTo::create(1,ccp(0,-pSender->getContentSize().height)), 0.7),GXRemoveFromParentsAction::create(),NULL));
    
    CCLayer* infoinfoLayer = (CCLayer*) this->getChildByTag(creatorLayerTag)->getChildByTag(armyInfoLayerTag)->getChildByTag(armyInfoInfoLayerTag);
    MyUnitCard* mainCard = (MyUnitCard*)infoinfoLayer->getParent()->getUserData();
    
    if (mainCard->getChildByTag(bling1Tag)) {
        mainCard->getChildByTag(bling1Tag)->runAction(CCSequence::create( CCFadeOut::create(1.4),GXRemoveFromParentsAction::create(),NULL));
    }
    
    if (mainCard->getChildByTag(bling2Tag)) {
        mainCard->getChildByTag(bling2Tag)->runAction(CCSequence::create( CCFadeOut::create(1.4),GXRemoveFromParentsAction::create(),NULL));
    }
    
    //    CCSequence::create(CCEaseBackInOut::create(CCMoveTo::create(1, ccp(120,444))),CCCallFuncO::create(this, callfuncO_selector(StartScene::toRunInfoAction), pSender) ,NULL))
    mainCard->runAction(CCSequence::create(CCEaseInOut::create(CCMoveTo::create(1, ccp(120,444)), 4),NULL));
    CCLayer* strenghthenLayer = (CCLayer*)infoinfoLayer->getChildByTag(armyInfoInfoStrenthenInfoLayerTag);
    CCObject* obj;
    
    infoinfoLayer->getChildByTag(armyInfoInfoStrenthenBlackTag)->runAction(CCFadeOut::create(1));
    infoinfoLayer->runAction(CCSequence::create(CCDelayTime::create(1.1),CCCallFunc::create(this, callfunc_selector(StartScene::finishStrenthenToInfo)),NULL));
    
    
    CCARRAY_FOREACH(strenghthenLayer->getChildren(), obj) {
        CCNode* node = (CCNode*)obj;
        node->runAction(CCFadeOut::create(0.7));
    }
}

void StartScene::finishStrenthenToInfo() {
    GXRadioMenu*  radio = (GXRadioMenu*) this->getChildByTag(creatorLayerTag)->getChildByTag(armyInfoLayerTag)->getChildByTag(armyInfoRadioMenuTag);
    radio->setSelect(0);
}

void  StartScene::toChooseArmytobeStrenthen(cocos2d::CCMenuItem *pSender){
    ((CCMenu*)pSender->getParent())->setEnabled(false);
    CCLayer* infoinfoLayer = (CCLayer*)this->getChildByTag(creatorLayerTag)->getChildByTag(armyInfoLayerTag)->getChildByTag(armyInfoInfoLayerTag);
    if (infoinfoLayer->getChildByTag(armyInfoStrenthenDivideLayerTag) != NULL) {
        return ;
    }
    
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sfx_popCreator.mp3");
    
    CCLayer* divideLayer = CCLayer::create();
    divideLayer->setPosition(ccp(0,0));
    divideLayer->setTag(armyInfoStrenthenDivideLayerTag);
    CCSprite* divideLine = CCSprite::createWithSpriteFrameName("armystrenthendivide.png");
    divideLine->setScale(1.25);
    divideLine->setAnchorPoint(ccp(0,0.5));
    divideLine->setPosition(ccp(265,390));
    
    CCSprite* gray = CCSprite::create("whiteImage.jpg");
    gray->setColor(ccc3(0,0,0));
    gray->setScaleX(592/gray->getContentSize().width);
    gray->setScaleY(331/gray->getContentSize().height);
    gray->setAnchorPoint(ccp(0.5,0));
    gray->setPosition(ccp(560,56));
    
    
    CCArray* userarray =  NULL;
    if (infoinfoLayer->getUserObject() != NULL) {
        userarray = (CCArray*)infoinfoLayer->getUserObject();
    } else {
        userarray = CCArray::create();
    }
    
    GXScrollView* scroll = GXScrollView::create(-502);
    scroll->setOriPosition(ccp(265,106));
    scroll->setContentSize(CCSizeMake(592, 280));
    scroll->setUserObject(userarray);
    
    CCArray* array = MyGameInfo::getInstance()->creatorArray;
    CCObject* obj;
    char str[30] = {0};
    int i=0;
    if (array->count() > 6) {
        scroll->setMapSize(CCSizeMake(592, 110*(array->count()/5+1)));
        scroll->setPosition(ccp(scroll->getOriPosition().x,-scroll->getMapSize().height+scroll->getViewSize().height+scroll->getOriPosition().y));
    }
    
    divideLayer->addChild(scroll,2);
    CCLabelTTF* sureLabel = CCLabelTTF::create("确  定","Arial",45);
    sureLabel->setColor(ccc3( 255, 186, 73));
    CCMenuItemLabel* sureItem = CCMenuItemLabel::create(sureLabel, this, menu_selector(StartScene::sureBeStrenthenCard));
    sureItem->setPosition(ccp(565,75));
    MyPriorityMenu* menu = MyPriorityMenu::create(-502, sureItem,NULL);
    menu->setPosition(ccp(0,0));
    menu->setTag(armyInfoStrenthenDivideLayerMenuTag);
    menu->setUserObject(userarray);
    
    CCARRAY_FOREACH(array, obj) {
        CreatorInfoBean* bean = (CreatorInfoBean*)obj;
        MyUnitCard* mainCard = (MyUnitCard*)infoinfoLayer->getParent()->getUserData();
        if(bean == mainCard->bean) {
            continue;
        }
        sprintf(str, "%sbp.png",bean->creator->getSpriteFileName());
        CCSprite* bp = CCSprite::createWithSpriteFrameName(str);
        //        if (bp == NULL) {
        //            break;
        //        }
        
        sprintf(str, "deployBack%d.png",(bean->creator->getRarity()));
        CCSprite* sprite = CCSprite::createWithSpriteFrameName(str);
        bp->setPosition(ccp(53,49));
        bp->setScale(Mathlib::min(115/bp->getContentSize().width, 90/bp->getContentSize().height));
        sprite->addChild(bp);
        sprintf(str, "Lv:%d",(bean->getLevel()));
        CCLabelTTF* lvfont = CCLabelTTF::create(str, "Arial", 25);
        lvfont->setAnchorPoint(ccp(0,0));
        lvfont->setPosition(ccp(10,5));;
        sprite->addChild(lvfont);
        //        sprite->setScale();
        
        MyMenuItem* cardBack = MyMenuItem::create(sprite,CCSprite::createWithSpriteFrameName("dialoggray.png"), this, menu_selector(StartScene::selectCard)) ;
        
        cardBack->setUserData(obj);
        cardBack->setPosition(ccp(70 + (i%5)*112,scroll->getMapSize().height-65-(i/5)*110));
        scroll->addChild(cardBack,2);
        CCObject* obj1;
        CCARRAY_FOREACH(userarray, obj1) {
            MyMenuItem* item1 = (MyMenuItem*)obj1;
            if (bean == item1->getUserData()) {
                cardBack ->setDisabled(false);
                item1->setUserData(cardBack);
                item1->retain();
                item1->removeFromParentAndCleanup(true);
                menu->addChild(item1);
                item1->release();
            }
        }
        
        i++;
    }
    
    
    
    divideLayer->addChild(divideLine);
    divideLayer->addChild(gray);
    divideLayer->addChild(menu);
    infoinfoLayer->addChild(divideLayer);
}

void StartScene::selectCard(CCMenuItem* _pSender) {
    CCArray* myArmyList = (CCArray*)(_pSender->getParent()->getUserObject());
    MyMenuItem* pSender = (MyMenuItem*)_pSender;
    if(myArmyList->count()==5) {
        CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sfx_error.wav");
        return;
    }
    
    
    
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sfx_click.mp3");
    
    pSender->setDisabled(false);
    
    CreatorInfoBean* bean = (CreatorInfoBean*)pSender->getUserData();
    char str[32] = {0};
    sprintf(str, "deployBack%d.png",(bean->creator->getRarity()));
    CCSprite* sprite = CCSprite::createWithSpriteFrameName(str);
    sprintf(str, "%sbp.png",bean->creator->getSpriteFileName());
    CCSprite* bp = CCSprite::createWithSpriteFrameName(str);
    bp->setPosition(ccp(53,49));
    bp->setScale(Mathlib::min(115/bp->getContentSize().width, 90/bp->getContentSize().height));
    sprite->addChild(bp);
    
    MyMenuItem* bpItem = MyMenuItem::create(sprite, this, menu_selector(StartScene::cancelCard));
    CCPoint pos = pSender->getPosition();
    bpItem->setPosition(ccp(pSender->convertToWorldSpace(CCPointZero).x + pSender->getContentSize().width/2,pSender->convertToWorldSpace(CCPointZero).y + pSender->getContentSize().height-pSender->getContentSize().width/2+5));
    //    this->getChildByTag(deployLayerTag)->getChildByTag(deployMenuTag)->addChild(bpItem);
    pSender->getParent()->getParent()->getChildByTag(armyInfoStrenthenDivideLayerMenuTag)->addChild(bpItem,4);
    //    int i = 0;
    //    for (i=0; i<5; i++) {
    //        if (flag[i] == 0) {
    //            flag[i] = 1;
    //            break;
    //        }
    //    }
    int count = myArmyList->count();
    bpItem->runAction(CCEaseInOut::create(CCMoveTo::create(0.2, ccp(374+count*104,442)), 2));
    bpItem->setUserData(pSender);
    myArmyList->addObject(bpItem);
    
}

void StartScene::cancelCard(CCMenuItem *pSender) {
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sfx_click.mp3");
    
    MyMenuItem* item = (MyMenuItem*)pSender->getUserData();
    item->setDisabled(true);
    pSender->setEnabled(false);
    CCPoint p = ccp(item->convertToWorldSpace(CCPointZero).x + item->getContentSize().width/2,item->convertToWorldSpace(CCPointZero).y + item->getContentSize().height-item->getContentSize().width/2+5);
    pSender->runAction(CCSequence::create(CCEaseInOut::create(CCMoveTo::create(0.2, p), 4),GXRemoveFromParentsAction::create(),NULL));
    CCArray* myArmyList = (CCArray*)pSender->getParent()->getUserObject();
    myArmyList->removeObject(pSender);
    CCObject* obj = NULL;
    int i = 0;
    CCARRAY_FOREACH(myArmyList, obj) {
        MyMenuItem* item = (MyMenuItem*)obj;
        item->runAction(CCEaseInOut::create(CCMoveTo::create(0.2, ccp(374+i*104,442)), 4));
        i++;
    }
}

void StartScene::sureBeStrenthenCard(cocos2d::CCMenuItem *pSender) {
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sfx_click.mp3");
    CCArray* myArmyList = (CCArray*)pSender->getParent()->getUserObject();
    CCLayer* infoinfoLayer = (CCLayer*)this->getChildByTag(creatorLayerTag)->getChildByTag(armyInfoLayerTag)->getChildByTag(armyInfoInfoLayerTag);
    CCObject* obj = NULL;
    ((CCMenu*)infoinfoLayer->getChildByTag(armyInfoInfoLayerMenuTag))->setEnabled(true);
    infoinfoLayer->setUserObject(myArmyList);
    CCARRAY_FOREACH(myArmyList, obj) {
        MyMenuItem* item = (MyMenuItem*)obj;
        CreatorInfoBean* bean = (CreatorInfoBean*)((CCNode*)item->getUserData())->getUserData();
        item->setUserData(bean);
        //        item->retain();
        item->removeFromParentAndCleanup(true);
        //        infoinfoLayer->getChildByTag(armyInfoInfoStrenthenInfoLayerTag)->addChild(item);
        //        item->release();
    }
    infoinfoLayer->removeChildByTag(armyInfoStrenthenDivideLayerTag, true);
    toInfoStrenthenCallBack();
}

CCSprite* StartScene::getArmyKuang() {
    CCSprite* kuangTop = CCSprite::createWithSpriteFrameName("armykuangtop.png");
    CCSprite* kuangBottom = CCSprite::createWithSpriteFrameName("armykuangbottom.png");
    CCSprite* kuangLeft =
    CCSprite::createWithSpriteFrameName("armykuangleft.png");
    CCSprite* kuangright = CCSprite::createWithSpriteFrameName("armykuangright.png");
    kuangTop->setScale(1.25);
    kuangTop->setAnchorPoint(ccp(0,1));
    kuangLeft->setPosition(ccp(12,2));
    kuangLeft->setAnchorPoint(ccp(0,1));
    kuangright->setAnchorPoint(ccp(1,1));
    kuangright->setPosition(ccp(kuangBottom->getContentSize().width+12,2));
    kuangBottom->setAnchorPoint(ccp(0,1));
    kuangBottom->setPosition(ccp(12,-kuangLeft->getContentSize().height+4));
    kuangTop->addChild(kuangLeft);
    kuangTop->addChild(kuangright);
    kuangTop->addChild(kuangBottom);
    return kuangTop;
}



void StartScene::toCharDialog(cocos2d::CCNode *pSender) {
    CCMenuItemToggle* toggle = ((CCMenuItemToggle*)pSender);
    if(toggle->getSelectedIndex() == 1) {
        this->getChildByTag(charDialogTag)->runAction(CCEaseElasticOut::create(CCMoveTo::create(0.35, ccp(-16,0)), 1));
        //        GXScrollView* scroll =((GXScrollView*)this->getChildByTag(charDialogTag)->getChildByTag(charScorllTag));
        //        CCPoint point = scroll->getPosition();
        totalCharListView->setOriPosition(ccp(-16,58));
        //        scroll->setPositionY(float y);
        totalCharListView->stopAllActions();
        totalCharListView->setPosition(ccp(-16,totalCharListView->getViewSize().height-totalCharListView->getMapSize().height+totalCharListView->getOriPosition().y));
        
        unionCharListView->setOriPosition(ccp(-16,58));
        unionCharListView->stopAllActions();
        unionCharListView->setPosition(ccp(-16,unionCharListView->getViewSize().height-unionCharListView->getMapSize().height+unionCharListView->getOriPosition().y));
    } else {
        this->getChildByTag(charDialogTag)->runAction(CCEaseElasticOut::create(CCMoveTo::create(0.35, ccp(-382,0)), 1));
        //        GXScrollView* scroll =((GXScrollView*)this->getChildByTag(charDialogTag)->getChildByTag(charScorllTag));
        CCPoint point = totalCharListView->getPosition();
        totalCharListView->setOriPosition(ccp(-382,58));
        totalCharListView->setPosition(point);
        
        CCPoint point2 = unionCharListView->getPosition();
        unionCharListView->setOriPosition(ccp(-382,58));
        unionCharListView->setPosition(point);
    }
}

void StartScene::displayIME(cocos2d::CCNode *node) {
    m_TextField->attachWithIME();
}

void StartScene::sendCallBack(cocos2d::CCNode *sender) {
    std::string str = m_TextField->cocos2d::CCLabelTTF::getString();
    if (str.compare(cacheChar) == 0) {
        addCharMsg(GXMsg::create("[系统公告]", "请不要重复发言"));
        m_TextField->setString("");
        return;
    } else {
        sprintf(cacheChar,"%s", str.c_str());
    }
    if (strcmp("", str.c_str()) != 0 && strcmp("点击此处输入文字", str.c_str()) != 0) {
        if (str.length()>450) {
            addCharMsg(GXMsg::create("[系统公告]","发言请少于150个字"));
            m_TextField->setString("");
            return;
        }
        if (unionCharListView->isVisible()) {
            if (MyGameInfo::getInstance()->getUnionBean()->getName()->compare("") != 0) {
                GXChatHandler::getInstance()->sendUnionChat(CCString::create(str));
            } else {
                addCharMsg(GXMsg::create("[系统公告]","请先加入联盟"));
            }
        } else  {
            GXChatHandler::getInstance()->sendWorldChat(CCString::create(str));
        }
        m_TextField->setString("");
    }
}

void StartScene::updateChar() {
    //    if (GXChatHandler::getInstance()->isWorldNew) {
    //
    //        int ret = pthread_mutex_lock(&GXChatHandler::mutex);
    //        CCAssert(ret == 0, "lock error ,error code ");
    //        CCLog("jiasuoceshi");
    CCObject* obj;
    GXMsg* msg;
    CCARRAY_FOREACH(GXChatHandler::getInstance()->worldMsgArray, obj) {
        msg = (GXMsg*)(obj);
        this->addCharMsg(msg);
    }
    GXChatHandler::getInstance()->worldMsgArray->removeAllObjects();
    //        GXChatHandler::getInstance()->isWorldNew = false;
    //        pthread_mutex_unlock(&GXChatHandler::mutex);
    //    }
    
    //    if (GXChatHandler::getInstance()->isUnionNew) {
    //        int ret = pthread_mutex_lock(&GXChatHandler::mutex);
    //        CCAssert(ret == 0, "lock error ,error code ");
    //        //        CCLog("jiasuoceshi");
    //        CCObject* obj;
    //        GXMsg* msg;
    CCARRAY_FOREACH(GXChatHandler::getInstance()->unionMsgArray, obj) {
        msg = (GXMsg*)(obj);
        this->addCharMsg(msg);
    }
    GXChatHandler::getInstance()->unionMsgArray->removeAllObjects();
    //        GXChatHandler::getInstance()->isUnionNew = false;
    //        pthread_mutex_unlock(&GXChatHandler::mutex);
    //    }
}

void StartScene::addCharMsg(GXMsg *msg) {
    char str[500] = {0};
    //    GXScrollView* scroll;
    //    scroll = dynamic_cast<GXScrollView*>(this->getChildByTag(charDialogTag)->getChildByTag(charScorllTag));
    //    CCLog("%d",msg->msg.length());
    if (msg->msg.length()>450) {
        return;
    }
    sprintf(str, "%s：%s",msg->name.c_str(),msg->msg.c_str());
    //    char str2[60] = {0};
    //    std::string str3;
    //
    //    int count  = strlen(str);
    //    int multi = 0;
    //    int i = 0;
    //    float fen = 0;
    //    int total = 0;
    ////    CCLog("%s",str);
    //
    //    while (i < count) {
    //        if (((str[i] & utfChinese) == utfChinese) && ((str[i] | utfChinese) == str[i])) {
    //            str2[i-total] = str[i];
    //            str2[i+1-total] = str[i+1];
    //            str2[i+2-total] = str[i+2];
    //
    ////            char str5[4] = {0};
    ////            str5[0] = str[i];
    ////            str5[1] = str[i+1];
    ////            str5[2] = str[i+2];
    //            i+=3;
    //            fen+=1;
    //            //                CCLog("%s",str5);
    //        } else {
    //            fen+=0.5;
    //            str2[i-total] = str[i];
    //            //                CCLog("%c",str2[i-total]);
    //            i+=1;
    //        }
    //        if ((int)(fen)%17 == 0 && fen >0.6) {
    //            //                str2[i] = '\n';
    //            multi+=1;
    //            str3.append(str2);
    //            str3.append("\n");
    //            total = i;
    //            fen = 0;
    //            //                CCLog("%s",str2);
    //            for (int j=0; j<60; j++) {
    //                str2[j] = 0;
    //            }
    //            //                CCLog("%s",str3.c_str());
    //        }
    //    }
    //        CCLog("%s",str2);
    //        if(total != 0) {
    //            str3.append("\n");
    //        }
    
    //    str3.append(str2);
    //        CCLog("%s",str3.c_str());
    std::string str3 = GXUtil::insertNewline(str,18);
    //    CCLog("%s",str3.c_str());
    
    
    CCLabelTTF* msgLabel = CCLabelTTF::create(str3.c_str(), "Arial",  18,CCSizeZero, kCCTextAlignmentLeft, kCCVerticalTextAlignmentTop);
    
    totalCharListView->addChild(msgLabel);
    msgLabel->setOpacity(0);
    msgLabel->runAction(CCSequence::create(CCDelayTime::create(0.35),CCFadeIn::create(0.25),NULL));
    if (msg->mode == unionMode) {
        msgLabel->setColor(ccc3(255,200,16));
        CCLabelTTF* unionMsgLabel = CCLabelTTF::create(str3.c_str(), "Arial",  18,CCSizeZero, kCCTextAlignmentLeft, kCCVerticalTextAlignmentTop);
        unionMsgLabel->setColor(ccc3(255,200,16));
        unionCharListView->addChild(unionMsgLabel);
        unionMsgLabel->setOpacity(0);
        unionMsgLabel->runAction(CCSequence::create(CCDelayTime::create(0.35),CCFadeIn::create(0.25),NULL));
    }
    
    if(totalCharListView->getOriPosition().x<-20) {
        CCLabelTTF* msgLabel2 = CCLabelTTF::create(str3.c_str(), "Arial",  16,CCSizeZero, kCCTextAlignmentLeft, kCCVerticalTextAlignmentTop);
        GXListView* list = dynamic_cast<GXListView*>(this->getChildByTag(transScorllTag));
        list->addChild(msgLabel2);
        msgLabel2->setOpacity(255);
        if (msg->mode == unionMode) {
            msgLabel2->setColor(ccc3(255,200,16));
        }
        msgLabel2->runAction(CCSequence::create(CCDelayTime::create(8), CCFadeOut::create(2),GXRemoveFromParentsAction::create(),NULL));
        
    }
}

void StartScene::keyboardWillHide(CCIMEKeyboardNotificationInfo& info) {
    //    std::string str = m_TextField->cocos2d::CCLabelTTF::getString();
    //    if (strcmp("", str.c_str()) != 0 && strcmp("点击此处输入文字", str.c_str()) != 0) {
    //        if (str.length()>450) {
    //            MyGameInfo::getInstance()->getXmppHandler()->send("发言请少于150个字");
    //            m_TextField->setString("");
    //            return;
    //        }
    //        MyGameInfo::getInstance()->getXmppHandler()->send(str);
    //        m_TextField->setString("");
    //    }
    CCLog("will hide");
    
}

void StartScene::keyboardDidHide(CCIMEKeyboardNotificationInfo& info) {
    sendCallBack(NULL);
    //    std::string str = m_TextField->cocos2d::CCLabelTTF::getString();
    //    if (strcmp("", str.c_str()) != 0 && strcmp("点击此处输入文字", str.c_str()) != 0) {
    //        if (str.length()>450) {
    //            MyGameInfo::getInstance()->getXmppHandler()->send("发言请少于150个字");
    //            m_TextField->setString("");
    //            return;
    //        }
    //        MyGameInfo::getInstance()->getXmppHandler()->send(str);
    //        m_TextField->setString("");
    //    }
    CCLog("did hide");
}

void StartScene::changeCharFliter(CCMenuItem* item) {
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sfx_click.mp3");
    if (item->getTag() == totalFliterTag) {
        totalCharListView->setVisible(true);
        unionCharListView->setVisible(false);
        ((CCSprite*)((CCMenuItem*)this->getChildByTag(charDialogTag)->getChildByTag(charmenuTag)->getUserObject())->getChildByTag(sendIconTag))->setColor(ccc3(255,255,255));
    } else if(item->getTag() == unionFliterTag) {
        totalCharListView->setVisible(false);
        unionCharListView->setVisible(true);
        ((CCSprite*)((CCMenuItem*)this->getChildByTag(charDialogTag)->getChildByTag(charmenuTag)->getUserObject())->getChildByTag(sendIconTag))->setColor(ccc3(255,200,16));
    } else if(item->getTag() == privateFliterTag) {
        totalCharListView->setVisible(false);
        unionCharListView->setVisible(false);
        ((CCSprite*)((CCMenuItem*)this->getChildByTag(charDialogTag)->getChildByTag(charmenuTag)->getUserObject())->getChildByTag(sendIconTag))->setColor(ccc3(231, 81, 251));
    }
}

void StartScene::displayRecordCallBack(CCNode* pSender) {
    
    if (this->getChildByTag(recorderLayerTag) ==  NULL) {
        return;
    }
    this->addChild(MyUtil::getInstance()->getWaitLayer("正在加载战绩"));
    this->getChildByTag(recorderLayerTag)->removeChildByTag(recordContentLayerTag, true);
    
    MyHttpConnection::getInstance()->sendGetWhoAttackMeMatch();
    
    //    const char* response = MyHttpConnection::getInstance()->getWhoAttackMeMatches();
    //    //    CCLog(response);
    //    if (strcmp(response, "failed")==0 || strcmp(response, "\0") == 0) {
    //
    //        //这里是回调的this,并不是startscene
    //
    //        this->getParent()->getParent()->addChild(MyUtil::getInstance()->getNetworkDialog());
    //        return;
    //    }
    //    disPlayRecordView((CCSprite*)(this->getChildByTag(recorderLayerTag)->getChildByTag(recordBackSpriteTag)), MyJsonUtil::parseMatches(response));
}

void StartScene::displayWonRecordCallBack(CCNode* pSender) {
    
    if (this->getChildByTag(recorderLayerTag) ==  NULL) {
        return;
    }
    this->addChild(MyUtil::getInstance()->getWaitLayer("正在加载战绩"));
    this->getChildByTag(recorderLayerTag)->removeChildByTag(recordContentLayerTag, true);
    
    MyHttpConnection::getInstance()->sendGetWhoAttackMeMatch(1);
    
}

void StartScene::displayLoseRecordCallBack(CCNode* pSender) {
    
    if (this->getChildByTag(recorderLayerTag) ==  NULL) {
        return;
    }
    this->addChild(MyUtil::getInstance()->getWaitLayer("正在加载战绩"));
    this->getChildByTag(recorderLayerTag)->removeChildByTag(recordContentLayerTag, true);
    
    MyHttpConnection::getInstance()->sendGetWhoAttackMeMatch(0);
    
}


//void StartScene::disPlayRecordViewWait() {
//    if (this->getChildByTag(recorderLayerTag) ==  NULL) {
//        return;
//    }
//    this->getChildByTag(recorderLayerTag)->removeChildByTag(recordContentLayerTag, true);
//    CCString* response = MyHttpConnection::getInstance()->getWhoAttackMeMatches();
//    //    CCLog(response);
//    if (response->compare( "failed")==0 || response->compare( "\0") == 0) {
//
//        //这里是回调的this,并不是startscene
//
//        this->addChild(MyUtil::getInstance()->getNetworkDialog());
//         this->removeChildByTag(waitMenuTag, true);
//        return;
//    }
//
//    this->scheduleOnce(schedule_selector(StartScene::removeWaitMenu), 0.2);
//    disPlayRecordView((CCSprite*)(this->getChildByTag(recorderLayerTag)->getChildByTag(recordBackSpriteTag)), MyJsonUtil::parseMatches(response));
//}

void StartScene::displayTopRankCallBack(CCNode* pSender){
    
    this->addChild(MyUtil::getInstance()->getWaitLayer("正在读取排名"),1000);
    MyHttpConnection::getInstance()->sendGetTopRank(pageNo);
    
}

void StartScene::displayTopRankView(CCArray* topArray) {
    
    this->scheduleOnce(schedule_selector(StartScene::removeWaitMenu), 0.2);
    CCLayer* recordLayer = dynamic_cast<CCLayer*>(this->getChildByTag(recorderLayerTag));
    recordLayer->removeChildByTag(recordContentLayerTag, true);
    CCSprite* recordBack = dynamic_cast<CCSprite*>(recordLayer->getChildByTag(recordBackSpriteTag));
    
    //    bool nextFlag  = true;
    bool preFlag = true;
    
    if (recordLayer == NULL) {
        return;
    }
    CCLayer* contentLayer = CCLayer::create();
    contentLayer->setTag(recordContentLayerTag);
    CCLayer* guding = CCLayer::create();
    contentLayer->addChild(guding);
    guding->setPosition(ccp(winSize.width/2+40-recordBack->getContentSize().width/2,winSize.height/2-recordBack->getContentSize().height/2));
    
    //    CCArray* topArray = MyJsonUtil::parseTopRank(response);
    CCLabelTTF* nolabel = CCLabelTTF::create("排行", "Arial", 30);
    nolabel->setColor(ccc3(223, 136, 42));
    nolabel->setPosition(ccp(recordBack->getContentSize().width/2-300, recordBack->getContentSize().height-80));
    guding->addChild(nolabel,2);
    
    CCLabelTTF* unionlabel = CCLabelTTF::create("联盟", "Arial", 30);
    unionlabel->setColor(ccc3(223, 136, 42));
    unionlabel->setPosition(ccp(recordBack->getContentSize().width/2-190, recordBack->getContentSize().height-80));
    guding->addChild(unionlabel,2);
    
    CCLabelTTF* namelabel = CCLabelTTF::create("昵称", "Arail", 30);
    namelabel->setColor(ccc3(223, 136, 42));
    namelabel->setPosition(ccp(recordBack->getContentSize().width/2, recordBack->getContentSize().height-80));
    guding->addChild(namelabel,2);
    
    
    
    CCLabelTTF* ranklabel = CCLabelTTF::create("军衔", "Arial", 30);
    ranklabel->setColor(ccc3(223, 136, 42));
    ranklabel->setPosition(ccp(recordBack->getContentSize().width/2+180, recordBack->getContentSize().height-80));
    guding->addChild(ranklabel,2);
    
    
    
    CCLabelTTF* powerlabel = CCLabelTTF::create("战斗力", "Arial", 30);
    powerlabel->setColor(ccc3(223, 136, 42));
    powerlabel->setPosition(ccp(recordBack->getContentSize().width/2+280, recordBack->getContentSize().height-80));
    guding->addChild(powerlabel,2);
    CCSprite* dividingLine =CCSprite::createWithSpriteFrameName("underline.png");
    dividingLine->setPosition(ccp(recordBack->getContentSize().width/2,recordBack->getContentSize().height-100));
    dividingLine->setScale(719/dividingLine->getContentSize().width);
    guding->addChild(dividingLine);
    
    CCSprite* dividingLine2 =CCSprite::createWithSpriteFrameName("underline.png");
    dividingLine2->setPosition(ccp(recordBack->getContentSize().width/2,80));
    dividingLine2->setScale(719/dividingLine2->getContentSize().width);
    guding->addChild(dividingLine2);
    
    CCObject* obj = NULL;
    topRankBean* bean = NULL;
    GXScrollView* scollView = GXScrollView::create(-500);
    scollView->setOriPosition(ccp(winSize.width/2-backSize.width/2+40,winSize.height/2-backSize.height/2+90));
    scollView->setContentSize(CCSizeMake(backSize.width, backSize.height-200));
    
    //    CCLog("matchInfo:%d",matchInfos->count()*30);
    //    float asd = -scollView->getMapSize().height;
    scollView->setPosition(ccp(winSize.width/2-backSize.width/2+40,-scollView->getMapSize().height+scollView->getViewSize().height+scollView->getOriPosition().y));
    float mapHeight = topArray->count()*20;
    int i = 0;
    char str[50] = {0};
    CCARRAY_FOREACH(topArray, obj) {
        if (i == 0) {
            bean =dynamic_cast<topRankBean*>(obj);
            sprintf(str, "%d",bean->rankNo);
            CCLabelTTF* beanNo = CCLabelTTF::create(str, "Arial", 24);
            beanNo->setPosition(ccp(backSize.width/2-300,60));
            guding->addChild(beanNo);
            sprintf(str, "%d",bean->rankNo);
            if (bean->getUnionName()->compare("") != 0 ) {
                sprintf(str, "%s",bean->getUnionName()->getCString());
                CCLabelTTF* nickname = CCLabelTTF::create(str, "Arial", 22);
                nickname->setPosition(ccp(backSize.width/2-175,60));
                guding->addChild(nickname);
                
                CCSprite* emblem = CCSprite::createWithSpriteFrameName(bean->getEmblem()->getCString());
                emblem->setScale(0.28);
                emblem->setPosition(ccp(backSize.width/2-243,60));
                guding->addChild(emblem);
            } else {
                CCLabelTTF* nickname = CCLabelTTF::create("---", "Arial", 25);
                nickname->setPosition(ccp(backSize.width/2-190,60));
                guding->addChild(nickname);
            }
            
            CCLabelTTF* nickname = CCLabelTTF::create(bean->getNickname()->getCString(), "Arial", 30);
            nickname->setPosition(ccp(backSize.width/2,60));
            guding->addChild(nickname);
            CCSprite* rankSprite = MyUtil::getInstance()->getRankSprite(bean->power);
            rankSprite->setPosition(ccp(backSize.width/2+155,60));
            rankSprite->setScale(0.6);
            guding->addChild(rankSprite);
            CCLabelTTF* rankname = CCLabelTTF::create(MyUtil::getInstance()->getRankString(bean->power),"Arial",24);
            rankname->setPosition(ccp(backSize.width/2+200,60));
            guding->addChild(rankname);
            sprintf(str, "%d",(int)(bean->power));
            CCLabelTTF* powerRank = CCLabelTTF::create(str,"Arial",24);
            powerRank->setPosition(ccp(backSize.width/2+300,60));
            guding->addChild(powerRank,2);
            
            CCSprite* powerSprite = CCSprite::createWithSpriteFrameName("powerIcon.png");
            powerSprite->setPosition(ccp(backSize.width/2+255,60));
            powerSprite->setScale(0.6);
            guding->addChild(powerSprite,2);
        } else {
            bean =dynamic_cast<topRankBean*>(obj);
            sprintf(str, "%d",bean->rankNo);
            CCLabelTTF* beanNo = CCLabelTTF::create(str, "Arial", 24);
            beanNo->setPosition(ccp(backSize.width/2-300,(mapHeight+10-20*i)*2));
            scollView->addChild(beanNo);
            
            if (bean->getUnionName()->compare("") != 0 ) {
                sprintf(str, "%s",bean->getUnionName()->getCString());
                CCLabelTTF* nickname = CCLabelTTF::create(str, "Arial", 22);
                nickname->setPosition(ccp(backSize.width/2-175,(mapHeight+10-20*i)*2));
                scollView->addChild(nickname);
                
                CCSprite* emblem = CCSprite::createWithSpriteFrameName(bean->getEmblem()->getCString());
                emblem->setScale(0.28);
                emblem->setPosition(ccp(backSize.width/2-243,(mapHeight+10-20*i)*2));
                scollView->addChild(emblem);
            } else {
                CCLabelTTF* nickname = CCLabelTTF::create("---", "Arial", 25);
                nickname->setPosition(ccp(backSize.width/2-190,(mapHeight+10-20*i)*2));
                scollView->addChild(nickname);
            }
            
            CCLabelTTF* nickname = CCLabelTTF::create(bean->getNickname()->getCString(), "Arial", 30);
            nickname->setPosition(ccp(backSize.width/2,(mapHeight+10-20*i)*2));
            scollView->addChild(nickname);
            CCSprite* rankSprite = MyUtil::getInstance()->getRankSprite(bean->power);
            rankSprite->setPosition(ccp(backSize.width/2+155,(mapHeight+10-20*i)*2));
            rankSprite->setScale(0.6);
            scollView->addChild(rankSprite);
            CCLabelTTF* rankname = CCLabelTTF::create(MyUtil::getInstance()->getRankString(bean->power),"Arial",24);
            rankname->setPosition(ccp(backSize.width/2+200,(mapHeight+10-20*i)*2));
            scollView->addChild(rankname);
            sprintf(str, "%d",(int)(bean->power));
            CCLabelTTF* powerRank = CCLabelTTF::create(str,"Arial",24);
            powerRank->setPosition(ccp(backSize.width/2+280,(mapHeight+10-20*i)*2));
            scollView->addChild(powerRank,2);
            
            //            CCSprite* powerSprite = CCSprite::createWithSpriteFrameName("powerIcon.png");
            //            powerSprite->setPosition(ccp(backSize.width/2+255,(mapHeight+10-20*i)*2));
            //            powerSprite->setScale(0.6);
            //            scollView->addChild(powerSprite,2);
            
            if (i == 1 && bean->rankNo == 1) {
                preFlag = false;
            }
            
        }
        i++;
    }
    scollView->setMapSize(CCSizeMake(200,mapHeight*2));
    scollView->setPosition(ccp(winSize.width/2-backSize.width/2+40,-scollView->getMapSize().height+scollView->getViewSize().height+scollView->getOriPosition().y));
    
    if (topArray->count()  == 21) {
        CCMenuItemSprite* nextButton =CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("nextPageButton.png"), CCSprite::createWithSpriteFrameName("nextPageButtonP.png"),this,menu_selector(StartScene::nextPageCallBack));
        scollView->addChild(nextButton);
        nextButton->setPosition(ccp(backSize.width/2+80,20));
    }
    if(preFlag) {
        CCMenuItemSprite* preButton =CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("prePageButton.png"), CCSprite::createWithSpriteFrameName("prePageButtonP.png"),this,menu_selector(StartScene::prePageCallBack));
        scollView->addChild(preButton);
        preButton->setPosition(ccp(backSize.width/2-80,20));
    }
    
    contentLayer->addChild(scollView);
    recordLayer->addChild(contentLayer);
}

void StartScene::nextPageCallBack(cocos2d::CCNode *pSender) {
    pageNo+=1;
    displayTopRankCallBack(NULL);
    //    displayTopRankView();
}

void StartScene::prePageCallBack(cocos2d::CCNode *pSender) {
    pageNo-=1;
    displayTopRankCallBack(NULL);
}

void StartScene::removeWaitMenu() {
    this->removeChildByTag(waitMenuTag, true);
}

void StartScene::loadResource() {
    CCTextureCache::sharedTextureCache()->dumpCachedTextureInfo();
    GXUtil::loadResourceUtilSucc("createui.plist","createui.pvr.ccz");
    GXUtil::loadResourceUtilSucc("tipTiled.plist", "tipTiled.pvr.ccz");
    GXUtil::loadResourceUtilSucc("armyui.plist", "armyui.pvr.ccz");
    GXUtil::loadResourceUtilSucc("armyui2.plist", "armyui2.pvr.ccz");
    GXUtil::loadResourceUtilSucc("chardialog.plist","chardialog.pvr.ccz");
    GXUtil::loadResourceUtilSucc("recordui.plist","recordui.pvr.ccz");
    GXUtil::loadResourceUtilSucc("normalButton.plist","normalButton.pvr.ccz");
    GXUtil::loadResourceUtilSucc("antiTank.plist","antiTank.png");
    GXUtil::loadResourceUtilSucc("armycardflop.plist","armycardflop.pvr.ccz");
    GXUtil::loadResourceUtilSucc("startSceneIcon.plist","startSceneIcon.pvr.ccz");
    GXUtil::loadResourceUtilSucc("huodong.plist","huodong.pvr.ccz");
    GXUtil::loadResourceUtilSucc("unionUI.plist","unionUI.pvr.ccz");
    GXUtil::loadResourceUtilSucc("shopUI.plist","shopUI.pvr.ccz");
    GXUtil::loadResourceUtilSucc("shopUI8888.plist","shopUI8888.pvr.ccz");
    GXUtil::loadResourceUtilSucc("questUI.plist","questUI.pvr.ccz");
    
    //    CCTextureCache::sharedTextureCache()->dumpCachedTextureInfo();
}

void StartScene::releaseResource() {
    
    CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile("antiTank.plist");
    CCTextureCache::sharedTextureCache()->removeTextureForKey("antiTank.png");
    
    CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile("createui.plist");
    CCTextureCache::sharedTextureCache()->removeTextureForKey("createui.pvr.ccz");
    CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile("tipTiled.plist");
    CCTextureCache::sharedTextureCache()->removeTextureForKey("tipTiled.pvr.ccz");
    CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile("chardialog.plist");
    CCTextureCache::sharedTextureCache()->removeTextureForKey("chardialog.pvr.ccz");
    CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile("recordui.plist");
    CCTextureCache::sharedTextureCache()->removeTextureForKey("recordui.pvr.ccz");
    CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile("normalButton.plist");
    CCTextureCache::sharedTextureCache()->removeTextureForKey("normalButton.pvr.ccz");
    
    
    CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile("armycardflop.plist");
    CCTextureCache::sharedTextureCache()->removeTextureForKey("armycardflop.pvr.ccz");
    
    CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile("armyui2.plist");
    CCTextureCache::sharedTextureCache()->removeTextureForKey("armyui2.pvr.ccz");
    
    CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile("armyui.plist");
    CCTextureCache::sharedTextureCache()->removeTextureForKey("armyui.pvr.ccz");
    
    CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile("startSceneIcon.plist");
    CCTextureCache::sharedTextureCache()->removeTextureForKey("startSceneIcon.pvr.ccz");
    
    CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile("questUI.plist");
    CCTextureCache::sharedTextureCache()->removeTextureForKey("questUI.pvr.ccz");
    
    CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile("huodong.plist");
    CCTextureCache::sharedTextureCache()->removeTextureForKey("huodong.pvr.ccz");
    
    CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile("unionUI.plist");
    CCTextureCache::sharedTextureCache()->removeTextureForKey("unionUI.pvr.ccz");
    
    CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile("shopUI.plist");
    CCTextureCache::sharedTextureCache()->removeTextureForKey("shopUI.pvr.ccz");
    
    CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile("shopUI8888.plist");
    CCTextureCache::sharedTextureCache()->removeTextureForKey("shopUI8888.pvr.ccz");
    
    
    
    CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile("defendNormal.plist");
    CCTextureCache::sharedTextureCache()->removeTextureForKey("defendNormal.pvr.ccz");
    
    CCTextureCache::sharedTextureCache()->removeTextureForKey("prizeLight.png");
    
    GarbageResourceCollection::getInstance()->GarbageCollection();
}

void StartScene::toChehiefSceneWait() {
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sfx_bugeiLaugh.mp3");
    this->addChild(MyUtil::getInstance()->getWaitLayer("努力加载中"),1000);
    scheduleOnce(schedule_selector(StartScene::toChehiefScene), 0.5);
}

void StartScene::toChehiefScene() {
    // 去掉MAP的注册
    MyMap* map = dynamic_cast<MyMap*>(this->getChildByTag(MainMapTag));
    updateMyData();
    map->pauseSchedulerAndActions();
    this->cleanup();
    
    MyGameInfo::getInstance()->enemyIron = 0;
    MyGameInfo::getInstance()->enemyOil = 0;
    CCScene* scene = TransitonScene::create(ChthiefSceneClassTag);
    //    long robdeltatime = 0;
    //    int i = 0;
    //    while (robdeltatime == 0) {
    //        robdeltatime = atol(MyHttpConnection::getInstance()->getRobDeltaTime()->getCString());
    //        CCLog("获得间隔时间：%ld",robdeltatime);
    //        CCAssert(i<1,"联网异常，在试一次");
    //    }
    
    CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.2,scene ,ccBLACK));
    CocosDenshion::SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
    
    
    
}

void StartScene::initBugei(unsigned long long robDeltaTime,long robMultipleTime) {
    int multipe = robDeltaTime/robMultipleTime;
    if (multipe>0) {
        int level = MyUtil::getInstance()->getLevelByExperience(MyGameInfo::getInstance()->getExperience());
        this->robMultiple = Mathlib::min(multipe,level);
        CCMenuItem*  bugeiButton = this->addBugeiButton();
        CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sfx_bugeiLaugh.mp3");
        CCMenu* menu = (CCMenu*)this->getChildByTag(UILayerTag)->getChildByTag(questMenuTag);
        this->addDisplayHuodong(menu,bugeiButton);
        
        
    }
    if (multipe>0){
        int second = robMultipleTime/1000;
        this->schedule(schedule_selector(StartScene::bugeiMultipleTimer),second,kCCRepeatForever,second-(robDeltaTime%robMultipleTime)/1000);
    }
}

void StartScene::bugeiMultipleTimer() {
    int multiple = robMultiple+1;
    int level = MyUtil::getInstance()->getLevelByExperience(MyGameInfo::getInstance()->getExperience());
    if (multiple > level) {
        return;
    }
    robMultiple = multiple;
    //    if (multiple > level/10) {
    //        CCMenu* huodongMenu = (CCMenu*)this->getChildByTag(UILayerTag)->getChildByTag(huodongMenuTag);
    CCMenu* questMenu = (CCMenu*)this->getChildByTag(UILayerTag)->getChildByTag(questMenuTag);
    CCNode* bugeiButton = questMenu->getChildByTag(bugeiButtonTag);
    if (bugeiButton == NULL) {
//        bugeiButton = addBugeiButton();
//        this->addDisplayHuodong(questMenu,(CCMenuItem*)bugeiButton);
        return;
        //            bugeiButton->setPosition(ccp(100,570-questMenu->getChildrenCount()*100));
    }
    char str[10] =  {0};
    sprintf(str,"/%d",multiple);
    ((CCLabelAtlas*)bugeiButton->getChildByTag(bugeiButtonMultipleTag))->setString(str);
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sfx_bugeiDropMoney.mp3");
    //        if (!bugeiButton->isVisible()) {
    //            bugeiButton->setVisible(true);
    //            bugeiButton->setPosition(ccp(150,(huodongMenu->getChildrenCount()-1)*130));
    //            bugeiButton->runAction(CCMoveBy::create(3,ccp(-150,0)));
    //            CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sfx_bugeiLaugh.mp3");
    //        }
    //    }
}

CCMenuItem* StartScene::addBugeiButton() {
    
    CCSprite*  normalSprite = CCSprite::createWithSpriteFrameName("huodongButton.png");
    
    MyMenuItem* bugeiButton = MyMenuItem::create(normalSprite,this,menu_selector(StartScene::toChehiefSceneWait));
    CCSprite* bugeiIcon = CCSprite::createWithSpriteFrameName("bugeiButton.png");
    bugeiIcon->setPosition(ccp(normalSprite->getContentSize().width/2,normalSprite->getContentSize().height/2+10));
    bugeiIcon->setScale(Mathlib::min(70/bugeiIcon->getContentSize().width,70/bugeiIcon->getContentSize().height));
    
    normalSprite->addChild(bugeiIcon);
    //    CCMenuItemSprite* bugeiButton = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("bugeiButton.png"),CCSprite::createWithSpriteFrameName("bugeiButtonP.png"),this,menu_selector(StartScene::toChehiefSceneWait));
    bugeiButton->setTag(bugeiButtonTag);
    
    //    CCSprite* bling1_1 = CCSprite::create("armyprizeLight.png");
    //    bling1_1->setPosition(ccp(bugeiButton->getContentSize().width/2,bugeiButton->getContentSize().height/2));
    //    bling1_1->setScale(0.7);
    //    bling1_1->runAction(CCRepeatForever::create(CCRotateBy::create(1000, 7200)));
    //    bugeiButton->addChild(bling1_1,-1);
    //
    //    CCSprite* bling1_2 = CCSprite::create("armyprizeLight.png");
    //    bling1_2->setPosition(ccp(bugeiButton->getContentSize().width/2,bugeiButton->getContentSize().height/2));
    //    bling1_2->runAction(CCRepeatForever::create(CCRotateBy::create(1000, -7200)));
    //    bling1_2->setScale(0.5);
    //    bugeiButton->addChild(bling1_2,-1);
    
    char str[5] = {0};
    sprintf(str,"/%d",robMultiple);
    CCLabelAtlas* beilv = CCLabelAtlas::create(str, "number6.png", 24, 36, '/');
    beilv->setAnchorPoint(ccp(0,0));
    beilv->setScale(0.7);
    beilv->setTag(bugeiButtonMultipleTag);
    bugeiButton->addChild(beilv);
    beilv->setPosition(ccp(5,0));
    
    return bugeiButton;
}

void StartScene::displayConmunication(CCMenuItem* item) {
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sfx_click.mp3");
    CCMenuItemToggle* toggle = ((CCMenuItemToggle*)item);
    if(toggle->getSelectedIndex() == 1) {
        
        CCSprite* grayUnion = CCSprite::createWithSpriteFrameName("unionIcon.png");
        grayUnion->setColor(ccGRAY);
        CCMenuItemSprite* unionButton = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("unionIcon.png"),grayUnion,this,menu_selector(StartScene::toUnionCallBack));
        CCSprite* unionBack = CCSprite::createWithSpriteFrameName("mainMenuBack.png");
        unionBack->setPosition(ccp(unionButton->getContentSize().width/2,unionButton->getContentSize().height/2));
        unionButton->addChild(unionBack,-1);
        unionButton->runAction(CCEaseElasticOut::create(CCMoveTo::create(0.5,ccp(-100,0)),1));
        
        
        CCSprite* grayShow = CCSprite::createWithSpriteFrameName("showIcon.png");
        grayShow->setColor(ccGRAY);
        CCMenuItemSprite* showButton = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("showIcon.png"),grayShow,this,menu_selector(StartScene::toShowCallBack));
        CCSprite* showBack = CCSprite::createWithSpriteFrameName("mainMenuBack.png");
        showBack->setPosition(ccp(showButton->getContentSize().width/2,showButton->getContentSize().height/2));
        showButton->addChild(showBack,-1);
        showButton->runAction(CCEaseElasticOut::create(CCMoveTo::create(0.5,ccp(-200,0)),1));
        
        MyPriorityMenu* menu = MyPriorityMenu::create(-502,unionButton,showButton, NULL);
        menu->setPosition(ccp(item->getContentSize().width/2,item->getContentSize().height/2));
        menu->setTag(controlSecondMenuTag);
        
        item->addChild(menu,2);
        
    } else {
        item->removeChildByTag(controlSecondMenuTag,true);
    }
}

void StartScene::displayVip(CCMenuItem* item) {
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sfx_click.mp3");
    CCMenuItemToggle* toggle = ((CCMenuItemToggle*)item);
    if(toggle->getSelectedIndex() == 1) {
        //关闭VIP
        
        CCSprite* grayShop = CCSprite::createWithSpriteFrameName("vipShopIcon.png");
        grayShop->setColor(ccGRAY);
        CCMenuItemSprite* shopButton = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("vipShopIcon.png"),grayShop,this,menu_selector(StartScene::toShopCallBackWait));
        shopButton->runAction(CCEaseElasticOut::create(CCMoveTo::create(0.5,ccp(-100,0)),1));
        CCSprite* shopBack = CCSprite::createWithSpriteFrameName("mainMenuBack.png");
        shopBack->setPosition(ccp(shopButton->getContentSize().width/2,shopButton->getContentSize().height/2));
        shopButton->addChild(shopBack,-1);
        
        CCSprite* graySK = CCSprite::createWithSpriteFrameName("vipArcheiveIcon.png");
        graySK->setColor(ccGRAY);
        CCMenuItemSprite* skButton = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("vipArcheiveIcon.png"),graySK,this,menu_selector(StartScene::toYiJianShouKuang));
        CCSprite* skBack = CCSprite::createWithSpriteFrameName("mainMenuBack.png");
        skBack->setPosition(ccp(skButton->getContentSize().width/2,skButton->getContentSize().height/2));
        skButton->addChild(skBack,-1);
        skButton->runAction(CCEaseElasticOut::create(CCMoveTo::create(0.5,ccp(-200,0)),1));
        
        CCSprite* grayUp = CCSprite::createWithSpriteFrameName("vipUpdateIcon.png");
        grayUp->setColor(ccGRAY);
        CCMenuItemSprite* upButton = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("vipUpdateIcon.png"),grayUp,this,menu_selector(StartScene::toOneKeyUpdate));
        CCSprite* upBack = CCSprite::createWithSpriteFrameName("mainMenuBack.png");
        upBack->setPosition(ccp(upButton->getContentSize().width/2,upButton->getContentSize().height/2));
        upButton->addChild(upBack,-1);
        upButton->runAction(CCEaseElasticOut::create(CCMoveTo::create(0.5,ccp(-300,0)),1));
        
        CCSprite* grayBoost = CCSprite::createWithSpriteFrameName("vipBoost.png");
        grayBoost->setColor(ccGRAY);
        CCMenuItemSprite* boostButton = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("vipBoost.png"),grayBoost,this,menu_selector(StartScene::toBoostProduce));
        CCSprite* boostBack = CCSprite::createWithSpriteFrameName("mainMenuBack.png");
        boostBack->setPosition(ccp(boostButton->getContentSize().width/2,boostButton->getContentSize().height/2));
        boostButton->addChild(boostBack,-1);
        boostButton->runAction(CCEaseElasticOut::create(CCMoveTo::create(0.5,ccp(-500,0)),1));
        
        CCSprite* grayConversion = CCSprite::createWithSpriteFrameName("vipConversion.png");
        grayConversion->setColor(ccGRAY);
        CCMenuItemSprite* conversionButton = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("vipConversion.png"),grayConversion,this,menu_selector(StartScene::toResourceConversion));
        CCSprite* conversionBack = CCSprite::createWithSpriteFrameName("mainMenuBack.png");
        conversionBack->setPosition(ccp(conversionButton->getContentSize().width/2,conversionButton->getContentSize().height/2));
        conversionButton->addChild(conversionBack,-1);
        conversionButton->runAction(CCEaseElasticOut::create(CCMoveTo::create(0.5,ccp(-400,0)),1));
        
        MyPriorityMenu* menu = MyPriorityMenu::create(-502,shopButton,skButton,upButton,conversionButton,boostButton, NULL);
        menu->setPosition(ccp(winSize.width-480,200));
        menu->setPosition(ccp(item->getContentSize().width/2,item->getContentSize().height/2));
        menu->setTag(controlSecondMenuTag);
        
        item->addChild(menu,2);
        
    } else {
        item->removeChildByTag(controlSecondMenuTag,true);
    }
}

void StartScene::toCancelSecond() {
    //    CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sfx_click.mp3");
    CCMenuItemToggle* showItem = ((CCMenuItemToggle*)controlMenu->getChildByTag(showToggleTag));
    if (showItem->getSelectedIndex() == 1) {
        showItem->removeChildByTag(controlSecondMenuTag,true);
        showItem->setSelectedIndex(0);
    }
    
    CCMenuItemToggle* vipItem = ((CCMenuItemToggle*)controlMenu->getChildByTag(vipToggleTag));
    if (vipItem->getSelectedIndex() == 1) {
        vipItem->removeChildByTag(controlSecondMenuTag,true);
        vipItem->setSelectedIndex(0);
    }
}

void StartScene::toUnionCallBack() {
    cancelAllDialog();
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sfx_union.mp3");
    if (this->getChildByTag(MainMapTag)->getChildByTag(lianluozhongxinTag) != NULL) {
        this->addChild(MyUtil::getInstance()->getWaitLayer("努力加载中"));
        MyHttpConnection::getInstance()->readUnionByItitiaId();
    } else {
        this->getChildByTag(resourceBarTag)->setVisible(false);
        //TODO 改声音
        //    CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sfx_army.mp3");
        
        
        CCLayer* unionLayer = CCLayer::create();
        CCSprite* back = MyUtil::getInstance()->getUnionBack();
        back->setAnchorPoint(ccp(0,0));
        unionLayer->addChild(back);
        this->addChild(unionLayer);
        unionLayer->setTag(creatorLayerTag);
        
        CCLayer* displayLayer = CCLayer::create();
        displayLayer->setTag(displayUnionLayerTag);
        displayLayer->setPosition(ccp(0,0));
        unionLayer->addChild(displayLayer,3);
        
        CCSprite* up =  CCSprite::createWithSpriteFrameName("unionCommonCloseButton.png");
        up->setContentSize(CCSizeMake(100,100));
        
        CCMenuItemSprite* quitItem = CCMenuItemSprite::create(up, CCSprite::createWithSpriteFrameName("unionCommonCloseButtonP.png.png"),this,menu_selector( StartScene::quitCreator));
        
        GXShieldTouchMenuItem* shild = GXShieldTouchMenuItem::create();
        shild->setContentSize(winSize);
        shild->setPosition(ccp(winSize.width/2,winSize.height/2));
        
        MyPriorityMenu* menu = MyPriorityMenu::create(-503,quitItem,shild,NULL);
        menu->setPosition(ccp(0,0));
        
        quitItem->setPosition(ccp(winSize.width-61,winSize.height+2));
        unionLayer->addChild(menu,2);
        
        
        CCSprite* lightSprite = CCSprite::createWithSpriteFrameName("creatorLight.png");
        lightSprite->setOpacity(153);
        lightSprite->setPosition(ccp(winSize.width/2,winSize.height/2+50));
        unionLayer->addChild(lightSprite);
        
        CCSprite* buildingSprite = CCSprite::createWithSpriteFrameName("communication.png");
        buildingSprite->setAnchorPoint(ccp(0.4,0.45));
        buildingSprite->setScale(1.2);
        buildingSprite->setPosition(ccp(winSize.width/2,winSize.height/2+50));
        unionLayer->addChild(buildingSprite);
        
        CCLabelTTF* needTipLabel = CCLabelTTF::create("修复或建造联络中心\n才可以和别的基地联合作战", "宋体", 40,CCSizeZero,kCCTextAlignmentCenter, kCCVerticalTextAlignmentTop);
        needTipLabel->setColor(ccc3(230, 207, 185));
        needTipLabel->setPosition(ccp(winSize.width/2,winSize.height/2-130));
        unionLayer->addChild(needTipLabel);
    }
    
}

void StartScene::toUnionMainUI() {
    removeWaitMenu();
    cancelAllDialog();
    this->getChildByTag(resourceBarTag)->setVisible(false);
    //TODO 改声音
    //    CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sfx_army.mp3");
    
    
    CCLayer* unionLayer = CCLayer::create();
    CCSprite* back = MyUtil::getInstance()->getUnionBack();
    back->setAnchorPoint(ccp(0,0));
    unionLayer->addChild(back);
    this->addChild(unionLayer);
    unionLayer->setTag(creatorLayerTag);
    
    CCLayer* displayLayer = CCLayer::create();
    displayLayer->setTag(displayUnionLayerTag);
    displayLayer->setPosition(ccp(0,0));
    unionLayer->addChild(displayLayer,3);
    
    CCSprite* up = CCSprite::createWithSpriteFrameName("unionCommonCloseButton.png");
    up->setContentSize(CCSizeMake(100,100));
    
    CCMenuItemSprite* quitItem = CCMenuItemSprite::create(up, CCSprite::createWithSpriteFrameName("unionCommonCloseButtonP.png.png"),this,menu_selector( StartScene::quitCreator));
    
    GXShieldTouchMenuItem* shild = GXShieldTouchMenuItem::create();
    shild->setContentSize(winSize);
    shild->setPosition(ccp(winSize.width/2,winSize.height/2));
    
    MyPriorityMenu* menu = MyPriorityMenu::create(-503,quitItem,shild,NULL);
    menu->setPosition(ccp(0,0));
    
    quitItem->setPosition(ccp(winSize.width-61,winSize.height+2));
    unionLayer->addChild(menu,2);
    
    CCSprite* banyue = CCSprite::createWithSpriteFrameName("banyuan.png");
    banyue->setScale(1.282);
    banyue->setAnchorPoint(ccp(0,0));
    banyue->setPosition(ccp(0,0));
    unionLayer->addChild(banyue);
    
    CCSprite* sprite = CCSprite::createWithSpriteFrameName(MyGameInfo::getInstance()->getUnionBean()->getEmblem()->getCString());
    //        sprite->setScale();
    sprite->setPosition(ccp(150,480));
    sprite->setScale(Mathlib::min(226/sprite->getContentSize().width,200/sprite->getContentSize().height));
    unionLayer->addChild(sprite);
    
    
    char str[30] = {0};
    sprintf(str,"『%s』", MyGameInfo::getInstance()->getUnionBean()->getName()->getCString());
    CCLabelTTF* nameLabel = CCLabelTTF::create(str,"Arial",33);
    nameLabel->setPosition(ccp(150,350));
    nameLabel->setColor(ccc3(240,147,1));
    
    
    CCSprite* di = CCSprite::create("whiteImage.jpg");
    di->setColor(ccc3(0,0,0));
    di->setOpacity(100);
    di->setScaleX(nameLabel->getContentSize().width/di->getContentSize().width);
    di->setScaleY(nameLabel->getContentSize().height/di->getContentSize().height);
    di->setPosition(ccp(150,350));
    unionLayer->addChild(di);
    unionLayer->addChild(nameLabel);
    
    
    CCMenuItemSprite* messageButton = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("unionMessageButton.png"), CCSprite::createWithSpriteFrameName("unionMessageButtonP.png"),this,menu_selector(StartScene::toUnionMessage));
    //    totalItem->setPosition(ccp(263,493));
    messageButton->setPosition(ccp(150,280));
    
    
    CCMenuItemSprite* infoButton = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("unionInfoButton.png"), CCSprite::createWithSpriteFrameName("unionInfoButtonP.png"),this,menu_selector(StartScene::toUnionInfo));
    //    groundItem->setPosition(ccp(263,355));
    infoButton->setPosition(ccp(150,210));
    
    CCMenuItemSprite* memberButton = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("unionMemberButton.png"), CCSprite::createWithSpriteFrameName("unionMemberButtonP.png"),this,menu_selector(StartScene::toUnionMember));
    //    armorItem->setPosition(ccp(263,215));
    memberButton->setPosition(ccp(150,140));
    GXRadioMenu* radio = GXRadioMenu::create(-503, messageButton,memberButton,infoButton,NULL);
    
    CCMenuItemSprite* managerButton = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("unionManagerButton.png"), CCSprite::createWithSpriteFrameName("unionManagerButtonP.png"),this,menu_selector(StartScene::toUnionManager));
    //    airItem->setPosition(ccp(263,70));
    managerButton->setPosition(ccp(150,70));
    radio->addChild(managerButton);
    
    
    
    
    radio->setPosition(ccp(0,0));
    
    unionLayer->addChild(radio);
    
    //        CCSprite* kuang =  MyUtil::getInstance()->getZhijiaoBox(600,500);
    //        kuang->setPosition(ccp(590,320));
    //        displayLayer->addChild(kuang);
    
}

void StartScene::toUnionJoinOrCreate() {
    removeWaitMenu();
    this->getChildByTag(resourceBarTag)->setVisible(false);
    //TODO 改声音
    //    CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sfx_army.mp3");
    
    CCLayer* unionLayer = CCLayer::create();
    CCSprite* back = MyUtil::getInstance()->getUnionBack();
    back->setAnchorPoint(ccp(0,0));
    unionLayer->addChild(back);
    this->addChild(unionLayer);
    unionLayer->setTag(creatorLayerTag);
    
    CCLayer* displayLayer = CCLayer::create();
    displayLayer->setTag(displayUnionLayerTag);
    displayLayer->setPosition(ccp(0,0));
    unionLayer->addChild(displayLayer,3);
    
    CCSprite* up = CCSprite::createWithSpriteFrameName("unionCommonCloseButton.png");
    up->setContentSize(CCSizeMake(100,100));
    
    CCMenuItemSprite* quitItem = CCMenuItemSprite::create(up, CCSprite::createWithSpriteFrameName("unionCommonCloseButtonP.png.png"),this,menu_selector( StartScene::quitCreator));
    
    GXShieldTouchMenuItem* shild = GXShieldTouchMenuItem::create();
    shild->setContentSize(winSize);
    shild->setPosition(ccp(0,0));
    shild->setAnchorPoint(ccp(0,0));
    
    MyPriorityMenu* menu = MyPriorityMenu::create(-503,quitItem,shild,NULL);
    menu->setPosition(ccp(0,0));
    
    quitItem->setPosition(ccp(winSize.width-61,winSize.height+2));
    unionLayer->addChild(menu,2);
    
    
    CCSprite* sprite = CCSprite::createWithSpriteFrameName("unionCommonEmblem.png");
    sprite->setScale(1.25);
    sprite->setPosition(ccp(winSize.width/2,winSize.height/2));
    displayLayer->addChild(sprite);
    
    CCMenuItemSprite* joinUnion = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("unionJoinUnion.png"),CCSprite::createWithSpriteFrameName("unionJoinUnionP.png"),this,menu_selector(StartScene::toUnionJoin));
    joinUnion->setPosition(ccp(winSize.width/2-250,winSize.height/2));
    joinUnion->setScale(2);
    
    CCMenuItemSprite* createUnion = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("unionCreateUnion.png"),CCSprite::createWithSpriteFrameName("unionCreateUnionP.png"),this,menu_selector(StartScene::toCreateUnion));
    createUnion->setPosition(ccp(winSize.width/2+250,winSize.height/2));
    createUnion->setScale(2);
    
    MyPriorityMenu* controlMenu = MyPriorityMenu::create(-511,createUnion,joinUnion,NULL);
    controlMenu->setPosition(ccp(0,0));
    displayLayer->addChild(controlMenu);
    
    
}

void StartScene::toUnionJoin() {
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sfx_click.mp3");
    this->addChild(MyUtil::getInstance()->getWaitLayer("努力加载中"));
    MyHttpConnection::getInstance()->getAllUnionByPage(1,99);
}

void StartScene::displayUnionJoin(CCArray* unionArray) {
    removeWaitMenu();
    if (unionArray->count() == 0) {
        this->addChild(MyUtil::getInstance()->getCommonTipDialog(CCString::create("暂时没有联盟，创建一个吧！"),this,menu_selector(StartScene::cancelTipDialog),0));
        return;
    }
    this->getChildByTag(creatorLayerTag)->removeChildByTag(displayUnionLayerTag,true);
    CCLayer* displayUnionLayer = CCLayer::create();
    displayUnionLayer->setTag(displayUnionLayerTag);
    
    CCSprite* dividingLine = CCSprite::createWithSpriteFrameName("uiDialogCommonLine.png");
    dividingLine->setScaleX(960/dividingLine->getContentSize().width);
    dividingLine->setPosition(ccp(winSize.width/2,185));
    
    CCSprite* levelIcon = CCSprite::createWithSpriteFrameName("levelIcon.png");
    
    levelIcon->setScale(0.8);
    
    levelIcon->setPosition(ccp(winSize.width/2-204,139));
    
    CCSprite* memberIcon = CCSprite::createWithSpriteFrameName("memberIcon.png");
    memberIcon->setPosition(ccp(winSize.width/2+119.5,139));
    
    
    
    CCMenuItemSprite* watchButton = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("unionJoinWatch.png"),CCSprite::createWithSpriteFrameName("unionJoinWatchP.png"));
    watchButton->setPosition(ccp(100,139));
    
    CCMenuItemSprite* joinButton = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("unionJoinJoin.png"),CCSprite::createWithSpriteFrameName("unionJoinJoinP.png"),this,menu_selector(StartScene::toSureJoin));
    joinButton->setPosition(ccp(winSize.width-100,139));
    
    MyPriorityMenu* menu = MyPriorityMenu::create(-506,watchButton,joinButton,NULL);
    menu->setPosition(ccp(0,0));
    
    
    
    displayUnionLayer->addChild(dividingLine);
    displayUnionLayer->addChild(levelIcon);
    displayUnionLayer->addChild(memberIcon);
    displayUnionLayer->addChild(menu);
    
    
    UnionJoinScroll* scroll = UnionJoinScroll::create(-505,unionArray);
    displayUnionLayer->addChild(scroll);
    scroll->scaleDis();
    joinButton->setUserObject(scroll);
    
    this->getChildByTag(creatorLayerTag)->addChild(displayUnionLayer);
}

void StartScene::toSureJoin(CCMenuItem* item) {
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sfx_click.mp3");
    UnionJoinScroll* scroll = (UnionJoinScroll*)item->getUserObject();
    UnionBean* selectUnion = scroll->getSelectUnion();
    CCLayer* tipLayer = CCLayer::create();
    CCSprite* back = MyUtil::getInstance()->getDialogBack();
    back->setPosition(ccp(winSize.width/2,winSize.height/2));
    CCSprite* black = CCSprite::create("whiteImage.jpg");
    black->setColor(ccc3(0,0,0));
    black->setOpacity(180);
    black->setPosition(ccp(winSize.width/2,winSize.height/2));
    black->setScaleX(winSize.width/black->getContentSize().width);
    black->setScaleY(winSize.height/black->getContentSize().height);
    CCMenuItemSprite* sureItem = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("dialogsure.png"), CCSprite::createWithSpriteFrameName("dialogsurep.png"),this,menu_selector(StartScene::sendJoinUnion));
    sureItem->setUserObject(selectUnion);
    CCMenuItemSprite* cancelItem =CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("dialogcancel.png"), CCSprite::createWithSpriteFrameName("dialogcancelp.png"),this,menu_selector(StartScene::cancelTipDialog));
    MyPriorityMenu* menu = MyPriorityMenu::create(-506,sureItem,cancelItem,NULL);
    menu->alignItemsHorizontallyWithPadding(30);
    
    GXShieldTouchMenuItem* shield = GXShieldTouchMenuItem::create();
    shield->setContentSize(CCSizeMake(winSize.width, winSize.height));
    shield->setAnchorPoint(ccp(0.5,0.5));
    shield->setPosition(ccp(-120,100));
    menu->addChild(shield,4);
    
    char str[300] = {0};
    sprintf(str,"确定要加入『%s』联盟吗？",selectUnion->getName()->getCString());
    menu->setPosition(ccp(winSize.width/2+120, winSize.height/2-80));
    
    CCLabelTTF* label = CCLabelTTF::create(str, "Arial", 32,CCSizeMake(400,0), kCCTextAlignmentCenter, kCCVerticalTextAlignmentTop);
    label->setColor(ccc3(230, 207, 185));
    label->setPosition(ccp(winSize.width/2+120,winSize.height/2+40));
    tipLayer->addChild(label,5);
    
    tipLayer->addChild(black);
    tipLayer->addChild(back);
    tipLayer->addChild(menu);
    tipLayer->setTag(joinUnionTipLayerTag);
    this->addChild(tipLayer);
}

void StartScene::sendJoinUnion(CCMenuItem* item) {
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sfx_click.mp3");
    item->getParent()->getParent()->removeFromParentAndCleanup(true);
    
    UnionBean* selectUnion = (UnionBean*)item->getUserObject();
    MyHttpConnection::getInstance()->sendJoinUnion(selectUnion->unionId);
    this->addChild(MyUtil::getInstance()->getCommonTipDialog(CCString::create("消息已发送，等待对方接收中！"),this,menu_selector(StartScene::cancelTipDialog),0));
    
}

void StartScene::toCreateUnion() {
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sfx_click.mp3");
    this->getChildByTag(creatorLayerTag)->removeChildByTag(displayUnionLayerTag,true);
    CCLayer* displayUnionLayer = CCLayer::create();
    CCSprite* kuangBack = MyUtil::getInstance()->getCreateUnionBack();
    kuangBack->setPosition(ccp(winSize.width/2,winSize.height/2));
    displayUnionLayer->setTag(displayUnionLayerTag);
    displayUnionLayer->addChild(kuangBack);
    
    CCSprite* emblem1Gray = CCSprite::createWithSpriteFrameName("unionEmblem1.png");
    emblem1Gray->setColor(ccGRAY);
    CCMenuItemSprite* emblem1 = CCMenuItemSprite::create(emblem1Gray,CCSprite::createWithSpriteFrameName("unionEmblem1.png"),this,menu_selector(StartScene::switchEmblem));
    emblem1->setUserObject(CCString::create("unionEmblem1.png"));
    emblem1->setScale(0.8);
    
    CCSprite* emblem2Gray = CCSprite::createWithSpriteFrameName("unionEmblem2.png");
    emblem2Gray->setColor(ccGRAY);
    CCMenuItemSprite* emblem2 = CCMenuItemSprite::create(emblem2Gray,CCSprite::createWithSpriteFrameName("unionEmblem2.png"),this,menu_selector(StartScene::switchEmblem));
    emblem2->setUserObject(CCString::create("unionEmblem2.png"));
    emblem2->setScale(0.8);
    
    CCSprite* emblem3Gray = CCSprite::createWithSpriteFrameName("unionEmblem3.png");
    emblem3Gray->setColor(ccGRAY);
    CCMenuItemSprite* emblem3 = CCMenuItemSprite::create(emblem3Gray,CCSprite::createWithSpriteFrameName("unionEmblem3.png"),this,menu_selector(StartScene::switchEmblem));
    emblem3->setUserObject(CCString::create("unionEmblem3.png"));
    emblem3->setScale(0.7);
    
    CCSprite* emblem4Gray = CCSprite::createWithSpriteFrameName("unionEmblem4.png");
    emblem4Gray->setColor(ccGRAY);
    CCMenuItemSprite* emblem4 = CCMenuItemSprite::create(emblem4Gray,CCSprite::createWithSpriteFrameName("unionEmblem4.png"),this,menu_selector(StartScene::switchEmblem));
    emblem4->setUserObject(CCString::create("unionEmblem4.png"));
    emblem4->setScale(0.65);
    
    GXRadioMenu* radio = GXRadioMenu::create(-505, emblem1,emblem2,emblem3,emblem4,NULL);
    radio->setPosition(ccp(winSize.width/2-335,320));
    radio->alignItemsVerticallyWithPadding(2);
    displayUnionLayer->addChild(radio);
    radio->setSelect(0);
    
    
    CCSprite* kuang1 = MyUtil::getInstance()->getLineBox(250,250);
    kuang1->setPosition(ccp(winSize.width/2-120,280));
    displayUnionLayer->addChild(kuang1);
    
    
    
    CCLabelTTF* emblemTip = CCLabelTTF::create("联盟徽章","Arial",30);
    emblemTip->setAnchorPoint(ccp(0.5,0.5));
    emblemTip->setPosition(ccp(winSize.width/2-120,425));
    emblemTip->setColor(ccc3(240,147,1));
    displayUnionLayer->addChild(emblemTip);
    
    CCSprite* kuang2 = MyUtil::getInstance()->getLineBox(240,50);
    kuang2->setPosition(ccp(winSize.width/2+255,415));
    displayUnionLayer->addChild(kuang2);
    
    CCLabelTTF* nameTip = CCLabelTTF::create("联盟名称","Arial",30);
    nameTip->setAnchorPoint(ccp(0,0.5));
    nameTip->setPosition(ccp(winSize.width/2+10,415));
    nameTip->setColor(ccc3(240,147,1));
    displayUnionLayer->addChild(nameTip);
    
    CCTextFieldTTF* nameTextField = CCTextFieldTTF::textFieldWithPlaceHolder("点击此处输入联盟名称","Arial",20);
    nameTextField->setAnchorPoint(ccp(0,0.5));
    nameTextField->setPosition(ccp(winSize.width/2+150,415));
    nameTextField->setColor(ccc3(240,147,1));
    displayUnionLayer->addChild(nameTextField);
    nameTextField->setTag(createUnionNameTextTag);
    
    
    
    CCSprite* nameSprite = CCSprite::create("transparent.png");
    nameSprite->setScaleX(240/nameSprite->getContentSize().width);
    nameSprite->setScaleY(60/nameSprite->getContentSize().height);
    nameSprite->setContentSize(CCSizeMake(240,60));
    MyMenuItem* changeNameButton = MyMenuItem::create(nameSprite, this,menu_selector(StartScene::displayUnionIME));
    changeNameButton->setAnchorPoint(ccp(0,0.5));
    changeNameButton->setPosition(ccp(winSize.width/2+130,415));
    changeNameButton->setUserObject(nameTextField);
    changeNameButton->setUserData((void*)30);
    
    CCSprite* kuang3 = MyUtil::getInstance()->getLineBox(300,150);
    kuang3->setPosition(ccp(winSize.width/2+230,265));
    displayUnionLayer->addChild(kuang3);
    
    CCLabelTTF* xuanyanTip = CCLabelTTF::create("联盟宣言","Arial",30);
    xuanyanTip->setAnchorPoint(ccp(0,0.5));
    xuanyanTip->setPosition(ccp(winSize.width/2+10,360));
    xuanyanTip->setColor(ccc3(240,147,1));
    displayUnionLayer->addChild(xuanyanTip);
    
    CCTextFieldTTF* descTextField = CCTextFieldTTF::textFieldWithPlaceHolder("点击此处输入联盟宣言，30字以内",CCSizeMake(290,130), kCCTextAlignmentLeft,"Arial",20);
    descTextField->setAnchorPoint(ccp(0,1));
    descTextField->setPosition(ccp(winSize.width/2+90,330));
    descTextField->setColor(ccc3(240,147,1));
    displayUnionLayer->addChild(descTextField);
    descTextField->setTag(createUnionDesTextTag);
    
    CCSprite* descSprite = CCSprite::create("transparent.png");
    descSprite->setScaleX(295/descSprite->getContentSize().width);
    descSprite->setScaleY(130/descSprite->getContentSize().height);
    descSprite->setContentSize(CCSizeMake(400,250));
    MyMenuItem* changeDescButton = MyMenuItem::create(descSprite, this,menu_selector(StartScene::displayUnionIME));
    changeDescButton->setAnchorPoint(ccp(0,0.5));
    changeDescButton->setPosition(ccp(winSize.width/2+90,325));
    changeDescButton->setUserObject(descTextField);
    changeDescButton->setUserData((void*)20);
    
    CCSprite* emblem = CCSprite::createWithSpriteFrameName("unionCommonEmblem.png");
    emblem->setPosition(ccp(winSize.width/2,winSize.height/2+200));
    emblem->setScale(0.8);
    displayUnionLayer->addChild(emblem);
    
    CCMenuItemSprite* item = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("unionSureButton.png"),CCSprite::createWithSpriteFrameName("unionSureButtonP.png"),this,menu_selector(StartScene::sureCreateUnion));
    item->setPosition(ccp(winSize.width/2+230,140));
    MyPriorityMenu* menu = MyPriorityMenu::create(-505,item,changeNameButton,changeDescButton,NULL);
    menu->setPosition(ccp(0,0));
    displayUnionLayer->addChild(menu);
    
    this->getChildByTag(creatorLayerTag)->addChild(displayUnionLayer);
}

void StartScene::displayUnionIME(CCMenuItem* item) {
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sfx_click.mp3");
    CCTextFieldTTF* textField = (CCTextFieldTTF*)item->getUserObject();
    textField->attachWithIME();
    //    CCInteger* fontSize = (CCInteger*)item->getUserData();
    //    textField->setFontSize(fontSize->getValue());
    int fontSize = (int)item->getUserData();
    textField->setFontSize(fontSize);
}

void StartScene::sureCreateUnion(CCMenuItem* item) {
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sfx_click.mp3");
    CCNode* parent = item->getParent()->getParent();
    CCLayer* tipLayer = CCLayer::create();
    CCTextFieldTTF* name = (CCTextFieldTTF*)parent->getChildByTag(createUnionNameTextTag);
    CCTextFieldTTF* desc = (CCTextFieldTTF*)parent->getChildByTag(createUnionDesTextTag);
    CCSprite* back = MyUtil::getInstance()->getDialogBack();
    back->setPosition(ccp(winSize.width/2,winSize.height/2));
    CCSprite* black = CCSprite::create("whiteImage.jpg");
    black->setColor(ccc3(0,0,0));
    black->setOpacity(180);
    black->setPosition(ccp(winSize.width/2,winSize.height/2));
    black->setScaleX(winSize.width/black->getContentSize().width);
    black->setScaleY(winSize.height/black->getContentSize().height);
    char str[100] = {0};
    CCMenuItemSprite* sureItem = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("dialogsure.png"), CCSprite::createWithSpriteFrameName("dialogsurep.png"),this,menu_selector(StartScene::toSendCreateUnionCmd));
    CCMenuItemSprite* cancelItem =CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("dialogcancel.png"), CCSprite::createWithSpriteFrameName("dialogcancelp.png"),this,menu_selector(StartScene::cancelTipDialog));
    MyPriorityMenu* menu  = NULL;
    if (strlen(name->getString()) <= 15 && strlen(name->getString()) > 3) {
        
        if (strlen(desc->getString()) <= 90) {
            
            if (MyGameInfo::getInstance()->getResource(gloryTag)>30000 && MyGameInfo::getInstance()->getResource(ironTag)>5000000) {
                
                CCSprite* ori = (CCSprite*)parent->getChildByTag(createUnionEmblemTag);
                CCSprite* emblem =  CCSprite::createWithTexture(ori->getTexture(),ori->getTextureRect());
                emblem->setTextureRect(ori->getTextureRect(), ori->isTextureRectRotated(), ori->getContentSize());
                emblem->setPosition(ccp(winSize.width/2-150,winSize.height/2+40));
                
                back = MyUtil::getInstance()->getDialogBackNoGirl();
                back->setPosition(ccp(winSize.width/2,winSize.height/2));
                CCLabelTTF* label1 = CCLabelTTF::create("联盟名称：", "宋体", 25,CCSizeZero, kCCTextAlignmentLeft, kCCVerticalTextAlignmentTop);
                label1->setColor(ccc3(230, 207, 185));
                label1->setPosition(ccp(winSize.width/2+15,winSize.height/2+120));
                
                sprintf(str,"『%s』",name->getString());
                CCLabelTTF* label2 = CCLabelTTF::create(str, "Arial", 30,CCSizeZero, kCCTextAlignmentLeft, kCCVerticalTextAlignmentTop);
                label2->setColor(ccc3(249, 155, 6));
                label2->setPosition(ccp(winSize.width/2+170,winSize.height/2+120));
                
                CCLabelTTF* label3 = CCLabelTTF::create("联盟宣言：", "宋体", 25,CCSizeZero, kCCTextAlignmentLeft, kCCVerticalTextAlignmentTop);
                label3->setColor(ccc3(230, 207, 185));
                label3->setPosition(ccp(winSize.width/2+15,winSize.height/2+80));
                
                sprintf(str,"%s",desc->getString());
                CCLabelTTF* label4 = CCLabelTTF::create(str, "Arial", 21,CCSizeMake(320,200), kCCTextAlignmentLeft, kCCVerticalTextAlignmentTop);
                label4->setAnchorPoint(ccp(0.5,1));
                label4->setColor(ccc3(249, 155, 6));
                label4->setPosition(ccp(winSize.width/2+120,winSize.height/2+60));
                
                CCLabelTTF* label5 = CCLabelTTF::create("花费：", "宋体", 25,CCSizeZero, kCCTextAlignmentLeft, kCCVerticalTextAlignmentTop);
                label5->setColor(ccc3(230, 207, 185));
                label5->setPosition(ccp(winSize.width/2-10,winSize.height/2-10));
                
                CCSprite* costIcon1 = MyUtil::getInstance()->getResourceIcon(gloryTag);
                costIcon1->setPosition(ccp(winSize.width/2+60,winSize.height/2-30));
                costIcon1->setScale(0.8);
                
                CCLabelAtlas* costLabel1 = CCLabelAtlas::create("30000", "number6.png", 24, 36, '/');
                costLabel1->setPosition(ccp(winSize.width/2+100,winSize.height/2-40));
                costLabel1->setScale(0.7);
                costLabel1->setColor(ccc3(231,219,138));
                
                CCSprite* costIcon2 = MyUtil::getInstance()->getResourceIcon(ironTag);
                costIcon2->setPosition(ccp(winSize.width/2+60,winSize.height/2-70));
                costIcon2->setScale(0.5);
                
                CCLabelAtlas* costLabel2 = CCLabelAtlas::create("5000000", "number6.png", 24, 36, '/');
                costLabel2->setPosition(ccp(winSize.width/2+100,winSize.height/2-80));
                costLabel2->setScale(0.7);
                costLabel2->setColor(ccc3(231,219,138));
                
                tipLayer->addChild(emblem,5);
                tipLayer->addChild(label1,5);
                tipLayer->addChild(label2,5);
                tipLayer->addChild(label3,5);
                tipLayer->addChild(label4,5);
                tipLayer->addChild(label5,5);
                tipLayer->addChild(costIcon1,5);
                tipLayer->addChild(costLabel1,5);
                tipLayer->addChild(costIcon2,5);
                tipLayer->addChild(costLabel2,5);
                
                
                menu = MyPriorityMenu::create(-505,sureItem,cancelItem,NULL);
                menu->setPosition(ccp(winSize.width/2+35, winSize.height/2-120));
                
            } else {
                sprintf(str,"资源不足，需要以下资源");
                menu  = MyPriorityMenu::create(-505,cancelItem,NULL);
                menu->setPosition(ccp(winSize.width/2+120, winSize.height/2-110));
                
                CCLabelTTF* label6 = CCLabelTTF::create(str, "宋体", 30,CCSizeZero, kCCTextAlignmentLeft, kCCVerticalTextAlignmentTop);
                label6->setColor(ccc3(230, 207, 185));
                label6->setPosition(ccp(winSize.width/2+120,winSize.height/2+60));
                
                
                CCSprite* costIcon1 = MyUtil::getInstance()->getResourceIcon(gloryTag);
                costIcon1->setPosition(ccp(winSize.width/2+60,winSize.height/2));
                costIcon1->setScale(0.8);
                
                CCLabelAtlas* costLabel1 = CCLabelAtlas::create("30000", "number6.png", 24, 36, '/');
                costLabel1->setPosition(ccp(winSize.width/2+100,winSize.height/2-10));
                costLabel1->setScale(0.7);
                costLabel1->setColor(ccc3(231,219,138));
                
                CCSprite* costIcon2 = MyUtil::getInstance()->getResourceIcon(ironTag);
                costIcon2->setPosition(ccp(winSize.width/2+60,winSize.height/2-40));
                costIcon2->setScale(0.5);
                
                CCLabelAtlas* costLabel2 = CCLabelAtlas::create("5000000", "number6.png", 24, 36, '/');
                costLabel2->setPosition(ccp(winSize.width/2+100,winSize.height/2-50));
                costLabel2->setScale(0.7);
                costLabel2->setColor(ccc3(231,219,138));
                
                tipLayer->addChild(label6,5);
                tipLayer->addChild(costIcon1,5);
                tipLayer->addChild(costLabel1,5);
                tipLayer->addChild(costIcon2,5);
                tipLayer->addChild(costLabel2,5);
            }
        } else {
            sprintf(str,"联盟宣言必须小于30个字");
            menu  = MyPriorityMenu::create(-505,cancelItem,NULL);
            menu->setPosition(ccp(winSize.width/2+120, winSize.height/2-80));
            
            CCLabelTTF* label = CCLabelTTF::create(str, "Arial", 32,CCSizeMake(400,0), kCCTextAlignmentCenter, kCCVerticalTextAlignmentTop);
            label->setColor(ccc3(230, 207, 185));
            label->setPosition(ccp(winSize.width/2+120,winSize.height/2+40));
            tipLayer->addChild(label,5);
        }
        
    } else {
        sprintf(str,"『%s』\n联盟名称必须小于2个字大于5个字",name->getString());
        menu  = MyPriorityMenu::create(-505,cancelItem,NULL);
        menu->setPosition(ccp(winSize.width/2+120, winSize.height/2-80));
        
        CCLabelTTF* label = CCLabelTTF::create(str, "Arial", 32,CCSizeMake(400,0), kCCTextAlignmentCenter, kCCVerticalTextAlignmentTop);
        label->setColor(ccc3(230, 207, 185));
        label->setPosition(ccp(winSize.width/2+120,winSize.height/2+40));
        tipLayer->addChild(label,5);
    }
    
    
    
    menu->alignItemsHorizontallyWithPadding(30);
    
    GXShieldTouchMenuItem* shield = GXShieldTouchMenuItem::create();
    shield->setContentSize(CCSizeMake(winSize.width, winSize.height));
    shield->setAnchorPoint(ccp(0.5,0.5));
    shield->setPosition(ccp(-120,100));
    menu->addChild(shield,4);
    
    tipLayer->addChild(black);
    tipLayer->addChild(back);
    tipLayer->addChild(menu);
    tipLayer->setTag(createUnionTipLayerTag);
    this->addChild(tipLayer);
}

void StartScene::cancelTipDialog(CCMenuItem* item) {
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sfx_click.mp3");
    item->getParent()->getParent()->removeFromParentAndCleanup(true);
}

void StartScene::switchEmblem(CCMenuItemSprite* item) {
    if (item->getParent()->getParent() != NULL) {
        CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sfx_click.mp3");
        CCSprite* ori = (CCSprite*)item->getSelectedImage();
        CCSprite* emblem =  CCSprite::createWithTexture(ori->getTexture(),ori->getTextureRect());
        emblem->setTextureRect(ori->getTextureRect(), ori->isTextureRectRotated(), ori->getContentSize());
        emblem->setUserObject(item->getUserObject());
        item->getParent()->getParent()->removeChildByTag(createUnionEmblemTag,true);
        item->getParent()->getParent()->addChild(emblem);
        emblem->setTag(createUnionEmblemTag);
        emblem->setScale(Mathlib::min(235/emblem->getContentSize().width,235/emblem->getContentSize().height));
        emblem->setPosition(ccp(winSize.width/2-120,280));
        emblem->setUserObject(item->getUserObject());
    }
}

void StartScene::toSendCreateUnionCmd(CCMenuItem* item) {
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sfx_click.mp3");
    item->setEnabled(false);
    this->addChild(MyUtil::getInstance()->getWaitLayer("努力加载中"));
    
    CCNode* parent = this->getChildByTag(creatorLayerTag)->getChildByTag(displayUnionLayerTag);
    CCTextFieldTTF* name = (CCTextFieldTTF*)parent->getChildByTag(createUnionNameTextTag);
    CCTextFieldTTF* desc = (CCTextFieldTTF*)parent->getChildByTag(createUnionDesTextTag);
    CCSprite* emblem = (CCSprite*)parent->getChildByTag(createUnionEmblemTag);
    
    MyHttpConnection::getInstance()->sendCreateUnionCmd(CCString::create(name->getString()),CCString::create(desc->getString()),(CCString*)emblem->getUserObject());
}

void StartScene::createUnionResult(bool isSucc,CCString* msg) {
    removeWaitMenu();
    this->removeChildByTag(createUnionTipLayerTag,true);
    //    CCLayer* tipLayer = CCLayer::create();
    //    CCSprite* black = CCSprite::create("black.jpg");
    //    black->setOpacity(180);
    //    black->setPosition(ccp(winSize.width/2,winSize.height/2));
    //    black->setScaleX(winSize.width/black->getContentSize().width);
    //    black->setScaleY(winSize.height/black->getContentSize().height);
    //    GXShieldTouchMenuItem* shield = GXShieldTouchMenuItem::create();
    //    shield->setContentSize(CCSizeMake(winSize.width, winSize.height));
    //    shield->setAnchorPoint(ccp(0.5,0.5));
    //    shield->setPosition(ccp(-120,100));
    //    CCMenuItemSprite* sureItem = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("dialogsure.png"), CCSprite::createWithSpriteFrameName("dialogsurep.png"),this,menu_selector(StartScene::cancelTipDialog));
    //    MyPriorityMenu* menu  = MyPriorityMenu::create(-505,sureItem,shield,NULL);
    //    menu->setPosition(ccp(winSize.width/2+120, winSize.height/2-80));
    //
    //    CCSprite* back = MyUtil::getInstance()->getDialogBack();
    //    back->setPosition(ccp(winSize.width/2,winSize.height/2));
    //    CCLabelTTF* label = CCLabelTTF::create(msg->getCString(), "Arial", 30,CCSizeMake(400,0), kCCTextAlignmentCenter, kCCVerticalTextAlignmentTop);
    //    label->setColor(ccc3(230, 207, 185));
    //    label->setPosition(ccp(winSize.width/2+120,winSize.height/2+40));
    //    tipLayer->addChild(black,5);
    //    tipLayer->addChild(back,5);
    //    tipLayer->addChild(label,5);
    //    tipLayer->addChild(menu,5);
    if (isSucc) {
        //跳转到信息界面 钱在这里扣免得扣错
        MyGameInfo::getInstance()->changeResource(gloryTag,-30000);
        MyGameInfo::getInstance()->changeResource(ironTag,-5000000);
        toUnionMainUI();
        this->addChild(MyUtil::getInstance()->getCommonTipDialog(msg,this,menu_selector(StartScene::cancelTipDialog),0));
        
    } else {
        //不跳转
        this->addChild(MyUtil::getInstance()->getCommonTipDialog(msg,this,menu_selector(StartScene::cancelTipDialog),0));
    }
    //    this->getChildByTag(creatorLayerTag)->getChildByTag(displayUnionLayerTag)->addChild(tipLayer,5);
}

void StartScene::toUnionMessage() {
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sfx_click.mp3");
    this->getChildByTag(creatorLayerTag)->removeChildByTag(displayUnionLayerTag,true);
    CCLayer* displayLayer = CCLayer::create();
    CCSprite* kuang =  MyUtil::getInstance()->getZhijiaoBox(600,500);
    kuang->setPosition(ccp(winSize.width/2+110,320));
    displayLayer->addChild(kuang);
    displayLayer->setTag(displayUnionLayerTag);
    this->getChildByTag(creatorLayerTag)->addChild(displayLayer);
    
    GXListView* scroll =NULL;
    if (this->getUserObject() == NULL) {
        scroll = GXListView::create(-506);
        scroll->setOriPosition(ccp(winSize.width/2-200,80));
        scroll->setContentSize(CCSizeMake(590, 480));
        displayLayer->addChild(scroll);
        this->setUserObject(scroll);
    } else {
        scroll = (GXListView*)this->getUserObject();
        displayLayer->addChild(scroll);
    }
    
    int scrollDisCount = scroll->getChildrenCount();
    char str[500] = {0};
    while (scrollDisCount < PushTrigger::getInstance()->unionPushArray->count()) {
        CCLayer* shenheLayer = CCLayer::create();
        CCDictionary* varMap = (CCDictionary*)PushTrigger::getInstance()->unionPushArray->objectAtIndex(scrollDisCount);
        sprintf(str,"『%s』申请加入组织，是否批准？",((CCString*)varMap->objectForKey("applicantNickName"))->getCString());
        CCLabelTTF* msgLabel = CCLabelTTF::create(str,"Arial",25,CCSizeMake(580,0), kCCTextAlignmentLeft, kCCVerticalTextAlignmentTop);
        msgLabel->setAnchorPoint(ccp(0,0.5));
        msgLabel->setColor(ccc3(230, 207, 185));
        msgLabel->setPosition(ccp(0,40));
        shenheLayer->addChild(msgLabel);
        CCMenuItemSprite* yesItem = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("unionCommonSingleButton.png"),CCSprite::createWithSpriteFrameName("unionCommonSingleButtonP.png"),this,menu_selector(StartScene::replayJoinApplicant));
        CCLabelTTF* yesLabel = CCLabelTTF::create("是","Arial",30);
        yesLabel->setPosition(ccp(20,20));
        yesLabel->setColor(ccc3(240,147,1));
        yesItem->addChild(yesLabel);
        yesItem->setUserObject(varMap);
        yesItem->setUserData((void*)1);
        CCMenuItemSprite* noItem = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("unionCommonSingleButton.png"),CCSprite::createWithSpriteFrameName("unionCommonSingleButtonP.png"),this,menu_selector(StartScene::replayJoinApplicant));
        CCLabelTTF* noLabel = CCLabelTTF::create("否","Arial",30);
        noLabel->setPosition(ccp(20,20));
        noLabel->setColor(ccc3(240,147,1));
        noItem->addChild(noLabel);
        noItem->setUserObject(varMap);
        noItem->setUserData((void*)0);
        MyPriorityMenu* menu2 = MyPriorityMenu::create(-507,yesItem,noItem,NULL);
        menu2->alignItemsHorizontallyWithPadding(50);
        menu2->setPosition(250,0);
        shenheLayer->addChild(menu2);
        
        shenheLayer->setContentSize(CCSizeMake(msgLabel->getContentSize().width,msgLabel->getContentSize().height+40));
        scroll->addChild(shenheLayer);
        scrollDisCount++;
    }
    
}

void StartScene::replayJoinApplicant(CCMenuItem* item) {
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sfx_click.mp3");
    CCDictionary* varMap = (CCDictionary*)item->getUserObject();
    int integer = (int)item->getUserData();
    if (integer == 1) {
        varMap->setObject(CCString::create("Y"),"succ");
    } else {
        varMap->setObject(CCString::create("N"),"succ");
    }
    
    MyHttpConnection::getInstance()->sendReplyApplicant(varMap);
    PushTrigger::getInstance()->unionPushArray->removeObject(varMap);
    item->setUserObject(NULL);
    ((GXListView*)item->getParent()->getParent()->getParent())->removeChildAction(item->getParent()->getParent());
}

bool StartScene::checkNewUnionMessage(CCDictionary* varMap) {
    char str[500] = {0};
    GXListView* scroll = (GXListView*)this->getUserObject();
    if (scroll == NULL) {
        return false;
    }
    CCLayer* shenheLayer = CCLayer::create();
    sprintf(str,"『%s』申请加入组织，是否批准？",((CCString*)varMap->objectForKey("applicantNickName"))->getCString());
    CCLabelTTF* msgLabel = CCLabelTTF::create(str,"Arial",25,CCSizeMake(580,0), kCCTextAlignmentLeft, kCCVerticalTextAlignmentTop);
    msgLabel->setAnchorPoint(ccp(0,0.5));
    msgLabel->setColor(ccc3(230, 207, 185));
    msgLabel->setPosition(ccp(0,40));
    shenheLayer->addChild(msgLabel);
    CCMenuItemSprite* yesItem = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("unionCommonSingleButton.png"),CCSprite::createWithSpriteFrameName("unionCommonSingleButtonP.png"),this,menu_selector(StartScene::replayJoinApplicant));
    CCLabelTTF* yesLabel = CCLabelTTF::create("是","Arial",30);
    yesLabel->setPosition(ccp(20,20));
    yesLabel->setColor(ccc3(240,147,1));
    yesItem->addChild(yesLabel);
    yesItem->setUserObject(varMap);
    yesItem->setUserData((void*)1);
    CCMenuItemSprite* noItem = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("unionCommonSingleButton.png"),CCSprite::createWithSpriteFrameName("unionCommonSingleButtonP.png"),this,menu_selector(StartScene::replayJoinApplicant));
    CCLabelTTF* noLabel = CCLabelTTF::create("否","Arial",30);
    noLabel->setPosition(ccp(20,20));
    noLabel->setColor(ccc3(240,147,1));
    noItem->addChild(noLabel);
    noItem->setUserObject(varMap);
    noItem->setUserData((void*)0);
    MyPriorityMenu* menu2 = MyPriorityMenu::create(-507,yesItem,noItem,NULL);
    menu2->alignItemsHorizontallyWithPadding(50);
    menu2->setPosition(250,0);
    shenheLayer->addChild(menu2);
    
    shenheLayer->setContentSize(CCSizeMake(msgLabel->getContentSize().width,msgLabel->getContentSize().height+40));
    scroll->addChild(shenheLayer);
    return true;
}

void StartScene::toUnionInfo() {
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sfx_click.mp3");
    this->getChildByTag(creatorLayerTag)->removeChildByTag(displayUnionLayerTag,true);
    CCLayer* displayLayer = CCLayer::create();
    CCSprite* kuang =  MyUtil::getInstance()->getZhijiaoBox(600,500);
    kuang->setPosition(ccp(winSize.width/2+110,320));
    displayLayer->addChild(kuang);
    displayLayer->setTag(displayUnionLayerTag);
    
    char str[1000] = {0};
    sprintf(str,"『%s』",MyGameInfo::getInstance()->getUnionBean()->getName()->getCString());
    CCLabelTTF* nameFont = CCLabelTTF::create(str,"Arial",40);
    nameFont->setColor(ccc3(230, 207, 185));
    nameFont->setPosition(ccp(winSize.width/2+110,520));
    displayLayer->addChild(nameFont);
    
    CCLabelTTF* descFont = CCLabelTTF::create("宣言：","Arial",25);
    descFont->setColor(ccc3(230, 207, 185));
    descFont->setPosition(ccp(winSize.width/2-100,480));
    displayLayer->addChild(descFont);
    
    sprintf(str,"    %s",MyGameInfo::getInstance()->getUnionBean()->getDesc()->getCString());
#if   (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    CCLabelTTF* desc = CCLabelTTF::create(str, "Arial", 30,CCSizeMake(500,200), kCCTextAlignmentLeft, kCCVerticalTextAlignmentTop);
#endif
#if   (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    CCLabelTTF* desc = CCLabelTTF::create(GXUtil::insertNewline(str,17).c_str(),"Arial", 30,CCSizeZero, kCCTextAlignmentLeft, kCCVerticalTextAlignmentTop);
#endif
    desc->setAnchorPoint(ccp(0,1));
    desc->setColor(ccc3(240,147,1));
    desc->setPosition(ccp(winSize.width/2-130,463));
    displayLayer->addChild(desc);
    
    CCLabelTTF* noticeFont = CCLabelTTF::create("公告：","Arial",25);
    noticeFont->setColor(ccc3(230, 207, 185));
    noticeFont->setPosition(ccp(winSize.width/2-100,373));
    displayLayer->addChild(noticeFont);
    
    CCSprite* noticeBox = MyUtil::getInstance()->getLineBox(510,250);
    noticeBox->setPosition(ccp(winSize.width/2 + 110,230));
    displayLayer->addChild(noticeBox);
    
    sprintf(str,"    %s",MyGameInfo::getInstance()->getUnionBean()->getNotice()->getCString());
#if   (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    CCLabelTTF* notice = CCLabelTTF::create(str, "Arial", 24,CCSizeMake(490,400), kCCTextAlignmentLeft, kCCVerticalTextAlignmentTop);
#endif
#if   (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    CCLabelTTF* notice = CCLabelTTF::create(GXUtil::insertNewline(str,20).c_str(),"Arial", 24,CCSizeZero, kCCTextAlignmentLeft, kCCVerticalTextAlignmentTop);
#endif
    notice->setAnchorPoint(ccp(0,1));
    notice->setColor(ccc3(240,147,1));
    notice->setPosition(ccp(winSize.width/2 - 132,347));
    displayLayer->addChild(notice);
    
    
    
    
    this->getChildByTag(creatorLayerTag)->addChild(displayLayer);
}
#define memberPageSize 8

void StartScene::toUnionMember() {
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sfx_click.mp3");
    this->getChildByTag(creatorLayerTag)->removeChildByTag(displayUnionLayerTag,true);
    this->addChild(MyUtil::getInstance()->getWaitLayer("正在读取成员列表"));
    MyGameInfo::getInstance()->getUnionBean()->memberPageNo = 1;
    MyHttpConnection::getInstance()->getAllMemberByPage(1,memberPageSize);
    
}

void StartScene::displayUnionMember(CCArray* member) {
    removeWaitMenu();
    
    CCLayer* displayLayer = CCLayer::create();
    
    GXListView* scroll = GXListView::create(-506);
    scroll->setOriPosition(ccp(winSize.width/2-180,45));
    scroll->setContentSize(CCSizeMake(610, 465));
    scroll->setEnabled(false);
    displayLayer->addChild(scroll);
    
    CCSprite* memberIcon = CCSprite::createWithSpriteFrameName("memberIcon.png");
    memberIcon->setPosition(ccp(winSize.width/2+250,555));
    memberIcon->setScale(0.7);
    displayLayer->addChild(memberIcon);
    char str[50] = {0};
    sprintf(str,"%d/25",MyGameInfo::getInstance()->getUnionBean()->memberCount);
    CCLabelTTF* memberLabel = CCLabelTTF::create(str,"Arial",30);
    memberLabel->setColor(ccc3(253,203,1));
    memberLabel->setPosition(ccp(winSize.width/2+310,555));
    displayLayer->addChild(memberLabel);
    
    
    
    CCSprite* kuang =  MyUtil::getInstance()->getZhijiaoBox(650,450);
    kuang->setPosition(ccp(winSize.width/2+120,310));
    displayLayer->addChild(kuang);
    displayLayer->setTag(displayUnionLayerTag);
    
    CCObject*  obj;
    int i =0;
    
    int role = MyGameInfo::getInstance()->getUnionBean()->role;
    
    MyPriorityMenu* menu = MyPriorityMenu::create(-506,NULL);
    
    CCARRAY_FOREACH_REVERSE(member,obj) {
        MyMemberBean* userBean = (MyMemberBean*)obj;
        CCLabelTTF* zhiwei ;
        CCLayer* memberLayer = CCLayer::create();
        if (userBean->role == 1) {
            zhiwei = CCLabelTTF::create("盟主","Arail",30);
        } else {
            zhiwei = CCLabelTTF::create("成员","Arail",30);
        }
        zhiwei->setPosition(ccp(10,10));
        memberLayer->addChild(zhiwei);
        
        
        CCLabelTTF* nickName = CCLabelTTF::create(userBean->getNickName(),"Arial",30);
        nickName->setPosition(ccp(160,10));
        memberLayer->addChild(nickName);
        
        sprintf(str,"%d",userBean->donatePower);
        CCLabelTTF* donatePower = CCLabelTTF::create(str,"Arial",30);
        donatePower->setPosition(ccp(510,10));
        memberLayer->addChild(donatePower);
        
        CCLabelTTF* rankName = CCLabelTTF::create(MyUtil::getInstance()->getRankString(userBean->power), "Arial", 30);
        rankName->setPosition(ccp(330,10));
        memberLayer->addChild(rankName);
        
        CCSprite* rankSprite = MyUtil::getInstance()->getRankSprite(userBean->power);
        rankSprite->setPosition(ccp(280,10));
        rankSprite->setScale(0.60);
        memberLayer->addChild(rankSprite);
        
        sprintf(str,"%d",MyUtil::getInstance()->getLevelByExperience(userBean->experience));
        CCLabelAtlas* levelLabel1 = CCLabelAtlas::create(str, "levelupnumber.png", 40, 32, '0');
        levelLabel1->setAnchorPoint(ccp(0.5,0.5));
        levelLabel1->setScaleY(0.8);
        levelLabel1->setScaleX(0.63);
        levelLabel1->setPosition(ccp(430,10));
        memberLayer->addChild(levelLabel1);
        
        CCSprite* levelIcon = CCSprite::createWithSpriteFrameName("levelIcon.png");
        levelIcon->setScale(0.5);
        levelIcon->setPosition(ccp(390,10));
        memberLayer->addChild(levelIcon);
        
        if (userBean->isOnline) {
            zhiwei->setColor(ccc3(230, 207, 185));
            nickName->setColor(ccc3(230, 207, 185));
            donatePower->setColor(ccc3(230, 207, 185));
            rankName->setColor(ccc3(230, 207, 185));
        } else {
            zhiwei->setColor(ccc3(100,100,100));
            nickName->setColor(ccc3(100,100,100));
            donatePower->setColor(ccc3(100,100,100));
            rankName->setColor(ccc3(100,100,100));
            levelIcon->setColor(ccc3(100,100,100));
            levelLabel1->setColor(ccc3(100,100,100));
            rankSprite->setColor(ccc3(100,100,100));
        }
        
        
        memberLayer->setContentSize(CCSizeMake(600,30));
        scroll->addChildNoAction(memberLayer);
        
        
        if (role == 1 && userBean->role != 1) {
            CCLabelTTF* kickLabel = CCLabelTTF::create("踢","Arial",30);
            kickLabel->setColor(ccc3(253,203,1));
            CCMenuItemSprite* kickItem = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("unionCommonSingleButton.png"),CCSprite::createWithSpriteFrameName("unionCommonSingleButtonP.png"),this,menu_selector(StartScene::sureKickMember));
            kickLabel->setPosition(ccp(20,20));
            kickItem->addChild(kickLabel);
            kickItem->setPosition(ccp(0,0));
            kickItem->setUserObject(userBean);
            MyPriorityMenu* kickMenu = MyPriorityMenu::create(-508,kickItem,NULL);
            kickMenu->setPosition(610,10);
            memberLayer->addChild(kickMenu);
            
        }
        
        i++;
    }
    
    CCLayer* titleLayer = CCLayer::create();
    
    CCSprite* tag1 = CCSprite::create("whiteImage.jpg");
    tag1->setScaleX(99/tag1->getContentSize().width);
    tag1->setScaleY(40/tag1->getContentSize().height);
    tag1->setColor(ccc3(132,97,61));
    tag1->setAnchorPoint(ccp(0,0.5));
    tag1->setPosition(ccp(-40,10));
    titleLayer->addChild(tag1);
    
    CCLabelTTF* label1 = CCLabelTTF::create("职位","Arail",30);
    label1->setPosition(ccp(10,10));
    titleLayer->addChild(label1);
    
    
    CCSprite* tag2 = CCSprite::create("whiteImage.jpg");
    tag2->setScaleX(199/tag2->getContentSize().width);
    tag2->setScaleY(40/tag2->getContentSize().height);
    tag2->setColor(ccc3(132,97,61));
    tag2->setAnchorPoint(ccp(0,0.5));
    tag2->setPosition(ccp(60,10));
    titleLayer->addChild(tag2);
    
    CCLabelTTF* label2 = CCLabelTTF::create("昵称","Arail",30);
    label2->setPosition(ccp(160,10));
    titleLayer->addChild(label2);
    
    CCSprite* tag3 = CCSprite::create("whiteImage.jpg");
    tag3->setScaleX(99/tag3->getContentSize().width);
    tag3->setScaleY(40/tag3->getContentSize().height);
    tag3->setColor(ccc3(132,97,61));
    tag3->setAnchorPoint(ccp(0,0.5));
    tag3->setPosition(ccp(260,10));
    titleLayer->addChild(tag3);
    
    CCLabelTTF* label3 = CCLabelTTF::create("军衔","Arail",30);
    label3->setPosition(ccp(310,10));
    titleLayer->addChild(label3);
    
    CCSprite* tag4 = CCSprite::create("whiteImage.jpg");
    tag4->setScaleX(99/tag4->getContentSize().width);
    tag4->setScaleY(40/tag4->getContentSize().height);
    tag4->setColor(ccc3(132,97,61));
    tag4->setAnchorPoint(ccp(0,0.5));
    tag4->setPosition(ccp(360,10));
    titleLayer->addChild(tag4);
    
    CCLabelTTF* label4 = CCLabelTTF::create("等级","Arail",30);
    label4->setPosition(ccp(410,10));
    titleLayer->addChild(label4);
    
    CCSprite* tag5 = CCSprite::create("whiteImage.jpg");
    tag5->setScaleX(99/tag4->getContentSize().width);
    tag5->setScaleY(40/tag4->getContentSize().height);
    tag5->setColor(ccc3(132,97,61));
    tag5->setAnchorPoint(ccp(0,0.5));
    tag5->setPosition(ccp(460,10));
    titleLayer->addChild(tag5);
    
    CCLabelTTF* label5 = CCLabelTTF::create("贡献值","Arail",30);
    label5->setPosition(ccp(510,10));
    titleLayer->addChild(label5);
    
    if (role == 1) {
        CCSprite* tag6 = CCSprite::create("whiteImage.jpg");
        tag6->setScaleX(99/tag4->getContentSize().width);
        tag6->setScaleY(40/tag4->getContentSize().height);
        tag6->setColor(ccc3(132,97,61));
        tag6->setAnchorPoint(ccp(0,0.5));
        tag6->setPosition(ccp(560,10));
        titleLayer->addChild(tag6);
        
        CCLabelTTF* label6 = CCLabelTTF::create("操作","Arail",30);
        label6->setPosition(ccp(610,10));
        titleLayer->addChild(label6);
    }
    
    
    
    titleLayer->setContentSize(CCSizeMake(600,30));
    scroll->addChildNoAction(titleLayer);
    
    CCMenuItemSprite* nextButton = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("nextPageButton.png"),CCSprite::createWithSpriteFrameName("nextPageButtonP.png"),this,menu_selector(StartScene::memberListPage));
    nextButton->setUserObject(CCInteger::create(1));
    
    CCMenuItemSprite* preButton = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("prePageButton.png"),CCSprite::createWithSpriteFrameName("prePageButtonP.png"),this,menu_selector(StartScene::memberListPage));
    preButton->setUserObject(CCInteger::create(-1));
    
    
    
    if (MyGameInfo::getInstance()->getUnionBean()->memberPageNo > 1) {
        menu->addChild(preButton);
    }
    
    //    CCLog("%d",MyGameInfo::getInstance()->getUnionBean()->memberPageNo);
    //    CCLog("%d",MyGameInfo::getInstance()->getUnionBean()->memberCount);
    int maxPage = MyGameInfo::getInstance()->getUnionBean()->memberPageCount;
    
    if (MyGameInfo::getInstance()->getUnionBean()->memberPageNo < maxPage) {
        menu->addChild(nextButton);
    }
    if (role == 1) {
        
        CCLabelTTF* kickLabel = CCLabelTTF::create("成员操作","Arial",30);
        kickLabel->setColor(ccc3(253,203,1));
        CCSprite* up =  CCSprite::createWithSpriteFrameName("unionCommonSingleButton.png");
        up->setScaleX(150/up->getContentSize().width);
        up->setContentSize(CCSizeMake(150,up->getContentSize().height));
        CCSprite* down =  CCSprite::createWithSpriteFrameName("unionCommonSingleButtonP.png");
        down->setScaleX(150/up->getContentSize().width);
        down->setContentSize(CCSizeMake(150,down->getContentSize().height));
        CCMenuItemSprite* kickItem = CCMenuItemSprite::create(up,down,this,menu_selector(StartScene::operatorMember));
        kickItem->setPosition(ccp(winSize.width/2-50,555));
        kickLabel->setPosition(ccp(kickItem->getContentSize().width/2,kickItem->getContentSize().height/2));
        kickItem->addChild(kickLabel);
        kickItem->setUserObject(scroll);
        menu->addChild(kickItem);
        
    }
    
    
    menu->setPosition(ccp(0,0));
    displayLayer->addChild(menu);
    
    this->getChildByTag(creatorLayerTag)->addChild(displayLayer);
    
    nextButton->setPosition(ccp(winSize.width/2+200,445 - i*40));
    preButton->setPosition(ccp(winSize.width/2+40,445 - i*40));
    
}

void StartScene::sureKickMember(CCMenuItem* item) {
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sfx_click.mp3");
    MyMemberBean* userBean = (MyMemberBean*)item->getUserObject();
    this->removeChildByTag(sureKickMemberLayerTag,true);
    CCLayer* tipLayer = CCLayer::create();
    CCSprite* back = MyUtil::getInstance()->getDialogBack();
    back->setPosition(ccp(winSize.width/2,winSize.height/2));
    CCSprite* black = CCSprite::create("whiteImage.jpg");
    black->setColor(ccc3(0,0,0));
    black->setOpacity(180);
    black->setPosition(ccp(winSize.width/2,winSize.height/2));
    black->setScaleX(winSize.width/black->getContentSize().width);
    black->setScaleY(winSize.height/black->getContentSize().height);
    CCMenuItemSprite* sureItem = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("dialogsure.png"), CCSprite::createWithSpriteFrameName("dialogsurep.png"),this,menu_selector(StartScene::toKickMember));
    sureItem->setUserObject(userBean);
    sureItem->setUserData(item->getParent()->getParent());
    
    CCMenuItemSprite* cancelItem =CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("dialogcancel.png"), CCSprite::createWithSpriteFrameName("dialogcancelp.png"),this,menu_selector(StartScene::cancelTipDialog));
    MyPriorityMenu* menu  = MyPriorityMenu::create(-506,sureItem,cancelItem,NULL);
    menu->alignItemsHorizontallyWithPadding(30);
    
    GXShieldTouchMenuItem* shield = GXShieldTouchMenuItem::create();
    shield->setContentSize(CCSizeMake(winSize.width, winSize.height));
    shield->setAnchorPoint(ccp(0.5,0.5));
    shield->setPosition(ccp(-120,100));
    menu->addChild(shield,4);
    
    char str[300] = {0};
    sprintf(str,"确定将『%s』踢出联盟吗？",userBean->getNickName());
    menu->setPosition(ccp(winSize.width/2+120, winSize.height/2-80));
    
    CCLabelTTF* label = CCLabelTTF::create(str, "Arial", 32,CCSizeMake(400,0), kCCTextAlignmentCenter, kCCVerticalTextAlignmentTop);
    label->setColor(ccc3(230, 207, 185));
    label->setPosition(ccp(winSize.width/2+120,winSize.height/2+40));
    
    
    tipLayer->addChild(label,5);
    tipLayer->addChild(black);
    tipLayer->addChild(back);
    tipLayer->addChild(menu);
    tipLayer->setTag(sureKickMemberLayerTag);
    this->addChild(tipLayer);
}

void StartScene::operatorMember(CCMenuItem* item) {
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sfx_click.mp3");
    GXListView* scroll = (GXListView*)item->getUserObject();
    if (scroll->getPosition().x - scroll->getOriPosition().x < -5) {
        scroll->runAction(CCMoveBy::create(0.2,ccp(100,0)));
    } else {
        scroll->runAction(CCMoveBy::create(0.2,ccp(-100,0)));
    }
}

void StartScene::toKickMember(CCMenuItem* item) {
    cancelTipDialog(item);
    MyMemberBean* userBean = (MyMemberBean*)item->getUserObject();
    CCLayer* layer = (CCLayer*)item->getUserData();
    ((GXListView*)layer->getParent())->removeChildAction(layer);
    MyHttpConnection::getInstance()->sendKickUnion(CCString::create(userBean->getItitaId()));
}

void StartScene::memberListPage(CCMenuItem* item) {
    int pos = ((GXInteger*)item->getUserObject())->getValue();
    this->addChild(MyUtil::getInstance()->getWaitLayer("正在读取成员列表"));
    MyGameInfo::getInstance()->getUnionBean()->memberPageNo += pos;
    MyHttpConnection::getInstance()->getAllMemberByPage(MyGameInfo::getInstance()->getUnionBean()->memberPageNo,8);
}

void StartScene::toUnionManager() {
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sfx_click.mp3");
    this->getChildByTag(creatorLayerTag)->removeChildByTag(displayUnionLayerTag,true);
    CCLayer* displayLayer = CCLayer::create();
    CCSprite* kuang =  MyUtil::getInstance()->getZhijiaoBox(600,440);
    kuang->setPosition(ccp(winSize.width/2+110,290));
    displayLayer->addChild(kuang);
    displayLayer->setTag(displayUnionLayerTag);
    
    GXRadioMenu* radioMenu = GXRadioMenu::create(-505,NULL);
    
    if (MyGameInfo::getInstance()->getUnionBean()->role == 1) {
        CCMenuItemSprite* managerAnnouncementButton = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("unionMessageAnnouncementButton.png"), CCSprite::createWithSpriteFrameName("unionMessageAnnouncementButtonP.png"),this,menu_selector(StartScene::unionManagerNotice));
        CCMenuItemSprite* managerAppointmentButton = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("unionManagerAppointmentButton.png"), CCSprite::createWithSpriteFrameName("unionManagerAppointmentButtonP.png"),this,menu_selector(StartScene::unionManagerAppointMent));
        CCMenuItemSprite* managerOperateButton = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("unionOperateButton.png"), CCSprite::createWithSpriteFrameName("unionOperateButtonP.png"),this,menu_selector(StartScene::unionManagerOperate));
        managerAnnouncementButton->setPosition(ccp(winSize.width/2-100,532));
        managerAppointmentButton->setPosition(ccp(winSize.width/2+60,532));
        managerOperateButton->setPosition(ccp(winSize.width/2+220,532));
        radioMenu->addChild(managerAnnouncementButton);
        radioMenu->addChild(managerAppointmentButton);
        radioMenu->addChild(managerOperateButton);
    } else {
        CCMenuItemSprite* managerOperateButton = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("unionOperateButton.png"), CCSprite::createWithSpriteFrameName("unionOperateButtonP.png"),this,menu_selector(StartScene::unionManagerOperate));
        managerOperateButton->setPosition(ccp(winSize.width/2-100,532));
        radioMenu->addChild(managerOperateButton);
    }
    
    
    
    
    
    
    radioMenu->setPosition(ccp(0,0));
    displayLayer->addChild(radioMenu);
    
    this->getChildByTag(creatorLayerTag)->addChild(displayLayer);
    radioMenu->setSelect(0);
}

void StartScene::unionManagerNotice() {
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sfx_click.mp3");
    CCNode* parent = this->getChildByTag(creatorLayerTag)->getChildByTag(displayUnionLayerTag);
    if (parent == NULL) {
        return;
    }
    parent->removeChildByTag(unionManagerLayerTag,true);
    CCLayer* managerLayer = CCLayer::create();
    managerLayer->setTag(unionManagerLayerTag);
    parent->addChild(managerLayer);
    
    
    CCSprite* noticeBox = MyUtil::getInstance()->getLineBox(585,180);
    noticeBox->setPosition(ccp(winSize.width/2+110,220));
    managerLayer->addChild(noticeBox);
    char str[1000] = {0};
    sprintf(str,"    %s",MyGameInfo::getInstance()->getUnionBean()->getNotice()->getCString());
    
#if   (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    CCLabelTTF* orinotice = CCLabelTTF::create(str, "Arial", 21,CCSizeMake(560,0), kCCTextAlignmentLeft, kCCVerticalTextAlignmentTop);
#endif
#if   (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    CCLabelTTF* orinotice = CCLabelTTF::create(GXUtil::insertNewline(str,26).c_str(),"Arial", 21,CCSizeZero, kCCTextAlignmentLeft, kCCVerticalTextAlignmentTop);
#endif
    
    orinotice->setAnchorPoint(ccp(0,1));
    orinotice->setColor(ccc3(240,147,1));
    orinotice->setPosition(ccp(winSize.width/2-162,300));
    managerLayer->addChild(orinotice);
    
    CCSprite* newNoticeBox = MyUtil::getInstance()->getLineBox(585,190);
    newNoticeBox->setPosition(ccp(winSize.width/2+110,405));
    managerLayer->addChild(newNoticeBox);
    
    CCTextFieldTTF* noticeTextField = CCTextFieldTTF::textFieldWithPlaceHolder("点击此处输入联盟公告，150字以内",CCSizeMake(560,0), kCCTextAlignmentLeft,"Arial",21);
    noticeTextField->setAnchorPoint(ccp(0,1));
    noticeTextField->setPosition(ccp(winSize.width/2-162,495));
    noticeTextField->setColor(ccc3(240,147,1));
    managerLayer->addChild(noticeTextField);
    
    CCSprite* noticeButtonSprite = CCSprite::create("transparent.png");
    noticeButtonSprite->setScaleX(585/noticeButtonSprite->getContentSize().width);
    noticeButtonSprite->setScaleY(190/noticeButtonSprite->getContentSize().height);
    noticeButtonSprite->setContentSize(CCSizeMake(585,190));
    
    MyMenuItem* noticeButton = MyMenuItem::create(noticeButtonSprite,this,menu_selector(StartScene::displayUnionIME));
    noticeButton->setPosition(ccp(winSize.width/2+110,405));
    noticeButton->setUserObject(noticeTextField);
    noticeButton->setUserData((void*)21);
    
    CCLabelTTF* label = CCLabelTTF::create("确认修改公告","Arial" ,35);
    label->setColor(ccc3(230, 207, 185));
    
    CCMenuItemLabel* changeNoticeButton = CCMenuItemLabel::create(label, this, menu_selector(StartScene::unionSendNotice));
    changeNoticeButton->setPosition(ccp(winSize.width/2+110,105));
    changeNoticeButton->setUserObject(noticeTextField);
    
    MyPriorityMenu* menu = MyPriorityMenu::create(-505,noticeButton,changeNoticeButton,NULL);
    menu->setPosition(ccp(0,0));
    
    
    managerLayer->addChild(menu);
    
}

void StartScene::unionSendNotice(CCMenuItem* item) {
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sfx_click.mp3");
    CCTextFieldTTF* notice = (CCTextFieldTTF*)item->getUserObject();
    if (strlen(notice->getString()) <= 450) {
        this->addChild(MyUtil::getInstance()->getWaitLayer("正在发布公告"));
        MyHttpConnection::getInstance()->sendNotice(CCString::create(notice->getString()));
        this->getChildByTag(creatorLayerTag)->getChildByTag(displayUnionLayerTag)->getChildByTag(unionManagerLayerTag)->setUserObject(CCString::create(notice->getString()));
        return;
    }
    this->addChild(MyUtil::getInstance()->getCommonTipDialog(CCString::create("公告请限制在150字以内"),this,menu_selector(StartScene::cancelTipDialog),0));
}

void StartScene::unionManagerAppointMent() {
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sfx_click.mp3");
    CCNode* parent = this->getChildByTag(creatorLayerTag)->getChildByTag(displayUnionLayerTag);
    if (parent == NULL) {
        return;
    }
    parent->removeChildByTag(unionManagerLayerTag,true);
}

void StartScene::unionManagerOperate() {
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sfx_click.mp3");
    CCNode* parent = this->getChildByTag(creatorLayerTag)->getChildByTag(displayUnionLayerTag);
    if (parent == NULL) {
        return;
    }
    parent->removeChildByTag(unionManagerLayerTag,true);
    CCLayer* managerLayer = CCLayer::create();
    managerLayer->setTag(unionManagerLayerTag);
    parent->addChild(managerLayer);
    CCLabelTTF* label;
    if (MyGameInfo::getInstance()->getUnionBean()->role == 1) {
        label = CCLabelTTF::create("解散联盟","Arial",40);
    } else {
        label = CCLabelTTF::create("退出联盟","Arial",40);
    }
    label->setColor(ccc3(253,203,1));
    CCMenuItemLabel* labelItem = CCMenuItemLabel::create(label,this,menu_selector(StartScene::sureOpeateUnion));
    labelItem->setPosition(ccp(winSize.width/2-30,450));
    MyPriorityMenu* menu = MyPriorityMenu::create(-507,labelItem,NULL);
    menu->setPosition(ccp(0,0));
    managerLayer->addChild(menu);
    
}

void StartScene::sureOpeateUnion(CCMenuItem* item) {
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sfx_click.mp3");
    char str[150] = {0};
    if (MyGameInfo::getInstance()->getUnionBean()->role == 1) {
        sprintf(str,"确定要解散联盟『%s』吗？",MyGameInfo::getInstance()->getUnionBean()->getName()->getCString());
        item->getParent()->getParent()->addChild(MyUtil::getInstance()->getCommonTipDialog(CCString::create(str),this,menu_selector(StartScene::sendOpeateUnion),1),10);
    } else {
        sprintf(str,"确定要退出联盟『%s』吗？",MyGameInfo::getInstance()->getUnionBean()->getName()->getCString());
        item->getParent()->getParent()->addChild(MyUtil::getInstance()->getCommonTipDialog(CCString::create(str),this,menu_selector(StartScene::sendOpeateUnion),1),10);
    }
    
}

void StartScene::sendOpeateUnion(CCMenuItem* item) {
    cancelTipDialog(item);
    quitCreator();
    //    removeUnionLayerInAvatar();
    if (MyGameInfo::getInstance()->getUnionBean()->role == 1) {
        MyHttpConnection::getInstance()->sendDissolveUnion();
    } else {
        MyHttpConnection::getInstance()->sendExitUnion();
    }
}

void StartScene::toShopCallBackWait(CCMenuItem* item) {
//    item->setEnabled(false);
    this->addChild(MyUtil::getInstance()->getWaitLayer("正在读取商品信息"));
    MyHttpConnection::getInstance()->sendGetBoughtList();
    quitCreator();
    toCancelSecond();
    //    this->scheduleOnce(schedule_selector(StartScene::toShopCallBack), 0.5);
}

void StartScene::toShopCallBack() {
    removeWaitMenu();
    this->getChildByTag(resourceBarTag)->setVisible(false);
    //TODO 改声音
    //    CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sfx_army.mp3");
    MyGameInfo::getInstance()->getOilAtlas()->removeFromParentAndCleanup(true);
    MyGameInfo::getInstance()->getIronAtlas()->removeFromParentAndCleanup(true);
    MyGameInfo::getInstance()->getGloryAtlas()->removeFromParentAndCleanup(true);
    MyGameInfo::getInstance()->getDiamondAtlas()->removeFromParentAndCleanup(true);
    
    CCLayer* shopLayer = CCLayer::create();
    CCSprite* back = MyUtil::getInstance()->getShopBack();
    back->setAnchorPoint(ccp(0,0));
    shopLayer->addChild(back);
    this->addChild(shopLayer);
    shopLayer->setTag(creatorLayerTag);
    
    
    CCLabelAtlas* diamondLabel = MyGameInfo::getInstance()->getDiamondAtlas();
    diamondLabel->setScale(1.2);
    diamondLabel->setPosition(ccp(winSize.width-305,550));
    shopLayer->addChild(diamondLabel);
    
    CCMenuItemSprite* quitItem = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("cancelRecord.png"), CCSprite::createWithSpriteFrameName("cancelRecordP.png"),this,menu_selector( StartScene::quitCreator));
    
    GXShieldTouchMenuItem* shild = GXShieldTouchMenuItem::create();
    shild->setContentSize(winSize);
    shild->setPosition(ccp(winSize.width/2,winSize.height/2));
    
    
    CCMenuItemSprite* chargeButton = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("shopChargeButton.png"),CCSprite::createWithSpriteFrameName("shopChargeButtonP.png"),this,menu_selector(StartScene::toDisplayCharge));
    chargeButton->setAnchorPoint(ccp(1,0.5));
    chargeButton->setPosition(ccp(winSize.width, winSize.height-70));
    
    MyPriorityMenu* menu = MyPriorityMenu::create(-503,chargeButton,quitItem,shild,NULL);
    menu->setPosition(ccp(0,0));
    
    quitItem->setPosition(ccp(winSize.width-15,winSize.height-15));
    //    quitItem->setScale(1.4);
    quitItem->setContentSize(CCSizeMake(quitItem->getContentSize().width,quitItem->getContentSize().height));
    shopLayer->addChild(menu,2);
    
    CCSprite* avatarSprite = CCSprite::createWithSpriteFrameName("avatar0.png");
    avatarSprite->setScale(1.17);
    avatarSprite->setAnchorPoint(ccp(0,0));
    avatarSprite->setPosition(ccp(10,530));
    shopLayer->addChild(avatarSprite);
    
    CCLabelTTF* nickName = CCLabelTTF::create(MyGameInfo::getInstance()->getNickName(),"Arial",37);
    nickName->setColor(ccc3(255,224,122));
    nickName->setAnchorPoint(ccp(0,0.5));
    nickName->setPosition(ccp(130,winSize.height-40));
    shopLayer->addChild(nickName);
    
    CCSprite* vipSprite = CCSprite::createWithSpriteFrameName("shopVIPIcon.png");
    vipSprite->setPosition(ccp(180,winSize.height-85));
    vipSprite->setScale(1.2);
    shopLayer->addChild(vipSprite);
    
    int vipLevel = MyUtil::getInstance()->getVipLevel(MyGameInfo::getInstance()->getVipExperience());
    
    char str[10] = {0};
    sprintf(str,"%d",vipLevel);
    CCLabelAtlas* vipLevelLabel = CCLabelAtlas::create(str, "levelupnumber.png", 40, 32, '0');
    vipLevelLabel->setAnchorPoint(ccp(0,0.5));
    vipLevelLabel->setPosition(ccp(230,winSize.height-85));
    vipLevelLabel->setScaleY(1.2);
    vipLevelLabel->setScaleX(0.9);
    shopLayer->addChild(vipLevelLabel);
    //    if (vipLevel == 0) {
    //        vipLevelLabel->setColor(ccGRAY);
    //        vipSprite->setColor(ccGRAY);
    //    }
    
    float di = MyUtil::getInstance()->getVipExperienceByLevel(vipLevel+1)-MyUtil::getInstance()->getVipExperienceByLevel(vipLevel);
    float now = MyGameInfo::getInstance()->getVipExperience()-MyUtil::getInstance()->getVipExperienceByLevel(vipLevel);
    
    GXProgressBar* vipExpBar = GXProgressBar::create(CCSprite::create("levelBarUp.png"), CCSprite::create("BarDown.png"));
    
    vipExpBar->setContentSize(CCSizeMake(320,25));
    vipExpBar->updatePercentage(now/di);
    vipExpBar->setPosition(ccp(270,winSize.height-85-12));
    shopLayer->addChild(vipExpBar);
    
    
    
    
    CCMenuItemSprite* hotItem = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("shopHotButton.png"),CCSprite::createWithSpriteFrameName("shopHotButtonP.png"),this,menu_selector(StartScene::toDisplayHot));
    
    CCMenuItemSprite* avatarItem = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("shopAvatarButton.png"),CCSprite::createWithSpriteFrameName("shopAvatarButtonP.png"),this,menu_selector(StartScene::toDisplayAvatar));
    
    CCMenuItemSprite* unitItem = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("shopArmyButton.png"),CCSprite::createWithSpriteFrameName("shopArmyButtonP.png"),this,menu_selector(StartScene::toDisplayUnit));
    
    CCMenuItemSprite* buildingItem = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("shopBuildingButton.png"),CCSprite::createWithSpriteFrameName("shopBuildingButtonP.png"),this,menu_selector(StartScene::toDisplayBuilding));
    
    CCMenuItemSprite* resourceItem = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("shopResourceButton.png"),CCSprite::createWithSpriteFrameName("shopResourceButtonP.png"),this,menu_selector(StartScene::toDisplayResource));
    
    GXRadioMenu* radio = GXRadioMenu::create(-506,hotItem,avatarItem,unitItem,buildingItem,resourceItem,NULL);
    radio->setPosition(winSize.width/2,469);
    radio->alignItemsHorizontallyWithPadding(-10);
    shopLayer->addChild(radio);
    
}

void StartScene::toDisplayHot() {
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sfx_click.mp3");
    CCLayer* shopLayer = (CCLayer*)this->getChildByTag(creatorLayerTag);
    shopLayer->removeChildByTag(displayShopLayerTag,true);
    
    CCLayer* displayLayer = CCLayer::create();
    displayLayer->setTag(displayShopLayerTag);
    displayLayer->setPosition(ccp(0,0));
    shopLayer->addChild(displayLayer,3);
    
    
    
    
    GXScrollView* scroll = GXScrollView::create(-507);
    scroll->setOriPosition(ccp(winSize.width/2-435,32));
    scroll->setContentSize(CCSizeMake(870, 400));
    
    
    CCArray* shopCards = CCArray::create();
    shopCards->addObject(MyShopCard::create((BuildingCreator*)MyGameFactory::createCreatorbyJsonScriptFile("superKC.j", buildingCreatorClassTag),500,hotMode,this,menu_selector(StartScene::toBuyBuilding)));
    shopCards->addObject(MyShopCard::create((BuildingCreator*)MyGameFactory::createCreatorbyJsonScriptFile("superYT.j", buildingCreatorClassTag),500,hotMode,this,menu_selector(StartScene::toBuyBuilding)));
    shopCards->addObject(MyShopCard::create((BuildingCreator*)MyGameFactory::createCreatorbyJsonScriptFile("HummingBirdShop.j", buildingCreatorClassTag),500,hotMode,this,menu_selector(StartScene::toBuyArmy)));
    shopCards->addObject(MyShopCard::create(CCSprite::createWithSpriteFrameName("shopChangeNameCard.png"),"改名卡",3000,hotMode,this,menu_selector(StartScene::toChangeName)));
    //    shopCards->addObject(MyShopCard::create((UnitCreator*)MyGameFactory::createCreatorbyJsonScriptFile("V8helicopter.j", unitCreatorClassTag),50,newMode,this,menu_selector(StartScene::toDisplayUnitInfo)));
    CCObject* obj1;
    CCObject* obj2;
    CCARRAY_FOREACH(shopCards,obj1) {
        MyShopCard* card = (MyShopCard*)obj1;
        CCARRAY_FOREACH(MyGameInfo::getInstance()->boughtArray,obj2) {
            int tag = ((CCInteger*)obj2)->getValue();
            if ((tag%10000)/100 == card->getTag()) {
                card->setBoughtInfo(false);
            }
        }
    }
    
    //    shopCards->addObject(CCString::create("123"));
    //    shopCards->addObject(CCString::create("123"));
    //    buildingCards->addChild(CCString::create("123"));
    
    if (shopCards->count() >= 4) {
        scroll->setMapSize(CCSizeMake(870, 205*(shopCards->count()/2+1)));
        scroll->setPosition(ccp(scroll->getOriPosition().x,-scroll->getMapSize().height+scroll->getViewSize().height+scroll->getOriPosition().y));
    } else {
        scroll->setMapSize(CCSizeMake(870, 400));
    }
    
    CCObject* obj;
    int i=0;
    CCARRAY_FOREACH(shopCards,obj) {
        
        MyShopCard* shopCard = (MyShopCard*)obj;
        //        cardBack->setScaleX(420/cardBack->getContentSize().width);
        //        cardBack->setScaleY(190/cardBack->getContentSize().height);
        shopCard->setPosition(ccp(217+(i%2)*435,scroll->getMapSize().height-98-(i/2)*200));
        scroll->addChild(shopCard);
        i++;
    }
    
    displayLayer->addChild(scroll);
    
}

void StartScene::toDisplayAvatar() {
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sfx_click.mp3");
    CCLayer* shopLayer = (CCLayer*)this->getChildByTag(creatorLayerTag);
    shopLayer->removeChildByTag(displayShopLayerTag,true);
    
    CCLayer* displayLayer = CCLayer::create();
    displayLayer->setTag(displayShopLayerTag);
    displayLayer->setPosition(ccp(0,0));
    shopLayer->addChild(displayLayer,3);
    
    
    
    
    
    GXScrollView* scroll = GXScrollView::create(-507);
    scroll->setOriPosition(ccp(winSize.width/2-435,32));
    scroll->setContentSize(CCSizeMake(870, 400));
    
    
    CCArray* shopCards = CCArray::create();
    
    //    shopCards->addObject(MyShopCard::create(CCSprite::createWithSpriteFrameName("avatar1.png"),"青年才俊【1】",100,noMode));
    //    shopCards->addObject(MyShopCard::create(CCSprite::createWithSpriteFrameName("avatar2.png"),"青年才俊【2】",100,noMode));
    //    shopCards->addObject(MyShopCard::create(CCSprite::createWithSpriteFrameName("avatar3.png"),"青年才俊【3】",100,noMode));
    //    shopCards->addObject(MyShopCard::create(CCSprite::createWithSpriteFrameName("avatar4.png"),"巾帼英雄【1】",100,noMode));
    //    shopCards->addObject(MyShopCard::create(CCSprite::createWithSpriteFrameName("avatar5.png"),"巾帼英雄【2】",100,noMode));
    //    shopCards->addObject(MyShopCard::create(CCSprite::createWithSpriteFrameName("avatar6.png"),"巾帼英雄【3】",100,noMode));
    
    CCObject* obj1;
    CCObject* obj2;
    CCARRAY_FOREACH(shopCards,obj1) {
        MyShopCard* card = (MyShopCard*)obj1;
        CCARRAY_FOREACH(MyGameInfo::getInstance()->boughtArray,obj2) {
            int tag = ((CCInteger*)obj2)->getValue();
            if ((tag%10000)/100 == card->getTag()) {
                card->setBoughtInfo(false);
            }
        }
    }
    
    if (shopCards->count() >= 4) {
        scroll->setMapSize(CCSizeMake(870, 205*(shopCards->count()/2+1)));
        scroll->setPosition(ccp(scroll->getOriPosition().x,-scroll->getMapSize().height+scroll->getViewSize().height+scroll->getOriPosition().y));
    } else {
        scroll->setMapSize(CCSizeMake(870, 400));
    }
    
    CCObject* obj;
    int i=0;
    CCARRAY_FOREACH(shopCards,obj) {
        
        MyShopCard* shopCard = (MyShopCard*)obj;
        //        cardBack->setScaleX(420/cardBack->getContentSize().width);
        //        cardBack->setScaleY(190/cardBack->getContentSize().height);
        shopCard->setPosition(ccp(217+(i%2)*435,scroll->getMapSize().height-98-(i/2)*200));
        scroll->addChild(shopCard);
        i++;
    }
    
    displayLayer->addChild(scroll);
}

void StartScene::toDisplayUnit() {
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sfx_click.mp3");
    CCLayer* shopLayer = (CCLayer*)this->getChildByTag(creatorLayerTag);
    shopLayer->removeChildByTag(displayShopLayerTag,true);
    
    CCLayer* displayLayer = CCLayer::create();
    displayLayer->setTag(displayShopLayerTag);
    displayLayer->setPosition(ccp(0,0));
    shopLayer->addChild(displayLayer,3);
    
    
    
    
    
    GXScrollView* scroll = GXScrollView::create(-507);
    scroll->setOriPosition(ccp(winSize.width/2-435,32));
    scroll->setContentSize(CCSizeMake(870, 400));
    
    
    CCArray* shopCards = CCArray::create();
    
    shopCards->addObject(MyShopCard::create((BuildingCreator*)MyGameFactory::createCreatorbyJsonScriptFile("PanzergrenadierShop.j", buildingCreatorClassTag),500,newMode,this,menu_selector(StartScene::toBuyArmy)));
    shopCards->addObject(MyShopCard::create((BuildingCreator*)MyGameFactory::createCreatorbyJsonScriptFile("InfanterieShop.j", buildingCreatorClassTag),500,newMode,this,menu_selector(StartScene::toBuyArmy)));
    shopCards->addObject(MyShopCard::create((BuildingCreator*)MyGameFactory::createCreatorbyJsonScriptFile("HummingBirdShop.j", buildingCreatorClassTag),500,hotMode,this,menu_selector(StartScene::toBuyArmy)));
    //    shopCards->addObject(MyShopCard::create((UnitCreator*)MyGameFactory::createCreatorbyJsonScriptFile("panzerIV.j", unitCreatorClassTag),50,newMode,this,menu_selector(StartScene::toDisplayUnitInfo)));
    //    shopCards->addObject(MyShopCard::create((UnitCreator*)MyGameFactory::createCreatorbyJsonScriptFile("tiger.j", unitCreatorClassTag),50,newMode,this,menu_selector(StartScene::toDisplayUnitInfo)));
    //    shopCards->addObject(MyShopCard::create((UnitCreator*)MyGameFactory::createCreatorbyJsonScriptFile("nurse.j", unitCreatorClassTag),50,newMode,this,menu_selector(StartScene::toDisplayUnitInfo)));
    //    shopCards->addObject(MyShopCard::create((UnitCreator*)MyGameFactory::createCreatorbyJsonScriptFile("V8helicopter.j", unitCreatorClassTag),50,newMode,this,menu_selector(StartScene::toDisplayUnitInfo)));
    //    shopCards->addObject(CCString::create("123"));
    //    shopCards->addObject(CCString::create("123"));
    //    buildingCards->addChild(CCString::create("123"));
    
    CCObject* obj1;
    CCObject* obj2;
    CCARRAY_FOREACH(shopCards,obj1) {
        MyShopCard* card = (MyShopCard*)obj1;
        CCARRAY_FOREACH(MyGameInfo::getInstance()->boughtArray,obj2) {
            int tag = ((CCInteger*)obj2)->getValue();
            if ((tag%10000)/100 == card->getTag()) {
                card->setBoughtInfo(false);
            }
        }
    }
    
    if (shopCards->count() >= 4) {
        scroll->setMapSize(CCSizeMake(870, 205*(shopCards->count()/2+1)));
        scroll->setPosition(ccp(scroll->getOriPosition().x,-scroll->getMapSize().height+scroll->getViewSize().height+scroll->getOriPosition().y));
    } else {
        scroll->setMapSize(CCSizeMake(870, 400));
    }
    
    CCObject* obj;
    int i=0;
    CCARRAY_FOREACH(shopCards,obj) {
        
        MyShopCard* shopCard = (MyShopCard*)obj;
        //        cardBack->setScaleX(420/cardBack->getContentSize().width);
        //        cardBack->setScaleY(190/cardBack->getContentSize().height);
        shopCard->setPosition(ccp(217+(i%2)*435,scroll->getMapSize().height-98-(i/2)*200));
        scroll->addChild(shopCard);
        i++;
    }
    
    displayLayer->addChild(scroll);
}

void StartScene::addRecordNewIcon() {
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sfx_beattack.mp3");
    CCMenuItemToggle* item = ((CCMenuItemToggle*)controlMenu->getChildByTag(recordToggleTag));
    CCSprite* newIcon = (CCSprite*)item->getChildByTag(recordNewIcon);
    if(newIcon == NULL) {
        newIcon = CCSprite::createWithSpriteFrameName("newRecord.png");
        newIcon->setTag(recordNewIcon);
        item->addChild(newIcon,2);
    }
    newIcon->setPosition(ccp(60,30));
    newIcon->stopAllActions();
    newIcon->setScale(5);
    newIcon->setOpacity(125);
    newIcon->runAction(CCSequence::create(CCSpawn::create(CCEaseElasticOut::create(CCScaleTo::create(0.8,1),1),CCFadeTo::create(0.5,255),NULL),CCCallFuncO::create(this,callfuncO_selector(StartScene::shakeEffect),newIcon),NULL));
    
}

void StartScene::toDisplayBuilding() {
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sfx_click.mp3");
    CCLayer* shopLayer = (CCLayer*)this->getChildByTag(creatorLayerTag);
    shopLayer->removeChildByTag(displayShopLayerTag,true);
    
    CCLayer* displayLayer = CCLayer::create();
    displayLayer->setTag(displayShopLayerTag);
    displayLayer->setPosition(ccp(0,0));
    shopLayer->addChild(displayLayer,3);
    
    
    
    
    
    GXScrollView* scroll = GXScrollView::create(-507);
    scroll->setOriPosition(ccp(winSize.width/2-435,32));
    scroll->setContentSize(CCSizeMake(870, 400));
    
    
    CCArray* shopCards = CCArray::create();
    
    shopCards->addObject(MyShopCard::create((BuildingCreator*)MyGameFactory::createCreatorbyJsonScriptFile("superKC.j", buildingCreatorClassTag),500,hotMode,this,menu_selector(StartScene::toBuyBuilding)));
    shopCards->addObject(MyShopCard::create((BuildingCreator*)MyGameFactory::createCreatorbyJsonScriptFile("superYT.j", buildingCreatorClassTag),500,hotMode,this,menu_selector(StartScene::toBuyBuilding)));
    //      shopCards->addObject(MyShopCard::create((BuildingCreator*)MyGameFactory::createCreatorbyJsonScriptFile("jammer.j", buildingCreatorClassTag),500,hotMode,this,menu_selector(StartScene::toDisplayBuildingInfo)));
    //      shopCards->addObject(MyShopCard::create((BuildingCreator*)MyGameFactory::createCreatorbyJsonScriptFile("Recycling.j", buildingCreatorClassTag),500,hotMode,this,menu_selector(StartScene::toDisplayBuildingInfo)));
    //      shopCards->addObject(MyShopCard::create((BuildingCreator*)MyGameFactory::createCreatorbyJsonScriptFile("cellar.j", buildingCreatorClassTag),500,hotMode,this,menu_selector(StartScene::toDisplayBuildingInfo)));
    
    //    shopCards->addObject(CCString::create("123"));
    //    shopCards->addObject(CCString::create("123"));
    //    buildingCards->addChild(CCString::create("123"));
    
    CCObject* obj1;
    CCObject* obj2;
    CCARRAY_FOREACH(shopCards,obj1) {
        MyShopCard* card = (MyShopCard*)obj1;
        CCARRAY_FOREACH(MyGameInfo::getInstance()->boughtArray,obj2) {
            int tag = ((CCInteger*)obj2)->getValue();
            if ((tag%10000)/100 == card->getTag()) {
                card->setBoughtInfo(false);
            }
        }
    }
    
    if (shopCards->count() >= 4) {
        scroll->setMapSize(CCSizeMake(870, 205*(shopCards->count()/2+1)));
        scroll->setPosition(ccp(scroll->getOriPosition().x,-scroll->getMapSize().height+scroll->getViewSize().height+scroll->getOriPosition().y));
    } else {
        scroll->setMapSize(CCSizeMake(870, 400));
    }
    
    CCObject* obj;
    int i=0;
    CCARRAY_FOREACH(shopCards,obj) {
        
        MyShopCard* shopCard = (MyShopCard*)obj;
        //        cardBack->setScaleX(420/cardBack->getContentSize().width);
        //        cardBack->setScaleY(190/cardBack->getContentSize().height);
        shopCard->setPosition(ccp(217+(i%2)*435,scroll->getMapSize().height-98-(i/2)*200));
        scroll->addChild(shopCard);
        i++;
    }
    
    displayLayer->addChild(scroll);
}

void StartScene::toDisplayResource() {
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sfx_click.mp3");
    CCLayer* shopLayer = (CCLayer*)this->getChildByTag(creatorLayerTag);
    shopLayer->removeChildByTag(displayShopLayerTag,true);
    
    CCLayer* displayLayer = CCLayer::create();
    displayLayer->setTag(displayShopLayerTag);
    displayLayer->setPosition(ccp(0,0));
    shopLayer->addChild(displayLayer,3);
    
    
    
    
    
    GXScrollView* scroll = GXScrollView::create(-507);
    scroll->setOriPosition(ccp(winSize.width/2-435,32));
    scroll->setContentSize(CCSizeMake(870, 400));
    
    
    CCArray* shopCards = CCArray::create();
    
    shopCards->addObject(MyShopCard::create("一千功勋",1000,gloryTag,600,noMode,1,this));
    shopCards->addObject(MyShopCard::create("五千功勋",5000,gloryTag,2500,noMode,2,this));
    shopCards->addObject(MyShopCard::create("一万功勋",10000,gloryTag,4000,noMode,3,this));
    shopCards->addObject(MyShopCard::create("十万桶油",100000,oilTag,600,noMode,1,this));
    shopCards->addObject(MyShopCard::create("五十万桶油",500000,oilTag,2500,noMode,2,this));
    shopCards->addObject(MyShopCard::create("一百万桶油",1000000,oilTag,4000,noMode,3,this));
    shopCards->addObject(MyShopCard::create("十万钢锭",100000,ironTag,600,noMode,1,this));
    shopCards->addObject(MyShopCard::create("五十万钢锭",500000,ironTag,2500,noMode,2,this));
    shopCards->addObject(MyShopCard::create("一百万钢锭",1000000,ironTag,4000,noMode,3,this));
    
    
    
    
    if (shopCards->count() >= 4) {
        scroll->setMapSize(CCSizeMake(870, 205*(shopCards->count()/2+1)));
        scroll->setPosition(ccp(scroll->getOriPosition().x,-scroll->getMapSize().height+scroll->getViewSize().height+scroll->getOriPosition().y));
    } else {
        scroll->setMapSize(CCSizeMake(870, 400));
    }
    
    CCObject* obj;
    int i=0;
    CCARRAY_FOREACH(shopCards,obj) {
        
        MyShopCard* shopCard = (MyShopCard*)obj;
        //        cardBack->setScaleX(420/cardBack->getContentSize().width);
        //        cardBack->setScaleY(190/cardBack->getContentSize().height);
        shopCard->setPosition(ccp(217+(i%2)*435,scroll->getMapSize().height-98-(i/2)*200));
        scroll->addChild(shopCard);
        i++;
    }
    
    displayLayer->addChild(scroll);
}

void StartScene::toDisplayCharge() {
    
    
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sfx_click.mp3");
    
    this->removeChildByTag(displayChargeLayerTag,true);
    
    CCLayer* layer = CCLayer::create();
    layer->setTag(displayChargeLayerTag);
    
    this->addChild(layer,5);
    
    CCSprite* grayBack = CCSprite::create("whiteImage.jpg");
    grayBack->setColor(ccc3(0,0,0));
    grayBack->setOpacity(180);
    grayBack->setScaleX(winSize.width/grayBack->getContentSize().width);
    grayBack->setScaleY(winSize.width/grayBack->getContentSize().height);
    grayBack->setPosition(ccp(winSize.width/2,winSize.height/2));
    layer->addChild(grayBack);
    
    CCSprite* back = MyUtil::getInstance()->getChargeBack();
    back->setPosition(ccp(winSize.width/2,winSize.height/2));
    layer->addChild(back);
    
    CCMenuItemSprite* cancelItem =CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("uiDialogCancelButton.png"), CCSprite::createWithSpriteFrameName("uiDialogCancelButtonP.png"),this,menu_selector(StartScene::cancelTipDialog));
    cancelItem->setPosition(ccp(winSize.width/2+450,620));
    cancelItem->setAnchorPoint(ccp(1,1));
    
    GXShieldTouchMenuItem* shild = GXShieldTouchMenuItem::create();
    shild->setContentSize(winSize);
    shild->setPosition(ccp(winSize.width/2,winSize.height/2));
    
    if (MyGameInfo::getInstance()->getVipExperience() <= 0) {
#if   (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
        CCMenuItemSprite* chargePost = CCMenuItemSprite::create(CCSprite::create("chargePost.png"),CCSprite::create("chargePost.png"),this,menu_selector(StartScene::dismissPost));
#endif
#if   (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
        CCMenuItemSprite* chargePost = CCMenuItemSprite::create(CCSprite::create("chargePost.png"),CCSprite::create("chargePost.png"),this,menu_selector(StartScene::toChargeCallBack));
#endif
        
        CCSprite* chargeButton = CCSprite::create("chargePostButton (0).png");
        CCSprite* chargeButton2 =CCSprite::create("chargePostButton (1).png");
        chargeButton2->setOpacity(0);
        chargeButton2->runAction(CCRepeatForever::create(static_cast<CCSequence*>(CCSequence::create(CCFadeIn::create(1),CCFadeOut::create(1),NULL))));
        
        chargeButton->setPosition(ccp(chargePost->getContentSize().width/2-50,75));
        chargeButton2->setPosition(ccp(chargePost->getContentSize().width/2-50,75));
        chargePost->addChild(chargeButton);
        chargePost->addChild(chargeButton2);
        chargePost->setPosition(ccp(winSize.width/2-430,35));
        chargePost->setAnchorPoint(ccp(0,0));
        MyPriorityMenu* menu = MyPriorityMenu::create(-507,cancelItem,chargePost,shild,NULL);
        menu->setPosition(ccp(0,0));
        layer->addChild(menu,3);
        return;
    } else {
        MyPriorityMenu* menu = MyPriorityMenu::create(-507,cancelItem,shild,NULL);
        menu->setPosition(ccp(0,0));
        layer->addChild(menu,3);
#if   (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID )
        toChargeCallBack(0);
        layer->removeFromParentAndCleanup(true);
        return;
#endif
    }
    
    
    
#if   (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    GXScrollView* scroll = GXScrollView::create(-507);
    scroll->setOriPosition(ccp(winSize.width/2-435,35));
    scroll->setContentSize(CCSizeMake(870, 550));
    
    
    CCArray* shopCards = CCArray::create();
    shopCards->addObject(MyShopCard::create(600,6,6,this,0));
    shopCards->addObject(MyShopCard::create(3150,32,30,this,1));
    shopCards->addObject(MyShopCard::create(7480,74.8,68,this,2));
    shopCards->addObject(MyShopCard::create(14720,147.2,128,this,3));
    shopCards->addObject(MyShopCard::create(39630,396.3,328,this,4));
    shopCards->addObject(MyShopCard::create(84240,842.4,648,this,5));
    
    //    shopCards->addObject(CCString::create("123"));
    //    shopCards->addObject(CCString::create("123"));
    //    buildingCards->addChild(CCString::create("123"));
    
    if (shopCards->count() >= 6) {
        scroll->setMapSize(CCSizeMake(870, 95*(shopCards->count()/2+1)));
        scroll->setPosition(ccp(scroll->getOriPosition().x,-scroll->getMapSize().height+scroll->getViewSize().height+scroll->getOriPosition().y));
    } else {
        scroll->setMapSize(CCSizeMake(870, 550));
    }
    
    CCObject* obj;
    int i=0;
    CCARRAY_FOREACH(shopCards,obj) {
        
        MyShopCard* shopCard = (MyShopCard*)obj;
        //        cardBack->setScaleX(420/cardBack->getContentSize().width);
        //        cardBack->setScaleY(190/cardBack->getContentSize().height);
        shopCard->setPosition(ccp(435,scroll->getMapSize().height-50-i*90));
        scroll->addChild(shopCard);
        i++;
    }
    
    layer->addChild(scroll);
#endif
    
}


void StartScene::toDisplayBuildingInfo(CCMenuItem* item) {
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sfx_click.mp3");
    
    MyShopCard* card = (MyShopCard*)item;
    
    CCLayer* shopLayer = (CCLayer*)this->getChildByTag(creatorLayerTag);
    CCNode* parent = shopLayer->getChildByTag(displayShopLayerTag);
    parent->removeChildByTag(displayShopInfoLayerTag,true);
    
    //    if (parent != NULL) {
    //        parent->setVisible(false);
    //    }
    
    
    CCLayer* displayLayer = CCLayer::create();
    displayLayer->setTag(displayShopInfoLayerTag);
    //    displayLayer->setPosition(ccp(0,0));
    parent->addChild(displayLayer,4);
    
    
    CCMenuItemSprite* cancelItem =CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("uiDialogCancelButton.png"), CCSprite::createWithSpriteFrameName("uiDialogCancelButtonP.png"),this,menu_selector(StartScene::cancelTipDialog));
    cancelItem->setPosition(ccp(winSize.width/2+450,450));
    cancelItem->setAnchorPoint(ccp(1,1));
    //诡异的购买按键
    CCSprite* boughtLabel1 = CCSprite::createWithSpriteFrameName("shopBoughtLabel_2.png");
    CCSprite* shopPurchaseButton = CCSprite::createWithSpriteFrameName("shopEmptyButton.png");
    boughtLabel1->setPosition(ccp(shopPurchaseButton->getContentSize().width/2,shopPurchaseButton->getContentSize().height/2+3));
    shopPurchaseButton->addChild(boughtLabel1);
    
    
    CCSprite* boughtLabel2 = CCSprite::createWithSpriteFrameName("shopBoughtLabel_2.png");
    CCSprite* shopPurchaseButtonP = CCSprite::createWithSpriteFrameName("shopEmptyButtonP.png");
    boughtLabel2->setPosition(ccp(shopPurchaseButtonP->getContentSize().width/2,shopPurchaseButtonP->getContentSize().height/2+3));
    shopPurchaseButtonP->addChild(boughtLabel2);
    
    CCSprite* alreadyBought = CCSprite::createWithSpriteFrameName("shopBoughtLabel.png");
    CCSprite* boughtLabel = CCSprite::createWithSpriteFrameName("shopBoughtLabel_2.png");
    alreadyBought->setAnchorPoint(ccp(1,0));
    alreadyBought->setPosition(ccp(4,1));
    boughtLabel->addChild(alreadyBought);
    CCMenuItemSprite* purchaseItem = CCMenuItemSprite::create(shopPurchaseButton,shopPurchaseButtonP,boughtLabel,this,card->purchaseSelector);
    
    boughtLabel->setPosition(ccp(53,20));
    purchaseItem->setEnabled(card->buyItem->isEnabled());
    purchaseItem->setPosition(ccp(winSize.width/2-180,70));
    purchaseItem->setUserData(card);
    
    GXShieldTouchMenuItem* shild = GXShieldTouchMenuItem::create();
    shild->setContentSize(CCSizeMake(870,403));
    shild->setPosition(ccp(winSize.width/2,232));
    
    MyPriorityMenu* menu = MyPriorityMenu::create(-510,cancelItem,purchaseItem,shild,NULL);
    displayLayer->addChild(menu,4);
    menu->setPosition(ccp(0,0));
    
    CCSprite* cardBack = CCSprite::createWithSpriteFrameName("shopCardBack.png");
    cardBack->setScaleX(870/cardBack->getContentSize().width);
    cardBack->setScaleY(403/cardBack->getContentSize().height);
    cardBack->setAnchorPoint(ccp(0,0));
    cardBack->setPosition(ccp(winSize.width/2-435,32));
    displayLayer->addChild(cardBack);
    
    
    
    
    
    if (card->mode == hotMode) {
        CCSprite* hotBack = CCSprite::createWithSpriteFrameName("shopHotBack.png");
        hotBack->setAnchorPoint(ccp(0,1));
        hotBack->setPosition(ccp(winSize.width/2-435,435));
        hotBack->setColor(ccc3(183,57,3));
        hotBack->setScale(1.5);
        displayLayer->addChild(hotBack);
        
        CCSprite* hotLabel = CCSprite::createWithSpriteFrameName("shopHotLabel.png");
        hotLabel->setAnchorPoint(ccp(0,1));
        hotLabel->setPosition(ccp(3,hotBack->getContentSize().height-3));
        hotBack->addChild(hotLabel);
    } else if(card->mode == newMode) {
        CCSprite* newBack = CCSprite::createWithSpriteFrameName("shopHotBack.png");
        newBack->setScale(1.5);
        newBack->setAnchorPoint(ccp(0,1));
        newBack->setPosition(ccp(winSize.width/2-435,435));
        newBack->setColor(ccc3(3,183,57));
        displayLayer->addChild(newBack);
        
        CCSprite* newLabel =
        CCSprite::createWithSpriteFrameName("shopNewLabel.png");
        newLabel->setAnchorPoint(ccp(0,1));
        newLabel->setPosition(ccp(3,newBack->getContentSize().height-3));
        newBack->addChild(newLabel);
    }
    
    char str[100]  = {0};
    if (((BuildingCreator*)card->bean)->rarity == 0) {
        CCSprite* bp = CCSprite::createWithSpriteFrameName(((BuildingCreator*)card->bean)->getSpriteFileName());
        bp->setPosition(ccp(winSize.width/2-220,200));
        bp->setScale(Mathlib::min(310/bp->getContentSize().width,290/bp->getContentSize().height));
        displayLayer->addChild(bp,1);
        
        CCSprite* lightSprite = CCSprite::createWithSpriteFrameName("creatorLight.png");
        lightSprite->setScale(1.6);
        lightSprite->setOpacity(153);
        lightSprite->setPosition(ccp(winSize.width/2-225,200));
        displayLayer->addChild(lightSprite);
    } else {
        char str[100]  = {0};
        sprintf(str, "%sbp.png",((BuildingCreator*)card->bean)->getSpriteFileName());
        CCSprite* bp = CCSprite::createWithSpriteFrameName(str);
        bp->setPosition(ccp(winSize.width/2-205,250));
        bp->setScale(Mathlib::min(300/bp->getContentSize().width,230/bp->getContentSize().height));
        displayLayer->addChild(bp,1);
        
        CCSprite* lightSprite = CCSprite::createWithSpriteFrameName("creatorLight.png");
        lightSprite->setScale(1.3);
        lightSprite->setOpacity(153);
        lightSprite->setPosition(ccp(winSize.width/2-215,250));
        displayLayer->addChild(lightSprite);
        
        //    CCSprite* underline = CCSprite::create("white.jpg");
        
        
        float posi = (((BuildingCreator*)card->bean)->rarity-1)*50;
        for (int i = 0; i<((BuildingCreator*)card->bean)->rarity; i++) {
            CCSprite* star = CCSprite::createWithSpriteFrameName("armystar.png");
            star->setScale(1.6);
            star->setPosition(ccp(275-posi/2 + i*50,100));
            displayLayer->addChild(star);
        }
        
    }
    
    
    //    CCSprite* underline = CCSprite::create("white.jpg");
    
    
    
    
    sprintf(str,"———%s———",((BuildingCreator*)card->bean)->getBuildingName());
    CCLabelTTF* name = CCLabelTTF::create(str,"Arial",40);
    name->setPosition(ccp(winSize.width/2+180,390));
    name->setColor(ccc3(255,224,122));
    displayLayer->addChild(name);
    
    sprintf(str,"No:%d",((BuildingCreator*)card->bean)->cardId);
    CCLabelTTF* No = CCLabelTTF::create(str,"Arial",31);
    No->setColor(ccc3(255,224,122));
    No->setAnchorPoint(ccp(0,0.5));
    No->setPosition(ccp(winSize.width/2-350,380));
    displayLayer->addChild(No);
    
    
    CCLayer* infoLayer = MyGameFactory::getBuildingClassDescript((BuildingCreator*)card->bean);
    infoLayer->setPosition(ccp(winSize.width/2-20,395-infoLayer->getContentSize().height));
    purchaseItem->setAnchorPoint(ccp(0.5,1));
    purchaseItem->setPosition(ccp(winSize.width/2+180,Mathlib::min(395-infoLayer->getContentSize().height-20,165)));
    displayLayer->addChild(infoLayer);
    infoLayer->setScaleY(0.9);
}

void StartScene::toBuyBuilding(CCMenuItem* item) {
    //    CCLog("买房子啦！");
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sfx_click.mp3");
    hiddenControlUI();
    MyShopCard* shopCard = (MyShopCard*)item->getUserData();
    MyMap* map = (MyMap*)getChildByTag(MainMapTag);
    map->oriBuildPos=ccp(0,0);
    
    MyBuilding* build = createReady(((BuildingCreator*)shopCard->bean)->cardId);
    ((ReadyToBuild*)build->fsm->getCurrentState())->setResourceTag(diamondTag);
    ((ReadyToBuild*)build->fsm->getCurrentState())->setSummaryCount(shopCard->cost);
    quitCreator();
    this->removeChildByTag(controlSecondMenuTag,true);
    CCMenuItemToggle* showItem = ((CCMenuItemToggle*)controlMenu->getChildByTag(vipToggleTag));
    if (showItem->getSelectedIndex() == 1) {
        showItem->setSelectedIndex(0);
    }
}
void StartScene::toBuyArmy(CCMenuItem* item) {
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sfx_click.mp3");
    //
    //
    CCMenuItemSprite* cancelItem =CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("uiDialogCancelButton.png"), CCSprite::createWithSpriteFrameName("uiDialogCancelButtonP.png"),this,menu_selector(StartScene::cancelTipDialog));
    
    MyShopCard* shopCard = (MyShopCard*)item->getUserData();
    
    
    GXShieldTouchMenuItem* shild = GXShieldTouchMenuItem::create();
    shild->setContentSize(winSize);
    shild->setPosition(ccp(-winSize.width/2,-winSize.height/2));
    shild->setAnchorPoint(ccp(0,0));
    
    MyPriorityMenu* menu  = MyPriorityMenu::create(-511,cancelItem,shild,NULL);
    
    
    menu->setPosition(ccp(winSize.width/2, winSize.height/2 -48));
    CCLayer* layer = CCLayer::create();
    layer->setTouchEnabled(true);
    char str[70] = {0};
    sprintf(str,"%s(%d★)",((BuildingCreator*)shopCard->bean)->getBuildingName(),((BuildingCreator*)shopCard->bean)->rarity);
    CCLabelTTF* label1 = CCLabelTTF::create("解锁：", "宋体", 25,CCSizeZero, kCCTextAlignmentLeft, kCCVerticalTextAlignmentTop);
    
    label1->setColor(ccc3(230, 207, 185));
    label1->setPosition(ccp(winSize.width/2+15,winSize.height/2+80));
    
    CCLabelTTF* label2 = CCLabelTTF::create(str, "Arial", 30,CCSizeZero, kCCTextAlignmentLeft, kCCVerticalTextAlignmentTop);
    
    label2->setColor(ccc3(249, 155, 6));
    label2->setPosition(ccp(winSize.width/2+120,winSize.height/2+40));
    
    CCLabelTTF* costFontLabel = CCLabelTTF::create("花费：", "宋体", 25);
    
    
    costFontLabel->setColor(ccc3(230, 207, 185));
    costFontLabel->setPosition(ccp(winSize.width/2+15,winSize.height/2));
    
    CCSprite* costIcon = MyUtil::getInstance()->getResourceIcon(diamondTag);
    costIcon->setPosition(ccp(winSize.width/2+50,winSize.height/2-50));
    costIcon->setScale(1.1);
    
    
    sprintf(str,"%d",shopCard->cost);
    CCLabelAtlas* costLabel = CCLabelAtlas::create(str, "number6.png", 24, 36, '/');
    costLabel->setPosition(ccp(winSize.width/2+100,winSize.height/2-70));
    costLabel->setScaleY(1);
    costLabel->setScaleX(0.9);
    costLabel->setColor(ccc3(231,219,138));
    
    CCSprite* dialogBack = MyUtil::getInstance()->getDialogBack();;
    dialogBack->setPosition(ccp(winSize.width/2,winSize.height/2));
    cancelItem->setPosition(ccp(dialogBack->getContentSize().width/2 - 24,dialogBack->getContentSize().height/2 + 24));
    layer->addChild(dialogBack);
    layer->addChild(menu);
    layer->addChild(label1);
    layer->addChild(label2);
    layer->addChild(costFontLabel);
    layer->addChild(costIcon);
    layer->addChild(costLabel);
    layer->setTag(armyInfoUnlockLayerTag);
    
    
    CCMenuItemSprite* unlockButton = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("unlockButton.png"),CCSprite::createWithSpriteFrameName("unlockButtonP.png"),this,menu_selector(StartScene::toSureBuyArmy));
    unlockButton->setPosition(ccp(100,-60));
    unlockButton->setScale(1.2);
    menu->addChild(unlockButton);
    unlockButton->setUserData(shopCard);
    
    
    this->getChildByTag(creatorLayerTag)->addChild(layer,100);
    
}

void StartScene::toSureBuyArmy(CCMenuItem* item) {
    MyShopCard* card = (MyShopCard*)item->getUserData();
    CreatorInfoBean* bean = (CreatorInfoBean*)card->getUserObject();
    
    if (MyGameInfo::getInstance()->getResource(bean->creator->unlockCostResourceTag) >= bean->creator->unlockCostCount) {
        MyGameInfo::getInstance()->changeResource(bean->creator->unlockCostResourceTag,bean->creator->unlockCostCount*-1);
        CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sfx_updateBuilding.mp3");
        UpdateArmyMessage::create(bean->creator->cardId,0,1)->sendMsg();
        //发送购买道具解锁指令
        MyHttpConnection::getInstance()->sendUpdateArmyId(bean->creator->cardId);
    } else {
        CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sfx_error.wav");
        this->removeChildByTag(NoResourceTag,true);
        this->addChild(MyUtil::getInstance()->getNoResourceDialog(this,bean->creator->unlockCostResourceTag));
        return;
    }
    
    this->getChildByTag(creatorLayerTag)->getChildByTag(displayShopLayerTag)->removeChildByTag(displayShopInfoLayerTag,true);
    
    
    
    MyGameInfo::getInstance()->creatorArray->addObject(bean);
    bean->setExperience(1);
    
    
    //显示已购
    
    card->setBoughtInfo(false);
    //    CCARRAY_FOREACH(card->getChildren(),obj) {
    //        CCRGBAProtocol* color = dynamic_cast<CCRGBAProtocol*>(obj);
    //        if(color) {
    //            color->setColor(ccc3(255,255,255));
    //        }
    //    }
    //    ((CCLabelTTF*)card->getChildByTag(lvFontTag))->setOpacity(255);
    //    card->removeChildByTag(buduiLockTag,true);
    //    card->setTarget(this,menu_selector(StartScene::toArmyInfoInfo));
    cancelTipDialog(item);
}


void StartScene::toBuyResource(CCMenuItem* item) {
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sfx_click.mp3");
    //
    CCMenuItemSprite* cancelItem =CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("uiDialogCancelButton.png"), CCSprite::createWithSpriteFrameName("uiDialogCancelButtonP.png"),this,menu_selector(StartScene::cancelTipDialog));
    
    MyShopCard* shopCard = (MyShopCard*)item->getUserData();
    
    
    GXShieldTouchMenuItem* shild = GXShieldTouchMenuItem::create();
    shild->setContentSize(winSize);
    shild->setPosition(ccp(-winSize.width/2,-winSize.height/2));
    shild->setAnchorPoint(ccp(0,0));
    
    MyPriorityMenu* menu  = MyPriorityMenu::create(-511,cancelItem,shild,NULL);
    
    
    menu->setPosition(ccp(winSize.width/2, winSize.height/2 -48));
    CCLayer* layer = CCLayer::create();
    layer->setTouchEnabled(true);
    char str[70] = {0};
    sprintf(str,"%s",((ShopResourceBean*)shopCard->bean)->name->getCString());
    CCLabelTTF* label1 = CCLabelTTF::create("购买：", "宋体", 30,CCSizeZero, kCCTextAlignmentLeft, kCCVerticalTextAlignmentTop);
    
    label1->setColor(ccc3(230, 207, 185));
    label1->setPosition(ccp(winSize.width/2+15,winSize.height/2+100));
    
    CCLabelTTF* label2 = CCLabelTTF::create(str, "Arial", 35,CCSizeZero, kCCTextAlignmentLeft, kCCVerticalTextAlignmentTop);
    
    label2->setColor(ccc3(249, 155, 6));
    label2->setPosition(ccp(winSize.width/2+120,winSize.height/2+60));
    
    CCLabelTTF* costFontLabel = CCLabelTTF::create("花费：", "宋体", 30);
    
    
    costFontLabel->setColor(ccc3(230, 207, 185));
    costFontLabel->setPosition(ccp(winSize.width/2+15,winSize.height/2+10));
    
    CCSprite* costIcon = MyUtil::getInstance()->getResourceIcon(diamondTag);
    costIcon->setPosition(ccp(winSize.width/2+50,winSize.height/2-35));
    costIcon->setScale(0.9);
    
    
    sprintf(str,"%d",((ShopResourceBean*)shopCard->bean)->getCost());
    CCLabelAtlas* costLabel = CCLabelAtlas::create(str, "number6.png", 24, 36, '/');
    costLabel->setPosition(ccp(winSize.width/2+100,winSize.height/2-60));
    costLabel->setScaleY(1.1);
    costLabel->setScaleX(1);
    costLabel->setColor(ccc3(231,219,138));
    
    CCSprite* dialogBack = MyUtil::getInstance()->getDialogBackNoGirl();;
    dialogBack->setPosition(ccp(winSize.width/2,winSize.height/2));
    cancelItem->setPosition(ccp(dialogBack->getContentSize().width/2 - 24,dialogBack->getContentSize().height/2 + 24));
    layer->addChild(dialogBack);
    layer->addChild(menu);
    layer->addChild(label1);
    layer->addChild(label2);
    layer->addChild(costFontLabel);
    layer->addChild(costIcon);
    layer->addChild(costLabel);
    layer->setTag(armyInfoUnlockLayerTag);
    
    
    //诡异的购买按钮
    CCSprite* boughtLabel1 = CCSprite::createWithSpriteFrameName("shopBoughtLabel_2.png");
    CCSprite* shopPurchaseButton = CCSprite::createWithSpriteFrameName("shopEmptyButton.png");
    boughtLabel1->setPosition(ccp(shopPurchaseButton->getContentSize().width/2,shopPurchaseButton->getContentSize().height/2+3));
    shopPurchaseButton->addChild(boughtLabel1);
    
    
    CCSprite* boughtLabel2 = CCSprite::createWithSpriteFrameName("shopBoughtLabel_2.png");
    CCSprite* shopPurchaseButtonP = CCSprite::createWithSpriteFrameName("shopEmptyButtonP.png");
    boughtLabel2->setPosition(ccp(shopPurchaseButtonP->getContentSize().width/2,shopPurchaseButtonP->getContentSize().height/2+3));
    shopPurchaseButtonP->addChild(boughtLabel2);
    
    
    CCMenuItemSprite* unlockButton = CCMenuItemSprite::create(shopPurchaseButton,shopPurchaseButtonP,this,menu_selector(StartScene::toSureBuyResource));
    
    unlockButton->setPosition(ccp(100,-60));
    menu->addChild(unlockButton);
    unlockButton->setUserData(shopCard);
    
    CCNode* bp = MyGameFactory::getShopResourceIcon(((ShopResourceBean*)shopCard->bean)->getResourceTag(),((ShopResourceBean*)shopCard->bean)->displayLevel);
    bp->setPosition(ccp(winSize.width/2-130,320));
    if (bp->getContentSize().width == 0) {
        if (((ShopResourceBean*)shopCard->bean)->displayLevel == 2) {
            bp->setScale(1.2);
        } else {
            bp->setScale(1);
        }
    } else {
        bp->setScale(160/bp->getContentSize().height);
    }
    layer->addChild(bp);
    
    this->getChildByTag(creatorLayerTag)->addChild(layer,100);
}

void StartScene::toSureBuyResource(CCMenuItem* item) {
    MyShopCard* card = (MyShopCard*)item->getUserData();
    ShopResourceBean* bean = ((ShopResourceBean*)card->bean);
    if (MyGameInfo::getInstance()->getResource(diamondTag) >= bean->getCost()) {
        MyGameInfo::getInstance()->changeResource(bean->getResourceTag(),bean->getCount());
        MyGameInfo::getInstance()->changeResource(diamondTag,bean->getCost()*-1);
        CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sfx_updateBuilding.mp3");
        int tag = 30000+bean->getResourceTag()*100+bean->displayLevel;
        MyHttpConnection::getInstance()->sendBuyResource(tag);
        
    } else {
        CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sfx_error.wav");
        this->removeChildByTag(NoResourceTag,true);
        this->addChild(MyUtil::getInstance()->getNoResourceDialog(this,diamondTag));
        return;
    }
    item->getParent()->getParent()->removeFromParentAndCleanup(true);
}

void StartScene::toChargeCallBack(CCMenuItem* item) {
#if   (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    int position = (int)item->getUserData();
    this->addChild(MyUtil::getInstance()->getWaitLayer("正在连接苹果商城"),10);
    PulsarNative::toPurchase(position);
    
#endif
#if   (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    PulsarNative::toPurchase(0);
#endif
}

void StartScene::toYiJianShouKuang() {
    if (MyUtil::getInstance()->getVipLevel(MyGameInfo::getInstance()->getVipExperience()) >= 1) {
        CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sfx_collect.mp3");
        MyHttpConnection::getInstance()->sendOneKeyCollect();
        MyMap* map = (MyMap*)getChildByTag(MainMapTag);
        CCObject* obj;
        CCARRAY_FOREACH(map->getItems(),obj) {
            MyBuilding* building = (MyBuilding*)obj;
            if (building->contentSizeByTiled.width == 3) {
                CollectState* state = dynamic_cast<CollectState*>(building->fsm->getCurrentState());
                if (state) {
                    state->doCollectCheckCapacity();
                }
            }
        }
    }else {
        this->removeChildByTag(NoResourceTag,true);
        this->addChild(MyUtil::getInstance()->getVipDesc(1,this,menu_selector(StartScene::toDisplayCharge)));
    }
}

void StartScene::toOneKeyUpdate() {
    if (MyUtil::getInstance()->getVipLevel(MyGameInfo::getInstance()->getVipExperience()) >= 2) {
        toCancelSecond();
        CCLayer* back = NULL;
        CCLayer* mainLayer = CCLayer::create();
        mainLayer->setTag(creatorLayerTag);
        back = MyUtil::getInstance()->getTitleBack(700,500,true,"一键升级");
        back->setPosition(ccp(winSize.width/2,winSize.height/2));
        mainLayer->addChild(back,0);
        //        mainLayer->setScale(0.75);
        //        mainLayer->runAction(CCScaleTo::create(0.25, 1));
        
        this->addChild(mainLayer);
        
        CCLayer* contentLayer = CCLayer::create();
        //        contentLayer->setTag(recordContentLayerTag);
        
        
        GXScrollViewNoScissor* scollView = GXScrollViewNoScissor::create(-505);
        
        scollView->setOriPosition(ccp(winSize.width/2-340,winSize.height/2-240));
        MyMap* map = (MyMap*)this->getChildByTag(MainMapTag);
        CCArray* buildings = map->getItems();
        CCDictionary* tagDict = CCDictionary::create();
        
        CCSprite* lie = CCSprite::create("whiteImage.jpg");
        lie->setColor(ccc3(120,97,58));
        lie->setScaleX(6/lie->getContentSize().width);
        lie->setScaleY(440/lie->getContentSize().height);
        lie->setPosition(ccp(winSize.width/2-150,winSize.height/2-5));
        contentLayer->addChild(lie);
        
        CCObject* obj;
        //        CCObject* obj2;
        //        CCLog("%d",sizeof(unsigned long long));
        
        CCARRAY_FOREACH(buildings,obj) {
            MyBuilding* build = (MyBuilding*)obj;
            if (build->getTag() == lianluozhongxinDestroyTag || build->getTag() == ghostTag || build->getTag() >= ornamentsDefineTag) {
                continue;
            }
            CCDictionary* levelDict = (CCDictionary*)tagDict->objectForKey(build->getTag());
            if (levelDict == NULL) {
                levelDict = CCDictionary::create();
                tagDict->setObject(levelDict,build->getTag());
            }
            GXunsignedlonglongValue* count = (GXunsignedlonglongValue*)levelDict->objectForKey(build->getLevel());
            if(count == NULL) {
                if (build->getLevel() < build->getMaxLevel()) {
                    float  summaryFinalCount =build->getUpdateSummary(build->getSummaryCount(),build->getLevel());
                    count = GXunsignedlonglongValue::create(((unsigned long long)(summaryFinalCount+0.01))*100000+((unsigned long long)(build->resourceTag))*10000);
                    levelDict->setObject(count,build->getLevel());
                } else {
                    count = GXunsignedlonglongValue::create(0);
                    levelDict->setObject(count,build->getLevel());
                }
            }
            count->setValue(count->getValue()+1);
        }
        
        //        scollView->setOriPosition(ccp(winSize.width/2-300,winSize.height/2-195));
        CCArray* buildingTags = tagDict->allKeys();
        int scrollHeight  = buildingTags->count()*155+5;
        //        MyPriorityMenu* toDefendButtonMenu = MyPriorityMenu::create(-508,NULL);
        //        toDefendButtonMenu->setPosition(ccp(0,0));
        int i=0;
        
        CCLayer* buildingsUnionLayer = CCLayer::create();
        scollView->setUnionNode(buildingsUnionLayer);
        GXScissorNode* scissorNode2 = GXScissorNode::create(CCSizeMake(400,460),ccp(winSize.width/2-140,winSize.height/2-240));
        scissorNode2->addChild(buildingsUnionLayer);
        contentLayer->addChild(scissorNode2,2);
        //        contentLayer->addChild(buildingsUnionLayer,2);
        char str[30] = {0};
        CCARRAY_FOREACH_REVERSE(buildingTags, obj) {
            CCInteger* buildTag = (CCInteger*)obj;
            CCSprite* buildingSprite = MyGameFactory::getBuildingSpriteByTag(buildTag->getValue());
            float minx = Mathlib::min(150.0/buildingSprite->getContentSize().width,1);
            float miny = Mathlib::min(120.0/buildingSprite->getContentSize().height,1);
            //            buildingSprite->setScale(Mathlib::min( Mathlib::min(150/buildingSprite->getContentSize().width,150/buildingSprite->getContentSize().height),1));
            buildingSprite->setScale( Mathlib::min((minx+miny)/2,1));
            CCSprite* lightSprite = CCSprite::createWithSpriteFrameName("creatorLight.png");
            lightSprite->setScale(0.75);
            lightSprite->setPosition(ccp(100,i*155+62));
            //                lightSprite->setOpacity(123);
            lightSprite->setColor(ccc3(155,145,135));
            buildingSprite->setPosition(ccp(100,i*155+62));
            
            
            CCLabelTTF* buildingName = MyGameFactory::getBuildingNameByTag(buildTag->getValue(),30);
            buildingName->setColor(ccc3(254, 218, 130));
            buildingName->setPosition(ccp(100,i*155+132));
            
            CCSprite* hang1 = CCSprite::create("whiteImage.jpg");
            hang1->setColor(ccc3(120,97,58));
            hang1->setScaleX(630/lie->getContentSize().width);
            hang1->setScaleY(3/lie->getContentSize().height);
            hang1->setPosition(ccp(345,i*155+37));
            
            CCSprite* hang2 = CCSprite::create("whiteImage.jpg");
            hang2->setColor(ccc3(120,97,58));
            hang2->setScaleX(630/lie->getContentSize().width);
            hang2->setScaleY(12/lie->getContentSize().height);
            hang2->setPosition(ccp(345,i*155+25));
            
            scollView->addChild(hang2);
            scollView->addChild(hang1);
            scollView->addChild(lightSprite);
            scollView->addChild(buildingSprite);
            scollView->addChild(buildingName);
            
            
            CCLayer* buildingTotalLayer = CCLayer::create();
            //            GXScrollViewNoScissor* levelScollView = GXScrollViewNoScissor::create(-506);
            buildingTotalLayer->setPosition(ccp(245,i*155));
            CCDictionary* levelDiction = (CCDictionary*)tagDict->objectForKey(buildTag->getValue());
            //            CCArray* levelArray = levelDiction->allKeys();
            
            int j = 0;
            MyPriorityMenu* nextPreMenu = MyPriorityMenu::create(-506,NULL);
            for(int k=1;k<26;k++) {
                
                int levelInt = k;
                GXunsignedlonglongValue* count = (GXunsignedlonglongValue*)levelDiction->objectForKey(levelInt);
                if (count == NULL) {
                    continue;
                }
                CCLayer* buildLevelInfoLayer = CCLayer::create();
                
                CCLabelTTF* infoLabel1 = CCLabelTTF::create("等级:","Arial",25);
                infoLabel1->setPosition(ccp(-10,16));
                CCLabelTTF* infoLabel2 = CCLabelTTF::create("数量:","Arial",25);
                infoLabel2->setPosition(ccp(-10,-14));
                sprintf(str,"%d",levelInt);
                CCLabelAtlas* levelatlas = CCLabelAtlas::create(str, "number6.png", 24, 36, '/');
                levelatlas->setPosition(ccp(20,3));
                levelatlas->setTag(oneKeyUpdateLevelLabelTag);
                levelatlas->setColor(ccc3(254, 218, 130));
                levelatlas->setScale(0.75);
                int countInt = count->getValue()%10000;
                sprintf(str,"%d",countInt);
                CCLabelAtlas* countatlas = CCLabelAtlas::create(str, "number6.png", 24, 36, '/');
                countatlas->setTag(oneKeyUpdateCountLabelTag);
                countatlas->setPosition(ccp(20,-27));
                countatlas->setScale(0.75);
                countatlas->setUserData((void*)countInt);
                if (count->getValue()>9999) {
                    int resourceTag = (count->getValue()%100000)/10000;
                    CCSprite* resourceIcon = MyUtil::getInstance()->getResourceIcon(resourceTag);
                    resourceIcon->setTag(oneKeyUpdateCostIconLabelTag);
                    resourceIcon->setScale(0.5);
                    resourceIcon->setPosition(ccp(-35,-40));
                    buildLevelInfoLayer->addChild(resourceIcon);
                    
                    CCMenuItemSprite* okUpdateButton = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("metalButton.png"),CCSprite::createWithSpriteFrameName("metalButtonP.png"),this,menu_selector(StartScene::sureOneKeyUpdate));
                    okUpdateButton->setScaleY(0.9);
                    okUpdateButton->setPosition(ccp(10,-84));
                    okUpdateButton->setUserObject(CCInteger::create(buildTag->getValue()));
                    okUpdateButton->setTag(levelInt);
                    okUpdateButton->setUserData(nextPreMenu);
                    
                    CCSprite* okUpdateLabel = CCSprite::createWithSpriteFrameName("updateButtonLabel.png");
                    okUpdateLabel->setScaleY(1.1111);
                    okUpdateLabel->setPosition(ccp(okUpdateButton->getContentSize().width/2,okUpdateButton->getContentSize().height/2+3));
                    okUpdateButton->addChild(okUpdateLabel);
                    MyPriorityMenu* okUpdateButtonMenu = MyPriorityMenu::create(-506,okUpdateButton,NULL);
                    okUpdateButtonMenu->setPosition(ccp(0,0));
                    buildLevelInfoLayer->addChild(okUpdateButtonMenu);
                    
                    
                }
                
                unsigned long long allSummary = (count->getValue()/100000)*countInt;
                CCLabelTTF* allSummaryLabel = NULL;
                if (allSummary>10000) {
                    sprintf(str,"%lld万",allSummary/10000);
                    allSummaryLabel = CCLabelTTF::create(str,"Arial",23);
                    allSummaryLabel->setPosition(ccp(20,-42));
                } else if(allSummary <=0) {
                    sprintf(str,"已满级");
                    allSummaryLabel = CCLabelTTF::create(str,"Arial",26);
                    allSummaryLabel->setColor(ccc3(255,133,80));
                    allSummaryLabel->setPosition(ccp(10,-47));
                } else  {
                    sprintf(str,"%lld",allSummary);
                    allSummaryLabel = CCLabelTTF::create(str,"Arial",23);
                    allSummaryLabel->setPosition(ccp(20,-42));
                }
                allSummaryLabel->setTag(onekeyUpdateCostLabelTag);
                
                
                buildLevelInfoLayer->setPosition(ccp(j*135,110));
                buildLevelInfoLayer->addChild(infoLabel1);
                buildLevelInfoLayer->addChild(infoLabel2);
                buildLevelInfoLayer->addChild(levelatlas);
                buildLevelInfoLayer->addChild(countatlas);
                buildLevelInfoLayer->addChild(allSummaryLabel);
                buildLevelInfoLayer->setTag(levelInt);
                
                buildingTotalLayer->addChild(buildLevelInfoLayer);
                if (j>2) {
                    buildLevelInfoLayer->setVisible(false);
                }
                
                j++;
            }
            if(j>3) {
                
                CCSprite* nextIcon = CCSprite::createWithSpriteFrameName("oneKeyUpdateNextIcon.png");
                //            CCSprite* nextButton = CCSprite::createWithSpriteFrameName("oneKeyUpdateNextBack.png");
                CCSprite* nextButtonSpriteP = CCSprite::createWithSpriteFrameName("oneKeyUpdateNextBack.png");
                nextButtonSpriteP->setColor(ccc3(180,180,180));
                CCMenuItemSprite* nextButton = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("oneKeyUpdateNextBack.png"),nextButtonSpriteP,this,menu_selector(StartScene::toOneKeyNextOrPreButton));
                nextButton->addChild(nextIcon);
                nextIcon->setPosition(ccp(nextButton->getContentSize().width/2,nextButton->getContentSize().height/2));
                nextButton->setPosition(ccp(635,i*155+105));
                nextButton->setUserData(buildingTotalLayer);
                nextButton->setUserObject(CCInteger::create(0));
                nextButton->setTag(oneKeyUpdateNextButtonTag);
                nextPreMenu->addChild(nextButton);
                
                CCSprite* preIcon = CCSprite::createWithSpriteFrameName("oneKeyUpdateNextIcon.png");
                preIcon->setRotation(180);
                CCSprite* preButtonSpriteP = CCSprite::createWithSpriteFrameName("oneKeyUpdateNextBack.png");
                preButtonSpriteP->setColor(ccc3(180,180,180));
                CCMenuItemSprite* preButton = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("oneKeyUpdateNextBack.png"),preButtonSpriteP,this,menu_selector(StartScene::toOneKeyNextOrPreButton));
                preButton->addChild(preIcon);
                preIcon->setPosition(ccp(nextButton->getContentSize().width/2,nextButton->getContentSize().height/2));
                preButton->setPosition(ccp(635,i*155+60));
                preButton->setVisible(false);
                preButton->setUserData(buildingTotalLayer);
                preButton->setUserObject(CCInteger::create(0));
                preButton->setTag(oneKeyUpdatePreButtonTag);
                nextPreMenu->addChild(preButton);
                
                nextPreMenu->setPosition(ccp(0,0));
                scollView->addChild(nextPreMenu);
                
            }
            
            buildingsUnionLayer->addChild(buildingTotalLayer);
            i++;
        }
        
        
        scollView->setContentSize(CCSizeMake(680,480));
        scollView->setMapSize(CCSizeMake(200,scrollHeight));
        
        scollView->setPosition(ccp(winSize.width/2-340,-scollView->getMapSize().height+scollView->getViewSize().height+scollView->getOriPosition().y));
        
        GXScissorNode* scissorNode = GXScissorNode::create(CCSizeMake(680,480),ccp(winSize.width/2-340,winSize.height/2-240));
        scissorNode->setPosition(ccp(0,0));
        scissorNode->addChild(scollView);
        contentLayer->addChild(scissorNode);
        mainLayer->addChild(contentLayer);
        
        CCMenuItemSprite* cancelItem = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("uiDialogCancelButton.png"), CCSprite::createWithSpriteFrameName("uiDialogCancelButtonP.png"),this,menu_selector(StartScene::quitCreator));
        cancelItem->setAnchorPoint(ccp(1,1));
        cancelItem->setPosition(ccp(winSize.width/2+350,winSize.height/2+250));
        cancelItem->setScale(0.9);
        MyPriorityMenu* menu  = MyPriorityMenu::create(-508,cancelItem,NULL);
        menu->setPosition(ccp(0,0));
        contentLayer->addChild(menu);
        
    } else {
        this->removeChildByTag(NoResourceTag,true);
        this->addChild(MyUtil::getInstance()->getVipDesc(2,this,menu_selector(StartScene::toDisplayCharge)));
    }
}

void StartScene::sureOneKeyUpdate(CCMenuItem* item) {
    int level = item->getTag();
    int buildingTag = ((CCInteger*)item->getUserObject())->getValue();
    CCLayer* layer = (CCLayer*)item->getParent()->getParent()->getParent();
    CCLayer* levelUpLayer = (CCLayer*)layer->getChildByTag(level+1);
    CCLayer* levelLayer = (CCLayer*)item->getParent()->getParent();
    char str[20] = {0};
    MyMap* map = (MyMap*)this->getChildByTag(MainMapTag);
    CCArray* buildings = map->getItems();
    CCObject* obj;
    int k=0;
    
    CCLabelAtlas* oriCountAtlas = (CCLabelAtlas*)levelLayer->getChildByTag(oneKeyUpdateCountLabelTag);
    int oriCount = (int)oriCountAtlas->getUserData();
    float summaryNextLevelFinalCount = -1;
    CCARRAY_FOREACH(buildings,obj) {
        MyBuilding* build = (MyBuilding*)obj;
        if (build->getTag() == buildingTag && build->getLevel() == level) {
            if (k == 0) {
                float summaryFinalCount =build->getUpdateSummary(build->getSummaryCount(),build->getLevel());
                if (build->getLevel()+1 < build->getMaxLevel()) {
                    summaryNextLevelFinalCount = build->getUpdateSummary(build->getSummaryCount(),build->getLevel()+1);
                }
                unsigned int summaryFinalAllCount = summaryFinalCount*oriCount;
                if (MyGameInfo::getInstance()->getResource(build->resourceTag) < summaryFinalAllCount) {
                    CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sfx_error.wav");
                    this->addChild(MyUtil::getInstance()->getNoResourceDialog(this,build->resourceTag));
                    return;
                }
                
            }
            build->updateBuilding();
            k++;
        }
    }
    
    if (k != oriCount) {
        //        CCDirector::sharedDirector()->end();
        quitCreator();
        return;
    }
    UpdateBuildingMessag::create(buildingTag,level,level+1,oriCount)->sendMsg();
    
    MyHttpConnection::getInstance()->sendOneKeyUpdate(buildingTag,level);
    
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sfx_updateBuilding.mp3");
    if (levelUpLayer == NULL) {
        levelUpLayer = levelLayer;
        CCLabelAtlas* levelAtlas = (CCLabelAtlas*)levelUpLayer->getChildByTag(oneKeyUpdateLevelLabelTag);
        sprintf(str,"%d",level+1);
        levelAtlas->setString(str);
        item->setTag(level+1);
        if (summaryNextLevelFinalCount >= 0) {
            CCLabelTTF* costLabel = (CCLabelTTF*)levelUpLayer->getChildByTag(onekeyUpdateCostLabelTag);
            unsigned int summaryAllFinalCount = summaryNextLevelFinalCount*oriCount;
            if (summaryAllFinalCount>10000) {
                sprintf(str,"%d万",summaryAllFinalCount/10000);
            } else {
                sprintf(str,"%d",summaryAllFinalCount);
            }
            costLabel->setString(str);
        } else {
            CCLabelTTF* allSummaryLabel = CCLabelTTF::create("已满级","Arial",26);
            allSummaryLabel->setColor(ccc3(255,133,80));
            allSummaryLabel->setPosition(ccp(10,-47));
            allSummaryLabel->setTag(onekeyUpdateCostLabelTag);
            levelUpLayer->removeChildByTag(onekeyUpdateCostLabelTag,true);
            levelUpLayer->removeChildByTag(oneKeyUpdateCostIconLabelTag,true);
            levelUpLayer->addChild(allSummaryLabel);
            item->setEnabled(false);
            item->getParent()->runAction(GXRemoveFromParentsAction::create());
        }
    } else {
        item->setEnabled(false);
        CCLabelAtlas* levelAtlas = (CCLabelAtlas*)levelUpLayer->getChildByTag(oneKeyUpdateLevelLabelTag);
        sprintf(str,"%d",level+1);
        levelAtlas->setString(str);
        
        CCLabelAtlas* countatlas = (CCLabelAtlas*)levelUpLayer->getChildByTag(oneKeyUpdateCountLabelTag);
        int count = oriCount+(int)countatlas->getUserData();
        countatlas->setUserData((void*)count);
        sprintf(str,"%d",count);
        countatlas->setString(str);
        if (summaryNextLevelFinalCount >= 0 ) {
            CCLabelTTF* costLabel = (CCLabelTTF*)levelUpLayer->getChildByTag(onekeyUpdateCostLabelTag);
            unsigned int summaryAllFinalCount = summaryNextLevelFinalCount*count;
            if (summaryAllFinalCount>10000) {
                sprintf(str,"%d万",summaryAllFinalCount/10000);
            } else {
                sprintf(str,"%d",summaryAllFinalCount);
            }
            costLabel->setString(str);
        }
        
        bool flag = false;
        int index = -1;
        int i = 0;
        CCARRAY_FOREACH(layer->getChildren(),obj) {
            CCLayer* layer = (CCLayer*) obj;
            if (flag) {
                layer->runAction(CCMoveBy::create(0.5,ccp(-135,0)));
                if (i == index) {
                    layer->setVisible(true);
                }
            }
            if (layer == levelLayer) {
                flag = true;
                index = i - (i%3)+3;
            }
            i++;
        }
        CCARRAY_FOREACH(levelLayer->getChildren(),obj) {
            CCNode* node = (CCNode*)obj;
            node->runAction(CCFadeOut::create(0.2));
        }
        levelLayer->runAction(CCSequence::create(CCDelayTime::create(0.2),GXRemoveFromParentsAction::create(),NULL));
        int childrenCount = layer->getChildrenCount()-1;
        if (childrenCount>2) {
            CCMenuItem* preItem = (CCMenuItem*)((CCMenu*)(item->getUserData()))->getChildByTag(oneKeyUpdatePreButtonTag);
            CCMenuItem* nextItem = (CCMenuItem*)((CCMenu*)(item->getUserData()))->getChildByTag(oneKeyUpdateNextButtonTag);
            int pageNo = ((CCInteger*)preItem->getUserObject())->getValue();
            if (childrenCount>(pageNo+1)*3) {
                nextItem->setVisible(true);
            } else {
                nextItem->setVisible(false);
            }
            if(pageNo > 0){
                item->setVisible(true);
            } else {
                item->setVisible(false);
            }
        }
    }
    
}

void StartScene::toOneKeyNextOrPreButton(CCMenuItem* item) {
    int pageNo = ((CCInteger*)item->getUserObject())->getValue();
    item->setEnabled(false);
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sfx_click.mp3");
    CCLayer* target = (CCLayer*)item->getUserData();
    CCObject* obj;
    CCARRAY_FOREACH(target->getChildren(),obj) {
        CCNode* node = (CCNode*)(obj);
        node->setVisible(true);
    }
    if (item->getTag() == oneKeyUpdateNextButtonTag) {
        target->runAction(CCSequence::create(CCEaseElasticOut::create(CCMoveBy::create(1,ccp(-405,0)),1.5), CCCallFuncO::create(this,callfuncO_selector(StartScene::oneKeyNextOrPreCallback),item),NULL));
        item->setUserObject(CCInteger::create(pageNo+1));
        CCMenuItem* preItem = (CCMenuItem*)item->getParent()->getChildByTag(oneKeyUpdatePreButtonTag);
        preItem->setUserObject(CCInteger::create(pageNo+1));
        preItem->setEnabled(false);
    } else if(item->getTag() == oneKeyUpdatePreButtonTag) {
        target->runAction(CCSequence::create(CCEaseElasticOut::create( CCMoveBy::create(1,ccp(405,0)),1.5), CCCallFuncO::create(this,callfuncO_selector(StartScene::oneKeyNextOrPreCallback),item),NULL));
        item->setUserObject(CCInteger::create(pageNo-1));
        CCMenuItem* nextItem = (CCMenuItem*)item->getParent()->getChildByTag(oneKeyUpdateNextButtonTag);
        nextItem->setUserObject(CCInteger::create(pageNo-1));
        nextItem->setEnabled(false);
        
    }
}

void StartScene::oneKeyNextOrPreCallback(CCMenuItem* item) {
    int pageNo = ((CCInteger*)item->getUserObject())->getValue();
    item->setEnabled(true);
    
    CCLayer* target = (CCLayer*)item->getUserData();
    CCObject* obj;
    int i=0;
    CCARRAY_FOREACH(target->getChildren(),obj) {
        CCNode* node = (CCNode*)(obj);
        if (i< pageNo*3 || i>= (pageNo+1)*3) {
            node->setVisible(false);
        }
        i++;
    }
    if (item->getTag() == oneKeyUpdateNextButtonTag) {
        CCMenuItem* preItem = (CCMenuItem*)item->getParent()->getChildByTag(oneKeyUpdatePreButtonTag);
        preItem->setEnabled(true);
        if (target->getChildrenCount()>(pageNo+1)*3) {
            item->setVisible(true);
        } else {
            item->setVisible(false);
        }
        if(pageNo > 0){
            preItem->setVisible(true);
        } else {
            preItem->setVisible(false);
        }
    } else if(item->getTag() == oneKeyUpdatePreButtonTag) {
        CCMenuItem* nextItem = (CCMenuItem*)item->getParent()->getChildByTag(oneKeyUpdateNextButtonTag);
        nextItem->setEnabled(true);
        if (target->getChildrenCount()>(pageNo+1)*3) {
            nextItem->setVisible(true);
        } else {
            nextItem->setVisible(false);
        }
        if(pageNo > 0){
            item->setVisible(true);
        } else {
            item->setVisible(false);
        }
    }
}

void StartScene::toBoostProduce() {
    if (MyUtil::getInstance()->getVipLevel(MyGameInfo::getInstance()->getVipExperience()) >= 4) {
        MyHttpConnection::getInstance()->sendGetIsFreeBoost();
        toCancelSecond();
        this->addChild(MyUtil::getInstance()->getWaitLayer("正在加载中"));
    } else {
        this->removeChildByTag(NoResourceTag,true);
        this->addChild(MyUtil::getInstance()->getVipDesc(4,this,menu_selector(StartScene::toDisplayCharge)));
    }
}

void StartScene::displayBoostProduceView(bool isFree) {
    
    MyMap* map = (MyMap*)this->getChildByTag(MainMapTag);
    CCArray* array = map->getItems();
    CCObject* obj;
    int totalOilCapacity = 0;
    int totalIronCapacity = 0;
    int nowOilCapacity = 0;
    int nowIronCapacity = 0;
    char str[30] = {0};
    CCARRAY_FOREACH(array,obj) {
        MyBuilding* build = (MyBuilding*)obj;
        if (build->contentSizeByTiled.width > 2) {
            CollectState* state = dynamic_cast<CollectState*>(build->fsm->getCurrentState());
            if (state != NULL) {
                if (state->getResourceTag() == oilTag) {
                    totalOilCapacity+=state->getMaxCapacity();
                    nowOilCapacity+=state->getCapacity();
                } else if(state->getResourceTag() == ironTag) {
                    totalIronCapacity+=state->getMaxCapacity();
                    nowIronCapacity+=state->getCapacity();
                }
            }
        }
    }
    
    CCLayer* mainLayer = CCLayer::create();
    mainLayer->setTag(creatorLayerTag);
    CCLayer* back = MyUtil::getInstance()->getTitleBack(500,370,true,"极速生产");
    back->setPosition(ccp(winSize.width/2+50,winSize.height/2));
    mainLayer->addChild(back,0);
    this->addChild(mainLayer);
    
    CCLabelTTF* yujichanzhiLabel = CCLabelTTF::create("预计产量：","Arial",25);
    yujichanzhiLabel->setPosition(ccp(winSize.width/2+70,450));
    yujichanzhiLabel->setAnchorPoint(ccp(1,0.5));
    yujichanzhiLabel->setColor(ccc3(255,231,19));
    
    CCSprite* yjoilIcon = MyUtil::getInstance()->getResourceIcon(oilTag);
    yjoilIcon->setPosition(ccp(winSize.width/2+80,450));
    yjoilIcon->setScale(Mathlib::min((30/yjoilIcon->getContentSize().width+30/yjoilIcon->getContentSize().height)/2,1));
    
    sprintf(str,"%d",(int)(totalOilCapacity-nowOilCapacity));
    CCLabelAtlas* yjoilCount = CCLabelAtlas::create(str, "number6.png", 24, 36, '/');
    yjoilCount->setScale(0.7);
    yjoilCount->setPosition(ccp(winSize.width/2+110,450));
    yjoilCount->setAnchorPoint(ccp(0,0.5));
    
    CCSprite* yjironIcon = MyUtil::getInstance()->getResourceIcon(ironTag);
    yjironIcon->setScale(Mathlib::min((30/yjironIcon->getContentSize().width+30/yjironIcon->getContentSize().height)/2,1));
    yjironIcon->setPosition(ccp(winSize.width/2+80,410));
    
    sprintf(str,"%d",(int)(totalIronCapacity-nowIronCapacity));
    CCLabelAtlas* yjironCount = CCLabelAtlas::create(str, "number6.png", 24, 36, '/');
    yjironCount->setScale(0.7);
    yjironCount->setPosition(ccp(winSize.width/2+110,410));
    yjironCount->setAnchorPoint(ccp(0,0.5));
    
    mainLayer->addChild(yujichanzhiLabel);
    mainLayer->addChild(yjoilIcon);
    mainLayer->addChild(yjoilCount);
    mainLayer->addChild(yjironIcon);
    mainLayer->addChild(yjironCount);
    
    CCLabelTTF* totalChanzhi = CCLabelTTF::create("最大产量：","Arial",25);
    totalChanzhi->setAnchorPoint(ccp(1,0.5));
    totalChanzhi->setPosition(ccp(winSize.width/2+70,360));
    totalChanzhi->setColor(ccc3(255,231,19));
    
    CCSprite* totaloilIcon = MyUtil::getInstance()->getResourceIcon(oilTag);
    totaloilIcon->setPosition(ccp(winSize.width/2+80,360));
    totaloilIcon->setScale(Mathlib::min((30/totaloilIcon->getContentSize().width+30/totaloilIcon->getContentSize().height)/2,1));
    
    sprintf(str,"%d",(int)(totalOilCapacity));
    CCLabelAtlas* totaloilCount = CCLabelAtlas::create(str, "number6.png", 24, 36, '/');
    totaloilCount->setPosition(ccp(winSize.width/2+110,360));
    totaloilCount->setAnchorPoint(ccp(0,0.5));
    totaloilCount->setScale(0.7);
    
    CCSprite* totolironIcon = MyUtil::getInstance()->getResourceIcon(ironTag);
    totolironIcon->setScale(Mathlib::min((30/totolironIcon->getContentSize().width+30/totolironIcon->getContentSize().height)/2,1));
    totolironIcon->setPosition(ccp(winSize.width/2+80,320));
    
    sprintf(str,"%d",(int)(totalIronCapacity));
    CCLabelAtlas* totolironCount = CCLabelAtlas::create(str, "number6.png", 24, 36, '/');
    totolironCount->setPosition(ccp(winSize.width/2+110,320));
    totolironCount->setAnchorPoint(ccp(0,0.5));
    totolironCount->setScale(0.7);
    
    mainLayer->addChild(totalChanzhi);
    mainLayer->addChild(totaloilIcon);
    mainLayer->addChild(totaloilCount);
    mainLayer->addChild(totolironIcon);
    mainLayer->addChild(totolironCount);
    
    CCLabelTTF* rateTitleLabel = CCLabelTTF::create("生产比：","Arial",25);
    rateTitleLabel->setPosition(ccp(winSize.width/2+95,280));
    rateTitleLabel->setAnchorPoint(ccp(1,0.5));
    rateTitleLabel->setColor(ccc3(255,231,19));
    float rate = (float)(nowOilCapacity+nowIronCapacity)/(float)(totalOilCapacity+totalIronCapacity);
    sprintf(str,"%%%.1f",((1-rate)*100));
    CCLabelTTF* rateLabel = CCLabelTTF::create(str,"Arial",25);
    rateLabel->setPosition(ccp(winSize.width/2+125,280));
    
    mainLayer->addChild(rateTitleLabel);
    mainLayer->addChild(rateLabel);
    
    CCSprite* line1 = CCSprite::create("whiteImage.jpg");
    line1->setColor(ccc3(186,173,131));
    line1->setScaleX(250/line1->getContentSize().width);
    line1->setScaleY(2/line1->getContentSize().height);
    line1->setPosition(ccp(winSize.width/2+85,255));
    
    mainLayer->addChild(line1);
    
    CCLabelTTF* costDescLabel =  CCLabelTTF::create("花费：","Arial",25);
    costDescLabel->setAnchorPoint(ccp(1,0.5));
    costDescLabel->setPosition(ccp(winSize.width/2+70,230));
    costDescLabel->setColor(ccc3(255,231,19));
    
    
    if (!isFree) {
        CCSprite* diamondIcon = MyUtil::getInstance()->getResourceIcon(diamondTag);
        diamondIcon->setPosition(ccp(winSize.width/2+80,235));
        diamondIcon->setScale(0.7);
        
        CCLabelAtlas* diamondCount = CCLabelAtlas::create("700", "number6.png", 24, 36, '/');
        diamondCount->setPosition(ccp(winSize.width/2+110,230));
        diamondCount->setAnchorPoint(ccp(0,0.5));
        diamondCount->setScale(0.75);
        diamondCount->setColor(ccc3(255,231,19));
        
        mainLayer->addChild(diamondIcon);
        mainLayer->addChild(diamondCount);
    } else {
        CCLabelTTF* freeLabel = CCLabelTTF::create("今日首次免费", "Arial", 25);
        freeLabel->setPosition(ccp(winSize.width/2+80,230));
        freeLabel->setAnchorPoint(ccp(0,0.5));
        freeLabel->setColor(ccc3(255,231,19));
        
        mainLayer->addChild(freeLabel);
    }
    mainLayer->addChild(costDescLabel);
    
    CCSprite* line2 = CCSprite::create("whiteImage.jpg");
    line2->setColor(ccc3(186,173,131));
    line2->setScaleX(400/line1->getContentSize().width);
    line2->setScaleY(1/line1->getContentSize().height);
    line2->setPosition(ccp(winSize.width/2+50,208));
    mainLayer->addChild(line2);
    
    CCSprite* line3 = CCSprite::create("whiteImage.jpg");
    line3->setColor(ccc3(186,173,131));
    line3->setScaleX(400/line1->getContentSize().width);
    line3->setScaleY(4/line1->getContentSize().height);
    line3->setPosition(ccp(winSize.width/2+50,203));
    mainLayer->addChild(line3);
    
    CCSprite* girl = CCSprite::createWithSpriteFrameName("girl.png");
    girl->setPosition(ccp(winSize.width/2-192,winSize.height/2));
    mainLayer->addChild(girl);
    
    CCMenuItemSprite* sureItem = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("dialogsure.png"),CCSprite::createWithSpriteFrameName("dialogsurep.png"),this,menu_selector(StartScene::sureBoostProduce));
    sureItem->setPosition(winSize.width/2+100,175);
    sureItem->setScale(0.9);
    sureItem->setUserData((void*) isFree);
    
    CCMenuItemSprite* cancelItem = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("uiDialogCancelButton.png"), CCSprite::createWithSpriteFrameName("uiDialogCancelButtonP.png"),this,menu_selector(StartScene::quitCreator));
    cancelItem->setAnchorPoint(ccp(1,1));
    cancelItem->setPosition(winSize.width/2+300,winSize.height/2+185);
    
    MyPriorityMenu* menu = MyPriorityMenu::create(-505,sureItem,cancelItem,NULL);
    menu->setPosition(ccp(0,0));
    mainLayer->addChild(menu);
}

void StartScene::sureBoostProduce(CCMenuItem* item) {
    bool isFree =(bool) item->getUserData();
    item->setEnabled(false);
    if (!isFree) {
        if(MyGameInfo::getInstance()->getResource(diamondTag) < 700) {
            this->addChild(MyUtil::getInstance()->getNoResourceDialog(this,diamondTag));
            return;
        }
        MyGameInfo::getInstance()->changeResource(diamondTag,-700);
    }
    
    MyMap* map = (MyMap*)this->getChildByTag(MainMapTag);
    CCArray* array = map->getItems();
    CCObject* obj;
    CCARRAY_FOREACH(array,obj) {
        MyBuilding* build = (MyBuilding*)obj;
        if (build->contentSizeByTiled.width > 2) {
            CollectState* state = dynamic_cast<CollectState*>(build->fsm->getCurrentState());
            if (state != NULL) {
                state->setCapacity(state->getMaxCapacity(),0);
            }
        }
    }
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sfx_updateBuilding.mp3");
    MyHttpConnection::getInstance()->sendSureBoost();
    item->getParent()->getParent()->runAction(GXRemoveFromParentsAction::create());
}

void StartScene::toResourceConversion(CCMenuItem* item) {
    if (MyUtil::getInstance()->getVipLevel(MyGameInfo::getInstance()->getVipExperience()) >= 3) {
        quitCreator();
        toCancelSecond();
        CCLayer* mainLayer = CCLayer::create();
        mainLayer->setTag(creatorLayerTag);
        CCLayer* back = MyUtil::getInstance()->getTitleBack(570,370,true,"资源转换");
        back->setPosition(ccp(winSize.width/2,winSize.height/2));
        mainLayer->addChild(back,0);
        this->addChild(mainLayer);
        
        
        CCMenuItemSprite* oilToIron = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("conversionButton.png"),CCSprite::createWithSpriteFrameName("conversionButtonP.png"),this,menu_selector(StartScene::changeConversionType));
        oilToIron->setPosition(ccp(winSize.width/2-123,400));
        oilToIron->setScale(2);
        oilToIron->setUserData((void*) 0);
        
        CCSprite* oilToIronLight1 = CCSprite::createWithSpriteFrameName("creatorLight.png");
        oilToIronLight1->setPosition(ccp(oilToIron->getContentSize().width/2-30,oilToIron->getContentSize().height/2));
        oilToIronLight1->setScale(0.15);
        oilToIronLight1->setColor(ccc3(155,145,135));
        oilToIronLight1->setOpacity(153);
        
        
        CCSprite* oilToIronResourceIcon1 = MyUtil::getInstance()->getResourceIcon(oilTag);
        oilToIronResourceIcon1->setScale(0.4);
        oilToIronResourceIcon1->setPosition(ccp(oilToIron->getContentSize().width/2-30,oilToIron->getContentSize().height/2));
        
        
        CCSprite* oilToIronLight2 = CCSprite::createWithSpriteFrameName("creatorLight.png");
        oilToIronLight2->setPosition(ccp(oilToIron->getContentSize().width/2+30,oilToIron->getContentSize().height/2));
        oilToIronLight2->setScale(0.15);
        oilToIronLight2->setColor(ccc3(155,145,135));
        oilToIronLight2->setOpacity(153);
        
        
        CCSprite* oilToIronResourceIcon2 = MyUtil::getInstance()->getResourceIcon(ironTag);
        oilToIronResourceIcon2->setScale(0.4);
        oilToIronResourceIcon2->setPosition(ccp(oilToIron->getContentSize().width/2+30,oilToIron->getContentSize().height/2));
        
        CCSprite* oilToIronConversionIcon = CCSprite::createWithSpriteFrameName("conversionIcon.png");
        oilToIronConversionIcon->setPosition(ccp(oilToIron->getContentSize().width/2,oilToIron->getContentSize().height/2));
        oilToIronConversionIcon->setScale(0.5);
        
        oilToIron->addChild(oilToIronLight1);
        oilToIron->addChild(oilToIronResourceIcon1);
        oilToIron->addChild(oilToIronLight2);
        oilToIron->addChild(oilToIronResourceIcon2);
        oilToIron->addChild(oilToIronConversionIcon);
        
        
        CCMenuItemSprite* ironToOil = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("conversionButton.png"),CCSprite::createWithSpriteFrameName("conversionButtonP.png"),this,menu_selector(StartScene::changeConversionType));
        ironToOil->setPosition(ccp(winSize.width/2+123,400));
        ironToOil->setScale(2);
        ironToOil->setUserData((void*) 1);
        
        
        CCSprite* ironToOilLight1 = CCSprite::createWithSpriteFrameName("creatorLight.png");
        ironToOilLight1->setPosition(ccp(ironToOil->getContentSize().width/2-30,ironToOil->getContentSize().height/2));
        ironToOilLight1->setScale(0.15);
        ironToOilLight1->setColor(ccc3(155,145,135));
        ironToOilLight1->setOpacity(153);
        
        
        CCSprite* ironToOilResourceIcon1 = MyUtil::getInstance()->getResourceIcon(ironTag);
        ironToOilResourceIcon1->setScale(0.4);
        ironToOilResourceIcon1->setPosition(ccp(ironToOil->getContentSize().width/2-30,ironToOil->getContentSize().height/2));
        
        
        CCSprite* ironToOilLight2 = CCSprite::createWithSpriteFrameName("creatorLight.png");
        ironToOilLight2->setPosition(ccp(ironToOil->getContentSize().width/2+30,ironToOil->getContentSize().height/2));
        ironToOilLight2->setScale(0.15);
        ironToOilLight2->setColor(ccc3(155,145,135));
        ironToOilLight2->setOpacity(153);
        
        
        CCSprite* ironToOilResourceIcon2 = MyUtil::getInstance()->getResourceIcon(oilTag);
        ironToOilResourceIcon2->setScale(Mathlib::min((20/ironToOilResourceIcon2->getContentSize().width+20/ironToOilResourceIcon2->getContentSize().height)/2,1));
        ironToOilResourceIcon2->setPosition(ccp(ironToOil->getContentSize().width/2+30,ironToOil->getContentSize().height/2));
        
        CCSprite* ironToOilConversionIcon = CCSprite::createWithSpriteFrameName("conversionIcon.png");
        ironToOilConversionIcon->setPosition(ccp(ironToOil->getContentSize().width/2,ironToOil->getContentSize().height/2));
        ironToOilConversionIcon->setScale(0.5);
        
        ironToOil->addChild(ironToOilLight1);
        ironToOil->addChild(ironToOilResourceIcon1);
        ironToOil->addChild(ironToOilLight2);
        ironToOil->addChild(ironToOilResourceIcon2);
        ironToOil->addChild(ironToOilConversionIcon);
        
        GXRadioMenu* conversionMenu = GXRadioMenu::create(-505 ,oilToIron,ironToOil,NULL);
        conversionMenu->setPosition(0,0);
        mainLayer->addChild(conversionMenu,2);
        
        CCSprite* middleLine = CCSprite::create("whiteImage.jpg");
        middleLine->setPosition(ccp(winSize.width/2,400));
        middleLine->setScaleX(2/middleLine->getContentSize().width);
        middleLine->setScaleY(100/middleLine->getContentSize().height);
        middleLine->setColor(ccc3(171,155,98));
        
        
        mainLayer->addChild(middleLine);
        
        GXScrollBar* scroll = GXScrollBar::create(-505,400,this,(SEL_ScrollBarChangeRate)(&StartScene::changeConversionResource));
        scroll->setPosition(ccp(winSize.width/2,winSize.height/2));
        mainLayer->addChild(scroll);
        mainLayer->setUserData(scroll);
        
        CCSprite* createLight1 = CCSprite::createWithSpriteFrameName("creatorLight.png");
        createLight1->setPosition(ccp(winSize.width/2-230,270));
        createLight1->setScale(0.25);
        createLight1->setColor(ccc3(155,145,135));
        createLight1->setOpacity(153);
        
        CCLabelAtlas* resouceCount1 = CCLabelAtlas::create("0", "number6.png", 24, 36, '/');
        resouceCount1->setScale(0.9);
        resouceCount1->setAnchorPoint(ccp(0.5,0.5));
        resouceCount1->setPosition(ccp(winSize.width/2-120,270));
        resouceCount1->setTag(conversionResourceCountLabel1);
        scroll->setUserObject(resouceCount1);
        
        CCSprite* resourceIcon1 = MyUtil::getInstance()->getResourceIcon(oilTag);
        resourceIcon1->setScale(Mathlib::min((35/resourceIcon1->getContentSize().width+35/resourceIcon1->getContentSize().height)/2,1));
        resourceIcon1->setPosition(ccp(winSize.width/2-230,270));
        resourceIcon1->setTag(conversionOilTag);
        
        
        CCSprite* createLight2 = CCSprite::createWithSpriteFrameName("creatorLight.png");
        createLight2->setPosition(ccp(winSize.width/2+50,270));
        createLight2->setScale(0.25);
        createLight2->setColor(ccc3(155,145,135));
        createLight2->setOpacity(153);
        
        CCLabelAtlas* resouceCount2 = CCLabelAtlas::create("0", "number6.png", 24, 36, '/');
        resouceCount2->setScale(0.9);
        resouceCount2->setAnchorPoint(ccp(0.5,0.5));
        resouceCount2->setPosition(ccp(winSize.width/2+160,270));
        resouceCount2->setTag(conversionResourceCountLabel2);
        scroll->setUserData(resouceCount2);
        
        CCSprite* resourceIcon2 = MyUtil::getInstance()->getResourceIcon(ironTag);
        resourceIcon2->setScale(Mathlib::min((35/resourceIcon2->getContentSize().width+35/resourceIcon2->getContentSize().height)/2,1));
        resourceIcon2->setPosition(ccp(winSize.width/2+50,270));
        resourceIcon2->setTag(conversionIronTag);
        
        CCSprite* conversionIcon = CCSprite::createWithSpriteFrameName("conversionIcon.png");
        conversionIcon->setPosition(ccp(winSize.width/2,270));
        
        mainLayer->addChild(createLight1);
        mainLayer->addChild(resouceCount1);
        mainLayer->addChild(createLight2);
        mainLayer->addChild(resouceCount2);
        mainLayer->addChild(resourceIcon2);
        mainLayer->addChild(resourceIcon1);
        mainLayer->addChild(conversionIcon);
        
        CCSprite* gou = CCSprite::createWithSpriteFrameName("conversionCheckBox.png");
        
        CCSprite* gouMark = CCSprite::createWithSpriteFrameName("conversionCheckBoxMark.png");
        gouMark->setAnchorPoint(ccp(0,0));
        gou->addChild(gouMark);
        
        CCMenuItemSprite* gouItem1 = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("conversionCheckBox.png"),gou,this,menu_selector(StartScene::changeConversionRate));
        gouItem1->setPosition(ccp(winSize.width/2-25,220));
        
        gouItem1->setContentSize(CCSizeMake(400,gouItem1->getContentSize().height));
        CCLabelTTF* gouItemLabel1 = CCLabelTTF::create("转化率100%,花费","Arial",23);
        gouItemLabel1->setPosition(ccp(40,gouItem1->getContentSize().height/2));
        gouItemLabel1->setAnchorPoint(ccp(0,0.5));
        gouItemLabel1->setColor(ccc3(255,210,0));
        gouItem1->addChild(gouItemLabel1);
        gouItem1->setUserData((void*) 0);
        
        CCSprite* diamondIcon = MyUtil::getInstance()->getResourceIcon(diamondTag);
        diamondIcon->setScale(0.7);
        diamondIcon->setPosition(ccp(winSize.width/2+15,225));
        
        CCLabelAtlas* diamondCount = CCLabelAtlas::create("10", "number6.png", 24, 36, '/');
        diamondCount->setAnchorPoint(ccp(0,0.5));
        diamondCount->setColor(ccc3(255,210,0));
        diamondCount->setScaleY(0.7);
        diamondCount->setScaleX(0.6);
        diamondCount->setTag(conversionDiamondCountLabel);
        diamondCount->setPosition(ccp(winSize.width/2+30,220));
        
        CCSprite* gou2 = CCSprite::createWithSpriteFrameName("conversionCheckBox.png");
        
        CCSprite* gouMark2 = CCSprite::createWithSpriteFrameName("conversionCheckBoxMark.png");
        gouMark2->setAnchorPoint(ccp(0,0));
        gou2->addChild(gouMark2);
        
        CCMenuItemSprite* gouItem2 = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("conversionCheckBox.png"),gou2,this,menu_selector(StartScene::changeConversionRate));
        gouItem2->setPosition(ccp(winSize.width/2-125,175));
        gouItem2->setContentSize(CCSizeMake(200,gouItem2->getContentSize().height));
        CCLabelTTF* gouItemLabel2 = CCLabelTTF::create("转化率50%,免费","Arial",23);
        gouItemLabel2->setPosition(ccp(40,gouItem1->getContentSize().height/2));
        gouItemLabel2->setAnchorPoint(ccp(0,0.5));
        gouItemLabel2->setColor(ccc3(255,210,0));
        gouItem2->addChild(gouItemLabel2);
        gouItem2->setUserData((void*) 1);
        mainLayer->setUserObject((GXfloatValue::create(0.5)));
        
        
        
        GXRadioMenu* gouMenu = GXRadioMenu::create(-505,gouItem2,gouItem1,NULL);
        gouMenu->setPosition(ccp(0,0));
        mainLayer->addChild(gouMenu);
        mainLayer->addChild(diamondCount);
        mainLayer->addChild(diamondIcon);
        
        
        CCMenuItemSprite* cancelItem = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("uiDialogCancelButton.png"), CCSprite::createWithSpriteFrameName("uiDialogCancelButtonP.png"),this,menu_selector(StartScene::quitCreator));
        cancelItem->setAnchorPoint(ccp(1,1));
        cancelItem->setPosition(ccp(winSize.width/2+285,winSize.height/2+185));
        
        CCMenuItemSprite* unlockButton = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("dialogsure.png"),CCSprite::createWithSpriteFrameName("dialogsurep.png"),this,menu_selector(StartScene::sureConversionResource));
        unlockButton->setPosition(ccp(winSize.width/2+170,200));
        
        GXShieldTouchMenuItem* shild = GXShieldTouchMenuItem::create();
        shild->setContentSize(CCSizeMake(570,370));
        shild->setPosition(ccp(winSize.width/2,winSize.height/2));
        shild->setAnchorPoint(ccp(0.5,0.5));
        
        MyPriorityMenu* menu = MyPriorityMenu::create(-504,unlockButton,cancelItem,shild,NULL);
        menu->setPosition(ccp(0,0));
        mainLayer->addChild(menu);
        
    } else {
        this->removeChildByTag(NoResourceTag,true);
        this->addChild(MyUtil::getInstance()->getVipDesc(3,this,menu_selector(StartScene::toDisplayCharge)));
    }
}

void StartScene::changeConversionType(CCMenuItem* item) {
    int flag = (int)item->getUserData();
    CCLayer* mainLayer = (CCLayer*)item->getParent()->getParent();
    GXfloatValue* rate = ((GXfloatValue*)mainLayer->getUserObject());
    if(rate == NULL) {
        return;
    }
    if(flag == 1) {
        if (rate->getValue() < 5) {
            rate->setValue(rate->getValue()+6);
            refreshConversionUI(mainLayer,1);
        }
    } else if(flag == 0) {
        if (rate->getValue() > 5) {
            rate->setValue(rate->getValue()-6);
            refreshConversionUI(mainLayer,0);
        }
    }
}

void StartScene::changeConversionRate(CCMenuItem* item) {
    CCLayer* mainLayer = (CCLayer*)item->getParent()->getParent();
    int flag = (int)item->getUserData();
    GXfloatValue* rate = ((GXfloatValue*)mainLayer->getUserObject());
    if (flag == 0) {
        //%100转化率
        
        if (rate->getValue() > 5) {
            if (rate->getValue() > 6.5) {
                return;
            }
            rate->setValue(7);
        } else {
            if (rate->getValue() > 0.5) {
                return;
            }
            rate->setValue(1);
        }
        CCLabelAtlas* resourceCount1 = (CCLabelAtlas*)mainLayer->getChildByTag(conversionResourceCountLabel1);
        
        
        CCLabelAtlas* resourceCount2 = (CCLabelAtlas*)mainLayer->getChildByTag(conversionResourceCountLabel2);
        resourceCount2->setString(resourceCount1->getString());
        
    } else if (flag == 1) {
        //%50转化率
        if (rate->getValue() > 5) {
            if (rate->getValue() < 6.6) {
                return;
            }
            rate->setValue(6.5);
        } else {
            if (rate->getValue() < 0.6) {
                return;
            }
            rate->setValue(0.5);
        }
        
        char str[30] = {0};
        
        CCLabelAtlas* resourceCount1 = (CCLabelAtlas*)mainLayer->getChildByTag(conversionResourceCountLabel1);
        int count1 = atoi( resourceCount1->getString());
        
        CCLabelAtlas* resourceCount2 = (CCLabelAtlas*)mainLayer->getChildByTag(conversionResourceCountLabel2);
        int count2 = count1*0.5;
        sprintf(str,"%d",count2);
        resourceCount2->setString(str);
        
    }
    
}

void StartScene::changeConversionResource(CCObject* obj) {
    GXScrollBar* bar = (GXScrollBar*)obj;
    CCLayer* mainLayer = (CCLayer*)bar->getParent();
    float rate = ((GXfloatValue*)mainLayer->getUserObject())->getValue();
    if (rate > 5 ) {
        char str[30] = {0};
        CCLabelAtlas* resourceCount1 = (CCLabelAtlas*)bar->getUserObject();
        int ironCount = MyGameInfo::getInstance()->getIron()*bar->percentage;
        sprintf(str,"%d",ironCount);
        resourceCount1->setString(str);
        
        CCLabelAtlas* resourceCount2 = (CCLabelAtlas*)bar->getUserData();
        int oilCount = ironCount*(rate-6);
        sprintf(str,"%d",oilCount);
        resourceCount2->setString(str);
        
        int diamondCount = Mathlib::max(10,ironCount/20000);
        CCLabelAtlas* diamondCountLabel = (CCLabelAtlas*)mainLayer->getChildByTag(conversionDiamondCountLabel);
        sprintf(str,"%d",diamondCount);
        diamondCountLabel->setString(str);
        
    } else {
        char str[30] = {0};
        CCLabelAtlas* resourceCount1 = (CCLabelAtlas*)bar->getUserObject();
        int oilCount = MyGameInfo::getInstance()->getOil()*bar->percentage;
        sprintf(str,"%d",oilCount);
        resourceCount1->setString(str);
        
        CCLabelAtlas* resourceCount2 = (CCLabelAtlas*)bar->getUserData();
        int ironCount = oilCount*rate;
        sprintf(str,"%d",ironCount);
        resourceCount2->setString(str);
        
        int diamondCount = Mathlib::max(10,oilCount/20000);
        CCLabelAtlas* diamondCountLabel = (CCLabelAtlas*)mainLayer->getChildByTag(conversionDiamondCountLabel);
        sprintf(str,"%d",diamondCount);
        diamondCountLabel->setString(str);
    }
}

void StartScene::refreshConversionUI(CCLayer* mainLayer,int typeInt) {
    float barRate =
    ((GXScrollBar*)mainLayer->getUserData())->percentage;
    float rate = ((GXfloatValue*)mainLayer->getUserObject())->getValue();
    if (typeInt == 0) {
        CCSprite* oilIcon = (CCSprite*)mainLayer->getChildByTag(conversionOilTag);
        CCSprite* ironIcon = (CCSprite*)mainLayer->getChildByTag(conversionIronTag);
        oilIcon->setPositionX(winSize.width/2-230);
        ironIcon->setPositionX(winSize.width/2+50);
        
        
        char str[30] = {0};
        CCLabelAtlas* resourceCount1 = (CCLabelAtlas*)mainLayer->getChildByTag(conversionResourceCountLabel1);
        int oilCount = MyGameInfo::getInstance()->getOil()*barRate;
        sprintf(str,"%d",oilCount);
        resourceCount1->setString(str);
        
        CCLabelAtlas* resourceCount2 = (CCLabelAtlas*)mainLayer->getChildByTag(conversionResourceCountLabel2);
        int ironCount = oilCount*rate;
        sprintf(str,"%d",ironCount);
        resourceCount2->setString(str);
        
        int diamondCount = Mathlib::max(10,oilCount/20000);
        CCLabelAtlas* diamondCountLabel = (CCLabelAtlas*)mainLayer->getChildByTag(conversionDiamondCountLabel);
        sprintf(str,"%d",diamondCount);
        diamondCountLabel->setString(str);
        
    } else if(typeInt == 1) {
        CCSprite* oilIcon = (CCSprite*)mainLayer->getChildByTag(conversionOilTag);
        CCSprite* ironIcon = (CCSprite*)mainLayer->getChildByTag(conversionIronTag);
        oilIcon->setPositionX(winSize.width/2+50);
        ironIcon->setPositionX(winSize.width/2-230);
        
        char str[30] = {0};
        CCLabelAtlas* resourceCount1 = (CCLabelAtlas*)mainLayer->getChildByTag(conversionResourceCountLabel1);
        int ironCount = MyGameInfo::getInstance()->getIron()*barRate;
        sprintf(str,"%d",ironCount);
        resourceCount1->setString(str);
        
        CCLabelAtlas* resourceCount2 = (CCLabelAtlas*)mainLayer->getChildByTag(conversionResourceCountLabel2);
        int oilCount = ironCount*(rate-6);
        sprintf(str,"%d",oilCount);
        resourceCount2->setString(str);
        
        int diamondCount = Mathlib::max(10,ironCount/20000);
        CCLabelAtlas* diamondCountLabel = (CCLabelAtlas*)mainLayer->getChildByTag(conversionDiamondCountLabel);
        sprintf(str,"%d",diamondCount);
        diamondCountLabel->setString(str);
    }
}

void StartScene::sureConversionResource(CCMenuItem* item) {
    
    CCLayer* mainLayer = (CCLayer*)item->getParent()->getParent();
    float rate = ((GXfloatValue*)mainLayer->getUserObject())->getValue();
    float percentage = ((GXScrollBar*)mainLayer->getUserData())->percentage;
    if(rate>5) {
        if (rate > 6.6) {
            float changeCount = MyGameInfo::getInstance()->getIron()*percentage;
            if (MyGameInfo::getInstance()->getDiamond() < Mathlib::max(10,changeCount/20000)) {
                this->addChild(MyUtil::getInstance()->getNoResourceDialog(this,diamondTag));
                return;
            }
            MyGameInfo::getInstance()->changeResource(diamondTag,-1*Mathlib::max(10,changeCount/20000));
            MyGameInfo::getInstance()->changeResource(ironTag,-1*changeCount);
            MyGameInfo::getInstance()->changeResource(oilTag,changeCount);
            MyHttpConnection::getInstance()->sendConversionResource(ironTag,percentage,true);
        } else {
            float changeCount = MyGameInfo::getInstance()->getIron()*percentage;
            
            MyGameInfo::getInstance()->changeResource(ironTag,-1*changeCount);
            MyGameInfo::getInstance()->changeResource(oilTag,changeCount/2);
            MyHttpConnection::getInstance()->sendConversionResource(ironTag,percentage,false);
        }
    } else {
        if (rate > 0.6) {
            float changeCount = MyGameInfo::getInstance()->getOil()*percentage;
            if (MyGameInfo::getInstance()->getDiamond() < Mathlib::max(10,changeCount/20000)) {
                this->addChild(MyUtil::getInstance()->getNoResourceDialog(this,diamondTag));
                return;
            }
            MyGameInfo::getInstance()->changeResource(diamondTag,-1*Mathlib::max(10,changeCount/20000));
            MyGameInfo::getInstance()->changeResource(oilTag,-1*changeCount);
            MyGameInfo::getInstance()->changeResource(ironTag,changeCount);
            MyHttpConnection::getInstance()->sendConversionResource(oilTag,percentage,true);
        } else {
            float changeCount = MyGameInfo::getInstance()->getOil()*percentage;
            MyGameInfo::getInstance()->changeResource(oilTag,-1*changeCount);
            MyGameInfo::getInstance()->changeResource(ironTag,changeCount/2);
            MyHttpConnection::getInstance()->sendConversionResource(oilTag,percentage,false);
        }
    }
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sfx_updateBuilding.mp3");
    item->setEnabled(false);
    mainLayer->runAction(GXRemoveFromParentsAction::create());
}

void StartScene::dismissPost(CCMenuItem* item) {
    CCNode* layer = item->getParent()->getParent();
    //    item->removeFromParentAndCleanup(true);
    item->setVisible(false);
    
#if   (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    GXScrollView* scroll = GXScrollView::create(-507);
    scroll->setOriPosition(ccp(winSize.width/2-435,35));
    scroll->setContentSize(CCSizeMake(870, 550));
    
    
    CCArray* shopCards = CCArray::create();
    shopCards->addObject(MyShopCard::create(600,6,6,this,0));
    shopCards->addObject(MyShopCard::create(3150,32,30,this,1));
    shopCards->addObject(MyShopCard::create(7480,74.8,68,this,2));
    shopCards->addObject(MyShopCard::create(14720,147.2,128,this,3));
    shopCards->addObject(MyShopCard::create(39630,396.3,328,this,4));
    shopCards->addObject(MyShopCard::create(84240,842.4,648,this,5));
    
    //    shopCards->addObject(CCString::create("123"));
    //    shopCards->addObject(CCString::create("123"));
    //    buildingCards->addChild(CCString::create("123"));
    
    if (shopCards->count() >= 6) {
        scroll->setMapSize(CCSizeMake(870, 95*(shopCards->count()/2+1)));
        scroll->setPosition(ccp(scroll->getOriPosition().x,-scroll->getMapSize().height+scroll->getViewSize().height+scroll->getOriPosition().y));
    } else {
        scroll->setMapSize(CCSizeMake(870, 550));
    }
    
    CCObject* obj;
    int i=0;
    CCARRAY_FOREACH(shopCards,obj) {
        
        MyShopCard* shopCard = (MyShopCard*)obj;
        //        cardBack->setScaleX(420/cardBack->getContentSize().width);
        //        cardBack->setScaleY(190/cardBack->getContentSize().height);
        shopCard->setPosition(ccp(435,scroll->getMapSize().height-50-i*90));
        scroll->addChild(shopCard);
        i++;
    }
    layer->addChild(scroll);
#endif
}

void StartScene::toOneKeyArchieveGhost(CCMenuItem* item) {
    //    if (item == NULL) {
    //        item = (CCMenuItem*)this->getChildByTag(UILayerTag)->getChildByTag(huodongMenuTag)->getChildByTag(mubeiButtonTag);
    //    }
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sfx_collect.mp3");
    MyMap* map = (MyMap*)getChildByTag(MainMapTag);
    CCObject* obj;
    long resourceTotal = 0;
    int mubeiCount = 0;
    MyBuilding* huishouCenter = (MyBuilding*)map->getChildByTag(GarbageCenterTag);
    float rate = 0;
    if(huishouCenter != NULL) {
        float maxRate = MyUtil::getInstance()->updateLevelByCount(hszxBaseMaxRecycling,huishouCenter->getLevel(),hszxUpdateMaxRecyclingCount);
        rate = Mathlib::min(maxRate,(YouTian::getYouTianInfo()->count+SuperYouTian::getSuperYouTianInfo()->count*3) * 0.01);
    }
    CCARRAY_FOREACH(map->getItems(),obj) {
        MyBuilding* building = (MyBuilding*)obj;
        if (building->getTag() == ghostTag) {
            GarbageCollectionNormalState* state = dynamic_cast<GarbageCollectionNormalState*>(building->fsm->getCurrentState());
            if (state && building->isEnabled()) {
                resourceTotal += state->doCollect(rate);
                building->setEnabled(false);
                state->isDestroy = true;
                mubeiCount++;
                //                building->runAction(GXFadeOutAndRemoveWhenStop::create(0.15));
            }
        }
    }
    MyHttpConnection::getInstance()->sendCollectAllMubei();
    this->addChild(MyUtil::getInstance()->getGarbageCollectionTotal(resourceTotal,mubeiCount,rate));
    item->setEnabled(false);
    item->runAction(GXFadeOutAndRemoveWhenStop::create(0.5));
    //    CCNode* huodongMenu = item->getParent();
    CCNode* questMenu = item->getParent();
    
    CCARRAY_FOREACH(questMenu->getChildren(),obj) {
        CCNode* node = (CCNode*)obj;
        if (node->getPosition().y < item->getPosition().y) {
            node->runAction(CCSequence::create(CCDelayTime::create(0.25), CCMoveBy::create(0.5,ccp(0,100)),NULL));
        }
    }
    
    //    CCARRAY_FOREACH(huodongMenu->getChildren(),obj) {
    //        CCNode* node = (CCNode*)obj;
    //        if (node->getPosition().y > item->getPosition().y) {
    //            node->runAction(CCSequence::create(CCDelayTime::create(0.25), CCMoveBy::create(0.5,ccp(0,-130)),NULL));
    //        }
    //    }
}

void StartScene::subMubei() {
    CCLabelAtlas* item = (CCLabelAtlas*)this->getChildByTag(UILayerTag)->getChildByTag(questMenuTag)->getChildByTag(mubeiButtonTag)->getChildByTag(mubeiButtonCountTag);
    //    CCLabelAtlas* item = (CCLabelAtlas*)this->getChildByTag(UILayerTag)->getChildByTag(huodongMenuTag)->getChildByTag(mubeiButtonTag)->getChildByTag(mubeiButtonCountTag);
    int count = (int)item->getUserData();
    char str[5] = {0};
    sprintf(str,"/%d",count-1);
    item->setString(str);
    item->setUserData((void*)(count-1));
    
}

void StartScene::addDisplayQuest(CCMenu* menu,CCObject* obj,bool isAppear ) {
    MyBaseQuest* quest = (MyBaseQuest*) obj;
    
    CCSprite*  normalSprite = CCSprite::createWithSpriteFrameName("questButton.png");
    
    MyMenuItem* questItem = MyMenuItem::create(normalSprite,this,menu_selector(StartScene::toDisplayMissionInfo));
    //    questItem->runAction(CCRepeatForever::create(static_cast<CCSequence*>(CCSequence::create(CCScaleTo::create(1, 0.9), CCScaleTo::create(1,1),NULL) )));
    
    if (isAppear) {
        CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sfx_missionAppear.mp3");
        questItem->setTag(appearQuestTag);
        questItem->setScale(2);
        questItem->runAction(CCSequence::create(CCEaseElasticOut::create(CCScaleTo::create(0.8,1),1),CCCallFuncO::create(this,callfuncO_selector(StartScene::shakeEffect2),questItem),NULL));
        CCSprite* questAppear = CCSprite::createWithSpriteFrameName("questAppear.png");
        questAppear->setPosition(ccp(questItem->getContentSize().width/2,questItem->getContentSize().height/2));
        normalSprite->addChild(questAppear);
    } else {
        if (quest->getIconName() != NULL) {
            CCSprite* questIcon = CCSprite::createWithSpriteFrameName(quest->getIconName()->getCString());
            questIcon->setPosition(ccp(questItem->getContentSize().width/2,questItem->getContentSize().height/2));
            if (questIcon->getContentSize().width > 80 || questIcon->getContentSize().height > 80) {
                questIcon->setScale(Mathlib::min(80/questIcon->getContentSize().width,80/questIcon->getContentSize().height));
            }
            
            normalSprite->addChild(questIcon);
        } else {
            CCSprite* questIcon = CCSprite::createWithSpriteFrameName("questQuestion.png");
            questIcon->setPosition(ccp(questItem->getContentSize().width/2,questItem->getContentSize().height/2));
            normalSprite->addChild(questIcon);
        }
    }
    
    
    questItem->setUserData(quest);
    menu->addChild(questItem);
    
    questItem->setPosition(ccp(100,(int)(570-(menu->getChildrenCount()*100))));
}

void StartScene::addDisplayQuest(CCObject* obj,bool isAppear) {
    CCMenu* menu = (CCMenu*)this->getChildByTag(UILayerTag)->getChildByTag(questMenuTag);
    addDisplayQuest(menu,obj,isAppear);
}

void StartScene::toDisplayMissionInfo(CCMenuItem* item) {
    this->removeChildByTag(updateLayerTag,true);
    MyBaseQuest* quest = (MyBaseQuest*)item->getUserData();
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sfx_click.mp3");
    item->stopAllActions();
    item->setScale(1);
    if (item->getTag() == appearQuestTag) {
        item->setTag(-1);
        MyMenuItem* item1 = (MyMenuItem*)item;
        item1->getImage()->removeAllChildrenWithCleanup(true);
        if (quest->getIconName() != NULL) {
            CCSprite* questIcon = CCSprite::createWithSpriteFrameName(quest->getIconName()->getCString());
            questIcon->setPosition(ccp(item1->getContentSize().width/2,item1->getContentSize().height/2));
            if (questIcon->getContentSize().width > 80 || questIcon->getContentSize().height > 80) {
                questIcon->setScale(Mathlib::min(80/questIcon->getContentSize().width,80/questIcon->getContentSize().height));
            }
            item1->getImage()->addChild(questIcon);
        } else {
            CCSprite* questIcon = CCSprite::createWithSpriteFrameName("questQuestion.png");
            questIcon->setPosition(ccp(item1->getContentSize().width/2,item1->getContentSize().height/2));
            item1->getImage()->addChild(questIcon);
        }
        if(quest->getDialog() != NULL && quest->getCompleteStatus() !=  questFinishedTag) {
            DiaLayer* diaLayer = DiaLayer::create(quest->getDialog());
            diaLayer->setTag(quest->questId);
            this->addChild(diaLayer);
            quest->setDialog(NULL);
            return;
        }
    }
    displayMissionInfo(quest);
}

void StartScene::displayMissionInfo(MyBaseQuest* quest) {
    CCLayer* layer = MyUtil::getInstance()->getQuestBack(quest,this,menu_selector(StartScene::toGetQuestPrize));
    layer->setTag(updateLayerTag);
    layer->setPosition(ccp(winSize.width/2+40,layer->getContentSize().height/2*-1));
    layer->runAction(CCEaseElasticOut::create(CCMoveTo::create(0.35, ccp(winSize.width/2+40,winSize.height/2)), 1));
    
    this->addChild(layer);
}

void StartScene::toGetQuestPrize(CCMenuItem* item) {
    MyBaseQuest* quest = (MyBaseQuest*)item->getUserData();
    this->removeChildByTag(updateLayerTag,true);
    MyHttpConnection::getInstance()->sendCompleteQuest(quest->questId);
}

void StartScene::toArchieveQuestPrize(int missionId) {
    //    CCArray* questArray = QuestManager::getInstance()->questList;
    CCMenu* menu = (CCMenu*)this->getChildByTag(UILayerTag)->getChildByTag(questMenuTag);
    //    CCObject* obj;
    MyBaseQuest* quest;
    int flag = -1;
    //    int i=0;
    //    CCARRAY_FOREACH(questArray,obj) {
    //        MyBaseQuest* tempQuest = (MyBaseQuest*)obj;
    //    questArray->removeObjectAtIndex(flag);
    for (int i=0; i<menu->getChildrenCount(); i++) {
        MyMenuItem* node = ((MyMenuItem*)menu->getChildren()->objectAtIndex(i));
        MyBaseQuest* tempQuest = dynamic_cast<MyBaseQuest*>((CCObject*)node->getUserData());
        if (tempQuest != NULL && tempQuest->questId == missionId) {
            quest = tempQuest;
            flag = i;
            quest->getPrize();
            QuestManager::getInstance()->questList->removeObject(tempQuest);
            if (quest->hasNext == false) {
                CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sfx_levelup.mp3");
            }else {
                CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sfx_updateBuilding.mp3");
            }
            node->runAction(CCSequence::create(CCFadeOut::create(0.5), GXRemoveFromParentsAction::create(),NULL));
            ((CCNode*)node->getImage()->getChildren()->objectAtIndex(0))->runAction(CCSequence::create(CCFadeOut::create(0.5),NULL));
            node->setEnabled(false);
        }
        if (i>flag && flag >-1) {
            node->runAction(CCSequence::create(CCDelayTime::create(0.25), CCMoveBy::create(0.5,ccp(0,100)),NULL));
        }
    }
    
    
    
    //    CCMenu* menu = (CCMenu*)this->getChildByTag(UILayerTag)->getChildByTag(questMenuTag);
    //    MyMenuItem* item = ((MyMenuItem*)menu->getChildren()->objectAtIndex(flag));
    
    
    //    for (int i=0; i<menu->getChildrenCount(); i++) {
    //        CCNode* node = ((CCNode*)menu->getChildren()->objectAtIndex(i));
    //        if (flag > -1 ) {
    //            MyBaseQuest*
    //            node->getUserData
    //            if () {
    //
    //            }
    //
    //
    //            node->runAction(CCSequence::create(CCDelayTime::create(0.25), CCMoveBy::create(0.5,ccp(0,100)),NULL));
    //        }
    //    }
    
}

void StartScene::updateQuestUI(int missionId) {
    CCMenu* menu = (CCMenu*)this->getChildByTag(UILayerTag)->getChildByTag(questMenuTag);
    CCObject* obj;
    bool flag = false;
    CCARRAY_FOREACH(menu->getChildren(),obj) {
        MyMenuItem* item = (MyMenuItem*)obj;
        MyBaseQuest* quest = (MyBaseQuest*)item->getUserData();
        if (quest && quest->getCompleteStatus() == questFinishedTag && missionId == quest->questId) {
            item->stopAllActions();
            item->setScale(1);
            item->setTag(appearQuestTag);
            item->getImage()->removeAllChildrenWithCleanup(true);
            
            CCSprite* questIcon = CCSprite::createWithSpriteFrameName("questAppear.png");
            questIcon->setPosition(ccp(item->getContentSize().width/2,item->getContentSize().height/2));
            item->getImage()->addChild(questIcon);
            item->setScale(2);
            item->runAction(CCSequence::create(CCEaseElasticOut::create(CCScaleTo::create(0.8,1),1),CCCallFuncO::create(this,callfuncO_selector(StartScene::shakeEffect2),item),NULL));
            flag = true;
        }
    }
    if (flag) {
        CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sfx_missionAppear.mp3");
    }
}

void StartScene::addDisplayHuodong(CCMenu* menu,CCMenuItem* huodong) {
//    CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sfx_missionAppear.mp3");
    huodong->setScale(2);
    huodong->runAction(CCSequence::create(CCEaseElasticOut::create(CCScaleTo::create(0.8,1),1),CCCallFuncO::create(this,callfuncO_selector(StartScene::shakeEffect2),huodong),NULL));
    
    menu->addChild(huodong);
    huodong->setPosition(ccp(100,570-menu->getChildrenCount()*100));
}

//void StartScene::addDisplayHuodong(CCMenuItem* huodong) {
//    CCMenu* menu = (CCMenu*)this->getChildByTag(UILayerTag)->getChildByTag(questMenuTag);
//    addDisplayHuodong(menu,huodong);
//}

void StartScene::addAttackInfo(CCObject* bean) {
    AttackerInfoBean* infobean = (AttackerInfoBean*)bean;
    CCMenu* questMenu =(CCMenu*) this->getChildByTag(UILayerTag)->getChildByTag(questMenuTag);
    CCSprite*  normalSprite = CCSprite::createWithSpriteFrameName("huodongButton.png");
    
    MyMenuItem* cpuWarItem = MyMenuItem::create(normalSprite,this,menu_selector(StartScene::moveToAttackerLoc));
    CCSprite* defendIcon = CCSprite::createWithSpriteFrameName("defendButton.png");
    defendIcon->setPosition(ccp(normalSprite->getContentSize().width/2,normalSprite->getContentSize().height/2+10));
    defendIcon->setScale(Mathlib::min(75/defendIcon->getContentSize().width,75/defendIcon->getContentSize().height));
    normalSprite->addChild(defendIcon);
    this->addDisplayHuodong(questMenu,cpuWarItem);
    //    cpuWarItem->setPosition(ccp(100,570-questMenu->getChildrenCount()*100));
    cpuWarItem->setScale(0.9);
    //    AttackerInfoBean* infobean = (AttackerInfoBean*)bean;
    //    CCMenu* huodongMenu = (CCMenu*)this->getChildByTag(UILayerTag)->getChildByTag(huodongMenuTag);
    //    huodongMenu->removeChildByTag(cpuWarQuestTag,true);
    //    CCSprite* cpuWarSpriteGray = CCSprite::createWithSpriteFrameName("defendButton.png");
    //    cpuWarSpriteGray->setColor(ccGRAY);
    //    CCSprite* cpuWarSprite = CCSprite::createWithSpriteFrameName("defendButton.png");
    //    cpuWarSprite->runAction(CCFadeIn::create(1));
    //    CCMenuItemSprite* cpuWarItem = CCMenuItemSprite::create(cpuWarSprite,cpuWarSpriteGray,this,menu_selector(StartScene::moveToAttackerLoc));
    //    cpuWarItem->setPosition(ccp(0,huodongMenu->getChildrenCount()*130));
    
    //    CCSprite* bling1_1 = CCSprite::create("armyprizeLight.png");
    //    bling1_1->setPosition(ccp(cpuWarItem->getContentSize().width/2,cpuWarItem->getContentSize().height/2));
    //    bling1_1->setScale(0.7);
    //    bling1_1->runAction(CCRepeatForever::create(CCRotateBy::create(1000, 7200)));
    //    cpuWarItem->addChild(bling1_1,-1);
    //
    //    CCSprite* bling1_2 = CCSprite::create("armyprizeLight.png");
    //    bling1_2->setPosition(ccp(cpuWarItem->getContentSize().width/2,cpuWarItem->getContentSize().height/2));
    //    bling1_2->runAction(CCRepeatForever::create(CCRotateBy::create(1000, -7200)));
    //    bling1_2->setScale(0.5);
    //    cpuWarItem->addChild(bling1_2,-1);
    
    if (infobean->level >= infobean->maxLevel) {
        CCLabelTTF* lvLabel = CCLabelTTF::create("Lv:MAX","Arial",22);
        lvLabel->setScaleX(0.93);
        lvLabel->setPosition(ccp(cpuWarItem->getContentSize().width/2,-3));
        lvLabel->setAnchorPoint(ccp(0.5,0));
        cpuWarItem->addChild(lvLabel,1);
    } else {
        CCLabelTTF* lvLabel = CCLabelTTF::create("Lv:","Arial",25);
        lvLabel->setAnchorPoint(ccp(0.5,0));
        lvLabel->setPosition(ccp(cpuWarItem->getContentSize().width/2-15,-3));
        char str[20] = {0};
        if (infobean->level < 0) {
            cpuWarItem->addChild(lvLabel,1);
            CCLabelTTF* level = CCLabelTTF::create("??", "Arial", 23);
            level->setAnchorPoint(ccp(0.5,0));
            level->setPosition(ccp(cpuWarItem->getContentSize().width/2+20,-2));
            cpuWarItem->addChild(level);
        } else {
            sprintf(str,"%d",infobean->level);
            cpuWarItem->addChild(lvLabel,1);
            CCLabelAtlas* level = CCLabelAtlas::create(str, "number6.png", 24, 36, '/');
            level->setAnchorPoint(ccp(0.5,0));
            level->setScale(0.7);
            level->setPosition(ccp(cpuWarItem->getContentSize().width/2+12,0));
            cpuWarItem->addChild(level);
        }
    }
    cpuWarItem->setUserObject(bean);
    addAttackArmy(bean);
    
    
    
}

void StartScene::addAttackArmy(CCObject* bean) {
    AttackerInfoBean* infobean = (AttackerInfoBean*)bean;
    MyMap* map = (MyMap*)this->getChildByTag(MainMapTag);
    CCPoint tield = ccp(-1,-1);
    CCSize size = CCSizeMake(7,7);
    char str[50] = {0};
    if (infobean->attackerDirection == attackLD) {
        tield.x = 30;
        for (int i=1; i<25; i=i+3) {
            tield.y = 45+i;
            if (!map->collisionDetectionSpecial(tield,size)) {
                break;
            }
        }
    } else if(infobean->attackerDirection == attackRD) {
        tield.y = 30;
        for (int i=1; i<25; i=i+3) {
            tield.x = 45+i;
            if (!map->collisionDetectionSpecial(tield,size)) {
                break;
            }
        }
    } else if(infobean->attackerDirection == attackLU) {
        tield.y = 30;
        for (int i=1; i<25; i=i+3) {
            tield.x = 15-i;
            if (!map->collisionDetectionSpecial(tield,size)) {
                break;
            }
        }
        tield.x = tield.x-1;
    } else if(infobean->attackerDirection == attackRU) {
        tield.x = 30;
        for (int i=1; i<25; i=i+3) {
            tield.y = 15-i;
            if (!map->collisionDetectionSpecial(tield,size)) {
                break;
            }
        }
        tield.y = tield.y-1;
    }
    
    CCPoint base = map->transTiledToMap(tield);
    
    //    infobean->attackerCount = 1000;
    
    CCPoint wavePosiStart;
    CCPoint wavePosiEnd;
    int beilv = 0;
    CCSprite* army;
    float countValue = 0;
    if(infobean->attackerCount < 10 && infobean->attackerCount >0) {
        CCSprite* army = infobean->getCreatorInfoBean()->creator->getAttackSprite(infobean->attackerDirection);
        army->setPosition(base);
        map->addChild(army,999999-army->getPosition().y);
    } else if(infobean->attackerCount < 100 || infobean->attackerCount<0) {
        for (int i =0; i<4; i++) {
            army = infobean->getCreatorInfoBean()->creator->getAttackSprite(infobean->attackerDirection);
            
            beilv = Mathlib::max(army->getContentSize().width/60,army->getContentSize().height/60);
            army->setPosition(map->transTiledToMap(ccp(tield.x-0.5*beilv+(i%2)*beilv,tield.y-1+(i/2)*beilv)));
            map->addChild(army,999999-army->getPosition().y);
        }
        countValue = 0.5;
    } else {
        for (int i=0; i<9; i++) {
            army = infobean->getCreatorInfoBean()->creator->getAttackSprite(infobean->attackerDirection);;
            beilv = Mathlib::max(army->getContentSize().width/60,army->getContentSize().height/60);
            army->setPosition(map->transTiledToMap(ccp(tield.x-1*beilv+(i%3)*beilv,tield.y-1*beilv+(i/3)*beilv)));
            map->addChild(army,999999-army->getPosition().y);
        }
        countValue = 1;
        //        wave->setScale(160*beilv / wave->getContentSize().width);
    }
    bool flipXBool = false;
    bool flipYBool = false;
    if (countValue != 0) {
        CCPoint wavePosiDispear;
        if (infobean->attackerDirection == attackLD) {
            wavePosiStart = map->transTiledToMap(ccp(tield.x,tield.y-countValue*beilv));
            wavePosiEnd = map->transTiledToMap(ccp(tield.x,tield.y+countValue*beilv));
            wavePosiDispear = map->transTiledToMap(ccp(tield.x,tield.y+3*countValue*beilv));
        } else if(infobean->attackerDirection == attackRD) {
            wavePosiStart = map->transTiledToMap(ccp(tield.x-countValue*beilv,tield.y));
            wavePosiEnd = map->transTiledToMap(ccp(tield.x+countValue*beilv,tield.y));
            wavePosiDispear = map->transTiledToMap(ccp(tield.x+3*countValue*beilv,tield.y));
            flipXBool = true;
        } else if(infobean->attackerDirection == attackLU) {
            wavePosiStart = map->transTiledToMap(ccp(tield.x+countValue*beilv,tield.y));
            wavePosiEnd = map->transTiledToMap(ccp(tield.x-countValue*beilv,tield.y));
            wavePosiDispear = map->transTiledToMap(ccp(tield.x-3*countValue*beilv,tield.y));
            flipYBool = true;
        } else if(infobean->attackerDirection == attackRU) {
            wavePosiStart = map->transTiledToMap(ccp(tield.x,tield.y+countValue*beilv));
            wavePosiEnd = map->transTiledToMap(ccp(tield.x,tield.y-countValue*beilv));
            wavePosiDispear = map->transTiledToMap(ccp(tield.x,tield.y-3*countValue*beilv));
            flipXBool = true;
            flipYBool = true;
        }
        if (countValue == 0.5) {
            for (int i =0; i<2; i++) {
                CCSprite* wave = CCSprite::createWithSpriteFrameName("defendwave.png");
                wave->setFlipX(flipXBool);
                wave->setFlipY(flipYBool);
                wave->setScale(100*beilv / wave->getContentSize().width);
                wave->setPosition(wavePosiStart);
                wave->setOpacity(0);
                wave->runAction(CCSequence::create(CCDelayTime::create(i),CCCallFuncO::create(this,callfuncO_selector(StartScene::runAttackerWave),wave),NULL));
                CCAction* action = CCRepeatForever::create(static_cast<CCSequence*>(CCSequence::create(CCSpawn::create(CCFadeIn::create(0.5), CCMoveTo::create(1,wavePosiEnd),NULL),CCSpawn::create(CCMoveTo::create(1,wavePosiDispear),CCFadeOut::create(1),NULL), CCMoveTo::create(0,wavePosiStart),NULL)));
                wave->setUserObject(action);
                map->addChild(wave);
            }
        } else if(countValue == 1) {
            for (int i=0; i<3; i++) {
                CCSprite* wave = CCSprite::createWithSpriteFrameName("defendwave.png");
                wave->setFlipX(flipXBool);
                wave->setFlipY(flipYBool);
                wave->setScale(160*beilv / wave->getContentSize().width);
                wave->setPosition(wavePosiStart);
                wave->setOpacity(0);
                wave->runAction(CCSequence::create(CCDelayTime::create(i),CCCallFuncO::create(this,callfuncO_selector(StartScene::runAttackerWave),wave),NULL));
                CCAction* action = CCRepeatForever::create(static_cast<CCSequence*>(CCSequence::create(CCSpawn::create(CCFadeIn::create(0.5), CCMoveTo::create(1.5,wavePosiEnd),NULL),CCSpawn::create(CCMoveTo::create(1.5,wavePosiDispear),CCFadeOut::create(1),NULL), CCMoveTo::create(0,wavePosiStart),NULL)));
                wave->setUserObject(action);
                map->addChild(wave);
            }
        }
    }
    
    
    CCSprite* defendBPGray = CCSprite::createWithSpriteFrameName("defendBP.png");
    defendBPGray->setColor(ccGRAY);
    CCMenuItemSprite* defendBP  = NULL;
    if (infobean->maxLevel < 3) {
        defendBP = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("defendBP.png"),defendBPGray,this,menu_selector(StartScene::toDefendScene));
        defendBP->setUserData((void*)infobean->maxLevel);
    } else {
        defendBP = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("defendBP.png"),defendBPGray,this,menu_selector(StartScene::toGetDefendList));
    }
    
    defendBP->setPosition(ccp(base.x+60,base.y+90));
    defendBP->setTag(cpuWarMapTag);
    CCLabelTTF* name = CCLabelTTF::create(infobean->getAttackerNickname()->getCString(),"Arial",18);
    name->setPosition(ccp(defendBP->getContentSize().width/2-10,43));
    name->setColor(ccc3(230, 207, 185));
    if (infobean->level < 0) {
        sprintf(str,"??级");
    } else {
        sprintf(str,"%d级",infobean->level);
    }
    CCLabelTTF* levelLabel = CCLabelTTF::create(str,"Arial",18);
    levelLabel->setPosition(ccp(155,66));
    levelLabel->setColor(ccc3(230, 207, 185));
    
    CCLabelTTF* countLabel = CCLabelTTF::create(MyUtil::getInstance()->getCountStrByCount(infobean->attackerCount),"Arial",18);
    countLabel->setPosition(ccp(168,97));
    countLabel->setColor(ccc3(230, 207, 185));
    
    CCSprite* light = CCSprite::createWithSpriteFrameName("creatorLight.png");
    light->setPosition(ccp(90,98));
    light->setOpacity(153);
    light->setScale(0.45);
    
    CCSprite* attackerbp = CCSprite::createWithSpriteFrameName(infobean->getAttackerAvatarStr()->getCString());
    attackerbp->setScale(Mathlib::max(85/attackerbp->getContentSize().width,80/attackerbp->getContentSize().height));
    attackerbp->setPosition(ccp(90,98));
    
    
    defendBP->addChild(name);
    defendBP->addChild(levelLabel);
    defendBP->addChild(countLabel);
    defendBP->addChild(light);
    defendBP->addChild(attackerbp);
    map->addChild(defendBP,1000000);
    
    
}

void StartScene::runAttackerWave(CCSprite* sprite) {
    CCAction* action = (CCAction*)sprite->getUserObject();
    sprite->runAction(action);
    sprite->setUserObject(NULL);
}

void StartScene::moveToAttackerLoc() {
    MyMap* map = (MyMap*)(this->getChildByTag(MainMapTag));
    CCNode* target = map->getChildByTag(cpuWarMapTag);
    CCPoint loc = target->getPosition();
    float x = -loc.x+map->getViewSize().width/2+60;
    float y = -loc.y+map->getViewSize().height/2+90;
    
    map->runAction(CCSequence::create(CCEaseInOut::create(CCMoveTo::create(2,ccp(x,y)),2),NULL));
}

void StartScene::toDefendScene(CCMenuItem* item) {
    // 去掉MAP的注册
    this->addChild(MyUtil::getInstance()->getWaitLayer("正在搜索基地"));
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sfx_click.mp3");
    MyMap* map = dynamic_cast<MyMap*>(this->getChildByTag(MainMapTag));
    
    updateMyData();
    map->pauseSchedulerAndActions();
    this->cleanup();
    
    MyGameInfo::getInstance()->enemyIron = 0;
    MyGameInfo::getInstance()->enemyOil = 0;
    CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.2, TransitonScene::create(defendSceneTag,CCInteger::create((int)item->getUserData())),ccBLACK));
    CocosDenshion::SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
    
}

void StartScene::toGetDefendList() {
    this->addChild(MyUtil::getInstance()->getWaitLayer("正在加载信息列表"),10);
    MyHttpConnection::getInstance()->sendGetDefendList();
    this->removeChildByTag(recorderLayerTag,true);
}

void StartScene::displayDefendList(CCArray* beans) {
    CCLayer* recordBack = NULL;
    
    CCLayer* recordLayer = CCLayer::create();
    recordLayer->setTag(recorderLayerTag);
    recordBack = MyUtil::getInstance()->getTitleBack(600,450,true,"防守战");
    recordBack->setTag(recordBackSpriteTag);
    recordBack->setPosition(ccp(winSize.width/2,winSize.height/2));
    recordLayer->addChild(recordBack,0);
    recordLayer->setScale(0.75);
    recordLayer->runAction(CCScaleTo::create(0.25, 1));
    
    this->addChild(recordLayer);
    
    CCLayer* contentLayer = CCLayer::create();
    contentLayer->setTag(recordContentLayerTag);
    
    CCObject* obj;
    MatchInfoBean* infobean;
    GXScrollView* scollView = GXScrollView::create(-500);
    
    int i = 0;
    char str[400] = {0};
    
    scollView->setOriPosition(ccp(winSize.width/2-300,winSize.height/2-195));
    
    int scrollHeight  = beans->count()*70;
    int level = beans->count();
    MyPriorityMenu* toDefendButtonMenu = MyPriorityMenu::create(-508,NULL);
    toDefendButtonMenu->setPosition(ccp(0,0));
    CCARRAY_FOREACH_REVERSE(beans, obj) {
        infobean = ((MatchInfoBean*)obj);
        CCLabelTTF* attackNameLabel = NULL;
        CCSprite* attackRank = MyUtil::getInstance()->getRankSprite(infobean->enemyPower);
        attackRank->setPosition(ccp(382,(scrollHeight-20-70*i)*2));
        attackRank->setScale(0.7);
        attackRank->setAnchorPoint(ccp(0.5,0.5));
        if (infobean->enemyPower < 0) {
            sprintf(str,"??级");
        } else {
            sprintf(str,"%d级",level);
        }
        CCLabelTTF* stageLevel = CCLabelTTF::create(str,"Arial",30);
        stageLevel->setPosition(ccp(420,(scrollHeight-45-70*i)*2));
        
        CCSprite* line = CCSprite::createWithSpriteFrameName("uiDialogCommonLine.png");
        line->setPosition(ccp(300,(scrollHeight-8-70*i)*2));
        line->setScaleX(550/line->getContentSize().width);
        line->setScaleY(0.6);
        
        CCSprite* dividLine = CCSprite::createWithSpriteFrameName("dividingline.png");
        dividLine->setPosition(ccp(300,(scrollHeight-50-70*i)*2));
        dividLine->setOpacity(200);
        dividLine->setScaleX(0.8);
        dividLine->setScaleY(0.6);
        
        CCSprite* metalButton = CCSprite::createWithSpriteFrameName("metalButton.png");
        CCSprite* startLabel1 = CCSprite::createWithSpriteFrameName("startDefendLabel.png");
        startLabel1->setPosition(ccp(metalButton->getContentSize().width/2,metalButton->getContentSize().height/2));
        metalButton->addChild(startLabel1);
        
        CCSprite* metalButtonP = CCSprite::createWithSpriteFrameName("metalButtonP.png");
        CCSprite* startLabel2 = CCSprite::createWithSpriteFrameName("startDefendLabel.png");
        startLabel2->setPosition(ccp(metalButtonP->getContentSize().width/2,metalButtonP->getContentSize().height/2));
        metalButtonP->addChild(startLabel2);
        
        CCMenuItemSprite* toDefendButton = CCMenuItemSprite::create(metalButton,metalButtonP,this,menu_selector(StartScene::toDefendScene));
        toDefendButton->setPosition(ccp(520,(scrollHeight-45-70*i)*2));
        toDefendButton->setScale(1.1);
        toDefendButton->setUserData((void*)level);
        toDefendButtonMenu->addChild(toDefendButton);
        
        
        attackNameLabel = CCLabelTTF::create(infobean->getAttackNickName()->getCString(),"Arial",26);
        //                CCLog("VIP经验值：%d",infobean->vipExperience);
        attackNameLabel->setPosition(ccp(405,(scrollHeight-18-70*i)*2));
        attackNameLabel->setAnchorPoint(ccp(0,0.5));
        attackNameLabel->setColor(ccc3(255,255,122));
        CCObject* obj2;
        int j =0;
        
        CCARRAY_FOREACH(infobean->frameNameArray, obj2) {
            sprintf(str, "%sbp.png",((CCString*)obj2)->getCString());
            CCSprite* bp = CCSprite::createWithSpriteFrameName(str);
            if (infobean->rarityArray->count() == 0) {
                break;
            }
            if (bp == NULL) {
                char str1[30] = {0};
                char str2[30] = {0};
                sprintf(str1, "%sbp.plist",((CCString*)obj2)->getCString());
                sprintf(str2, "%sbp.pvr.ccz",((CCString*)obj2)->getCString());
                GXUtil::loadResourceUtilSucc(str1,str2);
                GarbageResourceCollection::getInstance()->addGarbage(str1,CCString::create(str2));
                bp = CCSprite::createWithSpriteFrameName(str);
            }
            sprintf(str, "deployBack%d.png",((CCInteger*)infobean->rarityArray->objectAtIndex(j))->getValue());
            CCSprite* sprite = CCSprite::createWithSpriteFrameName(str);
            bp->setPosition(ccp(53,49));
            bp->setScale(Mathlib::min(115/bp->getContentSize().width, 90/bp->getContentSize().height));
            sprite->addChild(bp);
            sprite->setScale(0.75);
            
            sprite->setPosition(ccp(70+j*80,(scrollHeight-30-70*i)*2));
            if (((CCInteger*)infobean->unitCountArray->objectAtIndex(j))->getValue() < 0) {
                CCLabelTTF* unitCount = CCLabelTTF::create("???", "Arial", 25);
                unitCount->setAnchorPoint(ccp(0.5,1));
                unitCount->setPosition(ccp(sprite->getContentSize().width/2,0));
                sprite->addChild(unitCount);
            } else {
                sprintf(str, "/%d",((CCInteger*)infobean->unitCountArray->objectAtIndex(j))->getValue());
                CCLabelAtlas* unitCount = CCLabelAtlas::create(str, "number6.png", 24, 36, '/');
                unitCount->setAnchorPoint(ccp(0.5,1));
                unitCount->setScale(0.7);
                unitCount->setPosition(ccp(sprite->getContentSize().width/2,0));
                sprite->addChild(unitCount);
            }
            scollView->addChild(sprite,3);
            if (((CCInteger*)infobean->levelArray->objectAtIndex(j))->getValue() <0) {
                sprintf(str, "Lv:??");
            } else {
                sprintf(str, "Lv:%d",((CCInteger*)infobean->levelArray->objectAtIndex(j))->getValue());
            }
            CCLabelTTF* levelLabel = CCLabelTTF::create(str, "Arial", 25);
            levelLabel->setAnchorPoint(ccp(0,0));
            levelLabel->setPosition(ccp(10,5));
            sprite->addChild(levelLabel);
            
            j++;
        }
        
        
        
        scollView->addChild(dividLine,2);
        scollView->addChild(line,2);
        scollView->addChild(stageLevel,2);
        scollView->addChild(attackNameLabel,2);
        scollView->addChild(attackRank,2);
        
        i++;
        level--;
    }
    
    scollView->setContentSize(CCSizeMake(600,400));
    scollView->setMapSize(CCSizeMake(200,scrollHeight*2));
    
    scollView->setPosition(ccp(winSize.width/2-300,-scollView->getMapSize().height+scollView->getViewSize().height+scollView->getOriPosition().y));
    
    scollView->addChild(toDefendButtonMenu,5);
    contentLayer->addChild(scollView);
    recordLayer->addChild(contentLayer);
    
    CCMenuItemSprite* cancelItem = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("uiDialogCancelButton.png"), CCSprite::createWithSpriteFrameName("uiDialogCancelButtonP.png"),this,menu_selector(StartScene::toCancelRecorder));
    cancelItem->setAnchorPoint(ccp(1,1));
    cancelItem->setPosition(ccp(winSize.width/2+300,winSize.height/2+225));
    cancelItem->setScale(0.9);
    MyPriorityMenu* menu  = MyPriorityMenu::create(-508,cancelItem,NULL);
    menu->setPosition(ccp(0,0));
    contentLayer->addChild(menu);
    
}

void StartScene::shakeEffect(CCNode* node) {
    node->runAction(CCRepeatForever::create(static_cast<CCSequence*>(CCSequence::create(CCScaleTo::create(0.2, 0.9), CCScaleTo::create(0.2,1),NULL))));
}

void StartScene::shakeEffect2(CCNode* node) {
    node->runAction(CCRepeatForever::create(static_cast<CCSequence*>(CCSequence::create(CCScaleTo::create(0.25, 0.98), CCScaleTo::create(0.25,1),NULL))));
}

void StartScene::getServerOrderId() {
    MyHttpConnection::getInstance()->sendGetOrderId();
}

void StartScene::toRefreshStartScene() {
    //    CocosDenshion::SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sfx_click.mp3");
    MyMap* map = dynamic_cast<MyMap*>(this->getChildByTag(MainMapTag));
    map->pauseSchedulerAndActions();
    this->cleanup();
    MyGameInfo::getInstance()->enemyIron = 0;
    MyGameInfo::getInstance()->enemyOil = 0;
    CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.2, TransitonScene::create(startSceneTag), ccBLACK));
    CocosDenshion::SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
    
}

void StartScene::toChangeName() {
    
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sfx_click.mp3");
    //
    CCMenuItemSprite* cancelItem =CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("uiDialogCancelButton.png"), CCSprite::createWithSpriteFrameName("uiDialogCancelButtonP.png"),this,menu_selector(StartScene::cancelTipDialog));
    
    
    GXShieldTouchMenuItem* shild = GXShieldTouchMenuItem::create();
    shild->setContentSize(winSize);
    shild->setPosition(ccp(-winSize.width/2,-winSize.height/2));
    shild->setAnchorPoint(ccp(0,0));
    
    MyPriorityMenu* menu  = MyPriorityMenu::create(-508,cancelItem,shild,NULL);
    
    
    menu->setPosition(ccp(winSize.width/2, winSize.height/2 -48));
    CCLayer* layer = CCLayer::create();
    layer->setTouchEnabled(true);
    char str[70] = {0};
    sprintf(str,"旧昵称:　%s",MyGameInfo::getInstance()->getNickName());
    CCLabelTTF* oriusername = CCLabelTTF::create(str,"Arial",35,CCSizeZero, kCCTextAlignmentLeft, kCCVerticalTextAlignmentTop);
    oriusername->setAnchorPoint(ccp(0,0.5));
    oriusername->setPosition(ccp(winSize.width/2-200,410));
    oriusername->setColor(ccc3(255,222,0));
    
    
    CCLabelTTF* username = CCLabelTTF::create("新昵称:","Arial",35,CCSizeZero, kCCTextAlignmentLeft, kCCVerticalTextAlignmentTop);
    username->setAnchorPoint(ccp(0,0.5));
    username->setPosition(ccp(winSize.width/2-200,350));
    username->setColor(ccc3(255,222,0));
    
    
    
    CCSprite* sprite2 = CCSprite::create("serverMetalEditText.png");
    sprite2->setScale(2);
    sprite2->setContentSize(CCSizeMake(sprite2->getContentSize().width*2,sprite2->getContentSize().height*2));
    MyMenuItem* light2 = MyMenuItem::create(sprite2,this,menu_selector(StartScene::displayUnionIME));
    light2->setPosition(ccp(60,75));
    light2->setScale(0.6);
    
    
    CCTextFieldTTF*  loginPasswordTextField = CCTextFieldTTF::textFieldWithPlaceHolder("点击此处输入",CCSizeMake(light2->getContentSize().width,light2->getContentSize().height), kCCTextAlignmentLeft,"Arial",36);
    //    loginUsernameTextField->setColor(ccc3(254,185,0));
    loginPasswordTextField->setPosition(ccp(winSize.width/2+146,348));
    loginPasswordTextField->setAnchorPoint(ccp(0.5,0.5));
    loginPasswordTextField->setColor(ccc3(255,222,0));
    loginPasswordTextField->setDelegate(this);
    CC_SAFE_RETAIN(loginPasswordTextField);
    
    light2->setUserObject(loginPasswordTextField);
    light2->setUserData((void*)36);
    
    //    label1->setColor(ccc3(230, 207, 185));
    //    label1->setPosition(ccp(winSize.width/2+15,winSize.height/2+100));
    //
    //    CCLabelTTF* label2 = CCLabelTTF::create(str, "Arial", 35,CCSizeZero, kCCTextAlignmentLeft, kCCVerticalTextAlignmentTop);
    //
    //    label2->setColor(ccc3(249, 155, 6));
    //    label2->setPosition(ccp(winSize.width/2+120,winSize.height/2+60));
    //
    //    CCLabelTTF* costFontLabel = CCLabelTTF::create("花费：", "宋体", 30);
    //
    //
    //    costFontLabel->setColor(ccc3(230, 207, 185));
    //    costFontLabel->setPosition(ccp(winSize.width/2+15,winSize.height/2+10));
    //
    //    CCSprite* costIcon = MyUtil::getInstance()->getResourceIcon(diamondTag);
    //    costIcon->setPosition(ccp(winSize.width/2+50,winSize.height/2-35));
    //    costIcon->setScale(0.9);
    //
    //
    //    sprintf(str,"%d",((ShopResourceBean*)shopCard->bean)->getCost());
    //    CCLabelAtlas* costLabel = CCLabelAtlas::create(str, "number6.png", 24, 36, '/');
    //    costLabel->setPosition(ccp(winSize.width/2+100,winSize.height/2-60));
    //    costLabel->setScaleY(1.1);
    //    costLabel->setScaleX(1);
    //    costLabel->setColor(ccc3(231,219,138));
    
    CCSprite* dialogBack = MyUtil::getInstance()->getNormalBox(510,320);
    dialogBack->setPosition(ccp(winSize.width/2,winSize.height/2));
    cancelItem->setPosition(ccp(dialogBack->getContentSize().width/2 - 24,dialogBack->getContentSize().height/2 + 24));
    
    CCSprite* heidi = CCSprite::create("whiteImage.jpg");
    heidi->setScaleX(winSize.width/heidi->getContentSize().width);
    heidi->setScaleY(winSize.height/heidi->getContentSize().height);
    heidi->setPosition(ccp(winSize.width/2,winSize.height/2));
    heidi->setColor(ccc3(0,0,0));
    heidi->setOpacity(180);
    
    CCLabelTTF* costLabel = CCLabelTTF::create("花费　　:3000钻石","Arial",28,CCSizeZero, kCCTextAlignmentLeft, kCCVerticalTextAlignmentTop);
    costLabel->setAnchorPoint(ccp(0,0.5));
    costLabel->setPosition(ccp(winSize.width/2-120,285));
    costLabel->setColor(ccc3(255,222,0));
    
    CCSprite* diamondIcon = MyUtil::getInstance()->getResourceIcon(diamondTag);
    diamondIcon->setPosition(ccp(winSize.width/2-30,295));
    
    layer->addChild(heidi);
    layer->addChild(dialogBack);
    layer->addChild(menu);
    layer->addChild(oriusername);
    layer->addChild(username);
    layer->addChild(loginPasswordTextField);
    menu->addChild(light2,-1);
    layer->addChild(diamondIcon);
    layer->addChild(costLabel);
    layer->setTag(armyInfoUnlockLayerTag);
    
    
    //诡异的购买按钮
    
    
    CCMenuItemSprite* unlockButton = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("dialogsure.png"),CCSprite::createWithSpriteFrameName("dialogsurep.png"),this,menu_selector(StartScene::sureChangeName));
    unlockButton->setUserData(loginPasswordTextField);
    
    unlockButton->setPosition(ccp(0,-50));
    menu->addChild(unlockButton,-2);
    this->getChildByTag(creatorLayerTag)->addChild(layer,100);
}

void StartScene::sureChangeName(CCSprite* item) {
    CCTextFieldTTF*  nameTextField = (CCTextFieldTTF*)item->getUserData();
    const char* str = nameTextField->getString();
    if (!(strlen(str) <= 18 && strlen(str)>=1)) {
        this->addChild(MyUtil::getInstance()->getCommonTipDialog(CCString::create("昵称请在6个中文字符以内！"),this,menu_selector(StartScene::cancelTipDialog),0));
        return;
    }
    if (MyGameInfo::getInstance()->getResource(diamondTag) < 3000) {
        this->addChild(MyUtil::getInstance()->getNoResourceDialog(this,diamondTag));
        return;
    }
    
    //    MyGameInfo::getInstance()->changeResource(diamondTag,-3000);
    this->addChild(MyUtil::getInstance()->getWaitLayer("正在修改昵称"),1000);
    MyHttpConnection::getInstance()->sendChangeNickName(str);
}

void StartScene::addorUpdateBuilding(CCObject* asd) {
    BuildingBean* bean = (BuildingBean*)asd;
    MyMap* map = (MyMap*)this->getChildByTag(MainMapTag);
    CCObject* obj;
    CCARRAY_FOREACH(map->getItems(),obj) {
        MyBuilding* arrayBuild = (MyBuilding*)(obj);
        if(bean->tag == arrayBuild->getTag()) {
            GarbageCollectionNormalState* state = dynamic_cast<GarbageCollectionNormalState*>(arrayBuild->fsm->getCurrentState());
            if(state != NULL) {
                state->resourceCount = bean->arg0;
            }
            return;
        }
    }
    MyBuilding* build = MyGameFactory::createBuildingByBean(bean,this);
    map->addChild(build);
    //    CCMenu* huodongMenu = (CCMenu*)getChildByTag(UILayerTag)->getChildByTag(huodongMenuTag);
    //    huodongMenu->addChild(displayMubeiInfo(1,huodongMenu->getChildrenCount()));
    CCMenu* questMenu = (CCMenu*)this->getChildByTag(UILayerTag)->getChildByTag(questMenuTag);
    //    questMenu->
    CCMenuItem* mubeiButton = displayMubeiInfo(1);
    this->addDisplayHuodong(questMenu,mubeiButton);
    //    mubeiButton->setPosition(ccp(100,570-questMenu->getChildrenCount()*100));
    
}


//void StartScene::retain() {
//    CCObject::retain();
//    CCLog("日扯：%d",this->m_uReference);
//    if (this->m_uReference == 7) {
//        CCLog("日扯：中的战斗日扯");
//    }
//}
//
//void StartScene::release() {
//    CCObject::release();
//    CCLog("没释放么？:%d",this->m_uReference);
//}

//void StartScene::sendTestMsg() {
//   
//    //    CCLog("maxId:%d",MyGameInfo::getInstance()->maxId);
//    if (MyGameInfo::getInstance()->getIron()<50) {
//        return;
//    }
//    if(x < 60 ) {
//        x++;
//    } else if(x>=60 && y<60) {
//        y++;
//        x = 0;
//    } else {
//        CCLog("建设完了");
//    }
//    MyMap* map = (MyMap*)this->getChildByTag(MainMapTag);
//    
//    if (!map->collisionDetectionSpecial(ccp(x,y),CCSizeMake(1,1))) {
//        MyGameInfo::getInstance()->maxId++;
//        MyGameInfo::getInstance()->changeResource(ironTag,-40);
//        MyHttpConnection::getInstance()->sendConstructBuilding(MyGameInfo::getInstance()->maxId,53,x,y);
//        
//    }
//    
//    
//}