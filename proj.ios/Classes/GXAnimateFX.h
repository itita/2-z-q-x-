//
//  GXAnimateFX.h
//  ww2
//
//  Created by DingYu Fu on 12-9-9.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#ifndef ww2_GXAnimateFX_h
#define ww2_GXAnimateFX_h
#include "cocos2d.h"

using namespace cocos2d;

class GXAnimateFX : public cocos2d::CCSprite {
    
public:
    static GXAnimateFX* createWithAnitmateFrameNameByFadeout(const char* _frameName,float isDispear,bool isLoop);
    static GXAnimateFX* createWithAnitmateFrameName(const char* _frameName,bool isDispear,bool isLoop);
    static GXAnimateFX* createWithAnitmateFrameName(const char* _frameName,bool isDispear,bool isLoop,int startCount ,int endCount);
private:
    virtual cocos2d::CCAnimation* initAction(const char* _spriteFrameName);
    virtual cocos2d::CCAnimation* initAction(const char* _spriteFrameName,int startCount,int endCount);
    virtual void dispose();
};

#endif
