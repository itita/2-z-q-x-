//
//  GXShieldTouchMenuItem.cpp
//  ww3
//
//  Created by xiao tang on 12-11-5.
//
//

#include "GXShieldTouchMenuItem.h"


GXShieldTouchMenuItem* GXShieldTouchMenuItem::create() {
    GXShieldTouchMenuItem* item = new GXShieldTouchMenuItem();
    item->initWithTarget(item, menu_selector( GXShieldTouchMenuItem::sheild));
    item->autorelease();
    return item;
}

CCRect GXShieldTouchMenuItem::rect() {
//    CCLog("rect");
    return CCMenuItem::rect();
}

void GXShieldTouchMenuItem::sheild(cocos2d::CCNode *pSender) {
//    CCLog("touch sheild");
}