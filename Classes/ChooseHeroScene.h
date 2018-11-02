#pragma once
#include "cocos2d.h"
#include "MainGame.h"
#include "AllScene.h"
#include "swordMan.h"
USING_NS_CC;

class ChooseHeroScene : public AllScene{
public:
	ChooseHeroScene();
	~ChooseHeroScene();
	CCSpriteFrameCache *m_frameCache;//加载
	static cocos2d::Scene* createScene();//创建场景
	void menuCloseCallback(cocos2d::Ref* pSender);
	virtual bool init();//初始化
	void start();//进入游戏场景
	void back();//返回

	Vector<CheckBox *> box;//复选框
	void update(float dt);//循环更新
	void display();//显示到选择池
	Text *title = Text::create();//标题
	void setAction();//设置isAction
	bool isAction = false;//是否正在弹出标题
	//int cancelmusic = 0;//为了播放取消音乐
	CREATE_FUNC(ChooseHeroScene);
};

