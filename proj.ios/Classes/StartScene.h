//
//  StartScene.h
//  ww2
//
//  Created by DingYu Fu on 12-8-22.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#ifndef ww2_StartScene_h
#define ww2_StartScene_h

#include "cocos2d.h"
#include "MyBuilding.h"
#include "GXBaseScene.h"
#include "GXMsg.h"
#include "MyBaseTrigger.h"
#include "GXListView.h"
#include "MyBaseQuest.h"

//state
#define displayUnionLayerTag 1039
#define createUnionEmblemTag 1040
#define createUnionNameTextTag 1041
#define createUnionDesTextTag 1042
#define createUnionTipLayerTag 1043
#define unionManagerLayerTag 1044
#define questMenuTag 1061

using namespace cocos2d;

class StartScene : public GXBaseScene,public cocos2d::CCIMEDelegate,public cocos2d::CCTextFieldDelegate {

public:
    
    virtual void initUI();
    virtual void initControl();
//    CCString* nickname;
//    int oil;
//    int iron;
    bool isClickExit;
    void cancelClickExit();
public:
    StartScene():
    isClickExit(false),
    pageNo(1),
    controlMenu(NULL),
    m_TextField(NULL),
    unionTrigger(NULL),
    totalCharListView(NULL),
    unionCharListView(NULL),
    robMultiple(0){
        sprintf(cacheChar, "");
    };
    
    virtual ~StartScene();
    
    MyBaseTrigger* unionTrigger;
    MyBaseTrigger* storeTrigger;
    virtual bool init();
    virtual bool init(CCArray* buildings);
    CREATE_FUNC(StartScene);
    static  StartScene* create(CCArray* buildings);
    virtual bool updateMyData();
    virtual void toExit();
    virtual void doPause();
    virtual void doSaveToExit();
//    virtual void doSaveAsynchronous(CCMenuItemSprite* item);
//    virtual void doSaveAsynchronousCallBack(bool isSucc);
    virtual void toBattleScene();
    void toChehiefSceneWait();
    void toChehiefScene();
    void displayIME(CCNode* node);
    virtual void sendCallBack(CCNode* sender);
    virtual void updateChar();
    virtual void loadResource();
    virtual void releaseResource();
    void addRecordNewIcon();

    
//    virtual void retain();
//    virtual void release();
    
    int pageNo;
//小偷相关
    int robMultiple;
    void initBugei(unsigned long long robDeltaTime,long robMultipleTime);
    
public:
    CCTextFieldTTF* m_TextField;
    CCNode* controlMenu;
    GXListView* totalCharListView;
    GXListView* unionCharListView;
//    void testCallBack(CCObject* pSender);
//    void workCallBack(CCObject* pSender);
//    void destroyCallBack(CCObject* pSender);
//    void collectCallBack(CCObject* pSender);
    void infoCallBack(CCObject* pSender);
    void updateCallBack(CCObject* pSender);
//    void conscriptionCallBack(CCObject* pSender);
//    void sellCallBack(CCObject* pSender);
//    void toBattleCallBack(CCObject* pSender);
    void toCreateCallBack(CCObject* pSender);
    void toRecordCallBack(CCObject* pSender);
    void toShowCallBack(CCObject* psender);
    void toArmyCallBack(CCObject* psender);
    void toArmyCallBackSimple(CCObject* psender);
    void toUnlockBudui(CCMenuItem* item);
//    void toDismissUnlock(CCMenuItem* item);
    void unlockBuduiAndReturn(CCMenuItem* item);
//    void disPlayRecordViewWait();
    void disPlayRecordView(CCArray* matchInfos);
    void displayTopRankView(CCArray* topArray);
    
    void displayRecordCallBack(CCNode* pSender);
    void displayWonRecordCallBack(CCNode* pSender);
    void displayLoseRecordCallBack(CCNode* pSender);
    
    void displayTopRankCallBack(CCNode* pSender);
    void nextPageCallBack(CCNode* pSender);
    void prePageCallBack(CCNode* pSender);
    void toCancelRecorder(CCObject* pSender);
    void toReadyCallback(CCObject* pSender);
    void toZhengbingCallBack(CCMenuItem* pSender);
    void zhengbingWaitServerCallBack(CCMenuItem* pSender);
    void zhengbingCallBack(CCMenuItem* pSender);
//    void toBuildCallback(CCNode* pSender);
    void toggleRecorder(CCObject* pSender);
    void cancelAllDialog();
//    void getAllMatches(CCNode* pSender);
    virtual void hiddenControlUI();
    virtual void displayControlUI();
    MyBuilding* createReady(int tag);
    void quitCreator();
   
//    CCLayer* getUpdateDialog();
    bool cancelUpdateDialog(CCNode* pSender);
    void toCharDialog(CCNode* pSender);
    void addCharMsg(GXMsg* msg);
    void keyboardWillHide(CCIMEKeyboardNotificationInfo& info);
    void keyboardDidHide(CCIMEKeyboardNotificationInfo& info);
    void removeWaitMenu();
//    virtual void onExit();
//    void toReverageCallBack(CCObject* pSender);
//    void initSound();
    void createUnionResult(bool isSucc,CCString* msg);
    void toUnionJoinOrCreate();
    void toUnionMainUI();
    void cancelTipDialog(CCMenuItem* item);
    void unionManagerNotice();
    void displayUnionJoin(CCArray* unionArray);
    void displayUnionMember(CCArray* member);
    bool checkNewUnionMessage(CCDictionary* varMap);
    void addUnionLayerInAvatar();
    void removeUnionLayerInAvatar();
    void toOneKeyArchieveGhost(CCMenuItem* item);
    void subMubei();
    void toRefreshStartScene();
    void displayDefendList(CCArray* beans);
    void addorUpdateBuilding(CCObject* obj);
    CCMenuItem* displayMubeiInfo(int mubeiCount);
    void toShopCallBackWait(CCMenuItem* item);
    //充值
    void toDisplayCharge();
    void toShopCallBack();
    void toBuyBuilding(CCMenuItem* item);
    void toBuyArmy(CCMenuItem* item);
    void toBuyResource(CCMenuItem* item);
    void toDisplayBuildingInfo(CCMenuItem* item);
    void toChargeCallBack(CCMenuItem* item);
    void displayBoostProduceView(bool isFree);
    
    //任务
    void addDisplayQuest(CCObject* quest,bool isAppear = false);
    void addDisplayQuest(CCMenu* questMenu,CCObject* quest,bool isAppear = false);
//    void addDisplayHuodong(CCMenuItem* huodong);
    void addDisplayHuodong(CCMenu* menu,CCMenuItem* huodong);
    void toDisplayMissionInfo(CCMenuItem* item);
    void displayMissionInfo(MyBaseQuest* quest);
    void toGetQuestPrize(CCMenuItem* item);
    void updateQuestUI(int missionId);
    void addAttackInfo(CCObject* attackInfoBean);
    void addAttackArmy(CCObject* attackInfoBean);
    void toArchieveQuestPrize(int missionId);
    void toChangeName();
    void sureChangeName(CCSprite* item);
    
    
    
private:
    char cacheChar[450];
    inline bool dismissDisplayArmyLayer();
    inline CCSprite* getArmyKuang();
    void displayCardInfo(CCMenuItem* pSender);
    void dismissCardInfo(CCMenuItem* pSender);
    void armyUpCard(CCMenuItem* pSender, CCMenu* item);
    void armydowncard(CCMenuItem* pSender, CCMenu* item);
    void flopArmycard(CCMenuItem* pSender);
    void zhengbingtoBudui(CCMenuItem* pSender);
    void displayOtherCard(CCMenuItem* pSender);
    void archieveArmy();
    void displayNewArmyFromZhengbing(CCNode* target,CCMenuItem* pSender);
    void toArmyInfoInfo(CCMenuItem* pSender);
    void toRunInfoAction(CCMenuItem* pSender);
    void toInfoInfoCallBack();
    void toInfoStrenthenCallBack();
    void toInfoStrenthenCallBackSimple();
    void toChooseArmytobeStrenthen(CCMenuItem* pSender);
    void selectCard(CCMenuItem* pSender);
    void cancelCard(CCMenuItem *pSender);
    void sureBeStrenthenCard(CCMenuItem* pSender);
    void toSureStrenthenSimple(CCMenuItem* pSender);
    void toSureStrenthen(CCMenuItem* pSender);
    void runSureStrenthenAction(CCNode* pSender);
    void runSureStrenthenHeChengAction(CCNode* target,CCNode* Data);
    void runSureStrenthenReturnAction();
    void zhengbingReturnToInfo(CCMenuItem* pSender);
    void finishStrenthenToInfo();
    void changeStrenthanInfoInStrenthaning(CCNode* target,CCNode* data);
    void bugeiMultipleTimer();
    void getServerOrderId();
    void displayBuildingScroll(CCMenuItem* pSender);
    void displayArmyScroll(CCMenuItem* pSender);
    //显示二级界面的方法
    void displayConmunication(CCMenuItem* item);
    void displayVip(CCMenuItem* item);
    
    void toCancelSecond();
    //联盟
    void toUnionCallBack();
    void toCreateUnion();
    void toSendCreateUnionCmd(CCMenuItem* item);
    void toUnionMessage();
    void toUnionInfo();
    void toUnionMember();
    void toUnionManager();
    void switchEmblem(CCMenuItemSprite* item);
    void displayUnionIME(CCMenuItem* item);
    void sureCreateUnion(CCMenuItem* item);
    void unionSendNotice(CCMenuItem* item);
    void unionManagerAppointMent();
    void unionManagerOperate();
    void toUnionJoin();
    void toSureJoin(CCMenuItem* item);
    void sendJoinUnion(CCMenuItem* item);
    void replayJoinApplicant(CCMenuItem* item);
    void memberListPage(CCMenuItem* item);
    void operatorMember(CCMenuItem* item);
    void sureKickMember(CCMenuItem* item);
    void toKickMember(CCMenuItem* item);
    void sureOpeateUnion(CCMenuItem* item);
    void sendOpeateUnion(CCMenuItem* item);
    void changeCharFliter(CCMenuItem* item);
    void doLogout();
//    void popMenuMenu();
    
    
    //商城
    
    void toDisplayHot();
    void toDisplayAvatar();
    void toDisplayUnit();
    void toDisplayBuilding();
    void toDisplayResource();
    void toDisplayUnitInfo(CCMenuItem* item);
    void toSureBuyArmy(CCMenuItem* item);
    void toSureBuyResource(CCMenuItem* item);
    void dismissPost(CCMenuItem* item);
    void runAttackerWave(CCSprite* sprite);
    void moveToAttackerLoc();
    void toDefendScene(CCMenuItem* item);
    void shakeEffect(CCNode* node);
    void shakeEffect2(CCNode* node);
    CCMenuItem* addBugeiButton();

//VIP
    void toYiJianShouKuang();
    void toOneKeyUpdate();
    void toOneKeyNextOrPreButton(CCMenuItem* item);
    void oneKeyNextOrPreCallback(CCMenuItem* item);
    void sureOneKeyUpdate(CCMenuItem* item);
    void toBoostProduce();
    void sureBoostProduce(CCMenuItem* item);
    void toResourceConversion(CCMenuItem* item);
    void changeConversionResource(CCObject* obj);
    void changeConversionRate(CCMenuItem* item);
    void changeConversionType(CCMenuItem* item);
    void refreshConversionUI(CCLayer* mainLayer,int typeInt);
    void sureConversionResource(CCMenuItem* item);
    
//防守战
    void toGetDefendList();

//测试用例
//    void sendTestMsg();
//    int x;
//    int y;
};




#endif //ww2_StartScene_h
