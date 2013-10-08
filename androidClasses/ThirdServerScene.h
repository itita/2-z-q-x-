//
//  ThirdServerScene.h
//  ww4
//
//  Created by xiao tang on 13-9-26.
//
//

#ifndef __ww4__ThirdServerScene__
#define __ww4__ThirdServerScene__

#include "ServerScene.h"

class ThirdServerScene : public ServerScene {
    
public:
    
    //    ThirdServerScene();
    
    static ThirdServerScene* create();
    void myInit();
    virtual void loadResource();
    //    virtual void releaseResource();
    
#if   (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    void toLogin();
    void toRegister();
    void fastEnterGameWait();
    virtual void onEnterTransitionDidFinish();
    virtual void exitGame();
    virtual void keyBackClicked();
#endif   
    
    void toServerList();
    //    void toDisplayLogin(CCMenuItem* item);
    //    void toDisplayRegister(CCMenuItem* item);
    void toChangeServer(CCMenuItem* item);
    void toCancelServer(CCMenuItem* item);
    
private:
    
    void initServerInfo(SeverInfoBean* bean);
};

#endif /* defined(__ww4__ThirdServerScene__) */
