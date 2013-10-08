//
//  GXScrollView.cpp
//  ww2
//
//  Created by DingYu Fu on 12-8-22.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#ifndef ww3_GXScrollView_h
#define ww3_GXScrollView_h
#include "cocos2d.h"
#include "DefineSet.h"

#define clickMode 0
#define toggleMode 1


using namespace cocos2d;

class GXScrollView : public cocos2d::CCLayer{
public:
    GXScrollView():
    priority(-128),
    m_pSelectedItem(NULL),
    speedVector(ccp(0,0)),
    isEnabled(true),
    mode(clickMode),
    isMove(false)
    {
//#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
//        CCSize screenSize = CCEGLView::sharedOpenGLView()->getFrameSize();
//        screenWidthRate = screenSize.width / winSize.width;
//        screenHeightRate = screenSize.height / winSize.height;
//#endif
    }
    virtual ~GXScrollView();
    CCSize getViewSize() {return viewSize;};
    CCPoint getOriPosition() {return oriPosition;};
    virtual void setMapSize(CCSize size);
    CCSize getMapSize() {
        return mapSize;
    }
    static GXScrollView* create(int _priority);
    
    virtual void setMode(int modeCode);
    
    virtual bool init();
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
    virtual void registerWithTouchDispatcher(void); 
    virtual void setContentSize(const CCSize& size);
//    virtual void setPosition(CCPoint point);
    virtual void setOriPosition(const CCPoint& point);
    virtual void visit(void);
    virtual void decelerate();
    virtual bool getEnabled() {return isEnabled;}
    virtual void setEnabled(bool _isEnabled) {isEnabled = _isEnabled;}
    virtual void runChildAction(CCAction* action);
    
    static float screenWidthRate;
    static float screenHeightRate;
    
    
    //可能需要解除注册
//    virtual void addChild(CCNode *node);
protected:
    virtual CCMenuItem* itemForTouch(CCTouch *touch);
    bool isEnabled;
    virtual void setViewSize(const CCSize& size);
    CCSize viewSize;
    CCPoint oriPosition;
    CCSize mapSize;
    int priority;
    CCPoint speedVector;
    CCMenuItem *m_pSelectedItem;
    int mode;
    bool isMove;
//#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    
//#endif
//    virtual void dispatchToChild(CCTouch* pTouch,CCEvent* pEvent);
};
#endif