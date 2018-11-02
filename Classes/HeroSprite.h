#pragma once
#include "cocos2d.h"
#include "public_mercenary.h"
#include "AllSprites.h"
using namespace cocos2d;
class HeroSprite:public AllSprites{//作为英雄的抽象类
public:
	HeroSprite();
	virtual ~HeroSprite()=0;
	virtual int get_typeid() = 0;//获取对象类型
	virtual void SetAnimation(int from, int to, bool run_directon, int loop) = 0;
	//设置动画,run_directon为精灵脸朝向，false朝右,name_each为name_png中每一小张图片的公共名称部分,loop为播放次数,-1为无限
	virtual void StopAnimation()=0;//停止动画  
	virtual void walk(bool run_directon, int loop)=0;//走路动画
	virtual void attack_A_animation(bool run_directon) = 0;//攻击动画
	virtual void attack_A_effect(AllSprites *enemy) = 0;//溅血效果
	virtual void skill_J_ani(Vector<AllSprites *> allEnemy) = 0;//J技能
	virtual void skill_J_attack(AllSprites *enemy) = 0;//J技能产生的效果
	virtual void skill_K_ani(Vector<AllSprites *> allEnemy) = 0;//K技能
	virtual void death_ani() = 0;//死亡动画
	
	virtual bool get_hero_ani_block()=0;//获取动画是否阻塞
	virtual void set_hero_ani_block(bool hero_ani_block) = 0;//设置动画是否阻塞
	virtual bool get_Direction() = 0;//获取英雄方向
	virtual bool get_hittest_A()=0;
	virtual void set_hittest_A(bool hittest_A) = 0;
	virtual bool get_hittest_J() = 0;
	virtual void set_hittest_J(bool hittest_J) = 0;
	virtual bool get_hittest_K()=0;
	virtual void set_hittest_K(bool hittest_K)=0;
	virtual bool get_isWalk()=0;//获取是否在移动
	virtual bool get_attack_A()=0;//获取是否平A
	virtual void set_attack_A(bool attack_A)=0;//设置是否平A
	virtual float get_A_cd()=0;//获取平Acd
	virtual int get_attack_A_distance() = 0;//平A距离
	virtual bool get_skill_J()=0;//获取是否施放技能J
	virtual void set_skill_J(bool skill_J)=0;//设置是否施放技能J
	virtual float get_J_cd()=0;//获取J技能cd
	virtual bool get_skill_K()=0;
	virtual void set_skill_K(bool skill_K)=0;
	virtual float get_K_cd()=0;//获取K技能cd
	virtual int get_hero_walk_from()=0;//
	virtual int get_hero_walk_to()=0;//
	virtual int get_hero_attack_from()=0;
	virtual int get_hero_attack_to()=0;
	virtual int get_hero_die_from()=0;
	virtual int get_hero_die_to()=0;
	virtual std::string get_attack_A_img()=0;//获得平A图片路径
	virtual std::string get_skill_J_img()=0;//获得技能J图片路径
	virtual std::string get_skill_K_img()=0;//获得技能K图片路径
	virtual std::string get_icon_head_img() = 0;//获得头像图片路径
	virtual int get_life()=0;//获得当前生命值
	virtual void set_life(int delta) = 0;//设置生命值
	virtual void set_life_bar(int side)=0;//设置血条
	virtual float get_speed()=0;//获得英雄速度
	virtual void set_speed(float delta)=0;//改变英雄速度
	virtual void set_speed_orginally(float dt)=0;//恢复英雄速度
	virtual bool get_isblowup()=0;//是否被击飞
	virtual void set_isblowup(bool isblowup)=0;//设置是否被击飞
	virtual int get_money()=0;//获得初始金钱

	virtual bool get_isOver()=0;//获取是否需要移除
	virtual bool get_isdeath()=0;//获取是否死亡
	virtual void reborn()=0;//英雄重生

};