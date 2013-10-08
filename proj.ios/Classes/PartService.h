//
//  PartService.h
//  ww2
//
//  Created by DingYu Fu on 12-9-12.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#ifndef ww2_PartService_h
#define ww2_PartService_h
#include "cocos2d.h"
#include "PartInterface.h"

using namespace cocos2d;

class PartService : public CCObject {
    
public:
    virtual void addPart(PartInterface* _part);
    virtual void removePart(PartInterface* _part);
    virtual ~PartService();
    static PartService* create();
protected:
    CCArray* parts;
    
};

#endif
