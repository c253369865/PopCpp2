
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
	void setOneStar(StarComNode* star1, StarComNode* star2); // ������������Ƿ���ͬ��,
protected:
	// ������ʾ��10x10�����Ƕ�ά����
	/*
	(x, y)
	(y��)
	0,9 ---------- 9,9
	-				-
	-				-
	-				-
	-				-
	-				-
	0,0 ---------- 9,0 (x��)
	����:
	1. ��ʼ��(new)
	2. �������
	3. ����״̬
	4. ���(delete)
	*/
	StarComNode* _stars[COW][COW];
	// ���ʱ�Ļ����¼
	std::vector<StarComNode*> _needCheckStarVector;
	// ��ͬ��ɫ����������
	int sameStarCount;
};

class StarLayerUI : public BaseLayer
{
public:
	StarLayerUI(){};
	~StarLayerUI(){};

private:

};