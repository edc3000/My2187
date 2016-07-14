#pragma once
#include "cocos2d.h"
#include "GameDefine.h"
#include "Hexagon.h"
#include "GameHelper.h"

USING_NS_CC;

enum GridState{
	//没有选中
	NORMAL,
	//选中
	SELECTED,
	//被扩展
	EXTENDED
};

//正六边形的格子，背景是两个叠在一起的正六边形，中间是一个数字
class GridNode : public Node
{
public:
	GridNode(void);
	~GridNode(void);

	bool init();
	CREATE_FUNC(GridNode);

	void updateNum(int num);

	//设置格子的位置
	void setRowAndCol(int row, int col);
	//移动到某个位置，有动画
	void moveTo(int row, int col);

	//设置格子的状态，具体见GridState
	void changeState(GridState state);
	void stateNormal();
	void stateSelected();
	void stateExtended();

	//检测点的碰撞检测，用来实现点击的
	bool hitCheckPoint(const Point & pt);
	GridState getCurState();

	int getNum();
	int getRow();
	int getCol();
private:
	int _num;
	int _row;
	int _col;

	Label * _lblNum;
	Hexagon * _bg1;
	Hexagon * _bg2;

	GridState _currentState;


	void refreshView();
	Point getPositionByRowAndCol(int row, int col);
	void afterMoveToMovie();

};

 