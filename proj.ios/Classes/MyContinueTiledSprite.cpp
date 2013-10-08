//
//  MyContinueTiledSprite.cpp
//  ww3
//
//  Created by xiao tang on 12-12-3.
//
//

#include "MyContinueTiledSprite.h"
#include "MyBattleMap.h"
#include "MyBattleBuilding.h"
#include "MyBuilding.h"
#include "MyMenu.h"
#include "Mathlib.h"
#include "MyBattleState.h"

MyContinueTiledSprite::~MyContinueTiledSprite() {
    CC_SAFE_RELEASE_NULL(spriteFileName);
}



void MyContinueTiledSprite::updateLoc(int value) {
    //这个地方有点日甩
    MyBattleMap* map = dynamic_cast<MyBattleMap*>(this->getParent()->getParent());
//    CCLog("thisname:%s",this->spriteFileName->getCString());
    if (map!= NULL) {
        CCPoint thisPos = Mathlib::roundPoint(map->transMapToTiled(this->getParent()->getPosition()));
        int posX = (int)thisPos.x+1;
        int posY = (int)thisPos.y+2;
        MyBattleBuilding* ldbuiliding = (MyBattleBuilding*)map->mybuildingMap[posX][posY];
        if (ldbuiliding!= NULL) {
            MyContinueTiledSprite* item = dynamic_cast<MyContinueTiledSprite*>(ldbuiliding->getChildByTag(mainTiledSpriteTag));
            if(item != NULL && item != this && spriteFileName->compare(item->spriteFileName->getCString())==0) {
                this->ld = value;
                item->ru = value;
                item->updateSprite();
            }
        }
        posX = (int)thisPos.x+1;
        posY = (int)thisPos.y;
        MyBattleBuilding* rubuiliding = (MyBattleBuilding*)map->mybuildingMap[posX][posY];
        if (rubuiliding!= NULL) {
            MyContinueTiledSprite* item = dynamic_cast<MyContinueTiledSprite*>(rubuiliding->getChildByTag(mainTiledSpriteTag));
            if(item != NULL && item != this && spriteFileName->compare(item->spriteFileName->getCString())==0) {
                this->ru = value;
                item->ld = value;
                item->updateSprite();
            }
        }
        posX = (int)thisPos.x+2;
        posY = (int)thisPos.y+1;
        MyBattleBuilding* rdbuiliding = (MyBattleBuilding*)map->mybuildingMap[posX][posY];
        if (rdbuiliding!= NULL) {
            MyContinueTiledSprite* item = dynamic_cast<MyContinueTiledSprite*>(rdbuiliding->getChildByTag(mainTiledSpriteTag));
            if(item != NULL && item != this && spriteFileName->compare(item->spriteFileName->getCString())==0) {
                item->lu = value;
                this->rd = value;
                item->updateSprite();
            }
        }
        posX = (int)thisPos.x;
        posY = (int)thisPos.y+1;
        MyBattleBuilding* lubuiliding = (MyBattleBuilding*)map->mybuildingMap[(int)thisPos.x][(int)thisPos.y+1];
        if (lubuiliding!= NULL) {
            MyContinueTiledSprite* item = dynamic_cast<MyContinueTiledSprite*>(lubuiliding->getChildByTag(mainTiledSpriteTag));
            if(item != NULL && item != this && spriteFileName->compare(item->spriteFileName->getCString())==0) {
                this->lu = value;
                item->rd = value;
                item->updateSprite();
            }
        }
        
        
//        CCObject* obj;
//        CCARRAY_FOREACH(items, obj) {
//            MyBattleBuilding* builiding = (MyBattleBuilding*)obj;
//            MyContinueTiledSprite* item = dynamic_cast<MyContinueTiledSprite*>(builiding->getChildByTag(mainTiledSpriteTag));
////            if(item != NULL) {
//////                CCLog("thisname:%s",item->spriteFileName->getCString());
////            }
//            if(item != NULL && spriteFileName->compare(item->spriteFileName->getCString())==0) {
//                CCPoint itemPos = Mathlib::roundPoint(map->transMapToTiled(item->getParent()->getPosition()));
//                CCPoint thisPos = Mathlib::roundPoint(map->transMapToTiled(this->getParent()->getPosition()));
//                if (itemPos.x - thisPos.x == 1 && itemPos.y == thisPos.y) {
//                    item->lu = value;
//                    this->rd = value;
//                    item->updateSprite();
//                } else if (itemPos.x - thisPos.x == -1 && itemPos.y == thisPos.y) {
//                    this->lu = value;
//                    item->rd = value;
//                    item->updateSprite();
//                } else if (itemPos.y - thisPos.y == 1 && itemPos.x == thisPos.x)  {
//                    this->ld = value;
//                    item->ru = value;
//                    item->updateSprite();
//                } else if (itemPos.y - thisPos.y == -1 && itemPos.x == thisPos.x) {
//                    this->ru = value;
//                    item->ld = value;
//                    item->updateSprite();
//                }
//                //                CCLog("x:%f,y:%f",itemPos.x,itemPos.y);
//                //            item->
//            }
//        }
        updateSprite();
    }else {
        MyMap* map = dynamic_cast<MyMap*>(this->getParent()->getParent());
        CCArray* items = map->getItems();
        CCObject* obj;
        CCARRAY_FOREACH(items, obj) {
            MyBuilding* builiding = (MyBuilding*)obj;
            MyContinueTiledSprite* item = dynamic_cast<MyContinueTiledSprite*>(builiding->getNormalImage());
            if(item != NULL && spriteFileName->compare(item->spriteFileName->getCString())==0) {
                CCPoint itemPos = Mathlib::roundPoint(map->transMapToTiled(item->getParent()->getPosition()));
                CCPoint thisPos = Mathlib::roundPoint(map->transMapToTiled(this->getParent()->getPosition()));
                if (itemPos.x - thisPos.x == 1 && itemPos.y == thisPos.y) {
                    item->lu = value;
                    this->rd = value;
                    item->updateSprite();
                } else if (itemPos.x - thisPos.x == -1 && itemPos.y == thisPos.y) {
                    this->lu = value;
                    item->rd = value;
                    item->updateSprite();
                } else if (itemPos.y - thisPos.y == 1 && itemPos.x == thisPos.x)  {
                    this->ld = value;
                    item->ru = value;
                    item->updateSprite();
                } else if (itemPos.y - thisPos.y == -1 && itemPos.x == thisPos.x) {
                    this->ru = value;
                    item->ld = value;
                    item->updateSprite();
                }
                //                CCLog("x:%f,y:%f",itemPos.x,itemPos.y);
                //            item->
            }
        }
        updateSprite();
    }
}

//// 首先载入贴图集
//CCSpriteBatchNode *spriteBatch=CCSpriteBatchNode::batchNodeWithFile("snake.png");
//this->addChild(spriteBatch);
//CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("snake.plist");
//// 生成Sprite
//CCSprite *headSprite=CCSprite::spriteWithSpriteFrameName("headup.png");
////需要更换图片时
//CCSpriteFrame *frame=CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("headleft.png");
//headSprite->setDisplayFrame(frame);

void MyContinueTiledSprite::updateSprite() {
    char str[64];
    if ((ld && ru) && !lu && ! rd) {
        sprintf(str, "%sud.png",spriteFileName->getCString());
        CCSpriteFrame *frame=CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(str);
        this->setDisplayFrame(frame);
    } else if((lu && rd) && !ld && !ru){
        sprintf(str, "%slr.png",spriteFileName->getCString());
        CCSpriteFrame *frame=CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(str);
        this->setDisplayFrame(frame);
    }
    //    else if((lu && ru) && !ld && !rd) {
    //        sprintf(str, "%slu.png",spriteFileName->getCString());
    //        CCSprite* r = CCSprite::createWithSpriteFrameName(str);
    //        this->setNormalImage(r);
    //    } else if((lu && ld) && !ru && !rd) {
    //        sprintf(str, "%srd.png",spriteFileName->getCString());
    //        CCSprite* r = CCSprite::createWithSpriteFrameName(str);
    //        this->setNormalImage(r);
    //    } else if((ld && rd) && !ru && !lu) {
    //        sprintf(str, "%slr.png",spriteFileName->getCString());
    //        CCSprite* r = CCSprite::createWithSpriteFrameName(str);
    //        this->setNormalImage(r);
    //    } else if((ru && rd) && !lu && !ld) {
    //        sprintf(str, "%sld.png",spriteFileName->getCString());
    //        CCSprite* r = CCSprite::createWithSpriteFrameName(str);
    //        this->setNormalImage(r);
    //    }
    else {
        sprintf(str, "%sc.png",spriteFileName->getCString());
        CCSpriteFrame *frame=CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(str);
        this->setDisplayFrame(frame);
    }
}

MyContinueTiledSprite* MyContinueTiledSprite::create(cocos2d::CCString *spriteFileName) {
    MyContinueTiledSprite *pRet = new MyContinueTiledSprite();
    char str[64];
    sprintf(str, "%sc.png",spriteFileName->getCString());

    pRet->initWithSpriteFrameName(str);
    pRet->autorelease();
    pRet->spriteFileName = spriteFileName;
    pRet->ld = 0;
    pRet->lu = 0;
    pRet->rd = 0;
    pRet->ru = 0;
    pRet->isSelected = false;
    spriteFileName->retain();
    //    pRet->contentSizeByTiled = _contentSize;
    return pRet;
}