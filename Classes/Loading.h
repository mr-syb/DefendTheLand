#pragma once
#include "cocos2d.h"
#include "AllScene.h"
#include "HelloWorldScene.h"
#include "ui/CocosGUI.h"
USING_NS_CC;
using namespace ui;

class Loading : public AllScene{
public:
	Loading();
	static cocos2d::Scene* createScene();
	virtual bool init();
	//启动
	void start();
	CCSpriteFrameCache *m_frameCache;//加载
	void loadingCallBack(Texture2D* texture, const char *plist);//回调函数，每加载一张纹理就调用一次  
	void loadtextures();//加载图片
	
	cocos2d::CCLabelTTF *m_pLabelLoading;//文字标签，用于显示“Loading”字样  
	int currentNum;//当前加载到第几张
	int totalNum;//加载总数  
	
	Sprite *imagine;//背景图
	EventListenerTouchOneByOne *listener;//监听器
	virtual bool onTouchBegan(Touch *touch,Event *unused_event);//触摸屏幕

	CREATE_FUNC(Loading);
};