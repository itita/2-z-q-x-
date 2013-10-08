//
//  GXUtil.cpp
//  ww2
//
//  Created by DingYu Fu on 12-9-9.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "GXUtil.h"
#include "cocos2d.h"
#include "GXAnimate.h"


#if   (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#define utfChinese -32
#endif
#if   (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#define utfChinese 224
#endif

using namespace cocos2d;

CCAnimation* GXUtil::initAction(const char *_spriteFrameName,float interval,bool isReverse) {
    char str[64] = {0};
    CCArray* array = CCArray::create();
    int i = 0;
    while (true) {
        //            CCLog("%s (%d).png",spriteFileName);
        //            sprintf(str, "%s (%d).png",spriteFileName,15*j+i);
        sprintf(str, "%s (%d).png",_spriteFrameName,i);
        CCSpriteFrame* sprite = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(str);
        if(sprite == NULL) {
            break;
        } else {
            array->addObject(sprite);
        }
        i++;
    }
    if (isReverse) {
        for (int j = i-1; j>=0; j--) {
            sprintf(str, "%s (%d).png",_spriteFrameName,j);
            CCSpriteFrame* sprite = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(str);
            if(sprite == NULL) {
                break;
            } else {
                array->addObject(sprite);
            }
        }
    }
    
    CCAnimation* animation = CCAnimation::createWithSpriteFrames(array,interval);
    animation->setRestoreOriginalFrame(false);
//    animation->setLoops(loopTimes);
//    animation->retain();
    return animation;
}

CCString* GXUtil::readFile(const std::string& relativefilePath)  {
    unsigned long bufferSize = 0;
    unsigned char* data = CCFileUtils::sharedFileUtils()->getFileData(CCFileUtils::sharedFileUtils()->fullPathForFilename(relativefilePath.c_str()).c_str(), "r", &bufferSize);
    std::string str = (const char*)data;
    str = str.substr(0,bufferSize);
    
    return CCString::create(str);
}



void GXUtil::WStrToUTF8(std::string& dest, const std::wstring& src){
    
    dest.clear();
    
    for (size_t i = 0; i < src.size(); i++){
        
        wchar_t w = src[i];
        
        if (w <= 0x7f)
            
            dest.push_back((char)w);
        
        else if (w <= 0x7ff){
            
            dest.push_back(0xc0 | ((w >> 6)& 0x1f));
            
            dest.push_back(0x80| (w & 0x3f));
            
        }
        
        else if (w <= 0xffff){
            
            dest.push_back(0xe0 | ((w >> 12)& 0x0f));
            
            dest.push_back(0x80| ((w >> 6) & 0x3f));
            
            dest.push_back(0x80| (w & 0x3f));
            
        }
        
        else if (sizeof(wchar_t) > 2 && w <= 0x10ffff){
            
            dest.push_back(0xf0 | ((w >> 18)& 0x07)); // wchar_t 4-bytes situation
            
            dest.push_back(0x80| ((w >> 12) & 0x3f));
            
            dest.push_back(0x80| ((w >> 6) & 0x3f));
            
            dest.push_back(0x80| (w & 0x3f));
            
        }
        
        else
            
            dest.push_back('?');
        
    }
    
}

CCAnimate* GXUtil::flipFX(bool frontToBack) {
    CCArray* array = CCArray::create();
    CCSpriteFrame* s0 = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("armycardflop (0).png");
    CCSpriteFrame* s1 = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("armycardflop (1).png");
    CCSpriteFrame* s2 = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("armycardflop (2).png");
    CCSpriteFrame* s3 = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("armycardflop (3).png");
    if (frontToBack) {
        CCSpriteFrame* s4 = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("armycardbeimian.png");
        array->addObject(s0);
        array->addObject(s1);
        array->addObject(s2);
        array->addObject(s3);
        array->addObject(s4);
    } else {
        CCSpriteFrame* s4 = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("armycardback.png");
        array->addObject(s3);
        array->addObject(s2);
        array->addObject(s1);
        array->addObject(s0);
        array->addObject(s4);
    }
    CCAnimation* animation = CCAnimation::createWithSpriteFrames(array, 0.05);
    return GXAnimate::create(animation);
}

CCArray* GXUtil::Split(const char* content, const char* token) {
    if(content == NULL)
        return NULL;
    int len = strlen(content);
    if(len <= 0)
        return NULL;
    char* pBuf =(char*)malloc(len+1);
    strcpy(pBuf , content);
    char* str = strsep(&pBuf , token);
    CCArray* returnArray = CCArray::create();
    while(str != NULL)
    {
        returnArray->addObject(CCString::create(str));
        str = strsep(&pBuf, token);
    }
    free(pBuf);
    return returnArray;
}

char* GXUtil::transCharVectorToCCString(std::vector<char>* vector) {
    char* str = (char*)malloc(vector->size()*sizeof(char)+1);
    memset(str,0,vector->size()+1);
    for (unsigned int i = 0; i < vector->size(); i++)
    {
        str[i] = (*vector)[i];
    }
    return str;
}

bool GXUtil::loadResourceUtilSucc(const char* plist,const char* pvr) {
    bool flag = false;
    while(CCTextureCache::sharedTextureCache()->textureForKey(pvr) == NULL) {
        CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(plist,pvr);
        flag = true;
    };
    return flag;
}

std::string GXUtil::insertNewline(const char* str,int lineSize) {
//    char str2[60] = {0};
    
    int length = (lineSize*3+5)*sizeof(char);
    char* str2 = (char*)malloc(length);
    for (int j=0; j<length; j++) {
        str2[j] = 0;
    }
    std::string str3;
    
    int count  = strlen(str);
    int multi = 0;
    int i = 0;
    float fen = 0;
    int total = 0;
//    CCLog("%s",str);
    
    while (i < count) {
        if (((str[i] & utfChinese) == utfChinese) && ((str[i] | utfChinese) == str[i])) {
            str2[i-total] = str[i];
            str2[i+1-total] = str[i+1];
            str2[i+2-total] = str[i+2];
            
//            char str5[4] = {0};
//            str5[0] = str[i];
//            str5[1] = str[i+1];
//            str5[2] = str[i+2];
            i+=3;
            fen+=1;
//            CCLog("%s",str5);
        } else {
            fen+=0.57;
            str2[i-total] = str[i];
//            CCLog("%c",str2[i-total]);
            i+=1;
        }
        if ((int)(fen)%lineSize == 0 && fen >0.6) {
            //                str2[i] = '\n';
            multi+=1;
            str3.append(str2);
            str3.append("\n");
            total = i;
            fen = 0;
//            CCLog("%s",str2);
            for (int j=0; j<length; j++) {
                str2[j] = 0;
            }
//            CCLog("%s",str2);
//            CCLog("%s",str3.c_str());
        }
    }
//    CCLog("%s",str2);
    str3.append(str2);
//    CCLog("%s",str3.c_str());
    
    free(str2);
    
    return str3;
    
}

bool GXUtil::checkWordandNum(const char* str) {
    int length = strlen(str);
    if (length == 0) {
        return false;
    }
    for (int i=0; i<length; i++) {
        if (isalnum(str[i]) == 0) {
            return false;
        }
    }
    return true;
}


