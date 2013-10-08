//
//  GXPoint.cpp
//  ww4
//
//  Created by xiao tang on 13-1-14.
//
//

#include "GXPoint.h"

GXPoint* GXPoint::create() {
    GXPoint* point = new GXPoint();
    point->autorelease();
    return point;
}