//
//  BattleQuest.h
//  ww4
//
//  Created by xiao tang on 13-6-8.
//
//

#ifndef __ww4__BattleQuest__
#define __ww4__BattleQuest__

#include "MyBaseQuest.h"
#include "GXAntiCrack.h"

class BattleQuest : public MyBaseQuest {
    
    
public:
    ~BattleQuest() {
        CC_SAFE_RELEASE_NULL(descStr);
        CC_SAFE_RELEASE_NULL(titleStr);
        CC_SAFE_RELEASE_NULL(deadLineLabel);
        
        CC_SAFE_RELEASE_NULL(prizeResourceTagList);
        CC_SAFE_RELEASE_NULL(prizeResourceCountList);
        
        CC_SAFE_RELEASE_NULL(battleTimes);
        CC_SAFE_RELEASE_NULL(needBattleTimes);
    }
    BattleQuest():
    descStr(NULL),
    //    dest(NULL),
    titleStr(NULL),
//    battleTimes(0),
//    needBattleTimes(-1),
    deadLineLabel(NULL)
    {
        prizeResourceTagList = CCArray::create();
        prizeResourceTagList->retain();
        prizeResourceCountList = CCArray::create();
        prizeResourceCountList->retain();
        battleTimes = GXintValue::create(0);
        battleTimes->retain();
        needBattleTimes = GXintValue::create(0);
        needBattleTimes->retain();
        
    }
    static BattleQuest* create();
    virtual bool excuteMsg(MyBaseMessage* msg);
    virtual int getCompleteStatus();
    virtual void getPrize();
    virtual CCLayer* getDescLayer();
    //    virtual CCLayer* getSchedule();
    virtual CCLayer* getPrizeInfo();
    virtual CCLabelTTF* getTitle();
    CC_SYNTHESIZE_RETAIN(CCString*,descStr,DescStr);
    //    CC_SYNTHESIZE_RETAIN(CCString*,dest,Dest);
    CC_SYNTHESIZE_RETAIN(CCString*,titleStr,TitleStr);
    CC_SYNTHESIZE_RETAIN(CCString*,deadLineLabel,deadLineLabel);
    GXintValue* battleTimes;
    GXintValue* needBattleTimes;
   
    CCArray* prizeResourceTagList;
    CCArray* prizeResourceCountList;
    
};

#endif /* defined(__ww4__BattleQuest__) */
