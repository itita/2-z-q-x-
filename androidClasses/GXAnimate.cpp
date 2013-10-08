//
//  GXAnimate.cpp
//  ww4
//
//  Created by xiao tang on 13-1-29.
//
//

#include "GXAnimate.h"


GXAnimate* GXAnimate::create(CCAnimation *pAnimation)
{
    GXAnimate *pAnimate = new GXAnimate();
    pAnimate->initWithAnimation(pAnimation);
    pAnimate->autorelease();
    return pAnimate;
}

void GXAnimate::stop(void)
{
    if (getAnimation()->getRestoreOriginalFrame() && m_pTarget)
    {
        ((CCSprite*)(m_pTarget))->setDisplayFrame(m_pOrigFrame);
    } else {
        ((CCSprite*)(m_pTarget))->setDisplayFrame(((CCAnimationFrame*)getAnimation()->getFrames()->lastObject())->getSpriteFrame());
    }
    
    CCActionInterval::stop();
}