#pragma once
#include "cocos2d.h"
#include "talkNode.h"

using namespace cocos2d;

class DiaLayerInfoBean : public CCObject {
    
public:
    DiaLayerInfoBean():
    talkCreatorNodes(NULL),
    initSpriteCreator(NULL),
    pvrName(NULL),
    _nextNodeSfx(NULL),
    creatorPriority(-500){
    }
    ~DiaLayerInfoBean() {
        CC_SAFE_RELEASE_NULL(talkCreatorNodes);
        CC_SAFE_RELEASE_NULL(pvrName);
        CC_SAFE_RELEASE_NULL(initSpriteCreator);
        CC_SAFE_RELEASE_NULL(_nextNodeSfx);
    }
    static DiaLayerInfoBean* create();
    
    CCArray* talkCreatorNodes;
    
    CC_SYNTHESIZE_RETAIN(CCString* ,pvrName,PvrName);
    CC_SYNTHESIZE_RETAIN(CCString* ,_nextNodeSfx,CreateNextNodeSfx);
    
    CCArray* initSpriteCreator;
    
    int creatorPriority;
};

class DiaLayer :public cocos2d::CCLayerColor
{
public:
	bool init(DiaLayerInfoBean* infobean);
	void diaIn();
	void diaOut();
	void onEnter();
	void onExit();
//	CC_SYNTHESIZE_RETAIN(cocos2d::CCSprite* ,dia,Dia);
//	CC_SYNTHESIZE_RETAIN(cocos2d::CCSprite*, _pPlayer, pPlayer);
//	CC_SYNTHESIZE_RETAIN(cocos2d::CCSprite*, _pHero, pHero);
//	CC_SYNTHESIZE_RETAIN(cocos2d::CCLabelTTF*, _pName, pName);
//	CC_SYNTHESIZE_RETAIN(cocos2d::CCLabelTTF*, _pSpeak, pSpeak);
//	char * XMLName;
//	void setXMLName(char * filename);
	DiaLayer():
    talkNodeArray(NULL),
    talkIndex(0),
    priority(-500),
//    cachePvrName(NULL),
    currentNode(NULL),
    nextNodeSfx(NULL),
    isEnable(true){
//        _pName=NULL;
//        _pSpeak=NULL;
//        _pPlayer=NULL;
//        _pHero=NULL;
//        XMLName=NULL;
//        dia=NULL;
    }
	~DiaLayer() {
//        if (currentNode != NULL) {
//            currentNode->getScheduler()->unscheduleSelector(schedule_selector(TalkNode::typeWriterEffect), currentNode);
//            currentNode->release();
//            currentNode = NULL;
//        }
        CC_SAFE_RELEASE_NULL(currentNode);
//        CC_SAFE_RELEASE_NULL(cachePvrName);
        CC_SAFE_RELEASE_NULL(talkNodeArray);
        CC_SAFE_RELEASE_NULL(nextNodeSfx);
    }
	void ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
	static DiaLayer* create(DiaLayerInfoBean* infobean);

//	void readXml(char *filename);
	
	
	bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    virtual void setOpacity(GLubyte opacity);
    void toNextNode();
    void loadResource(CCString* filename);
    void releaseResource();
    bool isEnable;
private:
    CCArray* talkNodeArray;
    TalkNode* currentNode;
    void setCurrentNode(int index);
    void nextNode();
    int priority;
    int talkIndex;
//    CC_SYNTHESIZE_RETAIN(CCString* ,cachePvrName,CachePvrName);
    CC_SYNTHESIZE_RETAIN(CCString* ,nextNodeSfx,NextNodeSfx);
//    CC_SYNTHESIZE_RETAIN(TalkNode* , currentNode,CurrentNode);
};
