#include "GameScene.h"

GameNodeContainer * container;
GameScoreLayer * scoreLayer; 

bool GameScene::init(){
	if(!Layer::init()){
		return false;
	}

	//��ɫ����
	auto layerColor = LayerColor::create(Color4B(204, 204, 204, 255), VISIBLE_SIZE.width, VISIBLE_SIZE.height);
	layerColor->setPosition(Point::ZERO);
	this->addChild(layerColor);

	//��Ϸ�ĸ��ӵı���
	auto bg = GameBackgroundLayer::create();
	bg->setPosition(VISIBLE_SIZE.width / 2, VISIBLE_SIZE.height / 2);
	bg->setScale(1.1f);
	this->addChild(bg);

	//����
	scoreLayer = GameScoreLayer::create();
	scoreLayer->setPosition(Point::ZERO);
	this->addChild(scoreLayer);

	//����
	container = GameNodeContainer::create();
	container->setPosition(VISIBLE_SIZE.width / 2, VISIBLE_SIZE.height / 2);
	container->setScoreLayer(scoreLayer);
	this->addChild(container);

	// ֱ�ӽ���������GameOverLayerר��
	auto result = SimpleButton::create(60, "Pause", "����", 30, CC_CALLBACK_0(GameScene::gameOver, this));
	result->setPosition(VISIBLE_SIZE.width - 60, 60);
	this->addChild(result);

	return true;
}

void GameScene::restart(){
	Director::getInstance()->getEventDispatcher()->resumeEventListenersForTarget(container);
	container->restart();
}

void GameScene::gameOver(){
	auto gameOverLayer = GameOverLayer::create();
	Director::getInstance()->getEventDispatcher()->pauseEventListenersForTarget(container);
	gameOverLayer->setPosition(VISIBLE_SIZE.width / 2, VISIBLE_SIZE.height / 2);
	this->addChild(gameOverLayer);
}

void GameScene::pauseGame(){
	auto gameOverLayer = GameOverLayer::create();
	Director::getInstance()->getEventDispatcher()->pauseEventListenersForTarget(container);
	gameOverLayer->setPosition(VISIBLE_SIZE.width / 2, VISIBLE_SIZE.height / 2);
	this->addChild(gameOverLayer);
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
