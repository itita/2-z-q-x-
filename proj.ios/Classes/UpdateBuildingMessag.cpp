//
//  UpdateBuildingMessag.cpp
//  ww4
//
//  Created by xiao tang on 13-5-9.
//
//

#include "UpdateBuildingMessag.h"
#include "MyMessageManage.h"

UpdateBuildingMessag* UpdateBuildingMessag::create(int _buildingId,int _preLevel,int _nextLevel,int _count) {
    UpdateBuildingMessag* msg = new UpdateBuildingMessag();
    msg->buildingId = _buildingId;
    msg->preLevel = _preLevel;
    msg->nextLevel = _nextLevel;
    msg->count = _count;
    msg->autorelease();
    return msg;
}

void UpdateBuildingMessag::sendMsg() {
    MyMessageManage::getInstance()->msgList->addObject(this);
}