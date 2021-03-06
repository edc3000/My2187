#include "GameSceneTimeLimited.h"
#include "SimpleAudioEngine.h"

using namespace CocosDenshion;

bool GameSceneTimeLimited::init(){

	GameScene::init();

	this->setAnchorPoint(Point::ANCHOR_BOTTOM_LEFT);
	this->setPosition(Point::ZERO);

	auto bgTimer = Hexagon::create(60, BG_COLOR_4F);
	bgTimer->setPosition(100, VISIBLE_SIZE.height - 100);
	this->addChild(bgTimer);

	auto bgTimer2 = Hexagon::create(50, BG_COLOR_27);
	bgTimer2->setPosition(100, VISIBLE_SIZE.height - 100);
	this->addChild(bgTimer2);

	setLeftTime(60);
	_timer = Label::createWithSystemFont("60", "����", 36);
	_timer->setPosition(100, VISIBLE_SIZE.height - 100);
	this->addChild(_timer);
	auto lblTimerTitle = Label::createWithSystemFont("Time", "����", 20);
	lblTimerTitle->setPosition(_timer->getPositionX(), _timer->getPositionY() + 30);
	this->addChild(lblTimerTitle);

	schedule(schedule_selector(GameSceneTimeLimited::updateLeftTime), 0.5f);

	return true;
}


Scene * GameSceneTimeLimited::createScene(){
	auto scene = Scene::create();
	auto layer = GameSceneTimeLimited::create();
	scene->addChild(layer);
	return scene;
}

void GameSceneTimeLimited::updateLeftTime(float f)
{
	_leftTime -= f;

	if (_leftTime <= 0) {
		_leftTime = 0;
		gameOver();
	}
	_timer->setString(StringUtils::format("%.1f", _leftTime));
}

void GameSceneTimeLimited::setLeftTime(float t)
{
	_leftTime = t;
}

void GameSceneTimeLimited::restart()
{
	GameScene::restart();
	setLeftTime(60);
	_timer->setString(StringUtils::format("%.1f", _leftTime));
	schedule(schedule_selector(GameSceneTimeLimited::updateLeftTime), 0.5f);
}

void GameSceneTimeLimited::gameOver()
{
	GameScene::gameOver();
	unschedule(schedule_selector(GameSceneTimeLimited::updateLeftTime));
}

void GameSceneTimeLimited::exitGame()
{
	GameScene::exitGame();
}

void GameSceneTimeLimited::pauseGame()
{
	GameScene::pauseGame();
	unschedule(schedule_selector(GameSceneTimeLimited::updateLeftTime));
}

void GameSceneTimeLimited::backGame()
{
	GameScene::backGame();
	schedule(schedule_selector(GameSceneTimeLimited::updateLeftTime), 0.5f);
}
