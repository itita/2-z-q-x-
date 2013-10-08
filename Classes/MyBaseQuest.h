//
//  BaseQuset.h
//  ww3
//
//  Created by xiao tang on 12-12-14.
//
//

#ifndef ww3_MyBaseQuest_h
#define ww3_MyBaseQuest_h

#include "cocos2d.h"
#include "MyBaseMessage.h"
#include "DiaLayer.h"


#define questUnfinishedTag 0
#define questFinishedTag 1
#define questFailedTag 2

#define everyDayTaskTag 0
#define powerQuestTag 1
#define BuildingQuestTag 2
#define armyQuestTag 3
#define battleQuestTag 4
#define defendQuestTag 5
#define levelQuestTag 6

using namespace cocos2d;

class MyBaseQuest : public CCObject {
    
public:
    ~MyBaseQuest() {
        CC_SAFE_RELEASE_NULL(iconName);
        CC_SAFE_RELEASE_NULL(dialog);
    }
    MyBaseQuest():
    completeStatusInt(0),
    questTag(-1),
    questId(-1), 
    iconName(NULL),
    deadLine(0),
    hasNext(false),
    dialog(NULL)
    {}
    virtual bool excuteMsg(MyBaseMessage* msg);
    virtual int getCompleteStatus() = 0;
    virtual void getPrize() = 0;
    virtual CCLayer* getDescLayer() = 0;
//    virtual CCLayer* getSchedule() = 0;
    virtual CCLayer* getPrizeInfo() = 0;
    virtual CCLabelTTF* getTitle() = 0;
    int questTag;
    int questId;
    unsigned long long deadLine;
    bool hasNext;
    CC_SYNTHESIZE_RETAIN(CCString*,iconName,IconName);
    CC_SYNTHESIZE_RETAIN(DiaLayerInfoBean*,dialog,Dialog);
//    CC_SYNTHESIZE_RETAIN(CCString*,iconName,ServerName);
protected:
    int completeStatusInt;
};

#endif
