//
//  GXAntiCrack.h
//  ww4
//
//  Created by xiao tang on 13-2-28.
//
//

#ifndef __ww4__GXAntiCrack__
#define __ww4__GXAntiCrack__

#include <iostream>
#include "cocos2d.h"

using namespace cocos2d;

class GXfloatValue : public CCObject{
    
public:
    static GXfloatValue* create(float _value);
    
    void setValue(float value);
    float getValue();
    
private:
    float value;
    int bValue;
    int UUID;
    
};

class GXintValue : public CCObject{
    
public:
    static GXintValue* create(int _value);
    
    void setValue(int value);
    int getValue();
    
protected:
    int value;
    int bValue;
    int UUID;
};

class GXunsignedlonglongValue : public CCObject{
    
public:
    static GXunsignedlonglongValue* create(unsigned long long _value);
    
    void setValue(unsigned long long value);
    unsigned long long getValue();
    
protected:
    unsigned long long value;
    unsigned long long bValue;
    int UUID;
};

class TestintValue : public GXintValue {
    
public:
    static TestintValue* create(int i);
    
    virtual void release();
    virtual void retain();
    
};

class TestUnsignedlonglongValue : public GXunsignedlonglongValue {
    
public:
    static TestUnsignedlonglongValue* create(int i);
    
    
};

#endif /* defined(__ww4__GXAntiCrack__) */
