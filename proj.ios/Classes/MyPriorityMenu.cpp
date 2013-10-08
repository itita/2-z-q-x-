//
//  MyPriorityMenu.cpp
//  ww2
//
//  Created by DingYu Fu on 12-9-23.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "MyPriorityMenu.h"

MyPriorityMenu* MyPriorityMenu::create(int _priority, cocos2d::CCMenuItem *item, ...)
{
    va_list args;
    va_start(args,item);
    MyPriorityMenu *pRet = new MyPriorityMenu();
    CCArray* pArray = NULL;
    if( item )
    {
        pArray = CCArray::create(item, NULL);
        CCMenuItem *i = va_arg(args, CCMenuItem*);
        while(i)
        {
            pArray->addObject(i);
            i = va_arg(args, CCMenuItem*);
        }
    }
    
    if (pRet && pRet->initWithArray(pArray))
    {
        pRet->priority = _priority;
        pRet->autorelease();
        va_end(args);
        return pRet;
    }
    va_end(args);
    CC_SAFE_DELETE(pRet);
    return NULL;
}


void MyPriorityMenu::registerWithTouchDispatcher()
{
    CCDirector* pDirector = CCDirector::sharedDirector();
    pDirector->getTouchDispatcher()->addTargetedDelegate(this, priority, isSwallow);
}

MyPriorityMenu* MyPriorityMenu::createWithArray(int _priority,CCArray* pArrayOfItems)
{
    MyPriorityMenu *pRet = new MyPriorityMenu();
    if (pRet && pRet->initWithArray(pArrayOfItems))
    {
        pRet->priority = _priority;
        pRet->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(pRet);
    }
    
    return pRet;
}

MyPriorityMenu::~MyPriorityMenu() {
//    CCLog("MyPriorityMenu released");
}