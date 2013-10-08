//
//  Volksgrenadier.h
//  ww4
//
//  Created by xiao tang on 13-6-18.
//
//

#ifndef __ww4__Volksgrenadier__
#define __ww4__Volksgrenadier__

#include "MyUnit.h"
#include "UnitBean.h"

#define volksgrenaierCardId 50

class Volksgrenaier {
    
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

#endif /* defined(__ww4__Volksgrenadier__) */
