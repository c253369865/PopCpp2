
#pragma once
#include "base\BaseLayer.h"
#include "star\StarComNode.h"

#define COW 10

class StarLayer : public BaseLayer
{
public:
	StarLayer();
	virtual ~StarLayer();

	virtual bool init();

	StarComNode* addNodeAtPos(Vec2 pos, float scale);

	void onTouchesEnded(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event* event);

	CREATE_FUNC(StarLayer);

protected:
	void checkAllStarSelected();
	void resetStarStatus();
	void setOneStar(StarComNode* star1, StarComNode* star2); // 检查两个星星是否相同类,
protected:
	// 界面显示的10x10的星星二维数组
	/*
	(x, y)
	(y轴)
	0,9 ---------- 9,9
	-				-
	-				-
	-				-
	-				-
	-				-
	0,0 ---------- 9,0 (x轴)
	遍历:
	1. 初始化(new)
	2. 遍历输出
	3. 重设状态
	4. 清除(delete)
	*/
	StarComNode* _stars[COW][COW];
	// 点击时的缓存记录
	std::vector<StarComNode*> _needCheckStarVector;
	// 相同颜色的星星总数
	int sameStarCount;
};

class StarLayerUI : public BaseLayer
{
public:
	StarLayerUI(){};
	~StarLayerUI(){};

private:

};