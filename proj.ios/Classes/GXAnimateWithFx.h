//
//  GXAnimateWithFx.h
//  ww4
//
//  Created by xiao tang on 13-1-7.
//
//

#ifndef __ww4__GXAnimateWithFx__
#define __ww4__GXAnimateWithFx__

#include "cocos2d.h"
#include "GXFX.h"

using namespace cocos2d;

class GXAnimateWithFx : public CCAnimate{
    
public:
    GXAnimateWithFx() {
    
    };
    ~GXAnimateWithFx(){
//        CCLog("GXAnimateWithFx has been released");
//        CCObject* obj = NULL;
//        CCARRAY_FOREACH(fxArray, obj) {
//            GXFX* fx = (GXFX*)obj;
//            fx->setVisible(false);
//            fx->removeFromParentAndCleanup(true);
//        }
        CC_SAFE_RELEASE_NULL(fxArray);
    };
    
    static GXAnimateWithFx* create(CCAnimation *pAnimation,CCArray* _fxArray);
    static GXAnimateWithFx* create(CCAnimation *pAnimation,GXFX* fx);
    CCArray* fxArray;
    virtual void startWithTarget(CCNode *pTarget);
    virtual void update(float t);
    virtual void stop(void);

};

#endif /* defined(__ww4__GXAnimateWithFx__) */
