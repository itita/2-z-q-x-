//
//  MyXueTiao.h
//  ww2
//
//  Created by DingYu Fu on 12-9-9.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#ifndef ww2_MyXueTiao_h
#define ww2_MyXueTiao_h
#include "cocos2d.h"

using namespace cocos2d;

class MyXueTiao : public CCSprite{
    
public:
    ~MyXueTiao() {
        
    };
    float percentage;
    virtual void updatePercentage(float percentage);
    static MyXueTiao* create(const char* filename);
private:
//    CCSize oriSize;
//    CCPoint oriPoint;
    CCRect myoriRect;
};

#endif
