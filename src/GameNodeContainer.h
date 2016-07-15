#pragma once
#include "cocos2d.h"
#include "GameDefine.h"
#include "GridNode.h" 
#include "GameScene.h"
#include "GameScoreLayer.h"

USING_NS_CC;

//装格子的容器，最后连格子逻辑都写在里面了
class GameNodeContainer : public Layer
{
public:
	void restart();
	void stopTouchEvent();
	void startTouchEvent();
	void setScoreLayer(GameScoreLayer * scoreLayer);
	bool init();
	CREATE_FUNC(GameNodeContainer);
private:
	bool isExceptNode(int row, int col);

	void clearGridState();
	void addNewGrid(int row, int col);
	void resetSearchGrids();
	bool onClickGridContainer(Touch * tou, Event * evt);
	void updateScore(int score);

	//广度搜索周围的格子
	Vector<GridNode *> searchSameGrids(GridNode * node);
	void composeBiggerGrid(GridNode * node);
	void extendSameNumGrid(GridNode * node);
	bool isGameOver();

	GridNode * _listNode[5][5];

	Vector<GridNode *> _resultGrids;
	EventListenerTouchOneByOne * _eventListener;
	int _score;
	GameScoreLayer * _scoreLayer;
};

