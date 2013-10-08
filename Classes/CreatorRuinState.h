//
//  CreatorRuinState.h
//  ww3
//
//  Created by xiao tang on 12-10-29.
//
//

#ifndef ww3_CreatorRuinState_h
#define ww3_CreatorRuinState_h
#include "RuinState.h"
#include "MyXueTiao.h"

class CreatorRuinState :public RuinState {
    
public:
    virtual ~CreatorRuinState();
    CreatorRuinState():
    lifePercentage(100),
    xuetiao(NULL)
    {}
    int lifePercentage;
    static CreatorRuinState* create(int _stateId,CCSprite* item,int _lifePercentage);
    virtual void doState();
    MyXueTiao* xuetiao;
    virtual void init(MyBuilding* building);
    
};

//class CreatorRuinStateCreator : public RuinStateCreator {
//    
//public:
//    int lifePercentage;
//    CreatorRuinStateCreator():lifePercentage(100){}
//    
//    static CreatorRuinStateCreator* create();
//    virtual CCObject* init(CCObject* entity);
//
//};

#endif
