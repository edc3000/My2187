#pragma once
#include "cocos2d.h"

USING_NS_CC;
 
//�洢����
class LocalStore
{
public:
	static LocalStore * getInstance();

	int getHighScore();
	void setHighScore(int);
};

