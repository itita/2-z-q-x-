//
//  MyBattleMap.cpp
//  ww2
//
//  Created by DingYu Fu on 12-9-5.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "MyBattleMap.h"
#include "cocos2d.h"
#include "Mathlib.h"
#include "BattleScene.h"
#include "DefineSet.h"
#include "MyBattleBuilding.h"
#include "BuildingHeader.h"
#include "GXFadeOut.h"
#include "MyBattleState.h"
#include "GarbageCollectionState.h"
#include "SimpleAudioEngine.h"

#define winSize CCDirector::sharedDirector()->getWinSize()
#define blink 10


using namespace cocos2d;

MyBattleMap* MyBattleMap::create(const char *tmxFile) {
    MyBattleMap *pRet = new MyBattleMap();
    if (pRet->initWithTMXFile(tmxFile))
    {
        pRet->autorelease();
        pRet->setViewSize(winSize);
        pRet->initCostMap();
        pRet->items = CCArray::create();
        pRet->items->retain();
        pRet->units = CCArray::create();
        pRet->units->retain();
        pRet->setContentMapSize(pRet->getContentSize());
        pRet->tiledLayer = pRet->layerNamed("tiled");
        pRet->schedule(schedule_selector(MyBattleMap::clearSfxCount),0.5);
        //        CCSprite* tip = tipTiled
        return pRet;
    }
    CC_SAFE_DELETE(pRet);
    return NULL;
}

MyBattleMap::~MyBattleMap() {
    
    CC_SAFE_RELEASE_NULL(items);
    //    items->release();
    CC_SAFE_RELEASE_NULL(currentDeployButton);
    
//    for (int i=0; i<units->count(); i++) {
//        MyUnit* unit = units->
//    }
    
    CC_SAFE_RELEASE_NULL(units);
    
    //    CCLog("MyBattleMap released");
    //    currentCreator->release();
    for(int i = 0; i < this->getMapSize().width; i++) {
        delete []costMap[i];
    }
    delete []costMap;
    
    for(int i = 0; i < this->getMapSize().width+2; i++) {
        delete []mybuildingMap[i];
    }
    delete []mybuildingMap;
}




void MyBattleMap::addChild(cocos2d::CCNode *child) {
    MyBattleBuilding* build = dynamic_cast<MyBattleBuilding*>(child);
    if(build != NULL) {
        build->setMap(this);
        if(build->positionByTiled.x<9999999) {
            build->setPositionByTiled(build->positionByTiled);
        }
        CCPoint bpos = build->getPosition();
        if (build->getTag() != ghostTag && !checkRectTiledBound(build->getPositionByTiled(), build->contentSizeByTiled)) {
            //禁止加入出界建筑
            CCLog("child out of bound");
            //            checkRectTiledBound(build->getPositionByTiled(), build->contentSizeByTiled);
            CCAssert(1 == 2, "child out of bound");
            return;
        }
        
        
        GXScrollTMXTileMap::addChild(child,999999-build->getPositionY());
        
        //先设置瓦片位置才有位置~顺序不能错
        CCPoint posi = this->transMapToTiled(build->getPosition());
        if (build->isAlive()) {
            items->addObject(build);
            float width = build->costRange.width;
            float height = build->costRange.height;
            
            
            for (int i=(int)(posi.x-width/2+0.5); i<posi.x+width/2+0.5; ++i) {
                for (int j=(int)(posi.y-height/2+0.5); j<posi.y+height/2+0.5; ++j) {
                    if(checkTiledBound(i, j)) {
                        if (costMap[i][j] < 5) {
                            tiledLayer->tileAt(ccp(i,j))->setColor(ccc3(255,0,0));
                        }
                        costMap[i][j] += 5;
                        
                    }
                }
            }
        }
        
        if (build->getTag() == ghostTag) {
            oriGhost = build;
//           CCPoint posi = this->transMapToTiled(build->getPosition());
//            for (int i=(int)(posi.x-build->contentSizeByTiled.width/2+0.5); i<posi.x+build->contentSizeByTiled.width/2+0.5; ++i) {
//                for (int j=(int)(posi.y-build->contentSizeByTiled.height/2+0.5); j<posi.y+build->contentSizeByTiled.height/2+0.5; ++j) {
//                    if (i>=0 && i<62 && j>=0 && j<62) {
//                        mybuildingMap[i+1][j+1] = build;
//                    }
//                }
//            }
        }
        
        for (int i=(int)(posi.x-build->contentSizeByTiled.width/2+0.5); i<posi.x+build->contentSizeByTiled.width/2+0.5; ++i) {
            for (int j=(int)(posi.y-build->contentSizeByTiled.height/2+0.5); j<posi.y+build->contentSizeByTiled.height/2+0.5; ++j) {
                if (i>=0 && i<62 && j>=0 && j<62) {
                    mybuildingMap[i+1][j+1] = build;
                }
            }
        }
        
        if(dynamic_cast<MyBattleBuilding*>(build)) {
            ((MyBattleBuilding*)build)->fsm->getCurrentState()->doStart();
        }
    } else {
        GXScrollTMXTileMap::addChild(child);
    }
}

//void MyBattleMap::addChild(cocos2d::CCNode *child, int zorder){
//    GXScrollTMXTileMap::addChild(child,zorder);
//    MyBattleBuilding* build = dynamic_cast<MyBattleBuilding*>(child);
//    if(build != NULL) {
//        build->setMap(this);
//        if(build->positionByTiled.x<9999999) {
//            build->setPositionByTiled(build->positionByTiled);
//        }
//        CCPoint bpos = build->getPosition();
//        if (!checkRectTiledBound(build->getPositionByTiled(), build->contentSizeByTiled)) {
//            //禁止加入出界建筑
//            CCLog("child out of bound");
//            CCAssert(1 != 2, "child out of bound");
////            return;
//        }
//
//        items->addObject(build);
//        float width = build->costRange.width;
//        float height = build->costRange.height;
//
//        //先设置瓦片位置才有位置~顺序不能错
//
//
//
//        CCPoint posi = this->transMapToTiled(build->getPosition());
//
//
//        //        int up = (int)posi-width/2;
//        //        int down = ();
//
//
//        for (int i=(int)(posi.x-width/2+0.5); i<posi.x+width/2+0.5; ++i) {
//            for (int j=(int)(posi.y-height/2+0.5); j<posi.y+height/2+0.5; ++j) {
//                if(checkTiledBound(i, j)) {
//                    costMap[i][j] += 5;
//                }
//            }
//        }
//
//        for (int i=(int)(posi.x-build->contentSizeByTiled.width/2+0.5); i<posi.x+build->contentSizeByTiled.width/2+0.5; ++i) {
//            for (int j=(int)(posi.y-build->contentSizeByTiled.height/2+0.5); j<posi.y+build->contentSizeByTiled.height/2+0.5; ++j) {
//                if (i>=0 && i<62 && j>=0 && j<62) {
//                    mybuildingMap[i+1][j+1] = build;
//                }
//            }
//        }
//        if(dynamic_cast<MyBattleBuilding*>(build)) {
//            ((MyBattleBuilding*)build)->fsm->getCurrentState()->doStart();
//        }
//    }
//}

void MyBattleMap::addGhost(const CCPoint& ghostPos,const CCPoint& nowPos,int resourceCount) {
    if (nowPos.x >= -1 && nowPos.x<61 && nowPos.y >= -1 && nowPos.y<61 ) {
        //如果死亡点在地图内
        MyBattleBuilding* nowb = (MyBattleBuilding*) mybuildingMap[(int)nowPos.x+1][(int)nowPos.y+1];
        //检查地图是否有建筑
        if (nowb != NULL) {
            //如果有建筑
            if (nowb->getTag() == ghostTag) {
                //建筑是墓碑，累加
                ((GarbageCollectionState*)nowb->fsm->getCurrentState())->addResource(resourceCount);
            } else{
                //不是墓碑，检测派遣点
                if (ghostPos.x >= -1 && ghostPos.x<61 && ghostPos.y >= -1 && ghostPos.y<61 ) {
                    //派遣点在地图内
                    MyBattleBuilding* ori = (MyBattleBuilding*) mybuildingMap[(int)ghostPos.x+1][(int)ghostPos.y+1];
                    //检测派遣点建筑
                    if (ori != NULL) {
                        //建筑不为空
                        if (ori->getTag() == ghostTag) {
                            //如果是墓碑 累加
                            ((GarbageCollectionState*)ori->fsm->getCurrentState())->addResource(resourceCount);
                        } else if (oriGhost != NULL) {
                            //如果不是墓碑 累加在缓存墓碑
                            MyBattleBuilding* oriGhostb = (MyBattleBuilding*)oriGhost;
                            ((GarbageCollectionState*)oriGhostb->fsm->getCurrentState())->addResource(resourceCount);
                        } else {
                            //如果缓存墓碑也他妈没有，检测一个
                            MyBattleBuilding*  oriGhostb = Ghost::createBattle(resourceCount);
                            oriGhost = oriGhostb;
                            oriGhostb->setMap(this);
                            locatOriGhost(ghostPos);
                            GXScrollTMXTileMap::addChild(oriGhostb,999999-oriGhostb->getPositionY());
                            //
                        }
                        //返回 在派遣点得到的墓碑
                        return;
                    }
                    //派遣点无建筑 新建建筑
                    MyBattleBuilding* build = Ghost::createBattle(resourceCount);
                    oriGhost = build;
                    build->setMap(this);
                    build->setPositionByTiled(ghostPos);
                    GXScrollTMXTileMap::addChild(build,999999-build->getPositionY());
                    //
                    mybuildingMap[(int)ghostPos.x+1][(int)ghostPos.y+1] = build;
                    return;
                } else {
                    //派遣点在地图外
                    if (oriGhost != NULL) {
                        //检测缓冲并累加
                        MyBattleBuilding* oriGhostb = (MyBattleBuilding*)oriGhost;
                        ((GarbageCollectionState*)oriGhostb->fsm->getCurrentState())->addResource(resourceCount);
                    } else {
                        //没有缓冲，寻路创建
                        MyBattleBuilding*  oriGhostb = Ghost::createBattle(resourceCount);
                        oriGhost = oriGhostb;
                        oriGhostb->setMap(this);
                        locatOriGhost(ghostPos);
                        GXScrollTMXTileMap::addChild(oriGhostb,999999-oriGhostb->getPositionY());
                    }
                }
            }
            //派遣点检测结束 退出
            return;
        }
        //死亡点没有建筑，创建墓碑
        MyBattleBuilding* build = Ghost::createBattle(resourceCount);
        oriGhost = build;
        build->setMap(this);
        build->setPositionByTiled(nowPos);
        
        GXScrollTMXTileMap::addChild(build,999999-build->getPositionY());
        //
        mybuildingMap[(int)nowPos.x+1][(int)nowPos.y+1] = build;
    } else {
        //死亡点在地图外
        if (oriGhost != NULL) {
            //检测缓冲兵累加
            MyBattleBuilding* oriGhostb = (MyBattleBuilding*)oriGhost;
            ((GarbageCollectionState*)oriGhostb->fsm->getCurrentState())->addResource(resourceCount);
        } else {
            //无缓冲则创建
            MyBattleBuilding*  oriGhostb = Ghost::createBattle(resourceCount);
            oriGhost = oriGhostb;
            oriGhostb->setMap(this);
            locatOriGhost(nowPos);
            GXScrollTMXTileMap::addChild(oriGhostb,999999-oriGhostb->getPositionY());
        }
    }
}

void MyBattleMap::locatOriGhost(const CCPoint& ghostPos) {
    MyBattleBuilding* oriGhostb = (MyBattleBuilding*)oriGhost;
    for (int i=1; i<31; i++) {
        if (ghostPos.x+i >= -1 && ghostPos.x+i <61 && ghostPos.y >= -1 && ghostPos.y <61) {
            if (mybuildingMap[(int)ghostPos.x+i+1][(int)ghostPos.y+1] == NULL) {
                oriGhostb->setPositionByTiled(ccp(ghostPos.x+i,ghostPos.y));
                mybuildingMap[(int)ghostPos.x+i+1][(int)ghostPos.y+1] = oriGhostb;
                return;
            }
        }
        if (ghostPos.x-i >= -1 && ghostPos.x-i <61 && ghostPos.y >= -1 && ghostPos.y <61) {
            if (mybuildingMap[(int)ghostPos.x-i+1][(int)ghostPos.y+1] == NULL) {
                oriGhostb->setPositionByTiled(ccp(ghostPos.x-i,ghostPos.y));
                mybuildingMap[(int)ghostPos.x-i+1][(int)ghostPos.y+1] = oriGhostb;
                return;
            }
        }
        if (ghostPos.x >= -1 && ghostPos.x <61 && ghostPos.y+i >= -1 && ghostPos.y+i <61) {
            if (mybuildingMap[(int)ghostPos.x+1][(int)ghostPos.y+i+1] == NULL) {
                oriGhostb->setPositionByTiled(ccp(ghostPos.x,ghostPos.y+i));
                mybuildingMap[(int)ghostPos.x+1][(int)ghostPos.y+i+1] = oriGhostb;
                return;
            }
        }
        if (ghostPos.x >= -1 && ghostPos.x <61 && ghostPos.y-i >= -1 && ghostPos.y-i <61) {
            if (mybuildingMap[(int)ghostPos.x+1][(int)ghostPos.y-i+1] == NULL) {
                oriGhostb->setPositionByTiled(ccp(ghostPos.x,ghostPos.y-i));
                mybuildingMap[(int)ghostPos.x+1][(int)ghostPos.y-i+1] = oriGhostb;
                return;
            }
        }
    }
}

void MyBattleMap::displayTip() {
    //    CCTMXLayer* layer = this->layerNamed("tiled");
    //    CCSize size = this->getMapSize();
    ////
    //    for (int i=0; i<size.width; ++i) {
    //        for (int j=0; j<size.height; ++j) {
    //            if (costMap[i][j] >= 5) {
    //                CCAction* action = CCTintTo::create(0, 255, 0, 0);
    //                action->setTag(blink);
    //                layer->tileAt(ccp(i,j))->runAction(action);
    //            }
    //        }
    //    }
    
}

void MyBattleMap::initCostMap() {
    CCTMXLayer* layer = this->layerNamed("tiled");
    CCSize size = this->getMapSize();
    const char* str;
    int cost = 0;
    costMap = new int*[(int)size.width];
    for(int i = 0; i < size.width; i++) {
        costMap[i] = new int[(int)size.height];
    }
    for (int i=0; i<size.width; ++i) {
        for (int j=0; j<size.height; ++j) {
            str  = ((CCString*) this->propertiesForGID(layer->tileGIDAt(ccp(i,j)))->objectForKey("cost"))->getCString();
            costMap[i][j] = sscanf(str, "%d", &cost);
            
        }
    }
    mybuildingMap = new CCObject**[(int)size.width+2];
    for(int i = 0; i < size.width+2; i++) {
        mybuildingMap[i] = new CCObject*[(int)size.height+2];
    }
    for (int i=0; i<size.width+2; ++i) {
        for (int j=0; j<size.height+2; ++j) {
            mybuildingMap[i][j] = NULL;
        }
    }
    //    layer->get
    //    if (Mathlib::inBound(int(tiled.x+0.5),this->getMapSize().width-1 , 0)&&Mathlib::inBound(int(tiled.y+0.5),this->getMapSize().height-1 , 0)) {
    //    ////        CCLog("TransX:%f,transY:%f",ceil(tiled.x),ceil(tiled.y));
    //        layer->setTileGID(3,ccp(int(tiled.x+0.5),int(tiled.y+0.5)));
    //    }
}

bool MyBattleMap::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent) {
    isDeploy = true;
    return GXScrollTMXTileMap::ccTouchBegan(pTouch, pEvent);
}

void MyBattleMap::ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent) {
    if(((BattleScene*)this->getParent())->getFighting() != afterFightTag) {
        if (isDeploy && currentDeployButton != NULL) {
            
            CCPoint posi = this->transScreenToMap(pTouch->getLocationInView());
            CCPoint tilePosi = this->transMapToTiled(posi);
            if(Mathlib::inBound(tilePosi.x+0.5, this->getMapSize().width+2, -2) && Mathlib::inBound(tilePosi.y+0.5, this->getMapSize().height+2, -2)) {
                if(checkTiledBound(tilePosi.x+0.5, tilePosi.y+0.5)) {
                    if(costMap[(int)(tilePosi.x+0.5)][(int)(tilePosi.y+0.5)] >1) {
                        //                        CCLog("鬼子进村");
                        return;
                    }
                }
                MyUnit* unit = currentDeployButton->deployUnit();
                if (unit!=NULL) {
                    CCPoint posi = this->transScreenToMap(pTouch->getLocationInView());
                    unit->setPosition(posi);
                    unit->deployPosi = this->transMapToTiled(posi);
                    this->CCNode::addChild(unit,9999999);
                    units->addObject(unit);
                    unit->doAI();
                    currentDeployButton->count++;
                    ((BattleScene*)this->getParent())->toFight();
                }
            }
        }
        GXScrollTMXTileMap::ccTouchEnded(pTouch, pEvent);;
    }
    
}

void MyBattleMap::ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent) {
    if(Mathlib::getDistance(pTouch->getLocation(), pTouch->getPreviousLocation()) > 10) {
        isDeploy = false;
    }
    GXScrollTMXTileMap::ccTouchMoved(pTouch, pEvent);
}

void MyBattleMap::setCurrentDeployButton(CCMenuItem *_deployButton) {
    CC_SAFE_RELEASE(this->currentDeployButton);
    //    this->target->release();
    CC_SAFE_RETAIN(_deployButton);
    this->currentDeployButton = (MyDeployButton*)_deployButton;
}

void MyBattleMap::registerWithTouchDispatcher() {
    GXScrollTMXTileMap::registerWithTouchDispatcher();
    CCDirector::sharedDirector()->getKeypadDispatcher()->addDelegate(this);
}

void MyBattleMap::unRegisterWithTouchDispatcher() {
    GXScrollTMXTileMap::unRegisterWithTouchDispatcher();
    CCDirector::sharedDirector()->getKeypadDispatcher()->removeDelegate(this);
}

void MyBattleMap::keyBackClicked() {
    CCLog("keyBackClicked");
    
    ((BattleScene*)this->getParent())->toSurrender();
}

void MyBattleMap::keyMenuClicked() {
    CCLog("keyMenuClicked");
}

void MyBattleMap::clearSfxCount() {
    sfxCount = 0;
}

void MyBattleMap::playUnitEffect(const char* str,int testBase) {
    if ((sfxCount%(testBase*10))/testBase <1) {
        CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(str);
        sfxCount+=testBase;
    }
}
