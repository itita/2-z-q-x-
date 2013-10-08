//
//  UnitBean.cpp
//  ww4
//
//  Created by xiao tang on 13-5-8.
//
//

#include "UnitBean.h"
#include "GXUtil.h"

UnitBean::~UnitBean() {
    //野指针问题
    
    
    char str[30] = {0};
    
    sprintf(str, "%sbp.plist",spriteFileName->getCString());
    CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile(str);
    
    sprintf(str, "%sbp.pvr.ccz",spriteFileName->getCString());
    CCTextureCache::sharedTextureCache()->removeTextureForKey(str);
    
//    CC_SAFE_RELEASE_NULL(sfxFireName);
//    
//    CC_SAFE_RELEASE_NULL(sfxDeployName);
    
    CC_SAFE_RELEASE_NULL(spriteFileName);
    
//    CC_SAFE_RELEASE_NULL(fxArray);
    
//    CC_SAFE_RELEASE_NULL(summaryOil);
    CC_SAFE_RELEASE_NULL(rarity);
//    CC_SAFE_RELEASE_NULL(speed);
//    CC_SAFE_RELEASE_NULL(attackRange);
//    CC_SAFE_RELEASE_NULL(damage);
//    CC_SAFE_RELEASE_NULL(life);
    CCLog("unit released");
}

UnitBean* UnitBean::create(int cardId,CCString* name,CCString* _spriteFileName,int summaryOil,float _updateCostRate,int rarity) {
    UnitBean* creator = new UnitBean();
    creator->cardId=cardId;
    creator->setSpriteFileName(_spriteFileName);
    creator->autorelease();
    creator->setSummaryOil(summaryOil);
    creator->setName(name);
    creator->setRarity(rarity);
    creator->updateCostRate = _updateCostRate;
    
    return creator;
}

UnitBean* UnitBean::create() {
    UnitBean* creator = new UnitBean();
    creator->autorelease();
//    creator->fxArray  = CCArray::create();
//    creator->fxArray->retain();
    return creator;
}




void UnitBean::setSpriteFileName(cocos2d::CCString *_spriteFileName) {
    CC_SAFE_RELEASE_NULL(spriteFileName);
    spriteFileName  = _spriteFileName;
    // 加入兵牌数据
    char str[30] = {0};
    char str1[30] = {0};
    sprintf(str, "%sbp.plist",_spriteFileName->getCString());
    sprintf(str1, "%sbp.pvr.ccz",_spriteFileName->getCString());
    GXUtil::loadResourceUtilSucc(str,str1);
    spriteFileName->retain();
}

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

void UnitBean::setName(cocos2d::CCString *_name) {
    CC_SAFE_RELEASE_NULL(name);
    name = _name;
    name->retain();
}

const char* UnitBean::getSpriteFileName() {
    return spriteFileName->getCString();
}

const char* UnitBean::getName() {
    return name->getCString();
}

//CCObject* UnitCreator::creatObj() {
//    return NULL;
//}
//
MyUnit* UnitBean::createObj(int level) {
    return (*createUnit_selector)(level);
    //    float speedLevelData = 0;
    //    float damageLevelData = 0;
    //    float costLevelData = 100;
    //    float healthLevelData = 0;
    //    speedLevelData = MyUtil::getInstance()->updateLevelByCount(getSpeed(), level, updateSpeedRate);
    //    healthLevelData = MyUtil::getInstance()->updateLevelByRate(0,getLife(),level,updateHealthRate);
    //    damageLevelData = MyUtil::getInstance()->updateLevelByRate(0,getDamage(), level, updateDamageRate);
    //    costLevelData = MyUtil::getInstance()->updateLevelByRate(0,getSummaryOil(), level, updateCostRate);
    //    if(MyGameInfo::getInstance()->getOil()-costLevelData>=0) {
    //
    //        MoveToAttack* moveToAttack = MoveToAttack::create(MoveToAttackTag,speedLevelData,getAttackRange());
    //        AttackState* attack = AttackState::create(AttackStateTag,sfxFireName, getAttackRange(),damageLevelData);
    //        moveToAttack->addTransition(toAttackTransition, AttackStateTag);
    //        attack->addTransition(toMoveTransition, MoveToAttackTag);
    //        MyUnit* unit = MyUnit::create(moveToAttack,healthLevelData);
    //        unit->addState(attack);
    //
    //
    //        CCArray* moveArray[8];
    //        for (int i = 0; i<8; i++) {
    //            moveArray[i] = CCArray::create();
    //        }
    //        CCArray* fireArray[8];
    //        for (int i = 0; i<8; i++) {
    //            fireArray[i] = CCArray::create();
    //        }
    //        CCArray* dieArray[8];
    //        for (int i = 0; i<8; i++) {
    //            dieArray[i] = CCArray::create();
    //        }
    //
    //        CCObject* obj;
    //        UnitFXCreator* fxCreator = NULL;
    //        CCARRAY_FOREACH(fxArray, obj) {
    //            fxCreator  = (UnitFXCreator*)obj;
    //            if (fxCreator->getActionName()->compare("move") == 0) {
    //                GXFX* fx = GXFX::create(GXUtil::initAction(fxCreator->getFxname()->getCString(), 1,false), fxCreator->startFrameCount,fxCreator->zOrder);
    //                fx->setPosition(ccp(fxCreator->posX,fxCreator->posY));
    //                fx->setScale(fxCreator->scale);
    //                moveArray[fxCreator->dir]->addObject(fx);
    //            } else if (fxCreator->getActionName()->compare("fire") == 0) {
    //                GXFX* fx = GXFX::create(GXUtil::initAction(fxCreator->getFxname()->getCString(), 1,false), fxCreator->startFrameCount,fxCreator->zOrder);
    //                fx->setPosition(ccp(fxCreator->posX,fxCreator->posY));
    //                fx->setScale(fxCreator->scale);
    //                fireArray[fxCreator->dir]->addObject(fx);
    //            }else if (fxCreator->getActionName()->compare("die") == 0) {
    //                GXFX* fx = GXFX::create(GXUtil::initAction(fxCreator->getFxname()->getCString(), 1,false), fxCreator->startFrameCount,fxCreator->zOrder);
    //                fx->setPosition(ccp(fxCreator->posX,fxCreator->posY));
    //                fx->setScale(fxCreator->scale);
    //                dieArray[fxCreator->dir]->addObject(fx);
    //            }
    //        }
    //        char str[64] = {0};
    //        sprintf(str, "%smld",spriteFileName->getCString());
    //        if (moveArray[0]->count() == 0) {
    //            unit->move[0] = CCAnimate::create(GXUtil::initAction(str,moveAnimateRate,moveAnimateReverse));
    //        } else {
    //            unit->move[0] = GXAnimateWithFx::create(GXUtil::initAction(str,moveAnimateRate,moveAnimateReverse), moveArray[0]);
    //        }
    //        CC_SAFE_RETAIN(unit->move[0]);
    //
    //        sprintf(str, "%smd",spriteFileName->getCString());
    //        if (moveArray[1]->count() == 0) {
    //            unit->move[1] = CCAnimate::create(GXUtil::initAction(str,moveAnimateRate,moveAnimateReverse));
    //        } else {
    //            unit->move[1] = GXAnimateWithFx::create(GXUtil::initAction(str,moveAnimateRate,moveAnimateReverse), moveArray[1]);
    //        }
    //        CC_SAFE_RETAIN(unit->move[1]);
    //
    //        sprintf(str, "%smrd",spriteFileName->getCString());
    //        if (moveArray[2]->count() == 0) {
    //            unit->move[2] = CCAnimate::create(GXUtil::initAction(str,moveAnimateRate,moveAnimateReverse));
    //        } else {
    //            unit->move[2] = GXAnimateWithFx::create(GXUtil::initAction(str,moveAnimateRate,moveAnimateReverse), moveArray[2]);
    //        }
    //        CC_SAFE_RETAIN(unit->move[2]);
    //
    //        sprintf(str, "%smr",spriteFileName->getCString());
    //        if (moveArray[3]->count() == 0) {
    //            unit->move[3] = CCAnimate::create(GXUtil::initAction(str,moveAnimateRate,moveAnimateReverse));
    //        } else {
    //            unit->move[3] = GXAnimateWithFx::create(GXUtil::initAction(str,moveAnimateRate,moveAnimateReverse), moveArray[3]);
    //        }
    //        CC_SAFE_RETAIN(unit->move[3]);
    //
    //        sprintf(str, "%smru",spriteFileName->getCString());
    //        if (moveArray[4]->count() == 0) {
    //            unit->move[4] = CCAnimate::create(GXUtil::initAction(str,moveAnimateRate,moveAnimateReverse));
    //        } else {
    //            unit->move[4] = GXAnimateWithFx::create(GXUtil::initAction(str,moveAnimateRate,moveAnimateReverse), moveArray[4]);
    //        }
    //        CC_SAFE_RETAIN(unit->move[4]);
    //
    //        sprintf(str, "%smu",spriteFileName->getCString());
    //        if (moveArray[5]->count() == 0) {
    //            unit->move[5] = CCAnimate::create(GXUtil::initAction(str,moveAnimateRate,moveAnimateReverse));
    //        } else {
    //            unit->move[5] = GXAnimateWithFx::create(GXUtil::initAction(str,moveAnimateRate,moveAnimateReverse), moveArray[5]);
    //        }
    //        CC_SAFE_RETAIN(unit->move[5]);
    //
    //        sprintf(str, "%smlu",spriteFileName->getCString());
    //        if (moveArray[6]->count() == 0) {
    //            unit->move[6] = CCAnimate::create(GXUtil::initAction(str,moveAnimateRate,moveAnimateReverse));
    //        } else {
    //            unit->move[6] = GXAnimateWithFx::create(GXUtil::initAction(str,moveAnimateRate,moveAnimateReverse), moveArray[6]);
    //        }
    //        CC_SAFE_RETAIN(unit->move[6]);
    //
    //        sprintf(str, "%sml",spriteFileName->getCString());
    //        if (moveArray[7]->count() == 0) {
    //            unit->move[7] = CCAnimate::create(GXUtil::initAction(str,moveAnimateRate,moveAnimateReverse));
    //        } else {
    //            unit->move[7] = GXAnimateWithFx::create(GXUtil::initAction(str,moveAnimateRate,moveAnimateReverse), moveArray[7]);
    //        }
    //        CC_SAFE_RETAIN(unit->move[7]);
    //
    //
    //        sprintf(str, "%sfld",spriteFileName->getCString());
    //        if (fireArray[0]->count() == 0) {
    //            unit->fire[0] = CCAnimate::create(GXUtil::initAction(str,fireAnimateRate,fireAnimateReverse));
    //        } else {
    //            unit->fire[0] = GXAnimateWithFx::create(GXUtil::initAction(str,fireAnimateRate,fireAnimateReverse), fireArray[0]);
    //        }
    //        CC_SAFE_RETAIN(unit->fire[0]);
    //
    //        sprintf(str, "%sfd",spriteFileName->getCString());
    //        if (fireArray[1]->count() == 0) {
    //            unit->fire[1] = CCAnimate::create(GXUtil::initAction(str,fireAnimateRate,fireAnimateReverse));
    //        } else {
    //            unit->fire[1] = GXAnimateWithFx::create(GXUtil::initAction(str,fireAnimateRate,fireAnimateReverse), fireArray[1]);
    //        }
    //        CC_SAFE_RETAIN(unit->fire[1]);
    //
    //        sprintf(str, "%sfrd",spriteFileName->getCString());
    //        if (fireArray[2]->count() == 0) {
    //            unit->fire[2] = CCAnimate::create(GXUtil::initAction(str,fireAnimateRate,fireAnimateReverse));
    //        } else {
    //            unit->fire[2] = GXAnimateWithFx::create(GXUtil::initAction(str,fireAnimateRate,fireAnimateReverse), fireArray[2]);
    //        }
    //        CC_SAFE_RETAIN(unit->fire[2]);
    //
    //        sprintf(str, "%sfr",spriteFileName->getCString());
    //        if (fireArray[3]->count() == 0) {
    //            unit->fire[3] = CCAnimate::create(GXUtil::initAction(str,fireAnimateRate,fireAnimateReverse));
    //        } else {
    //            unit->fire[3] = GXAnimateWithFx::create(GXUtil::initAction(str,fireAnimateRate,fireAnimateReverse), fireArray[3]);
    //        }
    //        CC_SAFE_RETAIN(unit->fire[3]);
    //
    //        sprintf(str, "%sfru",spriteFileName->getCString());
    //        if (fireArray[4]->count() == 0) {
    //            unit->fire[4] = CCAnimate::create(GXUtil::initAction(str,fireAnimateRate,fireAnimateReverse));
    //        } else {
    //            unit->fire[4] = GXAnimateWithFx::create(GXUtil::initAction(str,fireAnimateRate,fireAnimateReverse), fireArray[4]);
    //        }
    //        CC_SAFE_RETAIN(unit->fire[4]);
    //
    //        sprintf(str, "%sfu",spriteFileName->getCString());
    //        if (fireArray[5]->count() == 0) {
    //            unit->fire[5] = CCAnimate::create(GXUtil::initAction(str,fireAnimateRate,fireAnimateReverse));
    //        } else {
    //            unit->fire[5] = GXAnimateWithFx::create(GXUtil::initAction(str,fireAnimateRate,fireAnimateReverse), fireArray[5]);
    //        }
    //        CC_SAFE_RETAIN(unit->fire[5]);
    //
    //        sprintf(str, "%sflu",spriteFileName->getCString());
    //        if (fireArray[6]->count() == 0) {
    //            unit->fire[6] = CCAnimate::create(GXUtil::initAction(str,fireAnimateRate,fireAnimateReverse));
    //        } else {
    //            unit->fire[6] = GXAnimateWithFx::create(GXUtil::initAction(str,fireAnimateRate,fireAnimateReverse), fireArray[6]);
    //        }
    //        CC_SAFE_RETAIN(unit->fire[6]);
    //
    //        sprintf(str, "%sfl",spriteFileName->getCString());
    //        if (fireArray[7]->count() == 0) {
    //            unit->fire[7] = CCAnimate::create(GXUtil::initAction(str,fireAnimateRate,fireAnimateReverse));
    //        } else {
    //            unit->fire[7] = GXAnimateWithFx::create(GXUtil::initAction(str,fireAnimateRate,fireAnimateReverse), fireArray[7]);
    //        }
    //        CC_SAFE_RETAIN(unit->fire[7]);
    //
    //        sprintf(str, "%sdld",spriteFileName->getCString());
    //        if (dieArray[0]->count() == 0) {
    //            unit->die[0] = CCAnimate::create(GXUtil::initAction(str,dieAnimateRate,dieAnimateRerverse));
    //        } else {
    //            unit->die[0] = GXAnimateWithFx::create(GXUtil::initAction(str,dieAnimateRate,dieAnimateRerverse), dieArray[0]);
    //        }
    //        CC_SAFE_RETAIN(unit->die[0]);
    //
    //        sprintf(str, "%sdd",spriteFileName->getCString());
    //        if (dieArray[1]->count() == 0) {
    //            unit->die[1] = CCAnimate::create(GXUtil::initAction(str,dieAnimateRate,dieAnimateRerverse));
    //        } else {
    //            unit->die[1] = GXAnimateWithFx::create(GXUtil::initAction(str,dieAnimateRate,dieAnimateRerverse), dieArray[1]);
    //        }
    //        CC_SAFE_RETAIN(unit->die[1]);
    //
    //        sprintf(str, "%sdrd",spriteFileName->getCString());
    //        if (dieArray[2]->count() == 0) {
    //            unit->die[2] = CCAnimate::create(GXUtil::initAction(str,dieAnimateRate,dieAnimateRerverse));
    //        } else {
    //            unit->die[2] = GXAnimateWithFx::create(GXUtil::initAction(str,dieAnimateRate,dieAnimateRerverse), dieArray[2]);
    //        }
    //        CC_SAFE_RETAIN(unit->die[2]);
    //
    //        sprintf(str, "%sdr",spriteFileName->getCString());
    //        if (dieArray[3]->count() == 0) {
    //            unit->die[3] = CCAnimate::create(GXUtil::initAction(str,dieAnimateRate,dieAnimateRerverse));
    //        } else {
    //            unit->die[3] = GXAnimateWithFx::create(GXUtil::initAction(str,dieAnimateRate,dieAnimateRerverse), dieArray[3]);
    //        }
    //        CC_SAFE_RETAIN(unit->die[3]);
    //
    //        sprintf(str, "%sdru",spriteFileName->getCString());
    //        if (dieArray[4]->count() == 0) {
    //            unit->die[4] = CCAnimate::create(GXUtil::initAction(str,dieAnimateRate,dieAnimateRerverse));
    //        } else {
    //            unit->die[4] = GXAnimateWithFx::create(GXUtil::initAction(str,dieAnimateRate,dieAnimateRerverse), dieArray[4]);
    //        }
    //        CC_SAFE_RETAIN(unit->die[4]);
    //
    //        sprintf(str, "%sdu",spriteFileName->getCString());
    //        if (dieArray[5]->count() == 0) {
    //            unit->die[5] = CCAnimate::create(GXUtil::initAction(str,dieAnimateRate,dieAnimateRerverse));
    //        } else {
    //            unit->die[5] = GXAnimateWithFx::create(GXUtil::initAction(str,dieAnimateRate,dieAnimateRerverse), dieArray[5]);
    //        }
    //        CC_SAFE_RETAIN(unit->die[5]);
    //
    //        sprintf(str, "%sdlu",spriteFileName->getCString());
    //        if (dieArray[6]->count() == 0) {
    //            unit->die[6] = CCAnimate::create(GXUtil::initAction(str,dieAnimateRate,dieAnimateRerverse));
    //        } else {
    //            unit->die[6] = GXAnimateWithFx::create(GXUtil::initAction(str,dieAnimateRate,dieAnimateRerverse), dieArray[6]);
    //        }
    //        CC_SAFE_RETAIN(unit->die[6]);
    //
    //        sprintf(str, "%sdl",spriteFileName->getCString());
    //        if (dieArray[7]->count() == 0) {
    //            unit->die[7] = CCAnimate::create(GXUtil::initAction(str,dieAnimateRate,dieAnimateRerverse));
    //        } else {
    //            unit->die[7] = GXAnimateWithFx::create(GXUtil::initAction(str,dieAnimateRate,dieAnimateRerverse), dieArray[7]);
    //        }
    //        CC_SAFE_RETAIN(unit->die[7]);
    //        
    //        CCAction* action = CCRepeatForever::create(unit->move[0]);
    //        action->setTag(currentAction);
    //        unit->runAction(action);
    //        
    //        MyGameInfo::getInstance()->changeResource(oilTag, -costLevelData);
    //        CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(sfxDeployName->getCString());
    ////        battleCreateCount++;
    //        return unit;
    //    } else {
    //        CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sfx_error.wav");
    //        NoResourceToDeployMessage::create(this)->sendMsg();
    //        return NULL;
    //    }
}

CCLayer* UnitBean::getUnitCardInfo(int level,bool isAll) {
    return (*getUnitCardInfo_selector)(level,isAll);
}

CCSprite* UnitBean::getAttackSprite(int dir) {
    return (getAttackSprite_selector)(dir);
}
//
//void UnitCreator::doFill(cocos2d::CCObject *entity) {
//    
//}

//MyUnit* UnitCreator::createUnit() {
//   
//}
