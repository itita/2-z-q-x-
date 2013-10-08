//
//  GXTintToCreator.cpp
//  Dialog2
//
//  Created by xiao tang on 13-8-24.
//
//

#include "GXTintToCreator.h"

GXTintToCreator* GXTintToCreator::create() {
    GXTintToCreator* creator = new GXTintToCreator();
    creator->autorelease();
    return creator;
}

CCAction* GXTintToCreator::getAction() {
    return CCTintTo::create(duration,r,g,b);
}