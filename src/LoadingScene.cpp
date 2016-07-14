#include "LoadingScene.h"

bool LoadingScene::init(){ 
	if(!Layer::init()){
		return false;
	}

	//��һ����ɫ�ı���
	auto layerColor = LayerColor::create(Color4B(204, 204, 204, 255), VISIBLE_SIZE.width, VISIBLE_SIZE.height);
	layerColor->setPosition(Point::ZERO);
	this->addChild(layerColor);

	//��Ļ�м�ġ�loading��(Flash�е�TextField��
	_lblLoading = Label::createWithSystemFont("Loading...", "����", 20);
	_lblLoading->setPosition(Point(VISIBLE_SIZE.width / 2, VISIBLE_SIZE.height / 2));
	_lblLoading->setTextColor(Color4B(0, 0, 0, 255));
	this->addChild(_lblLoading, 1);

	//����һ��0.5��ĵ��ȣ�Flash�п�����Timer��ʵ�֣�
	this->scheduleOnce(CC_CALLBACK_0(LoadingScene::showStartGameButton, this), 0.5, "showStartGameButton");

	return true;
}

Scene * LoadingScene::createScene(){
	auto scene = Scene::create();
	auto layer = LoadingScene::create();
	scene->addChild(layer);
	return scene;
}

void LoadingScene::showStartGameButton(){
	this->removeChild(_lblLoading);

	auto button = SimpleButton::create(60, "Start", "����", 20, CC_CALLBACK_0(LoadingScene::gotoStartScene, this));
	button->setPosition(VISIBLE_SIZE.width / 2, VISIBLE_SIZE.height / 2);
	this->addChild(button);
}

void LoadingScene::gotoStartScene(){
	//���������ұ߻�������
	Director::getInstance()->replaceScene(TransitionSlideInR::create(0.5, GameScene::createScene()));
}
