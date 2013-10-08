//
//  NewMenuSpriteItem.h
//  ww2
//
//  Created by DingYu Fu on 12-9-13.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#ifndef ww2_NewMenuSpriteItem_h
#define ww2_NewMenuSpriteItem_h
#include "cocos2d.h"

using namespace cocos2d;

class NewMenuSpriteItem : public cocos2d::CCMenuItemSprite {
    
public:
    
    static NewMenuSpriteItem * create(CCNode* normalSprite, CCNode* selectedSprite, CCObject* target, SEL_MenuHandler selector);
    
    //    CCSize contentSizeByTiled;
    
    virtual void runTouchAction();
};

#endif
