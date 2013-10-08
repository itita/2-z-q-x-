//
//  M5Stuart.h
//  ww4
//
//  Created by xiao tang on 13-5-8.
//
//

#ifndef __ww4__M5Stuart__
#define __ww4__M5Stuart__

#include <iostream>
#include "MyUnit.h"
#include "UnitBean.h"

#define M5StuartCardId 12

class M5Stuart {
    
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

#endif /* defined(__ww4__M5Stuart__) */
