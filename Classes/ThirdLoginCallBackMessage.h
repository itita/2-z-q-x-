//
//  ThirdLoginCallBackMessage.h
//  ww4
//
//  Created by xiao tang on 13-9-28.
//
//

#ifndef __ww4__ThirdLoginCallBackMessage__
#define __ww4__ThirdLoginCallBackMessage__

#include "MyBaseMessage.h"

class ThirdLoginCallBackMessage : public MyBaseMessage  {
    
public:
    ThirdLoginCallBackMessage() {
        tag = ThirdLoginCallBackMessageTag;
    }
    ~ThirdLoginCallBackMessage(){
        
    }
    static ThirdLoginCallBackMessage* create(int userId);
    virtual void sendMsg();
    int userId;
};

#endif /* defined(__ww4__ThirdLoginCallBackMessage__) */
