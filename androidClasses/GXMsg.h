//
//  GXMsg.h
//  ww3
//
//  Created by xiao tang on 12-11-22.
//
//

#ifndef ww3_GXMsg_h
#define ww3_GXMsg_h
#include "cocos2d.h"
#include <string.h>

#define worldMode 0
#define systemMode 2
#define unionMode 1

using namespace cocos2d;

class GXMsg : public CCObject{
    
public:
    ~GXMsg() {
//        CCLog("Gxmsg has been released");
    }
    
    GXMsg():
    name(""),
    msg(""),
    mode(0)
    {}
    static GXMsg* create();
    static GXMsg* create(std::string name,std::string msg);
    static GXMsg* create(std::string name,std::string msg,int mode);
    
    std::string name;
    std::string msg;
    int mode;

};

#endif
