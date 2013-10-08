////
////  MainMenuScroll.h
////  ww4
////
////  Created by xiao tang on 13-8-15.
////
////
//
//#ifndef __ww4__MainMenuScroll__
//#define __ww4__MainMenuScroll__
//
//#include "GXScrollView.h"
//
//class MainMenuScroll : public GXScrollView {
//    
//public:
//    MainMenuScroll():
//    space(0),
//    preCoordinate(0),
//    menuLight(NULL)
//    {
//        //#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
//        //        CCSize screenSize = CCEGLView::sharedOpenGLView()->getFrameSize();
//        //        screenWidthRate = screenSize.width / winSize.width;
//        //        screenHeightRate = screenSize.height / winSize.height;
//        //#endif
//    }
//    ~MainMenuScroll(){
//        CCLog("MainMenuScroll has bean released");
//    };
//    
//    static MainMenuScroll* create(int _priority,int space,const CCPoint& oriPoint);
//
//    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
//    virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
//    virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
//    virtual void decelerate();
//    virtual void addChild(cocos2d::CCNode* child);
//    
////    virtual void visit(void);
//    int space;
//    CCPoint oriPoint;
//    CCSprite* menuLight;
//private:
//    int preCoordinate;
//    
//};
//
//#endif /* defined(__ww4__MainMenuScroll__) */
