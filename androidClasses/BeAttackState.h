//
//  BeAttackState.h
//  ww2
//
//  Created by DingYu Fu on 12-9-9.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#ifndef ww2_BeAttackState_h
#define ww2_BeAttackState_h
#include "MyState.h"
#include "MyXueTiao.h"
#include "MyBattleState.h"

class BeAttackState : public MyBattleState,public IbeAttack {
    
public:
    
    BeAttackState():
    xuetiao(NULL){}
    
    MyXueTiao* xuetiao;
    virtual void doState();
    static BeAttackState* create(int _stateId,CCSprite* item,float life);
    virtual void init(MyBattleBuilding* building);
    virtual ~BeAttackState();
    virtual bool beAttack(float damage);

};

//class BeAttackStateCreator : public MyStateCreator {
//    
//public:
//    BeAttackStateCreator();
//    float life;
//    static BeAttackStateCreator* create();
//    virtual CCObject* createObj();
//    
//};

#endif
