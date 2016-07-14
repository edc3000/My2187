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
