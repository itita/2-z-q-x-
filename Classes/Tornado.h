//
//  Tornado.h
//  ww4
//
//  Created by xiao tang on 13-9-3.
//
//

#ifndef __ww4__Tornado__
#define __ww4__Tornado__

#include "MyUnit.h"
#include "UnitBean.h"

#define tornadoCardId 22

class Tornado : public CCObject {
    
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

#endif /* defined(__ww4__Tornado__) */
