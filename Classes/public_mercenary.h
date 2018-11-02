#pragma once
#include "cocos2d.h"
#include "AllSprites.h"
using namespace cocos2d;
class public_mercenary :public AllSprites{
public:
	public_mercenary();
	~public_mercenary();
	virtual int get_typeid()=0;//��ȡ��������
	virtual void SetAnimation(int from, int to, bool run_directon,int loop)=0;//���ö���
	virtual bool get_skill_J_ishurted()=0;
	virtual void set_skill_J_ishurted(bool skill_J_ishurted) = 0;
	virtual bool get_skill_K_ishurted() = 0;
	virtual void set_skill_K_ishurted(bool skill_K_ishurted) = 0;
	virtual int get_life()=0;//��ȡ����ֵ
	virtual void set_life(int delta)=0;//��������ֵ
	virtual void set_life_bar(int side)=0;//����Ѫ��
	virtual float get_speed();//����ٶ�
	virtual bool get_hittest_A()=0;
	virtual void set_hittest_A(bool hittest_A) = 0;
	virtual bool get_Direction() = 0;
	virtual void attack_A_effect(AllSprites *enemy)=0;//��ѪЧ��
	virtual int get_attack_A_distance() = 0;//ƽA����
	virtual bool get_isblowup()=0;//�Ƿ񱻻���
	virtual void set_isblowup(bool isblowup)=0;//�����Ƿ񱻻���
	//virtual void set_money_paid(bool paid);//�����Ƿ����Ǯ
	//virtual bool get_money_paid();//��ȡ�Ƿ����Ǯ

	virtual void core() = 0;//���AI
	virtual bool get_canControl()=0;//��ȡ�Ƿ�ɿ�
	virtual void set_canControl(bool canControl)=0;//�����Ƿ�ɿ�
	virtual bool get_isOver()=0;//��ȡ�Ƿ���Ҫ�Ƴ�
	virtual bool get_isdeath() = 0;//��ȡ�Ƿ�����
	virtual void object_select(Vector<AllSprites *> sprites)=0;//�ж�����Ŀ��
	virtual bool is_melee() = 0;//�Ƿ�Ϊ��ս��λ
};