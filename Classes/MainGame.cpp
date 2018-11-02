#include "MainGame.h"
Vector<AllSprites *> MainGame::redSide;
Vector<AllSprites *> MainGame::allSprites;
bool MainGame::isVictory;//�Ƿ�ʤ��
bool MainGame::isGameOver=false;//�Ƿ����
MainGame::MainGame(Vector<CheckBox *> choosed_objects)
{
	this->choosed_objects = choosed_objects;
}
MainGame::~MainGame()
{
}
Scene* MainGame::createScene(Vector<CheckBox *> choosed_objects){
	auto scene = Scene::create();
	auto layer = MainGame::create(choosed_objects);
	layer->setTag(999);
	// add layer as a child to scene
	scene->addChild(layer);
	
	// return the scene
	return scene;
}
MainGame* MainGame::create(Vector<CheckBox *> choosed_objects){
	auto newGame = new MainGame(choosed_objects);
	newGame->init();
	return newGame;
}

bool MainGame::init(){
	if (!Layer::init()){
		return false;
	}
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto bg = Sprite::create("map0.jpg");//������������
	auto size = Director::getInstance()->getWinSize();//�����Ļ��С
	bg->setAnchorPoint(Vec2(0,0));
	this->addChild(bg, 0);

	level = new Level01();//�ؿ�
	//��������
	auto b_fountain = new Tower_normal(0);
	b_fountain->setPosition(Vec2(200, visibleSize.height / 2));
	this->addChild(b_fountain);
	blueSide.pushBack(b_fountain);
	allSprites.pushBack(b_fountain);

	auto r_fountain = new Tower_normal(1);
	r_fountain->setPosition(Vec2(760, visibleSize.height / 2));
	this->addChild(r_fountain);
	redSide.pushBack(r_fountain);
	allSprites.pushBack(r_fountain);
	//����ˮȪ
	auto fountain0 = new Fountain(0);
	fountain0->setPosition(Vec2(50, visibleSize.height / 2));
	fountain0->setTag(101);
	this->addChild(fountain0);
	blueSide.pushBack(fountain0);
	allSprites.pushBack(fountain0);

	auto fountain1 = new Fountain(1);
	fountain1->setPosition(Vec2(910, visibleSize.height / 2));
	fountain1->setTag(102);
	this->addChild(fountain1);
	redSide.pushBack(fountain1);
	allSprites.pushBack(fountain1);

	//���ҡ��
	rocker = HRocker::createHRocker("rocker/Rocker.png", "rocker/Rockerbg.png", ccp(120, 110));//���е�һ��ͼƬΪҡ�˵İ�ť���ڶ���Ϊ����
	this->addChild(rocker, 2);

	//���̼���
	listener = EventListenerKeyboard::create();
	listener->onKeyPressed = CC_CALLBACK_2(MainGame::keyBoardEvent, this);
	listener->onKeyReleased = CC_CALLBACK_2(MainGame::keyBoardStop, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	int men = 0;
	//��� ���������ϵ���ϷӦ���������ݿ������Ϣ
	for (int i = 0; i < choosed_objects.size(); i++){
		if (choosed_objects.at(i)->getTag()==0){
			reborn_cd = 10;//��ʼ����ʱ��5��
			hero = new Hero_ryu(0);
			money = hero->get_money();//��ʼ��Ǯ
			hero->setPosition(Vec2(100, visibleSize.height / 2));
			this->addChild(hero);
			blueSide.pushBack(hero);
			allSprites.pushBack(hero);
		}
		else if (choosed_objects.at(i)->getTag() == 5){
			soldier *soldier0 = new soldier();
			soldier0->tag = 5;
			soldier0->player_img = "public/player_5.png";
			soldier0->cost = sword;
			soldier0->cd = sword_cd;
			choosed[men]=soldier0;
			men++;
		}
		else if (choosed_objects.at(i)->getTag() == 6){
			soldier *soldier0 = new soldier();
			soldier0->tag = 6;
			soldier0->player_img = "public/player_6.png";
			soldier0->cost = pike;
			soldier0->cd = pike_cd;
			choosed[men] = soldier0;
			men++;
		}
		else if (choosed_objects.at(i)->getTag() == 7){
			soldier *soldier0 = new soldier();
			soldier0->tag = 7;
			soldier0->player_img = "public/player_7.png";
			soldier0->cost = bow;
			soldier0->cd = bow_cd;
			choosed[men] = soldier0;
			men++;
		}
		else if (choosed_objects.at(i)->getTag() == 8){
			soldier *soldier0 = new soldier();
			soldier0->tag = 8;
			soldier0->player_img = "public/player_8.png";
			soldier0->cost = cav;
			soldier0->cd = cav_cd;
			choosed[men] = soldier0;
			men++;
		}
		else if (choosed_objects.at(i)->getTag() == 9){
			soldier *soldier0 = new soldier();
			soldier0->tag = 9;
			soldier0->player_img = "public/player_9.png";
			soldier0->cost = shield;
			soldier0->cd = shield_cd;
			choosed[men] = soldier0;
			men++;
		}
		else if (choosed_objects.at(i)->getTag() == 10){
			soldier *soldier0 = new soldier();
			soldier0->tag = 10;
			soldier0->player_img = "public/player_10.png";
			soldier0->cost = shoot;
			soldier0->cd = shoot_cd;
			choosed[men] = soldier0;
			men++;
		}
		else if (choosed_objects.at(i)->getTag() == 11){
			soldier *soldier0 = new soldier();
			soldier0->tag = 11;
			soldier0->player_img = "public/player_11.png";
			soldier0->cost = horse;
			soldier0->cd = horse_cd;
			choosed[men] = soldier0;
			men++;
		}
		else if (choosed_objects.at(i)->getTag() == 12){
			soldier *soldier0 = new soldier();
			soldier0->tag = 12;
			soldier0->player_img = "public/player_12.png";
			soldier0->cost = spear;
			soldier0->cd = spear_cd;
			choosed[men] = soldier0;
			men++;
		}
	}
	//չλ1
	choose_back0 = Button::create("public/mercenary_back.png");
	choose_back0->setPosition(Vec2(60, visibleSize.height - 65));
	choose_back0->setAnchorPoint(Vec2(0.5, 0.5));
	choose_back0->addTouchEventListener(CC_CALLBACK_2(MainGame::touchEvent_buy_0, this, choosed[0]));
	this->addChild(choose_back0, 100);
	auto mer0 = Sprite::create(choosed[0]->player_img);
	mer0->setPosition(Vec2(44, 23));
	mer0->setAnchorPoint(Vec2(0.5, 0));
	mer0->setFlipX(-1);
	choose_back0->addChild(mer0, 1);
	auto back0_price = Text::create();
	back0_price->setString(StringUtils::format("%d", choosed[0]->cost));
	back0_price->setFontName("fonts/arial.ttf");
	back0_price->setFontSize(24);
	back0_price->setAnchorPoint(Vec2(0.5, 0.5));
	back0_price->setPosition(Vec2(44, 85));
	back0_price->enableOutline(Color4B(0, 0, 0, 255), 2);
	choose_back0->addChild(back0_price, 1);
	back0_text->setFontName("fonts/arial.ttf");
	back0_text->setFontSize(30);
	back0_text->setAnchorPoint(Vec2(0.5, 0.5));
	back0_text->setPosition(Vec2(45, -15));
	back0_text->enableOutline(Color4B(0, 0, 255, 255), 2);
	back0_text->setVisible(false);
	choose_back0->addChild(back0_text, 2);//��������ʱ��ȴ
	//�����϶�����1
	sprite_back0 = Sprite::create(choosed[0]->player_img);
	sprite_back0->setFlipX(-1);
	sprite_back0->setAnchorPoint(Vec2(0.5, 0.5));
	sprite_back0->setOpacity(180);
	sprite_back0->setVisible(false);
	this->addChild(sprite_back0,101);
	//չλ2
	choose_back1 = Button::create("public/mercenary_back.png");
	choose_back1->setPosition(Vec2(60+105, visibleSize.height - 65));
	choose_back1->setAnchorPoint(Vec2(0.5, 0.5));
	choose_back1->addTouchEventListener(CC_CALLBACK_2(MainGame::touchEvent_buy_1, this, choosed[1]));
	this->addChild(choose_back1, 100);
	auto mer1 = Sprite::create(choosed[1]->player_img);
	mer1->setPosition(Vec2(44, 23));
	mer1->setAnchorPoint(Vec2(0.5, 0));
	mer1->setFlipX(-1);
	choose_back1->addChild(mer1, 1);
	auto back1_price = Text::create();
	back1_price->setString(StringUtils::format("%d", choosed[1]->cost));
	back1_price->setFontName("fonts/arial.ttf");
	back1_price->setFontSize(24);
	back1_price->setAnchorPoint(Vec2(0.5, 0.5));
	back1_price->setPosition(Vec2(44, 85));
	back1_price->enableOutline(Color4B(0, 0, 0, 255), 2);
	choose_back1->addChild(back1_price, 1);
	back1_text->setFontName("fonts/arial.ttf");
	back1_text->setFontSize(30);
	back1_text->setAnchorPoint(Vec2(0.5, 0.5));
	back1_text->setPosition(Vec2(45, -15));
	back1_text->enableOutline(Color4B(0, 0, 255, 255), 2);
	back1_text->setVisible(false);
	choose_back1->addChild(back1_text, 2);//��������ʱ��ȴ
	//�����϶�����2
	sprite_back1 = Sprite::create(choosed[1]->player_img);
	sprite_back1->setFlipX(-1);
	sprite_back1->setAnchorPoint(Vec2(0.5, 0.5));
	sprite_back1->setOpacity(180);
	sprite_back1->setVisible(false);
	this->addChild(sprite_back1, 101);
	//չλ3
	choose_back2 = Button::create("public/mercenary_back.png");
	choose_back2->setPosition(Vec2(60 + 105 + 105, visibleSize.height - 65));
	choose_back2->setAnchorPoint(Vec2(0.5, 0.5));
	choose_back2->addTouchEventListener(CC_CALLBACK_2(MainGame::touchEvent_buy_2, this, choosed[2]));
	this->addChild(choose_back2, 100);
	auto mer2 = Sprite::create(choosed[2]->player_img);
	mer2->setPosition(Vec2(44, 23));
	mer2->setAnchorPoint(Vec2(0.5, 0));
	mer2->setFlipX(-1);
	choose_back2->addChild(mer2, 1);
	auto back2_price = Text::create();
	back2_price->setString(StringUtils::format("%d", choosed[2]->cost));
	back2_price->setFontName("fonts/arial.ttf");
	back2_price->setFontSize(24);
	back2_price->setAnchorPoint(Vec2(0.5, 0.5));
	back2_price->setPosition(Vec2(44, 85));
	back2_price->enableOutline(Color4B(0, 0, 0, 255), 2);
	choose_back2->addChild(back2_price, 1);
	back2_text->setFontName("fonts/arial.ttf");
	back2_text->setFontSize(30);
	back2_text->setAnchorPoint(Vec2(0.5, 0.5));
	back2_text->setPosition(Vec2(45, -15));
	back2_text->enableOutline(Color4B(0, 0, 255, 255), 2);
	back2_text->setVisible(false);
	choose_back2->addChild(back2_text, 2);//��������ʱ��ȴ
	//�����϶�����3
	sprite_back2 = Sprite::create(choosed[2]->player_img);
	sprite_back2->setFlipX(-1);
	sprite_back2->setAnchorPoint(Vec2(0.5, 0.5));
	sprite_back2->setOpacity(180);
	sprite_back2->setVisible(false);
	this->addChild(sprite_back2, 101);
	//չλ4
	choose_back3 = Button::create("public/mercenary_back.png");
	choose_back3->setPosition(Vec2(60 + 105 + 105 +105, visibleSize.height - 65));
	choose_back3->setAnchorPoint(Vec2(0.5, 0.5));
	choose_back3->addTouchEventListener(CC_CALLBACK_2(MainGame::touchEvent_buy_3, this, choosed[3]));
	this->addChild(choose_back3, 100);
	auto mer3 = Sprite::create(choosed[3]->player_img);
	mer3->setPosition(Vec2(44, 23));
	mer3->setAnchorPoint(Vec2(0.5, 0));
	mer3->setFlipX(-1);
	choose_back3->addChild(mer3, 1);
	auto back3_price = Text::create();
	back3_price->setString(StringUtils::format("%d", choosed[3]->cost));
	back3_price->setFontName("fonts/arial.ttf");
	back3_price->setFontSize(24);
	back3_price->setAnchorPoint(Vec2(0.5, 0.5));
	back3_price->setPosition(Vec2(44, 85));
	back3_price->enableOutline(Color4B(0, 0, 0, 255), 2);
	choose_back3->addChild(back3_price, 1);
	back3_text->setFontName("fonts/arial.ttf");
	back3_text->setFontSize(30);
	back3_text->setAnchorPoint(Vec2(0.5, 0.5));
	back3_text->setPosition(Vec2(45, -15));
	back3_text->enableOutline(Color4B(0, 0, 255, 255), 2);
	back3_text->setVisible(false);
	choose_back3->addChild(back3_text, 2);//��������ʱ��ȴ
	//�����϶�����3
	sprite_back3 = Sprite::create(choosed[3]->player_img);
	sprite_back3->setFlipX(-1);
	sprite_back3->setAnchorPoint(Vec2(0.5, 0.5));
	sprite_back3->setOpacity(180);
	sprite_back3->setVisible(false);
	this->addChild(sprite_back3, 101);
	
	//��ʾ��Ǯ
	auto money_back = Sprite::create("public/money_back.png");
	money_back->setPosition(Vec2(60 + 105 + 105 + 105 + 104, visibleSize.height - 65));
	money_back->setAnchorPoint(Vec2(0.5, 0.5));
	money_back->setScale(0.8);
	this->addChild(money_back, 100);
	money_text->setFontName("fonts/arial.ttf");
	if (money < 10){
		money_text->setString(StringUtils::format("00%d", money));
	}
	else if (money < 100){
		money_text->setString(StringUtils::format("0%d", money));
	}
	else {
		money_text->setString(StringUtils::format("%d", money));
	}
	money_text->setFontSize(40);
	money_text->setAnchorPoint(Vec2(0, 1));
	money_text->setPosition(Vec2(20, 74));
	money_text->enableOutline(Color4B(255, 215, 0, 255), 2);
	money_text->setTextColor(Color4B(70, 70, 70, 255));
	money_back->addChild(money_text,1);

	//��Ӱ���
	//ƽA
	A = Button::create(hero->get_attack_A_img());
	A->setAnchorPoint(Vec2(1, 0));
	A->setScale(0.8);
	A->setPosition(Vec2(visibleSize.width-A->getContentSize().width/3.6,A->getContentSize().height/3.6));
	A->addTouchEventListener(CC_CALLBACK_2(MainGame::touchEvent_A, this));
	this->addChild(A,100);
	//����J
	J = Button::create(hero->get_skill_J_img());
	J->setAnchorPoint(Vec2(1, 0));
	J->setScale(0.8);
	J->setPosition(Vec2(visibleSize.width-J->getContentSize().width*1.17,J->getContentSize().height/3.6));
	J->addTouchEventListener(CC_CALLBACK_2(MainGame::touchEvent_J, this));
	this->addChild(J,100);
	J->addChild(text_J_timer,2);//��������ʱ��ȴ
	text_J_timer->setFontName("fonts/arial.ttf");
	text_J_timer->setFontSize(50);
	text_J_timer->setAnchorPoint(Vec2(0, 0));
	text_J_timer->setPosition(Vec2(28, 33));
	text_J_timer->enableOutline(Color4B(0,0,0,255),3);
	text_J_timer->setVisible(false);
	//����K
	K = Button::create(hero->get_skill_K_img());
	K->setAnchorPoint(Vec2(1, 0));
	K->setScale(0.8);
	K->setPosition(Vec2(visibleSize.width - A->getContentSize().width/3.6, A->getContentSize().height*1.17));
	K->addTouchEventListener(CC_CALLBACK_2(MainGame::touchEvent_K,this));
	this->addChild(K,100);
	K->addChild(text_K_timer, 2);//��������ʱ��ȴ
	text_K_timer->setFontName("fonts/arial.ttf");
	text_K_timer->setFontSize(50);
	text_K_timer->setAnchorPoint(Vec2(0, 0));
	text_K_timer->setPosition(Vec2(28, 33));
	text_K_timer->enableOutline(Color4B(0, 0, 0, 255), 3);
	text_K_timer->setVisible(false);
	//����ͷ��
	icon_head = Sprite::create(hero->get_icon_head_img());
	icon_head->setAnchorPoint(Vec2(0.5,0.5));
	icon_head->setScale(0.6);
	icon_head->setPosition(Vec2(290, 90));
	this->addChild(icon_head,2);
	//����Ѫ��
	life_bar_back = Sprite::create("public/blood_bar_back.png");
	life_bar_fore = Sprite::create("public/blue_fore.png");
	life_bar_fore->setAnchorPoint(Vec2(0, 0.5));
	life_bar_back->setAnchorPoint(Vec2(0, 0.5));
	life_bar_fore->setPosition(Vec2(343, 94));
	life_bar_back->setPosition(Vec2(343, 90));
	life_bar_fore->setScaleX(3.84);
	life_bar_back->setScaleX(0.35);
	life_bar_fore->setScaleY(3.98);
	life_bar_back->setScaleY(0.5);
	life_bar_fore->setOpacity(150);
	this->addChild(life_bar_back,0);
	this->addChild(life_bar_fore, 1);
	//����Ѫ����
	hero_life = hero->get_life();
	hero_original_life = hero_life;
	//����ֵ��ʾ
	life_text->setFontName("fonts/arial.ttf");
	life_text->setFontSize(30);
	life_text->setAnchorPoint(Vec2(0.5, 0.5));
	life_text->setPosition(Vec2(497, 94));
	life_text->enableOutline(Color4B(0, 0, 0, 255), 3);
	life_text->setString(StringUtils::format("%d/%d", hero_life, hero_original_life));
	this->addChild(life_text,2);
	//��������ͼ��
	skull = Sprite::create("public/skull.png");
	skull->setAnchorPoint(Vec2(0.5, 0.5));
	skull->setScale(0.3);
	skull->setPosition(Vec2(290, 92));
	skull->setVisible(false);
	this->addChild(skull,3);
	//��������ʱ
	reborn_timer->setFontName("fonts/arial.ttf");
	reborn_timer->setTextHorizontalAlignment(TextHAlignment::CENTER);
	reborn_timer->setFontSize(44);
	reborn_timer->setAnchorPoint(Vec2(0, 1));
	reborn_timer->setPosition(Vec2(visibleSize.width / 2 + 180, visibleSize.height - 80));
	//reborn_timer->setTextColor(Color4B(255, 0, 0, 255));
	reborn_timer->enableOutline(Color4B(255, 0, 0, 255), 2);
	reborn_timer->setVisible(false);
	this->addChild(reborn_timer, 99);
	//��������
	title->setFontName("fonts/arial.ttf");
	title->setFontSize(46);
	title->setAnchorPoint(Vec2(0.5, 0.5));
	title->setPosition(Vec2(visibleSize.width / 2 + 220, visibleSize.height - 40));
	title->enableOutline(Color4B(0, 0, 0, 255), 3);
	title->setVisible(false);
	this->addChild(title, 100);
	//ʱ����ʾ
	time->setFontName("fonts/arial.ttf");
	time->setString("00:00");
	time->setFontSize(30);
	time->setAnchorPoint(Vec2(0, 1));
	time->setPosition(Vec2(visibleSize.width-96, visibleSize.height - 13));
	time->enableOutline(Color4B(0, 0, 0, 255), 1);
	this->addChild(time, 100);
	//����
	SimpleAudioEngine::getInstance()->playEffect(fight);
	
	this->scheduleUpdate();//Ĭ�ϵ���Ψһupdate()
	this->schedule(CC_CALLBACK_1(MainGame::object_select, this), 0.5f, "object_select");//ÿ���ж����﹥��Ŀ��
	this->schedule(CC_CALLBACK_1(MainGame::level_run, this), 1, "level_run");//ÿ��ִ�йؿ�����
	this->schedule(CC_CALLBACK_1(MainGame::display_time, this), 1, "display_time");//��ʾʱ��
	this->schedule(CC_CALLBACK_1(MainGame::addMoney, this), 2, "addMoney");//���ӽ�Ǯ��ÿ�����1

	return true;
}
void MainGame::addMoney(float dt){
	money++;
	if (money < 10){
		money_text->setString(StringUtils::format("00%d", money));
	}
	else if (money < 100){
		money_text->setString(StringUtils::format("0%d", money));
	}
	else {
		money_text->setString(StringUtils::format("%d", money));
	}
}
void MainGame::display_time(float dt){
	second++;
	if (second == 60){
		minute++;
		second = 0;
	}
	if (second < 10 && minute < 10){
		time->setString(StringUtils::format("0%d:0%d", minute, second));
	}
	else if (second>=10 && minute < 10){
		time->setString(StringUtils::format("0%d:%d", minute, second));
	}
	else if (second < 10 && minute>=10){
		time->setString(StringUtils::format("%d:0%d", minute, second));
	}
	else if (second >=10 && minute >= 10){
		time->setString(StringUtils::format("%d:%d", minute, second));
	}
}

void MainGame::level_run(float dt){//ִ�йؿ�
	level->commander();
}
void MainGame::replace(){//�ָ�����
	isGameOver = false;
	blueSide.clear();
	redSide.clear();
	allSprites.clear();
}
void MainGame::back(){//�������ϼ�
	replace();//�ָ�MainGame����
	Director::getInstance()->popToRootScene();
	auto hello = HelloWorld::createScene();
	Director::getInstance()->replaceScene(TransitionFade::create(0.5f, hello));
	SimpleAudioEngine::getInstance()->playBackgroundMusic(menu_back);
	SimpleAudioEngine::getInstance()->playEffect(click);
}
void MainGame::gameOver(){//��Ϸ����
	unscheduleAllCallbacks();
	unscheduleAllSelectors();
	unscheduleUpdate();
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Sprite *sprite;
	if (isVictory){
		SimpleAudioEngine::getInstance()->playEffect(victory);
		sprite = Sprite::create("public/victory.png");
		sprite->setAnchorPoint(Vec2(0.5, 0.5));
		sprite->setPosition(Vec2(visibleSize.width / 2-15, visibleSize.height / 2 + 100));
		//sprite->addTouchEventListener(CC_CALLBACK_0(MainGame::back, this));
		this->addChild(sprite, 100);
	}
	else{
		SimpleAudioEngine::getInstance()->playEffect(defeat);
		sprite = Sprite::create("public/defeat.png");
		sprite->setAnchorPoint(Vec2(0.5, 0.5));
		sprite->setPosition(Vec2(visibleSize.width / 2-15, visibleSize.height / 2 + 100));
		//sprite->addTouchEventListener(CC_CALLBACK_0(MainGame::back, this));
		this->addChild(sprite, 100);
	}
	//��ť
	auto btn = Button::create("public/return.png");
	btn->setScale(0.7);
	btn->setAnchorPoint(Vec2(0.5, 0.5));
	btn->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2-20));
	btn->addTouchEventListener(CC_CALLBACK_0(MainGame::back, this));
	this->addChild(btn, 100);
	btn->setOpacity(0);
	auto fade0 = FadeIn::create(1);
	auto sequence = Sequence::create(DelayTime::create(0.8), fade0, NULL);
	btn->runAction(sequence);
	sprite->setScale(1.3);
	sprite->setOpacity(0);
	auto scale = ScaleTo::create(0.4, 1);
	auto fade1 = FadeIn::create(1);
	auto spawn = Spawn::create(scale, fade1, NULL);
	sprite->runAction(spawn);
}
void MainGame::update(float dt){//��Ϸ��ѭ��
	if (isGameOver){//��Ϸ����
		gameOver();
	}
	set_blood_bar();//����Ӣ��Ѫ���ٷֱ�
	coreCenter();//���AI
	hero_ani_manager();//Ӣ�۶�������
	Hittest_center();//��ײ�������
	deathCenter();//�Ƴ���λ
	setZorder();//�����㼶˳��
	//log("%.2f,%.2f",hero->getPosition().x,hero->getPosition().y);
	//log("%.2f,%.2f",hero->getContentSize().width, hero->getContentSize().height);
	//log("%d,%f", hero->get_life(), hero->get_speed());
}
void MainGame::coreCenter(){//���AI
	for (int i = 0; i < redSide.size(); i++){
		redSide.at(i)->core();
	}
	
	for (int i = 0; i < blueSide.size(); i++){
		blueSide.at(i)->core();
	}
}

void MainGame::object_select(float dt){//����ж�����Ŀ��
	for (int i = 0; i < blueSide.size(); i++){
		blueSide.at(i)->object_select(redSide);
	}
	for (int i = 0; i < redSide.size(); i++){
		redSide.at(i)->object_select(blueSide);
	}
}
void MainGame::Hittest_center(){//��ײ�������
	hittest_remote();//Զ�̵�λ���
	hittest_melee();//��ս��λ���
}
void MainGame::hittest_remote(){//Զ�̵�λ���
	for (int i = 0; i < blueSide.size(); i++){//�������
		bool isdeath_i = blueSide.at(i)->get_isdeath();
		bool is_meleei = blueSide.at(i)->is_melee();
		if (isdeath_i||is_meleei){//�����λ��������Ϊ��ս��λ��������ѭ��
			continue;
		}
		bool hittest_A = blueSide.at(i)->get_hittest_A();
		bool hittest_J = blueSide.at(i)->get_hittest_J();
		bool hittest_K = blueSide.at(i)->get_hittest_K();
		if (hittest_A){//ƽA�����ӵ�
			blueSide.at(i)->attack_A_effect(blueSide.at(i));
			addBullet(0, blueSide.at(i));
		}
		if (hittest_J){//����J
			blueSide.at(i)->skill_J_attack(blueSide.at(i));
		}
		if (hittest_K){//����K
			blueSide.at(i)->skill_K_attack(blueSide.at(i));
		}
	}
	for (int i = 0; i < redSide.size(); i++){//�췽���
		bool isdeath_i = redSide.at(i)->get_isdeath();
		bool is_meleei = redSide.at(i)->is_melee();
		if (isdeath_i||is_meleei){//�����λ������Ϊ��ս��λ��������ѭ��
			continue;
		}
		bool hittest_A = redSide.at(i)->get_hittest_A();
		bool hittest_J = redSide.at(i)->get_hittest_J();
		bool hittest_K = redSide.at(i)->get_hittest_K();
		if (hittest_A){//ƽA�����ӵ�
			redSide.at(i)->attack_A_effect(redSide.at(i));
			addBullet(1, redSide.at(i));
		}
		if (hittest_J){//����J
			redSide.at(i)->skill_J_attack(redSide.at(i));
		}
		if (hittest_K){//����K
			redSide.at(i)->skill_K_attack(redSide.at(i));
		}
	}
}
void MainGame::addBullet(int side,AllSprites *s){//�ٻ����е���
	float x = s->getPosition().x;
	float y = s->getPosition().y;
	auto kind = s->get_fly_kind();//��ȡ���е�������
	auto direction = s->get_Direction();//��õ�λ����
	int dir;//���з���
	if (direction){
		dir = 1;
	}
	else{
		dir = 0;
	}
	AllSprites *arrow0;
	AllSprites *arrow1;
	AllSprites *arrow2;
	switch (kind)
	{
	case -1:
		break;
	case 0://0�ͷ��е���
		arrow0 = new Fly0(dir);
		if (side==0){
			if (dir){
				arrow0->setPosition(Vec2(x, y));
			}
			else{
				arrow0->setPosition(Vec2(x, y));
			}
			blueSide.pushBack(arrow0);
		}
		else{
			if (dir){
				arrow0->setPosition(Vec2(x, y));
			}
			else{
				arrow0->setPosition(Vec2(x, y));
			}
			redSide.pushBack(arrow0);
		}
		this->addChild(arrow0);
		break;
	case 1://1�ͷ��е���
		arrow0 = new Fly1(dir);
		arrow1 = new Fly1(dir);
		arrow2 = new Fly1(dir);
		if (side == 0){
			if (dir){
				arrow0->setPosition(Vec2(x, y));
				arrow1->setPosition(Vec2(x, y + 8));
				arrow2->setPosition(Vec2(x, y - 8));
			}
			else{
				arrow0->setPosition(Vec2(x, y));
				arrow1->setPosition(Vec2(x, y + 8));
				arrow2->setPosition(Vec2(x, y - 8));
			}
			blueSide.pushBack(arrow0);
			blueSide.pushBack(arrow1);
			blueSide.pushBack(arrow2);
		}
		else{
			if (dir){
				arrow0->setPosition(Vec2(x, y));
				arrow1->setPosition(Vec2(x, y + 8));
				arrow2->setPosition(Vec2(x, y - 8));
			}
			else{
				arrow0->setPosition(Vec2(x, y));
				arrow1->setPosition(Vec2(x, y + 8));
				arrow2->setPosition(Vec2(x, y - 8));
			}
			redSide.pushBack(arrow0);
			redSide.pushBack(arrow1);
			redSide.pushBack(arrow2);
		}
		this->addChild(arrow0);
		this->addChild(arrow1);
		this->addChild(arrow2);
		break;
	case 2:
		arrow0 = new Fly2(dir,s->get_object_aim_pst());
		if (side == 0){
			if (dir){
				arrow0->setPosition(Vec2(x, y));
			}
			else{
				arrow0->setPosition(Vec2(x, y));
			}
			blueSide.pushBack(arrow0);
		}
		else{
			if (dir){
				arrow0->setPosition(Vec2(x, y));
			}
			else{
				arrow0->setPosition(Vec2(x, y));
			}
			redSide.pushBack(arrow0);
		}
		this->addChild(arrow0,100);
		break;
	default:
		break;
	}
}
void MainGame::hittest_melee(){//��ս��λ���
	for (int i = 0; i < blueSide.size(); i++){//�������
		bool isdeath_i = blueSide.at(i)->get_isdeath();
		bool is_meleei = blueSide.at(i)->is_melee();
		if (isdeath_i||!is_meleei){//�����λ��������ΪԶ�̵�λ��������ѭ��
			continue;
		}
		bool hittest_A = blueSide.at(i)->get_hittest_A();
		bool hittest_J = blueSide.at(i)->get_hittest_J();
		bool hittest_K = blueSide.at(i)->get_hittest_K();
		for (int j = 0; j < redSide.size(); j++){
			bool isdeath_j = redSide.at(j)->get_isdeath();
			bool is_fly = redSide.at(j)->is_fly_kind();
			if (isdeath_j||is_fly){//�����λ������Ϊ���е�����������ѭ��
				continue;
			}
			if (ishit_mercenary(blueSide.at(i), redSide.at(j))){//��������Ŀ��
				if (hittest_A){//ƽA
					blueSide.at(i)->attack_A_effect(redSide.at(j));
				}
				if (hittest_J){//����J
					blueSide.at(i)->skill_J_attack(redSide.at(j));
				}
				if (hittest_K){//����K
					blueSide.at(i)->skill_K_attack(redSide.at(j));
				}
			}
		}
	}
	for (int i = 0; i < redSide.size(); i++){//�췽���
		bool isdeath_i = redSide.at(i)->get_isdeath();
		bool is_meleei = redSide.at(i)->is_melee();
		if (isdeath_i||!is_meleei){//�����λ������ΪԶ�̵�λ��������ѭ��
			continue;
		}
		bool hittest_A = redSide.at(i)->get_hittest_A();
		bool hittest_J = redSide.at(i)->get_hittest_J();
		bool hittest_K = redSide.at(i)->get_hittest_K();
		for (int j = 0; j < blueSide.size(); j++){
			bool isdeath_j = blueSide.at(j)->get_isdeath();
			bool is_fly = blueSide.at(j)->is_fly_kind();
			if (isdeath_j||is_fly){//�����λ������Ϊ���е�����������ѭ��
				continue;
			}
			if (ishit_mercenary(redSide.at(i), blueSide.at(j))){//��������Ŀ��
				if (hittest_A){//ƽA
					redSide.at(i)->attack_A_effect(blueSide.at(j));
				}
				if (hittest_J){//����J
					redSide.at(i)->skill_J_attack(blueSide.at(j));
				}
				if (hittest_K){//����K
					redSide.at(i)->skill_K_attack(blueSide.at(j));
				}
			}
		}			
	}
	//һ��ɨ��û�й�������ȫ������Ϊfalse
	for (int i = 0; i < allSprites.size(); i++){
		allSprites.at(i)->set_hittest_A(false);
	}
}
bool MainGame::ishit_mercenary(AllSprites *s1, AllSprites *s2){//��ײ���
	float x1 = s1->getPosition().x;
	float y1 = s1->getPosition().y;
	float w1 = s1->getContentSize().width;
	float h1 = s1->getContentSize().height;
	float x2 = s2->getPosition().x;
	float y2 = s2->getPosition().y;
	float w2 = s2->getContentSize().width;
	float h2 = s2->getContentSize().height;
	if (abs(y1 - y2) > 10){//�߶Ȳ����10����
		return false;
	}
	if (x1 + s1->get_attack_A_distance() < x2 - w2*0.5)
		return false;//����1�ھ���2�󷽣���������ײ  
	else if (x1 - s1->get_attack_A_distance() > x2 + w2*0.5)
		return false;//����1�ھ���2�ҷ�����������ײ  
	/*
	//����Ƿ��е������������ж�
	bool is_fly = s1->is_fly_kind();
	if (is_fly){
		return true;
	}
	*/
	bool direction = s1->get_Direction();//��ȡ����
	if (direction == true && x1<x2){//�������
		return false;
	}
	if (direction == false && x1>x2){//�������
		return false;
	}
	return true;
}
void MainGame::deathCenter(){//����������λ
	//��λ����
	for (int i = 0; i < allSprites.size(); i++){
		if (allSprites.at(i)->get_isOver()){
			allSprites.at(i)->removeFromParent();
			allSprites.eraseObject(allSprites.at(i));
		}
	}
	for (int i = 0; i < redSide.size(); i++){
		if (redSide.at(i)->get_isdeath()&&!redSide.at(i)->get_money_paid()){
			redSide.at(i)->set_money_paid(true);
			money += redSide.at(i)->earn_money();
			if (money < 10){
				money_text->setString(StringUtils::format("00%d", money));
			}
			else if (money < 100){
				money_text->setString(StringUtils::format("0%d", money));
			}
			else {
				money_text->setString(StringUtils::format("%d", money));
			}
		}
		if (redSide.at(i)->get_isOver()){
			redSide.at(i)->removeFromParent();
			redSide.eraseObject(redSide.at(i));
		}
	}
	for (int i = 0; i < blueSide.size(); i++){
		if (blueSide.at(i)->get_isOver()){
			blueSide.at(i)->removeFromParent();
			blueSide.eraseObject(blueSide.at(i));
		}
	}
}
void MainGame::hero_ani_manager(){//Ӣ�۶�������
	if (hero->get_life() <= 0&&hero->get_isdeath()==false){//���Ӣ������
		SimpleAudioEngine::getInstance()->playEffect(ryu_die);
		hero->death_ani();
		skull->setVisible(true);//����ͼ����ʾ
		reborn_timer->setVisible(true);//���ֿɼ�
		reborn_timer->setOpacity(0);
		reborn_timer->runAction(FadeIn::create(0.5));
		scheduleOnce(schedule_selector(MainGame::hero_reborn),reborn_cd);//Ӣ����������ʱ
		reborn_time_left = reborn_cd;//ʣ��ʱ��
		schedule(schedule_selector(MainGame::set_reborn_timer),0.1f);
		title->setVisible(true);//����ɼ�
		title->setString("Reborn time");
		title->enableOutline(Color4B(255, 0, 0, 255), 2);
		title->setScale(0);
		title->setOpacity(0);
		auto scale = ScaleTo::create(0.2, 1);
		auto fade = FadeIn::create(0.5);
		auto spawn = Spawn::create(scale, fade, NULL);
		title->runAction(spawn);
		return;
	}
	if (hero->get_life() <= 0){//ǿ�Ʒ���
		return;
	}
	bool hero_ani_block = hero->get_hero_ani_block();
	if (hero_ani_block){//�������������������
		return;
	}
	bool attack_A = hero->get_attack_A();
	bool run_direction = hero->get_Direction();
	bool skill_J = hero->get_skill_J();
	bool skill_K = hero->get_skill_K();
	bool isWalk = hero->get_isWalk();
	if (skill_J){//��������J
		hero->skill_J_ani(redSide);
		return;
	}
	if (skill_K){//��������K
		hero->skill_K_ani(redSide);
		return;
	}
	if (attack_A){//����ƽA
		hero->attack_A_animation(run_direction);
		return;
	}
	moveControl();//��·
}
void MainGame::hero_reborn(float dt){//Ӣ������
	SimpleAudioEngine::getInstance()->playEffect(reborn);
	skull->setVisible(false);//����ͼ����ʧ
	reborn_timer->setVisible(false);//���ֲ��ɼ�
	unschedule(schedule_selector(MainGame::set_reborn_timer));//�����������ʱ
	title->setVisible(false);
	reborn_cd += 5;//5�����
	hero->setPosition(Vec2(100, Director::getInstance()->getVisibleSize().height / 2));
	hero->reborn();
}
void MainGame::setZorder(){//�����㼶˳��
	for (int i = 0; i < allSprites.size(); i++){//ð������y����Ӹߵ�����
		for (int j = i + 1; j < allSprites.size(); j++){
			if (allSprites.at(i)->getPosition().y < allSprites.at(j)->getPosition().y){
				allSprites.swap(i, j);
			}
		}
	}
	Sprite *sprite;
	for (int i = 0; i < allSprites.size(); i++){
		sprite = allSprites.at(i);
		sprite->setZOrder(i);
	}
}
void MainGame::moveControl(){
	//����ʹӢ����������
	if (hero->getPosition().x > 960){
		hero->setPosition(Vec2(960, hero->getPosition().y));
		return;
	}
	else if (hero->getPosition().x < 0){
		hero->setPosition(Vec2(0, hero->getPosition().y));
		return;
	}
	else if (hero->getPosition().y > 475){
		hero->setPosition(Vec2(hero->getPosition().x, 475));
		return;
	}
	else if (hero->getPosition().y < 192){
		hero->setPosition(Vec2(hero->getPosition().x, 192));
		return;
	}
	auto speed = hero->get_speed();//���Ӣ���ٶ�
	hero->set_isMoving(true);
	switch (rocker->rocketDirection)
	{
	case 1:
		hero->walk(rocker->rocketRun,-1);//������·����
		hero->setPosition(ccp(hero->getPosition().x + speed, hero->getPosition().y)); //������  
		break;
	case  2:
		hero->walk(rocker->rocketRun, -1);//������·����
		hero->setPosition(ccp(hero->getPosition().x, hero->getPosition().y + speed*0.75));   //������  
		break;
	case 3:
		hero->walk(rocker->rocketRun, -1);//������·����
		hero->setPosition(ccp(hero->getPosition().x - speed, hero->getPosition().y));   //������  
		break;
	case 4:
		hero->walk(rocker->rocketRun, -1);//������·����
		hero->setPosition(ccp(hero->getPosition().x, hero->getPosition().y - speed*0.75));   //������  
		break;
	default:
		hero->StopAnimation();//ֹͣ���ж������˶�
		hero->set_isMoving(false);
		break;
	}
}
void MainGame::keyBoardEvent(EventKeyboard::KeyCode code, Event* evt){//WASD
	switch (int(code)){
	case 146:
		rocker->setrocketDirection(rocker_up);
		keypressed++;
		break;
	case 124:
		rocker->setrocketDirection(rocker_left);
		rocker->rocketRun = true;
		keypressed++;
		break;
	case 142:
		rocker->setrocketDirection(rocker_down);
		keypressed++;
		break;
	case 127:
		rocker->setrocketDirection(rocker_right);
		rocker->rocketRun = false;
		keypressed++;
		break;
	}
	
}
void MainGame::keyBoardStop(EventKeyboard::KeyCode code, Event* evt){
	if (int(code) == 146 || int(code) == 124 || int(code) == 142 || int(code) == 127){
		keypressed--;
	}
	if (keypressed <= 0){
		keypressed = 0;
		rocker->setrocketDirection(rocker_stay);
	}
}
void MainGame::touchEvent_A(Ref* pSender, Widget::TouchEventType type){//ƽA
	float A_cd = hero->get_A_cd();
	switch (type)
	{
	case Widget::TouchEventType::BEGAN:
		hero->set_attack_A(true);
		button_A_cd(A_cd);
		break;
	case Widget::TouchEventType::MOVED:
		break;
	case Widget::TouchEventType::ENDED:
		break;
	default:
		//hero->StopAnimation();
		break;
	}
}
void MainGame::button_A_cd(float duration){//A��ʼ��ȴ
	A->setEnabled(false);
	CCSprite *s = CCSprite::create(hero->get_attack_A_img());
	CCProgressTimer *pt = CCProgressTimer::create(s);
	pt->setType(cocos2d::CCProgressTimerType(kCCProgressTimerTypeRadial));
	pt->setAnchorPoint(Vec2(0, 0));
	A->addChild(pt, 1);
	CCProgressTo *t = CCProgressTo::create(duration, 100);
	Sequence *act0 = Sequence::create(t, CCCallFuncN::create(pt, callfuncN_selector(MainGame::removeself)), NULL); //ɾ���Լ�
	CCCallFunc *callFunc = CCCallFunc::create(CC_CALLBACK_0(MainGame::button_A_cd_recover, this));//����Hero_ryuʵ��λ��
	CCActionInterval* act1 = CCSequence::create(act0, callFunc, NULL);//���ж���
	pt->runAction(act1);
}
void MainGame::button_A_cd_recover(){//ƽA��ȴ���
	A->setEnabled(true);
}
void MainGame::touchEvent_J(Ref* pSender, Widget::TouchEventType type){//����J
	bool skill_J = hero->get_skill_J();
	float J_cd = hero->get_J_cd();
	text_J_timer->setString(StringUtils::format("%.1f", J_cd));//ת��Ϊ�ַ��ʹ���,Ҫ��ǰ�ȼ�0.1
	switch (type)
	{
	case Widget::TouchEventType::BEGAN:
		hero->set_skill_J(true);
		button_J_cd(J_cd);
		schedule(schedule_selector(MainGame::button_J_timer), 0.1f);//����ʱ���
		text_J_timer->setVisible(true);
		break;
	case Widget::TouchEventType::MOVED:
		break;
	case Widget::TouchEventType::ENDED:
		break;
	default:
		//hero->StopAnimation();
		break;
	}
}
void MainGame::button_J_cd(float duration){//J��ʼ��ȴ
	J->setEnabled(false);
	CCSprite *s = CCSprite::create(hero->get_skill_J_img());
	CCProgressTimer *pt = CCProgressTimer::create(s);
	pt->setType(cocos2d::CCProgressTimerType(kCCProgressTimerTypeRadial));
	pt->setAnchorPoint(Vec2(0,0));
	J->addChild(pt,1);
	CCProgressTo *t = CCProgressTo::create(duration, 100);
	Sequence *act0 = Sequence::create(t, CCCallFuncN::create(pt, callfuncN_selector(MainGame::removeself)), NULL); //ɾ���Լ�
	CCCallFunc *callFunc = CCCallFunc::create(CC_CALLBACK_0(MainGame::button_J_cd_recover, this));
	CCActionInterval* act1 = CCSequence::create(act0, callFunc, NULL);//���ж���
	pt->runAction(act1);
}
void MainGame::button_J_cd_recover(){//J��ȴ���
	J->setEnabled(true);
	text_J_timer->setVisible(false);
	unschedule(schedule_selector(MainGame::button_J_timer));
}
void MainGame::button_J_timer(float dt){//ÿ�μ�ȥ0.1��
	String J_cd_string = text_J_timer->getString();
	float num = J_cd_string.floatValue();
	num -= dt;
	text_J_timer->setString(StringUtils::format("%.1f", num));//ת��Ϊ�ַ��ʹ���
}
void MainGame::removeself(Node *pSender){//�Ӹ����Ƴ�
	pSender->removeFromParentAndCleanup(true);
}
void MainGame::touchEvent_K(Ref* pSender, Widget::TouchEventType type){//����K
	bool skill_K = hero->get_skill_K();
	float K_cd = hero->get_K_cd();
	text_K_timer->setString(StringUtils::format("%.1f", K_cd));//ת��Ϊ�ַ��ʹ���,Ҫ��ǰ�ȼ�0.1
	switch (type)
	{
	case Widget::TouchEventType::BEGAN:
		hero->set_skill_K(true);
		button_K_cd(K_cd);
		schedule(schedule_selector(MainGame::button_K_timer), 0.1f);//����ʱ���
		text_K_timer->setVisible(true);
		break;
	case Widget::TouchEventType::MOVED:
		break;
	case Widget::TouchEventType::ENDED:
		break;
	default:
		//hero->StopAnimation();
		break;
	}
}
void MainGame::button_K_cd(float duration){//K��ʼ��ȴ
	K->setEnabled(false);
	CCSprite *s = CCSprite::create(hero->get_skill_K_img());
	CCProgressTimer *pt = CCProgressTimer::create(s);
	pt->setType(cocos2d::CCProgressTimerType(kCCProgressTimerTypeRadial));
	pt->setAnchorPoint(Vec2(0, 0));
	K->addChild(pt, 1);
	CCProgressTo *t = CCProgressTo::create(duration, 100);
	Sequence *act0 = Sequence::create(t, CCCallFuncN::create(pt, callfuncN_selector(MainGame::removeself)), NULL); //ɾ���Լ�
	CCCallFunc *callFunc = CCCallFunc::create(CC_CALLBACK_0(MainGame::button_K_cd_recover, this));//����Hero_ryuʵ��λ��
	CCActionInterval* act1 = CCSequence::create(act0, callFunc, NULL);//���ж���
	pt->runAction(act1);
}
void MainGame::button_K_cd_recover(){//K��ȴ���
	K->setEnabled(true);
	text_K_timer->setVisible(false);
	unschedule(schedule_selector(MainGame::button_K_timer));
}
void MainGame::button_K_timer(float dt){//ÿ�μ�ȥ0.1��
	String K_cd_string = text_K_timer->getString();
	float num = K_cd_string.floatValue();
	num -= dt;
	text_K_timer->setString(StringUtils::format("%.1f", num));//ת��Ϊ�ַ��ʹ���
}
void MainGame::set_blood_bar(){//����Ӣ��Ѫ���ٷֱ�
	if (hero_life == hero->get_life()){
		return;
	}
	else{
		hero_life = hero->get_life();
		auto act = ScaleTo::create(0.2f, hero_life / (float)hero_original_life*3.84, 3.98);
		life_bar_fore->runAction(act);
		life_text->setString(StringUtils::format("%d/%d", hero_life,hero_original_life));
	}
}
void MainGame::set_reborn_timer(float dt){//������������ʱ
	reborn_time_left -= dt;
	if (reborn_time_left >= 9.9f){
		reborn_timer->setString(StringUtils::format("%.1f", reborn_time_left));
	}
	else{
		reborn_timer->setString(StringUtils::format("0%.1f", reborn_time_left));
	}
}
void MainGame::touchEvent_buy_0(Ref* pSender, Widget::TouchEventType type, soldier *man){//�������
	int cost = man->cost;
	float buy_cd = man->cd;
	switch (type)
	{
	case Widget::TouchEventType::BEGAN:
		if (money < cost){
			SimpleAudioEngine::getInstance()->playEffect(notenough);
			back0_text->setOpacity(255);
			back0_text->setString(" Not enough!");
			back0_text->enableOutline(Color4B(255, 0, 0, 255), 2);
			back0_text->setFontSize(20);
			back0_text->setVisible(true);
			scheduleOnce(CC_CALLBACK_1(MainGame::lack_of_money, this, back0_text), 1.0f, "lack_of_money0");
			return;
		}
		break;
	case Widget::TouchEventType::MOVED:
		if (money < cost){
			return;
		}
		if (!sprite_back0->isVisible()){
			sprite_back0->setVisible(true);
		}
		sprite_back0->setPosition(Vec2(choose_back0->getTouchMovePosition().x, choose_back0->getTouchMovePosition().y));
		break;
	case Widget::TouchEventType::ENDED:
		sprite_back0->setVisible(false);
		break;
	case Widget::TouchEventType::CANCELED:
		sprite_back0->setVisible(false);
		if (money < cost){
			return;
		}
		change_x0 = false;
		if (choose_back0->getTouchEndPosition().y >= 498 || choose_back0->getTouchEndPosition().y <= 210){//����ص�
			SimpleAudioEngine::getInstance()->playEffect(notenough);
			back0_text->setOpacity(255);
			back0_text->setString(" Wrong place!");
			back0_text->enableOutline(Color4B(255, 0, 0, 255), 2);
			back0_text->setFontSize(20);
			back0_text->setVisible(true);
			scheduleOnce(CC_CALLBACK_1(MainGame::lack_of_money, this, back0_text), 1.0f, "lack_of_money1");
			return;
		}
		else if (choose_back0->getTouchEndPosition().x > 480){
			change_x0 = true;
		}
		unschedule("lack_of_money0");
		unschedule("lack_of_money1");
		back0_text->stopAllActions();
		money -= cost;
		if (money < 10){
			money_text->setString(StringUtils::format("00%d", money));
		}
		else if (money < 100){
			money_text->setString(StringUtils::format("0%d", money));
		}
		else {
			money_text->setString(StringUtils::format("%d", money));
		}
		if (change_x0){
			newFriend(480, choose_back0->getTouchEndPosition().y - 20, man->tag);//������λ
		}
		else {
			newFriend(choose_back0->getTouchEndPosition().x - 4, choose_back0->getTouchEndPosition().y - 20, man->tag);//������λ
		}
		SimpleAudioEngine::getInstance()->playEffect(dolo);
		sold_first_cd(buy_cd);
		schedule(schedule_selector(MainGame::sold_first_timer), 0.1f);//����ʱ���
		back0_text->setOpacity(255);
		back0_text->setString(StringUtils::format("%.1f", buy_cd));//��ȴʱ��
		back0_text->enableOutline(Color4B(0, 0, 255, 255), 2);
		back0_text->setFontSize(30);
		back0_text->setVisible(true);
		break;
	default:
		break;
	}
}
void MainGame::sold_first_cd(float duration){//չλ1��ʼ��ȴ
	choose_back0->setEnabled(false);
	CCSprite *s = CCSprite::create("public/mercenary_back.png");
	CCProgressTimer *pt = CCProgressTimer::create(s);
	pt->setType(cocos2d::CCProgressTimerType(kCCProgressTimerTypeBar));
	pt->setAnchorPoint(Vec2(0, 0));
	pt->setMidpoint(ccp(0, 0));
	pt->setBarChangeRate(ccp(0, 1));
	choose_back0->addChild(pt, 0);
	CCProgressTo *t = CCProgressTo::create(duration, 100);
	Sequence *act0 = Sequence::create(t, CCCallFuncN::create(pt, callfuncN_selector(MainGame::removeself)), NULL); //ɾ���Լ�
	CCCallFunc *callFunc = CCCallFunc::create(CC_CALLBACK_0(MainGame::sold_first_recover, this));
	CCActionInterval* act1 = CCSequence::create(act0, callFunc, NULL);//���ж���
	pt->runAction(act1);
}
void MainGame::sold_first_recover(){//չλ1��ȴ���
	choose_back0->setEnabled(true);
	back0_text->setVisible(false);
	unschedule(schedule_selector(MainGame::sold_first_timer));
}
void MainGame::sold_first_timer(float dt){//����ʱ
	String sold_cd_string = back0_text->getString();
	float num = sold_cd_string.floatValue();
	num -= dt;
	back0_text->setString(StringUtils::format("%.1f", num));//ת��Ϊ�ַ��ʹ���
}

void MainGame::touchEvent_buy_1(Ref* pSender, Widget::TouchEventType type, soldier *man){//�������
	int cost = man->cost;
	float buy_cd = man->cd;
	switch (type)
	{
	case Widget::TouchEventType::BEGAN:
		if (money < cost){
			SimpleAudioEngine::getInstance()->playEffect(notenough);
			back1_text->setOpacity(255);
			back1_text->setString(" Not enough!");
			back1_text->enableOutline(Color4B(255, 0, 0, 255), 2);
			back1_text->setFontSize(20);
			back1_text->setVisible(true);
			scheduleOnce(CC_CALLBACK_1(MainGame::lack_of_money, this, back1_text), 1.0f, "lack_of_money2");
			return;
		}
		break;
	case Widget::TouchEventType::MOVED:
		if (money < cost){
			return;
		}
		if (!sprite_back1->isVisible()){
			sprite_back1->setVisible(true);
		}
		sprite_back1->setPosition(Vec2(choose_back1->getTouchMovePosition().x, choose_back1->getTouchMovePosition().y));
		break;
	case Widget::TouchEventType::ENDED:
		sprite_back1->setVisible(false);
		break;
	case Widget::TouchEventType::CANCELED:
		sprite_back1->setVisible(false);
		if (money < cost){
			return;
		}
		change_x1 = false;
		if (choose_back1->getTouchEndPosition().y >= 498 || choose_back1->getTouchEndPosition().y <= 210){//����ص�
			SimpleAudioEngine::getInstance()->playEffect(notenough);
			back1_text->setOpacity(255);
			back1_text->setString(" Wrong place!");
			back1_text->enableOutline(Color4B(255, 0, 0, 255), 2);
			back1_text->setFontSize(20);
			back1_text->setVisible(true);
			scheduleOnce(CC_CALLBACK_1(MainGame::lack_of_money, this, back1_text), 1.0f, "lack_of_money3");
			return;
		}
		else if (choose_back1->getTouchEndPosition().x > 480){
			change_x1 = true;
		}
		unschedule("lack_of_money2");
		unschedule("lack_of_money3");
		back1_text->stopAllActions();
		money -= cost;
		if (money < 10){
			money_text->setString(StringUtils::format("00%d", money));
		}
		else if (money < 100){
			money_text->setString(StringUtils::format("0%d", money));
		}
		else {
			money_text->setString(StringUtils::format("%d", money));
		}
		if (change_x1){
			newFriend(480, choose_back1->getTouchEndPosition().y - 20, man->tag);//������λ
		}
		else {
			newFriend(choose_back1->getTouchEndPosition().x - 4, choose_back1->getTouchEndPosition().y - 20, man->tag);//������λ
		}
		SimpleAudioEngine::getInstance()->playEffect(dolo);
		sold_second_cd(buy_cd);
		schedule(schedule_selector(MainGame::sold_second_timer), 0.1f);//����ʱ���
		back1_text->setOpacity(255);
		back1_text->setString(StringUtils::format("%.1f", buy_cd));//��ȴʱ��
		back1_text->enableOutline(Color4B(0, 0, 255, 255), 2);
		back1_text->setFontSize(30);
		back1_text->setVisible(true);
		break;
	default:
		break;
	}
}
void MainGame::sold_second_cd(float duration){//չλ2��ʼ��ȴ
	choose_back1->setEnabled(false);
	CCSprite *s = CCSprite::create("public/mercenary_back.png");
	CCProgressTimer *pt = CCProgressTimer::create(s);
	pt->setType(cocos2d::CCProgressTimerType(kCCProgressTimerTypeBar));
	pt->setAnchorPoint(Vec2(0, 0));
	pt->setMidpoint(ccp(0, 0));
	pt->setBarChangeRate(ccp(0, 1));
	choose_back1->addChild(pt, 0);
	CCProgressTo *t = CCProgressTo::create(duration, 100);
	Sequence *act0 = Sequence::create(t, CCCallFuncN::create(pt, callfuncN_selector(MainGame::removeself)), NULL); //ɾ���Լ�
	CCCallFunc *callFunc = CCCallFunc::create(CC_CALLBACK_0(MainGame::sold_second_recover, this));
	CCActionInterval* act1 = CCSequence::create(act0, callFunc, NULL);//���ж���
	pt->runAction(act1);
}
void MainGame::sold_second_recover(){//չλ2��ȴ���
	choose_back1->setEnabled(true);
	back1_text->setVisible(false);
	unschedule(schedule_selector(MainGame::sold_second_timer));
}
void MainGame::sold_second_timer(float dt){
	String sold_cd_string = back1_text->getString();
	float num = sold_cd_string.floatValue();
	num -= dt;
	back1_text->setString(StringUtils::format("%.1f", num));//ת��Ϊ�ַ��ʹ���
}
void MainGame::touchEvent_buy_2(Ref* pSender, Widget::TouchEventType type, soldier *man){//�������
	int cost = man->cost;
	float buy_cd = man->cd;
	switch (type)
	{
	case Widget::TouchEventType::BEGAN:
		if (money < cost){
			SimpleAudioEngine::getInstance()->playEffect(notenough);
			back2_text->setOpacity(255);
			back2_text->setString(" Not enough!");
			back2_text->enableOutline(Color4B(255, 0, 0, 255), 2);
			back2_text->setFontSize(20);
			back2_text->setVisible(true);
			scheduleOnce(CC_CALLBACK_1(MainGame::lack_of_money, this, back2_text), 1.0f, "lack_of_money4");
			return;
		}
		break;
	case Widget::TouchEventType::MOVED:
		if (money < cost){
			return;
		}
		if (!sprite_back2->isVisible()){
			sprite_back2->setVisible(true);
		}
		sprite_back2->setPosition(Vec2(choose_back2->getTouchMovePosition().x, choose_back2->getTouchMovePosition().y));
		break;
	case Widget::TouchEventType::ENDED:
		sprite_back2->setVisible(false);
		break;
	case Widget::TouchEventType::CANCELED:
		sprite_back2->setVisible(false);
		if (money < cost){
			return;
		}
		change_x2 = false;
		if (choose_back2->getTouchEndPosition().y >= 498 || choose_back2->getTouchEndPosition().y <= 210){//����ص�
			SimpleAudioEngine::getInstance()->playEffect(notenough);
			back2_text->setOpacity(255);
			back2_text->setString(" Wrong place!");
			back2_text->enableOutline(Color4B(255, 0, 0, 255), 2);
			back2_text->setFontSize(20);
			back2_text->setVisible(true);
			scheduleOnce(CC_CALLBACK_1(MainGame::lack_of_money, this, back2_text), 1.0f, "lack_of_money5");
			return;
		}
		else if (choose_back2->getTouchEndPosition().x > 480){
			change_x2 = true;
		}
		unschedule("lack_of_money4");
		unschedule("lack_of_money5");
		back2_text->stopAllActions();
		money -= cost;
		if (money < 10){
			money_text->setString(StringUtils::format("00%d", money));
		}
		else if (money < 100){
			money_text->setString(StringUtils::format("0%d", money));
		}
		else {
			money_text->setString(StringUtils::format("%d", money));
		}
		if (change_x2){
			newFriend(480, choose_back2->getTouchEndPosition().y - 20, man->tag);//������λ
		}
		else {
			newFriend(choose_back2->getTouchEndPosition().x - 4, choose_back2->getTouchEndPosition().y - 20, man->tag);//������λ
		}
		SimpleAudioEngine::getInstance()->playEffect(dolo);
		sold_third_cd(buy_cd);
		schedule(schedule_selector(MainGame::sold_third_timer), 0.1f);//����ʱ���
		back2_text->setOpacity(255);
		back2_text->setString(StringUtils::format("%.1f", buy_cd));//��ȴʱ��
		back2_text->enableOutline(Color4B(0, 0, 255, 255), 2);
		back2_text->setFontSize(30);
		back2_text->setVisible(true);
		break;
	default:
		break;
	}
}
void MainGame::sold_third_cd(float duration){//չλ3��ʼ��ȴ
	choose_back2->setEnabled(false);
	CCSprite *s = CCSprite::create("public/mercenary_back.png");
	CCProgressTimer *pt = CCProgressTimer::create(s);
	pt->setType(cocos2d::CCProgressTimerType(kCCProgressTimerTypeBar));
	pt->setAnchorPoint(Vec2(0, 0));
	pt->setMidpoint(ccp(0, 0));
	pt->setBarChangeRate(ccp(0, 1));
	choose_back2->addChild(pt, 0);
	CCProgressTo *t = CCProgressTo::create(duration, 100);
	Sequence *act0 = Sequence::create(t, CCCallFuncN::create(pt, callfuncN_selector(MainGame::removeself)), NULL); //ɾ���Լ�
	CCCallFunc *callFunc = CCCallFunc::create(CC_CALLBACK_0(MainGame::sold_third_recover, this));
	CCActionInterval* act1 = CCSequence::create(act0, callFunc, NULL);//���ж���
	pt->runAction(act1);
}
void MainGame::sold_third_recover(){//չλ3��ȴ���
	choose_back2->setEnabled(true);
	back2_text->setVisible(false);
	unschedule(schedule_selector(MainGame::sold_third_timer));
}
void MainGame::sold_third_timer(float dt){
	String sold_cd_string = back2_text->getString();
	float num = sold_cd_string.floatValue();
	num -= dt;
	back2_text->setString(StringUtils::format("%.1f", num));//ת��Ϊ�ַ��ʹ���
}
void MainGame::touchEvent_buy_3(Ref* pSender, Widget::TouchEventType type, soldier *man){//�������
	int cost = man->cost;
	float buy_cd = man->cd;
	switch (type)
	{
	case Widget::TouchEventType::BEGAN:
		if (money < cost){
			SimpleAudioEngine::getInstance()->playEffect(notenough);
			back3_text->setOpacity(255);
			back3_text->setString(" Not enough!");
			back3_text->enableOutline(Color4B(255, 0, 0, 255), 2);
			back3_text->setFontSize(20);
			back3_text->setVisible(true);
			scheduleOnce(CC_CALLBACK_1(MainGame::lack_of_money, this, back3_text), 1.0f, "lack_of_money6");
			return;
		}
		break;
	case Widget::TouchEventType::MOVED:
		if (money < cost){
			return;
		}
		if (!sprite_back3->isVisible()){
			sprite_back3->setVisible(true);
		}
		sprite_back3->setPosition(Vec2(choose_back3->getTouchMovePosition().x, choose_back3->getTouchMovePosition().y));
		break;
	case Widget::TouchEventType::ENDED:
		sprite_back3->setVisible(false);
		break;
	case Widget::TouchEventType::CANCELED:
		sprite_back3->setVisible(false);
		if (money < cost){
			return;
		}
		change_x3 = false;
		if (choose_back3->getTouchEndPosition().y >= 498 || choose_back3->getTouchEndPosition().y <= 210){//����ص�
			SimpleAudioEngine::getInstance()->playEffect(notenough);
			back3_text->setOpacity(255);
			back3_text->setString(" Wrong place!");
			back3_text->enableOutline(Color4B(255, 0, 0, 255), 2);
			back3_text->setFontSize(20);
			back3_text->setVisible(true);
			scheduleOnce(CC_CALLBACK_1(MainGame::lack_of_money, this, back3_text), 1.0f, "lack_of_money7");
			return;
		}
		else if (choose_back3->getTouchEndPosition().x > 480){
			change_x3 = true;
		}
		unschedule("lack_of_money6");
		unschedule("lack_of_money7");
		back3_text->stopAllActions();
		money -= cost;
		if (money < 10){
			money_text->setString(StringUtils::format("00%d", money));
		}
		else if (money < 100){
			money_text->setString(StringUtils::format("0%d", money));
		}
		else {
			money_text->setString(StringUtils::format("%d", money));
		}
		if (change_x3){
			newFriend(480, choose_back3->getTouchEndPosition().y - 20, man->tag);//������λ
		}
		else {
			newFriend(choose_back3->getTouchEndPosition().x - 4, choose_back3->getTouchEndPosition().y - 20, man->tag);//������λ
		}
		SimpleAudioEngine::getInstance()->playEffect(dolo);
		sold_fourth_cd(buy_cd);
		schedule(schedule_selector(MainGame::sold_fourth_timer), 0.1f);//����ʱ���
		back3_text->setOpacity(255);
		back3_text->setString(StringUtils::format("%.1f", buy_cd));//��ȴʱ��
		back3_text->enableOutline(Color4B(0, 0, 255, 255), 2);
		back3_text->setFontSize(30);
		back3_text->setVisible(true);
		break;
	default:
		break;
	}
}
void MainGame::sold_fourth_cd(float duration){//չλ4��ʼ��ȴ
	choose_back3->setEnabled(false);
	CCSprite *s = CCSprite::create("public/mercenary_back.png");
	CCProgressTimer *pt = CCProgressTimer::create(s);
	pt->setType(cocos2d::CCProgressTimerType(kCCProgressTimerTypeBar));
	pt->setAnchorPoint(Vec2(0, 0));
	pt->setMidpoint(ccp(0, 0));
	pt->setBarChangeRate(ccp(0, 1));
	choose_back3->addChild(pt, 0);
	CCProgressTo *t = CCProgressTo::create(duration, 100);
	Sequence *act0 = Sequence::create(t, CCCallFuncN::create(pt, callfuncN_selector(MainGame::removeself)), NULL); //ɾ���Լ�
	CCCallFunc *callFunc = CCCallFunc::create(CC_CALLBACK_0(MainGame::sold_fourth_recover, this));
	CCActionInterval* act1 = CCSequence::create(act0, callFunc, NULL);//���ж���
	pt->runAction(act1);
}
void MainGame::sold_fourth_recover(){//չλ4��ȴ���
	choose_back3->setEnabled(true);
	back3_text->setVisible(false);
	unschedule(schedule_selector(MainGame::sold_fourth_timer));
}
void MainGame::sold_fourth_timer(float dt){
	String sold_cd_string = back3_text->getString();
	float num = sold_cd_string.floatValue();
	num -= dt;
	back3_text->setString(StringUtils::format("%.1f", num));//ת��Ϊ�ַ��ʹ���
}

void MainGame::lack_of_money(float dt,Text *back_text){//ȱ�ٽ�Ǯ��ʾ
	auto fade = FadeOut::create(0.5f);
	CCCallFunc *callFunc = CCCallFunc::create(CC_CALLBACK_0(MainGame::set_visible, this ,back_text));
	auto sequence = Sequence::create(fade, callFunc, NULL);
	back_text->runAction(sequence);
}
void MainGame::set_visible(Text *back_text){//������ʾ
	back_text->setVisible(false);
}
void MainGame::newFriend(float x, float y, int tag){//����һ���ѷ���λ
	if (tag == 5){
		auto sprite = new swordMan(0);
		sprite->setPosition(Vec2(x, y));
		this->addChild(sprite);
		blueSide.pushBack(sprite);
		allSprites.pushBack(sprite);
	}
	else if (tag == 6){
		auto sprite = new pikeMan(0);
		sprite->setPosition(Vec2(x, y));
		this->addChild(sprite);
		blueSide.pushBack(sprite);
		allSprites.pushBack(sprite);
	}
	else if (tag == 7){
		auto sprite = new bowMan(0);
		sprite->setPosition(Vec2(x, y));
		this->addChild(sprite);
		blueSide.pushBack(sprite);
		allSprites.pushBack(sprite);
	}
	else if (tag == 8){
		auto sprite = new cavMan(0);
		sprite->setPosition(Vec2(x, y));
		this->addChild(sprite);
		blueSide.pushBack(sprite);
		allSprites.pushBack(sprite);
	}
	else if (tag == 9){
		auto sprite = new shieldMan(0);
		sprite->setPosition(Vec2(x, y));
		this->addChild(sprite);
		blueSide.pushBack(sprite);
		allSprites.pushBack(sprite);
	}
	else if (tag == 10){
		auto sprite = new shootMan(0);
		sprite->setPosition(Vec2(x, y));
		this->addChild(sprite);
		blueSide.pushBack(sprite);
		allSprites.pushBack(sprite);
	}
	else if (tag == 11){
		auto sprite = new horseMan(0);
		sprite->setPosition(Vec2(x, y));
		this->addChild(sprite);
		blueSide.pushBack(sprite);
		allSprites.pushBack(sprite);
	}
	else if (tag == 12){
		auto sprite = new spearMan(0);
		sprite->setPosition(Vec2(x, y));
		this->addChild(sprite);
		blueSide.pushBack(sprite);
		allSprites.pushBack(sprite);
	}
}
void MainGame::addSprite(AllSprites *enemy){//��Ӻ���
	redSide.pushBack(enemy);
	allSprites.pushBack(enemy);
}