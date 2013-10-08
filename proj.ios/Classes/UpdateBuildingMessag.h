//
//  UpdateBuildingMessag.h
//  ww4
//
//  Created by xiao tang on 13-5-9.
//
//

#ifndef __ww4__UpdateBuildingMessag__
#define __ww4__UpdateBuildingMessag__

#include <iostream>

#include "MyBaseMessage.h"

using namespace cocos2d;

class UpdateBuildingMessag : public MyBaseMessage {
    
public:
    UpdateBuildingMessag() {
        tag = updateBuildingMessageTag;
    }
    ~UpdateBuildingMessag(){
        
    }
    static UpdateBuildingMessag* create(int buildingId,int preLevel,int nextLevelint,int count = 1);
    virtual void sendMsg();
    int buildingId;
    int preLevel;
    int nextLevel;
    int count;
};

#endif /* defined(__ww4__UpdateBuildingMessag__) */
