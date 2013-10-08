//
//  MyUnit.h
//  ww2
//
//  Created by DingYu Fu on 12-9-4.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//


#ifndef ww2_MyUnit_h
#define ww2_MyUnit_h
#include "cocos2d.h"
#include "GXFSMclass.h"
#include "AliveInterface.h"
#include "IbeAttack.h"
#include "GXCreator.h"
#include "DefineSet.h"
#include "GXantiCrack.h"

#define currentActionTag 10
#define MoveToAttackTag 100
#define toAttackTransition 101
#define AttackStateTag 102
#define toMoveTransition 103

#define groundMode 0
#define airMode 1
#define soldier 2
#define lightVehicles 3
#define heavyVehicles 4
#define special 5

using namespace cocos2d;

typedef CCAnimate* (*SEL_UnitFXCreator)(int);


class MyUnit :public cocos2d::CCSprite ,public AliveInterface,public IbeAttack{
public:
    MyUnit():
    fsm(NULL),
    dir(-1),
    fxCount(0), 
    mode(groundMode),
    level(1),
    moveAnimateCreator(NULL),
    fireAnimateCreator(NULL),
    dieAnimateCreator(NULL),
    die(NULL),
    bufferState(0){
        for (int i=0; i<8 ; i++) {
            move[i] =NULL;
            fire[i] =NULL;
//            die[i] = NULL;
        }
    }
    
    virtual ~MyUnit();
    GXFSM* fsm;
    CCAnimate* move[8];
    CCAnimate* fire[8];
    CCAnimate* die;
    int dir;
    int fxCount;
//    float speed;
    static MyUnit* create(GXFSMstate *state,float life,float aiRate,int level);
    virtual void runMoveAnimate(int direction);
    virtual CCAnimate* runFireAnimate(int direction);
    virtual CCAnimate* runDisposeAnimate();
    virtual void doAI();
    virtual void changeState(int inputId);
    virtual void addState(GXFSMstate* state);
    virtual bool setLife(float life);
    virtual void disposeNoFx();
    virtual void dispose();
//    virtual void retain();
//    virtual void release();
    
    SEL_UnitFXCreator moveAnimateCreator;
    SEL_UnitFXCreator fireAnimateCreator;
    SEL_UnitFXCreator dieAnimateCreator;
    
    float aiRate;
    int cost;
    CCPoint deployPosi;
    int mode;
    int bufferState;
    
    int getLevel() {
        return level;
    }
private:
    virtual void removeThis();
    int level;
};



//class UnitFXCreator : public CCObject {
//    
//public:
//    ~UnitFXCreator() {
//        CC_SAFE_RELEASE_NULL(actionName);
//        CC_SAFE_RELEASE_NULL(fxname);
//    }
//    
//    UnitFXCreator():
//    actionName(NULL),
//    dir(0),
//    startFrameCount(0),
//    fxname(NULL),
//    posX(0),
//    posY(0),
//    scale(1),
//    zOrder(0){
//    }
//    
//    static UnitFXCreator* create();
//    
//    int dir;
//    int startFrameCount;
//    float posX;
//    float posY;
//    float scale;
//    int zOrder;
//    
//    CC_SYNTHESIZE_RETAIN(CCString*,fxname,Fxname);
//    CC_SYNTHESIZE_RETAIN(CCString*,actionName,ActionName);
//};

//class <#class name#> {
//    <#instance variables#>
//    
//public:
//    <#member functions#>
//};


//class unitCreator {
//public:
//    
//    virtual MyUnit* creatUnit();
//
//};

#endif
