#include "Fly2.h"
//此飞弹为跟踪类型
Fly2::Fly2(int side,Vec2 point){
	Sprite::init();
	setName(Value(rand()).asString());//随机名字,scheduleOnce_Key用
	type_id = 22;//对象id
	is_melee_unit = true;//近战
	life = 1;//生命值
	orginal_life = life;
	speed = 2.5;//移动速度
	farthest_distance = 250;//最远射程
	damage_of_A = 7;
	attack_A_distance = 24;
	this->side = side;
	this->point = point;
	sprite_name = "public/Fly2.png";//初始图片
	m_frameCache = CCSpriteFrameCache::sharedSpriteFrameCache();//加载
	this->m_Sprite = Sprite::create(sprite_name);//hero_name为文件名
	this->setAnchorPoint(Vec2(0.5, 0));
	m_Sprite->setAnchorPoint(Vec2(0, 0));
	m_Sprite->setPosition(Vec2(0, 27));
	m_Sprite->setScale(0.5);
	this->setContentSize(Size(24, 24));
	this->addChild(m_Sprite);
	IsRunning = false;//没在放动画
	if (side == 0){//初始朝向问题
		SpriteDirecton = false;//蓝色方朝右
		m_Sprite->setFlipX(SpriteDirecton);
	}
	else{
		SpriteDirecton = true;//红色方朝左
		m_Sprite->setFlipX(SpriteDirecton);
	}
	ox = this->getPosition().x;
	setVisible(false);
	//m_Sprite->setRotation(atan((point.y - this->getPosition().y)*1.0f / (point.x - this->getPosition().x)));
	
}
Fly2::~Fly2(){

}
void Fly2::core(){//智能核心
	if (life <= 0 && isdeath == false){//死亡优先
		isdeath = true;
		isOver = true;
		return;
	}
	if (life <= 0){//强制返回
		return;
	}
	if (canControl){//如果单位存活且可以控制
		attack_ani();//如果在攻击范围内,攻击
		move();//朝目标移动
	}
}
void Fly2::object_select(Vector<AllSprites *> sprites){//判定攻击目标

}
void Fly2::attack_ani(){//攻击
	ani_block = true;
	hittest_A = true;
}
void Fly2::attack_A_effect(AllSprites *enemy){//溅血效果
	SimpleAudioEngine::getInstance()->playEffect(tower_normal_hit);
	set_life(-1);
	hittest_A = false;
	blood_effect(enemy);
	//地方单位掉血
	enemy->set_life(-1 * damage_of_A);
}
void Fly2::blood_effect(AllSprites *sprite){//溅血效果
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
		CCCallFuncN::create(sprite->get_n_Sprite(), callfuncN_selector(Fly2::removeself)), //删除自己
		NULL);
	sprite->get_n_Sprite()->addChild(blood, 10);
	blood->setAnchorPoint(Vec2(0.5, 0.5));
	blood->setScale(0.4);
	blood->setPosition(Vec2(24, 24));
	blood->runAction(act);
}
void Fly2::removeself(Node *pSender){//从父类移除图片特效
	pSender->removeFromParentAndCleanup(true);
}
void Fly2::move(){//朝着目标移动
	float ix = this->getPosition().x;
	float iy = this->getPosition().y;
	/*
	if (side){
		this->setPosition(Vec2(ix -= speed, iy));
		flew_distance += speed;
	}
	else{
		this->setPosition(Vec2(ix += speed, iy));
		flew_distance += speed;
	}
	*/
	if (!dxdyready){
		dxdyready = true;
		float ax = point.x;
		float ay = point.y;
		int flag0 = 1;
		if ((ax - ix)<0){
			flag0 = -1;
		}
		else{
			flag0 = 1;
		}
		int flag1 = 1;
		if ((ay - iy) < 0){
			flag1 = -1;
		}
		else{
			flag1 = 1;
		}
		dx = cos(atan((ay - iy)*1.0f / (ax - ix)))*speed*flag0;
		dy = abs(sin(atan((ay - iy)*1.0f / (ax - ix))))*speed*flag1;
		m_Sprite->setRotation(atan((point.y - this->getPosition().y)*1.0f / (point.x - this->getPosition().x)) * 180 / 3.1415926*-1);
		setVisible(true);
	}
	this->setPosition(Vec2(ix + dx,iy + dy));
	flew_distance += speed;
	if (flew_distance >= farthest_distance){//达到最远射程就消亡
		auto fade = FadeOut::create(0.1);
		CCCallFunc* callFunc = CCCallFunc::create(this, callfunc_selector(Fly2::auto_Over));
		auto sequence = Sequence::create(fade, callFunc, NULL);
		m_Sprite->runAction(sequence);
	}
}
void Fly2::auto_Over(){//自动消亡
	isdeath = true;
	isOver = true;
}
void Fly2::SetAnimation(int from, int to, bool run_directon, int loop){//动画
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
	*/
}
void Fly2::StopAnimation(){//停止所有动画
	/*
	if (!IsRunning)
	return;
	m_Sprite->stopAllActions();//当前精灵停止所有动画
	//恢复精灵原来的初始化贴图
	this->removeChild(m_Sprite, TRUE);//把原来的精灵删除掉
	m_Sprite = Sprite::createWithSpriteFrameName(sprite_name);//恢复精灵原来的贴图样子
	m_Sprite->setFlipX(SpriteDirecton);
	m_Sprite->setAnchorPoint(Vec2(0, 0));//要重新设置锚点
	this->addChild(m_Sprite);
	IsRunning = false;
	*/
}

bool Fly2::get_skill_J_ishurted(){
	return skill_J_ishurted;
}
void Fly2::set_skill_J_ishurted(bool skill_J_ishurted){
	this->skill_J_ishurted = skill_J_ishurted;
}
bool Fly2::get_skill_K_ishurted(){
	return skill_K_ishurted;
}
void Fly2::set_skill_K_ishurted(bool skill_K_ishurted){
	this->skill_K_ishurted = skill_K_ishurted;
}
int Fly2::get_life(){
	return life;
}
void Fly2::set_life(int delta){
	life += delta;
}
void Fly2::set_life_bar(int side){

}
bool Fly2::get_hittest_A(){
	return hittest_A;
}
void Fly2::set_hittest_A(bool hittest_A){
	this->hittest_A = hittest_A;
}
bool Fly2::get_Direction(){
	return SpriteDirecton;
}
bool Fly2::get_isblowup(){
	return isblowup;
}
void Fly2::set_isblowup(bool isblowup){
	this->isblowup = isblowup;
}
bool Fly2::get_canControl(){
	return canControl;
}
void Fly2::set_canControl(bool canControl){
	this->canControl = canControl;
}
bool Fly2::get_isOver(){
	return isOver;
}
bool Fly2::get_isdeath(){
	return isdeath;
}
int Fly2::get_typeid(){
	return type_id;
}
int Fly2::get_attack_A_distance(){
	return attack_A_distance;
}
bool Fly2::is_melee(){
	return is_melee_unit;
}
bool Fly2::is_fly_kind(){
	return true;
}