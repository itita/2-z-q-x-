//
//  GXSpriteCreatorBean.h
//  Dialog2
//
//  Created by xiao tang on 13-8-20.
//
//

#ifndef __Dialog2__GXSpriteCreator__
#define __Dialog2__GXSpriteCreator__

#include <iostream>
#include "cocos2d.h"
#include "DefineSet.h"
#include "GXActionCreator.h"

using namespace cocos2d;

class GXSpriteCreator : public CCObject {
    
public:
    GXSpriteCreator():
    spriteFrameName(NULL),
    x(0),
    y(0),
    scaleX(1),
    scaleY(1),
    anchorX(0.5),
    anchorY(0.5),
    a(255),
    r(255),
    g(255),
    b(255),
    relativeType(relativeZeroType),
    zOrder(0),
    isFilpX(false),
    actionCreator(NULL)
    {
        
    }
    
    ~GXSpriteCreator() {
        CC_SAFE_RELEASE_NULL(spriteFrameName);
        CC_SAFE_RELEASE_NULL(actionCreator);
    }
    
    static GXSpriteCreator* create();
    
    CC_SYNTHESIZE_RETAIN(cocos2d::CCString*, spriteFrameName, FrameName);
    float x;
    float y;
    float scaleX;
    float scaleY;
    float width;
    float height;
    float anchorX;
    float anchorY;
    CCSprite* getSprite();
    GLubyte a;
    GLubyte r;
    GLubyte g;
    GLubyte b;
    int relativeType;
    int zOrder;
    bool isFilpX;
    CC_SYNTHESIZE_RETAIN(GXActionCreator*, actionCreator, ActionCreator);
};

#endif /* defined(__Dialog2__GXSpriteCreatorBean__) */
