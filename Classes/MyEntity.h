//
//  NewUnit.h
//  ww2
//
//  Created by DingYu Fu on 12-9-12.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#ifndef ww2_NewUnit_h
#define ww2_NewUnit_h
#include "cocos2d.h"
#include "NewMap.h"
#include "DeviceInterface.h"

using namespace cocos2d;

class MyEntity : public CCNode{
    
public:
    virtual ~MyEntity();
    virtual void setMap(NewMap* _map);
    virtual NewMap* getMap() {return map;};
    virtual void addDevice(DeviceInterface* device);
    virtual void removeDevice(DeviceInterface* device);
    static MyEntity* create();
private:
    NewMap* map;
};

#endif
