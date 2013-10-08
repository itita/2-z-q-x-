//
//  MyTiledInfo.h
//  ww3
//
//  Created by xiao tang on 12-12-3.
//
//

#ifndef ww3_MyTiledInfo_h
#define ww3_MyTiledInfo_h
#include "cocos2d.h"
#include "GXScrollTMXTileMap.h"

using namespace cocos2d;

class MyTiledInfo {
    
public:
    MyTiledInfo():
    positionByTiled(ccp(9999999,0)),
    map(NULL),
    pid(-1)
    {};
    
    CCPoint positionByTiled;
    CCSize contentSizeByTiled;
    GXScrollTMXTileMap* map;
    
    virtual CCPoint getPositionByTiled();
    virtual void setPositionByTiled(const cocos2d::CCPoint &pos);
    virtual void setMap(GXScrollTMXTileMap *_map);
    int pid;
};

#endif
