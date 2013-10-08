//
//  MyAtlasNumber.h
//  ww3
//
//  Created by xiao tang on 12-10-17.
//
//

#ifndef ww3_MyAtlasNumber_h
#define ww3_MyAtlasNumber_h
#include "cocos2d.h"
#include "DefineSet.h"
#include "GXAntiCrack.h"

using namespace cocos2d;

class MyAtlasNumber :public CCLabelAtlas{
    
public:
    
    MyAtlasNumber():
    targetNumber(0),
    nowNumber(0),
    isSchedule(false),
    limit(1){}
    virtual ~MyAtlasNumber();
    static MyAtlasNumber* create();
    void setNumber(float number);
    virtual void setNowNumber(int _nowNumber);
//    {
//        nowNumber = INT_MAX - _nowNumber;
//    }
    virtual void pauseSchedulerAndActions();
    virtual void cleanup();
    virtual void setNumberNoFx(float number);
    virtual float getTargetNumber();
    
    
private:
    virtual void setTargetNumber(float number);
    virtual int getNowNumber();
    
    void flushNumber();
    int nowNumber;
    int limit;
    GXfloatValue* targetNumber;
    bool isSchedule;
    char bufferStr[20];
};

#endif
