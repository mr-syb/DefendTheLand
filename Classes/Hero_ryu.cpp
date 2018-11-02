#include "Hero_ryu.h"
Hero_ryu::Hero_ryu(int side){//初始化
	Sprite::init();
	type_id = 0;//对象类型
	money = 50;//初始金钱
	speed = 1.5;//移动速度
	original_speed = speed;
	life = 100;//生命值
	orginal_life = life;
	hero_walk_from = 4;
	hero_walk_to = 5;
	hero_attack_from = 0;
	hero_attack_to = 1;
	hero_die_from = 7;
	hero_die_to = 8;
	damage_of_A = 7;//平A伤害
	A_cd = 0.6;//平Acd
	attack_A_distance = 24;//平A距离
	distance_J = 180;//J位移的距离
	damage_of_J = 3;//J的伤害
	damage_of_J_blow = 7;//J技能击飞的伤害
	height_blow = 48;//击飞高度
	stun_time = 1.5f;//眩晕时间
	J_cd = 4;//J技能cd
	speedBuff_K = 0.5;//K技能增加移动速度量
	lifeBuff_K = 18;//K技能回血量
	K_duration = 3;//K技能BUFF持续时间
	K_cd = 8;//K技能cd
	name_each = "Hero02f_";
	Hero_name = "Hero02f_6.png";//初始图片
	attack_A_img = "hero_ryu/A.png";//平A图片 
	skill_J_img = "hero_ryu/J.png";//技能J图片
	skill_K_img = "hero_ryu/K.png";//技能K图片
	icon_head_img = "hero_ryu/ryu.png";//头像图片
	m_Sprite = Sprite::createWithSpriteFrameName("Hero02f_6.png");//hero_name为文件名
	m_frameCache = CCSpriteFrameCache::sharedSpriteFrameCache();//加载
	
	setAnchorPoint(Vec2(0.5, 0));
	m_Sprite->setAnchorPoint(Vec2(0, 0));
	setContentSize(Size(48, 48));
	//新添加n_Sprite
	n_Sprite = Sprite::create();
	n_Sprite->setAnchorPoint(Vec2(0, 0));
	this->addChild(n_Sprite);
	n_Sprite->addChild(m_Sprite);
	born_effect();//出生特效
	set_life_bar(side);
}
Hero_ryu::~Hero_ryu(){

}

void Hero_ryu::SetAnimation(int from, int to, bool run_directon, int loop){//动画
	if (HeroDirection != run_directon)
	{
		HeroDirection = run_directon;
		m_Sprite->setFlipX(run_directon);
	}
	if (IsRunning)
		return;
	Vector<SpriteFrame* > cache;//缓冲池
	char txt[50] = {};
	int i;
	for (i = from; i <= to; i++)
	{
		sprintf_s(txt,"%s%d.png",name_each,i);
		SpriteFrame* sf = m_frameCache->spriteFrameByName(txt);
		cache.pushBack(sf);
	}
	//使用列表创建动画对象  
	Animation* animation = Animation::createWithSpriteFrames(cache, 0.15f);
	if (HeroDirection != run_directon)
	{
		HeroDirection = run_directon;

	}
	animation->setLoops(loop);//表示无限循环播放  
	//将动画包装成一个动作  
	Animate* act = Animate::create(animation);
	m_Sprite->runAction(act);
	IsRunning = true;
}

void Hero_ryu::StopAnimation(){//停止动画
	if (!IsRunning)
		return;
	m_Sprite->stopAllActions();//当前精灵停止所有动画  
	//恢复精灵原来的初始化贴图   
	//this->removeChild(m_Sprite, TRUE);//把原来的精灵删除掉
	n_Sprite->removeChild(m_Sprite, true);
	m_Sprite = Sprite::createWithSpriteFrameName(Hero_name);//恢复精灵原来的贴图样子  
	m_Sprite->setFlipX(HeroDirection);
	m_Sprite->setAnchorPoint(Vec2(0, 0));//要重新设置锚点
	//this->addChild(m_Sprite);
	n_Sprite->addChild(m_Sprite);//修改的
	IsRunning = false;
}

void Hero_ryu::walk(bool run_directon,int loop){
	this->SetAnimation(hero_walk_from, hero_walk_to, run_directon, loop);
}
void Hero_ryu::attack_A_animation(bool run_directon){
	hero_ani_block = true;//动画阻塞
	if (m_Sprite->getAnchorPoint().x != 0.125&&m_Sprite->getAnchorPoint().y != 0.125){//此段代码解决了点击普攻闪烁问题
		//m_Sprite->stopAllActions();//当前精灵停止所有动画  
		//this->removeChild(m_Sprite, TRUE);//把原来的精灵删除掉
		n_Sprite->removeChild(m_Sprite, true);
		m_Sprite = Sprite::createWithSpriteFrameName("Hero02f_0.png");//恢复精灵原来的贴图样子  
		m_Sprite->setFlipX(HeroDirection);
		m_Sprite->setAnchorPoint(Vec2(0.125, 0.125));
		//this->addChild(m_Sprite);
		n_Sprite->addChild(m_Sprite);//修改的
		IsRunning = false;
	}
	if (HeroDirection != run_directon)
	{
		HeroDirection = run_directon;
		m_Sprite->setFlipX(run_directon);
	}
	if (IsRunning)
		return;
	Vector<SpriteFrame* > cache;//缓冲池
	char txt[50] = {};
	int i;
	for (i = hero_attack_from; i <= hero_attack_to; i++)
	{
		sprintf_s(txt, "%s%d.png", name_each, i);
		SpriteFrame* sf = m_frameCache->spriteFrameByName(txt);
		cache.pushBack(sf);
	}
	//使用列表创建动画对象  
	Animation* animation = Animation::createWithSpriteFrames(cache, 0.15f);
	if (HeroDirection != run_directon)
	{
		HeroDirection = run_directon;

	}
	animation->setLoops(1);//表示循环播放  
	//将动画包装成一个动作  
	Animate* act = Animate::create(animation);
	IsRunning = true;

	CCCallFunc* callFunc = CCCallFunc::create(this, callfunc_selector(Hero_ryu::attack_A_img_end));
	CCActionInterval* attackact = CCSequence::create(act,callFunc, NULL);//序列动作
	m_Sprite->runAction(attackact);
}
void Hero_ryu::attack_A_img_end(){
	SimpleAudioEngine::getInstance()->playEffect(ryu_A);
	hittest_A = true;//平A判定
	//砍下动画
	Vector<SpriteFrame* > cache;//缓冲池
	SpriteFrame* sf = m_frameCache->spriteFrameByName("Hero02f_2.png");//收刀动作
	cache.pushBack(sf);
	//使用列表创建动画对象  
	Animation* animation = Animation::createWithSpriteFrames(cache, 0.15f);
	//将动画包装成一个动作  
	Animate* act = Animate::create(animation);
	CCCallFunc *callFunc = CCCallFunc::create(CC_CALLBACK_0(Hero_ryu::attack_A_end, this));//传递Hero_ryu实际位置
	CCActionInterval* attackact = CCSequence::create(act, callFunc, NULL);//序列动作
	m_Sprite->runAction(attackact);
}
void Hero_ryu::attack_A_end(){
	hero_ani_block = false;//施放阻塞
	attack_A = false;//停止攻击
	m_Sprite->stopAllActions();//当前精灵停止所有动画  
	//恢复精灵原来的初始化贴图
	//this->removeChild(m_Sprite, TRUE);//把原来的精灵删除掉
	n_Sprite->removeChild(m_Sprite, true);
	m_Sprite = Sprite::createWithSpriteFrameName(Hero_name);//恢复精灵原来的贴图样子  
	m_Sprite->setFlipX(HeroDirection);
	m_Sprite->setAnchorPoint(Vec2(0, 0));//要重新设置锚点
	//this->addChild(m_Sprite);
	n_Sprite->addChild(m_Sprite);//修改的
	IsRunning = false;
}
void Hero_ryu::attack_A_effect(AllSprites *enemy){//溅血效果
	SimpleAudioEngine::getInstance()->playEffect(hit);
	hittest_A = false;//攻击为单次
	blood_effect(enemy);
	//地方单位掉血
	enemy->set_life(-1*damage_of_A);
}
void Hero_ryu::skill_J_ani(Vector<AllSprites *> allEnemy){//J技能
	SimpleAudioEngine::getInstance()->playEffect(ryu_J_start);
	hero_ani_block = true;//动画阻塞
	skill_J = false;//技能施放一次
	hittest_J = true;//技能
	skill_J_damage = true;//J技能造成伤害
	skill_J_effect();//扬沙图片特效
	if (m_Sprite->getAnchorPoint().x != 0.125&&m_Sprite->getAnchorPoint().y != 0.125){//此段代码解决了点击普攻闪烁问题
		//m_Sprite->stopAllActions();//当前精灵停止所有动画
		//this->removeChild(m_Sprite, TRUE);//把原来的精灵删除掉
		n_Sprite->removeChild(m_Sprite, true);
		m_Sprite = Sprite::createWithSpriteFrameName("Hero02f_0.png");//恢复精灵原来的贴图样子  
		m_Sprite->setFlipX(HeroDirection);
		m_Sprite->setAnchorPoint(Vec2(0.125, 0.125));
		//this->addChild(m_Sprite);
		n_Sprite->addChild(m_Sprite);//修改的
		IsRunning = false;
	}
	//产生位移
	int flag = 1;
	if (HeroDirection){
		flag = -1;
	}
	else{
		flag = 1;
	}
	CCMoveBy *moveBy = CCMoveBy::create(0.3f, Vec2(distance_J*flag,0));//产生位移
	//序列动作
	CCCallFunc *callFunc = CCCallFunc::create(CC_CALLBACK_0(Hero_ryu::skill_J_img_end, this,allEnemy));
	CCActionInterval* attackact = CCSequence::create(moveBy,callFunc,NULL);//序列动作
	runAction(attackact);
}
void Hero_ryu::skill_J_img_end(Vector<AllSprites *> allEnemy){//J技能收尾动画
	if (life <= 0) return;//解决BUG
	SimpleAudioEngine::getInstance()->playEffect(ryu_J_end);
	//砍下动画
	Vector<SpriteFrame* > cache;//缓冲池
	SpriteFrame* sf = m_frameCache->spriteFrameByName("Hero02f_2.png");//收刀动作
	cache.pushBack(sf);
	//使用列表创建动画对象
	Animation* animation = Animation::createWithSpriteFrames(cache, 0.15f);
	//animation->setLoops(1);//表示循环播放  
	//将动画包装成一个动作  
	Animate* act = Animate::create(animation);
	CCCallFunc *callFunc = CCCallFunc::create(CC_CALLBACK_0(Hero_ryu::skill_J_end, this,allEnemy));//传递Hero_ryu实际位置
	CCActionInterval* attackact = CCSequence::create(act, callFunc, NULL);//序列动作
	m_Sprite->runAction(attackact);
	skill_J_blowup();//击飞
	//blowup = true;//开始击飞
}
void Hero_ryu::skill_J_blowup(){
	blowup = true;//开始击飞
	Vector<SpriteFrame* > cache;//缓冲池
	char txt[50] = {};
	int i;
	for (i = 0; i <= 3; i++)
	{
		sprintf_s(txt, "%s%d.png", "blowup_", i);
		SpriteFrame* sf = m_frameCache->spriteFrameByName(txt);
		cache.pushBack(sf);
	}
	//使用列表创建动画对象  
	Animation* ani = Animation::createWithSpriteFrames(cache, 0.2f);
	auto blow = Sprite::create();
	Action * act = Sequence::create(
		Animate::create(ani),  //动画
		CCCallFunc::create(CC_CALLBACK_0(Hero_ryu::skill_J_setblowup, this)),//击飞结束
		CCCallFuncN::create(n_Sprite, callfuncN_selector(Hero_ryu::removeself)), //删除自己
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
	hero_ani_block = false;//施放阻塞
	hittest_J = false;//技能
	skill_J_damage = false;//技能停止
	if (life <= 0) return;//解决BUG
	m_Sprite->stopAllActions();//当前精灵停止所有动画
	//恢复精灵原来的初始化贴图
	//this->removeChild(m_Sprite, TRUE);//把原来的精灵删除掉
	n_Sprite->removeChild(m_Sprite, true);
	m_Sprite = Sprite::createWithSpriteFrameName(Hero_name);//恢复精灵原来的贴图样子
	m_Sprite->setFlipX(HeroDirection);
	m_Sprite->setAnchorPoint(Vec2(0, 0));//要重新设置锚点
	//this->addChild(m_Sprite);
	n_Sprite->addChild(m_Sprite);//修改的
	IsRunning = false;
    //设置敌人skill_J_ishurted=false
	for (int i = 0; i < allEnemy.size(); i++){
		allEnemy.at(i)->set_skill_J_ishurted(false);
		allEnemy.at(i)->set_isblowup(false);
	}
}
void Hero_ryu::skill_J_attack(AllSprites *enemy){//主函数调用J技能
	bool canMove = true;
	int id=enemy->get_typeid();
	if (id >= 30){//防御塔不可击飞
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
	if (skill_J_damage && ishurted == false){//冲撞
		blood_effect(enemy);
		enemy->set_skill_J_ishurted(true);
		//敌方单位掉血
		enemy->set_life(-1*damage_of_J);
	}
	bool isblowup_enemy = enemy->get_isblowup();
	if (blowup && isblowup_enemy == false && canMove){//击飞
		blood_effect(enemy);
		skill_J_bloweffect(enemy);//眩晕动画
		skill_J_blowmove(enemy);//击飞位移
		enemy->set_isblowup(true);
		enemy->set_life(-1 * damage_of_J_blow);
		enemy->set_canControl(false);//设置智能核心不可控制
		scheduleOnce(CC_CALLBACK_1(Hero_ryu::skill_J_blowdelay, this, enemy), stun_time, enemy->getName());
	}
}
void Hero_ryu::skill_J_blowdelay(float dt, AllSprites *enemy){//眩晕时间
	enemy->set_canControl(true);
}
void Hero_ryu::skill_J_bloweffect(AllSprites *enemy){
	Vector<SpriteFrame* > cache;//缓冲池
	char txt[50] = {};
	int i;
	for (i = 0; i <= 11; i++)
	{
		sprintf_s(txt, "%s%d.png", "stun_", i);
		SpriteFrame* sf = m_frameCache->spriteFrameByName(txt);
		cache.pushBack(sf);
	}
	//使用列表创建动画对象  
	Animation* ani = Animation::createWithSpriteFrames(cache, 0.1f);
	auto stunning = Sprite::create();
	Action * act = Sequence::create(
		Animate::create(ani),  //动画
		CCCallFuncN::create(enemy, callfuncN_selector(Hero_ryu::removeself)), //删除自己
		NULL);
	auto n_enemy = enemy->get_n_Sprite();
	n_enemy->addChild(stunning, 5);
	stunning->setAnchorPoint(Vec2(0.5, 0.5));
	stunning->setScale(0.3);
	stunning->setScaleX(0.22);
	stunning->setPosition(Vec2(24, 56));
	stunning->runAction(act);
}
void Hero_ryu::skill_J_blowmove(AllSprites *enemy){//抛向空中
	CCJumpBy *blow = CCJumpTo::create(0.5f, Vec2(0, 0), height_blow, 1);
	//序列动作
	CCActionInterval* act = CCSequence::create(blow, NULL);//序列动作
	auto n_enemy=enemy->get_n_Sprite();
	n_enemy->runAction(act);
	//enemy->runAction(act);
}
void Hero_ryu::skill_J_effect(){
	float x = m_Sprite->getPosition().x;
	float y = m_Sprite->getPosition().y;
	Vector<SpriteFrame* > cache;//缓冲池
	char txt[50] = {};
	int i;
	for (i = 0; i <= 4; i++)
	{
		sprintf_s(txt, "%s%d.png", "J_", i);
		SpriteFrame* sf = m_frameCache->spriteFrameByName(txt);
		cache.pushBack(sf);
	}
	//使用列表创建动画对象  
	Animation* ani= Animation::createWithSpriteFrames(cache, 0.1f);
	auto sprite = Sprite::create();
	Action * act = Sequence::create(
		Animate::create(ani),  //动画
		CCCallFuncN::create(sprite, callfuncN_selector(Hero_ryu::removeself)), //删除自己
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
void Hero_ryu::skill_K_ani(Vector<AllSprites *> allEnemy){//K技能
	SimpleAudioEngine::getInstance()->playEffect(ryu_K);
	skill_K = false;//技能施放一次
	hittest_K = true;//技能开始判定
	skill_K_effect();//K技能动画
}
void Hero_ryu::skill_K_effect(){
	float x = m_Sprite->getPosition().x;
	float y = m_Sprite->getPosition().y;
	Vector<SpriteFrame* > cache;//缓冲池
	char txt[50] = {};
	int i;
	for (i = 0; i <= 17; i++)
	{
		sprintf_s(txt, "%d.png", i);
		SpriteFrame* sf = m_frameCache->spriteFrameByName(txt);
		cache.pushBack(sf);
	}
	CCCallFunc *callFunc = CCCallFunc::create(CC_CALLBACK_0(Hero_ryu::skill_K_Buff, this));
	//使用列表创建动画对象
	Animation* ani = Animation::createWithSpriteFrames(cache, 0.1f);
	auto sprite = Sprite::create();
	Action * act = Sequence::create(Animate::create(ani), CCCallFuncN::create(sprite, callfuncN_selector(Hero_ryu::removeself)), callFunc, NULL); //删除自己	
	n_Sprite->addChild(sprite);
	sprite->setScale(0.8);
	sprite->setAnchorPoint(Vec2(0.5, 0.5));
	sprite->setPosition(Vec2(24,24));
	sprite->setOpacity(230);
	sprite->setZOrder(2);
	sprite->runAction(act);
}
void Hero_ryu::skill_K_Buff(){//K技能buff
	if (life <= 0) return;//解决BUG
	set_life(lifeBuff_K);
	set_speed(speedBuff_K);
	scheduleOnce(schedule_selector(Hero_ryu::set_speed_orginally), K_duration);
}
void Hero_ryu::removeself(Node *pSender){//从父类移除图片特效
	pSender->removeFromParentAndCleanup(true);
}
void Hero_ryu::blood_effect(AllSprites *sprite){//溅血效果
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
		CCCallFuncN::create(sprite->get_n_Sprite(), callfuncN_selector(Hero_ryu::removeself)), //删除自己
		NULL);
	sprite->get_n_Sprite()->addChild(blood, 5);
	blood->setAnchorPoint(Vec2(0.5,0.5));
	blood->setScale(0.4);
	blood->setPosition(Vec2(24,24));
	blood->runAction(act);
}
void Hero_ryu::death_ani(){
	life_bar_fore->setVisible(false);//血条不可见
	life_bar_back->setVisible(false);
	set_statusoriginal();//设置状态复原
	StopAnimation();//停止动画
	stopAllActions();//停止所有动作
	isdeath = true;//已经死亡
	Vector<SpriteFrame* > cache;//缓冲池
	char txt[50] = {};
	int i;
	for (i = hero_die_from; i <= hero_die_to; i++)
	{
		sprintf_s(txt, "%s%d.png", name_each, i);
		SpriteFrame* sf = m_frameCache->spriteFrameByName(txt);
		cache.pushBack(sf);
	}
	//使用列表创建动画对象
	Animation* ani = Animation::createWithSpriteFrames(cache, 0.2f);
	ani->setLoops(1);//表示循环播放  
	//将动画包装成一个动作  
	Animate* act = Animate::create(ani);
	IsRunning = true;
	auto fadeout = FadeOut::create(3);//淡出效果
	CCCallFunc* callFunc = CCCallFunc::create(this, callfunc_selector(Hero_ryu::death_effect));
	auto spawn = Spawn::create(fadeout, callFunc, NULL);//并行执行
	CCActionInterval* deathact = CCSequence::create(act, spawn, NULL);//序列动作
	m_Sprite->runAction(deathact);
}
void Hero_ryu::death_effect(){
	Vector<SpriteFrame* > cache;//缓冲池
	char txt[50] = {};
	int i;
	for (i = 0; i <= 8; i++)
	{
		sprintf_s(txt, "%s%d.png", "death_", i);
		SpriteFrame* sf = m_frameCache->spriteFrameByName(txt);
		cache.pushBack(sf);
	}
	//使用列表创建动画对象  
	Animation* ani = Animation::createWithSpriteFrames(cache, 0.15f);
	ani->setLoops(1);//表示循环播放
	auto sprite = Sprite::create();
	auto fadeout = FadeOut::create(1.2);//淡出效果
	Action * act = Sequence::create(
		Animate::create(ani),  //动画
		fadeout,
		CCCallFuncN::create(sprite, callfuncN_selector(Hero_ryu::removeself)), //删除自己
		NULL);
	IsRunning = true;
	n_Sprite->addChild(sprite, 6);
	sprite->setAnchorPoint(Vec2(0.5, 0.5));
	sprite->setScale(1);
	sprite->setPosition(Vec2(24, 24));
	sprite->runAction(act);
}
void Hero_ryu::set_statusoriginal(){//设置状态复原(最后再开发)
	attack_A = false;//是否平A
	hittest_A = false;
	skill_J = false;//是否施放技能J
	isWalk = false;//是否在移动
	blowup = false;//是否击飞
	hittest_J = false;
	skill_J_damage = false;//J技能造成伤害
	skill_K = false;//是否施放技能K
	hittest_K = false;
	isblowup = false;//是否被击飞
	//IsRunning = false;//动画管理用，无实际running用途
}
void Hero_ryu::reborn(){//英雄重生
	hero_ani_block = false;//动画管理阻塞
	life_bar_fore->setVisible(true);//血条可见
	life_bar_back->setVisible(true);
	StopAnimation();
	HeroDirection = false;
	set_life(orginal_life);
	isdeath = false;
	set_statusoriginal();
	born_effect();//出生特效
}
void Hero_ryu::born_effect(){//出生特效
	Vector<SpriteFrame* > cache;//缓冲池
	char txt[50] = {};
	int i;
	for (i = 0; i <= 3; i++)
	{
		sprintf_s(txt, "%s%d.png", "born_", i);
		SpriteFrame* sf = m_frameCache->spriteFrameByName(txt);
		cache.pushBack(sf);
	}
	//使用列表创建动画对象  
	Animation* ani = Animation::createWithSpriteFrames(cache, 0.15f);
	ani->setLoops(1);//表示循环播放  

	Vector<SpriteFrame* > cache0;//缓冲池
	SpriteFrame* sf0 = m_frameCache->spriteFrameByName("born_3.png");
	cache0.pushBack(sf0);
	//使用列表创建动画对象  
	Animation* animation = Animation::createWithSpriteFrames(cache0, 0.2f);
	//将动画包装成一个动作  
	Animate* act0 = Animate::create(animation);
	auto fadeout = FadeOut::create(3);//淡出效果
	auto sprite = Sprite::create();
	Action *act = Sequence::create(
		Animate::create(ani),  //动画
		act0,
		fadeout,
		CCCallFuncN::create(sprite, callfuncN_selector(Hero_ryu::removeself)), //删除自己
		NULL);
	IsRunning = true;
	n_Sprite->addChild(sprite, -1);
	sprite->setAnchorPoint(Vec2(0.5, 0.5));
	sprite->setScale(0.4);
	sprite->setPosition(Vec2(24, 0));
	sprite->runAction(act);
}
void Hero_ryu::set_life_bar(int side){//设置血条样式
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
void Hero_ryu::set_life_bar_scaleX(float per){//设置血条百分比
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
	set_life_bar_scaleX(life / (float)orginal_life*0.6);//设置血条百分比
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