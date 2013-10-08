//
//  GXFSMclass.h
//  ww2
//
//  Created by DingYu Fu on 12-9-1.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#ifndef ww2_GXFSMclass_h
#define ww2_GXFSMclass_h

#include "GXFSMstate.h"
#include "cocos2d.h"

using namespace cocos2d;

//class GXFSMclass : cocos2d::CCObject {
//    cocos2d::CCDictionary* map;
//    GXFSMstate* currentState;
//    
//}


class GXFSM : public cocos2d::CCObject{
    
    GXFSMstate* currentState; //当前stateID
    
public:
    //设置初始化state
    
    cocos2d::CCDictionary* stateMap; //保存全部的state
    
    static GXFSM* create(GXFSMstate* c_state);
    
    GXFSM(GXFSMstate* c_state);
    
    GXFSM();
    
    virtual ~GXFSM();
    
    GXFSMstate* getCurrentState() {return currentState;};
    
    virtual void setCurrentState(GXFSMstate* _c_state);
    
    //  取出某种状态。
    virtual GXFSMstate* getState(int iStateId);
    
    virtual void addState(GXFSMstate* pState);
    
    virtual void deleteState(int iStateId);
    
    //通过输入号来启动State，返回输出;
    virtual CCInteger* stateTransition(int input);
    
//    virtual void release();
//    
//    virtual void retain();
    
    CCArray* getAllState();

};

#endif
