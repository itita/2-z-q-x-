//
//  MyBattleState.h
//  ww3
//
//  Created by xiao tang on 12-12-3.
//
//

#ifndef ww3_MyBattleState_h
#define ww3_MyBattleState_h

#include "GXFSMstate.h"
#include "MyBattleBuilding.h"

class MyBattleState :public GXFSMstate{
    
public:
    MyBattleState();
    MyBattleBuilding* building;
    virtual void doState();
    static MyBattleState* create(int _stateId,CCSprite* item,int doStateTime);
    virtual void init(MyBattleBuilding* building);
    virtual ~MyBattleState();
    virtual void setItem(CCSprite* item);
    virtual CCSprite* getItem();
    virtual float getArg0();
    float doStateTime;
protected:
    CCSprite* item;
    
};

#endif
