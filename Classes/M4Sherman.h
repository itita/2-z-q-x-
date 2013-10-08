//
//  M4Sherman.h
//  ww4
//
//  Created by xiao tang on 13-5-9.
//
//

#ifndef __ww4__M4Sherman__
#define __ww4__M4Sherman__

#include "MyUnit.h"
#include "UnitBean.h"

#define M4ShermanCardId 13

class M4Sherman {
    
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


#endif /* defined(__ww4__M4Sherman__) */
