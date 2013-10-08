//
//  NewMenuDevice.h
//  ww2
//
//  Created by DingYu Fu on 12-9-13.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//
#define offsetX (pTouch->locationInView().x - pTouch->previousLocationInView().x)
#define offsetY (pTouch->previousLocationInView().y - pTouch->locationInView().y)
#define positionX (this->getPosition().x)
#define positionY (this->getPosition().y)
#define shiftX (pTouch->locationInView().x - this->convertToWorldSpace(this->getPosition()).x)
#define shiftY (pTouch->locationInView().y - this->convertToWorldSpace(this->getPosition()).y)
#define locationY ( CCDirector::sharedDirector()->getWinSize().height - pTouch->locationInView().y)
#ifndef ww2_NewMenuDevice_h
#define ww2_NewMenuDevice_h
#include "cocos2d.h"
#include "DeviceInterface.h"
#include "MyEntity.h"

class NewMenuDevice : public CCMenu,public DeviceInterface {
    
public:
    CCPoint positionByTiled;
    CCSize contentSizeByTiled;
    
    static  NewMenuDevice* create(const CCSize& contentSize,CCMenuItem* item, ...);
    //    virtual void setContentSizeByTiled(const CCSize& _size);
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
    virtual void addChild(cocos2d::CCNode* child);
    virtual void addChild(cocos2d::CCNode* child,int zorder);
    virtual void addChild(CCNode * child, int zOrder, int tag);
    //    void setParentMap(MyMap* _map) { map=_map;};
    
    virtual void setPosition(const CCPoint& pos);
    
//    virtual void setMap(GXScrollTMXTileMap* _map);
    virtual void setPositionByTiled(const CCPoint& pos);
    
protected:
    virtual CCMenuItem* itemForTouch(CCTouch *touch);
private:
    bool isMoved;
//    CCSize tiledSize;
    CCPoint cacheLoc;
    // 这里并不引用父类，避免内存释放不好~
    MyEntity* parent;
};

#endif
