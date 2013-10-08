//
//  PowerQuest.h
//  ww4
//
//  Created by xiao tang on 13-6-8.
//
//

#ifndef __ww4__PowerQuest__
#define __ww4__PowerQuest__

#include "MyBaseQuest.h"
#include "GXAntiCrack.h"

class PowerQuest : public MyBaseQuest {
    
public:
    ~PowerQuest() {
        CC_SAFE_RELEASE_NULL(descStr);
        //        CC_SAFE_RELEASE_NULL(dest);
        CC_SAFE_RELEASE_NULL(titleStr);
        CC_SAFE_RELEASE_NULL(deadLineLabel);
        CC_SAFE_RELEASE_NULL(costResourceTagList);
        CC_SAFE_RELEASE_NULL(costResourceCountList);
        CC_SAFE_RELEASE_NULL(prizePower);
    }
    PowerQuest():
    descStr(NULL),
    //    dest(NULL),
    titleStr(NULL),
    deadLineLabel(NULL)
    {
        costResourceTagList = CCArray::create();
        costResourceTagList->retain();
        costResourceCountList = CCArray::create();
        costResourceCountList->retain();
        prizePower = GXfloatValue::create(0.0);
        prizePower->retain();
    }
    static PowerQuest* create();
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
    GXfloatValue* prizePower;
    
};


#endif /* defined(__ww4__PowerQuest__) */
