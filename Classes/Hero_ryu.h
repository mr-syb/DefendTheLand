#ifndef __Hero_H__ 
#define __Hero_H__
#include "cocos2d.h"
#include "HeroSprite.h"
#include "public_mercenary.h"
using namespace cocos2d;

class Hero_ryu:public HeroSprite{
public:
	Hero_ryu(int side);
	~Hero_ryu();
	
	int get_typeid()override;//获取对象类型
	void SetAnimation(int from, int to, bool run_directon, int loop)override;
	//设置动画,run_directon为精灵脸朝向，false朝右,name_each为name_png中每一小张图片的公共名称部分,loop为播放次数,-1为无限
	void StopAnimation()override;//停止动画
	void set_statusoriginal();//设置状态还原
	void walk(bool run_directon, int loop)override;//走路动画
	void attack_A_animation(bool run_directon)override;//攻击动画
	void attack_A_img_end();//普攻收尾
	void attack_A_end();//停止攻击
	void attack_A_effect(AllSprites *enemy)override;//溅血效果
	void skill_J_ani(Vector<AllSprites *> allEnemy)override;//J技能
	void skill_J_img_end(Vector<AllSprites *> allEnemy);//J技能收尾动画
	void skill_J_blowup();//J技能击飞
	void skill_J_setblowup();//设置J技能击飞
	void skill_J_blowdelay(float dt, AllSprites *enemy);//解除智能核心不可控状态
	void skill_J_bloweffect(AllSprites *enemy);//击飞特效
	void skill_J_blowmove(AllSprites *enemy);//抛向空中
	void skill_J_blowattack(AllSprites *enemy);//造成伤害和眩晕
	void skill_J_end(Vector<AllSprites *> allEnemy);
	void skill_J_attack(AllSprites *enemy)override;//J技能产生的效果
	void skill_J_effect();//J技能特效
	void skill_K_ani(Vector<AllSprites *> allEnemy)override;//K技能动画
	void skill_K_effect();//K技能特效
	void skill_K_Buff();//K技能效果
	//死亡
	void death_ani()override;//死亡动画
	void death_effect();//死亡特效
	void born_effect();//出生特效

	void removeself(Node *pSender);//从父类移除
	void blood_effect(AllSprites *sprite);//溅血效果
	void set_life_bar(int side)override;//设置血条
	void set_life_bar_scaleX(float per);//设置血条百分比

	CCSpriteFrameCache *m_frameCache;//加载
	bool hero_ani_block = false;//动画管理阻塞
	bool IsRunning = false;//动画管理用，无实际running用途

	//平A
	bool attack_A = false;//是否平A
	bool hittest_A = false;
	int damage_of_A;//平A伤害
	float A_cd;
	int attack_A_distance;//平A距离
	//技能J
	bool skill_J=false;//是否施放技能J
	bool isWalk = false;//是否在移动
	bool blowup = false;//是否击飞
	bool hittest_J = false;
	bool skill_J_damage = false;//J技能造成伤害
	int distance_J;//J技能的位移距离
	int damage_of_J;//J技能的伤害值
	int damage_of_J_blow;//击飞伤害值
	float height_blow;//J技能击飞高度
	float stun_time;//J技能眩晕时间
	float J_cd;//J技能cd
	//技能K
	bool skill_K = false;//是否施放技能K
	bool hittest_K = false;
	int lifeBuff_K;//K技能回血量
	float K_duration;//K技能BUFF持续时间
	float speedBuff_K;//K技能增加移动速度量
	float K_cd;

	int hero_walk_from;
	int hero_walk_to;
	int hero_attack_from;
	int hero_attack_to;
	int hero_die_from;
	int hero_die_to;
	const char *name_each;//动画文件部分名字
	std::string attack_A_img;//平A图片路径
	std::string skill_J_img;//技能J图片路径
	std::string skill_K_img;//技能K图片路径
	std::string icon_head_img;//头像图片路径
	//英雄属性
	int type_id;//对象类型
	bool isOver = false;//是否需要移除
	bool isdeath = false;//是否死亡
	int life;//英雄血量
	int orginal_life;//原始血量
	float speed;//英雄移动速度
	float original_speed;//英雄默认设定速度
	bool isblowup = false;//是否被击飞
	bool HeroDirection = false;//英雄运动的方向  
	int money;//初始金钱
	bool isMoving=false;//是否正在移动

	bool get_hero_ani_block()override;//获取动画是否阻塞
	void set_hero_ani_block(bool hero_ani_block)override;//设置动画是否阻塞
	bool get_Direction()override;//获取英雄运动的方向
	bool get_hittest_A()override;
	void set_hittest_A(bool hittest_A)override;
	bool get_hittest_J()override;
	void set_hittest_J(bool hittest_J)override;
	bool get_hittest_K()override;
	void set_hittest_K(bool hittest_K)override;
	bool get_isWalk()override;//获取是否在移动
	bool get_attack_A()override;//获取是否平A
	void set_attack_A(bool attack_A)override;//设置是否平A
	float get_A_cd()override;//获取平Acd
	int get_attack_A_distance()override;//平A距离
	bool get_skill_J()override;//获取是否施放技能J
	void set_skill_J(bool skill_J)override;//设置是否施放技能J
	float get_J_cd()override;//获取J技能cd
	bool get_skill_K()override;
	void set_skill_K(bool skill_K)override;
	float get_K_cd()override;//获取K技能cd
	int get_hero_walk_from()override;//
	int get_hero_walk_to()override;//
	int get_hero_attack_from()override;
	int get_hero_attack_to()override;
	int get_hero_die_from()override;
	int get_hero_die_to()override;
	std::string get_attack_A_img()override;//获得平A图片路径
	std::string get_skill_J_img()override;//获得技能J图片路径
	std::string get_skill_K_img()override;//获得技能K图片路径
	std::string get_icon_head_img()override;//获得头像图片路径
	bool get_isOver()override;//获取是否需要移除
	bool get_isdeath()override;//获取是否死亡
	int get_life()override;//获得当前生命值
	void set_life(int delta)override;//改变生命值
	float get_speed()override;//获得英雄速度
	void set_speed(float delta)override;//改变英雄速度
	void set_speed_orginally(float dt)override;//恢复英雄速度
	bool get_isblowup()override;//是否被击飞
	void set_isblowup(bool isblowup)override;//设置是否被击飞
	void reborn()override;//英雄重生
	int get_money()override;//获得金钱
	void set_isMoving(bool isMoving)override;//设置是否正在移动
	bool get_isMoving()override;//获得是否正在移动
	Sprite *get_n_Sprite();//获得内部精灵
private:
	Sprite* m_Sprite;//精灵
	Sprite *n_Sprite;//精灵，解决删除问题
	char *Hero_name;//用来保存初始状态的精灵图片名称  
	Sprite *life_bar_fore;//血条前景
	Sprite *life_bar_back;//血条背景
};

#endif // !__Hero_H__ 
