//
//  CollectState.h
//  ww3
//
//  Created by xiao tang on 12-10-13.
//
//

#ifndef ww3_CollectState_h
#define ww3_CollectState_h
#include "MyState.h"

class CollectState : public MyState {
    
public:
    CollectState(float _output,float _maxCapacity):
    capacity(0),
    isCollect(false),
    resourceTag(0),
    dt(0),
    zhuyeMenu(NULL)
    {
        outputPsecond = GXfloatValue::create(_output);
        outputPsecond->retain();
        baseOutputPsecond = GXfloatValue::create(_output);
        baseOutputPsecond->retain();
        maxCapacity = GXfloatValue::create(_maxCapacity);
        maxCapacity->retain();
        baseMaxCapacity = GXfloatValue::create(_maxCapacity);
        baseMaxCapacity->retain();
        capacity = GXfloatValue::create(0);
        capacity->retain();
    }
    
    ~CollectState() {
        CC_SAFE_RELEASE_NULL(outputPsecond);
        CC_SAFE_RELEASE_NULL(baseOutputPsecond);
        CC_SAFE_RELEASE_NULL(maxCapacity);
        CC_SAFE_RELEASE_NULL(baseMaxCapacity);
        CC_SAFE_RELEASE_NULL(capacity);
    }
    
    static CollectState* create(int _stateId, CCSprite* item,float output,float maxCapacity,int resourceTag);
    virtual void doState();
    virtual void init(MyBuilding* building);
    virtual void clickCallBack();
    virtual void dismissAllTransition();
    virtual void showAllTransition();
    
    float getCapacity() {return capacity->getValue(); }
    virtual void setCapacity(float _capacity,long dt);
    virtual void doStart();
//    virtual float getMaxCapacity();
    virtual float getBaseMaxCapacity();
//    virtual float getOutputPsecond();
    virtual float getBaseOutputPsecond();
    virtual void setMaxCapacity(float maxCapacity);
    virtual float getMaxCapacity();
//    virtual void setBaseCapacity();
    virtual void setOutputPsecond(float outputPsecond);
//    virtual void setBaseOutputPsecond();
    bool checkCollect();
    
    void doCollectPlaysfx();
    void doCollectCheckCapacity();
    int getResourceTag() {return resourceTag;};
private:
    int resourceTag;
    int dt;
    GXfloatValue* outputPsecond;
    GXfloatValue* maxCapacity;
    GXfloatValue* capacity;
    GXfloatValue* baseMaxCapacity;
    GXfloatValue* baseOutputPsecond;
    bool isCollect;
    void doCollect();
    CCMenu* zhuyeMenu;
    
    
};

//class CollectStateCreator : public MyStateCreator {
//    
//public:
//    CollectStateCreator():
//    resourceTag(0),
//    outputPsecond(0),
//    maxCapacity(0){}
//    
//    int resourceTag;
//    float outputPsecond;
//    float maxCapacity;
//    
//    static CollectStateCreator* create();
//    virtual CCObject* init();
//};

#endif
