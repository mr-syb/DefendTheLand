#include "ChooseHeroScene.h"

Scene* ChooseHeroScene::createScene(){
	auto scene = Scene::create();
	auto layer = ChooseHeroScene::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

bool ChooseHeroScene::init(){
	if (!Layer::init()){
		return false;
	}
	m_frameCache = CCSpriteFrameCache::sharedSpriteFrameCache();//加载

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto label = Label::createWithTTF("Hero Select", "fonts/Marker Felt.ttf", 42);
	label->setColor(ccc3(0, 0, 0));   //设置颜色
	label->setPosition(Vec2(origin.x + visibleSize.width / 2,origin.y + visibleSize.height-label->getContentSize().height*3.5));//位置
	auto blink = Blink::create(200.0f, 180);//闪烁效果
	label->runAction(blink);
	this->addChild(label, 1);

	auto bg = Sprite::create("choosehero.jpg");//创建背景精灵
	auto size = Director::getInstance()->getWinSize();//获得屏幕大小
	float scaleX = size.width / bg->getContentSize().width;//计算缩放比例
	float scaleY = size.height / bg->getContentSize().height;//计算缩放比例
	bg->setScaleX(scaleX);//设置背景缩放
	bg->setScaleY(scaleY);
	// position the sprite on the center of the screen
	bg->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	// add the sprite as a child to this layer
	this->addChild(bg, 0);
	
	auto start = MenuItemFont::create(" -> Fight", CC_CALLBACK_0(ChooseHeroScene::start, this));//确认菜单
	start->setFontNameObj("Marker Felt.ttf");
	start->setFontSizeObj(30);
	auto back = MenuItemFont::create("<- Back", CC_CALLBACK_0(ChooseHeroScene::back, this));//返回菜单
	back->setFontNameObj("Marker Felt.ttf");
	back->setFontSizeObj(30);
	auto menu = Menu::create(start,back, NULL);//根据菜单项创建菜单
	menu->setColor(ccc3(0, 0, 0));
	menu->setAnchorPoint(Vec2(0, 0));
	menu->setPosition(Vec2(visibleSize.width-start->getContentSize().width/1.5f,start->getContentSize().height*3));
	menu->alignItemsVertically();//垂直对齐
	menu->alignItemsVerticallyWithPadding(20);
	this->addChild(menu);

	auto select_back = Sprite::create("select_back.png");
	select_back->setAnchorPoint(Vec2(1, 1));
	select_back->setPosition(Vec2(visibleSize.width,577));
	select_back->setScale(0.6);
	this->addChild(select_back);
	auto select_back_hero = Sprite::create("select_back.png");
	select_back_hero->setAnchorPoint(Vec2(0, 1));
	select_back_hero->setPosition(Vec2(0, 577));
	select_back_hero->setScale(0.6);
	this->addChild(select_back_hero);

	//英雄列表
	auto hero_label = Label::createWithTTF("<~Hero", "fonts/arial.ttf", 30);
	hero_label->setColor(ccc3(0, 0, 0));   //设置颜色
	hero_label->setPosition(Vec2(origin.x + visibleSize.width / 4.1, origin.y + visibleSize.height/1.18));//位置
	this->addChild(hero_label, 1);
	//hero0
	auto hero0 = CheckBox::create("public/player_0.png", "public/player_0.png");
	hero0->setAnchorPoint(Vec2(0.5, 0.5));
	hero0->setTag(0);
	hero0->setPosition(Vec2(hero0->getContentSize().width * 1, visibleSize.height - hero0->getContentSize().height * 2));
	this->addChild(hero0);
	box.pushBack(hero0);
	//hero1
	auto hero1 = CheckBox::create("public/player_1.png", "public/player_1.png");
	hero1->setAnchorPoint(Vec2(0.5, 0.5));
	hero1->setTag(1);
	hero1->setPosition(Vec2(hero1->getContentSize().width * 3.2, visibleSize.height - hero1->getContentSize().height * 2));
	this->addChild(hero1);
	//box.pushBack(hero1);
	//随从列表
	auto mercenary_label = Label::createWithTTF("Army~>", "fonts/arial.ttf", 30);
	mercenary_label->setColor(ccc3(0, 0, 0));   //设置颜色
	mercenary_label->setPosition(Vec2(origin.x + visibleSize.width / 1.33, origin.y + visibleSize.height / 1.18));//位置
	this->addChild(mercenary_label, 1);
	//swordMan5
	auto mercenary5 = CheckBox::create("public/player_5.png","public/player_5.png");
	mercenary5->setAnchorPoint(Vec2(0.5, 0.5));
	mercenary5->setTag(5);
	mercenary5->setPosition(Vec2(visibleSize.width - mercenary5->getContentSize().width * 3.8, visibleSize.height - mercenary5->getContentSize().height*2.5));
	this->addChild(mercenary5);
	box.pushBack(mercenary5);
	//pikeMan6
	auto mercenary6 = CheckBox::create("public/player_6.png", "public/player_6.png");
	mercenary6->setAnchorPoint(Vec2(0.5, 0.5));
	mercenary6->setTag(6);
	mercenary6->setPosition(Vec2(visibleSize.width - mercenary6->getContentSize().width * 1.3, visibleSize.height - mercenary6->getContentSize().height * 2.1));
	this->addChild(mercenary6);
	box.pushBack(mercenary6);
	//bowMan7
	auto mercenary7 = CheckBox::create("public/player_7.png", "public/player_7.png");
	mercenary7->setAnchorPoint(Vec2(0.5, 0.5));
	mercenary7->setTag(7);
	mercenary7->setPosition(Vec2(visibleSize.width - mercenary7->getContentSize().width * 3.4, visibleSize.height - mercenary7->getContentSize().height * 3.7));
	this->addChild(mercenary7);
	box.pushBack(mercenary7);
	//canMan8
	auto mercenary8 = CheckBox::create("public/player_8.png", "public/player_8.png");
	mercenary8->setAnchorPoint(Vec2(0.5, 0.5));
	mercenary8->setTag(8);
	mercenary8->setPosition(Vec2(visibleSize.width - mercenary8->getContentSize().width * 0.9, visibleSize.height - mercenary8->getContentSize().height * 3.5));
	this->addChild(mercenary8);
	box.pushBack(mercenary8);
	//shieldMan9
	auto mercenary9 = CheckBox::create("public/player_9.png", "public/player_9.png");
	mercenary9->setAnchorPoint(Vec2(0.5, 0.5));
	mercenary9->setTag(9);
	mercenary9->setPosition(Vec2(visibleSize.width - mercenary9->getContentSize().width * 3, visibleSize.height - mercenary9->getContentSize().height * 5.8));
	this->addChild(mercenary9);
	box.pushBack(mercenary9);
	//shootMan10
	auto mercenary10 = CheckBox::create("public/player_10.png", "public/player_10.png");
	mercenary10->setAnchorPoint(Vec2(0.5, 0.5));
	mercenary10->setTag(10);
	mercenary10->setPosition(Vec2(visibleSize.width - mercenary10->getContentSize().width * 1.3, visibleSize.height - mercenary10->getContentSize().height * 5.5));
	this->addChild(mercenary10);
	box.pushBack(mercenary10);
	//horseMan11
	auto mercenary11 = CheckBox::create("public/player_11.png", "public/player_11.png");
	mercenary11->setAnchorPoint(Vec2(0.5, 0.5));
	mercenary11->setTag(11);
	mercenary11->setPosition(Vec2(visibleSize.width - mercenary11->getContentSize().width * 0.9, visibleSize.height - mercenary11->getContentSize().height * 6.3));
	this->addChild(mercenary11);
	box.pushBack(mercenary11);
	//spearMan12
	auto mercenary12 = CheckBox::create("public/player_12.png", "public/player_12.png");
	mercenary12->setAnchorPoint(Vec2(0.5, 0.5));
	mercenary12->setTag(12);
	mercenary12->setPosition(Vec2(visibleSize.width - mercenary12->getContentSize().width * 3.1, visibleSize.height - mercenary12->getContentSize().height * 6.3));
	this->addChild(mercenary12);
	box.pushBack(mercenary12);

	//标题
	title->setFontName("fonts/arial.ttf");
	title->setString("You should choose only One hero and four mercenaries!");
	title->setFontSize(26);
	title->setAnchorPoint(Vec2(0.5, 0.5));
	title->setPosition(Vec2(visibleSize.width / 2, visibleSize.height/7));
	title->enableOutline(Color4B(255, 0, 0, 255), 3);
	title->setVisible(false);
	title->setScale(0);
	title->setOpacity(0);
	this->addChild(title, 100);

	//背景音乐
	SimpleAudioEngine::getInstance()->playBackgroundMusic(choose_back,true);

	this->scheduleUpdate();//默认调用唯一update()
	
	return true;
}
void ChooseHeroScene::display(){//显示到选择池
	for (int i = 0; i < box.size(); i++){//移除选择池所有对象
		if (getChildByTag(box.at(i)->getTag() + 200)){
			removeChildByTag(box.at(i)->getTag() + 200);
		}
	}
	Size visibleSize = Director::getInstance()->getVisibleSize();
	int j = 0;//四个随从
	int k = 0;
	for (int i = 0; i < choosed_objects.size(); i++){
		if (choosed_objects.at(i)->getTag() < 5&&k<1){
			int tag_num = choosed_objects.at(i)->getTag();
			char txt[50];
			sprintf_s(txt, "%s%d.png", "player_", tag_num);
			auto hero_select = Sprite::createWithSpriteFrameName(txt);
			hero_select->setTag(tag_num+200);
			hero_select->setAnchorPoint(Vec2(0.5,0.5));
			hero_select->setPosition(Vec2(visibleSize.width/2,visibleSize.height/2));
			this->addChild(hero_select,1);
			k++;
		}
		else if (choosed_objects.at(i)->getTag() < 5 ){
			choosed_objects.at(i)->setSelectedState(false);
			SimpleAudioEngine::getInstance()->stopEffect(SimpleAudioEngine::getInstance()->playEffect(select));
			if (!isAction){
				isAction = true;
				//提醒标题
				title->setVisible(true); 
				auto scale = ScaleTo::create(0.2, 1);
				auto fade = FadeIn::create(0.5);
				auto scale0 = ScaleTo::create(2, 1);
				auto scale1 = ScaleTo::create(0.2, 0);
				auto fade1 = FadeOut::create(0.5);
				auto spawn = Spawn::create(scale, fade, NULL);
				auto spawn1 = Spawn::create(scale1, fade1, NULL);
				CCCallFunc* callFunc = CCCallFunc::create(this, callfunc_selector(ChooseHeroScene::setAction));
				auto sequence = Sequence::create(spawn, scale0, spawn1, callFunc, NULL);
				title->runAction(sequence);
				SimpleAudioEngine::getInstance()->playEffect(warning);
			}
		}
		if (choosed_objects.at(i)->getTag() >= 5 && choosed_objects.at(i)->getTag() < 15&&j<4){
			int tag_num = choosed_objects.at(i)->getTag();
			char txt[50];
			sprintf_s(txt, "%s%d.png", "player_", tag_num);
			auto army_select = Sprite::createWithSpriteFrameName(txt);
			army_select->setTag(tag_num + 200);
			army_select->setAnchorPoint(Vec2(0.5, 0.5));
			army_select->setPosition(Vec2(visibleSize.width / 2.35 + j * 50, visibleSize.height / 2.8));
			this->addChild(army_select, 1);
			j++;
		}
		else if (choosed_objects.at(i)->getTag() >= 5 && choosed_objects.at(i)->getTag() < 15){
			choosed_objects.at(i)->setSelectedState(false);
			SimpleAudioEngine::getInstance()->stopEffect(SimpleAudioEngine::getInstance()->playEffect(select));
			if (!isAction){
				isAction = true;
				//提醒标题
				title->setVisible(true);
				auto scale = ScaleTo::create(0.2, 1);
				auto fade = FadeIn::create(0.5);
				auto scale0 = ScaleTo::create(2, 1);
				auto scale1 = ScaleTo::create(0.2, 0);
				auto fade1 = FadeOut::create(0.5);
				auto spawn = Spawn::create(scale, fade, NULL);
				auto spawn1 = Spawn::create(scale1, fade1, NULL);
				CCCallFunc* callFunc = CCCallFunc::create(this, callfunc_selector(ChooseHeroScene::setAction));
				auto sequence = Sequence::create(spawn, scale0, spawn1, callFunc, NULL);
				title->runAction(sequence);
				SimpleAudioEngine::getInstance()->playEffect(warning);
			}
		}
	}
}
void ChooseHeroScene::setAction(){//设置isAction
	isAction = false;
}
void ChooseHeroScene::update(float dt){//循环
	//int num = 0;
	for (int i = 0; i < box.size(); i++){
		bool flag = false;
		if (box.at(i)->getSelectedState()){
			//num++;
			for (int j = 0; j < choosed_objects.size(); j++){
				if (choosed_objects.at(j)->getTag() == box.at(i)->getTag()){
					flag = true;
				}
			}
			if (!flag){
				choosed_objects.pushBack(box.at(i));
				SimpleAudioEngine::getInstance()->playEffect(select);
			}
		}
		else{
			choosed_objects.eraseObject(box.at(i));
		}
	}
	/*
	if (num > cancelmusic){
		cancelmusic = num;
	}
	else if (num < cancelmusic){
		cancelmusic = num;
		SimpleAudioEngine::getInstance()->playEffect(cancel);
	}
	*/
	display();//显示选择池
}

void ChooseHeroScene::start(){//进入游戏
	if (choosed_objects.size() < 5){
		//提醒标题
		title->setVisible(true);
		auto scale = ScaleTo::create(0.2, 1);
		auto fade = FadeIn::create(0.5);
		auto scale0 = ScaleTo::create(2, 1);
		auto scale1 = ScaleTo::create(0.2, 0);
		auto fade1 = FadeOut::create(0.5);
		auto spawn = Spawn::create(scale, fade, NULL);
		auto spawn1 = Spawn::create(scale1, fade1, NULL);
		CCCallFunc* callFunc = CCCallFunc::create(this, callfunc_selector(ChooseHeroScene::setAction));
		auto sequence = Sequence::create(spawn, scale0, spawn1, callFunc, NULL);
		title->runAction(sequence);
		SimpleAudioEngine::getInstance()->playEffect(warning);
	}
	else{
		auto mainGame = MainGame::createScene(choosed_objects);
		Director::getInstance()->pushScene(TransitionFadeBL::create(0.5f, mainGame));
		SimpleAudioEngine::getInstance()->playEffect(click);
		SimpleAudioEngine::getInstance()->stopBackgroundMusic();
	}
}
void ChooseHeroScene::back(){//返回
	Director::getInstance()->popSceneWithTransition<TransitionFade>(0.5f);
	SimpleAudioEngine::getInstance()->playBackgroundMusic(menu_back);
	SimpleAudioEngine::getInstance()->playEffect(click);
}

ChooseHeroScene::ChooseHeroScene()
{
}


ChooseHeroScene::~ChooseHeroScene()
{
}
