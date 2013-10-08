//
//  GXString.cpp
//  ww4
//
//  Created by xiao tang on 13-3-19.
//
//

#include "GXString.h"

GXString::GXString()
:CCString("")
{}

GXString::GXString(const char * str)
:CCString(str)
{}

GXString::GXString(const std::string& str)
:CCString(str)
{}

GXString::GXString(const CCString& str)
:CCString(str.getCString())
{}

GXString::~GXString()
{
    
}

GXString* GXString::create(const std::string& str)
{
    GXString* pRet = new GXString(str);
    return pRet;
}