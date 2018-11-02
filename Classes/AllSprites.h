#pragma once
#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "AllScene.h"
using namespace CocosDenshion;
using namespace cocos2d;
class AllSprites : public Sprite{
public:
	AllSprites();
	~AllSprites();
	virtual int get_typeid();//获取对象类型
	//public_mercenary
	virtual void SetAnimation(int from, int to, bool run_directon,int loop);//设置动画
	virtual bool get_skill_J_ishurted();
	virtual void set_skill_J_ishurted(bool skill_J_ishurted);
	virtual bool get_skill_K_ishurted();
	virtual void set_skill_K_ishurted(bool skill_K_ishurted);
	virtual int get_life();//获取生命值
	virtual void set_life(int delta);//设置生命值
	virtual void set_life_bar(int side);//设置血条
	virtual float get_speed();//获得速度
	virtual bool get_hittest_A();
	virtual void set_hittest_A(bool hittest_A);
	virtual void attack_A_effect(AllSprites *enemy);//平A效果
	virtual int get_attack_A_distance();//平A距离
	virtual bool get_hittest_J();
	virtual void skill_J_attack(AllSprites *enemy);//J技能产生效果
	//virtual void get_J_attack_distance();//J技能距离
	virtual bool get_hittest_K();
	virtual void skill_K_attack(AllSprites *enemy);//K技能产生效果
	//virtual void get_K_attack_distance();//K技能距离
	virtual bool get_Direction();//获取方向
	virtual bool get_isblowup();//是否被击飞
	virtual void set_isblowup(bool isblowup);//设置是否被击飞
	virtual void set_money_paid(bool paid);//设置是否给过钱
	virtual bool get_money_paid();//获取是否给过钱
	virtual void set_isMoving(bool isMoving);//设置是否正在移动
	virtual bool get_isMoving();//获得是否正在移动

	virtual void core();//随从AI
	virtual bool get_canControl();//获取是否可控
	virtual void set_canControl(bool canControl);//设置是否可控
	virtual bool get_isOver();//获取是否需要移除
	virtual bool get_isdeath();//获取是否死亡
	virtual void object_select(Vector<AllSprites *> sprites);//判定攻击目标
	virtual bool is_melee();//是否为近战单位
	virtual int get_fly_kind();//获得飞行道具类型
	virtual bool is_fly_kind();//是否为飞行道具
	virtual int earn_money();//赚得金钱
	virtual Vec2 get_object_aim_pst();//获得目标坐标
	virtual Sprite *get_n_Sprite();//获得内部精灵
	Sprite *n_Sprite;

	//所有音效
	const char *menu_back = "sound/menu_back.mp3";
	const char *choose_back = "sound/choose_back.mp3";
	const char *click = "sound/click.mp3";
	const char *loading_ok = "sound/loading.mp3";
	const char *ryu_A = "sound/ryu_A.mp3";
	const char *ryu_J_start = "sound/ryu_J_start.mp3";
	const char *ryu_J_end = "sound/ryu_J_end.mp3";
	const char *ryu_K = "sound/ryu_K.mp3";
	const char *victory = "sound/victory.mp3";
	const char *warning = "sound/warning.mp3";
	const char *hit = "sound/hit.mp3";
	const char *ryu_die = "sound/ryu_die.mp3";
	const char *wave_A = "sound/wave_A.mp3";
	const char *bowMan_A = "sound/bowMan_A.mp3";
	const char *shootMan_A = "sound/shootMan_A.mp3";
	const char *bow_shoot_die = "sound/bow_shoot_die.mp3";
	const char *cav_horse_die = "sound/cav_horse_die.mp3";
	const char *cavMan_hit = "sound/cavMan_hit.mp3";
	const char *Fly0_hit = "sound/Fly0_hit.mp3";
	const char *Fly1_hit = "sound/Fly1_hit.mp3";
	const char *horseMan_hit = "sound/horseMan_hit.mp3";
	const char *pike_spear_die = "sound/pike_spear_die.mp3";
	const char *shieldMan_hit = "sound/shieldMan_hit.mp3";
	const char *spear_pike_hit = "sound/spear_pike_hit.mp3";
	const char *sword_shield_die = "sound/sword_shield_die.mp3";
	const char *swordMan_hit = "sound/swordMan_hit.mp3";
	const char *tower_die = "sound/tower_die.mp3";
	const char *tower_normal_A = "sound/tower_normal_A.mp3";
	const char *tower_normal_hit = "sound/tower_normal_hit.mp3";
	const char *army_attack = "sound/army_attack.mp3";
};
