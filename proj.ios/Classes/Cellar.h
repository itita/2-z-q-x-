//
//  Cellar.h
//  ww4
//
//  Created by xiao tang on 13-7-5.
//
//

#ifndef __ww4__Cellar__
#define __ww4__Cellar__

#include "cocos2d.h"
#include "MyBuilding.h"
#include "MyBattleBuilding.h"
#include "MyBuildingCard.h"
#include "BuildingInfo.h"

#define CellarMaxCount 1

class Cellar {
public:
    static MyBuilding* createNormal(CCObject* target,int level);
    static MyBattleBuilding* createBattle(int level,int stateId,float arg0);
    static MyBuildingCard* createCard(CCObject* target,SEL_MenuHandler selector);
//    static void setBattleLevel(int level,GXFSM* fsm);
    static void setUpdateInfo(GXFSMstate* state,CCLayer* updateLayer);
    static BuildingInfo* getCellarInfo();
private:
    static BuildingInfo* buildingInfo;
};

#endif /* defined(__ww4__Cellar__) */
