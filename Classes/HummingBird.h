//
//  HummingBird.h
//  ww4
//
//  Created by xiao tang on 13-5-10.
//
//

#ifndef __ww4__HummingBird__
#define __ww4__HummingBird__

#include <iostream>
#include "UnitBean.h"

#define HummingBirdCardId 19

class HummingBird {
    
public:
    static MyUnit* createUnit(int level);
    static CCAnimate* getFireAnimate(int dir);
    static CCAnimate* getMoveAnimate(int dir);
    static CCAnimate* getDieAnimate(int dir);
    static UnitBean* getUnitBean();
    static CCLayer* getUnitCardDesc(int level,bool isAll);
    static CCSprite* getAttackSprite(int dir);
private:
    static UnitBean* unitBean;
};

#endif /* defined(__ww4__HummingBird__) */
