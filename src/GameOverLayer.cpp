#include "GameOverLayer.h"

bool GameOverLayer::init(){
	if(!Layer::init()){ 
		return false;
	}

	auto bg = LayerColor::create(Color4B(0, 0, 0, 200), VISIBLE_SIZE.width, VISIBLE_SIZE.height);
	bg->setPosition(VISIBLE_SIZE.width / -2, VISIBLE_SIZE.height / -2);
	this->addChild(bg);

	auto restartButton = SimpleButton::create(80, "Restart", "ºÚÌå", 40, CC_CALLBACK_0(GameOverLayer::onClickRestart, this));
	restartButton->setPosition(0, VISIBLE_SIZE.height / 5);
	this->addChild(restartButton);

	auto exitButton = SimpleButton::create(80, "Exit", "ºÚÌå", 40, CC_CALLBACK_0(GameOverLayer::onClickExit, this));
	exitButton->setPosition(0, -VISIBLE_SIZE.height / 5);
	this->addChild(exitButton);

	this->setAnchorPoint(Point::ANCHOR_MIDDLE);

	return true;
}

void GameOverLayer::onClickRestart(){
	((GameScene *)this->getParent())->restart();
	this->removeFromParent();
}

void GameOverLayer::onClickExit()
{
	((GameScene *)this->getParent())->ExitGame();
	this->removeFromParent();
}
