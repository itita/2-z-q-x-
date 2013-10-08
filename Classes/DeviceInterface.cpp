//
//  DeviceInterface.cpp
//  ww2
//
//  Created by DingYu Fu on 12-9-12.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "DeviceInterface.h"
#include "MyEntity.h"


void DeviceInterface::onInstall(CCNode *_entity) {
    MyEntity* entity = dynamic_cast<MyEntity*>(_entity);
    CCAssert(entity != NULL, "parent must be ENTITY");
}

void DeviceInterface::onRemove(CCNode *_entity) {
    MyEntity* entity = dynamic_cast<MyEntity*>(_entity);
    CCAssert(entity != NULL, "parent must be ENTITY");
}