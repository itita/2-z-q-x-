//
//  AoeAttackState.h
//  ww4
//
//  Created by xiao tang on 13-7-11.
//
//

#ifndef __ww4__AoeAttackState__
#define __ww4__AoeAttackState__

#include "AttackState.h"

class AoeAttackState : public AttackState {
    
public:
    AoeAttackState():splashRange(0) {
        
    }

    ~AoeAttackState() {
//        CCLog("~AoeAttackState has been release");
    }
    static AoeAttackState* create(int _stateId,CCString* _sfxFireName,float _attackRange,float damage,int _sfxId,float splashRange);
    virtual void attackTarget();
private:
    float splashRange;
    MyBattleBuilding* attackTargets[10];
    
};

#endif /* defined(__ww4__AoeAttackState__) */
