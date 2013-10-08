//
//  GarbageCollectionState.h
//  ww4
//
//  Created by xiao tang on 13-5-24.
//
//

#ifndef __ww4__GarbageCollectionState__
#define __ww4__GarbageCollectionState__

#include "MyBattleState.h"
#include "DefineSet.h"



class GarbageCollectionState : public MyBattleState {
    
public:
    
    ~GarbageCollectionState() {
    }
    GarbageCollectionState():
    resourceCount(0){}
    
    static GarbageCollectionState* create(int _stateId,CCSprite* item,int resourceCount);
    
    virtual void addResource(int resourceCount);
    
    virtual float getArg0();
    
    int resourceCount;
    
private:
    
};

#endif /* defined(__ww4__GarbageCollectionState__) */
