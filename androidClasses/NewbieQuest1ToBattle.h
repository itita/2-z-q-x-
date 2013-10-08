//
//  NewbieQuest1ToBattle.h
//  ww3
//
//  Created by xiao tang on 12-12-14.
//
//

#ifndef ww3_NewbieQuest1ToBattle_h
#define ww3_NewbieQuest1ToBattle_h

#include "MyBaseQuest.h"

class NewbieQuest1ToBattle : public MyBaseQuest {
    
    
public:
    ~NewbieQuest1ToBattle() {
        CCLog("~NewbieQuest1ToBattle 结束了");
    }
    static NewbieQuest1ToBattle* create();
    virtual void getPrize();
    virtual bool excuteMsg(MyBaseMessage* msg);
    virtual int getCompleteStatus();
    virtual CCLayer* getDescLayer();
//    virtual CCLayer* getSchedule();
    virtual CCLayer* getPrizeInfo();
    virtual CCLabelTTF* getTitle();
};

#endif
