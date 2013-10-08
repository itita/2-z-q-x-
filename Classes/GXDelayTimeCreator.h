//
//  GXDelayTime.h
//  Dialog2
//
//  Created by xiao tang on 13-8-23.
//
//

#ifndef __Dialog2__GXDelayTimeCreator__
#define __Dialog2__GXDelayTimeCreator__

#include "GXActionCreator.h"

class GXDelayTimeCreator : public GXActionCreator {
    
public:
    GXDelayTimeCreator():
    duration(0) {
        
    }
    
    ~GXDelayTimeCreator() {
        CCLog("GXDelayTimeCreator has released");
    }
    
    static GXDelayTimeCreator* create();
    int duration;
    virtual CCAction* getAction();
};

#endif /* defined(__Dialog2__GXDelayTime__) */
