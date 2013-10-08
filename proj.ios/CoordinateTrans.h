//
//  CoordinateTrans.h
//  ww2
//
//  Created by xiao tang on 12-9-28.
//
//


#ifndef ww2_CoordinateTrans_h
#define ww2_CoordinateTrans_h



#include "cocos2d.h"

using namespace cocos2d;

class CoordinateTrans {
    
public:
    static CCSize transWindowToGLInRetina(const CCSize& _size);
    static CCPoint transWindowToGLInRetina(const CCPoint& _point);
    static CCPoint transWindowToGLInRetina(float x,float y);
    static float transWindowToGLInRetina(float f);
    static int transWindowToGLInRetinaInt(int f);
    static CCSize transTiledSizeInRetina(const CCSize& _size);
    static CCSize transTiledSizeInRetina(float x,float y);
    static int glScissorAdapter(float x);
};

#endif
