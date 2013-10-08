//
//  LevelQuest.h
//  ww4
//
//  Created by xiao tang on 13-6-19.
//
//

#ifndef __ww4__LevelQuest__
#define __ww4__LevelQuest__

#include "MyBaseQuest.h"
#include "GXAntiCrack.h"

class LevelQuest : public MyBaseQuest {
    
    
public:
    ~LevelQuest() {
        CC_SAFE_RELEASE_NULL(descStr);
        CC_SAFE_RELEASE_NULL(titleStr);
        CC_SAFE_RELEASE_NULL(deadLineLabel);
        
        CC_SAFE_RELEASE_NULL(prizeResourceTagList);
        CC_SAFE_RELEASE_NULL(prizeResourceCountList);
        
        CC_SAFE_RELEASE_NULL(needLevel);
    }
    LevelQuest():
    descStr(NULL),
    //    dest(NULL),
    titleStr(NULL),
    //    battleTimes(0),
    //    needBattleTimes(-1),
    deadLineLabel(NULL),
    isComplete(-1)
    {
        prizeResourceTagList = CCArray::create();
        prizeResourceTagList->retain();
        prizeResourceCountList = CCArray::create();
        prizeResourceCountList->retain();
    
        needLevel = GXintValue::create(0);
        needLevel->retain();
        
    }
    static LevelQuest* create();
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
   
    GXintValue* needLevel;
    
    CCArray* prizeResourceTagList;
    CCArray* prizeResourceCountList;
    bool checkComplete();
private:
    int isComplete;
};

#endif /* defined(__ww4__LevelQuest__) */
