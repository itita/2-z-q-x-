//
//  ServerScene.h
//  ww4
//
//  Created by xiao tang on 13-4-24.
//
//

#ifndef __ww4__ServerScene__
#define __ww4__ServerScene__

#include <iostream>
#include "GXBaseScene.h"
#include "LoginTrigger.h"
#include "MyMessageManage.h"
#include "ServerSelectScroll.h"

#define upTipTag 13
#define downTipTag 14

#define normalTag 2
#define weihuTag 3
#define baomanTag 4
#define tuijianTag 5

class SeverInfoBean : public CCObject {
    
public:
    SeverInfoBean():
    serverId(-1),
    serverStatusId(-1),
    serverName(NULL),
    serverStatus(NULL),
    hostUrl(NULL),
    chatServerUrl(NULL){
        
    }
    
    ~SeverInfoBean() {
        CC_SAFE_RELEASE_NULL(serverName);
        CC_SAFE_RELEASE_NULL(serverStatus);
        CC_SAFE_RELEASE_NULL(hostUrl);
        CC_SAFE_RELEASE_NULL(chatServerUrl);
    }
    
    static SeverInfoBean* create();
    
    int serverId;
    int serverStatusId;
    CC_SYNTHESIZE_RETAIN(CCString*,serverName,ServerName);
    CC_SYNTHESIZE_RETAIN(CCString*,serverStatus,ServerStatus);
    CC_SYNTHESIZE_RETAIN(CCString*,hostUrl,HostUrl);
    CC_SYNTHESIZE_RETAIN(CCString*,chatServerUrl,ChatServerUrl);
    
    
};

class ServerScene : public GXBaseScene,public cocos2d::CCIMEDelegate,public cocos2d::CCTextFieldDelegate, public CCKeypadDelegate{
    
public:
    
    ServerScene():
    loginUsernameTextField(NULL),
    loginPasswordTextField(NULL),
    registerUsernameTextField(NULL),
    registerPasswordTextField(NULL),
    registerSurePasswordTextField(NULL),
    registerNicknameTextField(NULL),
    registerMailTextField(NULL),
    registerSignatureTextField(NULL),
    loginTrigger(NULL),
    isFast(false),
    scroll(NULL),
    beans(NULL),
    cacheServerId(-1),
    selectBean(NULL),
    cacheChatServerUrl(NULL)
    {}
    
    virtual ~ServerScene();
    
    static ServerScene* create();
    void myInit();
    virtual void loadResource();
    virtual void releaseResource();
    void toLogin();
    void toRegister();
    void toServerList();
    void toDisplayLogin(CCMenuItem* item);
    void toDisplayRegister(CCMenuItem* item);
    void toAttachIME(CCMenuItem* item);
    CCTextFieldTTF* loginUsernameTextField;
    CCTextFieldTTF* loginPasswordTextField;
    CCTextFieldTTF* registerUsernameTextField;
    CCTextFieldTTF* registerPasswordTextField;
    CCTextFieldTTF* registerSurePasswordTextField;
    CCTextFieldTTF* registerNicknameTextField;
    CCTextFieldTTF* registerMailTextField;
    CCTextFieldTTF* registerSignatureTextField;
    
    void toSureRegister();
    void dismissTip(CCNode* pSender);
    void loginEnterGameWait();
    void loginEnterGame();
    void fastEnterGameWait();
    void fastEnterGame();
    void registerGameWait();
    void registerGame();
    virtual void exitGame();
    void updateGame();
    
    void toStartScene();
    bool isFast;

    LoginTrigger* loginTrigger;
    
    virtual void onEnter(void);
    virtual void onExit(void);
    virtual void onEnterTransitionDidFinish();
    
    //Android 返回键
    
    virtual void keyBackClicked();
    int cacheServerId;
    CC_SYNTHESIZE_RETAIN(CCString*,cacheChatServerUrl,CacheChatServerUrl);
    
    void toChangeServer(CCMenuItem* item);
    void toCancelServer(CCMenuItem* item);
    void initServerInfo(SeverInfoBean* bean);
    SeverInfoBean* getSelectBean() {
        return selectBean;
    }
//    virtual void onEnterTransitionDidFinish();
    
    //Android 菜单键
    
//    virtual void keyMenuClicked();
protected:
    ServerSelectScroll* scroll;
    CCArray* beans;
    int cacheServerIndex;
    SeverInfoBean* selectBean;
    
    
    
};

class UserBean : public CCObject {
    
public:
    
    ~UserBean() {
        CC_SAFE_RELEASE_NULL(ititaId);
        CC_SAFE_RELEASE_NULL(password);
        CC_SAFE_RELEASE_NULL(nickname);
        CC_SAFE_RELEASE_NULL(QQ);
        CC_SAFE_RELEASE_NULL(signature);
        CC_SAFE_RELEASE_NULL(avatar);
    }
    
    UserBean():
    ititaId(NULL),
    password(NULL),
    nickname(NULL),
    QQ(NULL),
    signature(NULL),
    avatar(NULL){
        
    }
    static UserBean* create();
    CC_SYNTHESIZE_RETAIN(CCString*,ititaId,ItitaId);
    CC_SYNTHESIZE_RETAIN(CCString*,password,Password);
    CC_SYNTHESIZE_RETAIN(CCString*,nickname,Nickname);
    CC_SYNTHESIZE_RETAIN(CCString*,QQ,QQ);
    CC_SYNTHESIZE_RETAIN(CCString*,signature,Signature);
    CC_SYNTHESIZE_RETAIN(CCString*,avatar,Avatar);
};



#endif /* defined(__ww4__ServerScene__) */
