/*
ProjectName: 2048
Author: ÂíÈýÐ¡»ï¶ù
Blog: http://www.cnblogs.com/msxh/
Github:https://github.com/XINCGer
Date: 2016/08/11
*/

#ifndef __GAMEOVERSENCE_H_
#define __GAMEOVERSENCE_H_

#include "cocos2d.h"
USING_NS_CC;

class GameOverScene :public Layer{
public:
	static Scene *createScene();
	virtual bool init();
	CREATE_FUNC(GameOverScene);
};
#endif