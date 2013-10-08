#pragma once

#include "cocos2d.h"
#include "GXSpriteCreator.h"
#include "GXLabelTTFCreator.h"
#include "GXLabelBMFontCreator.h"

class TalkNodeCreator :public CCObject {
    
public:
    
    
    TalkNodeCreator():
    iconCreatorArray(NULL),
    nameCreator(NULL),
    contentCreator(NULL),
    _typeWriterEffectRate(0.05){
    
    }
    ~TalkNodeCreator() {
        CC_SAFE_RELEASE_NULL(iconCreatorArray);
        CC_SAFE_RELEASE_NULL(nameCreator);
        CC_SAFE_RELEASE_NULL(contentCreator);
    }
    
    static TalkNodeCreator* create();
    float _typeWriterEffectRate;
    CCArray* iconCreatorArray;
//    GXLabelTTFCreator* nameCreator;
//    GXLabelTTFCreator* contentCreator;
    CC_SYNTHESIZE_RETAIN(GXLabelTTFCreator*, nameCreator, NameCreator);
    CC_SYNTHESIZE_RETAIN(GXLabelBMFontCreator*, contentCreator, ContentCreator);
};

class TalkNode:public cocos2d::CCObject
{
public:
    static TalkNode* create(TalkNodeCreator* creator);
    
	TalkNode(void):
    iconArray(NULL),
    name(NULL),
    content(NULL),
    wordCount(0),
    contentLength(0),
    typeWriterEffectRate(0.05)
    {};
	~TalkNode(void) {
        CC_SAFE_RELEASE_NULL(iconArray);
        CC_SAFE_RELEASE_NULL(name);
        CC_SAFE_RELEASE_NULL(content);
    };
	CCArray* iconArray;
	CC_SYNTHESIZE_RETAIN(CCLabelTTF*, name, Name);
	
    void init(TalkNodeCreator* creator);
    //    const char* getIcon1() {
    //        return icon1->getCString();
    //    };
    //    const char* getIcon() {
    //        return icon->getCString();
    //    };
    const char* getName(){
        return name->getString();
    };
    
    const std::string& getContent(){
        return contentStr;
    };
    
    void setContent(CCLabelBMFont* label) {
        CC_SAFE_RELEASE_NULL(this->content);
        this->content = label;
        if (label != NULL) {
            contentStr = label->getString();
        } else {
            contentStr = "";
        }
        CC_SAFE_RETAIN(this->content);
    }

    int contentLength;
    //    int getContentLength();
    void onEnter(CCLayer* layer);
    void onExit(CCLayer* layer);
    void onTouch(CCLayer* layer,bool isBegin,CCTouch *pTouch, CCEvent *pEvent);
    CC_PROPERTY(CCScheduler*, m_pScheduler, Scheduler);
    void typeWriterEffect();
    float typeWriterEffectRate;
private:
    int wordCount;
    CCLabelBMFont* content;
    std::string contentStr;
    std::string getNextStr();
    void addNextTip(CCNode* parent);
    
};