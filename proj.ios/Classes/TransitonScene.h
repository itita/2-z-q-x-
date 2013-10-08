//
//  TransitonScene.h
//  ww3
//
//  Created by xiao tang on 12-12-21.
//
//

#ifndef __ww3__TransitonScene__
#define __ww3__TransitonScene__

#include "GXBaseScene.h"
#include "GXCreator.h"
#include "TransitionTrigger.h"
#include "MyMessageManage.h"

using namespace cocos2d;

class TransitonScene : public GXBaseScene {
    
public:
//    virtual bool init();
    ~TransitonScene();
    TransitonScene():
    toSceneTag(0),
    data(NULL),
    step(0)
    {
        trigger = TransitionTrigger::create(this);
        trigger->retain();
        MyMessageManage::getInstance()->registerTrigger(trigger);
    }
    static TransitonScene* create(int sceneTag,CCObject* response);
    static TransitonScene* create(int sceneTag);
    int toSceneTag;
    int step;
    virtual void onEnterTransitionDidFinish();
    void toStartSceneWait();
    void toStartScene();
    void toBattleSceneWait();
    void toBattleScene();
    void toDefendSceneWait();
    void toDefendScene();
    void toReadytoBattleScene(CCScene* scene);
    void setResponse(CCObject* response) {
        CC_SAFE_RELEASE_NULL(data);
        data = response;
        CC_SAFE_RETAIN(data);
    };
    virtual void loadResource() {
    
    }
    
    virtual void releaseResource() {
    
    }
//    virtual void loadingContentAndReplace();
//    virtual void loadResource();
//    static bool isLoaded;
private:
    void toChangeScene();
    CCObject* data;
    TransitionTrigger* trigger;
//    CCScene* tempScene;
};

#endif /* defined(__ww3__TransitonScene__) */
