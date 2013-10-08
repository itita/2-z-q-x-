//
//  PartService.cpp
//  ww2
//
//  Created by DingYu Fu on 12-9-13.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "PartService.h"

PartService::~PartService() {
    parts->release();
}

void PartService::addPart(PartInterface *_part) {
    CCNode* obj = dynamic_cast<CCNode*>(_part);
    CCAssert(obj!=NULL, "part must extend ccnode,为了避免多继承，part必须继承node");
    parts->addObject(obj);
}

void PartService::removePart(PartInterface *_part) {
    CCNode* obj = dynamic_cast<CCNode*>(_part);
    CCAssert(obj!=NULL, "part must extend ccnode,为了避免多继承，part必须继承node");
    parts->removeObject(obj);
}

PartService* PartService::create() {
    PartService* partService = new PartService();
    partService->autorelease();
    partService->parts = CCArray::create();
    partService->parts ->retain();
    return partService;
}