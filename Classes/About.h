#pragma once
#include "cocos2d.h"
#include "AllScene.h"

class About : public AllScene{
public:
	About();
	~About();
	static cocos2d::Scene* createScene();//��������
	void menuCloseCallback(cocos2d::Ref* pSender);
	virtual bool init();//��ʼ��
	void preturn();
	CREATE_FUNC(About);
};

