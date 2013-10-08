//
//  GXSpriteCreator.cpp
//  Dialog2
//
//  Created by xiao tang on 13-8-20.
//
//

#include "GXSpriteCreator.h"

GXSpriteCreator* GXSpriteCreator::create() {
    GXSpriteCreator* bean = new GXSpriteCreator();
    bean->autorelease();
    return bean;
}

CCSprite* GXSpriteCreator::getSprite() {
    if (spriteFrameName != NULL) {
        CCSprite* sprite = CCSprite::createWithSpriteFrameName(spriteFrameName->getCString());
        if (relativeType == relativeZeroType) {
            sprite->setPosition(ccp(x,y));
        } else if(relativeType == relativeCenterType) {
            sprite->setPosition(ccp(winSize.width/2+x,y));
        } else if(relativeType == relativeWidthType) {
            sprite->setPosition(ccp(winSize.width+x,y));
        }
        sprite->setScaleX(scaleX);
        sprite->setScaleY(scaleY);
        sprite->setAnchorPoint(ccp(anchorX,anchorY));
        sprite->setColor(ccc3(r,g,b));
//        CCLog("%d",a);
        sprite->setOpacity(a);
        sprite->_setZOrder(zOrder);
        sprite->setFlipX(isFilpX);
        if (this->getActionCreator() != NULL) {
            sprite->runAction(this->getActionCreator()->getAction());
        }
        return sprite;
    }
    return NULL;
}