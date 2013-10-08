//
//  GXPoint.h
//  ww2
//
//  Created by DingYu Fu on 12-8-29.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#ifndef ww2_GXPoint_h
#define ww2_GXPoint_h

#include "cocos2d.h"

class GXPoint :public cocos2d::CCObject {
public:
    
    static GXPoint* create();
    int x;
    int y;
};

#endif
