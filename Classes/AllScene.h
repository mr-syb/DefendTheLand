#pragma once
#include "cocos2d.h"
#include "AllSprites.h"
#include "ui\UICheckBox.h"
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;
USING_NS_CC;
using namespace ui;
class AllScene : public Layer{
public:
	AllScene();
	~AllScene();
	const char *menu_back = "sound/menu_back.mp3";
	const char *choose_back = "sound/choose_back.mp3";
	const char *click = "sound/click.mp3";
	const char *loading_ok = "sound/loading.mp3";
	const char *ryu_A = "sound/ryu_A.mp3";
	const char *ryu_J_start = "sound/ryu_J_start.mp3";
	const char *ryu_J_end = "sound/ryu_J_end.mp3";
	const char *ryu_K = "sound/ryu_K.mp3";
	const char *victory = "sound/victory.mp3";
	const char *warning = "sound/warning.mp3";
	const char *hit = "sound/hit.mp3";
	const char *ryu_die = "sound/ryu_die.mp3";
	const char *reborn = "sound/reborn.mp3";
	const char *fight = "sound/fight.mp3";
	const char *dolo = "sound/dolo.mp3";
	const char *notenough = "sound/notenough.mp3";
	const char *wave_A = "sound/wave_A.mp3";
	const char *bowMan_A = "sound/bowMan_A.mp3";
	const char *shootMan_A = "sound/shootMan_A.mp3";
	const char *bow_shoot_die = "sound/bow_shoot_die.mp3";
	const char *cav_horse_die = "sound/cav_horse_die.mp3";
	const char *cavMan_hit = "sound/cavMan_hit.mp3";
	const char *Fly0_hit = "sound/Fly0_hit.mp3";
	const char *Fly1_hit = "sound/Fly1_hit.mp3";
	const char *horseMan_hit = "sound/horseMan_hit.mp3";
	const char *pike_spear_die = "sound/pike_spear_die.mp3";
	const char *shieldMan_hit = "sound/shieldMan_hit.mp3";
	const char *spear_pike_hit = "sound/spear_pike_hit.mp3";
	const char *sword_shield_die = "sound/sword_shield_die.mp3";
	const char *swordMan_hit = "sound/swordMan_hit.mp3";
	const char *tower_die = "sound/tower_die.mp3";
	const char *tower_normal_A = "sound/tower_normal_A.mp3";
	const char *tower_normal_hit = "sound/tower_normal_hit.mp3";
	const char *army_attack = "sound/army_attack.mp3";
	const char *defeat = "sound/defeat.mp3";
	const char *select = "sound/select.mp3";
	const char *cancel = "sound/cancel.mp3";

	//偷懒 应当设在随从类里
	//随从价钱
	int sword = 15;
	int pike = 16;
	int bow = 18;
	int cav = 20;
	int shield = 22;
	int shoot = 18;
	int horse = 21;
	int spear = 18;

	//随从cd
	float sword_cd = 8;
	float pike_cd = 8;
	float bow_cd = 10;
	float cav_cd = 15;
	float shield_cd = 15;
	float shoot_cd = 10;
	float horse_cd = 15;
	float spear_cd = 10;
	
	Vector<CheckBox *> choosed_objects;//选中的对象
};