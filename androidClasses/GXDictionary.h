//
//  GXDictionary.h
//  ww4
//
//  Created by xiao tang on 13-3-22.
//
//

#ifndef __ww4__GXDictionary__
#define __ww4__GXDictionary__

#include <iostream>
#include "cocos2d.h"

using namespace cocos2d;

class GXDictionary : public CCDictionary {
    
public:
    ~GXDictionary() {
        
    }
    static GXDictionary* create();
};

#endif /* defined(__ww4__GXDictionary__) */
