//
//  JammerDefend.cpp
//  ww4
//
//  Created by xiao tang on 13-9-25.
//
//

#include "JammerDefend.h"
#include "cocos2d.h"
#include "GXAnimateFX.h"
#include "MyBattleMap.h"
#include "Mathlib.h"
#include "GXUtil.h"
#include "DefineSet.h"
#include "GarbageResourceCollection.h"


JammerDefend* JammerDefend::create(int _stateId, CCSprite* item,CCString* name,float life,float attackRange,float damage,float attackRate,int _maxTarget,int _sfxId) {
    JammerDefend* pState = new JammerDefend();
    pState->stateId = _stateId;
    pState->autorelease();
    pState->life = life;
    pState->maxLife = life;
    pState->attackRange = attackRange;
    pState->damage = damage;
    pState->name = name;
    pState->maxTarget = _maxTarget;
    CC_SAFE_RETAIN(name);
    //    pState->animateRate = animateRate;
    pState->doStateTime = attackRate;
    pState->sfxId = _sfxId;
    sprintf(pState->sfx, "%s",name->getCString());
    //  CCSprite* grayBd = CCSprite::create(string);
    //    grayBd->setColor(ccGRAY);
    pState->item = item;
    pState->targetArray = CCArray::create();
    pState->targetArray->retain();
    pState->lightPool = CCArray::create();
    pState->lightPool->retain();
    pState->toRemoveTargetArray = CCArray::create();
    pState->toRemoveTargetArray->retain();
    
    if (GXUtil::loadResourceUtilSucc("lightning.plist","lightning.pvr.ccz")) {
        GarbageResourceCollection::getInstance()->addGarbage("lightning.plist",CCString::create("lightning.pvr.ccz"));
    }
    
    CC_SAFE_RETAIN(item);
    return pState;
}

void JammerDefend::setItem(CCSprite *_item) {
    building->removeChildByTag(mainTiledSpriteTag, true);
    CC_SAFE_RELEASE(item);
    this->item = _item;
    _item ->setTag(mainTiledSpriteTag);
    _item->retain();
    building->addChild(_item,10);
    //    xuetiao->removeFromParentAndCleanup(true);
    //    _item->addChild(xuetiao,10);
}

void JammerDefend::doState() {
    if(building->isAlive()) {
        CCObject* obj;
        CCARRAY_FOREACH(targetArray,obj){
            MyUnit* unit = (MyUnit*)((CCNode*)obj)->getUserObject();
            if(!unit->isAlive()){
                unit->resumeSchedulerAndActions();
                ((CCNode*)obj)->removeFromParentAndCleanup(true);
                toRemoveTargetArray->addObject(obj);
                returnLight((CCSprite*)obj);
            } else{
                unit->fxCount = 0;
            }
        }
        if(toRemoveTargetArray->count()>0){
            targetArray->removeObjectsInArray(toRemoveTargetArray);
            toRemoveTargetArray->removeAllObjects();
        }
        if (targetArray->count() < maxTarget) {
//            setTarget(rangeTarget());
//            CCLog("COUNT:%d",targetArray->count());
            rangeTarget();
        }
        if (targetArray->count() > 0 && playjiange >= 1) {
            ((MyBattleMap*)building->map)->playUnitEffect(sfx,sfxId);
            playjiange = 0;
        } else {
            playjiange++;
        }
//        else {
//            CCLog("怪我咯2？");
//        }
        
    }
    //
}

MyUnit* JammerDefend::rangeTarget() {
    
    MyBattleMap* battleMap = (MyBattleMap*)building->map;
    CCArray* units = battleMap->getUnits();
    CCObject* object;
    MyUnit* targetUnit;
    //    float minDistance = 9999999;
    CCPoint buildPosi = battleMap->transMapToTiled(building->getPosition());
    CCPoint targetPosi;
    CCARRAY_FOREACH(units, object) {
        targetUnit = (MyUnit*)(object);
        //        distance = battleMap->transMapToTiled(unit->getPosition())-battleMap->transMapToTiled(building->getPosition());
        targetPosi =  battleMap->transMapToTiled(targetUnit->getPosition());
        if (targetUnit->mode == heavyVehicles && targetUnit->bufferState != 1 && targetUnit->isAlive() && Mathlib::getDistance(buildPosi,targetPosi) < attackRange) {
//            float angle = Mathlib::getAngle(building->getPosition(),targetUnit->getPosition());>
            CCPoint p1 = ccp(building->getPosition().x,building->getPosition().y+this->item->getContentSize().height*(1-this->item->getAnchorPoint().y)-20);
            float angle = Mathlib::getAngle(p1,targetUnit->getPosition());
            //            int dir = (((int)(angle*180/3.141592654+22.5)+360)%360)/45 ;
            //            CCAction* action = CCSequence::create(getFireAnimate(dir),CCCallFunc::create(this,callfunc_selector(DefendState::attackTarget)),NULL);
            float length = Mathlib::getDistance(p1,targetUnit->getPosition());
            CCSprite* light = getLight();
            GXUtil::initAction("lightning", 0.1,false);
            light->runAction(CCRepeatForever::create(CCAnimate::create(GXUtil::initAction("lightning", 0.1,false))));
            light->setAnchorPoint(ccp(0.5,0.95));
            light->setPosition(p1);
            light->setScaleY(length/light->getContentSize().height);
            light->setScaleX(0.8);
            light->setOpacity(190);
            light->setRotation((angle*180)/3.141592654+180);
            light->setUserObject(targetUnit);
            
            targetArray->addObject(light);
            targetUnit->pauseSchedulerAndActions();
            targetUnit->bufferState = 1;
            building->getParent()->addChild(light,9999999);
//            return  targetUnit;
            if (targetArray->count() >= maxTarget) {
                CCLog("X:%d",targetArray->count());
                return NULL;
            }
        }
    }
    return NULL;
}

void JammerDefend::doEnd() {
    CCObject* obj;
    CCARRAY_FOREACH(targetArray,obj){
        MyUnit* unit = (MyUnit*)((CCNode*)obj)->getUserObject();
        if(unit->isAlive()){
            unit->resumeSchedulerAndActions();
        }
        ((CCNode*)obj)->removeFromParentAndCleanup(true);
        returnLight((CCSprite*)obj);
    }
    targetArray->removeAllObjects();
}

CCSprite* JammerDefend::getLight() {
    if (lightPool->count() > 0) {
        CCSprite* light = (CCSprite*)lightPool->lastObject();
        light->retain();
        lightPool->removeLastObject();
        return light;
    } else {
        CCSprite* light = CCSprite::createWithSpriteFrameName("lightning (1).png");
        light->retain();
        return light;
    }
}

void JammerDefend::returnLight(CCSprite* light) {
    light->setUserObject(NULL);
    lightPool->addObject(light);
    light->release();
}