//
//  GXJsonUtil.cpp
//  ww2
//
//  Created by DingYu Fu on 12-9-14.
//  Copyright (c) 2012骞�__MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "GXJsonUtil.H"
#include "_internal/Source/JSONNode.h"
#include "libjson.h"
#include "GXFadeToCreator.h"
#include "GXDelayTimeCreator.h"
#include "GXSequenceCreator.h"
#include "GXPlayAudioEffectCreator.h"
#include "GXTintToCreator.h"

using namespace cocos2d;

DiaLayerInfoBean* GXJsonUtil::parseDiaLayerInfoBean(const char* str) {
    JSONNODE* node = json_parse(str);
    if (node == NULL) {
        return NULL;
    }
    return parseDiaLayerInfoBean(node);
}

DiaLayerInfoBean* GXJsonUtil::parseDiaLayerInfoBean(JSONNODE* node) {
    JSONNODE_ITERATOR i = json_begin(node);
    DiaLayerInfoBean* bean = DiaLayerInfoBean::create();
    while (i != json_end(node)){
        json_char *node_name = json_name(*i);
        if (strcmp(node_name, "creatorPriority") == 0) {
            bean->creatorPriority = json_as_int(*i);
        } else if (strcmp(node_name, "pvrName") == 0){
            json_char* tempChar = json_as_string(*i);
            bean->setPvrName(CCString::create(tempChar));
            json_free(tempChar);
        } else if (strcmp(node_name, "nextNodeSfx") == 0){
            json_char* tempChar = json_as_string(*i);
            bean->setCreateNextNodeSfx(CCString::create(tempChar));
            json_free(tempChar);
        } else if (strcmp(node_name, "initSprites") == 0){
            JSONNODE_ITERATOR j = json_begin(*i);
            while (j!=json_end(*i)) {
                bean->initSpriteCreator->addObject(parseGXSpriteCreator(*j));
                j++;
            }
        }
        else if (strcmp(node_name, "talkNodes") == 0){
            JSONNODE_ITERATOR j = json_begin(*i);
            while (j!=json_end(*i)) {
                bean->talkCreatorNodes->addObject(parseTalkNodeCreator(*j));
                j++;
            }
        }
        ++i;
        json_free(node_name);
    }
    json_delete(node);
    
    return bean;
}

TalkNodeCreator* GXJsonUtil::parseTalkNodeCreator(JSONNODE* node) {
    if (node == NULL) {
        return NULL;
    }
    JSONNODE_ITERATOR i = json_begin(node);
    TalkNodeCreator* bean = TalkNodeCreator::create();
    while (i != json_end(node)){
        json_char *node_name = json_name(*i);
        if (strcmp(node_name, "name") == 0) {
            bean->setNameCreator(parseGXLabelTTFCreator(*i));
        } else if (strcmp(node_name, "content") == 0){
            bean->setContentCreator(parseGXLabelBMFontCreator(*i));
        } else if (strcmp(node_name, "typeWriterEffectRate") == 0) {
            bean->_typeWriterEffectRate = json_as_float(*i);
        } else if (strcmp(node_name, "icons") == 0){
            JSONNODE_ITERATOR j = json_begin(*i);
            while (j!=json_end(*i)) {
                bean->iconCreatorArray->addObject(parseGXSpriteCreator(*j));
                j++;
            }
        }
        ++i;
        json_free(node_name);
    }
    //    json_delete(node);
    return bean;
}

GXSpriteCreator* GXJsonUtil::parseGXSpriteCreator(JSONNODE* node) {
    if (node == NULL) {
        return NULL;
    }
    JSONNODE_ITERATOR i = json_begin(node);
    GXSpriteCreator* bean = GXSpriteCreator::create();
    while (i != json_end(node)){
        json_char *node_name = json_name(*i);
        if (strcmp(node_name, "frameName") == 0) {
            json_char* tempChar = json_as_string(*i);
            bean->setFrameName(CCString::create(tempChar));
            json_free(tempChar);
        } else if (strcmp(node_name, "x") == 0){
            bean->x = json_as_float(*i);
        } else if (strcmp(node_name, "y") == 0){
            bean->y = json_as_float(*i);
        } else if (strcmp(node_name, "scaleX") == 0){
            bean->scaleX = json_as_float(*i);
        } else if (strcmp(node_name, "scaleY") == 0){
            bean->scaleY = json_as_float(*i);
        } else if (strcmp(node_name, "anchorX") == 0) {
            bean->anchorX = json_as_float(*i);
        } else if (strcmp(node_name, "anchorY") == 0) {
            bean->anchorY = json_as_float(*i);
        } else if (strcmp(node_name, "a") == 0) {
            bean->a = json_as_int(*i);
        } else if (strcmp(node_name, "r") == 0) {
            bean->r = json_as_int(*i);
        } else if (strcmp(node_name, "g") == 0) {
            bean->g = json_as_int(*i);
        } else if (strcmp(node_name, "b") == 0) {
            bean->b = json_as_int(*i);
        } else if (strcmp(node_name, "relativeType") == 0) {
            bean->relativeType = json_as_int(*i);
        } else if (strcmp(node_name, "zOrder") == 0) {
            bean->zOrder = json_as_int(*i);
        } else if (strcmp(node_name, "isFlipX") == 0) {
            bean->isFilpX = json_as_int(*i);
        } else if (strcmp(node_name, "action") == 0) {
            bean->setActionCreator(parseGXActionCreator(*i));
        }
        ++i;
        json_free(node_name);
    }
    //    json_delete(node);
    
    return bean;
}

GXLabelTTFCreator* GXJsonUtil::parseGXLabelTTFCreator(JSONNODE* node) {
    if (node == NULL) {
        return NULL;
    }
    JSONNODE_ITERATOR i = json_begin(node);
    GXLabelTTFCreator* bean = GXLabelTTFCreator::create();
    while (i != json_end(node)){
        json_char *node_name = json_name(*i);
        if (strcmp(node_name, "content") == 0) {
            json_char* tempChar = json_as_string(*i);
            bean->setContent(CCString::create(tempChar));
            json_free(tempChar);
        }
        else if (strcmp(node_name, "x") == 0){
            bean->x = json_as_float(*i);
        } else if (strcmp(node_name, "y") == 0){
            bean->y = json_as_float(*i);
        } else if (strcmp(node_name, "scaleX") == 0){
            bean->scaleX = json_as_float(*i);
        } else if (strcmp(node_name, "scaleY") == 0){
            bean->scaleY = json_as_float(*i);
        } else if (strcmp(node_name, "anchorX") == 0) {
            bean->anchorX = json_as_float(*i);
        } else if (strcmp(node_name, "anchorY") == 0) {
            bean->anchorY = json_as_float(*i);
        } else if (strcmp(node_name, "a") == 0) {
            bean->a = json_as_int(*i);
        } else if (strcmp(node_name, "r") == 0) {
            bean->r = json_as_int(*i);
        } else if (strcmp(node_name, "g") == 0) {
            bean->g = json_as_int(*i);
        } else if (strcmp(node_name, "b") == 0) {
            bean->b = json_as_int(*i);
        } else if (strcmp(node_name, "relativeType") == 0) {
            bean->relativeType = json_as_int(*i);
        } else if (strcmp(node_name, "relativeDWidthType") == 0) {
            bean->relativeDWidthType = json_as_int(*i);
        } else if (strcmp(node_name, "zOrder") == 0) {
            bean->zOrder = json_as_int(*i);
        } else if (strcmp(node_name, "size") == 0) {
            bean->size = json_as_int(*i);
        } else if (strcmp(node_name, "dimensionsWidth") == 0) {
            bean->dimensionsWidth = json_as_float(*i);
        } else if (strcmp(node_name, "dimensionsHeight") == 0) {
            bean->dimensionsHeight = json_as_float(*i);
        } else if (strcmp(node_name, "textAlignment") == 0) {
            int index = json_as_int(*i);
            if (index == 0) {
                bean->textAlignment = kCCTextAlignmentLeft;
            } else if(index == 1) {
                bean->textAlignment = kCCTextAlignmentCenter;
            } else if(index == 2) {
                bean->textAlignment = kCCTextAlignmentRight;
            }
            
        } else if (strcmp(node_name, "verticalAlignment") == 0) {
            int index = json_as_int(*i);
            if (index == 0) {
                bean->verticalAlignment = kCCVerticalTextAlignmentTop;
            } else if(index == 1) {
                bean->verticalAlignment = kCCVerticalTextAlignmentCenter;
            } else if(index == 2) {
                bean->verticalAlignment = kCCVerticalTextAlignmentBottom;
            }
        }
        ++i;
        json_free(node_name);
    }
    //    json_delete(node);
    
    return bean;
}

GXActionCreator* GXJsonUtil::parseGXActionCreator(JSONNODE* node) {
    if (node == NULL) {
        return NULL;
    }
    JSONNODE_ITERATOR i = json_begin(node);
    GXActionCreator* creator = NULL;
    while (i != json_end(node)){
        json_char *node_name = json_name(*i);
        if(strcmp(node_name,"fadeTo") == 0) {
            creator = parseGXFadeToCreator(*i);
        } else if (strcmp(node_name,"delayTime") == 0){
            creator = parseGXDelayTimeCreator(*i);
        } else if (strcmp(node_name,"sequence") == 0) {
            creator = parseGXSequenceCreator(*i);
        }  else if(strcmp(node_name, "playEffect") == 0) {
            creator = parseGXPlayAudioEffectCreator(*i);
        }  else if(strcmp(node_name, "tintTo") == 0) {
            creator = parseGXTintToCreator(*i);
        }
        ++i;
        json_free(node_name);
    }
    return creator;
}

GXActionCreator* GXJsonUtil::parseGXFadeToCreator(JSONNODE* node) {
    if (node == NULL) {
        return NULL;
    }
    JSONNODE_ITERATOR i = json_begin(node);
    GXFadeToCreator* creator = GXFadeToCreator::create();
    while (i != json_end(node)){
        json_char *node_name = json_name(*i);
        if(strcmp(node_name,"duration") == 0) {
            creator->_duration = json_as_float(*i);
        } else if(strcmp(node_name, "targetOpacity") == 0) {
            creator->_targetOpacity = json_as_int(*i);
        } else if(strcmp(node_name, "oriOpacity") == 0) {
            creator->_oriOpacity = json_as_int(*i);
        }
        ++i;
        json_free(node_name);
    }
    return creator;
}

GXActionCreator* GXJsonUtil::parseGXDelayTimeCreator(JSONNODE* node) {
    if (node == NULL) {
        return NULL;
    }
    JSONNODE_ITERATOR i = json_begin(node);
    GXDelayTimeCreator* creator = GXDelayTimeCreator::create();
    while (i != json_end(node)){
        json_char *node_name = json_name(*i);
        if(strcmp(node_name,"duration") == 0) {
            creator->duration = json_as_float(*i);
        }
        ++i;
        json_free(node_name);
    }
    return creator;
}

GXActionCreator* GXJsonUtil::parseGXSequenceCreator(JSONNODE* node) {
    if (node == NULL) {
        return NULL;
    }
    JSONNODE_ITERATOR i = json_begin(node);
    GXSequenceCreator* creator = GXSequenceCreator::create();
    while (i != json_end(node)){
        creator->actionCreatorArray->addObject(parseGXActionCreator(*i));
        ++i;
    }
    return creator;
}

GXActionCreator* GXJsonUtil::parseGXPlayAudioEffectCreator(JSONNODE* node) {
    if (node == NULL) {
        return NULL;
    }
    JSONNODE_ITERATOR i = json_begin(node);
    GXPlayAudioEffectCreator* creator = GXPlayAudioEffectCreator::create();
    while (i != json_end(node)){
        json_char *node_name = json_name(*i);
        if(strcmp(node_name,"effectName") == 0) {
            json_char* tempChar = json_as_string(*i);
            creator->setEffectName(CCString::create(tempChar));
            json_free(tempChar);
        }
        ++i;
        json_free(node_name);
    }
    return creator;
}

GXActionCreator* GXJsonUtil::parseGXTintToCreator(JSONNODE* node) {
    if (node == NULL) {
        return NULL;
    }
    JSONNODE_ITERATOR i = json_begin(node);
    GXTintToCreator* creator = GXTintToCreator::create();
    while (i != json_end(node)){
        json_char *node_name = json_name(*i);
        if(strcmp(node_name,"duration") == 0) {
            creator->duration = json_as_int(*i);
        } else if(strcmp(node_name,"r") == 0) {
            creator->r = json_as_int(*i);
        } else if(strcmp(node_name,"g") == 0) {
            creator->g = json_as_int(*i);
        } else if(strcmp(node_name,"b") == 0) {
            creator->b = json_as_int(*i);
        }
        ++i;
        json_free(node_name);
    }
    return creator;
    
}

GXLabelBMFontCreator* GXJsonUtil::parseGXLabelBMFontCreator(JSONNODE* node) {
    if (node == NULL) {
        return NULL;
    }
    JSONNODE_ITERATOR i = json_begin(node);
    GXLabelBMFontCreator* bean = GXLabelBMFontCreator::create();
    while (i != json_end(node)){
        json_char *node_name = json_name(*i);
        if (strcmp(node_name, "content") == 0) {
            json_char* tempChar = json_as_string(*i);
            bean->setContent(CCString::create(tempChar));
            json_free(tempChar);
        } else if (strcmp(node_name, "fntFileName") == 0) {
            json_char* tempChar = json_as_string(*i);
            bean->setFntFileName(CCString::create(tempChar));
            json_free(tempChar);
        }
        else if (strcmp(node_name, "x") == 0){
            bean->x = json_as_float(*i);
        } else if (strcmp(node_name, "y") == 0){
            bean->y = json_as_float(*i);
        } else if (strcmp(node_name, "scaleX") == 0){
            bean->scaleX = json_as_float(*i);
        } else if (strcmp(node_name, "scaleY") == 0){
            bean->scaleY = json_as_float(*i);
        } else if (strcmp(node_name, "anchorX") == 0) {
            bean->anchorX = json_as_float(*i);
        } else if (strcmp(node_name, "anchorY") == 0) {
            bean->anchorY = json_as_float(*i);
        } else if (strcmp(node_name, "a") == 0) {
            bean->a = json_as_int(*i);
        } else if (strcmp(node_name, "r") == 0) {
            bean->r = json_as_int(*i);
        } else if (strcmp(node_name, "g") == 0) {
            bean->g = json_as_int(*i);
        } else if (strcmp(node_name, "b") == 0) {
            bean->b = json_as_int(*i);
        } else if (strcmp(node_name, "size") == 0) {
            bean->size = json_as_int(*i);
        } else if (strcmp(node_name, "relativeType") == 0) {
            bean->relativeType = json_as_int(*i);
        } else if (strcmp(node_name, "relativeDWidthType") == 0) {
            bean->relativeDWidthType = json_as_int(*i);
        } else if (strcmp(node_name, "zOrder") == 0) {
            bean->zOrder = json_as_int(*i);
        } else if (strcmp(node_name, "width") == 0) {
            bean->labelWidth = json_as_float(*i);
        }else if (strcmp(node_name, "textAlignment") == 0) {
            int index = json_as_int(*i);
            if (index == 0) {
                bean->textAlignment = kCCTextAlignmentLeft;
            } else if(index == 1) {
                bean->textAlignment = kCCTextAlignmentCenter;
            } else if(index == 2) {
                bean->textAlignment = kCCTextAlignmentRight;
            }
            
        }
        ++i;
        json_free(node_name);
    }
    //    json_delete(node);
    
    return bean;
}
