//
//  PartInterface.h
//  ww2
//
//  Created by DingYu Fu on 12-9-12.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#ifndef ww2_PartInterface_h
#define ww2_PartInterface_h

#include "cocos2d.h"

using namespace cocos2d;
//前提是你要有方位才有效

class PartInterface {
    
public:
    virtual CCSize getPartSize();
    virtual void setPartSize(const CCSize& _partSize);
    virtual CCPoint getPartPosition();
protected:
    CCSize partSize;
    
};

#endif
