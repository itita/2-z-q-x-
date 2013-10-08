//
//  MyMemberBean.h
//  ww4
//
//  Created by xiao tang on 13-3-28.
//
//

#ifndef __ww4__MyMemberBean__
#define __ww4__MyMemberBean__

#include <iostream>
#include "cocos2d.h"

using namespace cocos2d;

class MyMemberBean : public CCObject {
    
public:
    MyMemberBean():
    power(0),
    role(0),
    experience(1),
    donatePower(0),
    isOnline(false),
    nickName(NULL),
    ititaId(NULL){
    
    }
    
    ~MyMemberBean() {
        CC_SAFE_RELEASE_NULL(nickName);
        CC_SAFE_RELEASE_NULL(ititaId);
    }
    
    int role;
    bool isOnline;
    
    float power;
    unsigned long long experience;
    int donatePower;
    
    static MyMemberBean* create();
    
    const char* getNickName() {
        return nickName->getCString();
    };
    void setNickName(CCString* create);
    
    const char* getItitaId() {
        return ititaId->getCString();
    };
    void setItitaId(CCString* create);
    
    
private:
    CCString* nickName;
    CCString* ititaId;
};

#endif /* defined(__ww4__MyMemberBean__) */
