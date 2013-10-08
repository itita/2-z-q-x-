//
//  Tiger.h
//  ww4
//
//  Created by xiao tang on 13-7-11.
//
//

#ifndef __ww4__Tiger__
#define __ww4__Tiger__

#define  TigerCardId 21

#include "MyUnit.h"
#include "UnitBean.h"

class Tiger {
    
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

#endif /* defined(__ww4__Tiger__) */
