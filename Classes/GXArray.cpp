//
//  GXArray.cpp
//  ww4
//
//  Created by xiao tang on 13-3-27.
//
//


#include "GXArray.h"

GXArray* GXArray::create() {
    
    GXArray* pArray = new GXArray();
    
    if (pArray && pArray->init())
    {
        
    }
    else
    {
        CC_SAFE_DELETE(pArray);
    }
    
    return pArray;
}
