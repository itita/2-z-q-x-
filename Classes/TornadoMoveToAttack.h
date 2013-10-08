//
//  TornadoMoveToAttack.h
//  ww4
//
//  Created by xiao tang on 13-9-4.
//
//

#ifndef __ww4__TornadoMoveToAttack__
#define __ww4__TornadoMoveToAttack__

#include "RobotMoveToAttack.h"

class TornadoMoveToAttack : public RobotMoveToAttack {
    
public:
    static TornadoMoveToAttack* create(int _stateId,float _speed,float animateRate,float _attackRange);
    MyBattleBuilding* searchTarget();
};

#endif /* defined(__ww4__TornadoMoveToAttack__) */
