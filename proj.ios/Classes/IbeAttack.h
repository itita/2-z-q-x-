//
//  IbeAttack.h
//  ww2
//
//  Created by DingYu Fu on 12-9-13.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#ifndef ww2_IbeAttack_h
#define ww2_IbeAttack_h

class IbeAttack {
    
public:
    IbeAttack():
    life(0),
    maxLife(0){}
    
    virtual bool setLife(float _life);
    virtual float getLife();
    float getMaxLife() {return maxLife;}
    virtual void setMaxLife(float maxLife);
protected:
    float life;
    float maxLife;
};

#endif
