//
//  GXUtil.h
//  ww2
//
//  Created by DingYu Fu on 12-9-9.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#ifndef ww2_GXUtil_h
#define ww2_GXUtil_h
#include "cocos2d.h"

class GXUtil {
    
    
public:
    static cocos2d::CCAnimation* initAction(const char* _spriteFrameName,float interval,bool isReverse);
    static cocos2d::CCString* readFile(const std::string& relativefilePath);
    static void WStrToUTF8(std::string& dest, const std::wstring& src);
    static cocos2d::CCAnimate* flipFX(bool frontToback);
    static cocos2d::CCArray* Split(const char* content, const char* token);
    static char* transCharVectorToCCString(std::vector<char>* vector);
    static bool loadResourceUtilSucc(const char* plist,const char* pvr);
    static std::string insertNewline(const char* str, int lineSize);
    static bool checkWordandNum(const char* str);
};

#endif
