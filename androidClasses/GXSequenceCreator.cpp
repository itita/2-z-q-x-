//
//  GXSequenceCreator.cpp
//  Dialog2
//
//  Created by xiao tang on 13-8-23.
//
//

#include "GXSequenceCreator.h"

GXSequenceCreator* GXSequenceCreator::create() {
    GXSequenceCreator* creator = new GXSequenceCreator();
    creator->autorelease();
    creator->actionCreatorArray = CCArray::create();
    creator->actionCreatorArray->retain();
    return creator;
}

CCAction* GXSequenceCreator::getAction() {
    CCArray* actionArray = CCArray::create();
    CCObject* obj;
    CCARRAY_FOREACH(actionCreatorArray,obj) {
        actionArray->addObject(((GXActionCreator*)obj)->getAction());
    }
    return CCSequence::create(actionArray);
}