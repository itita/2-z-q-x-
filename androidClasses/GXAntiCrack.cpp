//
//  GXAntiCrack.cpp
//  ww4
//
//  Created by xiao tang on 13-2-28.
//
//

#include "GXAntiCrack.h"

GXfloatValue* GXfloatValue::create(float _value) {
    GXfloatValue* fValue = new GXfloatValue();
    fValue->autorelease();
    fValue->value = _value;
    fValue->UUID = arc4random()%10000;
    fValue->bValue = (~(int)_value)^fValue->UUID;
    
    return fValue;
}

void GXfloatValue::setValue(float _value) {
    if ((int)this->value == (~(this->bValue^this->UUID))) {
        this->value = _value;
        this->bValue = (~(int)_value)^this->UUID;
    } else {
        CCLog("float cheat has been search");
        CCDirector::sharedDirector()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
        exit(0);
#endif
        return;
    }
}

float GXfloatValue::getValue() {
    if ((int)this->value == (~(this->bValue^this->UUID))) {
        return this->value;
    } else {
        CCLog("float cheat has been search");
        CCDirector::sharedDirector()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
        exit(0);
#endif
        return 0;
    }
}

GXintValue* GXintValue::create(int _value) {
    GXintValue* iValue = new GXintValue();
    iValue->autorelease();
    iValue->value = _value;
    iValue->UUID = arc4random()%10000;
    iValue->bValue = (~_value)^iValue->UUID;
    return iValue;
}

void GXintValue::setValue(int _value) {
    if (this->value == (~(this->bValue^this->UUID))) {
        this->value = _value;
        this->bValue = (~_value)^this->UUID;
    } else {
        CCLog("INT cheat has been search");
        CCDirector::sharedDirector()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
        exit(0);
#endif
        return;
    }
}

int GXintValue::getValue() {
    if (this->value == (~(this->bValue^this->UUID))) {
        return this->value;
    } else {
        
        CCLog("INT cheat has been search");
        CCDirector::sharedDirector()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
        exit(0);
#endif
        return 0;
    }
}

GXunsignedlonglongValue* GXunsignedlonglongValue::create(unsigned long long _value) {
    GXunsignedlonglongValue* iValue = new GXunsignedlonglongValue();
    iValue->autorelease();
    iValue->value = _value;
    iValue->UUID = arc4random()%1000000;
    iValue->bValue = (~_value)^iValue->UUID;
    return iValue;
}

void GXunsignedlonglongValue::setValue(unsigned long long  _value) {
    if (this->value == (~(this->bValue^this->UUID))) {
        this->value = _value;
        this->bValue = (~_value)^this->UUID;
    } else {
        CCLog("LONGLONG cheat has been search");
        CCDirector::sharedDirector()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
        exit(0);
#endif
        return;
    }
}

unsigned long long GXunsignedlonglongValue::getValue() {
    if (this->value == (~(this->bValue^this->UUID))) {
        return this->value;
    } else {
        
        CCLog("LONGLONG cheat has been search");
        CCDirector::sharedDirector()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
        exit(0);
#endif
        return 0;
    }
}

TestintValue* TestintValue::create(int _value) {
    TestintValue* iValue = new TestintValue();
    iValue->value = _value;
    iValue->UUID = arc4random()%10000;
    iValue->bValue = (~_value)^iValue->UUID;
    return iValue;
}

void TestintValue::release() {
    CCObject::release();
    CCLog("release:%d",m_uReference);
}

void TestintValue::retain() {
    CCObject::retain();
     CCLog("retain:%d",m_uReference);
}

TestUnsignedlonglongValue* TestUnsignedlonglongValue::create(int _value) {
    TestUnsignedlonglongValue* iValue = new TestUnsignedlonglongValue();
    iValue->value = _value;
    iValue->UUID = arc4random()%1000000;
    iValue->bValue = (~_value)^iValue->UUID;
    return iValue;
}