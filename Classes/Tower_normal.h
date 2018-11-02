#pragma once
#include"cocos2d.h"
#include "public_mercenary.h"
#include "MainGame.h"
using namespace cocos2d;
USING_NS_CC;
class Tower_normal : public public_mercenary{
public:
	Tower_normal(int side);
	~Tower_normal();
	CCSpriteFrameCache *m_frameCache;//加载
	int type_id;//对象类型
	bool is_melee()override;//是否为近战单位
	int fly_kind;//飞行道具类型
	bool is_melee_unit;//随从类型
	bool IsRunning;//判断是否在跑动画
	bool SpriteDirecton;//运动的方向
	bool skill_J_ishurted = false;
	bool skill_K_ishurted = false;
	float speed;//移动速度
	int life;//血量
	int orginal_life;//原始血量
	int side;//英雄阵营，0为蓝色方，1为红色方
	int damage_of_A;//平A伤害
	bool isblowup = false;//是否被击飞
	const char *name_each;//动画文件部分名字
	bool ani_block = false;//动画阻塞
	void StopAnimation();//停止所有动画
	void idle();//站立动画
	void attack_ani();//攻击动画
	bool attack_A = false;//是否在平A
	bool hittest_A = false;//平A碰撞判定
	int attack_A_distance;//平A距离
	int attack_gap = 81;//普攻间隔
	float ox = 0;//复原x坐标
	void deadth_ani();//死亡动画
	bool isdeath = false;//是否死亡
	void setisOver();//设置可以移除
	bool paid = false;//是否给过钱

	//AI
	void core();//AI管理中心
	bool isOver = false;//可否移除此单位
	bool canControl = true;//可否控制
	void object_select(Vector<AllSprites *> sprites);//判定攻击目标
	AllSprites *object_aim = nullptr;//锁定目标
	void move();//朝目标移动
	Vec2 point;//目标坐标

	int get_typeid();//获取对象类型
	void SetAnimation(int from, int to, bool run_directon, int loop)override;//设置动画
	bool get_skill_J_ishurted()override;
	void set_skill_J_ishurted(bool skill_J_ishurted)override;
	bool get_skill_K_ishurted()override;
	void set_skill_K_ishurted(bool skill_K_ishurted)override;
	int get_life()override;//获取生命值
	void set_life(int delta)override;//设置生命值
	void set_life_bar(int side)override;//设置血条
	bool get_hittest_A()override;
	void set_hittest_A(bool hittest_A)override;
	bool get_Direction()override;//获取随从方向
	bool get_isblowup()override;//是否被击飞
	void set_isblowup(bool isblowup)override;//设置是否被击飞
	bool get_canControl()override;//获取是否可控
	void set_canControl(bool canControl)override;//设置是否可控
	bool get_isOver()override;//获取是否需要移除
	bool get_isdeath()override;//获取是否死亡
	void attack_A_effect(AllSprites *enemy);//溅血效果
	int get_attack_A_distance()override;//平A距离
	void blood_effect(AllSprites *sprite);//溅血效果
	void removeself(Node *pSender);//从父类移除
	int get_fly_kind()override;//获得飞行道具类型
	Vec2 get_object_aim_pst()override;//获得目标坐标
	void set_money_paid(bool paid);//设置是否给过钱
	bool get_money_paid();//获取是否给过钱
	Sprite *get_n_Sprite();//获得内部精灵
private:
	Sprite *m_Sprite;//精灵
	Sprite *n_Sprite;//精灵，解决删除问题
	char *sprite_name;//用来保存初始状态的精灵图片名称
	Sprite *life_bar_fore;//血条前景
	Sprite *life_bar_back;//血条背景
};