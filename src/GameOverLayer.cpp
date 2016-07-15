#include "GameOverLayer.h"
#include "LoadingScene.h"
#include "SimpleAudioEngine.h"

using namespace CocosDenshion;

bool GameOverLayer::init(){
	if(!Layer::init()){ 
		return false;
	}

	auto bg = LayerColor::create(Color4B(0, 0, 0, 200), VISIBLE_SIZE.width, VISIBLE_SIZE.height);
	bg->setPosition(VISIBLE_SIZE.width / -2, VISIBLE_SIZE.height / -2);
	this->addChild(bg);

	auto restartButton = SimpleButton::create(80, "Restart", "ºÚÌå", 40, CC_CALLBACK_0(GameOverLayer::onClickRestart, this));
	restartButton->setPosition(0, VISIBLE_SIZE.height / 8);
	this->addChild(restartButton);

	auto exitButton = SimpleButton::create(80, "Exit", "ºÚÌå", 40, CC_CALLBACK_0(GameOverLayer::onClickExit, this));
	exitButton->setPosition(VISIBLE_SIZE.width / 4, -VISIBLE_SIZE.height / 8);
	this->addChild(exitButton);

	auto menuButton = SimpleButton::create(80, "Menu", "ºÚÌå", 40, CC_CALLBACK_0(GameOverLayer::onClickMenu, this));
	menuButton->setPosition(-VISIBLE_SIZE.width / 4, -VISIBLE_SIZE.height / 8);
	this->addChild(menuButton);

	this->setAnchorPoint(Point::ANCHOR_MIDDLE);

	return true;
}

void GameOverLayer::onClickRestart(){
	((GameScene *)this->getParent())->restart();
	SimpleAudioEngine::getInstance()->playEffect("replaceScene.mp3");
	this->removeFromParent();
}

void GameOverLayer::onClickExit()
{
	((GameScene *)this->getParent())->exitGame();
	this->removeFromParent();
}

void GameOverLayer::onClickMenu()
{
	SimpleAudioEngine::getInstance()->playEffect("replaceScene.mp3");
	Director::getInstance()->replaceScene(TransitionSlideInL::create(0.5, LoadingScene::createScene()));
}
