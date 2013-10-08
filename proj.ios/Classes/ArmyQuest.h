//
//  ArmyQuest.h
//  ww4
//
//  Created by xiao tang on 13-6-8.
//
//

#ifndef __ww4__ArmyQuest__
#define __ww4__ArmyQuest__

#include "MyBaseQuest.h"

class ArmyQuest : public MyBaseQuest {
    
public:
    ~ArmyQuest() {
        CC_SAFE_RELEASE_NULL(descStr);
        CC_SAFE_RELEASE_NULL(titleStr);
        CC_SAFE_RELEASE_NULL(deadLineLabel);
        
        CC_SAFE_RELEASE_NULL(needArmyTagList);
        CC_SAFE_RELEASE_NULL(needArmyLevelList);
        CC_SAFE_RELEASE_NULL(needArmyLabelList);
        CC_SAFE_RELEASE_NULL(finishArmyList);
        
        CC_SAFE_RELEASE_NULL(prizeResourceTagList);
        CC_SAFE_RELEASE_NULL(prizeResourceCountList);
        
       
    }
    ArmyQuest():
    descStr(NULL),
    //    dest(NULL),
    titleStr(NULL),
    deadLineLabel(NULL),
    completeFlag(-1)
    {
        needArmyTagList = CCArray::create();
        needArmyTagList->retain();
        needArmyLevelList = CCArray::create();
        needArmyLevelList->retain();
        needArmyLabelList = CCArray::create();
        needArmyLabelList->retain();
      
        finishArmyList = CCArray::create();
        finishArmyList->retain();
        
        prizeResourceTagList = CCArray::create();
        prizeResourceTagList->retain();
        prizeResourceCountList = CCArray::create();
        prizeResourceCountList->retain();
    }
    static ArmyQuest* create();
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
    
//    bool checkCompleteStatues();
    
    CCArray* needArmyTagList;
    CCArray* needArmyLevelList;
    CCArray* needArmyLabelList;
    CCArray* finishArmyList;
    
    CCArray* prizeResourceTagList;
    CCArray* prizeResourceCountList;
private:
    int completeFlag;
    void checkCompleteStatues();
};
#endif /* defined(__ww4__ArmyQuest__) */
