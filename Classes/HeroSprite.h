#pragma once
#include "cocos2d.h"
#include "public_mercenary.h"
#include "AllSprites.h"
using namespace cocos2d;
class HeroSprite:public AllSprites{//��ΪӢ�۵ĳ�����
public:
	HeroSprite();
	virtual ~HeroSprite()=0;
	virtual int get_typeid() = 0;//��ȡ��������
	virtual void SetAnimation(int from, int to, bool run_directon, int loop) = 0;
	//���ö���,run_directonΪ����������false����,name_eachΪname_png��ÿһС��ͼƬ�Ĺ������Ʋ���,loopΪ���Ŵ���,-1Ϊ����
	virtual void StopAnimation()=0;//ֹͣ����  
	virtual void walk(bool run_directon, int loop)=0;//��·����
	virtual void attack_A_animation(bool run_directon) = 0;//��������
	virtual void attack_A_effect(AllSprites *enemy) = 0;//��ѪЧ��
	virtual void skill_J_ani(Vector<AllSprites *> allEnemy) = 0;//J����
	virtual void skill_J_attack(AllSprites *enemy) = 0;//J���ܲ�����Ч��
	virtual void skill_K_ani(Vector<AllSprites *> allEnemy) = 0;//K����
	virtual void death_ani() = 0;//��������
	
	virtual bool get_hero_ani_block()=0;//��ȡ�����Ƿ�����
	virtual void set_hero_ani_block(bool hero_ani_block) = 0;//���ö����Ƿ�����
	virtual bool get_Direction() = 0;//��ȡӢ�۷���
	virtual bool get_hittest_A()=0;
	virtual void set_hittest_A(bool hittest_A) = 0;
	virtual bool get_hittest_J() = 0;
	virtual void set_hittest_J(bool hittest_J) = 0;
	virtual bool get_hittest_K()=0;
	virtual void set_hittest_K(bool hittest_K)=0;
	virtual bool get_isWalk()=0;//��ȡ�Ƿ����ƶ�
	virtual bool get_attack_A()=0;//��ȡ�Ƿ�ƽA
	virtual void set_attack_A(bool attack_A)=0;//�����Ƿ�ƽA
	virtual float get_A_cd()=0;//��ȡƽAcd
	virtual int get_attack_A_distance() = 0;//ƽA����
	virtual bool get_skill_J()=0;//��ȡ�Ƿ�ʩ�ż���J
	virtual void set_skill_J(bool skill_J)=0;//�����Ƿ�ʩ�ż���J
	virtual float get_J_cd()=0;//��ȡJ����cd
	virtual bool get_skill_K()=0;
	virtual void set_skill_K(bool skill_K)=0;
	virtual float get_K_cd()=0;//��ȡK����cd
	virtual int get_hero_walk_from()=0;//
	virtual int get_hero_walk_to()=0;//
	virtual int get_hero_attack_from()=0;
	virtual int get_hero_attack_to()=0;
	virtual int get_hero_die_from()=0;
	virtual int get_hero_die_to()=0;
	virtual std::string get_attack_A_img()=0;//���ƽAͼƬ·��
	virtual std::string get_skill_J_img()=0;//��ü���JͼƬ·��
	virtual std::string get_skill_K_img()=0;//��ü���KͼƬ·��
	virtual std::string get_icon_head_img() = 0;//���ͷ��ͼƬ·��
	virtual int get_life()=0;//��õ�ǰ����ֵ
	virtual void set_life(int delta) = 0;//��������ֵ
	virtual void set_life_bar(int side)=0;//����Ѫ��
	virtual float get_speed()=0;//���Ӣ���ٶ�
	virtual void set_speed(float delta)=0;//�ı�Ӣ���ٶ�
	virtual void set_speed_orginally(float dt)=0;//�ָ�Ӣ���ٶ�
	virtual bool get_isblowup()=0;//�Ƿ񱻻���
	virtual void set_isblowup(bool isblowup)=0;//�����Ƿ񱻻���
	virtual int get_money()=0;//��ó�ʼ��Ǯ

	virtual bool get_isOver()=0;//��ȡ�Ƿ���Ҫ�Ƴ�
	virtual bool get_isdeath()=0;//��ȡ�Ƿ�����
	virtual void reborn()=0;//Ӣ������

};