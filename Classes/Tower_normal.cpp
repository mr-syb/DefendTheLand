#include "Tower_normal.h"

Tower_normal::Tower_normal(int side){
	Sprite::init();
	setName(Value(rand()).asString());//�������,scheduleOnce_Key��
	type_id = 31;//����id
	is_melee_unit = false;//Զ��
	fly_kind = 2;
	life = 400;//����ֵ
	orginal_life = life;
	speed = 0;//�ƶ��ٶ�
	damage_of_A = 0;
	attack_A_distance = 200;
	this->side = side;
	sprite_name = "public/tower_normal.png";//��ʼͼƬ
	m_frameCache = CCSpriteFrameCache::sharedSpriteFrameCache();//����
	this->m_Sprite = Sprite::create(sprite_name);
	this->setAnchorPoint(Vec2(0.5, 0));
	m_Sprite->setAnchorPoint(Vec2(0, 0));
	this->setContentSize(Size(48, 80));
	//�����n_Sprite
	n_Sprite = Sprite::create();
	n_Sprite->setAnchorPoint(Vec2(0, 0));
	this->addChild(n_Sprite);
	n_Sprite->addChild(m_Sprite);
	IsRunning = false;//û�ڷŶ���
	if (side == 0){//��ʼ��������
		SpriteDirecton = false;//��ɫ������
	}
	else{
		SpriteDirecton = true;//��ɫ������
	}
	set_life_bar(side);
}
Tower_normal::~Tower_normal(){

}
void Tower_normal::core(){//���ܺ���
	if (life <= 0 && isdeath == false){//��������
		isdeath = true;
		deadth_ani();
		return;
	}
	if (life <= 0){//ǿ�Ʒ���
		return;
	}
	if (canControl){//�����λ����ҿ��Կ���
		attack_ani();//����ڹ�����Χ��,����
		move();//��Ŀ���ƶ�
	}
	else{
		idle();//վ��
	}
}
void Tower_normal::object_select(Vector<AllSprites *> sprites){//�ж�����Ŀ��
	Vector<AllSprites *> chancellor;
	//�ų�������λ�ͷ��е���
	for (int i = 0; i < sprites.size(); i++){
		if (!sprites.at(i)->get_isdeath() && !sprites.at(i)->is_fly_kind()){
			chancellor.pushBack(sprites.at(i));
		}
	}
	if (chancellor.size() == 0){//�������������
		return;
	}
	float min_x;
	AllSprites *min_object;
	min_object = chancellor.at(0);
	min_x = (pow(this->getPosition().x - chancellor.at(0)->getPosition().x, 2) + pow(this->getPosition().y - chancellor.at(0)->getPosition().y, 2));//��С����
	for (int i = 1; i < chancellor.size(); i++){//���������б�
		float distance = pow(this->getPosition().x - chancellor.at(i)->getPosition().x, 2) + pow(this->getPosition().y - chancellor.at(i)->getPosition().y, 2);
		if (distance < min_x){
			min_x = distance;
			min_object = chancellor.at(i);
		}
	}
	object_aim = min_object;
	/*
	AllSprites *s1 = nullptr, *s2 = nullptr, *s3 = nullptr;//��ѡ������λ
	float max_x;
	if (side == 0){//�������ɫ��
		for (int i = 0; i < (chancellor.size() > 3 ? 3 : chancellor.size()); i++){//�ҵ���ǰ���������
			max_x = chancellor.at(i)->getPosition().x;
			for (int j = i+1; j < chancellor.size(); j++){//���������б�
				if (chancellor.at(j)->getPosition().x < max_x){
					max_x = chancellor.at(j)->getPosition().x;
					chancellor.swap(i, j);//����λ��
				}
			}
		}
	}
	else{//����Ǻ�ɫ��
		for (int i = 0; i < (chancellor.size() > 3 ? 3 : chancellor.size()); i++){//�ҵ���ǰ���������
			max_x = chancellor.at(i)->getPosition().x;
			for (int j = i+1; j < chancellor.size(); j++){//���������б�
				if (chancellor.at(j)->getPosition().x > max_x){
					max_x = chancellor.at(j)->getPosition().x;
					chancellor.swap(i, j);//����λ��
				}
			}
		}
	}
	if (chancellor.size() < 2){
		s1 = chancellor.at(0);
	}
	else if (chancellor.size() < 3){
		s1 = chancellor.at(0);
		s2 = chancellor.at(1);
	}
	else{
		s1 = chancellor.at(0);
		s2 = chancellor.at(1);
		s3 = chancellor.at(2);
	}
	//�ж�s123�ĸ����Լ����(�����ֱ�����)
	if (s2 == nullptr){
		object_aim = s1;
	}
	else if (s3 == nullptr){
		float distance1 = pow(this->getPosition().x - s1->getPosition().x, 2) + pow(this->getPosition().y - s1->getPosition().y, 2);
		float distance2 = pow(this->getPosition().x - s2->getPosition().x, 2) + pow(this->getPosition().y - s2->getPosition().y, 2);
		if (distance1 > distance2){
			distance1 = distance2;
			s1 = s2;
		}
		object_aim = s1;
	}
	else{
		float distance1 = pow(this->getPosition().x - s1->getPosition().x, 2) + pow(this->getPosition().y - s1->getPosition().y, 2);
		float distance2 = pow(this->getPosition().x - s2->getPosition().x, 2) + pow(this->getPosition().y - s2->getPosition().y, 2);
		float distance3 = pow(this->getPosition().x - s3->getPosition().x, 2) + pow(this->getPosition().y - s3->getPosition().y, 2);
		if (distance1 > distance2){
			distance1 = distance2;
			s1 = s2;
		}
		if (distance1 > distance3){
			distance1 = distance3;
			s1 = s3;
		}
		object_aim = s1;
	}
	*/
}
void Tower_normal::attack_ani(){//����
	if (!attack_A || ani_block){//������ǹ���״̬���߶���������
		return;
	}
	if (IsRunning)
		return;
	attack_A = false;//ֹͣ����
	hittest_A = true;//ƽA�ж�
	SimpleAudioEngine::getInstance()->playEffect(tower_normal_A);
}
void Tower_normal::attack_A_effect(AllSprites *enemy){//��ѪЧ��
	hittest_A = false;
}
void Tower_normal::blood_effect(AllSprites *sprite){//��ѪЧ��
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
		CCCallFuncN::create(sprite, callfuncN_selector(Tower_normal::removeself)), //ɾ���Լ�
		NULL);
	sprite->addChild(blood, 10);
	blood->setAnchorPoint(Vec2(0.5, 0.5));
	blood->setScale(0.4);
	blood->setPosition(Vec2(24, 24));
	blood->runAction(act);
}
void Tower_normal::removeself(Node *pSender){//�Ӹ����Ƴ�ͼƬ��Ч
	pSender->removeFromParentAndCleanup(true);
}
void Tower_normal::move(){//����Ŀ���ƶ�
	if (object_aim == nullptr || ani_block){
		return;
	}
	float x = object_aim->getPosition().x;
	float y = object_aim->getPosition().y;
	float w = object_aim->getContentSize().width;
	float h = object_aim->getContentSize().height;
	float ix = this->getPosition().x;
	float iy = this->getPosition().y;
	float iw = this->getContentSize().width;
	float ih = this->getContentSize().height;
	if (x > ix){//���ĳ���
		SpriteDirecton = false;
	}
	else{
		SpriteDirecton = true;
	}
	//���������ж�
	if (attack_gap <= 80){//�������ж��������в�ͬ
		attack_gap++;
	}
	if (x > ix && (x - w*0.5 - ix - attack_A_distance)>0){

	}
	else if (x < ix && (x + w*0.5 - ix + attack_A_distance)<0){
		
	}
	/*
	else if (y > iy&&abs(y - iy) > 10){

	}
	else if (y < iy&&abs(y - iy) > 10){

	}
	*/
	else if (attack_gap>80){//��������
		attack_A = true;
		attack_gap = 0;
		point=object_aim->getPosition();
	}
	else{
		idle();
	}
}
void Tower_normal::idle(){
	StopAnimation();//��ǰ����ֹͣ���ж���  
	//�ָ�����ԭ���ĳ�ʼ����ͼ
	//this->removeChild(m_Sprite, TRUE);//��ԭ���ľ���ɾ����
	n_Sprite->removeChild(m_Sprite, true);
	m_Sprite = Sprite::create(sprite_name);//�ָ�����ԭ������ͼ����  
	//m_Sprite->setFlipX(SpriteDirecton);
	m_Sprite->setAnchorPoint(Vec2(0, 0));//Ҫ��������ê��
	//this->addChild(m_Sprite);
	n_Sprite->addChild(m_Sprite);//�޸ĵ�
	IsRunning = false;
}
void Tower_normal::deadth_ani(){
	SimpleAudioEngine::getInstance()->playEffect(tower_die);
	life_bar_fore->setVisible(false);//Ѫ�����ɼ�
	life_bar_back->setVisible(false);
	StopAnimation();//��ǰ����ֹͣ���ж���
	auto fadeout = FadeOut::create(1.5);//����Ч��
	CCCallFunc* callFunc = CCCallFunc::create(this, callfunc_selector(Tower_normal::setisOver));
	CCActionInterval* deathact = CCSequence::create(fadeout, callFunc, NULL);//���ж���
	m_Sprite->runAction(deathact);
}
void Tower_normal::setisOver(){
	isOver = true;
}
void Tower_normal::SetAnimation(int from, int to, bool run_directon, int loop){//����
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
	Animation* animation = Animation::createWithSpriteFrames(cache, 0.25f);
	if (SpriteDirecton != run_directon)
	{
		SpriteDirecton = run_directon;

	}
	animation->setLoops(loop);//��ʾ����ѭ������  
	//��������װ��һ������  
	Animate* act = Animate::create(animation);
	m_Sprite->runAction(act);
	IsRunning = true;
}
void Tower_normal::StopAnimation(){//ֹͣ���ж���
	if (!IsRunning)
		return;
	m_Sprite->stopAllActions();//��ǰ����ֹͣ���ж���  
	//�ָ�����ԭ���ĳ�ʼ����ͼ   
	//this->removeChild(m_Sprite, TRUE);//��ԭ���ľ���ɾ����
	n_Sprite->removeChild(m_Sprite, true);
	m_Sprite = Sprite::create(sprite_name);//�ָ�����ԭ������ͼ����  
	//m_Sprite->setFlipX(SpriteDirecton);
	m_Sprite->setAnchorPoint(Vec2(0, 0));//Ҫ��������ê��
	//this->addChild(m_Sprite);
	n_Sprite->addChild(m_Sprite);//�޸ĵ�
	IsRunning = false;
	ani_block = false;//����û������
	attack_A = false;//����ȡ��
}
bool Tower_normal::get_skill_J_ishurted(){
	return skill_J_ishurted;
}
void Tower_normal::set_skill_J_ishurted(bool skill_J_ishurted){
	this->skill_J_ishurted = skill_J_ishurted;
}
bool Tower_normal::get_skill_K_ishurted(){
	return skill_K_ishurted;
}
void Tower_normal::set_skill_K_ishurted(bool skill_K_ishurted){
	this->skill_K_ishurted = skill_K_ishurted;
}
int Tower_normal::get_life(){
	return life;
}
void Tower_normal::set_life(int delta){
	life += delta;
	auto act = ScaleTo::create(0.2f, life / (float)orginal_life*0.6, 0.7);
	life_bar_fore->runAction(act);
}
void Tower_normal::set_life_bar(int side){
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
bool Tower_normal::get_hittest_A(){
	return hittest_A;
}
void Tower_normal::set_hittest_A(bool hittest_A){
	this->hittest_A = hittest_A;
}
bool Tower_normal::get_Direction(){
	return SpriteDirecton;
}
bool Tower_normal::get_isblowup(){
	return isblowup;
}
void Tower_normal::set_isblowup(bool isblowup){
	this->isblowup = isblowup;
}
bool Tower_normal::get_canControl(){
	return canControl;
}
void Tower_normal::set_canControl(bool canControl){
	this->canControl = canControl;
}
bool Tower_normal::get_isOver(){
	return isOver;
}
bool Tower_normal::get_isdeath(){
	return isdeath;
}
int Tower_normal::get_typeid(){
	return type_id;
}
int Tower_normal::get_attack_A_distance(){
	return attack_A_distance;
}
bool Tower_normal::is_melee(){
	return is_melee_unit;
}
int Tower_normal::get_fly_kind(){
	return fly_kind;
}
Vec2 Tower_normal::get_object_aim_pst(){
	return point;
}
void Tower_normal::set_money_paid(bool paid){
	this->paid = paid;
}
bool Tower_normal::get_money_paid(){
	return paid;
}
Sprite* Tower_normal::get_n_Sprite(){
	return	n_Sprite;
}