//
//  LoadingScene.h
//  ww2
//
//  Created by DingYu Fu on 12-9-16.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#ifndef ww2_LoadingScene_h
#define ww2_LoadingScene_h
#include "cocos2d.h"

using namespace cocos2d;

class LoadingScene : public CCScene {
    
public:
    ~LoadingScene() {
        releaseResource();
    }
    virtual bool init();
    CREATE_FUNC(LoadingScene);
    virtual void loadingReplace();
    virtual void loadPublicResource();
//    virtual void loadStartResource();
    virtual void releaseResource();
    static bool isLoaded;
    void onEnterTransitionDidFinish();
private:
    
//    bool isConn;
};

#endif
