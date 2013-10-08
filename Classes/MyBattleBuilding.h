//
//  MyBattleBuilding.h
//  ww3
//
//  Created by xiao tang on 12-12-3.
//
//
#define mainTiledSpriteTag 10
#ifndef ww3_MyBattleBuilding_h
#define ww3_MyBattleBuilding_h
#include "cocos2d.h"
#include "GXFSMclass.h"
#include "GXFSMstate.h"
#include "MyTiledInfo.h"
#include "AliveInterface.h"
#include "GXAntiCrack.h"

typedef void (*SEL_SetBattleLevel)(int,GXFSM*);

using namespace cocos2d;

class MyBattleBuilding :public CCLayer,public MyTiledInfo,public AliveInterface{
    
public:
    GXFSM* fsm;
    MyBattleBuilding():
    maxLevel(0),
    fsm(NULL),
    buildingName(NULL),
    setLevel_selector(NULL){
        level = GXintValue::create(1);
        level->retain();
    };
    static MyBattleBuilding* create(int tag,const CCSize& _contentSizebyTiled,GXFSMstate* state);
    
    ~MyBattleBuilding() {
//        this->fsm->release();
        CC_SAFE_RELEASE_NULL(this->fsm);
        CC_SAFE_RELEASE_NULL(buildingName);
        CC_SAFE_RELEASE_NULL(level);
    }
    virtual void doCurrentState();
    virtual CCPoint getPositionByTiled();
    virtual void setPositionByTiled(const cocos2d::CCPoint &pos);
    //    virtual void showAllTransition();

    virtual void addState(GXFSMstate* state);
    virtual void changeState(int inputId);
    virtual void changeStateById(int id);
    virtual void dispose();
    virtual void displaySummary();
//    virtual bool dismissSummary();
    //这个属性可以交给状态~哎 也不好~毕竟最后什么模式都会显示
    CCSize costRange;
    int getLevel();
    void setLevel(int level);
    
    int getMaxLevel();
    void setMaxLevel(int level);
    
    SEL_SetBattleLevel setLevel_selector;
    
    void setBuildingName(CCString* _buildingName,float _y) {
        CC_SAFE_RELEASE_NULL(buildingName);
        buildingName = _buildingName;
        buildingName->retain();
        y = _y;
    }
    
    const char* getBuildingName() {
        return buildingName->getCString();
    }
    
private:
    GXintValue* level;
    GXintValue* maxLevel;
    CCString* buildingName;
    int y;
    

};

#endif
