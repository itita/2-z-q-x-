//
//  ServerScene2.h
//  ww4
//
//  Created by xiao tang on 13-9-17.
//
//

#ifndef __ww4__ServerScene2__
#define __ww4__ServerScene2__

#include "ServerScene.h"

class ServerScene2 : public ServerScene {
public:
    
    ServerScene2();
        
    static ServerScene2* create();
    void myInit();
    virtual void loadResource();
//    virtual void releaseResource();
    void toLogin();
    void toRegister();
    void toServerList();
    void toDisplayLogin(CCMenuItem* item);
    void toDisplayRegister(CCMenuItem* item);
    void toChangeServer(CCMenuItem* item);
    void toCancelServer(CCMenuItem* item);
    
private:

    void initServerInfo(SeverInfoBean* bean);
    
};

#endif /* defined(__ww4__ServerScene2__) */
