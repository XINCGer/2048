/*
ProjectName: 2048
Author: 马三小伙儿
Blog: http://www.cnblogs.com/msxh/
Github:https://github.com/XINCGer
Date: 2016/08/03
*/
#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "CardSprite.h"
#include "ScoreBroad.h"
#include "GameOverScene.h"

USING_NS_CC;

class HelloWorld : public cocos2d::Layer
{
public:
	// 最高纪录
	int record;
	// 当前分数
	int score;
	// 目标数字
	int demo;
	float x;
	float y;
	bool isLock;
	bool isPlay;		//判定是否播放音效
	CardSprite* card[4][4];
	// 目标
	ScoreBroad* broad1;
	// 最高纪录
	ScoreBroad* broad2;
	// 总分
	ScoreBroad* broad3;
	
	bool doUp();
	bool doDown();
	bool doLeft();
	bool doRight();
	void createCard();
	void scoreAddUp(ScoreBroad* broad, int number);
	void refreshBroad(int x);
	bool isGameOver();	//判断游戏是否结束
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
	virtual bool onTouchBegan(Touch *touch, Event *event);
	virtual void onTouchMoved(Touch *touch, Event *event);
	virtual void onTouchEnded(Touch *touch, Event *event);

    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
};

#endif // __HELLOWORLD_SCENE_H__
