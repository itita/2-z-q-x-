//
//  GXLineSprite.cpp
//  ww4
//
//  Created by xiao tang on 13-5-19.
//
//

#include "GXLineSprite.h"

GXLineSprite* GXLineSprite::create(const CCPoint& begin,const CCPoint& end) {
    GXLineSprite * pRet = new GXLineSprite();
	pRet->autorelease();
    pRet->setPosition(begin);
    pRet->setEndPosition(end);
    return pRet;
}

void GXLineSprite::draw(void) {

    
    // line: color, width, aliased
    // glLineWidth > 1 and GL_LINE_SMOOTH are not compatible
    // GL_SMOOTH_LINE_WIDTH_RANGE = (1,1) on iPhone
    //    glDisable(GL_LINE_SMOOTH);
//    glEnable(GL_LINE_SMOOTH);
    glLineWidth( 3.0f );
    ccDrawColor4B(255,0,0,255);
    ccDrawLine( getPosition(), getEndPosition());
   
}

const CCPoint& GXLineSprite::getEndPosition(void) {
    return endPosition;
}
void GXLineSprite::setEndPosition(const CCPoint& var) {
    endPosition = var;
    m_bTransformDirty = m_bInverseDirty = true;
}