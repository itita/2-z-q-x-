//
//  GXScissorNode.cpp
//  ww4
//
//  Created by xiao tang on 13-7-25.
//
//

#include "GXScissorNode.h"
#include "GXScrollView.h"

GXScissorNode* GXScissorNode::create(const CCSize& viewSize,const CCPoint& oriPosition) {
    GXScissorNode * pRet = new GXScissorNode();
	pRet->autorelease();
    pRet->viewSize = viewSize;
    pRet->oriPosition = oriPosition;
	return pRet;
}

void GXScissorNode::visit() {
    glEnable(GL_SCISSOR_TEST);
    //x, y, w, h
    //    CCLog("OX:%f,OY:%f",oriPosition.x,oriPosition.y);
    //    CCLog("Vw:%f,Vh:%f",viewSize.width, viewSize.height);
    
    // 480 320 作为IOS设计大小存在。
    
    //#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    //    glScissor(oriPosition.x, oriPosition.y, viewSize.width , viewSize.height);
    //#endif
    
    // 960 640 作为android设计大小存在
    
    //#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    
    float zoomX = GXScrollView::screenWidthRate;
	float zoomY = GXScrollView::screenHeightRate;
	float orix = oriPosition.x * zoomX;
	float oriy = oriPosition.y * zoomY;
	float viewW = viewSize.width * zoomX;
	float viewH = viewSize.height * zoomY;
	glScissor(orix, oriy, viewW, viewH);
    
    //    float heibian = screenSize.width
    //    - (screenSize.height / 640 * 960);
    //	float zoomX = screenSize.width / 960;
    //	float zoomY = screenSize.height / 640;
    //	float orix = getOriPosition().x * zoomX + heibian / 2;
    //	float oriy = getOriPosition().y * zoomY;
    //	float viewW = viewSize.width * zoomX - heibian;
    //	float viewH = viewSize.height * zoomY;
    //	glScissor(orix, oriy, viewW, viewH);
    //#endif
    
    
    
    
    
    
    //    glScissor(glScissorAdapter(oriPosition.x), glScissorAdapter(oriPosition.y), glScissorAdapter(viewSize.width), glScissorAdapter(viewSize.height));
    
    CCNode::visit();
    
    glDisable(GL_SCISSOR_TEST);
}

