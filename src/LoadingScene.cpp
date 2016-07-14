#include "LoadingScene.h"

bool LoadingScene::init(){ 
	if(!Layer::init()){
		return false;
	}

	//画一个纯色的背景
	auto layerColor = LayerColor::create(Color4B(204, 204, 204, 255), VISIBLE_SIZE.width, VISIBLE_SIZE.height);
	layerColor->setPosition(Point::ZERO);
	this->addChild(layerColor);

	//屏幕中间的“loading”(Flash中的TextField）
	_lblLoading = Label::createWithSystemFont("Loading...", "黑体", 20);
	_lblLoading->setPosition(Point(VISIBLE_SIZE.width / 2, VISIBLE_SIZE.height / 2));
	_lblLoading->setTextColor(Color4B(0, 0, 0, 255));
	this->addChild(_lblLoading, 1);

	//启动一个0.5秒的调度（Flash中可以用Timer来实现）
	this->scheduleOnce(CC_CALLBACK_0(LoadingScene::showStartGameButton, this), 0.5, "showStartGameButton");

	return true;
}

Scene * LoadingScene::createScene(){
	auto scene = Scene::create();
	auto layer = LoadingScene::create();
	scene->addChild(layer);
	return scene;
}

void LoadingScene::showStartGameButton(){
	this->removeChild(_lblLoading);

	auto button = SimpleButton::create(60, "Start", "黑体", 20, CC_CALLBACK_0(LoadingScene::gotoStartScene, this));
	button->setPosition(VISIBLE_SIZE.width / 2, VISIBLE_SIZE.height / 2);
	this->addChild(button);
}

void LoadingScene::gotoStartScene(){
	//切屏，从右边滑动进入
	Director::getInstance()->replaceScene(TransitionSlideInR::create(0.5, GameScene::createScene()));
}
