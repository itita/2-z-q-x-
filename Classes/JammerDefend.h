//
//  JammerDefend.h
//  ww4
//
//  Created by xiao tang on 13-9-25.
//
//

#ifndef __ww4__JammerDefend__
#define __ww4__JammerDefend__

#include "DefendState.h"

class JammerDefend :public BeAttackState {
public:
    
    float damage;
    float attackRange;
    
    JammerDefend():
    maxTarget(7),
    damage(0),
    attackRange(0),
    sfxId(1),
    name(NULL),
    lightPool(NULL),
    toRemoveTargetArray(NULL),
    playjiange(0){
        
    }
    
    ~JammerDefend() {
        CC_SAFE_RELEASE_NULL(targetArray);
        CC_SAFE_RELEASE_NULL(name);
        CC_SAFE_RELEASE_NULL(lightPool);
        CC_SAFE_RELEASE_NULL(toRemoveTargetArray);
    }
    static JammerDefend* create(int _stateId,CCSprite* item,CCString* name,float life,float attackRange,float damage,float attackRate,int maxTarget,int sfxId);
//    virtual void attackTarget();
    //    virtual void init(MyBuilding* building);
    virtual void setItem(CCSprite* _item);
    virtual MyUnit* rangeTarget();
    virtual void doState();
    virtual void doEnd();
    void setMaxTarget(int targetCount) {
        maxTarget = targetCount;
    }
    
    CCString* name;
    char sfx[64];
private:
    int maxTarget;
    int sfxId;
    CCArray* targetArray;
    CCArray* lightPool;
    CCArray* toRemoveTargetArray;
    
    CCSprite* getLight();
    void returnLight(CCSprite* light);
    int playjiange;
};

#endif /* defined(__ww4__JammerDefend__) */
