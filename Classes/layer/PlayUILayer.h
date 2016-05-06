
#pragma once

#include "cocos2d.h"

USING_NS_CC;

class PlayUILayer : public Layer
{
public:
	bool init();

	CREATE_FUNC(PlayUILayer);

	// 飞行的分数
	void flyScoreLabel(int score, Vec2 flyTo);
};