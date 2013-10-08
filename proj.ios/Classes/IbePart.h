//
//  IbePart.h
//  ww2
//
//  Created by DingYu Fu on 12-9-13.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#ifndef ww2_IbePart_h
#define ww2_IbePart_h
#include "PartInterface.h"

class IbePart  {
    
public:
    virtual PartInterface* getPart();
    virtual void hit(PartInterface* attacker);
};

#endif
