#pragma once
#include "cocos2d.h"
#include "GameDefine.h" 

USING_NS_CC;

#define SIDE_COUNT		6

//�������Σ���0,0����ͼ�����м�
class Hexagon : public Node
{
public:

	Hexagon(int sideLen, const Color4F & bgColor);
	~Hexagon(void);

	bool init();
	void updateSideLen(int sideLen);
	void updateBgColor(const Color4F & bgColor);

	//��ȡ�������εĸ�����������
	Point * getPos();

	//�ж���⣬���߷������Ƿ�����͹�������
	bool hitCheckPoint(const Point & pt);

	static Hexagon * create(int SideLen, const Color4F & bgColor);
private:
	//�߳�
	int _sideLen;
	Color4F _color;
	DrawNode * _drawNode;
	Point _pos[SIDE_COUNT];

	void refreshView();
};

