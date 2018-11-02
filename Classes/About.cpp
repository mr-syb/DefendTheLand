#include "About.h"
USING_NS_CC;

Scene* About::createScene(){
	auto scene = Scene::create();
	auto layer = About::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

bool About::init(){
	if (!Layer::init()){
		return false;
	}
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto label = Label::createWithTTF("Jiaqi Liu @ Gench", "fonts/Marker Felt.ttf", 38);
	label->setColor(ccc3(0, 0, 0));   //设置颜色
	// position the label on the center of the screen
	label->setPosition(Vec2(origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height - label->getContentSize().height * 4.8f));

	// add the label as a child to this layer
	this->addChild(label, 1);

	auto label2 = Label::createWithTTF("Since 2017-12-25", "fonts/Marker Felt.ttf", 38);
	label2->setColor(ccc3(0, 0, 0));   //设置颜色
	// position the label on the center of the screen
	label2->setPosition(Vec2(origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height - label2->getContentSize().height * 6.5f));
	this->addChild(label2, 2);

	auto icon = Sprite::create("icon.jpg");//创建背景精灵
	auto size = Director::getInstance()->getWinSize();//获得屏幕大小
	float scaleX1 =300/size.width;//计算缩放比例
	float scaleY1 =200/size.height;//计算缩放比例
	icon->setScaleX(scaleX1);//设置背图像缩放
	icon->setScaleY(scaleY1);
	// position the sprite on the center of the screen
	icon->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y-icon->getContentSize().height/7.5f));
	// add the sprite as a child to this layer
	this->addChild(icon, 1);

	// add "HelloWorld" splash screen"
	auto bg = Sprite::create("brick.jpg");//创建背景精灵
	//auto size = Director::getInstance()->getWinSize();//获得屏幕大小
	float scaleX = size.width / bg->getContentSize().width;//计算缩放比例
	float scaleY = size.height / bg->getContentSize().height;//计算缩放比例
	bg->setScaleX(scaleX);//设置背景缩放
	bg->setScaleY(scaleY);
	// position the sprite on the center of the screen
	bg->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	// add the sprite as a child to this layer
	this->addChild(bg, 0);

	auto returnItem = MenuItemFont::create("<- Back", CC_CALLBACK_0(About::preturn, this));//开始菜单
	returnItem->setFontNameObj("Marker Felt.ttf");
	returnItem->setFontSizeObj(38);
	auto menu = Menu::create(returnItem,NULL);//根据菜单项创建菜单
	menu->setColor(ccc3(0, 0, 0));
	menu->alignItemsVertically();//垂直对齐
	menu->setAnchorPoint(Vec2(0, 0));
	menu->setPosition(Vec2(visibleSize.width - returnItem->getContentSize().width *2.2f, returnItem->getContentSize().height * 5));
	this->addChild(menu);

	return true;

}
void About::preturn(){//回到游戏主界面
	Director::getInstance()->popSceneWithTransition<TransitionFade>(0.5f);
	SimpleAudioEngine::getInstance()->playEffect(click);
}

About::About()
{
}


About::~About()
{
}
