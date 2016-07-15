#pragma once
#include "cocos2d.h"
#include "Hexagon.h"
#include "GameDefine.h"
#include "LocalStore.h"

USING_NS_CC;

class GameScoreLayer : public Layer
{
public:
	bool init();
	CREATE_FUNC(GameScoreLayer);
	
	void showScore(int);
private:
	Label * _lblScore;
	Label * _lblMaxScore;
};