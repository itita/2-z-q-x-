//
//  ww2AppDelegate.cpp
//  ww2
//
//  Created by DingYu Fu on 12-9-10.
//  Copyright __MyCompanyName__ 2012年. All rights reserved.
//

#include "AppDelegate.h"

#include "cocos2d.h"
#include "StartScene.h"
#include "LoadingScene.h"
#include "SimpleAudioEngine.h"
#include "GXBaseScene.h"
#include "MyHttpConnection.h"
#include "PulsarNative.h"
#include "GXScrollView.h"
#include "GXChatHandler.h"

USING_NS_CC;

AppDelegate::AppDelegate()
{
}

AppDelegate::~AppDelegate()
{
}

bool AppDelegate::applicationDidFinishLaunching()
{
    // initialize director
    CCDirector *pDirector = CCDirector::sharedDirector();
    pDirector->setOpenGLView(CCEGLView::sharedOpenGLView());
    
    
    //#if   (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    //    float width = (float)PulsarNative::getDisplayWidth();
    //    float height = (float)PulsarNative::getDisplayHeight();
    //    CCEGLView::sharedOpenGLView()->setDesignResolutionSize((width*640)/height, 640, kResolutionExactFit);
    //#endif
    //#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    CCSize screenSize = CCEGLView::sharedOpenGLView()->getFrameSize();
    float width = (screenSize.width*640.0)/screenSize.height;
    if (width > 960) {
        CCEGLView::sharedOpenGLView()->setDesignResolutionSize(width, 640, kResolutionExactFit);
        GXScrollView::screenWidthRate = screenSize.width / winSize.width;
        GXScrollView::screenHeightRate = screenSize.height / winSize.height;
    } else {
        CCEGLView::sharedOpenGLView()->setDesignResolutionSize(960, 640, kResolutionShowAll);
        GXScrollView::screenWidthRate = screenSize.width / winSize.width;
        GXScrollView::screenHeightRate = screenSize.height / winSize.height;
    }
    //#endif
    
    
    // enable High Resource Mode(2x, such as iphone4) and maintains low resource on other devices.
    // pDirector->enableRetinaDisplay(true);
    
    // turn on display FPS
    //    pDirector->setDisplayStats(true);
#if   (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    //    pDirector->enableRetinaDisplay(true);
#endif
    
    // set FPS. the default value is 1.0/60 if you don't call this
    pDirector->setAnimationInterval(1.0 / 60);
    
    pDirector->setProjection(kCCDirectorProjection2D);
    
    // create a scene. it's an autorelease object
    //    CCScene *pScene = StartScene::create();
    CCScene *pScene = LoadingScene::create();
    
    
    // run
    pDirector->runWithScene(pScene);
    //    initOpenssl();
    //    readShuzi();
    //    CCUserDefault::sharedUserDefault()->setBoolForKey("newbieTag",false);
    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground()
{
    GXBaseScene* scene = dynamic_cast<GXBaseScene*>(CCDirector::sharedDirector()->getRunningScene());
    if (scene && scene->isEnter) {
        scene->doPause();
    }
    // if you use SimpleAudioEngine, it must be pause
    CocosDenshion::SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
    if (MyHttpConnection::isConn) {
        // 要么残留 断开 会死人的
        MyHttpConnection::getInstance()->sendDisconnect();
        MyHttpConnection::sendbyPipline();
    }
    if (GXChatHandler::isConn) {
        GXChatHandler::getInstance()->sendDisconnect();
    }
    
    CCDirector::sharedDirector()->stopAnimation();
    CCDirector::sharedDirector()->pause();
    CCLog("program pause");
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground()
{
    CCDirector::sharedDirector()->startAnimation();
    GXBaseScene* scene = dynamic_cast<GXBaseScene*>(CCDirector::sharedDirector()->getRunningScene());
    if (scene && scene->isEnter) {
        scene->doResume();
    }
    
    //    MyGameInfo::getInstance()->getXmppHandler()->startThread();
    CCDirector::sharedDirector()->resume();
    CocosDenshion::SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
    CCLog("program resume");
    // if you use SimpleAudioEngine, it must resume here
}

//void AppDelegate::initOpenssl() {
//
//
//
//
//    bio = BIO_new_connect("192.168.1.100:8000");
//
//
//
//}

//int AppDelegate::testSocket(){
//
//    struct sockaddr_in sa;
//    struct hostent* hp;
////    char port[] = "http://192.168.0.100";
//
//    hp = gethostbyname("192.168.1.100");
//    if(!hp){
//        return -1;
//    }
//    memset(&sa, 0, sizeof(sa));
//    memcpy((char*)&sa.sin_addr, hp->h_addr, hp->h_length);
//    sa.sin_family = hp->h_addrtype;
//    sa.sin_port = htons(8000);
//
//    socketHandle = socket(sa.sin_family, SOCK_STREAM, 0);
//
//    if(socketHandle < 0){
//        printf( "failed to create socket\n" );
//        return -1;
//    }
//    if(::connect(socketHandle, (sockaddr*)&sa, sizeof(sa)) < 0){
//        printf( "failed to connect socket\n" );
//        ::close(socketHandle);
//        return -1;
//    }
//
//    int errorCode= send(socketHandle,"12345678\r\n",strlen("12345678\r\n"),0);
//    if(errorCode == -1){
//        CCLog("发送失败");
//    }else{
//        CCLog("发送成功，字节数是：%d",errorCode);
//    }
//
//
//    CCLOG("Client connect OK ！ IP: %s:%d ","http://192.168.0.100",8000);
//    readShuzi();
//    return 0;
//}
//
//void AppDelegate::readShuzi() {
//}



