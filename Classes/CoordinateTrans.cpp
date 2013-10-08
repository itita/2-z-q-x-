//
//  CoordinateTrans.cpp
//  ww2
//
//  Created by xiao tang on 12-9-28.
//
//

//inretina 指的的是在retina的坐标系下开发，其中winsize contentsize position都变小一半的情况，但是屏幕坐标不变的情况

#include "CoordinateTrans.h"
#include "cocos2d.h"

CCSize CoordinateTrans::transWindowToGLInRetina(const cocos2d::CCSize &_size) {
//android
//#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)  
    return CCSizeMake(_size.width*2, _size.height*2);
//#endif
////ios retina
//#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
//    return CCSizeMake(_size.width, _size.height);
//#endif
}

CCPoint CoordinateTrans::transWindowToGLInRetina(const cocos2d::CCPoint &_point) {
//android
//#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    return ccp(_point.x *2, _point.y*2);
//#endif
////ios retina
//#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
//    return ccp(_point.x, _point.y);
//#endif
}

CCPoint CoordinateTrans::transWindowToGLInRetina(float x,float y) {
//android
//#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    return ccp(x*2,y*2);
//#endif
////ios retina
//#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
//    return ccp(x,y);
//#endif
}

float CoordinateTrans::transWindowToGLInRetina(float f) {
    //android
//#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    return f*2;
//#endif
//    //ios retina
//#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
//    return f;
//#endif
    //
}

int CoordinateTrans::transWindowToGLInRetinaInt(int f) {
    //android
//#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    return f*2;
//#endif
    //    //ios retina
//#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
//    return f;
//#endif
    //
}

//地图块用到了此方法，所以是反的
CCSize CoordinateTrans::transTiledSizeInRetina(const cocos2d::CCSize &_size) {
//android
//#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    return CCSizeMake(_size.width, _size.height);
//#endif
//ios retina
//#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
//    return CCSizeMake(_size.width/2, _size.height/2);
//#endif
}


CCSize CoordinateTrans::transTiledSizeInRetina(float x,float y) {
    //android
//#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    return CCSizeMake(x*2, y*2);
//#endif
    //ios retina
//#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
//    return CCSizeMake(x, y);
//#endif
}

int CoordinateTrans::glScissorAdapter(float x) {
//android
//#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    return x/2;
//#endif
//ios retina
//#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
//    return x*2;
//#endif
}