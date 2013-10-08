//
//  AoeDefendState.h
//  ww2
//
//  Created by DingYu Fu on 12-9-23.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#ifndef ww2_AoeDefendState_h
#define ww2_AoeDefendState_h
#include "DefendState.h"

class AoeDefendState : public DefendState{
    
public:
    virtual ~AoeDefendState();
    static AoeDefendState* create(int _stateId,CCSprite* item,CCString* name,float life,float attackRange,float damage,float _splashRange,float attackRate,int sfxId);
    virtual void attackTarget();
//    virtual void init(MyBuilding* building);
    virtual void setItem(CCSprite* _item);
    virtual MyUnit* rangeTarget();

protected:
    float splashRange;
};

//class AoeDefendStateCreator : public DefendStateCreator{
//    
//public:
//    float splashRange;
//    AoeDefendStateCreator():
//    splashRange(0){}
//    
//    static AoeDefendStateCreator* create();
//    virtual CCObject* init();
//    
//};

#endif
