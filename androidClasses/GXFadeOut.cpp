//
//  GXFadeOut.cpp
//  ww3
//
//  Created by xiao tang on 12-10-15.
//
//

#include "GXFadeOut.h"


void GXFadeOut::stop() {
    getTarget()->stopAllActions();
    getTarget()->setVisible(false);
    CCFadeOut::stop();
}

GXFadeOut* GXFadeOut::create(float d) {
    GXFadeOut* pAction = new GXFadeOut();
    
    pAction->initWithDuration(d);
    pAction->autorelease();
    
    return pAction;
}