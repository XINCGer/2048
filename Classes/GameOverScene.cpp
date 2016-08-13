/*
ProjectName: 2048
Author: 马三小伙儿
Blog: http://www.cnblogs.com/msxh/
Github:https://github.com/XINCGer
Date: 2016/08/11
*/
#include "GameOverScene.h"
#include "HelloWorldScene.h"
#include "ui\CocosGUI.h"
USING_NS_CC;
using namespace ui;

Scene* GameOverScene::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = GameOverScene::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

bool GameOverScene::init(){
	if (!Layer::init()){
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();

	auto* bgLabel = LayerColor::create(Color4B(255, 255, 255, 255));
	auto *overTip = Sprite::create("gameover.png");
	overTip->setPosition(visibleSize.width / 2, visibleSize.height*0.7);
	overTip->setScale(0.6);
	auto *ReStartBtn = Button::create("button_regame.png");
	ReStartBtn->setPosition(Vec2(visibleSize.width*0.3, visibleSize.height*0.4));
	ReStartBtn->addTouchEventListener([](Ref* pSender, Widget::TouchEventType type){
		if (type == Widget::TouchEventType::ENDED){
			//切换到HelloWorld场景
			auto transtion = TransitionTurnOffTiles::create(1.0, HelloWorld::createScene());
			//auto transtion = TransitionSlideInL::create(2.0, HelloWorld::createScene());
			Director::getInstance()->replaceScene(transtion);
		}
	});
	auto* exitBtn = Button::create("button_no.png");
	exitBtn->addTouchEventListener([](Ref *pSender, Widget::TouchEventType type){
		if (type == Widget::TouchEventType::ENDED){
			Director::getInstance()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
			MessageBox("您将退出游戏！", "提示信息");
			exit(0);
#endif

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
			exit(0);
#endif

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
			exit(0);
#endif
		}
	});
	exitBtn->setPosition(Vec2(visibleSize.width*0.7, visibleSize.height*0.4));
	addChild(bgLabel);
	addChild(overTip);
	addChild(ReStartBtn);
	addChild(exitBtn);
	return true;
}