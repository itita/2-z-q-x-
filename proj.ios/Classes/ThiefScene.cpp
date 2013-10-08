//
//  ThiefScene.cpp
//  ww4
//
//  Created by xiao tang on 13-3-5.
//
//

#include "ThiefScene.h"
#include "TransitonScene.h"
#include "DefineSet.h"
#include "GXUtil.h"

ThiefScene* ThiefScene::create() {
    ThiefScene *pRet = new ThiefScene();
    pRet->loadResource();
    pRet->myInit();
    pRet->autorelease();
    return pRet;
}

void ThiefScene::loadResource() {
    GXUtil::loadResourceUtilSucc("bugei.plist","bugei.pvr.ccz");
    GXUtil::loadResourceUtilSucc("bubeiBack.plist","bubeiBack.pvr.ccz");
}

void ThiefScene::releaseResource() {
    CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile("bugei.plist");
    CCTextureCache::sharedTextureCache()->removeTextureForKey("bugei.pvr.ccz");
    CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile("bubeiBack.plist");
    CCTextureCache::sharedTextureCache()->removeTextureForKey("bubeiBack.pvr.ccz");
}

void ThiefScene::myInit() {
    CCLayer* backLayer = CCLayer::create();
    backLayer->setPosition(ccp(0,0));
    CCMenuItemSprite* item = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("startBugeiButton.png"),CCSprite::createWithSpriteFrameName("startBugeiButtonP.png"),this,menu_selector(ThiefScene::returnStart));
    CCMenu* menu = CCMenu::create(item,NULL);
    menu->setPosition(ccp(480,320));
    CCSprite* sprite = CCSprite::createWithSpriteFrameName("bubeiBack.png");
    sprite->setPosition(ccp(480,320));
    backLayer->addChild(sprite);
    backLayer->addChild(menu);
   
    this->addChild(backLayer);
}

void ThiefScene::returnStart() {
    CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.2, TransitonScene::create(startSceneTag), ccBLACK));
}
