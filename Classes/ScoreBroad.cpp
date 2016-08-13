/*
ProjectName: 2048
Author: 马三小伙儿
Blog: http://www.cnblogs.com/msxh/
Github:https://github.com/XINCGer
Date: 2016/08/09
*/

#include "ScoreBroad.h"

ScoreBroad* ScoreBroad::createScoreBroad(int score, int width, int height, const char*title, int type, float x, float y){
	//套用二段构建设计模式（套用模版）
	ScoreBroad *enemy = new ScoreBroad();
	if (enemy&&enemy->init()){
		enemy->autorelease();
		enemy->enemyInit(score, width, height, title, type, x, y);
		return enemy;
	}
	CC_SAFE_DELETE(enemy);
	return NULL;
}

bool ScoreBroad::init(){
	if (!Layer::init()){
		return false;
	}
	return true;
}

void ScoreBroad::enemyInit(int score, int width, int height, const char*title, int type, float x, float y){
	this->type = type;
	this->score = score;
	if (type == 1){		//判断是哪一类记分牌
		background = LayerColor::create(Color4B(2, 168, 209, 255), width, height);
		background->setPosition(x, y);
		addChild(background);
		scoreLabel = Label::create(String::createWithFormat("%d", score)->getCString(),"Arial",40);
		scoreLabel->setPosition(width / 2, height / 2);
		background->addChild(scoreLabel);
	}
	else{
		background = LayerColor::create(Color4B(215, 224, 223, 255), width, height);
		background->setPosition(x, y);
		addChild(background);
		auto *label = Label::create(title, "Arial", 26);
		label->setPosition(width / 2, height-20);
		background->addChild(label);
		scoreLabel = Label::create(String::createWithFormat("%d", score)->getCString(), "Arial", 34);
		scoreLabel->setPosition(width / 2, 30);
		background->addChild(scoreLabel);
	}
}

void ScoreBroad::setScore(int number){		//修改记分牌的分数
	this->score = number;
	scoreLabel->setString(String::createWithFormat("%d", number)->getCString());
}

int ScoreBroad::getScore(){		//获取记分牌显示的分数
	return this->score;
}
