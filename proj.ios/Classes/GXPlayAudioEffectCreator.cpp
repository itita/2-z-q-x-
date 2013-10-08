//
//  GXPlayAudioEffectCreator.cpp
//  Dialog2
//
//  Created by xiao tang on 13-8-23.
//
//

#include "GXPlayAudioEffectCreator.h"
#include "SimpleAudioEngine.h"


GXPlayAudioEffectAction* GXPlayAudioEffectAction::create(CCString* name) {
    GXPlayAudioEffectAction* action = new GXPlayAudioEffectAction();
    action->autorelease();
    action->effectName = name;
    action->effectName->retain();
    return action;
}


void GXPlayAudioEffectAction::stop(void) {
    CCActionInstant::stop();
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(effectName->getCString());
}

GXPlayAudioEffectCreator* GXPlayAudioEffectCreator::create() {
    GXPlayAudioEffectCreator* creator = new GXPlayAudioEffectCreator();
    creator->autorelease();
    return creator;
}

CCAction* GXPlayAudioEffectCreator::getAction() {
    return GXPlayAudioEffectAction::create(getEffectName());
}
