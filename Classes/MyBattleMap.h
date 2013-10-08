//
//  MyBattleMap.h
//  ww2
//
//  Created by DingYu Fu on 12-9-5.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#ifndef ww2_MyBattleMap_h
#define ww2_MyBattleMap_h
#include "GXScrollTMXTileMap.h"
#include "MyDeployButton.h"

class MyBattleMap :public GXScrollTMXTileMap ,public CCKeypadDelegate{
public:
    
    MyBattleMap():
    currentDeployButton(NULL),
    items(NULL),
    units(NULL),
    oriGhost(NULL),
    sfxCount(0),
    isDeploy(true){}
    
    int** costMap;
    CCObject*** mybuildingMap;
    virtual void addChild(cocos2d::CCNode* child);
//    virtual void addChild(cocos2d::CCNode* child,int zorder);
    virtual void addGhost(const CCPoint& ghostPos,const CCPoint& nowPos,int resourceCount);
    static MyBattleMap* create(const char *tmxFile);
    virtual ~MyBattleMap();
    //    cocos2d::CCSprite* getGreen(){return green; };
    //    cocos2d::CCSprite* getRed(){return red; };
//    virtual CCSprite* getTip();
    CCArray* getItems() {return items;};
    CCArray* getUnits() {return units;};
    virtual void displayTip();
//    virtual bool collisionDetection();
//    CCMenu* moveTemp;
//    virtual void initTip(CCPoint pos,float scale);
//    virtual void dispearTip();
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);

    virtual void setCurrentDeployButton(CCMenuItem* _deployButton);
    
    virtual void registerWithTouchDispatcher(void);
    virtual void unRegisterWithTouchDispatcher(void);
    virtual void keyBackClicked();
    virtual void keyMenuClicked();
    virtual void playUnitEffect(const char* str,int testBase);
    
    CCObject* oriGhost;
    
    int sfxCount;
    
private:
    CCArray* items;
    CCArray* units;
    MyDeployButton* currentDeployButton;
    virtual void initCostMap();
    bool isDeploy;
    CCTMXLayer* tiledLayer;
    void locatOriGhost(const CCPoint& ghostPos);
    void clearSfxCount();
//    CCSpriteBatchNode* roadSheet;
};

#endif
