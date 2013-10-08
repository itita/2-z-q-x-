//
//  ReadyToBattleScene.h
//  ww3
//
//  Created by xiao tang on 12-12-30.
//
//

#ifndef __ww3__ReadyToBattleScene__
#define __ww3__ReadyToBattleScene__

#include "GXBaseScene.h"
#include "MyMenuItem.h"




class ReadyToBattleScene : public GXBaseScene {
    
public:
    ReadyToBattleScene():
    baseInfoBeanArray(NULL){
    }
    
    ~ReadyToBattleScene() {
//        releaseResource();
//        CC_SAFE_RELEASE(baseInfoBeanArray);
//        CC_SAFE_RELEASE(myArmyList);
    }
    
    CCArray* baseInfoBeanArray;
    CCArray* myArmyList;
    void myinit();
    static ReadyToBattleScene* create(CCArray* baseList);
    virtual void loadResource();
    virtual void releaseResource();
    void toDeployArmy(CCNode* pSender);
    void quitDeployCallBack();
    
    int flag[0];
    
    
protected:
    void cloudCallBack(CCNode* pSender,CCSprite* cloud);
    void initCloud();
    void toNextCallBack();
    void toHomeCallBack();
    void selectCard(MyMenuItem* pSender);
    void cancelCard(MyMenuItem* pSender);
//    CCMenuItemSprite* getBaseInfoItem(BaseInfoBean* bean);
};





#endif /* defined(__ww3__ReadyToBattleScene__) */
