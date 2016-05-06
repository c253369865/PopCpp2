
#include "cocos2d.h"
#include "star/StarComNode.h"
#include "layer/PlayUILayer.h"

USING_NS_CC;

class PlayMgr
{
public:
	static PlayMgr* instance();

	static void destoryInstance();

	// ��������λ��,��ʾ��PlayUILayer
	Vec2 scorePos;

	/*
	�ɹ����һ������
	�÷�����Ҫ:
		1.ʹ��ǰ������ʧ
		2.�����������(������һ��ʼ�͵�����ʾ��)
		3.������ը����Ч��
	*/
	void finishOneStar(StarComNode* star, float beginTime, int score);

	// ӵ��PlayUILayer������
	// ���������Ǻܺ�
	PlayUILayer *uiLayer;
};