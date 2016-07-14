#pragma once
#include "cocos2d.h"
#include "GameDefine.h"
#include "Hexagon.h"
#include "GameHelper.h"

USING_NS_CC;

enum GridState{
	//û��ѡ��
	NORMAL,
	//ѡ��
	SELECTED,
	//����չ
	EXTENDED
};

//�������εĸ��ӣ���������������һ����������Σ��м���һ������
class GridNode : public Node
{
public:
	GridNode(void);
	~GridNode(void);

	bool init();
	CREATE_FUNC(GridNode);

	void updateNum(int num);

	//���ø��ӵ�λ��
	void setRowAndCol(int row, int col);
	//�ƶ���ĳ��λ�ã��ж���
	void moveTo(int row, int col);

	//���ø��ӵ�״̬�������GridState
	void changeState(GridState state);
	void stateNormal();
	void stateSelected();
	void stateExtended();

	//�������ײ��⣬����ʵ�ֵ����
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

 