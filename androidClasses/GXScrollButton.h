//
//  GXScrollButton.h
//  ww2
//
//  Created by DingYu Fu on 12-8-25.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#ifndef ww2_GXScrollButton_h
#define ww2_GXScrollButton_h
#include "cocos2d.h"
using namespace cocos2d;

class GXScrollButton : public cocos2d::CCNode {
public:

    static GXScrollButton* creat(CCSprite* _downFacade,CCSprite* _upFacade);
    virtual bool init();
    virtual bool onDown(CCTouch* pTouch,CCEvent* pEvent);
    virtual bool onUp(CCTouch* pTouch,CCEvent* pEvent);
    virtual bool onCancel(CCTouch* pTouch,CCEvent* pEvent);
private:
    CCSprite* downFacade;
    CCSprite* upFacade;
    bool isPress;
};


#endif
