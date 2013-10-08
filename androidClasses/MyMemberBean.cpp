//
//  MyMemberBean.cpp
//  ww4
//
//  Created by xiao tang on 13-3-28.
//
//


#include "MyMemberBean.h"

MyMemberBean* MyMemberBean::create() {
    MyMemberBean* bean = new MyMemberBean();
    bean->autorelease();
    return bean;
}

void MyMemberBean::setNickName(CCString* _nickName) {
    CC_SAFE_RELEASE_NULL(nickName);
    nickName = _nickName;
    nickName->retain();
}

void MyMemberBean::setItitaId(CCString* _ititaId) {
    CC_SAFE_RELEASE_NULL(ititaId);
    ititaId = _ititaId;
    ititaId->retain();
}
