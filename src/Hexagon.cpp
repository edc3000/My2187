#include "Hexagon.h"
 
//正六边形的6个顶点
static int pointConfig[][2] = {{1, 1}, {2, 0}, {1, -1}, {-1, -1}, {-2, 0}, {-1, 1}};

Hexagon::Hexagon(int sideLen, const Color4F & color)
{
	_sideLen = sideLen;
	_color = color;
}


Hexagon::~Hexagon(void)
{
}

bool Hexagon::init(){
	if(!Node::init()){
		return false;
	}

	_drawNode = DrawNode::create();
	this->addChild(_drawNode);
	refreshView();
	return true;
}

void Hexagon::updateSideLen(int sideLen){
	_sideLen = sideLen;
	refreshView();
}

void Hexagon::updateBgColor(const Color4F & bgColor){
	_color = bgColor;
	refreshView();
}

void Hexagon::refreshView(){
	float halfSideLen = _sideLen / 2;
	//这个是垂直方向的直角边，用来计算y坐标
	float rightAngleSideLen = 2 * halfSideLen * COS_30;
	for(int i = 0; i < SIDE_COUNT; i++){
		_pos[i] = Point(pointConfig[i][0] * halfSideLen, pointConfig[i][1] * rightAngleSideLen);
	}
	_drawNode->clear();
	_drawNode->drawSolidPoly(_pos, SIDE_COUNT, _color);
}

Hexagon * Hexagon::create(int sideLen, const Color4F & color){
	auto hexagon = new Hexagon(sideLen, color);
	if(hexagon && hexagon->init()){
		hexagon->autorelease();
	}else{
		delete hexagon;
		hexagon = NULL;
	}

	return hexagon;
}

Point * Hexagon::getPos(){
	return _pos;
}

//射线法检测点是否落在凸多边形内
bool Hexagon::hitCheckPoint(const Point & pt){
	int count = 0;
	for(int i = 0; i < SIDE_COUNT; i++){
		Point p1 = _pos[i];
		Point p2 = _pos[(i + 1) % SIDE_COUNT];
		if(p1.y == pt.y && p2.y == pt. y){
			continue;
		}
		if(pt.y < MIN(p1.y, p2.y)){
			continue;
		}
		if(pt.y >= MAX(p1.y, p2.y)){
			continue;
		}

		double x = (double)(pt.y - p1.y) * (double)(p2.x - p1.x) / (double)(p2.y - p1.y) + p1.x;
		if(x > pt.x){
			count++;
		}
	}

	return count % 2 == 1;
}