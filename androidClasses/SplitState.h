//
//  SplitState.h
//  ww4
//
//  Created by xiao tang on 13-4-7.
//
//

#ifndef __ww4__SplitState__
#define __ww4__SplitState__

#include <iostream>
#include "MyState.h"

class SplitState : public MyState {
    
public:
    ~SplitState() {
//        CCLog("SplitState has been release");
    }
    SplitState(){
    }
    virtual void doState();
    static SplitState* create(int _stateId,CCSprite* item,int _splitBuildingTag);
    virtual void init(MyBuilding* building);
    virtual void toSplitCallBack(CCMenuItem* pSender);
    virtual void setItem(CCSprite* item);

private:
    int splitBuildingTag;
    
};

#endif /* defined(__ww4__SplitState__) */
