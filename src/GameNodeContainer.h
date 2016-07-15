#pragma once
#include "cocos2d.h"
#include "GameDefine.h"
#include "GridNode.h" 
#include "GameScene.h"
#include "GameScoreLayer.h"

USING_NS_CC;

//װ���ӵ�����������������߼���д��������
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

	//���������Χ�ĸ���
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

