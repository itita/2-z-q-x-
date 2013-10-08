////
////  PulsarNative_and.cpp
////  ww2
////
////  Created by DingYu Fu on 12-9-21.
////  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
////
//
//#include <iostream>
//#include "PulsarNative.h"
//#include "../platform/android/jni/JniHelper.h"
//#include "cocos2d.h"
//#include "MyHttpConnection.h"
//#include "ThirdLoginCallBackMessage.h"
//
//using namespace cocos2d;
//
//std::string PulsarNative::deviceId = "";
//std::string PulsarNative::serverInfoStr = "";
//std::string PulsarNative::ititaChannelStr = "";
//int PulsarNative::userId = -1;
//int PulsarNative::serverId = -1;
//
//char* jstringTostring(JNIEnv* env, jstring jstr) {
//	char* rtn = NULL;
//	jclass clsstring = env->FindClass("java/lang/String");
//	jstring strencode = env->NewStringUTF("utf-8");
//	jmethodID mid = env->GetMethodID(clsstring, "getBytes",
//                                     "(Ljava/lang/String;)[B");
//	jbyteArray barr = (jbyteArray) env->CallObjectMethod(jstr, mid, strencode);
//	jsize alen = env->GetArrayLength(barr);
//	jbyte* ba = env->GetByteArrayElements(barr, JNI_FALSE);
//	if (alen > 0) {
//		rtn = (char*) malloc(alen + 1);
//		memcpy(rtn, ba, alen);
//		rtn[alen] = 0;
//	}
//	env->ReleaseByteArrayElements(barr, ba, 0);
//	env->DeleteLocalRef(clsstring);
//	env->DeleteLocalRef(strencode);
//	return rtn;
//}
//
//const char* PulsarNative::getDeviceId() {
//    
//	if (deviceId.compare("") == 0) {
//		JniMethodInfo_ minfo;
//		bool isHave = JniHelper::getStaticMethodInfo(minfo,
//                                                     "com/itita/ww2/Util", "getDeviceId", "()Ljava/lang/String;");
//		jstring jstr;
//		char* tmp;
//		if (isHave) {
//			CCLog("此函数存在");
//			jstr = (jstring) minfo.env->CallStaticObjectMethod(minfo.classID,
//                                                               minfo.methodID);
//			tmp = jstringTostring(minfo.env, jstr);
//		}
//		deviceId.clear();
//		deviceId.append(tmp);
//		cocos2d::CCLog("第一次亲密接触");
//		minfo.env->DeleteLocalRef(jstr);
//        //		return "353561055891745";
//	}
//	return deviceId.c_str();
//    //	return "353561055891745";
//}
//
//void PulsarNative::toSetting() {
//	JniMethodInfo_ minfo;
//	bool isHave = JniHelper::getStaticMethodInfo(minfo, "com/itita/ww2/Util",
//                                                 "toSetting", "()V");
//	if (isHave) {
//		CCLog("此函数存在");
//		minfo.env->CallStaticObjectMethod(minfo.classID, minfo.methodID);
//	}
//}
//
//void PulsarNative::showExitMessage() {
//	JniMethodInfo_ minfo;
//	bool isHave = JniHelper::getStaticMethodInfo(minfo, "com/itita/ww2/Util",
//                                                 "showMessage", "()V");
//	if (isHave) {
//		CCLog("此函数存在");
//		minfo.env->CallStaticObjectMethod(minfo.classID, minfo.methodID);
//	}
//}
//
//void PulsarNative::toShow() {
//    MyHttpConnection::getInstance()->sendDisconnect();
//	JniMethodInfo_ minfo;
//	bool isHave = JniHelper::getStaticMethodInfo(minfo, "com/itita/ww2/Util",
//                                                 "toShow", "()V");
//	if (isHave) {
//		CCLog("此函数存在");
//		minfo.env->CallStaticObjectMethod(minfo.classID, minfo.methodID);
//	}
//}
//
//void PulsarNative::thirdAccountlogout() {
//    MyHttpConnection::getInstance()->sendDisconnect();
//	JniMethodInfo_ minfo;
//	bool isHave = JniHelper::getStaticMethodInfo(minfo, "com/itita/ww2/Util",
//                                                 "Loginout", "()V");
//	if (isHave) {
//		CCLog("91这个SB的注销函数存在");
//		minfo.env->CallStaticObjectMethod(minfo.classID, minfo.methodID);
//	}
//}
//
//void PulsarNative::thirdAccountlogin() {
//    MyHttpConnection::getInstance()->sendDisconnect();
//	JniMethodInfo_ minfo;
//	bool isHave = JniHelper::getStaticMethodInfo(minfo, "com/itita/ww2/Util",
//                                                 "Loginin", "()V");
//	if (isHave) {
//		CCLog("91这个SB的登陆函数存在");
//		minfo.env->CallStaticObjectMethod(minfo.classID, minfo.methodID);
//	}
//}
//
//void PulsarNative::thirdGuestLogin() {
//    MyHttpConnection::getInstance()->sendDisconnect();
//    JniMethodInfo_ minfo;
//    bool isHave = JniHelper::getStaticMethodInfo(minfo, "com/itita/ww2/Util",
//                                                 "QuickLogin", "()V");
//    if (isHave) {
//        CCLog("91这个SB的游客函数存在");
//        minfo.env->CallStaticObjectMethod(minfo.classID, minfo.methodID);
//    }
//}
//
//void PulsarNative::toHome() {
//	JniMethodInfo_ minfo;
//	bool isHave = JniHelper::getStaticMethodInfo(minfo, "com/itita/ww2/Util",
//                                                 "toHome", "()V");
//	if (isHave) {
//		CCLog("此函数存在");
//		minfo.env->CallStaticObjectMethod(minfo.classID, minfo.methodID);
//	}
//}
//
//
//void PulsarNative::toPurchase(int position) {
//    JniMethodInfo_ minfo;
//	bool isHave = JniHelper::getStaticMethodInfo(minfo, "com/itita/ww2/Util",
//                                                 "toPuchase", "(III)V");
//	if (isHave) {
//		CCLog("此函数存在");
//		minfo.env->CallStaticObjectMethod(minfo.classID, minfo.methodID,userId,serverId,serverId);
//	}
//}
//
//const char* PulsarNative::getServerInfos() {
//    if (serverInfoStr.compare("") == 0) {
//        JniMethodInfo_ minfo;
//        bool isHave = JniHelper::getStaticMethodInfo(minfo,
//                                                     "name/wwd/update/ClientIndex", "getServerItems", "()Ljava/lang/String;");
//        jstring jstr;
//        char* tmp;
//        if (isHave) {
//            CCLog("获得服务器信息存在此函数存在");
//            jstr = (jstring) minfo.env->CallStaticObjectMethod(minfo.classID,
//                                                               minfo.methodID);
//            tmp = jstringTostring(minfo.env, jstr);
//        }
//        serverInfoStr.clear();
//        serverInfoStr.append(tmp);
//        minfo.env->DeleteLocalRef(jstr);
//    }
//    
//    return serverInfoStr.c_str();
//}
//
//const char* PulsarNative::getItitaChannel() {
//    if (ititaChannelStr.compare("") == 0) {
//        JniMethodInfo_ minfo;
//        bool isHave = JniHelper::getStaticMethodInfo(minfo,
//                                                     "com/itita/ww2/Util", "getItitaChanael", "()Ljava/lang/String;");
//        jstring jstr;
//        char* tmp;
//        if (isHave) {
//            CCLog("获得渠道号存在此函数存在");
//            jstr = (jstring) minfo.env->CallStaticObjectMethod(minfo.classID,
//                                                               minfo.methodID);
//            tmp = jstringTostring(minfo.env, jstr);
//        }
//        ititaChannelStr.clear();
//        ititaChannelStr.append(tmp);
//        minfo.env->DeleteLocalRef(jstr);
//    }
//    return ititaChannelStr.c_str();
//}
//
//void PulsarNative::toUpdateGame() {
//}
//
//extern "C"
//{
//    /* 命名规则：Java_Java的包名_类名*/
//	jint Java_com_itita_ww_javatoc_thirdlogincallback(JNIEnv *, jobject, jint intvalue)
//    {
//        ThirdLoginCallBackMessage::create(intvalue)->sendMsg();
//    	return 1;
//    }
//}
//
