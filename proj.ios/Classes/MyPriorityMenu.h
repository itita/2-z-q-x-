//
//  MyPriorityMenu.h
//  ww2
//
//  Created by DingYu Fu on 12-9-23.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#ifndef ww2_MyPriorityMenu_h
#define ww2_MyPriorityMenu_h
#include "cocos2d.h"

using namespace cocos2d;

class MyPriorityMenu : public CCMenu{
    
public:
    MyPriorityMenu():
    priority(-499),
    isSwallow(true){
    }
    
    ~MyPriorityMenu();
    static MyPriorityMenu* create(int _priority,CCMenuItem* item, ...);
    virtual void registerWithTouchDispatcher();
    static MyPriorityMenu* createWithArray(int _priority,CCArray* pArrayOfItems);
    bool isSwallow;
private:
    int priority;
    
};




#endif
