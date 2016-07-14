#include "GameScoreLayer.h"

bool GameScoreLayer::init(){ 
	if(!Layer::init()){
		return false;
	}

	this->setAnchorPoint(Point::ANCHOR_BOTTOM_LEFT);
	this->setPosition(Point::ZERO);
	
	auto bgScore = Hexagon::create(60, BG_COLOR_4F);
	bgScore->setPosition(VISIBLE_SIZE.width - 120, VISIBLE_SIZE.height - 100);
	this->addChild(bgScore);
	auto bgMaxScore = Hexagon::create(60, BG_COLOR_4F);
	bgMaxScore->setPosition(VISIBLE_SIZE.width - 60, VISIBLE_SIZE.height - 160);
	this->addChild(bgMaxScore);

	auto bgScore2 = Hexagon::create(50, BG_COLOR_27);
	bgScore2->setPosition(VISIBLE_SIZE.width - 120, VISIBLE_SIZE.height - 100);
	this->addChild(bgScore2);
	auto bgMaxScore2 = Hexagon::create(50, BG_COLOR_27);
	bgMaxScore2->setPosition(VISIBLE_SIZE.width - 60, VISIBLE_SIZE.height - 160);
	this->addChild(bgMaxScore2);


	_lblScore = Label::createWithSystemFont("0", "黑体", 36);
	_lblScore->setPosition(VISIBLE_SIZE.width - 120, VISIBLE_SIZE.height - 100);
	this->addChild(_lblScore);
	auto lblScoreTitle = Label::createWithSystemFont("SCORE", "黑体", 20);
	lblScoreTitle->setPosition(_lblScore->getPositionX(), _lblScore->getPositionY() + 30);
	this->addChild(lblScoreTitle);

	_lblMaxScore = Label::createWithSystemFont(StringUtils::format("%d", LocalStore::getInstance()->getHighScore()), "黑体", 36);
	_lblMaxScore->setPosition(VISIBLE_SIZE.width - 60, VISIBLE_SIZE.height - 160);
	this->addChild(_lblMaxScore);
	auto lblMaxScoreTitle = Label::createWithSystemFont("BEST", "黑体", 20);
	lblMaxScoreTitle->setPosition(_lblMaxScore->getPositionX(), _lblMaxScore->getPositionY() + 30);
	this->addChild(lblMaxScoreTitle);

	return true;
}

void GameScoreLayer::showScore(int score){
	_lblScore->setString(StringUtils::format("%d",score));
	if(score > LocalStore::getInstance()->getHighScore()){
		LocalStore::getInstance()->setHighScore(score);
		_lblMaxScore->setString(StringUtils::format("%d",score));
	}
}