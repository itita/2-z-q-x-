//
//  EveryDayTask1.h
//  ww4
//
//  Created by xiao tang on 13-6-3.
//
//

#ifndef __ww4__EveryDayTask1__
#define __ww4__EveryDayTask1__

#include "MyBaseQuest.h"

class EveryDayTask1 : public MyBaseQuest {
    
    
public:
    ~EveryDayTask1() {
        CC_SAFE_RELEASE_NULL(descStr);
//        CC_SAFE_RELEASE_NULL(dest);
        CC_SAFE_RELEASE_NULL(titleStr);
        CC_SAFE_RELEASE_NULL(deadLineLabel);
        CC_SAFE_RELEASE_NULL(costResourceTagList);
        CC_SAFE_RELEASE_NULL(costResourceCountList);
        CC_SAFE_RELEASE_NULL(prizeResourceTagList);
        CC_SAFE_RELEASE_NULL(prizeResourceCountList);
    }
    EveryDayTask1():
    descStr(NULL),
//    dest(NULL),
    titleStr(NULL),
    deadLineLabel(NULL)
    {
        costResourceTagList = CCArray::create();
        costResourceTagList->retain();
        costResourceCountList = CCArray::create();
        costResourceCountList->retain();
        prizeResourceTagList = CCArray::create();
        prizeResourceTagList->retain();
        prizeResourceCountList = CCArray::create();
        prizeResourceCountList->retain();
    }
    static EveryDayTask1* create();
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
    
    CCArray* costResourceTagList;
    CCArray* costResourceCountList;
    CCArray* prizeResourceTagList;
    CCArray* prizeResourceCountList;

};


#endif /* defined(__ww4__EveryDayTask1__) */
