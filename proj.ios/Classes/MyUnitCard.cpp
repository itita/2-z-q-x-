//
//  MyUnitCard.cpp
//  ww3
//
//  Created by xiao tang on 12-11-13.
//
//
//#define lvFontTag 102
//#define levelFontTag 103

#include "MyUnitCard.h"
#include "DefineSet.h"
#include "MyGameFactory.h"
#include "MyGameInfo.h"
#include "MyPriorityMenu.h"
#include "MyUtil.h"
#include "Mathlib.h"
#include "SimpleAudioEngine.h"

MyUnitCard* MyUnitCard::create(CreatorInfoBean* _bean,cocos2d::CCObject *rec, SEL_MenuHandler selector) {

    MyUnitCard *pRet = new MyUnitCard();
    CCSprite* sprite = CCSprite::createWithSpriteFrameName("armycardback.png");
    sprite->setPosition(ccp(0,-32));
    sprite->setScale(210/sprite->getContentSize().width);
    sprite->setContentSize(CCSizeMake(210, 246));
    pRet->initWithImage(sprite, rec, selector);
//    pRet->addChild(pRet->itemImage);
    pRet->autorelease();
    pRet->bean = _bean;
    _bean->retain();
    char str[30] = {0};
    sprintf(str, "%sbp.png",_bean->creator->getSpriteFileName());
    pRet->init(CCSprite::createWithSpriteFrameName(str),_bean->creator->cardId, 10, oilTag, 100, _bean->creator->getName());
    return pRet;
}

void MyUnitCard::init(cocos2d::CCSprite *unitSprite, int cardId, int count, int resourceTag, int summaryCount, const char *name) {
    this->cardId = cardId;
    this->setTag(cardId);
    this->count = count;
    this->resourceTag = resourceTag;
    this->summaryCount = summaryCount;
    this->name = name;
    //    CCLabelTTF* nameLabel =
    
    
    unitSprite->setPosition(ccp(this->getContentSize().width/2,this->getContentSize().height-this->getContentSize().width/2));
    unitSprite->setScale(Mathlib::min(180/unitSprite->getContentSize().width, 130/unitSprite->getContentSize().height));
    unitSprite->setTag(unitSpriteTag);
//    unitSprite->setAnchorPoint(ccp(0,0));
    CCSprite* lightSprite = CCSprite::createWithSpriteFrameName("creatorLight.png");
    lightSprite->setScale(0.8);
    lightSprite->setOpacity(153);
//    lightSprite->setAnchorPoint(ccp(0,0));
    lightSprite->setPosition(ccp(this->getContentSize().width/2,this->getContentSize().height-this->getContentSize().width/2));
    //    buildingSprite->setScale((itemImage->getContentSize().width-transWindowToGLInRetina(20))/buildingSprite->getContentSize().width);
    
    CCLabelTTF* nameLabel = CCLabelTTF::create(name, "Arial", 22);
    nameLabel->setPosition(ccp(134,this->getContentSize().height-30));
    nameLabel->setAnchorPoint(ccp(0.5,0.5));
    nameLabel->setColor(ccWHITE);
    
    
    
    char str[10] = {0};
    sprintf(str,"No.%d", cardId);
    
    CCLabelTTF* idLabel = CCLabelTTF::create(str, "Arial", 19);
    idLabel->setPosition(ccp(10,this->getContentSize().height-15));
    idLabel->setAnchorPoint(ccp(0,0.5));
    idLabel->setColor(ccBLACK);
    
    sprintf(str,"Lv:%d", bean->getLevel());
    
    CCLabelTTF* levelLabel = CCLabelTTF::create(str, "Arial", 25);
    levelLabel->setPosition(ccp(10,this->getContentSize().height - this->getContentSize().width+20));
    levelLabel->setAnchorPoint(ccp(0,0));
    levelLabel->setColor(ccWHITE);
    levelLabel->setTag(lvFontTag);
   
    this->addChild(lightSprite,1);
    this->addChild(unitSprite,3);
    this->addChild(idLabel,2);
    this->addChild(nameLabel,2);
    this->addChild(levelLabel,2);
    
    float posi = (bean->creator->getRarity()-1)*30;
    for (int i = 0; i<bean->creator->getRarity(); i++) {
        CCSprite* star = CCSprite::createWithSpriteFrameName("armystar.png");
        star->setPosition(ccp(this->getContentSize().width/2-posi/2 + i*30,40));
        this->addChild(star);
    }
}

//void MyUnitCard::displayDetail(cocos2d::CCNode *psender){
//    int maxLevel = bean->creator->getMaxLevel();
//    this->getParent()->getParent()-> removeChildByTag(unitDescrptionTag, true);
//    CCLayer* layer = CCLayer::create();
//    layer->setTag(unitDescrptionTag);
//    char str[10] = {0};
//    sprintf(str, "No.%d",cardId);
//    
//    CCSprite* blink = CCSprite::createWithSpriteFrameName("creatorLight.png");
//    blink->setPosition(ccp(-204,110));
//    blink->setScale(0.5);
//    layer->addChild(blink,-1);
//    
//    CCLabelTTF* NoLabel = CCLabelTTF::create(str, "Arial", 16);
//    NoLabel->setColor(ccc3(114,66,45));
//    NoLabel->setAnchorPoint(ccp(0,0.5));
//    NoLabel->setPosition(ccp(-280,192));
//    
//    CCSprite* image =  CCSprite::createWithTexture(((CCSprite*)this->getChildByTag(unitSpriteTag))->getTexture());
//    image->setPosition(ccp(-204,110));
//    image->setScale(68/image->getContentSize().width);
//    layer->addChild(image);
//    
//    sprintf(str, "等级 %d",bean->getLevel());
//    CCLabelTTF* levelLabel = CCLabelTTF::create(str, "Arial", 24);
//    levelLabel->setColor(ccc3(114,66,45));
//    levelLabel->setAnchorPoint(ccp(0.5,0.5));
//    levelLabel->setPosition(ccp(-198,42));
//    levelLabel->setTag(levelFontTag);
//    layer->addChild(levelLabel);
// 
//    if (bean->getLevel()< maxLevel) {
//        CCMenuItemSprite* updateButton = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("updateButton.png"), CCSprite::createWithSpriteFrameName("updateButtonP.png"),this,menu_selector(MyUnitCard::updateCallBack));
//        updateButton->setPosition(ccp(0,-130));
//        
//        MyPriorityMenu* menu = MyPriorityMenu::create(-503,updateButton,NULL);
//        menu->setPosition(ccp(0,0));
//        layer->addChild(menu);
//        
//        if (resourceTag == oilTag) {
//            CCSprite* resourceIcon = CCSprite::createWithSpriteFrameName("oilIcon.png");
//            resourceIcon->setScale(0.4);
//            resourceIcon->setPosition(ccp(-40,-168));
//            layer->addChild(resourceIcon);
//        } else {
//            CCSprite* resourceIcon = CCSprite::createWithSpriteFrameName("ironIcon.png");
//            resourceIcon->setScale(0.4);
//            resourceIcon->setPosition(ccp(-40,-168));
//            layer->addChild(resourceIcon);
//        }
//        
//        sprintf(str, "%d",(int)MyUtil::getInstance()->updateLevelBySquare(summaryCount, bean->getLevel(), updateSummaryRate));
//        CCLabelTTF* summaryResourceCount = CCLabelTTF::create(str, "Arial", 24);
//        summaryResourceCount->setColor(ccc3(114, 66,45));
//        summaryResourceCount->setAnchorPoint(ccp(0.5,0.5));
//        
//        summaryResourceCount->setPosition(ccp(Mathlib::max(summaryResourceCount->getContentSize().width/2-28, 4),-168) );
//        layer->addChild(summaryResourceCount);
//        
//    } else {
//        CCLabelTTF* maxLeveltip = CCLabelTTF::create("已达到最大等级", "Arial", 24);
//        maxLeveltip->setColor(ccc3(114, 66,45));
//        maxLeveltip->setPosition(ccp(0,-160));
//        layer->addChild(maxLeveltip);
//    }
//    layer->addChild(NoLabel);
//    layer->setPosition(ccp(620,280));
//    this->getParent()->getParent()->addChild(layer);
//}

void MyUnitCard::updateCallBack(cocos2d::CCNode *pSender) {
    float  summaryFinalCount = MyUtil::getInstance()->updateLevelBySquare(summaryCount, bean->getLevel(), updateSummaryRate);
    if (MyGameInfo::getInstance()->getResource(resourceTag) >= summaryFinalCount ) {
        setLevel(bean->getLevel()+1);
        
        MyGameInfo::getInstance()->changeResource(resourceTag, summaryFinalCount*-1);
        
        CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sfx_updateBuilding.mp3");
        CCLabelTTF* levelFont = dynamic_cast<CCLabelTTF*>(this->getChildByTag(lvFontTag));

//        CCLog("%f,%f",levelFont->getPosition().x,levelFont->getPosition().y);
//        float x = levelFont->getPosition().x;
//        float y = levelFont->getPosition().y;
        char str[5] = {0};
        sprintf(str, "lv:%d",bean->getLevel());
        levelFont->setString(str);
//        CCMenuItemFont::setFontSize(transWindowToGLInRetina(9));
//        CCMenuItemFont::setFontName("Arial");
//        CCMenuItemFont* levelFont2 = CCMenuItemFont::create(str);
//        levelFont2->setPosition(ccp(x,y));
//        levelFont2->setTag(levelFontTag);
//        this->addChild(levelFont2,1000000);
//        levelFont->removeFromParentAndCleanup(true);
    } else {
        this->getParent()->getParent()->addChild(MyUtil::getInstance()->getNoResourceDialog(this->getParent()->getParent()->getParent(),resourceTag),99);
    }
//    this->displayDetail(pSender);
}

void MyUnitCard::setLevel(int level) {
//    this->level = level;
//    if (cardId == tankCreatorTag) {
        //TODO CREATOR_LEVEL
//        MyGameInfo::getInstance()->tankLevel = level;
//    } else if(cardId == bubingCreatorTag) {
        //TODO CREATOR_LEVEL
//        MyGameInfo::getInstance()->bubingLevel = level;
//    }
    
}
int MyUnitCard::getLevel() {
    return bean->getLevel();
}

