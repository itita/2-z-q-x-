//
//  PartInterface.cpp
//  ww2
//
//  Created by DingYu Fu on 12-9-12.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "PartInterface.h"

CCSize PartInterface::getPartSize() {
    return partSize;
}

void PartInterface::setPartSize(const cocos2d::CCSize &_partSize) {
    this->partSize = partSize;
}

CCPoint PartInterface::getPartPosition() {
    return CCPointZero;
}

