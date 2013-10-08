//
//  Newbie4Trigger.h
//  ww3
//
//  Created by xiao tang on 12-12-20.
//
//

#ifndef __ww3__Newbie4Trigger__
#define __ww3__Newbie4Trigger__

#include "MyBaseTrigger.h"
#include "NewbieMovieScene.h"

class Newbie4Trigger : public MyBaseTrigger {
    
public:
    ~Newbie4Trigger();
    Newbie4Trigger():status(0){};
    virtual bool excuteMsg(MyBaseMessage* msg);
    static Newbie4Trigger* create(NewbieMovieScene* scene);
    void toNextCallBack();
    virtual bool onRegist();
    virtual bool onUnRegist();
    NewbieMovieScene* scene;
private:
    void inCallBack();
    void outCallBack(CCNode* pSender);
    void cloudCallBack(CCNode* pSender,CCSprite* cloud);
    void crashCallBack(CCNode* pSender,MyBattleMap* map);
    void toBeginScene(CCNode* pSender);
    int status;
};

#endif /* defined(__ww3__Newbie4Trigger__) */
