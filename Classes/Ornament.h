//
//  Ornament.h
//  ww4
//
//  Created by xiao tang on 13-5-4.
//
//

#ifndef __ww4__Ornament__
#define __ww4__Ornament__

#include <iostream>
#include "cocos2d.h"
#include "MyBuilding.h"
#include "MyBattleBuilding.h"

class Ornament {
    
public:
    static MyBuilding* createNormal(int tag,CCObject* target);
    static MyBattleBuilding* createBattle(int tag,int level,int stateId);
};

#endif /* defined(__ww4__Ornament__) */
