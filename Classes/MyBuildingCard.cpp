//
//  MyBuildingCard.cpp
//  ww2
//
//  Created by xiao tang on 12-10-10.
//
//

#define grayTag 10
#define detailBackTag 11
#define lockTag 12
#define blackTag 13

#include "MyBuildingCard.h"
#include "DefineSet.h"
#include "MyPriorityMenu.h"
#include "GXScrollView.h"
#include "GXRemoveFromParentsAction.h"
#include "MyUtil.h"
#include "MyGameInfo.h"


MyBuildingCard* MyBuildingCard::activeCard = NULL;

MyBuildingCard* MyBuildingCard::create(CCSprite* buildingSprite,int cardId, int maxCount,int count, int _resourceTag, int _summaryCount, const char *name, cocos2d::CCObject *rec, SEL_MenuHandler selector) {
    
    MyBuildingCard *pRet = new MyBuildingCard();
    CCSprite* sprite = CCSprite::createWithSpriteFrameName("armycardback.png");
    sprite->setPosition(ccp(0,-32));
    sprite->setScale(210/sprite->getContentSize().width);
    sprite->setContentSize(CCSizeMake(210, 246));
    
    pRet->initWithImage(sprite, rec, selector);
    pRet->autorelease();

    pRet->init(buildingSprite,cardId, maxCount, count, _resourceTag, _summaryCount, name,0);
    return pRet;
}

MyBuildingCard* MyBuildingCard::create(CCSprite* buildingSprite,int cardId, int maxCount,int count, int _resourceTag, int _summaryCount,int unlockLevel,const char *name, cocos2d::CCObject *rec, SEL_MenuHandler selector) {
    
    MyBuildingCard *pRet = new MyBuildingCard();
    CCSprite* sprite = CCSprite::createWithSpriteFrameName("armycardback.png");
    sprite->setPosition(ccp(0,-32));
    sprite->setScale(210/sprite->getContentSize().width);
    sprite->setContentSize(CCSizeMake(210, 246));
    
    pRet->initWithImage(sprite, rec, selector);
    pRet->autorelease();
    
    pRet->init(buildingSprite,cardId, maxCount, count, _resourceTag, _summaryCount, name,unlockLevel);
    return pRet;
}

void MyBuildingCard::init(CCSprite* buildingSprite,int cardId, int maxCount,int count, int _resourceTag, int _summaryCount, const char *name,int unlockLevel) {
    this->cardId = cardId;
    this->setTag(cardId);
    this->maxCount = maxCount;
    this->count = count;
    this->resourceTag->setValue(_resourceTag);
    this->summaryCount->setValue(_summaryCount);
    this->setUnlockLevel(unlockLevel);
    this->name = name;
//    CCLabelTTF* nameLabel =
    int level = MyUtil::getInstance()->getLevelByExperience(MyGameInfo::getInstance()->getExperience());
    buildingSprite->setPosition(ccp(this->itemImage->getContentSize().width/2,itemImage->getContentSize().height/2 +24));
    CCSprite* lightSprite = CCSprite::createWithSpriteFrameName("creatorLight.png");
    lightSprite->setScale(0.8);
    lightSprite->setOpacity(153);
    lightSprite->setPosition(ccp(this->getContentSize().width/2,this->getContentSize().height-this->getContentSize().width/2));
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
    CCSprite* resourceIcon = MyUtil::getInstance()->getResourceIcon(getResourceTag());
    resourceIcon->setScale(32/resourceIcon->getContentSize().height);
    resourceIcon->setPosition(ccp(55,38));
    this->addChild(resourceIcon,2);
    sprintf(str,"%d", getSummaryCount());
    CCLabelTTF* summaryLabel = CCLabelTTF::create(str, "Arial", 28);
    summaryLabel->setColor(ccc3(254,241,158));
    summaryLabel->setPosition(ccp(this->getContentSize().width/2+13,38));
    summaryLabel->setAnchorPoint(ccp(0.5,0.5));
    this->addChild(summaryLabel);
//    }
//    if (_summaryIron != 0) {
//        CCSprite* ironIcon = CCSprite::createWithSpriteFrameName("ironIcon.png");
//        ironIcon->setScale(0.6);
//        ironIcon->setPosition(ccp(55,38));
//        this->addChild(ironIcon,2);
//        sprintf(str,"%d", _summaryIron);
//        CCLabelTTF* ironLabel = CCLabelTTF::create(str, "Arial", 28);
//        ironLabel->setColor(ccc3(254,241,158));
//        ironLabel->setPosition(ccp(this->getContentSize().width/2+13,38));
//        ironLabel->setAnchorPoint(ccp(0.5,0.5));
//        this->addChild(ironLabel,2);
//    }
    CCSprite* up =  CCSprite::createWithSpriteFrameName("creatordetail.png");
    up->setScaleX(0.88);
    
    CCSprite* down = CCSprite::createWithSpriteFrameName("creatordetail.png");
    down->setScaleX(0.88);
    CCMenuItemSprite* detailButton = CCMenuItemSprite::create(up,down);
    detailButton->setScale(0.8);
    
    detailButton->setPosition(ccp(175,68));
    MyPriorityMenu* menu = MyPriorityMenu::create(-503,detailButton,NULL);
    menu->setPosition(ccp(0,0)),
    this->addChild(menu,3);
    this->addChild(buildingSprite,2);
    this->addChild(lightSprite,1);
    this->addChild(idLabel,2);
    this->addChild(nameLabel,2);
    
    if (level < unlockLevel) {
        CCSprite* black = CCSprite::create("whiteImage.jpg");
        black->setColor(ccc3(0,0,0));
        black->setScaleX(210/black->getContentSize().width);
        black->setScaleY(246/black->getContentSize().height);
        black->setPosition(ccp(210/2,246/2+2));
        black->setOpacity(130);
        black->setTag(blackTag);
        this->addChild(black,20);
        
        CCSprite* lock = CCSprite::create("lock.png");
        lock->setPosition(ccp(40,80));
        lock->setOpacity(180);
        lock->setTag(lockTag);
        this->addChild(lock,20);
        //    buildingSprite->setScale((itemImage->getContentSize().width-transWindowToGLInRetina(20))/buildingSprite->getContentSize().width);
        
        
        
       
        
        //    CCSprite* militrayIcon = CCSprite::createWithSpriteFrameName("militaryIcon.png");
        //    militrayIcon->setPosition(ccp(itemImage->getContentSize().width/2 +40,94));
        //    militrayIcon->setScale(0.45f);
        
        //    sprintf(str,"%d", summaryMilitary);
        //    CCLabelTTF* militaryLabel = CCLabelTTF::create(str, "Arial", 30);
        //    militaryLabel->setPosition(ccp(itemImage->getContentSize().width/2 +60,94));
        //    militaryLabel->setAnchorPoint(ccp(0,0.5));
        //    militaryLabel->setColor(ccc3(114,66,45));
        
        //    CCMenuItemSprite* sprite = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("creatorquitp.png"), CCSprite::createWithSpriteFrameName("creatorquit.png"),this, menu_selector(MyBuildingCard::displayDetail));
        
    }
    if (maxCount > 0) {
        sprintf(str,"%d/%d",count,maxCount);
        CCLabelTTF* countLabel = CCLabelTTF::create(str,"Arial",20);
        countLabel->setPosition(ccp(175,this->getContentSize().height-57));
//        countLabel->setPosition()
        this->addChild(countLabel,20);
    }
    
    
    
//    this->addChild(militrayIcon);
//    this->addChild(militaryLabel);
    
}

void MyBuildingCard::displayDetail(cocos2d::CCNode *psender){
    MyBuildingCard* card = (MyBuildingCard*)psender->getParent()->getParent();
    activeCard = card;
    oriPosition = card->getPosition();
    card->runAction(CCEaseInOut::create(CCMoveTo::create(0.2, ccp(200-card->getParent()->getPosition().x,320)),2));
    card->runAction(CCEaseInOut::create(CCScaleTo::create(0.2, 1.2),2));
    card->isEnabled = false;
    ((GXScrollView*)(card->getParent()))->setEnabled(false);
    card->getParent()->reorderChild(card, 100000);
    CCMenuItemSprite* gray = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("dialoggray.png"), CCSprite::createWithSpriteFrameName("dialoggray.png"));
    MyPriorityMenu* grayMenu = MyPriorityMenu::create(-503,gray,NULL);
    grayMenu->setTag(grayTag);
    card->getParent()->addChild(grayMenu,99999);
    gray->setScaleX(960/gray->getContentSize().width);
    gray->setScaleY(540/gray->getContentSize().height);
    grayMenu->setPosition(ccp(480-card->getParent()->getPosition().x,320));
//    gray->setPosition(ccp(0,0));
    
    CCSprite* detailBack = CCSprite::createWithSpriteFrameName("creatoruidetail.jpg");    detailBack->setPosition(ccp(634-card->getParent()->getPosition().x,-detailBack->getContentSize().height/2-100));
    detailBack->setScale(1.2);
    detailBack->setTag(detailBackTag);
    card->getParent()->addChild(detailBack,100000);
    detailBack->runAction(CCSequence::create(CCDelayTime::create(0.2),CCEaseInOut::create(CCMoveTo::create(0.2, ccp(634-card->getParent()->getPosition().x,320)),2), NULL));
    CCMenuItemFont::setFontSize(24);
    CCMenuItemFont* back = CCMenuItemFont::create("返回",this,menu_selector(MyBuildingCard::cancelDetail));
    back->setColor(ccc3(114,66,45));
    MyPriorityMenu* backMenu = MyPriorityMenu::create(-503,back,NULL);
    backMenu->setPosition(ccp(detailBack->getContentSize().width-44,44));
    detailBack->addChild(backMenu,NULL);
}

void MyBuildingCard::selected() {
    if (isEnabled) {
        MyMenuItem::selected();
    } else {
        m_bSelected = true;
    }
}

void MyBuildingCard::unselected() {
    if (isEnabled) {
        MyMenuItem::unselected();
    } else {
        m_bSelected = false;
    }
}


void MyBuildingCard::activate() {
    MyMenuItem::activate();
}

void MyBuildingCard::cancelDetail(cocos2d::CCNode *psender) {
    CCSprite* detailback = (CCSprite*)activeCard->getParent()->getChildByTag(detailBackTag);
    detailback->runAction(CCSequence::create(CCEaseInOut::create(CCMoveTo::create(0.2, ccp(detailback->getPosition().x,-detailback->getContentSize().height/2-100)),2),GXRemoveFromParentsAction::create(), NULL));
    
    
    activeCard->runAction(CCSequence::create(CCDelayTime::create(0.2),CCEaseInOut::create(CCScaleTo::create(0.2, 1),2),NULL));
    activeCard->runAction(CCSequence::create(CCDelayTime::create(0.2),CCEaseInOut::create(CCMoveTo::create(0.2, oriPosition),2),CCCallFunc::create(this,callfunc_selector(MyBuildingCard::reorderCall)),NULL));
    CCMenu* grayMenu = (CCMenu*)activeCard->getParent()->getChildByTag(grayTag);
    grayMenu->runAction(CCSequence::create(CCDelayTime::create(0.2),CCFadeOut::create(0.2),GXRemoveFromParentsAction::create(),NULL));
    
    
    
}

void MyBuildingCard::reorderCall() {
    GXScrollView* scrol = (GXScrollView*)activeCard->getParent();
    scrol->setEnabled(true);
    scrol->reorderChild(activeCard, 0);
    detailButton->setSelectedIndex(0);
}

void MyBuildingCard::toggleDetail(cocos2d::CCNode *pSender) {
    CCMenuItemToggle* toggle = ((CCMenuItemToggle*)pSender);
    if(toggle->getSelectedIndex() == 1) {
        displayDetail(pSender);
    } else {
        cancelDetail(pSender);
    }
}

//void MyBuildingCard::setSummaryIron(int _summaryIron) {
//    summaryIron->setValue(_summaryIron);
//}

int MyBuildingCard::getResourceTag() {
    return resourceTag->getValue();
}
//
//void MyBuildingCard::setSummaryOil(int _summaryOil) {
//    summaryOil->setValue(_summaryOil);
//};
int MyBuildingCard::getSummaryCount() {
    return summaryCount->getValue();
}

void MyBuildingCard::setUnlockLevel(int _unlockLevel) {
    unlockLevel->setValue(_unlockLevel);
};
int MyBuildingCard::getUnlockLevel() {
    return unlockLevel->getValue();
}


CCObject* MyBuildingCardCreator::init() {
    
    return NULL;
}

void MyBuildingCardCreator::doFill(CCObject* entity) {
    
}

