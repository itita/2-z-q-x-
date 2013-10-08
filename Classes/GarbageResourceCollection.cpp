//
//  GarbageResourceCollection.cpp
//  ww4
//
//  Created by xiao tang on 13-9-13.
//
//

#include "GarbageResourceCollection.h"

static GarbageResourceCollection* instance = NULL;

GarbageResourceCollection* GarbageResourceCollection::getInstance() {
    if (instance == NULL) {
        instance = new GarbageResourceCollection();
        instance->garbageResourceMap = CCDictionary::create();
        instance->garbageResourceMap->retain();
    }
    return instance;
}

void GarbageResourceCollection::addGarbage(const std::string& key,CCString* recString){
    if (garbageResourceMap->objectForKey(key)==NULL) {
        garbageResourceMap->setObject(recString,key);
    }
}

void GarbageResourceCollection::GarbageCollection() {
    CCArray* array = garbageResourceMap->allKeys();
    CCObject* obj;
    CCARRAY_FOREACH(array,obj){
        CCString* key = (CCString*)obj;
//        CCLog("key:%s",key->getCString());
        CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile(key->getCString());
        CCTextureCache::sharedTextureCache()->removeTextureForKey(((CCString*)garbageResourceMap->objectForKey(key->m_sString))->getCString());
    }
    garbageResourceMap->removeAllObjects();
}