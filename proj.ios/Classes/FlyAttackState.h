//
//  FlyAttackState.h
//  ww4
//
//  Created by xiao tang on 13-5-11.
//
//

#ifndef __ww4__FlyAttackState__
#define __ww4__FlyAttackState__

#include "AttackState.h"

class FlyAttackState : public AttackState {
public:
    ~FlyAttackState();
    virtual MyBattleBuilding* rangeTarget();
    //    void enemyInRange();
    static FlyAttackState* create(int _stateId,CCString* _sfxFireName,float _attackRange,float damage,int _sfxId);

    
};



#endif /* defined(__ww4__FlyAttackState__) */
