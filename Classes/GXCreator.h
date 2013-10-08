//
//  GXCreator.h
//  ww3
//
//  Created by xiao tang on 12-10-31.
//
//

#ifndef ww3_GXCreator_h
#define ww3_GXCreator_h

#include "cocos2d.h"

using namespace cocos2d;

class GXCreator : public CCObject{
    
public:
    virtual CCObject* creatObj() = 0;
    virtual void doFill(CCObject* entity) =0 ;
};

#endif
