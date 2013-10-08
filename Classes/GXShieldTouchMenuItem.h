//
//  GXShieldTouchMenuItem.h
//  ww3
//
//  Created by xiao tang on 12-11-5.
//
//

#ifndef ww3_GXShieldTouchMenuItem_h
#define ww3_GXShieldTouchMenuItem_h
#include "cocos2d.h"

using namespace cocos2d;

class GXShieldTouchMenuItem : public CCMenuItem {
    
public:
    static GXShieldTouchMenuItem* create();
    virtual void sheild(CCNode* pSender);
    virtual CCRect rect();
};

#endif
