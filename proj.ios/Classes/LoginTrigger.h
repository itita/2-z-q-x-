//
//  LoginTrigger.h
//  ww4
//
//  Created by xiao tang on 13-4-26.
//
//

#ifndef __ww4__LoginTrigger__
#define __ww4__LoginTrigger__

#include <iostream>
#include "MyBaseTrigger.h"

class LoginTrigger :public MyBaseTrigger{
    
public:
    ~LoginTrigger() {
//        CCLog("LoginTrigger release");
    }
    
    LoginTrigger():
    scene(NULL){
    
    }
    static LoginTrigger* create(CCNode* _scene);
    virtual bool excuteMsg(MyBaseMessage* msg);
    virtual bool onRegist();
    virtual bool onUnRegist();
    CCNode* scene;
};

#endif /* defined(__ww4__LoginTrigger__) */
