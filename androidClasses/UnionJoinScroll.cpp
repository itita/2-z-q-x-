//
//  UnionJoinScroll.cpp
//  ww4
//
//  Created by xiao tang on 13-3-26.
//
//

#define offsetX pTouch->getLocationInView().x - pTouch->getPreviousLocationInView().x
#define offsetY pTouch->getPreviousLocationInView().y - pTouch->getLocationInView().y
#define positionX this->getPosition().x
#define positionY this->getPosition().y
#define dividingLengthBase 300

#include "UnionJoinScroll.h"
#include "MyGameInfo.h"
#include "Mathlib.h"




UnionJoinScroll* UnionJoinScroll::create(int _priority,CCArray* unionArray) {
    UnionJoinScroll* pRet = new UnionJoinScroll();
    pRet->layerArray = CCArray::create();
    pRet->layerArray->retain();
    pRet->descArray = CCArray::create();
    pRet->descArray->retain();
    pRet->dividingLength = dividingLengthBase*(winSize.width/960);
    if (pRet && pRet->init(unionArray))
    {
        pRet->priority = _priority;
        pRet->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(pRet);
    }
    return pRet;
}

bool UnionJoinScroll::init(CCArray* unionArray) {
    CCLayer::init();
    this->setTouchEnabled(true);
    setContentSize(CCSizeMake(winSize.width, winSize.height-50));
    setMapSize(CCSizeMake(dividingLength*(unionArray->count()+2)+50, 505));
    CCObject* obj;
    int i=1;
    char str[50] = {0};
    idArray = unionArray;
    idArray->retain();
    CCARRAY_FOREACH(unionArray,obj) {
        UnionBean* bean = (UnionBean*)obj;
        CCSprite* emblem = CCSprite::createWithSpriteFrameName(bean->getEmblem()->getCString());
        emblem->setPosition(ccp(0,420));
        emblem->setScale(1.4);
        sprintf(str,"『%s』",bean->getName()->getCString());
        CCLabelTTF* name = CCLabelTTF::create(str,"Arial",24);
        name->setPosition(ccp(emblem->getContentSize().width/2,emblem->getContentSize().height/2-90));
        name->setColor(ccc3(240,147,1));
        
//        tempLayer->addChild(emblem);
        emblem->addChild(name);
        emblem->setPosition(ccp(175+dividingLength*i,420));
        layerArray->addObject(emblem);
        
        CCLayer* infoLayer = CCLayer::create();
        infoLayer->setPosition(ccp(0,0));
        CCLabelTTF* descLabel = CCLabelTTF::create(bean->getDesc()->getCString(),"Arial",30);
        descLabel->setPosition(ccp(winSize.width/2,80));
        descLabel->setColor(ccc3(230, 207, 185));
        
        
        sprintf(str,"%d",bean->level);
        CCLabelAtlas* levelLabel1 = CCLabelAtlas::create(str, "levelupnumber.png", 40, 32, '0');
        levelLabel1->setAnchorPoint(ccp(0.5,0.5));
        levelLabel1->setScaleY(1.2);
        levelLabel1->setOpacity(0);
        levelLabel1->setPosition(ccp(winSize.width/2-139,139));
        levelLabel1->setTag(1);
        
        sprintf(str,"%d/25",bean->memberCount);
        CCLabelTTF* memberLabel = CCLabelTTF::create(str,"Arial",40);
        memberLabel->setColor(ccc3(253,203,1));
        memberLabel->setScaleY(1.2);
        memberLabel->setOpacity(0);
        memberLabel->setPosition(ccp(winSize.width/2+189.5,139));
        
        infoLayer->addChild(descLabel);
        infoLayer->addChild(levelLabel1);
        infoLayer->addChild(memberLabel);
        descArray->addObject(infoLayer);
//        tempLayer->setScale(2);
        this->addChild(emblem);
        i++;
    }
    int count = unionArray->count();
    CCLog("%f",-1*(count/2)*dividingLength+winSize.width/2);
    setOriPosition(ccp(0,0));
    setPosition(ccp(-1*(count/2+1.5)*dividingLength+winSize.width/2,0));
    return true;
}

void UnionJoinScroll::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent) {
    CCLayer::ccTouchMoved(pTouch,pEvent);
    if (isEnabled) {
        
        CCPoint lastLoc = this->getPosition();
        this->setPosition(ccp(Mathlib::bound(positionX + offsetX,
                                             oriPosition.x,
                                             viewSize.width-mapSize.width+oriPosition.x),
                              Mathlib::bound(positionY + offsetY,
                                             oriPosition.y,
                                             viewSize.height-mapSize.height+oriPosition.y)));
        scaleDis();
        if (mode == clickMode && m_pSelectedItem && Mathlib::getDistance(pTouch->getLocationInView(), pTouch->getPreviousLocationInView())>10 ) {
            m_pSelectedItem->unselected();
            m_pSelectedItem = NULL;
        }
        if (mode == toggleMode) {
            if (m_pSelectedItem && Mathlib::getDistance(pTouch->getLocationInView(), pTouch->getPreviousLocationInView())>10) {
                isMove = true;
            }
        }
        speedVector.x = (getPosition().x - lastLoc.x+speedVector.x)/2;
        speedVector.y = (getPosition().y - lastLoc.y+speedVector.y)/2;
    }
}

bool UnionJoinScroll::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent) {
    //    CCLOG("COME BEGIN");
    //    return CCLayer::ccTouchBegan(pTouch,pEvent);
    //    CCLOG("thisX:%f", pTouch->locationInView().x);
    //    CCLOG("thisY:%f", pTouch->locationInView().y);
    if (!isVisible())
    {
		return false;
    }
    
    if(Mathlib::inBound(pTouch->getLocationInView().x,
                        this->getOriPosition().x+viewSize.width,
                        this->getOriPosition().x)
       &&Mathlib::inBound((CCDirector::sharedDirector()->getWinSize().height
                           -pTouch->getLocationInView().y),
                          this->getOriPosition().y+viewSize.height,
                          this->getOriPosition().y)) {
           //           dispatchToChild(pTouch, pEvent);
           CC_UNUSED_PARAM(pEvent);
           this->unschedule(schedule_selector(UnionJoinScroll::decelerate));
           if(isEnabled) {
               if(mode == toggleMode) {
                   
                   m_pSelectedItem =this->itemForTouch(pTouch);
                   isMove = false;
               } else {
                   m_pSelectedItem = this->itemForTouch(pTouch);
                   if (m_pSelectedItem)
                   {
                       
                       m_pSelectedItem->selected();
                       
                   }
               }
           }
           speedVector.x = 0;
           speedVector.y = 0;
           return true;
       }
    return false;
}

void UnionJoinScroll::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent) {
    CCLayer::ccTouchEnded(pTouch,pEvent);
    CC_UNUSED_PARAM(pTouch);
    CC_UNUSED_PARAM(pEvent);
    this->schedule(schedule_selector(UnionJoinScroll::decelerate));
    if (mode == clickMode) {
        if (m_pSelectedItem && isEnabled)
        {
            m_pSelectedItem->unselected();
            m_pSelectedItem->activate();
        }
    } else {
        if (!isMove&&m_pSelectedItem!=NULL) {
            CCObject* obj;
            CCMenuItem* item;
            CCARRAY_FOREACH(this->getChildren(), obj) {
                item = dynamic_cast<CCMenuItem*>(obj);
                item->unselected();
            }
            m_pSelectedItem->selected();
            m_pSelectedItem->activate();
        }
    }
    
}

void UnionJoinScroll::decelerate() {
    float biaozhun = (this->getPosition().x-viewSize.width/2)/(-dividingLength)-1;
    if (speedVector.x > 0) {
        speedVector.x = 15;
    } else {
        speedVector.x = -15;
    }
    if (biaozhun - (int)biaozhun >0.47 && biaozhun - (int)biaozhun<0.53) {
        this->setPosition(ccp(Mathlib::bound(((int)biaozhun+1.5)*(-dividingLength)+viewSize.width/2 ,
                                             oriPosition.x,
                                             viewSize.width-mapSize.width+oriPosition.x),
                              Mathlib::bound(positionY,
                                             oriPosition.y,
                                             viewSize.height-mapSize.height+oriPosition.y)));
        this->unschedule(schedule_selector(GXScrollView::decelerate));
        scaleDis();
        return ;
    }

    this->setPosition(ccp(Mathlib::bound(positionX + speedVector.x,
                                         oriPosition.x,
                                         viewSize.width-mapSize.width+oriPosition.x),
                          Mathlib::bound(positionY + speedVector.y,
                                         oriPosition.y,
                                         viewSize.height-mapSize.height+oriPosition.y)));
    scaleDis();
}

void UnionJoinScroll::scaleDis() {
    float biaozhun = (this->getPosition().x-viewSize.width/2)/(-dividingLength)-1;
    int down = (int)(biaozhun-0.5);
    int up = (int)(biaozhun + 0.5);
    if (down>=0 && down<layerArray->count()) {
        CCSprite* layer1 = (CCSprite*)layerArray->objectAtIndex(down);
        layer1->setScale(1.4+Mathlib::max(0,(1-(biaozhun-0.5-down))*0.7));
        CCLayer* downLabel = (CCLayer*)descArray->objectAtIndex(down);
        if (downLabel->getParent() == NULL && this->getParent() !=NULL) {
            this->getParent()->addChild(downLabel);
        }
        downLabel->setVisible(true);
        CCObject* obj;
        CCARRAY_FOREACH(downLabel->getChildren(),obj) {
            if (((CCNode*)obj)->getTag() != 1) {
                ((CCLabelTTF*)obj)->setOpacity(255*(1-(biaozhun-0.5-down)));
            } else {
                ((CCLabelAtlas*)obj)->setOpacity(255*(1-(biaozhun-0.5-down)));
            }
            
        }
        
    }
    if (up>=0 && up<layerArray->count()) {
        CCSprite* layer2 = (CCSprite*)layerArray->objectAtIndex(up);
        layer2->setScale(1.4+Mathlib::max(0,(biaozhun+0.5-up)*0.7));
        CCLayer* upLabel = (CCLayer*)descArray->objectAtIndex(up);
        if (upLabel->getParent() == NULL && this->getParent() !=NULL) {
            this->getParent()->addChild(upLabel);
        }
        upLabel->setVisible(true);
        CCObject* obj;
        CCARRAY_FOREACH(upLabel->getChildren(),obj) {
            if (dynamic_cast<CCLabelTTF*>(obj)) {
                ((CCLabelTTF*)obj)->setOpacity(255*(biaozhun+0.5-up));
            } else {
                ((CCLabelAtlas*)obj)->setOpacity(255*(biaozhun+0.5-up));
            }
        }
        
    }
    if (down>=1 && down<layerArray->count()) {
        CCSprite* layer3 = (CCSprite*)layerArray->objectAtIndex(down-1);
        layer3->setScale(1.4);
        CCLabelTTF* Label3 = (CCLabelTTF*)descArray->objectAtIndex(down-1);
        Label3->setVisible(false);
//        CCARRAY_FOREACH(Label3->getChildren(),obj) {
//            if (dynamic_cast<CCLabelTTF*>(obj)) {
//                ((CCLabelTTF*)obj)->setOpacity(0);
//            } else {
//                ((CCLabelAtlas*)obj)->setOpacity(0);
//            }
//        }
    }
    if (up>=0 && up<layerArray->count()-1) {
        CCSprite* layer4 = (CCSprite*)layerArray->objectAtIndex(up+1);
        layer4->setScale(1.4);
        CCLabelTTF* Label4 = (CCLabelTTF*)descArray->objectAtIndex(up+1);
        Label4->setVisible(false);
//        CCARRAY_FOREACH(Label4->getChildren(),obj) {
//            if (dynamic_cast<CCLabelTTF*>(obj)) {
//                ((CCLabelTTF*)obj)->setOpacity(0);
//            } else {
//                ((CCLabelAtlas*)obj)->setOpacity(0);
//            }
//        }
        
    }
    
    
}

UnionBean* UnionJoinScroll::getSelectUnion() {
    float biaozhun = (this->getPosition().x-viewSize.width/2)/(-dividingLength)-1;
    int down = (int)(biaozhun-0.5);
    int up = (int)(biaozhun + 0.5);
    if ((biaozhun+0.5-up) > (1-(biaozhun-0.5-down))) {
        return (UnionBean*)idArray->objectAtIndex(up);
    } else {
        return (UnionBean*)idArray->objectAtIndex(down);
    }
}