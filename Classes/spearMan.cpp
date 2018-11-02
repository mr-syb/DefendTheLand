#include "spearMan.h"

spearMan::spearMan(int side){
	Sprite::init();
	setName(Value(rand()).asString());//�������,scheduleOnce_Key��
	type_id = 12;//����id
	is_melee_unit = true;
	pay_back = 9;//ֵ����Ǯ
	life = 50;//����ֵ
	orginal_life = life;
	speed = 1;//�ƶ��ٶ�
	orginal_speed = speed;
	damage_of_A = 9;
	attack_A_distance = 48;//ƽA����
	attack_area = attack_A_distance + 18;
	this->side = side;
	sprite_name = "A4f_6.png";//��ʼͼƬ
	name_each = "A4f_";
	walk_from = 4;
	walk_to = 5;
	attack_from = 0;
	attack_to = 1;
	die_from = 7;
	die_to = 8;
	random_y = CCRANDOM_0_1() * 8;
	while (random_y < 0.75){//���������
		random_y += CCRANDOM_0_1() * 8;
	}
	m_frameCache = CCSpriteFrameCache::sharedSpriteFrameCache();//����
	this->m_Sprite = Sprite::createWithSpriteFrameName(sprite_name);//hero_nameΪ�ļ���
	this->setAnchorPoint(Vec2(0.5, 0));
	m_Sprite->setAnchorPoint(Vec2(0, 0));
	this->setContentSize(Size(48, 48));
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
	set_life_bar(side);
}
spearMan::~spearMan(){

}
void spearMan::core(){//���ܺ���
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
void spearMan::object_select(Vector<AllSprites *> sprites){//�ж�����Ŀ��
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
}
void spearMan::attack_ani(){//����
	if (!attack_A || ani_block){//������ǹ���״̬���߶���������
		return;
	}
	ani_block = true;
	if (SpriteDirecton){//�ƶ��乥��
		n_Sprite->setPosition(Vec2(n_Sprite->getPosition().x - 18, n_Sprite->getPosition().y));
		ox += -18;
	}
	else{
		n_Sprite->setPosition(Vec2(n_Sprite->getPosition().x + 18, n_Sprite->getPosition().y));
		ox += 18;
	}
	if (m_Sprite->getAnchorPoint().x != 0.125&&m_Sprite->getAnchorPoint().y != 0.125){//�˶δ������˵���չ���˸����
		//this->removeChild(m_Sprite, TRUE);//��ԭ���ľ���ɾ����
		n_Sprite->removeChild(m_Sprite, true);
		m_Sprite = Sprite::createWithSpriteFrameName("A4f_0.png");//�ָ�����ԭ������ͼ����
		m_Sprite->setFlipX(SpriteDirecton);
		m_Sprite->setAnchorPoint(Vec2(0.125, 0.125));
		//this->addChild(m_Sprite);
		n_Sprite->addChild(m_Sprite);//�޸ĵ�
		IsRunning = false;
	}
	if (IsRunning)
		return;
	Vector<SpriteFrame* > cache;//�����
	char txt[50] = {};
	int i;
	for (i = attack_from; i <= attack_to; i++)
	{
		sprintf_s(txt, "%s%d.png", name_each, i);
		SpriteFrame* sf = m_frameCache->spriteFrameByName(txt);
		cache.pushBack(sf);
	}
	//ʹ���б�����������  
	Animation* animation = Animation::createWithSpriteFrames(cache, 0.2f);
	animation->setLoops(1);//����һ��  
	//��������װ��һ������  
	Animate* act = Animate::create(animation);
	IsRunning = true;
	CCCallFunc* callFunc = CCCallFunc::create(this, callfunc_selector(spearMan::attack_A_img_end));
	CCActionInterval* attackact = CCSequence::create(act, callFunc, NULL);//���ж���
	m_Sprite->runAction(attackact);
}
void spearMan::attack_A_img_end(){
	SimpleAudioEngine::getInstance()->playEffect(wave_A);
	if (SpriteDirecton){//�ƶ��乥��
		n_Sprite->setPosition(Vec2(n_Sprite->getPosition().x - 0, n_Sprite->getPosition().y));
		ox += 0;
	}
	else{
		n_Sprite->setPosition(Vec2(n_Sprite->getPosition().x + 0, n_Sprite->getPosition().y));
		ox += 0;
	}
	hittest_A = true;//ƽA�ж�
	//���¶���
	Vector<SpriteFrame* > cache;//�����
	char txt[50] = {};
	int i;
	for (i = 0; i <= 1; i++)
	{
		sprintf_s(txt, "A4f_2.png");
		SpriteFrame* sf = m_frameCache->spriteFrameByName(txt);
		cache.pushBack(sf);
	}
	//ʹ���б�����������  
	Animation* animation = Animation::createWithSpriteFrames(cache, 0.18f);
	//��������װ��һ������  
	Animate* act = Animate::create(animation);
	CCCallFunc *callFunc = CCCallFunc::create(CC_CALLBACK_0(spearMan::attack_A_end, this));
	CCActionInterval* attackact = CCSequence::create(act, callFunc, NULL);//���ж���
	m_Sprite->runAction(attackact);
}
void spearMan::attack_A_end(){//ֹͣ����
	if (SpriteDirecton){//�ƶ��乥��
		n_Sprite->setPosition(Vec2(n_Sprite->getPosition().x - ox, n_Sprite->getPosition().y));
		ox = 0;
	}
	else{
		n_Sprite->setPosition(Vec2(n_Sprite->getPosition().x - ox, n_Sprite->getPosition().y));
		ox = 0;
	}
	ani_block = false;//ʩ������
	attack_A = false;//ֹͣ����
	m_Sprite->stopAllActions();//��ǰ����ֹͣ���ж���  
	//�ָ�����ԭ���ĳ�ʼ����ͼ
	//this->removeChild(m_Sprite, TRUE);//��ԭ���ľ���ɾ����
	n_Sprite->removeChild(m_Sprite, true);
	m_Sprite = Sprite::createWithSpriteFrameName(sprite_name);//�ָ�����ԭ������ͼ����  
	m_Sprite->setFlipX(SpriteDirecton);
	m_Sprite->setAnchorPoint(Vec2(0, 0));//Ҫ��������ê��
	//this->addChild(m_Sprite);
	n_Sprite->addChild(m_Sprite);//�޸ĵ�
	IsRunning = false;
}
void spearMan::attack_A_effect(AllSprites *enemy){//��ѪЧ��
	SimpleAudioEngine::getInstance()->stopEffect(SimpleAudioEngine::getInstance()->playEffect(wave_A));
	SimpleAudioEngine::getInstance()->playEffect(spear_pike_hit);
	hittest_A = false;
	blood_effect(enemy);
	//�ط���λ��Ѫ
	enemy->set_life(-1 * damage_of_A);
}
void spearMan::blood_effect(AllSprites *sprite){//��ѪЧ��
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
		CCCallFuncN::create(sprite->get_n_Sprite(), callfuncN_selector(spearMan::removeself)), //ɾ���Լ�
		NULL);
	sprite->get_n_Sprite()->addChild(blood, 10);
	blood->setAnchorPoint(Vec2(0.5, 0.5));
	blood->setScale(0.4);
	blood->setPosition(Vec2(24, 24));
	blood->runAction(act);
}
void spearMan::removeself(Node *pSender){//�Ӹ����Ƴ�ͼƬ��Ч
	pSender->removeFromParentAndCleanup(true);
}
void spearMan::move(){//����Ŀ���ƶ�
	isMoving = true;
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
		walk(false);
	}
	else{
		walk(true);
	}
	//�ƶ����
	if (attack_now > 40){//�೤�ƶ���һ���չ��������̴���
		attack_gap = 41;
		attack_now = 0;
	}
	if (abs(x - ix) < 30 && attack_gap <= 40 && object_aim->get_isMoving() && speed > object_aim->get_speed()){
		speed = object_aim->get_speed();
		attack_gap++;
	}
	else if (abs(x - ix) > 48){
		speed = orginal_speed;
	}
	if (object_aim->get_isMoving()){//�ٶȲ�Ϊ0
		if ((x > ix && (x - w*0.5 - ix - attack_A_distance) > -20) && attack_gap <= 41){
			this->setPosition(Vec2(ix + speed, iy));
			attack_now++;
		}
		else if ((x < ix && (x + w*0.5 - ix + attack_A_distance) < 20) && attack_gap <= 41){
			this->setPosition(Vec2(ix - speed, iy));
			attack_now++;
		}
		else if (y > iy&&abs(y - iy) > random_y){
			this->setPosition(Vec2(ix, iy + speed*0.75));
			attack_now++;
		}
		else if (y < iy&&abs(y - iy) > random_y){
			this->setPosition(Vec2(ix, iy - speed*0.75));
			attack_now++;
		}
		else if (attack_gap>40){//��������
			attack_A = true;
			attack_gap = 0;
			attack_now = 0;
		}
		else{
			idle();
			attack_gap++;
			attack_now = 0;
		}
	}
	else{
		if ((x > ix && (x - w*0.5 - ix - attack_A_distance) > 0) && attack_gap <= 41){
			this->setPosition(Vec2(ix + speed, iy));
			attack_now++;
		}
		else if ((x < ix && (x + w*0.5 - ix + attack_A_distance) < 0) && attack_gap <= 41){
			this->setPosition(Vec2(ix - speed, iy));
			attack_now++;
		}
		else if (y > iy&&abs(y - iy) > random_y){
			this->setPosition(Vec2(ix, iy + speed*0.75));
			attack_now++;
		}
		else if (y < iy&&abs(y - iy) > random_y){
			this->setPosition(Vec2(ix, iy - speed*0.75));
			attack_now++;
		}
		else if (attack_gap>40){//��������
			attack_A = true;
			attack_gap = 0;
			attack_now = 0;
		}
		else{
			idle();
			attack_gap++;
			attack_now = 0;
		}
	}
}
void spearMan::idle(){
	isMoving = false;
	StopAnimation();//��ǰ����ֹͣ���ж���  
	//�ָ�����ԭ���ĳ�ʼ����ͼ
	//this->removeChild(m_Sprite, TRUE);//��ԭ���ľ���ɾ����
	n_Sprite->removeChild(m_Sprite, true);
	m_Sprite = Sprite::createWithSpriteFrameName(sprite_name);//�ָ�����ԭ������ͼ����  
	m_Sprite->setFlipX(SpriteDirecton);
	m_Sprite->setAnchorPoint(Vec2(0, 0));//Ҫ��������ê��
	//this->addChild(m_Sprite);
	n_Sprite->addChild(m_Sprite);//�޸ĵ�
	IsRunning = false;
}
void spearMan::deadth_ani(){
	SimpleAudioEngine::getInstance()->playEffect(pike_spear_die);
	life_bar_fore->setVisible(false);//Ѫ�����ɼ�
	life_bar_back->setVisible(false);
	StopAnimation();//��ǰ����ֹͣ���ж��� 
	Vector<SpriteFrame* > cache;//�����
	char txt[50] = {};
	int i;
	for (i = die_from; i <= die_to; i++)
	{
		sprintf_s(txt, "%s%d.png", name_each, i);
		SpriteFrame* sf = m_frameCache->spriteFrameByName(txt);
		cache.pushBack(sf);
	}
	//ʹ���б�����������  
	Animation* animation = Animation::createWithSpriteFrames(cache, 0.2f);
	animation->setLoops(1);//����һ��  
	//��������װ��һ������  
	Animate* act = Animate::create(animation);
	auto fadeout = FadeOut::create(1.5);//����Ч��
	IsRunning = true;
	CCCallFunc* callFunc = CCCallFunc::create(this, callfunc_selector(spearMan::setisOver));
	CCActionInterval* deathact = CCSequence::create(act, fadeout, callFunc, NULL);//���ж���
	m_Sprite->runAction(deathact);
}
void spearMan::setisOver(){
	isOver = true;
}
void spearMan::SetAnimation(int from, int to, bool run_directon, int loop){//����
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
	Animation* animation = Animation::createWithSpriteFrames(cache, 0.28f);
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
void spearMan::StopAnimation(){//ֹͣ���ж���
	if (!IsRunning)
		return;
	m_Sprite->stopAllActions();//��ǰ����ֹͣ���ж���  
	//�ָ�����ԭ���ĳ�ʼ����ͼ   
	//this->removeChild(m_Sprite, TRUE);//��ԭ���ľ���ɾ����
	n_Sprite->removeChild(m_Sprite, true);
	m_Sprite = Sprite::createWithSpriteFrameName(sprite_name);//�ָ�����ԭ������ͼ����  
	m_Sprite->setFlipX(SpriteDirecton);
	m_Sprite->setAnchorPoint(Vec2(0, 0));//Ҫ��������ê��
	//this->addChild(m_Sprite);
	n_Sprite->addChild(m_Sprite);//�޸ĵ�
	IsRunning = false;
	ani_block = false;//����û������
	attack_A = false;//����ȡ��
	if (ox != 0){//��ԭ��λλ��
		if (SpriteDirecton){//�ƶ��乥��
			n_Sprite->setPosition(Vec2(n_Sprite->getPosition().x - ox, n_Sprite->getPosition().y));
			ox = 0;
		}
		else{
			n_Sprite->setPosition(Vec2(n_Sprite->getPosition().x - ox, n_Sprite->getPosition().y));
			ox = 0;
		}
	}
}
void spearMan::walk(bool run_directon){
	this->SetAnimation(walk_from, walk_to, run_directon, -1);
}

bool spearMan::get_skill_J_ishurted(){
	return skill_J_ishurted;
}
void spearMan::set_skill_J_ishurted(bool skill_J_ishurted){
	this->skill_J_ishurted = skill_J_ishurted;
}
bool spearMan::get_skill_K_ishurted(){
	return skill_K_ishurted;
}
void spearMan::set_skill_K_ishurted(bool skill_K_ishurted){
	this->skill_K_ishurted = skill_K_ishurted;
}
int spearMan::get_life(){
	return life;
}
void spearMan::set_life(int delta){
	life += delta;
	auto act = ScaleTo::create(0.2f, life / (float)orginal_life*0.4, 0.7);
	life_bar_fore->runAction(act);
}
void spearMan::set_life_bar(int side){
	if (side == 0){
		life_bar_fore = Sprite::create("public/blue_fore.png");
	}
	else{
		life_bar_fore = Sprite::create("public/red_fore.png");
	}
	life_bar_back = Sprite::create("public/life_back.png");
	life_bar_fore->setAnchorPoint(Vec2(0, 0.5));
	life_bar_back->setAnchorPoint(Vec2(0, 0.5));
	life_bar_fore->setPosition(Vec2(6, 52));
	life_bar_back->setPosition(Vec2(6, 52));
	life_bar_fore->setScaleX(0.4);
	life_bar_back->setScaleX(0.4);
	life_bar_fore->setScaleY(0.7);
	life_bar_back->setScaleY(0.7);
	life_bar_fore->setOpacity(180);
	life_bar_back->setOpacity(180);
	n_Sprite->addChild(life_bar_back, 1);
	n_Sprite->addChild(life_bar_fore, 1);
}
bool spearMan::get_hittest_A(){
	return hittest_A;
}
void spearMan::set_hittest_A(bool hittest_A){
	this->hittest_A = hittest_A;
}
bool spearMan::get_Direction(){
	return SpriteDirecton;
}
bool spearMan::get_isblowup(){
	return isblowup;
}
void spearMan::set_isblowup(bool isblowup){
	this->isblowup = isblowup;
}
bool spearMan::get_canControl(){
	return canControl;
}
void spearMan::set_canControl(bool canControl){
	this->canControl = canControl;
}
bool spearMan::get_isOver(){
	return isOver;
}
bool spearMan::get_isdeath(){
	return isdeath;
}
int spearMan::get_typeid(){
	return type_id;
}
int spearMan::get_attack_A_distance(){
	return attack_area;
}
bool spearMan::is_melee(){
	return is_melee_unit;
}
float spearMan::get_speed(){
	return speed;
}
int spearMan::earn_money(){
	return pay_back;
}
Sprite* spearMan::get_n_Sprite(){
	return	n_Sprite;
}
void spearMan::set_money_paid(bool paid){
	this->paid = paid;
}
bool spearMan::get_money_paid(){
	return paid;
}
void spearMan::set_isMoving(bool isMoving){
	this->isMoving = isMoving;
}
bool spearMan::get_isMoving(){
	return isMoving;
}