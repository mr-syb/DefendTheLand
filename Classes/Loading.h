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
	//����
	void start();
	CCSpriteFrameCache *m_frameCache;//����
	void loadingCallBack(Texture2D* texture, const char *plist);//�ص�������ÿ����һ������͵���һ��  
	void loadtextures();//����ͼƬ
	
	cocos2d::CCLabelTTF *m_pLabelLoading;//���ֱ�ǩ��������ʾ��Loading������  
	int currentNum;//��ǰ���ص��ڼ���
	int totalNum;//��������  
	
	Sprite *imagine;//����ͼ
	EventListenerTouchOneByOne *listener;//������
	virtual bool onTouchBegan(Touch *touch,Event *unused_event);//������Ļ

	CREATE_FUNC(Loading);
};