//
//  GXRadioMenu.h
//  ww2
//
//  Created by DingYu Fu on 12-9-6.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#ifndef ww2_GXRadioMenu_h
#define ww2_GXRadioMenu_h
#include "cocos2d.h"

using namespace cocos2d;

class GXRadioMenu :public cocos2d::CCMenu  {
    
public:
    static GXRadioMenu* create(int _priority,CCMenuItem* item, ...);
    static GXRadioMenu* create(int _priority);
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
    virtual void setSelect(int index);
    virtual void registerWithTouchDispatcher();
    virtual void onEnter();
private:
    CCMenuItem* selectTemp;
    int priority;
};

#endif
