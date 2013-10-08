//
//  GXCommander.h
//  ww4
//
//  Created by xiao tang on 13-3-19.
//
//

#ifndef __ww4__GXCommander__
#define __ww4__GXCommander__

#include <iostream>
#include "cocos2d.h"
#include "GXString.h"

using namespace cocos2d;

class GXCommander : public CCObject{
public:
    ~GXCommander() {
        CC_SAFE_RELEASE_NULL(cmd);
        CC_SAFE_RELEASE_NULL(msg);
        CC_SAFE_RELEASE_NULL(detail);
    }
    GXCommander():
    cmd(GXString::create("")),
    succ(false),
    msg(GXString::create("")),
    detail(GXString::create(""))
    {}
    GXString* cmd;
    bool succ;
    GXString* msg;
    GXString* detail;
    
    static GXCommander* create();
};


#endif /* defined(__ww4__GXCommander__) */
