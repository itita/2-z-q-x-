//
//  GXResourceLoader.cpp
//  ww4
//
//  Created by xiao tang on 13-4-22.
//
//

#include "GXResourceLoader.h"
#include "GXUtil.h"

GXResourceLoader* GXResourceLoader::create(CCArray* array,float delay,CCObject* rec,SEL_CallFunc selector) {
    
    GXResourceLoader *pRet = new GXResourceLoader();
    
    if (rec)
    {
        rec->retain();
    }
    
    if (pRet->m_pSelectorTarget)
    {
        pRet->m_pSelectorTarget->release();
    }
    pRet->m_pSelectorTarget = rec;
    
    pRet->m_pCallFunc = selector;
//    pRet->autorelease();
    pRet->fileArray = array;
    CC_SAFE_RETAIN(pRet->fileArray);
    
    pRet->m_pScheduler->scheduleSelector(schedule_selector(GXResourceLoader::excute), pRet, delay, kCCRepeatForever, 0, false);
    
    return pRet;
}


void GXResourceLoader::excute() {
    if (step < fileArray->count()) {
        char str1[50] = {0};
        char str2[50] = {0};
        sprintf(str1,"%s.plist",((CCString*)fileArray->objectAtIndex(step))->getCString());
        sprintf(str2,"%s.pvr.ccz",((CCString*)fileArray->objectAtIndex(step))->getCString());
        GXUtil::loadResourceUtilSucc(str1,str2);
    } else {
        m_pScheduler->unscheduleSelector(schedule_selector(GXResourceLoader::excute), this);
        (m_pSelectorTarget->*m_pCallFunc)();
        this->release();
    }
    step++;
}