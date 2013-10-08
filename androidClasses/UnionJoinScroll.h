//
//  UnionJoinScroll.h
//  ww4
//
//  Created by xiao tang on 13-3-26.
//
//

#ifndef __ww4__UnionJoinScroll__
#define __ww4__UnionJoinScroll__

#include <iostream>
#include "GXScrollView.h"
#include "MyGameInfo.h"

class UnionJoinScroll : public GXScrollView {
    
public:
    ~UnionJoinScroll() {
        layerArray->release();
        descArray->release();
        idArray->release();
    }
    UnionJoinScroll():
    layerArray(NULL),
    descArray(NULL),
    dividingLength(0){};
    static UnionJoinScroll* create(int _priority,CCArray* unionArray);
    bool init(CCArray* unionArray);
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
    virtual void decelerate();
    void scaleDis();
    UnionBean* getSelectUnion();
private:
    CCArray* layerArray;
    CCArray* descArray;
    CCArray* idArray;
    int dividingLength;
};

#endif /* defined(__ww4__UnionJoinScroll__) */
