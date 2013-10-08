//
//  GXSequenceCreator.h
//  Dialog2
//
//  Created by xiao tang on 13-8-23.
//
//

#ifndef __Dialog2__GXSequenceCreator__
#define __Dialog2__GXSequenceCreator__

#include <iostream>

#include "GXActionCreator.h"

class GXSequenceCreator : public GXActionCreator {
    
public:
    GXSequenceCreator():
    actionCreatorArray(NULL) {
        
    }
    
    ~GXSequenceCreator() {
        CC_SAFE_RELEASE_NULL(actionCreatorArray);
    }
    
    static GXSequenceCreator* create();
    CCArray* actionCreatorArray;
    virtual CCAction* getAction();
};

#endif /* defined(__Dialog2__GXSequenceCreator__) */
