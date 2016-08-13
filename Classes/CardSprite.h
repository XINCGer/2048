/*
ProjectName: 2048
Author: 马三小伙儿
Blog: http://www.cnblogs.com/msxh/
Github:https://github.com/XINCGer
Date: 2016/08/03
*/
#ifndef __CARDSPRITE_H__
#define __CARDSPRITE_H__
#include "cocos2d.h"
USING_NS_CC;
#define CARD_BORDER 4

class CardSprite :public Sprite{
public:
	int number;  //卡片中的数值
	int getNumber();   //获取卡片中的数值
	void setNumber(int num);  //设置卡片中的数值
	Label* labelNumber;		//用来显示数值的标签
	LayerColor* layerColorBG;	//卡片的背景颜色
	static CardSprite* createCardSprite(int number, int size, float x, float y);  //创建卡片的静态方法
	void enemyInit(int number, int size, float x, float y);  //卡片的初始化函数
	virtual bool init();
	CREATE_FUNC(CardSprite);
};
#endif