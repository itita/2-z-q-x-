//
//  GXScaleTo.cpp
//  ww3
//
//  Created by xiao tang on 12-12-17.
//
//

#include "GXScaleTo.h"
#include "cocos2d.h"

GXScaleTo* GXScaleTo::create(float duration, float s) {
    GXScaleTo *pScaleTo = new GXScaleTo();
    pScaleTo->initWithDuration(duration, s);
    pScaleTo->autorelease();
    
    return pScaleTo;
}

void GXScaleTo::startWithTarget(CCNode *pTarget) {
    CCScaleTo::startWithTarget(pTarget);
    oriScaleX = pTarget->getScaleX();
    oriScaleY = pTarget->getScaleY();
}

void GXScaleTo::stop(void) {
    getTarget()->setScaleX(oriScaleX);
    getTarget()->setScaleY(oriScaleY);
    CCScaleTo::stop();
}

bool GXScaleTo::isDone() {
    bool isdone = CCScaleTo::isDone();
    if (isdone) {
        getTarget()->setScaleX(oriScaleX);
        getTarget()->setScaleY(oriScaleY);
    }
    return isdone;
}