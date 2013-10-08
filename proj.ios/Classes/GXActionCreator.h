//
//  GXActionCreator.h
//  Dialog2
//
//  Created by xiao tang on 13-8-23.
//
//

#ifndef Dialog2_GXActionCreator_h
#define Dialog2_GXActionCreator_h

#include "cocos2d.h"

using namespace cocos2d;

class GXActionCreator : public CCObject {
    
public:
    virtual CCAction* getAction() = 0;
};


#endif
