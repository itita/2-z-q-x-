//
//  MyMenuItem.h
//  ww2
//
//  Created by xiao tang on 12-10-8.
//
//

#ifndef ww2_MyMenuItem_h
#define ww2_MyMenuItem_h
#define zoomActionTag 10
#include "cocos2d.h"
using namespace cocos2d;

class MyMenuItem : public CCMenuItem {
    
public:
    ~MyMenuItem() {
//        CCLog("~MyMenuItem has been released");
    }
    MyMenuItem():
    itemImage(NULL),
    disableImage(NULL),
    m_fOriginalScale(0){
        m_eScriptType = kScriptTypeNone;
    }
    static MyMenuItem* create(CCSprite* image,CCObject *rec, SEL_MenuHandler selector);
    static MyMenuItem* create(CCSprite* image,CCSprite* disableImage, CCObject *rec, SEL_MenuHandler selector);
    
    virtual void initWithImage(cocos2d::CCSprite *image, cocos2d::CCObject *rec, SEL_MenuHandler selector);
    virtual void selected();
    virtual void unselected();
    virtual void setDisabled(bool bEnabled);
    virtual void setColor(const ccColor3B& color);
    virtual const ccColor3B& getColor(void);
    virtual GLubyte getOpacity(void);
    virtual void setOpacity(GLubyte opacity);
    virtual void setOpacityModifyRGB(bool bValue);
    virtual bool isOpacityModifyRGB(void);
    
    virtual const ccColor3B& getDisplayedColor(void);
    
    virtual GLubyte getDisplayedOpacity(void);
    
    virtual bool isCascadeColorEnabled(void);
    virtual void setCascadeColorEnabled(bool cascadeColorEnabled);
    virtual void updateDisplayedColor(const ccColor3B& color);
    
    virtual bool isCascadeOpacityEnabled(void);
    virtual void setCascadeOpacityEnabled(bool cascadeOpacityEnabled);
    
    virtual void updateDisplayedOpacity(GLubyte opacity);
    CCSprite* getImage() {
        return itemImage;
    }

protected:
    CCSprite* itemImage;
    CCSprite* disableImage;
    ccColor3B imageColor;
    float  m_fOriginalScale;
};

#endif
