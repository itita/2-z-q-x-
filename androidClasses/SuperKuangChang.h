//
//  SuperKuangChang.h
//  ww4
//
//  Created by xiao tang on 13-5-4.
//
//

#ifndef __ww4__SuperKuangChang__
#define __ww4__SuperKuangChang__

#include <iostream>
#include "cocos2d.h"
#include "MyBuildingCard.h"
#include "MyBuilding.h"
#include "MyBattleBuilding.h"
#include "BuildingInfo.h"

class SuperKuangChang {
    
public:
    static MyBuilding* createNormal(CCObject* target,int level,float ori,long dt);
    static MyBattleBuilding* createBattle(int level,int stateId,float ori,float rate);
    static MyBuildingCard* createCard(CCObject* target,SEL_MenuHandler selector);
    static void setNormalLevel(int level,GXFSM* fsm);
    static void setBattleLevel(int level,GXFSM* fsm);
    static void setUpdateInfo(GXFSMstate* state,CCLayer* updateLayer);
    static BuildingInfo* getSuperKuangChangInfo();
private:
    static BuildingInfo* buildingInfo;
};

#endif /* defined(__ww4__SuperKuangChang__) */
