#include "GridNode.h"

 
GridNode::GridNode(void)
{
}


GridNode::~GridNode(void)
{
}

bool GridNode::init(){
	if(!Node::init()){
		return false;
	}

	//两个正六边形叠在一起组成背景
	_bg1 = Hexagon::create(GRID_SIDE_LEN, BG_COLOR_1);
	_bg2 = Hexagon::create(GRID_SIDE_LEN, BG_COLOR_EXTENDED);
	this->addChild(_bg1, 2);
	this->addChild(_bg2, 1);

	//数字部分
	_lblNum = Label::createWithSystemFont(StringUtils::format("%d", _num), "黑体", 40);
	_lblNum->setTextColor(Color4B(0, 0, 0, 255));
	this->addChild(_lblNum, 3);
	
	//出现动画，慢慢放大
	this->setScale(0.01f);
	auto scaleTo = ScaleTo::create(0.5f, 1.0f);
	this->runAction(scaleTo);

	changeState(GridState::NORMAL);

	return true;
}

void GridNode::updateNum(int num){
	_num = num;
	refreshView();
}


void GridNode::setRowAndCol(int row, int col){
	_row = row;
	_col = col;
	this->setPosition(getPositionByRowAndCol(row, col));
}



Point GridNode::getPositionByRowAndCol(int row, int col){
	if(row % 2 == 0){
		return Point((row - DRAW_GRID_OFFSET) * (GRID_SIDE_LEN * 1.5 + GRID_SPACE), 
			(col - DRAW_GRID_OFFSET) * (GRID_SIDE_LEN * COS_30 * 2 + GRID_SPACE));
	}else{
		return Point((row - DRAW_GRID_OFFSET) * (GRID_SIDE_LEN * 1.5 + GRID_SPACE), 
			(col - DRAW_GRID_OFFSET) * (GRID_SIDE_LEN * COS_30 * 2 + GRID_SPACE) - GRID_SIDE_LEN * COS_30 - GRID_SPACE / 2);
	}
}

void GridNode::changeState(GridState state){
	_currentState = state;
	refreshView();
}

//格子的碰撞检测
bool GridNode::hitCheckPoint(const Point & pt){
	return _bg1->hitCheckPoint(pt) || _bg2->hitCheckPoint(pt);
}

int GridNode::getRow(){
	return _row;
}

int GridNode::getCol(){
	return _col;
}

int GridNode::getNum(){
	return _num;
}

GridState GridNode::getCurState(){
	return _currentState;
}