//
//  GarbageCollectionNormalState.h
//  ww4
//
//  Created by xiao tang on 13-5-24.
//
//

#ifndef __ww4__GarbageCollectionNormalState__
#define __ww4__GarbageCollectionNormalState__

#include "MyState.h"

class GarbageCollectionNormalState : public MyState {
    
public:
    ~GarbageCollectionNormalState() {
        CCLog("GarbageCollectionNormalState");
    }
    GarbageCollectionNormalState():
    resourceCount(0),
    isDestroy(false){
    }
    static GarbageCollectionNormalState* create(int _stateId,CCSprite* item,int resourceCount);
    virtual void clickCallBack();
    int doCollect(float rate);
    long resourceCount;
    void doState();
    bool isDestroy;
private:
    
    
};

#endif /* defined(__ww4__GarbageCollectionNormalState__) */
