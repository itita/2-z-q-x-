//
//  GXLabelTTFCreator.cpp
//  Dialog2
//
//  Created by xiao tang on 13-8-21.
//
//

#include "GXLabelTTFCreator.h"

GXLabelTTFCreator* GXLabelTTFCreator::create() {
    GXLabelTTFCreator* bean = new GXLabelTTFCreator();
    bean->autorelease();
    return bean;
}

CCLabelTTF* GXLabelTTFCreator::getLabel() {
    if (content != NULL) {
        CCLabelTTF* label = NULL;
        if(relativeDWidthType == relativeDWidthZeroType) {
            label = CCLabelTTF::create(content->getCString(),"Arial",size,CCSizeMake(dimensionsWidth,dimensionsHeight),textAlignment,verticalAlignment);
        } else if(relativeDWidthType == relativeDWidthCenterType) {
            label = CCLabelTTF::create(content->getCString(),"Arial",size,CCSizeMake(winSize.width/2 + dimensionsWidth, dimensionsHeight),textAlignment,verticalAlignment);
        } else if(relativeDWidthType == relativeDWidthWidthType) {
            label = CCLabelTTF::create(content->getCString(),"Arial",size,CCSizeMake(winSize.width + dimensionsWidth, dimensionsHeight),textAlignment,verticalAlignment);
        }
        if (relativeType == relativeZeroType) {
            label->setPosition(ccp(x,y));
        } else if(relativeType == relativeCenterType) {
            label->setPosition(ccp(winSize.width/2+x,y));
        } else if(relativeType == relativeWidthType) {
            label->setPosition(ccp(winSize.width+x,y));
        }
        label->setScaleX(scaleX);
        label->setScaleY(scaleY);
        label->setAnchorPoint(ccp(anchorX,anchorY));
        label->setColor(ccc3(r,g,b));
        label->setOpacity(a);
        label->_setZOrder(zOrder);
        return label;
    }
    return NULL;
}