#include "LocalStore.h"

static LocalStore * _instance = nullptr;

LocalStore * LocalStore::getInstance(){
	if(!_instance){ 
		_instance = new LocalStore();
	}

	return _instance;
}

int LocalStore::getHighScore(){
	return UserDefault::getInstance()->getIntegerForKey("highScore");
}

void LocalStore::setHighScore(int score){
	UserDefault::getInstance()->setIntegerForKey("highScore", score);
}