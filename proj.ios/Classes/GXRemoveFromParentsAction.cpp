//
//  GXRemoveFromParentsAction.cpp
//  ww3
//
//  Created by xiao tang on 12-10-14.
//
//

#include "GXRemoveFromParentsAction.h"

GXRemoveFromParentsAction* GXRemoveFromParentsAction::create() {
    GXRemoveFromParentsAction * pRet = new GXRemoveFromParentsAction();
    pRet->autorelease();
    return pRet;
}

void GXRemoveFromParentsAction::update(float time) {
//    CCAction::update(time);
//    getTarget()->stopAllActions();
//    getTarget()->removeFromParentAndCleanup(true);
}

//WARN 在先后死亡顺序上可能会引起内存泄露~在CCCallFunc之类上面

void GXRemoveFromParentsAction::stop(void) {
    getTarget()->stopAllActions();
    getTarget()->removeFromParentAndCleanup(true);
    CCAction::stop();
    
}
