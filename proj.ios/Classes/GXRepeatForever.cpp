//
//  GXRepeatForever.cpp
//  ww3
//
//  Created by xiao tang on 12-12-17.
//
//

#include "GXRepeatForever.h"

void GXRepeatForever::step(float dt) {
    m_pInnerAction->step(dt);
    if (m_pInnerAction->isDone())
    {
        m_pInnerAction->stop();
        float diff = m_pInnerAction->getElapsed() - m_pInnerAction->getDuration();
        m_pInnerAction->startWithTarget(m_pTarget);
        // to prevent jerk. issue #390, 1247
        m_pInnerAction->step(0.0f);
        m_pInnerAction->step(diff);
    }
}

GXRepeatForever* GXRepeatForever::create(cocos2d::CCActionInterval *pAction) {
    GXRepeatForever *pRet = new GXRepeatForever();
    if (pRet && pRet->initWithAction(pAction))
    {
        pRet->autorelease();
        return pRet;
    }
    CC_SAFE_DELETE(pRet);
    return NULL;
}