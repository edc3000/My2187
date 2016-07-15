#pragma once
#include "cocos2d.h"
#include "GameScene.h"

USING_NS_CC;

class GameSceneTimeLimited : GameScene
{
public:
	bool init();
	CREATE_FUNC(GameSceneTimeLimited);
	static Scene * createScene();

	void restart();
	void gameOver();
	void exitGame();
	void pauseGame();
	void backGame();

	void updateLeftTime(float f);
	void setLeftTime(float t);
	Label* _timer;
	float _leftTime;
};

