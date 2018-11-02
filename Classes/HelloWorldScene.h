#define __HELLOWORLD_SCENE_H__
#pragma once
#include "cocos2d.h"
#include "About.h"
#include "ChooseHeroScene.h"
#include "AllScene.h"

class HelloWorld : AllScene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
	//∆Ù∂Ø
	void start();
	//…Ë÷√
	void about();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
};

