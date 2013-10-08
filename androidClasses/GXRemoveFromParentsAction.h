//
//  RemoveFromParentsAction.h
//  ww3
//
//  Created by xiao tang on 12-10-13.
//
//

#ifndef ww3_GXRemoveFromParentsAction_h
#define ww3_GXRemoveFromParentsAction_h
#include "cocos2d.h"

using namespace cocos2d;

class GXRemoveFromParentsAction :public CCActionInstant{
    
public:
    static GXRemoveFromParentsAction* create();
    virtual void update(float time);
    virtual void stop(void);
};

#endif
