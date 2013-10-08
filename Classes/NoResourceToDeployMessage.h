//
//  NoResourceToDeployMessage.h
//  ww3
//
//  Created by xiao tang on 12-12-19.
//
//

#ifndef __ww3__NoResourceToDeployMessage__
#define __ww3__NoResourceToDeployMessage__

#include "MyBaseMessage.h"
#include "UnitSet.h"

class NoResourceToDeployMessage : public MyBaseMessage{
    
public:
    NoResourceToDeployMessage() {
        tag = noResourceToDeployMessageTag;
    }
    ~NoResourceToDeployMessage(){
//        CC_SAFE_RELEASE_NULL(creator);
    }
    static NoResourceToDeployMessage* create(UnitBean* creator);
    virtual void sendMsg();
    
    UnitBean* creator;
};

#endif /* defined(__ww3__NoResourceToDeployMessage__) */
