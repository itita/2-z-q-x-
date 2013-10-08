//
//  MyMenuItem.cpp
//  ww2
//
//  Created by xiao tang on 12-10-8.
//
//

#include "MyMenuItem.h"

#define  disableimageTag 12

MyMenuItem* MyMenuItem::create(cocos2d::CCSprite *image, cocos2d::CCObject *rec, SEL_MenuHandler selector) {
    MyMenuItem *pRet = new MyMenuItem();
    pRet->initWithImage(image, rec, selector);
    pRet->autorelease();
    return pRet;
}

MyMenuItem* MyMenuItem::create(cocos2d::CCSprite *image,CCSprite *_disableImage, cocos2d::CCObject *rec, SEL_MenuHandler selector) {
    MyMenuItem *pRet = new MyMenuItem();
    pRet->disableImage = _disableImage;
    _disableImage->retain();
    pRet->initWithImage(image, rec, selector);
    pRet->autorelease();
    return pRet;
}

void MyMenuItem::initWithImage(cocos2d::CCSprite *image, cocos2d::CCObject *rec, SEL_MenuHandler selector) {
    itemImage = image;
    imageColor = image->getColor();
    initWithTarget(rec, selector);
    addChild(itemImage);
    setContentSize(image->getContentSize());
    image->setAnchorPoint(ccp(0,0));
}


void MyMenuItem::selected() {
    if(m_bEnabled)
    {
        CCMenuItem::selected();
        
        CCAction *action = getActionByTag(zoomActionTag);
        if (action)
        {
            this->stopAction(action);
        }
        else
        {
            m_fOriginalScale = this->getScale();
        }
        
        CCAction *zoomAction = CCScaleTo::create(0.1f, m_fOriginalScale * 0.9f);
        zoomAction->setTag(zoomActionTag);
        this->runAction(zoomAction);
    }
}

void MyMenuItem::unselected() {
    if(m_bEnabled)
    {
        CCMenuItem::unselected();
        this->stopActionByTag(zoomActionTag);
        CCAction *zoomAction = CCScaleTo::create(0.1f, m_fOriginalScale);
        zoomAction->setTag(zoomActionTag);
        this->runAction(zoomAction);
    }
}

void MyMenuItem::setOpacity(GLubyte opacity) {
//    im
    itemImage->setOpacity(opacity);
}

GLubyte MyMenuItem::getOpacity() {
    return itemImage->getOpacity();
}

void MyMenuItem::setColor(const ccColor3B& color) {
    itemImage->setColor(color);
}


const ccColor3B& MyMenuItem::getColor(void) {
    return itemImage->getColor();
}

void MyMenuItem::setOpacityModifyRGB(bool bValue) {
    itemImage->setOpacityModifyRGB(bValue);
}

bool MyMenuItem::isOpacityModifyRGB() {
    return itemImage->isOpacityModifyRGB();
}

const ccColor3B& MyMenuItem::getDisplayedColor(void) {
    return itemImage->getDisplayedColor();
}

GLubyte MyMenuItem::getDisplayedOpacity(void) {
    return itemImage->getDisplayedOpacity();
}

bool MyMenuItem::isCascadeColorEnabled(void) {
    return itemImage->isCascadeOpacityEnabled();
}

void MyMenuItem::setCascadeColorEnabled(bool cascadeColorEnabled) {
    itemImage->setCascadeColorEnabled(cascadeColorEnabled);
}

void MyMenuItem::updateDisplayedColor(const ccColor3B& color) {
    itemImage->updateDisplayedColor(color);
}

bool MyMenuItem::isCascadeOpacityEnabled(void) {
    return itemImage->isCascadeOpacityEnabled();
}

void MyMenuItem::setCascadeOpacityEnabled(bool cascadeOpacityEnabled) {
    itemImage->setCascadeOpacityEnabled(cascadeOpacityEnabled);
}

void MyMenuItem::updateDisplayedOpacity(GLubyte opacity) {
    itemImage->updateDisplayedOpacity(opacity);
}

void MyMenuItem::setDisabled(bool bEnabled) {
    CCMenuItem::setEnabled(bEnabled);
    if(disableImage == NULL) {
        if (bEnabled) {
            itemImage->setColor(imageColor);
        } else {
            itemImage->setColor(ccGRAY);
        }
    } else {
        if (bEnabled) {
            this->removeChildByTag(disableimageTag, true);
        } else {
            if (this->getChildByTag(disableimageTag) != NULL) {
                return;
            }
            disableImage->setScaleX(getImage()->getContentSize().width/disableImage->getContentSize().width);
            disableImage->setScaleY(getImage()->getContentSize().height/disableImage->getContentSize().height);
            disableImage->setAnchorPoint(ccp(0,0));
            disableImage->setTag(disableimageTag);
            this->addChild(disableImage,10);
        }
    }
}
