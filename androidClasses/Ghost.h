//
//  Ghost.h
//  ww4
//
//  Created by xiao tang on 13-5-24.
//
//

#ifndef __ww4__Ghost__
#define __ww4__Ghost__

#include <iostream>
#include "cocos2d.h"
#include "MyBuilding.h"
#include "MyBattleBuilding.h"

class Ghost {
    
public:
    static MyBuilding* createNormal(int resoucreCount);
    static MyBattleBuilding* createBattle(int resoucreCount);
};

#endif /* defined(__ww4__Ghost__) */
