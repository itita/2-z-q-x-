//
//  GXTintToCreator.h
//  Dialog2
//
//  Created by xiao tang on 13-8-24.
//
//

#ifndef __Dialog2__GXTintToCreator__
#define __Dialog2__GXTintToCreator__

#include "GXActionCreator.h"

class GXTintToCreator : public GXActionCreator {
    
public:
    GXTintToCreator():
    duration(0),
    r(255),
    g(255),
    b(255){
    
    }
    
    ~GXTintToCreator() {
        CCLog("GXTintToCreator has released");
    }
    static GXTintToCreator* create();
    int duration;
    GLubyte r;
    GLubyte g;
    GLubyte b;
    virtual CCAction* getAction();
    
};

#endif /* defined(__Dialog2__GXTintToCreator__) */
