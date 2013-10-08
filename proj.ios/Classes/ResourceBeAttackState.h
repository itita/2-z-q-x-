//
//  ResourceBeAttackState.h
//  ww3
//
//  Created by xiao tang on 12-10-26.
//
//

#ifndef ww3_ResourceBeAttackState_h
#define ww3_ResourceBeAttackState_h
#include "BeAttackState.h"

class ResourceBeAttackState : public BeAttackState {
    
public:
    ResourceBeAttackState():
    resourceTag(0),
    capacity(0),
    outputPsecond(0),
    maxCapacity(0),
    nowResource(0),
    robberResource(0),
    trophyRate(0.5){}
    
    int resourceTag;
    virtual void setCapacity(float _capacity,long dt,float rate);
    virtual float getCapacity();
    virtual float getLastCapacity();
    static ResourceBeAttackState* create(int _stateId, CCSprite *item, float life,float output,float maxCapacity,int resourceTag);
    virtual bool beAttack(float damage);
    virtual void beRobberResource(float num);
    virtual float getBaseMaxCapacity();
    virtual float getBaseOutputPsecond();
    virtual void setMaxCapacity(float maxCapacity);
    virtual void setOutputPsecond(float outputPsecond);
    virtual float getArg0();
protected:
    float nowResource;
    float capacity;
    float outputPsecond;
    float maxCapacity;
    float robberResource;
    float baseMaxCapacity;
    float baseOutputPsecond;
    float trophyRate;
    
    
    
};

//class ResourceBeAttackStateCreator :public BeAttackStateCreator {
//    
//public:
//    float life;
//    float output;
//    float maxCapacity;
//    int resourceTag;
//    
//    ResourceBeAttackStateCreator():
//    life(0),
//    maxCapacity(0),
//    resourceTag(0),
//    output(0)
//    {}
//    
//    static ResourceBeAttackStateCreator* create();
//    virtual CCObject* init();
//};

#endif
