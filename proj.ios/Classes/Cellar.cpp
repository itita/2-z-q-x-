//
//  Cellar.cpp
//  ww4
//
//  Created by xiao tang on 13-7-5.
//
//

#include "Cellar.h"
#include "NormalState.h"
#include "DefineSet.h"
#include "BeAttackState.h"
#include "StartScene.h"
#include "MyUtil.h"
#include "KuangChang.h"
#include "SuperKuangChang.h"
#include "CellarProtectState.h"

BuildingInfo* Cellar::buildingInfo = NULL;

MyBuilding* Cellar::createNormal(CCObject* target,int level) {
    CCSprite* byItem = CCSprite::createWithSpriteFrameName("cellar.png");
    byItem->setAnchorPoint(ccp(0.45,0.47));
    // 普通状态
    
    NormalState* workState = NormalState::create(WorkStateTag, byItem);
    
    
    
    TransitionInfo* infoItem =  TransitionInfo::create(InfoTransition,"info.png",workState,menu_selector(MyState::infoCallBack));
    
    
    
    MyBuilding* BDbuilding = MyBuilding::create(bingyingTag,CCSizeMake(4,4),workState,10);
    
    BDbuilding->setLevel(level);
    BDbuilding->setTag(CellarTag);
    BDbuilding->setSummaryCount(5000);
    BDbuilding->resourceTag = ironTag;
    BDbuilding->setUpdateInfo_selector = (SEL_SetUpdateInfo)(Cellar::setUpdateInfo);
    
    TransitionInfo* updateItem =  TransitionInfo::create(UpdateTransition,"update.png",BDbuilding,menu_selector(MyBuilding::updateLevel));
    
    workState->addTransition(UpdateTransition, WorkStateTag,updateItem);
    workState->addTransition(InfoTransition, WorkStateTag,infoItem);
    
    BDbuilding->setBuildingName(CCString::create("地下金库"),108);
    getCellarInfo()->count++;
    BDbuilding->setUserData(getCellarInfo());
    
    return BDbuilding;
}

MyBattleBuilding* Cellar::createBattle(int level,int stateId,float arg0) {
    MyBattleState* beAttackState;
    if (stateId == UnfinishedStateTag) {
        beAttackState = BeAttackState::create(UnfinishedStateTag, CCSprite::createWithSpriteFrameName("buildstruct3x3(0).png"), 100);
    } else {
        CCSprite* ytItem = CCSprite::createWithSpriteFrameName("cellar.png");
        ytItem->setAnchorPoint(ccp(0.45,0.47));
        beAttackState = CellarProtectState::create(BeAttackStateTag, ytItem,arg0);
    }
    
    MyBattleBuilding* BDbuilding = MyBattleBuilding::create(CellarTag,CCSizeMake(4,4),beAttackState);
    //    BDbuilding->setLevel_selector = (SEL_SetBattleLevel)(&Cellar::setBattleLevel);
    BDbuilding->setLevel(level);
    BDbuilding->setBuildingName(CCString::create("地下金库"),108);
//    BDbuilding->displaySummary();
    CCSize normalCost = CCSizeMake(BDbuilding->contentSizeByTiled.width+2, BDbuilding->contentSizeByTiled.height+2);
    BDbuilding->costRange = normalCost;
    //    BDbuilding->AliveInterface::dispose();
    
    return BDbuilding;
}

MyBuildingCard* Cellar::createCard(CCObject* target,SEL_MenuHandler selector) {
    CCSprite* sprite = CCSprite::createWithSpriteFrameName("cellar.png");
    sprite->setAnchorPoint(ccp(0.50,0.63));
    sprite->setScale(0.8);
    MyBuildingCard* card = MyBuildingCard::create(sprite,CellarTag,CellarMaxCount,getCellarInfo()->count,ironTag,20000,10,"地下金库", target,selector);
    return card;
}

void Cellar::setUpdateInfo(GXFSMstate* _state,CCLayer* updateLayer)
{
    MyState* state = (MyState*)_state;
    
    int kcCount = KuangChang::getKuangChangInfo()->count;
    int skcCount = SuperKuangChang::getSuperKuangChangInfo()->count;
    
    int level = MyUtil::getInstance()->getLevelByExperience(MyGameInfo::getInstance()->getExperience());
    
    
    float cellarLevelData = MyUtil::getInstance()->updateLevelByRate(0,cellarBase, state->building->getLevel(), cellarUpdateRate);
    float cellarNextData = MyUtil::getInstance()->updateLevelByRate(0,cellarBase, state->building->getLevel()+1, cellarUpdateRate);
    float cellarMaxData = MyUtil::getInstance()->updateLevelByRate(0,cellarBase, state->building->getMaxLevel(), cellarUpdateRate);
    
    CCSprite* cellarIcon = CCSprite::createWithSpriteFrameName("cellarIcon.png");
    cellarIcon->setPosition(ccp(-68,134));
    updateLayer->addChild(cellarIcon);
    CCLayer* cellarBar = MyUtil::getInstance()->getUpdateBar(cellarNextData/cellarMaxData, cellarLevelData/cellarMaxData,"levelBarUp.png");
    
    cellarBar->setPosition(ccp(-40,116));
    
    char str[100] = {0};
    if (state->building->getLevel() < state->building->getMaxLevel()) {
        float value1 =(cellarLevelData*(level-9)*30);
        float value2 =(cellarNextData-cellarLevelData)*(level-9)*30;
        if (value1 < 10000 && value2<10000) {
            sprintf(str, "最大保护容量:%d+%d油钢",(int)value1,(int)value2);
        } else if(value1 < 10000) {
            sprintf(str, "最大保护容量:%d+%d万油钢",(int)value1,(int)(value2/10000));
        } else if(value2 < 10000) {
            sprintf(str, "最大保护容量:%d万+%d油钢",(int)(value1/10000),(int)value2);
        } else {
            sprintf(str, "最大保护容量:%d万+%d万油钢",(int)(value1/10000),(int)(value2/10000));
        }
        
    } else {
        sprintf(str, "最大保护容量:%d万油钢",(int)((cellarMaxData*(level-9)*30)/10000));
    }
    
    CCLabelTTF* cellarLabel = CCLabelTTF::create(str, "Arial", 24);
    cellarLabel->setAnchorPoint(ccp(0,0));
    cellarLabel->setColor(ccc3(254, 218, 130));
    cellarLabel->setPosition(ccp(-40,126));
    updateLayer->addChild(cellarBar);
    updateLayer->addChild(cellarLabel);
    float currentCapacity = (kcCount+skcCount*3)*(level-9)*cellarLevelData;
    CCPoint loc = ccp(-78,35);
    int labelSize = 24;
    if ((kcCount+skcCount*3) >= 30) {
        float value = (cellarLevelData*(level-9)*30);
        if (value < 10000) {
            sprintf(str,"当前保护容量:%d万(已达到最大值)",(int)value);
        } else {
            sprintf(str,"当前保护容量:%d万(已达到最大值)",(int)(value/10000));
        }
        loc.y = 50;
    } else {
        if (currentCapacity < 10000) {
            sprintf(str,"当前保护容量:%d(建设钢厂扩容)",(int)(currentCapacity));
        } else {
            sprintf(str,"当前保护容量:%d万(建设钢厂扩容)",(int)(currentCapacity/10000));
        }
        loc.y = 50;
    }
    //    else if(kcCount > 0 && skcCount>0) {
    //        sprintf(str,"当前保护容量:\n(%d(钢厂)+%d(超钢)x3)x(%d(等级)-9)x%d=%d万",kcCount,skcCount,level,(int)cellarLevelData,(int)(currentCapacity/10000));
    //        labelSize = 20;
    //        loc.x = -108;
    //    } else if(kcCount > 0){
    //        sprintf(str,"当前保护容量:\n%d(钢厂)x(%d(等级)-9)x%d=%d万",kcCount,level,(int)cellarLevelData,(int)(currentCapacity/10000));
    //    } else if(skcCount > 0){
    //        sprintf(str,"当前保护容量:\n%d(超级钢厂)x(%d(等级)-9)x%d=%d万",skcCount,level,(int)cellarLevelData,(int)(currentCapacity/10000));
    //    } else {
    //        sprintf(str,"当前回收率:0(需要建造钢厂)");
    //    }
    
    CCLabelTTF* currentCollectRateLabel = CCLabelTTF::create(str, "Arial", labelSize,CCSizeZero, kCCTextAlignmentLeft, kCCVerticalTextAlignmentCenter);
    currentCollectRateLabel->setAnchorPoint(ccp(0,0));
    currentCollectRateLabel->setColor(ccc3(255,133,80));
    currentCollectRateLabel->setPosition(loc);
    updateLayer->addChild(currentCollectRateLabel);
    
    
    CCLabelTTF* nameLabel = CCLabelTTF::create("地下金库", "Arial", 24);
    nameLabel->setColor(ccc3(254, 218, 130));
    nameLabel->setAnchorPoint(ccp(0.5,0.5));
    nameLabel->setPosition(ccp(-204,172));
    updateLayer->addChild(nameLabel);
    
    CCLabelTTF* description = CCLabelTTF::create("　　地下金库会在被攻击的时候保护资源免受掠\n夺，每一个炼钢厂增加一定数值的保护金额，但\n最多只能支持30个炼钢厂。地下金库将资源保存\n在地下,即使是核弹攻击也无法摧毁。", "Arial",  26,CCSizeZero, kCCTextAlignmentLeft, kCCVerticalTextAlignmentTop);
    description->setAnchorPoint(ccp(0,0.5));
    description->setColor(ccc3(254, 218, 130));
    description->setPosition(ccp(-280,-50));
    updateLayer->addChild(description);
}

BuildingInfo* Cellar::getCellarInfo() {
    if(buildingInfo == NULL) {
        buildingInfo = BuildingInfo::create();
    }
    return buildingInfo;
}
