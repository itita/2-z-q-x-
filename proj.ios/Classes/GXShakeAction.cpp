//
//  GXShakeAction.cpp
//  ww4
//
//  Created by xiao tang on 13-5-10.
//
//

#include "GXShakeAction.h"

GXShakeAction* GXShakeAction::create(float duration,float _xDelta,float _yDelta,const CCPoint& _oriAnchorPoint)
{
    GXShakeAction *pMoveTo = new GXShakeAction();
    pMoveTo->CCActionInterval::initWithDuration(duration);
    pMoveTo->xDelta = _xDelta;
    pMoveTo->yDelta = _yDelta;
    pMoveTo->oriAnchor = _oriAnchorPoint;
    pMoveTo->autorelease();
    
    return pMoveTo;
}


void GXShakeAction::startWithTarget(CCNode *pTarget)
{
    CCActionInterval::startWithTarget(pTarget);
    pTarget->setAnchorPoint(oriAnchor);
    randomXDelta = (arc4random()%((int)(xDelta*2000)))/1000.0-xDelta;
    randomYDelta = (arc4random()%((int)(yDelta*2000)))/1000.0-yDelta;
}

void GXShakeAction::update(float time)
{
    if (m_pTarget)
    {
        if (time <= 0.5) {
            m_pTarget->setAnchorPoint(ccp(oriAnchor.x + randomXDelta * time*2,
                                       oriAnchor.y + randomYDelta * time*2));
        } else {
            time-=0.5;
            m_pTarget->setAnchorPoint(ccp(oriAnchor.x + randomXDelta*(1-time*2) ,
                                       oriAnchor.y + randomYDelta*(1-time*2)));
        }
    }
}

void GXShakeAction::stop(void) {
    m_pTarget->setAnchorPoint(oriAnchor);
    CCActionInterval::stop();
}