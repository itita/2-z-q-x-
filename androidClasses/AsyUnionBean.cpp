//
//  AsyUnionBean.cpp
//  ww4
//
//  Created by xiao tang on 13-3-27.
//
//

#include "AsyUnionBean.h"

AsyUnionBean* AsyUnionBean::create() {
    AsyUnionBean* bean = new AsyUnionBean();
    bean->name = GXString::create("");
    bean->desc = GXString::create("");
    bean->notice = GXString::create("");
    return bean;
}

void AsyUnionBean::setName(GXString* nameStr) {
    CC_SAFE_RELEASE_NULL(name);
    name = nameStr;
    name->retain();
}

GXString* AsyUnionBean::getName() {
    return name;
}

void AsyUnionBean::setDesc(GXString* descStr) {
    CC_SAFE_RELEASE_NULL(desc);
    desc = descStr;
    desc->retain();
}

GXString* AsyUnionBean::getDesc() {
    return desc;
}

void AsyUnionBean::setNotice(GXString* noticeStr) {
    CC_SAFE_RELEASE_NULL(notice);
    notice = noticeStr;
    notice->retain();
}

GXString* AsyUnionBean::getNotice() {
    return notice;
}

void AsyUnionBean::setEmblem(GXString* emblemStr) {
    CC_SAFE_RELEASE_NULL(emblem);
    emblem = emblemStr;
    emblem->retain();
}

GXString* AsyUnionBean::getEmblem() {
    return emblem;
}
