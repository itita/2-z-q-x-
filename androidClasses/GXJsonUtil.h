//
//  GXJsonUtil.h
//  ww2
//
//  Created by DingYu Fu on 12-9-14.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#ifndef ww2_GXJsonUtil_h
#define ww2_GXJsonUtil_h

#include "cocos2d.h"
#include "libjson.h"
#include "GXSpriteCreator.h"
#include "GXLabelTTFCreator.h"
#include "GXLabelBMFontCreator.h"
#include "TalkNode.h"
#include "DiaLayer.h"

using namespace cocos2d;

class GXJsonUtil {
    
public:
    static DiaLayerInfoBean* parseDiaLayerInfoBean(const char* str);
    static DiaLayerInfoBean* parseDiaLayerInfoBean(JSONNODE* node);
    static TalkNodeCreator* parseTalkNodeCreator(JSONNODE* node);
    static GXSpriteCreator* parseGXSpriteCreator(JSONNODE* node);
    static GXLabelTTFCreator* parseGXLabelTTFCreator(JSONNODE* node);
    static GXActionCreator* parseGXActionCreator(JSONNODE* node);
    static GXActionCreator* parseGXFadeToCreator(JSONNODE* node);
    static GXActionCreator* parseGXDelayTimeCreator(JSONNODE* node);
    static GXActionCreator* parseGXSequenceCreator(JSONNODE* node);
    static GXActionCreator* parseGXPlayAudioEffectCreator(JSONNODE* node);
    static GXActionCreator* parseGXTintToCreator(JSONNODE* node);
    static GXLabelBMFontCreator* parseGXLabelBMFontCreator(JSONNODE* node);
};

#endif
