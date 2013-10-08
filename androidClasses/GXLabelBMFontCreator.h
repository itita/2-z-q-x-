//
//  GXLabelBMFontCreator.h
//  ww4
//
//  Created by xiao tang on 13-9-7.
//
//

#ifndef __ww4__GXLabelBMFontCreator__
#define __ww4__GXLabelBMFontCreator__

#include "cocos2d.h"
#include "DefineSet.h"

using namespace cocos2d;

class GXLabelBMFontCreator : public CCObject{
    
public:
    GXLabelBMFontCreator():
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
    labelWidth(-1),
    fntFileName(NULL),
    textAlignment(kCCTextAlignmentLeft),
    relativeType(relativeZeroType),
    relativeDWidthType(relativeDWidthZeroType),
    zOrder(0),
    size(25)
    {
        setFntFileName(CCString::create("basicfont.fnt"));
    }
    
    ~GXLabelBMFontCreator() {
        CC_SAFE_RELEASE_NULL(content);
        CC_SAFE_RELEASE_NULL(fntFileName);
    }
    
    
    static GXLabelBMFontCreator* create();
    
    CC_SYNTHESIZE_RETAIN(cocos2d::CCString*, content, Content);
    CC_SYNTHESIZE_RETAIN(cocos2d::CCString*, fntFileName, FntFileName);
    float x;
    float y;
    float scaleX;
    float scaleY;
    float anchorX;
    float anchorY;
    int size;
    CCLabelBMFont* getLabel();
    GLubyte a;
    GLubyte r;
    GLubyte g;
    GLubyte b;
    float labelWidth;
    CCTextAlignment textAlignment;
    int relativeType;
    int relativeDWidthType;
    int zOrder;
};

#endif /* defined(__ww4__GXLabelBMFontCreator__) */
