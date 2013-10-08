//
//  GXFadeToCreator.h
//  Dialog2
//
//  Created by xiao tang on 13-8-23.
//
//

#ifndef __Dialog2__GXFadeToCreator__
#define __Dialog2__GXFadeToCreator__

#include <iostream>
#include "GXActionCreator.h"

class GXFadeToCreator : public GXActionCreator  {
    
public:
    GXFadeToCreator():
    _duration(0),
    _targetOpacity(0),
    _oriOpacity(0) {
    
    }
    
    ~GXFadeToCreator() {
        CCLog("GXFadeToCreator has released");
    }
    
    static GXFadeToCreator* create();
    virtual CCAction* getAction();
    
    
    float _duration;
    GLubyte _targetOpacity;
    GLubyte _oriOpacity;
    
};

class GXFadeTo : public CCFadeTo {
    
public:
    static GXFadeTo* create(float duration,GLubyte targetOpacity,GLubyte oriOpacity);
    virtual void startWithTarget(CCNode *pTarget);
};

#endif /* defined(__Dialog2__GXFadeToCreator__) */
