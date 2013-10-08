//
//  AliveInterface.cpp
//  ww2
//
//  Created by DingYu Fu on 12-9-9.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "AliveInterface.h"


AliveInterface::AliveInterface() {
    alive = true;
}

bool AliveInterface::isAlive() {
    return alive;
}

void AliveInterface::dispose() {
    alive = false;
}

void AliveInterface::dispose(int var) {

}