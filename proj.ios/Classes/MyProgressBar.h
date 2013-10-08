//
//  MyProgressBar.h
//  ww3
//
//  Created by xiao tang on 12-10-17.
//
//

#ifndef ww3_MyProgressBar_h
#define ww3_MyProgressBar_h
#include "GXProgressBar.h"

class MyProgressBar : public GXProgressBar {
    
public:
    MyProgressBar():
    label(NULL),
    maxCapacity(0),
    capacity(0){}
    virtual void setCapacity(int capacity);
    static MyProgressBar* create(CCSprite* upSprite,CCSprite* backSprite,int maxCapacity);
    virtual void setContentSize(const CCSize & var);
private:
    CCLabelAtlas* label;
    int maxCapacity;
    int capacity;
};


#endif
