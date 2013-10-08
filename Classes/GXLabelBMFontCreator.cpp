//
//  GXLabelBMFontCreator.cpp
//  ww4
//
//  Created by xiao tang on 13-9-7.
//
//

#include "GXLabelBMFontCreator.h"
#include "GXUtil.h"
#include "GarbageResourceCollection.h"


GXLabelBMFontCreator* GXLabelBMFontCreator::create() {
    GXLabelBMFontCreator* bean = new GXLabelBMFontCreator();
    bean->autorelease();
    return bean;
}

CCLabelBMFont* GXLabelBMFontCreator::getLabel() {
    if (content != NULL) {
        CCLabelBMFont* label = NULL;
        if(relativeDWidthType == relativeDWidthZeroType) {
            int count = labelWidth/(size*scaleX);
            label = CCLabelBMFont::create(GXUtil::insertNewline(content->getCString(),count).c_str(),getFntFileName()->getCString(),-1,textAlignment,CCPointZero);
        } else if(relativeDWidthType == relativeDWidthCenterType) {
            int count = (winSize.width/2 + labelWidth)/(size*scaleX);
            label = CCLabelBMFont::create(GXUtil::insertNewline(content->getCString(),count).c_str(),getFntFileName()->getCString(),-1,textAlignment,CCPointZero);
        } else if(relativeDWidthType == relativeDWidthWidthType) {
            int count = (winSize.width + labelWidth)/(size*scaleX);
            label = CCLabelBMFont::create(GXUtil::insertNewline(content->getCString(),count).c_str(),getFntFileName()->getCString(),-1,textAlignment,CCPointZero);
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
        //字体先不频繁加载，所以不能垃圾回收
//        GarbageResourceCollection::getInstance()->addGarbage(getFntFileName()->getCString(),getFntFileName());
        return label;
    }
    return NULL;
}