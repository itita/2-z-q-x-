//
//  DefendInCreateState.h
//  ww4
//
//  Created by xiao tang on 13-8-17.
//
//

#ifndef __ww4__DefendInCreateState__
#define __ww4__DefendInCreateState__

#include <iostream>
#include "NormalState.h"

class DefendInCreateState : public NormalState {
    
public:
    DefendInCreateState():
    attackRange(0){
    
    }
    
    ~DefendInCreateState() {
//        CCLog("DefendInCreateState");
    }
    static DefendInCreateState* create(int _stateId,CCSprite* item);
    void setAttackRange(float _attackRange);
    virtual void dismissAllTransition();
    virtual void showAllTransition();
    
private:
    float attackRange;
};

#endif /* defined(__ww4__DefendInCreateState__) */
