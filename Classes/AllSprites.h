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
	virtual int get_typeid();//��ȡ��������
	//public_mercenary
	virtual void SetAnimation(int from, int to, bool run_directon,int loop);//���ö���
	virtual bool get_skill_J_ishurted();
	virtual void set_skill_J_ishurted(bool skill_J_ishurted);
	virtual bool get_skill_K_ishurted();
	virtual void set_skill_K_ishurted(bool skill_K_ishurted);
	virtual int get_life();//��ȡ����ֵ
	virtual void set_life(int delta);//��������ֵ
	virtual void set_life_bar(int side);//����Ѫ��
	virtual float get_speed();//����ٶ�
	virtual bool get_hittest_A();
	virtual void set_hittest_A(bool hittest_A);
	virtual void attack_A_effect(AllSprites *enemy);//ƽAЧ��
	virtual int get_attack_A_distance();//ƽA����
	virtual bool get_hittest_J();
	virtual void skill_J_attack(AllSprites *enemy);//J���ܲ���Ч��
	//virtual void get_J_attack_distance();//J���ܾ���
	virtual bool get_hittest_K();
	virtual void skill_K_attack(AllSprites *enemy);//K���ܲ���Ч��
	//virtual void get_K_attack_distance();//K���ܾ���
	virtual bool get_Direction();//��ȡ����
	virtual bool get_isblowup();//�Ƿ񱻻���
	virtual void set_isblowup(bool isblowup);//�����Ƿ񱻻���
	virtual void set_money_paid(bool paid);//�����Ƿ����Ǯ
	virtual bool get_money_paid();//��ȡ�Ƿ����Ǯ
	virtual void set_isMoving(bool isMoving);//�����Ƿ������ƶ�
	virtual bool get_isMoving();//����Ƿ������ƶ�

	virtual void core();//���AI
	virtual bool get_canControl();//��ȡ�Ƿ�ɿ�
	virtual void set_canControl(bool canControl);//�����Ƿ�ɿ�
	virtual bool get_isOver();//��ȡ�Ƿ���Ҫ�Ƴ�
	virtual bool get_isdeath();//��ȡ�Ƿ�����
	virtual void object_select(Vector<AllSprites *> sprites);//�ж�����Ŀ��
	virtual bool is_melee();//�Ƿ�Ϊ��ս��λ
	virtual int get_fly_kind();//��÷��е�������
	virtual bool is_fly_kind();//�Ƿ�Ϊ���е���
	virtual int earn_money();//׬�ý�Ǯ
	virtual Vec2 get_object_aim_pst();//���Ŀ������
	virtual Sprite *get_n_Sprite();//����ڲ�����
	Sprite *n_Sprite;

	//������Ч
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
