//
//  ResendOrder.h
//  ww4
//
//  Created by xiao tang on 13-7-3.
//
//

#ifndef __ww4__ResendOrder__
#define __ww4__ResendOrder__

#include <iostream>
#include "cocos2d.h"

using namespace cocos2d;

class ResendOrder : public CCString {
    
public:
    ~ResendOrder();
    ResendOrder();
    ResendOrder(const char * str);
    ResendOrder(const std::string& str);
    ResendOrder(const CCString& str);
    
    
    static ResendOrder* create(const std::string& str,int _orderId);
    int orderId;
    
};

#endif /* defined(__ww4__ResendOrder__) */
