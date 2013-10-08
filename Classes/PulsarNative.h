//
//  PulsarNative.h
//  ww2
//
//  Created by DingYu Fu on 12-9-16.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#ifndef ww2_PulsarNative_h
#define ww2_PulsarNative_h

class PulsarNative {
    
public:
    static const char* getDeviceId();
//    static const char* getItitaId();
    static void toSetting();
    static void showExitMessage();
    static void toShow();
    static void toHome();
    static void toLoginOrRegister();
//    static void setItitaId(std::string _ititaId);
    static void toPurchase(int position);
    static const char* getServerInfos();
    static const char* getItitaChannel();
    static void setServerInfoStr();
    static void toUpdateGame();
#if   (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    static void thirdAccountlogout();
    static void thirdAccountlogin();
    static void thirdGuestLogin();
    static void thirdExitGame();
#endif
    static int userId;
    static int serverId;
//    static int getDisplayWidth();
//    static int getDisplayHeight();
private:
    static std::string deviceId;
//    static std::string ititaId;
    static std::string serverInfoStr;
    static std::string ititaChannelStr;
    
};

#endif
