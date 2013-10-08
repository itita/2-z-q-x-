//
//  M3HalfTrack.h
//  ww4
//
//  Created by xiao tang on 13-5-9.
//
//

#ifndef __ww4__M3HalfTrack__
#define __ww4__M3HalfTrack__

#include <iostream>

#include "MyUnit.h"
#include "UnitBean.h"

#define M3HalfTrackCardId 14

class M3HalfTrack {
    
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

#endif /* defined(__ww4__M3HalfTrack__) */
