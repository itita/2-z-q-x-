//
//  GXPlayAudioEffectCreator.h
//  Dialog2
//
//  Created by xiao tang on 13-8-23.
//
//

#ifndef __Dialog2__GXPlayAudioEffectCreator__
#define __Dialog2__GXPlayAudioEffectCreator__

#include "GXActionCreator.h"

class GXPlayAudioEffectCreator : public GXActionCreator {
    
public:
    
    GXPlayAudioEffectCreator():
    _effectName(NULL) {
        
    }
    
    ~GXPlayAudioEffectCreator() {
        CC_SAFE_RELEASE_NULL(_effectName);
    }
    
    static GXPlayAudioEffectCreator* create();
    CC_SYNTHESIZE_RETAIN(CCString*, _effectName, EffectName);
    virtual CCAction* getAction();
};

class GXPlayAudioEffectAction : public CCActionInstant {
    
public:
    
    GXPlayAudioEffectAction():
    effectName(NULL) {
        
    }
    
    ~GXPlayAudioEffectAction() {
        CC_SAFE_RELEASE_NULL(effectName);
    }
    
    static GXPlayAudioEffectAction* create(CCString* name);
    virtual void stop(void);
private:
    CCString* effectName;
};

#endif /* defined(__Dialog2__GXPlayAudioEffectCreator__) */
