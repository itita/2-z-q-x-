//
//  MyUnitCard.h
//  ww3
//
//  Created by xiao tang on 12-11-13.
//
//

#ifndef ww3_MyUnitCard_h
#define ww3_MyUnitCard_h
#include "MyMenuItem.h"
#include "MyUnit.h"
#include "MyGameInfo.h"


#define unitSpriteTag 22
#define unitDescrptionTag 23
#define lvFontTag 102

class MyUnitCard : public MyMenuItem {
    
public:
    ~MyUnitCard() {
//        bean->release();
        CC_SAFE_RELEASE_NULL(bean);
    }
    int cardId;
    int count;
    int resourceTag;
    int summaryCount;
    const char* name;
    MyUnitCard():
    isEnabled(true),
    detailButton(NULL),
    bean(NULL)
    {
//        CCLog("unit Card has bean create");
    }
    
    CreatorInfoBean* bean;
    
    static MyUnitCard* create(CreatorInfoBean* bean,cocos2d::CCObject *rec, SEL_MenuHandler selector);
    virtual void init(CCSprite* unitSprite,int cardId,int count, int resourceTag, int summaryCounty, const char *name);
//    virtual void displayDetail(CCNode* psender);
    virtual void updateCallBack(CCNode* pSender);
//    virtual void cancelDetail(CCNode* psender);
//    virtual void selected();
//    virtual void unselected();
//    virtual void activate();
    
    bool isEnabled;
    virtual void setLevel(int level);
    virtual int getLevel();
//    virtual void retain();
    
private:
   
    CCPoint oriPosition;
//    virtual void reorderCall();
//    virtual void toggleDetail(cocos2d::CCNode *pSender);
    CCMenuItemToggle* detailButton;
};

#endif
