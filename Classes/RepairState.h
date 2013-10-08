//
//  RepairState.h
//  ww4
//
//  Created by xiao tang on 13-3-31.
//
//

#ifndef __ww4__RepairState__
#define __ww4__RepairState__

#include <iostream>
#include "MyState.h"

class RepairState : public MyState {
    
public:
    
    ~RepairState()
    {
        CCLog("RepairCallBack has released");
    }
    RepairState():
    targetTag(-1){
    }
    static RepairState* create(int _stateId,int targetTag,CCSprite* item);
    virtual void changeIdCallBack(CCMenuItem* pSender);
    virtual void init(MyBuilding* building);
    void RepairCallBack(cocos2d::CCObject *pSender);
private:
    int targetTag;
};

#endif /* defined(__ww4__RepairState__) */
