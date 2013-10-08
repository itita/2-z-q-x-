//
//  MyContinueBuilding.h
//  ww3
//
//  Created by xiao tang on 12-12-7.
//
//

#ifndef ww3_MyContinueBuilding_h
#define ww3_MyContinueBuilding_h
#include "MyBuilding.h"

class MyContinueBuilding : public MyBuilding {
    
public:
    
    
    static MyContinueBuilding* create(int tag,const CCSize& _contentSizebyTiled,GXFSMstate* state,int level,int _maxLevel);
//    virtual void activate();
    virtual void selected();
    virtual void unselected();
    
};

#endif
