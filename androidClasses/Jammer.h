//
//  Jammer.h
//  ww4
//
//  Created by xiao tang on 13-9-23.
//
//

#ifndef __ww4__Jammer__
#define __ww4__Jammer__

#include "cocos2d.h"
#include "MyBuilding.h"
#include "MyBattleBuilding.h"
#include "MyBuildingCard.h"
#include "BuildingInfo.h"

#define JammerMaxCount 2

class Jammer  {
        
public:
    static MyBuilding* createNormal(CCObject* target,int level);
    static MyBattleBuilding* createBattle(int level,int stateId,float arg0);
    static MyBuildingCard* createCard(CCObject* target,SEL_MenuHandler selector);
    
    static void setUpdateInfo(GXFSMstate* state,CCLayer* updateLayer);
    static BuildingInfo* getJammerInfo();
    static void setBattleLevel(int level,GXFSM* fsm);
    static void setNormalLevel(int level,GXFSM* fsm);
private:
    static BuildingInfo* buildingInfo;
};

#endif /* defined(__ww4__Jammer__) */
