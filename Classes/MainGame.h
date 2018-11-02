#pragma once//ֻ������һ��
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
	static cocos2d::Scene* createScene(Vector<CheckBox *> choosed_objects);//��������
	void menuCloseCallback(cocos2d::Ref* pSender);
	virtual bool init();//��ʼ��
	CCSpriteFrameCache *m_frameCache;//����
	void start();//������Ϸ����
	void back();//����
	void update(float dt);//ˢ�¼��ʱ��
	void addMoney(float dt);//���ӽ�ң�ÿ�����1

	static bool isGameOver;//��Ϸ�Ƿ����
	static bool isVictory;//�Ƿ�ʤ��
	void gameOver();//��Ϸ����
	void replace();//���ó���

	AllLevel* level;//�ؿ�
	void level_run(float dt);//ִ�йؿ�����
	int second = 0;//��Ϸʱ��
	int minute = 0;
	void display_time(float dt);//��ʾ��Ϸʱ��
	Text *time = Text::create();
	static void addSprite(AllSprites *enemy);//��ӵ���

	HRocker* rocker;//ҡ��
	Button *A;//����A
	void button_A_cd(float duration);//ƽAcd��ȴ
	void button_A_cd_recover();//cd�ָ�
	Button *J;//����J
	void button_J_cd(float duration);//����cd��ȴ
	void button_J_cd_recover();//����cd�ָ�
	void button_J_timer(float dt);//J����CD����ʱ���
	Text *text_J_timer=Text::create();//J����ʱ��
	Button *K;//����K
	void button_K_cd(float duration);
	void button_K_cd_recover();
	void button_K_timer(float dt);
	Text *text_K_timer = Text::create();
	Sprite *icon_head;//����ͷ��
	Sprite *life_bar_back;//Ѫ������
	Sprite *life_bar_fore;
	void set_blood_bar();//����Ѫ���ٷֱ�
	Text *life_text = Text::create();
	int hero_life;//Ӣ�۵�ǰѪ��
	int hero_original_life;//Ӣ����Ѫ��
	Sprite *skull;//��������ͼ��
	Text *title = Text::create();//��������
	Text *reborn_timer = Text::create();//��������ʱ
	void set_reborn_timer(float dt);//������������ʱ
	float reborn_time_left=0;//����ʣ��ʱ��

	void removeself(Node *pSender);//�Ӹ����Ƴ�

	void moveControl();//�ƶ�����
	EventListenerKeyboard* listener;//���̼�����������
	void keyBoardEvent(EventKeyboard::KeyCode code,Event* evt);//���̼�����������
	void keyBoardStop(EventKeyboard::KeyCode code, Event* evt);//���̼�����������
	int keypressed = 0;//�����˶��ٸ���
	void touchEvent_A(Ref* pSender, Widget::TouchEventType type);//ƽA�չ�
	void touchEvent_J(Ref* pSender, Widget::TouchEventType type);//����J
	void touchEvent_K(Ref* pSender, Widget::TouchEventType type);//����K

	//�Զ�������
	typedef struct{
		int tag;
		const char *player_img;
		int cost;
		float cd;
	}soldier;
	soldier *choosed[4];//ѡ��ĵ�λ һ���ĸ�

	//��ʼ��Ǯ
	int money;
	//�������
	//չλ1
	Button *choose_back0;
	Text *back0_text = Text::create();//����CD
	void touchEvent_buy_0(Ref* pSender, Widget::TouchEventType type, soldier *man);
	void sold_first_cd(float duration);//չλ1��ʼ��ȴ
	void sold_first_recover();//չλ1��ȴ���
	void sold_first_timer(float dt);//����ʱ
	Sprite *sprite_back0;//�����϶�����1
	bool change_x0=false;//�޸ķ���xλ��
	//չλ2
	Button *choose_back1;
	Text *back1_text = Text::create();//����CD
	void touchEvent_buy_1(Ref* pSender, Widget::TouchEventType type, soldier *man);
	void sold_second_cd(float duration);
	void sold_second_recover();
	void sold_second_timer(float dt);
	Sprite *sprite_back1;
	bool change_x1 = false;//�޸ķ���xλ��
	//չλ3
	Button *choose_back2;
	Text *back2_text = Text::create();//����CD
	void touchEvent_buy_2(Ref* pSender, Widget::TouchEventType type, soldier *man);
	void sold_third_cd(float duration);
	void sold_third_recover();
	void sold_third_timer(float dt);
	Sprite *sprite_back2;
	bool change_x2 = false;//�޸ķ���xλ��
	//չλ4
	Button *choose_back3;
	Text *back3_text = Text::create();//����CD
	void touchEvent_buy_3(Ref* pSender, Widget::TouchEventType type, soldier *man);
	void sold_fourth_cd(float duration);
	void sold_fourth_recover();
	void sold_fourth_timer(float dt);
	Sprite *sprite_back3;
	bool change_x3 = false;//�޸ķ���xλ��
	
	//��ʾ���
	Text *money_text = Text::create();

	void newFriend(float x,float y,int tag);//����һ���ѷ���λ
	void lack_of_money(float dt, Text *back_text);//ȱ�ٽ�Ǯ
	void set_visible(Text *back_text);//������ʾ

	//Ӣ��
	HeroSprite *hero;//Ӣ��ͨ��
	void hero_ani_manager();//��������
	void hero_reborn(float dt);//Ӣ������
	int reborn_cd;//����cdʱ��

	//��Ӫ
	Vector<AllSprites *> blueSide;//������λ
	static Vector<AllSprites *> redSide;//�췽��λ
	void Hittest_center();//��ײ�������
	void hittest_melee();//��ս�������
	void hittest_remote();//Զ�̹������
	bool ishit_mercenary(AllSprites *s1,AllSprites *s2);//�������
	void addBullet(int side,AllSprites *s);//��ӷ��е���

	static Vector<AllSprites *> allSprites;//���е�λ �������ò㼶˳��
	void setZorder();//���ø߶�
	void deathCenter();//�Ƴ���λ
	
	void coreCenter();//���AI
	void object_select(float dt);//����ж�����Ŀ��
	//CREATE_FUNC(MainGame);
	static MainGame* create(Vector<CheckBox *> choosed_objects);
};