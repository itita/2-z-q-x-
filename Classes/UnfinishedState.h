//
//  UnfinishedState.h
//  ww3
//
//  Created by xiao tang on 12-10-18.
//
//

#ifndef ww3_UnfinishedState_h
#define ww3_UnfinishedState_h
#include "MyState.h"

class UnfinishedState :public MyState {
    
public:
    virtual  ~UnfinishedState();
    UnfinishedState():
    maxLevel(0),
    level(0),
    cost(NULL),
    fileName(NULL){}
    static UnfinishedState* create(int _stateId,const char* fileName,int maxLevel);
    virtual void init(MyBuilding* building);
    virtual void CallBack(cocos2d::CCObject *pSender);
    virtual void changeIdCallBack(CCObject* pSender);
    virtual void sellCallBack(CCObject* pSender);
//    virtual void dismissAllTransition();
    virtual void showAllTransition();
    virtual void doStart();
    virtual void doEnd();
private:
    //maxlevel是建造时候所需要的级数
    int maxLevel;
    int level;
    int* cost;
    const char* fileName;
    void updateItem();
};

//class UnfinishedStateCreator : public MyStateCreator {
//    
//public:
//    UnfinishedStateCreator():
//    maxLevel(0) {}
//    int maxLevel;
//    static UnfinishedStateCreator* create();
//    virtual CCObject* init();
//   
//};

#endif
