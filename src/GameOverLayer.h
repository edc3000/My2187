#pragma once
#include "cocos2d.h"
#include "GameDefine.h"
#include "Hexagon.h" 
#include "SimpleButton.h"
#include "GameScene.h"

USING_NS_CC;

class GameOverLayer : public Layer
{
public:
	bool init();

	CREATE_FUNC(GameOverLayer);
private:
	void onClickRestart();
};

