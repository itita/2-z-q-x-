//
//  NewMap.cpp
//  ww2
//
//  Created by DingYu Fu on 12-9-13.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "NewMap.h"
#include "MyEntity.h"
#include "DeviceInterface.h"

NewMap::~NewMap() {
    CC_SAFE_RELEASE_NULL(partService);
}

void NewMap::addChild(cocos2d::CCNode *child) {
    GXScrollTMXTileMap::addChild(child);
    MyEntity* entity = dynamic_cast<MyEntity*>(child);
    CCAssert(entity != NULL, "only allow entity");
    CCArray* array = entity->getChildren();
    CCObject* obj;
    DeviceInterface* device;
    CCARRAY_FOREACH(array, obj) {
        device = ((DeviceInterface*)obj);
        device->onInstall(entity);
    }
}

void NewMap::initMap() {
    partService = PartService::create();
    CC_SAFE_RETAIN(partService);
}


