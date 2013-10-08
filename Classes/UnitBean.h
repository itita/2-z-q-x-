//
//  UnitBean.h
//  ww4
//
//  Created by xiao tang on 13-5-8.
//
//

#ifndef __ww4__UnitBean__
#define __ww4__UnitBean__

#include <iostream>
#include "cocos2d.h"
#include "GXAntiCrack.h"
#include "DefineSet.h"
#include "MyUnit.h"

using namespace cocos2d;

typedef MyUnit* (*SEL_CreateUnit)(int);
typedef CCLayer* (*SEL_GetUnitCardInfo)(int,bool);
typedef CCSprite* (*SEL_GetAttackSprite)(int);
typedef float (*SEL_GetCostCool)(int);

class UnitBean : public CCObject{
public:
    
    UnitBean():
//    updateHealthRate(0),
//    updateDamageRate(0),
    updateCostRate(0),
//    updateSpeedRate(0),
//    moveAnimateRate(0.1),
//    fireAnimateRate(0.1),
//    dieAnimateRate(0.1),
//    moveAnimateReverse(false),
//    fireAnimateReverse(false),
//    dieAnimateRerverse(false),
    //    fxArray(NULL),
    name(NULL),
//    sfxDeployName(NULL),
    spriteFileName(NULL),
//    sfxFireName(NULL),
    unlockCostResourceTag(gloryTag),
    unlockCostCount(10),
    unlockNeedResourceTag(levelTag),
    unlockNeedCount(0),
    summaryOil(0),
    summaryOriOil(0),
    costCool(1),
    createUnit_selector(NULL),
    getUnitCardInfo_selector(NULL),
    getAttackSprite_selector(NULL),
    getCostCool_selector(NULL){
//        summaryOil = GXintValue::create(0);
//        summaryOil->retain();
        rarity =GXintValue::create(1);
        rarity->retain();
//        speed = GXfloatValue::create(0);
//        speed->retain();
//        attackRange = GXfloatValue::create(0);
//        attackRange->retain();
//        damage = GXfloatValue::create(0);
//        damage->retain();
//        life = GXfloatValue::create(0);
//        life->retain();
    }
    
    //    int battleCreateCount;
//    //    int summaryOil;
    //    int rarity;
    //    float speed;
    //    float attackRange;
    //    float damage;
    //    float life;
//    float moveAnimateRate;
//    float fireAnimateRate;
//    float dieAnimateRate;
    int unlockCostResourceTag;
    float unlockCostCount;
    int unlockNeedResourceTag;
    float unlockNeedCount;
//    bool moveAnimateReverse;
//    bool fireAnimateReverse;
//    bool dieAnimateRerverse;
    int cardId;
    
//    CCArray* fxArray;
    
    static UnitBean* create(int cardId,CCString* name,CCString* _spriteFileName,int summaryOil,float _updateCostRate,int rarity);
    static UnitBean* create();
    //    static UnitCreator* create(SEL_CreateUnit _createUnit_selector);
    //    virtual MyUnit* createUnit();
    MyUnit* createObj(int level);
    CCLayer* getUnitCardInfo(int level,bool isAll);
    ~UnitBean();
    const char* getSpriteFileName();
    const char* getName();

    void setSpriteFileName(CCString* _spriteFileName);

    void setName(CCString* name);
    
//    float updateHealthRate;
//    float updateDamageRate;
    float updateCostRate;
//    float updateSpeedRate;
    
    void setSummaryOil(int _summaryOil) {
//        summaryOil->setValue(_summaryOil);
        summaryOil = _summaryOil;
    }
    
    int getSummaryOil() {
//        return summaryOil->getValue();
        return summaryOil;
    }
    
    void setRarity(int _rarity) {
        rarity->setValue(_rarity);
    }
    
    int getRarity() {
        return rarity->getValue();
    }
    
    CCSprite* getAttackSprite(int dir);
    
//    void setSpeed(float _speed) {
//        speed->setValue(_speed);
//    }
//    
//    float getSpeed() {
//        return speed->getValue();
//    }
//    
//    void setAttackRange(int _attackRange) {
//        attackRange->setValue(_attackRange);
//    }
//    
//    float getAttackRange() {
//        return attackRange->getValue();
//    }
//    
//    void setDamage(int _damage) {
//        damage->setValue(_damage);
//    }
//    
//    float getDamage() {
//        return damage->getValue();
//    }
//    
//    void setLife(int _life) {
//        life->setValue(_life);
//    }
//    
//    int getLife() {
//        return life->getValue();
//    }
    
    int getMaxLevel() {
        return getRarity()*5;
    }
    
    SEL_CreateUnit createUnit_selector;
    SEL_GetUnitCardInfo getUnitCardInfo_selector;
    SEL_GetAttackSprite getAttackSprite_selector;
    SEL_GetCostCool getCostCool_selector;
    
    float getCostCool(int level) {
        if (getCostCool_selector != NULL) {
            return (*getCostCool_selector)(level);
        }
        return costCool;
    }
    
    int summaryOriOil;
    std::string sfxDeployNameString;
    float costCool;
private:
    CCString* spriteFileName;
    CCString* name;
    int summaryOil;
    GXintValue* rarity;
//    GXfloatValue* speed;
//    GXfloatValue* attackRange;
//    GXfloatValue* damage;
//    GXfloatValue* life;
};

#endif /* defined(__ww4__UnitBean__) */
