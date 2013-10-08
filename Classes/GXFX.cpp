//
//  GXFX.cpp
//  ww4
//
//  Created by xiao tang on 13-1-7.
//
//

#include "GXFX.h"

GXFX* GXFX::create(cocos2d::CCAnimation *_animation, unsigned int _startFrameCount,int _zorder) {
    GXFX *pobSprite = new GXFX();
    
    if (pobSprite && pobSprite->initWithSpriteFrame(((CCAnimationFrame*)_animation->getFrames()->objectAtIndex(0))->getSpriteFrame()))
    {
        pobSprite->autorelease();
        pobSprite->animation = _animation;
        _animation->retain();
        pobSprite->startFrameCount = _startFrameCount;
        pobSprite->endFrameCount = _startFrameCount + _animation->getFrames()->count()-1;
        pobSprite->setVisible(false);
        pobSprite->zorder =_zorder;
        return pobSprite;
    }
    CC_SAFE_DELETE(pobSprite);
    return NULL;
}