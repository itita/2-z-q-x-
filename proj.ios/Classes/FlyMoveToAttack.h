//
//  FlyMoveToAttack.h
//  ww4
//
//  Created by xiao tang on 13-5-11.
//
//

#ifndef __ww4__FlyMoveToAttack__
#define __ww4__FlyMoveToAttack__

#include <iostream>
#include "FlyMoveToAttack.h"
#include "MoveToAttack.h"

class FlyMoveToAttack : public MoveToAttack {
    
public:
    ~FlyMoveToAttack();
    static FlyMoveToAttack* create(int _stateId,float _speed,float _attackRange);
    virtual bool enemyInRange();
    virtual MyBattleBuilding* searchTarget();
};

#endif /* defined(__ww4__FlyMoveToAttack__) */
