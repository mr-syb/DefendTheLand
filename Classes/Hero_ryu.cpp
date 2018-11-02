#include "Hero_ryu.h"
Hero_ryu::Hero_ryu(int side){//��ʼ��
	Sprite::init();
	type_id = 0;//��������
	money = 50;//��ʼ��Ǯ
	speed = 1.5;//�ƶ��ٶ�
	original_speed = speed;
	life = 100;//����ֵ
	orginal_life = life;
	hero_walk_from = 4;
	hero_walk_to = 5;
	hero_attack_from = 0;
	hero_attack_to = 1;
	hero_die_from = 7;
	hero_die_to = 8;
	damage_of_A = 7;//ƽA�˺�
	A_cd = 0.6;//ƽAcd
	attack_A_distance = 24;//ƽA����
	distance_J = 180;//Jλ�Ƶľ���
	damage_of_J = 3;//J���˺�
	damage_of_J_blow = 7;//J���ܻ��ɵ��˺�
	height_blow = 48;//���ɸ߶�
	stun_time = 1.5f;//ѣ��ʱ��
	J_cd = 4;//J����cd
	speedBuff_K = 0.5;//K���������ƶ��ٶ���
	lifeBuff_K = 18;//K���ܻ�Ѫ��
	K_duration = 3;//K����BUFF����ʱ��
	K_cd = 8;//K����cd
	name_each = "Hero02f_";
	Hero_name = "Hero02f_6.png";//��ʼͼƬ
	attack_A_img = "hero_ryu/A.png";//ƽAͼƬ 
	skill_J_img = "hero_ryu/J.png";//����JͼƬ
	skill_K_img = "hero_ryu/K.png";//����KͼƬ
	icon_head_img = "hero_ryu/ryu.png";//ͷ��ͼƬ
	m_Sprite = Sprite::createWithSpriteFrameName("Hero02f_6.png");//hero_nameΪ�ļ���
	m_frameCache = CCSpriteFrameCache::sharedSpriteFrameCache();//����
	
	setAnchorPoint(Vec2(0.5, 0));
	m_Sprite->setAnchorPoint(Vec2(0, 0));
	setContentSize(Size(48, 48));
	//�����n_Sprite
	n_Sprite = Sprite::create();
	n_Sprite->setAnchorPoint(Vec2(0, 0));
	this->addChild(n_Sprite);
	n_Sprite->addChild(m_Sprite);
	born_effect();//������Ч
	set_life_bar(side);
}
Hero_ryu::~Hero_ryu(){

}

void Hero_ryu::SetAnimation(int from, int to, bool run_directon, int loop){//����
	if (HeroDirection != run_directon)
	{
		HeroDirection = run_directon;
		m_Sprite->setFlipX(run_directon);
	}
	if (IsRunning)
		return;
	Vector<SpriteFrame* > cache;//�����
	char txt[50] = {};
	int i;
	for (i = from; i <= to; i++)
	{
		sprintf_s(txt,"%s%d.png",name_each,i);
		SpriteFrame* sf = m_frameCache->spriteFrameByName(txt);
		cache.pushBack(sf);
	}
	//ʹ���б�����������  
	Animation* animation = Animation::createWithSpriteFrames(cache, 0.15f);
	if (HeroDirection != run_directon)
	{
		HeroDirection = run_directon;

	}
	animation->setLoops(loop);//��ʾ����ѭ������  
	//��������װ��һ������  
	Animate* act = Animate::create(animation);
	m_Sprite->runAction(act);
	IsRunning = true;
}

void Hero_ryu::StopAnimation(){//ֹͣ����
	if (!IsRunning)
		return;
	m_Sprite->stopAllActions();//��ǰ����ֹͣ���ж���  
	//�ָ�����ԭ���ĳ�ʼ����ͼ   
	//this->removeChild(m_Sprite, TRUE);//��ԭ���ľ���ɾ����
	n_Sprite->removeChild(m_Sprite, true);
	m_Sprite = Sprite::createWithSpriteFrameName(Hero_name);//�ָ�����ԭ������ͼ����  
	m_Sprite->setFlipX(HeroDirection);
	m_Sprite->setAnchorPoint(Vec2(0, 0));//Ҫ��������ê��
	//this->addChild(m_Sprite);
	n_Sprite->addChild(m_Sprite);//�޸ĵ�
	IsRunning = false;
}

void Hero_ryu::walk(bool run_directon,int loop){
	this->SetAnimation(hero_walk_from, hero_walk_to, run_directon, loop);
}
void Hero_ryu::attack_A_animation(bool run_directon){
	hero_ani_block = true;//��������
	if (m_Sprite->getAnchorPoint().x != 0.125&&m_Sprite->getAnchorPoint().y != 0.125){//�˶δ������˵���չ���˸����
		//m_Sprite->stopAllActions();//��ǰ����ֹͣ���ж���  
		//this->removeChild(m_Sprite, TRUE);//��ԭ���ľ���ɾ����
		n_Sprite->removeChild(m_Sprite, true);
		m_Sprite = Sprite::createWithSpriteFrameName("Hero02f_0.png");//�ָ�����ԭ������ͼ����  
		m_Sprite->setFlipX(HeroDirection);
		m_Sprite->setAnchorPoint(Vec2(0.125, 0.125));
		//this->addChild(m_Sprite);
		n_Sprite->addChild(m_Sprite);//�޸ĵ�
		IsRunning = false;
	}
	if (HeroDirection != run_directon)
	{
		HeroDirection = run_directon;
		m_Sprite->setFlipX(run_directon);
	}
	if (IsRunning)
		return;
	Vector<SpriteFrame* > cache;//�����
	char txt[50] = {};
	int i;
	for (i = hero_attack_from; i <= hero_attack_to; i++)
	{
		sprintf_s(txt, "%s%d.png", name_each, i);
		SpriteFrame* sf = m_frameCache->spriteFrameByName(txt);
		cache.pushBack(sf);
	}
	//ʹ���б�����������  
	Animation* animation = Animation::createWithSpriteFrames(cache, 0.15f);
	if (HeroDirection != run_directon)
	{
		HeroDirection = run_directon;

	}
	animation->setLoops(1);//��ʾѭ������  
	//��������װ��һ������  
	Animate* act = Animate::create(animation);
	IsRunning = true;

	CCCallFunc* callFunc = CCCallFunc::create(this, callfunc_selector(Hero_ryu::attack_A_img_end));
	CCActionInterval* attackact = CCSequence::create(act,callFunc, NULL);//���ж���
	m_Sprite->runAction(attackact);
}
void Hero_ryu::attack_A_img_end(){
	SimpleAudioEngine::getInstance()->playEffect(ryu_A);
	hittest_A = true;//ƽA�ж�
	//���¶���
	Vector<SpriteFrame* > cache;//�����
	SpriteFrame* sf = m_frameCache->spriteFrameByName("Hero02f_2.png");//�յ�����
	cache.pushBack(sf);
	//ʹ���б�����������  
	Animation* animation = Animation::createWithSpriteFrames(cache, 0.15f);
	//��������װ��һ������  
	Animate* act = Animate::create(animation);
	CCCallFunc *callFunc = CCCallFunc::create(CC_CALLBACK_0(Hero_ryu::attack_A_end, this));//����Hero_ryuʵ��λ��
	CCActionInterval* attackact = CCSequence::create(act, callFunc, NULL);//���ж���
	m_Sprite->runAction(attackact);
}
void Hero_ryu::attack_A_end(){
	hero_ani_block = false;//ʩ������
	attack_A = false;//ֹͣ����
	m_Sprite->stopAllActions();//��ǰ����ֹͣ���ж���  
	//�ָ�����ԭ���ĳ�ʼ����ͼ
	//this->removeChild(m_Sprite, TRUE);//��ԭ���ľ���ɾ����
	n_Sprite->removeChild(m_Sprite, true);
	m_Sprite = Sprite::createWithSpriteFrameName(Hero_name);//�ָ�����ԭ������ͼ����  
	m_Sprite->setFlipX(HeroDirection);
	m_Sprite->setAnchorPoint(Vec2(0, 0));//Ҫ��������ê��
	//this->addChild(m_Sprite);
	n_Sprite->addChild(m_Sprite);//�޸ĵ�
	IsRunning = false;
}
void Hero_ryu::attack_A_effect(AllSprites *enemy){//��ѪЧ��
	SimpleAudioEngine::getInstance()->playEffect(hit);
	hittest_A = false;//����Ϊ����
	blood_effect(enemy);
	//�ط���λ��Ѫ
	enemy->set_life(-1*damage_of_A);
}
void Hero_ryu::skill_J_ani(Vector<AllSprites *> allEnemy){//J����
	SimpleAudioEngine::getInstance()->playEffect(ryu_J_start);
	hero_ani_block = true;//��������
	skill_J = false;//����ʩ��һ��
	hittest_J = true;//����
	skill_J_damage = true;//J��������˺�
	skill_J_effect();//��ɳͼƬ��Ч
	if (m_Sprite->getAnchorPoint().x != 0.125&&m_Sprite->getAnchorPoint().y != 0.125){//�˶δ������˵���չ���˸����
		//m_Sprite->stopAllActions();//��ǰ����ֹͣ���ж���
		//this->removeChild(m_Sprite, TRUE);//��ԭ���ľ���ɾ����
		n_Sprite->removeChild(m_Sprite, true);
		m_Sprite = Sprite::createWithSpriteFrameName("Hero02f_0.png");//�ָ�����ԭ������ͼ����  
		m_Sprite->setFlipX(HeroDirection);
		m_Sprite->setAnchorPoint(Vec2(0.125, 0.125));
		//this->addChild(m_Sprite);
		n_Sprite->addChild(m_Sprite);//�޸ĵ�
		IsRunning = false;
	}
	//����λ��
	int flag = 1;
	if (HeroDirection){
		flag = -1;
	}
	else{
		flag = 1;
	}
	CCMoveBy *moveBy = CCMoveBy::create(0.3f, Vec2(distance_J*flag,0));//����λ��
	//���ж���
	CCCallFunc *callFunc = CCCallFunc::create(CC_CALLBACK_0(Hero_ryu::skill_J_img_end, this,allEnemy));
	CCActionInterval* attackact = CCSequence::create(moveBy,callFunc,NULL);//���ж���
	runAction(attackact);
}
void Hero_ryu::skill_J_img_end(Vector<AllSprites *> allEnemy){//J������β����
	if (life <= 0) return;//���BUG
	SimpleAudioEngine::getInstance()->playEffect(ryu_J_end);
	//���¶���
	Vector<SpriteFrame* > cache;//�����
	SpriteFrame* sf = m_frameCache->spriteFrameByName("Hero02f_2.png");//�յ�����
	cache.pushBack(sf);
	//ʹ���б�����������
	Animation* animation = Animation::createWithSpriteFrames(cache, 0.15f);
	//animation->setLoops(1);//��ʾѭ������  
	//��������װ��һ������  
	Animate* act = Animate::create(animation);
	CCCallFunc *callFunc = CCCallFunc::create(CC_CALLBACK_0(Hero_ryu::skill_J_end, this,allEnemy));//����Hero_ryuʵ��λ��
	CCActionInterval* attackact = CCSequence::create(act, callFunc, NULL);//���ж���
	m_Sprite->runAction(attackact);
	skill_J_blowup();//����
	//blowup = true;//��ʼ����
}
void Hero_ryu::skill_J_blowup(){
	blowup = true;//��ʼ����
	Vector<SpriteFrame* > cache;//�����
	char txt[50] = {};
	int i;
	for (i = 0; i <= 3; i++)
	{
		sprintf_s(txt, "%s%d.png", "blowup_", i);
		SpriteFrame* sf = m_frameCache->spriteFrameByName(txt);
		cache.pushBack(sf);
	}
	//ʹ���б�����������  
	Animation* ani = Animation::createWithSpriteFrames(cache, 0.2f);
	auto blow = Sprite::create();
	Action * act = Sequence::create(
		Animate::create(ani),  //����
		CCCallFunc::create(CC_CALLBACK_0(Hero_ryu::skill_J_setblowup, this)),//���ɽ���
		CCCallFuncN::create(n_Sprite, callfuncN_selector(Hero_ryu::removeself)), //ɾ���Լ�
		NULL);
	n_Sprite->addChild(blow, 3);
	blow->setAnchorPoint(Vec2(0.5, 0.5));
	blow->setScale(0.7);
	blow->setPosition(Vec2(24, 6));
	blow->runAction(act);
}
void Hero_ryu::skill_J_setblowup(){
	blowup = false;
}
void Hero_ryu::skill_J_end(Vector<AllSprites *> allEnemy){
	hero_ani_block = false;//ʩ������
	hittest_J = false;//����
	skill_J_damage = false;//����ֹͣ
	if (life <= 0) return;//���BUG
	m_Sprite->stopAllActions();//��ǰ����ֹͣ���ж���
	//�ָ�����ԭ���ĳ�ʼ����ͼ
	//this->removeChild(m_Sprite, TRUE);//��ԭ���ľ���ɾ����
	n_Sprite->removeChild(m_Sprite, true);
	m_Sprite = Sprite::createWithSpriteFrameName(Hero_name);//�ָ�����ԭ������ͼ����
	m_Sprite->setFlipX(HeroDirection);
	m_Sprite->setAnchorPoint(Vec2(0, 0));//Ҫ��������ê��
	//this->addChild(m_Sprite);
	n_Sprite->addChild(m_Sprite);//�޸ĵ�
	IsRunning = false;
    //���õ���skill_J_ishurted=false
	for (int i = 0; i < allEnemy.size(); i++){
		allEnemy.at(i)->set_skill_J_ishurted(false);
		allEnemy.at(i)->set_isblowup(false);
	}
}
void Hero_ryu::skill_J_attack(AllSprites *enemy){//����������J����
	bool canMove = true;
	int id=enemy->get_typeid();
	if (id >= 30){//���������ɻ���
		canMove = false;
	}
	if (HeroDirection){
		if (canMove){
			enemy->setPosition(Vec2(this->getPosition().x - 38, enemy->getPosition().y));
		}
		else{
			setPosition(Vec2(enemy->getPosition().x + enemy->getContentSize().width, getPosition().y));
		}
	}
	else{
		if (canMove){
			enemy->setPosition(Vec2(this->getPosition().x + 38, enemy->getPosition().y));
		}
		else{
			setPosition(Vec2(enemy->getPosition().x - enemy->getContentSize().width, getPosition().y));
		}
	}
	bool ishurted = enemy->get_skill_J_ishurted();
	if (skill_J_damage && ishurted == false){//��ײ
		blood_effect(enemy);
		enemy->set_skill_J_ishurted(true);
		//�з���λ��Ѫ
		enemy->set_life(-1*damage_of_J);
	}
	bool isblowup_enemy = enemy->get_isblowup();
	if (blowup && isblowup_enemy == false && canMove){//����
		blood_effect(enemy);
		skill_J_bloweffect(enemy);//ѣ�ζ���
		skill_J_blowmove(enemy);//����λ��
		enemy->set_isblowup(true);
		enemy->set_life(-1 * damage_of_J_blow);
		enemy->set_canControl(false);//�������ܺ��Ĳ��ɿ���
		scheduleOnce(CC_CALLBACK_1(Hero_ryu::skill_J_blowdelay, this, enemy), stun_time, enemy->getName());
	}
}
void Hero_ryu::skill_J_blowdelay(float dt, AllSprites *enemy){//ѣ��ʱ��
	enemy->set_canControl(true);
}
void Hero_ryu::skill_J_bloweffect(AllSprites *enemy){
	Vector<SpriteFrame* > cache;//�����
	char txt[50] = {};
	int i;
	for (i = 0; i <= 11; i++)
	{
		sprintf_s(txt, "%s%d.png", "stun_", i);
		SpriteFrame* sf = m_frameCache->spriteFrameByName(txt);
		cache.pushBack(sf);
	}
	//ʹ���б�����������  
	Animation* ani = Animation::createWithSpriteFrames(cache, 0.1f);
	auto stunning = Sprite::create();
	Action * act = Sequence::create(
		Animate::create(ani),  //����
		CCCallFuncN::create(enemy, callfuncN_selector(Hero_ryu::removeself)), //ɾ���Լ�
		NULL);
	auto n_enemy = enemy->get_n_Sprite();
	n_enemy->addChild(stunning, 5);
	stunning->setAnchorPoint(Vec2(0.5, 0.5));
	stunning->setScale(0.3);
	stunning->setScaleX(0.22);
	stunning->setPosition(Vec2(24, 56));
	stunning->runAction(act);
}
void Hero_ryu::skill_J_blowmove(AllSprites *enemy){//�������
	CCJumpBy *blow = CCJumpTo::create(0.5f, Vec2(0, 0), height_blow, 1);
	//���ж���
	CCActionInterval* act = CCSequence::create(blow, NULL);//���ж���
	auto n_enemy=enemy->get_n_Sprite();
	n_enemy->runAction(act);
	//enemy->runAction(act);
}
void Hero_ryu::skill_J_effect(){
	float x = m_Sprite->getPosition().x;
	float y = m_Sprite->getPosition().y;
	Vector<SpriteFrame* > cache;//�����
	char txt[50] = {};
	int i;
	for (i = 0; i <= 4; i++)
	{
		sprintf_s(txt, "%s%d.png", "J_", i);
		SpriteFrame* sf = m_frameCache->spriteFrameByName(txt);
		cache.pushBack(sf);
	}
	//ʹ���б�����������  
	Animation* ani= Animation::createWithSpriteFrames(cache, 0.1f);
	auto sprite = Sprite::create();
	Action * act = Sequence::create(
		Animate::create(ani),  //����
		CCCallFuncN::create(sprite, callfuncN_selector(Hero_ryu::removeself)), //ɾ���Լ�
		NULL);
	n_Sprite->addChild(sprite);
	sprite->setAnchorPoint(Vec2(0.8, -0.05));
	if (HeroDirection){
		sprite->setFlipX(-1);
		sprite->setPosition(Vec2(x+90, y));
	}
	else{
		sprite->setPosition(Vec2(x, y));
	}
	sprite->runAction(act);
}
void Hero_ryu::skill_K_ani(Vector<AllSprites *> allEnemy){//K����
	SimpleAudioEngine::getInstance()->playEffect(ryu_K);
	skill_K = false;//����ʩ��һ��
	hittest_K = true;//���ܿ�ʼ�ж�
	skill_K_effect();//K���ܶ���
}
void Hero_ryu::skill_K_effect(){
	float x = m_Sprite->getPosition().x;
	float y = m_Sprite->getPosition().y;
	Vector<SpriteFrame* > cache;//�����
	char txt[50] = {};
	int i;
	for (i = 0; i <= 17; i++)
	{
		sprintf_s(txt, "%d.png", i);
		SpriteFrame* sf = m_frameCache->spriteFrameByName(txt);
		cache.pushBack(sf);
	}
	CCCallFunc *callFunc = CCCallFunc::create(CC_CALLBACK_0(Hero_ryu::skill_K_Buff, this));
	//ʹ���б�����������
	Animation* ani = Animation::createWithSpriteFrames(cache, 0.1f);
	auto sprite = Sprite::create();
	Action * act = Sequence::create(Animate::create(ani), CCCallFuncN::create(sprite, callfuncN_selector(Hero_ryu::removeself)), callFunc, NULL); //ɾ���Լ�	
	n_Sprite->addChild(sprite);
	sprite->setScale(0.8);
	sprite->setAnchorPoint(Vec2(0.5, 0.5));
	sprite->setPosition(Vec2(24,24));
	sprite->setOpacity(230);
	sprite->setZOrder(2);
	sprite->runAction(act);
}
void Hero_ryu::skill_K_Buff(){//K����buff
	if (life <= 0) return;//���BUG
	set_life(lifeBuff_K);
	set_speed(speedBuff_K);
	scheduleOnce(schedule_selector(Hero_ryu::set_speed_orginally), K_duration);
}
void Hero_ryu::removeself(Node *pSender){//�Ӹ����Ƴ�ͼƬ��Ч
	pSender->removeFromParentAndCleanup(true);
}
void Hero_ryu::blood_effect(AllSprites *sprite){//��ѪЧ��
	Vector<SpriteFrame* > cache;//�����
	char txt[50] = {};
	int i;
	for (i = 0; i <= 4; i++)
	{
		sprintf_s(txt, "%s%d.png", "blood_", i);
		SpriteFrame* sf = m_frameCache->spriteFrameByName(txt);
		cache.pushBack(sf);
	}
	//ʹ���б�����������  
	Animation* ani = Animation::createWithSpriteFrames(cache, 0.2f);
	auto blood = Sprite::create();
	Action * act = Sequence::create(
		Animate::create(ani),  //����
		CCCallFuncN::create(sprite->get_n_Sprite(), callfuncN_selector(Hero_ryu::removeself)), //ɾ���Լ�
		NULL);
	sprite->get_n_Sprite()->addChild(blood, 5);
	blood->setAnchorPoint(Vec2(0.5,0.5));
	blood->setScale(0.4);
	blood->setPosition(Vec2(24,24));
	blood->runAction(act);
}
void Hero_ryu::death_ani(){
	life_bar_fore->setVisible(false);//Ѫ�����ɼ�
	life_bar_back->setVisible(false);
	set_statusoriginal();//����״̬��ԭ
	StopAnimation();//ֹͣ����
	stopAllActions();//ֹͣ���ж���
	isdeath = true;//�Ѿ�����
	Vector<SpriteFrame* > cache;//�����
	char txt[50] = {};
	int i;
	for (i = hero_die_from; i <= hero_die_to; i++)
	{
		sprintf_s(txt, "%s%d.png", name_each, i);
		SpriteFrame* sf = m_frameCache->spriteFrameByName(txt);
		cache.pushBack(sf);
	}
	//ʹ���б�����������
	Animation* ani = Animation::createWithSpriteFrames(cache, 0.2f);
	ani->setLoops(1);//��ʾѭ������  
	//��������װ��һ������  
	Animate* act = Animate::create(ani);
	IsRunning = true;
	auto fadeout = FadeOut::create(3);//����Ч��
	CCCallFunc* callFunc = CCCallFunc::create(this, callfunc_selector(Hero_ryu::death_effect));
	auto spawn = Spawn::create(fadeout, callFunc, NULL);//����ִ��
	CCActionInterval* deathact = CCSequence::create(act, spawn, NULL);//���ж���
	m_Sprite->runAction(deathact);
}
void Hero_ryu::death_effect(){
	Vector<SpriteFrame* > cache;//�����
	char txt[50] = {};
	int i;
	for (i = 0; i <= 8; i++)
	{
		sprintf_s(txt, "%s%d.png", "death_", i);
		SpriteFrame* sf = m_frameCache->spriteFrameByName(txt);
		cache.pushBack(sf);
	}
	//ʹ���б�����������  
	Animation* ani = Animation::createWithSpriteFrames(cache, 0.15f);
	ani->setLoops(1);//��ʾѭ������
	auto sprite = Sprite::create();
	auto fadeout = FadeOut::create(1.2);//����Ч��
	Action * act = Sequence::create(
		Animate::create(ani),  //����
		fadeout,
		CCCallFuncN::create(sprite, callfuncN_selector(Hero_ryu::removeself)), //ɾ���Լ�
		NULL);
	IsRunning = true;
	n_Sprite->addChild(sprite, 6);
	sprite->setAnchorPoint(Vec2(0.5, 0.5));
	sprite->setScale(1);
	sprite->setPosition(Vec2(24, 24));
	sprite->runAction(act);
}
void Hero_ryu::set_statusoriginal(){//����״̬��ԭ(����ٿ���)
	attack_A = false;//�Ƿ�ƽA
	hittest_A = false;
	skill_J = false;//�Ƿ�ʩ�ż���J
	isWalk = false;//�Ƿ����ƶ�
	blowup = false;//�Ƿ����
	hittest_J = false;
	skill_J_damage = false;//J��������˺�
	skill_K = false;//�Ƿ�ʩ�ż���K
	hittest_K = false;
	isblowup = false;//�Ƿ񱻻���
	//IsRunning = false;//���������ã���ʵ��running��;
}
void Hero_ryu::reborn(){//Ӣ������
	hero_ani_block = false;//������������
	life_bar_fore->setVisible(true);//Ѫ���ɼ�
	life_bar_back->setVisible(true);
	StopAnimation();
	HeroDirection = false;
	set_life(orginal_life);
	isdeath = false;
	set_statusoriginal();
	born_effect();//������Ч
}
void Hero_ryu::born_effect(){//������Ч
	Vector<SpriteFrame* > cache;//�����
	char txt[50] = {};
	int i;
	for (i = 0; i <= 3; i++)
	{
		sprintf_s(txt, "%s%d.png", "born_", i);
		SpriteFrame* sf = m_frameCache->spriteFrameByName(txt);
		cache.pushBack(sf);
	}
	//ʹ���б�����������  
	Animation* ani = Animation::createWithSpriteFrames(cache, 0.15f);
	ani->setLoops(1);//��ʾѭ������  

	Vector<SpriteFrame* > cache0;//�����
	SpriteFrame* sf0 = m_frameCache->spriteFrameByName("born_3.png");
	cache0.pushBack(sf0);
	//ʹ���б�����������  
	Animation* animation = Animation::createWithSpriteFrames(cache0, 0.2f);
	//��������װ��һ������  
	Animate* act0 = Animate::create(animation);
	auto fadeout = FadeOut::create(3);//����Ч��
	auto sprite = Sprite::create();
	Action *act = Sequence::create(
		Animate::create(ani),  //����
		act0,
		fadeout,
		CCCallFuncN::create(sprite, callfuncN_selector(Hero_ryu::removeself)), //ɾ���Լ�
		NULL);
	IsRunning = true;
	n_Sprite->addChild(sprite, -1);
	sprite->setAnchorPoint(Vec2(0.5, 0.5));
	sprite->setScale(0.4);
	sprite->setPosition(Vec2(24, 0));
	sprite->runAction(act);
}
void Hero_ryu::set_life_bar(int side){//����Ѫ����ʽ
	if (side == 0){
		life_bar_fore = Sprite::create("public/blue_fore.png");
	}
	else{
		life_bar_fore = Sprite::create("public/red_fore.png");
	}
	life_bar_back = Sprite::create("public/life_back.png");
	life_bar_fore->setAnchorPoint(Vec2(0, 0.5));
	life_bar_back->setAnchorPoint(Vec2(0, 0.5));
	life_bar_fore->setPosition(Vec2(0, 57));
	life_bar_back->setPosition(Vec2(0, 57));
	life_bar_fore->setScaleX(0.6);
	life_bar_back->setScaleX(0.6);
	life_bar_fore->setOpacity(180);
	life_bar_back->setOpacity(180);
	n_Sprite->addChild(life_bar_back,1);
	n_Sprite->addChild(life_bar_fore, 1);
}
void Hero_ryu::set_life_bar_scaleX(float per){//����Ѫ���ٷֱ�
	auto act = ScaleTo::create(0.2f,per,1);
	life_bar_fore->runAction(act);
}
int Hero_ryu::get_typeid(){
	return type_id;
}
bool Hero_ryu::get_hero_ani_block(){
	return hero_ani_block;
}
void Hero_ryu::set_hero_ani_block(bool hero_ani_block){
	this->hero_ani_block = hero_ani_block;
}
bool Hero_ryu::get_Direction(){
	return HeroDirection;
}
bool Hero_ryu::get_hittest_A(){
	return hittest_A;
}
void Hero_ryu::set_hittest_A(bool hittest_A){
	this->hittest_A = hittest_A;
}
bool Hero_ryu::get_hittest_J(){
	return hittest_J;
}
void Hero_ryu::set_hittest_J(bool hittest_J){
	this->hittest_J = hittest_J;
}
bool Hero_ryu::get_hittest_K(){
	return hittest_K;
}
void Hero_ryu::set_hittest_K(bool hittest_K){
	this->hittest_K = hittest_K;
}
bool Hero_ryu::get_isWalk(){
	return isWalk;
}
bool Hero_ryu::get_attack_A(){
	return attack_A;
}
void Hero_ryu::set_attack_A(bool attack_A){
	this->attack_A = attack_A;
}
float Hero_ryu::get_A_cd(){
	return A_cd;
}
int Hero_ryu::get_attack_A_distance(){
	return attack_A_distance;
}
bool Hero_ryu::get_skill_J(){
	return skill_J;
}
void Hero_ryu::set_skill_J(bool skill_J){
	this->skill_J = skill_J;
}
float Hero_ryu::get_J_cd(){
	return J_cd;
}
bool Hero_ryu::get_skill_K(){
	return skill_K;
}
void Hero_ryu::set_skill_K(bool skill_K){
	this->skill_K = skill_K;
}
float Hero_ryu::get_K_cd(){
	return K_cd;
}
int Hero_ryu::get_hero_walk_from(){
	return hero_walk_from;
}
int Hero_ryu::get_hero_walk_to(){
	return hero_walk_to;
}
int Hero_ryu::get_hero_attack_from(){
	return hero_attack_from;
}
int Hero_ryu::get_hero_attack_to(){
	return hero_attack_to;
}
int Hero_ryu::get_hero_die_from(){
	return hero_die_from;
}
int Hero_ryu::get_hero_die_to(){
	return hero_die_to;
}
std::string Hero_ryu::get_attack_A_img(){
	return attack_A_img;
}
std::string Hero_ryu::get_skill_J_img(){
	return skill_J_img;
}
std::string Hero_ryu::get_skill_K_img(){
	return skill_K_img;
}
std::string Hero_ryu::get_icon_head_img(){
	return icon_head_img;
}
bool Hero_ryu::get_isOver(){
	return isOver;
}
bool Hero_ryu::get_isdeath(){
	return isdeath;
}
int Hero_ryu::get_life(){
	return life;
}
void Hero_ryu::set_life(int delta){
	life += delta;
	if (life > orginal_life){
		life = orginal_life;
	}
	if (life < 0){
		life = 0;
	}
	set_life_bar_scaleX(life / (float)orginal_life*0.6);//����Ѫ���ٷֱ�
}
float Hero_ryu::get_speed(){
	return speed;
}
void Hero_ryu::set_speed(float delta){
	speed += delta;
}
void Hero_ryu::set_speed_orginally(float dt){
	speed = original_speed;
}
bool Hero_ryu::get_isblowup(){
	return isblowup;
}
void Hero_ryu::set_isblowup(bool isblowup){
	this->isblowup = isblowup;
}
int Hero_ryu::get_money(){
	return money;
}
void Hero_ryu::set_isMoving(bool isMoving){
	this->isMoving = isMoving;
}
bool Hero_ryu::get_isMoving(){
	return isMoving;
}
Sprite* Hero_ryu::get_n_Sprite(){
	return	n_Sprite;
}