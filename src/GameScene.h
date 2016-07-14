#pragma once
#include "cocos2d.h"
#include "GameDefine.h"
#include "GridNode.h" 
#include "SimpleButton.h"
#include "GameBackgroundLayer.h"
#include "GameNodeContainer.h"
#include "GameOverLayer.h"
#include "GameScoreLayer.h"
#include "GamePauseLayer.h"

USING_NS_CC;

class GameScene : Layer
{
public:
	bool init();
	CREATE_FUNC(GameScene);
	static Scene * createScene();

	void restart();
	void gameOver();
	void exitGame();
	void pauseGame();
	void backGame();
};

