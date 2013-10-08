//
//  MyCombineBuilding.h
//  ww4
//
//  Created by xiao tang on 13-4-3.
//
//

#ifndef __ww4__MyCombineBuilding__
#define __ww4__MyCombineBuilding__

#include <iostream>
#include "MyBuilding.h"

class MyCombineBuilding : public MyBuilding
{
    
public:
    static MyCombineBuilding* create(int tag,const CCSize& _contentSizebyTiled,GXFSMstate* state,int _level,int _maxLevel);
//    virtual const CCPoint& getZorderPosition();
    
    
    
};

#endif /* defined(__ww4__MyCombineBuilding__) */
