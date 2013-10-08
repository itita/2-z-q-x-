//
//  GXScaleTo.h
//  ww3
//
//  Created by xiao tang on 12-12-17.
//
//

#ifndef ww3_GXScaleTo_h
#define ww3_GXScaleTo_h
#include "cocos2d.h"

using namespace cocos2d;

class GXScaleTo :public CCScaleTo{
    
public:
    static GXScaleTo* create(float duration, float s);
    virtual void startWithTarget(CCNode *pTarget);
    virtual void stop(void);
    virtual bool isDone();
    float oriScaleX;
    float oriScaleY;
};

#endif
