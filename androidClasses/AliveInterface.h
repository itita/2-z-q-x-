//
//  AliveInterface.h
//  ww2
//
//  Created by DingYu Fu on 12-9-9.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#ifndef ww2_AliveInterface_h
#define ww2_AliveInterface_h

class AliveInterface {
    
public:
//    AliveInterface():alive(true){};
    AliveInterface();
    virtual bool isAlive();
    virtual void dispose();
    virtual void dispose(int var);
private:
    bool alive;
};

#endif
