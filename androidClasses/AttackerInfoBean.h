//
//  AttackerInfoBean.h
//  ww4
//
//  Created by xiao tang on 13-6-15.
//
//

#ifndef __ww4__AttackerInfoBean__
#define __ww4__AttackerInfoBean__

#include "cocos2d.h"
#include "DefineSet.h"
#include "GXUtil.h"
#include "MyGameInfo.h"
#include "GarbageResourceCollection.h"

using namespace cocos2d;

class AttackerInfoBean : public cocos2d::CCObject {
    
public:
    
    ~AttackerInfoBean() {
//        if (this->infobean != NULL) {
//            char str[30] = {0};
//            sprintf(str, "%s.plist",this->infobean->creator->getSpriteFileName());
//            CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile(str);
//            sprintf(str, "%s.pvr.ccz",this->infobean->creator->getSpriteFileName());
//            CCTextureCache::sharedTextureCache()->removeTextureForKey(str);
//            
//        }
        CC_SAFE_RELEASE_NULL(attackerAvatarStr);
        CC_SAFE_RELEASE_NULL(attackerNickname);
        CC_SAFE_RELEASE_NULL(infobean);
//        CC_SAFE_RELEASE_NULL(attackSpriteStr);
    }
    
    AttackerInfoBean():
    attackerLevel(1),
//    attackerTag(-1),
    infobean(NULL),
    attackerCount(1),
    attackerPower(21),
    level(0),
    maxLevel(0),
    attackerAvatarStr(NULL),
    attackerNickname(NULL),
//    attackSpriteStr(NULL),
    attackerDirection(attackLD){
    
    }
    
    static AttackerInfoBean* create() {
        AttackerInfoBean* bean = new AttackerInfoBean();
        bean->autorelease();
        return bean;
    }
    
    int attackerLevel;
//    int attackerTag;
    int attackerCount;
    int level;
    int maxLevel;
    int attackerDirection;
    float attackerPower;
    CC_SYNTHESIZE_RETAIN(CCString*,attackerAvatarStr,AttackerAvatarStr);
    CC_SYNTHESIZE_RETAIN(CCString*,attackerNickname,AttackerNickname);
    
    CreatorInfoBean* getCreatorInfoBean() {
        return infobean;
    }

    void setCreatorInfoBean(CreatorInfoBean* _infoBean) {
        if (_infoBean != infobean)
        {
            if (_infoBean != NULL) {
                char str[30] = {0};
                char str1[30] = {0};
                sprintf(str, "%s.plist",_infoBean->creator->getSpriteFileName());
                sprintf(str1, "%s.pvr.ccz",_infoBean->creator->getSpriteFileName());
                GXUtil::loadResourceUtilSucc(str,str1);
                GarbageResourceCollection::getInstance()->addGarbage(str,CCString::create(str1));
//                sprintf(str, "%sbp.plist",_infoBean->creator->getSpriteFileName());
//                sprintf(str1, "%sbp.pvr.ccz",_infoBean->creator->getSpriteFileName());
//                GXUtil::loadResourceUtilSucc(str,str1);
//                GarbageResourceCollection::getInstance()->addGarbage(str,CCString::create(str1));
                _infoBean->retain();
            }
            if (this->infobean != NULL) {
                this->infobean->release();
            }
            this->infobean = _infoBean;
        }
    }

    
//    CC_SYNTHESIZE_RETAIN(CCString*,attackSpriteStr,AttackSpriteStr);
//    CCString* attackSpriteStr;
//    CCString* getAttackSpriteStr() {
//        return attackSpriteStr;
//    }
    
//    void setAttackSpriteStr(CCString* _attackSpriteStr) {
//        if (attackSpriteStr != _attackSpriteStr)
//        {
//            if (_attackSpriteStr != NULL) {
//                char str[30] = {0};
//                char str1[30] = {0};
//                sprintf(str, "%s.plist",_attackSpriteStr->getCString());
//                sprintf(str1, "%s.pvr.ccz",_attackSpriteStr->getCString());
//                GXUtil::loadResourceUtilSucc(str,str1);
//                sprintf(str, "%sbp.plist",_attackSpriteStr->getCString());
//                sprintf(str1, "%sbp.pvr.ccz",_attackSpriteStr->getCString());
//                GXUtil::loadResourceUtilSucc(str,str1);
//                _attackSpriteStr->retain();
//            }
//            if (this->attackSpriteStr != NULL) {
//                char str[30] = {0};
//                sprintf(str, "%s.plist",this->attackSpriteStr->getCString());
//                CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile(str);
//                sprintf(str, "%s.pvr.ccz",this->attackSpriteStr->getCString());
//                CCTextureCache::sharedTextureCache()->removeTextureForKey(str);
//
//                this->attackSpriteStr->release();
//            }
//            this->attackSpriteStr = _attackSpriteStr;
//        }
//    }
private:
//    int attackerTag;
    CreatorInfoBean* infobean;
};

#endif /* defined(__ww4__AttackerInfoBean__) */
