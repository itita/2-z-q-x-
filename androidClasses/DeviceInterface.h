//
//  DeviceInterface.h
//  ww2
//
//  Created by DingYu Fu on 12-9-12.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//


#define TiledMenuItemTag 10
#ifndef ww2_DeviceInterface_h
#define ww2_DeviceInterface_h
//#include "MyEntity.h"
#include "cocos2d.h"

using namespace cocos2d;

class DeviceInterface {
    
public:
    virtual void onInstall(CCNode* entity);
    virtual void onRemove(CCNode* entity);
};

#endif
