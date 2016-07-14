#pragma once
#include "cocos2d.h"
#include "GameDefine.h"
#include "Hexagon.h" 
#include "SimpleButton.h"
#include "GameScene.h"

USING_NS_CC;

class gamePauseLayer : public Layer
{
public:
	bool init();

	CREATE_FUNC(gamePauseLayer);
private:
	void onClickRestart();
	void onClickExit();
	void onClickBack();
};

