//
//  GXLineSprite.h
//  ww4
//
//  Created by xiao tang on 13-5-19.
//
//

#ifndef __ww4__GXLineSprite__
#define __ww4__GXLineSprite__

#include <iostream>
#include "cocos2d.h"

using namespace cocos2d;

class GXLineSprite : public CCNode {
    
public:
    
    static GXLineSprite* create(const CCPoint& begin,const CCPoint& end);
    
    virtual void draw(void);
    const CCPoint& getEndPosition(void);
    void setEndPosition(const CCPoint& var);
private:
    CCPoint endPosition;
};

#endif /* defined(__ww4__GXLineSprite__) */
