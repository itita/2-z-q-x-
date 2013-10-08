//
//  DepandOnZHSNormalState.h
//  ww4
//
//  Created by xiao tang on 13-5-1.
//
//

#ifndef __ww4__DepandOnZHSNormalState__
#define __ww4__DepandOnZHSNormalState__

#include <iostream>
#include "NormalState.h"

class DepandOnZHSNormalState : public NormalState {
    
public:
    ~DepandOnZHSNormalState() {
        CC_SAFE_RELEASE_NULL(spriteFileName);
    }
    DepandOnZHSNormalState():
    spriteFileName(NULL){
        
    }
    static DepandOnZHSNormalState* create(int _stateId,CCString* spriteFileName);
    virtual CCSprite* getItem();
private :
    CCString* spriteFileName;
};

#endif /* defined(__ww4__DepandOnZHSNormalState__) */
