#include "SimpleButton.h"


SimpleButton::SimpleButton(int sideLen, const std::string & content, const std::string & font, int fontSize, const ccMenuCallback & callback){
	_sideLen = sideLen; 
	_content = content;
	_font = font;
	_fontSize = fontSize;
	_callback = callback;
}


SimpleButton::~SimpleButton(void){
}

bool SimpleButton::init(){
	if(!Node::init()){
		return false;
	}
	
	//两个叠在一起的正六边形
	auto bg1 = Hexagon::create(_sideLen, BG_COLOR_4F);
	this->addChild(bg1);
	auto bg2 = Hexagon::create(_sideLen * 0.8, Color4F(1, 0.75f, 0.14f, 1));
	this->addChild(bg2);
	
	//按钮中间的文字
	auto lblContent = Label::createWithSystemFont(_content, "黑体", 32);
	lblContent->setPosition(Point::ZERO);
	this->addChild(lblContent);

	//触摸的监听事件
	_eventListener = EventListenerTouchOneByOne::create();
	//_eventListener->setSwallowTouches(true);
	//C++11的lambda
	_eventListener->onTouchBegan = [=](Touch * tou, Event * evt){
		auto target = static_cast<Node *>(evt->getCurrentTarget());
		Point locatioInNode = target->convertToNodeSpace(tou->getLocation());

		//判断是否点击，自己处理碰撞检测（(⊙o⊙)…应该是触摸）中按钮，点击中放大
		if(bg1->hitCheckPoint(locatioInNode)){
			target->setScale(1.1f);
		}
		return true;
	};

	//触摸结束
	_eventListener->onTouchEnded = [=](Touch * tou, Event * evt){
		auto target = static_cast<Node *>(evt->getCurrentTarget());
		Point locatioInNode = target->convertToNodeSpace(tou->getLocation());
		target->setScale(1.0f);

		if(bg1->hitCheckPoint(locatioInNode)){
			_callback(this);
		}
	};

	_eventDispatcher->addEventListenerWithSceneGraphPriority(_eventListener, this);

	return true;
}

SimpleButton * SimpleButton::create(int sideLen, const std::string & content, const std::string & font, int fontSize, const ccMenuCallback & callback){
	auto button = new SimpleButton(sideLen, content, font, fontSize, callback);
	if (button && button->init()) { 
        button->autorelease(); 
        return button; 
    } else { 
        delete button; 
        button = NULL; 
        return NULL; 
    } 
}