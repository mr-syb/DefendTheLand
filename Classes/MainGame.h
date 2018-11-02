#pragma once//只被编译一次
#include "cocos2d.h"
#include <string.h>
#include "Hero_ryu.h"
#include "HRocker.h"
#include "swordMan.h"
#include "ui/CocosGUI.h"
#include "HeroSprite.h"
#include "public_mercenary.h"
#include "AllSprites.h"
#include "AllScene.h"
#include "pikeMan.h"
#include "bowMan.h"
#include "Fly0.h"
#include "cavMan.h"
#include "Fountain.h"
#include "shieldMan.h"
#include "shootMan.h"
#include "Fly1.h"
#include "horseMan.h"
#include "spearMan.h"
#include "Tower_normal.h"
#include "Fly2.h"
#include "AllLevel.h"
#include "Level01.h"
#include "HelloWorldScene.h"
USING_NS_CC;
using namespace ui;
using namespace std;
class MainGame : public AllScene{
public:
	MainGame(Vector<CheckBox *> choosed_objects);
	~MainGame();
	static cocos2d::Scene* createScene(Vector<CheckBox *> choosed_objects);//创建场景
	void menuCloseCallback(cocos2d::Ref* pSender);
	virtual bool init();//初始化
	CCSpriteFrameCache *m_frameCache;//加载
	void start();//进入游戏场景
	void back();//返回
	void update(float dt);//刷新间隔时间
	void addMoney(float dt);//增加金币，每两秒加1

	static bool isGameOver;//游戏是否结束
	static bool isVictory;//是否胜利
	void gameOver();//游戏结束
	void replace();//重置场景

	AllLevel* level;//关卡
	void level_run(float dt);//执行关卡内容
	int second = 0;//游戏时间
	int minute = 0;
	void display_time(float dt);//显示游戏时间
	Text *time = Text::create();
	static void addSprite(AllSprites *enemy);//添加敌人

	HRocker* rocker;//摇杆
	Button *A;//按键A
	void button_A_cd(float duration);//平Acd冷却
	void button_A_cd_recover();//cd恢复
	Button *J;//按键J
	void button_J_cd(float duration);//技能cd冷却
	void button_J_cd_recover();//技能cd恢复
	void button_J_timer(float dt);//J技能CD倒计时秒表
	Text *text_J_timer=Text::create();//J技能时间
	Button *K;//按键K
	void button_K_cd(float duration);
	void button_K_cd_recover();
	void button_K_timer(float dt);
	Text *text_K_timer = Text::create();
	Sprite *icon_head;//人物头像
	Sprite *life_bar_back;//血条背景
	Sprite *life_bar_fore;
	void set_blood_bar();//调整血条百分比
	Text *life_text = Text::create();
	int hero_life;//英雄当前血量
	int hero_original_life;//英雄总血量
	Sprite *skull;//死亡骷髅图标
	Text *title = Text::create();//顶部标题
	Text *reborn_timer = Text::create();//重生倒计时
	void set_reborn_timer(float dt);//设置重生倒计时
	float reborn_time_left=0;//重生剩余时间

	void removeself(Node *pSender);//从父类移除

	void moveControl();//移动控制
	EventListenerKeyboard* listener;//键盘监听，测试用
	void keyBoardEvent(EventKeyboard::KeyCode code,Event* evt);//键盘监听，测试用
	void keyBoardStop(EventKeyboard::KeyCode code, Event* evt);//键盘监听，测试用
	int keypressed = 0;//按下了多少个键
	void touchEvent_A(Ref* pSender, Widget::TouchEventType type);//平A普攻
	void touchEvent_J(Ref* pSender, Widget::TouchEventType type);//技能J
	void touchEvent_K(Ref* pSender, Widget::TouchEventType type);//技能K

	//自定义类型
	typedef struct{
		int tag;
		const char *player_img;
		int cost;
		float cd;
	}soldier;
	soldier *choosed[4];//选择的单位 一共四个

	//初始金钱
	int money;
	//购买随从
	//展位1
	Button *choose_back0;
	Text *back0_text = Text::create();//购买CD
	void touchEvent_buy_0(Ref* pSender, Widget::TouchEventType type, soldier *man);
	void sold_first_cd(float duration);//展位1开始冷却
	void sold_first_recover();//展位1冷却完毕
	void sold_first_timer(float dt);//倒计时
	Sprite *sprite_back0;//精灵拖动背景1
	bool change_x0=false;//修改放置x位置
	//展位2
	Button *choose_back1;
	Text *back1_text = Text::create();//购买CD
	void touchEvent_buy_1(Ref* pSender, Widget::TouchEventType type, soldier *man);
	void sold_second_cd(float duration);
	void sold_second_recover();
	void sold_second_timer(float dt);
	Sprite *sprite_back1;
	bool change_x1 = false;//修改放置x位置
	//展位3
	Button *choose_back2;
	Text *back2_text = Text::create();//购买CD
	void touchEvent_buy_2(Ref* pSender, Widget::TouchEventType type, soldier *man);
	void sold_third_cd(float duration);
	void sold_third_recover();
	void sold_third_timer(float dt);
	Sprite *sprite_back2;
	bool change_x2 = false;//修改放置x位置
	//展位4
	Button *choose_back3;
	Text *back3_text = Text::create();//购买CD
	void touchEvent_buy_3(Ref* pSender, Widget::TouchEventType type, soldier *man);
	void sold_fourth_cd(float duration);
	void sold_fourth_recover();
	void sold_fourth_timer(float dt);
	Sprite *sprite_back3;
	bool change_x3 = false;//修改放置x位置
	
	//显示金币
	Text *money_text = Text::create();

	void newFriend(float x,float y,int tag);//创建一个友方单位
	void lack_of_money(float dt, Text *back_text);//缺少金钱
	void set_visible(Text *back_text);//设置显示

	//英雄
	HeroSprite *hero;//英雄通用
	void hero_ani_manager();//动画管理
	void hero_reborn(float dt);//英雄重生
	int reborn_cd;//重生cd时间

	//阵营
	Vector<AllSprites *> blueSide;//蓝方单位
	static Vector<AllSprites *> redSide;//红方单位
	void Hittest_center();//碰撞检测中心
	void hittest_melee();//近战攻击检测
	void hittest_remote();//远程攻击检测
	bool ishit_mercenary(AllSprites *s1,AllSprites *s2);//攻击检测
	void addBullet(int side,AllSprites *s);//添加飞行道具

	static Vector<AllSprites *> allSprites;//所有单位 用来设置层级顺序
	void setZorder();//设置高度
	void deathCenter();//移除单位
	
	void coreCenter();//随从AI
	void object_select(float dt);//随从判定攻击目标
	//CREATE_FUNC(MainGame);
	static MainGame* create(Vector<CheckBox *> choosed_objects);
};