
#pragma once
#include "base\BaseLayer.h"
#include "StarLayer.h"
#include "PlayUILayer.h"

class PlayLayer : public BaseLayer
{
public:
	PlayLayer();
	virtual ~PlayLayer();

	virtual bool init();

	void menuCloseCallback(Ref* pSender);

	CREATE_FUNC(PlayLayer);

	// ÐÇÐÇlayer
	StarLayer *starLayer;
	// UI layer
	PlayUILayer *uiLayer;
};