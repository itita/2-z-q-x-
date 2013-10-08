//
//  GXRepeatForever.h
//  ww3
//
//  Created by xiao tang on 12-12-17.
//
//

#ifndef __ww3__GXRepeatForever__
#define __ww3__GXRepeatForever__

#include "cocos2d.h"

using namespace cocos2d;

class GXRepeatForever : public CCRepeatForever {
    
public:
    static GXRepeatForever* create(CCActionInterval *pAction);
    virtual void step(float dt);
};


#endif /* defined(__ww3__GXRepeatForever__) */
