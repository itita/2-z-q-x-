#include "DiaLayer.h"
#include <string>
#include "HelloWorldScene.h" 
#include "TalkNode.h"
#include "GXRemoveFromParentsAction.h"
#include "DefineSet.h"
#include "GXUtil.h"
#include "SimpleAudioEngine.h"
#include "DialogCompleteMessage.h"
#include "GarbageResourceCollection.h"

#define baseIconTag 9000


DiaLayer* DiaLayer::create(DiaLayerInfoBean* infobean) {
    DiaLayer* pRet = new DiaLayer();
    pRet->loadResource(infobean->getPvrName());
    pRet->init(infobean);
    pRet->autorelease();
    return pRet;
}

bool DiaLayer::init(DiaLayerInfoBean* infobean)
{
    if ( CCLayerColor::initWithColor( ccc4(0, 0, 0, 0) ) )
    {
        //			talkIndex=0;
//        CCLog("aaaaaaaaaaaaaaaa");
        
//        CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile();
//        CCSprite* dia =CCSprite::createWithSpriteFrameName("666.png");
        
//        dia->setPosition(ccpinitSpriteCreator(winSize.width/2,winSize.height/8));
//        this->addChild(dia,-1);
        //this->initdialog(dia);
        this->priority = infobean->creatorPriority;
        
        CCObject* obj;
        CCARRAY_FOREACH(infobean->initSpriteCreator,obj) {
            this->addChild(((GXSpriteCreator*)obj)->getSprite());
        }
        this->setNextNodeSfx(infobean->getCreateNextNodeSfx());
//        this->setOpacity(0);
        //				this->readXml("plist.xml");
        //           this->talkNodeArray = CCArray::create();
        //           this->talkNodeArray->retain();
        //           CCObject* obj;
        //           CCARRAY_FOREACH(infobean->talkCreatorNodes,obj) {
        //               this->talkNodeArray->addObject(TalkNode::create((TalkNodeCreator*)obj));
        //           }
        this->talkNodeArray = infobean->talkCreatorNodes;
        this->talkNodeArray->retain();
        setCurrentNode(0);
        
        
        //this->diaIn();
        return true;
        
    }
    
    else
    {
        return false;
    }

}
//void DiaLayer::initdialog()
//{

//    CCLayer *TalkLayer = CCLayer::create();
//    TalkNode* node = (TalkNode*)talkList[talkIndex];
    
//    TalkNode* node = (TalkNode*)talkNodeArray->objectAtIndex(talkIndex);
//    
//    this->_pName = CCLabelTTF::create(node->getName(),"Artial", 56,CCSize(200,80),kCCTextAlignmentLeft);
//    _pName->retain();
//    _pName->setColor( ccc3(255,0 , 0) );
//    _pName->setPosition(ccp(winSize.width/4+20,winSize.height/6));
//    this->addChild(_pName);
//    
//    this->_pPlayer = icon->getSprite();
//    _pPlayer->retain();
//    _pPlayer->setPosition(ccp(winSize.width/9, winSize.height/5));
//    this->addChild(_pPlayer);
//    
//    this->_pSpeak = CCLabelTTF::create(node->getContent(),"Artial", 30,CCSize(400,60),kCCTextAlignmentLeft);
//    _pSpeak->retain();
//    _pSpeak->setColor( ccc3(0, 0, 0) );
//    _pSpeak->setPosition(ccp(winSize.width/2,winSize.height/9));
//    this->addChild(_pSpeak);
//    
//    this->_pHero= icon1->getSprite();
//    _pHero->retain();
//    _pHero->setPosition(ccp(winSize.width/3,2*winSize.height/3));
//    this->addChild(_pHero);
    
//}
//void DiaLayer::dialog()
//{	

//	TalkNode* node = (TalkNode*)talkList[talkIndex];
//    TalkNode* node = (TalkNode*)talkNodeArray->objectAtIndex(talkIndex);
//	CCSpriteFrame* frame =CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(node->getIcon());
//	CCSpriteFrame* frame1 =CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(node->getIcon1());
//
//	CCPoint _nPoint[4]={ccp(winSize.width/4+20,winSize.height/6),ccp(3*winSize.width/4+40,winSize.height/6),ccp(winSize.width/4+20,winSize.height/6),ccp(3*winSize.width/4+40,winSize.height/6)};
//	CCPoint _pPoint[4]={ccp(winSize.width/9, winSize.height/5),ccp(8*winSize.width/9, winSize.height/5),ccp(winSize.width/9, winSize.height/5),ccp(8*winSize.width/9, winSize.height/5)};
//	CCPoint _sPoint[4]={ccp(winSize.width/4+40,20),ccp(3*winSize.width/4+40,20),ccp(winSize.width/4+40,20),ccp(3*winSize.width/4+40,20)};
//	CCPoint _hPoint[4]={ccp(winSize.width/3,2*winSize.height/3),ccp(winSize.width/2,2*winSize.height/3),ccp(winSize.width/3,2*winSize.height/3),ccp(winSize.width/2,2*winSize.height/3)};
//	
//	_pName->setString(node->getName());
//	_pName->setPosition(_nPoint[i]);
//	_pHero->setDisplayFrame(frame1);
//	_pHero->setPosition(_hPoint[i]);
//	_pPlayer->setDisplayFrame(frame);
//	_pPlayer->setPosition(_pPoint[i]);
//
//	wordCount =0;
//	this->schedule(schedule_selector(DiaLayer::logic),0.2);

//}

void DiaLayer::onEnter()
{
//	CCLayerColor::onEnter();
    CCNode::onEnter();
	currentNode->onEnter(this);
	this->diaIn();
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this,
                                     priority,
                                     true);
}

void DiaLayer::onExit()
{
	CCLayerColor::onExit();
//	this->releaseResource();
    CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
    if (currentNode != NULL) {
        currentNode->onExit(this);
    }
}

void DiaLayer::diaOut()
{	
	
//	CCActionInterval*  action1 = CCFadeOut::create(2.0f);
//	CCActionInterval*  action2 = CCFadeOut::create(2.0f);
//	CCActionInterval*  action3 = CCFadeOut::create(2.0f);
//	CCActionInterval*  action4 = CCFadeOut::create(2.0f);
//	CCActionInterval*  action5 = CCFadeOut::create(2.0f);
	
//	this->_pName->runAction(action2);
//	this->_pHero->runAction(action3);
//	this->_pSpeak->runAction(action4);
//	this->_pPlayer->runAction(action5);
//	this->dia->runAction(action1);
	this->runAction(CCSequence::create(CCFadeOut::create(2.0f),GXRemoveFromParentsAction::create(),NULL));
}

void DiaLayer::diaIn()
{
////	CCActionInterval*  action = CCFadeIn::create(2.0f);
//	CCActionInterval*  action1 = CCFadeIn::create(2.0f);
//	CCActionInterval*  action2 = CCFadeIn::create(2.0f);
//	CCActionInterval*  action3 = CCFadeIn::create(2.0f);
//	CCActionInterval*  action4 = CCFadeIn::create(2.0f);
//	CCActionInterval*  action5 = CCFadeIn::create(2.0f);
////	this->dia->runAction(action1);	
//	this->_pName->runAction(action2);
//	this->_pHero->runAction(action3);
//	this->_pSpeak->runAction(action4);
//	this->_pPlayer->runAction(action5);
//    this->runAction(CCFadeIn::create(2.0f));
}

void DiaLayer::setOpacity(GLubyte opacity){
    CCObject* obj;
    CCARRAY_FOREACH(this->getChildren(),obj) {
        CCRGBAProtocol* color = dynamic_cast<CCRGBAProtocol*>(obj);
        if(color != NULL) {
            color->setOpacity(opacity);
        }
    }
}

void DiaLayer::setCurrentNode(int index) {
    CC_SAFE_RELEASE_NULL(currentNode);
    if (index < talkNodeArray->count() && index >=0) {
        
        currentNode = TalkNode::create(((TalkNodeCreator*)talkNodeArray->objectAtIndex(index)));
        CC_SAFE_RETAIN(currentNode);
    } else {
        currentNode = NULL;
    }
}

bool DiaLayer::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)  
{
    if (isEnable) {
        //    TalkNode* node = (TalkNode*)talkList[talkIndex];
        if (currentNode!=NULL) {
            currentNode->onTouch(this,true,pTouch,pEvent);
        }
        //    if (wordCount < node->contentLength)
        //    {
        //        wordCount = node->contentLength;
        //    }
        
        return true;
    }
    return false;
}  

void DiaLayer::ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    if (currentNode!=NULL) {
        currentNode->onTouch(this,false,pTouch,pEvent);
    } 
    
//			if(i<3)
//			{
//				i++;
//				talkIndex++;
//				dialog();
//				
//			}
//			else
//			{	
//				diaOut();
//				this->setTouchEnabled(false);
//			}
}

void DiaLayer::toNextNode() {
    this->scheduleOnce(schedule_selector(DiaLayer::nextNode),0);
}

void DiaLayer::nextNode() {
    talkIndex++;
    currentNode->onExit(this);
    setCurrentNode(talkIndex);
    if (getNextNodeSfx() != NULL) {
        CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(getNextNodeSfx()->getCString());
    }
    if (currentNode != NULL) {
        currentNode->onEnter(this);
    } else {
//        diaOut();
        this->removeFromParentAndCleanup(true);
    }
     DialogCompleteMessage::create(talkNodeArray->count(),talkIndex,this->getTag())->sendMsg();
}

void DiaLayer::loadResource(CCString* filename) {
    char name1[20] = {0};
    sprintf(name1,"%s.plist",filename->getCString());
    char name2[20] = {0};
    sprintf(name2,"%s.png",filename->getCString());
    GXUtil::loadResourceUtilSucc(name1,name2);
//    setCachePvrName(filename);
    GarbageResourceCollection::getInstance()->addGarbage(name1,CCString::create(name2));
}

void DiaLayer::releaseResource() {
//    char name1[20] = {0};
//    sprintf(name1,"%s.plist",getCachePvrName()->getCString());
//    CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile(name1);
//    sprintf(name1,"%s.png",getCachePvrName()->getCString());
//    CCTextureCache::sharedTextureCache()->removeTextureForKey(name1);
}

//void DiaLayer::setXMLName(char *filename)
//{
//	this->XMLName = filename;
//	
//}

DiaLayerInfoBean* DiaLayerInfoBean::create() {
    DiaLayerInfoBean* infoBean = new DiaLayerInfoBean();
    infoBean->autorelease();
    infoBean->talkCreatorNodes = CCArray::create();
    infoBean->talkCreatorNodes->retain();
    infoBean->initSpriteCreator = CCArray::create();
    infoBean->initSpriteCreator->retain();
    return infoBean;
}