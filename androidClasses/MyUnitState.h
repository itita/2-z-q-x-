//
//  MyUnitState.h
//  ww2
//
//  Created by DingYu Fu on 12-9-5.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#ifndef ww2_MyUnitState_h
#define ww2_MyUnitState_h
#include "GXFSMstate.h"
#include "MyBattleMap.h"

class MyUnitState :public GXFSMstate {
public:
//    MyBattleMap* map;
    MyUnitState();
    MyUnit* unit;
    static MyUnitState* create(int _stateId);
    virtual void doState(); 
    virtual void init(MyUnit* unit);
//    virtual ~MyUnitState();
    
};

#endif
