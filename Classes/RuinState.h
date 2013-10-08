//
//  RuinState.h
//  ww3
//
//  Created by xiao tang on 12-10-28.
//
//

#ifndef ww3_RuinState_h
#define ww3_RuinState_h
#include "NormalState.h"

class RuinState :public NormalState{
    
public:
    RuinState():currentId(0) {}
    static RuinState* create(int _stateId,CCSprite* item);
    int currentId;
//    virtual void doStart();
    virtual void setCurrentId(int id);
    
};

//class RuinStateCreator : public NormalStateCreator {
//    
//public:
//    
//    static RuinStateCreator* create();
//    virtual CCObject* init();
//    
//};

#endif
