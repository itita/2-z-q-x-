//
//  GXFX.h
//  ww4
//
//  Created by xiao tang on 13-1-7.
//
//

#ifndef __ww4__GXFX__
#define __ww4__GXFX__

#include "cocos2d.h"

using namespace cocos2d;

class GXFX : public CCSprite {
    
public:
    
    GXFX():
    startFrameCount(-1),
    endFrameCount(-1),
    zorder(0){};
    ~GXFX() {
//        CCLog("GXFX has been released");
        CC_SAFE_RELEASE_NULL(animation);
    }
    
    static GXFX* create(CCAnimation* _animation,unsigned int _startFrameCount,int zorder);
    int startFrameCount;
    int endFrameCount;
    int zorder;
    CCAnimation* animation;
    
};

#endif /* defined(__ww4__GXFX__) */
