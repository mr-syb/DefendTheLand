#include "Fountain.h"

Fountain::Fountain(int side){
	Sprite::init();
	setName(Value(rand()).asString());//随机名字,scheduleOnce_Key用
	type_id = 30;//对象id
	is_melee_unit = true;//近战
	life = 300;//生命值
	orginal_life = life;
	speed = 0;//移动速度
	farthest_distance = 0;//最远射程
	damage_of_A = 0;
	attack_A_distance = 24;
	this->side = side;
	m_frameCache = CCSpriteFrameCache::sharedSpriteFrameCache();//加载
	if (side == 0){
		sprite_name = "public/fountain.png";//初始图片
	}else{
		sprite_name = "public/fountain.png";//初始图片
	}
	this->m_Sprite = Sprite::create(sprite_name);//hero_name为文件名
	this->setAnchorPoint(Vec2(0.5, 0));
	m_Sprite->setAnchorPoint(Vec2(0, 0));
	//m_Sprite->setPosition(Vec2(0, 27));
	this->setContentSize(Size(48, 80));
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
	ox = this->getPosition().x;
	set_life_bar(side);
}
Fountain::~Fountain(){

}
void Fountain::core(){//智能核心
	if (life <= 0 && isdeath == false){//死亡优先
		isdeath = true;
		deadth_ani();
		return;
	}
	if (life <= 0){//强制返回
		return;
	}
	if (canControl){//如果单位存活且可以控制
		//attack_ani();//如果在攻击范围内,攻击
		//move();//朝目标移动
	}
}
void Fountain::deadth_ani(){//死亡动画
	SimpleAudioEngine::getInstance()->playEffect(tower_die);
	life_bar_fore->setVisible(false);//血条不可见
	life_bar_back->setVisible(false);
	StopAnimation();//当前精灵停止所有动画
	auto fadeout = FadeOut::create(1.5);//淡出效果
	CCCallFunc* callFunc = CCCallFunc::create(this, callfunc_selector(Fountain::setisOver));
	CCActionInterval* deathact = CCSequence::create(fadeout, callFunc, NULL);//序列动作
	m_Sprite->runAction(deathact);
}
void Fountain::setisOver(){
	isOver = true;
	MainGame::isGameOver = true;//游戏结束
	if (side == 0){//游戏是否胜利判断
		MainGame::isVictory = false;
	}
	else{
		MainGame::isVictory = true;
	}
}
void Fountain::object_select(Vector<AllSprites *> sprites){//判定攻击目标

}
void Fountain::attack_ani(){//攻击
	ani_block = true;
	//hittest_A = true;
}
void Fountain::attack_A_effect(AllSprites *enemy){//溅血效果
	set_life(-1);
	hittest_A = false;
	blood_effect(enemy);
	//地方单位掉血
	enemy->set_life(-1 * damage_of_A);
}
void Fountain::blood_effect(Sprite *sprite){//溅血效果
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
		CCCallFuncN::create(sprite, callfuncN_selector(Fountain::removeself)), //删除自己
		NULL);
	sprite->addChild(blood, 10);
	blood->setAnchorPoint(Vec2(0.5, 0.5));
	blood->setScale(0.4);
	blood->setPosition(Vec2(24, 24));
	blood->runAction(act);
}
void Fountain::removeself(Node *pSender){//从父类移除图片特效
	pSender->removeFromParentAndCleanup(true);
}
void Fountain::move(){//朝着目标移动
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
	if (flew_distance >= farthest_distance){//达到最远射程就消亡
		auto fade = FadeOut::create(0.1);
		CCCallFunc* callFunc = CCCallFunc::create(this, callfunc_selector(Fountain::auto_Over));
		auto sequence = Sequence::create(fade, callFunc, NULL);
		m_Sprite->runAction(sequence);
	}
}
void Fountain::auto_Over(){//自动消亡
	isdeath = true;
	isOver = true;
}
void Fountain::SetAnimation(int from, int to, bool run_directon, int loop){//动画
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
void Fountain::StopAnimation(){//停止所有动画
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