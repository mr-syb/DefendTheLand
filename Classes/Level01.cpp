#include "Level01.h"
Level01::Level01(){
	visibleSize = Director::getInstance()->getVisibleSize();//获取窗口大小
}
Level01::~Level01(){

}
/*
swordMan  5
pikeMan   6
bowMan    7
cavMan    8
shieldMan 9
shootMan  10
horseMan  11
spearMan  12
*/
void Level01::commander(){//总调度
	timer++;
	if (timer == 5){
		addEnemy(Vec2(930, visibleSize.height / 2 - 5), 5);
	}
	if (timer == 10){
		addEnemy(Vec2(930, visibleSize.height / 2 + 30), 5);
		addEnemy(Vec2(930, visibleSize.height / 2 + 20), 6);
	}
	if (timer == 20){
		triOrder(-20);
	}
	if (timer == 30){
		addEnemy(Vec2(930, visibleSize.height / 2 + 50), 5);
		addEnemy(Vec2(930, visibleSize.height / 2 - 50), 9);
	}
	if (timer == 45){
		addEnemy(Vec2(930, visibleSize.height / 2 - 5), 10);
		addEnemy(Vec2(930, visibleSize.height / 2 - 20), 12);
	}
	if (timer == 65){
		SimpleAudioEngine::getInstance()->playEffect(army_attack);
		triOrder(30);
		addEnemy(Vec2(930, visibleSize.height / 2 + 10), 11);
		addEnemy(Vec2(930, visibleSize.height / 2 + 40), 8);
	}
	if (timer == 80){
		addEnemy(Vec2(930, visibleSize.height / 2 - 20), 7);
		addEnemy(Vec2(930, visibleSize.height / 2 - 30), 10);
	}
	if (timer == 90){
		addEnemy(Vec2(930, visibleSize.height / 2 + 5), 5);
		addEnemy(Vec2(930, visibleSize.height / 2 + 25), 5);
	}
	if (timer == 100){
		addEnemy(Vec2(930, visibleSize.height / 2 + 15), 9);
		addEnemy(Vec2(930, visibleSize.height / 2 + 25), 9);
	}
	if (timer == 110){
		addEnemy(Vec2(930, visibleSize.height / 2 + 15), 12);
		addEnemy(Vec2(930, visibleSize.height / 2 + 5), 6);
	}
	if (timer == 130){
		SimpleAudioEngine::getInstance()->playEffect(army_attack);
		addEnemy(Vec2(930, visibleSize.height / 2 - 30), 10);
		quaOrder(-40);
	}
	if (timer == 140){
		addEnemy(Vec2(930, visibleSize.height / 2 + 30), 5);
		addEnemy(Vec2(930, visibleSize.height / 2 + 20), 6);
	}
	if (timer == 150){
		triOrder(20);
		addEnemy(Vec2(930, visibleSize.height / 2 - 5), 10);
		addEnemy(Vec2(930, visibleSize.height / 2 - 20), 12);
	}
	if (timer == 160){
		addEnemy(Vec2(930, visibleSize.height / 2 + 50), 5);
		addEnemy(Vec2(930, visibleSize.height / 2 - 50), 8);
	}
	if (timer == 180){
		SimpleAudioEngine::getInstance()->playEffect(army_attack);
		addEnemy(Vec2(930, visibleSize.height / 2 - 70), 6);
		triOrder(70);
		addEnemy(Vec2(930, visibleSize.height / 2 - 5), 10);
		addEnemy(Vec2(930, visibleSize.height / 2 - 30), 11);
	}
	if (timer == 190){
		addEnemy(Vec2(930, visibleSize.height / 2 - 60), 11);
		addEnemy(Vec2(930, visibleSize.height / 2 - 80), 11);
		addEnemy(Vec2(930, visibleSize.height / 2 + 80), 8);
		addEnemy(Vec2(930, visibleSize.height / 2 + 60), 8);
	}
	if (timer == 205){
		triOrder(-5);
		addEnemy(Vec2(930, visibleSize.height / 2 + 30), 7);
		addEnemy(Vec2(930, visibleSize.height / 2 - 30), 10);
	}
	if (timer == 215){
		addEnemy(Vec2(930, visibleSize.height / 2 + 50), 5);
		addEnemy(Vec2(930, visibleSize.height / 2 - 50), 9);
	}
	if (timer == 235){
		SimpleAudioEngine::getInstance()->playEffect(army_attack);
		addEnemy(Vec2(930, visibleSize.height / 2 + 50), 5);
		addEnemy(Vec2(930, visibleSize.height / 2 + 60), 6);
		addEnemy(Vec2(930, visibleSize.height / 2 + 70), 7);
		addEnemy(Vec2(930, visibleSize.height / 2 + 80), 8);
		addEnemy(Vec2(930, visibleSize.height / 2 - 50), 9);
		addEnemy(Vec2(930, visibleSize.height / 2 - 60), 10);
		addEnemy(Vec2(930, visibleSize.height / 2 - 70), 11);
		addEnemy(Vec2(930, visibleSize.height / 2 - 80), 12);
	}
	if (timer == 255){
		addEnemy(Vec2(930, visibleSize.height / 2 + 50), 9);
		addEnemy(Vec2(930, visibleSize.height / 2 + 60), 10);
		addEnemy(Vec2(930, visibleSize.height / 2 + 70), 11);
		addEnemy(Vec2(930, visibleSize.height / 2 + 80), 12);
	}
	if (timer == 270){
		addEnemy(Vec2(930, visibleSize.height / 2 - 50), 11);
		addEnemy(Vec2(930, visibleSize.height / 2 - 60), 11);
		addEnemy(Vec2(930, visibleSize.height / 2 - 70), 8);
		addEnemy(Vec2(930, visibleSize.height / 2 - 80), 8);
	}
	if (timer >= 290){
		terminator++;
		if (terminator >= 17){
			terminator = 0;
			SimpleAudioEngine::getInstance()->playEffect(army_attack);
			addEnemy(Vec2(930, visibleSize.height / 2 + 50), 5);
			addEnemy(Vec2(930, visibleSize.height / 2 + 60), 6);
			addEnemy(Vec2(930, visibleSize.height / 2 + 70), 7);
			addEnemy(Vec2(930, visibleSize.height / 2 + 80), 8);
			addEnemy(Vec2(930, visibleSize.height / 2 - 50), 9);
			addEnemy(Vec2(930, visibleSize.height / 2 - 60), 10);
			addEnemy(Vec2(930, visibleSize.height / 2 - 70), 11);
			addEnemy(Vec2(930, visibleSize.height / 2 - 80), 12);
		}
	}
	/*
	swordMan  5
	pikeMan   6
	bowMan    7
	cavMan    8
	shieldMan 9
	shootMan  10
	horseMan  11
	spearMan  12
	*/
}
void Level01::triOrder(int y){//两近战，一射手
	addEnemy(Vec2(930, visibleSize.height / 2 + y + 5), 5);
	addEnemy(Vec2(930, visibleSize.height / 2 + y - 5), 6);
	addEnemy(Vec2(940, visibleSize.height / 2 + y), 7);
}
void Level01::quaOrder(int y){//方阵队形
	addEnemy(Vec2(900, visibleSize.height / 2 + y), 9);
	addEnemy(Vec2(900, visibleSize.height / 2 + y - 20), 9);
	addEnemy(Vec2(940, visibleSize.height / 2 + y), 6);
	addEnemy(Vec2(940, visibleSize.height / 2 + y - 20), 12);
}
void Level01::addEnemy(Vec2 position, int tag){//添加随从
	auto layer = Director::getInstance()->getRunningScene()->getChildByTag(999);
	if (tag == 5){
		auto enemy = new swordMan(1);
		enemy->setPosition(position);
		layer->addChild(enemy);
		MainGame::addSprite(enemy);
	}
	else if (tag == 6){
		auto enemy = new pikeMan(1);
		enemy->setPosition(position);
		layer->addChild(enemy);
		MainGame::addSprite(enemy);
	}
	else if (tag == 7){
		auto enemy = new bowMan(1);
		enemy->setPosition(position);
		layer->addChild(enemy);
		MainGame::addSprite(enemy);
	}
	else if (tag == 8){
		auto enemy = new cavMan(1);
		enemy->setPosition(position);
		layer->addChild(enemy);
		MainGame::addSprite(enemy);
	}
	else if (tag == 9){
		auto enemy = new shieldMan(1);
		enemy->setPosition(position);
		layer->addChild(enemy);
		MainGame::addSprite(enemy);
	}
	else if (tag == 10){
		auto enemy = new shootMan(1);
		enemy->setPosition(position);
		layer->addChild(enemy);
		MainGame::addSprite(enemy);
	}
	else if (tag == 11){
		auto enemy = new horseMan(1);
		enemy->setPosition(position);
		layer->addChild(enemy);
		MainGame::addSprite(enemy);
	}
	else if (tag == 12){
		auto enemy = new spearMan(1);
		enemy->setPosition(position);
		layer->addChild(enemy);
		MainGame::addSprite(enemy);
	}
}