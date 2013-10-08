//
//  NewbieReadyTrigger.h
//  ww4
//
//  Created by xiao tang on 13-1-5.
//
//

#ifndef __ww4__NewbieReadyTrigger__
#define __ww4__NewbieReadyTrigger__

#include "MyBaseTrigger.h"
#include "NewbieReadyScene.h"

class NewbieReadyTrigger : public MyBaseTrigger  {
    
public:
    ~NewbieReadyTrigger();
    NewbieReadyTrigger():
    status(0),
    scene(NULL){};
    virtual bool excuteMsg(MyBaseMessage* msg);
    static NewbieReadyTrigger* create(NewbieReadyScene* scene);
    void toNextCallBack(CCNode* node);
    virtual bool onRegist();
    virtual bool onUnRegist();
    NewbieReadyScene* scene;
private:
    int status;
};

#endif /* defined(__ww4__NewbieReadyTrigger__) */
