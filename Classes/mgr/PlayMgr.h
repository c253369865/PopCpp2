
#include "cocos2d.h"
#include "star/StarComNode.h"
#include "layer/PlayUILayer.h"

USING_NS_CC;

class PlayMgr
{
public:
	static PlayMgr* instance();

	static void destoryInstance();

	// 分数所在位置,显示在PlayUILayer
	Vec2 scorePos;

	/*
	成功点击一个星星
	该方法需要:
		1.使当前星星消失
		2.产生飞翔分数(分数在一开始就递增显示了)
		3.产生爆炸粒子效果
	*/
	void finishOneStar(StarComNode* star, float beginTime, int score);

	// 拥有PlayUILayer的引用
	// 这样做不是很好
	PlayUILayer *uiLayer;
};