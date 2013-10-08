//
//  Header.h
//  ww2
//
//  Created by DingYu Fu on 12-9-1.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#ifndef ww2_GXInteger_h
#define ww2_GXInteger_h
#include "cocos2d.h"

using namespace cocos2d;

class GXInteger :public CCInteger {
public:
    ~GXInteger() {
    
    }
    
    GXInteger(int v)
    :CCInteger(v)
    {}
    
    static GXInteger* create(int v)
    {
        GXInteger* pRet = new GXInteger(v);
        return pRet;
    }
};

#endif
