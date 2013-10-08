//
//  MyBaseTrigger.h
//  ww3
//
//  Created by xiao tang on 12-12-14.
//
//

#ifndef ww3_MyBaseTrigger_h
#define ww3_MyBaseTrigger_h

#include "cocos2d.h"
#include "MyBaseMessage.h"


using namespace cocos2d;

class MyBaseTrigger : public CCObject {
    
public:
    virtual bool excuteMsg(MyBaseMessage* msg) = 0;
    virtual bool onRegist() = 0;
    virtual bool onUnRegist() = 0;
};

#endif
