//
//  TestScene.cpp
//  ww4
//
//  Created by xiao tang on 13-1-22.
//
//

#include "TestScene.h"
#include "TransitonScene.h"
#include "MyGameFactory.h"
#include "MyUtil.h"
#include "Mathlib.h"
#include "GXShieldTouchMenuItem.h"
#include "MyMenuItem.h"
#include "MyPriorityMenu.h"
#include "GXScrollView.h"
#include "MyGameInfo.h"
#include "SimpleAudioEngine.h"
#include "GXRemoveFromParentsAction.h"
#include "MyHttpConnection.h"

#define deployLayerTag 20
#define deployMenuTag 21
#define cardGrayTag 22
#define battleButtonTag 23
#define searchLayerTag 24
#define searchListLayerTag 25

TestScene* TestScene::create(cocos2d::CCArray *beanArray) {
    TestScene *pRet = new TestScene();
    for (int i = 0; i<5; i++) {
        pRet->flag[i] = 0;
    }
//    pRet->baseInfoBeanArray = beanArray;
//    pRet->baseInfoBeanArray->retain();
    pRet->myArmyList = CCArray::create();
    pRet->myArmyList->retain();
    pRet->init(beanArray);
    pRet->autorelease();
    return pRet;
    
//    CC_SAFE_DELETE(pRet);
//    return NULL;
}


bool TestScene::init(CCArray* baseInfoBeanArray) {
    loadResource();
    CCLayer* backLayer = CCLayer::create();
    backLayer->setPosition(ccp(0,0));
    
    CCSprite* back = CCSprite::createWithSpriteFrameName("area1.jpg");
    back->setPosition(ccp(winSize.width/2,winSize.height/2));
    backLayer->addChild(back);
    this->addChild(backLayer);
    
    //    bean
    CCMenu* menu =CCMenu::create();
    char str[15] = {0};
    if (0<baseInfoBeanArray->count()) {
        BaseInfoBean* bean = (BaseInfoBean*)baseInfoBeanArray->objectAtIndex(0);
        int level = MyUtil::getInstance()->getLevelByExperience(bean->experience);
        sprintf(str, "baseIcon%d.png",1+Mathlib::boundInt(level/5, 4, 0));
        
        CCSprite* baseIcon1Sprite = CCSprite::createWithSpriteFrameName(str);
        baseIcon1Sprite->setColor(ccGRAY);
        CCMenuItemSprite* baseIcon1 = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName(str),baseIcon1Sprite,this,menu_selector(TestScene::toDeployArmy));
        baseIcon1->setUserObject(bean);
        baseIcon1->setPosition(ccp(winSize.width/2-200,270));
        CCMenuItemSprite* baseui1 = getBaseInfoItem(bean);
        baseui1->setPosition(ccp(winSize.width/2-200,375));
        menu->addChild(baseIcon1);
        menu->addChild(baseui1);
    }
    
    
    // -------2---------
    
    if (1<baseInfoBeanArray->count()) {
        BaseInfoBean* bean = (BaseInfoBean*)baseInfoBeanArray->objectAtIndex(1);
        int level = MyUtil::getInstance()->getLevelByExperience(bean->experience);
        sprintf(str, "baseIcon%d.png",1+Mathlib::boundInt(level/5, 4, 0));
        CCSprite* baseIcon2Sprite = CCSprite::createWithSpriteFrameName(str);
        baseIcon2Sprite->setColor(ccGRAY);
        CCMenuItemSprite* baseIcon2 = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName(str),baseIcon2Sprite,this,menu_selector(TestScene::toDeployArmy));
        baseIcon2->setUserObject(bean);
        baseIcon2->setPosition(ccp(winSize.width/2-80,76));
        CCMenuItemSprite* baseui2 = getBaseInfoItem(bean);
        baseui2->setPosition(ccp(winSize.width/2-75,181));
        menu->addChild(baseIcon2);
        menu->addChild(baseui2);
    }
    
    
    //--------3-------
    if (2<baseInfoBeanArray->count()) {
        BaseInfoBean* bean = (BaseInfoBean*)baseInfoBeanArray->objectAtIndex(2);
        int level = MyUtil::getInstance()->getLevelByExperience(bean->experience);
        sprintf(str, "baseIcon%d.png",1+Mathlib::boundInt(level/5, 4, 0));
        CCSprite* baseIcon3Sprite = CCSprite::createWithSpriteFrameName(str);
        baseIcon3Sprite->setColor(ccGRAY);
        CCMenuItemSprite* baseIcon3 = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName(str),baseIcon3Sprite,this,menu_selector(TestScene::toDeployArmy));
        baseIcon3->setUserObject(bean);
        baseIcon3->setPosition(ccp(winSize.width/2+270,20));
        CCMenuItemSprite* baseui3 = getBaseInfoItem(bean);
        baseui3->setPosition(ccp(winSize.width/2+270,125));
        menu->addChild(baseIcon3);
        menu->addChild(baseui3);
    }
    
    
    //--------4-------
    if (3<baseInfoBeanArray->count()) {
        BaseInfoBean* bean = (BaseInfoBean*)baseInfoBeanArray->objectAtIndex(3);
        int level = MyUtil::getInstance()->getLevelByExperience(bean->experience);
        sprintf(str, "baseIcon%d.png",1+Mathlib::boundInt(level/5, 4, 0));
        CCSprite* baseIcon4Sprite = CCSprite::createWithSpriteFrameName(str);
        baseIcon4Sprite->setColor(ccGRAY);
        CCMenuItemSprite* baseIcon4 = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName(str),baseIcon4Sprite,this,menu_selector(TestScene::toDeployArmy));
        baseIcon4->setUserObject(bean);
        baseIcon4->setPosition(ccp(winSize.width/2+300,489));
        CCMenuItemSprite* baseui4 = getBaseInfoItem(bean);
        baseui4->setPosition(ccp(winSize.width/2+181,560));
        menu->addChild(baseIcon4);
        menu->addChild(baseui4);
    }
    
    
    //---------5----------
    if (4<baseInfoBeanArray->count()) {
        BaseInfoBean* bean = (BaseInfoBean*)baseInfoBeanArray->objectAtIndex(4);
        int level = MyUtil::getInstance()->getLevelByExperience(bean->experience);
        sprintf(str, "baseIcon%d.png",1+Mathlib::boundInt(level/5, 4, 0));
        CCSprite* baseIcon5Sprite = CCSprite::createWithSpriteFrameName(str);
        baseIcon5Sprite->setColor(ccGRAY);
        CCMenuItemSprite* baseIcon5 = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName(str),baseIcon5Sprite,this,menu_selector(TestScene::toDeployArmy));
        baseIcon5->setUserObject(bean);
        baseIcon5->setPosition(ccp(winSize.width/2+420,326));
        CCMenuItemSprite* baseui5 = getBaseInfoItem(bean);
        baseui5->setPosition(ccp(winSize.width/2+275,380));
        menu->addChild(baseIcon5);
        menu->addChild(baseui5);
    }
    
    CCSprite* next = CCSprite::createWithSpriteFrameName("next.png");
    CCSprite* gynext = CCSprite::createWithSpriteFrameName("next.png");
    gynext->setColor(ccGRAY);
    
    CCMenuItemSprite* nextItem = CCMenuItemSprite::create(next, gynext, this, menu_selector(TestScene::toNextCallBack));
    nextItem->setPosition(ccp(winSize.width - 100,winSize.height/3));
    
    CCSprite* surrender = CCSprite::createWithSpriteFrameName("backToBuild.png");
    CCSprite* gysurrender = CCSprite::createWithSpriteFrameName("backToBuild.png");
    gysurrender->setColor(ccGRAY);
    
    CCMenuItemSprite* homeItem = CCMenuItemSprite::create(surrender, gysurrender, this, menu_selector(TestScene::toHomeCallBack));
    homeItem->setPosition(ccp(100,winSize.height/3));
    
    CCSprite*  searchEnemyByLocationSpriteGray =  CCSprite::createWithSpriteFrameName("searchEnemyByLocation.png");
    searchEnemyByLocationSpriteGray->setColor(ccGRAY);
    
//    CCMenuItemSprite* searchEnemyByLocationButton = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("searchEnemyByLocation.png"),searchEnemyByLocationSpriteGray);
//    searchEnemyByLocationButton->setPosition(ccp(110,500));
    
    
    CCSprite*  searchEnemyByNicknameSpriteGray =  CCSprite::createWithSpriteFrameName("searchEnemyByNickname.png");
    searchEnemyByNicknameSpriteGray->setColor(ccGRAY);
    
    CCMenuItemSprite* searchEnemyByNicknameButton = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("searchEnemyByNickname.png"),searchEnemyByNicknameSpriteGray,this,menu_selector(TestScene::toSearchNickname));
    searchEnemyByNicknameButton->setPosition(ccp(110,500));
    
    CCMenu* uiMenu = CCMenu::create(nextItem,homeItem,searchEnemyByNicknameButton,NULL);
    uiMenu->setPosition(ccp(0,0));
    
    menu->setPosition(ccp(0,0));
    backLayer->addChild(menu);
    
//    for(int i=0;i<10;i++) {
//        MyGameInfo::getInstance()->creatorArray->addObject(CCString::create("tank.j"));
//    }
    initCloud();
    backLayer->addChild(uiMenu,5);
    return true;
}

void TestScene::initCloud() {
    CCLayer* cloudLayer = CCLayer::create();
    CCSprite* cloud1 = CCSprite::createWithSpriteFrameName("cloud1.png");
    cloud1->setPosition(ccp(arc4random()%960,arc4random()%640));
    cloud1->setRotation(arc4random()%360);
    cloud1->setOpacity(arc4random()%100+155);
    cloud1->setScale(((float)(arc4random()%70))/100 +0.3);
    float distanceX =  -cloud1->getContentSize().width/2 - cloud1->getPositionX();
    int speed = arc4random()%40+10;
    //    CCLog("%f",distanceX);
    cloud1->runAction(CCSequence::create(CCMoveBy::create(-(distanceX/speed),ccp(distanceX,0)),CCCallFuncND::create(this, callfuncND_selector(TestScene::cloudCallBack), (void*)cloud1),NULL));
    
    CCSprite* cloud2 = CCSprite::createWithSpriteFrameName("cloud2.png");
    cloud2->setPosition(ccp(arc4random()%960,arc4random()%640));
    cloud2->setRotation(arc4random()%360);
    cloud2->setOpacity(arc4random()%100+155);
    cloud2->setScale((((float)(arc4random()%70))/100 +0.3)*2);
    distanceX =  -cloud2->getContentSize().width - cloud2->getPositionX();
    //    CCLog("%f",distanceX);
    speed = arc4random()%40+10;
    cloud2->runAction(CCSequence::create(CCMoveBy::create(-(distanceX/speed),ccp(distanceX,0)),CCCallFuncND::create(this, callfuncND_selector(TestScene::cloudCallBack), (void*)cloud2),NULL));
    
    CCSprite* cloud3 = CCSprite::createWithSpriteFrameName("cloud3.png");
    cloud3->setPosition(ccp(arc4random()%960,arc4random()%640));
    cloud3->setRotation(arc4random()%360);
    cloud3->setOpacity(arc4random()%100+155);
    cloud3->setScale((((float)(arc4random()%70))/100 +0.3)*2);
    distanceX =  -cloud3->getContentSize().width - cloud3->getPositionX();
    //    CCLog("%f",distanceX);
    speed = arc4random()%40+10;
    cloud3->runAction(CCSequence::create(CCMoveBy::create(-(distanceX/speed),ccp(distanceX,0)),CCCallFuncND::create(this, callfuncND_selector(TestScene::cloudCallBack), (void*)cloud3),NULL));
    
    cloudLayer->addChild(cloud1);
    cloudLayer->addChild(cloud2);
    cloudLayer->addChild(cloud3);
    
    this->addChild(cloudLayer);
}

void TestScene::cloudCallBack(CCNode* pSender,CCSprite* cloud) {
    cloud->setScale((((float)(arc4random()%70))/100 +0.3)*2);
    float posiX= 960+cloud->getContentSize().width;
    cloud->setPosition(ccp(posiX,arc4random()%640));
    cloud->setRotation(arc4random()%360);
    cloud->setOpacity(arc4random()%100+155);
    
    float distanceX =  -cloud->getContentSize().width - cloud->getPositionX();
    //    CCLog("%f",distanceX);
    int speed = arc4random()%40+10;
    cloud->runAction(CCSequence::create(CCMoveBy::create(-(distanceX/speed),ccp(distanceX,0)),CCCallFuncND::create(this, callfuncND_selector(TestScene::cloudCallBack), (void*)cloud),NULL));
}

void TestScene::toHomeCallBack(CCNode* pSender) {
    CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.2, TransitonScene::create(startSceneTag), ccBLACK));
}

void TestScene::toNextCallBack() {
    CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.2, TransitonScene::create(ReadyToBattleTag),ccBLACK));
}


void TestScene::loadResource() {
    GXUtil::loadResourceUtilSucc("baseIcon.plist","baseIcon.pvr.ccz");
    GXUtil::loadResourceUtilSucc("battleui.plist","battleui.pvr.ccz");
    GXUtil::loadResourceUtilSucc("deployui.plist","deployui.pvr.ccz");
    GXUtil::loadResourceUtilSucc("cloud.plist","cloud.pvr.ccz");
    GXUtil::loadResourceUtilSucc("area1.plist","area1.pvr.ccz");
//    CCTextureCache::sharedTextureCache()->dumpCachedTextureInfo();
}

void TestScene::releaseResource() {
    CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile("battleui.plist");
    CCTextureCache::sharedTextureCache()->removeTextureForKey("battleui.pvr.ccz");
    CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile("baseIcon.plist");
    CCTextureCache::sharedTextureCache()->removeTextureForKey("baseIcon.pvr.ccz");
    
    CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile("deployui.plist");
    CCTextureCache::sharedTextureCache()->removeTextureForKey("deployui.pvr.ccz");
    
    
    CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile("area1.plist");
    CCTextureCache::sharedTextureCache()->removeTextureForKey("area1.pvr.ccz");
    
    CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile("cloud.plist");
    CCTextureCache::sharedTextureCache()->removeTextureForKey("cloud.pvr.ccz");
    
    GarbageResourceCollection::getInstance()->GarbageCollection();
}

CCMenuItemSprite* TestScene::getBaseInfoItem(BaseInfoBean* bean) {
    CCSprite* baseui1Sprite = CCSprite::create("baseui.png");
    baseui1Sprite->setColor(ccGRAY);
    CCMenuItemSprite* baseui1 = CCMenuItemSprite::create(CCSprite::create("baseui.png"), baseui1Sprite,this,menu_selector(TestScene::toDeployArmy));
    //    CCMenuItemSprite*
    baseui1->setUserObject(bean);
    
    CCSprite* rank1 =  MyUtil::getInstance()->getRankSprite(bean->honor);
    rank1->setAnchorPoint(ccp(0.5,0.5));
    rank1->setPosition(ccp(20,25));
    rank1->setScale(0.4);
    baseui1->addChild(rank1);
    
    CCLabelTTF* rankname = CCLabelTTF::create(MyUtil::getInstance()->getRankString(bean->honor), "Arial", 16);
    rankname->setAnchorPoint(ccp(0.5,0.5));
    rankname->setPosition(ccp(50,25));
    rankname->setColor(ccc3(246, 255, 0));
    baseui1->addChild(rankname);
    
    char str[50] = {0};
    sprintf(str, "%d",MyUtil::getInstance()->getLevelByExperience(bean->experience));
    CCLabelAtlas* level1 = CCLabelAtlas::create(str, "levelupnumber.png", 40, 32, '0');
    level1->setAnchorPoint(ccp(0.5,0.5));
    level1->setPosition(ccp(50,44));
    level1->setScale(0.4);
    baseui1->addChild(level1);
    
    if (bean->getUnionName()->compare("") == 0) {
        CCLabelTTF* name = CCLabelTTF::create(
                                              bean->getNickname()->getCString(), "Arial", 17);
        name->setAnchorPoint(ccp(0.5,0.5));
        name->setPosition(ccp(120,88));
        name->setColor(ccBLACK);
        baseui1->addChild(name);
    } else {
    
        CCLabelTTF* name = CCLabelTTF::create(bean->getNickname()->getCString(), "Arial", 17);
        name->setAnchorPoint(ccp(0.5,0.5));
        name->setPosition(ccp(120,95));
        name->setColor(ccBLACK);
        baseui1->addChild(name);
        
        sprintf(str, "[%s]",bean->getUnionName()->getCString());
        CCLabelTTF* unionName = CCLabelTTF::create(str, "Arial", 14);
        unionName->setAnchorPoint(ccp(0.5,0.5));
        unionName->setPosition(ccp(120,80));
        unionName->setOpacity(180);
        baseui1->addChild(unionName);
    }

    int  level = MyUtil::getInstance()->getLevelByExperience(bean->experience);
//    float quan =  (Mathlib::bound(bean->nowTime - bean->time, 36000000, 0)/1000*ytBaseColletSpeed*level+bean->oil+bean->iron)*0.2*bean->trophyRate;
    float quan =  (Mathlib::bound(bean->nowTime - bean->time, 36000000, 0)/1000*MyUtil::getInstance()->updateLevelByRate(0,ytBaseColletSpeed,level,ytUpdateColletSpeedRate)+Mathlib::max(bean->oil+bean->iron,1000*level*level))*Mathlib::bound(MyGameInfo::getInstance()->enemyPower/MyGameInfo::getInstance()->getPower(),0.4,0)*bean->trophyRate;
    if (quan < 1000) {
        sprintf(str, "极少");
    } else if(quan<2000) {
        sprintf(str, "很少");
    } else if (quan<5000) {
        sprintf(str, "少");
    } else if (quan <10000) {
        sprintf(str, "略少");
    } else if (quan < 20000) {
        sprintf(str, "一般");
    } else if (quan < 50000) {
        sprintf(str, "略多");
    } else if (quan < 100000) {
        sprintf(str, "多");
    } else if (quan < 200000) {
        sprintf(str, "很多");
    } else {
        sprintf(str, "极多");
    }
    
    CCLabelTTF* resourceCount = CCLabelTTF::create(str, "Arial", 20);
    resourceCount->setAnchorPoint(ccp(0.5,0.5));
    resourceCount->setPosition(ccp(138,56));
    resourceCount->setColor(ccc3(246, 255, 0));
    baseui1->addChild(resourceCount);
    
    CCLabelTTF* defenSucc = CCLabelTTF::create(bean->getDefenSuccRate()->getCString(), "Arial", 20);
    defenSucc->setAnchorPoint(ccp(0.5,0.5));
    defenSucc->setPosition(ccp(138,31));
    defenSucc->setColor(ccc3(246, 255, 0));
    baseui1->addChild(defenSucc);
    return baseui1;
}


void TestScene::toDeployArmy(CCNode* pSender) {
    
    CCLayer* deployLayer = CCLayer::create();
    CCSprite* deployBack = CCSprite::createWithSpriteFrameName("deployback.png");
    deployLayer->setPosition(ccp(winSize.width+deployBack->getContentSize().width,0));
    deployLayer->setTag(deployLayerTag);
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sfx_popCreator.mp3");
    
    
    deployBack->setPosition(ccp(winSize.width,winSize.height/2));
    deployBack->setAnchorPoint(ccp(1,0.5));
    
    deployLayer->addChild(deployBack);
    deployLayer->runAction(CCEaseElasticOut::create(CCMoveTo::create(0.4, ccp(0,0)),1));
    
    GXShieldTouchMenuItem* shieldTouch= GXShieldTouchMenuItem::create();
    shieldTouch->setPosition(ccp(winSize.width/2,winSize.height/2));
    shieldTouch->setContentSize(winSize);
    
    CCMenuItemSprite* quitItem = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("quitdeploy.png"), CCSprite::createWithSpriteFrameName("quitdeployp.png"),this,menu_selector( TestScene::quitDeployCallBack));
    
    quitItem->setPosition(ccp(winSize.width-24,winSize.height-24));
    
    
    MyPriorityMenu* menu = MyPriorityMenu::create(-506, quitItem,shieldTouch,NULL);
    menu->setPosition(ccp(0,0));
    menu->setTag(deployMenuTag);
    
    deployLayer->addChild(menu,2);
    
    
    GXScrollView* scroll = GXScrollView::create(-507);
    //    CCSprite* test = CCSprite::create("loading.jpg");
    //    test->setAnchorPoint(ccp(0,0));
    //    scroll->addChild(test);
    scroll->setOriPosition(ccp(winSize.width-768,45));
    scroll->setContentSize(CCSizeMake(548, 350));
    CCArray* array = MyGameInfo::getInstance()->creatorArray;
    CCObject* obj;
    char str[30] = {0};
    int i=0;
    if (array->count() > 6) {
        scroll->setMapSize(CCSizeMake(548, 180*(array->count()/3+1)-10));
        scroll->setPosition(ccp(scroll->getOriPosition().x,-scroll->getMapSize().height+scroll->getViewSize().height+scroll->getOriPosition().y));
    }
    
    deployLayer->addChild(scroll);
    CCARRAY_FOREACH(array, obj) {
        CreatorInfoBean* bean = (CreatorInfoBean*)obj;
        MyMenuItem* cardBack = MyMenuItem::create(CCSprite::createWithSpriteFrameName("deployCardBack.png"), this, menu_selector(TestScene::selectCard)) ;
        
        sprintf(str, "%sbp.png",bean->creator->getSpriteFileName());
        CCSprite* bp = CCSprite::createWithSpriteFrameName(str);
        if (bp == NULL) {
            break;
        }
        sprintf(str, "deployBack%d.png",(bean->creator->getRarity()));
        CCSprite* sprite = CCSprite::createWithSpriteFrameName(str);
        bp->setPosition(ccp(53,49));
        bp->setScale(Mathlib::min(115/bp->getContentSize().width, 90/bp->getContentSize().height));
        sprite->addChild(bp);
        sprite->setPosition(ccp(cardBack->getContentSize().width/2,cardBack->getContentSize().height-cardBack->getContentSize().width/2+5));
        sprite->setScale(1.1);
//        CCSprite* mIcon = CCSprite::createWithSpriteFrameName("militaryIcon.png");
//        mIcon->setPosition(ccp(50,35));
//        mIcon->setScale(0.4);
        
        sprintf(str, "Lv:%d",(bean->getLevel()));
        CCLabelTTF* lvfont = CCLabelTTF::create(str, "Arial", 25);
        lvfont->setAnchorPoint(ccp(0,0));
        lvfont->setPosition(ccp(10,5));;
        
        cardBack->addChild(sprite);
//        cardBack->addChild(mIcon);
        sprite->addChild(lvfont);
        cardBack->setUserData(obj);
        
        float posi = (bean->creator->getRarity()-1)*23;
        for (int j = 0; j<bean->creator->getRarity(); j++) {
            CCSprite* star = CCSprite::createWithSpriteFrameName("armystar.png");
            star->setPosition(ccp(cardBack->getContentSize().width/2-posi/2 + j*23,13));
            star->setScale(0.75);
            cardBack->addChild(star);
        }
        if (i<5) {
            cardBack->setEnabled(false);
            CCSprite* gray = CCSprite::createWithSpriteFrameName("dialoggray.png");
            gray->setScaleX(cardBack->getImage()->getContentSize().width/gray->getContentSize().width);
            gray->setScaleY(cardBack->getImage()->getContentSize().height/gray->getContentSize().height);
            gray->setAnchorPoint(ccp(0,0));
            gray->setTag(cardGrayTag);
            cardBack->addChild(gray);
            
            sprintf(str, "deployBack%d.png",(bean->creator->getRarity()));
            CCSprite* sprite = CCSprite::createWithSpriteFrameName(str);
            sprintf(str, "%sbp.png",bean->creator->getSpriteFileName());
            CCSprite* bp = CCSprite::createWithSpriteFrameName(str);
            bp->setPosition(ccp(53,49));
            bp->setScale(Mathlib::min(115/bp->getContentSize().width, 90/bp->getContentSize().height));
            sprite->addChild(bp);
            sprintf(str, "Lv:%d",(bean->getLevel()));
            CCLabelTTF* lvfont = CCLabelTTF::create(str, "Arial", 25);
            lvfont->setAnchorPoint(ccp(0,0));
            lvfont->setPosition(ccp(10,5));;
            sprite->addChild(lvfont);
            MyMenuItem* bpItem = MyMenuItem::create(sprite, this, menu_selector(TestScene::cancelCard));
            
            menu->addChild(bpItem);
            bpItem->setScale(1.15);
            flag[i] = 1;
            bpItem->setPosition(ccp(winSize.width-720+i*118,522));
            
            bpItem->setUserData(cardBack);
            myArmyList->addObject(obj);
        }
        
        
        
        cardBack->setPosition(ccp(100 + (i%3)*180,scroll->getMapSize().height-85-(i/3)*180));
        scroll->addChild(cardBack);
        i++;
    }
    
    CCSprite* sprite = CCSprite::createWithSpriteFrameName("startfight.png");
    sprite->setColor(ccGRAY);
    
    CCMenuItemSprite* toBattle = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("startfight.png"), CCSprite::createWithSpriteFrameName("startfightp.png"),sprite,(BaseInfoBean*)pSender->getUserObject(),menu_selector(BaseInfoBean::toBattleScene));
    toBattle->setUserData(this);
    toBattle->setAnchorPoint(ccp(1,0));
    toBattle->setPosition(ccp(winSize.width-15,16));
    toBattle->setTag(battleButtonTag);
    menu->addChild(toBattle);
    
    this->addChild(deployLayer);
}


void TestScene::quitDeployCallBack() {
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sfx_click.mp3");
    this->removeChildByTag(deployLayerTag, true);
    for (int i = 0; i<5; i++) {
        flag[i] = 0;
    }
    CCObject* obj = NULL;
    int i = 0;
    CCARRAY_FOREACH(myArmyList, obj) {
        CreatorInfoBean* bean = (CreatorInfoBean*)obj;
        int j = MyGameInfo::getInstance()->creatorArray->indexOfObject(bean);
        if(i != j) {
            MyGameInfo::getInstance()->creatorArray->exchangeObjectAtIndex(i, j);
        }
        i++;
    }
    myArmyList->removeAllObjects();
}

void TestScene::selectCard(MyMenuItem* pSender) {
    if(myArmyList->count()==5) {
        CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sfx_error.wav");
        return;
    }
    
    isChangeArmy = true;
    
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sfx_click.mp3");
    
    pSender->setEnabled(false);
    CCSprite* gray = CCSprite::createWithSpriteFrameName("dialoggray.png");
    gray->setScaleX(pSender->getImage()->getContentSize().width/gray->getContentSize().width);
    gray->setScaleY(pSender->getImage()->getContentSize().height/gray->getContentSize().height);
    gray->setAnchorPoint(ccp(0,0));
    gray->setTag(cardGrayTag);
    pSender->addChild(gray);
    
    CreatorInfoBean* bean = (CreatorInfoBean*)pSender->getUserData();
    char str[32] = {0};
    sprintf(str, "deployBack%d.png",(bean->creator->getRarity()));
    CCSprite* sprite = CCSprite::createWithSpriteFrameName(str);
    sprintf(str, "%sbp.png",bean->creator->getSpriteFileName());
    CCSprite* bp = CCSprite::createWithSpriteFrameName(str);
    bp->setPosition(ccp(53,49));
    bp->setScale(Mathlib::min(115/bp->getContentSize().width, 90/bp->getContentSize().height));
    sprite->addChild(bp);
    sprintf(str, "Lv:%d",(bean->getLevel()));
    CCLabelTTF* lvfont = CCLabelTTF::create(str, "Arial", 25);
    lvfont->setAnchorPoint(ccp(0,0));
    lvfont->setPosition(ccp(10,5));;
    sprite->addChild(lvfont);
    
    MyMenuItem* bpItem = MyMenuItem::create(sprite, this, menu_selector(TestScene::cancelCard));
    CCPoint pos = pSender->getPosition();
    bpItem->setPosition(ccp(pSender->convertToWorldSpace(CCPointZero).x + pSender->getContentSize().width/2,pSender->convertToWorldSpace(CCPointZero).y + pSender->getContentSize().height-pSender->getContentSize().width/2+5));
    this->getChildByTag(deployLayerTag)->getChildByTag(deployMenuTag)->addChild(bpItem);
    bpItem->setScale(1.15);
    int i = 0;
    for (i=0; i<5; i++) {
        if (flag[i] == 0) {
            flag[i] = 1;
            break;
        }
    }
    
    bpItem->runAction(CCEaseInOut::create(CCMoveTo::create(0.2, ccp(winSize.width-720+i*118,522)), 2));
    bpItem->setUserData(pSender);
    myArmyList->addObject((CreatorInfoBean*)pSender->getUserData());
    if (myArmyList->count() > 0) {
        ((CCMenuItemSprite*)this->getChildByTag(deployLayerTag)->getChildByTag(deployMenuTag)->getChildByTag(battleButtonTag))->setEnabled(true);
    }
}

void TestScene::cancelCard(MyMenuItem *pSender) {
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sfx_click.mp3");
    
    MyMenuItem* item = (MyMenuItem*)pSender->getUserData();
    item->setEnabled(true);
    item->removeChildByTag(cardGrayTag, true);
    pSender->setEnabled(false);
    CCPoint p = ccp(item->convertToWorldSpace(CCPointZero).x + item->getContentSize().width/2,item->convertToWorldSpace(CCPointZero).y + item->getContentSize().height-item->getContentSize().width/2+5);
    pSender->runAction(CCSequence::create(CCEaseInOut::create(CCMoveTo::create(0.2, p), 1),GXRemoveFromParentsAction::create(),NULL));
    int i = (pSender->getPosition().x - (winSize.width-720))/118+0.5;
    flag[i] = 0;
    myArmyList->removeObject((CCObject*)item->getUserData());
    if (myArmyList->count() == 0) {
        ((CCMenuItemSprite*)this->getChildByTag(deployLayerTag)->getChildByTag(deployMenuTag)->getChildByTag(battleButtonTag))->setEnabled(false);
    }
}

void TestScene::toSearchNickname() {
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sfx_click.mp3");
    CCLayer* searchLayer = CCLayer::create();
    searchLayer->setTag(searchLayerTag);
    
    CCSprite* heiying = CCSprite::create("whiteImage.jpg");
    heiying->setScaleX(winSize.width/heiying->getContentSize().width);
    heiying->setScaleY(winSize.height/heiying->getContentSize().height);
    heiying->setColor(ccBLACK);
    heiying->setAnchorPoint(ccp(0,0));
    heiying->setOpacity(0);
    heiying->setPosition(ccp(0,0));
    heiying->runAction(CCFadeTo::create(0.5,100));
    searchLayer->addChild(heiying);
    
    CCLayer* banner = CCLayer::create();
    banner->setPosition(ccp(0,winSize.height+50));
    banner->runAction(CCEaseElasticOut::create(CCMoveTo::create(0.5,ccp(0,winSize.height))));
    CCSprite* heidi = CCSprite::create("whiteImage.jpg");
    heidi->setColor(ccBLACK);
    heidi->setScaleX(winSize.width/heidi->getContentSize().width);
    heidi->setScaleY(50/heidi->getContentSize().height);
    heidi->setAnchorPoint(ccp(0,1));
    heidi->setOpacity(123);
    
    banner->addChild(heidi);

    CCLabelTTF* tipLabel = CCLabelTTF::create("按昵称索敌","Arial",30);
    tipLabel->setAnchorPoint(ccp(0,0.5));
    tipLabel->setPosition(ccp(10,-25));
    tipLabel->setColor(ccc3(255,216,0));
    banner->addChild(tipLabel);
    
    CCSprite* inputSprite = CCSprite::create("whiteImage.jpg");
    inputSprite->setScaleX(200/inputSprite->getContentSize().width);
    inputSprite->setScaleY(40/inputSprite->getContentSize().height);
    inputSprite->setContentSize(CCSizeMake(200,40));
    inputSprite->setColor(ccc3(210,212,155));
    
    MyMenuItem* searchNickNameInputItem = MyMenuItem::create(inputSprite,this,menu_selector(TestScene::toAttachIME));
    searchNickNameInputItem->setPosition(ccp(winSize.width/2,-25));
    
    MyMenuItem* searchNickNameSureItem = MyMenuItem::create(CCSprite::createWithSpriteFrameName("searchIcon.png"),this,menu_selector(TestScene::sureSearchEnemyByNickname));
    searchNickNameSureItem->setPosition(ccp(winSize.width/2+150,-25));
    searchNickNameSureItem->setScale(0.9);
    
    
    
    CCMenuItemSprite* quitSearchNickname =CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("quitdeploy.png"),CCSprite::createWithSpriteFrameName("quitdeployp.png"),this,menu_selector(TestScene::quitSearch));
    quitSearchNickname->setPosition(ccp(winSize.width-50,-25));

    MyPriorityMenu* searchNickNameMenu = MyPriorityMenu::create(-502,searchNickNameInputItem,searchNickNameSureItem,quitSearchNickname,NULL);
    searchNickNameMenu->setPosition(ccp(0,0));
    
    banner->addChild(searchNickNameMenu);
    
    CCTextFieldTTF* searchNickNameField = CCTextFieldTTF::textFieldWithPlaceHolder("输入搜索昵称",CCSizeMake(190,0), kCCTextAlignmentLeft,"Arial",30);
    searchNickNameField->setAnchorPoint(ccp(0.5,0.5));
    searchNickNameField->setPosition(ccp(winSize.width/2,-25));
    searchNickNameInputItem->setUserData(searchNickNameField);
    searchNickNameSureItem->setUserData(searchNickNameField);
    searchNickNameField->setColor(ccc3(0,0,0));
    banner->addChild(searchNickNameField);
    
    GXShieldTouchMenuItem* shieldTouch= GXShieldTouchMenuItem::create();
    shieldTouch->setPosition(ccp(winSize.width/2,winSize.height/2));
    shieldTouch->setContentSize(winSize);
    
    MyPriorityMenu* shieldMenu = MyPriorityMenu::create(-501,shieldTouch,NULL);
    shieldMenu->setPosition(ccp(0,0));
    
    searchLayer->addChild(shieldMenu);
    searchLayer->addChild(banner);
    this->addChild(searchLayer);
    
}

void TestScene::quitSearch() {
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sfx_click.mp3");
    this->removeChildByTag(searchLayerTag,true);
}

void TestScene::toAttachIME(CCMenuItem* item) {
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sfx_click.mp3");
    CCTextFieldTTF* textField = (CCTextFieldTTF*)item->getUserData();
    textField->attachWithIME();
}

void TestScene::sureSearchEnemyByNickname(CCMenuItem* item) {
    CCString* nickname = CCString::create(((CCTextFieldTTF*)item->getUserData())->getString());
    if (nickname->length() > 18) {
        this->addChild(MyUtil::getInstance()->getCommonTipDialog(CCString::create("昵称请在6个中文字符以内"),MyUtil::getInstance(),menu_selector(MyUtil::cancelTipItem),2));
        return;
    } else if(nickname->length() <= 0) {
        this->addChild(MyUtil::getInstance()->getCommonTipDialog(CCString::create("昵称不能为空"),MyUtil::getInstance(),menu_selector(MyUtil::cancelTipItem),2));
        return;
    }
    this->addChild(MyUtil::getInstance()->getWaitLayer("正在加载中"));
    MyHttpConnection::getInstance()->sendSearchEnemyByNickname(nickname);
}

void TestScene::displaySearchResultList(CCArray* searchBaseInfoBeanArray) {
    
    if (searchBaseInfoBeanArray->count() <= 0) {
        this->addChild(MyUtil::getInstance()->getCommonTipDialog(CCString::create("没有搜索到指定玩家。"),MyUtil::getInstance(),menu_selector(MyUtil::cancelTipItem),2));
        return;
    }
    
    CCLayer* listLayer = CCLayer::create();
    listLayer->setTag(searchListLayerTag);
    listLayer->setPosition(ccp(-550,0));
    listLayer->runAction((CCEaseElasticOut::create(CCMoveTo::create(0.4, ccp(0,0)),1)));
    CCLayer* searchLayer = (CCLayer*)this->getChildByTag(searchLayerTag);
    searchLayer->removeChildByTag(searchListLayerTag,true);
    searchLayer->addChild(listLayer);
    
    CCSprite* back = MyUtil::getInstance()->getSecondMenuBox(650,550);
    back->setPosition(ccp(325,300));
    
    CCSprite* back2 = CCSprite::create("whiteImage.jpg");
    back2->setScaleX(640/back2->getContentSize().width);
    back2->setScaleY(540/back2->getContentSize().height);
    back2->setPosition(ccp(325,300));
    back2->setColor(ccc3(40,32,24));
    listLayer->addChild(back2);
    
    listLayer->addChild(back);
    
    GXScrollView* scollView = GXScrollView::create(-505);
    int i = 0;
    if (searchBaseInfoBeanArray->count() <7) {
        scollView->setOriPosition(ccp(10,35+(6-searchBaseInfoBeanArray->count())*80+40));
    } else {
        scollView->setOriPosition(ccp(10,35));
    }
    BaseInfoBean* bean;
    CCObject* obj;
    CCARRAY_FOREACH(searchBaseInfoBeanArray, obj) {
        bean = ((BaseInfoBean*)obj);
        
        CCSprite* line1 = CCSprite::create("whiteImage.jpg");
        line1->setScaleX(600/line1->getContentSize().width);
        line1->setScaleY(3/line1->getContentSize().height);
        line1->setAnchorPoint(ccp(0,0.5));
        line1->setPosition(ccp(10,16+i*80));
        line1->setColor(ccc3(157,137,88));
        scollView->addChild(line1);
        
        CCSprite* line2 = CCSprite::create("whiteImage.jpg");
        line2->setScaleX(600/line1->getContentSize().width);
        line2->setScaleY(6/line1->getContentSize().height);
        line2->setAnchorPoint(ccp(0,0.5));
        line2->setPosition(ccp(10,8+i*80));
        line2->setColor(ccc3(157,137,88));
        scollView->addChild(line2);
        
        CCMenuItemSprite* baseui1 = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("metalButton.png"), CCSprite::createWithSpriteFrameName("metalButtonP.png"),this,menu_selector(TestScene::toDeployArmy));
        //    CCMenuItemSprite*
        baseui1->setUserObject(bean);
        baseui1->setPosition(ccp(550,30+i*80));
        
        CCSprite* searchEnemyLabel = CCSprite::createWithSpriteFrameName("searchEnemyLabel.png");
        searchEnemyLabel->setPosition(ccp(baseui1->getContentSize().width/2,baseui1->getContentSize().height/2));
        baseui1->addChild(searchEnemyLabel);
        
        scollView->addChild(baseui1);
        
        CCSprite* rank1 =  MyUtil::getInstance()->getRankSprite(bean->honor);
        rank1->setAnchorPoint(ccp(0.5,0.5));
        rank1->setPosition(ccp(230,30+i*80));
        rank1->setScale(0.7);
        scollView->addChild(rank1);
        
        CCLabelTTF* rankname = CCLabelTTF::create(MyUtil::getInstance()->getRankString(bean->honor), "Arial", 25);
        rankname->setAnchorPoint(ccp(0.5,0.5));
        rankname->setPosition(ccp(270,30+i*80));
        rankname->setColor(ccc3(246, 255, 0));
        scollView->addChild(rankname);
        
        CCSprite* levelIcon = CCSprite::createWithSpriteFrameName("levelIcon.png");
        levelIcon->setPosition(ccp(320,30+i*80));
        levelIcon->setScale(0.5);
        scollView->addChild(levelIcon);
        
        char str[50] = {0};
        sprintf(str, "%d",MyUtil::getInstance()->getLevelByExperience(bean->experience));
        CCLabelAtlas* level1 = CCLabelAtlas::create(str, "levelupnumber.png", 40, 32, '0');
        level1->setAnchorPoint(ccp(0.5,0.5));
        level1->setPosition(ccp(360,30+i*80));
        level1->setScaleX(0.6);
        level1->setScaleY(0.7);
        scollView->addChild(level1);
        
        
        CCLabelTTF* name = CCLabelTTF::create(
                                              bean->getNickname()->getCString(), "Arial", 30);
        name->setAnchorPoint(ccp(0,0.5));
        name->setPosition(ccp(15,25+i*80));
        scollView->addChild(name);
       
        if (bean->getUnionName()->compare("") != 0) {
            sprintf(str, "[%s]",bean->getUnionName()->getCString());
            CCLabelTTF* unionName = CCLabelTTF::create(str, "Arial", 20);
            unionName->setAnchorPoint(ccp(0,0.5));
            unionName->setPosition(ccp(10,50+i*80));
//            unionName->setOpacity(180);
            scollView->addChild(unionName);
        }
        
        int  level = MyUtil::getInstance()->getLevelByExperience(bean->experience);
    
        float quan =  (Mathlib::bound(bean->nowTime - bean->time, 36000000, 0)/1000*MyUtil::getInstance()->updateLevelByRate(0,ytBaseColletSpeed,level,ytUpdateColletSpeedRate)+Mathlib::max(bean->oil+bean->iron,1000*level*level))*Mathlib::bound(MyGameInfo::getInstance()->enemyPower/MyGameInfo::getInstance()->getPower(),0.4,0)*bean->trophyRate;
        if (quan < 1000) {
            sprintf(str, "极少");
        } else if(quan<2000) {
            sprintf(str, "很少");
        } else if (quan<5000) {
            sprintf(str, "少");
        } else if (quan <10000) {
            sprintf(str, "略少");
        } else if (quan < 20000) {
            sprintf(str, "一般");
        } else if (quan < 50000) {
            sprintf(str, "略多");
        } else if (quan < 100000) {
            sprintf(str, "多");
        } else if (quan < 200000) {
            sprintf(str, "很多");
        } else {
            sprintf(str, "极多");
        }
        
        CCSprite* resourceIcon1 = MyUtil::getInstance()->getResourceIcon(oilTag);
        resourceIcon1->setScale(0.4);
        resourceIcon1->setAnchorPoint(ccp(0.5,0.5));
        resourceIcon1->setPosition(ccp(420,25+i*80));

        
        CCSprite* resourceIcon2 = MyUtil::getInstance()->getResourceIcon(ironTag);
        resourceIcon2->setScale(0.35);
        resourceIcon2->setAnchorPoint(ccp(0.5,0.5));
        resourceIcon2->setPosition(ccp(410,35+i*80));
        
        scollView->addChild(resourceIcon2);
        scollView->addChild(resourceIcon1);
        
        CCLabelTTF* resourceCount = CCLabelTTF::create(str, "Arial", 25);
        resourceCount->setAnchorPoint(ccp(0.5,0.5));
        resourceCount->setPosition(ccp(460,30+i*80));
        resourceCount->setColor(ccc3(246, 255, 0));
        scollView->addChild(resourceCount);
        
//        CCLabelTTF* defenSucc = CCLabelTTF::create(bean->getDefenSuccRate()->getCString(), "Arial", 25);
//        defenSucc->setAnchorPoint(ccp(0.5,0.5));
//        defenSucc->setPosition(ccp(500,30+i*80));
//        defenSucc->setColor(ccc3(246, 255, 0));
//        scollView->addChild(defenSucc);
       
        
        i++;
        
        //        scollView->setPosition(ccp(winSize.width/2,winSize.height/2));
    }
    

    scollView->setContentSize(CCSizeMake(630,530));
    scollView->setMapSize(CCSizeMake(200,80*searchBaseInfoBeanArray->count()));
    
    scollView->setPosition(ccp(10,-scollView->getMapSize().height+scollView->getViewSize().height+scollView->getOriPosition().y));
   
    listLayer->addChild(scollView);
}


BaseInfoBean* BaseInfoBean::create() {
    BaseInfoBean* bean = new BaseInfoBean();
    bean->autorelease();
    return bean;
}

void BaseInfoBean::toBattleScene(CCNode* pSender) {
    ((TestScene*)pSender->getUserData())->quitDeployCallBack();
    if (this->type == 1) {
        CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.2, TransitonScene::create(battleSceneBySearchTag,CCInteger::create(userId)), ccBLACK));
    } else {
        CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.2, TransitonScene::create(battleSceneTag,CCInteger::create(userId)), ccBLACK));
    }
    
    
    if (((TestScene*)pSender->getUserData())->isChangeArmy) {
        int id[5] = {-1,-1,-1,-1,-1};
        
        int up = Mathlib::min(MyGameInfo::getInstance()->creatorArray->count(),5);
        for (int i =0; i<up; i++) {
            id[i] = ((CreatorInfoBean*)MyGameInfo::getInstance()->creatorArray->objectAtIndex(i))->creator->cardId;
        }
        
        
        MyHttpConnection::getInstance()->sendCreateSort(id);
    }
}