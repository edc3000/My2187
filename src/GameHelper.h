#pragma once
#include "cocos2d.h"
#include "GameDefine.h" 

USING_NS_CC;

class GameHelper
{
public:
	Color4F getColorByNum(int num);
	Color4B getFontColorByNum(int num);
	int getFontSizeByNum(int num);
	int getRandomNum();

	static GameHelper * getInstance();
};

