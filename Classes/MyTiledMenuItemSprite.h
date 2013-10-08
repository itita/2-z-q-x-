//
//  MyTiledMenuItemSprite.h
//  ww2
//
//  Created by DingYu Fu on 12-8-29.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#ifndef ww2_MyTiledMenuItemSprite_h
#define ww2_MyTiledMenuItemSprite_h

#include "cocos2d.h"

using namespace cocos2d;

class MyTiledMenuItemSprite : public cocos2d::CCMenuItemSprite {
    
public:
    
    virtual ~MyTiledMenuItemSprite();
    
    static MyTiledMenuItemSprite * create(CCNode* normalSprite, CCNode* selectedSprite, CCObject* target, SEL_MenuHandler selector);
    
    static MyTiledMenuItemSprite * create(CCNode* normalSprite, CCNode* selectedSprite);
    

//    CCSize contentSizeByTiled;
    
    virtual void runTouchAction();
//    virtual void updateTouchPriority();
private:
    
};


#endif
