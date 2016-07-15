#include "GameNodeContainer.h"
 
//����ĵ�ͼ��ÿ����������������չ��x��ֵΪ������ż���ֿ�����������Ϸ�У�ĳЩ���ǲ��õģ���Ҫ�ų���
int exceptNode[][2] = {{0, 0}, {1, 0},{3, 0},{4, 0},{0, 4}, {4, 4}};
int extendedInEven[][2] = {{0, 1}, {1, 1}, {1, 0}, {0, -1}, {-1, 0}, {-1, 1}};
int extendedInOdd[][2] = {{0, 1}, {1, 0}, {1, -1}, {0, -1}, {-1, 0}, {-1, -1}};
//����ʱ������¼�Ƿ��Ѿ�������������
int searchedGrids[GRID_ROWS][GRID_COLS];
//����ʱ����������Ҫ�����ĸ���
Vector<GridNode *> searchGrids;

bool GameNodeContainer::init(){
	if(!Layer::init()){
		return false;
	}

	_score = 0;

	//��������
	for(int row = 0; row < GRID_ROWS; row++){
		for(int col = 0; col < GRID_COLS; col++){
			if(isExceptNode(row, col)){
				continue;
			}
			addNewGrid(row, col);
		}
	}

	//���������¼�
	_eventListener = EventListenerTouchOneByOne::create();
	_eventListener->onTouchBegan = CC_CALLBACK_2(GameNodeContainer::onClickGridContainer, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(_eventListener, this);
	return true;
}

void GameNodeContainer::setScoreLayer(GameScoreLayer * scoreLayer){
	_scoreLayer = scoreLayer;
}

//�����������û��Flash�е����ܣ����ܱȽ��������ܰɣ�����Ҫ�Լ��ж��Ƿ����ĳ��Ԫ����������Node�����жϵĺ��ľ��ǵ��ͼ�ε���ײ��⡣
//�򵥵�ͼ�ξ��ù�ʽ������Ϸ���á����Ƿ���͹������С������㡣���ӵ��Ҳ������ɵĻ����������ؼ����ж���⣬Flash��Ҳ����Ӧ������
bool GameNodeContainer::onClickGridContainer(Touch * tou, Event * evt){
	//����ÿһ�����ӣ��ж��Ƿ����
	for(int row = 0; row < GRID_ROWS; row++){
		for(int col = 0; col < GRID_COLS; col++){
			if(isExceptNode(row, col)){
				continue;
			}
			
			auto node = _listNode[row][col];
			//��Ҫת����ͬһ������ϵ���ܲ������
			Point locatioInNode = node->convertToNodeSpace(tou->getLocation());
			
			if(node->hitCheckPoint(locatioInNode)){
				switch(node->getCurState()){
					case NORMAL:
						//���ĳ�����ӣ���չ��ͬ���ֵĸ���
						extendSameNumGrid(node);
						break;
					case SELECTED:
						//֮ǰ�Ѿ���������ˣ��ٴε����Ҫ�ϲ�������
						composeBiggerGrid(node);
						break;
					case EXTENDED:
						//֮ǰ�Ǳ���չ�ĸ��ӣ��ٴε��������չ��Χ�ĸ���
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

//ѡ��һ�����ӣ���չ����Χ������ͬ��ֵ�ĸ���
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

//���������ͬ���ֵĸ���
Vector<GridNode *> GameNodeContainer::searchSameGrids(GridNode * node){
	resetSearchGrids();
	//��ʼ�������б�ͽ��
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

//�ϲ���ͬ�ĸ��ӣ����ɸ���һ��ĸ��ӣ������ڱ��ϲ��ĸ��Ӵ������µĸ���
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
		//��Ҫ�����ӷŵ����ϲ㣬ͨ��ƽ�ƶ����ƶ���Ŀ���
		node->setLocalZOrder(2);
		node->moveTo(targetNode->getRow(), targetNode->getCol());
		addNewGrid(node->getRow(), node->getCol());
	}

	//���·���������ķ������ӷ�ʽ���Լ������
	updateScore(_score += _resultGrids.size() * targetNode->getNum());
	//���ɸ��ߵ�����
	targetNode->updateNum(targetNode->getNum() * (_resultGrids.size() >= 9 ? 9 : 3));

	clearGridState();

	//��Ϸ�����������������
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

//5*5�ĸ��ӣ������м����ǲ���Ҫ���ģ�Ҳ����������
bool GameNodeContainer::isExceptNode(int row, int col){
	for(int i = 0; i < EXCEPT_POINT_COUNT; i++){
		if(row == exceptNode[i][0] && col == exceptNode[i][1]){
			return true;
		}
	}

	return false;
}

//��Ϸ�������жϣ���ÿһ�����Ӷ�������չ3����3�����ϵĸ��Ӻ��Ǿ�GameOver��
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