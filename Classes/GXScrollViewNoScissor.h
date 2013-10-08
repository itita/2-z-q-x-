//
//  GXScrollViewNoScissor.h
//  ww4
//
//  Created by xiao tang on 13-7-25.
//
//

#ifndef __ww4__GXScrollViewNoScissor__
#define __ww4__GXScrollViewNoScissor__

#include "GXScrollView.h"

class GXScrollViewNoScissor : public GXScrollView {
    
public:
    GXScrollViewNoScissor():
    unionNode(NULL){}
    
    static GXScrollViewNoScissor* create(int _priority);
    ~GXScrollViewNoScissor() {
        CC_SAFE_RELEASE_NULL(unionNode);
    }
    
    virtual void visit(void);
    virtual void setPosition(const CCPoint& newPosition);
    
    CCNode* getUnionNode() {
        return unionNode;
    }
    
    void setUnionNode(CCNode* _unionNode) {
        CC_SAFE_RELEASE_NULL(unionNode);
        CC_SAFE_RETAIN(_unionNode);
        unionNode = _unionNode;
    }
    
//    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
//    virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
//    virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
    
private:
    CCNode* unionNode;
};

#endif /* defined(__ww4__GXScrollViewNoScissor__) */
