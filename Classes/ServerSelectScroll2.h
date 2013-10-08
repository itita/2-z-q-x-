//
//  ServerSelectScroll2.h
//  ww4
//
//  Created by xiao tang on 13-9-20.
//
//

#ifndef __ww4__ServerSelectScroll2__
#define __ww4__ServerSelectScroll2__

#include "GXScrollView.h"

class ServerSelectScroll2 : public GXScrollView{
    
public:
    
    ~ServerSelectScroll2() {
        
    }
    
    ServerSelectScroll2(){
        
    }
    
    static ServerSelectScroll2* create(int _priority);
//    bool init();
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
    
};

#endif /* defined(__ww4__ServerSelectScroll2__) */
