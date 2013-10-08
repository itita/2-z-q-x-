//
//  MyEntity.cpp
//  ww2
//
//  Created by DingYu Fu on 12-9-13.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "MyEntity.h"

MyEntity::~MyEntity() {
    CC_SAFE_RELEASE_NULL(map);
}

MyEntity* MyEntity::create() {
    MyEntity* entity = new MyEntity();
    entity->autorelease();
    return entity;
}

void MyEntity::addDevice(DeviceInterface *device) {
    CCNode* node = dynamic_cast<CCNode*>(device);
    CCAssert(node != NULL, "必须继承NODE，防止多继承才不能这样");
    addChild(node);
    device->onInstall(this);
}

void MyEntity::setMap(NewMap *_map) {
    CC_SAFE_RELEASE_NULL(map);
    map = _map;
    CC_SAFE_RETAIN(map);
}

void MyEntity::removeDevice(DeviceInterface *device){

}