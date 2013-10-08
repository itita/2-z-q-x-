//
//  CellarProtectState.h
//  ww4
//
//  Created by xiao tang on 13-7-8.
//
//

#ifndef __ww4__CellarProtectState__
#define __ww4__CellarProtectState__

#include <iostream>
#include "MyBattleState.h"

class CellarProtectState : public MyBattleState {
    
public:
    
    ~CellarProtectState(){
        CCLog("CellarProtectState has been released");
    }
    
    CellarProtectState():
    protectCount(0){
    }
    static CellarProtectState* create(int _stateId,CCSprite* item,float _protectCount);
    float protectCount;
    virtual float getArg0();
    virtual void doStart();

};

#endif /* defined(__ww4__CellarProtectState__) */
