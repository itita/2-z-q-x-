//
//  GXFadeOut.h
//  ww3
//
//  Created by xiao tang on 12-10-15.
//
//

#ifndef ww3_GXFadeOut_h
#define ww3_GXFadeOut_h
#include "cocos2d.h"

using namespace cocos2d;

class GXFadeOut  :public CCFadeOut{
    
    
public:
    static GXFadeOut* create(float d);
    virtual void stop(void);
    
};

#endif
