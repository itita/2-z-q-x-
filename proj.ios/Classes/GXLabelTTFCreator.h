//
//  GXLabelTTFCreator.h
//  Dialog2
//
//  Created by xiao tang on 13-8-21.
//
//

#ifndef __Dialog2__GXLabelTTFCreator__
#define __Dialog2__GXLabelTTFCreator__

#include <iostream>
#include "cocos2d.h"
#include "DefineSet.h"

using namespace cocos2d;

class GXLabelTTFCreator : public CCObject {
    
public:
    GXLabelTTFCreator():
    content(NULL),
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
    size(25),
    dimensionsWidth(0),
    dimensionsHeight(0),
    textAlignment(kCCTextAlignmentLeft),
    verticalAlignment(kCCVerticalTextAlignmentTop),
    relativeType(relativeZeroType),
    relativeDWidthType(relativeDWidthZeroType),
    zOrder(0)
    {
        
    }
    
    ~GXLabelTTFCreator() {
        CC_SAFE_RELEASE_NULL(content);
    }
    
    
    static GXLabelTTFCreator* create();
    
    CC_SYNTHESIZE_RETAIN(cocos2d::CCString*, content, Content);
    float x;
    float y;
    float scaleX;
    float scaleY;
    float width;
    float height;
    float anchorX;
    float anchorY;
    int size;
    CCLabelTTF* getLabel();
    GLubyte a;
    GLubyte r;
    GLubyte g;
    GLubyte b;
    float dimensionsWidth;
    float dimensionsHeight;
    CCTextAlignment textAlignment;
    CCVerticalTextAlignment verticalAlignment;
    int relativeType;
    int relativeDWidthType;
    int zOrder;
};

#endif /* defined(__Dialog2__GXLabelTTFCreator__) */
