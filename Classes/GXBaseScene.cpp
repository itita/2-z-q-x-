//
//  GXBaseScene.cpp
//  ww2
//
//  Created by xiao tang on 12-10-4.
//
//

#include "GXBaseScene.h"



//GXBaseScene::~GXBaseScene() {
//    releaseResource();
//}

void GXBaseScene::doPause() {

}

void GXBaseScene::doResume() {
    
}


void GXBaseScene::onEnterTransitionDidFinish() {
    CCScene::onEnterTransitionDidFinish();
    isEnter = true;
}
//void GXBaseScene::onEnter() {
//    CCScene::onEnter();
//    loadResource();
//}

//void GXBaseScene::onExit() {
//    CCScene::onExit();
//    releaseResource();
//}

//void GXBaseScene::loadResource() {
//    CCLog("chedan");
//}
//
//void GXBaseScene::releaseResource() {
//
//}