//
//  GXListView.h
//  ww3
//
//  Created by xiao tang on 12-11-22.
//
//

#ifndef ww3_GXListView_h
#define ww3_GXListView_h
#include "GXScrollView.h"

class GXListView : public GXScrollView {
    
public:
    ~GXListView() {
    
    }
    static  GXListView* create(int _priority);
    virtual void addChild(CCNode* child);
    virtual void addChildNoAction(CCNode* child);
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    virtual void removeChildAction(CCNode* child);
private:
    CCSize childSize;
};

#endif
