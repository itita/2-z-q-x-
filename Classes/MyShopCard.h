//
//  MyShopCard.h
//  ww4
//
//  Created by xiao tang on 13-4-19.
//
//

#ifndef __ww4__MyShopCard__
#define __ww4__MyShopCard__

#include "MyMenuItem.h"
#include "UnitSet.h"
#include "MyBuilding.h"

#include <iostream>

#define noMode 0
#define hotMode 1
#define newMode 2

class MyShopCard : public MyMenuItem {
    
public:
    
    ~MyShopCard() {
        CC_SAFE_RELEASE_NULL(bean);
    }
    MyShopCard():bean(NULL),
    mode(noMode),
    cost(1000),
    buyItem(NULL),
    purchaseSelector(NULL){
    }
    
    int mode;
    int cost;
    CCObject* bean;
    SEL_MenuHandler purchaseSelector;
    static MyShopCard* create(BuildingCreator* buildingBean,int cost,int mode,CCObject *rec, SEL_MenuHandler selector);
    static MyShopCard* create(CCSprite* avatarSprite,const std::string &name,int cost,int mode,CCObject *rec, SEL_MenuHandler selector);
    static MyShopCard* create(const std::string &nameStr,int count,int resourceTag,int cost,int mode,int displayLevel,CCObject* rec);
    static MyShopCard* create(int countNum,float oriCost,float cost,CCObject* rec,int position);
    void setBoughtInfo(bool isBought);
    CCMenuItemSprite* buyItem;
private:
    
};

class ShopResourceBean : public CCObject {
    
public:
    ShopResourceBean():name(NULL) {
        count = GXintValue::create(0);
        count->retain();
        resourceTag = GXintValue::create(0);
        resourceTag->retain();
        cost = GXintValue::create(0);
        cost->retain();
    }
    ~ShopResourceBean() {
        CC_SAFE_RELEASE_NULL(name);
        CC_SAFE_RELEASE_NULL(count);
        CC_SAFE_RELEASE_NULL(resourceTag);
        CC_SAFE_RELEASE_NULL(cost);
    }
    static ShopResourceBean* create(CCString* name,int count,int resourceTag,int cost,int displayLevel);
    
    void setCount(int _count) {
        count->setValue(_count);
    }
    
    void setResourceTag(int _resourceTag) {
        resourceTag->setValue(_resourceTag);
    }
    
    void setCost(int _cost) {
        cost->setValue(_cost);
    }
    
    int getCount() {
        return count->getValue();
    }
    
    int getResourceTag() {
        return resourceTag->getValue();
    }
    
    int getCost() {
        return cost->getValue();
    }
    
    CCString* name;
    int displayLevel;
private:
    GXintValue* count;
    GXintValue* resourceTag;
    GXintValue* cost;
    
};


#endif /* defined(__ww4__MyShopCard__) */
