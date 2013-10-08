//
//  GXScrollTMXTileMap.h
//  ww2
//
//  Created by DingYu Fu on 12-8-26.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#ifndef ww2_GXScrollTMXTileMap_h
#define ww2_GXScrollTMXTileMap_h
#include "cocos2d.h"

using namespace cocos2d;

class GXScrollTMXTileMap : public cocos2d::CCTMXTiledMap,public cocos2d::CCTouchDelegate
{
public:
    ~GXScrollTMXTileMap() {
        CCLog("GXScrollTMXTileMap has released");
    }
    GXScrollTMXTileMap():
    m_enabled(true),
    speedVector(ccp(0,0)){}
//    virtual ~GXScrollTMXTileMap();
    CCPoint getOriPosition() {return oriPosition;};
    void setViewSize(CCSize size) {viewSize = size;};
    CCSize getViewSize() {return viewSize;}
//与父类方法重名，还是区分为好。
    virtual void setContentMapSize(CCSize size);
    CCSize getContentMapSize() {return contentMapSize;}
    static GXScrollTMXTileMap* create(const char *tmxFile);
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
    virtual void registerWithTouchDispatcher(void); 
    virtual void setContentSize(const CCSize _size);
    //    virtual void setPosition(CCPoint point);
    virtual void setOriPosition(const CCPoint _point);
    void decelerate();
    CCPoint transScreenToMap(const CCPoint& _point);
    CCPoint transTiledToMap(const CCPoint& _point);
    CCPoint transMapToTiled(const CCPoint& _point);
    bool checkScreenBound(float i,float j);
    bool checkTiledBound(float i,float j);
    bool checkTiledBound(const CCPoint& cPoint);
    bool checkRectTiledBound(const CCPoint& cPoint,const CCSize& rectSize);
    virtual void unRegisterWithTouchDispatcher(void);
    virtual void pauseSchedulerAndActions(void); 
    virtual void resumeSchedulerAndActions(void);
    void centerView();
    void onEnter();
    void onExit();
    void setEnabled(bool enabled) {m_enabled = enabled;}
    bool isEnabled() {return m_enabled;}
protected:
    CCPoint oriPosition;
    CCSize contentMapSize;
    CCSize viewSize;
    CCPoint speedVector;
    bool m_enabled;
};

#endif
