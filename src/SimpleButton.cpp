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
	
	//��������һ�����������
	auto bg1 = Hexagon::create(_sideLen, BG_COLOR_4F);
	this->addChild(bg1);
	auto bg2 = Hexagon::create(_sideLen * 0.8, Color4F(1, 0.75f, 0.14f, 1));
	this->addChild(bg2);
	
	//��ť�м������
	auto lblContent = Label::createWithSystemFont(_content, "����", 32);
	lblContent->setPosition(Point::ZERO);
	this->addChild(lblContent);

	//�����ļ����¼�
	_eventListener = EventListenerTouchOneByOne::create();
	//_eventListener->setSwallowTouches(true);
	//C++11��lambda
	_eventListener->onTouchBegan = [=](Touch * tou, Event * evt){
		auto target = static_cast<Node *>(evt->getCurrentTarget());
		Point locatioInNode = target->convertToNodeSpace(tou->getLocation());

		//�ж��Ƿ������Լ�������ײ��⣨(��o��)��Ӧ���Ǵ������а�ť������зŴ�
		if(bg1->hitCheckPoint(locatioInNode)){
			target->setScale(1.1f);
		}
		return true;
	};

	//��������
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