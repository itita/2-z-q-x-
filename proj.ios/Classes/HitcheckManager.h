//
//  HitcheckManager.h
//  ww2
//
//  Created by DingYu Fu on 12-9-12.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#ifndef ww2_HitcheckManager_h
#define ww2_HitcheckManager_h
#include "PartInterface.h"

class HitcheckManager {
    
    
public:
    static HitcheckManager* getInstance();
    static void release();
    virtual bool hitCheck(PartInterface* part1,PartInterface* part2);
private:
    
    HitcheckManager();
};

#endif
