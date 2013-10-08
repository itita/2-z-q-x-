//
//  TornadoAttack.h
//  ww4
//
//  Created by xiao tang on 13-9-3.
//
//

#ifndef __ww4__TornadoAttack__
#define __ww4__TornadoAttack__

#include "AttackState.h"

class TornadoAttack : public AttackState  {
    
public:
    TornadoAttack():
    splashRange(0),
    speed(0),
    attackTargets(NULL){
        
    }
    
    ~TornadoAttack() {
        CC_SAFE_RELEASE_NULL(attackTargets);
    }
    static TornadoAttack* create(int _stateId,CCString* _sfxFireName,float _attackRange,float damage,int _sfxId,float splashRange,float speed);
    virtual void attackTarget();
    virtual MyBattleBuilding* rangeTarget();
    virtual void doState();
//    virtual void doNext();
private:
    float speed;
    float splashRange;
    CCArray* attackTargets;
};

#endif /* defined(__ww4__TornadoAttack__) */
