#include "GamePauseLayer.h"

bool gamePauseLayer::init(){
	if (!Layer::init()){
		return false;
	}

	auto bg = LayerColor::create(Color4B(0, 0, 0, 200), VISIBLE_SIZE.width, VISIBLE_SIZE.height);
	bg->setPosition(VISIBLE_SIZE.width / -2, VISIBLE_SIZE.height / -2);
	this->addChild(bg);

	auto restartButton = SimpleButton::create(80, "Restart", "ºÚÌå", 40, CC_CALLBACK_0(gamePauseLayer::onClickRestart, this));
	restartButton->setPosition(0, VISIBLE_SIZE.height / 8);
	this->addChild(restartButton);

	auto backButton = SimpleButton::create(80, "Back", "ºÚÌå", 40, CC_CALLBACK_0(gamePauseLayer::onClickBack, this));
	backButton->setPosition(-VISIBLE_SIZE.width / 4, -VISIBLE_SIZE.height / 8);
	this->addChild(backButton);

	auto exitButton = SimpleButton::create(80, "Exit", "ºÚÌå", 40, CC_CALLBACK_0(gamePauseLayer::onClickExit, this));
	exitButton->setPosition(VISIBLE_SIZE.width / 4, -VISIBLE_SIZE.height / 8);
	this->addChild(exitButton);

	this->setAnchorPoint(Point::ANCHOR_MIDDLE);

	return true;
}

void gamePauseLayer::onClickRestart(){
	((GameScene *)this->getParent())->restart();
	this->removeFromParent();
}

void gamePauseLayer::onClickExit()
{
	((GameScene *)this->getParent())->exitGame();
	this->removeFromParent();
}

void gamePauseLayer::onClickBack()
{
	((GameScene *)this->getParent())->backGame();
	this->removeFromParent();
}
