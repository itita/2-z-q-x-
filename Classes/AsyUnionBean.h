//
//  AsyUnionBean.h
//  ww4
//
//  Created by xiao tang on 13-3-27.
//
//

#ifndef __ww4__AsyUnionBean__
#define __ww4__AsyUnionBean__

#include <iostream>
#include "cocos2d.h"
#include "GXString.h"

class AsyUnionBean : public CCObject {
    
public:
    ~AsyUnionBean() {
        CC_SAFE_RELEASE_NULL(name);
        CC_SAFE_RELEASE_NULL(desc);
        CC_SAFE_RELEASE_NULL(notice);
        CC_SAFE_RELEASE_NULL(emblem);
    }
    
    AsyUnionBean():
    name(NULL),
    desc(NULL),
    notice(NULL),
    emblem(NULL),
    level(1),
    role(1),
    unionId(-1){
    }
    int level;
    int role;
    int unionId;
    int memberCount;
    static AsyUnionBean* create();
    void setName(GXString* nameStr);
    GXString* getName();
    void setDesc(GXString* descStr);
    GXString* getDesc();
    void setNotice(GXString* noticeStr);
    GXString* getNotice();
    void setEmblem(GXString* emblemStr);
    GXString* getEmblem();
    
private:
    GXString* name;
    GXString* desc;
    GXString* notice;
    GXString* emblem;
};

#endif /* defined(__ww4__AsyUnionBean__) */
