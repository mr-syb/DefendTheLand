#pragma once//ֻ������һ��
#include "cocos2d.h"
#include "AllScene.h"

USING_NS_CC;
using namespace ui;
class AllLevel:public AllScene{
public:
	AllLevel();
	~AllLevel();
	virtual void commander() = 0;//��˾��
	virtual void addEnemy(Vec2 position,int tag) = 0;//������

	const char *army_attack = "sound/army_attack.mp3";
};