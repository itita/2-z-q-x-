//
//  ResourceOnlyBeRobberState.h
//  ww3
//
//  Created by xiao tang on 12-11-17.
//
//

#ifndef ww3_ResourceOnlyBeRobberState_h
#define ww3_ResourceOnlyBeRobberState_h

#include "BeAttackState.h"

class ResourceOnlyBeRobberState :public BeAttackState {
    
public:
    
    
    ResourceOnlyBeRobberState():
    oil(0),
    iron(0),
    nowOil(0),
    robberOil(0),
    nowIron(0),
    robberIron(0)
    {}
    
    static ResourceOnlyBeRobberState* create(int _stateId, CCSprite *item, float life);
    virtual bool beAttack(float damage);
    virtual void setOil(float oil);
    virtual void setIron(float iron);
    virtual float getOil();
    virtual float getIron();
private:
    float nowOil;
    float robberOil;
    float nowIron;
    float robberIron;
    float oil;
    float iron;
    
};

#endif
