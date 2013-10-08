//
//  GXFadeOutAndRemoveWhenStop.h
//  ww4
//
//  Created by xiao tang on 13-4-2.
//
//

#ifndef __ww4__GXFadeOutAndRemoveWhenStop__
#define __ww4__GXFadeOutAndRemoveWhenStop__

#include <iostream>

#include "cocos2d.h"

using namespace cocos2d;

class GXFadeOutAndRemoveWhenStop :public CCFadeOut{
    
public:
    static GXFadeOutAndRemoveWhenStop* create(float d);
    virtual void stop(void);
};

#endif /* defined(__ww4__GXFadeOutAndRemoveWhenStop__) */
