#pragma once
#include "cocos2d.h"
#include "Hexagon.h" 
#include "GameDefine.h"

USING_NS_CC;
USING_NS_CC_MATH;

//һ�������������εļ򵥰�ť���������ð�ť������
class SimpleButton : public Node
{
public:
	SimpleButton(int sideLen, const std::string & content, const std::string & font, int fontSize, const ccMenuCallback & callback);
	~SimpleButton(void);

	bool init();

	static SimpleButton * create(int sideLen, const std::string & content, const std::string & font, int fontSize, const ccMenuCallback & callback);
private:
	int _sideLen;
	std::string _content;
	std::string _font;
	int _fontSize;
	EventListenerTouchOneByOne * _eventListener;
	ccMenuCallback _callback;
};

