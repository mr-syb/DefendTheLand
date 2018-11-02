#include "horseMan.h"

horseMan::horseMan(int side){
	Sprite::init();
	setName(Value(rand()).asString());//随机名字,scheduleOnce_Key用
	type_id = 11;//对象id
	is_melee_unit = true;//近战
	pay_back = 12;
	life = 70;//生命值
	orginal_life = life;
	speed = 1.8;//移动速度
	orginal_speed = speed;
	damage_of_A = 11;
	attack_A_distance = 24;
	attack_area = attack_A_distance;
	this->side = side;
	sprite_name = "A3f_6.png";//初始图片
	name_each = "A3f_";
	walk_from = 4;
	walk_to = 5;
	attack_from = 0;
	attack_to = 1;
	die_from = 7;
	die_to = 8;
	random_y = CCRANDOM_0_1() * 8;
	while (random_y < 0.75){//保护随机数
		random_y += CCRANDOM_0_1() * 8;
	}
	m_frameCache = CCSpriteFrameCache::sharedSpriteFrameCache();//加载
	this->m_Sprite = Sprite::createWithSpriteFrameName(sprite_name);//hero_name为文件名
	this->setAnchorPoint(Vec2(0.5, 0));
	m_Sprite->setAnchorPoint(Vec2(0, 0));
	this->setContentSize(Size(48, 48));
	//新添加n_Sprite
	n_Sprite = Sprite::create();
	n_Sprite->setAnchorPoint(Vec2(0, 0));
	this->addChild(n_Sprite);
	n_Sprite->addChild(m_Sprite);
	IsRunning = false;//没在放动画
	if (side == 0){//初始朝向问题
		SpriteDirecton = false;//蓝色方朝右
		m_Sprite->setFlipX(SpriteDirecton);
	}
	else{
		SpriteDirecton = true;//红色方朝左
		m_Sprite->setFlipX(SpriteDirecton);
	}
	set_life_bar(side);
}
horseMan::~horseMan(){

}
void horseMan::core(){//智能核心
	if (life <= 0 && isdeath == false){//死亡优先
		isdeath = true;
		deadth_ani();
		return;
	}
	if (life <= 0){//强制返回
		return;
	}
	if (canControl){//如果单位存活且可以控制
		attack_ani();//如果在攻击范围内,攻击
		move();//朝目标移动
	}
	else{
		idle();//站立
	}
}
void horseMan::object_select(Vector<AllSprites *> sprites){//判定攻击目标
	Vector<AllSprites *> chancellor;
	//排除死亡单位和飞行道具
	for (int i = 0; i < sprites.size(); i++){
		if (!sprites.at(i)->get_isdeath() && !sprites.at(i)->is_fly_kind()){
			chancellor.pushBack(sprites.at(i));
		}
	}
	if (chancellor.size() == 0){//解决容器空问题
		return;
	}
	float min_x;
	AllSprites *min_object;
	min_object = chancellor.at(0);
	min_x = (pow(this->getPosition().x - chancellor.at(0)->getPosition().x, 2) + pow(this->getPosition().y - chancellor.at(0)->getPosition().y, 2));//最小距离
	for (int i = 1; i < chancellor.size(); i++){//遍历对象列表
		float distance = pow(this->getPosition().x - chancellor.at(i)->getPosition().x, 2) + pow(this->getPosition().y - chancellor.at(i)->getPosition().y, 2);
		if (distance < min_x){
			min_x = distance;
			min_object = chancellor.at(i);
		}
	}
	object_aim = min_object;
}
void horseMan::attack_ani(){//攻击
	if (!attack_A || ani_block){//如果不是攻击状态或者动画被阻塞
		return;
	}
	ani_block = true;
	if (SpriteDirecton){//移动间攻击
		n_Sprite->setPosition(Vec2(n_Sprite->getPosition().x - 0, n_Sprite->getPosition().y));
		ox += -0;
	}
	else{
		n_Sprite->setPosition(Vec2(n_Sprite->getPosition().x + 0, n_Sprite->getPosition().y));
		ox += 0;
	}
	if (m_Sprite->getAnchorPoint().x != 0.125&&m_Sprite->getAnchorPoint().y != 0.125){//此段代码解决了点击普攻闪烁问题
		//this->removeChild(m_Sprite, TRUE);//把原来的精灵删除掉
		n_Sprite->removeChild(m_Sprite, true);
		m_Sprite = Sprite::createWithSpriteFrameName("A3f_0.png");//恢复精灵原来的贴图样子
		m_Sprite->setFlipX(SpriteDirecton);
		m_Sprite->setAnchorPoint(Vec2(0.125, 0.125));
		//this->addChild(m_Sprite);
		n_Sprite->addChild(m_Sprite);//修改的
		IsRunning = false;
	}
	if (IsRunning)
		return;
	Vector<SpriteFrame* > cache;//缓冲池
	char txt[50] = {};
	int i;
	for (i = attack_from; i <= attack_to; i++)
	{
		sprintf_s(txt, "%s%d.png", name_each, i);
		SpriteFrame* sf = m_frameCache->spriteFrameByName(txt);
		cache.pushBack(sf);
	}
	//使用列表创建动画对象
	Animation* animation = Animation::createWithSpriteFrames(cache, 0.2f);
	animation->setLoops(1);//播放一次  
	//将动画包装成一个动作  
	Animate* act = Animate::create(animation);
	IsRunning = true;
	CCCallFunc* callFunc = CCCallFunc::create(this, callfunc_selector(horseMan::attack_A_img_end));
	CCActionInterval* attackact = CCSequence::create(act, callFunc, NULL);//序列动作
	m_Sprite->runAction(attackact);
}
void horseMan::attack_A_img_end(){
	SimpleAudioEngine::getInstance()->playEffect(wave_A);
	if (SpriteDirecton){//移动间攻击
		n_Sprite->setPosition(Vec2(n_Sprite->getPosition().x - 0, n_Sprite->getPosition().y));
		ox += -0;
	}
	else{
		n_Sprite->setPosition(Vec2(n_Sprite->getPosition().x + 0, n_Sprite->getPosition().y));
		ox += 0;
	}
	hittest_A = true;//平A判定
	//砍下动画
	Vector<SpriteFrame* > cache;//缓冲池
	char txt[50] = {};
	int i;
	for (i = 0; i <= 1; i++)
	{
		sprintf_s(txt, "A3f_2.png");
		SpriteFrame* sf = m_frameCache->spriteFrameByName(txt);
		cache.pushBack(sf);
	}
	//使用列表创建动画对象  
	Animation* animation = Animation::createWithSpriteFrames(cache, 0.18f);
	//将动画包装成一个动作  
	Animate* act = Animate::create(animation);
	CCCallFunc *callFunc = CCCallFunc::create(CC_CALLBACK_0(horseMan::attack_A_end, this));
	CCActionInterval* attackact = CCSequence::create(act, callFunc, NULL);//序列动作
	m_Sprite->runAction(attackact);
}
void horseMan::attack_A_end(){//停止攻击
	if (SpriteDirecton){//移动间攻击
		n_Sprite->setPosition(Vec2(n_Sprite->getPosition().x - ox, n_Sprite->getPosition().y));
		ox = 0;
	}
	else{
		n_Sprite->setPosition(Vec2(n_Sprite->getPosition().x - ox, n_Sprite->getPosition().y));
		ox = 0;
	}
	ani_block = false;//施放阻塞
	attack_A = false;//停止攻击
	m_Sprite->stopAllActions();//当前精灵停止所有动画  
	//恢复精灵原来的初始化贴图
	//this->removeChild(m_Sprite, TRUE);//把原来的精灵删除掉
	n_Sprite->removeChild(m_Sprite, true);
	m_Sprite = Sprite::createWithSpriteFrameName(sprite_name);//恢复精灵原来的贴图样子  
	m_Sprite->setFlipX(SpriteDirecton);
	m_Sprite->setAnchorPoint(Vec2(0, 0));//要重新设置锚点
	//this->addChild(m_Sprite);
	n_Sprite->addChild(m_Sprite);//修改的
	IsRunning = false;
}
void horseMan::attack_A_effect(AllSprites *enemy){//溅血效果
	SimpleAudioEngine::getInstance()->stopEffect(SimpleAudioEngine::getInstance()->playEffect(wave_A));
	SimpleAudioEngine::getInstance()->playEffect(horseMan_hit);
	hittest_A = false;
	blood_effect(enemy);
	//地方单位掉血
	enemy->set_life(-1 * damage_of_A);
}
void horseMan::blood_effect(AllSprites *sprite){//溅血效果
	Vector<SpriteFrame* > cache;//缓冲池
	char txt[50] = {};
	int i;
	for (i = 0; i <= 4; i++)
	{
		sprintf_s(txt, "%s%d.png", "blood_", i);
		SpriteFrame* sf = m_frameCache->spriteFrameByName(txt);
		cache.pushBack(sf);
	}
	//使用列表创建动画对象  
	Animation* ani = Animation::createWithSpriteFrames(cache, 0.2f);
	auto blood = Sprite::create();
	Action * act = Sequence::create(
		Animate::create(ani),  //动画
		CCCallFuncN::create(sprite->get_n_Sprite(), callfuncN_selector(horseMan::removeself)), //删除自己
		NULL);
	sprite->get_n_Sprite()->addChild(blood, 10);
	blood->setAnchorPoint(Vec2(0.5, 0.5));
	blood->setScale(0.4);
	blood->setPosition(Vec2(24, 24));
	blood->runAction(act);
}
void horseMan::removeself(Node *pSender){//从父类移除图片特效
	pSender->removeFromParentAndCleanup(true);
}
void horseMan::move(){//朝着目标移动
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
	if (x > ix){//更改朝向
		walk(false);
	}
	else{
		walk(true);
	}
	//移动随从
	if (attack_now > 40){//多长移动下一次普攻可以立刻触发
		attack_gap = 41;
		attack_now = 0;
	}
	if (abs(x - ix) < 30 && attack_gap <= 41 && object_aim->get_isMoving() && speed > object_aim->get_speed()){
		speed = object_aim->get_speed();
		attack_gap++;
	}
	else if (abs(x - ix) > 48){
		speed = orginal_speed;
	}
	if (object_aim->get_isMoving()){//速度不为0
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
		else if (attack_gap>40){//发动攻击
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
		else if (attack_gap>40){//发动攻击
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
void horseMan::idle(){
	isMoving = false;
	StopAnimation();//当前精灵停止所有动画  
	//恢复精灵原来的初始化贴图
	//this->removeChild(m_Sprite, TRUE);//把原来的精灵删除掉
	n_Sprite->removeChild(m_Sprite, true);
	m_Sprite = Sprite::createWithSpriteFrameName(sprite_name);//恢复精灵原来的贴图样子  
	m_Sprite->setFlipX(SpriteDirecton);
	m_Sprite->setAnchorPoint(Vec2(0, 0));//要重新设置锚点
	//this->addChild(m_Sprite);
	n_Sprite->addChild(m_Sprite);//修改的
	IsRunning = false;
}
void horseMan::deadth_ani(){
	SimpleAudioEngine::getInstance()->playEffect(cav_horse_die);
	life_bar_fore->setVisible(false);//血条不可见
	life_bar_back->setVisible(false);
	StopAnimation();//当前精灵停止所有动画 
	Vector<SpriteFrame* > cache;//缓冲池
	char txt[50] = {};
	int i;
	for (i = die_from; i <= die_to; i++)
	{
		sprintf_s(txt, "%s%d.png", name_each, i);
		SpriteFrame* sf = m_frameCache->spriteFrameByName(txt);
		cache.pushBack(sf);
	}
	//使用列表创建动画对象  
	Animation* animation = Animation::createWithSpriteFrames(cache, 0.2f);
	animation->setLoops(1);//播放一次  
	//将动画包装成一个动作  
	Animate* act = Animate::create(animation);
	auto fadeout = FadeOut::create(1.5);//淡出效果
	IsRunning = true;
	CCCallFunc* callFunc = CCCallFunc::create(this, callfunc_selector(horseMan::setisOver));
	CCActionInterval* deathact = CCSequence::create(act, fadeout, callFunc, NULL);//序列动作
	m_Sprite->runAction(deathact);
}
void horseMan::setisOver(){
	isOver = true;
}
void horseMan::SetAnimation(int from, int to, bool run_directon, int loop){//动画
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
	//使用列表创建动画对象  
	Animation* animation = Animation::createWithSpriteFrames(cache, 0.2f);
	if (SpriteDirecton != run_directon)
	{
		SpriteDirecton = run_directon;

	}
	animation->setLoops(loop);//表示无限循环播放  
	//将动画包装成一个动作  
	Animate* act = Animate::create(animation);
	m_Sprite->runAction(act);
	IsRunning = true;
}
void horseMan::StopAnimation(){//停止所有动画
	if (!IsRunning)
		return;
	m_Sprite->stopAllActions();//当前精灵停止所有动画  
	//恢复精灵原来的初始化贴图   
	//this->removeChild(m_Sprite, TRUE);//把原来的精灵删除掉
	n_Sprite->removeChild(m_Sprite, true);
	m_Sprite = Sprite::createWithSpriteFrameName(sprite_name);//恢复精灵原来的贴图样子  
	m_Sprite->setFlipX(SpriteDirecton);
	m_Sprite->setAnchorPoint(Vec2(0, 0));//要重新设置锚点
	//this->addChild(m_Sprite);
	n_Sprite->addChild(m_Sprite);//修改的
	IsRunning = false;
	ani_block = false;//动画没有阻塞
	attack_A = false;//攻击取消
	if (ox != 0){//复原单位位置
		if (SpriteDirecton){//移动间攻击
			n_Sprite->setPosition(Vec2(n_Sprite->getPosition().x - ox, n_Sprite->getPosition().y));
			ox = 0;
		}
		else{
			n_Sprite->setPosition(Vec2(n_Sprite->getPosition().x - ox, n_Sprite->getPosition().y));
			ox = 0;
		}
	}
}
void horseMan::walk(bool run_directon){
	this->SetAnimation(walk_from, walk_to, run_directon, -1);
}

bool horseMan::get_skill_J_ishurted(){
	return skill_J_ishurted;
}
void horseMan::set_skill_J_ishurted(bool skill_J_ishurted){
	this->skill_J_ishurted = skill_J_ishurted;
}
bool horseMan::get_skill_K_ishurted(){
	return skill_K_ishurted;
}
void horseMan::set_skill_K_ishurted(bool skill_K_ishurted){
	this->skill_K_ishurted = skill_K_ishurted;
}
int horseMan::get_life(){
	return life;
}
void horseMan::set_life(int delta){
	life += delta;
	auto act = ScaleTo::create(0.2f, life / (float)orginal_life*0.4, 0.7);
	life_bar_fore->runAction(act);
}
void horseMan::set_life_bar(int side){
	if (side == 0){
		life_bar_fore = Sprite::create("public/blue_fore.png");
	}
	else{
		life_bar_fore = Sprite::create("public/red_fore.png");
	}
	life_bar_back = Sprite::create("public/life_back.png");
	life_bar_fore->setAnchorPoint(Vec2(0, 0.5));
	life_bar_back->setAnchorPoint(Vec2(0, 0.5));
	life_bar_fore->setPosition(Vec2(8, 52));
	life_bar_back->setPosition(Vec2(8, 52));
	life_bar_fore->setScaleX(0.4);
	life_bar_back->setScaleX(0.4);
	life_bar_fore->setScaleY(0.7);
	life_bar_back->setScaleY(0.7);
	life_bar_fore->setOpacity(180);
	life_bar_back->setOpacity(180);
	n_Sprite->addChild(life_bar_back, 1);
	n_Sprite->addChild(life_bar_fore, 1);
}
bool horseMan::get_hittest_A(){
	return hittest_A;
}
void horseMan::set_hittest_A(bool hittest_A){
	this->hittest_A = hittest_A;
}
bool horseMan::get_Direction(){
	return SpriteDirecton;
}
bool horseMan::get_isblowup(){
	return isblowup;
}
void horseMan::set_isblowup(bool isblowup){
	this->isblowup = isblowup;
}
bool horseMan::get_canControl(){
	return canControl;
}
void horseMan::set_canControl(bool canControl){
	this->canControl = canControl;
}
bool horseMan::get_isOver(){
	return isOver;
}
bool horseMan::get_isdeath(){
	return isdeath;
}
int horseMan::get_typeid(){
	return type_id;
}
int horseMan::get_attack_A_distance(){
	return attack_area;
}
bool horseMan::is_melee(){
	return is_melee_unit;
}
float horseMan::get_speed(){
	return speed;
}
int horseMan::earn_money(){
	return pay_back;
}
Sprite* horseMan::get_n_Sprite(){
	return	n_Sprite;
}
void horseMan::set_money_paid(bool paid){
	this->paid = paid;
}
bool horseMan::get_money_paid(){
	return paid;
}
void horseMan::set_isMoving(bool isMoving){
	this->isMoving = isMoving;
}
bool horseMan::get_isMoving(){
	return isMoving;
}