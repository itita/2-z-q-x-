//
//  RobotMoveToAttack.h
//  ww4
//
//  Created by xiao tang on 13-9-3.
//
//

#ifndef __ww4__RobotMoveToAttack__
#define __ww4__RobotMoveToAttack__

#include "MoveToAttack.h"

class RobotMoveToAttack : public MoveToAttack {
    
public: 
    RobotMoveToAttack():
    animateRate(0) {
    
    }
    static RobotMoveToAttack* create(int _stateId,float _speed,float animateRate,float _attackRange);
//    virtual bool enemyInRange();
    
protected:
    virtual void moveToTarget();
    float animateRate;
};


#endif /* defined(__ww4__RobotMoveToAttack__) */
