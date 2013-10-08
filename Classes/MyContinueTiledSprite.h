//
//  MyContinueTiledSprite.h
//  ww3
//
//  Created by xiao tang on 12-12-3.
//
//

#ifndef ww3_MyContinueTiledSprite_h
#define ww3_MyContinueTiledSprite_h
#include "cocos2d.h"

using namespace cocos2d;


class MyContinueTiledSprite  : public  CCSprite{
    
public:
    MyContinueTiledSprite():
    lu(0),
    ru(0),
    ld(0),
    rd(0){}
    virtual ~MyContinueTiledSprite();
   
    static MyContinueTiledSprite* create(CCString* spriteFileName);
    virtual void updateSprite();
    virtual void updateLoc(int value);
    int lu;
    int ru;
    int ld;
    int rd;
private:
    CCString* spriteFileName;
    bool isSelected;
    CCPoint oriPos;
    
};

#endif
