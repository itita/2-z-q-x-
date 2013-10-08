//
//  MyUtil.h
//  ww2
//
//  Created by DingYu Fu on 12-9-19.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#define NoResourceTag 10

#ifndef ww2_MyUtil_h
#define ww2_MyUtil_h
#include "cocos2d.h"
#include "MyJsonUtil.h"
#include "GXUtil.h"

using namespace cocos2d;

class MyUtil : public CCObject{
    
public:
    static MyUtil* getInstance();
    static void releaseInstance();
    CCLayer* getNetworkDialog();
    CCLayer* getNoResourceDialog(CCObject* target,int resourceTag);
    CCLayer* getNoGloryDialog();
    CCLayer* getCommonTipDialog(CCString* str,cocos2d::CCObject *rec, SEL_MenuHandler selector,int mode);
    const char* getNickNamebyNet();
    ConscribeInfoBean* cardLottery(CCArray* conscribeArray);
    float updateLevelByRate(float ori,float base,float level,float rate);
    float updateLevelByCount(float base,int level,float count);
    float updateLevelBySquare(float base,int level,int count);
    CCSprite* getRankSprite(float power);
    const char* getRankString(float power);
    CCLayer* getWaitLayer(const char* label);
    CCLayer* getScanEnemyLayer();
    CCLayer* getSaveLayer();
    int getLevelByExperience(unsigned long long _exp);
    int getUnitLevelByExperience(unsigned long long _exp,float rarity);
    unsigned long long getExperienceByUnitLevel(int _level,float rarity);
    unsigned long long getExperienceByLevel(int level);
    float getSummaryGloryByFlopTime(int time);
    int getUnitStrenthanExp(CreatorInfoBean* bean);
    int getVirtoryGloryFromEnemy(float enemyPower);
//    bool checkSummary(int)
    CCSprite* getResourceIcon(int resourceTag);
    CCSprite* getRecordBack();
    CCSprite* getVictoryUIBack();
    CCSprite* getDialogBack();
    CCSprite* getUnionBack();
    CCSprite* getCreateUnionBack();
    CCSprite* getNormalBox(float width, float height);
    CCSprite* getLineBox(float width, float height);
    CCSprite* getZhijiaoBox(float width, float height);
    CCSprite* getSecondMenuBox(float width, float height,float locx=0);
    CCSprite* getUpdateDialogBack();
    CCSprite* getDialogBackNoGirl();
    CCLayer* getUpdateDialog(bool isAction);
    CCLayer* getInfoDialog();
    CCSprite* getShopBack();
    CCSprite* getChargeBack();
    CCSprite* getServerRegistBack();
    CCSprite* getServerTipBack(int width,int height);
    CCLayer* getServerTipDialog(const std::string& msg);
    CCLayer* getServerTipDialog(const std::string& msg,CCObject* obj,SEL_MenuHandler selector);
    CCLayer* getUpdateBar(float per1,float per2,const char* upName);
    void cancelTipItem(CCMenuItem* item);
    void removeFromParentCallBack(CCMenuItem* item);
    int getVipLevel(int _vipExperience);
    CCLabelTTF* getVipColorLabel(const char *string,int size,int vipExperience);
    int getVipExperienceByLevel(int vipLevel);
    CCLayer* getVipDesc(int vipLevel,CCObject* rec,SEL_MenuHandler selector);
    CCLayer* getGarbageCollectionTotal(int resourceCount,int mubeiCount,float rate);
    CCLayer* getBuildingUnlockLayer(const char* name,int unlockLevel);
    CCLayer* getTitleBack(int width,int height,bool isCancel,const char* title);
//    int getRobMultipleByTime(unsigned long long deltaRobtime,long multiRobtime);
    
    void addloadSpeakerLayer(CCNode* parent,CCString* content);
    CCLayer* getQuestBack(CCObject* baseQuest,CCObject* rec,SEL_MenuHandler selector,bool isCancel = true);
    const char* getCountStrByCount(int count);
    
private:
    unsigned long long levelMap[100];
    MyUtil();
    virtual void toSettingCallBack();
    virtual void toExit();
    virtual void dismiss(CCNode* pSender);

    GXListView* loudSpeakerList;

};
//static MyUtil* instance;
#endif
