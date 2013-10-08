//
//  HitCheckManager.cpp
//  ww2
//
//  Created by DingYu Fu on 12-9-12.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "HitcheckManager.h"
#include "cocos2d.h"
#include "RectPart.h"



HitcheckManager::HitcheckManager() {
    
}

static HitcheckManager* instance;

HitcheckManager* HitcheckManager::getInstance() {
    if(instance == NULL) {
        instance = new HitcheckManager();
    } 
    return instance;
}

void HitcheckManager::release() {
    CC_SAFE_RELEASE_NULL(instance);
    instance = NULL;
}

bool HitcheckManager::hitCheck(PartInterface *part1, PartInterface *part2) {
    RectPart* rect1 = dynamic_cast<RectPart*>(part1);
    RectPart* rect2 = dynamic_cast<RectPart*>(part2);
    
    if(rect1 && rect2) {
//        float dx =
//                if(dx< (testItem->contentSizeByTiled.width + temp->contentSizeByTiled.width)/2 && dy<(testItem->contentSizeByTiled.height+ temp->contentSizeByTiled.height)/2
//                   ) {
//                    isCollision = true;
//                    //                CCLog("tiled1X:%f,tiled1Y:%f,tiled2X:%f,tiled2Y%f",tiled1.x,tiled1.y,tiled2.x,tiled2.y);
//                    return true;
//                }

    }
    return false;
}



