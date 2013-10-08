//
//  ContinueState.h
//  ww4
//
//  Created by xiao tang on 13-4-5.
//
//

#ifndef __ww4__ContinueState__
#define __ww4__ContinueState__

#include <iostream>
#include "MyState.h"

class ContinueState : public MyState {
    
public:
    ~ContinueState() {
//        CCLog("ContinueState has been release");
    }
    ContinueState():
    lrLoc(-1),
    udLoc(-1){
        for (int i=0; i<4; i++) {
            destroyBuilding[i] = 0;
        }
    }
    virtual void doState();
    static ContinueState* create(int _stateId,CCSprite* item,int _combineBuildingTag);
    virtual void init(MyBuilding* building);
    virtual void clickCallBack();
    virtual void toCombineCallBack(CCMenuItem* pSender);
    virtual void setItem(CCSprite* item);
    virtual void checkContinue();
    virtual void showAllTransition();
private:
    int lrLoc;
    int udLoc;
    MyBuilding* destroyBuilding[4];
    MyBuilding* destroyBuilding2[4];
    int combineBuildingTag;
    void combine();
    void toLrCombine(CCMenuItem* item);
    void toUdCombine(CCMenuItem* item);
};

#endif /* defined(__ww4__ContinueState__) */
