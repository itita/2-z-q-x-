//
//  BuildingInfo.h
//  ww4
//
//  Created by xiao tang on 13-5-25.
//
//

#ifndef __ww4__BuildingInfo__
#define __ww4__BuildingInfo__

#include "cocos2d.h"

class BuildingInfo :public cocos2d::CCObject {
    
public:
    BuildingInfo():count(0) {};
    static BuildingInfo* create();
    int count;
    
};

#endif /* defined(__ww4__BuildingInfo__) */
