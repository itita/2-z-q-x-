//
//  Newbie2Trigger.h
//  ww3
//
//  Created by xiao tang on 12-12-15.
//
//

#ifndef ww3_Newbie2Trigger_h
#define ww3_Newbie2Trigger_h

#include "MyBaseTrigger.h"
#include "cocos2d.h"
#include "NewbieStartScene.h"

using namespace cocos2d;

class Newbie2Trigger : public MyBaseTrigger  {
    
public:
    ~Newbie2Trigger();
    Newbie2Trigger():status(0)
    ,isDialog(false){};
    virtual bool excuteMsg(MyBaseMessage* msg);
    static Newbie2Trigger* create(NewbieStartScene* node);
    void toNextCallBack(CCNode* node);
    virtual bool onRegist();
    virtual bool onUnRegist();
    NewbieStartScene* scene;
    void getPrizeCallBack(CCNode* pSender);
    void displayQuestInfoCallback(CCMenuItem* item);
    void toBattleScene(CCNode* pSender);
    void toGetQuestPrize(CCMenuItem* item);
private:
    int status;
    bool isDialog;
    void scaleCallBack(CCNode* pSender);
    void shakeEffect2(CCNode* node);
};

#endif
