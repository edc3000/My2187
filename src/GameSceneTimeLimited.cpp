#include "GameSceneTimeLimited.h"

bool GameSceneTimeLimited::init(){

	__super::init();

	this->setAnchorPoint(Point::ANCHOR_BOTTOM_LEFT);
	this->setPosition(Point::ZERO);

	auto bgTimer = Hexagon::create(60, BG_COLOR_4F);
	bgTimer->setPosition(100, VISIBLE_SIZE.height - 100);
	this->addChild(bgTimer);

	auto bgTimer2 = Hexagon::create(50, BG_COLOR_27);
	bgTimer2->setPosition(100, VISIBLE_SIZE.height - 100);
	this->addChild(bgTimer2);

	setLeftTime(60);
	_timer = Label::createWithSystemFont("60", "ºÚÌå", 36);
	_timer->setPosition(100, VISIBLE_SIZE.height - 100);
	this->addChild(_timer);
	auto lblTimerTitle = Label::createWithSystemFont("Time", "ºÚÌå", 20);
	lblTimerTitle->setPosition(_timer->getPositionX(), _timer->getPositionY() + 30);
	this->addChild(lblTimerTitle);

	schedule(schedule_selector(GameSceneTimeLimited::updateLeftTime));

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
	__super::restart();
	setLeftTime(60);
	_timer->setString(StringUtils::format("%.1f", _leftTime));
	schedule(schedule_selector(GameSceneTimeLimited::updateLeftTime));
	log("time limited scene restart");
}

void GameSceneTimeLimited::gameOver()
{
	__super::gameOver();
	unschedule(schedule_selector(GameSceneTimeLimited::updateLeftTime));
	log("time limited scene");
}

void GameSceneTimeLimited::exitGame()
{
	__super::exitGame();
	log("time limited scene");
}

void GameSceneTimeLimited::pauseGame()
{
	__super::pauseGame();
	unschedule(schedule_selector(GameSceneTimeLimited::updateLeftTime));
	log("time limited scene");
}

void GameSceneTimeLimited::backGame()
{
	__super::backGame();
	schedule(schedule_selector(GameSceneTimeLimited::updateLeftTime));
	log("time limited scene");
}
