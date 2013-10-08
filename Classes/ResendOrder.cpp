//
//  ResendOrder.cpp
//  ww4
//
//  Created by xiao tang on 13-7-3.
//
//

#include "ResendOrder.h"

ResendOrder::ResendOrder()
:CCString(""),
orderId(0)
{}

ResendOrder::ResendOrder(const char * str)
:CCString(str),
orderId(0)
{}

ResendOrder::ResendOrder(const std::string& str)
:CCString(str),
orderId(0)
{}

ResendOrder::ResendOrder(const CCString& str)
:CCString(str.getCString()),
orderId(0)
{}

ResendOrder::~ResendOrder()
{
    
}

ResendOrder* ResendOrder::create(const std::string& str,int _orderId)
{
    ResendOrder* pRet = new ResendOrder(str);
    pRet->autorelease();
    pRet->orderId = _orderId;
    return pRet;
}