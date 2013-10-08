//
//  DaPao.h
//  ww4
//
//  Created by xiao tang on 13-5-3.
//
//

#ifndef __ww4__DaPao__
#define __ww4__DaPao__

#include <iostream>
#include "cocos2d.h"
#include "MyBuilding.h"
#include "MyBattleBuilding.h"
#include "MyBuildingCard.h"

class DaPao {
    
public:
    static MyBuilding* createNormal(CCObject* target,int level);
    static MyBattleBuilding* createBattle(int level,int stateId);
    static MyBuilding* createReady(CCObject* target,int level);
    static MyBuildingCard* createCard(CCObject* target,SEL_MenuHandler selector);
    static void setBattleLevel(int level,GXFSM* fsm);
    static void setUpdateInfo(GXFSMstate* state,CCLayer* updateLayer);
    static CCAnimate* getFireAnimate(int dir);
    static void setNormalLevel(int level,GXFSM* fsm);
};

#endif /* defined(__ww4__DaPao__) */
