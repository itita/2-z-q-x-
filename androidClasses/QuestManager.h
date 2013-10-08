//
//  QuestManager.h
//  ww3
//
//  Created by xiao tang on 12-12-14.
//
//

#ifndef ww3_QuestManager_h
#define ww3_QuestManager_h

#include "MyBaseTrigger.h"
#include "MyBaseQuest.h"
#include "MyBaseMessage.h"

class QuestManager : public MyBaseTrigger{
    
public:
    QuestManager():
    questList(NULL)
    {}
    ~QuestManager();
    
    static QuestManager* questManagerInstance;
    static QuestManager* getInstance();
    static QuestManager* create();
    
    CCArray* questList;
    bool addQuest(MyBaseQuest* quest);
    void removeQuest(MyBaseQuest* quest);
    virtual bool excuteMsg(MyBaseMessage* msg);
    virtual bool onRegist();
    virtual bool onUnRegist();
    void clear();
    
    
    
};

#endif
