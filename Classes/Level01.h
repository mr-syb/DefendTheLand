#pragma once//ֻ������һ��
#include "cocos2d.h"
#include "AllLevel.h"
#include "MainGame.h"
#include "pikeMan.h"
#include "bowMan.h"
#include "cavMan.h"
#include "Fountain.h"
#include "shieldMan.h"
#include "shootMan.h"
#include "horseMan.h"
#include "spearMan.h"
USING_NS_CC;
using namespace ui;
class Level01 : public AllLevel{
public:
	Level01();
	~Level01();
	void commander()override;//��˾��
	int timer = 0;//��ʱ��
	void addEnemy(Vec2 position, int tag)override;//������
	void triOrder(int y);//���Ƕ���,ֻ������y�ĸ߶�
	void quaOrder(int y);//�������
	int terminator = 15;//�ս�
	Size visibleSize;//���ڴ�С
};