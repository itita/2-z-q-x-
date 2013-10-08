//
//  GXMsg.cpp
//  ww3
//
//  Created by xiao tang on 12-11-22.
//
//

#include "GXMsg.h"

GXMsg* GXMsg::create(std::string name,std::string msg) {
    GXMsg* gx = new GXMsg();
//    gx->autorelease();
    gx->name = name;
    gx->msg = msg;
    return gx;
}

GXMsg* GXMsg::create() {
    GXMsg* gx = new GXMsg();
    return gx;
}

GXMsg* GXMsg::create(std::string name,std::string msg,int mode) {
    GXMsg* gx = new GXMsg();
    gx->name = name;
    gx->msg = msg;
    gx->mode = mode;
    return gx;
}