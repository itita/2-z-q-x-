//
//  CombineWall.h
//  ww4
//
//  Created by xiao tang on 13-5-3.
//
//

#ifndef __ww4__CombineWall__
#define __ww4__CombineWall__

#include <iostream>
#include "cocos2d.h"
#include "MyBuilding.h"
#include "MyBattleBuilding.h"
#include "MyBuildingCard.h"

class CombineWall {
    
public:
    static MyBuilding* createNormal(int tag,CCObject* target,int level);
    static MyBattleBuilding* createBattle(int tag,int level,int stateId);
    static void setBattleLevel(int level,GXFSM* fsm);
    static void setUpdateInfo(GXFSMstate* state,CCLayer* updateLayer);
};

#endif /* defined(__ww4__CombineWall__) */
