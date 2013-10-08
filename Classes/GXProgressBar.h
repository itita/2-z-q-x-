//
//  GXProgressBar.h
//  ww3
//
//  Created by xiao tang on 12-10-17.
//
//

#ifndef ww3_GXProgressBar_h
#define ww3_GXProgressBar_h
#define backTag 10
#include "cocos2d.h"

using namespace cocos2d;

class GXProgressBar :public CCLayer, public CCRGBAProtocol{
    
public:
    GXProgressBar():
    percentage(100),
    upSprite(NULL){}
    float percentage;
    virtual void updatePercentage(float percentage);
    static GXProgressBar* create(CCSprite* upSprite,CCSprite* backSprite);
    virtual void setContentSize(const CCSize & var);
    virtual CCSprite* getUpSprite();
   
    virtual void setColor(const ccColor3B& color) ;
    
    virtual const ccColor3B& getColor(void);
    
    virtual GLubyte getOpacity(void);
    
    
    virtual void setOpacity(GLubyte opacity);
    
  
    virtual void setOpacityModifyRGB(bool bValue);
    
    virtual bool isOpacityModifyRGB(void);
    
    
    /**
     * Returns the displayed color.
     *
     * @return The ccColor3B contains R,G,B bytes.
     */
    virtual const ccColor3B& getDisplayedColor(void);
    
    /**
     * Returns the displayed opacity.
     *
     * @return  The opacity of sprite, from 0 ~ 255
     */
    virtual GLubyte getDisplayedOpacity(void);
    
   

    
    /**
     *  whether or not color should be propagated to its children.
     */
    virtual bool isCascadeColorEnabled(void);
    virtual void setCascadeColorEnabled(bool cascadeColorEnabled);
    
    /**
     *  recursive method that updates display color
     */
    virtual void updateDisplayedColor(const ccColor3B& color);
    
    /**
     *  whether or not opacity should be propagated to its children.
     */
    virtual bool isCascadeOpacityEnabled(void);
    virtual void setCascadeOpacityEnabled(bool cascadeOpacityEnabled);
    
    /**
     *  recursive method that updates the displayed opacity.
     */
    virtual void updateDisplayedOpacity(GLubyte opacity);
protected:
    //    CCSize oriSize;
    //    CCPoint oriPoint;
    CCSprite* upSprite;
    CCRect myoriRect;
};

#endif
