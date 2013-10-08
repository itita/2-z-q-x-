//
//  GXScrollBar.h
//  ww4
//
//  Created by xiao tang on 13-7-30.
//
//

#ifndef __ww4__GXScrollBar__
#define __ww4__GXScrollBar__

#include <iostream>
#include "cocos2d.h"
#include "GXUtil.h"

using namespace cocos2d;

typedef void (CCObject::*SEL_ScrollBarChangeRate)(CCObject*);

class GXScrollBar : public CCLayer {
    
public:
    
    GXScrollBar():
    priority(0),
    length(0),
    target(NULL),
    percentage(0){
        GXUtil::loadResourceUtilSucc("SliderUI.plist","SliderUI.pvr.ccz");
    }
    
    ~GXScrollBar() {
        CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile("SliderUI.plist");
        CCTextureCache::sharedTextureCache()->removeTextureForKey("SliderUI.pvr.ccz");
    }
    
    static GXScrollBar* create(int _priority,int length,CCObject* target,SEL_ScrollBarChangeRate selector);
    void init(int length);
    float percentage;
    virtual void registerWithTouchDispatcher();
    
    virtual bool ccTouchBegan(CCTouch* touch, CCEvent* event);
    virtual void ccTouchEnded(CCTouch* touch, CCEvent* event);
    virtual void ccTouchMoved(CCTouch* touch, CCEvent* event);
    
private:
    int priority;
    int length;
    CCSprite* bar;
    //target的循环持有，很危险
    CCObject* target;
    SEL_ScrollBarChangeRate selector;
    
};

#endif /* defined(__ww4__GXScrollBar__) */
