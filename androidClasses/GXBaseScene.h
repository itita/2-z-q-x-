//
//  GXBaseScene.h
//  ww2
//
//  Created by xiao tang on 12-10-4.
//
//

#ifndef ww2_GXBaseScene_h
#define ww2_GXBaseScene_h
#include "cocos2d.h"
#include "GarbageResourceCollection.h"

using namespace cocos2d;


class GXBaseScene : public CCScene {
    
public:
    ~GXBaseScene() {
//        GarbageResourceCollection::getInstance()->GarbageCollection();
    }
    GXBaseScene():isEnter(false) {
    
    }
    virtual void doPause();
//    virtual void onEnter();
//    virtual void onExit();
    virtual void loadResource() = 0;
    virtual void releaseResource() = 0;
    virtual void doResume();
    virtual void onEnterTransitionDidFinish();
    bool isEnter;
};

#endif
