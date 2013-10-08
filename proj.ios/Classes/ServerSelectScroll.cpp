//
//  ServerSelectScroll.cpp
//  ww4
//
//  Created by xiao tang on 13-4-25.
//
//

#define offsetX pTouch->getLocationInView().x - pTouch->getPreviousLocationInView().x
#define offsetY pTouch->getPreviousLocationInView().y - pTouch->getLocationInView().y
#define positionX this->getPosition().x
#define positionY this->getPosition().y
#define dividingLength 66

#include "ServerSelectScroll.h"
#include "MyGameInfo.h"
#include "Mathlib.h"
#include "ServerScene.h"

ServerSelectScroll* ServerSelectScroll::create(int _priority,CCArray*_serverArray,int selectedServerIndex) {
    ServerSelectScroll* pRet = new ServerSelectScroll();
    if (pRet && pRet->init(_serverArray, selectedServerIndex))
    {
        pRet->priority = _priority;
        pRet->beilv = winSize.width/960;
        pRet->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(pRet);
    }
    return pRet;
}

bool ServerSelectScroll::init(CCArray* _serverArray,int selectedServerIndex) {
    CCLayer::init();
    this->setTouchEnabled(true);
    setContentSize(CCSizeMake(winSize.width, 198));
    setMapSize(CCSizeMake(winSize.width/2, dividingLength*(_serverArray->count()+2)));
    CCObject* obj;
    int i=1;
//    int i=0;
    serverArray = _serverArray;
    serverArray->retain();

    CCARRAY_FOREACH(serverArray,obj) {
        CCLayer* bean = (CCLayer*)obj;
    
        
        //        tempLayer->addChild(emblem);
        
        bean->setPosition(ccp(winSize.width/2-207,dividingLength*i+33));
        
        
        this->addChild(bean);
        i++;
    }
    int count = serverArray->count();
//    CCLog("%f",-1*(count/2)*dividingLength+winSize.width/2);
    setOriPosition(ccp(0,405));
    if (selectedServerIndex >=0 && selectedServerIndex < count) {
        setPosition(ccp(0,-1*(selectedServerIndex+0.5)*(dividingLength)+33+405));
    } else {
        setPosition(ccp(0,-1*(count-0.5)*(dividingLength)+33+405));
    }
    
    return true;
}

void ServerSelectScroll::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent) {
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

bool ServerSelectScroll::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent) {
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
           this->unschedule(schedule_selector(ServerSelectScroll::decelerate));
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

void ServerSelectScroll::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent) {
    CCLayer::ccTouchEnded(pTouch,pEvent);
    CC_UNUSED_PARAM(pTouch);
    CC_UNUSED_PARAM(pEvent);
    this->schedule(schedule_selector(ServerSelectScroll::decelerate));
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

void ServerSelectScroll::decelerate() {
    float biaozhun = (this->getPosition().y-viewSize.height/2-405)/(-dividingLength);
    if (speedVector.x > 0) {
        speedVector.x = 15;
    } else {
        speedVector.x = -15;
    }
    if (biaozhun - (int)biaozhun >0.47 && biaozhun - (int)biaozhun<0.53) {
        this->setPosition(ccp(Mathlib::bound(positionX,
                                               oriPosition.x,
                                               viewSize.width-mapSize.width+oriPosition.x),Mathlib::bound(((int)biaozhun+0.5)*(-dividingLength)+viewSize.height/2+405 ,
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

void ServerSelectScroll::scaleDis() {
    float biaozhun = (this->getPosition().y-viewSize.height/2-405)/(-dividingLength)-1;
    int down = (int)(biaozhun-0.5);
    int up = (int)(biaozhun + 0.5);
    if (down>=0 && down<serverArray->count()) {
        CCLayer* layer1 = (CCLayer*)serverArray->objectAtIndex(down);
        layer1->setScale(1+Mathlib::max(0,(1-(biaozhun-0.5-down))*0.1));
        //放大缩小锚点不规则，适配未对其
        layer1->setPosition(ccp(winSize.width/2-207+(layer1->getScale()-1)*205*beilv,dividingLength*(down+1)+33+(layer1->getScale()-1)*300));
//        layer1->setPosition(ccp(winSize.width/2-215,dividingLength*(down+1)+33+(layer1->getScale()-1)*300));
        
    }
    if (up>=0 && up<serverArray->count()) {
        CCLayer* layer2 = (CCLayer*)serverArray->objectAtIndex(up);
        layer2->setScale(1+Mathlib::max(0,(biaozhun+0.5-up)*0.1));
        //放大缩小锚点不规则，适配未对其
        layer2->setPosition(ccp(winSize.width/2-207+(layer2->getScale()-1)*205*beilv,dividingLength*(up+1)+33+(layer2->getScale()-1)*300));
//        layer2->setPosition(ccp(winSize.width/2-215,dividingLength*(up+1)+33+(layer2->getScale()-1)*300));
    }
    if (((biaozhun+0.5-up) > (1-(biaozhun-0.5-down))) && serverArray->count()>0) {
        if (up-1>=0 && up-1<serverArray->count()) {
            CCLabelTTF* upLabel1 = ((CCLabelTTF*)((CCNode*)serverArray->objectAtIndex(up-1))->getChildByTag(serverNameLabelTag));
            if (upLabel1->getColor().b == 0) {
                upLabel1->setColor(ccc3(155,155,155));
            }
            CCSprite* downTip = (CCSprite*)this->getParent()->getChildByTag(downTipTag);
            if (!downTip->isVisible()) {
                downTip->setVisible(true);
            }
        } else {
            CCSprite* downTip = (CCSprite*)this->getParent()->getChildByTag(downTipTag);
            if (downTip->isVisible()) {
                downTip->setVisible(false);
            }
        }
        if (up>=0 && up<serverArray->count()) {
            CCLabelTTF* upLabel2 = ((CCLabelTTF*)((CCNode*)serverArray->objectAtIndex(up))->getChildByTag(serverNameLabelTag));
            if (upLabel2->getColor().b > 0) {
                upLabel2->setColor(ccc3(255,222,0));
            }
        }
        if (up+1>=0 && up+1<serverArray->count()) {
            CCLabelTTF* upLabel3 = ((CCLabelTTF*)((CCNode*)serverArray->objectAtIndex(up+1))->getChildByTag(serverNameLabelTag));
            if (upLabel3->getColor().b == 0) {
                upLabel3->setColor(ccc3(155,155,155));
            }
            CCSprite* upTip = (CCSprite*)this->getParent()->getChildByTag(upTipTag);
            if (!upTip->isVisible()) {
                upTip->setVisible(true);
            }
        } else {
            CCSprite* upTip = (CCSprite*)this->getParent()->getChildByTag(upTipTag);
            if (upTip->isVisible()) {
                upTip->setVisible(false);
            }
        }
    } else {
        if (down-1>=0 && down-1<serverArray->count()) {
            CCLabelTTF* downLabel1 = ((CCLabelTTF*)((CCNode*)serverArray->objectAtIndex(down-1))->getChildByTag(serverNameLabelTag));
            if (downLabel1->getColor().b == 0) {
                downLabel1->setColor(ccc3(155,155,155));
            }
            CCSprite* downTip = (CCSprite*)this->getParent()->getChildByTag(downTipTag);
            if (!downTip->isVisible()) {
                downTip->setVisible(true);
            }
        } else {
            CCSprite* downTip = (CCSprite*)this->getParent()->getChildByTag(downTipTag);
            if (downTip->isVisible()) {
                downTip->setVisible(false);
            }
        }
        
        if (down>=0 && down<serverArray->count()) {
            CCLabelTTF* downLabel2 = ((CCLabelTTF*)((CCNode*)serverArray->objectAtIndex(down))->getChildByTag(serverNameLabelTag));
            if (downLabel2->getColor().b > 0) {
                downLabel2->setColor(ccc3(255,222,0));
            }
        }
        if (down+1>=0 && down+1<serverArray->count()) {
            CCLabelTTF* downLabel3 = ((CCLabelTTF*)((CCNode*)serverArray->objectAtIndex(down+1))->getChildByTag(serverNameLabelTag));
            if (downLabel3->getColor().b == 0) {
                downLabel3->setColor(ccc3(155,155,155));
            }
            CCSprite* upTip = (CCSprite*)this->getParent()->getChildByTag(upTipTag);
            if (!upTip->isVisible()) {
                upTip->setVisible(true);
            }
        } else {
            CCSprite* upTip = (CCSprite*)this->getParent()->getChildByTag(upTipTag);
            if (upTip->isVisible()) {
                upTip->setVisible(false);
            }
        }
    }
}

CCObject* ServerSelectScroll::getSelectServer() {
    float biaozhun = (this->getPosition().y-viewSize.height/2-405)/(-dividingLength)-1;
    int down = (int)(biaozhun-0.5);
    int up = (int)(biaozhun + 0.5);
    if ((biaozhun+0.5-up) > (1-(biaozhun-0.5-down))) {
        return ((CCNode*)serverArray->objectAtIndex(up))->getUserObject();
    } else {
        return ((CCNode*)serverArray->objectAtIndex(down))->getUserObject();
    }
    return NULL;
}