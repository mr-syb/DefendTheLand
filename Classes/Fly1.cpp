#include "Fly1.h"

Fly1::Fly1(int side){
	Sprite::init();
	setName(Value(rand()).asString());//�������,scheduleOnce_Key��
	type_id = 21;//����id
	is_melee_unit = true;//��ս
	life = 1;//����ֵ
	orginal_life = life;
	speed = 6;//�ƶ��ٶ�
	farthest_distance = 220;//��Զ���
	damage_of_A = 4;
	attack_A_distance = 24;
	this->side = side;
	sprite_name = "public/Fly1.png";//��ʼͼƬ
	m_frameCache = CCSpriteFrameCache::sharedSpriteFrameCache();//����
	this->m_Sprite = Sprite::create(sprite_name);//hero_nameΪ�ļ���
	this->setAnchorPoint(Vec2(0.5, 0));
	m_Sprite->setAnchorPoint(Vec2(0, 0));
	m_Sprite->setPosition(Vec2(0, 27));
	this->setContentSize(Size(48, 48));
	this->addChild(m_Sprite);
	IsRunning = false;//û�ڷŶ���
	if (side == 0){//��ʼ��������
		SpriteDirecton = false;//��ɫ������
		m_Sprite->setFlipX(SpriteDirecton);
	}
	else{
		SpriteDirecton = true;//��ɫ������
		m_Sprite->setFlipX(SpriteDirecton);
	}
	ox = this->getPosition().x;
}
Fly1::~Fly1(){

}
void Fly1::core(){//���ܺ���
	if (life <= 0 && isdeath == false){//��������
		isdeath = true;
		isOver = true;
		return;
	}
	if (life <= 0){//ǿ�Ʒ���
		return;
	}
	if (canControl){//�����λ����ҿ��Կ���
		attack_ani();//����ڹ�����Χ��,����
		move();//��Ŀ���ƶ�
	}
}
void Fly1::object_select(Vector<AllSprites *> sprites){//�ж�����Ŀ��

}
void Fly1::attack_ani(){//����
	ani_block = true;
	hittest_A = true;
}
void Fly1::attack_A_effect(AllSprites *enemy){//��ѪЧ��
	SimpleAudioEngine::getInstance()->playEffect(Fly1_hit);
	set_life(-1);
	hittest_A = false;
	blood_effect(enemy);
	//�ط���λ��Ѫ
	enemy->set_life(-1 * damage_of_A);
}
void Fly1::blood_effect(AllSprites *sprite){//��ѪЧ��
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
		CCCallFuncN::create(sprite->get_n_Sprite(), callfuncN_selector(Fly1::removeself)), //ɾ���Լ�
		NULL);
	sprite->get_n_Sprite()->addChild(blood, 10);
	blood->setAnchorPoint(Vec2(0.5, 0.5));
	blood->setScale(0.4);
	blood->setPosition(Vec2(24, 24));
	blood->runAction(act);
}
void Fly1::removeself(Node *pSender){//�Ӹ����Ƴ�ͼƬ��Ч
	pSender->removeFromParentAndCleanup(true);
}
void Fly1::move(){//����Ŀ���ƶ�
	float ix = this->getPosition().x;
	float iy = this->getPosition().y;
	if (side){
		this->setPosition(Vec2(ix -= speed, iy));
		flew_distance += speed;
	}
	else{
		this->setPosition(Vec2(ix += speed, iy));
		flew_distance += speed;
	}
	if (flew_distance >= farthest_distance){//�ﵽ��Զ��̾�����
		auto fade = FadeOut::create(0.1);
		CCCallFunc* callFunc = CCCallFunc::create(this, callfunc_selector(Fly1::auto_Over));
		auto sequence = Sequence::create(fade, callFunc, NULL);
		m_Sprite->runAction(sequence);
	}
}
void Fly1::auto_Over(){//�Զ�����
	isdeath = true;
	isOver = true;
}
void Fly1::SetAnimation(int from, int to, bool run_directon, int loop){//����
	/*
	if (SpriteDirecton != run_directon)
	{
	SpriteDirecton = run_directon;
	m_Sprite->setFlipX(run_directon);
	}
	if (IsRunning)
	return;
	Vector<SpriteFrame* > cache;
	char txt[100] = {};
	int i;
	for (i = from; i <= to; i++)
	{
	sprintf_s(txt, "%s%d.png", name_each, i);
	SpriteFrame *sf = m_frameCache->spriteFrameByName(txt);
	cache.pushBack(sf);
	}
	//ʹ���б�����������
	Animation* animation = Animation::createWithSpriteFrames(cache, 0.2f);
	if (SpriteDirecton != run_directon)
	{
	SpriteDirecton = run_directon;

	}
	animation->setLoops(loop);//��ʾ����ѭ������
	//��������װ��һ������
	Animate* act = Animate::create(animation);
	m_Sprite->runAction(act);
	IsRunning = true;
	*/
}
void Fly1::StopAnimation(){//ֹͣ���ж���
	/*
	if (!IsRunning)
	return;
	m_Sprite->stopAllActions();//��ǰ����ֹͣ���ж���
	//�ָ�����ԭ���ĳ�ʼ����ͼ
	this->removeChild(m_Sprite, TRUE);//��ԭ���ľ���ɾ����
	m_Sprite = Sprite::createWithSpriteFrameName(sprite_name);//�ָ�����ԭ������ͼ����
	m_Sprite->setFlipX(SpriteDirecton);
	m_Sprite->setAnchorPoint(Vec2(0, 0));//Ҫ��������ê��
	this->addChild(m_Sprite);
	IsRunning = false;
	*/
}

bool Fly1::get_skill_J_ishurted(){
	return skill_J_ishurted;
}
void Fly1::set_skill_J_ishurted(bool skill_J_ishurted){
	this->skill_J_ishurted = skill_J_ishurted;
}
bool Fly1::get_skill_K_ishurted(){
	return skill_K_ishurted;
}
void Fly1::set_skill_K_ishurted(bool skill_K_ishurted){
	this->skill_K_ishurted = skill_K_ishurted;
}
int Fly1::get_life(){
	return life;
}
void Fly1::set_life(int delta){
	life += delta;
}
void Fly1::set_life_bar(int side){

}
bool Fly1::get_hittest_A(){
	return hittest_A;
}
void Fly1::set_hittest_A(bool hittest_A){
	this->hittest_A = hittest_A;
}
bool Fly1::get_Direction(){
	return SpriteDirecton;
}
bool Fly1::get_isblowup(){
	return isblowup;
}
void Fly1::set_isblowup(bool isblowup){
	this->isblowup = isblowup;
}
bool Fly1::get_canControl(){
	return canControl;
}
void Fly1::set_canControl(bool canControl){
	this->canControl = canControl;
}
bool Fly1::get_isOver(){
	return isOver;
}
bool Fly1::get_isdeath(){
	return isdeath;
}
int Fly1::get_typeid(){
	return type_id;
}
int Fly1::get_attack_A_distance(){
	return attack_A_distance;
}
bool Fly1::is_melee(){
	return is_melee_unit;
}
bool Fly1::is_fly_kind(){
	return true;
}