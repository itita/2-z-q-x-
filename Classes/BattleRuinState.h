//
//  BattleRuinState.h
//  ww3
//
//  Created by xiao tang on 12-12-3.
//
//

#ifndef ww3_BattleRuinState_h
#define ww3_BattleRuinState_h
#include "MyBattleState.h"

class BattleRuinState :public MyBattleState{
    
public:
    static BattleRuinState* create(int _stateId,const std::string& spriteName);
    int currentId;
    virtual void doStart();
    virtual CCSprite* getItem();
private:
    std::string spriteName;

};

#endif
