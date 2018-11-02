#include "HelloWorldScene.h"
USING_NS_CC;

Scene* HelloWorld::createScene()//��������
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


bool HelloWorld::init()//��ʼ������
{
    if ( !Layer::init())
    {
        return false;
    }
	
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto label = Label::createWithTTF("Defend the land", "fonts/Marker Felt.ttf", 46);
	label->setColor(ccc3(0,0,0));   //������ɫ
    // position the label on the center of the screen
    label->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height*2));

    // add the label as a child to this layer
    this->addChild(label, 1);

    auto bg = Sprite::create("bg.jpg");//������������
	auto size = Director::getInstance()->getWinSize();//�����Ļ��С
	float scaleX = size.width / bg->getContentSize().width;//�������ű���
	float scaleY = size.height / bg->getContentSize().height;//�������ű���
	bg->setScaleX(scaleX);//���ñ�������
	bg->setScaleY(scaleY);
    bg->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    this->addChild(bg, 0);
    
	auto startItem = MenuItemFont::create("Start", CC_CALLBACK_0(HelloWorld::start, this));//��ʼ�˵�
	startItem->setFontNameObj("Marker Felt.ttf");
	startItem->setFontSizeObj(40);
	auto about = MenuItemFont::create("About", CC_CALLBACK_0(HelloWorld::about, this));//���ڲ˵�
	about->setFontNameObj("Marker Felt.ttf");
	about->setFontSizeObj(40);
	auto menu = Menu::create(startItem, about, NULL);//���ݲ˵�����˵�
	menu->setColor(ccc3(0, 0, 0));
	menu->alignItemsVertically();//��ֱ����
	menu->alignItemsVerticallyWithPadding(10);
	this->addChild(menu);

	//��������
	SimpleAudioEngine::getInstance()->playBackgroundMusic(menu_back);
	
	return true;
}

void HelloWorld::start(){//ѡ��Ӣ��
	auto select = ChooseHeroScene::createScene();
	Director::getInstance()->pushScene(TransitionFade::create(0.5f,select));
	//SimpleAudioEngine::getInstance()->stopBackgroundMusic();
	SimpleAudioEngine::getInstance()->playEffect(click);
}

void HelloWorld::about(){//��Ϸ���ý���
	auto sc =About::createScene();
	Director::getInstance()->pushScene(TransitionFade::create(0.5f,sc));
	SimpleAudioEngine::getInstance()->playEffect(click);
}