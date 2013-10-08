//
//  GarbageCenter.h
//  ww4
//
//  Created by xiao tang on 13-5-25.
//
//

#ifndef __ww4__GarbageCenter__
#define __ww4__GarbageCenter__

#include "cocos2d.h"
#include "MyBuilding.h"
#include "MyBattleBuilding.h"
#include "MyBuildingCard.h"
#include "BuildingInfo.h"

#define garbageCenterMaxCount 1

class GarbageCenter {
    
public:
    static MyBuilding* createNormal(CCObject* target,int level);
    static MyBattleBuilding* createBattle(int level,int stateId);
    static MyBuildingCard* createCard(CCObject* target,SEL_MenuHandler selector);
    static void setBattleLevel(int level,GXFSM* fsm);
    static void setUpdateInfo(GXFSMstate* state,CCLayer* updateLayer);
    static BuildingInfo* getGarbageCenterInfo();
private:
    static BuildingInfo* buildingInfo;
};

#endif /* defined(__ww4__GarbageCenter__) */
