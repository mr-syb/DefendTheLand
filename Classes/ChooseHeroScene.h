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
	CCSpriteFrameCache *m_frameCache;//����
	static cocos2d::Scene* createScene();//��������
	void menuCloseCallback(cocos2d::Ref* pSender);
	virtual bool init();//��ʼ��
	void start();//������Ϸ����
	void back();//����

	Vector<CheckBox *> box;//��ѡ��
	void update(float dt);//ѭ������
	void display();//��ʾ��ѡ���
	Text *title = Text::create();//����
	void setAction();//����isAction
	bool isAction = false;//�Ƿ����ڵ�������
	//int cancelmusic = 0;//Ϊ�˲���ȡ������
	CREATE_FUNC(ChooseHeroScene);
};

