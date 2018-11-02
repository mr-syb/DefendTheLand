#include "HelloWorldScene.h"
USING_NS_CC;

Scene* HelloWorld::createScene()//创建场景
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}


bool HelloWorld::init()//初始化方法
{
    if ( !Layer::init())
    {
        return false;
    }
	
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto label = Label::createWithTTF("Defend the land", "fonts/Marker Felt.ttf", 46);
	label->setColor(ccc3(0,0,0));   //设置颜色
    // position the label on the center of the screen
    label->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height*2));

    // add the label as a child to this layer
    this->addChild(label, 1);

    auto bg = Sprite::create("bg.jpg");//创建背景精灵
	auto size = Director::getInstance()->getWinSize();//获得屏幕大小
	float scaleX = size.width / bg->getContentSize().width;//计算缩放比例
	float scaleY = size.height / bg->getContentSize().height;//计算缩放比例
	bg->setScaleX(scaleX);//设置背景缩放
	bg->setScaleY(scaleY);
    bg->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    this->addChild(bg, 0);
    
	auto startItem = MenuItemFont::create("Start", CC_CALLBACK_0(HelloWorld::start, this));//开始菜单
	startItem->setFontNameObj("Marker Felt.ttf");
	startItem->setFontSizeObj(40);
	auto about = MenuItemFont::create("About", CC_CALLBACK_0(HelloWorld::about, this));//关于菜单
	about->setFontNameObj("Marker Felt.ttf");
	about->setFontSizeObj(40);
	auto menu = Menu::create(startItem, about, NULL);//根据菜单项创建菜单
	menu->setColor(ccc3(0, 0, 0));
	menu->alignItemsVertically();//垂直对齐
	menu->alignItemsVerticallyWithPadding(10);
	this->addChild(menu);

	//背景音乐
	SimpleAudioEngine::getInstance()->playBackgroundMusic(menu_back);
	
	return true;
}

void HelloWorld::start(){//选择英雄
	auto select = ChooseHeroScene::createScene();
	Director::getInstance()->pushScene(TransitionFade::create(0.5f,select));
	//SimpleAudioEngine::getInstance()->stopBackgroundMusic();
	SimpleAudioEngine::getInstance()->playEffect(click);
}

void HelloWorld::about(){//游戏设置界面
	auto sc =About::createScene();
	Director::getInstance()->pushScene(TransitionFade::create(0.5f,sc));
	SimpleAudioEngine::getInstance()->playEffect(click);
}