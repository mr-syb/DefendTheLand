#include "Tower_normal.h"

Tower_normal::Tower_normal(int side){
	Sprite::init();
	setName(Value(rand()).asString());//随机名字,scheduleOnce_Key用
	type_id = 31;//对象id
	is_melee_unit = false;//远程
	fly_kind = 2;
	life = 400;//生命值
	orginal_life = life;
	speed = 0;//移动速度
	damage_of_A = 0;
	attack_A_distance = 200;
	this->side = side;
	sprite_name = "public/tower_normal.png";//初始图片
	m_frameCache = CCSpriteFrameCache::sharedSpriteFrameCache();//加载
	this->m_Sprite = Sprite::create(sprite_name);
	this->setAnchorPoint(Vec2(0.5, 0));
	m_Sprite->setAnchorPoint(Vec2(0, 0));
	this->setContentSize(Size(48, 80));
	//新添加n_Sprite
	n_Sprite = Sprite::create();
	n_Sprite->setAnchorPoint(Vec2(0, 0));
	this->addChild(n_Sprite);
	n_Sprite->addChild(m_Sprite);
	IsRunning = false;//没在放动画
	if (side == 0){//初始朝向问题
		SpriteDirecton = false;//蓝色方朝右
	}
	else{
		SpriteDirecton = true;//红色方朝左
	}
	set_life_bar(side);
}
Tower_normal::~Tower_normal(){

}
void Tower_normal::core(){//智能核心
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
void Tower_normal::object_select(Vector<AllSprites *> sprites){//判定攻击目标
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
	/*
	AllSprites *s1 = nullptr, *s2 = nullptr, *s3 = nullptr;//备选三个单位
	float max_x;
	if (side == 0){//如果是蓝色方
		for (int i = 0; i < (chancellor.size() > 3 ? 3 : chancellor.size()); i++){//找到最前面的三个人
			max_x = chancellor.at(i)->getPosition().x;
			for (int j = i+1; j < chancellor.size(); j++){//遍历对象列表
				if (chancellor.at(j)->getPosition().x < max_x){
					max_x = chancellor.at(j)->getPosition().x;
					chancellor.swap(i, j);//调换位置
				}
			}
		}
	}
	else{//如果是红色方
		for (int i = 0; i < (chancellor.size() > 3 ? 3 : chancellor.size()); i++){//找到最前面的三个人
			max_x = chancellor.at(i)->getPosition().x;
			for (int j = i+1; j < chancellor.size(); j++){//遍历对象列表
				if (chancellor.at(j)->getPosition().x > max_x){
					max_x = chancellor.at(j)->getPosition().x;
					chancellor.swap(i, j);//调换位置
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
	//判断s123哪个离自己最近(两点间直线最短)
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
void Tower_normal::attack_ani(){//攻击
	if (!attack_A || ani_block){//如果不是攻击状态或者动画被阻塞
		return;
	}
	if (IsRunning)
		return;
	attack_A = false;//停止攻击
	hittest_A = true;//平A判定
	SimpleAudioEngine::getInstance()->playEffect(tower_normal_A);
}
void Tower_normal::attack_A_effect(AllSprites *enemy){//溅血效果
	hittest_A = false;
}
void Tower_normal::blood_effect(AllSprites *sprite){//溅血效果
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
		CCCallFuncN::create(sprite, callfuncN_selector(Tower_normal::removeself)), //删除自己
		NULL);
	sprite->addChild(blood, 10);
	blood->setAnchorPoint(Vec2(0.5, 0.5));
	blood->setScale(0.4);
	blood->setPosition(Vec2(24, 24));
	blood->runAction(act);
}
void Tower_normal::removeself(Node *pSender){//从父类移除图片特效
	pSender->removeFromParentAndCleanup(true);
}
void Tower_normal::move(){//朝着目标移动
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
		SpriteDirecton = false;
	}
	else{
		SpriteDirecton = true;
	}
	//攻击距离判定
	if (attack_gap <= 80){//防御塔判定机制稍有不同
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
	else if (attack_gap>80){//发动攻击
		attack_A = true;
		attack_gap = 0;
		point=object_aim->getPosition();
	}
	else{
		idle();
	}
}
void Tower_normal::idle(){
	StopAnimation();//当前精灵停止所有动画  
	//恢复精灵原来的初始化贴图
	//this->removeChild(m_Sprite, TRUE);//把原来的精灵删除掉
	n_Sprite->removeChild(m_Sprite, true);
	m_Sprite = Sprite::create(sprite_name);//恢复精灵原来的贴图样子  
	//m_Sprite->setFlipX(SpriteDirecton);
	m_Sprite->setAnchorPoint(Vec2(0, 0));//要重新设置锚点
	//this->addChild(m_Sprite);
	n_Sprite->addChild(m_Sprite);//修改的
	IsRunning = false;
}
void Tower_normal::deadth_ani(){
	SimpleAudioEngine::getInstance()->playEffect(tower_die);
	life_bar_fore->setVisible(false);//血条不可见
	life_bar_back->setVisible(false);
	StopAnimation();//当前精灵停止所有动画
	auto fadeout = FadeOut::create(1.5);//淡出效果
	CCCallFunc* callFunc = CCCallFunc::create(this, callfunc_selector(Tower_normal::setisOver));
	CCActionInterval* deathact = CCSequence::create(fadeout, callFunc, NULL);//序列动作
	m_Sprite->runAction(deathact);
}
void Tower_normal::setisOver(){
	isOver = true;
}
void Tower_normal::SetAnimation(int from, int to, bool run_directon, int loop){//动画
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
	Animation* animation = Animation::createWithSpriteFrames(cache, 0.25f);
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
void Tower_normal::StopAnimation(){//停止所有动画
	if (!IsRunning)
		return;
	m_Sprite->stopAllActions();//当前精灵停止所有动画  
	//恢复精灵原来的初始化贴图   
	//this->removeChild(m_Sprite, TRUE);//把原来的精灵删除掉
	n_Sprite->removeChild(m_Sprite, true);
	m_Sprite = Sprite::create(sprite_name);//恢复精灵原来的贴图样子  
	//m_Sprite->setFlipX(SpriteDirecton);
	m_Sprite->setAnchorPoint(Vec2(0, 0));//要重新设置锚点
	//this->addChild(m_Sprite);
	n_Sprite->addChild(m_Sprite);//修改的
	IsRunning = false;
	ani_block = false;//动画没有阻塞
	attack_A = false;//攻击取消
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