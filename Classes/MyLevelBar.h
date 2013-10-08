//
//  MyLevelBar.h
//  ww3
//
//  Created by xiao tang on 12-10-17.
//
//

#ifndef ww3_MyLevelBar_h
#define ww3_MyLevelBar_h
#include "GXProgressBar.h"

class MyLevelBar : public GXProgressBar {
    
public:
    MyLevelBar():
    label(NULL),
//    maxCapacity(0),
    capacity(0),
    level(1){}
    virtual void levelUp();
    virtual void setLevel(int level);
    int getLevel() {
        return level;
    }
//    virtual void setCapacity(int capacity);
    static MyLevelBar* create(CCSprite* upSprite,CCSprite* backSprite,const CCSize &size);
    virtual void setContentSize(const CCSize & var);
private:
    CCLabelAtlas* label;
//    int maxCapacity;
    int capacity;
    int level;
};

#endif
