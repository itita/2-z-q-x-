//
//  GXMessage.h
//  ww4
//
//  Created by xiao tang on 13-3-19.
//
//

#ifndef __ww4__GXMessage__
#define __ww4__GXMessage__

#include <iostream>
#include "MyBaseMessage.h"
#include "GXString.h"
#include "GXDictionary.h"


class GXMessage : public MyBaseMessage{
    
public:
    GXMessage():
    msg(NULL),
    cmd(NULL),
    detail(NULL){
        tag = -1;
    }
    ~GXMessage(){
//        CCLog("GXMessage has been release");
        CC_SAFE_RELEASE_NULL(cmd);
        CC_SAFE_RELEASE_NULL(msg);
        CC_SAFE_RELEASE_NULL(detail);
    }
    
    static GXMessage* create();
    virtual void sendMsg();
    CC_SYNTHESIZE_RETAIN(GXString*,cmd,Cmd);
    bool succ;
    CC_SYNTHESIZE_RETAIN(GXString*,msg,Msg);
//    GXString* msg;
//    GXString* getMsg() {
//        return msg;
//    }
//    
//    void setMsg(GXString* _msg) {
//        CC_SAFE_RELEASE_NULL(msg);
//        CC_SAFE_RETAIN(_msg);
//        msg = _msg;
//    }
    
    CC_SYNTHESIZE_RETAIN(GXString*,detail,Detail);
    
};

#endif /* defined(__ww4__UnionMessage__) */
