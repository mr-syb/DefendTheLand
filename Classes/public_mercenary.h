#pragma once
#include "cocos2d.h"
#include "AllSprites.h"
using namespace cocos2d;
class public_mercenary :public AllSprites{
public:
	public_mercenary();
	~public_mercenary();
	virtual int get_typeid()=0;//获取对象类型
	virtual void SetAnimation(int from, int to, bool run_directon,int loop)=0;//设置动画
	virtual bool get_skill_J_ishurted()=0;
	virtual void set_skill_J_ishurted(bool skill_J_ishurted) = 0;
	virtual bool get_skill_K_ishurted() = 0;
	virtual void set_skill_K_ishurted(bool skill_K_ishurted) = 0;
	virtual int get_life()=0;//获取生命值
	virtual void set_life(int delta)=0;//设置生命值
	virtual void set_life_bar(int side)=0;//设置血条
	virtual float get_speed();//获得速度
	virtual bool get_hittest_A()=0;
	virtual void set_hittest_A(bool hittest_A) = 0;
	virtual bool get_Direction() = 0;
	virtual void attack_A_effect(AllSprites *enemy)=0;//溅血效果
	virtual int get_attack_A_distance() = 0;//平A距离
	virtual bool get_isblowup()=0;//是否被击飞
	virtual void set_isblowup(bool isblowup)=0;//设置是否被击飞
	//virtual void set_money_paid(bool paid);//设置是否给过钱
	//virtual bool get_money_paid();//获取是否给过钱

	virtual void core() = 0;//随从AI
	virtual bool get_canControl()=0;//获取是否可控
	virtual void set_canControl(bool canControl)=0;//设置是否可控
	virtual bool get_isOver()=0;//获取是否需要移除
	virtual bool get_isdeath() = 0;//获取是否死亡
	virtual void object_select(Vector<AllSprites *> sprites)=0;//判定攻击目标
	virtual bool is_melee() = 0;//是否为近战单位
};