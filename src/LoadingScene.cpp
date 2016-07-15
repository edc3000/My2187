#include "LoadingScene.h"
#include "SimpleAudioEngine.h"

using namespace CocosDenshion;

bool LoadingScene::init(){ 
	if(!Layer::init()){
		return false;
	}
	
	SimpleAudioEngine::getInstance()->preloadBackgroundMusic("BG.mp3");
	SimpleAudioEngine::getInstance()->preloadEffect("touch.mp3");
	SimpleAudioEngine::getInstance()->preloadEffect("replaceScene.mp3");
	SimpleAudioEngine::getInstance()->preloadEffect("merge.mp3");
	SimpleAudioEngine::getInstance()->preloadEffect("timeout.mp3");


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

	SimpleAudioEngine::getInstance()->playBackgroundMusic("BG.mp3", true);

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

	auto normalButton = SimpleButton::create(100, "Normal", "����", 20, CC_CALLBACK_0(LoadingScene::gotoNormalScene, this));
	normalButton->setPosition(VISIBLE_SIZE.width / 2, VISIBLE_SIZE.height / 3 * 2);
	this->addChild(normalButton);

	auto timeLimiteBt = SimpleButton::create(100, "Time", "����", 20, CC_CALLBACK_0(LoadingScene::gotoTimeScene, this));
	timeLimiteBt->setPosition(VISIBLE_SIZE.width / 2, VISIBLE_SIZE.height / 3);
	this->addChild(timeLimiteBt);
}

void LoadingScene::gotoNormalScene(){
	//���������ұ߻�������
	SimpleAudioEngine::getInstance()->playEffect("replaceScene.mp3");
	Director::getInstance()->replaceScene(TransitionSlideInR::create(0.5, GameScene::createScene()));
}

void LoadingScene::gotoTimeScene(){
	//���������ұ߻�������
	SimpleAudioEngine::getInstance()->playEffect("replaceScene.mp3");
	Director::getInstance()->replaceScene(TransitionSlideInR::create(0.5, GameSceneTimeLimited::createScene()));
}