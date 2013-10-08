//
//  Mathlib.cpp
//  ww2
//
//  Created by DingYu Fu on 12-8-23.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "Mathlib.h"
#include "cocos2d.h"
#include "math.h"

using namespace cocos2d;


bool Mathlib::inBound(float value, float up,float low) {
    return (value>=low) && (value<=up);
}

bool Mathlib::inBoundInt(int value, int up,int low) {
    return (value>=low) && (value<=up);
}

float Mathlib::bound(float value, float up, float low){
    if (value > up) {
        value = up;
    }
    if (value <= low) {
        value = low;
    }
    return value;
}

int Mathlib::boundInt(int value, int up, int low){
    if (value > up) {
        value = up;
    }
    if (value <= low) {
        value = low;
    }
    return value;
}

float Mathlib::max(float a,float b) {
    return a>b?a:b;
}

float Mathlib::min(float a,float b) {
    return a<b?a:b;
}

int Mathlib::getGcd(int a,int b) {
    while(b != 0)
    {
        int r = b;
        b = a % b;
        a = r;
    }
    return a;
}

CCPoint Mathlib::getGlobalPosition(CCNode* pNode) {
    CCNode* parent = pNode->getParent();
    float x=pNode->getPosition().x;
    float y=pNode->getPosition().y;
    while (parent != NULL) {
        x = x + parent->getPosition().x;
        y = y + parent->getPosition().y;
        parent = parent->getParent();
    }
    return ccp(x,y);
}

CCPoint Mathlib::roundPoint(const cocos2d::CCPoint &point) {
    int x = (int)(point.x+0.5);
    int y = (int)(point.y+0.5);
    return ccp(x,y);
}

float Mathlib::getDistance(const cocos2d::CCPoint &point1, const cocos2d::CCPoint &point2){
    return sqrt((point1.x-point2.x)*(point1.x-point2.x) + (point1.y-point2.y)*(point1.y-point2.y));
}

float Mathlib::getAngle(const CCPoint& point1,const CCPoint& point2) {
//    atan2f(<#float#>, <#float#>)
    return atan2f(point2.x-point1.x,point2.y-point1.y);
}

int Mathlib::getEightDirection(const CCPoint& base ,const CCPoint& target) {
    float angle = Mathlib::getAngle(base, target);
    int dir = (((int)(angle*180/3.141592654+22.5)+360)%360)/45; 
    return dir;
}


float Mathlib::absFloat(float x) {
    if (x< 0) {
        x = -x;
    }
    return x;
}

int Mathlib::intToZero(float x) {
    if (x>0) {
        return (int)x;
    }
    return (int)(x+1);
}

bool Mathlib::collisionCheck(const CCSize& size,const CCPoint& spoint ,float range,const CCPoint& rpoint) {
    if (size.width == size.height) {
        return Mathlib::getDistance(spoint,rpoint) <= range+size.width/2;
    } else {
        return (absFloat(spoint.x - rpoint.x) <=range+size.width/2) && (absFloat(spoint.y - rpoint.y) <= range+size.height/2);
    }
}

int Mathlib::abs(int a) {
    if(a<0) {
        return -a;
    } else {
        return a;
    }
}
