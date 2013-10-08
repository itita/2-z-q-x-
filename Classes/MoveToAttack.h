//
//  MoveToAttack.h
//  ww2
//
//  Created by DingYu Fu on 12-9-7.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#ifndef ww2_MoveToAttack_h
#define ww2_MoveToAttack_h
#include "MyUnitState.h"
#include "MyBattleBuilding.h"

class MoveToAttack : public MyUnitState {
public:
    virtual ~MoveToAttack();
    
    virtual MyBattleBuilding* searchTarget();
    float attackRange;
    float speed;
    virtual bool enemyInRange();
    static MoveToAttack* create(int _stateId,float _speed,float _attackRange);
    virtual void doState();
    virtual void init(MyUnit* unit);
    virtual void setTarget(MyBattleBuilding* target);
    virtual void doEnd();
//    virtual void setUnit(MyUnit* unit);
protected:
    MyBattleBuilding* target;
    virtual void moveToTarget();
//    MyBattleBuilding* getLatestBuilding
};

#endif
