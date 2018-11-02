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
	label->setColor(ccc3(0, 0, 0));   //������ɫ
	// position the label on the center of the screen
	label->setPosition(Vec2(origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height - label->getContentSize().height * 4.8f));

	// add the label as a child to this layer
	this->addChild(label, 1);

	auto label2 = Label::createWithTTF("Since 2017-12-25", "fonts/Marker Felt.ttf", 38);
	label2->setColor(ccc3(0, 0, 0));   //������ɫ
	// position the label on the center of the screen
	label2->setPosition(Vec2(origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height - label2->getContentSize().height * 6.5f));
	this->addChild(label2, 2);

	auto icon = Sprite::create("icon.jpg");//������������
	auto size = Director::getInstance()->getWinSize();//�����Ļ��С
	float scaleX1 =300/size.width;//�������ű���
	float scaleY1 =200/size.height;//�������ű���
	icon->setScaleX(scaleX1);//���ñ�ͼ������
	icon->setScaleY(scaleY1);
	// position the sprite on the center of the screen
	icon->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y-icon->getContentSize().height/7.5f));
	// add the sprite as a child to this layer
	this->addChild(icon, 1);

	// add "HelloWorld" splash screen"
	auto bg = Sprite::create("brick.jpg");//������������
	//auto size = Director::getInstance()->getWinSize();//�����Ļ��С
	float scaleX = size.width / bg->getContentSize().width;//�������ű���
	float scaleY = size.height / bg->getContentSize().height;//�������ű���
	bg->setScaleX(scaleX);//���ñ�������
	bg->setScaleY(scaleY);
	// position the sprite on the center of the screen
	bg->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	// add the sprite as a child to this layer
	this->addChild(bg, 0);

	auto returnItem = MenuItemFont::create("<- Back", CC_CALLBACK_0(About::preturn, this));//��ʼ�˵�
	returnItem->setFontNameObj("Marker Felt.ttf");
	returnItem->setFontSizeObj(38);
	auto menu = Menu::create(returnItem,NULL);//���ݲ˵�����˵�
	menu->setColor(ccc3(0, 0, 0));
	menu->alignItemsVertically();//��ֱ����
	menu->setAnchorPoint(Vec2(0, 0));
	menu->setPosition(Vec2(visibleSize.width - returnItem->getContentSize().width *2.2f, returnItem->getContentSize().height * 5));
	this->addChild(menu);

	return true;

}
void About::preturn(){//�ص���Ϸ������
	Director::getInstance()->popSceneWithTransition<TransitionFade>(0.5f);
	SimpleAudioEngine::getInstance()->playEffect(click);
}

About::About()
{
}


About::~About()
{
}
