//
//  ServerSelectScroll.h
//  ww4
//
//  Created by xiao tang on 13-4-25.
//
//

#ifndef __ww4__ServerSelectScroll__
#define __ww4__ServerSelectScroll__

#include <iostream>
#include "GXScrollView.h"

#define serverNameLabelTag 1000

class ServerSelectScroll : public GXScrollView{
    
public:
    
    ~ServerSelectScroll() {
        CC_SAFE_RELEASE_NULL(serverArray);
    }
    
    ServerSelectScroll()
    :serverArray(NULL) {
    
    }
    
    static ServerSelectScroll* create(int _priority,CCArray* _serverArray,int selectedServerIndex);
    bool init(CCArray* _serverArray,int selectedServerIndex);
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
    virtual void decelerate();
    void scaleDis();
    CCObject* getSelectServer();
    float beilv;
private:
    CCArray* serverArray;
};

#endif /* defined(__ww4__ServerSelectScroll__) */
