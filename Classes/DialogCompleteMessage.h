//
//  DialogCompleteMessage.h
//  ww4
//
//  Created by xiao tang on 13-8-24.
//
//

#ifndef __ww4__DialogCompleteMessage__
#define __ww4__DialogCompleteMessage__

#include "MyBaseMessage.h"

class DialogCompleteMessage : public MyBaseMessage {
    
public:
    DialogCompleteMessage():
    currentNode(0),
    maxNode(0),
    dialogTag(-1){
        tag = DialogCompleteMessageTag;
    }
    ~DialogCompleteMessage(){
        
    }
    static DialogCompleteMessage* create(int maxNode,int currentNode,int dialogTag);
    virtual void sendMsg();
    int maxNode;
    int currentNode;
    int dialogTag;
    
};

#endif /* defined(__ww4__DialogCompleteMessage__) */
