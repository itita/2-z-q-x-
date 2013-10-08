//
//  GXResourceLoader.h
//  ww4
//
//  Created by xiao tang on 13-4-22.
//
//

#ifndef __ww4__GXResourceLoader__
#define __ww4__GXResourceLoader__

#include <iostream>
#include "cocos2d.h"

using namespace cocos2d;

class GXResourceLoader : public CCObject {
    
public:
    
    CCObject*   m_pSelectorTarget;
    SEL_CallFunc    m_pCallFunc;
    CCArray* fileArray;
    
    ~GXResourceLoader() {
        CC_SAFE_RELEASE_NULL(m_pSelectorTarget);
        CC_SAFE_RELEASE_NULL(fileArray);
        CC_SAFE_RELEASE_NULL(m_pScheduler);
    }
    
    GXResourceLoader():
    m_pSelectorTarget(NULL),
    m_pCallFunc(NULL),
    fileArray(NULL),
    step(0){
        m_pScheduler = CCDirector::sharedDirector()->getScheduler();
        m_pScheduler->retain();
    }
    
    
    static GXResourceLoader* create(CCArray* array,float delay,CCObject* rec,SEL_CallFunc selector);
    
    
private:
    int step;
    void excute();
    CCScheduler* m_pScheduler;
    
};

#endif /* defined(__ww4__GXResourceLoader__) */
