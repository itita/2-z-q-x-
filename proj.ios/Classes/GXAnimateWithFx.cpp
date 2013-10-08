//
//  GXAnimateWithFx.cpp
//  ww4
//
//  Created by xiao tang on 13-1-7.
//
//

#include "GXAnimateWithFx.h"
#include "GXFX.h"
#include "Mathlib.h"

GXAnimateWithFx* GXAnimateWithFx::create(cocos2d::CCAnimation *pAnimation, cocos2d::CCArray *_fxArray) {
    GXAnimateWithFx *pAnimate = new GXAnimateWithFx();
    CCObject* obj = NULL;
    int max = 0;
    CCARRAY_FOREACH(_fxArray, obj) {
        GXFX* ani = (GXFX*) obj;
        if(ani->endFrameCount > max) {
            max = ani->endFrameCount+1;
        }
    }
    if (max > pAnimation->getFrames()->count() ) {
        for (int i = 0; i< max - pAnimation->getFrames()->count(); i++) {
            pAnimation->addSpriteFrame(((CCAnimationFrame*)pAnimation->getFrames()->lastObject())->getSpriteFrame());
        }
    }
    pAnimate->initWithAnimation(pAnimation);
    pAnimate->fxArray = _fxArray;
    
    _fxArray->retain();
    pAnimate->autorelease();
    
    return pAnimate;
}

GXAnimateWithFx* GXAnimateWithFx::create(cocos2d::CCAnimation *pAnimation, GXFX *fx) {
    GXAnimateWithFx *pAnimate = new GXAnimateWithFx();
    pAnimate->initWithAnimation(pAnimation);
    pAnimate->fxArray = CCArray::create();
    pAnimate->fxArray->retain();
    pAnimate->fxArray->addObject(fx);
    pAnimate->autorelease();
    
    return pAnimate;
}

void GXAnimateWithFx::startWithTarget(cocos2d::CCNode *pTarget) {
//    CCActionInterval::startWithTarget(pTarget);
//    CCSprite *pSprite = (CCSprite*)(pTarget);
//    
//    CC_SAFE_RELEASE(m_pOrigFrame);
//    
//    if (getAnimation()->getRestoreOriginalFrame())
//    {
//        m_pOrigFrame = pSprite->displayFrame();
//        m_pOrigFrame->retain();
//    }
//    m_nNextFrame = 0;
//    m_uExecutedLoops = 0;
    CCAnimate::startWithTarget(pTarget);
    CCObject* obj = NULL;
    CCARRAY_FOREACH(fxArray, obj) {
        GXFX* fx = (GXFX*)obj;
        if (fx->getParent() == NULL) {
            pTarget->addChild(fx,fx->zorder);
        }
    }
}

void GXAnimateWithFx::stop() {
    CCAnimate::stop();
    CCObject* obj = NULL;
    CCARRAY_FOREACH(fxArray, obj) {
        GXFX* fx = (GXFX*)obj;
        fx->setVisible(false);
        fx->removeFromParentAndCleanup(true);
    }
}

void GXAnimateWithFx::update(float t) {
    // if t==1, ignore. Animation should finish with t==1
    if( t < 1.0f ) {
        t *= getAnimation()->getLoops();
        
        // new loop?  If so, reset frame counter
        unsigned int loopNumber = (unsigned int)t;
        if( loopNumber > m_uExecutedLoops ) {
            m_nNextFrame = 0;
            m_uExecutedLoops++;
        }
        
        // new t for animations
        t = fmodf(t, 1.0f);
    }
    if (m_pTarget == NULL) {
        return;
    }
    
    CCArray* frames = getAnimation()->getFrames();
    unsigned int numberOfFrames = frames->count();
    CCSpriteFrame *frameToDisplay = NULL;
    
    for( unsigned int i=m_nNextFrame; i < numberOfFrames; i++ ) {
        float splitTime = m_pSplitTimes->at(i);
        
        if( splitTime <= t ) {
            CCAnimationFrame* frame = (CCAnimationFrame*)frames->objectAtIndex(i);
            frameToDisplay = frame->getSpriteFrame();
            ((CCSprite*)m_pTarget)->setDisplayFrame(frameToDisplay);
            
            CCDictionary* dict = frame->getUserInfo();
            if( dict )
            {
                //TODO: [[NSNotificationCenter defaultCenter] postNotificationName:CCAnimationFrameDisplayedNotification object:target_ userInfo:dict];
            }
            CCObject* obj;
            CCARRAY_FOREACH(fxArray, obj) {
                GXFX* fx =(GXFX*)obj;
                if(i - fx->startFrameCount == 0) {
                    fx->setVisible(true);
                    fx->setDisplayFrame(((CCAnimationFrame*)(fx->animation->getFrames()->objectAtIndex(0)))->getSpriteFrame());
                } else if(Mathlib::inBound(i, fx->endFrameCount, fx->startFrameCount)){
                    fx->setDisplayFrame(((CCAnimationFrame*)(fx->animation->getFrames()->objectAtIndex(i-fx->startFrameCount)))->getSpriteFrame());
                } else if (i== fx->endFrameCount+1) {
                    fx->setVisible(false);
                }
            }
            
            m_nNextFrame = i+1;
            
            break;
        }
    }
}