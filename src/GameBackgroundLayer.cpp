#include "GameBackgroundLayer.h"

bool GameBackgroundLayer::init(){
	if(!Node::init()){ 
		return false;
	}

	//�����е����б�Ե�㣬���һ��������
	int pointConfig[][2] = {
		{1, 5},   {2, 4},   {4, 4},   {5, 3},   {7, 3},   {8, 2},   {7, 1},  {8, 0},	//��һ����
		{7, -1},  {8, -2},  {7, -3},  {5, -3},  {4, -4},  {2, -4},  {1, -5},			//��������
		{-1, -5}, {-2, -4}, {-4, -4}, {-5, -3}, {-7, -3}, {-8, -2}, {-7, -1},			//��������
		{-8, 0},  {-7, 1},  {-8, 2},  {-7, 3},  {-5, 3},  {-4, 4},  {-2, 4}, {-1, 5}	//�ڶ�����
	};


	float halfSideLen = GRID_SIDE_LEN / 2;
	float rightAngleSideLen = GRID_SIDE_LEN * COS_30;
	Point pos[GAME_BG_POINT_COUNT];
	for(int i = 0; i < GAME_BG_POINT_COUNT; i++){
		pos[i] = Point(pointConfig[i][0] * halfSideLen, pointConfig[i][1] * rightAngleSideLen);
	}

	//��������ǲ���ֱ�ӻ��ģ���Ҫת����͹���β��ܻ�������ת����������
	auto drawNode = DrawNode::create();
	for(int i = 0; i < GAME_BG_POINT_COUNT - 1; i++){
		drawNode->drawTriangle(Point::ZERO, pos[i], pos[i + 1], BG_COLOR_4F);
	}
	drawNode->drawTriangle(Point::ZERO, pos[0], pos[GAME_BG_POINT_COUNT - 1], BG_COLOR_4F);

	//ê�㣬����Flash�����ע�����
	this->setAnchorPoint(Point::ANCHOR_MIDDLE);

	this->addChild(drawNode);

	return true;
}