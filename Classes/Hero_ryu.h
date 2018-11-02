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
	
	int get_typeid()override;//��ȡ��������
	void SetAnimation(int from, int to, bool run_directon, int loop)override;
	//���ö���,run_directonΪ����������false����,name_eachΪname_png��ÿһС��ͼƬ�Ĺ������Ʋ���,loopΪ���Ŵ���,-1Ϊ����
	void StopAnimation()override;//ֹͣ����
	void set_statusoriginal();//����״̬��ԭ
	void walk(bool run_directon, int loop)override;//��·����
	void attack_A_animation(bool run_directon)override;//��������
	void attack_A_img_end();//�չ���β
	void attack_A_end();//ֹͣ����
	void attack_A_effect(AllSprites *enemy)override;//��ѪЧ��
	void skill_J_ani(Vector<AllSprites *> allEnemy)override;//J����
	void skill_J_img_end(Vector<AllSprites *> allEnemy);//J������β����
	void skill_J_blowup();//J���ܻ���
	void skill_J_setblowup();//����J���ܻ���
	void skill_J_blowdelay(float dt, AllSprites *enemy);//������ܺ��Ĳ��ɿ�״̬
	void skill_J_bloweffect(AllSprites *enemy);//������Ч
	void skill_J_blowmove(AllSprites *enemy);//�������
	void skill_J_blowattack(AllSprites *enemy);//����˺���ѣ��
	void skill_J_end(Vector<AllSprites *> allEnemy);
	void skill_J_attack(AllSprites *enemy)override;//J���ܲ�����Ч��
	void skill_J_effect();//J������Ч
	void skill_K_ani(Vector<AllSprites *> allEnemy)override;//K���ܶ���
	void skill_K_effect();//K������Ч
	void skill_K_Buff();//K����Ч��
	//����
	void death_ani()override;//��������
	void death_effect();//������Ч
	void born_effect();//������Ч

	void removeself(Node *pSender);//�Ӹ����Ƴ�
	void blood_effect(AllSprites *sprite);//��ѪЧ��
	void set_life_bar(int side)override;//����Ѫ��
	void set_life_bar_scaleX(float per);//����Ѫ���ٷֱ�

	CCSpriteFrameCache *m_frameCache;//����
	bool hero_ani_block = false;//������������
	bool IsRunning = false;//���������ã���ʵ��running��;

	//ƽA
	bool attack_A = false;//�Ƿ�ƽA
	bool hittest_A = false;
	int damage_of_A;//ƽA�˺�
	float A_cd;
	int attack_A_distance;//ƽA����
	//����J
	bool skill_J=false;//�Ƿ�ʩ�ż���J
	bool isWalk = false;//�Ƿ����ƶ�
	bool blowup = false;//�Ƿ����
	bool hittest_J = false;
	bool skill_J_damage = false;//J��������˺�
	int distance_J;//J���ܵ�λ�ƾ���
	int damage_of_J;//J���ܵ��˺�ֵ
	int damage_of_J_blow;//�����˺�ֵ
	float height_blow;//J���ܻ��ɸ߶�
	float stun_time;//J����ѣ��ʱ��
	float J_cd;//J����cd
	//����K
	bool skill_K = false;//�Ƿ�ʩ�ż���K
	bool hittest_K = false;
	int lifeBuff_K;//K���ܻ�Ѫ��
	float K_duration;//K����BUFF����ʱ��
	float speedBuff_K;//K���������ƶ��ٶ���
	float K_cd;

	int hero_walk_from;
	int hero_walk_to;
	int hero_attack_from;
	int hero_attack_to;
	int hero_die_from;
	int hero_die_to;
	const char *name_each;//�����ļ���������
	std::string attack_A_img;//ƽAͼƬ·��
	std::string skill_J_img;//����JͼƬ·��
	std::string skill_K_img;//����KͼƬ·��
	std::string icon_head_img;//ͷ��ͼƬ·��
	//Ӣ������
	int type_id;//��������
	bool isOver = false;//�Ƿ���Ҫ�Ƴ�
	bool isdeath = false;//�Ƿ�����
	int life;//Ӣ��Ѫ��
	int orginal_life;//ԭʼѪ��
	float speed;//Ӣ���ƶ��ٶ�
	float original_speed;//Ӣ��Ĭ���趨�ٶ�
	bool isblowup = false;//�Ƿ񱻻���
	bool HeroDirection = false;//Ӣ���˶��ķ���  
	int money;//��ʼ��Ǯ
	bool isMoving=false;//�Ƿ������ƶ�

	bool get_hero_ani_block()override;//��ȡ�����Ƿ�����
	void set_hero_ani_block(bool hero_ani_block)override;//���ö����Ƿ�����
	bool get_Direction()override;//��ȡӢ���˶��ķ���
	bool get_hittest_A()override;
	void set_hittest_A(bool hittest_A)override;
	bool get_hittest_J()override;
	void set_hittest_J(bool hittest_J)override;
	bool get_hittest_K()override;
	void set_hittest_K(bool hittest_K)override;
	bool get_isWalk()override;//��ȡ�Ƿ����ƶ�
	bool get_attack_A()override;//��ȡ�Ƿ�ƽA
	void set_attack_A(bool attack_A)override;//�����Ƿ�ƽA
	float get_A_cd()override;//��ȡƽAcd
	int get_attack_A_distance()override;//ƽA����
	bool get_skill_J()override;//��ȡ�Ƿ�ʩ�ż���J
	void set_skill_J(bool skill_J)override;//�����Ƿ�ʩ�ż���J
	float get_J_cd()override;//��ȡJ����cd
	bool get_skill_K()override;
	void set_skill_K(bool skill_K)override;
	float get_K_cd()override;//��ȡK����cd
	int get_hero_walk_from()override;//
	int get_hero_walk_to()override;//
	int get_hero_attack_from()override;
	int get_hero_attack_to()override;
	int get_hero_die_from()override;
	int get_hero_die_to()override;
	std::string get_attack_A_img()override;//���ƽAͼƬ·��
	std::string get_skill_J_img()override;//��ü���JͼƬ·��
	std::string get_skill_K_img()override;//��ü���KͼƬ·��
	std::string get_icon_head_img()override;//���ͷ��ͼƬ·��
	bool get_isOver()override;//��ȡ�Ƿ���Ҫ�Ƴ�
	bool get_isdeath()override;//��ȡ�Ƿ�����
	int get_life()override;//��õ�ǰ����ֵ
	void set_life(int delta)override;//�ı�����ֵ
	float get_speed()override;//���Ӣ���ٶ�
	void set_speed(float delta)override;//�ı�Ӣ���ٶ�
	void set_speed_orginally(float dt)override;//�ָ�Ӣ���ٶ�
	bool get_isblowup()override;//�Ƿ񱻻���
	void set_isblowup(bool isblowup)override;//�����Ƿ񱻻���
	void reborn()override;//Ӣ������
	int get_money()override;//��ý�Ǯ
	void set_isMoving(bool isMoving)override;//�����Ƿ������ƶ�
	bool get_isMoving()override;//����Ƿ������ƶ�
	Sprite *get_n_Sprite();//����ڲ�����
private:
	Sprite* m_Sprite;//����
	Sprite *n_Sprite;//���飬���ɾ������
	char *Hero_name;//���������ʼ״̬�ľ���ͼƬ����  
	Sprite *life_bar_fore;//Ѫ��ǰ��
	Sprite *life_bar_back;//Ѫ������
};

#endif // !__Hero_H__ 
