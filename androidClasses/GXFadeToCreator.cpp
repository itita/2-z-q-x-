//
//  GXFadeToCreator.cpp
//  Dialog2
//
//  Created by xiao tang on 13-8-23.
//
//

#include "GXFadeToCreator.h"

void GXFadeTo::startWithTarget(CCNode *pTarget) {
    CCActionInterval::startWithTarget(pTarget);
    CCRGBAProtocol *pRGBAProtocol = dynamic_cast<CCRGBAProtocol*>(pTarget);
    if (pRGBAProtocol)
    {
        pRGBAProtocol->setOpacity(m_fromOpacity);
    }
}

GXFadeTo* GXFadeTo::create(float duration,GLubyte targetOpacity,GLubyte oriOpacity) {
    GXFadeTo *pFadeTo = new GXFadeTo();
    pFadeTo->CCActionInterval::initWithDuration(duration);
    pFadeTo->m_toOpacity = targetOpacity;
    pFadeTo->m_fromOpacity = oriOpacity;
    pFadeTo->autorelease();
    return pFadeTo;
}

GXFadeToCreator* GXFadeToCreator::create() {
    GXFadeToCreator* creator = new GXFadeToCreator();
    creator->autorelease();
    return creator;
}

CCAction* GXFadeToCreator::getAction() {
//    GXFadeTo* action = GXFadeTo::create(duration,_targetOpacity,_oriOpacity);
    return GXFadeTo::create(_duration,_targetOpacity,_oriOpacity);
}