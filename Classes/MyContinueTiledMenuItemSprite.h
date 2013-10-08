//
//  MyContinueTiledMenuItemSprite.h
//  ww2
//
//  Created by DingYu Fu on 12-9-15.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#ifndef ww2_MyContinueTiledMenuItemSprite_h
#define ww2_MyContinueTiledMenuItemSprite_h
#include "MyTiledMenuItemSprite.h"
#include "MyMap.h"

using namespace cocos2d;

class MyContinueTiledMenuItemSprite : public MyTiledMenuItemSprite{
    
public:
    virtual ~MyContinueTiledMenuItemSprite();
    static MyContinueTiledMenuItemSprite* create(CCString* spriteFileName,CCObject* target, SEL_MenuHandler selector);
    static MyContinueTiledMenuItemSprite* create(CCString* spriteFileName);
    virtual void runTouchAction();
    virtual void updateSprite();
    virtual void selected();
    virtual void updateLoc(int value);
private:
    CCString* spriteFileName;
    bool isSelected;
    CCPoint oriPos;
    int lu;
    int ru;
    int ld;
    int rd;
};

#endif
