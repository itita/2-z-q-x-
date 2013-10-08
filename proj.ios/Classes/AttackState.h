//
//  AttackState.h
//  ww2
//
//  Created by DingYu Fu on 12-9-8.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#ifndef ww2_AttackState_h
#define ww2_AttackState_h
#include "MyBattleBuilding.h"
#include "MyUnitState.h"
#include "MyUnit.h"

class AttackState : public MyUnitState {
public:
    AttackState():
    attackRange(0),
    damage(0),
    target(NULL),
    sfxFireName(NULL),
    sfxId(1)
    {
    }
    ~AttackState();
    virtual MyBattleBuilding* rangeTarget();
    float attackRange;
    float damage;
//    void enemyInRange();
    static AttackState* create(int _stateId,CCString* _sfxFireName,float _attackRange,float damage,int _sfxId);
    virtual void doState();
    virtual void init(MyUnit* unit);
    virtual void attackTarget();
    virtual void setTarget(MyBattleBuilding *_target);
    virtual void doEnd();
    virtual void doStart();
//    virtual void doNext();
protected:
    MyBattleBuilding* target;
    CCString* sfxFireName;
    int sfxId;
    
};




#endif
