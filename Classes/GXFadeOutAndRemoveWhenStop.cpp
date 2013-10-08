//
//  GXFadeOutAndRemoveWhenStop.cpp
//  ww4
//
//  Created by xiao tang on 13-4-2.
//
//

#include "GXFadeOutAndRemoveWhenStop.h"


GXFadeOutAndRemoveWhenStop* GXFadeOutAndRemoveWhenStop::create(float d) {
    GXFadeOutAndRemoveWhenStop* pAction = new GXFadeOutAndRemoveWhenStop();
    
    pAction->initWithDuration(d);
    pAction->autorelease();
    
    return pAction;
}

void GXFadeOutAndRemoveWhenStop::stop(void) {
    getTarget()->removeFromParentAndCleanup(true);
    CCFadeOut::stop();
}