/*
ProjectName: 2048
Author: 马三小伙儿
Blog: http://www.cnblogs.com/msxh/
Github:https://github.com/XINCGer
Date: 2016/08/03
*/
#include "HelloWorldScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;
using namespace CocosDenshion;

#define TOUCH_LONG 50 //触摸操作方向上的距离
#define TOUCH_SHORT 10 //触摸操作垂直方向的偏移范围

using namespace cocostudio::timeline;

Scene* HelloWorld::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = HelloWorld::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}
	auto size = Director::getInstance()->getVisibleSize();

	this->isPlay = true;	//isPlay进行初始化
	this->isLock = false; //isLock进行初始化
	auto *dispatcher = Director::getInstance()->getEventDispatcher();
	auto *listener = EventListenerTouchOneByOne::create(); //创建监听器
	listener->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(HelloWorld::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(HelloWorld::onTouchEnded, this);
	dispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	auto* background = cocos2d::LayerColor::create(cocos2d::Color4B(255, 255, 255, 255));
	addChild(background);

	int width = size.width;				// 屏幕宽度
	int height = size.height;				// 屏幕高度
	int cardSize = (width - 30) / 4;			// 卡片的宽高

	//卡片的底座
	auto *baseBG = LayerColor::create(cocos2d::Color4B(186, 191, 191, 255), width - 30, width - 30);
	baseBG->setPosition(15, (height - 100 - width - 15) / 2);
	addChild(baseBG);

	for (int i = 0; i < 4; i++){
		for (int j = 0; j < 4; j++){
			//预先创建4x4的卡片，并使他们的值全部为0
			card[i][j] = CardSprite::createCardSprite(0, cardSize, cardSize * i + CARD_BORDER / 2, cardSize * j + CARD_BORDER / 2);
			baseBG->addChild(card[i][j]);	//将卡片附加在底座上面
		}
	}

	//游戏开始时，显示两张数值为2的卡片
	this->createCard();
	this->createCard();

	record = UserDefault::getInstance()->getIntegerForKey("record");
	demo = 2048;
	score = 0;
	broad1 = ScoreBroad::createScoreBroad(demo, 120, 90, "", 1, 15, size.height - 100);
	broad2 = ScoreBroad::createScoreBroad(record, 90, 90, "high", 2, 150, size.height - 100);
	broad3 = ScoreBroad::createScoreBroad(score, 90, 90, "score", 2, 255, size.height - 100);
	addChild(broad1);
	addChild(broad2);
	addChild(broad3);
	return true;
}

bool HelloWorld::onTouchBegan(Touch *touch, Event *event){
	this->x = touch->getLocation().x; //记录触摸开始时的坐标位置
	this->y = touch->getLocation().y;
	return true;
}

void  HelloWorld::onTouchMoved(Touch *touch, Event *event){
	if (!isLock){      //判断此时触摸事件是否已经生效
		float dx = touch->getLocation().x - this->x;  //获取触摸移动的差值
		float dy = touch->getLocation().y - this->y;
		//与初识坐标比较，判断触摸的移动方向
		if (dx > TOUCH_LONG &&fabs(dy) < TOUCH_SHORT){
			if (doRight()){			//向右操作
				createCard();
			}
			this->isLock = true;	//isLock为true时表示触摸操作已经被响应
		}
		else if (dx < -TOUCH_LONG && fabs(dy) < TOUCH_SHORT){
			if (doLeft()){		//向左操作
				createCard();
			}
			this->isLock = true;
		}
		else if (dy>TOUCH_LONG &&fabs(dx) < TOUCH_SHORT){
			if (doUp()){	//向上操作
				createCard();
			}
			this->isLock = true;
		}
		else if (dy < -TOUCH_LONG &&fabs(dx) < TOUCH_SHORT){
			if (doDown()){		//向下操作
				createCard();
			}
			this->isLock = true;
		}
	}
}

void HelloWorld::onTouchEnded(Touch *touch, Event *event){
	//触摸结束时，将isLock还原为false初值
	this->isLock = false;
	if (isGameOver()){
		SimpleAudioEngine::getInstance()->stopAllEffects();
		SimpleAudioEngine::getInstance()->playEffect("death.mp3");
		auto transtion = TransitionFade::create(1.0, GameOverScene::createScene());
		Director::getInstance()->replaceScene(transtion);
	}
}

bool HelloWorld::doLeft(){
	bool isdo = false;		//用于判断滑动操作是否有效
	for (int y = 0; y < 4; y++){	//y表示列
		for (int x = 0; x < 4; x++){	//从每一行左侧第一个卡片开始
			log("x:%d", x);
			for (int x1 = x + 1; x1 < 4; x1++){		//指向卡片右侧
				if (card[x1][y]->getNumber()>0){	//如果当前指向卡片的右侧卡片的值不是0
					if (card[x][y]->getNumber() <= 0){		//如果当前指向卡片的值为0，则直接移动其右侧卡片
						card[x][y]->setNumber(card[x1][y]->getNumber());
						card[x1][y]->setNumber(0);
						x--;  //指针后退
						log("x->%d", x);
						isdo = true;
					}
					else if (card[x][y]->getNumber() == card[x1][y]->getNumber()){  //相邻的两个卡片数字如果相同则合并
						refreshBroad(card[x][y]->getNumber());
						card[x][y]->setNumber(card[x][y]->getNumber() * 2);
						card[x1][y]->setNumber(0);
						isdo = true;
					}
					SimpleAudioEngine::getInstance()->playEffect("move.wav");
					break;
				}
			}
		}

	}
	log("LEFT");
	return isdo;
}

bool HelloWorld::doRight(){
	bool isdo = false;
	for (int y = 0; y < 4; y++)
	{
		for (int x = 3; x >= 0; x--) 				// 从最右边的卡片开始
		{
			for (int x1 = x - 1; x1 >= 0; x1--) 	// 指向当前卡片左侧的卡片
			{
				if (card[x1][y]->getNumber() > 0)
				{
					if (card[x][y]->getNumber() <= 0)
					{
						card[x][y]->setNumber(card[x1][y]->getNumber());
						card[x1][y]->setNumber(0);
						x++;
						isdo = true;
					}
					else if (card[x][y]->getNumber() == card[x1][y]->getNumber())
					{
						refreshBroad(card[x][y]->getNumber());
						card[x][y]->setNumber(card[x][y]->getNumber() * 2);
						card[x1][y]->setNumber(0);
						isdo = true;
					}
					SimpleAudioEngine::getInstance()->playEffect("move.wav");
					break;
				}
			}
		}
	}
	log("RIGHT");
	return isdo;

}

bool HelloWorld::doUp(){
	bool isdo = false;
	for (int x = 0; x < 4; x++)
	{
		for (int y = 3; y >= 0; y--)
		{
			for (int y1 = y - 1; y1 >= 0; y1--)
			{
				if (card[x][y1]->getNumber() > 0)
				{
					if (card[x][y]->getNumber() <= 0)
					{
						card[x][y]->setNumber(card[x][y1]->getNumber());
						card[x][y1]->setNumber(0);
						y++;
						isdo = true;
					}
					else if (card[x][y]->getNumber() == card[x][y1]->getNumber())
					{
						refreshBroad(card[x][y]->getNumber());
						card[x][y]->setNumber(card[x][y]->getNumber() * 2);
						card[x][y1]->setNumber(0);
						isdo = true;
					}
					SimpleAudioEngine::getInstance()->playEffect("move.wav");
					break;
				}
			}
		}
	}
	log("UP");
	return isdo;
}

bool HelloWorld::doDown(){
	bool isdo = false;
	for (int x = 0; x < 4; x++)
	{
		for (int y = 0; y < 4; y++)
		{
			for (int y1 = y + 1; y1 < 4; y1++)
			{
				if (card[x][y1]->getNumber() > 0)
				{
					if (card[x][y]->getNumber() <= 0)
					{
						card[x][y]->setNumber(card[x][y1]->getNumber());
						card[x][y1]->setNumber(0);
						y--;
						isdo = true;
					}
					else if (card[x][y]->getNumber() == card[x][y1]->getNumber())
					{
						refreshBroad(card[x][y]->getNumber());
						card[x][y]->setNumber(card[x][y]->getNumber() * 2);
						card[x][y1]->setNumber(0);
						isdo = true;
					}
					SimpleAudioEngine::getInstance()->playEffect("move.wav");
					break;
				}
			}
		}
	}
	log("DOWN");
	return isdo;
}

void HelloWorld::createCard(){
	int i = CCRANDOM_0_1() * 4;
	int j = CCRANDOM_0_1() * 4;
	//判断这个位置是否有值
	if (card[i][j]->getNumber() > 0){
		createCard();	 //递归调用
	}
	else{
		card[i][j]->setNumber(2);		//加入新的卡片
	}
}

void HelloWorld::scoreAddUp(ScoreBroad* broad, int number){
	int score = broad->getScore();
	broad->setScore(score + number);
}

void HelloWorld::refreshBroad(int x){
	if (2 * x == demo){
		demo = 4 * x;
		broad1->setScore(demo);
	}
	score += x;

	if (x % 32 == 0){
		SimpleAudioEngine::getInstance()->stopAllEffects();
		SimpleAudioEngine::getInstance()->playEffect("good1.wav");
	}
	if (score > record){
		record = score;
		UserDefault::getInstance()->setIntegerForKey("record", record);
		broad2->setScore(record);
		if (isPlay && record >= 100){
			SimpleAudioEngine::getInstance()->stopAllEffects();
			SimpleAudioEngine::getInstance()->playEffect("good2.wav");
			isPlay = !isPlay;
		}

	}
	broad3->setScore(score);
}

bool HelloWorld::isGameOver(){
	for (int idx = 0; idx < 4; idx++)
	{
		for (int idy = 0; idy < 4; idy++)
		{
			if (card[idx][idy]->getNumber() == 0)
			{
				return false;
			}
		}
	}

	for (int idx = 0; idx < 4; idx++)
	{
		auto num = 0;
		auto index = 0;
		for (int idy = 3; idy >= 0; idy--)
		{
			auto grid = card[idx][idy];
			if (grid->getNumber() == 0) continue;
			if (num == 0)
			{
				num = grid->getNumber();
				index = idy;
				continue;
			}
			if (num == grid->getNumber())
			{
				return false;
			}
			num = grid->getNumber();
			index = idy;
		}
	}

	for (int idy = 0; idy < 4; idy++)
	{
		auto num = 0;
		auto index = 0;
		for (int idx = 0; idx < 4; idx++)
		{
			auto grid = card[idx][idy];
			if (grid->getNumber() == 0) continue;
			if (num == 0)
			{
				num = grid->getNumber();
				index = idx;
				continue;
			}
			if (num == grid->getNumber())
			{
				return false;
			}
			num = grid->getNumber();
			index = idx;
		}
	}

	return true;
}