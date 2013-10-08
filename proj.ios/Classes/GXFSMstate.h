//
//  GXFSMstate.h
//  ww2
//
//  Created by DingYu Fu on 12-9-1.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#ifndef ww2_GXFSMstate_h
#define ww2_GXFSMstate_h
#include "cocos2d.h"
#define ccint(_int) CCInteger::create(_int)
//#define getIntAndDelete(_pint) _pint->getAndDelete()

using namespace cocos2d;

class GXFSMstate : public cocos2d::CCObject{
    
//    int* inputs;
//    int* outputs;
    
    
public:
    static GXFSMstate* create(int _stateId);
//    GXFSMstate(int _stateId);
    virtual ~GXFSMstate();
    int getId() {return stateId;};
    virtual void addTransition(int inputId,int ioutputId);
    virtual void deleteTransition(int outputId);
    virtual CCArray* getAllInput();
    virtual CCInteger* getOutPut(int inputId);
//    virtual void release();
//    virtual void retain();
    virtual void doState();
    virtual void doStart();
    virtual void doEnd();
    
    
    int stateId;
protected:
    cocos2d::CCDictionary* input_output;
};


#endif
