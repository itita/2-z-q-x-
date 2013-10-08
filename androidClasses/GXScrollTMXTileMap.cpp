//
//  GXScrollTMXTileMap.cpp
//  ww2
//
//  Created by DingYu Fu on 12-8-26.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//
#define positionX this->getPosition().x
#define positionY this->getPosition().y

#define offsetY pTouch->getPreviousLocationInView().y - pTouch->getLocationInView().y
#define offsetX pTouch->getLocationInView().x - pTouch->getPreviousLocationInView().x



#include <iostream>
#include "GXScrollTMXTileMap.h"
#include "cocos2d.h"
#include "Mathlib.h"
#include "DefineSet.h"

using namespace cocos2d;


//GXScrollTMXTileMap::~GXScrollTMXTileMap() {
//    
//}

GXScrollTMXTileMap* GXScrollTMXTileMap::create(const char *tmxFile) {
    GXScrollTMXTileMap *pRet = new GXScrollTMXTileMap();
    if (pRet->initWithTMXFile(tmxFile))
    {
        pRet->autorelease();
        pRet->viewSize = winSize;
        CCDirector::sharedDirector()->setProjection(kCCDirectorProjection2D);
        return pRet;
    }
    CC_SAFE_DELETE(pRet);
    return NULL;
}

void GXScrollTMXTileMap::registerWithTouchDispatcher(void) {
    //    CCLayer::registerWithTouchDispatcher();
    //    CCDirector* pDirector = CCDirector::sharedDirector();
    //    CCLOG("registed");
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, kCCMenuHandlerPriority+1, true);

    //    CCDirector::sharedDirector()->getTouchDispatcher()->addStandardDelegate(this,0);
    
}
bool GXScrollTMXTileMap::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent) {
    if (!m_enabled) {
        return false;
    }
    CCPoint test = transScreenToMap(ccp(pTouch->getLocationInView().x,pTouch->getLocationInView().y));
//    CCLog("testX:%f,testY:%f",test.x,test.y);
    CCPoint tiled = transMapToTiled(test);
//    CCLog("tiledX:%f,tiledY:%f",tiled.x,tiled.y);
//    CCTMXLayer* layer = this->layerNamed("tiled");
//    if (Mathlib::inBound(int(tiled.x+0.5),this->getMapSize().width-1 , 0)&&Mathlib::inBound(int(tiled.y+0.5),this->getMapSize().height-1 , 0)) {
////        CCLog("TransX:%f,transY:%f",ceil(tiled.x),ceil(tiled.y));
//        layer->setTileGID(3,ccp(int(tiled.x+0.5),int(tiled.y+0.5)));
//    }
// 
    if(Mathlib::inBound(pTouch->getLocationInView().x,
                        0+viewSize.width,
                        0)
       &&Mathlib::inBound((CCDirector::sharedDirector()->getWinSize().height
                           -pTouch->getLocationInView().y),
                         0+viewSize.height,
                          0)) {
           //           dispatchToChild(pTouch, pEvent);
           speedVector.x = 0;
           speedVector.y = 0;
           this->unschedule(schedule_selector(GXScrollTMXTileMap::decelerate));
           return true;
       }
    return false;
}

void GXScrollTMXTileMap::ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent){
//    this->setPosition(ccp(positionX + offsetX,positionY + offsetY));
    CCPoint lastLoc = this->getPosition();
    this->setPosition(ccp(Mathlib::bound(positionX + offsetX,
                                         oriPosition.x,
                                         viewSize.width-contentMapSize.width+oriPosition.x),
                          Mathlib::bound(positionY + offsetY,
                                         oriPosition.y,
                                         viewSize.height-contentMapSize.height+oriPosition.y)));
    speedVector.x = (getPosition().x - lastLoc.x+speedVector.x)/2;
    speedVector.y = (getPosition().y - lastLoc.y+speedVector.y)/2;
}

void GXScrollTMXTileMap::ccTouchEnded(CCTouch* pTouch, CCEvent* pEvent){
    this->schedule(schedule_selector(GXScrollTMXTileMap::decelerate));
}

void GXScrollTMXTileMap::setContentMapSize(CCSize size) {
    contentMapSize = CCSizeMake(MAX(size.width, viewSize.width), MAX(size.height, viewSize.height));
}

void GXScrollTMXTileMap::setContentSize(const cocos2d::CCSize size) {
    CCTMXTiledMap::setContentSize(size);
    this->contentMapSize = size;
}

void GXScrollTMXTileMap::setOriPosition(const cocos2d::CCPoint point){
    CCTMXTiledMap::setPosition(point);
//    CCTMXTiledMap::setAnchorPoint(point);
    this->oriPosition = point;
}

CCPoint GXScrollTMXTileMap::transScreenToMap(const cocos2d::CCPoint &_point) {
    CCPoint temp = Mathlib::getGlobalPosition(this);
    return ccp(_point.x-temp.x,CCDirector::sharedDirector()->getWinSize().height-_point.y-temp.y);
}

CCPoint GXScrollTMXTileMap::transTiledToMap(const cocos2d::CCPoint &_point){
    CCSize tiledSize = this->layerNamed("tiled")->getMapTileSize();
    float mapX = this->getContentSize().width/2+0.5*tiledSize.width*(_point.x-_point.y);
    float mapY = this->getContentSize().height - (0.5*tiledSize.height + 0.5*tiledSize.height*(_point.x+_point.y));
    
    return ccp(mapX,mapY);
}

CCPoint GXScrollTMXTileMap::transMapToTiled(const cocos2d::CCPoint &_point) {
     CCSize tiledSize = this->layerNamed("tiled")->getMapTileSize();
    float mx = _point.x;
    float my = _point.y;
    float mw = this->getContentSize().width;
    float mh = this->getContentSize().height;
    float sw = tiledSize.width;
    float sh = tiledSize.height;
//    CCSize s = CoordinateTrans::transWindowToGLInRetina(tiledSize);

//    CCLog("winsizeWidth:%f,winsizeHeight:%f",winSize.width,winSize.height);
    
    float tx = ((2*mx-mw)/sw + (2*mh-2*my)/sh)/2 - 0.5;
    float ty = (((2*mh-2*my)/sh) - (2*mx-mw)/sw)/2 - 0.5;
    return ccp(tx,ty);
}

bool GXScrollTMXTileMap::checkRectTiledBound(const cocos2d::CCPoint &cPoint, const cocos2d::CCSize &rectSize) {
    float dRadiusWidth = getMapSize().width - rectSize.width;
    float dRadiusHeight = getMapSize().height - rectSize.height;
    float dx = absf(cPoint.x - getMapSize().width/2+0.5);
    float dy = absf(cPoint.y - getMapSize().height/2+0.5);
//    return (absf(cPoint.x - getMapSize().width/2) <= (getMapSize().width - rectSize.width)/2)&&(absf(cPoint.y - getMapSize().height/2) <= (getMapSize().height - rectSize.height)/2);
    return (dx <= dRadiusWidth/2+0.01) && (dy <= dRadiusHeight/2+0.01);
}

bool GXScrollTMXTileMap::checkScreenBound(float i, float j) {
//    return Mathlib::inBound(i, this->getMapSize().width-1, 0) && Mathlib::inBound(j, this->getMapSize().height-1, 0);
    
    return  Mathlib::inBound(i,
                             contentMapSize.width-oriPosition.x,
                             -oriPosition.x)&&
    Mathlib::inBound(j,
                     contentMapSize.height-oriPosition.y,
                     -oriPosition.y);
}

bool GXScrollTMXTileMap::checkTiledBound(float i, float j) {
    return Mathlib::inBound(i, this->getMapSize().width-1, 0) && Mathlib::inBound(j, this->getMapSize().height-1, 0);
}

bool GXScrollTMXTileMap::checkTiledBound(const cocos2d::CCPoint &cPoint) {
    return Mathlib::inBound(cPoint.x, this->getMapSize().width-1, 0) && Mathlib::inBound(cPoint.y, this->getMapSize().height-1, 0);
}

//如果注册了~就一定要解锁免得就没得释放，就点击重叠出错
void GXScrollTMXTileMap::unRegisterWithTouchDispatcher() {
    CCDirector* pDirector = CCDirector::sharedDirector();
    pDirector->getTouchDispatcher()->removeDelegate(this);
}


void GXScrollTMXTileMap::pauseSchedulerAndActions() {
    CCTMXTiledMap::pauseSchedulerAndActions();
    CCArray* children = this->getChildren();
    CCObject* obj;
    CCARRAY_FOREACH(children, obj) {
        ((CCNode*)obj) -> cleanup();
    }
}

void GXScrollTMXTileMap::resumeSchedulerAndActions() {
    CCTMXTiledMap::resumeSchedulerAndActions();
    CCArray* children = this->getChildren();
    CCObject* obj;
    CCARRAY_FOREACH(children, obj) {
        ((CCNode*)obj) -> resumeSchedulerAndActions();
    }
}

void GXScrollTMXTileMap::centerView() {
    float centerX = this->getOriPosition().x-this->getContentMapSize().width/2+winSize.width/2;
    float centerY = this->getOriPosition().y-this->getContentMapSize().height/2+winSize.height/2;
    setPosition(ccp(centerX,centerY));
    
}

void GXScrollTMXTileMap::onEnter() {

    //当进入时才注册点击事件，退出时封锁
    CCTMXTiledMap::onEnter();
    
    registerWithTouchDispatcher();

}

void GXScrollTMXTileMap::onExit() {
    
    CCTMXTiledMap::onExit();
    unRegisterWithTouchDispatcher();
}

void GXScrollTMXTileMap::decelerate() {
    if (Mathlib::inBound(positionX + speedVector.x,
                         oriPosition.x,
                         viewSize.width-contentMapSize.width+oriPosition.x) && Mathlib::inBound(positionY + speedVector.y,
                                                                                              oriPosition.y,
                                                                                              viewSize.height-contentMapSize.height+oriPosition.y)) {
        this->setPosition(ccp(positionX + speedVector.x,positionY + speedVector.y));
        float length = Mathlib::getDistance(ccp(0,0), speedVector);
        if(length < decelerateSpeed) {
            this->unschedule(schedule_selector(GXScrollTMXTileMap::decelerate));
        }
        speedVector.x -= decelerateSpeed * speedVector.x/length;
        speedVector.y -= decelerateSpeed * speedVector.y/length;
    } else {
        this->unschedule(schedule_selector(GXScrollTMXTileMap::decelerate));
    }
}