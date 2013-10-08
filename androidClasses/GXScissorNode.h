//
//  GXScissorNode.h
//  ww4
//
//  Created by xiao tang on 13-7-25.
//
//

#ifndef __ww4__GXScissorNode__
#define __ww4__GXScissorNode__

#include "cocos2d.h"

using namespace cocos2d;

class GXScissorNode : public CCNode {
    
public:
    static GXScissorNode* create(const CCSize& viewSize,const CCPoint& oriPosition);
    virtual void visit(void);
    
protected:
    CCSize viewSize;
    CCPoint oriPosition;
    
};

#endif /* defined(__ww4__GXScissorNode__) */
