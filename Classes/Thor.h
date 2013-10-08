//
//  Thor.h
//  ww4
//
//  Created by xiao tang on 13-9-5.
//
//

#ifndef __ww4__Thor__
#define __ww4__Thor__

#include "MyUnit.h"
#include "UnitBean.h"

#define ThorCardId 23

class Thor : public CCObject {
    
public:
    static MyUnit* createUnit(int level);
    static CCAnimate* getFireAnimate(int dir);
    static CCAnimate* getMoveAnimate(int dir);
    static CCAnimate* getDieAnimate(int dir);
    static UnitBean* getUnitBean();
    static CCLayer* getUnitCardDesc(int level,bool isAll);
    static CCSprite* getAttackSprite(int dir);
    static float getCostCool(int level);
private:
    static UnitBean* unitBean;
};

#endif /* defined(__ww4__Thor__) */
