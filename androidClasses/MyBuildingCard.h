//
//  MyBuildingCard.h
//  ww2
//
//  Created by xiao tang on 12-10-10.
//
//

#ifndef ww2_MyBuildingCard_h
#define ww2_MyBuildingCard_h
#include "MyMenuItem.h"
#include "cocos2d.h"
#include "GXCreator.h"
#include "GXAntiCrack.h"

using namespace cocos2d;

class MyBuildingCard :public MyMenuItem {
    
public:
    
    ~MyBuildingCard() {
        CC_SAFE_RELEASE_NULL(resourceTag);
        CC_SAFE_RELEASE_NULL(summaryCount);
        CC_SAFE_RELEASE_NULL(unlockLevel);
    }
    
    int cardId;
    int count;
    int maxCount;
    GXintValue* unlockLevel;
   
    const char* name;
    MyBuildingCard():
    cardId(0),
    maxCount(0),
    count(0),
    name(""),
    isEnabled(true),
    detailButton(NULL)
    {
        resourceTag = GXintValue::create(0);
        resourceTag->retain();
        summaryCount = GXintValue::create(0);
        summaryCount->retain();
        unlockLevel = GXintValue::create(0);
        unlockLevel->retain();
    }
    
    static MyBuildingCard* create(CCSprite* buildingSprite,int cardId,int maxCount,int count,int resourceTag,int summaryCount,const char* name,cocos2d::CCObject *rec, SEL_MenuHandler selector);
    static MyBuildingCard* create(CCSprite* buildingSprite,int cardId,int maxCount,int count,int resourceTag,int summaryCount,int unlockLevel,const char* name,cocos2d::CCObject *rec, SEL_MenuHandler selector);
    virtual void init(CCSprite* buildingSprite,int cardId, int maxCount,int count, int resourceTag,int summaryCount, const char *name,int unlockLevel);
    virtual void displayDetail(CCNode* psender);
    virtual void cancelDetail(CCNode* psender);
    virtual void selected();
    virtual void unselected();
    virtual void activate();
    
    virtual int getResourceTag();
    virtual int getSummaryCount();
    virtual void setUnlockLevel(int _unlockLevel);
    virtual int getUnlockLevel();
    
    bool isEnabled;
    static MyBuildingCard* activeCard;
private:
    
    CCPoint oriPosition;
    virtual void reorderCall();
    virtual void toggleDetail(cocos2d::CCNode *pSender);
    CCMenuItemToggle* detailButton;
    GXintValue* resourceTag;
    GXintValue* summaryCount;
};

class MyBuildingCardCreator : public GXCreator {
    
public:
    virtual CCObject* init();
    virtual void doFill(CCObject* entity);
    
    
};

#endif
