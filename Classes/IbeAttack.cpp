//
//  IbeAttack.cpp
//  ww2
//
//  Created by DingYu Fu on 12-9-13.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "IbeAttack.h"

float IbeAttack::getLife() {
    return life;
}

bool IbeAttack::setLife(float _life) {
    life = _life;
    if(life < 0) {
        return false;
    }
    return true;
}

void IbeAttack::setMaxLife(float maxLife) {
    this->maxLife = maxLife;
}