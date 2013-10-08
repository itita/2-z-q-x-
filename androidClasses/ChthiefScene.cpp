#include "ChthiefScene.h"
#include "MyGameInfo.h"
#include "MyHttpConnection.h"
#include "MyUtil.h"
#include "PulsarNative.h"
#include "TransitonScene.h"
#include "DefineSet.h"

using namespace cocos2d;

CCScene* Chthief::scene(int dengji)
{
    ChthiefScene* scene = NULL;
    // 'scene' is an autorelease object
    
    scene = ChthiefScene::create();
    
    // 'layer' is an autorelease object
    Chthief *layer = Chthief::create();
    layer->dengji->setValue(dengji);
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool Chthief::init()
{
    loadResource();
    bool bRet = false;
    do
    {
        CC_BREAK_IF(! CCLayer::init());
		//初始化金币数组
        _jinbis = CCArray::create();
        _jinbis->retain();
        
		CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect("sfx_bugeiDropMoney.mp3");
		CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect("sfx_bugeiCritical.mp3");
		CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect("sfx_bugeiLaugh.mp3");
		CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic("sfx_bugeiElf.mp3");
		CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("sfx_bugeiElf.mp3", true);
        
        
		this->setTouchEnabled(true);
        
		buffer_lift = new char[128];
        
        // 1. Add a menu item with "X" image, which is clicked to quit the program.
		size = CCDirector::sharedDirector()->getWinSize();
		
        // Create a "close" menu item with close icon, it's an auto release object.
        
        
		CCSprite* pSprite = CCSprite::createWithSpriteFrameName("resourseBar.png");
		pSprite->setPosition(ccp(301, size.height-14.5));
        pSprite->setScale(1.25);
		// Add the sprite to Chthief layer as a child layer.
		this->addChild(pSprite, 1);
		
        //		cache=CCSpriteFrameCache::sharedSpriteFrameCache();
        //		cache->retain();
        //		cache->release();
        //		cache->addSpriteFramesWithFile("bugei.plist");
        
		CCSprite *pSpriteFrame = CCSprite::createWithSpriteFrameName("bubeiBack.png");
        
		pSpriteFrame->setPosition(ccp(size.width/2,size.height/2));//设置sprite位置
		this->addChild(pSpriteFrame,0,899);
		pSpriteFrame->setScaleX(winSize.width/pSpriteFrame->getContentSize().width);
        pSpriteFrame->setScaleY(winSize.height/pSpriteFrame->getContentSize().height);
        
		oilSprite = MyGameInfo::getInstance()->getOilAtlas();
		oilSprite->setPosition(ccp(27,6));
        oilSprite->setScale(0.5);
		pSprite->addChild(oilSprite, 1);
        
		gangSprite = MyGameInfo::getInstance()->getIronAtlas();
		gangSprite->setPosition(ccp(130,6));
        gangSprite->setScale(0.5);
		pSprite->addChild(gangSprite, 1);
        
		rongSprite = MyGameInfo::getInstance()->getGloryAtlas();
		rongSprite->setPosition(ccp(235,6));
        rongSprite->setScale(0.5);
		pSprite->addChild(rongSprite, 1);
        
        
        //		jingSprite = CCLabelAtlas::create("0", "criticalNumber.png", 15,23, '.');
        //		CC_BREAK_IF(! jingSprite);
        //		jingSprite->setPosition(ccp(480,size.height-28));
        //		this->addChild(jingSprite, 1);
		
        
		Chthief::addstartview();
		//qianSprite = CCSprite::create("qiandai.png");
		//CC_BREAK_IF(! qianSprite);
		//qianSprite->setPosition(ccp(60,60));
		//// Add the sprite to Chthief layer as a child layer.
		//this->addChild(qianSprite, 800);
		
        
        batchNode = CCSpriteBatchNode::create("bugei.pvr.ccz");
        this->addChild(batchNode);
		
        bRet = true;
    } while (0);
    
    return bRet;
}



void Chthief::menuStartGame(CCObject* pSender)
{
    
	this->removeChildByTag(901,true);
	//this->removeChildByTag(898,true);
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sfx_bugeiLaugh.mp3");
    timevalue=59;
	sprintf(buffer_lift,"%d",timevalue);
	liftlostLabelshow = CCLabelAtlas::create(buffer_lift, "number.png", 24, 30, '.');
    liftlostLabelshow->setScale(3);
//    liftlostLabelshow->setContentSize(CCSizeMake(0,0));
    liftlostLabelshow->setAnchorPoint(ccp(0.5,0.5));
    liftlostLabelshow->setPosition(ccp(size.width/2,size.height-100));
    
    this->addChild(liftlostLabelshow, 90);
	
	// Place the sprite on the center of the screen
	paddle = Paddle::create();
	paddle->setPosition(ccp(size.width/2, size.height/2) );
	batchNode->addChild(paddle);
    
	this->schedule( schedule_selector(Chthief::updateGame),4.0f);
	this->schedule( schedule_selector(Chthief::lostdao));
	//	this->schedule( schedule_selector(Chthief::movejibi));
	this->schedule( schedule_selector(Chthief::timelose),1.0f);
	Chthief::updateGame(3.5f);
	
    
}

void Chthief::updateGame(float aa){
    
    if(timevalue>4){
        xx=rand()%(int)(size.width-250)+125;
        yy=rand()%(int)(size.height-300)+100;
        
        CCActionInterval* action_to = CCEaseInOut::create(CCMoveTo::create(aa, CCPointMake(xx,yy)),1.0f);
        
        paddle->runAction(action_to);
        
    }
    
}


void Chthief::lostdao(float aa){
    
    
	if(timevalue>=0){
		CCFlipX *flip;
		if(timevalue<=4&&timevalue>=2){
            
			flip= CCFlipX::create(true);
			paddle->runAction(flip);
			if (timevalue==4)
			{
                paddle->stopAllActions();
				CCActionInterval* action_to = CCMoveBy::create(1.0, CCPointMake(winSize.width-paddle->getPositionX()+100,0));
				paddle->runAction(action_to);
			}
            
		}
        
        
        //		sprintf(buffer_lift,"%d",oilvalue1*jingyouvalue+oilvalue2*yingyouvalue+oilvalue3*tongyouvalue);
        //		oilSprite->setString(buffer_lift);
        //		sprintf(buffer_lift,"%d",gangvalue1*jinggangvalue+gangvalue2*yinggangvalue+gangvalue3*tonggangvalue);
        //		gangSprite->setString(buffer_lift);
        //		sprintf(buffer_lift,"%d",rongvalue1*jingrongvalue+rongvalue2*yingrongvalue+rongvalue3*tongrongvalue);
        //		rongSprite->setString(buffer_lift);
		
		if(xx>=paddle->getPositionX()&&timevalue>4){
			flip= CCFlipX::create(true);
			paddle->runAction(flip);
		}else{
			if (timevalue>4)
			{
				flip = CCFlipX::create(false);
				paddle->runAction(flip);
			}
			
		}
		
		batchNode->reorderChild(paddle, (int)(size.height-paddle->getPositionY())+40);
		paddle->setScale((size.height-paddle->getPositionY()/2)/size.height);
		for(int i=0;i<_jinbis->count();i++){
			Jinbi* myjinbi=(Jinbi*)_jinbis->objectAtIndex(i);
			myjinbi->setScale((size.height-myjinbi->getPositionY()/2)/size.height);
		}
        
        if (paddle->istouch && paddle->step <= 0)
        {
            paddle->step = 5;
            speakvalue=0;
            CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sfx_bugeiCritical.mp3");
            
            int ti=rand()%2+1;
            for (int i=0;i<ti;i++)
            {
                int ts=rand()%300-150;
                paddle->istouch=false;
                int mytype=(int)rand()%allrand+1;
                Jinbi* jinbi = Jinbi::create(mytype);
                jinbi->setPosition(ccp(paddle->getPositionX(),paddle->getPositionY()));
                batchNode->addChild(jinbi,(int)(size.height-jinbi->getPositionY()));
                CCActionInterval*  actionTo = CCJumpBy::create(1.2f, CCPointMake(ts,0), 60, 1);
                jinbi->runAction(actionTo);
                _jinbis->addObject(jinbi);
            }
            
            //CCFlipX *flip;
            //if(xx>=paddle->getPositionX()){
            //	flip= CCFlipX::create(true);
            //}else{
            //	flip = CCFlipX::create(false);
            //}
            //paddle->runAction(flip);
        }
        paddle->step = paddle->step - 1;
        
        for(int i=0;i<_jinbis->count();i++){
            Jinbi* myjinbi=(Jinbi*)_jinbis->objectAtIndex(i);
            CCActionInterval* action_to ;
            if (myjinbi->istouch)
            {
                //					if(myjinbi->mytype==jingbi){
                //						action_to= CCMoveTo::create(0.9f, CCPointMake(jingSprite->getPositionX(),jingSprite->getPositionY()));
                //
                //					}
                //					if(myjinbi->mytype>jingbi&&myjinbi->mytype<=yingbi){
                //						action_to= CCMoveTo::create(0.9f, CCPointMake(jingSprite->getPositionX(),jingSprite->getPositionY()));
                //					}
                //
                //					if(myjinbi->mytype>yingbi&&myjinbi->mytype<=tongbi){
                //						action_to= CCMoveTo::create(0.9f, CCPointMake(jingSprite->getPositionX(),jingSprite->getPositionY()));
                //					}
                
                if(myjinbi->mytype>tongbi&&myjinbi->mytype<=jingyou){
                    action_to= CCMoveTo::create(0.9f, oilSprite->convertToWorldSpace(ccp(0,0)));
                }
                if(myjinbi->mytype>jingyou&&myjinbi->mytype<=yingyou){
                    action_to= CCMoveTo::create(0.9f, oilSprite->convertToWorldSpace(ccp(0,0)));
                    
                }
                if(myjinbi->mytype>yingyou&&myjinbi->mytype<=tongyou){
                    
                    action_to= CCMoveTo::create(0.9f, oilSprite->convertToWorldSpace(ccp(0,0)));
                }
                if(myjinbi->mytype>tongyou&&myjinbi->mytype<=jinggang){
                    
                    action_to= CCMoveTo::create(0.9f, gangSprite->convertToWorldSpace(ccp(0,0)));
                }
                if(myjinbi->mytype>jinggang&&myjinbi->mytype<=yinggang){
                    
                    action_to= CCMoveTo::create(0.9f, gangSprite->convertToWorldSpace(ccp(0,0)));
                }
                if(myjinbi->mytype>yinggang&&myjinbi->mytype<=tonggang){
                    
                    action_to= CCMoveTo::create(0.9f, gangSprite->convertToWorldSpace(ccp(0,0)));
                }
                
                if(myjinbi->mytype>tonggang&&myjinbi->mytype<=jingrong){
                    
                    action_to= CCMoveTo::create(0.9f, rongSprite->convertToWorldSpace(ccp(0,0)));
                }
                if(myjinbi->mytype>jingrong&&myjinbi->mytype<=yingrong){
                    
                    action_to= CCMoveTo::create(0.9f, rongSprite->convertToWorldSpace(ccp(0,0)));
                }
                if(myjinbi->mytype>yingrong&&myjinbi->mytype<=tongrong){
                    
                    action_to= CCMoveTo::create(0.9f, rongSprite->convertToWorldSpace(ccp(0,0)));
                }
                
                CCFiniteTimeAction* actions=CCSequence::create(action_to,CCCallFuncO::create(this, callfuncO_selector(Chthief::callBack),myjinbi),NULL);
                myjinbi->istouch=false;
                myjinbi->runAction(actions);
            }
        }
	}
    
	
}



void Chthief::menuCloseCallback(CCObject* pSender)
{
	// "close" menu item clicked
    //	CCDirector::sharedDirector()->replaceScene(Chthief::scene());
    this->addChild(MyUtil::getInstance()->getWaitLayer("努力加载中"),1000);
    this->runAction(CCSequence::create(CCDelayTime::create(0.5),CCCallFunc::create(this, callfunc_selector(Chthief::toBuildScene)),NULL));
}

void Chthief::toBuildScene() {
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sfx_click.mp3");

    this->cleanup();
    
    MyGameInfo::getInstance()->enemyIron = 0;
    MyGameInfo::getInstance()->enemyOil = 0;
    CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.2, TransitonScene::create(startSceneTag),ccBLACK));
    CocosDenshion::SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
}

void Chthief::menucloseCording(CCObject* pSender){
    
	//this->removeChildByTag(100,true);
	
    
}
void Chthief::keyBackClicked(){
    
	CCDirector::sharedDirector()->end();
}

void Chthief::keyMenuClicked(){
	CCLog("Android- keyMenuClicked!");
}








void Chthief::movejibi(float gh){
    
    
	
}

void Chthief::callBack(CCObject* obj){
	
	Jinbi*myjinbi=(Jinbi*)obj;
	CCPoint point;
	if(myjinbi->mytype==jingbi){
        jingvalue1->setValue(jingvalue1->getValue()+1);
	}
	if(myjinbi->mytype>jingbi&&myjinbi->mytype<=yingbi){
        
        jingvalue2->setValue(jingvalue2->getValue()+1);;
        
	}
    
	if(myjinbi->mytype>yingbi&&myjinbi->mytype<=tongbi){
        jingvalue3->setValue(jingvalue3->getValue()+1);;
	}
    
	if(myjinbi->mytype>tongbi&&myjinbi->mytype<=jingyou){
		point = oilSprite->convertToWorldSpace(ccp(0,0));
        oilvalue1->setValue(oilvalue1->getValue()+1);
        MyGameInfo::getInstance()->changeResource(oilTag,jingyouvalue*dengji->getValue());
	}
	if(myjinbi->mytype>jingyou&&myjinbi->mytype<=yingyou){
		point = oilSprite->convertToWorldSpace(ccp(0,0));
		oilvalue2->setValue(oilvalue2->getValue()+1);
        MyGameInfo::getInstance()->changeResource(oilTag,yingyouvalue*dengji->getValue());
	}
	if(myjinbi->mytype>yingyou&&myjinbi->mytype<=tongyou){
		point = oilSprite->convertToWorldSpace(ccp(0,0));
		oilvalue3->setValue(oilvalue3->getValue()+1);
        MyGameInfo::getInstance()->changeResource(oilTag,tongyouvalue*dengji->getValue());
	}
	if(myjinbi->mytype>tongyou&&myjinbi->mytype<=jinggang){
        
		point = gangSprite->convertToWorldSpace(ccp(0,0));
		gangvalue1->setValue(gangvalue1->getValue()+1);
        MyGameInfo::getInstance()->changeResource(ironTag,jinggangvalue*dengji->getValue());
	}
	if(myjinbi->mytype>jinggang&&myjinbi->mytype<=yinggang){
		point = gangSprite->convertToWorldSpace(ccp(0,0));
		gangvalue2->setValue(gangvalue2->getValue()+1);
        MyGameInfo::getInstance()->changeResource(ironTag,yinggangvalue*dengji->getValue());
	}
	if(myjinbi->mytype>yinggang&&myjinbi->mytype<=tonggang){
		point = gangSprite->convertToWorldSpace(ccp(0,0));
		gangvalue3->setValue(gangvalue3->getValue()+1);
        MyGameInfo::getInstance()->changeResource(ironTag,tonggangvalue*dengji->getValue());
	}
    
	if(myjinbi->mytype>tonggang&&myjinbi->mytype<=jingrong){
        
		point = rongSprite->convertToWorldSpace(ccp(0,0));
		rongvalue1->setValue(rongvalue1->getValue()+1);
        MyGameInfo::getInstance()->changeResource(gloryTag,jingrongvalue*dengji->getValue());
	}
	if(myjinbi->mytype>jingrong&&myjinbi->mytype<=yingrong){
		point = rongSprite->convertToWorldSpace(ccp(0,0));
        rongvalue2->setValue(rongvalue2->getValue()+1);
        MyGameInfo::getInstance()->changeResource(gloryTag,yingrongvalue*dengji->getValue());
	}
	if(myjinbi->mytype>yingrong&&myjinbi->mytype<=tongrong){
		point = rongSprite->convertToWorldSpace(ccp(0,0));
        rongvalue3->setValue(rongvalue3->getValue()+1);
        MyGameInfo::getInstance()->changeResource(gloryTag,tongrongvalue*dengji->getValue());
	}
    
    
    
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sfx_bugeiDropMoney.mp3");
    
	sprintf(buffer_lift,"/%d",myjinbi->jibivalue*dengji->getValue());
	CCLabelAtlas* liftlostLabelshow1 = CCLabelAtlas::create(buffer_lift, "number.png", 24, 30, '.');
	liftlostLabelshow1->setPosition(point);
	CCActionInterval* action_to = CCEaseInOut::create(CCMoveTo::create(0.5f, CCPointMake(liftlostLabelshow1->getPositionX(),liftlostLabelshow1->getPositionY()-20)),1.35f);
	CCFiniteTimeAction* actions=CCSequence::create(action_to,CCCallFuncO::create(this, callfuncO_selector(Chthief::loseatlas),liftlostLabelshow1),NULL);
	liftlostLabelshow1->runAction(actions);
	this->addChild(liftlostLabelshow1, 10000);
    
	myjinbi->istouch=false;
	_jinbis->removeObject(myjinbi);
	batchNode->removeChild(myjinbi,true);
}

void Chthief::loseatlas(CCObject* obj){
    
	
	this->removeChild((CCLabelAtlas*)obj,true);
}

void Chthief::addbaseview(){
    
	baseSprite = CCLayer::create();
	baseSprite->setPosition(ccp(0, 0));
	// Add the sprite to Chthief layer as a child layer.
	this->addChild(baseSprite, 2,901);
	//baseSprite->setScale(320);
	CCSprite* qiandaiSprite= CCSprite::create("whiteImage.jpg");
    qiandaiSprite->setColor(ccc3(0,0,0));
	qiandaiSprite->setPosition(ccp(size.width/2, size.height/2));
    qiandaiSprite->setOpacity(150);
    //    qiandaiSprite->setColor(ccBLACK);
	// Add the sprite to Chthief layer as a child layer.
	baseSprite->addChild(qiandaiSprite, 2);
	qiandaiSprite->setScale(320);
    
    
	qiandaiSprite= CCSprite::create("whiteImage.jpg");
	qiandaiSprite->setPosition(ccp(size.width/2, size.height/2-15));
	// Add the sprite to Chthief layer as a child layer.
    qiandaiSprite->setOpacity(120);
    qiandaiSprite->setColor(ccc3(168,158,129));
	baseSprite->addChild(qiandaiSprite, 2);
	qiandaiSprite->setScaleX(57.5);
	qiandaiSprite->setScaleY(40.5);
    
	qiandaiSprite= CCSprite::createWithSpriteFrameName("bugeiDialogUp.png");
	qiandaiSprite->setPosition(ccp(size.width/2, size.height/2+190));
	// Add the sprite to Chthief layer as a child layer.
	baseSprite->addChild(qiandaiSprite, 2);
	qiandaiSprite->setScaleX(1.4f);
	qiandaiSprite= CCSprite::createWithSpriteFrameName("bugeiDialogUp.png");
	qiandaiSprite->setPosition(ccp(size.width/2, size.height/2-225));
	// Add the sprite to Chthief layer as a child layer.
	baseSprite->addChild(qiandaiSprite, 2);
	qiandaiSprite->setScaleX(1.4f);
    
	qiandaiSprite= CCSprite::createWithSpriteFrameName("bugeiZhuangshiGun.png");
	qiandaiSprite->setPosition(ccp(size.width/2-240, size.height/2-230));
	// Add the sprite to Chthief layer as a child layer.
	baseSprite->addChild(qiandaiSprite, 2);
    
	qiandaiSprite= CCSprite::createWithSpriteFrameName("bugeiZhuangshiOil.png");
	qiandaiSprite->setPosition(ccp(size.width/2+240, size.height/2-230));
	// Add the sprite to Chthief layer as a child layer.
	baseSprite->addChild(qiandaiSprite, 2);
    
	qiandaiSprite= CCSprite::createWithSpriteFrameName("bugeiQiandai.png");
	qiandaiSprite->setPosition(ccp(size.width/2+100, size.height/2+215));
	// Add the sprite to Chthief layer as a child layer.
	baseSprite->addChild(qiandaiSprite, 2);
	qiandaiSprite->setScale(1.2f);
	CCFlipX *flip;
    
	flip= CCFlipX::create(true);
	qiandaiSprite->runAction(flip);
    
}

void Chthief::addstartview(){
	Chthief::addbaseview();
    
	CCSprite* qiandaiSprite= CCSprite::createWithSpriteFrameName("bugeiInsturction.png");
	qiandaiSprite->setPosition(ccp(size.width/2-20, size.height/2+205));
	// Add the sprite to Chthief layer as a child layer.
	baseSprite->addChild(qiandaiSprite, 2);
	qiandaiSprite->setScale(0.8f);
	//qiandaiSprite= CCSprite::create("shuomingbg.png");
	//qiandaiSprite->setPosition(ccp(size.width/2, size.height/2));
    
	// Add the sprite to Chthief layer as a child layer.
	//baseSprite->addChild(qiandaiSprite, 2);
    
	CCLabelTTF* getLabelshow=CCLabelTTF::create(Jieshao, "Microsoft YaHei",35,CCSizeMake(492,288),kCCTextAlignmentLeft , kCCVerticalTextAlignmentTop);
	baseSprite->addChild(getLabelshow, 1009, 1010);
    
	getLabelshow->setPosition( ccp(size.width/2,size.height/2-20) );
	getLabelshow->setColor(ccc3(244,229,161));
    //开始按钮
	CCMenuItemSprite* pCloseItem = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("startBugeiButton.png"),
                                                            CCSprite::createWithSpriteFrameName("startBugeiButtonP.png"),
                                                            this,
                                                            menu_selector(Chthief::menuStartGame));
	pCloseItem->setPosition( ccp(size.width/2,size.height/2-200));
	CCMenu* pMenu = CCMenu::create();
	pMenu->setPosition( CCPointZero );
	baseSprite->addChild(pMenu ,1000,898);
	pMenu->addChild(pCloseItem,1);
}
void Chthief::addvinview(){
    
	this->removeChildByTag(901,true);
	Chthief::addbaseview();
    
    int deltaOil = oilvalue1->getValue()*jingyouvalue+oilvalue2->getValue()*yingyouvalue+oilvalue3->getValue()*tongyouvalue;
    int deltaIron = gangvalue1->getValue()*jinggangvalue+gangvalue2->getValue()*yinggangvalue+gangvalue3->getValue()*tonggangvalue;
    int deltaRong = rongvalue1->getValue()*jingrongvalue+rongvalue2->getValue()*yingrongvalue+rongvalue3->getValue()*tongrongvalue;
    
    MyHttpConnection::getInstance()->sendUpdateResource(deltaOil*dengji->getValue(),deltaIron*dengji->getValue(),deltaRong*dengji->getValue());
	
	Chthief::showlabels(myrong,deltaRong,size.width/2-100,size.height/2+96);
	Chthief::showlabels(myoil,deltaOil,size.width/2-100,size.height/2+20);
	Chthief::showlabels(mygang,deltaIron,size.width/2-100,size.height/2-56);
    
    
    //	Chthief::showlabels(myjing,jingvalue1*jingbivalue+jingvalue2*yingbivalue+jingvalue3*tongbivalue,size.width/2-100,size.height/2-123);
    //关闭按钮
	CCMenuItemSprite* pCloseItem = CCMenuItemSprite::create(
                                                            CCSprite::createWithSpriteFrameName("bugeiReturnBase.png"),
                                                            CCSprite::createWithSpriteFrameName("bugeiReturnBaseP.png"),
                                                            this,
                                                            menu_selector(Chthief::menuCloseCallback));
	pCloseItem->setScale(0.9f);
	pCloseItem->setPosition( ccp(size.width/2-50,size.height/2-205));
	CCMenu* pMenu = CCMenu::create();
	pMenu->setPosition( CCPointZero );
	baseSprite->addChild(pMenu ,1000);
	pMenu->addChild(pCloseItem,1);
	CCMenuItemSprite* ppaihangItem = CCMenuItemSprite::create(
                                                              CCSprite::createWithSpriteFrameName("bugeiTopButton.png"),
                                                              CCSprite::createWithSpriteFrameName("bugeiTopButtonP.png"),
                                                              this,
                                                              menu_selector(Chthief::addpaihangview));
	ppaihangItem->setPosition( ccp(size.width/2+90,size.height/2-205));
	pMenu->addChild(ppaihangItem,1);
	ppaihangItem->setScale(0.9f);
	this->removeChild(liftlostLabelshow,true);
	this->removeChild(paddle,true);
	for(int i=0;i<_jinbis->count();i++){
		Jinbi* myjinbi=(Jinbi*)_jinbis->objectAtIndex(i);
		this->removeChild(myjinbi,true);
	}
	_jinbis->removeAllObjects();
	CCSprite*  qiandaiSprite= CCSprite::createWithSpriteFrameName("bugeiTotal.png");
	qiandaiSprite->setPosition(ccp(size.width/2-20, size.height/2+205));
	// Add the sprite to Chthief layer as a child layer.
	baseSprite->addChild(qiandaiSprite, 2);
	qiandaiSprite->setScale(0.8f);
    
	qiandaiSprite= CCSprite::createWithSpriteFrameName("bugeiHonor (3).png");
	qiandaiSprite->setPosition(ccp(size.width/2-150, size.height/2+96));
	// Add the sprite to Chthief layer as a child layer.
	baseSprite->addChild(qiandaiSprite, 2);
	qiandaiSprite->setScale(0.9f);
    
	qiandaiSprite= CCSprite::createWithSpriteFrameName("bugeiOil (0).png");
	qiandaiSprite->setPosition(ccp(size.width/2-150, size.height/2+23));
	// Add the sprite to Chthief layer as a child layer.
	baseSprite->addChild(qiandaiSprite, 2);
	qiandaiSprite->setScale(0.8f);
    
	qiandaiSprite= CCSprite::createWithSpriteFrameName("bugeiIron (1).png");
	qiandaiSprite->setPosition(ccp(size.width/2-150, size.height/2-53));
	// Add the sprite to Chthief layer as a child layer.
	baseSprite->addChild(qiandaiSprite, 2);
	qiandaiSprite->setScale(0.7f);
    
	qiandaiSprite= CCSprite::createWithSpriteFrameName("bugeijin (0).png");
	qiandaiSprite->setPosition(ccp(size.width/2-150, size.height/2-125));
	// Add the sprite to Chthief layer as a child layer.
	baseSprite->addChild(qiandaiSprite, 2);
	qiandaiSprite->setScale(0.68f);
    
}
void Chthief::addpaihangview(CCObject* pSender){
	
	this->removeChildByTag(901,true);
	Chthief::addbaseview();
    //排行榜退出
	CCMenuItemSprite* pCloseItem = CCMenuItemSprite::create(
                                                            CCSprite::createWithSpriteFrameName("bugeiReturnBase.png"),
                                                            CCSprite::createWithSpriteFrameName("bugeiReturnBaseP.png"),
                                                            this,
                                                            menu_selector(Chthief::menuCloseCallback));
	pCloseItem->setScale(0.9f);
	pCloseItem->setPosition(ccp(size.width/2,size.height/2-205));
	CCMenu* pMenu = CCMenu::create();
	pMenu->setPosition( CCPointZero );
	baseSprite->addChild(pMenu ,1000);
	pMenu->addChild(pCloseItem,1);
	CCMenuItemSprite* ppaihangItem = CCMenuItemSprite::create(
                                                              CCSprite::createWithSpriteFrameName("bugeiTopButton.png"),
                                                              CCSprite::createWithSpriteFrameName("bugeiTopButtonP.png"),
                                                              this,
                                                              menu_selector(Chthief::addpaihangview));
	ppaihangItem->setPosition( ccp(size.width/2+90,size.height/2-205));
//	pMenu->addChild(ppaihangItem,1);
	ppaihangItem->setScale(0.9f);
	ppaihangItem->setEnabled(false);
	ppaihangItem->selected();
	
	this->removeChild(liftlostLabelshow,true);
	this->removeChild(paddle,true);
	for(int i=0;i<_jinbis->count();i++){
		Jinbi* myjinbi=(Jinbi*)_jinbis->objectAtIndex(i);
		this->removeChild(myjinbi,true);
	}
	_jinbis->removeAllObjects();
	CCSprite*  qiandaiSprite= CCSprite::createWithSpriteFrameName("bugeiTopIcon.png");
	qiandaiSprite->setPosition(ccp(size.width/2-20, size.height/2+205));
	// Add the sprite to Chthief layer as a child layer.
	baseSprite->addChild(qiandaiSprite, 2);
	qiandaiSprite->setScale(0.8f);
    
	CCSprite* zongjiSprite=  CCSprite::createWithSpriteFrameName("bugeiTopMingci.png");
	zongjiSprite->setPosition(ccp(size.width/2-180, size.height/2+135));
	// Add the sprite to Chthief layer as a child layer.
	baseSprite->addChild(zongjiSprite, 2);
    
	zongjiSprite=  CCSprite::createWithSpriteFrameName("bugeiTopWanjia.png");
	zongjiSprite->setPosition(ccp(size.width/2, size.height/2+135));
	// Add the sprite to Chthief layer as a child layer.
	baseSprite->addChild(zongjiSprite, 2);
    
	zongjiSprite=  CCSprite::createWithSpriteFrameName("bugeiTopDefen.png");
	zongjiSprite->setPosition(ccp(size.width/2+180, size.height/2+135));
	// Add the sprite to Chthief layer as a child layer.
	baseSprite->addChild(zongjiSprite, 2);
    
	zongjiSprite=  CCSprite::createWithSpriteFrameName("bugeiTopDivideLine.png");
	zongjiSprite->setPosition(ccp(size.width/2, size.height/2+118));
	// Add the sprite to Chthief layer as a child layer.
	baseSprite->addChild(zongjiSprite, 2);
	zongjiSprite->setScaleX(1.2f);
}

void Chthief::gameover(){
    
	Chthief::addvinview();
	
}
void Chthief::showlabels(int mytype, int labshow,int with,int hight){
    //TODO
    
	if (mytype!=myjing)
	{
        sprintf(buffer_lift,"%d x %d = %d",labshow,dengji->getValue(),labshow*dengji->getValue());
	}else{
        sprintf(buffer_lift,"%d",labshow);
	}
    CCLabelTTF* winlostLabelshow = CCLabelTTF::create(buffer_lift, "Arial", 35);
    winlostLabelshow->setAnchorPoint(ccp(0,0.5));
	winlostLabelshow->setPosition(ccp(with,hight));
    winlostLabelshow->setColor(ccc3(244,229,161));
	baseSprite->addChild(winlostLabelshow, 1000);
    
    
	//Jinbi* jinbi = Jinbi::JinbiWithTexture(mytype);
	//jinbi->setPosition(ccp(with-30,hight));
	//this->addChild(jinbi,1000);
    
}

void Chthief::timelose(float aa){
	speakvalue++;
	timevalue--;
	
    
	if (timevalue==-1)
	{
		liftlostLabelshow->setString("0");
		this->runAction( CCSequence::create(
                                            CCDelayTime::create(1.5f),
                                            CCCallFunc::create(this,
                                                               callfunc_selector(Chthief::gameover)),
                                            NULL));
        //	Chthief::gameover();
	}
	if (timevalue>=0)
	{
		sprintf(buffer_lift,"%d",timevalue);
		liftlostLabelshow->setString(buffer_lift);
        
		if (speakvalue==(3+at))
		{
			at=(int)rand()%8;
			speakvalue=0;
			CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sfx_bugeiLaugh.mp3");
		}
	}
}

void Chthief::loadResource() {
    GXUtil::loadResourceUtilSucc("bugei.plist","bugei.pvr.ccz");
    GXUtil::loadResourceUtilSucc("bubeiBack.plist","bubeiBack.pvr.ccz");
    //    CCTextureCache::sharedTextureCache()->dumpCachedTextureInfo();
}

void Chthief::releaseResource() {
    CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile("bugei.plist");
    CCTextureCache::sharedTextureCache()->removeTextureForKey("bugei.pvr.ccz");
    CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile("bubeiBack.plist");
    CCTextureCache::sharedTextureCache()->removeTextureForKey("bubeiBack.pvr.ccz");
}


Jinbi::Jinbi(void)
{
}

Jinbi::~Jinbi(void)
{
    //    CCLog("jinbi has bean released");
}

CCRect Jinbi::rect()
{
	CCSize s = getContentSize();
	return  CCRectMake(-s.width/2,-s.height/2, s.width,s.height);
}

Jinbi* Jinbi::create(int mytype)
{
	
	Jinbi* pJinbi = new Jinbi();
	pJinbi->mytype=mytype;
	pJinbi->istouch=false;
	pJinbi->initJinbi(0.2);
	pJinbi->autorelease();
    //	pJinbi->movemove(0.2f);
	return pJinbi;
}

bool Jinbi::initJinbi(float time)
{
	
    m_state = hkJinbiStateUngrabbed;
    
    
	if(mytype==jingbi){
        CCArray* animFrames = CCArray::createWithCapacity(6);
//        CCSpriteFrame *frame0;
        char keyname[100];
		jibivalue=jingbivalue;
        CCSprite::initWithSpriteFrameName("bugeijin (0).png");
		for (int i=0;i<6;i++)
		{
			sprintf(keyname,"bugeijin (%d).png",i);
			animFrames->addObject(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(keyname));
            
		}
        CCAnimation *animation = CCAnimation::createWithSpriteFrames(animFrames, time);
        CCAnimate *animate = CCAnimate::create(animation);
        CCActionInterval* seq = (CCActionInterval*)(CCSequence::create( animate,
                                                                       animate->copy()->autorelease(),
                                                                       CCFlipX::create(false),
                                                                       NULL) );
        CCAction *ccactivon=CCRepeatForever::create( seq ) ;
        runAction(ccactivon);
	} else if(mytype>jingbi&&mytype<=yingbi){
        CCArray* animFrames = CCArray::createWithCapacity(6);
//        CCSpriteFrame *frame0;
        char keyname[100];
		jibivalue=yingbivalue;
		CCSprite::initWithSpriteFrameName("bugeiyin (0).png");
        
		for (int i=0;i<6;i++)
		{
			sprintf(keyname,"bugeiyin (%d).png",i);
			animFrames->addObject(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(keyname));
		}
	} else if(mytype>yingbi&&mytype<=tongbi){
        
        CCArray* animFrames = CCArray::createWithCapacity(6);
//        CCSpriteFrame *frame0;
        char keyname[100];
        CCSprite::initWithSpriteFrameName("bugeitong (0).png");
		jibivalue=tongbivalue;
		for (int i=0;i<6;i++)
		{
			sprintf(keyname,"bugeitong (%d).png",i);
			animFrames->addObject(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(keyname));
		}
	}
    
	if(mytype>tongbi&&mytype<=jingyou){
		jibivalue=jingyouvalue;
	    CCSprite::initWithSpriteFrameName("bugeiOil (3).png");
	}
	if(mytype>jingyou&&mytype<=yingyou){
		jibivalue=yingyouvalue;
		
		CCSprite::initWithSpriteFrameName("bugeiOil (2).png");
	}
	if(mytype>yingyou&&mytype<=tongyou){
		jibivalue=tongyouvalue;
		
		CCSprite::initWithSpriteFrameName("bugeiOil (0).png");
	}
	if(mytype>tongyou&&mytype<=jinggang){
		jibivalue=jinggangvalue;
		CCSprite::initWithSpriteFrameName("bugeiIron (2).png");
	}
	if(mytype>jinggang&&mytype<=yinggang){
        
		jibivalue=yinggangvalue;
		CCSprite::initWithSpriteFrameName("bugeiIron (1).png");
	}
	if(mytype>yinggang&&mytype<=tonggang){
		jibivalue=tonggangvalue;
		CCSprite::initWithSpriteFrameName("bugeiIron (0).png");
	}
    
	if(mytype>tonggang&&mytype<=jingrong){
		jibivalue=jingrongvalue;
		CCSprite::initWithSpriteFrameName("bugeiHonor (3).png");
	}
	if(mytype>jingrong&&mytype<=yingrong){
		jibivalue=yingrongvalue;
		CCSprite::initWithSpriteFrameName("bugeiHonor (1).png");
	}
	if(mytype>yingrong&&mytype<=tongrong){
		jibivalue=tongrongvalue;
		CCSprite::initWithSpriteFrameName("bugeiHonor (0).png");
	}
    
	return true;
}

void Jinbi::onEnter()
{
	CCDirector* pDirector = CCDirector::sharedDirector();
	pDirector->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
	CCSprite::onEnter();
}

void Jinbi::onExit()
{
	CCDirector* pDirector = CCDirector::sharedDirector();
	pDirector->getTouchDispatcher()->removeDelegate(this);
	CCSprite::onExit();
}

bool Jinbi::containsTouchLocation(CCTouch* touch)
{
	return rect().containsPoint(convertTouchToNodeSpaceAR(touch));
}

bool Jinbi::ccTouchBegan(CCTouch* touch, CCEvent* event)
{
	
	if (m_state != hkJinbiStateUngrabbed) return false;
	if ( !containsTouchLocation(touch) ) return false;
	istouch=true;
	m_state = hkJinbiStateGrabbed;
	return true;
}

void Jinbi::ccTouchMoved(CCTouch* touch, CCEvent* event)
{
    
//	CCAssert(m_state == hkJinbiStateGrabbed, L"Jinbi - Unexpected state!");
    
    
}

//CCObject* Jinbi::copyWithZone(CCZone *pZone)
//{
//	this->retain();
//	return this;
//}

void Jinbi::ccTouchEnded(CCTouch* touch, CCEvent* event)
{
//	CCAssert(m_state == hkJinbiStateGrabbed, L"Jinbi - Unexpected state!");
	CCPoint touchPoint = touch->getLocation();
	m_state = hkJinbiStateUngrabbed;
	istouch=true;
    
} 



Paddle::~Paddle(void)
{
    //    CCLog("paddle has been released");
}

CCRect Paddle::rect()
{
	CCSize s =  getContentSize();
	return CCRectMake(-s.width/2,-s.height/2, s.width,s.height);
}

Paddle* Paddle::create()
{
	//CCTexture2D* paddleTexture = CCTextureCache::sharedTextureCache()->addImage("els1.png");
	Paddle* pPaddle = new Paddle();
    
	pPaddle->istouch=false;
	
	pPaddle->initPaddle("bugeiEnermy (1).png");
	pPaddle->autorelease();
	pPaddle->movemove(0.3f);
    
	return pPaddle;
}

bool Paddle::initPaddle(const char* aTexture)
{
	if(CCSprite::initWithSpriteFrameName(aTexture) ) 
	{
		m_state = hkPaddleStateUngrabbed;
	}
	return true;
}

void Paddle::onEnter()
{
	CCDirector* pDirector = CCDirector::sharedDirector();
	pDirector->getTouchDispatcher()->addTargetedDelegate(this, -100, true);
	CCSprite::onEnter();
}

void Paddle::onExit()
{
	CCDirector* pDirector = CCDirector::sharedDirector();
	pDirector->getTouchDispatcher()->removeDelegate(this);
	CCSprite::onExit();
}    

bool Paddle::containsTouchLocation(CCTouch* touch)
{
    
	return rect().containsPoint(convertTouchToNodeSpaceAR(touch));
}

bool Paddle::ccTouchBegan(CCTouch* touch, CCEvent* event)
{
	if (m_state != hkPaddleStateUngrabbed) return false;
	if ( !containsTouchLocation(touch) ) return false;
	istouch=true;
	m_state = hkPaddleStateGrabbed;
	return true;
}

void Paddle::ccTouchMoved(CCTouch* touch, CCEvent* event)
{
    
//	CCAssert(m_state == hkPaddleStateGrabbed, L"Paddle - Unexpected state!");    
    
    
}

//CCObject* Paddle::copyWithZone(CCZone *pZone)
//{
//	this->retain();
//	return this;
//}

void Paddle::ccTouchEnded(CCTouch* touch, CCEvent* event)
{
	CCAssert(m_state == hkPaddleStateGrabbed, "Paddle - Unexpected state!");    
//	CCPoint touchPoint = touch->getLocation();
	
	this->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("bugeiEnermy (2).png"));
	m_state = hkPaddleStateUngrabbed;
	
    
} 

//void Paddle::touchDelegateRetain()
//{
//	this->retain();
//}
//
//void Paddle::touchDelegateRelease()
//{
//	this->release();
//}

void Paddle::movemove(float time){
    
	CCArray* animFrames = CCArray::createWithCapacity(2);
	
    
	CCSpriteFrame* frame =CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("bugeiEnermy (0).png");
	animFrames->addObject(frame);
	CCSpriteFrame *frame1=CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("bugeiEnermy (1).png");
	animFrames->addObject(frame1);
	CCSpriteFrame *frame2=CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("bugeiEnermy (1).png");
	animFrames->addObject(frame2);
    
	
    
	CCAnimation *animation = CCAnimation::createWithSpriteFrames(animFrames, 0.2f);
	CCAnimate *animate = CCAnimate::create(animation);
	CCActionInterval* seq = (CCActionInterval*)(CCSequence::create( animate,
                                                                   animate->copy()->autorelease(),
                                                                   CCFlipX::create(false),
                                                                   NULL) );
	CCAction *ccactivon=CCRepeatForever::create( seq ) ;
	runAction(ccactivon);
	//	runAction(CCSequence::actions( CCDelayTime::actionWithDuration(1.0f), NULL));
    
}

ChthiefScene* ChthiefScene::create() {
    ChthiefScene* scene = new ChthiefScene();
    if (scene && scene->init())
    {
        scene->autorelease();
        return scene;
    }
    else
    {
        CC_SAFE_DELETE(scene);
        return NULL;
    }
    return scene;
}

void ChthiefScene::loadResource(){
}
void ChthiefScene::releaseResource() {
}