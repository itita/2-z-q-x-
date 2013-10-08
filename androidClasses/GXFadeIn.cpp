//
//  GXFadeIn.cpp
//  ww3
//
//  Created by xiao tang on 12-10-15.
//
//

#include "GXFadeIn.h"

void GXFadeIn::stop() {
    getTarget()->setVisible(true);
    CCFadeIn::stop();
}