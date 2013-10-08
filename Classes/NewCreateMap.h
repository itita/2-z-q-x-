//
//  NewCreateMap.h
//  ww2
//
//  Created by DingYu Fu on 12-9-13.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#ifndef ww2_NewCreateMap_h
#define ww2_NewCreateMap_h
#include "NewMap.h"
#include "NewMenuDevice.h"

class NewCreateMap: public NewMap {
    
public:
    
    NewMenuDevice* moveTemp;
    static NewCreateMap* create(const char* tmxfileName); 
    virtual void initTip(CCPoint pos,float scale);
    virtual void dispearTip();
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    virtual void cancelAllBuilding();
    virtual void loadTip();
    CCSprite* getTip();
    
protected:
    cocos2d::CCSprite* red;
    cocos2d::CCSprite* green;
    bool isCollision;
};

#endif
