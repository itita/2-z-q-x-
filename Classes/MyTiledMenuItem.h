//
//  MyTiledMenuItem.h
//  ww3
//
//  Created by xiao tang on 12-12-4.
//
//
//#define myTiledMenuItemTag 10
#ifndef ww3_MyTiledMenuItem_h
#define ww3_MyTiledMenuItem_h

#include "cocos2d.h"
#include "MyMap.h"
#include "MyTiledInfo.h"

using namespace cocos2d;

class MyTiledMenuItem :public CCMenuItem,public MyTiledInfo{
public:
    MyTiledMenuItem():
    isActive(false),
    moveEnabled(true),
    normalImage(NULL){}
    //    CCPoint positionByTiled;
    //    CCSize contentSizeByTiled;
    //    GXScrollTMXTileMap* map;
    static  MyTiledMenuItem* create(const CCSize& contentSize,CCSprite* normalImage);
    //    virtual void setContentSizeByTiled(const CCSize& _size);
//    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
//    virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
//    virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
    
    virtual void activate();
    virtual void selected();
    virtual void unselected();
    
    //    void setParentMap(MyMap* _map) { map=_map;};
    
    virtual void setPosition(const CCPoint& pos);
    virtual void setMap(GXScrollTMXTileMap* _map);
    virtual void setPositionByTiled(const CCPoint& pos);
    virtual CCPoint getPositionByTiled();
    //根据Y轴设置优先级
    
//    virtual void registerWithTouchDispatcher();
    
    
    virtual void setActive(bool active);
    bool getActive() {return isActive;}
    virtual void toReLoc();
    virtual void reorderZandTouchPriority(int zorder) ;
    CCPoint cacheLoc;
    virtual void runTouchAction();
    
    virtual void setNormalImage(CCSprite* normalImage);
    virtual CCSprite* getNormalImage();
    virtual CCRect rect();
    bool moveEnabled;
//    bool isCollision;
    
    
protected:
//    virtual CCMenuItem* itemForTouch(CCTouch *touch);
    bool isActive;
//    bool isMoved;
    CCPoint cacheTouch;
    CCSprite* normalImage;
    
private:
    
    
    virtual void updateImagesVisibility();
    //    CCSize tiledSize;
//    int varTouchPriority;
    
    
//    virtual void updateTouchPriority();
};

#endif
