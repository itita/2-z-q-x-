//
//  GXShakeAction.h
//  ww4
//
//  Created by xiao tang on 13-5-10.
//
//

#ifndef __ww4__GXShakeAction__
#define __ww4__GXShakeAction__

#include <iostream>
#include "cocos2d.h"

using namespace cocos2d;

class GXShakeAction : public CCActionInterval{
    
public:
  
    virtual void startWithTarget(CCNode *pTarget);
    virtual void update(float time);
    virtual void stop(void);
    
public:
    /** creates the action */
    static GXShakeAction* create(float duration,float _xDelta,float _yDelta,const CCPoint& _oriAnchorPoint);
protected:
    float xDelta;
    float yDelta;
    float randomXDelta;
    float randomYDelta;
    CCPoint oriAnchor;
};

#endif /* defined(__ww4__GXShakeAction__) */
