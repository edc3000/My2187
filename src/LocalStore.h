#pragma once
#include "cocos2d.h"

USING_NS_CC;
 
//´æ´¢Êý¾Ý
class LocalStore
{
public:
	static LocalStore * getInstance();

	int getHighScore();
	void setHighScore(int);
};

