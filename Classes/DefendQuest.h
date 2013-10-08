//
//  DefendQuest.h
//  ww4
//
//  Created by xiao tang on 13-6-18.
//
//

#ifndef __ww4__DefendQuest__
#define __ww4__DefendQuest__

#include "MyBaseQuest.h"
#include "GXAntiCrack.h"

class DefendQuest : public MyBaseQuest {
    
    
public:
    ~DefendQuest() {
        CC_SAFE_RELEASE_NULL(descStr);
        CC_SAFE_RELEASE_NULL(titleStr);
        CC_SAFE_RELEASE_NULL(deadLineLabel);
        
        CC_SAFE_RELEASE_NULL(prizeResourceTagList);
        CC_SAFE_RELEASE_NULL(prizeResourceCountList);
        
        CC_SAFE_RELEASE_NULL(defendTimes);
        CC_SAFE_RELEASE_NULL(needDefendTimes);
    }
    DefendQuest():
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
        defendTimes = GXintValue::create(0);
        defendTimes->retain();
        needDefendTimes = GXintValue::create(0);
        needDefendTimes->retain();
        
    }
    static DefendQuest* create();
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
    GXintValue* defendTimes;
    GXintValue* needDefendTimes;
    
    CCArray* prizeResourceTagList;
    CCArray* prizeResourceCountList;
    
};

#endif /* defined(__ww4__DefendQuest__) */
