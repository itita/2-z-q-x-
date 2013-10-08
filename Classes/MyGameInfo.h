//
//  MyGameInfo.h
//  ww2
//
//  Created by DingYu Fu on 12-9-18.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#ifndef ww2_MyGameInfo_h
#define ww2_MyGameInfo_h

#include "cocos2d.h"
#include "MyAtlasNumber.h"
#include "MyLevelBar.h"
#include "UnitSet.h"
#include "GXAntiCrack.h"

using namespace cocos2d;

class UnionBean : public CCObject {
    
public:
    ~UnionBean() {
        CC_SAFE_RELEASE_NULL(name);
        CC_SAFE_RELEASE_NULL(desc);
        CC_SAFE_RELEASE_NULL(notice);
        CC_SAFE_RELEASE_NULL(emblem);
    }
    
    UnionBean():
    name(NULL),
    desc(NULL),
    notice(NULL),
    emblem(NULL),
    level(1),
    role(1),
    unionId(-1),
    memberCount(1),
    memberPageNo(1),
    memberPageCount(1){
    }
    int level;
    int role;
    int unionId;
    int memberCount;
    int memberPageNo;
    int memberPageCount;
    static UnionBean* create();
    void setName(CCString* nameStr);
    CCString* getName();
    void setDesc(CCString* descStr);
    CCString* getDesc();
    void setNotice(CCString* noticeStr);
    CCString* getNotice();
    void setEmblem(CCString* emblemStr);
    CCString* getEmblem();
    
private:
    CCString* name;
    CCString* desc;
    CCString* notice;
    CCString* emblem;
};

class MyGameInfo : public CCObject{
    
public:
    
    MyGameInfo():
    nickname(NULL),
    lastTime(0),
    nowTime(0),
//    robdeltaTime(0),
    enemyOil(0),
    enemyIron(0),
    enemyDeltaOil(0),
    enemyDeltaIron(0),
    enemyLevel(-1),
    oilAtlas(NULL),
    ironAtlas(NULL),
    gloryAtlas(NULL),
    diamondAtlas(NULL),
    levelBar(NULL),
    robberOil(1),
    robberIron(1),
    power(21),
    enemyPower(20),
    enemyNickname(NULL),
    maxId(-1),
    experience(0){
        oil = GXfloatValue::create(2000);
        oil->retain();
        iron = GXfloatValue::create(2000);
        iron->retain();
        glory = GXfloatValue::create(40);
        glory->retain();
        diamond = GXfloatValue::create(0);
        diamond->retain();
//        deltaOil = GXfloatValue::create(0);
//        deltaOil->retain();
//        deltaIron = GXfloatValue::create(0);
//        deltaIron->retain();
//        deltaGlory = GXfloatValue::create(0);
//        deltaGlory->retain();
        
        experience = GXunsignedlonglongValue::create(1);
        experience->retain();
        
        vipExperience = GXintValue::create(0);
        vipExperience->retain();
        
//        robMultiple = GXintValue::create(1);
//        robMultiple->retain();
        
        unionBean = UnionBean::create();
        unionBean->retain();
        
        nickname = CCString::create("");
        nickname->retain();
        
        creatorArray = CCArray::create();
        creatorArray->retain();
        
        boughtArray = CCArray::create();
        boughtArray->retain();
        
        enemyUserId = GXintValue::create(-1);
        enemyUserId->retain();
        
    }
    virtual ~MyGameInfo();
    
    static MyGameInfo* infoInstance;
    static MyGameInfo* getInstance();
    
    
    long long lastTime;
    long long nowTime;
    
    float enemyDeltaOil;
    float enemyDeltaIron;
    
    GXintValue* enemyUserId;
    
    int getEnemyUserId() {
        return enemyUserId->getValue();
    }
    
    void setEnemyUserId(int _enemyUserId) {
        enemyUserId->setValue(_enemyUserId);
    }
    
    CC_SYNTHESIZE_RETAIN(CCString*,enemyNickname,EnemyNickname);
    virtual CCLayer* changeResourceAndFloatText(int tag,int ResourceCount,const CCPoint& pos);
    MyAtlasNumber* getOilAtlas();
    MyAtlasNumber* getIronAtlas();
    MyAtlasNumber* getGloryAtlas();
    MyAtlasNumber* getDiamondAtlas();
    
    MyLevelBar* getLevelBar();
    float getOil();
    float getIron();
    float getGlory();
    float getDiamond();
    
    float getResource(int tag);
    void  setOil(float _oil);
    void setIron(float _iron);
    void setGlory(float _glory);
    void setDiamond(float _diamond);
    void  setInitOil(float _oil);
    void setInitIron(float _iron);
    void setInitGlory(float _glory);
//    void initDelta();
    void changeResource(int tag,int ResourceCount);
//    void changeBaseOil(int resourceCount);
//    void changeBaseIron(int resourceCount);
    void releaseXmppHandler();
    
//    void release();
//    void retain();
    
//    float getDeltaOil();
//    float getDeltaIron();
//    float getDeltaGlory();
    
    float getRobberOil();
    void setRobberOil(float _robberOil);
    float getRobberIron();
    void setRobberIron(float _robberIron);
    
    float getPower();
    void setPower(float _Power);
    
    float enemyPower;
    int enemyLevel;
    
    float enemyOil;
    float enemyIron;
    
    int maxId;
  
    void setExperienceNoFx(unsigned long long _exp);
    void setExperience(unsigned long long _exp);
    void setUpdateLevel(unsigned long long _exp);

    unsigned long long getExperience();
    
//    int getRobMultiple();
//    void setRobMultiple(int multiple);
//    void setRobMultipleByTime(unsigned long long deltaRobtime);
    void clear();
//    unsigned long robdeltaTime;
    
    CC_SYNTHESIZE_RETAIN(UnionBean*,unionBean,UnionBean);
    
    const char* getNickName() {
        return nickname->getCString();
    }
    
    void setNickName(CCString* _nickName) {
        CC_SAFE_RELEASE_NULL(nickname);
        nickname = _nickName;
        nickname->retain();
    }
    
    CCArray* creatorArray;
    CCArray* boughtArray;
    
    void setVipExperience(int _vipExperience) {
        vipExperience->setValue(_vipExperience);
    }
    
    int getVipExperience() {
        return vipExperience->getValue();
    }
    
private:
    
    float robberOil;
    float robberIron;
    float power;
    GXunsignedlonglongValue* experience;
    CCString* nickname;
   
    
    MyAtlasNumber* oilAtlas;
    MyAtlasNumber* ironAtlas;
    MyAtlasNumber* gloryAtlas;
    MyAtlasNumber* diamondAtlas;
    
    MyLevelBar*  levelBar;
    
    GXfloatValue* oil;
    GXfloatValue* iron;
    GXfloatValue* glory;
    GXfloatValue* diamond;
    
//    GXfloatValue* deltaOil;
//    GXfloatValue* deltaIron;
//    GXfloatValue* deltaGlory;
//    GXintValue* robMultiple;
    
    GXintValue* vipExperience;
    
    
};

class MatchInfoBean : public CCObject{
public:
    ~MatchInfoBean() {
//        CCLog("MatchInfoBean realsed");
        CC_SAFE_RELEASE_NULL(unitCountArray);
        CC_SAFE_RELEASE_NULL(frameNameArray);
        CC_SAFE_RELEASE_NULL(levelArray);
        CC_SAFE_RELEASE_NULL(rarityArray);
        CC_SAFE_RELEASE_NULL(attackNickName);
//        CC_SAFE_RELEASE_NULL(attackId);
        CC_SAFE_RELEASE_NULL(defenderNickName);
        CC_SAFE_RELEASE_NULL(defenderId);
        CC_SAFE_RELEASE_NULL(emblemName);
    }
    MatchInfoBean():
    attackNickName(NULL),
//    attackId(NULL),
    defenderNickName(NULL),
    defenderId(NULL),
    note(NULL),
    time(NULL),
    emblemName(NULL),
    frameNameArray(NULL),
    unitCountArray(NULL),
    levelArray(NULL),
    rarityArray(NULL),
    isWin(false),
    robberOil(0),
    robberIron(0),
    deltaPower(0),
    enemyPower(20),
    attackType(0),
    attackUserId(-1){
        unionName = CCString::create("");
        unionName->retain();
    }
    bool isWin;
    int robberOil;
    int robberIron;
    int deltaPower;
    int enemyPower;
    int vipExperience;
    int attackType;
    int attackUserId;
    CCArray* frameNameArray;
    CCArray* unitCountArray;
    CCArray* levelArray;
    CCArray* rarityArray;
    static MatchInfoBean* create();
    virtual CCMenuItemSprite* getReverageButton();
    void setAttackNickName(const char* str) {
        CC_SAFE_RELEASE_NULL(attackNickName);
        attackNickName = CCString::create(str);
        attackNickName->retain();
    }
//    void setAttackId(const char* str) {
//        CC_SAFE_RELEASE_NULL(attackId);
//        attackId = CCString::create(str);
//        attackId->retain();
//    }
    
    void setDefenderNickName(const char* str) {
        CC_SAFE_RELEASE_NULL(defenderNickName);
        defenderNickName = CCString::create(str);
        defenderNickName->retain();
    }
    
    void setDefenderId(const char* str) {
        CC_SAFE_RELEASE_NULL(defenderId);
        defenderId = CCString::create(str);
        defenderId->retain();
    }
    
    void setTime(const char* str) {
        CC_SAFE_RELEASE_NULL(time);
        time = CCString::create(str);
        time->retain();
    }
    
    void setNote(const char* str) {
        CC_SAFE_RELEASE_NULL(note);
        note = CCString::create(str);
        note->retain();
    }
    
    void setEmblem(const char* str) {
        CC_SAFE_RELEASE_NULL(emblemName);
        emblemName = CCString::create(str);
        emblemName->retain();
    }
    
    void setUnionName(const char* str) {
        CC_SAFE_RELEASE_NULL(unionName);
        unionName = CCString::create(str);
        unionName->retain();
    }
    
    CCString* getAttackNickName() {
        return attackNickName;
    }
    
//    CCString* getAttackId() {
//        return attackId;
//    }
    
    CCString* getDefenderNickName() {
        return defenderNickName;
    }
    
    CCString* getDefenderId() {
        return defenderId;
    }
    
    CCString* getTime() {
        return time;
    }
    
    CCString* getNote() {
        return note;
    }
    
    CCString* getEmblem() {
        return emblemName;
    }
    
    CCString* getUnionName() {
        return unionName;
    }
    
//    virtual void retain();
//    virtual void release();
  
private:
    void toReverageCallBack(CCObject* pSender);
    void replaceScene();
    CCString* attackNickName;
//    CCString* attackId;
    CCString* defenderNickName;
    CCString* defenderId;
    CCString* time;
    CCString* note;
    CCString* emblemName;
    CCString* unionName;
};

//typedef UnitBean* (*SEL_GetUnitBean)();

class CreatorInfoBean : public CCObject {
    
public:

    CreatorInfoBean()
//    creator(NULL),
//    scriptName(NULL)
    {
        level = GXintValue::create(1);
        level->retain();
        experience = GXunsignedlonglongValue::create(1);
        experience->retain();
    }
    ~CreatorInfoBean() {
//        CC_SAFE_RELEASE_NULL(creator);
//        CC_SAFE_RELEASE_NULL(scriptName);
        CC_SAFE_RELEASE_NULL(level);
        CC_SAFE_RELEASE_NULL(experience);
    }
    //    CCString* scriptName;
    UnitBean* creator;
    void setExperience(unsigned long long _experience) {
        experience->setValue(_experience);
        level->setValue(-1);
    }
    
    unsigned long long getExperience() {
        return experience->getValue();
    }
    
    static CreatorInfoBean* create(int unitTag);
    CCLayer* getUnitCardDesc(bool isALL);
//    CCString* getScriptName() {
//        return scriptName;
//    }
    int getLevel();
    
    float getCostCool();
    
private:
    GXintValue* level;
    GXunsignedlonglongValue* experience;
//    SEL_GetUnitBean getUnitBean_selector;
//    CCString* scriptName;
};




#endif
