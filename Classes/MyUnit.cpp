//
//  MyUnit.cpp
//  ww2
//
//  Created by DingYu Fu on 12-9-4.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "MyUnit.h"
#include "cocos2d.h"
#include "MyUnitState.h"
#include "MoveToAttack.h"
#include "AttackState.h"
#include "GXUtil.h"
#include "SimpleAudioEngine.h"
#include "MyGameInfo.h"
#include "MyUnit.h"
#include "MyGameFactory.h"
#include "MyUtil.h"
#include "NoResourceToDeployMessage.h"
#include "GXAnimateWithFx.h"
#include "MathLib.h"

MyUnit::~MyUnit() {
    fsm->release();
    CC_SAFE_RELEASE_NULL(die);
    for (int i = 0; i<8; ++i) {
        
        CC_SAFE_RELEASE_NULL(move[i]);
        CC_SAFE_RELEASE_NULL(fire[i]);
//        CC_SAFE_RELEASE_NULL(die[i]);
        
    }
//目前就一个爆炸
//    die[0]->release();
//    delete [] move;
//    delete [] fire;
//    delete [] die;
//    CCLog("unit 死求鸡公");

    
    //这货内存有泄露
    
}

MyUnit* MyUnit::create(GXFSMstate *state,float life,float _aiRate,int _level) {
    //todo: 把ACTION给持久化
    MyUnit* unit = new MyUnit();
    
//    sprintf(str, "%s (0).png",spriteFileName);
//    unit->initWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(str));
    unit->init();
//    unit->speed = _speed;
    unit -> autorelease();
//    unit->alive = true;
    unit->life = life;
    unit->maxLife = life;
    unit->aiRate = _aiRate;
    unit->level = _level;
//    char str[64] = {0};
//    sprintf(str, "%smld",spriteFileName);
//    unit->move[0] = GXUtil::initAction(str,0.1);
//    CC_SAFE_RETAIN(unit->move[0]);
//    
//    sprintf(str, "%smd",spriteFileName);
//    unit->move[1] = GXUtil::initAction(str,0.1);
//    CC_SAFE_RETAIN(unit->move[1]);
//    
//    sprintf(str, "%smrd",spriteFileName);
//    unit->move[2] = GXUtil::initAction(str,0.1);
//    CC_SAFE_RETAIN(unit->move[2]);
//    
//    sprintf(str, "%smr",spriteFileName);
//    unit->move[3] = GXUtil::initAction(str,0.1);
//    CC_SAFE_RETAIN(unit->move[3]);
//    
//    sprintf(str, "%smru",spriteFileName);
//    unit->move[4] = GXUtil::initAction(str,0.1);
//    CC_SAFE_RETAIN(unit->move[4]);
//    
//    sprintf(str, "%smu",spriteFileName);
//    unit->move[5] = GXUtil::initAction(str,0.1);
//    CC_SAFE_RETAIN(unit->move[5]);
//    
//    sprintf(str, "%smlu",spriteFileName);
//    unit->move[6] = GXUtil::initAction(str,0.1);
//    CC_SAFE_RETAIN(unit->move[6]);
//    
//    sprintf(str, "%sml",spriteFileName);
//    unit->move[7] = GXUtil::initAction(str,0.1);
//    CC_SAFE_RETAIN(unit->move[7]);
//    
//    
//    sprintf(str, "%sfld",spriteFileName);
//    unit->fire[0] = GXUtil::initAction(str,0.1);
//    CC_SAFE_RETAIN(unit->fire[0]);
//    
//    sprintf(str, "%sfd",spriteFileName);
//    unit->fire[1] = GXUtil::initAction(str,0.1);
//    CC_SAFE_RETAIN(unit->fire[1]);
//    
//    sprintf(str, "%sfrd",spriteFileName);
//    unit->fire[2] = GXUtil::initAction(str,0.1);
//    CC_SAFE_RETAIN(unit->fire[2]);
//    
//    sprintf(str, "%sfr",spriteFileName);
//    unit->fire[3] = GXUtil::initAction(str,0.1);
//    CC_SAFE_RETAIN(unit->fire[3]);
//    
//    sprintf(str, "%sfru",spriteFileName);
//    unit->fire[4] = GXUtil::initAction(str,0.1);
//    CC_SAFE_RETAIN(unit->fire[4]);
//    
//    sprintf(str, "%sfu",spriteFileName);
//    unit->fire[5] = GXUtil::initAction(str,0.1);
//    CC_SAFE_RETAIN(unit->fire[5]);
//    
//    sprintf(str, "%sflu",spriteFileName);
//    unit->fire[6] = GXUtil::initAction(str,0.1);
//    CC_SAFE_RETAIN(unit->fire[6]);
//    
//    sprintf(str, "%sfl",spriteFileName);
//    unit->fire[7] = GXUtil::initAction(str,0.1);
//    CC_SAFE_RETAIN(unit->fire[7]);
//    
//    sprintf(str, "%sdld",spriteFileName);
//    unit->die[0] = GXUtil::initAction(str,0.1);
//    CC_SAFE_RETAIN(unit->die[0]);
//    
//    sprintf(str, "%sdd",spriteFileName);
//    unit->die[1] = GXUtil::initAction(str,0.1);
//    CC_SAFE_RETAIN(unit->die[1]);
//    
//    sprintf(str, "%sdrd",spriteFileName);
//    unit->die[2] = GXUtil::initAction(str,0.1);
//    CC_SAFE_RETAIN(unit->die[2]);
//    
//    sprintf(str, "%sdr",spriteFileName);
//    unit->die[3] = GXUtil::initAction(str,0.1);
//    CC_SAFE_RETAIN(unit->die[3]);
//    
//    sprintf(str, "%sdru",spriteFileName);
//    unit->die[4] = GXUtil::initAction(str,0.1);
//    CC_SAFE_RETAIN(unit->die[4]);
//    
//    sprintf(str, "%sdu",spriteFileName);
//    unit->die[5] = GXUtil::initAction(str,0.1);
//    CC_SAFE_RETAIN(unit->die[5]);
//    
//    sprintf(str, "%sdlu",spriteFileName);
//    unit->die[6] = GXUtil::initAction(str,0.1);
//    CC_SAFE_RETAIN(unit->die[6]);
//    
//    sprintf(str, "%sdl",spriteFileName);
//    unit->die[7] = GXUtil::initAction(str,0.1);
//    CC_SAFE_RETAIN(unit->die[7]);
    
//    bool flag = true;
//    int i = 0;
//    char str[64] = {0};
//    CCArray* array = CCArray::create();
//    while (flag) {
//        sprintf(str, "%sld (%d).png",spriteFileName,i);
//        CCSpriteFrame* sprite = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(str);
//        if(sprite == NULL) {
//            flag = false;
//        } else {
//            array->addObject(sprite);
//        }
//        i++;
//    }
//    this->move[0] = CCAnimation::create(array,0.1);
//    this->move[0]->retain();
//    i++;
//    for (int j =0; j<1; j++) {
//        CCArray* array = CCArray::create();
//        for (int i=0; i<7; i++) {
////            CCLog("%s (%d).png",spriteFileName);
////            sprintf(str, "%s (%d).png",spriteFileName,15*j+i);
//            sprintf(str, "%s (%d).png",spriteFileName,15*j+i);
//            CCSpriteFrame* sprite = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(str);
//            array->addObject(sprite);
////            CCLog(str);
//            //        CCSprite* aaa =  CCSprite::create(sprite);
//        }
//        unit->move[j] = CCAnimation::create(array,0.1);
//        unit->move[j]->retain();
//    }
//    CCAction* action = CCRepeatForever::create(unit->move[0]);
//    action->setTag(currentAction);
//    unit->runAction(action);
    
    unit->schedule(schedule_selector(MyUnit::doAI),_aiRate);
//    test->
//    move =
    //初始化状态机
    MyUnitState* myState = dynamic_cast<MyUnitState*>(state);
    CCAssert(myState != NULL, "这里只能传UNITSTATE");
    myState->init(unit);
    unit->fsm = GXFSM::create(myState);
    unit->fsm->retain();  
    return unit;
}

void MyUnit::runMoveAnimate(int direction) {
    if(dir == direction) {
        return;
    }
    this->stopActionByTag(currentActionTag);
    if (move[direction] == NULL) {
        move[direction] = (*moveAnimateCreator)(direction);
        move[direction]->retain();
    }
    CCAction* action = CCRepeatForever::create(this->move[direction]);
    action->setTag(currentActionTag);
    dir = direction;
    this->runAction(action);
}

bool MyUnit::setLife(float life) {
    this->life = life;
    if(life < 0) {
//        this->dispose();
        return false;
    }
    return true;
}

void MyUnit::disposeNoFx() {
    //播放死亡动画~然后死掉这样可以防止野指针，通过ALIVE先去掉调用，然后在死

        
    //从目标集合中删除
    
    MyBattleMap* battleMap = (MyBattleMap*)getParent();
    battleMap->getUnits()->removeObject(this);
    AliveInterface::dispose();
    this->removeFromParentAndCleanup(true);
    
    //删除子状态对自己的持有,这样不好，因为 子类的析构还会放弃对自己的引用，不过也不一定，因为是SAFE释放~也不是太恼火。,日 你个垃圾，被你弄成循环持有了
    
    fsm->stateMap->removeAllObjects();
    
//    changeState(toRuinsTransition);
}

void MyUnit::dispose() {
    removeAllChildrenWithCleanup(true);
    stopAllActions();
    
    runAction(CCSequence::create(CCSpawn::create(runDisposeAnimate(),CCFadeOut::create(2),NULL),CCCallFunc::create(this,callfunc_selector(MyUnit::removeThis)),NULL));
    //从目标集合中删除
    MyBattleMap* battleMap = (MyBattleMap*)getParent();
    battleMap->getUnits()->removeObject(this);
    AliveInterface::dispose();
//    fsm->stateMap->removeAllObjects();
//    this->unschedule(schedule_selector(MyUnit::doAI));
//    battleMap->addGhost(Mathlib::roundPoint(battleMap->transMapToTiled(this->getPosition())));
}

void MyUnit::removeThis() {
    this->removeFromParentAndCleanup(true);
}

CCAnimate* MyUnit::runFireAnimate(int direction) {
    this->stopActionByTag(currentActionTag);
    dir = direction*10+10;
    if (fire[direction] == NULL) {
        fire[direction] = (*fireAnimateCreator)(direction);
        fire[direction]->retain();
    }
    
    this->fire[direction]->setTag(currentActionTag);
    return this->fire[direction];
}

CCAnimate* MyUnit::runDisposeAnimate() {
    this->stopActionByTag(currentActionTag);
    if (dir>=10) {
        dir = (dir-10)/10;
    }
    if (die == NULL) {
        die = (*dieAnimateCreator)(dir);
        die->retain();
    } else {
        CCLog("你玩复活？");
    }
    this->die->setTag(currentActionTag);
    return this->die;
}

void MyUnit::doAI() {
//    CCLog("DOAI");
//    this->stopActionByTag(currentAction);
//    this->runMoveAnimate(arc4random()%5);
    if (isAlive()) {
        fxCount = 0;
        fsm->getCurrentState()->doState();
    } else {
        this->unschedule(schedule_selector(MyUnit::doAI));
        MyBattleMap* battleMap = (MyBattleMap*)getParent();
        battleMap->addGhost(Mathlib::roundPoint(deployPosi),Mathlib::roundPoint(battleMap->transMapToTiled(this->getPosition())),this->cost);
    }
}

void MyUnit::addState(GXFSMstate *state) {
    MyUnitState* mystate = (MyUnitState*)state;
    fsm->addState(state);
    mystate->init(this);
}

void MyUnit::changeState(int _inputId) {
    CCInteger* out = fsm->stateTransition(_inputId);
    MyUnitState* mystate = (MyUnitState*)(fsm->getState(out->getValue()));
//    MyUnitState* current = (MyUnitState*)(fsm->getCurrentState());
    fsm->getCurrentState()->doEnd();
    mystate->doStart();
    fsm->setCurrentState(mystate);
    //    this->map->moveTemp = mystate->item;
    //    this->map->getItems()->removeObject(current->item);
}

//CCAnimation* MyUnit::initAction(const char* _spritFrameName) {
//    char str[64] = {0};
//    CCArray* array = CCArray::create();
//    int i = 0;
//    while (true) {
////            CCLog("%s (%d).png",spriteFileName);
////            sprintf(str, "%s (%d).png",spriteFileName,15*j+i);
//        sprintf(str, "%s (%d).png",_spritFrameName,i);
//        CCSpriteFrame* sprite = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(str);
//        if(sprite == NULL) {
//            break;
//        } else {
//            array->addObject(sprite);
//        }
//        i++;
//    }
//    CCAnimation* animation = CCAnimation::createWithSpriteFrames(array, 0.1);
//    animation->retain();
//    return animation;
//}


//UnitBean::~UnitBean() {
//    //野指针问题
//    
//    
//    char str[30] = {0};
//    
//    sprintf(str, "%sbp.plist",spriteFileName->getCString());
//    CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile(str);
//    
//    sprintf(str, "%sbp.pvr.ccz",spriteFileName->getCString());
//    CCTextureCache::sharedTextureCache()->removeTextureForKey(str);
//    
//    CC_SAFE_RELEASE_NULL(sfxFireName);
//    
//    CC_SAFE_RELEASE_NULL(sfxDeployName);
//    
//    CC_SAFE_RELEASE_NULL(spriteFileName);
//    
//    CC_SAFE_RELEASE_NULL(fxArray);
//    
//    CC_SAFE_RELEASE_NULL(summaryOil);
//    CC_SAFE_RELEASE_NULL(rarity);
//    CC_SAFE_RELEASE_NULL(speed);
//    CC_SAFE_RELEASE_NULL(attackRange);
//    CC_SAFE_RELEASE_NULL(damage);
//    CC_SAFE_RELEASE_NULL(life);
//    CCLog("unit released");
//}
//
//UnitCreator* UnitCreator::create(int cardId,CCString* _spriteFileName,CCString* sfxDeployName,CCString* sfxFireName,float speed,float _attackRange,float damage,float life,int summaryOil) {
//    UnitCreator* creator = new UnitCreator();
//    creator->cardId=cardId;
//    creator->setSpriteFileName(_spriteFileName);
//    creator->autorelease();
//    creator->setSpeed(speed);
//    creator->setAttackRange(_attackRange);
//    creator->setDamage(damage);
//    creator->setLife(life);
//    creator->sfxDeployName = sfxDeployName;
//    creator->sfxDeployName->retain();
//    creator->sfxFireName = sfxFireName;
//    creator->sfxFireName->retain();
//    creator->fxArray  = CCArray::create();
//    creator->fxArray->retain();
//    creator->setSummaryOil(summaryOil);
//    
//    return creator;
//}
//
//UnitCreator* UnitCreator::create() {
//    UnitCreator* creator = new UnitCreator();
//    creator->autorelease();
//    creator->fxArray  = CCArray::create();
//    creator->fxArray->retain();
//    return creator;
//}
//
//
//
//
//void UnitCreator::setSpriteFileName(cocos2d::CCString *_spriteFileName) {
//    CC_SAFE_RELEASE_NULL(spriteFileName);
//    spriteFileName  = _spriteFileName;
//    // 加入兵牌数据
//    char str[30] = {0};
//    char str1[30] = {0};
//    sprintf(str, "%sbp.plist",_spriteFileName->getCString());
//    sprintf(str1, "%sbp.pvr.ccz",_spriteFileName->getCString());
//    GXUtil::loadResourceUtilSucc(str,str1);
//    spriteFileName->retain();
//}
//
//void UnitCreator::setSfxFireName(cocos2d::CCString *_sfxFireName) {
//    CC_SAFE_RELEASE_NULL(sfxFireName);
//    sfxFireName = _sfxFireName;
//    sfxFireName->retain();
//}
//
//void UnitCreator::setSfxDeployName(cocos2d::CCString *_sfxDeployName) {
//    CC_SAFE_RELEASE_NULL(sfxDeployName);
//    sfxDeployName = _sfxDeployName;
//    sfxDeployName->retain();
//}
//
//void UnitCreator::setName(cocos2d::CCString *_name) {
//    CC_SAFE_RELEASE_NULL(name);
//    name = _name;
//    name->retain();
//}
//
//const char* UnitCreator::getSpriteFileName() {
//    return spriteFileName->getCString();
//}
//
//const char* UnitCreator::getName() {
//    return name->getCString();
//}
//
//CCObject* UnitCreator::creatObj() {
//    return NULL;
//}
//
//CCObject* UnitCreator::creatObj(int level) {
//   return (*createUnit_selector)(level);
////    float speedLevelData = 0;
////    float damageLevelData = 0;
////    float costLevelData = 100;
////    float healthLevelData = 0;
////    speedLevelData = MyUtil::getInstance()->updateLevelByCount(getSpeed(), level, updateSpeedRate);
////    healthLevelData = MyUtil::getInstance()->updateLevelByRate(0,getLife(),level,updateHealthRate);
////    damageLevelData = MyUtil::getInstance()->updateLevelByRate(0,getDamage(), level, updateDamageRate);
////    costLevelData = MyUtil::getInstance()->updateLevelByRate(0,getSummaryOil(), level, updateCostRate);
////    if(MyGameInfo::getInstance()->getOil()-costLevelData>=0) {
////        
////        MoveToAttack* moveToAttack = MoveToAttack::create(MoveToAttackTag,speedLevelData,getAttackRange());
////        AttackState* attack = AttackState::create(AttackStateTag,sfxFireName, getAttackRange(),damageLevelData);
////        moveToAttack->addTransition(toAttackTransition, AttackStateTag);
////        attack->addTransition(toMoveTransition, MoveToAttackTag);
////        MyUnit* unit = MyUnit::create(moveToAttack,healthLevelData);
////        unit->addState(attack);
////        
////        
////        CCArray* moveArray[8];
////        for (int i = 0; i<8; i++) {
////            moveArray[i] = CCArray::create();
////        }
////        CCArray* fireArray[8];
////        for (int i = 0; i<8; i++) {
////            fireArray[i] = CCArray::create();
////        }
////        CCArray* dieArray[8];
////        for (int i = 0; i<8; i++) {
////            dieArray[i] = CCArray::create();
////        }
////        
////        CCObject* obj;
////        UnitFXCreator* fxCreator = NULL;
////        CCARRAY_FOREACH(fxArray, obj) {
////            fxCreator  = (UnitFXCreator*)obj;
////            if (fxCreator->getActionName()->compare("move") == 0) {
////                GXFX* fx = GXFX::create(GXUtil::initAction(fxCreator->getFxname()->getCString(), 1,false), fxCreator->startFrameCount,fxCreator->zOrder);
////                fx->setPosition(ccp(fxCreator->posX,fxCreator->posY));
////                fx->setScale(fxCreator->scale);
////                moveArray[fxCreator->dir]->addObject(fx);
////            } else if (fxCreator->getActionName()->compare("fire") == 0) {
////                GXFX* fx = GXFX::create(GXUtil::initAction(fxCreator->getFxname()->getCString(), 1,false), fxCreator->startFrameCount,fxCreator->zOrder);
////                fx->setPosition(ccp(fxCreator->posX,fxCreator->posY));
////                fx->setScale(fxCreator->scale);
////                fireArray[fxCreator->dir]->addObject(fx);
////            }else if (fxCreator->getActionName()->compare("die") == 0) {
////                GXFX* fx = GXFX::create(GXUtil::initAction(fxCreator->getFxname()->getCString(), 1,false), fxCreator->startFrameCount,fxCreator->zOrder);
////                fx->setPosition(ccp(fxCreator->posX,fxCreator->posY));
////                fx->setScale(fxCreator->scale);
////                dieArray[fxCreator->dir]->addObject(fx);
////            }
////        }
////        char str[64] = {0};
////        sprintf(str, "%smld",spriteFileName->getCString());
////        if (moveArray[0]->count() == 0) {
////            unit->move[0] = CCAnimate::create(GXUtil::initAction(str,moveAnimateRate,moveAnimateReverse));
////        } else {
////            unit->move[0] = GXAnimateWithFx::create(GXUtil::initAction(str,moveAnimateRate,moveAnimateReverse), moveArray[0]);
////        }
////        CC_SAFE_RETAIN(unit->move[0]);
////    
////        sprintf(str, "%smd",spriteFileName->getCString());
////        if (moveArray[1]->count() == 0) {
////            unit->move[1] = CCAnimate::create(GXUtil::initAction(str,moveAnimateRate,moveAnimateReverse));
////        } else {
////            unit->move[1] = GXAnimateWithFx::create(GXUtil::initAction(str,moveAnimateRate,moveAnimateReverse), moveArray[1]);
////        }
////        CC_SAFE_RETAIN(unit->move[1]);
////    
////        sprintf(str, "%smrd",spriteFileName->getCString());
////        if (moveArray[2]->count() == 0) {
////            unit->move[2] = CCAnimate::create(GXUtil::initAction(str,moveAnimateRate,moveAnimateReverse));
////        } else {
////            unit->move[2] = GXAnimateWithFx::create(GXUtil::initAction(str,moveAnimateRate,moveAnimateReverse), moveArray[2]);
////        }
////        CC_SAFE_RETAIN(unit->move[2]);
////    
////        sprintf(str, "%smr",spriteFileName->getCString());
////        if (moveArray[3]->count() == 0) {
////            unit->move[3] = CCAnimate::create(GXUtil::initAction(str,moveAnimateRate,moveAnimateReverse));
////        } else {
////            unit->move[3] = GXAnimateWithFx::create(GXUtil::initAction(str,moveAnimateRate,moveAnimateReverse), moveArray[3]);
////        }
////        CC_SAFE_RETAIN(unit->move[3]);
////    
////        sprintf(str, "%smru",spriteFileName->getCString());
////        if (moveArray[4]->count() == 0) {
////            unit->move[4] = CCAnimate::create(GXUtil::initAction(str,moveAnimateRate,moveAnimateReverse));
////        } else {
////            unit->move[4] = GXAnimateWithFx::create(GXUtil::initAction(str,moveAnimateRate,moveAnimateReverse), moveArray[4]);
////        }
////        CC_SAFE_RETAIN(unit->move[4]);
////    
////        sprintf(str, "%smu",spriteFileName->getCString());
////        if (moveArray[5]->count() == 0) {
////            unit->move[5] = CCAnimate::create(GXUtil::initAction(str,moveAnimateRate,moveAnimateReverse));
////        } else {
////            unit->move[5] = GXAnimateWithFx::create(GXUtil::initAction(str,moveAnimateRate,moveAnimateReverse), moveArray[5]);
////        }
////        CC_SAFE_RETAIN(unit->move[5]);
////    
////        sprintf(str, "%smlu",spriteFileName->getCString());
////        if (moveArray[6]->count() == 0) {
////            unit->move[6] = CCAnimate::create(GXUtil::initAction(str,moveAnimateRate,moveAnimateReverse));
////        } else {
////            unit->move[6] = GXAnimateWithFx::create(GXUtil::initAction(str,moveAnimateRate,moveAnimateReverse), moveArray[6]);
////        }
////        CC_SAFE_RETAIN(unit->move[6]);
////    
////        sprintf(str, "%sml",spriteFileName->getCString());
////        if (moveArray[7]->count() == 0) {
////            unit->move[7] = CCAnimate::create(GXUtil::initAction(str,moveAnimateRate,moveAnimateReverse));
////        } else {
////            unit->move[7] = GXAnimateWithFx::create(GXUtil::initAction(str,moveAnimateRate,moveAnimateReverse), moveArray[7]);
////        }
////        CC_SAFE_RETAIN(unit->move[7]);
////    
////    
////        sprintf(str, "%sfld",spriteFileName->getCString());
////        if (fireArray[0]->count() == 0) {
////            unit->fire[0] = CCAnimate::create(GXUtil::initAction(str,fireAnimateRate,fireAnimateReverse));
////        } else {
////            unit->fire[0] = GXAnimateWithFx::create(GXUtil::initAction(str,fireAnimateRate,fireAnimateReverse), fireArray[0]);
////        }
////        CC_SAFE_RETAIN(unit->fire[0]);
////    
////        sprintf(str, "%sfd",spriteFileName->getCString());
////        if (fireArray[1]->count() == 0) {
////            unit->fire[1] = CCAnimate::create(GXUtil::initAction(str,fireAnimateRate,fireAnimateReverse));
////        } else {
////            unit->fire[1] = GXAnimateWithFx::create(GXUtil::initAction(str,fireAnimateRate,fireAnimateReverse), fireArray[1]);
////        }
////        CC_SAFE_RETAIN(unit->fire[1]);
////    
////        sprintf(str, "%sfrd",spriteFileName->getCString());
////        if (fireArray[2]->count() == 0) {
////            unit->fire[2] = CCAnimate::create(GXUtil::initAction(str,fireAnimateRate,fireAnimateReverse));
////        } else {
////            unit->fire[2] = GXAnimateWithFx::create(GXUtil::initAction(str,fireAnimateRate,fireAnimateReverse), fireArray[2]);
////        }
////        CC_SAFE_RETAIN(unit->fire[2]);
////    
////        sprintf(str, "%sfr",spriteFileName->getCString());
////        if (fireArray[3]->count() == 0) {
////            unit->fire[3] = CCAnimate::create(GXUtil::initAction(str,fireAnimateRate,fireAnimateReverse));
////        } else {
////            unit->fire[3] = GXAnimateWithFx::create(GXUtil::initAction(str,fireAnimateRate,fireAnimateReverse), fireArray[3]);
////        }
////        CC_SAFE_RETAIN(unit->fire[3]);
////    
////        sprintf(str, "%sfru",spriteFileName->getCString());
////        if (fireArray[4]->count() == 0) {
////            unit->fire[4] = CCAnimate::create(GXUtil::initAction(str,fireAnimateRate,fireAnimateReverse));
////        } else {
////            unit->fire[4] = GXAnimateWithFx::create(GXUtil::initAction(str,fireAnimateRate,fireAnimateReverse), fireArray[4]);
////        }
////        CC_SAFE_RETAIN(unit->fire[4]);
////    
////        sprintf(str, "%sfu",spriteFileName->getCString());
////        if (fireArray[5]->count() == 0) {
////            unit->fire[5] = CCAnimate::create(GXUtil::initAction(str,fireAnimateRate,fireAnimateReverse));
////        } else {
////            unit->fire[5] = GXAnimateWithFx::create(GXUtil::initAction(str,fireAnimateRate,fireAnimateReverse), fireArray[5]);
////        }
////        CC_SAFE_RETAIN(unit->fire[5]);
////    
////        sprintf(str, "%sflu",spriteFileName->getCString());
////        if (fireArray[6]->count() == 0) {
////            unit->fire[6] = CCAnimate::create(GXUtil::initAction(str,fireAnimateRate,fireAnimateReverse));
////        } else {
////            unit->fire[6] = GXAnimateWithFx::create(GXUtil::initAction(str,fireAnimateRate,fireAnimateReverse), fireArray[6]);
////        }
////        CC_SAFE_RETAIN(unit->fire[6]);
////        
////        sprintf(str, "%sfl",spriteFileName->getCString());
////        if (fireArray[7]->count() == 0) {
////            unit->fire[7] = CCAnimate::create(GXUtil::initAction(str,fireAnimateRate,fireAnimateReverse));
////        } else {
////            unit->fire[7] = GXAnimateWithFx::create(GXUtil::initAction(str,fireAnimateRate,fireAnimateReverse), fireArray[7]);
////        }
////        CC_SAFE_RETAIN(unit->fire[7]);
////    
////        sprintf(str, "%sdld",spriteFileName->getCString());
////        if (dieArray[0]->count() == 0) {
////            unit->die[0] = CCAnimate::create(GXUtil::initAction(str,dieAnimateRate,dieAnimateRerverse));
////        } else {
////            unit->die[0] = GXAnimateWithFx::create(GXUtil::initAction(str,dieAnimateRate,dieAnimateRerverse), dieArray[0]);
////        }
////        CC_SAFE_RETAIN(unit->die[0]);
////    
////        sprintf(str, "%sdd",spriteFileName->getCString());
////        if (dieArray[1]->count() == 0) {
////            unit->die[1] = CCAnimate::create(GXUtil::initAction(str,dieAnimateRate,dieAnimateRerverse));
////        } else {
////            unit->die[1] = GXAnimateWithFx::create(GXUtil::initAction(str,dieAnimateRate,dieAnimateRerverse), dieArray[1]);
////        }
////        CC_SAFE_RETAIN(unit->die[1]);
////    
////        sprintf(str, "%sdrd",spriteFileName->getCString());
////        if (dieArray[2]->count() == 0) {
////            unit->die[2] = CCAnimate::create(GXUtil::initAction(str,dieAnimateRate,dieAnimateRerverse));
////        } else {
////            unit->die[2] = GXAnimateWithFx::create(GXUtil::initAction(str,dieAnimateRate,dieAnimateRerverse), dieArray[2]);
////        }
////        CC_SAFE_RETAIN(unit->die[2]);
////    
////        sprintf(str, "%sdr",spriteFileName->getCString());
////        if (dieArray[3]->count() == 0) {
////            unit->die[3] = CCAnimate::create(GXUtil::initAction(str,dieAnimateRate,dieAnimateRerverse));
////        } else {
////            unit->die[3] = GXAnimateWithFx::create(GXUtil::initAction(str,dieAnimateRate,dieAnimateRerverse), dieArray[3]);
////        }
////        CC_SAFE_RETAIN(unit->die[3]);
////        
////        sprintf(str, "%sdru",spriteFileName->getCString());
////        if (dieArray[4]->count() == 0) {
////            unit->die[4] = CCAnimate::create(GXUtil::initAction(str,dieAnimateRate,dieAnimateRerverse));
////        } else {
////            unit->die[4] = GXAnimateWithFx::create(GXUtil::initAction(str,dieAnimateRate,dieAnimateRerverse), dieArray[4]);
////        }
////        CC_SAFE_RETAIN(unit->die[4]);
////        
////        sprintf(str, "%sdu",spriteFileName->getCString());
////        if (dieArray[5]->count() == 0) {
////            unit->die[5] = CCAnimate::create(GXUtil::initAction(str,dieAnimateRate,dieAnimateRerverse));
////        } else {
////            unit->die[5] = GXAnimateWithFx::create(GXUtil::initAction(str,dieAnimateRate,dieAnimateRerverse), dieArray[5]);
////        }
////        CC_SAFE_RETAIN(unit->die[5]);
////        
////        sprintf(str, "%sdlu",spriteFileName->getCString());
////        if (dieArray[6]->count() == 0) {
////            unit->die[6] = CCAnimate::create(GXUtil::initAction(str,dieAnimateRate,dieAnimateRerverse));
////        } else {
////            unit->die[6] = GXAnimateWithFx::create(GXUtil::initAction(str,dieAnimateRate,dieAnimateRerverse), dieArray[6]);
////        }
////        CC_SAFE_RETAIN(unit->die[6]);
////            
////        sprintf(str, "%sdl",spriteFileName->getCString());
////        if (dieArray[7]->count() == 0) {
////            unit->die[7] = CCAnimate::create(GXUtil::initAction(str,dieAnimateRate,dieAnimateRerverse));
////        } else {
////            unit->die[7] = GXAnimateWithFx::create(GXUtil::initAction(str,dieAnimateRate,dieAnimateRerverse), dieArray[7]);
////        }
////        CC_SAFE_RETAIN(unit->die[7]);
////        
////        CCAction* action = CCRepeatForever::create(unit->move[0]);
////        action->setTag(currentAction);
////        unit->runAction(action);
////        
////        MyGameInfo::getInstance()->changeResource(oilTag, -costLevelData);
////        CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(sfxDeployName->getCString());
//////        battleCreateCount++;
////        return unit;
////    } else {
////        CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sfx_error.wav");
////        NoResourceToDeployMessage::create(this)->sendMsg();
////        return NULL;
////    }
//}
//
//void UnitCreator::doFill(cocos2d::CCObject *entity) {
//    
//}
//
////MyUnit* UnitCreator::createUnit() {
////   
////}
//
////void MyUnit::retain() {
////    CCSprite::retain();
////}
////
////void MyUnit::release() {
////    CCSprite::release();
////}
//
////UnitFXCreator* UnitFXCreator::create() {
////    UnitFXCreator* creator = new UnitFXCreator();
////    creator->autorelease();
////    return creator;
////}
//

