//
//  MyJsonUtil.cpp
//  ww2
//
//  Created by DingYu Fu on 12-9-16.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#include "MyJsonUtil.h"
#include "JSONNode.h"
#include "libjson.h"
#include "cocos2d.h"
#include "MyBuilding.h"
#include "MyGameFactory.h"
#include "BattleScene.h"
#include "MyGameInfo.h"
#include "CollectState.h"
#include "MyDeployButton.h"
#include "MyUnit.h"
#include "RuinState.h"
#include "ResourceBeAttackState.h"
#include "MyBattleBuilding.h"
#include "GXPoint.h"
#include "DataCompressionUtil.h"
#include "CryptologyUtil.h"
#include "TestScene.h"
#include "GXUtil.h"
#include "GXInteger.h"
#include "AsyUnionBean.h"
#include "GXArray.h"
#include "MyMemberBean.h"
#include "PulsarNative.h"
#include "GarbageCollectionState.h"
#include "GarbageCollectionNormalState.h"
#include "ServerScene.h"
#include "EveryDayTask1.h"
#include "PowerQuest.h"
#include "BuildingQuest.h"
#include "BattleQuest.h"
#include "DefendQuest.h"
#include "LevelQuest.h"
#include "ArmyQuest.h"
#include "MyUtil.h"
#include "ChthiefScene.h"
#include "GXJsonUtil.h"


CCString* MyJsonUtil::packAllBuilding(CCArray *array) {
    
    JSONNODE *parent = json_new(JSON_NODE);
    
    CCObject* obj;
    
    MyBuilding* building;
    CCAssert(array->count() > 0, "building count error");
    
    CCARRAY_FOREACH(array, obj) {
        JSONNODE *child = json_new(JSON_NODE);
        building = dynamic_cast<MyBuilding*>(obj);
        json_push_back(child, json_new_i("tag", building->getTag()));
        if (building->fsm->getCurrentState()->getId() == RuinsStateTag) {
            if (((RuinState*)building->fsm->getCurrentState())->currentId == 0 && ((RuinState*)building->fsm->getCurrentState())->currentId >100) {
                CCAssert(true, "currentId error");
            }
            json_push_back(child, json_new_i("currentStateId", ((RuinState*)building->fsm->getCurrentState())->currentId));
        } else {
            json_push_back(child, json_new_i("currentStateId", building->fsm->getCurrentState()->getId()));
        }
        CCPoint tiledPosi = building->getPositionByTiled();
        json_push_back(child, json_new_f("posX", tiledPosi.x));
        json_push_back(child, json_new_f("posY", tiledPosi.y));
        if (dynamic_cast<CollectState*>(building->fsm->getState(WorkStateTag)) != NULL) {
            float capacity = ((CollectState*)building->fsm->getState(WorkStateTag))->getCapacity();
            json_push_back(child, json_new_f("arg0", capacity));
        }
        if(building->fsm->getState(GarbageCollectionStateTag) != NULL) {
            float resource =  ((GarbageCollectionNormalState*)building->fsm->getState(GarbageCollectionStateTag))->resourceCount;
            json_push_back(child, json_new_f("arg0", resource));
        }
        json_push_back(child, json_new_i("level",building->getLevel()));
        json_push_back(parent,child);
    }

//    JSONNODE *n1 = json_new(JSON_NODE);
//    json_push_back(n1, json_new_i("number", 99));  
//    json_push_back(n1, json_new_a("string", "n2n2n2n"));  
//    json_push_back(n1, json_new_a("charactor", "中文")); 
    
    
    
    
    json_char *jc = json_write_formatted(parent);
//    CCLOG("%s", jc);  
//    json_free(jc);  
    json_delete(parent);
    
    
//    CCLog("%d before unCompressingData..",strlen(jc));

    CCString* compressingData = DataCompressionUtil::compressData(CCString::create(jc));
//    // base64??
//    CCLog("%d",compressingData->length());
    CCString*  dada = CryptologyUtil::encode64(compressingData);

//    CCString* unCompressingData = CryptologyUtil::decode64(dada);
//    CCString* asddd = DataCompressionUtil::unCompressData(unCompressingData);
//    CCLog("%d after compressingData", dada->length());
//    CCLog("%s",dada->getCString());
    
//    CCString* result = CCString::create(dada);
    json_free(jc);
    
    return dada;
}

CCArray* MyJsonUtil::parseBuildingFromJson(json_char* str) {
//    CCLog(str);
    
//    CCLog(str);
    MyGameInfo::getInstance()->maxId = -1;
//    CCLog("maxId:%d",MyGameInfo::getInstance()->maxId);
    CCString*  unCompressingData = CryptologyUtil::decode64(CCString::create(str));
    const char* str2 = DataCompressionUtil::unCompressData(unCompressingData)->getCString();
//    CCLog(str2);
    JSONNODE* node = json_parse(str2);
//    CCLog(str2);
    JSONNODE_ITERATOR i = json_begin(node);
    
    CCArray* beans = CCArray::create();
    
    
    while (i != json_end(node)){
        
//        CCLog("%s",json_write_formatted(i));
        
        CCAssert(i!=NULL, "非法的i节点");  
        beans->addObject(parseNode(*i));
        ++i;
    }
    return beans;
}

CCArray* MyJsonUtil::parseBuildingFromJson(CCString* str) {
    MyGameInfo::getInstance()->maxId = -1;
//    CCLog("maxId:%d",MyGameInfo::getInstance()->maxId);
    CCString*  unCompressingData = CryptologyUtil::decode64(str);
    const char* str2 = DataCompressionUtil::unCompressData(unCompressingData)->getCString();
//    CCLog(str2);
    
    JSONNODE* node = json_parse(str2);
    JSONNODE_ITERATOR i = json_begin(node);
    
    CCArray* beans = CCArray::create();
    
    
    while (i != json_end(node)){
        
        CCAssert(i!=NULL, "非法的i节点");
        beans->addObject(parseNode(*i));
        ++i;
    }
    return beans;
}

CCArray* MyJsonUtil::parseBuildingFromJsonNoCompress(CCString* str) {
    
    MyGameInfo::getInstance()->maxId = -1;
//    CCLog("maxId:%d",MyGameInfo::getInstance()->maxId);
    JSONNODE* node = json_parse(str->getCString());
    JSONNODE_ITERATOR i = json_begin(node);
    
    CCArray* beans = CCArray::create();
    
    
    while (i != json_end(node)){
        
        CCAssert(i!=NULL, "非法的i节点");
        beans->addObject(parseNode(*i));
        ++i;
    }
    return beans;
}

BuildingBean* MyJsonUtil::parseNode(JSONNODE* node) {
    
    BuildingBean* bean = BuildingBean::create();
    
    JSONNODE_ITERATOR j = json_begin(node);  
    while (j != json_end(node)) {
        
        // get the node name and value as a string  
        json_char *node_name = json_name(*j);  
        
        // find out where to store the values  
        if (strcmp(node_name, "tag") == 0){  
            json_int_t tagValue = json_as_int(*j);  
            //                CCLOG("%d", tagValue); 
            bean->tag = tagValue;
        }  
        else if (strcmp(node_name, "sid") == 0){  
            json_int_t currentStateIdValue = json_as_int(*j);
            bean->currentStateId = currentStateIdValue; 
        }  
        else if (strcmp(node_name, "x") == 0)  { 
            json_number posX = json_as_float(*j);
            bean->posX = posX;
        } 
        else if(strcmp(node_name, "y") == 0) {
            json_number posY = json_as_float(*j);
            bean->posY = posY;
        }
        else if(strcmp(node_name, "arg0") == 0) {
            json_number arg0 = json_as_float(*j);
            bean->arg0 = arg0;
        }
        else if(strcmp(node_name, "life") == 0) {
            json_number arg1 = json_as_int(*j);
            bean->lifePercentage = arg1;
        } else if (strcmp(node_name, "level") == 0) {
            bean->level = json_as_int(*j);
        } else if (strcmp(node_name, "id") == 0) {
            bean->pid = json_as_int(*j);
            if(bean->pid > MyGameInfo::getInstance()->maxId) {
//                if (bean->pid - MyGameInfo::getInstance()->maxId != 1) {
//                    CCLog("估计有错啊");
//                }
                MyGameInfo::getInstance()->maxId = bean->pid;
//                CCLog("maxId:%d",MyGameInfo::getInstance()->maxId);
            }
        }
        
        // cleanup and increment the iterator  
        json_free(node_name);  
        ++j;
    }
//    json_delete(j);
    return bean;
}

BuildingBean* BuildingBean::create() {
    BuildingBean* bean = new BuildingBean();
    bean->tag = 0;
    bean->currentStateId = 0;
    bean->posX = 0;
    bean->posY = 0;
    bean->autorelease();
    return bean;
}

topRankBean* topRankBean::create() {
    topRankBean* bean = new topRankBean();
    bean->autorelease();
    return bean;
}

ConscribeInfoBean* ConscribeInfoBean::create() {
    ConscribeInfoBean* bean =  new ConscribeInfoBean();
    bean->autorelease();
    return bean;
}

void ConscribeInfoBean::setJsonName(cocos2d::CCString *_jsonName) {
    if (_jsonName != NULL) {
        CC_SAFE_RELEASE_NULL(jsonName);
        jsonName = _jsonName;
        CC_SAFE_RETAIN(jsonName);
    }
}

StartScene* MyJsonUtil::parseNativeInfo(CCString* str) {
//    std::string str2 = str;
//    int k = 0;
//    for (k =str2.length()-1; k>=0; --k) {
////        char a = str2.at(k);
//        if ( str2.at(k) ==  '}') {
//            break;
//        } 
//    }
//    str2 = str2.substr(0,k+1);
//    str = str.c_str();
//    CCLog(str);
    
//    CCLog(str);
    json_char* buildingStr = NULL;
    json_char* creatorStr =  NULL;
    
    JSONNODE* node = json_parse(str->getCString());
    if (node == NULL) {
        return NULL;
    }
    JSONNODE_ITERATOR i = json_begin(node);
    StartScene* start = NULL;
    int buildingSize = -1;
    unsigned long long robDeltaTime = 0;
    long robMultipleTime = 0;
    while (i != json_end(node)){
        json_char *node_name = json_name(*i);
    
        
        if (strcmp(node_name, "buildingStyle") == 0) {
            buildingStr = json_as_string(*i);
//             start = StartScene::create(parseBuildingFromJson());
        } else if (strcmp(node_name, "gameLevel") == 0){
            json_char* tempChar = json_as_string(*i);
//            unsigned  long long exp = atoll(tempChar);
//            MyGameInfo::getInstance()->setExperienceNoFx(exp);
             MyGameInfo::getInstance()->setUpdateLevel(atoll(tempChar));
            json_free(tempChar);
//            CCLOG("%s", tagValue);
//            bean->tag = tagValue;
//            CCLog("gameLevel:%d",json_as_int(*i));
        }
//        else if (strcmp(node_name, "ititaId") == 0){
//            json_char* tempChar = json_as_string(*i);
//            PulsarNative::setItitaId(tempChar);
//            json_free(tempChar);
//            //            CCLOG("%s", tagValue);
//            //            bean->tag = tagValue;
//            //            CCLog("gameLevel:%d",json_as_int(*i));
//        }
        else if (strcmp(node_name, "lastTime") == 0){
//            json_int_t currentStateIdValue = ni(*j);
//            bean->currentStateId = currentStateIdValue;
            json_char* tempChar = json_as_string(*i);
            MyGameInfo::getInstance()->lastTime = atoll(tempChar);
            json_free(tempChar);
            
//            CCLog("lastTime:%lld",MyGameInfo::getInstance()->lastTime);
        }
        else if (strcmp(node_name, "robDeltaTime") == 0){
            //            json_int_t currentStateIdValue = ni(*j);
            //            bean->currentStateId = currentStateIdValue;
            json_char* tempChar = json_as_string(*i);
//            MyGameInfo::getInstance()->setRobMultipleByTime(atoll(tempChar));
//            MyGameInfo::getInstance()->robdeltaTime = atol(tempChar);
            robDeltaTime = atoll(tempChar);
            json_free(tempChar);
        } else if(strcmp(node_name, "robMultipleTime") == 0){
            robMultipleTime = json_as_int(*i);
        }
        else if (strcmp(node_name,"unionName") == 0) {
            json_char* tempChar = json_as_string(*i);
            MyGameInfo::getInstance()->getUnionBean()->setName(CCString::create(tempChar));
            json_free(tempChar);
        } else if (strcmp(node_name,"emblem") == 0) {
            json_char* tempChar = json_as_string(*i);
            MyGameInfo::getInstance()->getUnionBean()->setEmblem(CCString::create(tempChar));
            json_free(tempChar);
        }
        else if (strcmp(node_name, "nowTime") == 0){  
            //            json_int_t currentStateIdValue = json_as_int(*j);
            //            bean->currentStateId = currentStateIdValue;
//            char *str = json_as_string(*i);
//            long long count = atoll(str);
            json_char* tempChar = json_as_string(*i);
            MyGameInfo::getInstance()->nowTime = atoll(tempChar);
            json_free(tempChar);
//            CCLog("nowTime,%lld",MyGameInfo::getInstance()->nowTime);
        } else if (strcmp(node_name, "glory") == 0) {
            json_char* tempChar = json_as_string(*i);
            MyGameInfo::getInstance()->setInitGlory(atol(json_as_string(*i)));
            json_free(tempChar);
        } else if (strcmp(node_name, "oil") == 0)  {
            json_char* tempChar = json_as_string(*i);
            MyGameInfo::getInstance()->setInitOil(atol(json_as_string(*i)));
            json_free(tempChar);
        } else if(strcmp(node_name, "VIPLevel") == 0) {
            MyGameInfo::getInstance()->setVipExperience(json_as_int(*i));
        } else if(strcmp(node_name, "iron") == 0) {
            MyGameInfo::getInstance()->setInitIron(atol(json_as_string(*i)));
        } else if(strcmp(node_name,"diamond") == 0) {
            MyGameInfo::getInstance()->setDiamond(json_as_int(*i));
        } else if(strcmp(node_name, "nickname") == 0) {
            json_char* tempChar = json_as_string(*i);
            MyGameInfo::getInstance()->setNickName(CCString::create(tempChar));
            json_free(tempChar);
//            CCLog(MyGameInfo::getInstance()->nickname);
        } else if(strcmp(node_name, "creatorStyle") == 0) {
            creatorStr = json_as_string(*i);
        } else if (strcmp(node_name, "power") == 0) {
            MyGameInfo::getInstance()->setPower(json_as_float(*i));
//            CCLog("power:%f",MyGameInfo::getInstance()->power);
        } else if (strcmp(node_name, "buildingSize") == 0) {
            buildingSize = json_as_int(*i);
        }
        ++i;
        json_free(node_name);
    }
    json_delete(node);
    
    
    if (creatorStr != NULL) {
        parseCreatorStyle(creatorStr);
        json_free(creatorStr);
    }
    if (buildingStr != NULL) {
        start = StartScene::create(parseBuildingFromJson(buildingStr));
        json_free(buildingStr);
    }
    if (buildingSize-1 > MyGameInfo::getInstance()->maxId) {
        CCLog("maxId:%d",MyGameInfo::getInstance()->maxId);
        MyGameInfo::getInstance()->maxId = buildingSize-1;
    }
    start->initBugei(robDeltaTime,robMultipleTime);
    
//    if(MyGameInfo::getInstance()->getRobMultiple() <= MyUtil::getInstance()->getLevelByExperience(MyGameInfo::getInstance()->getExperience())/10) {
//        
//    } else {
//        CCMenuItem*  bugeiButton = this->addBugeiButton();
//        //        bugeiButton->runAction(CCMoveBy::create(3,ccp(-150,0)));
//        CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sfx_bugeiLaugh.mp3");
//        this->addDisplayHuodong(questMenu,bugeiButton);
//        //        bugeiButton->setPosition(100,570-questMenu->getChildrenCount()*100);
//    }
//    //    int abc = MyGameInfo::getInstance()->robdeltaTime%1200000;
//    this->schedule(schedule_selector(StartScene::bugeiMultipleTimer),1800,kCCRepeatForever,1800-(MyGameInfo::getInstance()->robdeltaTime%1800000)/1000);
    
    return start;
}

void MyJsonUtil::parseCreatorStyle(json_char* str) {
    CCString*  unCompressingData = CryptologyUtil::decode64(CCString::create(str));
    CCString* str1 = DataCompressionUtil::unCompressData(unCompressingData);
    
    if (str1->compare("null") == 0 && str1->compare("") == 0) {
        return;
    }
    JSONNODE* node1 = json_parse(str1->getCString());
//    CCLog(str1->getCString());
    JSONNODE_ITERATOR k = json_begin(node1);
    if (k == NULL) {
        CCLog("creatorStyle not Null");
//        MyGameFactory::createCreatorbyJsonScriptFile("garade.j", unitCreatorClassTag);
//        MyGameInfo::getInstance()->creatorArray->addObject(CreatorInfoBean::create(garadeCardId));
//        MyGameFactory::createCreatorbyJsonScriptFile("M5Stuart.j", unitCreatorClassTag);
//        MyGameInfo::getInstance()->creatorArray->addObject(CreatorInfoBean::create(M5StuartCardId));
        return;
    }
    while (k && k != json_end(node1)){
        JSONNODE_ITERATOR l = json_begin(*k);
        CreatorInfoBean* creator = NULL;
        if (l == NULL) {
            CCLog("unitCreator not Null");
        }
        while (l && l != json_end(*k)) {
            json_char *node_name2 = json_name(*l);
//            if(strcmp(node_name2, "jsString") == 0) {
//                //todo 这里的对应关系变化
//                //                    MyGameInfo::getInstance()->bubingLevel = json_as_int(*k);
//                json_char* tempChar = json_as_string(*l);
//                if (strcmp("garade.j",tempChar) == 0) {
//                    creator = CreatorInfoBean::create(garadeCardId);
//                    MyGameInfo::getInstance()->creatorArray->addObject(creator);
//                } else if(strcmp("M5Stuart.j",tempChar) == 0) {
//                    creator = CreatorInfoBean::create(M5StuartCardId);
//                    MyGameInfo::getInstance()->creatorArray->addObject(creator);
//                } else if(strcmp("WillysMB.j",tempChar) == 0) {
//                    creator = CreatorInfoBean::create(WillysMBCardId);
//                    MyGameInfo::getInstance()->creatorArray->addObject(creator);
//                } else if(strcmp("M3HalfTrack.j",tempChar) == 0) {
//                    creator = CreatorInfoBean::create(M3HalfTrackCardId);
//                    MyGameInfo::getInstance()->creatorArray->addObject(creator);
//                } else if(strcmp("M4Sherman.j",tempChar) == 0) {
//                    creator = CreatorInfoBean::create(M4ShermanCardId);
//                    MyGameInfo::getInstance()->creatorArray->addObject(creator);
//                } else if(strcmp("Calliope.j",tempChar) == 0) {
//                    creator = CreatorInfoBean::create(CalliopeCardId);
//                    MyGameInfo::getInstance()->creatorArray->addObject(creator);
//                }
//                
//                json_free(tempChar);
//                
//            } else
            if(strcmp(node_name2, "level") == 0) {
                json_char* tempChar = json_as_string(*l);
                if (creator != NULL) {
                    creator->setExperience(atoll(tempChar));
                }
                json_free(tempChar);
            } else if(strcmp(node_name2, "unitCardId") == 0) {
                creator = CreatorInfoBean::create(json_as_int(*l));
                MyGameInfo::getInstance()->creatorArray->addObject(creator);
            }
            l++;
            json_free(node_name2);
        }
        ++k;
    }
    json_delete(node1);
}

CCString* MyJsonUtil::packBattleUnit(cocos2d::CCArray *creatorArray) {
    
//    std::vector<char> sendBuffer;
//    char* ptr = "\"\":{";
//    sendBuffer.insert(sendBuffer.end(), ptr, ptr+strlen(ptr));
//    
//    CCObject* obj;
//    MyDeployButton* button;
//    CCARRAY_FOREACH(creatorArray, obj) {
//        JSONNODE *child = json_new(JSON_NODE);
//        button = dynamic_cast<MyDeployButton*>(obj);
//        if (button->count != 0) {
//            char* ptr1 = "\"frameName\":\"";
//            sendBuffer.insert(sendBuffer.end(), ptr1, ptr1+strlen(ptr1));
//            
//            char* ptr2 = button->bean->creator->getSpriteFileName();
//            sendBuffer.insert(sendBuffer.end(), ptr2, ptr2+strlen(ptr2));
//            
//            char* ptr3 = button->bean->creator-
//            
//            json_push_back(child, json_new_a("frameName", );
//            json_push_back(child, json_new_i("count", button->count));
//            json_push_back(child, json_new_i("level", button->bean->getLevel()));
//            json_push_back(child, json_new_i("rarity", button->bean->creator->getRarity()));
//        } else {
//            continue;
//        }
//
//    }
//    
//    sendBuffer.insert(sendBuffer.end(), tempStr->getCString(), tempStr->getCString()+tempStr->length());
    
    JSONNODE *parent = json_new(JSON_NODE);
    
    CCObject* obj;
    
    MyDeployButton* button;
    CCARRAY_FOREACH(creatorArray, obj) {
        JSONNODE *child = json_new(JSON_NODE);
        button = dynamic_cast<MyDeployButton*>(obj);
        if (button->count != 0) {
            json_push_back(child, json_new_a("frameName", button->bean->creator->getSpriteFileName()));
            json_push_back(child, json_new_i("count", button->count));
            json_push_back(child, json_new_i("level", button->bean->getLevel()));
            json_push_back(child, json_new_i("rarity", button->bean->creator->getRarity()));
        } else {
            continue;
        }

        
        json_push_back(parent,child);
        //        json_delete(child);
    }
    
    
    //    JSONNODE *n1 = json_new(JSON_NODE);
    //    json_push_back(n1, json_new_i("number", 99));
    //    json_push_back(n1, json_new_a("string", "n2n2n2n"));
    //    json_push_back(n1, json_new_a("charactor", "中文"));
    
    
    
    
    json_char *jc = json_write_formatted(parent);
    //    CCLOG("%s", jc);
    //    json_free(jc);
    json_delete(parent);
    CCString* compressingData = DataCompressionUtil::compressData(CCString::create(jc));
    //    // base64??
    //    CCLog("%d",compressingData->length());
    CCString*  data = CryptologyUtil::encode64(compressingData);
    
    
    json_free(jc);
    return data;
}

//UnitCreator* MyJsonUtil::parseUnitCreator(CCString *str) {
//    JSONNODE* node = json_parse(str->getCString());
//    JSONNODE_ITERATOR i = json_begin(node);
//    UnitCreator* creator = UnitCreator::create();
////    CCLog("%s",json_write_formatted(node));
//    while (i != json_end(node)){
//        json_char *node_name = json_name(*i);      
//        
//        if (strcmp(node_name, "cardId") == 0) {
//            creator->cardId = json_as_int(*i);
//        } else if (strcmp(node_name, "name") == 0){
//            json_char* tempStr = json_as_string(*i);
//            creator->setName(CCString::create(tempStr));
//            json_free(tempStr);
//        }
//        else if (strcmp(node_name, "spriteFileName") == 0){
//            json_char* tempStr = json_as_string(*i);
//            creator->setSpriteFileName(CCString::create(tempStr));
//            json_free(tempStr);
//        }
//        else if (strcmp(node_name, "sfxDeployName") == 0){
//            json_char* tempStr = json_as_string(*i);
//            creator->setSfxDeployName(CCString::create(tempStr));
//            json_free(tempStr);
//        }
//        else if (strcmp(node_name, "sfxFireName") == 0){
//            json_char* tempStr = json_as_string(*i);
//            creator->setSfxFireName(CCString::create(tempStr));
//            json_free(tempStr);
//        }
//        else if (strcmp(node_name, "speed") == 0)  {
//            creator->setSpeed(json_as_float(*i));
//        }
//        else if(strcmp(node_name, "attackRange") == 0) {
//            creator->setAttackRange(json_as_float(*i));
//        } else if(strcmp(node_name, "damage") == 0) {
//            creator->setDamage(json_as_float(*i));
//        } else if(strcmp(node_name, "health") == 0) {
//            creator->setLife(json_as_float(*i));
//        } else if (strcmp(node_name, "cost") == 0) {
//            creator->setSummaryOil(json_as_int(*i));
//        } else if (strcmp(node_name, "rarity") == 0) {
//            creator->setRarity(json_as_int(*i));
//        } else if (strcmp(node_name, "updateHealthRate") == 0) {
//            creator->updateHealthRate = json_as_float(*i);
//        } else if (strcmp(node_name, "updateDamageRate") == 0) {
//            creator->updateDamageRate = json_as_float(*i);
//        } else if (strcmp(node_name, "updateCostRate") == 0) {
//            creator->updateCostRate = json_as_float(*i);
//        } else if (strcmp(node_name, "updateSpeedRate") == 0) {
//            creator->updateSpeedRate = json_as_float(*i);
//        } else if (strcmp(node_name, "moveAnimateRate")==0) {
//            creator->moveAnimateRate = json_as_float(*i);
//        } else if (strcmp(node_name, "fireAnimateRate")==0) {
//            creator->fireAnimateRate = json_as_float(*i);
//        } else if (strcmp(node_name, "dieAnimateRate")==0) {
//            creator->dieAnimateRate = json_as_float(*i);
//        } else if (strcmp(node_name, "moveAnimateReverse")==0) {
//            creator->moveAnimateReverse = json_as_bool(*i);
//        } else if (strcmp(node_name, "fireAnimateReverse")==0) {
//            creator->fireAnimateReverse = json_as_bool(*i);
//        } else if (strcmp(node_name, "dieAnimateReverse")==0) {
//            creator->dieAnimateRerverse = json_as_bool(*i);
//        } else if (strcmp(node_name, "unlockCostResourceTag")==0) {
//            creator->unlockCostResourceTag = json_as_int(*i);
//        } else if (strcmp(node_name, "unlockCostCount")==0) {
//            creator->unlockCostCount = json_as_float(*i);
//        } else if (strcmp(node_name, "unlockNeedResourceTag")==0) {
//            creator->unlockNeedResourceTag = json_as_int(*i);
//        } else if (strcmp(node_name, "unlockNeedCount")==0) {
//            creator->unlockNeedCount = json_as_float(*i);
//        }
////        else if (strcmp(node_name, "fx") == 0) {
////            JSONNODE_ITERATOR l = json_begin(*i);
////            UnitFXCreator* unitCreator = UnitFXCreator::create();
////            while (l && l != json_end(*i)) {
////                json_char *node_name2 = json_name(*l);
////                if(strcmp(node_name2, "action") == 0) {
//////                    CCLog("%s",json_as_string(*l));
////                    json_char* tempStr = json_as_string(*l);
////                    unitCreator->setActionName(CCString::create(tempStr));
////                    json_free(tempStr);
////                } else if(strcmp(node_name2, "dir") == 0) {
////                    unitCreator->dir = json_as_int(*l);
////                } else if(strcmp(node_name2, "startFrameCount") == 0) {
////                    unitCreator->startFrameCount = json_as_int(*l);
////                } else if(strcmp(node_name2, "fxname") == 0) {
////                    json_char* tempStr = json_as_string(*l);
////                    unitCreator->setFxname(CCString::create(tempStr));
////                    json_free(tempStr);
////                } else if(strcmp(node_name2, "posX") == 0) {
////                    unitCreator->posX = json_as_float(*l);
////                } else if (strcmp(node_name2, "posY") == 0) {
////                    unitCreator->posY = json_as_float(*l);
////                } else if (strcmp(node_name2, "scale") == 0) {
////                    unitCreator->scale = json_as_float(*l);
////                } else if (strcmp(node_name2, "zorder") == 0) {
////                    unitCreator->zOrder = json_as_int(*l);
////                }
////                json_free(node_name2);
////                l++;
////            }
////            creator->fxArray->addObject(unitCreator);
////        }
//        json_free(node_name);
//        ++i;
//    }
//    json_delete(node);
//    return creator;
//}

BattleScene* MyJsonUtil::parseBattleNativeInfo(CCString *str) {
    std::string str2 = str->m_sString;
    
//    std::string  unCompressingData = CryptologyUtil::decode64(str);
//    str = DataCompressionUtil::unCompressData(unCompressingData).c_str();
//    CCLog(str);
    JSONNODE* node = json_parse(str2.c_str());
    JSONNODE_ITERATOR i = json_begin(node);
    BattleScene* battle = NULL;
    float _trophyRate = 0.5;
    int enemyVipExp = 0;
    CCArray* buildings = NULL;
    UnionBean* unionBean = UnionBean::create();
    unionBean->setName(CCString::create(""));
    json_char* buildingStr;
    int attackType = 0;
    while (i != json_end(node)){
        json_char *node_name = json_name(*i);
        
        if (strcmp(node_name, "buildingStyle") == 0) {
            buildingStr = json_as_string(*i);
//            buildings = parseBuildingFromJson();
//            battle = BattleScene::create(parseBuildingFromJson(json_as_string(*i)));
        } else if (strcmp(node_name, "gameLevel") == 0){
            //            json_int_t tagValue = json_as_int(*j);  
            //            //                CCLOG("%d", tagValue); 
            //            bean->tag = tagValue;
            
//            CCLog("gameLevel:%d",json_as_int(*i));
            json_char* tempStr = json_as_string(*i);
            MyGameInfo::getInstance()->enemyLevel = MyUtil::getInstance()-> getLevelByExperience(atoll(tempStr));
            json_free(tempStr);
           
        }
        else if (strcmp(node_name, "lastTime") == 0){  
            //            json_int_t currentStateIdValue = json_as_int(*j);
            //            bean->currentStateId = currentStateIdValue;
            json_char* tempStr = json_as_string(*i);
            MyGameInfo::getInstance()->lastTime = atoll(tempStr);
            json_free(tempStr);
//            CCLog("time:%d",json_as_int(*i));
        }
        else if (strcmp(node_name, "nowTime") == 0){  
            //            json_int_t currentStateIdValue = json_as_int(*j);
            //            bean->currentStateId = currentStateIdValue;
            json_char* tempStr = json_as_string(*i);
            MyGameInfo::getInstance()->nowTime = atoll(json_as_string(*i));
            json_free(tempStr);
//            CCLog("time:%d",json_as_int(*i));
        }
        else if (strcmp(node_name, "oil") == 0)  { 
            //            json_number posX = json_as_float(*j);
            //            bean->posX = posX;
            MyGameInfo::getInstance()->enemyOil = json_as_int(*i);
//            CCLog("oil:%d",json_as_int(*i));
        } 
        else if(strcmp(node_name, "iron") == 0) {
            //            json_number posY = json_as_float(*j);
            //            bean->posY = posY;
            MyGameInfo::getInstance()->enemyIron = json_as_int(*i);
//            CCLog("iron:%d",json_as_int(*i));
        } else if(strcmp(node_name, "nickname") == 0) {
            json_char* tempStr = json_as_string(*i);
            MyGameInfo::getInstance()->setEnemyNickname(CCString::create(tempStr));
            json_free(tempStr);
        } else if(strcmp(node_name, "userId") == 0) {
//            json_char* tempStr = json_as_string(*i);
            MyGameInfo::getInstance()->setEnemyUserId(json_as_int(*i));
//            json_free(tempStr);
        } else if (strcmp(node_name, "power") == 0) {
            MyGameInfo::getInstance()->enemyPower = json_as_float(*i);
//            CCLog("enemypower:%f",MyGameInfo::getInstance()->enemyPower);
        } else if (strcmp(node_name, "trophyRate") == 0) {
            _trophyRate = json_as_float(*i);
            //            CCLog("enemypower:%f",MyGameInfo::getInstance()->enemyPower);
        } else if (strcmp(node_name, "unionName") == 0) {
            json_char* tempStr = json_as_string(*i);
            unionBean->setName(CCString::create(tempStr));
            json_free(tempStr);
        } else if(strcmp(node_name, "emblem") == 0) {
            json_char* tempStr = json_as_string(*i);
            unionBean->setEmblem(CCString::create(tempStr));
            json_free(tempStr);
        } else if(strcmp(node_name,"VIPLevel") == 0) {
            enemyVipExp = json_as_int(*i);
        } else if(strcmp(node_name,"type") == 0) {
            attackType = json_as_int(*i);
        }
        json_free(node_name);
        ++i;
    }
    json_delete(node);
    
    buildings = buildings = parseBuildingFromJson(buildingStr);
    json_free(buildingStr);
    battle = BattleScene::create(buildings,_trophyRate,unionBean,enemyVipExp);
    battle->attackType = attackType;
//    battle->enemyVipExperience = enemyVipExp;
    return battle;
}

DefendScene* MyJsonUtil::parseDefendNativeInfo(CCString *str2) {
    const char* str = str2->getCString();
    
//    const char* str = DataCompressionUtil::unCompressData(CryptologyUtil::decode64(str2))->getCString();
//    CCLog(str);
    JSONNODE* node = json_parse(str);
    JSONNODE_ITERATOR i = json_begin(node);
    DefendScene* defend = DefendScene::create();
    CCArray* buildings = NULL;
    UnionBean* unionBean = UnionBean::create();
    unionBean->setName(CCString::create(""));
    CCString* attackerAvatarStr = NULL;
    CCArray* attackerLevels = CCArray::create();
    json_char* buildingStr;
    while (i != json_end(node)){
        json_char *node_name = json_name(*i);
        
        if (strcmp(node_name, "buildingStyle") == 0) {
            buildingStr = json_as_string(*i);
            //            buildings = parseBuildingFromJson();
            //            battle = BattleScene::create(parseBuildingFromJson(json_as_string(*i)));
        } else if(strcmp(node_name,"attackerAvatarStr") == 0) {
            json_char* tempStr = json_as_string(*i);
            attackerAvatarStr = CCString::create(tempStr);
            json_free(tempStr);
        }
//        else if (strcmp(node_name, "gameLevel") == 0){
//            //            json_int_t tagValue = json_as_int(*j);
//            //            //                CCLOG("%d", tagValue);
//            //            bean->tag = tagValue;
//            
//            CCLog("gameLevel:%d",json_as_int(*i));
//        }
        
        else if (strcmp(node_name, "lastTime") == 0){
            //            json_int_t currentStateIdValue = json_as_int(*j);
            //            bean->currentStateId = currentStateIdValue;
            json_char* tempStr = json_as_string(*i);
            MyGameInfo::getInstance()->lastTime = atoll(tempStr);
            json_free(tempStr);
            //            CCLog("time:%d",json_as_int(*i));
        }
        else if (strcmp(node_name, "nowTime") == 0){
            //            json_int_t currentStateIdValue = json_as_int(*j);
            //            bean->currentStateId = currentStateIdValue;
            json_char* tempStr = json_as_string(*i);
            MyGameInfo::getInstance()->nowTime = atoll(json_as_string(*i));
            json_free(tempStr);
            //            CCLog("time:%d",json_as_int(*i));
        }
        else if(strcmp(node_name, "attackerNickname") == 0) {
            json_char* tempStr = json_as_string(*i);
            MyGameInfo::getInstance()->setEnemyNickname(CCString::create(tempStr));
            json_free(tempStr);
        }else if(strcmp(node_name, "CPUWarLevel") == 0) {
            defend->cpuWarLevel = json_as_int(*i);
        }
        else if (strcmp(node_name, "attackerPower") == 0) {
            MyGameInfo::getInstance()->enemyPower = json_as_float(*i);
            //            CCLog("enemypower:%f",MyGameInfo::getInstance()->enemyPower);
        }
        else if (strcmp(node_name, "attackerTags") == 0){
            JSONNODE_ITERATOR k = json_begin(*i);
            while (k != json_end(*i)){
                defend->addAttackerCreateInfoBean(CreatorInfoBean::create(json_as_int(*k)));
                k++;
            }
        }
        else if (strcmp(node_name, "attackerLevels") == 0){
            JSONNODE_ITERATOR k = json_begin(*i);
            while (k != json_end(*i)){
                attackerLevels->addObject(GXintValue::create(json_as_int(*k)));
                k++;
            }
        }
        else if(strcmp(node_name,"attackerCounts") == 0) {
            JSONNODE_ITERATOR k = json_begin(*i);
            while (k != json_end(*i)){
                defend->attackerCountList->addObject(GXintValue::create(json_as_int(*k)));
                k++;
            }
        } else if(strcmp(node_name,"attackerTimes") == 0) {
            JSONNODE_ITERATOR k = json_begin(*i);
            while (k != json_end(*i)){
                defend->attackerTimeList->addObject(GXintValue::create(json_as_int(*k)));
                k++;
            }
        } else if(strcmp(node_name,"prizeBox1Tags") == 0) {
            JSONNODE_ITERATOR k = json_begin(*i);
            while (k != json_end(*i)){
                defend->prizeBoxTagList[0]->addObject(GXintValue::create(json_as_int(*k)));
                k++;
            }
        } else if(strcmp(node_name,"prizeBox1Counts") == 0) {
            JSONNODE_ITERATOR k = json_begin(*i);
            while (k != json_end(*i)){
                defend->prizeBoxCountList[0]->addObject(GXintValue::create(json_as_int(*k)));
                k++;
            }
        } else if(strcmp(node_name,"prizeBox2Tags") == 0) {
            JSONNODE_ITERATOR k = json_begin(*i);
            while (k != json_end(*i)){
                defend->prizeBoxTagList[1]->addObject(GXintValue::create(json_as_int(*k)));
                k++;
            }
        } else if(strcmp(node_name,"prizeBox2Counts") == 0) {
            JSONNODE_ITERATOR k = json_begin(*i);
            while (k != json_end(*i)){
                defend->prizeBoxCountList[1]->addObject(GXintValue::create(json_as_int(*k)));
                k++;
            }
        } else if(strcmp(node_name,"prizeBox3Tags") == 0) {
            JSONNODE_ITERATOR k = json_begin(*i);
            while (k != json_end(*i)){
                defend->prizeBoxTagList[2]->addObject(GXintValue::create(json_as_int(*k)));
                k++;
            }
        } else if(strcmp(node_name,"prizeBox3Counts") == 0) {
            JSONNODE_ITERATOR k = json_begin(*i);
            while (k != json_end(*i)){
                defend->prizeBoxCountList[2]->addObject(GXintValue::create(json_as_int(*k)));
                k++;
            }
        } else if(strcmp(node_name,"attackerDirection") == 0) {
            defend->attackerDirection = json_as_int(*i);
        } else if(strcmp(node_name,"prizeBox1Id") == 0) {
            defend->prizeBoxIds[0] = json_as_int(*i);
        } else if(strcmp(node_name,"prizeBox2Id") == 0) {
            defend->prizeBoxIds[1] = json_as_int(*i);
        } else if(strcmp(node_name,"prizeBox3Id") == 0) {
            defend->prizeBoxIds[2] = json_as_int(*i);
        }
        
//        else if (strcmp(node_name, "trophyRate") == 0) {
//            _trophyRate = json_as_float(*i);
//            //            CCLog("enemypower:%f",MyGameInfo::getInstance()->enemyPower);
//        }
//        else if (strcmp(node_name, "unionName") == 0) {
//            json_char* tempStr = json_as_string(*i);
//            unionBean->setName(CCString::create(tempStr));
//            json_free(tempStr);
//        } else if(strcmp(node_name, "emblem") == 0) {
//            json_char* tempStr = json_as_string(*i);
//            unionBean->setEmblem(CCString::create(tempStr));
//            json_free(tempStr);
//        } else if(strcmp(node_name,"VIPLevel") == 0) {
//            enemyVipExp = json_as_int(*i);
//        }
        json_free(node_name);
        ++i;
    }
    json_delete(node);
    
    buildings = buildings = parseBuildingFromJson(buildingStr);
    json_free(buildingStr);
//    defend = DefendScene::create(buildings,attackerAvatarStr);
    for (int i=0; i<attackerLevels->count(); i++) {
        int level = ((GXintValue*)attackerLevels->objectAtIndex(i))->getValue();
        CreatorInfoBean* bean = ((CreatorInfoBean*)defend->attackerCreatorInfoBeanList->objectAtIndex(i));
        bean->setExperience(MyUtil::getInstance()->getExperienceByUnitLevel(level-1,bean->creator->getRarity())+1);
        defend->attackerSummaryList[i] = (int)MyUtil::getInstance()->updateLevelByRate(bean->creator->summaryOriOil,bean->creator->getSummaryOil(), bean->getLevel(), bean->creator->updateCostRate);
    }
    defend->init(buildings);
    defend->initUI(attackerAvatarStr);
    MyGameInfo::getInstance()->setEnemyUserId(PulsarNative::userId);
    MyGameInfo::getInstance()->enemyDeltaOil =0;
    MyGameInfo::getInstance()->enemyDeltaIron = 0;
//    CCArray* attackerCreatorInfoBeanList;
//    CCArray* attackerCountList;
//    CCArray* attackerTimeList;
    
//    defend->addAttackerCreateInfoBean(CreatorInfoBean::create(garadeCardId));
//    defend->addAttackerCreateInfoBean(CreatorInfoBean::create(WillysMBCardId));
//    defend->addAttackerCreateInfoBean(CreatorInfoBean::create(CalliopeCardId));
//    
//    defend->attackerCountList->addObject(GXintValue::create(50));
//    defend->attackerCountList->addObject(GXintValue::create(30));
//    defend->attackerCountList->addObject(GXintValue::create(10));
//    
//    defend->attackerTimeList->addObject(GXintValue::create(0));
//    defend->attackerTimeList->addObject(GXintValue::create(50));
//    defend->attackerTimeList->addObject(GXintValue::create(100));
//    defend->setAttackerAvatar(attackerAvatarStr);
    //    battle->enemyVipExperience = enemyVipExp;
    return defend;
}

CCScene* MyJsonUtil::parseReadyNativeInfo(CCString *str) {
//    CCLog("%s",str->getCString());
    JSONNODE* node = json_parse(str->getCString());
    
    JSONNODE_ITERATOR i = json_begin(node);
    
    CCArray* array =  CCArray::create();
    while (i != json_end(node)){
        if (json_type(*i) == JSON_ARRAY || json_type(*i) == JSON_NODE){
            BaseInfoBean* bean = BaseInfoBean::create();
            JSONNODE_ITERATOR j = json_begin(*i);
            while (j!=json_end(*i)) {
                json_char *node_name = json_name(*j);
                if (strcmp(node_name, "gameLevel") == 0) {
                    json_char* tempStr = json_as_string(*j);
                    bean->experience = atoll(tempStr);
                    json_free(tempStr);
                } else if (strcmp(node_name, "nickname") == 0){
                    json_char* tempStr = json_as_string(*j);
                    bean->setNickname(CCString::create(tempStr));
                    json_free(tempStr);
                }
                else if (strcmp(node_name, "lastTime") == 0){
                    json_char* tempStr = json_as_string(*j);
                    bean->time = atoll(tempStr);
                    json_free(tempStr);
                }
                else if (strcmp(node_name, "nowTime") == 0){
                    json_char* tempStr = json_as_string(*j);
                    bean->nowTime = atoll(tempStr);
                    json_free(tempStr);
                }
                else if (strcmp(node_name, "oil") == 0)  {
                    //            json_number posX = json_as_float(*j);
                    //            bean->posX = posX;
                    bean->oil = json_as_int(*j);
                    //            CCLog("oil:%d",json_as_int(*i));
                }
                else if(strcmp(node_name, "iron") == 0) {
                    //            json_number posY = json_as_float(*j);
                    //            bean->posY = posY;
                    bean->iron = json_as_int(*j);
                    //            CCLog("iron:%d",json_as_int(*i));
                }  else if (strcmp(node_name, "power") == 0) {
                    bean->honor = json_as_float(*j);
    
                }   else if (strcmp(node_name, "userId") == 0){
//                    json_char* tempStr = json_as_string(*j);
                    bean->userId = json_as_int(*j);
//                    json_free(tempStr);
                } else if (strcmp(node_name, "defenSuccRate") == 0){
                    json_char* tempStr = json_as_string(*j);
                    bean->setDefenSuccRate(CCString::create(tempStr));
                    json_free(tempStr);
                } else if (strcmp(node_name, "trophyRate") == 0){
                    bean->trophyRate = json_as_float(*j);
                } else if (strcmp(node_name, "unionName") == 0) {
                    json_char* tempStr = json_as_string(*j);
                    bean->setUnionName(CCString::create(tempStr));
                    json_free(tempStr);
                }
                json_free(node_name);
                ++j;
            }
            array->addObject(bean);
        }
        
            
        ++i;
    }
    json_delete(node);
    return TestScene::create(array);
}

CCArray* MyJsonUtil::parseBaseInfoBean(CCString* str) {
    
    JSONNODE* node = json_parse(str->getCString());
    JSONNODE_ITERATOR i = json_begin(node);
    CCArray* array =  CCArray::create();

    while (i != json_end(node)){
        if (json_type(*i) == JSON_ARRAY || json_type(*i) == JSON_NODE){
            BaseInfoBean* bean = BaseInfoBean::create();
            bean->type = 1;
            JSONNODE_ITERATOR j = json_begin(*i);
            while (j!=json_end(*i)) {
                json_char *node_name = json_name(*j);
                if (strcmp(node_name, "gameLevel") == 0) {
                    json_char* tempStr = json_as_string(*j);
                    bean->experience = atoll(tempStr);
                    json_free(tempStr);
                } else if (strcmp(node_name, "nickname") == 0){
                    json_char* tempStr = json_as_string(*j);
                    bean->setNickname(CCString::create(tempStr));
                    json_free(tempStr);
                }
                else if (strcmp(node_name, "lastTime") == 0){
                    json_char* tempStr = json_as_string(*j);
                    bean->time = atoll(tempStr);
                    json_free(tempStr);
                }
                else if (strcmp(node_name, "nowTime") == 0){
                    json_char* tempStr = json_as_string(*j);
                    bean->nowTime = atoll(tempStr);
                    json_free(tempStr);
                }
                else if (strcmp(node_name, "oil") == 0)  {
                    //            json_number posX = json_as_float(*j);
                    //            bean->posX = posX;
                    bean->oil = json_as_int(*j);
                    //            CCLog("oil:%d",json_as_int(*i));
                }
                else if(strcmp(node_name, "iron") == 0) {
                    //            json_number posY = json_as_float(*j);
                    //            bean->posY = posY;
                    bean->iron = json_as_int(*j);
                    //            CCLog("iron:%d",json_as_int(*i));
                }  else if (strcmp(node_name, "power") == 0) {
                    bean->honor = json_as_float(*j);
                    
                }   else if (strcmp(node_name, "userId") == 0){
//                    json_char* tempStr = json_as_string(*j);
                    bean->userId = json_as_int(*j);
//                    json_free(tempStr);
                } else if (strcmp(node_name, "defenSuccRate") == 0){
                    json_char* tempStr = json_as_string(*j);
                    bean->setDefenSuccRate(CCString::create(tempStr));
                    json_free(tempStr);
                } else if (strcmp(node_name, "trophyRate") == 0){
                    bean->trophyRate = json_as_float(*j);
                } else if (strcmp(node_name, "unionName") == 0) {
                    json_char* tempStr = json_as_string(*j);
                    bean->setUnionName(CCString::create(tempStr));
                    json_free(tempStr);
                }
                json_free(node_name);
                ++j;
            }
            array->addObject(bean);
        }
        
        
        ++i;
    }
    return array;
}

CCArray* MyJsonUtil::parseMatches(CCString* str) {
    
//    CCLog(str);
    if (str->compare("") == 0 ) {
        return CCArray::create();
    }
    JSONNODE* node = json_parse(str->getCString());
    if (node == NULL) {
        return CCArray::create();
    }
    JSONNODE_ITERATOR ri = json_begin(node);
    JSONNODE_ITERATOR i =json_begin(*ri);
    MatchInfoBean* infoBean;
    CCArray* beans = CCArray::create();
    

    while (i != json_end(*ri)){
        JSONNODE_ITERATOR j = json_begin(*i);
        infoBean = MatchInfoBean::create();
        while (j != json_end(*i)) {
            json_char *node_name = json_name(*j);
//            if (strcmp(node_name, "attack") == 0) {
//               
//                while (k!= json_end(*j)) {
//                    json_char *node_name1 = json_name(*k);
//                    if (strcmp(node_name1, "nickname") == 0) {
////                        CCLog("nickname:%s",json_as_string(*k));
//                    } else if(strcmp(node_name1, "ititaId") == 0) {
////                        CCLog("ititaId:%s",json_as_string(*k));
//                    } else if(strcmp(node_name1, "power") == 0) {
//                    } else if(strcmp(node_name1, "emblem") ==0) {
//                        json_char* tempStr = json_as_string(*k);
//                        infoBean->setEmblem(tempStr);
//                        json_free(tempStr);
//                    } else if(strcmp(node_name1, "unionName") ==0) {
//                    }
//                    json_free(node_name1);
//                    k++;
//                }
//
//            }else
            if (strcmp(node_name, "attackerUserId") == 0) {
//                json_char* tempStr = json_as_string(*j);
//                infoBean->setAttackId(tempStr);
                infoBean->attackUserId = json_as_int(*j);
//                json_free(tempStr);
            } else if (strcmp(node_name, "attackerNickname") == 0) {
                json_char* tempStr = json_as_string(*j);
                infoBean->setAttackNickName(tempStr);
                json_free(tempStr);
            } else if (strcmp(node_name, "attackerPower") == 0) {
                infoBean->enemyPower = json_as_float(*j);
            } else if (strcmp(node_name, "attackerUnionName") == 0) {
                json_char* tempStr = json_as_string(*j);
                infoBean->setUnionName(tempStr);
                json_free(tempStr);

            } else if(strcmp(node_name, "attackerVIPLevel") == 0) {
                infoBean->vipExperience = json_as_int(*j);
            }
//            else if (strcmp(node_name, "defense") == 0){
//                JSONNODE_ITERATOR k = json_begin(*j);
//                while (k!= json_end(*j)) {
//                    json_char *node_name1 = json_name(*k);
//                    if (strcmp(node_name1, "nickname") == 0) {
////                        CCLog("nickname:%s",json_as_string(*k));
//                    } else if(strcmp(node_name1, "ititaId") == 0) {
////                        CCLog("ititaId:%s",json_as_string(*k));
//                    }
//
//                }
//            }
//            else if (strcmp(node_name, "defenderItitaId") == 0) {
//                json_char* tempStr = json_as_string(*j);
//                infoBean->setDefenderId(tempStr);
//                json_free(tempStr);
//            } else if (strcmp(node_name, "defenderNickname") == 0) {
//                json_char* tempStr = json_as_string(*j);
//                infoBean->setDefenderNickName(tempStr);
//                json_free(tempStr);
//            } else if (strcmp(node_name, "defenderPower") == 0) {
////                infoBean->enemyPower = json_as_float(*j);
//            } else if (strcmp(node_name, "defenderUnionName") == 0) {
////                json_char* tempStr = json_as_string(*j);
////                infoBean->setUnionName(tempStr);
////                json_free(tempStr);
//            }
            else if (strcmp(node_name, "won") == 0){
       
                infoBean->isWin = json_as_bool(*j);
            } else if(strcmp(node_name, "type") == 0) {
                infoBean->attackType = json_as_int(*j);
            } else if (strcmp(node_name, "beforeCurrentTime") == 0){
                json_char* tempStr = json_as_string(*j);
                infoBean->setTime(tempStr);
                json_free(tempStr);
            }
            else if (strcmp(node_name, "trophyIron") == 0) {
                infoBean->robberIron = json_as_int(*j);

            }
            else if (strcmp(node_name, "trophyOil") == 0) {
                infoBean->robberOil = json_as_int(*j);
            
            }else if (strcmp(node_name, "trophyPower") == 0) {
                infoBean->deltaPower = json_as_float(*j);
//                CCLog("POWER:%d",infoBean->deltaPower);
            }
            else if (strcmp(node_name, "note") == 0) {
                json_char* tempStr = json_as_string(*j);
                infoBean->setNote(tempStr);
                json_free(tempStr);
                //                CCLog("POWER:%d",infoBean->deltaPower);
            }
            else if(strcmp(node_name, "unitJSON") == 0) {
                json_char* tempStr = json_as_string(*j);
                CCString*  unCompressingData = CryptologyUtil::decode64(CCString::create(tempStr));
                const char* str2 = DataCompressionUtil::unCompressData(unCompressingData)->getCString();
                
                JSONNODE* node1 = json_parse(str2);
                if (node1 == NULL) {
                    //todo 这里不友好啊
                    j++;
                    continue;
                }
                JSONNODE_ITERATOR k = json_begin(node1);
                
                
                
                while (k != json_end(node1)){
                    
                    CCAssert(i!=NULL, "非法的i节点");
                    JSONNODE_ITERATOR l = json_begin(*k);
                    while (l != json_end(*k)) {
                        
                        // get the node name and value as a string
                        json_char *node_name2 = json_name(*l);
                        if (strcmp(node_name2, "frameName") == 0) {
                            json_char* tempStr = json_as_string(*l);
                            infoBean->frameNameArray->addObject(CCString::create(tempStr));
                            json_free(tempStr);
                        } else if(strcmp(node_name2, "count") == 0) {
                            infoBean->unitCountArray->addObject(CCInteger::create(json_as_int(*l)));
                        } else if(strcmp(node_name2, "level")==0) {
                            infoBean->levelArray->addObject(CCInteger::create(json_as_int(*l)));
                        } else if(strcmp(node_name2, "rarity")==0) {
                            infoBean->rarityArray->addObject(CCInteger::create(json_as_int(*l)));
                        }
                        json_free(node_name2);
                        ++l;
                    }
                    ++k;
                }
            }
            json_free(node_name); 
            j++;
        }
        i++;
        beans->addObject(infoBean);
    }
    json_delete(node);
    return beans;
}

CCString* MyJsonUtil::packAllBattleBuilding(CCArray* array) {
    JSONNODE *parent = json_new(JSON_NODE);
    
    CCObject* obj;
    
    MyBattleBuilding* building;
    CCAssert(array->count()>0, "building must more than 0");
//    CCLog("arrayBuildingcount:%d",array->count());
    std::vector<char> strBuffer;
    strBuffer.clear();
    
    strBuffer.insert(strBuffer.end(), "[", "["+strlen("["));
   
    char tempStr[100] = {0};
    int i = 0;
    CCARRAY_FOREACH(array, obj) {
        JSONNODE *child = json_new(JSON_NODE);
        building = dynamic_cast<MyBattleBuilding*>(obj);
        if(building != NULL) {
            if (i > 0) {
                strBuffer.insert(strBuffer.end(), ",", ","+strlen(","));
            }
//            if(building->getTag() == CellarTag) {
//                CCLog("Cellar has comming");
//            }
            strBuffer.insert(strBuffer.end(), "{", "{"+strlen("{"));
//            json_push_back(child, json_new_i("tag", building->getTag()));
            sprintf(tempStr,"\"id\":\"%d\",",building->pid);
            strBuffer.insert(strBuffer.end(), tempStr, tempStr+strlen(tempStr));
            sprintf(tempStr,"\"tag\":\"%d\",",building->getTag());
            strBuffer.insert(strBuffer.end(), tempStr, tempStr+strlen(tempStr));
            if (building->fsm->getCurrentState()->getId() == RuinsStateTag) {
//                json_push_back(child, json_new_i("currentStateId",((RuinState*) building->fsm->getCurrentState())->currentId));
                sprintf(tempStr,"\"sid\":\"%d\",",((RuinState*) building->fsm->getCurrentState())->currentId);
                strBuffer.insert(strBuffer.end(), tempStr, tempStr+strlen(tempStr));
                MyBattleState* battleState = (MyBattleState*)(building->fsm->getState(WorkStateTag));
                if (battleState != NULL ) {
//                    json_push_back(child, json_new_f("arg0", capacity));
                    float arg0 = battleState->getArg0();
                    if (arg0 >= 0) {
                        sprintf(tempStr,"\"arg0\":\"%f\",",arg0);
                        strBuffer.insert(strBuffer.end(), tempStr, tempStr+strlen(tempStr));
                    }
                }
//                json_push_back(child, json_new_i("life",0));
                sprintf(tempStr,"\"life\":\"%d\",",0);
                strBuffer.insert(strBuffer.end(), tempStr, tempStr+strlen(tempStr));
            } else {
                MyBattleState* battleState = ((MyBattleState*)building->fsm->getCurrentState());
                sprintf(tempStr,"\"sid\":\"%d\",",building->fsm->getCurrentState()->getId());
                strBuffer.insert(strBuffer.end(), tempStr, tempStr+strlen(tempStr));
                float arg0 = battleState->getArg0();
                if (arg0 >=0) {
                    sprintf(tempStr,"\"arg0\":\"%f\",",arg0);
                    strBuffer.insert(strBuffer.end(), tempStr, tempStr+strlen(tempStr));
                }
                BeAttackState* beAttack = dynamic_cast<BeAttackState*>(battleState);
                if (beAttack) {
                    int life = beAttack->getLife()/beAttack->getMaxLife()*100;
                    if(life < 100) {
                        sprintf(tempStr,"\"life\":\"%d\",",life);
                        strBuffer.insert(strBuffer.end(), tempStr, tempStr+strlen(tempStr));
                    }
                }

            }
//            else if(building->fsm->getCurrentState()->getId() == GarbageCollectionStateTag) {
////                json_push_back(child, json_new_i("currentStateId", building->fsm->getCurrentState()->getId()));
//                sprintf(tempStr,"\"sid\":\"%i\",",building->fsm->getCurrentState()->getId());
//                strBuffer.insert(strBuffer.end(), tempStr, tempStr+strlen(tempStr));
////                json_push_back(child, json_new_i("arg0", ((GarbageCollectionState*)building->fsm->getCurrentState())->resourceCount));
//                sprintf(tempStr,"\"arg0\":\"%i\",",((GarbageCollectionState*)building->fsm->getCurrentState())->resourceCount);
//                strBuffer.insert(strBuffer.end(), tempStr, tempStr+strlen(tempStr));
//            } else {
////                json_push_back(child, json_new_i("currentStateId", building->fsm->getCurrentState()->getId()));
//                sprintf(tempStr,"\"sid\":\"%i\",",building->fsm->getCurrentState()->getId());
//                strBuffer.insert(strBuffer.end(), tempStr, tempStr+strlen(tempStr));
//                
//                if (dynamic_cast<ResourceBeAttackState*>(building->fsm->getState(WorkStateTag)) != NULL) {
//                    float capacity = ((ResourceBeAttackState*)building->fsm->getCurrentState())->getLastCapacity();
////                    json_push_back(child, json_new_f("arg0", capacity));
//                    sprintf(tempStr,"\"arg0\":\"%f\",",capacity);
//                    strBuffer.insert(strBuffer.end(), tempStr, tempStr+strlen(tempStr));
//                }
//                BeAttackState* beAttack = ((BeAttackState*)building->fsm->getCurrentState());
//                int life = beAttack->getLife()/beAttack->getMaxLife()*100;
////                CCLog("lastLife:%d",life);
//                if(life < 100) {
////                    json_push_back(child, json_new_i("life",life));
//                    sprintf(tempStr,"\"life\":\"%i\",",life);
//                    strBuffer.insert(strBuffer.end(), tempStr, tempStr+strlen(tempStr));
//                }
//            }
            CCPoint tiledPosi = building->getPositionByTiled();
//            json_push_back(child, json_new_f("posX", tiledPosi.x));
            sprintf(tempStr,"\"x\":\"%.2f\",",tiledPosi.x);
            strBuffer.insert(strBuffer.end(), tempStr, tempStr+strlen(tempStr));
            
//            json_push_back(child, json_new_f("posY", tiledPosi.y));
            sprintf(tempStr,"\"y\":\"%.2f\",",tiledPosi.y);
            strBuffer.insert(strBuffer.end(), tempStr, tempStr+strlen(tempStr));
            
//            json_push_back(child, json_new_i("level", building->getLevel()));
            sprintf(tempStr,"\"level\":\"%i\"",building->getLevel());
            strBuffer.insert(strBuffer.end(), tempStr, tempStr+strlen(tempStr));
            json_push_back(parent,child);
            //        json_delete(child);
            strBuffer.insert(strBuffer.end(), "}", "}"+strlen("}"));
            i++;
        }
        
    }
    strBuffer.insert(strBuffer.end(), "]", "]"+strlen("]"));
    
//    json_char *jc = json_write_formatted(parent);
//    json_delete(parent);
    char* sendStr = GXUtil::transCharVectorToCCString(&strBuffer);
//    CCLog(sendStr);
    CCString* result = CCString::create(sendStr);
    json_free(sendStr);
    return CryptologyUtil::encode64(DataCompressionUtil::compressData(result));
//    return result;
}

CCString* MyJsonUtil::packAllCreator() {
//    JSONNODE *child = json_new(JSON_NODE);
//    json_push_back(child, json_new_i("bubingLevel", MyGameInfo::getInstance()->bubingLevel));
//    json_push_back(child, json_new_i("tankLevel",  MyGameInfo::getInstance()->tankLevel));
//    json_char *jc = json_write_formatted(child);
//    //    CCLOG("%s", jc);
//    //    json_free(jc);
//    json_delete(child);
    
    
    
    JSONNODE *parent = json_new(JSON_NODE);
    
    CCObject* obj;
    
    CreatorInfoBean* creatorInfoBean;
    CCArray* array = MyGameInfo::getInstance()->creatorArray;
    char str[64] = {0};
    CCARRAY_FOREACH(array, obj) {
        JSONNODE *child = json_new(JSON_NODE);
        creatorInfoBean = dynamic_cast<CreatorInfoBean*>(obj);
        json_push_back(child, json_new_i("unitCardId", creatorInfoBean->creator->cardId));
        
        sprintf(str, "%lld", creatorInfoBean->getExperience());
        
        json_push_back(child, json_new_a("level", str));
        
        json_push_back(parent,child);
        //        json_delete(child);
    }
    
    json_char *jc = json_write_formatted(parent);
    //    json_free(jc);
    json_delete(parent);
    
    CCString* compressingData = DataCompressionUtil::compressData(CCString::create(jc));
    //    // base64??
    CCString*  dada = CryptologyUtil::encode64(compressingData);
    
//    CCString* result = CCString::create(dada);
    json_free(jc);

    return dada;
}

CCString* MyJsonUtil::parseUserData(CCString* str) {
    CCString* result = NULL;
//    CCLog(str);
    JSONNODE* node = json_parse(str->getCString());
    if (node == NULL) {
        return CCString::create("");
    }
    JSONNODE_ITERATOR i = json_begin(node);
    while (i != json_end(node)){
        json_char *node_name = json_name(*i);
        if(strcmp(node_name, "nickname") == 0) {
            json_char* tempStr = json_as_string(*i);
            result = CCString::create(tempStr);
            json_free(tempStr);
        }
        json_free(node_name);
        i++;
    }
    json_delete(node);
    return result;
}

CCArray* MyJsonUtil::parseTopRank(CCString *str) {
 
    JSONNODE* node = json_parse(str->getCString());
    if (node == NULL) {
        return CCArray::create();
    }
    JSONNODE_ITERATOR ri = json_begin(node);
    JSONNODE_ITERATOR i = json_begin(*ri);
    topRankBean* topBean;
    CCArray* beans = CCArray::create();
    
    
    while (i != json_end(*ri)){
        JSONNODE_ITERATOR j = json_begin(*i);
        topBean = topRankBean::create();
        while (j != json_end(*i)) {
            json_char *node_name = json_name(*j);
            if (strcmp(node_name, "rankNo") == 0) {
                topBean->rankNo = json_as_int(*j);
            } else if (strcmp(node_name, "ititaId") == 0){
                json_char* tempStr = json_as_string(*j);
                topBean->setItitaId(CCString::create(tempStr));
                json_free(tempStr);
            }
            else if (strcmp(node_name, "nickname") == 0){
                json_char* tempStr = json_as_string(*j);
                topBean->setNickname(CCString::create(tempStr));
                json_free(tempStr);
            }
            else if (strcmp(node_name, "power") == 0){
                topBean->power = json_as_float(*j);
            }
            else if(strcmp(node_name, "emblem") == 0) {
                json_char* tempStr = json_as_string(*j);
                topBean->setEmblem(CCString::create(tempStr));
                json_free(tempStr);
            }
            else if(strcmp(node_name, "unionName") == 0) {
                json_char* tempStr = json_as_string(*j);
                topBean->setUnionName(CCString::create(tempStr));
                json_free(tempStr);
            }
            json_free(node_name);
            j++;
        }
        i++;
        beans->addObject(topBean);
    }
    json_delete(node);
    return beans;
}

CCArray* MyJsonUtil::parseConscribeList(cocos2d::CCString *str) {
//    CCLog(str->getCString());
    JSONNODE* node = json_parse(str->getCString());
    if (node == NULL) {
        return CCArray::create();
    }
    JSONNODE_ITERATOR i = json_begin(node);
    ConscribeInfoBean* bean;
    CCArray* beans = CCArray::create();
    
    while (i != json_end(node)){
        JSONNODE_ITERATOR j = json_begin(*i);
        bean = ConscribeInfoBean::create();
        while (j != json_end(*i)) {
            json_char *node_name = json_name(*j);
            if (strcmp(node_name, "name") == 0) {
                json_char* tempStr = json_as_string(*j);
                bean->setJsonName(CCString::create(tempStr));
                json_free(tempStr);
            } else if (strcmp(node_name, "level") == 0){
                bean->level = json_as_int(*j);
            }
            else if (strcmp(node_name, "random") == 0){
                json_char* str = json_as_string(*j);
                CCArray* randomArray = GXUtil::Split(str, ",");
                CCObject* obj = NULL;
                int i = 0;
                CCAssert(randomArray->count()<=9, "more than avaliable");
                CCARRAY_FOREACH(randomArray, obj) {
                    CCString* cStr = (CCString*)obj;
                    int num = atoi(cStr->getCString());
                    bean->randomSeed[i] = num;
                    i++;
//                    CCAssert(i<9, "more than avaliable");
                }
                json_free(str);
            }
            json_free(node_name);
            j++;
        }
        i++;
        beans->addObject(bean);
    }
    return beans;
}

GXCommander* MyJsonUtil::parseGXCommanderByString(char* str) {
//    CCLog("接受内容为：%s",str);
    if(str[0] != '{') {
//        CCLog("2过来了么？");
    	return GXCommander::create();
    }
    JSONNODE* node = json_parse(str);
    
    
    JSONNODE_ITERATOR i = json_begin(node);
    GXCommander* comm = GXCommander::create();
    while (i != json_end(node)){
        json_char *node_name = json_name(*i);
        if (strcmp(node_name, "cmd") == 0) {
            comm->cmd->release();
            json_char* tempStr = json_as_string(*i);
            comm->cmd = GXString::create(tempStr);
            json_free(tempStr);
        } else if (strcmp(node_name, "succ") == 0){
            comm->succ = json_as_bool(*i);
        } else if (strcmp(node_name, "msg") == 0){
            comm->msg->release();
            json_char* tempStr = json_as_string(*i);
            comm->msg = GXString::create(tempStr);
            json_free(tempStr);
        } else if (strcmp(node_name, "details") == 0){
            comm->detail->release();
            json_char *jc = json_write_formatted(*i);
            comm->detail = GXString::create(jc);
            json_free(jc);
        }
        json_free(node_name);
        ++i;
    }
    json_delete(node);
    return comm;
}

UnionBean* MyJsonUtil::parseUserUnion(CCString* str) {
    JSONNODE* node = json_parse(str->getCString());
    JSONNODE_ITERATOR i = json_begin(node);
//    CCLog(str->getCString());
    if (i == NULL) {
        return UnionBean::create();
    }
    JSONNODE_ITERATOR j = json_begin(*i);
    UnionBean* bean = UnionBean::create();
    while (j != json_end(*i)){
        json_char *node_name = json_name(*j);
        if (strcmp(node_name, "description") == 0) {
            json_char* tempStr = json_as_string(*j);
            if (strcmp(tempStr,"") !=0) {
                bean->setDesc(CCString::create(tempStr));
            }
            json_free(tempStr);
        } else if (strcmp(node_name, "emblem") == 0){
            json_char* tempStr = json_as_string(*j);
            if (strcmp(tempStr,"") !=0) {
                bean->setEmblem(CCString::create(tempStr));
            }
            json_free(tempStr);
        } else if (strcmp(node_name, "level") == 0){
            bean->level = json_as_int(*j);
        } else if (strcmp(node_name, "name") == 0){
            json_char* tempStr = json_as_string(*j);
            if (strcmp(tempStr,"") !=0) {
                bean->setName(CCString::create(tempStr));
            }
            json_free(tempStr);
        } else if (strcmp(node_name, "unionId") == 0){
            bean->unionId = json_as_int(*j);
        } else if (strcmp(node_name, "role") == 0){
            bean->role = json_as_int(*j);
        } else if(strcmp(node_name, "memberCount") == 0) {
            bean->memberCount =json_as_int(*j);
        } else if (strcmp(node_name, "notice") == 0){
            json_char* tempStr = json_as_string(*j);
            if (strcmp(tempStr,"") !=0) {
                bean->setNotice(CCString::create(tempStr));
            }
            json_free(tempStr);
        }
//        else if (strcmp(node_name ,"list") == 0) {
//            JSONNODE_ITERATOR k = json_begin(*j);
//            GXArray* beanArray = GXArray::create();
//            while (k != json_end(*j)){
//                AsyUnionBean* unionBean = AsyUnionBean::create();
//                JSONNODE_ITERATOR l = json_begin(*k);
//                while (l !=  json_end(*k)) {
//                    json_char *node_name2 = json_name(*l);
//                    if (strcmp(node_name2, "description") == 0) {
//                        json_char* tempStr = json_as_string(*l);
//                        GXString* string = GXString::create(tempStr);
//                        json_free(tempStr);
//                        if (string->compare("") !=0) {
//                            unionBean->setDesc(string);
//                        }
//                        string->release();
//                    } else if (strcmp(node_name2, "emblem") == 0){
//                        json_char* tempStr = json_as_string(*l);
//                        GXString* string = GXString::create(tempStr);
//                        json_free(tempStr);
//                        if (string->compare("") !=0) {
//                            unionBean->setEmblem(string);
//                        }
//                        string->release();
//                    } else if (strcmp(node_name2, "level") == 0){
//                        unionBean->level = json_as_int(*l);
//                    } else if (strcmp(node_name2, "name") == 0){
//                        json_char* tempStr = json_as_string(*l);
//                        GXString* string = GXString::create(tempStr);
//                        json_free(tempStr);
//                        if (string->compare("") !=0) {
//                            unionBean->setName(string);
//                        }
//                        string->release();
//                    } else if (strcmp(node_name2, "unionId") == 0){
//                        unionBean->unionId = json_as_int(*l);
//                    } else if (strcmp(node_name2, "role") == 0){
//                        unionBean->role = json_as_int(*l);
//                    } else if (strcmp(node_name2, "notice") == 0){
//                        json_char* tempStr = json_as_string(*l);
//                        GXString* string = GXString::create(tempStr);
//                        json_free(tempStr);
//                        if (string->compare("") !=0) {
//                            unionBean->setNotice(string);
//                        }
//                        string->release();
//                    } else if(strcmp(node_name2, "memberCount") == 0) {
//                        unionBean->memberCount = json_as_int(*l);
//                    }
//                    json_free(node_name2);
//                    ++l;
//                }
//                beanArray->addObject(unionBean);
//                unionBean->release();
//                ++k;
//            }
//            msg->varMap->setObject(beanArray,"unions");
//            beanArray->release();
//        }
        json_free(node_name);
        ++j;
    }
    json_delete(node);
    return bean;
}

CCArray* MyJsonUtil::parseUnionList(CCString* str) {
    JSONNODE* node = json_parse(str->getCString());
    JSONNODE_ITERATOR i = json_begin(node);
    //    CCLog(str->getCString());
    if (i == NULL) {
        return CCArray::create();
    }
    JSONNODE_ITERATOR j = json_begin(*i);
    CCArray* beanArray = CCArray::create();
    while (j != json_end(*i)){
        json_char *node_name = json_name(*j);
        if (strcmp(node_name ,"list") == 0) {
            JSONNODE_ITERATOR k = json_begin(*j);
            while (k != json_end(*j)){
                UnionBean* bean = UnionBean::create();
                JSONNODE_ITERATOR l = json_begin(*k);
                while (l !=  json_end(*k)) {
                    json_char *node_name2 = json_name(*l);
                    if (strcmp(node_name2, "description") == 0) {
                        json_char* tempStr = json_as_string(*l);
                        if (strcmp(tempStr,"") !=0) {
                            bean->setDesc(CCString::create(tempStr));
                        }
                        json_free(tempStr);
                    } else if (strcmp(node_name2, "emblem") == 0){
                        json_char* tempStr = json_as_string(*l);
                        if (strcmp(tempStr,"") !=0) {
                            bean->setEmblem(CCString::create(tempStr));
                        }
                        json_free(tempStr);
                    } else if (strcmp(node_name2, "level") == 0){
                        bean->level = json_as_int(*l);
                    } else if (strcmp(node_name2, "name") == 0){
                        json_char* tempStr = json_as_string(*l);
                        if (strcmp(tempStr,"") !=0) {
                            bean->setName(CCString::create(tempStr));
                        }
                        json_free(tempStr);
                    } else if (strcmp(node_name2, "unionId") == 0){
                        bean->unionId = json_as_int(*l);
                    } else if (strcmp(node_name2, "role") == 0){
                        bean->role = json_as_int(*l);
                    } else if(strcmp(node_name2, "memberCount") == 0) {
                        bean->memberCount =json_as_int(*l);
                    } else if (strcmp(node_name2, "notice") == 0){
                        json_char* tempStr = json_as_string(*l);
                        if (strcmp(tempStr,"") !=0) {
                            bean->setNotice(CCString::create(tempStr));
                        }
                        json_free(tempStr);
                    }
                    json_free(node_name2);
                    ++l;
                }
                beanArray->addObject(bean);
                ++k;
            }
        }
        json_free(node_name);
        ++j;
    }
    json_delete(node);
    return beanArray;
}

CCArray* MyJsonUtil::parsePushUnionApplyJoin(CCString* str) {
    JSONNODE* node = json_parse(str->getCString());
    JSONNODE_ITERATOR i = json_begin(node);
//    CCLog(str->getCString());
    if (i == NULL) {
        return CCArray::create();
    }
    JSONNODE_ITERATOR j = json_begin(*i);
    CCArray* msgArray = CCArray::create();
    while (j != json_end(*i)){
        JSONNODE_ITERATOR k = json_begin(*j);
//        GXMessage* msg = GXMessage::create();
//        msg->cmd = GXString::create("unionApplyJoin");
        CCDictionary* varMap = CCDictionary::create();
        while (k != json_end(*j)) {
            json_char *node_name = json_name(*k);
            if (strcmp(node_name, "applicantUserId") == 0) {
                json_char* tempStr = json_as_string(*k);
                CCString* string = CCString::create(tempStr);
                json_free(tempStr);
                varMap->setObject(string,"applicant");
            } else if (strcmp(node_name, "extraMsg") == 0) {
                json_char* tempStr = json_as_string(*k);
                CCString* string = CCString::create(tempStr);
                json_free(tempStr);
                varMap->setObject(string,"extraMsg");
            } else if (strcmp(node_name, "unionId") == 0) {
                CCInteger* integer = CCInteger::create(json_as_int(*k));
                varMap->setObject(integer,"unionId");
            } else if (strcmp(node_name, "applicantNickname") == 0) {
                json_char* tempStr = json_as_string(*k);
                CCString* string = CCString::create(tempStr);
                json_free(tempStr);
                varMap->setObject(string,"applicantNickName");
            }
            json_free(node_name);
            k++;
        }
        msgArray->addObject(varMap);
//        msg->release();
        j++;
    }
    json_delete(node);
    return msgArray;
}

CCArray* MyJsonUtil::parseUnionMember(CCString* str) {
    JSONNODE* node = json_parse(str->getCString());
    JSONNODE_ITERATOR i = json_begin(node);
//    CCLog(str->getCString());
    if (i == NULL) {
        return CCArray::create();
    }
    CCArray* memberArray = CCArray::create();
    JSONNODE_ITERATOR j = json_begin(*i);
    while (j != json_end(*i)){
        json_char *node_name2 = json_name(*j);
        if (strcmp(node_name2,"list") == 0) {
            JSONNODE_ITERATOR k = json_begin(*j);
            while (k != json_end(*j)){
                MyMemberBean* bean = MyMemberBean::create();
                JSONNODE_ITERATOR l = json_begin(*k);
                while (l != json_end(*k)) {
                    json_char *node_name = json_name(*l);
                    if (strcmp(node_name,"userId") == 0) {
                        json_char* tempStr = json_as_string(*l);
                        bean->setItitaId(CCString::create(tempStr));
                        json_free(tempStr);
                    } else if(strcmp(node_name,"online") == 0) {
                        bean->isOnline = json_as_bool(*l);
                    } else if(strcmp(node_name,"power") == 0) {
                        bean->power = json_as_float(*l);
                    } else if(strcmp(node_name,"gameLevel") == 0) {
                        json_char* tempStr = json_as_string(*l);
                        bean->experience = atoll(tempStr);
                        json_free(tempStr);
                    } else if(strcmp(node_name,"nickname") == 0) {
                        json_char* tempStr = json_as_string(*l);
                        bean->setNickName(CCString::create(tempStr));
                        json_free(tempStr);
                    } else if(strcmp(node_name,"role") == 0) {
                        bean->role = json_as_int(*l);
                    }
                    json_free(node_name);
                    l++;
                }
                memberArray->addObject(bean);
                k++;
            }
        } else if(strcmp(node_name2,"record") == 0) {
            MyGameInfo::getInstance()->getUnionBean()->memberCount = json_as_int(*j);
        } else if(strcmp(node_name2,"pageCount") == 0) {
            MyGameInfo::getInstance()->getUnionBean()->memberPageCount = json_as_int(*j);
        } else if(strcmp(node_name2,"page") == 0) {
            MyGameInfo::getInstance()->getUnionBean()->memberPageNo = json_as_int(*j);
        }
        json_free(node_name2);
        j++;
    }
    json_delete(node);
    return memberArray;
}

GXMsg* MyJsonUtil::parseGXMsg(GXString* str) {
    JSONNODE* node = json_parse(str->getCString());
    JSONNODE_ITERATOR i = json_begin(node);
//    CCLog(str->getCString());
 
    JSONNODE_ITERATOR j = json_begin(*i);
    GXMsg* msg = GXMsg::create();
    while (j != json_end(*i)){
        json_char *node_name = json_name(*j);
        if (strcmp(node_name, "content") == 0) {
            json_char* tempStr = json_as_string(*j);
            msg->msg = tempStr;
            json_free(tempStr);
        } else if (strcmp(node_name, "speaker") == 0) {
            json_char* tempStr = json_as_string(*j);
            msg->name = tempStr;
            json_free(tempStr);
        } 
        json_free(node_name);
        j++;
    }
    json_delete(node);
    return msg;
}

BuildingCreator* MyJsonUtil::parseBuildingCreator(CCString *str) {
    JSONNODE* node = json_parse(str->getCString());
    JSONNODE_ITERATOR i = json_begin(node);
    BuildingCreator* creator = BuildingCreator::create();
    //    CCLog("%s",json_write_formatted(node));
    while (i != json_end(node)){
        json_char *node_name = json_name(*i);
        if (strcmp(node_name, "cardId") == 0) {
            creator->cardId = json_as_int(*i);
        } else if (strcmp(node_name, "name") == 0) {
            json_char* tempStr = json_as_string(*i);
            creator->setBuildingName(CCString::create(json_as_string(*i)));
            json_free(tempStr);
        } else if(strcmp(node_name, "spriteFileName") == 0) {
            json_char* tempStr = json_as_string(*i);
            creator->setSpriteFileName(CCString::create(json_as_string(*i)));
            json_free(tempStr);
        } else if(strcmp(node_name, "rarity") == 0) {
            creator->rarity = json_as_int(*i);
        } else if(strcmp(node_name, "descInfo") == 0) {
            JSONNODE_ITERATOR j = json_begin(*i);
            while (j != json_end(*i)){
                DescInfo* desc = DescInfo::create();
                JSONNODE_ITERATOR k = json_begin(*j);
                while (k != json_end(*j)){
                    json_char *node_name2 = json_name(*k);
                    if (strcmp(node_name2, "icon") == 0) {
                        json_char* tempStr = json_as_string(*k);
                        desc->icon = tempStr;
                        json_free(tempStr);
                    } else if (strcmp(node_name2, "label") == 0) {
                        json_char* tempStr = json_as_string(*k);
                        desc->label = tempStr;
                        json_free(tempStr);
                    }
                    
                    json_free(node_name2);
                    k++;
                }
                creator->descInfos->addObject(desc);
                j++;
            }
        }
        json_free(node_name);
        ++i;
    }
    json_delete(node);
    return creator;
}

void MyJsonUtil::parseBoughtInfo(CCString* str) {
    JSONNODE* node = json_parse(str->getCString());
    JSONNODE_ITERATOR rc = json_begin(node);
    JSONNODE_ITERATOR i = json_begin(*rc);
    
    
    while (i != json_end(*rc)){
        JSONNODE_ITERATOR j =json_begin(*i);
        while (j != json_end(*i)) {
            json_char *node_name = json_name(*j);
            if (strcmp(node_name, "tag") == 0) {
                MyGameInfo::getInstance()->boughtArray->addObject(CCInteger::create(json_as_int(*j)));
            }
            json_free(node_name);
            j++;
        }
        ++i;
    }
    json_delete(node);
}

void MyJsonUtil::parseLoginInfo(CCString* str) {
    JSONNODE* node = json_parse(str->getCString());
    JSONNODE_ITERATOR i = json_begin(node);
    while (i != json_end(node)){
        json_char *node_name = json_name(*i);
        if (strcmp(node_name, "userId") == 0) {
            PulsarNative::userId = json_as_int(*i);
        } else if(strcmp(node_name,"nickname") == 0) {
            json_char* tempChar = json_as_string(*i);
            MyGameInfo::getInstance()->setNickName(CCString::create(tempChar));
            json_free(tempChar);
        }
//        else if(strcmp(node_name,"VIPLevel") == 0) {
//            MyGameInfo::getInstance()->setVipExperience(json_as_int(*i));
//        }
        json_free(node_name);
        ++i;
    }
    json_delete(node);
}

bool MyJsonUtil::parseChargeInfo(CCString* str) {
    JSONNODE* node = json_parse(str->getCString());
    JSONNODE_ITERATOR rc = json_begin(node);
    JSONNODE_ITERATOR i = json_begin(*rc);
    bool isFirst = false;
    while (i != json_end(*rc)){
        
        json_char *node_name = json_name(*i);
        if (strcmp(node_name, "diamond") == 0) {
            MyGameInfo::getInstance()->setDiamond(json_as_int(*i));
        }else if(strcmp(node_name, "viplevel") == 0) {
            MyGameInfo::getInstance()->setVipExperience(json_as_int(*i));
        }else if(strcmp(node_name, "isFirst") == 0) {
            isFirst = json_as_bool(*i);
        }
        json_free(node_name);
        ++i;
    }
    json_delete(node);
    return isFirst;
}

CCArray* MyJsonUtil::parseServerInfo() {
    JSONNODE* node = json_parse(PulsarNative::getServerInfos());
    if (node == NULL) {
        return CCArray::create();
    }
    JSONNODE_ITERATOR k = json_begin(node);
    
    CCArray* beans = CCArray::create();
    
    while (k != json_end(node)){
        JSONNODE_ITERATOR i = json_begin(*k);
        SeverInfoBean* infoBean = SeverInfoBean::create();
        while (i != json_end(*k)){
            json_char *node_name = json_name(*i);
            if (strcmp(node_name, "serverId") == 0) {
//                MyGameInfo::getInstance()->setDiamond(json_as_int(*i));
                infoBean->serverId = json_as_int(*i);
            }else if(strcmp(node_name, "serverName") == 0) {
//                MyGameInfo::getInstance()->setVipExperience(json_as_int(*i));
                json_char* tempStr = json_as_string(*i);
                infoBean->setServerName(CCString::create(tempStr));
                json_free(tempStr);
            }else if(strcmp(node_name, "serverStatus") == 0) {
                json_char* tempStr = json_as_string(*i);
                infoBean->setServerStatus(CCString::create(tempStr));
                json_free(tempStr);
            }else if(strcmp(node_name, "serverStatusId") == 0) {
                infoBean->serverStatusId = json_as_int(*i);
            }else if(strcmp(node_name, "hostUrl") == 0) {
                json_char* tempStr = json_as_string(*i);
                infoBean->setHostUrl(CCString::create(tempStr));
                json_free(tempStr);
            }else if(strcmp(node_name, "chatServerUrl") == 0) {
                json_char* tempStr = json_as_string(*i);
                infoBean->setChatServerUrl(CCString::create(tempStr));
                json_free(tempStr);
            }
            json_free(node_name);
            ++i;
        }
        beans->addObject(infoBean);
        k++;
    }
    json_delete(node);
    return beans;
}

const char* MyJsonUtil::parseGameInfo(const char* str) {
//    CCLog(str);
    JSONNODE* node = json_parse(str);
    if (node == NULL) {
        char* returnStr = new char[10];
        return strcpy(returnStr,"{}");
    }
    JSONNODE_ITERATOR k = json_begin(node);
    
//    CCArray* beans = CCArray::create();
    char* temp = new char[10];
    strcpy(temp,"{}");
    while (k != json_end(node)){
        json_char *node_name = json_name(*k);
        if (strcmp(node_name, "update") == 0) {
            JSONNODE_ITERATOR i = json_begin(*k);
            while (i != json_end(*k)){
                json_char *node_name1 = json_name(*i);
                if (strcmp(node_name1, "mustUpdate") == 0) {
                    json_char* tempStr = json_as_string(*i);
                    bool flag = false;
                    if (strcmp(tempStr, "true") == 0) {
                        flag = true;
                    }
                    json_free(tempStr);
                    if (flag) {
                        json_free(node_name1);
                        json_free(node_name);
                        json_delete(node);
                        char* returnStr = new char[10];
                        return strcpy(returnStr,"update");
                    }
                }
                json_free(node_name1);
                ++i;
            }
        } else if(strcmp(node_name,"serverItems") == 0){
            delete temp;
            temp = json_write_formatted(*k);
        }
        json_free(node_name);
        k++;
    }
    json_delete(node);
    return temp;
}

CCArray* MyJsonUtil::parseQuest(CCString* str) {
//    CCLog("%s",str->getCString());
    JSONNODE* node = json_parse(str->getCString());
    JSONNODE_ITERATOR i = json_begin(node);

    CCArray* beans = CCArray::create();

    while (i != json_end(node)){
//        JSONNODE_ITERATOR i = json_begin(*k);
//        SeverInfoBean* infoBean = SeverInfoBean::create();
        json_char *node_name = json_name(*i);
        int tag = atoi(node_name);
//        CCLog("tag:%d",tag);
        if (tag/1000 == 0) {
            JSONNODE_ITERATOR j = json_begin(*i);
            EveryDayTask1* task = EveryDayTask1::create();
            while (j != json_end(*i)){
                json_char *node_name1 = json_name(*j);
                
                if (strcmp(node_name1,"missionId") == 0) {
                    task->questId = json_as_int(*j);
                }else if (strcmp(node_name1,"hasNext") == 0) {
                    task->hasNext = json_as_bool(*j);
                } else if(strcmp(node_name1,"title") == 0) {
                    json_char* tempStr = json_as_string(*j);
                    task->setTitleStr(CCString::create(tempStr));
                    json_free(tempStr);
                } else if(strcmp(node_name1,"desc") == 0) {
                    json_char* tempStr = json_as_string(*j);
                    task->setDescStr(CCString::create(tempStr));
                    json_free(tempStr);
                } else if(strcmp(node_name1,"missionIconName") == 0) {
                    json_char* tempStr = json_as_string(*j);
                    task->setIconName(CCString::create(tempStr));
                    json_free(tempStr);
                } else if(strcmp(node_name1,"deadlineTime") == 0) {
                    json_char* tempStr = json_as_string(*j);
                    task->deadLine = atoll(tempStr);
                    json_free(tempStr);
                } else if(strcmp(node_name1,"deadlineStr") == 0) {
                    json_char* tempStr = json_as_string(*j);
                    task->setdeadLineLabel(CCString::create(tempStr));
                    json_free(tempStr);
                } else if(strcmp(node_name1,"costResourceTags") == 0) {
                    JSONNODE_ITERATOR k = json_begin(*j);
                    while (k != json_end(*j)){
                        task->costResourceTagList->addObject(GXintValue::create(json_as_int(*k)));
                        k++;
                    }
                } else if(strcmp(node_name1,"costResourceCounts") == 0) {
                    JSONNODE_ITERATOR k = json_begin(*j);
                    while (k != json_end(*j)){
                        task->costResourceCountList->addObject(GXintValue::create(json_as_int(*k)));
                        k++;
                    }
                } else if(strcmp(node_name1,"prizeResourceTags") == 0) {
                    JSONNODE_ITERATOR k = json_begin(*j);
                    while (k != json_end(*j)){
                        task->prizeResourceTagList->addObject(GXintValue::create(json_as_int(*k)));
                        k++;
                    }
                } else if(strcmp(node_name1,"prizeResourceCounts") == 0) {
                    JSONNODE_ITERATOR k = json_begin(*j);
                    while (k != json_end(*j)){
                        task->prizeResourceCountList->addObject(GXintValue::create(json_as_int(*k)));
                        k++;
                    }
                }  else if(strcmp(node_name1,"dialog") == 0) {
                    json_char* tempStr = json_as_string(*j);
                    if (strcmp("",tempStr) !=0 ) {
                        CCString*  unCompressingData = CryptologyUtil::decode64(CCString::create(tempStr));
                        const char* str2 = DataCompressionUtil::unCompressData(unCompressingData)->getCString();
                        task->setDialog(GXJsonUtil::parseDiaLayerInfoBean(str2));
                    }
                    json_free(tempStr);
                }
                json_free(node_name1);
                ++j;
            }
            beans->addObject(task);
        } else if(tag/1000 == 1) {
            JSONNODE_ITERATOR j = json_begin(*i);
            PowerQuest* task = PowerQuest::create();
            while (j != json_end(*i)){
                json_char *node_name1 = json_name(*j);
                
                if (strcmp(node_name1,"missionId") == 0) {
                    task->questId = json_as_int(*j);
                }else if (strcmp(node_name1,"hasNext") == 0) {
                    task->hasNext = json_as_bool(*j);
                } else if(strcmp(node_name1,"title") == 0) {
                    json_char* tempStr = json_as_string(*j);
                    task->setTitleStr(CCString::create(tempStr));
                    json_free(tempStr);
                } else if(strcmp(node_name1,"desc") == 0) {
                    json_char* tempStr = json_as_string(*j);
                    task->setDescStr(CCString::create(tempStr));
                    json_free(tempStr);
                } else if(strcmp(node_name1,"missionIconName") == 0) {
                    json_char* tempStr = json_as_string(*j);
                    task->setIconName(CCString::create(tempStr));
                    json_free(tempStr);
                } else if(strcmp(node_name1,"deadlineTime") == 0) {
                    json_char* tempStr = json_as_string(*j);
                    task->deadLine = atoll(tempStr);
                    json_free(tempStr);
                } else if(strcmp(node_name1,"deadlineStr") == 0) {
                    json_char* tempStr = json_as_string(*j);
                    task->setdeadLineLabel(CCString::create(tempStr));
                    json_free(tempStr);
                } else if(strcmp(node_name1,"costResourceTags") == 0) {
                    JSONNODE_ITERATOR k = json_begin(*j);
                    while (k != json_end(*j)){
                        task->costResourceTagList->addObject(GXintValue::create(json_as_int(*k)));
                        k++;
                    }
                } else if(strcmp(node_name1,"costResourceCounts") == 0) {
                    JSONNODE_ITERATOR k = json_begin(*j);
                    while (k != json_end(*j)){
                        task->costResourceCountList->addObject(GXintValue::create(json_as_int(*k)));
                        k++;
                    }
                } else if(strcmp(node_name1,"prizePower") == 0) {
                    task->prizePower->setValue(json_as_float(*j));
                }  else if(strcmp(node_name1,"dialog") == 0) {
                    json_char* tempStr = json_as_string(*j);
                    if (strcmp("",tempStr) !=0 ) {
                        CCString*  unCompressingData = CryptologyUtil::decode64(CCString::create(tempStr));
                        const char* str2 = DataCompressionUtil::unCompressData(unCompressingData)->getCString();
                        task->setDialog(GXJsonUtil::parseDiaLayerInfoBean(str2));
                    }
                    json_free(tempStr);
                }
                json_free(node_name1);
                ++j;
            }
            beans->addObject(task);
        } else if(tag/1000 == 2) {
            JSONNODE_ITERATOR j = json_begin(*i);
            BuildingQuest* task = BuildingQuest::create();
            while (j != json_end(*i)){
                json_char *node_name1 = json_name(*j);
                
                if (strcmp(node_name1,"missionId") == 0) {
                    task->questId = json_as_int(*j);
                }else if (strcmp(node_name1,"hasNext") == 0) {
                    task->hasNext = json_as_bool(*j);
                } else if(strcmp(node_name1,"title") == 0) {
                    json_char* tempStr = json_as_string(*j);
                    task->setTitleStr(CCString::create(tempStr));
                    json_free(tempStr);
                } else if(strcmp(node_name1,"desc") == 0) {
                    json_char* tempStr = json_as_string(*j);
                    task->setDescStr(CCString::create(tempStr));
                    json_free(tempStr);
                } else if(strcmp(node_name1,"missionIconName") == 0) {
                    json_char* tempStr = json_as_string(*j);
                    task->setIconName(CCString::create(tempStr));
                    json_free(tempStr);
                } else if(strcmp(node_name1,"deadlineTime") == 0) {
                    json_char* tempStr = json_as_string(*j);
                    task->deadLine = atoll(tempStr);
                    json_free(tempStr);
                } else if(strcmp(node_name1,"deadlineStr") == 0) {
                    json_char* tempStr = json_as_string(*j);
                    task->setdeadLineLabel(CCString::create(tempStr));
                    json_free(tempStr);
                } else if(strcmp(node_name1,"needBuildingTags") == 0) {
                    JSONNODE_ITERATOR k = json_begin(*j);
                    while (k != json_end(*j)){
                        task->needBuildingTagList->addObject(GXintValue::create(json_as_int(*k)));
                        k++;
                    }
                } else if(strcmp(node_name1,"needBuildingLabels") == 0) {
                    JSONNODE_ITERATOR k = json_begin(*j);
                    while (k != json_end(*j)){
                        json_char* tempStr = json_as_string(*j);
                        task->needBuildingLabelList->addObject(CCString::create(json_as_string(*k)));
                        json_free(tempStr);
                        k++;
                    }
                } else if(strcmp(node_name1,"needBuildingCounts") == 0) {
                    JSONNODE_ITERATOR k = json_begin(*j);
                    while (k != json_end(*j)){
                        task->needBuildingCountList->addObject(GXintValue::create(json_as_int(*k)));
                        k++;
                    }
                } else if(strcmp(node_name1,"needBuildingLevels") == 0) {
                    JSONNODE_ITERATOR k = json_begin(*j);
                    while (k != json_end(*j)){
                        task->needBuildingLevelList->addObject(GXintValue::create(json_as_int(*k)));
                        k++;
                    }
                }  else if(strcmp(node_name1,"finishBuildingCounts") == 0) {
                    JSONNODE_ITERATOR k = json_begin(*j);
                    while (k != json_end(*j)){
                        task->finishBuildingCountList->addObject(GXintValue::create(json_as_int(*k)));
                        k++;
                    }
                }  else if(strcmp(node_name1,"prizeResourceTags") == 0) {
                    JSONNODE_ITERATOR k = json_begin(*j);
                    while (k != json_end(*j)){
                        task->prizeResourceTagList->addObject(GXintValue::create(json_as_int(*k)));
                        k++;
                    }
                } else if(strcmp(node_name1,"prizeResourceCounts") == 0) {
                    JSONNODE_ITERATOR k = json_begin(*j);
                    while (k != json_end(*j)){
                        task->prizeResourceCountList->addObject(GXintValue::create(json_as_int(*k)));
                        k++;
                    }
                } else if(strcmp(node_name1,"dialog") == 0) {
                    json_char* tempStr = json_as_string(*j);
                    if (strcmp("",tempStr) !=0 ) {
                        CCString*  unCompressingData = CryptologyUtil::decode64(CCString::create(tempStr));
                        const char* str2 = DataCompressionUtil::unCompressData(unCompressingData)->getCString();
                        task->setDialog(GXJsonUtil::parseDiaLayerInfoBean(str2));
                    }
                    json_free(tempStr);
                }
                json_free(node_name1);
                ++j;
            }
            task->checkCompleteStatues();
            beans->addObject(task);
        } else if(tag/1000 == 3) {
            JSONNODE_ITERATOR j = json_begin(*i);
            ArmyQuest* task = ArmyQuest::create();
            while (j != json_end(*i)){
                json_char *node_name1 = json_name(*j);
                
                if (strcmp(node_name1,"missionId") == 0) {
                    task->questId = json_as_int(*j);
                }else if (strcmp(node_name1,"hasNext") == 0) {
                    task->hasNext = json_as_bool(*j);
                } else if(strcmp(node_name1,"title") == 0) {
                    json_char* tempStr = json_as_string(*j);
                    task->setTitleStr(CCString::create(tempStr));
                    json_free(tempStr);
                } else if(strcmp(node_name1,"desc") == 0) {
                    json_char* tempStr = json_as_string(*j);
                    task->setDescStr(CCString::create(tempStr));
                    json_free(tempStr);
                } else if(strcmp(node_name1,"missionIconName") == 0) {
                    json_char* tempStr = json_as_string(*j);
                    task->setIconName(CCString::create(tempStr));
                    json_free(tempStr);
                } else if(strcmp(node_name1,"deadlineTime") == 0) {
                    json_char* tempStr = json_as_string(*j);
                    task->deadLine = atoll(tempStr);
                    json_free(tempStr);
                } else if(strcmp(node_name1,"deadlineStr") == 0) {
                    json_char* tempStr = json_as_string(*j);
                    task->setdeadLineLabel(CCString::create(tempStr));
                    json_free(tempStr);
                } else if(strcmp(node_name1,"needArmyTags") == 0) {
                    JSONNODE_ITERATOR k = json_begin(*j);
                    while (k != json_end(*j)){
                        task->needArmyTagList->addObject(GXintValue::create(json_as_int(*k)));
                        task->finishArmyList->addObject(GXintValue::create(0));
                        k++;
                    }
                } else if(strcmp(node_name1,"needArmyLevels") == 0) {
                    JSONNODE_ITERATOR k = json_begin(*j);
                    while (k != json_end(*j)){
                        json_char* tempStr = json_as_string(*j);
                        task->needArmyLevelList->addObject(GXintValue::create(json_as_int(*k)));
                        json_free(tempStr);
                        k++;
                    }
                } else if(strcmp(node_name1,"needArmyLabels") == 0) {
                    JSONNODE_ITERATOR k = json_begin(*j);
                    while (k != json_end(*j)){
                        task->needArmyLabelList->addObject(CCString::create(json_as_string(*k)));
                        k++;
                    }
                } else if(strcmp(node_name1,"finishArmyCounts") == 0) {
                    JSONNODE_ITERATOR k = json_begin(*j);
                    while (k != json_end(*j)){
                        task->finishArmyList->addObject(GXintValue::create(json_as_int(*k)));
                        k++;
                    }
                }  else if(strcmp(node_name1,"prizeResourceTags") == 0) {
                    JSONNODE_ITERATOR k = json_begin(*j);
                    while (k != json_end(*j)){
                        task->prizeResourceTagList->addObject(GXintValue::create(json_as_int(*k)));
                        k++;
                    }
                } else if(strcmp(node_name1,"prizeResourceCounts") == 0) {
                    JSONNODE_ITERATOR k = json_begin(*j);
                    while (k != json_end(*j)){
                        task->prizeResourceCountList->addObject(GXintValue::create(json_as_int(*k)));
                        k++;
                    }
                }  else if(strcmp(node_name1,"dialog") == 0) {
                    json_char* tempStr = json_as_string(*j);
                    if (strcmp("",tempStr) !=0 ) {
                        CCString*  unCompressingData = CryptologyUtil::decode64(CCString::create(tempStr));
                        const char* str2 = DataCompressionUtil::unCompressData(unCompressingData)->getCString();
                        task->setDialog(GXJsonUtil::parseDiaLayerInfoBean(str2));
                    }
                    json_free(tempStr);
                }
                json_free(node_name1);
                ++j;
            }
            beans->addObject(task);
        }  else if(tag/1000 == 4) {
            JSONNODE_ITERATOR j = json_begin(*i);
            BattleQuest* task = BattleQuest::create();
            while (j != json_end(*i)){
                json_char *node_name1 = json_name(*j);
                
                if (strcmp(node_name1,"missionId") == 0) {
                    task->questId = json_as_int(*j);
                }else if (strcmp(node_name1,"hasNext") == 0) {
                    task->hasNext = json_as_bool(*j);
                } else if(strcmp(node_name1,"title") == 0) {
                    json_char* tempStr = json_as_string(*j);
                    task->setTitleStr(CCString::create(tempStr));
                    json_free(tempStr);
                } else if(strcmp(node_name1,"desc") == 0) {
                    json_char* tempStr = json_as_string(*j);
                    task->setDescStr(CCString::create(tempStr));
                    json_free(tempStr);
                } else if(strcmp(node_name1,"missionIconName") == 0) {
                    json_char* tempStr = json_as_string(*j);
                    task->setIconName(CCString::create(tempStr));
                    json_free(tempStr);
                } else if(strcmp(node_name1,"deadlineTime") == 0) {
                    json_char* tempStr = json_as_string(*j);
                    task->deadLine = atoll(tempStr);
                    json_free(tempStr);
                } else if(strcmp(node_name1,"deadlineStr") == 0) {
                    json_char* tempStr = json_as_string(*j);
                    task->setdeadLineLabel(CCString::create(tempStr));
                    json_free(tempStr);
                } else if(strcmp(node_name1,"needAttackTimes") == 0) {
                    task->needBattleTimes->setValue(json_as_float(*j));
                } else if(strcmp(node_name1,"finishAttackTimes") == 0) {
                    task->battleTimes->setValue(json_as_float(*j));
                } else if(strcmp(node_name1,"prizeResourceTags") == 0) {
                    JSONNODE_ITERATOR k = json_begin(*j);
                    while (k != json_end(*j)){
                        task->prizeResourceTagList->addObject(GXintValue::create(json_as_int(*k)));
                        k++;
                    }
                } else if(strcmp(node_name1,"prizeResourceCounts") == 0) {
                    JSONNODE_ITERATOR k = json_begin(*j);
                    while (k != json_end(*j)){
                        task->prizeResourceCountList->addObject(GXintValue::create(json_as_int(*k)));
                        k++;
                    }
                }  else if(strcmp(node_name1,"dialog") == 0) {
                    json_char* tempStr = json_as_string(*j);
                    if (strcmp("",tempStr) !=0 ) {
                        CCString*  unCompressingData = CryptologyUtil::decode64(CCString::create(tempStr));
                        const char* str2 = DataCompressionUtil::unCompressData(unCompressingData)->getCString();
                        task->setDialog(GXJsonUtil::parseDiaLayerInfoBean(str2));
                    }
                    json_free(tempStr);
                }
                json_free(node_name1);
                ++j;
            }
            beans->addObject(task);
        }  else if(tag/1000 == 5) {
            JSONNODE_ITERATOR j = json_begin(*i);
            DefendQuest* task = DefendQuest::create();
            while (j != json_end(*i)){
                json_char *node_name1 = json_name(*j);
                
                if (strcmp(node_name1,"missionId") == 0) {
                    task->questId = json_as_int(*j);
                }else if (strcmp(node_name1,"hasNext") == 0) {
                    task->hasNext = json_as_bool(*j);
                } else if(strcmp(node_name1,"title") == 0) {
                    json_char* tempStr = json_as_string(*j);
                    task->setTitleStr(CCString::create(tempStr));
                    json_free(tempStr);
                } else if(strcmp(node_name1,"desc") == 0) {
                    json_char* tempStr = json_as_string(*j);
                    task->setDescStr(CCString::create(tempStr));
                    json_free(tempStr);
                } else if(strcmp(node_name1,"missionIconName") == 0) {
                    json_char* tempStr = json_as_string(*j);
                    task->setIconName(CCString::create(tempStr));
                    json_free(tempStr);
                } else if(strcmp(node_name1,"deadlineTime") == 0) {
                    json_char* tempStr = json_as_string(*j);
                    task->deadLine = atoll(tempStr);
                    json_free(tempStr);
                } else if(strcmp(node_name1,"deadlineStr") == 0) {
                    json_char* tempStr = json_as_string(*j);
                    task->setdeadLineLabel(CCString::create(tempStr));
                    json_free(tempStr);
                } else if(strcmp(node_name1,"needDefendTimes") == 0) {
                    task->needDefendTimes->setValue(json_as_float(*j));
                } else if(strcmp(node_name1,"finishDefendTimes") == 0) {
                    task->defendTimes->setValue(json_as_float(*j));
                } else if(strcmp(node_name1,"prizeResourceTags") == 0) {
                    JSONNODE_ITERATOR k = json_begin(*j);
                    while (k != json_end(*j)){
                        task->prizeResourceTagList->addObject(GXintValue::create(json_as_int(*k)));
                        k++;
                    }
                } else if(strcmp(node_name1,"prizeResourceCounts") == 0) {
                    JSONNODE_ITERATOR k = json_begin(*j);
                    while (k != json_end(*j)){
                        task->prizeResourceCountList->addObject(GXintValue::create(json_as_int(*k)));
                        k++;
                    }
                }  else if(strcmp(node_name1,"dialog") == 0) {
                    json_char* tempStr = json_as_string(*j);
                    if (strcmp("",tempStr) !=0 ) {
                        CCString*  unCompressingData = CryptologyUtil::decode64(CCString::create(tempStr));
                        const char* str2 = DataCompressionUtil::unCompressData(unCompressingData)->getCString();
                        task->setDialog(GXJsonUtil::parseDiaLayerInfoBean(str2));
                    }
                    json_free(tempStr);
                }
                json_free(node_name1);
                ++j;
            }
            beans->addObject(task);
        }  else if(tag/1000 == 6) {
            JSONNODE_ITERATOR j = json_begin(*i);
            LevelQuest* task = LevelQuest::create();
            while (j != json_end(*i)){
                json_char *node_name1 = json_name(*j);
                
                if (strcmp(node_name1,"missionId") == 0) {
                    task->questId = json_as_int(*j);
                }else if (strcmp(node_name1,"hasNext") == 0) {
                    task->hasNext = json_as_bool(*j);
                } else if(strcmp(node_name1,"title") == 0) {
                    json_char* tempStr = json_as_string(*j);
                    task->setTitleStr(CCString::create(tempStr));
                    json_free(tempStr);
                } else if(strcmp(node_name1,"desc") == 0) {
                    json_char* tempStr = json_as_string(*j);
                    task->setDescStr(CCString::create(tempStr));
                    json_free(tempStr);
                } else if(strcmp(node_name1,"missionIconName") == 0) {
                    json_char* tempStr = json_as_string(*j);
                    task->setIconName(CCString::create(tempStr));
                    json_free(tempStr);
                } else if(strcmp(node_name1,"deadlineTime") == 0) {
                    json_char* tempStr = json_as_string(*j);
                    task->deadLine = atoll(tempStr);
                    json_free(tempStr);
                } else if(strcmp(node_name1,"deadlineStr") == 0) {
                    json_char* tempStr = json_as_string(*j);
                    task->setdeadLineLabel(CCString::create(tempStr));
                    json_free(tempStr);
                } else if(strcmp(node_name1,"needLevel") == 0) {
                    task->needLevel->setValue(json_as_float(*j));
                }  else if(strcmp(node_name1,"prizeResourceTags") == 0) {
                    JSONNODE_ITERATOR k = json_begin(*j);
                    while (k != json_end(*j)){
                        task->prizeResourceTagList->addObject(GXintValue::create(json_as_int(*k)));
                        k++;
                    }
                } else if(strcmp(node_name1,"prizeResourceCounts") == 0) {
                    JSONNODE_ITERATOR k = json_begin(*j);
                    while (k != json_end(*j)){
                        task->prizeResourceCountList->addObject(GXintValue::create(json_as_int(*k)));
                        k++;
                    }
                }  else if(strcmp(node_name1,"dialog") == 0) {
                    json_char* tempStr = json_as_string(*j);
                    if (strcmp("",tempStr) !=0 ) {
                        CCString*  unCompressingData = CryptologyUtil::decode64(CCString::create(tempStr));
                        const char* str2 = DataCompressionUtil::unCompressData(unCompressingData)->getCString();
                        task->setDialog(GXJsonUtil::parseDiaLayerInfoBean(str2));
                    }
                    json_free(tempStr);
                }
                json_free(node_name1);
                ++j;
            }
            beans->addObject(task);
        }
        json_free(node_name);
        ++i;
    }
    json_delete(node);
    return beans;
}

AttackerInfoBean* MyJsonUtil::parseAttackInfoBean(CCString* str) {
    JSONNODE* node = json_parse(str->getCString());
    JSONNODE_ITERATOR i = json_begin(node);
    
    AttackerInfoBean* bean = AttackerInfoBean::create();
    while (i != json_end(node)){
        json_char *node_name = json_name(*i);
        if (strcmp(node_name, "attackerLevel") == 0) {
            bean->attackerLevel = json_as_int(*i);
        } else if(strcmp(node_name, "attackerAvatarStr") == 0) {
            json_char* tempStr = json_as_string(*i);
            bean->setAttackerAvatarStr(CCString::create(tempStr));
            json_free(tempStr);
        } else if(strcmp(node_name, "attackSpriteStr") == 0) {
//            json_char* tempStr = json_as_string(*i);
//            bean->setAttackSpriteStr(CCString::create(tempStr));
//            json_free(tempStr);
        } else if(strcmp(node_name, "attackerTag") == 0) {
            bean->setCreatorInfoBean(CreatorInfoBean::create(json_as_int(*i)));
        } else if(strcmp(node_name, "attackerNickname") == 0) {
            json_char* tempStr = json_as_string(*i);
            bean->setAttackerNickname(CCString::create(tempStr));
            json_free(tempStr);
        } else if(strcmp(node_name, "attackerPower") == 0) {
            bean->attackerPower = json_as_int(*i);
        } else if(strcmp(node_name, "attackerCount") == 0) {
            bean->attackerCount = json_as_int(*i);
        } else if(strcmp(node_name, "CPUWarLevel") == 0) {
            bean->level = json_as_int(*i);
        } else if(strcmp(node_name, "CPUWarMaxLevel") == 0) {
            bean->maxLevel = json_as_int(*i);
        } else if(strcmp(node_name, "attackerDirection") == 0) {
            bean->attackerDirection = json_as_int(*i);
        }
        json_free(node_name);
        ++i;
    }
    json_delete(node);
    return bean;
}

CCArray* MyJsonUtil::parsePushMatch(CCString* str) {
    //    CCLog(str);
    if (str->compare("") == 0 ) {
        return CCArray::create();
    }
    JSONNODE* node = json_parse(str->getCString());
    if (node == NULL) {
        return CCArray::create();
    }

    MatchInfoBean* infoBean;
    CCArray* beans = CCArray::create();
    
    JSONNODE_ITERATOR j = json_begin(node);
    infoBean = MatchInfoBean::create();
    while (j != json_end(node)) {
        json_char *node_name = json_name(*j);
//        if (strcmp(node_name, "attackerItitaId") == 0) {
//            json_char* tempStr = json_as_string(*j);
//            infoBean->setAttackId(tempStr);
//            json_free(tempStr);
//        } else if (strcmp(node_name, "attackerNickname") == 0) {
//            json_char* tempStr = json_as_string(*j);
//            infoBean->setAttackNickName(tempStr);
//            json_free(tempStr);
//        } else if (strcmp(node_name, "attackerPower") == 0) {
//            infoBean->enemyPower = json_as_float(*j);
//        } else if (strcmp(node_name, "attackerUnionName") == 0) {
//            json_char* tempStr = json_as_string(*j);
//            infoBean->setUnionName(tempStr);
//            json_free(tempStr);
//            
//        } else if(strcmp(node_name, "attackerVIPLevel") == 0) {
//            infoBean->vipExperience = json_as_int(*j);
//        }
//        else
//        if (strcmp(node_name, "defenderItitaId") == 0) {
//            json_char* tempStr = json_as_string(*j);
//            infoBean->setDefenderId(tempStr);
//            json_free(tempStr);
//        }
//        else if (strcmp(node_name, "defenderNickname") == 0) {
//            json_char* tempStr = json_as_string(*j);
//            infoBean->setDefenderNickName(tempStr);
//            json_free(tempStr);
//        }
//        else
        if (strcmp(node_name, "defenderPower") == 0) {
            MyGameInfo::getInstance()->setPower(json_as_float(*j));
        }  else if(strcmp(node_name,"defenderOil") == 0) {
            json_char* tempStr = json_as_string(*j);
            MyGameInfo::getInstance()->setOil(atol(tempStr));
            json_free(tempStr);
        } else if(strcmp(node_name,"defenderIron") == 0) {
            json_char* tempStr = json_as_string(*j);
            MyGameInfo::getInstance()->setIron(atol(tempStr));
            json_free(tempStr);
        }

//        else if (strcmp(node_name, "defenderUnionName") == 0) {
//            //                json_char* tempStr = json_as_string(*j);
//            //                infoBean->setUnionName(tempStr);
//            //                json_free(tempStr);
//        }
//        else if (strcmp(node_name, "won") == 0){
//            
//            infoBean->isWin = json_as_bool(*j);
//        }
//        else if (strcmp(node_name, "beforeCurrentTime") == 0){
//            json_char* tempStr = json_as_string(*j);
//            infoBean->setTime(tempStr);
//            json_free(tempStr);
//        }
        else if (strcmp(node_name, "trophyIron") == 0) {
            int trophyIron = json_as_int(*j);
            infoBean->robberIron = trophyIron;
//            MyGameInfo::getInstance()->changeResource(ironTag,-trophyIron);
        }
        else if (strcmp(node_name, "trophyOil") == 0) {
            int trophyOil = json_as_int(*j);
            infoBean->robberOil = trophyOil;
//            MyGameInfo::getInstance()->changeResource(oilTag,-trophyOil);
        }else if (strcmp(node_name, "trophyPower") == 0) {
            infoBean->deltaPower = json_as_float(*j);
            //                CCLog("POWER:%d",infoBean->deltaPower);
        }
//        else if (strcmp(node_name, "note") == 0) {
//            json_char* tempStr = json_as_string(*j);
//            infoBean->setNote(tempStr);
//            json_free(tempStr);
//            //                CCLog("POWER:%d",infoBean->deltaPower);
//        }
//        else if(strcmp(node_name, "unitJSON") == 0) {
//            json_char* tempStr = json_as_string(*j);
//            CCString*  unCompressingData = CryptologyUtil::decode64(CCString::create(tempStr));
//            const char* str2 = DataCompressionUtil::unCompressData(unCompressingData)->getCString();
//            
//            JSONNODE* node1 = json_parse(str2);
//            if (node1 == NULL) {
//                //todo 这里不友好啊
//                j++;
//                continue;
//            }
//            JSONNODE_ITERATOR k = json_begin(node1);
//            
//            
//            
//            while (k != json_end(node1)){
//                
//                JSONNODE_ITERATOR l = json_begin(*k);
//                while (l != json_end(*k)) {
//                    
//                    // get the node name and value as a string
//                    json_char *node_name2 = json_name(*l);
//                    if (strcmp(node_name2, "frameName") == 0) {
//                        json_char* tempStr = json_as_string(*l);
//                        infoBean->frameNameArray->addObject(CCString::create(tempStr));
//                        json_free(tempStr);
//                    } else if(strcmp(node_name2, "count") == 0) {
//                        infoBean->unitCountArray->addObject(CCInteger::create(json_as_int(*l)));
//                    } else if(strcmp(node_name2, "level")==0) {
//                        infoBean->levelArray->addObject(CCInteger::create(json_as_int(*l)));
//                    } else if(strcmp(node_name2, "rarity")==0) {
//                        infoBean->rarityArray->addObject(CCInteger::create(json_as_int(*l)));
//                    }
//                    json_free(node_name2);
//                    ++l;
//                }
//                ++k;
//            }
//        }
        json_free(node_name);
        j++;
    }
    beans->addObject(infoBean);
    
    json_delete(node);
    return beans;
}

CCScene* MyJsonUtil::parseChiefSceneInfo(CCString* str) {
    //    CCLog(str);
    JSONNODE* node = json_parse(str->getCString());
    JSONNODE_ITERATOR i = json_begin(node);
    unsigned long long robDeltaTime = 0;
    int robMultipleTime = 0;
    while (i != json_end(node)){
        json_char *node_name = json_name(*i);
        if(strcmp(node_name, "robDeltaTime") == 0) {
            json_char* tempStr = json_as_string(*i);
//            MyGameInfo::getInstance()->setRobMultipleByTime(atoll(tempStr));
            robDeltaTime = atoll(tempStr);
            json_free(tempStr);
        } else if (strcmp(node_name, "robMultipleTime") == 0){
            robMultipleTime = json_as_int(*i);
        }
        json_free(node_name);
        i++;
    }
    json_delete(node);
    int level = MyUtil::getInstance()->getLevelByExperience(MyGameInfo::getInstance()->getExperience());
    int multipe = robDeltaTime/robMultipleTime;
    if (multipe > level) {
        multipe = level;
    }
    return Chthief::scene(multipe);
}

void  MyJsonUtil::parseResourceChange(CCString* str) {
    JSONNODE* node = json_parse(str->getCString());
    JSONNODE_ITERATOR i = json_begin(node);
    int resourceTag = -1;
    unsigned long long resourceCount = 0;
    while (i != json_end(node)){
        json_char *node_name = json_name(*i);
        if(strcmp(node_name, "resourceTag") == 0) {
            resourceTag = json_as_int(*i);
        } else if(strcmp(node_name, "newCount") == 0) {
            json_char* tempStr = json_as_string(*i);
            resourceCount  = (atoll(tempStr));
            json_free(tempStr);
        }
        json_free(node_name);
        i++;
    }
    json_delete(node);
    if (resourceTag == expTag) {
        MyGameInfo::getInstance()->setUpdateLevel(resourceCount);
    } else {
        MyGameInfo::getInstance()->changeResource(resourceTag,resourceCount);
    }
}

CCArray* MyJsonUtil::parseDefendList(CCString* str) {
    
    JSONNODE* node = json_parse(str->getCString());
    if (node == NULL) {
        return CCArray::create();
    }
    JSONNODE_ITERATOR ri = json_begin(node);
    JSONNODE_ITERATOR i =json_begin(*ri);
    MatchInfoBean* infoBean;
    CCArray* beans = CCArray::create();
    while (i != json_end(*ri)){
        JSONNODE_ITERATOR j = json_begin(*i);
        infoBean = MatchInfoBean::create();
        while (j != json_end(*i)) {
            json_char *node_name = json_name(*j);
            if (strcmp(node_name, "nickname") == 0) {
                json_char* tempStr = json_as_string(*j);
                infoBean->setAttackNickName(tempStr);
                json_free(tempStr);
            } else if (strcmp(node_name, "power") == 0) {
                infoBean->enemyPower = json_as_float(*j);
            }  else if(strcmp(node_name,"framenames") == 0) {
                JSONNODE_ITERATOR k = json_begin(*j);
                while (k != json_end(*j)){
                    json_char* tempStr = json_as_string(*k);
                    infoBean->frameNameArray->addObject(CCString::create(tempStr));
                    json_free(tempStr);
                    k++;
                }
            } else if(strcmp(node_name,"stars") == 0) {
                JSONNODE_ITERATOR k = json_begin(*j);
                while (k != json_end(*j)){
                    infoBean->rarityArray->addObject(CCInteger::create(json_as_int(*k)));
                    k++;
                }
            } else if(strcmp(node_name,"levels") == 0) {
                JSONNODE_ITERATOR k = json_begin(*j);
                while (k != json_end(*j)){
                    infoBean->levelArray->addObject(CCInteger::create(json_as_int(*k)));
                    k++;
                }
            }
            else if(strcmp(node_name,"counts") == 0) {
                JSONNODE_ITERATOR k = json_begin(*j);
                while (k != json_end(*j)){
                    infoBean->unitCountArray->addObject(CCInteger::create(json_as_int(*k)));
                    k++;
                }
            }
            json_free(node_name); 
            j++;
        }
        i++;
        beans->addObject(infoBean);
    }
    json_delete(node);
    return beans;
}

void MyJsonUtil::parseChatInfoBean(GXChatInfoBean* bean) {
    JSONNODE* node = json_parse(bean->base);
    if (node == NULL) {
        return ;
    }
    JSONNODE_ITERATOR i = json_begin(node);
    while (i != json_end(node)){
        json_char *node_name = json_name(*i);
        if (strcmp(node_name, "code") == 0) {
            bean->code = json_as_int(*i);
        } else if(strcmp(node_name, "host") == 0) {
            bean->host = json_as_string(*i);
            bean->msgType = PC_MSG_Route;
        } else if(strcmp(node_name, "port") == 0)  {
            bean->port = json_as_int(*i);
            bean->msgType = PC_MSG_Route;
        } else if(strcmp(node_name, "sys") == 0) {
            JSONNODE_ITERATOR j = json_begin(*i);
            while (j != json_end(*i)) {
                json_char *node_name2 = json_name(*j);
                if (strcmp(node_name2, "heartbeat") == 0) {
                    GXChatHandler::getInstance()->setHeartbeat(json_as_int(*j)-10);
                }
                json_free(node_name2);
                j++;
            }
        }
        else if(strcmp(node_name, "users") == 0) {
            GXChatHandler::getInstance()->initSucc = true;
            char* str = (char*)malloc(strlen("addUnion")*sizeof(char)+1);
            strcpy(str,"addUnion");
            bean->route_str = str;
        }
        json_free(node_name);
        i++;
    }
    json_delete(node);
    return;
}

GXMsg* MyJsonUtil::parseChat(const char* str) {
    JSONNODE* node = json_parse(str);
    if (node == NULL) {
        return NULL;
    }
    JSONNODE_ITERATOR i = json_begin(node);
    GXMsg* msg = GXMsg::create();
    while (i != json_end(node)){
        json_char *node_name = json_name(*i);
        if (strcmp(node_name, "from") == 0) {
            json_char* tempStr = json_as_string(*i);
            msg->name = tempStr;
            json_free(tempStr);
        } else if(strcmp(node_name, "msg") == 0) {
            json_char* tempStr = json_as_string(*i);
            msg->msg = tempStr;
            json_free(tempStr);
        } else if(strcmp(node_name,"target") == 0) {
            json_char* tempStr = json_as_string(*i);
            if (strcmp(tempStr,"*") != 0) {
                msg->mode = atoi(tempStr);
            }
            json_free(tempStr);
//            
//            int unionId = json_as_int(*
//            if (unionId > -1) {
//                msg->mode = unionMode;
//            }
        }
        json_free(node_name);
        i++;
    }
    json_delete(node);
    return msg;
}

BuildingBean* MyJsonUtil::parseBuildBean(CCString* str) {
    JSONNODE* node = json_parse(str->getCString());
//    JSONNODE_ITERATOR i =json_begin(node);
    return parseNode(node);

}