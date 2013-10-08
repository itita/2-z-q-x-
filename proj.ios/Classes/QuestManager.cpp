//
//  QuestManager.cpp
//  ww3
//
//  Created by xiao tang on 12-12-15.
//
//

#include "QuestManager.h"
#include "MyMessageManage.h"
#include "MyJsonUtil.h"

QuestManager* QuestManager::questManagerInstance = NULL;

QuestManager* QuestManager::getInstance(){
    if (!questManagerInstance) {
        //CREATE
        QuestManager* trigger = QuestManager::create();
        MyMessageManage::getInstance()->registerTrigger(trigger);
        questManagerInstance = trigger;
    }
    return questManagerInstance;
}

QuestManager::~QuestManager() {
    CC_SAFE_RELEASE_NULL(questList);
}

QuestManager* QuestManager::create() {
    QuestManager* manager = new QuestManager();
    manager->autorelease();
    manager->questList = CCArray::create();
    manager->questList->retain();
    return manager;
}

bool QuestManager::addQuest(MyBaseQuest *quest) {
    CCObject* obj;
    CCARRAY_FOREACH(questList,obj) {
        MyBaseQuest* oriQuest = (MyBaseQuest*)obj;
        if (oriQuest->questId == quest->questId) {
            oriQuest->deadLine = quest->deadLine;
            return false;
        }
    }
    questList->addObject(quest);
    return true;
}

void QuestManager::removeQuest(MyBaseQuest *quest) {
    questList->removeObject(quest);
}

bool QuestManager::excuteMsg(MyBaseMessage* msg) {
    CCObject* obj =NULL;
    MyBaseQuest* quest = NULL;
    if (msg->tag == questMessageTag) {
        GXMessage* uMsg = (GXMessage*)msg;
        if (uMsg->getDetail() != NULL) {
            char str[5] = {0};
            sprintf(str,"%d",questList->count());
            GXString* string = GXString::create(str);
            uMsg->setMsg(string);
            string->release();
            CCArray* newQuests = MyJsonUtil::parseQuest(uMsg->getDetail());
            CCObject* obj;
            CCARRAY_FOREACH(newQuests,obj) {
                MyBaseQuest* newQuest = (MyBaseQuest*)obj;
                addQuest(newQuest);
            }
            uMsg->setDetail(NULL);
        }
        return false;
    }
    CCARRAY_FOREACH(questList, obj) {
        quest = (MyBaseQuest*)obj;
        if (quest->getCompleteStatus() == questUnfinishedTag && quest->excuteMsg(msg)) {
            break;
        }
    }
    return false;
}

bool QuestManager::onRegist() {
    return false;
}

bool QuestManager::onUnRegist() {
    return false;
}

void QuestManager::clear() {
    questList->removeAllObjects();
}