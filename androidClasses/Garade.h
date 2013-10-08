//
//  Garade.h
//  ww4
//
//  Created by xiao tang on 13-5-7.
//
//

#ifndef __ww4__Garade__
#define __ww4__Garade__

#include <iostream>
#include "MyUnit.h"
#include "UnitBean.h"

#define garadeCardId 11




class Garade {
    
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


#endif /* defined(__ww4__Garade__) */
