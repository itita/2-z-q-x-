//
//  ReadyToBuild.h
//  ww2
//
//  Created by xiao tang on 12-10-9.
//
//

#ifndef ww2_ReadyToBuild_h
#define ww2_ReadyToBuild_h
#include "NormalState.h"
#include "GXAntiCrack.h"
#include "BuildingHeader.h"

class ReadyToBuild : public NormalState{
    
public:
    ReadyToBuild():
    buildingInfo(NULL),
    maxCount(0)
    {
        resourceTag = GXintValue::create(0);
        resourceTag->retain();
        summaryCount = GXintValue::create(0);
        summaryCount->retain();
        addExp = GXintValue::create(0);
        addExp->retain();
    }
    ~ReadyToBuild();
    static ReadyToBuild* create(int _stateId, CCSprite* item);
    virtual void cancelCallBack(cocos2d::CCObject *pSender);
    virtual void toBuildCallback(CCNode* pSender);
//    virtual void dismissAllTransition();
    virtual void showAllTransition();
    virtual void doEnd();
    
    virtual void setResourceTag(int _resourceTag);
    virtual int getResourceTag();
    virtual void setSummaryCount(int _summaryCount);
    virtual int getSummaryCount();
    virtual void setAddExp(int addExp);
    virtual int getAddExp();

    BuildingInfo* buildingInfo;
    int maxCount;
private:
    void removeFromFSM();
    GXintValue* resourceTag;
    GXintValue* summaryCount;
    GXintValue* addExp;
};

//class ReadyToBuildCreator : public NormalStateCreator{
//    
//public:
//    int summaryOil;
//    int summaryIron;
//    int summaryMilitary;
//    int addExp;
//    ReadyToBuildCreator():
//    summaryOil(0),
//    summaryIron(0),
//    summaryMilitary(0),
//    addExp(0){}
//    static ReadyToBuildCreator* create();
//    virtual CCObject* init();
//    
//};

#endif
