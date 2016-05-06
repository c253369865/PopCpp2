#pragma once
#include "base\BaseLayer.h"
class StartLayer : public BaseLayer
{
public:
	StartLayer();
	virtual ~StartLayer();

	virtual bool init();

	void menuCloseCallback(Ref* pSender);

	CREATE_FUNC(StartLayer);
};

