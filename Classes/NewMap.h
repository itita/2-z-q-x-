//
//  NewMap.h
//  ww2
//
//  Created by DingYu Fu on 12-9-12.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#ifndef ww2_NewMap_h
#define ww2_NewMap_h
#include "GXScrollTMXTileMap.h"
#include "PartService.h"

class NewMap : public GXScrollTMXTileMap {
    
public:
    virtual ~NewMap();
    virtual void addChild(cocos2d::CCNode* child);
    virtual void initMap();
private:
    PartService* partService;
};

#endif
