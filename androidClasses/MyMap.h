//
//  Header.h
//  WW2
//
//  Created by DingYu Fu on 12-8-26.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//


//要对地图进行一次大型封装~
#ifndef ww2_MyMap_h
#define ww2_MyMap_h
#include "GXScrollTMXTileMap.h"
#include "cocos2d.h"
#include "MyTiledMenuItemSprite.h"
//#include "MyMenu.h"
//#include "MyMenu.h"

class MyMap : public GXScrollTMXTileMap , public CCKeypadDelegate{
public:
    MyMap():
    isMoved(false),
    isCollision(false),
    _isBuild(false),
    moveTemp(NULL),
    m_pSelectedItem(NULL),
    moveEnabled(false),
    buildisMove(false),
    roadSheet(NULL){}
    virtual void addChild(cocos2d::CCNode* child);
    virtual void addChild(cocos2d::CCNode* child,int zorder);
    static MyMap* create(const char *tmxFile);
    virtual ~MyMap();
//    cocos2d::CCSprite* getGreen(){return green; };
//    cocos2d::CCSprite* getRed(){return red; };
    virtual CCLayer* getTip();
    CCArray* getItems() {return items;};
    virtual bool collisionDetection(CCMenuItem* checkItem);
    virtual bool collisionDetection();
    virtual bool collisionDetectionSpecial(const CCPoint& posi,const CCSize& size);
    CCMenuItem* moveTemp;
    virtual void initTip(CCPoint pos,CCSize &contentSize);
    virtual void dispearTip();
    virtual void dispearArrowTip();
    virtual void displayAllSummary();
    virtual void moveArrowTip(const CCPoint& pos, CCSize& size);
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
    virtual bool cancelAllBuilding();
    
    virtual void registerWithTouchDispatcher(void);
    virtual void unRegisterWithTouchDispatcher(void);
    
    
    //Android 返回键
    
    virtual void keyBackClicked();
    
    //Android 菜单键
    
    virtual void keyMenuClicked();
    
    virtual void removeChild(CCNode* child, bool cleanup);
    
    
    virtual void setBuild(bool __isbuild,CCMenuItem* moveTemp);
    virtual bool isBuild();
    CCPoint oriBuildPos;
    
    
    
    cocos2d::CCSprite* arrowl;
    cocos2d::CCSprite* arrowr;
    cocos2d::CCSprite* arrowu;
    cocos2d::CCSprite* arrowd;
    CCSpriteBatchNode* roadSheet;
protected:
    cocos2d::CCLayer* red;
    cocos2d::CCLayer* green;
    
private:
    virtual CCMenuItem* itemForTouch(CCTouch *touch);
    CCMenuItem *m_pSelectedItem;
    virtual void loadTip();
    bool isCollision;
    CCArray* items;
    bool isMoved;
    bool _isBuild;
    
    //建筑是否移动
    bool moveEnabled;
    CCPoint cacheTouch;
    bool buildisMove;
    
    
//    void setMapPriority();
//    CCMenu* temp;
};

#endif
