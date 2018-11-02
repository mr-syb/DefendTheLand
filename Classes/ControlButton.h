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
	//������ť,����name_pngΪ��ť�ı���ͼƬ��button_titleΪ��ťͼƬ��Ҫ��ʾ�����֣�numΪ���ֵ�͸����0-100��0Ϊ͸��  
	void CreateButton(const char* name_png, const char* button_title = "0", unsigned int num = 0);
	void BindButtonEven();//��д��ť�¼� 
	/* ����괦�ڰ��²��������а�ťʱ���򴥷�һ�� */
	void touchDownAction(CCObject* pSender, CCControlEvent event);
	/* ����괦�ڰ��²��������а�ť��״̬�£������밴ť��Χ���򴥷�һ�� */
	void touchDragEnter(CCObject* pSender, CCControlEvent event);
	/* ����괦�ڰ��²��������а�ť��״̬�£�����뿪��ť��Χ���򴥷�һ�� */
	void touchDragExit(CCObject* pSender, CCControlEvent event);
	/* ����괦�ڰ��²��������а�ť��״̬�£������밴ť��Χ���򴥷���ֻҪ�ﵽ�������Ͳ��ϴ��� */
	void touchDragInside(CCObject* pSender, CCControlEvent event);
	/* ����괦�ڰ��²��������а�ť��״̬�£�����뿪��ť��Χ���򴥷���ֻҪ�ﵽ�������Ͳ��ϴ��� */
	void touchDragOutside(CCObject* pSender, CCControlEvent event);
	/* ����괦�ڰ��²��������а�ť��״̬�£�����ɿ����ڰ�ť��Χ�ڣ��򴥷�һ�� */
	void touchUpInside(CCObject* pSender, CCControlEvent event);
	/* ����괦�ڰ��²��������а�ť��״̬�£�����ɿ����ڰ�ť��Χ�⣬�򴥷�һ�� */
	void touchUpOutside(CCObject* pSender, CCControlEvent event);
};