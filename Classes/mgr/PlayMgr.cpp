
#include "PlayMgr.h"
#include "Constants.h"

static PlayMgr *mgr;

PlayMgr* PlayMgr::instance()
{
	if (!mgr)
	{
		mgr = new PlayMgr();
	}
	return mgr;
}

void PlayMgr::destoryInstance()
{
	if (mgr)
	{
		if (mgr->uiLayer)
		{
			mgr->uiLayer = nullptr;
		}
		delete mgr;
		mgr = nullptr;
	}
}

void PlayMgr::finishOneStar(StarComNode* star, float beginTime, int score)
{
	Vec2 starPos = star->getSprite()->getPosition();

	star->startDisappear(beginTime, STAR_DISAPPEAR_TIME);

	// 飞行的分数
	if (score >= 0)
	{
		if (uiLayer)
		{
			uiLayer->flyScoreLabel(score, starPos);
		}
	}
}