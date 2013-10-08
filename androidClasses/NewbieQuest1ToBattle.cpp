//
//  NewbieQuest1ToBattle.cpp
//  ww3
//
//  Created by xiao tang on 12-12-14.
//
//

#include "NewbieQuest1ToBattle.h"
#include "GXUtil.h"

bool NewbieQuest1ToBattle::excuteMsg(MyBaseMessage* msg) {
    return false;
}

int NewbieQuest1ToBattle::getCompleteStatus() {
    return questFinishedTag;
}

void NewbieQuest1ToBattle::getPrize() {
    
}

NewbieQuest1ToBattle* NewbieQuest1ToBattle::create() {
    NewbieQuest1ToBattle* quest = new NewbieQuest1ToBattle();
    quest->autorelease();
    quest->setIconName(CCString::create("questBattle.png"));
    return quest;
}

CCLayer* NewbieQuest1ToBattle::getDescLayer()  {
    CCLayer* layer = CCLayer::create();
    CCLabelTTF* descTitle = CCLabelTTF::create("任务简报：","Arial",25);
    descTitle->setAnchorPoint(ccp(0,0.5));
    descTitle->setPosition(ccp(25,360));
    descTitle->setColor(ccc3(255,120,0));
    
    CCLabelTTF* desc = CCLabelTTF::create(GXUtil::insertNewline("　　指挥官，据总部消息，德军暗中建设了一个前哨站。艾森豪威尔司令指示，为了登陆作战的最终胜利，不惜一切代价将它摧毁。总部支援部队已到达，指挥这些部队，进攻！",15).c_str(),"Arial",23,CCSizeZero, kCCTextAlignmentLeft, kCCVerticalTextAlignmentTop);
    desc->setAnchorPoint(ccp(0,1));
    desc->setPosition(ccp(25,340));
    desc->setColor(ccc3(230, 207, 185));
    
    CCLabelTTF* destTitle = CCLabelTTF::create("任务目标：","Arial",25);
    destTitle->setAnchorPoint(ccp(0,1));
    destTitle->setPosition(ccp(25,150));
    destTitle->setColor(ccc3(255,120,0));
    
    CCLabelTTF* dest = CCLabelTTF::create("　　[已完成]　视察基地。","Arial",23);
    dest->setAnchorPoint(ccp(0,1));
    dest->setPosition(ccp(25,115));
    dest->setColor(ccc3(230, 207, 185));
    
    CCSprite* tixing;
    
    tixing = CCSprite::createWithSpriteFrameName("questAppear.png");
    tixing->setScale(0.45);
    tixing->setPosition(ccp(55,101));
    tixing->runAction(CCRepeatForever::create(static_cast<CCSequence*>(CCSequence::create(CCScaleTo::create(1, 0.5), CCScaleTo::create(1,0.45),NULL) )));
    
    
    
    layer->addChild(descTitle);
    layer->addChild(desc);
    layer->addChild(destTitle);
    layer->addChild(dest);
    layer->addChild(tixing);
    
    return layer;
}

//CCLayer* NewbieQuest1ToBattle::getSchedule()  {
//    return CCLayer::create();
//}

CCLayer* NewbieQuest1ToBattle::getPrizeInfo() {
    CCLayer* prizeLayer = CCLayer::create();
    
    GXUtil::loadResourceUtilSucc("bubing1bp.plist","bubing1bp.pvr.ccz");
    GXUtil::loadResourceUtilSucc("M5Stuartbp.plist","M5Stuartbp.pvr.ccz");
    
    CCSprite* bingzhong1 = CCSprite::createWithSpriteFrameName("bubing1bp.png");
    bingzhong1->setPosition(ccp(430,292));
    bingzhong1->setScale(0.25);
    
    CCSprite* sprite1 = CCSprite::createWithSpriteFrameName("questLight.png");
    sprite1->setScale(1.15);
    sprite1->setOpacity(200);
    sprite1->setPosition(ccp(430,292));
    
    CCLabelTTF* bingzhong1Label = CCLabelTTF::create("解锁\n『步枪兵』", "Arial" , 24);
    bingzhong1Label->setPosition(ccp(535,292));
    bingzhong1Label->setColor(ccc3(230, 207, 185));
    bingzhong1Label->setAnchorPoint(ccp(0.5,0.5));
    
    CCSprite* bingzhong2 = CCSprite::createWithSpriteFrameName("M5Stuartbp.png");
    bingzhong2->setPosition(ccp(430,232));
    bingzhong2->setScale(0.25);
    
    CCSprite* sprite2 = CCSprite::createWithSpriteFrameName("questLight.png");
    sprite2->setScale(1.15);
    sprite2->setOpacity(200);
    sprite2->setPosition(ccp(430,232));
    
    CCLabelTTF* bingzhong2Label = CCLabelTTF::create("解锁\n『M5轻型坦克』", "Arial" , 24);
    bingzhong2Label->setPosition(ccp(535,232));
    bingzhong2Label->setColor(ccc3(230, 207, 185));
    bingzhong2Label->setAnchorPoint(ccp(0.5,0.5));
    
    prizeLayer->addChild(sprite1);
    prizeLayer->addChild(sprite2);
    prizeLayer->addChild(bingzhong1);
    prizeLayer->addChild(bingzhong2);
    prizeLayer->addChild(bingzhong1Label);
    prizeLayer->addChild(bingzhong2Label);
    
    
    
    
    return prizeLayer;
}

CCLabelTTF* NewbieQuest1ToBattle::getTitle() {
    return CCLabelTTF::create("进攻德军前哨站","Arial",30);
}
