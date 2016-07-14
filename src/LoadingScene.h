#pragma once
#include "cocos2d.h"
#include "GameDefine.h"
#include "GameScene.h" 

USING_NS_CC;

class LoadingScene : Layer
{
public:
	bool init();
	CREATE_FUNC(LoadingScene);
	static Scene * createScene();

	void gotoStartScene();

private:
	Label * _lblLoading;
};

