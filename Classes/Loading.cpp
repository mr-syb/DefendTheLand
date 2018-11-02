#include "Loading.h"

Loading::Loading(){
}
Scene* Loading::createScene()//创建场景
{
	auto scene = Scene::create();
	auto layer = Loading::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

bool Loading::init(){//初始化
	currentNum = 0;
	totalNum = 9;
	//取得屏幕大小  
	CCSize size = CCDirector::sharedDirector()->getWinSize();
	m_frameCache = CCSpriteFrameCache::sharedSpriteFrameCache();//加载

	imagine = Sprite::create("warning.png");
	imagine->setPosition(Vec2(size.width / 2, size.height / 2));
	this->addChild(imagine);
	imagine->setOpacity(0);
	auto fadein = FadeIn::create(1);
	imagine->runAction(fadein);

	//加载音乐
	SimpleAudioEngine::getInstance()->preloadBackgroundMusic(menu_back);
	SimpleAudioEngine::getInstance()->preloadBackgroundMusic(choose_back);
	SimpleAudioEngine::getInstance()->preloadEffect(click);
	SimpleAudioEngine::getInstance()->preloadEffect(loading_ok);
	SimpleAudioEngine::getInstance()->preloadEffect(ryu_A);
	SimpleAudioEngine::getInstance()->preloadEffect(ryu_J_start);
	SimpleAudioEngine::getInstance()->preloadEffect(ryu_J_end);
	SimpleAudioEngine::getInstance()->preloadEffect(ryu_K);
	SimpleAudioEngine::getInstance()->preloadEffect(victory);
	SimpleAudioEngine::getInstance()->preloadEffect(warning);
	SimpleAudioEngine::getInstance()->preloadEffect(hit);
	SimpleAudioEngine::getInstance()->preloadEffect(ryu_die);
	SimpleAudioEngine::getInstance()->preloadEffect(reborn);
	SimpleAudioEngine::getInstance()->preloadEffect(fight);
	SimpleAudioEngine::getInstance()->preloadEffect(dolo);
	SimpleAudioEngine::getInstance()->preloadEffect(notenough);
	SimpleAudioEngine::getInstance()->preloadEffect(wave_A);
	SimpleAudioEngine::getInstance()->preloadEffect(bowMan_A);
	SimpleAudioEngine::getInstance()->preloadEffect(shootMan_A);
	SimpleAudioEngine::getInstance()->preloadEffect(bow_shoot_die);
	SimpleAudioEngine::getInstance()->preloadEffect(cav_horse_die);
	SimpleAudioEngine::getInstance()->preloadEffect(cavMan_hit);
	SimpleAudioEngine::getInstance()->preloadEffect(Fly0_hit);
	SimpleAudioEngine::getInstance()->preloadEffect(Fly1_hit);
	SimpleAudioEngine::getInstance()->preloadEffect(horseMan_hit);
	SimpleAudioEngine::getInstance()->preloadEffect(pike_spear_die);
	SimpleAudioEngine::getInstance()->preloadEffect(shieldMan_hit);
	SimpleAudioEngine::getInstance()->preloadEffect(spear_pike_hit);
	SimpleAudioEngine::getInstance()->preloadEffect(sword_shield_die);
	SimpleAudioEngine::getInstance()->preloadEffect(swordMan_hit);
	SimpleAudioEngine::getInstance()->preloadEffect(tower_die);
	SimpleAudioEngine::getInstance()->preloadEffect(tower_normal_A);
	SimpleAudioEngine::getInstance()->preloadEffect(tower_normal_hit);
	SimpleAudioEngine::getInstance()->preloadEffect(army_attack);
	SimpleAudioEngine::getInstance()->preloadEffect(defeat);
	SimpleAudioEngine::getInstance()->preloadEffect(select);
	SimpleAudioEngine::getInstance()->preloadEffect(cancel);

	//文字标签，用于显示Loding字样和加载的进度  
	m_pLabelLoading = CCLabelTTF::create("Loading...", "Arial", 20);
	m_pLabelLoading->setAnchorPoint(Vec2(1, 0));
	m_pLabelLoading->setPosition(ccp(size.width-15, 10));
	m_pLabelLoading->setOpacity(0);
	this->addChild(m_pLabelLoading,1);
	auto fadein1 = FadeIn::create(1);
	CCCallFunc* callFunc = CCCallFunc::create(this, callfunc_selector(Loading::loadtextures));
	auto sequence = Sequence::create(fadein1,callFunc,NULL);
	m_pLabelLoading->runAction(sequence);
	
	listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(Loading::onTouchBegan, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
	return true;
}
void Loading::loadtextures(){
	//加载纹理
	CCTextureCache::sharedTextureCache()->addImageAsync("public/ActorsPack1.png", CC_CALLBACK_1(Loading::loadingCallBack, this, "public/ActorsPack1.plist"));
	CCTextureCache::sharedTextureCache()->addImageAsync("hero_ryu/blood.png", CC_CALLBACK_1(Loading::loadingCallBack, this, "hero_ryu/blood.plist"));
	CCTextureCache::sharedTextureCache()->addImageAsync("public/player_select.png", CC_CALLBACK_1(Loading::loadingCallBack, this, "public/player_select.plist"));
	CCTextureCache::sharedTextureCache()->addImageAsync("hero_ryu/J_effect.png", CC_CALLBACK_1(Loading::loadingCallBack, this, "hero_ryu/J_effect.plist"));
	CCTextureCache::sharedTextureCache()->addImageAsync("hero_ryu/shield.png", CC_CALLBACK_1(Loading::loadingCallBack, this, "hero_ryu/shield.plist"));
	CCTextureCache::sharedTextureCache()->addImageAsync("hero_ryu/blowup.png", CC_CALLBACK_1(Loading::loadingCallBack, this, "hero_ryu/blowup.plist"));
	CCTextureCache::sharedTextureCache()->addImageAsync("hero_ryu/stun.png", CC_CALLBACK_1(Loading::loadingCallBack, this, "hero_ryu/stun.plist"));
	CCTextureCache::sharedTextureCache()->addImageAsync("hero_ryu/death.png", CC_CALLBACK_1(Loading::loadingCallBack, this, "hero_ryu/death.plist"));
	CCTextureCache::sharedTextureCache()->addImageAsync("hero_ryu/born.png", CC_CALLBACK_1(Loading::loadingCallBack, this, "hero_ryu/born.plist"));
}
void Loading::loadingCallBack(Texture2D* texture, const char *plist)
{ 
	currentNum++;
	m_frameCache->addSpriteFramesWithFile(plist, texture);
	if (currentNum==totalNum)
	{
		m_pLabelLoading->setString("Touch screen to continue");
		SimpleAudioEngine::getInstance()->playEffect(loading_ok);
	}
}
bool Loading::onTouchBegan(Touch *touch, Event *unused_event){//触摸屏幕
	if (currentNum == totalNum){
		//场景跳转
		auto hello = HelloWorld::createScene();
		Director::getInstance()->replaceScene(TransitionFade::create(1.5f, hello));
		SimpleAudioEngine::getInstance()->playEffect(click);
		return true;
	}
}