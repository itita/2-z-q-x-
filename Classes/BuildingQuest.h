//
//  BuildingQuest.h
//  ww4
//
//  Created by xiao tang on 13-6-8.
//
//

#ifndef __ww4__BuildingQuest__
#define __ww4__BuildingQuest__

#include <iostream>
#include "MyBaseQuest.h"

class BuildingQuest : public MyBaseQuest {
    
public:
    ~BuildingQuest() {
        CC_SAFE_RELEASE_NULL(descStr);
        //        CC_SAFE_RELEASE_NULL(dest);
        CC_SAFE_RELEASE_NULL(titleStr);
        CC_SAFE_RELEASE_NULL(deadLineLabel);
        CC_SAFE_RELEASE_NULL(needBuildingTagList);
        CC_SAFE_RELEASE_NULL(needBuildingLevelList);
        CC_SAFE_RELEASE_NULL(needBuildingLabelList);
        CC_SAFE_RELEASE_NULL(needBuildingCountList);
        CC_SAFE_RELEASE_NULL(finishBuildingCountList);
        
        CC_SAFE_RELEASE_NULL(prizeResourceTagList);
        CC_SAFE_RELEASE_NULL(prizeResourceCountList);
        
        
    }
    BuildingQuest():
    descStr(NULL),
    //    dest(NULL),
    titleStr(NULL),
    deadLineLabel(NULL),
    completeFlag(false)
    {
        needBuildingTagList = CCArray::create();
        needBuildingTagList->retain();
        needBuildingLevelList = CCArray::create();
        needBuildingLevelList->retain();
        needBuildingLabelList = CCArray::create();
        needBuildingLabelList->retain();
        needBuildingCountList = CCArray::create();
        needBuildingCountList->retain();
        finishBuildingCountList = CCArray::create();
        finishBuildingCountList->retain();
        
        prizeResourceTagList = CCArray::create();
        prizeResourceTagList->retain();
        prizeResourceCountList = CCArray::create();
        prizeResourceCountList->retain();
    }
    static BuildingQuest* create();
    virtual bool excuteMsg(MyBaseMessage* msg);
    virtual int getCompleteStatus();
    virtual void getPrize();
    virtual CCLayer* getDescLayer();
    //    virtual CCLayer* getSchedule();
    virtual CCLayer* getPrizeInfo();
    virtual CCLabelTTF* getTitle();
    bool checkCompleteStatues();
    CC_SYNTHESIZE_RETAIN(CCString*,descStr,DescStr);
    //    CC_SYNTHESIZE_RETAIN(CCString*,dest,Dest);
    CC_SYNTHESIZE_RETAIN(CCString*,titleStr,TitleStr);
    CC_SYNTHESIZE_RETAIN(CCString*,deadLineLabel,deadLineLabel);
    
    CCArray* needBuildingTagList;
    CCArray* needBuildingLevelList;
    CCArray* needBuildingLabelList;
    CCArray* needBuildingCountList;
    CCArray* finishBuildingCountList;
    
    CCArray* prizeResourceTagList;
    CCArray* prizeResourceCountList;
private:
    bool completeFlag;
};

#endif /* defined(__ww4__BuildingQuest__) */
