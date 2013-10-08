//
//  MyContinueBuilding.cpp
//  ww3
//
//  Created by xiao tang on 12-12-7.
//
//

#include "MyContinueBuilding.h"
#include "MyContinueTiledSprite.h"
#include "MyState.h"


MyContinueBuilding* MyContinueBuilding::create(int tag,const CCSize& _contentSizebyTiled,GXFSMstate *state,int level,int _maxLevel) {
    
    MyContinueBuilding *pRet = new MyContinueBuilding();
    if (pRet && pRet->initWithTarget(pRet, menu_selector(MyBuilding::runTouchAction)))
    {
        pRet->autorelease();
        pRet->positionByTiled.x = 9999999;
        pRet->setTag(tag);
        
        
        pRet->contentSizeByTiled =_contentSizebyTiled;
        MyState* myState = dynamic_cast<MyState*>(state);
        CCAssert(myState != NULL, "没办法，不能循环声明，咋整咯？？");
        pRet->fsm = GXFSM::create(state);
        pRet->fsm->retain();
        //        myState->building = pRet;
        myState->init(pRet);
        pRet->setNormalImage(myState->getItem());
        pRet->setMaxLevel(_maxLevel);
        
        pRet->setLevel(level);
        return pRet;
    }
    CC_SAFE_DELETE(pRet);
    return NULL;
}

void MyContinueBuilding::selected() {
    MyBuilding::selected();
    MyContinueTiledSprite* tiledSprite = dynamic_cast<MyContinueTiledSprite*>(getNormalImage());
    if(getActive() && tiledSprite) {
        ((MyContinueTiledSprite*)getNormalImage())->updateLoc(0);
        tiledSprite->lu = 0;
        tiledSprite->ld = 0;
        tiledSprite->ru = 0;
        tiledSprite->rd = 0;
    }
}
void MyContinueBuilding::unselected() {
    MyBuilding::unselected();
    if(dynamic_cast<MyContinueTiledSprite*>(getNormalImage())) {
        ((MyContinueTiledSprite*)getNormalImage())->updateLoc(1);
    }
}