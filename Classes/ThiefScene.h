//
//  ThiefScene.h
//  ww4
//
//  Created by xiao tang on 13-3-5.
//
//

#ifndef __ww4__ThiefScene__
#define __ww4__ThiefScene__

#include <iostream>
#include "GXBaseScene.h"

class ThiefScene : public GXBaseScene{
    
public:
    ~ThiefScene() {
        releaseResource();
    }
    static ThiefScene* create();
    void myInit();
    virtual void loadResource();
    virtual void releaseResource();
    void returnStart();
};

#endif /* defined(__ww4__ThiefScene__) */
