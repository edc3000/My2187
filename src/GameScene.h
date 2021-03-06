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

class GameScene : public Layer
{
public:
	bool init();
	CREATE_FUNC(GameScene);
	static Scene * createScene();

	virtual void restart();
	virtual void gameOver();
	virtual void exitGame();
	virtual void pauseGame();
	virtual void backGame();
private:
	SimpleButton* _pause;
};

