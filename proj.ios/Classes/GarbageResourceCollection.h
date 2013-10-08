//
//  GarbageResourceCollection.h
//  ww4
//
//  Created by xiao tang on 13-9-13.
//
//

#ifndef __ww4__GarbageResourceCollection__
#define __ww4__GarbageResourceCollection__

#include "cocos2d.h"

using namespace cocos2d;

class GarbageResourceCollection  {
    
public:
    GarbageResourceCollection():
    garbageResourceMap(NULL){
    
    }
    static GarbageResourceCollection* getInstance();
    void addGarbage(const std::string& key,CCString* recString);
    void GarbageCollection();
private:
    CCDictionary* garbageResourceMap;
};
#endif /* defined(__ww4__GarbageResourceCollection__) */
