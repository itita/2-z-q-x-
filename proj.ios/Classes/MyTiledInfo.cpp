//
//  MyTiledInfo.cpp
//  ww3
//
//  Created by xiao tang on 12-12-3.
//
//

#include "MyTiledInfo.h"


CCPoint MyTiledInfo::getPositionByTiled() {
//    positionByTiled = map->transMapToTiled(getPosition());
    return positionByTiled;
}

void MyTiledInfo::setPositionByTiled(const cocos2d::CCPoint &pos) {
    if(map != NULL) {
//        this->setPosition(map->transTiledToMap(pos));
        this->positionByTiled = pos;
    } else {
        this->positionByTiled = pos;
    }
}

void MyTiledInfo::setMap(GXScrollTMXTileMap *_map) {
    map = _map;
    //    tiledSize = transTiledSizeInRetina(map->layerNamed("tiled")->getMapTileSize());
    //    setContentSizeByTiled(this->getContentSize());
}