#include "GameBackgroundLayer.h"

bool GameBackgroundLayer::init(){
	if(!Node::init()){ 
		return false;
	}

	//背景中的所有边缘点，组成一个凹边形
	int pointConfig[][2] = {
		{1, 5},   {2, 4},   {4, 4},   {5, 3},   {7, 3},   {8, 2},   {7, 1},  {8, 0},	//第一象限
		{7, -1},  {8, -2},  {7, -3},  {5, -3},  {4, -4},  {2, -4},  {1, -5},			//第四象限
		{-1, -5}, {-2, -4}, {-4, -4}, {-5, -3}, {-7, -3}, {-8, -2}, {-7, -1},			//第三象限
		{-8, 0},  {-7, 1},  {-8, 2},  {-7, 3},  {-5, 3},  {-4, 4},  {-2, 4}, {-1, 5}	//第二象限
	};


	float halfSideLen = GRID_SIDE_LEN / 2;
	float rightAngleSideLen = GRID_SIDE_LEN * COS_30;
	Point pos[GAME_BG_POINT_COUNT];
	for(int i = 0; i < GAME_BG_POINT_COUNT; i++){
		pos[i] = Point(pointConfig[i][0] * halfSideLen, pointConfig[i][1] * rightAngleSideLen);
	}

	//凹多边形是不能直接画的，需要转换成凸边形才能画，这里转换成三角形
	auto drawNode = DrawNode::create();
	for(int i = 0; i < GAME_BG_POINT_COUNT - 1; i++){
		drawNode->drawTriangle(Point::ZERO, pos[i], pos[i + 1], BG_COLOR_4F);
	}
	drawNode->drawTriangle(Point::ZERO, pos[0], pos[GAME_BG_POINT_COUNT - 1], BG_COLOR_4F);

	//锚点，就是Flash里面的注册点啦
	this->setAnchorPoint(Point::ANCHOR_MIDDLE);

	this->addChild(drawNode);

	return true;
}