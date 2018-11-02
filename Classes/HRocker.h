#ifndef __HROCKER_H__  
#define __HROCKER_H__  

#include "cocos2d.h"  

using namespace cocos2d;

//���ڱ�ʶҡ����ҡ�˵ı���  
typedef enum{
	tag_rocker,
	tag_rockerBG,
}tagForHRocker;
//���ڱ�ʶҡ�˷���  
typedef enum{
	rocker_stay,
	rocker_right,
	rocker_up,
	rocker_left,
	rocker_down,
}tagDirecton;
class HRocker :public CCLayer
{
public:
	HRocker(void);
	~HRocker(void);

	//����ҡ��(ҡ�˵Ĳ�����ͼƬ��Դ����ҡ�˱���ͼƬ��Դ������ʼ����)
	static HRocker* createHRocker(const char *rockerImageName, const char *rockerBGImageName, CCPoint position);
	//����ҡ��(��ʾҡ�ˡ�����ҡ�˴����¼�)  
	//void startRocker(bool _isStopOther);
	//�жϿ��Ƹ˷��������жϾ����ϡ��¡������˶�  
	int rocketDirection;
	void setrocketDirection(int i);//���̲�����
	//��ǰ�������߷���,�����жϾ���ĳ��򣬾��������һ��ǳ���  
	bool rocketRun;
	virtual void update(float dt);
	void touchEvent();
	//�����¼�
	virtual bool onTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	virtual void onTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
	virtual void onTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
	CREATE_FUNC(HRocker);
private:
	//�Զ����ʼ������  
	void rockerInit(const char* rockerImageName, const char* rockerBGImageName, CCPoint position);
	//�Ƿ�ɲ���ҡ��  
	bool isCanMove=false;
	//��ȡ��ǰҡ�����û�������ĽǶ�  
	float getRad(CCPoint pos1, CCPoint pos2);
	//ҡ�˱���������  
	CCPoint rockerBGPosition;
	//ҡ�˱����İ뾶  
	float rockerBGR;
};

#endif  