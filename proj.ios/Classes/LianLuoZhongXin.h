//
//  LianLuoZhongXin.h
//  ww4
//
//  Created by xiao tang on 13-5-3.
//
//

#ifndef __ww4__LianLuoZhongXin__
#define __ww4__LianLuoZhongXin__

#include <iostream>
#include "cocos2d.h"
#include "MyBuilding.h"
#include "MyBattleBuilding.h"
#include "MyBuildingCard.h"

class LianLuoZhongXin {
    
public:
    static MyBuilding* createNormal(CCObject* target,int level);
    static MyBattleBuilding* createBattle(int level,int stateId);
    static MyBuilding* createDestroy(CCObject* target,int level);
    static MyBattleBuilding* createBattleDestroy(int level,int stateId);
    static MyBuildingCard* createCard(CCObject* target,SEL_MenuHandler selector);
    static void setUpdateInfo(GXFSMstate* state,CCLayer* updateLayer);
};

#endif /* defined(__ww4__LianLuoZhongXin__) */
