/*
ProjectName: 2048
Author: 马三小伙儿
Blog: http://www.cnblogs.com/msxh/
Github:https://github.com/XINCGer
Date: 2016/08/09
*/

#ifndef __SCOREBROAD_H__
#define __SCOREBROAD_H__
#include "cocos2d.h"
USING_NS_CC;
class ScoreBroad :public Layer{
public :
	int type;		//记分牌的类型，有两种
	int score;		//记分牌中的分数
	void setScore(int number);
	int getScore();
	Label* scoreLabel;
	LayerColor* background;		//背景颜色
	static ScoreBroad* createScoreBroad(int score, int width, int height, const char*title, int type, float x, float y);
	void enemyInit(int score, int width, int height, const char*title, int type, float x, float y);
	virtual bool init();
	CREATE_FUNC(ScoreBroad);
};
#endif