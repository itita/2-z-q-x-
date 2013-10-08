//
//  MyCombineBuilding.cpp
//  ww4
//
//  Created by xiao tang on 13-4-3.
//
//

#include "MyCombineBuilding.h"
#include "MyState.h"

MyCombineBuilding* MyCombineBuilding::create(int tag,const CCSize& _contentSizebyTiled,GXFSMstate* state,int _level,int _maxLevel) {
    
    MyCombineBuilding *pRet = new MyCombineBuilding();
    //    pRet->map = NULL;
    if (pRet && pRet->initWithTarget(pRet, menu_selector(MyBuilding::runTouchAction)))
    {
        pRet->autorelease();
        pRet->positionByTiled.x = 9999999;
        //        MyTiledMenuItemSprite* myItem= dynamic_cast<MyTiledMenuItemSprite*>(item);
        //        if(myItem != NULL) {
        //            myItem -> setTag(myTiledMenuItemTag);
        //        }
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
        
        pRet->setLevel(_level);
        return pRet;
    }
    CC_SAFE_DELETE(pRet);
    return NULL;
}


//const CCPoint& MyCombineBuilding::getZorderPosition() {
////    return ccp(getPosition().x,getPosition().y-1);
//    return getPosition();
//}
