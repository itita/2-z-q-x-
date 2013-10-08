//
//  BattleScene.h
//  ww2
//
//  Created by DingYu Fu on 12-9-5.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#ifndef ww2_BattleScene_h
#define ww2_BattleScene_h
#include "cocos2d.h"
#include "MyBattleMap.h"
#include "GXBaseScene.h"
#include "MyAtlasNumber.h"

#define beforeFightTag 0
#define fightingTag 1
#define afterFightTag 2

#define surrenderTag 11
#define nextTag 12
#define surrenderDialogTag 13
#define bingzhongmenuTag 33

//#define bubingCreatorTag 101
//#define tankCreatorTag 102

class BattleScene : public GXBaseScene,public cocos2d::CCIMEDelegate,public cocos2d::CCTextFieldDelegate {
    
public:
    BattleScene():
    battleMap(NULL),
    isFighting(0),
    isVictory(false),
    fightMenu(NULL),
    enemyOilLabel(NULL),
    enemyIronLabel(NULL),
    enemyHonorLabel(NULL),
    enemyPowerLabel(NULL),
    lastTime(400),
    lastTimeLabel(NULL),
    trophyRate(0.5),
    enemyVipExperience(0),
    cellarProtectCount(0),
    attackType(0){
        char str[160] = {0};
        sprintf(str,"【点击此处更改留言】%s", CCUserDefault::sharedUserDefault()->getStringForKey("loseNoteTag","我还会回来的！！！").c_str());
        m_TextField = CCTextFieldTTF::textFieldWithPlaceHolder(str,CCSizeMake(545,100), kCCTextAlignmentLeft,"Arial",22);
        m_TextField->setColorSpaceHolder(ccc3(254,185,0));
        m_TextField->setColor(ccc3(254,185,0));
        m_TextField->setPosition(ccp(winSize.width/2-267,winSize.height/2-155));
        m_TextField->setAnchorPoint(ccp(0,0.5));
        m_TextField->setDelegate(this);
        CC_SAFE_RETAIN(m_TextField);
    };
    
    float trophyRate;
    int enemyVipExperience;
    
    virtual bool init();
    CREATE_FUNC(BattleScene);
    virtual bool init(CCArray* buildings);
    virtual void callback1(CCObject* pSender);
    static  BattleScene* create(CCArray* buildings,float _trophyRate,UnionBean* unionBean,int _enemyVipExperience);
    virtual ~BattleScene();
    virtual void toVictory();
    virtual void victory();
    virtual void toFight();
//    virtual void retain();
    virtual void toSurrender();
    virtual void doPause();
    virtual void doResume();
    virtual void loadResource();
    virtual void releaseResource();
    MyAtlasNumber* enemyOilLabel;
    MyAtlasNumber* enemyIronLabel;
    MyAtlasNumber* enemyHonorLabel;
    MyAtlasNumber* enemyPowerLabel;
    
    int getFighting() {
        return isFighting;
    }
    int attackType;
//    void setFighting(int i) {
//        isFighting = i;
//    }
    
    MyBattleMap* battleMap;
protected:
    
    
    CCTextFieldTTF* m_TextField;
    void displayIME(CCNode* node);
    int isFighting;
    bool isVictory;
    CCMenu* fightMenu;
//    virtual void initSound();
//    virtual void toReturnHomeWait();
//    virtual void toContinueWarWait();
    virtual void toBuildSceneWait(CCMenuItem* item);
    virtual void toBuildScene();
    virtual void toNext();
    virtual void toNextWait(CCMenuItem* item);
    virtual void initUI(UnionBean* unionBean,int _enemyVipExperience);
    virtual void surrender();
    virtual void cancelSurrender();
    virtual CCLayer* getVictoryUI(bool isVictory);
    virtual void addMatchInfo(bool victory);

private:
    int lastTime;
    CCLabelAtlas* lastTimeLabel;
    void countdown();
    float cellarProtectCount;
};

#endif
