#ifndef __Chthief_SCENE_H__
#define __Chthief_SCENE_H__

#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "MyAtlasNumber.h"
#include "GXBaseScene.h"
#include "GXAntiCrack.h"



using namespace cocos2d;
//初始场景
class Paddle;
class Chthief : public cocos2d::CCLayer
{
public:
    Chthief():
    addtet(0),
    at(0),
    speakvalue(0), 
    batchNode(NULL){
        dengji = GXintValue::create(0);
        dengji->retain();
        oilvalue1 = GXintValue::create(0);
        oilvalue1->retain();
        gangvalue1 = GXintValue::create(0);
        gangvalue1->retain();
        rongvalue1 = GXintValue::create(0);
        rongvalue1->retain();
        jingvalue1 = GXintValue::create(0);
        jingvalue1->retain();
        oilvalue2 = GXintValue::create(0);
        oilvalue2->retain();
        gangvalue2 = GXintValue::create(0);
        gangvalue2->retain();
        rongvalue2 = GXintValue::create(0);
        rongvalue2->retain();
        jingvalue2 = GXintValue::create(0);
        jingvalue2->retain();
        oilvalue3 = GXintValue::create(0);
        oilvalue3->retain();
        gangvalue3 = GXintValue::create(0);
        gangvalue3->retain();
        rongvalue3 = GXintValue::create(0);
        rongvalue3->retain();
        jingvalue3 = GXintValue::create(0);
        jingvalue3->retain();
    }
    ~Chthief() {
        CC_SAFE_RELEASE_NULL(_jinbis);
        delete []buffer_lift;
        releaseResource();
    }
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

    // there's no 'id' in cpp, so we recommand to return the exactly class pointer
    static cocos2d::CCScene* scene(int dengji);
    
    // a selector callback
    void menuStartGame(CCObject* pSender);
    
    CCSpriteBatchNode* batchNode ;

	Paddle* paddle;
	//char* buffer;
	GXintValue* dengji;
	int addtet;
	GXintValue* oilvalue1;
    GXintValue* oilvalue2;
    GXintValue* oilvalue3;
    GXintValue* gangvalue1;
    GXintValue* gangvalue2;
    GXintValue* gangvalue3;
    GXintValue* rongvalue1;
    GXintValue* rongvalue2;
    GXintValue* rongvalue3;
    GXintValue* jingvalue1;
    GXintValue* jingvalue2;
    GXintValue* jingvalue3;
	int speakvalue;
	CCArray* _jinbis;

	CCLabelTTF *label2;
	CCMenu* pcolseMenu;
	CCSize size;
	bool isflip;
	MyAtlasNumber* oilSprite;
	MyAtlasNumber* gangSprite;
	MyAtlasNumber* rongSprite;
	CCLayer* baseSprite;
	int at;
	float xx,yy;
	int timevalue;
	char* buffer_lift;
	CCLabelAtlas *liftlostLabelshow;
	void timelose(float aa);
	void menuCloseCallback(CCObject* pSender);
    
    void toBuildScene();

	void menucloseCording(CCObject* pSender);
	void gameover();
	void lostdao(float aa);
	void showlabels(int mytype,int labshow,int with,int hight);
	void updateGame(float aa);
	void movejibi(float gh);
	void callBack(CCObject* obj);
	void loseatlas(CCObject* obj);


	void addbaseview();
	void addstartview();
	void addvinview();
	void addpaihangview(CCObject* pSender);

	virtual void keyBackClicked();//Android 返回键
	virtual void keyMenuClicked();//Android 菜单键
    
    virtual void loadResource();
    virtual void releaseResource();

    // implement the "static node()" method manually
     CREATE_FUNC(Chthief);
};

#endif  // __Chthief_SCENE_H__


#ifndef _PADDLE_H_
#define _PADDLE_H_

#include "cocos2d.h"

USING_NS_CC;

typedef enum tagPaddleState 
{
	hkPaddleStateGrabbed,
	hkPaddleStateUngrabbed
} PaddleState; 

class Paddle : public CCSprite, public CCTargetedTouchDelegate
{
	PaddleState        m_state;

public:
	Paddle():
    step(0)
    {};
	virtual ~Paddle(void);
	void movemove(float time);
	bool  istouch;
	CCRect rect();
    int step;
	bool initPaddle(const char* name);
	virtual void onEnter();
	virtual void onExit();
	bool containsTouchLocation(CCTouch* touch);
	virtual bool ccTouchBegan(CCTouch* touch, CCEvent* event);
	virtual void ccTouchMoved(CCTouch* touch, CCEvent* event);
	virtual void ccTouchEnded(CCTouch* touch, CCEvent* event);
//	virtual CCObject* copyWithZone(CCZone *pZone);

//	virtual void touchDelegateRetain();
//	virtual void touchDelegateRelease();

	static Paddle* create();
};

#endif


#ifndef _Jinbi_H_
#define _Jinbi_H_

#define Jieshao "玩法介绍：\n        德军士兵车上有各种资源勋章,正准备逃走!60秒内,点击他,就会被揍出各种战利品!!点击战利品进行收获!!"

#define allrand 625
#define jingbi  0
#define yingbi  0
#define tongbi  0
#define jingyou 20
#define yingyou 100
#define tongyou 250
#define jinggang 270
#define yinggang 350
#define tonggang 500
#define jingrong 510
#define yingrong 550
#define tongrong 625

#define myjing  10001
#define myoil  10002
#define mygang 10003
#define myrong 10004
#define jingbivalue 3
#define yingbivalue 2
#define tongbivalue 1
#define jingyouvalue 120
#define yingyouvalue 48
#define tongyouvalue 12
#define jinggangvalue 120
#define yinggangvalue 48
#define tonggangvalue 12
#define jingrongvalue 5
#define yingrongvalue 2
#define tongrongvalue 1

#include "cocos2d.h"
#include "string"
USING_NS_CC;
using namespace std;






typedef enum tagJinbiState 
{
	hkJinbiStateGrabbed,
	hkJinbiStateUngrabbed
} JinbiState; 

class Jinbi : public CCSprite, public CCTargetedTouchDelegate
{
	JinbiState        m_state;

public:
	Jinbi(void);
	virtual ~Jinbi(void);
	int jibivalue;
	bool  istouch;
	int mytype;
	CCRect rect();
	bool initJinbi(float time);
	virtual void onEnter();
	virtual void onExit();

	bool containsTouchLocation(CCTouch* touch);
	virtual bool ccTouchBegan(CCTouch* touch, CCEvent* event);
	virtual void ccTouchMoved(CCTouch* touch, CCEvent* event);
	virtual void ccTouchEnded(CCTouch* touch, CCEvent* event);
//	virtual CCObject* copyWithZone(CCZone *pZone);
//
//	virtual void touchDelegateRetain();
//	virtual void touchDelegateRelease();

	static Jinbi* create(int mytype);
};

class ChthiefScene : public GXBaseScene {
    
public:
    ~ChthiefScene() {
        CCLog("ChthiefScene released");
    }
    static ChthiefScene* create();
    virtual void loadResource();
    virtual void releaseResource();
};

#endif
