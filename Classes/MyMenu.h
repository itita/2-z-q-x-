//
//  MyMenu.h
//  ww2
//
//  Created by DingYu Fu on 12-8-25.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//
//#define myTiledMenuItemTag 10
#ifndef ww2_MyMenu_h
#define ww2_MyMenu_h

#include "cocos2d.h"
#include "MyMap.h"
#include "MyTiledInfo.h"


//可以尝试把TILE相关的分离出来
using namespace cocos2d;

class MyMenu : public cocos2d::CCMenu ,public MyTiledInfo{
public:
    MyMenu():
    isActive(false),
    moveEnabled(false),
    isMoved(false)
    {}
//    CCPoint positionByTiled;
//    CCSize contentSizeByTiled;
//    GXScrollTMXTileMap* map;
    static  MyMenu* create(const CCSize& contentSize,CCMenuItem* item, ...);
//    virtual void setContentSizeByTiled(const CCSize& _size);
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
    virtual void addChild(cocos2d::CCNode* child);
    virtual void addChild(cocos2d::CCNode* child,int zorder);
    virtual void addChild(CCNode * child, int zOrder, int tag);
//    void setParentMap(MyMap* _map) { map=_map;};
    
    virtual void setPosition(const CCPoint& pos);
    virtual void setMap(GXScrollTMXTileMap* _map);
    virtual void setPositionByTiled(const CCPoint& pos);
    virtual CCPoint getPositionByTiled();
    //根据Y轴设置优先级
    
    virtual void registerWithTouchDispatcher();
    
    
    virtual void setActive(bool active);
    bool getActive() {return isActive;}
    virtual void toReLoc();
    virtual void reorderZandTouchPriority(int zorder,int TouchPriority) ;
    CCPoint cacheLoc;
 
protected:
    virtual CCMenuItem* itemForTouch(CCTouch *touch);
    bool isActive;
    bool moveEnabled;
    bool isMoved;
    CCPoint cacheTouch;
private:
   
   
    
//    CCSize tiledSize;
    int varTouchPriority;
    
    
    virtual void updateTouchPriority();
};


#endif
