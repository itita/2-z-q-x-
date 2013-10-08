#include "TalkNode.h"
#include "DiaLayer.h"
using namespace cocos2d;

#define baseIconTag 9000
#define tiphandTag 8999
#define tipCircleTag 8998

#if   (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#define utfChinese -32
#endif
#if   (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#define utfChinese 224
#endif

TalkNode* TalkNode::create(TalkNodeCreator* creator) {
    TalkNode *node= new TalkNode();
    node->m_pScheduler = CCDirector::sharedDirector()->getScheduler();
    node->m_pScheduler->retain();
    node->init(creator);
    node->autorelease();
    return node;
}

CCScheduler* TalkNode::getScheduler()
{
    return m_pScheduler;
}

void TalkNode::setScheduler(CCScheduler* scheduler)
{
    if( scheduler != m_pScheduler ) {
        //        this->unscheduleAllSelectors();
        CC_SAFE_RETAIN(scheduler);
        CC_SAFE_RELEASE(m_pScheduler);
        m_pScheduler = scheduler;
    }
}


void TalkNode::init(TalkNodeCreator* creator)
{
//    TiXmlElement *element =node->ToElement();

    iconArray = CCArray::create();
    iconArray->retain();
    CCObject* obj;
    CCARRAY_FOREACH(creator->iconCreatorArray, obj) {
        iconArray->addObject(((GXSpriteCreator*)obj)->getSprite());
    }
    if (creator->getNameCreator() != NULL) {
        setName(creator->getNameCreator()->getLabel());
    }
    if (creator->getContentCreator() != NULL) {
        setContent(creator->getContentCreator()->getLabel());
    }
    
    contentLength = strlen(content->getString());
    
    content->setString("");
    this->typeWriterEffectRate = creator->_typeWriterEffectRate;
//    int i = 0;
//    while(i < length)
//    {
//        char ch = getContent()[i];
//        //÷ÿµ„‘⁄’‚¿Ô
//        //÷–Œƒ‘⁄ASCII¬Î÷– «-127~0
//        if (ch > -127 && ch< 0)
//        {
//            //’‚¿ÔŒ™ ≤√¥+£Ω3ƒÿ
//            //“ÚŒ™“ª∏ˆ÷–Œƒ’º3∏ˆ◊÷Ω⁄
//            i+=3;
//        }
//        else
//        {
//            i++;
//        }
//        contentLength++;
//    }
}
//ªÒ»°ƒ⁄»›µƒ◊‹≥§∂»
//int TalkNode::getContentLength()
//{
//    return contentLength;
//}

//∑µªÿÀ˘–Ë≥§∂»µƒ◊÷∑˚¥Æ
std::string TalkNode::getNextStr()
{
    if (wordCount >= contentLength)
    {
        return getContent();
    }
   
    char ch = getContent()[wordCount];
    //’‚¿Ô…œ√ÊÀµπ˝¡À
    if (((ch & utfChinese) == utfChinese) && ((ch | utfChinese) == ch))
    {
        wordCount+=3;
    }
    else
    {
        wordCount++;
    }
    
    
    //Ωÿ»°strng
//    std::string str = content->m_string.substr(0, i);
  
    return getContent().substr(0, wordCount);
}

void TalkNode::onEnter(CCLayer* layer) {
    //    TalkNode* node = (TalkNode*)talkNodeArray->objectAtIndex(talkIndex);
    //	CCSpriteFrame* frame =CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(node->getIcon());
    //	CCSpriteFrame* frame1 =CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(node->getIcon1());
    CCObject* obj;
    int i=0;
    CCARRAY_FOREACH(iconArray,obj) {
        CCSprite* sprite = (CCSprite*)obj;
        sprite->setTag(baseIconTag+i);
        layer->addChild(sprite);
        i++;
    }
    if (name != NULL) {
        layer->addChild(name);
    }
    if (content != NULL) {
        layer->addChild(content);
    }
    
//    frame->setTag(baseIconTag);
//    frame1->setTag(baseIconTag+1);
    
	
    
    //	_pName->setString(node->getName());
    //	_pName->setPosition(_nPoint[i]);
    //	_pHero->setDisplayFrame(frame1);
    //	_pHero->setPosition(_hPoint[i]);
    //	_pPlayer->setDisplayFrame(frame);
    //	_pPlayer->setPosition(_pPoint[i]);
    
    m_pScheduler->scheduleSelector(schedule_selector(TalkNode::typeWriterEffect), this, typeWriterEffectRate, kCCRepeatForever, 0, false);
}

void TalkNode::onExit(CCLayer* layer) {
//    layer->removeChildByTag(baseIconTag,true);
//    layer->removeChildByTag(baseIconTag+1,true);
    
    m_pScheduler->unscheduleSelector(schedule_selector(TalkNode::typeWriterEffect), this);
    
    for (int i=0; i<iconArray->count(); i++) {
        layer->removeChildByTag(baseIconTag+i,true);
    }
    if (name != NULL) {
        name->removeFromParentAndCleanup(true);
    }
    if (content != NULL) {
        content->removeFromParentAndCleanup(true);
    }
    
    layer->removeChildByTag(tiphandTag,true);
    layer->removeChildByTag(tipCircleTag,true);
}

void TalkNode::onTouch(CCLayer* layer,bool isBegin,CCTouch *pTouch, CCEvent *pEvent) {
    if (!isBegin) {
        if (wordCount < this->contentLength) {
            this->content->setString(getContent().c_str());
            m_pScheduler->unscheduleSelector(schedule_selector(TalkNode::typeWriterEffect), this);
            wordCount = this->contentLength;
            addNextTip(layer);
        } else {
            ((DiaLayer*)layer)->toNextNode();
        }
    }
}

void TalkNode::typeWriterEffect()
{
    //    TalkNode* node = (TalkNode*)talkList[talkIndex];
    //    TalkNode* node = (TalkNode*)talkNodeArray->objectAtIndex(talkIndex);
    if (wordCount >= this->contentLength)
    {
        m_pScheduler->unscheduleSelector(schedule_selector(TalkNode::typeWriterEffect), this);
        addNextTip(this->content->getParent());
        return;
    }
	this->content->setString(getNextStr().c_str());
}

void TalkNode::addNextTip(CCNode* parent) {
    CCSprite* tiphand = CCSprite::createWithSpriteFrameName("nextTipHand.png");
    tiphand->setPosition(ccp(winSize.width-20,50));
    tiphand->setTag(tiphandTag);
    tiphand->setScale(0.8);
    tiphand->runAction(CCRepeatForever::create(static_cast<CCSequence*>(CCSequence::create(CCEaseIn::create( CCMoveBy::create(0.5, ccp(0,-10)), 2),CCEaseOut::create(CCMoveBy::create(0.5, ccp(0,10)),2),NULL))));
    tiphand->setColor(ccc3(200,200,200));
    
    CCSprite* tipCircle = CCSprite::createWithSpriteFrameName("nextTipCircle.png");
    tipCircle->setPosition(ccp(winSize.width-37,20));
    tipCircle->setTag(tipCircleTag);
    tipCircle->setScale(0.8);
    tipCircle->setColor(ccc3(200,200,200));
//    tipCircle->runAction(CCRepeatForever::create(static_cast<CCSequence*>(CCSequence::create(CCDelayTime::create(0),CCFadeOut::create(0.5),CCFadeIn::create(0.5),CCDelayTime::create(0),NULL))));
    tipCircle->runAction(CCRepeatForever::create(static_cast<CCSequence*>(CCSequence::create(CCDelayTime::create(0.5), CCSpawn::create(CCScaleTo::create(0.5,1.1),CCFadeOut::create(0.5),NULL),CCScaleTo::create(0,0.8),CCFadeIn::create(0),NULL))));
    
    
    parent->addChild(tipCircle);
    parent->addChild(tiphand);
}

TalkNodeCreator* TalkNodeCreator::create() {
    TalkNodeCreator* bean = new TalkNodeCreator();
    bean->iconCreatorArray = CCArray::create();
    bean->iconCreatorArray->retain();
    bean->autorelease();
    return bean;
}

//TalkNode* TalkNodeCreator::createTalkNode() {
//    return TalkNode::create(this);
//}
