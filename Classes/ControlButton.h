#pragma once
#include "cocos2d.h"
USING_NS_CC;
typedef enum{
	touch_begin,
	touch_down,
	touch_up,
}tagForTouch;
class ControlButton :public CCNode{
public:
	ControlButton();
	~ControlButton();
	CREATE_FUNC(ControlButton);
	//创建按钮,其中name_png为按钮的背景图片，button_title为按钮图片上要显示的文字，num为文字的透明度0-100，0为透明  
	void CreateButton(const char* name_png, const char* button_title = "0", unsigned int num = 0);
	void BindButtonEven();//绑写按钮事件 
	/* 当鼠标处于按下并曾经点中按钮时，则触发一次 */
	void touchDownAction(CCObject* pSender, CCControlEvent event);
	/* 当鼠标处于按下并曾经点中按钮的状态下，鼠标进入按钮范围，则触发一次 */
	void touchDragEnter(CCObject* pSender, CCControlEvent event);
	/* 当鼠标处于按下并曾经点中按钮的状态下，鼠标离开按钮范围，则触发一次 */
	void touchDragExit(CCObject* pSender, CCControlEvent event);
	/* 当鼠标处于按下并曾经点中按钮的状态下，鼠标进入按钮范围，则触发，只要达到条件，就不断触发 */
	void touchDragInside(CCObject* pSender, CCControlEvent event);
	/* 当鼠标处于按下并曾经点中按钮的状态下，鼠标离开按钮范围，则触发，只要达到条件，就不断触发 */
	void touchDragOutside(CCObject* pSender, CCControlEvent event);
	/* 当鼠标处于按下并曾经点中按钮的状态下，鼠标松开且在按钮范围内，则触发一次 */
	void touchUpInside(CCObject* pSender, CCControlEvent event);
	/* 当鼠标处于按下并曾经点中按钮的状态下，鼠标松开且在按钮范围外，则触发一次 */
	void touchUpOutside(CCObject* pSender, CCControlEvent event);
};