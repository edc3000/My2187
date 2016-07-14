#include "GameOverLayer.h"

bool GameOverLayer::init(){
	if(!Layer::init()){ 
		return false;
	}

	auto bg = LayerColor::create(Color4B(0, 0, 0, 200), VISIBLE_SIZE.width, VISIBLE_SIZE.height);
	bg->setPosition(VISIBLE_SIZE.width / -2, VISIBLE_SIZE.height / -2);
	this->addChild(bg);

	auto button = SimpleButton::create(80, "Restart", "ºÚÌå", 40, CC_CALLBACK_0(GameOverLayer::onClickRestart, this));
	this->addChild(button);

	this->setAnchorPoint(Point::ANCHOR_MIDDLE);

	return true;
}

void GameOverLayer::onClickRestart(){
	((GameScene *)this->getParent())->restart();
	this->getParent()->removeChild(this);
}