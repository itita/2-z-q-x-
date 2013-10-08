//
//  Header.h
//  ww2
//
//  Created by DingYu Fu on 12-8-23.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#ifndef ww2_Header_h
#define ww2_Header_h

#include "cocos2d.h"
using namespace cocos2d;

class Mathlib {
public:
    static bool inBound(float value, float up,float low);
    static bool inBoundInt(int value, int up,int low);
    static float bound(float value,float up,float low);
    static int boundInt(int value,int up,int low);
    static float max(float a,float b);
    static float min(float a,float b);
    static CCPoint getGlobalPosition(CCNode* pNode);
    static CCPoint roundPoint(const CCPoint& point);
    static float getDistance(const CCPoint& point1,const CCPoint& point2);
    static float getAngle(const CCPoint& point1,const CCPoint& point2);
    static int getEightDirection(const CCPoint& base ,const CCPoint& target);
    static int intToZero(float x);
    static float absFloat(float x);
    static int getGcd(int a,int b);
    static bool collisionCheck(const CCSize& size,const CCPoint& spoint ,float range,const CCPoint& rpoint);
    static int abs(int a);
};

#endif
