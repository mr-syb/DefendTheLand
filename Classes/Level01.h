#pragma once//只被编译一次
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
	void commander()override;//总司令
	int timer = 0;//计时器
	void addEnemy(Vec2 position, int tag)override;//添加随从
	void triOrder(int y);//三角队形,只需输入y的高度
	void quaOrder(int y);//方阵队形
	int terminator = 15;//终结
	Size visibleSize;//窗口大小
};