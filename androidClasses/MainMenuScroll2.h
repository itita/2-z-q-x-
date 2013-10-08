//
//  MainMenuScroll2.h
//  ww4
//
//  Created by xiao tang on 13-8-30.
//
//

#ifndef __ww4__MainMenuScroll2__
#define __ww4__MainMenuScroll2__

#include "GXScrollView.h"

class MainMenuScroll2 : public GXScrollView {
    
public:
    MainMenuScroll2()
//    menuLight(NULL),
//    menuDownTip(NULL),
//    menuUpTip(NULL)
    {
        //#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
        //        CCSize screenSize = CCEGLView::sharedOpenGLView()->getFrameSize();
        //        screenWidthRate = screenSize.width / winSize.width;
        //        screenHeightRate = screenSize.height / winSize.height;
        //#endif
    }
    ~MainMenuScroll2(){
        CCLog("MainMenuScroll has bean released");
    };
    
    static MainMenuScroll2* create(int _priority);
    
//    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
//    virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
    virtual void decelerate();
    virtual void visit(void);
    
//    CCSprite* menuLight;
//    CCSprite* menuDownTip;
//    CCSprite* menuUpTip;
private:
    float screenWidth;
};

#endif /* defined(__ww4__MainMenuScroll2__) */
