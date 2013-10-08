//
//  GXString.h
//  ww4
//
//  Created by xiao tang on 13-3-19.
//
//

#ifndef __ww4__GXString__
#define __ww4__GXString__

#include <iostream>
#include "cocos2d.h"

using namespace cocos2d;

class GXString : public CCString {
    
public:
    ~GXString();
    GXString();
    GXString(const char * str);
    GXString(const std::string& str);
    GXString(const CCString& str);
    
    static GXString* create(const std::string& str);
    
    
};

#endif /* defined(__ww4__GXString__) */
