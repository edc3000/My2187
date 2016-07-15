#pragma once
#include "cocos2d.h"
#include "GameDefine.h" 

USING_NS_CC;

#define SIDE_COUNT		6

//正六边形，（0,0）在图形正中间
class Hexagon : public Node
{
public:

	Hexagon(int sideLen, const Color4F & bgColor);
	~Hexagon(void);

	bool init();
	void updateSideLen(int sideLen);
	void updateBgColor(const Color4F & bgColor);

	//获取正六边形的各个顶点坐标
	Point * getPos();

	//判定检测，射线法检测点是否落在凸多边形内
	bool hitCheckPoint(const Point & pt);

	static Hexagon * create(int SideLen, const Color4F & bgColor);
private:
	//边长
	int _sideLen;
	Color4F _color;
	DrawNode * _drawNode;
	Point _pos[SIDE_COUNT];

	void refreshView();
};

