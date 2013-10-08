//
//  GXProgressBar.cpp
//  ww3
//
//  Created by xiao tang on 12-10-17.
//
//

#include "GXProgressBar.h"
#include "Mathlib.h"

GXProgressBar* GXProgressBar::create(CCSprite* upSprite,CCSprite* backSprite) {
    GXProgressBar *progressBar = new GXProgressBar();
    if (progressBar && progressBar->init())
    {
        progressBar->autorelease();
//        pobSprite->oriSize = pobSprite->getTextureRect().size;
//        pobSprite->oriPoint = pobSprite->getTextureRect().origin;
        progressBar->myoriRect = upSprite->getTextureRect();
//        pobSprite->myoriRect->retain()
        
        progressBar->addChild(backSprite);
        backSprite->setTag(backTag);
        backSprite->setAnchorPoint(ccp(0,0));
        progressBar->addChild(upSprite);
        upSprite->setAnchorPoint(ccp(0,0));
        progressBar->upSprite = upSprite;
        return progressBar;
    }
    CC_SAFE_RELEASE_NULL(progressBar);
    return NULL;
}

void GXProgressBar::updatePercentage(float percentage) {
    //    getTextureRect().= oriSize.height/2;
    this->percentage = percentage;
    float zoom = Mathlib::bound(percentage, 1, 0);
//    CCLog("%f",zoom);
//    CCLog("%f",myoriRect.origin.x);
//    CCLog("%f",myoriRect.origin.y);
//    CCLog("%f",myoriRect.size.width);
//    CCLog("%f",myoriRect.size.height);
    upSprite->setTextureRect(CCRectMake(myoriRect.origin.x, myoriRect.origin.y, myoriRect.size.width*zoom, myoriRect.size.height));
//    upSprite->setTextureRect(CCRectMake(0, 0, 75*0.3, myoriRect.size.height));
}

void GXProgressBar::setContentSize(const cocos2d::CCSize &var) {
    CCLayer::setContentSize(var);
    if(upSprite) {
        upSprite->setScaleX(var.width/upSprite->getContentSize().width);
        upSprite->setScaleY(var.height/upSprite->getContentSize().height);
        CCSprite* back = (CCSprite*)getChildByTag(backTag);
        back->setScaleX(var.width/back->getContentSize().width);
        back->setScaleY(var.height/back->getContentSize().height);
    }
}

CCSprite* GXProgressBar::getUpSprite() {
    return upSprite;
}

void GXProgressBar::setColor(const ccColor3B& color) {
    upSprite->setColor(color);
};

const ccColor3B& GXProgressBar::getColor(void) {
    return upSprite->getColor();
};

// returns the opacity
GLubyte GXProgressBar::getOpacity(void)  {
    return  upSprite->getOpacity();
};


void GXProgressBar::setOpacity(GLubyte opacity) {
    CCObject* obj;
    CCARRAY_FOREACH(getChildren(), obj) {
        CCRGBAProtocol* pro = dynamic_cast<CCRGBAProtocol*>(obj);
        if (pro) {
            pro->setOpacity(opacity);
        }
    }
};

void GXProgressBar::setOpacityModifyRGB(bool bValue) {
    upSprite->setOpacityModifyRGB(bValue);
};


bool GXProgressBar::isOpacityModifyRGB(void) {
    return upSprite->isOpacityModifyRGB();
};

const ccColor3B& GXProgressBar::getDisplayedColor(void) {
    return upSprite->getDisplayedColor();
}

GLubyte GXProgressBar::getDisplayedOpacity(void) {
    return upSprite->getDisplayedOpacity();
}

bool GXProgressBar::isCascadeColorEnabled(void)  {
    return upSprite->isCascadeColorEnabled();
}

void GXProgressBar::setCascadeColorEnabled(bool cascadeColorEnabled){
    return upSprite->setCascadeColorEnabled(cascadeColorEnabled);
}

void GXProgressBar::updateDisplayedColor(const ccColor3B& color) {
    return upSprite->updateDisplayedColor(color);
}

/**
 *  whether or not opacity should be propagated to its children.
 */
bool GXProgressBar::isCascadeOpacityEnabled(void) {
    return upSprite->isCascadeOpacityEnabled();
}

void GXProgressBar::setCascadeOpacityEnabled(bool cascadeOpacityEnabled) {
    upSprite->setCascadeColorEnabled(cascadeOpacityEnabled);
}


void GXProgressBar::updateDisplayedOpacity(GLubyte opacity){
    upSprite->updateDisplayedOpacity(opacity);
}