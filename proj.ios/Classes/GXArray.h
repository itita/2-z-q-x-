//
//  GXArray.h
//  ww4
//
//  Created by xiao tang on 13-3-27.
//
//

#ifndef __ww4__GXArray__
#define __ww4__GXArray__

#include <iostream>
#include "GXArray.h"
#include "cocos2d.h"

using namespace cocos2d;

class GXArray : public CCArray  {
    
public:
    ~GXArray() {
        
    }
    static GXArray* create();
};
#endif /* defined(__ww4__GXArray__) */
