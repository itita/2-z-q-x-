//
//  MyBattleBuilding.cpp
//  ww3
//
//  Created by xiao tang on 12-12-3.
//
//

#include "MyBattleBuilding.h"
#include "MyBattleState.h"
#include "MyGameFactory.h"
#include "GXAnimateFX.h"
#include "DefineSet.h"
#include "GXFadeOut.h"
#include "GXFadeOutAndRemoveWhenStop.h"


MyBattleBuilding* MyBattleBuilding::create(int tag,const CCSize& _contentSizebyTiled,GXFSMstate *state) {

    MyBattleBuilding *pRet = new MyBattleBuilding();
    //    pRet->map = NULL;
    if (pRet && pRet->init())
    {
        pRet->autorelease();
        pRet->positionByTiled.x = 9999999;
        //        MyTiledMenuItemSprite* myItem= dynamic_cast<MyTiledMenuItemSprite*>(item);
        //        if(myItem != NULL) {
        //            myItem -> setTag(myTiledMenuItemTag);
        //        }
        pRet->setTag(tag);
        
        
        pRet->contentSizeByTiled =_contentSizebyTiled;
        MyBattleState* myState = dynamic_cast<MyBattleState*>(state);
        CCAssert(myState != NULL, "没办法，不能循环声明，咋整咯？？");
        pRet->fsm = GXFSM::create(state);
        pRet->fsm->retain();
        //        myState->building = pRet;
        myState->init(pRet);
        CCSprite* item = myState->getItem();
        if (item) {
            pRet->addChild(myState->getItem());
        }
        if (myState->doStateTime>=0) {
            pRet->schedule(schedule_selector(MyBattleBuilding::doCurrentState),myState->doStateTime);
        }
        
        return pRet;
    }
    return NULL;
}

CCPoint MyBattleBuilding::getPositionByTiled() {
    positionByTiled = map->transMapToTiled(getPosition());
    return positionByTiled;
}

void MyBattleBuilding::setLevel(int level) {
    
    this->level->setValue(level);
    if (setLevel_selector != NULL) {
        (*setLevel_selector)(level,fsm);
    }
}

void MyBattleBuilding::setPositionByTiled(const cocos2d::CCPoint &pos) {
    if(map != NULL) {
        this->setPosition(map->transTiledToMap(pos));
        this->positionByTiled = pos;
    } else {
        this->positionByTiled = pos;
    }
}

void MyBattleBuilding::displaySummary() {
    if (buildingName->compare("") ==0) {
        return;
    }
    CCNode* exist = getChildByTag(nameFontTag);
    if (exist) {
        return;
    }
    char str[30] = {0};
    CCLabelTTF* name = CCLabelTTF::create(getBuildingName(),"Arial",22);
    name->setColor(ccWHITE);
    name->setPosition(ccp(0,y));
    name->setTag(nameFontTag);
    
    sprintf(str, "等级 %d",getLevel());
    CCLabelTTF* levelFont = CCLabelTTF::create(str,"Arial",18);
    levelFont -> setPosition(ccp(0,y-22));
    levelFont->setColor(ccWHITE);
    levelFont->setTag(levelFontTag);
    
    this->addChild(name,20);
    this->addChild(levelFont,20);
}

//bool MyBattleBuilding::dismissSummary() {
//    bool flag = false;
//    CCNode* name = getChildByTag(nameFontTag);
//    CCNode* level = getChildByTag(levelFontTag);
//    if (name!=NULL) {
//        //        name->setVisible(true);
//        name->stopAllActions();
//        name->runAction(GXFadeOutAndRemoveWhenStop::create(0.15));
//        flag= true;
//    }
//    if (level!=NULL) {
//        level->stopAllActions();
//        level->runAction(GXFadeOutAndRemoveWhenStop::create(0.15));
//        flag = true;
//    }
//    return flag;
//}

void MyBattleBuilding::dispose() {
    MyBattleMap* battleMap = (MyBattleMap*)map;
    if(((BattleScene*)battleMap->getParent())->getFighting() == 1) {
    
        GXAnimateFX* animate = GXAnimateFX::createWithAnitmateFrameNameByFadeout("collapse", 2, false);
        animate->setPosition(this->getPosition());
        map->addChild(animate,999999-this->getPosition().y);
        animate->setAnchorPoint(ccp(0.51,0.361));
    
#if game_version == hard_version 
//        CCLog("%f,%f",contentSizeByTiled.width,contentSizeByTiled.height);
        animate->setScale(((contentSizeByTiled.width+contentSizeByTiled.height)/2)*50/145);
#endif
#if game_version == soft_version
        if (this->contentSizeByTiled.width > 1) {
            animate->setScale(((contentSizeByTiled.width+contentSizeByTiled.height)/2-1)*60/145);
        } else {
            animate->setScale((contentSizeByTiled.width+contentSizeByTiled.height)/2*60/145);
        }
#endif
        //去掉地皮的提示
        float width = this->costRange.width;
        float height = this->costRange.height;
        CCPoint posi = map->transMapToTiled(this->getPosition());
        CCTMXLayer* layer = map->layerNamed("tiled");
        for (int i=(int)(posi.x-width/2+0.5); i<posi.x+width/2+0.5; ++i) {
            for (int j=(int)(posi.y-height/2+0.5); j<posi.y+height/2+0.5; ++j) {
                if (map->checkTiledBound(i, j)) {
                    battleMap->costMap[i][j] -= 5;
                    if ( battleMap->costMap[i][j] <5) {
                       
                        layer->tileAt(ccp(i,j))->setColor(ccc3(255, 255, 255));
                    }
                    
                }
            }
        }
    }
    
    
    ((MyBattleMap*)map)->getItems()->removeObject(this);
    
    
    AliveInterface::dispose();
    changeState(toRuinsTransition);
    //    fsm->stateMap->removeAllObjects();
}

void MyBattleBuilding::changeState(int inputId) {
    CCInteger* out = fsm->stateTransition(inputId);
    MyBattleState* mystate = (MyBattleState*)(fsm->getState(out->getValue()));
    MyBattleState* current = (MyBattleState*)(fsm->getCurrentState());
    this->removeChildByTag(mainTiledSpriteTag,true);
    this->addChild(mystate->getItem(),10);
    current->doEnd();
    mystate->doStart();
    fsm->setCurrentState(mystate);
}

void MyBattleBuilding::changeStateById(int id) {
    if (id != fsm->getCurrentState()->getId() && id != 0 ) {
        MyBattleState* mystate = (MyBattleState*)(fsm->getState(id));
        if (mystate == NULL) {
            return;
        }
        MyBattleState* current = (MyBattleState*)(fsm->getCurrentState());
        this->removeChildByTag(mainTiledSpriteTag,true);
        this->addChild(mystate->getItem(),10);
        current->doEnd();
        if(map != NULL) {
            mystate->doStart();
        }
        fsm->setCurrentState(mystate);
    }
}
void MyBattleBuilding::doCurrentState() {
    //活着的时候才动吧 播死亡动画 复活什么的可以在谈
    
    if (isAlive()) {
        GXFSMstate* state = fsm->getCurrentState();
        if (state!=NULL) {
            state->doState();
        } else {
            CCLog("怪我咯？");
        }
    }
}

int MyBattleBuilding::getLevel() {
    return level->getValue();
}

void MyBattleBuilding::addState(GXFSMstate *state) {
    MyBattleState* mystate = dynamic_cast<MyBattleState*>(state);
    CCAssert(mystate != NULL, "MyBattleState is NULL");

    fsm->addState(state);
    mystate->init(this);
}
