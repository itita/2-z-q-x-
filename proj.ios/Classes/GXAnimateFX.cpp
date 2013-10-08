//
//  File.cpp
//  ww2
//
//  Created by DingYu Fu on 12-9-9.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "GXAnimateFX.h"
#include "cocos2d.h"
#include "GXRemoveFromParentsAction.h"

GXAnimateFX* GXAnimateFX::createWithAnitmateFrameName(const char* _frameName,bool isDispear,bool isLoop) {
    GXAnimateFX* fx = new GXAnimateFX();
    
    //    sprintf(str, "%s (0).png",spriteFileName);
    //    unit->initWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(str));
    fx->init();
    //    unit->speed = _speed;
    fx -> autorelease();
    
    CCAnimation* animation = fx->initAction(_frameName);
    if (isLoop) {
        fx->runAction(CCRepeatForever::create(CCAnimate::create(animation)));
        return fx;
    }
    if (isDispear) {
        fx->runAction(CCSequence::create(CCAnimate::create(animation),GXRemoveFromParentsAction::create(),NULL));
        return fx;
    }
    
    //    CCAction* action = CCRepeatForever::create(CCAnimate::create(unit->move[0]));
    //    action->setTag(currentAction);
    //    unit->runAction(action);
    
    return NULL;
}

GXAnimateFX* GXAnimateFX::createWithAnitmateFrameNameByFadeout(const char *_frameName, float isDispear, bool isLoop) {
    GXAnimateFX* fx = new GXAnimateFX();
    
    //    sprintf(str, "%s (0).png",spriteFileName);
    //    unit->initWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(str));
    fx->init();
    //    unit->speed = _speed;
    fx -> autorelease();
    
    CCAnimation* animation = fx->initAction(_frameName);
    if (isLoop) {
        fx->runAction(CCRepeatForever::create(CCAnimate::create(animation)));
        return fx;
    }
    if (isDispear > 0) {
        fx->runAction(CCSequence::create(CCAnimate::create(animation),CCFadeOut::create(isDispear),GXRemoveFromParentsAction::create(),NULL));
        return fx;
    }
    
//    CCAction* action = CCRepeatForever::create(CCAnimate::create(unit->move[0]));
//    action->setTag(currentAction);
//    unit->runAction(action);
    
    return NULL;
    
}

GXAnimateFX* GXAnimateFX::createWithAnitmateFrameName(const char* _frameName,bool isDispear,bool isLoop,int startCount ,int endCount) {
    GXAnimateFX* fx = new GXAnimateFX();
    
    //    sprintf(str, "%s (0).png",spriteFileName);
    //    unit->initWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(str));
    fx->init();
    //    unit->speed = _speed;
    fx -> autorelease();
    
    CCAnimation* animation = fx->initAction(_frameName,startCount,endCount);
    if (isLoop) {
        fx->runAction(CCRepeatForever::create(CCAnimate::create(animation)));
        return fx;
    }
    if (isDispear) {
        fx->runAction(CCSequence::create(CCAnimate::create(animation),GXRemoveFromParentsAction::create(),NULL));
        return fx;
    }
    
    //    CCAction* action = CCRepeatForever::create(CCAnimate::create(unit->move[0]));
    //    action->setTag(currentAction);
    //    unit->runAction(action);
    
    return NULL;
}

CCAnimation* GXAnimateFX::initAction(const char* _spritFrameName) {
    return initAction(_spritFrameName,0,999999);
}

CCAnimation* GXAnimateFX::initAction(const char* _spritFrameName,int startCount,int endCount) {
    char str[64] = {0};
    CCArray* array = CCArray::create();
    int i = startCount;
    while (true) {
        //            CCLog("%s (%d).png",spriteFileName);
        //            sprintf(str, "%s (%d).png",spriteFileName,15*j+i);
        sprintf(str, "%s (%d).png",_spritFrameName,i);
        CCSpriteFrame* sprite = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(str);
        if(sprite == NULL || i+1 >= endCount) {
//            CCLog("frameName:%s,count:%d",_spritFrameName,i);
            break;
        } else {
            array->addObject(sprite);
        }
        i++;
    }
    CCAnimation* animation = CCAnimation::createWithSpriteFrames(array,0.1);
    animation->retain();
    return animation;
}

void GXAnimateFX::dispose() {
    this->stopAllActions();
    this->removeFromParentAndCleanup(true);
}