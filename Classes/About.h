#pragma once
#include "cocos2d.h"
#include "AllScene.h"

class About : public AllScene{
public:
	About();
	~About();
	static cocos2d::Scene* createScene();//创建场景
	void menuCloseCallback(cocos2d::Ref* pSender);
	virtual bool init();//初始化
	void preturn();
	CREATE_FUNC(About);
};

