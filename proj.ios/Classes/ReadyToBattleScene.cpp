//
//  ReadyToBattleScene.cpp
//  ww3
//
//  Created by xiao tang on 12-12-30.
//
//

#include "ReadyToBattleScene.h"
#include "MyPriorityMenu.h"
#include "DefineSet.h"
#include "MyUtil.h"
#include "Mathlib.h"
#include "MyGameFactory.h"
#include "TransitonScene.h"
#include "GXShieldTouchMenuItem.h"
#include "SimpleAudioEngine.h"
#include "GXScrollView.h"
#include "MyGameInfo.h"
#include "GXRemoveFromParentsAction.h"
#include "TestScene.h"

#define deployLayerTag 20
#define deployMenuTag 21
#define cardGrayTag 22
#define battleButtonTag 23

ReadyToBattleScene* ReadyToBattleScene::create(CCArray* arrayList) {
    ReadyToBattleScene *pRet = new ReadyToBattleScene();
    if (pRet && pRet->init()) {
        for (int i = 0; i<5; i++) {
            pRet->flag[i] = 0;
        }
//        pRet->baseInfoBeanArray = arrayList;
//        pRet->baseInfoBeanArray->retain();
//        pRet->myArmyList = CCArray::create();
//        pRet->myArmyList->retain();
        pRet->myinit();
        pRet->autorelease();
        return pRet;
    }
    
    CC_SAFE_DELETE(pRet);
    return NULL;
}

void ReadyToBattleScene::myinit() {
//    loadResource();
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
        CCMenuItemSprite* baseIcon1 = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName(str),baseIcon1Sprite,this,menu_selector(ReadyToBattleScene::toDeployArmy));
        baseIcon1->setUserData(bean);
        baseIcon1->setPosition(ccp(280,270));
        
//        CCMenuItemSprite* baseui1 = getBaseInfoItem(bean);
//        baseui1->setPosition(ccp(280,375));
//        menu->addChild(baseIcon1);
//        menu->addChild(baseui1);
    }
    
    
    // -------2---------
    
    if (1<baseInfoBeanArray->count()) {
        BaseInfoBean* bean = (BaseInfoBean*)baseInfoBeanArray->objectAtIndex(1);
        int level = MyUtil::getInstance()->getLevelByExperience(bean->experience);
        sprintf(str, "baseIcon%d.png",1+Mathlib::boundInt(level/5, 4, 0));
        CCSprite* baseIcon2Sprite = CCSprite::createWithSpriteFrameName(str);
        baseIcon2Sprite->setColor(ccGRAY);
        CCMenuItemSprite* baseIcon2 = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName(str),baseIcon2Sprite,this,menu_selector(ReadyToBattleScene::toDeployArmy));
        baseIcon2->setUserData(bean);
        baseIcon2->setPosition(ccp(400,76));
        
//        CCMenuItemSprite* baseui2 = getBaseInfoItem(bean);
//        baseui2->setPosition(ccp(405,181));
//        menu->addChild(baseIcon2);
//        menu->addChild(baseui2);
    }
    
    
    //--------3-------
    if (2<baseInfoBeanArray->count()) {
        BaseInfoBean* bean = (BaseInfoBean*)baseInfoBeanArray->objectAtIndex(2);
        int level = MyUtil::getInstance()->getLevelByExperience(bean->experience);
        sprintf(str, "baseIcon%d.png",1+Mathlib::boundInt(level/5, 4, 0));
        CCSprite* baseIcon3Sprite = CCSprite::createWithSpriteFrameName(str);
        baseIcon3Sprite->setColor(ccGRAY);
        CCMenuItemSprite* baseIcon3 = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName(str),baseIcon3Sprite,this,menu_selector(ReadyToBattleScene::toDeployArmy));
        baseIcon3->setUserData(bean);
        baseIcon3->setPosition(ccp(750,20));
        
//        CCMenuItemSprite* baseui3 = getBaseInfoItem(bean);
//        baseui3->setPosition(ccp(750,125));
//        menu->addChild(baseIcon3);
//        menu->addChild(baseui3);
    }
    
    
    //--------4-------
    if (3<baseInfoBeanArray->count()) {
        BaseInfoBean* bean = (BaseInfoBean*)baseInfoBeanArray->objectAtIndex(3);
        int level = MyUtil::getInstance()->getLevelByExperience(bean->experience);
        sprintf(str, "baseIcon%d.png",1+Mathlib::boundInt(level/5, 4, 0));
        CCSprite* baseIcon4Sprite = CCSprite::createWithSpriteFrameName(str);
        baseIcon4Sprite->setColor(ccGRAY);
        CCMenuItemSprite* baseIcon4 = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName(str),baseIcon4Sprite,this,menu_selector(ReadyToBattleScene::toDeployArmy));
        baseIcon4->setUserData(bean);
        baseIcon4->setPosition(ccp(780,489));
        
//        CCMenuItemSprite* baseui4 = getBaseInfoItem(bean);
//        baseui4->setPosition(ccp(661,560));
//        menu->addChild(baseIcon4);
//        menu->addChild(baseui4);
    }
    
    
   //---------5----------
    if (4<baseInfoBeanArray->count()) {
        BaseInfoBean* bean = (BaseInfoBean*)baseInfoBeanArray->objectAtIndex(4);
        int level = MyUtil::getInstance()->getLevelByExperience(bean->experience);
        sprintf(str, "baseIcon%d.png",1+Mathlib::boundInt(level/5, 4, 0));
        CCSprite* baseIcon5Sprite = CCSprite::createWithSpriteFrameName(str);
        baseIcon5Sprite->setColor(ccGRAY);
        CCMenuItemSprite* baseIcon5 = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName(str),baseIcon5Sprite,this,menu_selector(ReadyToBattleScene::toDeployArmy));
        baseIcon5->setUserData(bean);
        baseIcon5->setPosition(ccp(900,326));
        
//        CCMenuItemSprite* baseui5 = getBaseInfoItem(bean);
//        baseui5->setPosition(ccp(755,380));
//        menu->addChild(baseIcon5);
//        menu->addChild(baseui5);
    }

    CCSprite* next = CCSprite::createWithSpriteFrameName("next.png");
    CCSprite* gynext = CCSprite::createWithSpriteFrameName("next.png");
    gynext->setColor(ccGRAY);

    CCMenuItemSprite* nextItem = CCMenuItemSprite::create(next, gynext, this, menu_selector(ReadyToBattleScene::toNextCallBack));
    nextItem->setPosition(ccp(winSize.width - 100,winSize.height/3));
    
    CCSprite* surrender = CCSprite::createWithSpriteFrameName("backToBuild.png");
    CCSprite* gysurrender = CCSprite::createWithSpriteFrameName("backToBuild.png");
    gysurrender->setColor(ccGRAY);
    
    CCMenuItemSprite* homeItem = CCMenuItemSprite::create(surrender, gysurrender, this, menu_selector(ReadyToBattleScene::toHomeCallBack));
    homeItem->setPosition(ccp(100,winSize.height/3));
    
    
    CCMenu* uiMenu = CCMenu::create(nextItem,homeItem,NULL);
    uiMenu->setPosition(ccp(0,0));
   
    menu->setPosition(ccp(0,0));
    backLayer->addChild(menu);

//    for(int i=0;i<10;i++) {
//                MyGameInfo::getInstance()->creatorArray->addObject(CCString::create("tank.j"));
//    }
    
//    initCloud();
    backLayer->addChild(uiMenu,5);
}

void ReadyToBattleScene::initCloud() {
    CCLayer* cloudLayer = CCLayer::create();
    CCSprite* cloud1 = CCSprite::createWithSpriteFrameName("cloud1.png");
    cloud1->setPosition(ccp(arc4random()%960,arc4random()%640));
    cloud1->setRotation(arc4random()%360);
    cloud1->setOpacity(arc4random()%100+155);
    cloud1->setScale((((float)(arc4random()%70))/100 +0.3)*2);
    float distanceX =  -cloud1->getContentSize().width - cloud1->getPositionX();
    int speed = arc4random()%40+10;
    //    CCLog("%f",distanceX);
    cloud1->runAction(CCSequence::create(CCMoveBy::create(-(distanceX/speed),ccp(distanceX,0)),CCCallFuncND::create(this, callfuncND_selector(ReadyToBattleScene::cloudCallBack), (void*)cloud1),NULL));
    
    CCSprite* cloud2 = CCSprite::createWithSpriteFrameName("cloud2.png");
    cloud2->setPosition(ccp(arc4random()%960,arc4random()%640));
    cloud2->setRotation(arc4random()%360);
    cloud2->setOpacity(arc4random()%100+155);
    cloud2->setScale((((float)(arc4random()%70))/100 +0.3)*2);
    distanceX =  -cloud2->getContentSize().width - cloud2->getPositionX();
    //    CCLog("%f",distanceX);
    speed = arc4random()%40+10;
    cloud2->runAction(CCSequence::create(CCMoveBy::create(-(distanceX/speed),ccp(distanceX,0)),CCCallFuncND::create(this, callfuncND_selector(ReadyToBattleScene::cloudCallBack), (void*)cloud2),NULL));
    
    CCSprite* cloud3 = CCSprite::createWithSpriteFrameName("cloud3.png");
    cloud3->setPosition(ccp(arc4random()%960,arc4random()%640));
    cloud3->setRotation(arc4random()%360);
    cloud3->setOpacity(arc4random()%100+155);
    cloud3->setScale((((float)(arc4random()%70))/100 +0.3)*2);
    distanceX =  -cloud3->getContentSize().width/2 - cloud3->getPositionX();
    //    CCLog("%f",distanceX);
    speed = arc4random()%40+10;
    cloud3->runAction(CCSequence::create(CCMoveBy::create(-(distanceX/speed),ccp(distanceX,0)),CCCallFuncND::create(this, callfuncND_selector(ReadyToBattleScene::cloudCallBack), (void*)cloud3),NULL));
    
    cloudLayer->addChild(cloud1);
    cloudLayer->addChild(cloud2);
    cloudLayer->addChild(cloud3);
    
    this->addChild(cloudLayer);
}

void ReadyToBattleScene::releaseResource() {
    
    CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile("battleui.plist");
    CCTextureCache::sharedTextureCache()->removeTextureForKey("battleui.pvr.ccz");
    CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile("baseIcon.plist");
    CCTextureCache::sharedTextureCache()->removeTextureForKey("baseIcon.pvr.ccz");
    
    CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile("deployui.plist");
    CCTextureCache::sharedTextureCache()->removeTextureForKey("deployui.pvr.ccz");

    
    CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile("cloud.plist");
    CCTextureCache::sharedTextureCache()->removeTextureForKey("cloud.pvr.ccz");
    
     CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile("area1.plist");
    CCTextureCache::sharedTextureCache()->removeTextureForKey("area1.pvr.ccz");

    GarbageResourceCollection::getInstance()->GarbageCollection();
}

void ReadyToBattleScene::loadResource() {
    GXUtil::loadResourceUtilSucc("baseIcon.plist","baseIcon.pvr.ccz");
    GXUtil::loadResourceUtilSucc("battleui.plist","battleui.pvr.ccz");
    GXUtil::loadResourceUtilSucc("deployui.plist","deployui.pvr.ccz");
    GXUtil::loadResourceUtilSucc("cloud.plist","cloud.pvr.ccz");
    GXUtil::loadResourceUtilSucc("area1.plist","area1.pvr.ccz");
}

void ReadyToBattleScene::cloudCallBack(CCNode* pSender,CCSprite* cloud) {
    cloud->setScale((((float)(arc4random()%70))/100 +0.3)*2);
    float posiX= 960+cloud->getContentSize().width;
    cloud->setPosition(ccp(posiX,arc4random()%640));
    cloud->setRotation(arc4random()%360);
    cloud->setOpacity(arc4random()%100+155);
    
    float distanceX =  -cloud->getContentSize().width/2 - cloud->getPositionX();
    //    CCLog("%f",distanceX);
    int speed = arc4random()%40+10;
    cloud->runAction(CCSequence::create(CCMoveBy::create(-(distanceX/speed),ccp(distanceX,0)),CCCallFuncND::create(this, callfuncND_selector(ReadyToBattleScene::cloudCallBack), (void*)cloud),NULL));
}

//CCMenuItemSprite* ReadyToBattleScene::getBaseInfoItem(BaseInfoBean* bean) {
//    CCSprite* baseui1Sprite = CCSprite::create("baseui.png");
//    baseui1Sprite->setColor(ccGRAY);
//    CCMenuItemSprite* baseui1 = CCMenuItemSprite::create(CCSprite::create("baseui.png"), baseui1Sprite,this,menu_selector(ReadyToBattleScene::toDeployArmy));
//    //    CCMenuItemSprite*
//    baseui1->setUserData(bean);
//    
//    CCSprite* rank1 =  MyUtil::getInstance()->getRankSprite(bean->honor);
//    rank1->setAnchorPoint(ccp(0.5,0.5));
//    rank1->setPosition(ccp(20,25));
//    rank1->setScale(0.4);
//    baseui1->addChild(rank1);
//    
//    CCLabelTTF* rankname = CCLabelTTF::create(MyUtil::getInstance()->getRankString(bean->honor), "Arial", 16);
//    rankname->setAnchorPoint(ccp(0.5,0.5));
//    rankname->setPosition(ccp(50,25));
//    rankname->setColor(ccc3(246, 255, 0));
//    baseui1->addChild(rankname);
//    
//    char str[10] = {0};
//    sprintf(str, "%d",MyUtil::getInstance()->getLevelByExperience(bean->experience));
//    CCLabelAtlas* level1 = CCLabelAtlas::create(str, "levelupnumber.png", 40, 32, '0');
//    level1->setAnchorPoint(ccp(0.5,0.5));
//    level1->setPosition(ccp(50,44));
//    level1->setScale(0.4);
//    baseui1->addChild(level1);
//    
//    CCLabelTTF* name = CCLabelTTF::create(bean->nickName, "Arial", 17);
//    name->setAnchorPoint(ccp(0.5,0.5));
//    name->setPosition(ccp(120,88));
//    name->setColor(ccBLACK);
//    baseui1->addChild(name);
//    
//    int  level = MyUtil::getInstance()->getLevelByExperience(bean->experience);
//    float quan =  (Mathlib::bound(bean->nowTime - bean->time, 36000000, 0)*ytBaseColletSpeed/1000*level+bean->oil+bean->iron)*0.2;
//    if (quan < 1000) {
//        sprintf(str, "极少");
//    } else if(quan<2000) {
//        sprintf(str, "很少");
//    } else if (quan<5000) {
//        sprintf(str, "少");
//    } else if (quan <10000) {
//        sprintf(str, "略少");
//    } else if (quan < 20000) {
//        sprintf(str, "一般");
//    } else if (quan < 50000) {
//        sprintf(str, "略多");
//    } else if (quan < 100000) {
//        sprintf(str, "多");
//    } else if (quan < 200000) {
//        sprintf(str, "很多");
//    } else {
//        sprintf(str, "极多");
//    }
//    
//    CCLabelTTF* resourceCount = CCLabelTTF::create(str, "Arial", 20);
//    resourceCount->setAnchorPoint(ccp(0.5,0.5));
//    resourceCount->setPosition(ccp(138,56));
//    resourceCount->setColor(ccc3(246, 255, 0));
//    baseui1->addChild(resourceCount);
//    
//    CCLabelTTF* defenSucc = CCLabelTTF::create(bean->defenSuccRate, "Arial", 20);
//    defenSucc->setAnchorPoint(ccp(0.5,0.5));
//    defenSucc->setPosition(ccp(138,31));
//    defenSucc->setColor(ccc3(246, 255, 0));
//    baseui1->addChild(defenSucc);
//    return baseui1;
//}

void ReadyToBattleScene::toNextCallBack() {
    CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.2, TransitonScene::create(ReadyToBattleTag),ccBLACK));
}

void ReadyToBattleScene::toHomeCallBack() {
    CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.2, TransitonScene::create(startSceneTag), ccBLACK));
}

void ReadyToBattleScene::toDeployArmy(CCNode* pSender) {
    
    
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
    
    CCMenuItemSprite* quitItem = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("quitdeploy.png"), CCSprite::createWithSpriteFrameName("quitdeployp.png"),this,menu_selector( ReadyToBattleScene::quitDeployCallBack));
    
    quitItem->setPosition(ccp(winSize.width-24,winSize.height-24));
    
    
    MyPriorityMenu* menu = MyPriorityMenu::create(-501, quitItem,shieldTouch,NULL);
    menu->setPosition(ccp(0,0));
    menu->setTag(deployMenuTag);
    
    deployLayer->addChild(menu,2);
    
    
    GXScrollView* scroll = GXScrollView::create(-502);
//    CCSprite* test = CCSprite::create("loading.jpg");
//    test->setAnchorPoint(ccp(0,0));
//    scroll->addChild(test);
    scroll->setOriPosition(ccp(192,45));
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
//        UnitCreator* creator = (UnitCreator*)MyGameFactory::createCreatorbyJsonScriptFile(((CreatorInfoBean*)obj)->getScriptName()->getCString(), unitCreatorClassTag);
        UnitBean* creator = ((CreatorInfoBean*)obj)->creator;
        MyMenuItem* cardBack = MyMenuItem::create(CCSprite::createWithSpriteFrameName("deployCardBack.png"), this, menu_selector(ReadyToBattleScene::selectCard)) ;
        
        sprintf(str, "%sbp.png",creator->getSpriteFileName());
        CCSprite* bp = CCSprite::createWithSpriteFrameName(str);
        if (bp == NULL) {
            break;
        }
        sprintf(str, "deployBack%d.png",(creator->getRarity()));
        CCSprite* sprite = CCSprite::createWithSpriteFrameName(str);
        bp->setPosition(ccp(53,49));
        bp->setScale(Mathlib::min(115/bp->getContentSize().width, 90/bp->getContentSize().height));
        sprite->addChild(bp);
        sprite->setPosition(ccp(cardBack->getContentSize().width/2,cardBack->getContentSize().height-cardBack->getContentSize().width/2+5));
        sprite->setScale(1.1);
        CCSprite* mIcon = CCSprite::createWithSpriteFrameName("militaryIcon.png");
        mIcon->setPosition(ccp(50,35));
        mIcon->setScale(0.4);
        cardBack->addChild(sprite);
        cardBack->addChild(mIcon);
        cardBack->setUserData(obj);
        
        float posi = (creator->getRarity()-1)*23;
        for (int j = 0; j<creator->getRarity(); j++) {
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
        
            sprintf(str, "deployBack%d.png",(creator->getRarity()));
            CCSprite* sprite = CCSprite::createWithSpriteFrameName(str);
            sprintf(str, "%sbp.png",creator->getSpriteFileName());
            CCSprite* bp = CCSprite::createWithSpriteFrameName(str);
            bp->setPosition(ccp(53,49));
            bp->setScale(Mathlib::min(115/bp->getContentSize().width, 90/bp->getContentSize().height));
            sprite->addChild(bp);
            
            MyMenuItem* bpItem = MyMenuItem::create(sprite, this, menu_selector(ReadyToBattleScene::cancelCard));

            menu->addChild(bpItem);
            bpItem->setScale(1.15);
            flag[i] = 1;
            bpItem->setPosition(ccp(240+i*118,522));
            
            bpItem->setUserData(cardBack);
            myArmyList->addObject(obj);
        }
        
        

        cardBack->setPosition(ccp(100 + (i%3)*180,scroll->getMapSize().height-85-(i/3)*180));
        scroll->addChild(cardBack);
        i++;
    }
    
    CCSprite* sprite = CCSprite::createWithSpriteFrameName("startfight.png");
    sprite->setColor(ccGRAY);
    
    CCMenuItemSprite* toBattle = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("startfight.png"), CCSprite::createWithSpriteFrameName("startfightp.png"),sprite,(BaseInfoBean*)pSender->getUserData(),menu_selector(BaseInfoBean::toBattleScene));
    toBattle->setAnchorPoint(ccp(1,0));
    toBattle->setPosition(ccp(winSize.width-15,16));
    toBattle->setTag(battleButtonTag);
    menu->addChild(toBattle);
    
    this->addChild(deployLayer);
}

void ReadyToBattleScene::selectCard(MyMenuItem* pSender) {
//    if(myArmyList->count()==5) {
//        CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sfx_error.wav");
//        return;
//    }
//    
//    
//    
//    CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sfx_click.mp3");
//    
//    pSender->setEnabled(false);
//    CCSprite* gray = CCSprite::createWithSpriteFrameName("dialoggray.png");
//    gray->setScaleX(pSender->getImage()->getContentSize().width/gray->getContentSize().width);
//    gray->setScaleY(pSender->getImage()->getContentSize().height/gray->getContentSize().height);
//    gray->setAnchorPoint(ccp(0,0));
//    gray->setTag(cardGrayTag);
//    pSender->addChild(gray);
//    
//    UnitCreator* creator = (UnitCreator*)MyGameFactory::createCreatorbyJsonScriptFile(((CCString*)pSender->getUserData())->getCString(), unitCreatorClassTag);
//    char str[32] = {0};
//    sprintf(str, "deployBack%d.png",(creator->getRarity()));
//    CCSprite* sprite = CCSprite::createWithSpriteFrameName(str);
//    sprintf(str, "%sbp.png",creator->getSpriteFileName());
//    CCSprite* bp = CCSprite::createWithSpriteFrameName(str);
//    bp->setPosition(ccp(53,49));
//    bp->setScale(Mathlib::min(115/bp->getContentSize().width, 90/bp->getContentSize().height));
//    sprite->addChild(bp);
//    
//    MyMenuItem* bpItem = MyMenuItem::create(sprite, this, menu_selector(ReadyToBattleScene::cancelCard));
//    CCPoint pos = pSender->getPosition();
//    bpItem->setPosition(ccp(pSender->convertToWorldSpace(CCPointZero).x + pSender->getContentSize().width/2,pSender->convertToWorldSpace(CCPointZero).y + pSender->getContentSize().height-pSender->getContentSize().width/2+5));
//    this->getChildByTag(deployLayerTag)->getChildByTag(deployMenuTag)->addChild(bpItem);
//    bpItem->setScale(1.15);
//    int i = 0;
//    for (i=0; i<5; i++) {
//        if (flag[i] == 0) {
//            flag[i] = 1;
//            break;
//        }
//    }
//    
//    bpItem->runAction(CCEaseInOut::create(CCMoveTo::create(0.2, ccp(240+i*118,522)), 2));
//    bpItem->setUserData(pSender);
//    myArmyList->addObject((CCString*)pSender->getUserData());
//    if (myArmyList->count() > 0) {
//        ((CCMenuItemSprite*)this->getChildByTag(deployLayerTag)->getChildByTag(deployMenuTag)->getChildByTag(battleButtonTag))->setEnabled(true);
//    }
}

void ReadyToBattleScene::cancelCard(MyMenuItem *pSender) {
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sfx_click.mp3");

    MyMenuItem* item = (MyMenuItem*)pSender->getUserData();
    item->setEnabled(true);
    item->removeChildByTag(cardGrayTag, true);
    pSender->setEnabled(false);
    CCPoint p = ccp(item->convertToWorldSpace(CCPointZero).x + item->getContentSize().width/2,item->convertToWorldSpace(CCPointZero).y + item->getContentSize().height-item->getContentSize().width/2+5);
    pSender->runAction(CCSequence::create(CCEaseInOut::create(CCMoveTo::create(0.2, p), 1),GXRemoveFromParentsAction::create(),NULL));
    int i = (pSender->getPosition().x - 240)/118+0.5;
    flag[i] = 0;
    myArmyList->removeObject((UnitBean*)item->getUserData());
    if (myArmyList->count() == 0) {
        ((CCMenuItemSprite*)this->getChildByTag(deployLayerTag)->getChildByTag(deployMenuTag)->getChildByTag(battleButtonTag))->setEnabled(false);
    }
}

void ReadyToBattleScene::quitDeployCallBack() {
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sfx_click.mp3");
    this->removeChildByTag(deployLayerTag, true);
    for (int i = 0; i<5; i++) {
        flag[i] = 0;
    }
    CCObject* obj = NULL;
    int i = 0;
    CCARRAY_FOREACH(myArmyList, obj) {
        CCString* str = (CCString*)obj;
        int j = MyGameInfo::getInstance()->creatorArray->indexOfObject(str);
        if(i != j) {
            MyGameInfo::getInstance()->creatorArray->exchangeObjectAtIndex(i, j);
        }
        i++;
    }
    myArmyList->removeAllObjects();
}



