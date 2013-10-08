//
//  NewbieReadyScene.h
//  ww4
//
//  Created by xiao tang on 13-1-5.
//
//

#ifndef __ww4__NewbieReadyScene__
#define __ww4__NewbieReadyScene__

#include "ReadyToBattleScene.h"


#define baseMenuTag 999


class NewbieReadyScene : public ReadyToBattleScene{

public:
    
    ~NewbieReadyScene() {
        releaseResource();
        CC_SAFE_RELEASE(baseInfoBeanArray);
    }
    
    void myInit();
    static NewbieReadyScene* create();
    CCMenuItemSprite* getBaseInfoItem();
    void toNewbieBattleCallback();
};

#endif /* defined(__ww4__NewbieReadyScene__) */
