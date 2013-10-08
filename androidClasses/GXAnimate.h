//
//  GXAnimate.h
//  ww4
//
//  Created by xiao tang on 13-1-29.
//
//

#ifndef __ww4__GXAnimate__
#define __ww4__GXAnimate__

#include "cocos2d.h"

using namespace cocos2d;

class GXAnimate : public CCAnimate {
    
public:
    static GXAnimate* create(CCAnimation *pAnimation);
    virtual void stop(void);
};

#endif /* defined(__ww4__GXAnimate__) */
