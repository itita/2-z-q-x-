//
//  MyShopCard.cpp
//  ww4
//
//  Created by xiao tang on 13-4-19.
//
//

#include "MyShopCard.h"
#include "MathLib.h"
#include "MyPriorityMenu.h"
#include "StartScene.h"
#include "MyGameInfo.h"
#include "MyGameFactory.h"
#include "GXLineSprite.h"



MyShopCard* MyShopCard::create(BuildingCreator* buildingCreator,int cost,int mode,CCObject *rec,SEL_MenuHandler selector) {
    MyShopCard *pRet = new MyShopCard();
    pRet->purchaseSelector = selector;
    pRet->mode = mode;
    pRet->cost = cost;
    pRet->setTag(buildingCreator->cardId);
    CCSprite* cardBack = CCSprite::createWithSpriteFrameName("shopCardBack.png");
    cardBack->setScaleX(420/cardBack->getContentSize().width);
    cardBack->setScaleY(190/cardBack->getContentSize().height);
    cardBack->setContentSize(CCSizeMake(420, 190));
    
    pRet->bean = buildingCreator;
    CC_SAFE_RETAIN(pRet->bean);
    
    if (mode == hotMode) {
        CCSprite* hotBack = CCSprite::createWithSpriteFrameName("shopHotBack.png");
        hotBack->setScale(0.5);
        hotBack->setAnchorPoint(ccp(0,1));
        hotBack->setPosition(ccp(0,95));
        hotBack->setColor(ccc3(183,57,3));
        cardBack->addChild(hotBack);
        
        CCSprite* hotLabel = CCSprite::createWithSpriteFrameName("shopHotLabel.png");
        hotLabel->setAnchorPoint(ccp(0,1));
        hotLabel->setPosition(ccp(3,hotBack->getContentSize().height-3));
        hotBack->addChild(hotLabel);
    } else if(mode == newMode) {
        CCSprite* newBack = CCSprite::createWithSpriteFrameName("shopHotBack.png");
        newBack->setScale(0.5);
        newBack->setAnchorPoint(ccp(0,1));
        newBack->setPosition(ccp(0,95));
        newBack->setColor(ccc3(3,183,57));
        cardBack->addChild(newBack);
        
        CCSprite* newLabel = CCSprite::createWithSpriteFrameName("shopNewLabel.png");
        newLabel->setAnchorPoint(ccp(0,1));
        newLabel->setPosition(ccp(3,newBack->getContentSize().height-3));
        newBack->addChild(newLabel);
    }
    
    if (buildingCreator->rarity == 0) {
        CCSprite* lightSprite = CCSprite::createWithSpriteFrameName("creatorLight.png");
        lightSprite->setScale(0.4);
        lightSprite->setOpacity(153);
        lightSprite->setPosition(ccp(50,55));
        cardBack->addChild(lightSprite);
        
        CCSprite* bp = CCSprite::createWithSpriteFrameName(buildingCreator->getSpriteFileName());
        bp->setPosition(ccp(55,47));
        bp->setScale(Mathlib::min(195/bp->getContentSize().width,154/bp->getContentSize().height)*0.5);
        cardBack->addChild(bp);
    } else {
        
        pRet->setUserObject(CreatorInfoBean::create(buildingCreator->cardId));

        CCSprite* lightSprite = CCSprite::createWithSpriteFrameName("creatorLight.png");
        lightSprite->setScale(0.4);
        lightSprite->setOpacity(153);
        lightSprite->setPosition(ccp(55,55));
        cardBack->addChild(lightSprite);
        
        char str[50]  = {0};
        sprintf(str, "%sbp.png",buildingCreator->getSpriteFileName());
        CCSprite* bp = CCSprite::createWithSpriteFrameName(str);
        bp->setPosition(ccp(60,55));
        bp->setScale(Mathlib::min(195/bp->getContentSize().width,132/bp->getContentSize().height)*0.5);
        cardBack->addChild(bp);
                
        float posi = (buildingCreator->rarity-1)*15;
        for (int i = 0; i<buildingCreator->rarity; i++) {
            CCSprite* star = CCSprite::createWithSpriteFrameName("armystar.png");
            star->setPosition(ccp(60-posi/2 + i*15,15));
            star->setScale(0.5);
            cardBack->addChild(star);
        }

    }
    
    
    
    
    CCLabelTTF* name = CCLabelTTF::create(buildingCreator->getBuildingName(),"Arial",36);
    name->setPosition(ccp(145,78));
    name->setColor(ccc3(255,224,122));
    name->setScale(0.5);
    cardBack->addChild(name);
    
    CCSprite* diamond = CCSprite::createWithSpriteFrameName("diamond.png");
    diamond->setScale(0.5);
    diamond->setPosition(ccp(120,59));
    cardBack->addChild(diamond);
    
    CCSprite* boughtLabel1 = CCSprite::createWithSpriteFrameName("shopBoughtLabel_2.png");
    CCSprite* shopPurchaseButton = CCSprite::createWithSpriteFrameName("shopEmptyButton.png");
    boughtLabel1->setPosition(ccp(shopPurchaseButton->getContentSize().width/2,shopPurchaseButton->getContentSize().height/2+3));
    shopPurchaseButton->addChild(boughtLabel1);
    
    
    CCSprite* boughtLabel2 = CCSprite::createWithSpriteFrameName("shopBoughtLabel_2.png");
    CCSprite* shopPurchaseButtonP = CCSprite::createWithSpriteFrameName("shopEmptyButtonP.png");
    boughtLabel2->setPosition(ccp(shopPurchaseButtonP->getContentSize().width/2,shopPurchaseButtonP->getContentSize().height/2+3));
    shopPurchaseButtonP->addChild(boughtLabel2);
    
    CCSprite* alreadyBought = CCSprite::createWithSpriteFrameName("shopBoughtLabel.png");
    CCSprite* boughtLabel = CCSprite::createWithSpriteFrameName("shopBoughtLabel_2.png");
    alreadyBought->setAnchorPoint(ccp(1,0));
    alreadyBought->setPosition(ccp(4,1));
    boughtLabel->addChild(alreadyBought);
    
    
    CCMenuItemSprite* purchaseItem = CCMenuItemSprite::create(shopPurchaseButton,shopPurchaseButtonP,boughtLabel,rec,selector);
    boughtLabel->setPosition(ccp(53,15));
    purchaseItem->setScale(0.5);
    purchaseItem->setUserData(pRet);
    pRet->buyItem = purchaseItem;
    //    purchaseItem->setContentSize(CCSizeMake(purchaseItem->getContentSize().width/2,purchaseItem->getContentSize().height/2));
    
    MyPriorityMenu* menu = MyPriorityMenu::create(-508,purchaseItem,NULL);
    menu->setPosition(ccp(145,22));
    cardBack->addChild(menu);
    
    char str[50] = {0};
    sprintf(str,"%d",cost);
    CCLabelAtlas* costLabel = CCLabelAtlas::create(str, "number6.png", 24, 36, '/');
    costLabel->setPosition(ccp(155,55));
    costLabel->setAnchorPoint(ccp(0.5,0.5));
    costLabel->setColor(ccc3(255,224,122));
    costLabel->setScale(0.5);
    cardBack->addChild(costLabel);
    
    pRet->initWithImage(cardBack, rec,menu_selector(StartScene::toDisplayBuildingInfo));
    pRet->autorelease();
    
    return pRet;
}

MyShopCard* MyShopCard::create(CCSprite* avatarSprite,const std::string& nameStr,int cost,int mode,CCObject *rec, SEL_MenuHandler selector) {
    MyShopCard *pRet = new MyShopCard();
    
    pRet->mode = mode;
    CCSprite* cardBack = CCSprite::createWithSpriteFrameName("shopCardBack.png");
    cardBack->setScaleX(420/cardBack->getContentSize().width);
    cardBack->setScaleY(190/cardBack->getContentSize().height);
    cardBack->setContentSize(CCSizeMake(420, 190));
    
    if (mode == hotMode) {
        CCSprite* hotBack = CCSprite::createWithSpriteFrameName("shopHotBack.png");
        hotBack->setScale(0.5);
        hotBack->setAnchorPoint(ccp(0,1));
        hotBack->setPosition(ccp(0,95));
        hotBack->setColor(ccc3(183,57,3));
        cardBack->addChild(hotBack);
        
        CCSprite* hotLabel = CCSprite::createWithSpriteFrameName("shopHotLabel.png");
        hotLabel->setAnchorPoint(ccp(0,1));
        hotLabel->setPosition(ccp(3,hotBack->getContentSize().height-3));
        hotBack->addChild(hotLabel);
    } else if(mode == newMode) {
        CCSprite* newBack = CCSprite::createWithSpriteFrameName("shopHotBack.png");
        newBack->setScale(0.5);
        newBack->setAnchorPoint(ccp(0,1));
        newBack->setPosition(ccp(0,95));
        newBack->setColor(ccc3(3,183,57));
        cardBack->addChild(newBack);
        
        CCSprite* newLabel = CCSprite::createWithSpriteFrameName("shopNewLabel.png");
        newLabel->setAnchorPoint(ccp(0,1));
        newLabel->setPosition(ccp(3,newBack->getContentSize().height-3));
        newBack->addChild(newLabel);
    }
    
    CCSprite* lightSprite = CCSprite::createWithSpriteFrameName("creatorLight.png");
    lightSprite->setScale(0.4);
    lightSprite->setOpacity(153);
    lightSprite->setPosition(ccp(50,55));
    cardBack->addChild(lightSprite);
    
    
    avatarSprite->setPosition(ccp(55,47));
    avatarSprite->setScale(Mathlib::min(165/avatarSprite->getContentSize().width,134/avatarSprite->getContentSize().height)*0.5);
    cardBack->addChild(avatarSprite);
    
    
    
    CCLabelTTF* name = CCLabelTTF::create(nameStr.c_str(),"Arial",36);
    name->setPosition(ccp(145,78));
    name->setColor(ccc3(255,224,122));
    name->setScale(0.5);
    cardBack->addChild(name);
    
    CCSprite* diamond = CCSprite::createWithSpriteFrameName("diamond.png");
    diamond->setScale(0.5);
    diamond->setPosition(ccp(120,59));
    cardBack->addChild(diamond);
    
    //诡异的购买按钮
    CCSprite* boughtLabel1 = CCSprite::createWithSpriteFrameName("shopBoughtLabel_2.png");
    CCSprite* shopPurchaseButton = CCSprite::createWithSpriteFrameName("shopEmptyButton.png");
    boughtLabel1->setPosition(ccp(shopPurchaseButton->getContentSize().width/2,shopPurchaseButton->getContentSize().height/2+3));
    shopPurchaseButton->addChild(boughtLabel1);
    
    
    CCSprite* boughtLabel2 = CCSprite::createWithSpriteFrameName("shopBoughtLabel_2.png");
    CCSprite* shopPurchaseButtonP = CCSprite::createWithSpriteFrameName("shopEmptyButtonP.png");
    boughtLabel2->setPosition(ccp(shopPurchaseButtonP->getContentSize().width/2,shopPurchaseButtonP->getContentSize().height/2+3));
    shopPurchaseButtonP->addChild(boughtLabel2);
    
    CCSprite* alreadyBought = CCSprite::createWithSpriteFrameName("shopBoughtLabel.png");
    CCSprite* boughtLabel = CCSprite::createWithSpriteFrameName("shopBoughtLabel_2.png");
    alreadyBought->setAnchorPoint(ccp(1,0));
    alreadyBought->setPosition(ccp(4,1));
    boughtLabel->addChild(alreadyBought);
    
    
    CCMenuItemSprite* purchaseItem = CCMenuItemSprite::create(shopPurchaseButton,shopPurchaseButtonP,boughtLabel,rec,selector);
    
    boughtLabel->setPosition(ccp(53,15));
    purchaseItem->setScale(0.5);
    pRet->buyItem = purchaseItem;

    //    purchaseItem->setContentSize(CCSizeMake(purchaseItem->getContentSize().width/2,purchaseItem->getContentSize().height/2));
    
    MyPriorityMenu* menu = MyPriorityMenu::create(-508,purchaseItem,NULL);
    menu->setPosition(ccp(145,22));
    cardBack->addChild(menu);
    
    char str[50] = {0};
    sprintf(str,"%d",cost);
    CCLabelAtlas* costLabel = CCLabelAtlas::create(str, "number6.png", 24, 36, '/');
    costLabel->setPosition(ccp(155,55));
    costLabel->setAnchorPoint(ccp(0.5,0.5));
    costLabel->setColor(ccc3(255,224,122));
    costLabel->setScale(0.5);
    cardBack->addChild(costLabel);
    
    pRet->initWithImage(cardBack, NULL,NULL);
    pRet->autorelease();
    pRet->setEnabled(false);
    
    return pRet;
}

MyShopCard* MyShopCard::create(const std::string &nameStr,int count,int resourceTag,int cost,int mode,int displayLevel,CCObject* rec) {
    MyShopCard *pRet = new MyShopCard();
    
    pRet->mode = mode;
    CCSprite* cardBack = CCSprite::createWithSpriteFrameName("shopCardBack.png");
    cardBack->setScaleX(420/cardBack->getContentSize().width);
    cardBack->setScaleY(190/cardBack->getContentSize().height);
    cardBack->setContentSize(CCSizeMake(420, 190));
    
    if (mode == hotMode) {
        CCSprite* hotBack = CCSprite::createWithSpriteFrameName("shopHotBack.png");
        hotBack->setScale(0.5);
        hotBack->setAnchorPoint(ccp(0,1));
        hotBack->setPosition(ccp(0,95));
        hotBack->setColor(ccc3(183,57,3));
        cardBack->addChild(hotBack);
        
        CCSprite* hotLabel = CCSprite::createWithSpriteFrameName("shopHotLabel.png");
        hotLabel->setAnchorPoint(ccp(0,1));
        hotLabel->setPosition(ccp(3,hotBack->getContentSize().height-3));
        hotBack->addChild(hotLabel);
    } else if(mode == newMode) {
        CCSprite* newBack = CCSprite::createWithSpriteFrameName("shopHotBack.png");
        newBack->setScale(0.5);
        newBack->setAnchorPoint(ccp(0,1));
        newBack->setPosition(ccp(0,95));
        newBack->setColor(ccc3(3,183,57));
        cardBack->addChild(newBack);
        
        CCSprite* newLabel = CCSprite::createWithSpriteFrameName("shopNewLabel.png");
        newLabel->setAnchorPoint(ccp(0,1));
        newLabel->setPosition(ccp(3,newBack->getContentSize().height-3));
        newBack->addChild(newLabel);
    }
    
    
    CCSprite* lightSprite = CCSprite::createWithSpriteFrameName("creatorLight.png");
    lightSprite->setScale(0.4);
    lightSprite->setOpacity(153);
    lightSprite->setPosition(ccp(50,55));
    cardBack->addChild(lightSprite);
    
    CCNode* bp = MyGameFactory::getShopResourceIcon(resourceTag,displayLevel);
    
    bp->setPosition(ccp(55,47));
    cardBack->addChild(bp);
    
//    avatarSprite->setPosition(ccp(55,47));
//    avatarSprite->setScale(Mathlib::min(165/avatarSprite->getContentSize().width,134/avatarSprite->getContentSize().height)*0.5);
//    cardBack->addChild(avatarSprite);
    
    
    CCLabelTTF* name = CCLabelTTF::create(nameStr.c_str(),"Arial",36);
    name->setPosition(ccp(145,78));
    name->setColor(ccc3(255,224,122));
    name->setScale(0.5);
    cardBack->addChild(name);
    
    CCSprite* diamond = CCSprite::createWithSpriteFrameName("diamond.png");
    diamond->setScale(0.5);
    diamond->setPosition(ccp(120,59));
    cardBack->addChild(diamond);
    
    //诡异的购买按钮
    CCSprite* boughtLabel1 = CCSprite::createWithSpriteFrameName("shopBoughtLabel_2.png");
    CCSprite* shopPurchaseButton = CCSprite::createWithSpriteFrameName("shopEmptyButton.png");
    boughtLabel1->setPosition(ccp(shopPurchaseButton->getContentSize().width/2,shopPurchaseButton->getContentSize().height/2+3));
    shopPurchaseButton->addChild(boughtLabel1);
    
    
    CCSprite* boughtLabel2 = CCSprite::createWithSpriteFrameName("shopBoughtLabel_2.png");
    CCSprite* shopPurchaseButtonP = CCSprite::createWithSpriteFrameName("shopEmptyButtonP.png");
    boughtLabel2->setPosition(ccp(shopPurchaseButtonP->getContentSize().width/2,shopPurchaseButtonP->getContentSize().height/2+3));
    shopPurchaseButtonP->addChild(boughtLabel2);
    
    CCSprite* alreadyBought = CCSprite::createWithSpriteFrameName("shopBoughtLabel.png");
    CCSprite* boughtLabel = CCSprite::createWithSpriteFrameName("shopBoughtLabel_2.png");
    alreadyBought->setAnchorPoint(ccp(1,0));
    alreadyBought->setPosition(ccp(4,1));
    boughtLabel->addChild(alreadyBought);
    
    
    CCMenuItemSprite* purchaseItem = CCMenuItemSprite::create(shopPurchaseButton,shopPurchaseButtonP,boughtLabel,rec,menu_selector(StartScene::toBuyResource));

    boughtLabel->setPosition(ccp(53,15));
    purchaseItem->setUserData(pRet);
    purchaseItem->setScale(0.5);
    pRet->buyItem = purchaseItem;
    //    purchaseItem->setContentSize(CCSizeMake(purchaseItem->getContentSize().width/2,purchaseItem->getContentSize().height/2));
    
    MyPriorityMenu* menu = MyPriorityMenu::create(-508,purchaseItem,NULL);
    menu->setPosition(ccp(145,22));
    cardBack->addChild(menu);
    char str[50] = {0};
    sprintf(str,"%s",nameStr.c_str());
    pRet->bean = ShopResourceBean::create(CCString::create(str),count,resourceTag,cost,displayLevel);
    pRet->bean->retain();
    
    
    sprintf(str,"%d",cost);
    CCLabelAtlas* costLabel = CCLabelAtlas::create(str, "number6.png", 24, 36, '/');
    costLabel->setPosition(ccp(155,55));
    costLabel->setAnchorPoint(ccp(0.5,0.5));
    costLabel->setColor(ccc3(255,224,122));
    costLabel->setScale(0.5);
    cardBack->addChild(costLabel);
    
    pRet->initWithImage(cardBack, NULL,NULL);
    pRet->autorelease();
    pRet->setEnabled(false);
    
    return pRet;
}

MyShopCard* MyShopCard::create(int countNum,float oriCost,float costNum,CCObject* rec,int position) {
    MyShopCard *pRet = new MyShopCard();
    CCSprite* cardBack = CCSprite::createWithSpriteFrameName("shopCardBack.png");
    cardBack->setScaleX(850/cardBack->getContentSize().width);
    cardBack->setScaleY(85/cardBack->getContentSize().height);
    cardBack->setContentSize(CCSizeMake(850, 85));
    

    
    
    
//    CCSprite* lightSprite = CCSprite::createWithSpriteFrameName("creatorLight.png");
//    lightSprite->setScale(0.4);
//    lightSprite->setOpacity(153);
//    lightSprite->setPosition(ccp(50,55));
//    cardBack->addChild(lightSprite);
    
    
//
    
//
    
    pRet->initWithImage(cardBack, NULL,NULL);
    pRet->autorelease();
    pRet->setEnabled(false);
    
    
    CCSprite* cardleft = CCSprite::createWithSpriteFrameName("shopCardBack.png");
    if (cardleft->isTextureRectRotated()) {
        CCRect  rect = cardleft->getTextureRect();
        cardleft->setTextureRect(CCRectMake(rect.origin.x,rect.origin.y,rect.size.width,50),cardleft->isTextureRectRotated() , CCSizeMake(50,cardleft->getContentSize().height));
    } else {
        CCRect  rect = cardleft->getTextureRect();
        cardleft->setTextureRect(CCRectMake(rect.origin.x,rect.origin.y,50,rect.size.height),cardleft->isTextureRectRotated() , CCSizeMake(50,cardleft->getContentSize().height));
    }

    cardleft->setScaleY(85/cardleft->getContentSize().height);
    cardleft->setAnchorPoint(ccp(0,0));
    pRet->addChild(cardleft);
    
    CCSprite* cardright = CCSprite::createWithSpriteFrameName("shopCardBack.png");
    if (cardright->isTextureRectRotated()) {
        CCRect  rect = cardright->getTextureRect();
        cardright->setTextureRect(CCRectMake(rect.origin.x,rect.origin.y,rect.size.width,50),cardleft->isTextureRectRotated() , CCSizeMake(50,cardright->getContentSize().height));
    } else {
        CCRect  rect = cardright->getTextureRect();
        cardright->setTextureRect(CCRectMake(rect.origin.x,rect.origin.y,50,rect.size.height),cardright->isTextureRectRotated() , CCSizeMake(50,cardright->getContentSize().height));
    }
    
    cardright->setScaleY(85/cardright->getContentSize().height);
    cardright->setAnchorPoint(ccp(1,0));
    cardright->setFlipX(true);
    cardright->setPosition(ccp(pRet->getContentSize().width,0));
    pRet->addChild(cardright);
    
    CCSprite* diamond = CCSprite::createWithSpriteFrameName("diamond.png");
    diamond->setPosition(ccp(50,45));
    diamond->setScale(1.2);
    pRet->addChild(diamond);
    
    CCMenuItemSprite* purchaseItem = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("shopEmptyButton.png"),CCSprite::createWithSpriteFrameName("shopEmptyButtonP.png"),rec,menu_selector(StartScene::toChargeCallBack));
    purchaseItem->setUserData((void*)position);

    //    purchaseItem->setContentSize(CCSizeMake(purchaseItem->getContentSize().width/2,purchaseItem->getContentSize().height/2));
    
    MyPriorityMenu* menu = MyPriorityMenu::create(-508,purchaseItem,NULL);
    menu->setPosition(ccp(750,37));
    pRet->addChild(menu);

    char str[50] = {0};
    
    
    
    CCLabelTTF* name = CCLabelTTF::create("钻石","Arial",32);
    name->setPosition(ccp(80,42.5));
    name->setAnchorPoint(ccp(0,0.5));
    name->setColor(ccc3(255,224,122));
    pRet->addChild(name);
    
    sprintf(str,"%d",countNum);
    CCLabelAtlas* count = CCLabelAtlas::create(str, "number6.png", 24, 36, '/');
    count->setPosition(ccp(80+name->getContentSize().width,42.5));
    count->setAnchorPoint(ccp(0,0.5));
    count->setColor(ccc3(255,224,122));
    pRet->addChild(count);
    
    
    if (oriCost>costNum) {
        
        
        CCLabelTTF* giftName = CCLabelTTF::create("原价:￥","Arial",30);
        giftName->setPosition(ccp(280,42.5));
        giftName->setAnchorPoint(ccp(0,0.5));
        pRet->addChild(giftName);
        
        sprintf(str,"%d",(int)oriCost);
        CCLabelAtlas* giftCount = CCLabelAtlas::create(str, "number6.png", 24, 36, '/');
        giftCount->setPosition(ccp(325+giftName->getContentSize().width,42.5));
        giftCount->setAnchorPoint(ccp(0.5,0.5));
        pRet->addChild(giftCount);
        
        float per = ((oriCost-costNum)/(costNum));
        sprintf(str,"优惠:%%%d",(int)((per+0.001)*100));
        CCLabelTTF* totalCount = CCLabelTTF::create(str, "Arial", 30);
        totalCount->setPosition(ccp(580,42.5));
        totalCount->setAnchorPoint(ccp(0.5,0.5));
        totalCount->setColor(ccc3(255,133,80));
        pRet->addChild(totalCount);
        
        GXLineSprite* line = GXLineSprite::create(ccp(140,20),ccp(275+giftCount->getContentSize().width/1.5,31));
        pRet->addChild(line);
        
    }
    CCLabelTTF* costName = CCLabelTTF::create("￥","Arial",40);
    costName->setPosition(ccp(50,purchaseItem->getContentSize().height/2));
    costName->setAnchorPoint(ccp(0.5,0.5));
//    costName->setColor(ccc3(255,80,80));
    purchaseItem->addChild(costName);
    
    sprintf(str,"%d",(int)costNum);
    CCLabelAtlas* costCount = CCLabelAtlas::create(str, "number6.png", 24, 36, '/');
    costCount->setPosition(ccp(purchaseItem->getContentSize().width/2+10,purchaseItem->getContentSize().height/2+4));
    costCount->setAnchorPoint(ccp(0.5,0.5));
//    costCount->setColor(ccc3(255,80,80));
    purchaseItem->addChild(costCount);
    
    costName->setPosition(ccp(purchaseItem->getContentSize().width/2-costCount->getContentSize().width/2,purchaseItem->getContentSize().height/2));
    
    return pRet;
}

void MyShopCard::setBoughtInfo(bool isbought) {
    buyItem->setEnabled(isbought);
}

ShopResourceBean* ShopResourceBean::create(CCString* _name,int _count,int _resourceTag,int _cost,int _displayLevel){
    ShopResourceBean* bean = new ShopResourceBean();
    bean->autorelease();
    bean->name = _name;
    bean->name->retain();
    bean->setCount(_count);
    bean->setResourceTag(_resourceTag);
    bean->setCost(_cost);
//    bean->resourceTag = _resourceTag;
//    bean->cost = _cost;
    bean->displayLevel = _displayLevel;
    return bean;
}