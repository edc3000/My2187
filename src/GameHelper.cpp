#include "GameHelper.h"

static GameHelper * _instance = nullptr; 

int numArr[] = {1, 3, 9, 27, 81, 243, 729, 2187};
Color4F colorArr[] = {BG_COLOR_1, BG_COLOR_3, BG_COLOR_9, BG_COLOR_27, BG_COLOR_81, BG_COLOR_243, BG_COLOR_729, BG_COLOR_2187};
Color4B fontArr[] = {Color4B::BLACK, Color4B::BLACK, Color4B::BLACK, Color4B::BLACK,Color4B::BLACK, Color4B::WHITE, Color4B::WHITE, Color4B::WHITE};
int fontSizeArr[] = {60, 60, 60, 60, 60, 40, 40, 30};
int randomNumber[3] = {1, 3, 9};

GameHelper * GameHelper::getInstance(){
	if(!_instance){
		_instance = new GameHelper();
	}

	return _instance;
}

Color4F GameHelper::getColorByNum(int num){
	for(int i = 0; i < NUM_COUNT; i++){
		if(numArr[i] == num){
			return colorArr[i];
		}
	}

	return colorArr[0];
}

Color4B GameHelper::getFontColorByNum(int num){
	for(int i = 0; i < NUM_COUNT; i++){
		if(numArr[i] == num){
			return fontArr[i];
		}
	}

	return fontArr[0];
}

int GameHelper::getFontSizeByNum(int num){
	for(int i = 0; i < NUM_COUNT; i++){
		if(numArr[i] == num){
			return fontSizeArr[i];
		}
	}

	return fontSizeArr[0];
}

int GameHelper::getRandomNum(){
	return randomNumber[rand() % 3];
}