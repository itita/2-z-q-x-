//
//  DefendState.h
//  ww2
//
//  Created by DingYu Fu on 12-9-9.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#ifndef ww2_DefendState_h
#define ww2_DefendState_h
#include "BeAttackState.h"
#include "MyUnit.h"
#include "GXAnimateWithFx.h"

typedef CCAnimate* (*SEL_FXCreator)(int);

class DefendState : public BeAttackState {
    
public:
    float damage;
    float attackRange;
//    float animateRate;
    virtual void doState();
    static DefendState* create(int _stateId,CCSprite* item,CCString* name,float life,float attackRange,float damage,float attackRate,int _sfxId);
    virtual void init(MyBattleBuilding* building);
    virtual MyUnit* rangeTarget();
    DefendState();
    virtual ~DefendState();
    virtual void setTarget(MyUnit* target);
    virtual void doEnd();
    virtual void attackTarget();
//    CCAnimation* fireAnimation[8];
    virtual void setAnimateCreator(SEL_FXCreator _animateCreator);
    char sfx[64];
    CCString* name;
protected:
    int sfxId;
    MyUnit* target;
    CCAnimate* animate[8];
    SEL_FXCreator animateCreator;
    inline CCAnimate* getFireAnimate(int dir) {
        if (animate[dir] == NULL) {
            animate[dir] = (*animateCreator)(dir);
            animate[dir]->retain();
        }
        return animate[dir];
    }
};

//class DefendStateCreator : public BeAttackStateCreator {
//    
//public:
//    DefendStateCreator();
//    float damage;
//    float attackRange;
//    const char* fireAnimationString;
//    
//    static DefendStateCreator* create();
//    virtual CCObject* init();
//};

#endif
