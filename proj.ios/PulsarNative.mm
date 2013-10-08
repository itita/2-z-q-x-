//
//  PulsarNative.cpp
//  ww2
//
//  Created by DingYu Fu on 12-9-16.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "PulsarNative.h"
#include "OpenUDID.h"
#include "cocos2d.h"
#include "MyJsonUtil.h"
#import "PuchaseHandle.h"

std::string PulsarNative::deviceId = "";
//std::string PulsarNative::ititaId = "";
std::string PulsarNative::serverInfoStr = "";
std::string PulsarNative::ititaChannelStr = "";
int PulsarNative::userId = -1;
int PulsarNative::serverId = -1;

const char* PulsarNative::getDeviceId() {
//    [PulsarNative_objc getDeviceId];
//    [[PulsarNative_objc getDeviceId] cStringUsingEncoding:NSUTF8StringEncoding];
    if (deviceId.compare("") == 0) {
        deviceId.clear();
        deviceId.append([[OpenUDID value] cStringUsingEncoding:NSUTF8StringEncoding]);
        cocos2d::CCLog("第一次亲密接触");
    }
    return deviceId.c_str();
//    return "A00000427F0D73";
//    return "354707044336677";
    
}

//const char* PulsarNative::getItitaId() {
//    if (ititaId.compare("") == 0) {
//        return PulsarNative::getDeviceId();
//    }
//    return ititaId.c_str();
//}
//
//void PulsarNative::setItitaId(std::string _ititaId) {
//    ititaId = _ititaId;
//}

void PulsarNative::toSetting() {
//    [[UIApplication sharedApplication] openURL:[NSURL URLWithString:@"prefs:root=General&path=Network"]];
    [[UIApplication sharedApplication] openURL:[NSURL URLWithString:@"prefs:root=General"]];
}


void PulsarNative::showExitMessage() {

}

void PulsarNative::toShow() {
    [[UIApplication sharedApplication] openURL:[NSURL URLWithString:@"http://17erzhan.com/"]];
}

void PulsarNative::toLoginOrRegister() {
    
}

void PulsarNative::toHome() {

}

void PulsarNative::toPurchase(int position) {
    [[PuchaseHandle sharedPuchaseHandle] buy:position ServiceId:serverId UserId:userId ];
}

const char* PulsarNative::getServerInfos() {
//    if (serverInfoStr.compare("") == 0) {
        serverInfoStr = "[{\"serverId\":403,\"serverName\":\"mm1区\",\"serverStatusId\":2,\"serverStatus\":\"火爆\",\"hostUrl\":\"121.199.44.131:8000\",\"chatServerUrl\":\"112.124.27.78:3014\"},{\"serverId\":407,\"serverName\":\"mm2区\",\"serverStatusId\":2,\"serverStatus\":\"火爆\",\"hostUrl\":\"121.199.61.84:8000\",\"chatServerUrl\":\"112.124.27.78:3014\"},{\"serverId\":998,\"serverName\":\"本地服务器\",\"serverStatusId\":2,\"serverStatus\":\"火爆\",\"hostUrl\":\"192.168.1.222:8000\",\"chatServerUrl\":\"192.168.1.100:3014\"},{\"serverId\":999,\"serverName\":\"我的服务器\",\"serverStatusId\":2,\"serverStatus\":\"火爆\",\"hostUrl\":\"192.168.1.111:8000\",\"chatServerUrl\":\"192.168.1.100:3014\"},{\"serverId\":406,\"serverName\":\"焦总服务器\",\"serverStatusId\":2,\"serverStatus\":\"火爆\",\"hostUrl\":\"192.168.1.100:8000\",\"chatServerUrl\":\"192.168.1.100:3014\"},{\"serverId\":416,\"serverName\":\"SVN服务器\",\"serverStatusId\":5,\"serverStatus\":\"推荐\",\"hostUrl\":\"112.124.32.61:8000\",\"chatServerUrl\":\"112.124.32.61:3014\"},{\"serverId\":412,\"serverName\":\"市场服务器\",\"serverStatusId\":5,\"serverStatus\":\"推荐\",\"hostUrl\":\"112.124.48.45:8000\",\"chatServerUrl\":\"112.124.27.78:3014\"},{\"serverId\":404,\"serverName\":\"电信服务器\",\"serverStatusId\":5,\"serverStatus\":\"推荐\",\"hostUrl\":\"112.124.45.15:8000\",\"chatServerUrl\":\"112.124.27.78:3014\"},{\"serverId\":408,\"serverName\":\"苹果服务器\",\"serverStatusId\":5,\"serverStatus\":\"推荐\",\"hostUrl\":\"112.124.50.6:8000\",\"chatServerUrl\":\"112.124.27.78:3014\"},{\"serverId\":1000,\"serverName\":\"新服务器\",\"serverStatusId\":5,\"serverStatus\":\"推荐\",\"hostUrl\":\"112.124.27.78:8000\",\"chatServerUrl\":\"112.124.27.78:3014\"}]";
//       return "{}";
//    }
    return serverInfoStr.c_str();
}

void PulsarNative::setServerInfoStr() {
    // 初始化請求
    NSMutableURLRequest *request = [[NSMutableURLRequest alloc] init];
    // 設置URL
    
    NSString *version = [[[NSBundle mainBundle] infoDictionary] objectForKey:(NSString *)kCFBundleVersionKey];
    NSString *baoming = [[[NSBundle mainBundle] infoDictionary] objectForKey:(NSString *)kCFBundleIdentifierKey];
    
    NSString* URL = [NSString stringWithFormat:@"http://121.199.27.213:81/Master/client/index?source=ios&channlePackageName=%@&versionCode=%@",baoming, version ];
//    NSLog(URL);
    
    [request setURL:[NSURL URLWithString:URL]];
    // 設置HTTP方法
    [request setHTTPMethod:@"GET"];
    // 發送同步請求, 這裡得returnData就是返回得數據楽
    NSData *returnData = [NSURLConnection sendSynchronousRequest:request    returningResponse:nil error:nil];
    const char* str = "";
    if (returnData != nil) {
        NSString * strData1= [[NSString alloc] initWithData:returnData encoding:NSUTF8StringEncoding];
        str = [strData1 cStringUsingEncoding:NSUTF8StringEncoding];
        [strData1 release];
        [URL release];
    }
//    else {
//        void *buf = malloc(1);
//        returnData = [NSData dataWithBytes:buf length:1];
//    }
    
//    serverInfoStr.append();
    // 釋放對象
    

    [request release];
//    [version release];
//    [baoming release];
    
    const char* str2 = MyJsonUtil::parseGameInfo(str);
    serverInfoStr.clear();
    serverInfoStr.append(str2);
    delete str2;
}

const char* PulsarNative::getItitaChannel() {
    if (ititaChannelStr.compare("") == 0) {
        ititaChannelStr = "APPSTORE";
    }
    return ititaChannelStr.c_str();
}

void PulsarNative::toUpdateGame() {
    [[UIApplication sharedApplication] openURL:[NSURL URLWithString:@"itms-apps://phobos.apple.com/WebObjects/MZStore.woa/wa/viewSoftware?id=649859980"]];
}
#if   (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
void PulsarNative::thirdAccountlogout(){

}

void PulsarNative::thirdAccountlogin(){

}

#endif

//int PulsarNative::getDisplayWidth() {
//    return 960;
//}
//
//int PulsarNative::getDisplayHeight() {
//    return 960;
//}

