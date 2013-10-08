//
//  GXReverseSheild.h
//  ww3
//
//  Created by xiao tang on 12-12-19.
//
//

#ifndef __ww3__GXReverseSheild__
#define __ww3__GXReverseSheild__

#include "cocos2d.h"

using namespace cocos2d;

class GXReverseSheild : public CCMenu{
    
public:
    ~GXReverseSheild();
    static GXReverseSheild* create(int _priority);
    virtual void registerWithTouchDispatcher();
    
    virtual bool ccTouchBegan(CCTouch* touch, CCEvent* event);
    virtual void ccTouchEnded(CCTouch* touch, CCEvent* event);
 
    virtual void ccTouchMoved(CCTouch* touch, CCEvent* event);
    
private:
    int priority;
    
};

#endif /* defined(__ww3__GXReverseSheild__) */
