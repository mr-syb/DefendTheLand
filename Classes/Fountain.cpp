#include "Fountain.h"

Fountain::Fountain(int side){
	Sprite::init();
	setName(Value(rand()).asString());//�������,scheduleOnce_Key��
	type_id = 30;//����id
	is_melee_unit = true;//��ս
	life = 300;//����ֵ
	orginal_life = life;
	speed = 0;//�ƶ��ٶ�
	farthest_distance = 0;//��Զ���
	damage_of_A = 0;
	attack_A_distance = 24;
	this->side = side;
	m_frameCache = CCSpriteFrameCache::sharedSpriteFrameCache();//����
	if (side == 0){
		sprite_name = "public/fountain.png";//��ʼͼƬ
	}else{
		sprite_name = "public/fountain.png";//��ʼͼƬ
	}
	this->m_Sprite = Sprite::create(sprite_name);//hero_nameΪ�ļ���
	this->setAnchorPoint(Vec2(0.5, 0));
	m_Sprite->setAnchorPoint(Vec2(0, 0));
	//m_Sprite->setPosition(Vec2(0, 27));
	this->setContentSize(Size(48, 80));
	//�����n_Sprite
	n_Sprite = Sprite::create();
	n_Sprite->setAnchorPoint(Vec2(0, 0));
	this->addChild(n_Sprite);
	n_Sprite->addChild(m_Sprite);
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
	set_life_bar(side);
}
Fountain::~Fountain(){

}
void Fountain::core(){//���ܺ���
	if (life <= 0 && isdeath == false){//��������
		isdeath = true;
		deadth_ani();
		return;
	}
	if (life <= 0){//ǿ�Ʒ���
		return;
	}
	if (canControl){//�����λ����ҿ��Կ���
		//attack_ani();//����ڹ�����Χ��,����
		//move();//��Ŀ���ƶ�
	}
}
void Fountain::deadth_ani(){//��������
	SimpleAudioEngine::getInstance()->playEffect(tower_die);
	life_bar_fore->setVisible(false);//Ѫ�����ɼ�
	life_bar_back->setVisible(false);
	StopAnimation();//��ǰ����ֹͣ���ж���
	auto fadeout = FadeOut::create(1.5);//����Ч��
	CCCallFunc* callFunc = CCCallFunc::create(this, callfunc_selector(Fountain::setisOver));
	CCActionInterval* deathact = CCSequence::create(fadeout, callFunc, NULL);//���ж���
	m_Sprite->runAction(deathact);
}
void Fountain::setisOver(){
	isOver = true;
	MainGame::isGameOver = true;//��Ϸ����
	if (side == 0){//��Ϸ�Ƿ�ʤ���ж�
		MainGame::isVictory = false;
	}
	else{
		MainGame::isVictory = true;
	}
}
void Fountain::object_select(Vector<AllSprites *> sprites){//�ж�����Ŀ��

}
void Fountain::attack_ani(){//����
	ani_block = true;
	//hittest_A = true;
}
void Fountain::attack_A_effect(AllSprites *enemy){//��ѪЧ��
	set_life(-1);
	hittest_A = false;
	blood_effect(enemy);
	//�ط���λ��Ѫ
	enemy->set_life(-1 * damage_of_A);
}
void Fountain::blood_effect(Sprite *sprite){//��ѪЧ��
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
		CCCallFuncN::create(sprite, callfuncN_selector(Fountain::removeself)), //ɾ���Լ�
		NULL);
	sprite->addChild(blood, 10);
	blood->setAnchorPoint(Vec2(0.5, 0.5));
	blood->setScale(0.4);
	blood->setPosition(Vec2(24, 24));
	blood->runAction(act);
}
void Fountain::removeself(Node *pSender){//�Ӹ����Ƴ�ͼƬ��Ч
	pSender->removeFromParentAndCleanup(true);
}
void Fountain::move(){//����Ŀ���ƶ�
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
		CCCallFunc* callFunc = CCCallFunc::create(this, callfunc_selector(Fountain::auto_Over));
		auto sequence = Sequence::create(fade, callFunc, NULL);
		m_Sprite->runAction(sequence);
	}
}
void Fountain::auto_Over(){//�Զ�����
	isdeath = true;
	isOver = true;
}
void Fountain::SetAnimation(int from, int to, bool run_directon, int loop){//����
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
void Fountain::StopAnimation(){//ֹͣ���ж���
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

bool Fountain::get_skill_J_ishurted(){
	return skill_J_ishurted;
}
void Fountain::set_skill_J_ishurted(bool skill_J_ishurted){
	this->skill_J_ishurted = skill_J_ishurted;
}
bool Fountain::get_skill_K_ishurted(){
	return skill_K_ishurted;
}
void Fountain::set_skill_K_ishurted(bool skill_K_ishurted){
	this->skill_K_ishurted = skill_K_ishurted;
}
int Fountain::get_life(){
	return life;
}
void Fountain::set_life(int delta){
	life += delta;
	auto act = ScaleTo::create(0.2f, life / (float)orginal_life*0.6, 0.7);
	life_bar_fore->runAction(act);
}
void Fountain::set_life_bar(int side){
	if (side == 0){
		life_bar_fore = Sprite::create("public/blue_fore.png");
	}
	else{
		life_bar_fore = Sprite::create("public/red_fore.png");
	}
	life_bar_back = Sprite::create("public/life_back.png");
	life_bar_fore->setAnchorPoint(Vec2(0, 0.5));
	life_bar_back->setAnchorPoint(Vec2(0, 0.5));
	life_bar_fore->setPosition(Vec2(0, 85));
	life_bar_back->setPosition(Vec2(0, 85));
	life_bar_fore->setScaleX(0.6);
	life_bar_back->setScaleX(0.6);
	life_bar_fore->setScaleY(0.7);
	life_bar_back->setScaleY(0.7);
	life_bar_fore->setOpacity(180);
	life_bar_back->setOpacity(180);
	n_Sprite->addChild(life_bar_back, 1);
	n_Sprite->addChild(life_bar_fore, 1);
}
bool Fountain::get_hittest_A(){
	return hittest_A;
}
void Fountain::set_hittest_A(bool hittest_A){
	this->hittest_A = hittest_A;
}
bool Fountain::get_Direction(){
	return SpriteDirecton;
}
bool Fountain::get_isblowup(){
	return isblowup;
}
void Fountain::set_isblowup(bool isblowup){
	this->isblowup = isblowup;
}
bool Fountain::get_canControl(){
	return canControl;
}
void Fountain::set_canControl(bool canControl){
	this->canControl = canControl;
}
bool Fountain::get_isOver(){
	return isOver;
}
bool Fountain::get_isdeath(){
	return isdeath;
}
int Fountain::get_typeid(){
	return type_id;
}
int Fountain::get_attack_A_distance(){
	return attack_A_distance;
}
bool Fountain::is_melee(){
	return is_melee_unit;
}
Sprite* Fountain::get_n_Sprite(){
	return	n_Sprite;
}