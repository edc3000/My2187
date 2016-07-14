#pragma once
#include "cocos2d.h"

USING_NS_CC;

class GameScene : Layer
{
public:
	bool init();
	CREATE_FUNC(GameScene);
	static Scene * createScene();

};

