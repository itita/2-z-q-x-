//
//  MyAtlasNumber.cpp
//  ww3
//
//  Created by xiao tang on 12-10-17.
//
//

#include "MyAtlasNumber.h"
#include "DefineSet.h"
#include "Mathlib.h"
MyAtlasNumber* MyAtlasNumber::create() {
    MyAtlasNumber *pRet = new MyAtlasNumber();
    if(pRet && pRet->initWithString("0", "number3.png", 18, 24, '.'))
    {
        pRet->autorelease();
        pRet->targetNumber = GXfloatValue::create(0);
        pRet->targetNumber->retain();
//        pRet->bufferStr = "0";
//        pRet->bufferStr = new char[10];
        return pRet;
    }
    CC_SAFE_DELETE(pRet);
    return NULL;
}

void MyAtlasNumber::setNumber(float number) {
    if (!isSchedule) {
        schedule(schedule_selector(MyAtlasNumber::flushNumber),0.02);
        isSchedule = true;
    }
    setTargetNumber(number);
}

void MyAtlasNumber::flushNumber() {
    if(getTargetNumber() - getNowNumber() > limit) {
        setNowNumber(getNowNumber()+Mathlib::max((getTargetNumber() - getNowNumber())/5,limit));
//        nowNumber+=Mathlib::max((targetNumber - nowNumber)/5,1);
        if(getNowNumber()>=0) {
            sprintf(bufferStr, "%d",(int)getNowNumber());
        } else {
            sprintf(bufferStr, "/%d",(int)getNowNumber()*-1);
        }
        setString(bufferStr);
    } else if(getTargetNumber() - getNowNumber() < -1*limit){
        setNowNumber(getNowNumber()+Mathlib::min((getTargetNumber() - getNowNumber())/5,-1*limit));
//        sprintf(bufferStr, "%d",getNowNumber());
        if(getNowNumber()>=0) {
            sprintf(bufferStr, "%d",(int)getNowNumber());
        } else {
            sprintf(bufferStr, "/%d",(int)getNowNumber()*-1);
        }
        setString(bufferStr);
    } else  {
        setNowNumber(getTargetNumber());
//        nowNumber = targetNumber;
//        sprintf(bufferStr, "%d",getNowNumber());
        if(getNowNumber()>=0) {
            sprintf(bufferStr, "%d",(int)getNowNumber());
        } else {
            sprintf(bufferStr, "/%d",(int)getNowNumber()*-1);
        }
        setString(bufferStr);
        unschedule(schedule_selector(MyAtlasNumber::flushNumber));
        isSchedule = false;
    }
}

void MyAtlasNumber::setNumberNoFx(float number) {
    if (isSchedule) {
        unschedule(schedule_selector(MyAtlasNumber::flushNumber));
        isSchedule = false;
    }
    setTargetNumber(number);
    setNowNumber(number);
//    sprintf(bufferStr, "%d",getNowNumber());
    if(getNowNumber()>=0) {
        sprintf(bufferStr, "%d",(int)getNowNumber());
    } else {
        sprintf(bufferStr, "/%d",(int)getNowNumber()*-1);
    }
    setString(bufferStr);
}

void MyAtlasNumber::pauseSchedulerAndActions() {
    CCLabelAtlas::pauseSchedulerAndActions();
}

void MyAtlasNumber::cleanup() {
    CCLabelAtlas::cleanup();
    char str[10] = {0};
//    sprintf(str, "%d",(int)getTargetNumber());
    if(getTargetNumber()>=0) {
        sprintf(str, "%d",(int)getTargetNumber());
    } else {
        sprintf(str, "/%d",(int)getTargetNumber()*-1);
    }
    this->setString(str);
    this->setNowNumber(getTargetNumber());
    isSchedule = false;
}

MyAtlasNumber::~MyAtlasNumber() {
//    CCLog("MyAtlasNumber released");
    CC_SAFE_RELEASE_NULL(targetNumber);
}

void MyAtlasNumber::setTargetNumber(float number){
    targetNumber->setValue(number);
    if (number>100000) {
        limit = 10;
    } else if(number < -100000) {
        limit = 10;
    } else {
        limit = 1;
    }
}

int MyAtlasNumber::getNowNumber() {
    return nowNumber;
}

void MyAtlasNumber::setNowNumber(int _nowNumber){
    nowNumber =  _nowNumber;
}

float MyAtlasNumber::getTargetNumber() {
    return targetNumber->getValue();
}