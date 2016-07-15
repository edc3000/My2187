#include "GameNodeContainer.h"
 
//六向的地图，每个点有六个方向扩展，x的值为奇数和偶数分开处理。并且游戏中，某些点是不用的，需要排除。
int exceptNode[][2] = {{0, 0}, {1, 0},{3, 0},{4, 0},{0, 4}, {4, 4}};
int extendedInEven[][2] = {{0, 1}, {1, 1}, {1, 0}, {0, -1}, {-1, 0}, {-1, 1}};
int extendedInOdd[][2] = {{0, 1}, {1, 0}, {1, -1}, {0, -1}, {-1, 0}, {-1, -1}};
//搜索时用来记录是否已经搜索过的数组
int searchedGrids[GRID_ROWS][GRID_COLS];
//搜索时用来保存需要搜索的格子
Vector<GridNode *> searchGrids;

bool GameNodeContainer::init(){
	if(!Layer::init()){
		return false;
	}

	_score = 0;

	//创建格子
	for(int row = 0; row < GRID_ROWS; row++){
		for(int col = 0; col < GRID_COLS; col++){
			if(isExceptNode(row, col)){
				continue;
			}
			addNewGrid(row, col);
		}
	}

	//监听触摸事件
	_eventListener = EventListenerTouchOneByOne::create();
	_eventListener->onTouchBegan = CC_CALLBACK_2(GameNodeContainer::onClickGridContainer, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(_eventListener, this);
	return true;
}

void GameNodeContainer::setScoreLayer(GameScoreLayer * scoreLayer){
	_scoreLayer = scoreLayer;
}

//点击处理，这里没有Flash中的智能（可能比较消耗性能吧），需要自己判定是否点中某个元件（这里是Node），判断的核心就是点和图形的碰撞检测。
//简单的图形就用公式，本游戏是用“点是否在凸多边形中”来计算。复杂的找不到规律的还可以用像素级的判定检测，Flash中也有相应的例子
bool GameNodeContainer::onClickGridContainer(Touch * tou, Event * evt){
	//遍历每一个格子，判断是否击中
	for(int row = 0; row < GRID_ROWS; row++){
		for(int col = 0; col < GRID_COLS; col++){
			if(isExceptNode(row, col)){
				continue;
			}
			
			auto node = _listNode[row][col];
			//需要转换成同一个坐标系才能参与计算
			Point locatioInNode = node->convertToNodeSpace(tou->getLocation());
			
			if(node->hitCheckPoint(locatioInNode)){
				switch(node->getCurState()){
					case NORMAL:
						//点击某个格子，扩展相同数字的格子
						extendSameNumGrid(node);
						break;
					case SELECTED:
						//之前已经被点击过了，再次点击就要合并格子了
						composeBiggerGrid(node);
						break;
					case EXTENDED:
						//之前是被扩展的格子，再次点击就是扩展周围的格子
						extendSameNumGrid(node);
						break;
					default:
						break;
				}
			}
		}
	}
	return true;
}

//选中一个格子，扩展到周围所有相同数值的格子
void GameNodeContainer::extendSameNumGrid(GridNode * node){
	clearGridState();
	node->changeState(SELECTED);
	_resultGrids = searchSameGrids(node);
	for(auto resultNode : _resultGrids){
		if(resultNode != node){
			resultNode->changeState(GridState::EXTENDED);
		}
	}
}

//广度搜索相同数字的格子
Vector<GridNode *> GameNodeContainer::searchSameGrids(GridNode * node){
	resetSearchGrids();
	//初始化搜索列表和结果
	Vector<GridNode *> result;
	searchGrids.clear();
	result.pushBack(node);
	searchGrids.pushBack(node);
	while(!searchGrids.empty()){
		GridNode * checkNode = searchGrids.front();
		searchGrids.eraseObject(checkNode);

		searchedGrids[checkNode->getRow()][checkNode->getCol()] = 1;
		for(int i = 0; i < SIDE_COUNT; i++){
			int row, col;
			if(checkNode->getRow() % 2 == 0){
				row = checkNode->getRow() + extendedInEven[i][0];
				col = checkNode->getCol() + extendedInEven[i][1];
			}else{
				row = checkNode->getRow() + extendedInOdd[i][0];
				col = checkNode->getCol() + extendedInOdd[i][1];
			}

			if(row < 0 || col < 0 || row >= GRID_ROWS || col >= GRID_COLS){
				continue;
			}

			GridNode * extendNode = _listNode[row][col];
			if(!isExceptNode(row, col) && searchedGrids[row][col] == 0 && extendNode->getNum() == node->getNum() && !result.contains(extendNode)){
				result.pushBack(extendNode);
				searchGrids.pushBack(extendNode);
			}
		}
	}

	return result;
}

//合并相同的格子，生成更大一点的格子，并且在被合并的格子处生成新的格子
void GameNodeContainer::composeBiggerGrid(GridNode * targetNode){
	if(_resultGrids.size() < MIN_COMPOSE_COUNT){
		return;
	}

	if(targetNode->getCurState() != GridState::SELECTED){
		return;
	}

	for(auto node : _resultGrids){
		if(node == targetNode){
			continue;
		}
		//需要将格子放到最上层，通过平移动画移动到目标点
		node->setLocalZOrder(2);
		node->moveTo(targetNode->getRow(), targetNode->getCol());
		addNewGrid(node->getRow(), node->getCol());
	}

	//更新分数，这里的分数叠加方式是自己定义的
	updateScore(_score += _resultGrids.size() * targetNode->getNum());
	//生成更高的数字
	targetNode->updateNum(targetNode->getNum() * (_resultGrids.size() >= 9 ? 9 : 3));

	clearGridState();

	//游戏结束，弹出重来面板
	if(isGameOver()){
		((GameScene *)this->getParent())->gameOver();
	}
}

void GameNodeContainer::addNewGrid(int row, int col){
	auto newNode = GridNode::create();
	newNode->setRowAndCol(row, col);
	newNode->updateNum(GameHelper::getInstance()->getRandomNum());
	this->addChild(newNode, 1);
	_listNode[newNode->getRow()][newNode->getCol()] = newNode;
}

void GameNodeContainer::clearGridState(){
	for(int row = 0; row < GRID_ROWS; row++){
		for(int col = 0; col < GRID_COLS; col++){
			if(isExceptNode(row, col)){
				continue;
			}

			_listNode[row][col]->changeState(GridState::NORMAL);
		}
	}
}

//5*5的格子，其中有几个是不需要画的，也不参与搜索
bool GameNodeContainer::isExceptNode(int row, int col){
	for(int i = 0; i < EXCEPT_POINT_COUNT; i++){
		if(row == exceptNode[i][0] && col == exceptNode[i][1]){
			return true;
		}
	}

	return false;
}

//游戏结束的判断，当每一个格子都不能扩展3个及3个以上的格子后，那就GameOver了
bool GameNodeContainer::isGameOver(){
	for(int row = 0; row < GRID_ROWS; row++){
		for(int col = 0; col < GRID_COLS; col++){
			if(isExceptNode(row, col)){
				continue;
			}

			if(searchSameGrids(_listNode[row][col]).size() >= 3){
				return false;
			}
		}
	}

	return true;
}

void GameNodeContainer::restart(){
	for(int row = 0; row < GRID_ROWS; row++){
		for(int col = 0; col < GRID_COLS; col++){
			if(isExceptNode(row, col)){
				continue;
			}
			_listNode[row][col]->changeState(GridState::NORMAL);
			_listNode[row][col]->updateNum(GameHelper::getInstance()->getRandomNum());
		}
	}

	updateScore(0);
}
	
void GameNodeContainer::updateScore(int score){
	_score = score;
	_scoreLayer->showScore(_score);
}


void GameNodeContainer::resetSearchGrids(){
	for(int row = 0; row < GRID_ROWS; row++){
		for(int col = 0; col < GRID_COLS; col++){
			searchedGrids[row][col] = 0;
		}
	}	
}