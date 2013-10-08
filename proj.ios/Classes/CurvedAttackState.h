//
//  CurvedAttackState.h
//  ww4
//
//  Created by xiao tang on 13-9-12.
//
//

#ifndef __ww4__CurvedAttackState__
#define __ww4__CurvedAttackState__

#include "AttackState.h"

class CurvedAttackState : public AttackState {
public:
    ~CurvedAttackState();
    virtual MyBattleBuilding* rangeTarget();
    //    void enemyInRange();
    static CurvedAttackState* create(int _stateId,CCString* _sfxFireName,float _attackRange,float damage,int _sfxId);
    
    
};

#endif /* defined(__ww4__CurvedAttackState__) */
