//
//  DiaoBao.h
//  ww4
//
//  Created by xiao tang on 13-5-3.
//
//

#ifndef __ww4__DiaoBao__
#define __ww4__DiaoBao__

#include <iostream>
#include "cocos2d.h"
#include "MyBuilding.h"
#include "MyBattleBuilding.h"
#include "MyBuildingCard.h"

class DiaoBao {
    
public:
    static MyBuilding* createNormal(CCObject* target,int level);
    static MyBattleBuilding* createBattle(int level,int stateId);
    static MyBuildingCard* createCard(CCObject* target,SEL_MenuHandler selector);
    static void setBattleLevel(int level,GXFSM* fsm);
    static void setUpdateInfo(GXFSMstate* state,CCLayer* updateLayer);
    static CCAnimate* getFireAnimate(int dir);
};

#endif /* defined(__ww4__DiaoBao__) */
