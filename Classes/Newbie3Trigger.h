//
//  Newbie3Trigger.h
//  ww3
//
//  Created by xiao tang on 12-12-18.
//
//

#ifndef __ww3__Newbie3Trigger__
#define __ww3__Newbie3Trigger__

#include <iostream>

#include "MyBaseTrigger.h"
#include "cocos2d.h"
#include "NewbieBattleScene.h"

using namespace cocos2d;

class Newbie3Trigger : public MyBaseTrigger  {
    
public:
    ~Newbie3Trigger();
    Newbie3Trigger():status(0)
    ,isDialog(false){};
    virtual bool excuteMsg(MyBaseMessage* msg);
    static Newbie3Trigger* create(NewbieBattleScene* node);
    void toNextCallBack(CCNode* node);
    virtual bool onRegist();
    virtual bool onUnRegist();
    NewbieBattleScene* scene;
    void getPrizeCallBack(CCNode* pSender);
    void toBattleScene(CCNode* pSender);
private:
    int status;
    bool isDialog;
    void scaleCallBack(CCNode* pSender);
    void mapMoveCallBack();
    void shakeEffect2(CCNode* node);
};

#endif /* defined(__ww3__Newbie3Trigger__) */
