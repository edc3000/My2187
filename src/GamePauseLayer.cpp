#include "GamePauseLayer.h"
#include "LoadingScene.h"
#include "SimpleAudioEngine.h"

using namespace CocosDenshion;

bool GamePauseLayer::init(){
	if (!Layer::init()){
		return false;
	}

	auto bg = LayerColor::create(Color4B(0, 0, 0, 200), VISIBLE_SIZE.width, VISIBLE_SIZE.height);
	bg->setPosition(VISIBLE_SIZE.width / -2, VISIBLE_SIZE.height / -2);
	this->addChild(bg);

	auto backButton = SimpleButton::create(80, "Back", "黑体", 40, CC_CALLBACK_0(GamePauseLayer::onClickBack, this));
	backButton->setPosition(-VISIBLE_SIZE.width / 4, VISIBLE_SIZE.height / 8);
	this->addChild(backButton);

	auto menuButton = SimpleButton::create(80, "Menu", "黑体", 40, CC_CALLBACK_0(GamePauseLayer::onClickMenu, this));
	menuButton->setPosition(VISIBLE_SIZE.width / 4, VISIBLE_SIZE.height / 8);
	this->addChild(menuButton);

	auto restartButton = SimpleButton::create(80, "Restart", "黑体", 40, CC_CALLBACK_0(GamePauseLayer::onClickRestart, this));
	restartButton->setPosition(-VISIBLE_SIZE.width / 4, -VISIBLE_SIZE.height / 8);
	this->addChild(restartButton);

	auto exitButton = SimpleButton::create(80, "Exit", "黑体", 40, CC_CALLBACK_0(GamePauseLayer::onClickExit, this));
	exitButton->setPosition(VISIBLE_SIZE.width / 4, -VISIBLE_SIZE.height / 8);
	this->addChild(exitButton);

	this->setAnchorPoint(Point::ANCHOR_MIDDLE);

	return true;
}

void GamePauseLayer::onClickRestart(){
	((GameScene *)this->getParent())->restart();
	SimpleAudioEngine::getInstance()->playEffect("replaceScene.mp3");
	this->removeFromParent();
}

void GamePauseLayer::onClickExit()
{
	((GameScene *)this->getParent())->exitGame();
	this->removeFromParent();
}

void GamePauseLayer::onClickBack()
{
	((GameScene *)this->getParent())->backGame();
	this->removeFromParent();
}

void GamePauseLayer::onClickMenu()
{
	SimpleAudioEngine::getInstance()->playEffect("replaceScene.mp3");
	Director::getInstance()->replaceScene(TransitionSlideInL::create(0.5, LoadingScene::createScene()));
}
