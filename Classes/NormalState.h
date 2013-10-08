//
//  NormalState.h
//  ww2
//
//  Created by DingYu Fu on 12-9-14.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#ifndef ww2_NormalState_h
#define ww2_NormalState_h
#include "MyState.h"

class NormalState : public MyState{
    
public:
//    virtual void doState();
    static NormalState* create(int _stateId,CCSprite* item);
    virtual void init(MyBuilding* building);
//    virtual void clickCallBack();
//    virtual void changeIdCallBack(CCObject* pSender);
//    virtual void sellCallBack(CCObject* pSender);
    virtual void setItem(CCSprite* item);
    
};

//class NormalStateCreator : public MyStateCreator{
//    
//public:
//    NormalStateCreator(){}
//    static NormalStateCreator* create();
//    virtual CCObject* createObj();
//    
//};

#endif
