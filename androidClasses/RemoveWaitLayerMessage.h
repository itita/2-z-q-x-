//
//  RemoveWaitLayerMessage.h
//  ww4
//
//  Created by xiao tang on 13-7-23.
//
//

#ifndef __ww4__RemoveWaitLayerMessage__
#define __ww4__RemoveWaitLayerMessage__

#include "MyBaseMessage.h"

class RemoveWaitLayerMessage : public MyBaseMessage {
    
public:
    RemoveWaitLayerMessage() {
        tag = RemoveWaitLayerMessageTag;
    }
    ~RemoveWaitLayerMessage(){
        
    }
    static RemoveWaitLayerMessage* create();
    virtual void sendMsg();
    
};

#endif /* defined(__ww4__RemoveWaitLayerMessage__) */
