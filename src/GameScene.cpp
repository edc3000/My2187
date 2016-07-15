#include "GameScene.h"

GameNodeContainer * container;
GameScoreLayer * scoreLayer; 

bool GameScene::init(){
	if(!Layer::init()){
		return false;
	}

	//纯色背景
	auto layerColor = LayerColor::create(Color4B(204, 204, 204, 255), VISIBLE_SIZE.width, VISIBLE_SIZE.height);
	layerColor->setPosition(Point::ZERO);
	this->addChild(layerColor);

	//游戏的格子的背景
	auto bg = GameBackgroundLayer::create();
	bg->setPosition(VISIBLE_SIZE.width / 2, VISIBLE_SIZE.height / 2);
	bg->setScale(1.1f);
	this->addChild(bg);

	//分数
	scoreLayer = GameScoreLayer::create();
	scoreLayer->setPosition(Point::ZERO);
	this->addChild(scoreLayer);

	//格子
	container = GameNodeContainer::create();
	container->setPosition(VISIBLE_SIZE.width / 2, VISIBLE_SIZE.height / 2);
	container->setScoreLayer(scoreLayer);
	this->addChild(container);

	// 暂停按钮
	_pause = SimpleButton::create(60, "Pause", "黑体", 30, CC_CALLBACK_0(GameScene::pauseGame, this));
	_pause->setPosition(VISIBLE_SIZE.width - 60, 60);
	this->addChild(_pause);

	return true;
}

void GameScene::restart(){
	Director::getInstance()->getEventDispatcher()->resumeEventListenersForTarget(container);
	Director::getInstance()->getEventDispatcher()->resumeEventListenersForTarget(_pause);
	container->restart();
}

void GameScene::gameOver(){
	auto gameOverLayer = GameOverLayer::create();
	Director::getInstance()->getEventDispatcher()->pauseEventListenersForTarget(container);
	Director::getInstance()->getEventDispatcher()->pauseEventListenersForTarget(_pause);
	gameOverLayer->setPosition(VISIBLE_SIZE.width / 2, VISIBLE_SIZE.height / 2);
	this->addChild(gameOverLayer);
}

void GameScene::pauseGame(){
	auto gamePauseLayer = GamePauseLayer::create();
	Director::getInstance()->getEventDispatcher()->pauseEventListenersForTarget(container);
	Director::getInstance()->getEventDispatcher()->pauseEventListenersForTarget(_pause);
	gamePauseLayer->setPosition(VISIBLE_SIZE.width / 2, VISIBLE_SIZE.height / 2);
	this->addChild(gamePauseLayer);
}

void GameScene::backGame(){
	Director::getInstance()->getEventDispatcher()->resumeEventListenersForTarget(container);
	Director::getInstance()->getEventDispatcher()->resumeEventListenersForTarget(_pause);
}

Scene * GameScene::createScene(){
	auto scene = Scene::create();
	auto layer = GameScene::create();
	scene->addChild(layer);
	return scene;
}

void GameScene::exitGame()
{
	this->stopAllActions();
	Director::getInstance()->end();
}
